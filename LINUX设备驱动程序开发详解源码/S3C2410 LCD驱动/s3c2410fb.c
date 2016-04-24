//
// * linux/drivers/video/s3c2410fb.c
// *	Copyright (c) Arnaud Patard, Ben Dooks
// *
// * This file is subject to the terms and conditions of the GNU General Public
// * License.  See the file COPYING in the main directory of this archive for
// * more details.
// *
// *	    S3C2410 LCD Controller Frame Buffer Driver
// *	    based on skeletonfb.c, sa1100fb.c and others
// *
// * ChangeLog
// * 2005-04-07: Arnaud Patard <arnaud.patard@rtp-net.org>
// *      - u32 state -> pm_message_t state
// *      - S3C2410_{VA,SZ}_LCD -> S3C24XX
// *
// * 2005-03-15: Arnaud Patard <arnaud.patard@rtp-net.org>
// *      - Removed the ioctl
// *      - use readl/writel instead of __raw_writel/__raw_readl
// *
// * 2004-12-04: Arnaud Patard <arnaud.patard@rtp-net.org>
// *      - Added the possibility to set on or off the
// *      debugging mesaages
// *      - Replaced 0 and 1 by on or off when reading the
// *      /sys files
// *
// * 2005-03-23: Ben Dooks <ben-linux@fluff.org>
// *	- added non 16bpp modes
// *	- updated platform information for range of x/y/bpp
// *	- add code to ensure palette is written correctly
// *	- add pixel clock divisor control
// *
// * 2004-11-11: Arnaud Patard <arnaud.patard@rtp-net.org>
// * 	- Removed the use of currcon as it no more exist
// * 	- Added LCD power sysfs interface
// *
// * 2004-11-03: Ben Dooks <ben-linux@fluff.org>
// *	- minor cleanups
// *	- add suspend/resume support
// *	- s3c2410fb_setcolreg() not valid in >8bpp modes
// *	- removed last CONFIG_FB_S3C2410_FIXED
// *	- ensure lcd controller stopped before cleanup
// *	- added sysfs interface for backlight power
// *	- added mask for gpio configuration
// *	- ensured IRQs disabled during GPIO configuration
// *	- disable TPAL before enabling video
// *
// * 2004-09-20: Arnaud Patard <arnaud.patard@rtp-net.org>
// *      - Suppress command line options
// *
// * 2004-09-15: Arnaud Patard <arnaud.patard@rtp-net.org>
// * 	- code cleanup
// *
// * 2004-09-07: Arnaud Patard <arnaud.patard@rtp-net.org>
// * 	- Renamed from h1940fb.c to s3c2410fb.c
// * 	- Add support for different devices
// * 	- Backlight support
// *
// * 2004-09-05: Herbert P鰐zl <herbert@13thfloor.at>
// *	- added clock (de-)allocation code
// *	- added fixem fbmem option
// *
// * 2004-07-27: Arnaud Patard <arnaud.patard@rtp-net.org>
// *	- code cleanup
// *	- added a forgotten return in h1940fb_init
// *
// * 2004-07-19: Herbert P鰐zl <herbert@13thfloor.at>
// *	- code cleanup and extended debugging
// *
// * 2004-07-15: Arnaud Patard <arnaud.patard@rtp-net.org>
// *	- First version
// 
////
//图 18.3 所示为 Linux 帧缓冲设备驱动的主要结构，帧缓冲设备提供给用户空间的
//file_operations结构体由 fbmem.c 中的 file_operations 提供，而特定帧缓冲设备 fb_info
//结构体的注册、注销以及其中成员的维护，尤其是 fb_ops中成员函数的实现则由对应
//的xxxfb.c文件实现，fb_ops中的成员函数最终会操作LCD 控制器硬件寄存器.
//
//	在帧缓冲设备驱动的模块加载函数中，应该完成如下4 个工作。 
//l  申请FBI结构体的内存空间，初始化 FBI结构体中固定和可变的屏幕参数，
//即填充FBI中 fb_var_screeninfo var 和struct fb_fix_screeninfo fix成员。 
//l  根据具体LCD 屏幕的特点，完成LCD 控制器硬件的初始化。 
//l  申请帧缓冲设备的显示缓冲区空间。 
//l  注册帧缓冲设备。 
//	在帧缓冲设备驱动的模块卸载函数中，应该完成相反的工作，包括释放 FBI结构
//体内存、关闭LCD、释放显示缓冲区以及注销帧缓冲设备。 
//由于 LCD 控制器经常被集成在 SoC 上作为一个独立的硬件模块而存在（成为
//platform_device），因此，LCD 驱动中也经常包含平台驱动，这样，在帧缓冲设备驱动
//的模块加载函数中完成的工作只是注册平台驱动， 而初始化FBI结构体中的固定和可变
//参数、LCD 控制器硬件的初始化、申请帧缓冲设备的显示缓冲区空间和注册帧缓冲设
//备的工作则移交到平台驱动的探测函数中完成。
//	同样地，在使用平台驱动的情况下，释放FBI结构体内存、关闭 LCD、释放显示
//缓冲区以及注销帧缓冲设备的工作也移交到平台驱动的移除函数中完成。
//
//	虽然帧缓冲设备的 file_operations 中的成员函数，即文件操作函数已经由内核在
//fbmem.c 文件中实现，一般不再需要驱动工程师修改，但分析这些函数对于巩固字符
//设备驱动的知识以及加深对帧缓冲设备驱动的理解是大有裨益的。
//
//帧缓冲设备是一种典型的字符设备，它统一了显存，将显示缓冲区直接映射到
//用户空间。帧缓冲设备驱动 file_operations 中 VFS 接口函数由 fbmem.c 文件统一实
//现。这样，驱动工程师的工作重点将是实现针对特定设备 fb_info 中的 fb_ops 的成
//员函数，另外，理解并能灵活地修改 fb_info 中的 var 和 fix 参数非常关键。fb_info
//中的 var 参数直接和 LCD 控制器的硬件设置以及 LCD 屏幕对应。 
//在用户空间，应用程序直接按照预先设置的R、G、B位数和偏移写经过 mmap()
//映射后的显示缓冲区就可实现图形的显示，省去了内存从用户空间到内核空间的复制
//过程。


//===============打开注释:回车  /*=====================================


//#include <linux/module.h>
//#include <linux/kernel.h>
//#include <linux/errno.h>
//#include <linux/string.h>
//#include <linux/mm.h>
//#include <linux/tty.h>
//#include <linux/slab.h>
//#include <linux/delay.h>
//#include <linux/fb.h>
//#include <linux/init.h>
//#include <linux/dma-mapping.h>
//#include <linux/interrupt.h>
//#include <linux/workqueue.h>
//#include <linux/wait.h>
//#include <linux/platform_device.h>
//#include <linux/clk.h>

//#include <asm/io.h>
//#include <asm/uaccess.h>
//#include <asm/div64.h>

//#include <asm/mach/map.h>
//#include <asm/arch/regs-lcd.h>
//#include <asm/arch/regs-gpio.h>
//#include <asm/arch/fb.h>

#ifdef CONFIG_PM
//#include <linux/pm.h>
#endif

//#include "s3c2410fb.h"


static struct s3c2410fb_mach_info *mach_info;

// Debugging stuff 
#ifdef CONFIG_FB_S3C2410_DEBUG
static int debug	   = 1;
#else
static int debug	   = 0;
#endif

#define dprintk(msg...)	if (debug) { printk(KERN_DEBUG "s3c2410fb: " msg); }

// useful functions 

// s3c2410fb_set_lcdaddr
// *
// * initialise lcd controller address pointers


static void s3c2410fb_set_lcdaddr(struct s3c2410fb_info *fbi)
{
	struct fb_var_screeninfo *var = &fbi->fb->var;
	unsigned long saddr1, saddr2, saddr3;

	saddr1  = fbi->fb->fix.smem_start >> 1;
	saddr2  = fbi->fb->fix.smem_start;
	saddr2 += (var->xres * var->yres * var->bits_per_pixel)/8;
	saddr2>>= 1;

	saddr3 =  S3C2410_OFFSIZE(0) | S3C2410_PAGEWIDTH(var->xres);

	dprintk("LCDSADDR1 = 0x%08lx\n", saddr1);
	dprintk("LCDSADDR2 = 0x%08lx\n", saddr2);
	dprintk("LCDSADDR3 = 0x%08lx\n", saddr3);

	writel(saddr1, S3C2410_LCDSADDR1);
	writel(saddr2, S3C2410_LCDSADDR2);
	writel(saddr3, S3C2410_LCDSADDR3);
}

// s3c2410fb_calc_pixclk()
// *
// * calculate divisor for clk->pixclk


static unsigned int s3c2410fb_calc_pixclk(struct s3c2410fb_info *fbi,
					  unsigned long pixclk)
{
	unsigned long clk = clk_get_rate(fbi->clk);
	unsigned long long div;

	// pixclk is in picoseoncds, our clock is in Hz
	 *
	 * Hz -> picoseconds is / 10^-12
	 

	div = (unsigned long long)clk * pixclk;
	do_div(div,1000000UL);
	do_div(div,1000000UL);

	dprintk("pixclk %ld, divisor is %ld\n", pixclk, (long)div);
	return div;
}

//
// *	s3c2410fb_check_var():
// *	Get the video params out of 'var'. If a value doesn't fit, round it up,
// *	if it's too big, return -EINVAL.
// *
// s3c2410fb_check_var()函数用于检查用户设置的屏幕参数是否合理， 譬如xres、 yres
//和 BPP 都有一个范围 min～max，用户的设置如果在这个范围之外，则进行调整。另
//外，当BPP改变后，R、G、B的位域也要进行相应调整，
static int s3c2410fb_check_var(struct fb_var_screeninfo *var,
			       struct fb_info *info)
{
	struct s3c2410fb_info *fbi = info->par;

	dprintk("check_var(var=%p, info=%p)\n", var, info);

	  // 验证x/y解析度 // validate x/y resolution 

	if (var->yres > fbi->mach_info->yres.max)
		var->yres = fbi->mach_info->yres.max;
	else if (var->yres < fbi->mach_info->yres.min)
		var->yres = fbi->mach_info->yres.min;

	if (var->xres > fbi->mach_info->xres.max)
		var->yres = fbi->mach_info->xres.max;
	else if (var->xres < fbi->mach_info->xres.min)
		var->xres = fbi->mach_info->xres.min;

	 // 验证bpp  // validate bpp 

	if (var->bits_per_pixel > fbi->mach_info->bpp.max)
		var->bits_per_pixel = fbi->mach_info->bpp.max;
	else if (var->bits_per_pixel < fbi->mach_info->bpp.min)
		var->bits_per_pixel = fbi->mach_info->bpp.min;

	 // 设置R、G、B 位置  // set r/g/b positions 

	if (var->bits_per_pixel == 16) {
		var->red.offset		= 11;
		var->green.offset	= 5;
		var->blue.offset	= 0;
		var->red.length		= 5;
		var->green.length	= 6;
		var->blue.length	= 5;
		var->transp.length	= 0;
	} else {
		var->red.length		= var->bits_per_pixel;
		var->red.offset		= 0;
		var->green.length	= var->bits_per_pixel;
		var->green.offset	= 0;
		var->blue.length	= var->bits_per_pixel;
		var->blue.offset	= 0;
		var->transp.length	= 0;
	}

	return 0;
}

// s3c2410fb_activate_var
// *
// * activate (set) the controller from the given framebuffer
// * information

 // 根据var和fix参数设置LCD控制器的硬件寄存器  
static void s3c2410fb_activate_var(struct s3c2410fb_info *fbi,
				   struct fb_var_screeninfo *var)
{
	fbi->regs.lcdcon1 &= ~S3C2410_LCDCON1_MODEMASK;

	dprintk("%s: var->xres  = %d\n", __FUNCTION__, var->xres);
	dprintk("%s: var->yres  = %d\n", __FUNCTION__, var->yres);
	dprintk("%s: var->bpp   = %d\n", __FUNCTION__, var->bits_per_pixel);

	switch (var->bits_per_pixel) {
	case 1: //设置bpp
		fbi->regs.lcdcon1 |= S3C2410_LCDCON1_TFT1BPP;
		break;
	case 2:
		fbi->regs.lcdcon1 |= S3C2410_LCDCON1_TFT2BPP;
		break;
	case 4:
		fbi->regs.lcdcon1 |= S3C2410_LCDCON1_TFT4BPP;
		break;
	case 8:
		fbi->regs.lcdcon1 |= S3C2410_LCDCON1_TFT8BPP;
		break;
	case 16:
		fbi->regs.lcdcon1 |= S3C2410_LCDCON1_TFT16BPP;
		break;
	}

	// check to see if we need to update sync/borders 
	 // 检查是否需要更新同步和边界  
	if (!fbi->mach_info->fixed_syncs) {
		dprintk("setting vert: up=%d, low=%d, sync=%d\n",
			var->upper_margin, var->lower_margin,
			var->vsync_len);

		dprintk("setting horz: lft=%d, rt=%d, sync=%d\n",
			var->left_margin, var->right_margin,
			var->hsync_len);

		fbi->regs.lcdcon2 =
			S3C2410_LCDCON2_VBPD(var->upper_margin - 1) |
			S3C2410_LCDCON2_VFPD(var->lower_margin - 1) |
			S3C2410_LCDCON2_VSPW(var->vsync_len - 1);

		fbi->regs.lcdcon3 =
			S3C2410_LCDCON3_HBPD(var->right_margin - 1) |
			S3C2410_LCDCON3_HFPD(var->left_margin - 1);

		fbi->regs.lcdcon4 &= ~S3C2410_LCDCON4_HSPW(0xff);
		fbi->regs.lcdcon4 |=  S3C2410_LCDCON4_HSPW(var->hsync_len - 1);
	}

	 // 更新 X/Y 信息  // update X/Y info 

	fbi->regs.lcdcon2 &= ~S3C2410_LCDCON2_LINEVAL(0x3ff);
	fbi->regs.lcdcon2 |=  S3C2410_LCDCON2_LINEVAL(var->yres - 1);

	fbi->regs.lcdcon3 &= ~S3C2410_LCDCON3_HOZVAL(0x7ff);
	fbi->regs.lcdcon3 |=  S3C2410_LCDCON3_HOZVAL(var->xres - 1);

	if (var->pixclock > 0) {
		int clkdiv = s3c2410fb_calc_pixclk(fbi, var->pixclock);

		clkdiv = (clkdiv / 2) -1;
		if (clkdiv < 0)
			clkdiv = 0;

		fbi->regs.lcdcon1 &= ~S3C2410_LCDCON1_CLKVAL(0x3ff);
		fbi->regs.lcdcon1 |=  S3C2410_LCDCON1_CLKVAL(clkdiv);
	}

	 // 重写LCD控制器寄存器 // write new registers 

	dprintk("new register set:\n");
	dprintk("lcdcon[1] = 0x%08lx\n", fbi->regs.lcdcon1);
	dprintk("lcdcon[2] = 0x%08lx\n", fbi->regs.lcdcon2);
	dprintk("lcdcon[3] = 0x%08lx\n", fbi->regs.lcdcon3);
	dprintk("lcdcon[4] = 0x%08lx\n", fbi->regs.lcdcon4);
	dprintk("lcdcon[5] = 0x%08lx\n", fbi->regs.lcdcon5);

	writel(fbi->regs.lcdcon1 & ~S3C2410_LCDCON1_ENVID, S3C2410_LCDCON1);
	writel(fbi->regs.lcdcon2, S3C2410_LCDCON2);
	writel(fbi->regs.lcdcon3, S3C2410_LCDCON3);
	writel(fbi->regs.lcdcon4, S3C2410_LCDCON4);
	writel(fbi->regs.lcdcon5, S3C2410_LCDCON5);

	// set lcd address pointers 
	s3c2410fb_set_lcdaddr(fbi);

	writel(fbi->regs.lcdcon1, S3C2410_LCDCON1);
}


//
// *      s3c2410fb_set_par - Optional function. Alters the hardware state.
// *      @info: frame buffer structure that represents a single frame buffer
// *
// s3c2410fb_set_par()函数根据用户设置的可变参数 var 调整固定参数 fix，修改 fix
//的line_length，最终将相应的修改在硬件上激活，
static int s3c2410fb_set_par(struct fb_info *info)
{
	struct s3c2410fb_info *fbi = info->par;
	struct fb_var_screeninfo *var = &info->var;

	if (var->bits_per_pixel == 16)
		fbi->fb->fix.visual = FB_VISUAL_TRUECOLOR;
	else
		fbi->fb->fix.visual = FB_VISUAL_PSEUDOCOLOR;

	fbi->fb->fix.line_length     = (var->width*var->bits_per_pixel)/8;

	 // 激活新的配置  // activate this new configuration 

	s3c2410fb_activate_var(fbi, var);
	return 0;
}

static void schedule_palette_update(struct s3c2410fb_info *fbi,
				    unsigned int regno, unsigned int val)
{
	unsigned long flags;
	unsigned long irqen;

	local_irq_save(flags);

	fbi->palette_buffer[regno] = val;

	if (!fbi->palette_ready) {
		fbi->palette_ready = 1;

		// enable IRQ 
		irqen = readl(S3C2410_LCDINTMSK);
		irqen &= ~S3C2410_LCDINT_FRSYNC;
		writel(irqen, S3C2410_LCDINTMSK);
	}

	local_irq_restore(flags);
}

// from pxafb.c 
static inline unsigned int chan_to_field(unsigned int chan, struct fb_bitfield *bf)
{
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	return chan << bf->offset;
}

static int s3c2410fb_setcolreg(unsigned regno,
			       unsigned red, unsigned green, unsigned blue,
			       unsigned transp, struct fb_info *info)
{
	struct s3c2410fb_info *fbi = info->par;
	unsigned int val;

	// dprintk("setcol: regno=%d, rgb=%d,%d,%d\n", regno, red, green, blue); 

	switch (fbi->fb->fix.visual) {
	case FB_VISUAL_TRUECOLOR:
		// 真彩色，设置伪颜色表 true-colour, use pseuo-palette 
		if (regno < 16) {
			u32 *pal = fbi->fb->pseudo_palette;

			val  = chan_to_field(red,   &fbi->fb->var.red);
			val |= chan_to_field(green, &fbi->fb->var.green);
			val |= chan_to_field(blue,  &fbi->fb->var.blue);

			pal[regno] = val;
		}
		break;

	case FB_VISUAL_PSEUDOCOLOR:
		if (regno < 256) {
			 // RGB565模式  // currently assume RGB 5-6-5 mode 
			val  = ((red   >>  0) & 0xf800);
			val |= ((green >>  5) & 0x07e0);
			val |= ((blue  >> 11) & 0x001f);

			writel(val, S3C2410_TFTPAL(regno));
			schedule_palette_update(fbi, regno, val);
		}

		break;

	default:
		return 1;   // unknown type 
	}

	return 0;
}


//*
// *      s3c2410fb_blank
// *	@blank_mode: the blank mode we want.
// *	@info: frame buffer structure that represents a single frame buffer
// *
// *	Blank the screen if blank_mode != 0, else unblank. Return 0 if
// *	blanking succeeded, != 0 if un-/blanking failed due to e.g. a
// *	video mode which doesn't support it. Implements VESA suspend
// *	and powerdown modes on hardware that supports disabling hsync/vsync:
// *	blank_mode == 2: suspend vsync
// *	blank_mode == 3: suspend hsync
// *	blank_mode == 4: powerdown
// *
// *	Returns negative errno on error, or zero on success.
// *
 
static int s3c2410fb_blank(int blank_mode, struct fb_info *info)
{
	dprintk("blank(mode=%d, info=%p)\n", blank_mode, info);

	if (mach_info == NULL)
		return -EINVAL;

	if (blank_mode == FB_BLANK_UNBLANK)
		writel(0x0, S3C2410_TPAL);
	else {
		dprintk("setting TPAL to output 0x000000\n");
		writel(S3C2410_TPAL_EN, S3C2410_TPAL);
	}

	return 0;
}

static int s3c2410fb_debug_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%s\n", debug ? "on" : "off");
}
static int s3c2410fb_debug_store(struct device *dev, struct device_attribute *attr,
					   const char *buf, size_t len)
{
	if (mach_info == NULL)
		return -EINVAL;

	if (len < 1)
		return -EINVAL;

	if (strnicmp(buf, "on", 2) == 0 ||
	    strnicmp(buf, "1", 1) == 0) {
		debug = 1;
		printk(KERN_DEBUG "s3c2410fb: Debug On");
	} else if (strnicmp(buf, "off", 3) == 0 ||
		   strnicmp(buf, "0", 1) == 0) {
		debug = 0;
		printk(KERN_DEBUG "s3c2410fb: Debug Off");
	} else {
		return -EINVAL;
	}

	return len;
}


static DEVICE_ATTR(debug, 0666,
		   s3c2410fb_debug_show,
		   s3c2410fb_debug_store);

static struct fb_ops s3c2410fb_ops = {
	.owner		= THIS_MODULE,
	.fb_check_var   = s3c2410fb_check_var,//检查可变参数 
	.fb_set_par        = s3c2410fb_set_par,  //设置参数 
	.fb_blank           = s3c2410fb_blank,  //显示空白 
	.fb_setcolreg   = s3c2410fb_setcolreg, //设置颜色表 
	.fb_fillrect    = cfb_fillrect, //矩形填充 
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
};


//
// * s3c2410fb_map_video_memory():
// *	Allocates the DRAM memory for the frame buffer.  This buffer is
// *	remapped into a non-cached, non-buffered, memory region to
// *	allow palette and pixel writes to occur without flushing the
// *	cache.  Once this area is remapped, all virtual memory
// *	access to the video memory should occur at the new region.
//	在嵌入式系统中，一种常见的方式是直接在 RAM 空间中分配一段显示缓冲区
//writecombining意味着“写合并” ，它允许写入的数据被合并，并临时保存在写合
//并缓冲区（WCB）中，直到进行一次 burst 传输而不再需要多次 single 传输。通过
//dma_alloc_ writecombine()分配的显示缓冲区不会出现cache一致性问题，这一点类似
//于dma_alloc_ coherent()。
 
static int __init s3c2410fb_map_video_memory(struct s3c2410fb_info *fbi)
{
	dprintk("map_video_memory(fbi=%p)\n", fbi);

	fbi->map_size = PAGE_ALIGN(fbi->fb->fix.smem_len + PAGE_SIZE);
	fbi->map_cpu  = dma_alloc_writecombine(fbi->dev, fbi->map_size,
					       &fbi->map_dma, GFP_KERNEL);//分配内存 

	fbi->map_size = fbi->fb->fix.smem_len; //显示缓冲区大小

	if (fbi->map_cpu) {
		// prevent initial garbage on screen 
		dprintk("map_video_memory: clear %p:%08x\n",
			fbi->map_cpu, fbi->map_size);
		memset(fbi->map_cpu, 0xf0, fbi->map_size);

		fbi->screen_dma		= fbi->map_dma;
		fbi->fb->screen_base	= fbi->map_cpu;
		fbi->fb->fix.smem_start  = fbi->screen_dma;//赋值 fix 的smem_start

		dprintk("map_video_memory: dma=%08x cpu=%p size=%08x\n",
			fbi->map_dma, fbi->map_cpu, fbi->fb->fix.smem_len);
	}

	return fbi->map_cpu ? 0 : -ENOMEM;
}
//在分配显示缓冲区时一定要考虑 cache 的一致性问题，因为系统往往会通过
//DMA 方式搬移显示数据。合适的方式是使用 dma_alloc_writecombine()函数分配
//一段 writecombining 区 域
static inline void s3c2410fb_unmap_video_memory(struct s3c2410fb_info *fbi)
{ //释放显示缓冲区
	dma_free_writecombine(fbi->dev,fbi->map_size,fbi->map_cpu, fbi->map_dma);
}

static inline void modify_gpio(void __iomem *reg,
			       unsigned long set, unsigned long mask)
{
	unsigned long tmp;

	tmp = readl(reg) & ~mask;
	writel(tmp | set, reg);
}


//
// * s3c2410fb_init_registers - Initialise all LCD-related registers
 

static int s3c2410fb_init_registers(struct s3c2410fb_info *fbi)
{
	unsigned long flags;

	// Initialise LCD with values from haret 

	local_irq_save(flags);

	// modify the gpio(s) with interrupts set (bjd) 

	modify_gpio(S3C2410_GPCUP,  mach_info->gpcup,  mach_info->gpcup_mask);
	modify_gpio(S3C2410_GPCCON, mach_info->gpccon, mach_info->gpccon_mask);
	modify_gpio(S3C2410_GPDUP,  mach_info->gpdup,  mach_info->gpdup_mask);
	modify_gpio(S3C2410_GPDCON, mach_info->gpdcon, mach_info->gpdcon_mask);

	local_irq_restore(flags);

	writel(fbi->regs.lcdcon1, S3C2410_LCDCON1);
	writel(fbi->regs.lcdcon2, S3C2410_LCDCON2);
	writel(fbi->regs.lcdcon3, S3C2410_LCDCON3);
	writel(fbi->regs.lcdcon4, S3C2410_LCDCON4);
	writel(fbi->regs.lcdcon5, S3C2410_LCDCON5);

 	s3c2410fb_set_lcdaddr(fbi);

	dprintk("LPCSEL    = 0x%08lx\n", mach_info->lpcsel);
	writel(mach_info->lpcsel, S3C2410_LPCSEL);

	dprintk("replacing TPAL %08x\n", readl(S3C2410_TPAL));

	// ensure temporary palette disabled 
	writel(0x00, S3C2410_TPAL);

	// Enable video by setting the ENVID bit to 1 
	fbi->regs.lcdcon1 |= S3C2410_LCDCON1_ENVID;
	writel(fbi->regs.lcdcon1, S3C2410_LCDCON1);
	return 0;
}

static void s3c2410fb_write_palette(struct s3c2410fb_info *fbi)
{
	unsigned int i;
	unsigned long ent;

	fbi->palette_ready = 0;

	for (i = 0; i < 256; i++) {
		if ((ent = fbi->palette_buffer[i]) == PALETTE_BUFF_CLEAR)
			continue;

		writel(ent, S3C2410_TFTPAL(i));

		// it seems the only way to know exactly
		 * if the palette wrote ok, is to check
		 * to see if the value verifies ok
		 

		if (readw(S3C2410_TFTPAL(i)) == ent)
			fbi->palette_buffer[i] = PALETTE_BUFF_CLEAR;
		else
			fbi->palette_ready = 1;   // retry 
	}
}

static irqreturn_t s3c2410fb_irq(int irq, void *dev_id, struct pt_regs *r)
{
	struct s3c2410fb_info *fbi = dev_id;
	unsigned long lcdirq = readl(S3C2410_LCDINTPND);

	if (lcdirq & S3C2410_LCDINT_FRSYNC) {
		if (fbi->palette_ready)
			s3c2410fb_write_palette(fbi);

		writel(S3C2410_LCDINT_FRSYNC, S3C2410_LCDINTPND);
		writel(S3C2410_LCDINT_FRSYNC, S3C2410_LCDSRCPND);
	}

	return IRQ_HANDLED;
}

static char driver_name[]="s3c2410fb";

static int __init s3c2410fb_probe(struct platform_device *pdev)
{
	struct s3c2410fb_info *info;
	struct fb_info	   *fbinfo;
	struct s3c2410fb_hw *mregs;
	int ret;
	int irq;
	int i;

	mach_info = pdev->dev.platform_data;//获得mach_info结构体指针
	if (mach_info == NULL) {
		dev_err(&pdev->dev,"no platform data for lcd, cannot attach\n");
		return -EINVAL;
	}

	mregs = &mach_info->regs; //获得mach_info结构体中的寄存器指针 

	irq = platform_get_irq(pdev, 0); //获得IRQ号 
	if (irq < 0) {
		dev_err(&pdev->dev, "no irq for device\n");
		return -ENOENT;
	}
	 //分配fb_info结构体 
	fbinfo = framebuffer_alloc(sizeof(struct s3c2410fb_info), &pdev->dev);
	if (!fbinfo) {
		return -ENOMEM;
	}


	info = fbinfo->par; //可变参数 
	info->fb = fbinfo; //固定参数 
	platform_set_drvdata(pdev, fbinfo);//设置平台设备数据 

	dprintk("devinit\n");

	strcpy(fbinfo->fix.id, driver_name);

	memcpy(&info->regs, &mach_info->regs, sizeof(info->regs));

	info->mach_info		    = pdev->dev.platform_data;
	 //初始化固定参数 
	fbinfo->fix.type	    = FB_TYPE_PACKED_PIXELS;
	fbinfo->fix.type_aux	    = 0;
	fbinfo->fix.xpanstep	    = 0;
	fbinfo->fix.ypanstep	    = 0;
	fbinfo->fix.ywrapstep	    = 0;
	fbinfo->fix.accel	    = FB_ACCEL_NONE;
	 //初始化可变参数 
	fbinfo->var.nonstd	    = 0;
	fbinfo->var.activate	    = FB_ACTIVATE_NOW;
	fbinfo->var.height	    = mach_info->height;
	fbinfo->var.width	    = mach_info->width;
	fbinfo->var.accel_flags     = 0;
	fbinfo->var.vmode	    = FB_VMODE_NONINTERLACED;

	fbinfo->fbops		    = &s3c2410fb_ops;
	fbinfo->flags		    = FBINFO_FLAG_DEFAULT;
	fbinfo->pseudo_palette      = &info->pseudo_pal;
	 //初始化可变参数中的分辨率和bpp 
	fbinfo->var.xres	    = mach_info->xres.defval;
	fbinfo->var.xres_virtual    = mach_info->xres.defval;
	fbinfo->var.yres	    = mach_info->yres.defval;
	fbinfo->var.yres_virtual    = mach_info->yres.defval;
	fbinfo->var.bits_per_pixel  = mach_info->bpp.defval;
	 //初始化可变参数中的上下边界和垂直同步 
	fbinfo->var.upper_margin    = S3C2410_LCDCON2_GET_VBPD(mregs->lcdcon2) + 1;
	fbinfo->var.lower_margin    = S3C2410_LCDCON2_GET_VFPD(mregs->lcdcon2) + 1;
	fbinfo->var.vsync_len	    = S3C2410_LCDCON2_GET_VSPW(mregs->lcdcon2) + 1;
	 //初始化可变参数中的左右边界和水平同步 
	fbinfo->var.left_margin	    = S3C2410_LCDCON3_GET_HFPD(mregs->lcdcon3) + 1;
	fbinfo->var.right_margin    = S3C2410_LCDCON3_GET_HBPD(mregs->lcdcon3) + 1;
	fbinfo->var.hsync_len	    = S3C2410_LCDCON4_GET_HSPW(mregs->lcdcon4) + 1;
	 //设置可变参数中的R/G/B位数和位置 
	fbinfo->var.red.offset      = 11;
	fbinfo->var.green.offset    = 5;
	fbinfo->var.blue.offset     = 0;
	fbinfo->var.transp.offset   = 0;
	fbinfo->var.red.length      = 5;
	fbinfo->var.green.length    = 6;
	fbinfo->var.blue.length     = 5;
	fbinfo->var.transp.length   = 0;
	fbinfo->fix.smem_len        =	mach_info->xres.max *
					mach_info->yres.max *
					mach_info->bpp.max / 8;//buffer长度

	for (i = 0; i < 256; i++)
		info->palette_buffer[i] = PALETTE_BUFF_CLEAR;
	 //申请内存区域 
	if (!request_mem_region((unsigned long)S3C24XX_VA_LCD, SZ_1M, "s3c2410-lcd")) {
		ret = -EBUSY;
		goto dealloc_fb;
	}


	dprintk("got LCD region\n");
	  //申请中断 
	ret = request_irq(irq, s3c2410fb_irq, SA_INTERRUPT, pdev->name, info);
	if (ret) {
		dev_err(&pdev->dev, "cannot get irq %d - err %d\n", irq, ret);
		ret = -EBUSY;
		goto release_mem;
	}
	 //获得时钟源并使能 
	info->clk = clk_get(NULL, "lcd");
	if (!info->clk || IS_ERR(info->clk)) {
		printk(KERN_ERR "failed to get lcd clock source\n");
		ret = -ENOENT;
		goto release_irq;
	}

	clk_enable(info->clk);
	dprintk("got and enabled clock\n");

	msleep(1);

	 // 初始化显示缓冲区 // Initialize video memory 
	ret = s3c2410fb_map_video_memory(info);
	if (ret) {
		printk( KERN_ERR "Failed to allocate video RAM: %d\n", ret);
		ret = -ENOMEM;
		goto release_clock;
	}
	dprintk("got video memory\n");

	ret = s3c2410fb_init_registers(info);//初始化 S3C2410 的LCD 控制器的寄存器 
	 //检查可变参数
	ret = s3c2410fb_check_var(&fbinfo->var, fbinfo);
	 //注册fb_info 
	ret = register_framebuffer(fbinfo);
	if (ret < 0) {
		printk(KERN_ERR "Failed to register framebuffer device: %d\n", ret);
		goto free_video_memory;
	}

	  // 创建设备文件  // create device files 
	device_create_file(&pdev->dev, &dev_attr_debug);

	printk(KERN_INFO "fb%d: %s frame buffer device\n",
		fbinfo->node, fbinfo->fix.id);

	return 0;

free_video_memory:
	s3c2410fb_unmap_video_memory(info);
release_clock:
	clk_disable(info->clk);
	clk_put(info->clk);
release_irq:
	free_irq(irq,info);
release_mem:
 	release_mem_region((unsigned long)S3C24XX_VA_LCD, S3C24XX_SZ_LCD);
dealloc_fb:
	framebuffer_release(fbinfo);
	return ret;
}

// s3c2410fb_stop_lcd
// *
// * shutdown the lcd controller


static void s3c2410fb_stop_lcd(void)
{
	unsigned long flags;
	unsigned long tmp;

	local_irq_save(flags);

	tmp = readl(S3C2410_LCDCON1);
	writel(tmp & ~S3C2410_LCDCON1_ENVID, S3C2410_LCDCON1);

	local_irq_restore(flags);
}

//
// *  Cleanup
 
static int s3c2410fb_remove(struct platform_device *pdev)
{
	struct fb_info	   *fbinfo = platform_get_drvdata(pdev);
	struct s3c2410fb_info *info = fbinfo->par;
	int irq;

	s3c2410fb_stop_lcd();//停止LCD 
	msleep(1);

	s3c2410fb_unmap_video_memory(info); //释放显示缓冲区 

 	if (info->clk) { //释放时钟源 
 		clk_disable(info->clk);
 		clk_put(info->clk);
 		info->clk = NULL;
	}

	irq = platform_get_irq(pdev, 0); //获得平台设备使用的IRQ
	free_irq(irq,info);//释放IRQ
	 //释放内存区域 
	release_mem_region((unsigned long)S3C24XX_VA_LCD, S3C24XX_SZ_LCD);
	unregister_framebuffer(fbinfo); //注销fb_info 

	return 0;
}

#ifdef CONFIG_PM

// suspend and resume support for the lcd controller 

static int s3c2410fb_suspend(struct platform_device *dev, pm_message_t state)
{
	struct fb_info	   *fbinfo = platform_get_drvdata(dev);
	struct s3c2410fb_info *info = fbinfo->par;

	s3c2410fb_stop_lcd();//停止LCD 

	// sleep before disabling the clock, we need to ensure
	// * the LCD DMA engine is not going to get back on the bus
	// * before the clock goes off again (bjd) 

	msleep(1); //在停止时钟源前延迟
	clk_disable(info->clk);//停止时钟源

	return 0;
}

static int s3c2410fb_resume(struct platform_device *dev)
{
	struct fb_info	   *fbinfo = platform_get_drvdata(dev);
	struct s3c2410fb_info *info = fbinfo->par;

	clk_enable(info->clk);  //启动时钟源 
	msleep(1);

	s3c2410fb_init_registers(info);//初始化LCD控制器寄存器 

	return 0;
}

#else //不支持能量管理 
#define s3c2410fb_suspend NULL
#define s3c2410fb_resume  NULL
#endif

static struct platform_driver s3c2410fb_driver = {
	.probe		= s3c2410fb_probe, //平台驱动探测函数 
	.remove		= s3c2410fb_remove, //平台驱动移除函数 
	.suspend	= s3c2410fb_suspend,
	.resume		= s3c2410fb_resume,
	.driver		= {
		.name	= "s3c2410-lcd", //驱动名 
		.owner	= THIS_MODULE,
	},
};

int __devinit s3c2410fb_init(void)
{
	return platform_driver_register(&s3c2410fb_driver);
}

static void __exit s3c2410fb_cleanup(void)
{
	platform_driver_unregister(&s3c2410fb_driver);
}


//module_init(s3c2410fb_init);
//module_exit(s3c2410fb_cleanup);

//MODULE_AUTHOR("Arnaud Patard <arnaud.patard@rtp-net.org>, Ben Dooks <ben-linux@fluff.org>");
//MODULE_DESCRIPTION("Framebuffer driver for the s3c2410");
//MODULE_LICENSE("GPL");
