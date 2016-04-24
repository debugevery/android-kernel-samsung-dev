/* linux/drivers/mtd/nand/s3c2410.c
 * 支持depends on ARCH_S3C2410 || ARCH_S3C64XX
 * Copyright 漏 2004-2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Samsung S3C2410/S3C2440/S3C2412 NAND driver================zjz
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
【 Nand flash 驱动工作原理】 
在介绍具体如何写 Nand Flash 驱动之前，我们先要了解，大概的，整个系统，和 Nand Flash 相关的部分的驱动工作流程，这样，对于后面的驱动实现，才能更加清楚机制，才更容易实现，否则就是，即使写完了代码，也还是没搞懂系统是如何工作的了。 
让我们以最常见的， Linux 内核中已经有的三星的 Nand Flash 驱动，来解释 Nand Flash 驱动具体流程和原理。 
此处是参考 2.6.29 版本的 Linux 源码中的 /drivers/mtd/nand/s3c2410.c ，以 2410 为例。 
1.       在 nand flash 驱动加载后，第一步，就是去调用对应的 init 函数， s3c2410_nand_init, 去将在 nand flash 驱动注册到 Linux 驱动框架中。 
2.       驱动本身，真正开始，是从 probe 函数， s3c2410_nand_probe->s3c24xx_nand_probe, 
在 probe 过程中，去用 clk_enable 打开 nand flash 控制器的 clock 时钟，用 request_mem_region 去申请驱动所需要的一些内存等相关资源。然后，在 s3c2410_nand_inithw 中，去初始化硬件相关的部分，主要是关于时钟频率的计算，以及启用 nand flash 控制器，使得硬件初始化好了，后面才能正常工作。 
3.       需要多解释一下的，是这部分代码： s3c24xx_nand_probe
4.       等所有的参数都计算好了，函数都挂载完毕，系统就可以正常工作了。 
上层访问你的 nand falsh 中的数据的时候，通过 MTD 层，一层层调用，最后调用到你所实现的那些底层访问硬件数据 / 缓存的函数中。 

【 Linux 下 nand flash 驱动编写步骤简介】 
关于上面提到的，在 nand_scan_tail 的时候，系统会根据你的驱动，如果没有实现一些函数的话，那么就用系统默认的。如果实现了自己的函数，就用你的。 
估计很多人就会问了，那么到底我要实现哪些函数呢，而又有哪些是可以不实现，用系统默认的就可以了呢。 
此问题的，就是我们下面要介绍的，也就是，你要实现的，你的驱动最少要做哪些工作，才能使整个 nand flash 工作起来。 
1.       对于驱动框架部分 
其实，要了解，关于驱动框架部分，你所要做的事情的话，只要看看三星的整个 nand flash 驱动中的这个结构体，就差不多了： 
static struct platform_driver s3c2410_nand_driver 
2.       对于 nand flash 底层操作实现部分 
而对于底层硬件操作的有些函数，总体上说，都可以在上面提到的 s3c2410_nand_init_chip 中找到： 

而我们要实现的底层函数，也就是上面蓝色标出来的一些函数而已： 
（ 1 ） s3c2410_nand_write_buf 和 s3c2410_nand_read_buf ：这是两个最基本的操作函数，其功能，就是往你的 nand flash 的控制器中的 FIFO 读写数据。一般情况下，是 MTD 上层的操作，比如要读取一页的数据，那么在发送完相关的读命令和等待时间之后，就会调用到你底层的 read_buf ，去 nand Flash 的 FIFO 中，一点点把我们要的数据，读取出来，放到我们制定的内存的缓存中去。写操作也是类似，将我们内存中的数据，写到 Nand Flash 的 FIFO 中去。具体的数据流向，参考上面的图 4 。 
（ 2 ） s3c2410_nand_select_chip ： 实现 Nand Flash 的片选。 
（ 3 ） s3c2410_nand_hwcontrol ：给底层发送命令或地址，或者设置具体操作的模式，都是通过此函数。 
（ 4 ） s3c2410_nand_devready ： Nand Flash 的一些操作，比如读一页数据，写入（编程）一页数据，擦除一个块，都是需要一定时间的，在命发送完成后，就是硬件开始忙着工作的时候了，而硬件什么时候完成这些操作，什么时候不忙了，变就绪了，就是通过这个函数去检查状态的。一般具体实现都是去读硬件的一个状态寄存器，其中某一位是否是 1 ，对应着是出于“就绪 / 不忙”还是“忙”的状态。这个寄存器，也就是我们前面分析时序图中的 R/B# 。 
（ 5 ） s3c2410_nand_enable_hwecc ： 在硬件支持的前提下，前面设置了硬件 ECC 的话，要实现这个函数，用于每次在读写操作前，通过设置对应的硬件寄存器的某些位，使得启用硬件 ECC ，这样在读写操作完成后，就可以去读取硬件校验产生出来的 ECC 数值了。 
（ 6 ） s3c2410_nand_calculate_ecc ：如果是上面提到的硬件 ECC 的话，就不用我们用软件去实现校验算法了，而是直接去读取硬件产生的 ECC 数值就可以了。 
（ 7 ） s3c2410_nand_correct_data ：当实际操作过程中，读取出来的数据所对应的硬件或软件计算出来的 ECC ，和从 oob 中读出来的 ECC 不一样的时候，就是说明数据有误了，就需要调用此函数去纠正错误。对于现在 SLC 常见的 ECC 算法来说，可以发现 2 位，纠正 1 位。如果错误大于 1 位，那么就无法纠正回来了。一般情况下，出错超过 1 位的，好像几率不大。至少我看到的不是很大。更复杂的情况和更加注重数据安全的情况下，一般是需要另外实现更高效和检错和纠错能力更强的 ECC 算法的。 
当然，除了这些你必须实现的函数之外，在你更加熟悉整个框架之后，你可以根据你自己的 nand flash 的特点，去实现其他一些原先用系统默认但是效率不高的函数，而用自己的更高效率的函数替代他们，以提升你的 nand flash 的整体性能和效率。 
*/
/*
对于MTD(memory technology device)
将所有的方法封装在两个结构体中 mtd_info 和 nand_chip
在注册驱动时，调用nand_init_chip，最终注册的就是这两个结构体

mtd_info 和 nand_chip的一些结构封装，对于移植（更换新的NAND FLASH，或者不同的SOC），只要改写底层（就是第二层）的相关函数就可以。
比如读数据的命令，在MTD封装中包括两部分，一部分是nand_chip->cmdctrl发送命令，一部分是nand_chip->read_page，而这两部分都封装在mtd_info *info的info->read中，Write和erase，isbad_block类
至于ECC部分（移植相关，可以参看stage1中copy_main函数的实现），根据不同的页大小配置不同的ECC.Layout
其相关操作在nand_chip中,所以移植过程只要注意修改nand_chip结构下的操作方法即可。

驱动的注册和相关调用
U-BOOT中注册驱动的时候调用 nand_init_chip
有四个调用，Board_nand_init(mtd)，Nand_scan_ident，Board_nand_ecc_init，
Nand_scan_tail

       对于这四个调用不细说，注册之后只要学会第三层相关调用。
       得到对应的mtd_info 结构指针之后，就可以调用相应方法了
       包括
       Info->read，Info->write，Info->isbad_block，Info->erase等
       关键的问题在于如何得到mtd_info结构指针，而这个取决于写的上层程序，只要在希望读写的分区的结构中嵌入mtd_info *info结构指针，并对其初始化，对相应的分区进行操作便可以调用相应函数。

*/
#ifdef CONFIG_MTD_NAND_S3C2410_DEBUG
#define DEBUG
#endif

//#include <linux/module.h>
//#include <linux/types.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
//#include <linux/string.h>
//#include <linux/ioport.h>
//#include <linux/platform_device.h>
//#include <linux/delay.h>
//#include <linux/err.h>
//#include <linux/slab.h>
//#include <linux/clk.h>
//#include <linux/cpufreq.h>

//#include <linux/mtd/mtd.h>
//#include <linux/mtd/nand.h>
//#include <linux/mtd/nand_ecc.h>
//#include <linux/mtd/partitions.h>

//#include <asm/io.h>

//#include <plat/regs-nand.h>
//#include <plat/nand.h>

#ifdef CONFIG_MTD_NAND_S3C2410_HWECC
static int hardware_ecc = 1;//设置ECC方式
#else
static int hardware_ecc = 0;
#endif

#ifdef CONFIG_MTD_NAND_S3C2410_CLKSTOP
static int clock_stop = 1;
#else
static const int clock_stop = 0;
#endif


/* new oob placement block for use with hardware ecc generation
 */

static struct nand_ecclayout nand_hw_eccoob = {
	.eccbytes = 3,
	.eccpos = {0, 1, 2},
	.oobfree = {{8, 8}}
};

/* controller and mtd information */

struct s3c2410_nand_info;

/**
 * struct s3c2410_nand_mtd - driver MTD structure
 * @mtd: The MTD instance to pass to the MTD layer.
 * @chip: The NAND chip information.
 * @set: The platform information supplied for this set of NAND chips.
 * @info: Link back to the hardware information.
 * @scan_res: The result from calling nand_scan_ident().
*/
struct s3c2410_nand_mtd {
	struct mtd_info			mtd;
	struct nand_chip		chip;
	struct s3c2410_nand_set		*set;
	struct s3c2410_nand_info	*info;
	int				scan_res;
};

enum s3c_cpu_type {
	TYPE_S3C2410,
	TYPE_S3C2412,
	TYPE_S3C2440,
};

/* overview of the s3c2410 nand state */

/**
 * struct s3c2410_nand_info - NAND controller state.
 * @mtds: An array of MTD instances on this controoler.
 * @platform: The platform data for this board.
 * @device: The platform device we bound to.
 * @area: The IO area resource that came from request_mem_region().
 * @clk: The clock resource for this controller.
 * @regs: The area mapped for the hardware registers described by @area.
 * @sel_reg: Pointer to the register controlling the NAND selection.
 * @sel_bit: The bit in @sel_reg to select the NAND chip.
 * @mtd_count: The number of MTDs created from this controller.
 * @save_sel: The contents of @sel_reg to be saved over suspend.
 * @clk_rate: The clock rate from @clk.
 * @cpu_type: The exact type of this controller.
 */
struct s3c2410_nand_info {
	/* mtd info */
	struct nand_hw_control		controller;
	struct s3c2410_nand_mtd		*mtds;
	struct s3c2410_platform_nand	*platform;

	/* device info */
	struct device			*device;
	struct resource			*area;
	struct clk			*clk;
	void __iomem			*regs;
	void __iomem			*sel_reg;
	int				sel_bit;
	int				mtd_count;
	unsigned long			save_sel;
	unsigned long			clk_rate;

	enum s3c_cpu_type		cpu_type;

#ifdef CONFIG_CPU_FREQ
	struct notifier_block	freq_transition;
#endif
};

/* conversion functions */

static struct s3c2410_nand_mtd *s3c2410_nand_mtd_toours(struct mtd_info *mtd)
{
	return container_of(mtd, struct s3c2410_nand_mtd, mtd);
}

static struct s3c2410_nand_info *s3c2410_nand_mtd_toinfo(struct mtd_info *mtd)
{
	return s3c2410_nand_mtd_toours(mtd)->info;
}

static struct s3c2410_nand_info *to_nand_info(struct platform_device *dev)
{
	return platform_get_drvdata(dev);
}

static struct s3c2410_platform_nand *to_nand_plat(struct platform_device *dev)
{
	return dev->dev.platform_data;
}

static inline int allow_clk_stop(struct s3c2410_nand_info *info)
{
	return clock_stop;
}

/* timing calculations */

#define NS_IN_KHZ 1000000

/**
 * s3c_nand_calc_rate - calculate timing data.
 * @wanted: The cycle time in nanoseconds.
 * @clk: The clock rate in kHz.
 * @max: The maximum divider value.
 *
 * Calculate the timing value from the given parameters.
 ===========通过传入的参数计算定时寄存器的值*/
static int s3c_nand_calc_rate(int wanted, unsigned long clk, int max)
{
	int result;

	result = DIV_ROUND_UP((wanted * clk), NS_IN_KHZ);

	pr_debug("result %d from %ld, %d\n", result, clk, wanted);

	if (result > max) {
		printk("%d ns is too big for current clock rate %ld\n", wanted, clk);
		return -1;
	}

	if (result < 1)
		result = 1;

	return result;
}

#define to_ns(ticks,clk) (((ticks) * NS_IN_KHZ) / (unsigned int)(clk))

/* controller setup */

/**
 * s3c2410_nand_setrate - setup controller timing information.
 * @info: The controller instance.
 *
 * Given the information supplied by the platform, calculate and set
 * the necessary timing registers in the hardware to generate the
 * necessary timing cycles to the hardware.==设置定时寄存器来产生时钟周期
 */
//设置时钟频率==设置定时寄存器来产生时钟周期
static int s3c2410_nand_setrate(struct s3c2410_nand_info *info)
{
	struct s3c2410_platform_nand *plat = info->platform;
	int tacls_max = (info->cpu_type == TYPE_S3C2412) ? 8 : 4;
	int tacls, twrph0, twrph1;
	unsigned long clkrate = clk_get_rate(info->clk);
	unsigned long uninitialized_var(set), cfg, uninitialized_var(mask);
	unsigned long flags;

	/* calculate the timing information for the controller */

	info->clk_rate = clkrate;
	clkrate /= 1000;	/* turn clock into kHz for ease of use */

	if (plat != NULL) {//计算定时寄存器的值
		tacls = s3c_nand_calc_rate(plat->tacls, clkrate, tacls_max);
		twrph0 = s3c_nand_calc_rate(plat->twrph0, clkrate, 8);
		twrph1 = s3c_nand_calc_rate(plat->twrph1, clkrate, 8);
	} else {
		/* default timings 默认时间控制*/
		tacls = tacls_max;
		twrph0 = 8;
		twrph1 = 8;
	}

	if (tacls < 0 || twrph0 < 0 || twrph1 < 0) {
		dev_err(info->device, "cannot get suitable timings\n");
		return -EINVAL;
	}

	dev_info(info->device, "Tacls=%d, %dns Twrph0=%d %dns, Twrph1=%d %dns\n",
	       tacls, to_ns(tacls, clkrate), twrph0, to_ns(twrph0, clkrate), twrph1, to_ns(twrph1, clkrate));

	switch (info->cpu_type) {
	case TYPE_S3C2410:
		mask = (S3C2410_NFCONF_TACLS(3) |
			S3C2410_NFCONF_TWRPH0(7) |
			S3C2410_NFCONF_TWRPH1(7));
		set = S3C2410_NFCONF_EN;
		set |= S3C2410_NFCONF_TACLS(tacls - 1);
		set |= S3C2410_NFCONF_TWRPH0(twrph0 - 1);
		set |= S3C2410_NFCONF_TWRPH1(twrph1 - 1);
		break;

	case TYPE_S3C2440:
	case TYPE_S3C2412:
		mask = (S3C2440_NFCONF_TACLS(tacls_max - 1) |
			S3C2440_NFCONF_TWRPH0(7) |
			S3C2440_NFCONF_TWRPH1(7));

		set = S3C2440_NFCONF_TACLS(tacls - 1);
		set |= S3C2440_NFCONF_TWRPH0(twrph0 - 1);
		set |= S3C2440_NFCONF_TWRPH1(twrph1 - 1);
		break;

	default:
		BUG();
	}

	local_irq_save(flags);

	cfg = readl(info->regs + S3C2410_NFCONF);//读取定时寄存器初始值
	cfg &= ~mask;
	cfg |= set;
	writel(cfg, info->regs + S3C2410_NFCONF);//写入寄存器，设置时钟频率

	local_irq_restore(flags);

	dev_dbg(info->device, "NF_CONF is 0x%lx\n", cfg);

	return 0;
}

/**
 * s3c2410_nand_inithw - basic hardware initialisation
 * @info: The hardware state.
 *
 * Do the basic initialisation of the hardware, using s3c2410_nand_setrate()
 * to setup the hardware access speeds and set the controller to be enabled.
*/	
//去初始化硬件相关的部分，主要是关于时钟频率的计算，以及启用 nand flash 控制器，使得硬件初始化好了，后面才能正常工作。
static int s3c2410_nand_inithw(struct s3c2410_nand_info *info)
{
	int ret;
	//设置时钟频率==设置定时寄存器来产生时钟周期
	ret = s3c2410_nand_setrate(info);
	if (ret < 0)
		return ret;

 	switch (info->cpu_type) {
 	case TYPE_S3C2410:
	default:
		break;

 	case TYPE_S3C2440:
 	case TYPE_S3C2412:
		/* enable the controller========使能控制寄存器 and de-assert nFCE */
		writel(S3C2440_NFCONT_ENABLE, info->regs + S3C2440_NFCONT);
	}

	return 0;
}

/**
 * s3c2410_nand_select_chip - select the given nand chip
 * @mtd: The MTD instance for this chip.
 * @chip: The chip number.
 *
 * This is called by the MTD layer to either select a given chip for the
 * @mtd instance, or to indicate that the access has finished and the
 * chip can be de-selected.
 *
 * The routine ensures that the nFCE line is correctly setup, and any
 * platform specific selection code is called to route nFCE to the specific
 * chip.
 */
 /* 
 * 根据chip都值设置nand flash都片选信号:
 * chip = -1 -- 禁用nand flash
 * chip !=-1 -- 选择对应的nand flash
 */
static void s3c2410_nand_select_chip(struct mtd_info *mtd, int chip)
{
	struct s3c2410_nand_info *info;
	struct s3c2410_nand_mtd *nmtd;
	struct nand_chip *this = mtd->priv;
	unsigned long cur;

	nmtd = this->priv;
	info = nmtd->info;

	if (chip != -1 && allow_clk_stop(info))
		clk_enable(info->clk);

	cur = readl(info->sel_reg);//读寄存器

	if (chip == -1) {
		cur |= info->sel_bit;
	} else {
		if (nmtd->set != NULL && chip > nmtd->set->nr_chips) {
			dev_err(info->device, "invalid chip %d\n", chip);
			return;
		}

		if (info->platform != NULL) {
			if (info->platform->select_chip != NULL)
				(info->platform->select_chip) (nmtd->set, chip);
		}

		cur &= ~info->sel_bit;
	}

	writel(cur, info->sel_reg);//写寄存器

	if (chip == -1 && allow_clk_stop(info))
		clk_disable(info->clk);
}

/* s3c2410_nand_hwcontrol
 *
 * Issue command and address cycles to the chip
*/
//给底层发送命令或地址，或者设置具体操作的模式，都是通过此函数。 
static void s3c2410_nand_hwcontrol(struct mtd_info *mtd, int cmd,
				   unsigned int ctrl)
{
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	if (cmd == NAND_CMD_NONE)
		return;

	if (ctrl & NAND_CLE)
		writeb(cmd, info->regs + S3C2410_NFCMD);//写命令
	else
		writeb(cmd, info->regs + S3C2410_NFADDR);//写地址
}

/* command and control functions */
/*
static void s3c2440_nand_hwcontrol(struct mtd_info *mtd, int cmd,
				   unsigned int ctrl)
{
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	if (cmd == NAND_CMD_NONE)
		return;

	if (ctrl & NAND_CLE)
		writeb(cmd, info->regs + S3C2440_NFCMD);
	else
		writeb(cmd, info->regs + S3C2440_NFADDR);
}
*/

/* s3c2410_nand_devready()
 *
 * returns 0 if the nand is busy, 1 if it is ready
*/
//Nand Flash 的一些操作，比如读一页数据，写入（编程）一页数据，擦除一个块，都是需要一定时间的，在命发送完成后，就是硬件开始忙着工作的时候了，而硬件什么时候完成这些操作，什么时候不忙了，变就绪了，就是通过这个函数去检查状态的。一般具体实现都是去读硬件的一个状态寄存器，其中某一位是否是 1 ，对应着是出于“就绪 / 不忙”还是“忙”的状态。这个寄存器，也就是我们前面分析时序图中的 R/B# 。 
static int s3c2410_nand_devready(struct mtd_info *mtd)
{
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	return readb(info->regs + S3C2410_NFSTAT) & S3C2410_NFSTAT_BUSY;;//返回nand flash都忙标志
}
/*
static int s3c2440_nand_devready(struct mtd_info *mtd)
{
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	return readb(info->regs + S3C2440_NFSTAT) & S3C2440_NFSTAT_READY;
}

static int s3c2412_nand_devready(struct mtd_info *mtd)
{
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	return readb(info->regs + S3C2412_NFSTAT) & S3C2412_NFSTAT_READY;
}

/* ECC handling functions */
//当实际操作过程中，读取出来的数据所对应的硬件或软件计算出来的 ECC ，和从 oob 中
//读出来的 ECC 不一样的时候，就是说明数据有误了，就需要调用此函数去纠正错误。
//对于现在 SLC 常见的 ECC 算法来说，可以发现 2 位，纠正 1 位。如果错误大于 1 位，
//那么就无法纠正回来了。一般情况下，出错超过 1 位的，好像几率不大。至少我看到的
//不是很大。更复杂的情况和更加注重数据安全的情况下，一般是需要另外实现更高效和
//检错和纠错能力更强的 ECC 算法的。 

/*该函数首先把read_ecc数组内的ECC存入寄存器NFMECCD0和寄存器NFMECCD1中，这样系统就会自动校验数据，并把状态放入
寄存器NFESTAT0中，然后读取该寄存器的后4位，当为0时表示校验正确；当为1时表示发生了1位错误（该类错误可以校正），
我们把它校正过来；当为2和3时表示发生其他类型的错误，这类错误是无法校正的。*/
static int s3c2410_nand_correct_data(struct mtd_info *mtd, u_char *dat,
				     u_char *read_ecc, u_char *calc_ecc)
{//ECC校验数据,并纠正错误
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	unsigned int diff0, diff1, diff2;
	unsigned int bit, byte;

	pr_debug("%s(%p,%p,%p,%p)\n", __func__, mtd, dat, read_ecc, calc_ecc);

	diff0 = read_ecc[0] ^ calc_ecc[0];
	diff1 = read_ecc[1] ^ calc_ecc[1];
	diff2 = read_ecc[2] ^ calc_ecc[2];

	pr_debug("%s: rd %02x%02x%02x calc %02x%02x%02x diff %02x%02x%02x\n",
		 __func__,
		 read_ecc[0], read_ecc[1], read_ecc[2],
		 calc_ecc[0], calc_ecc[1], calc_ecc[2],
		 diff0, diff1, diff2);

	if (diff0 == 0 && diff1 == 0 && diff2 == 0)
		return 0;		/* ECC is ok */

	/* sometimes people do not think about using the ECC, so check
	 * to see if we have an 0xff,0xff,0xff read ECC and then ignore
	 * the error, on the assumption that this is an un-eccd page.
	 */
	if (read_ecc[0] == 0xff && read_ecc[1] == 0xff && read_ecc[2] == 0xff
	    && info->platform->ignore_unset_ecc)
		return 0;

	/* Can we correct this ECC (ie, one row and column change).
	 * Note, this is similar to the 256 error code on smartmedia */

	if (((diff0 ^ (diff0 >> 1)) & 0x55) == 0x55 &&
	    ((diff1 ^ (diff1 >> 1)) & 0x55) == 0x55 &&
	    ((diff2 ^ (diff2 >> 1)) & 0x55) == 0x55) {
		/* calculate the bit position of the error */

		bit  = ((diff2 >> 3) & 1) |
		       ((diff2 >> 4) & 2) |
		       ((diff2 >> 5) & 4);

		/* calculate the byte position of the error */

		byte = ((diff2 << 7) & 0x100) |
		       ((diff1 << 0) & 0x80)  |
		       ((diff1 << 1) & 0x40)  |
		       ((diff1 << 2) & 0x20)  |
		       ((diff1 << 3) & 0x10)  |
		       ((diff0 >> 4) & 0x08)  |
		       ((diff0 >> 3) & 0x04)  |
		       ((diff0 >> 2) & 0x02)  |
		       ((diff0 >> 1) & 0x01);

		dev_dbg(info->device, "correcting error bit %d, byte %d\n",
			bit, byte);

		dat[byte] ^= (1 << bit);
		return 1;
	}

	/* if there is only one bit difference in the ECC, then
	 * one of only a row or column parity has changed, which
	 * means the error is most probably in the ECC itself */

	diff0 |= (diff1 << 8);
	diff0 |= (diff2 << 16);

	if ((diff0 & ~(1<<fls(diff0))) == 0)
		return 1;

	return -1;
}

/* ECC functions
 *
 * These allow the s3c2410 and s3c2440 to use the controller's ECC
 * generator block to ECC the data as it passes through]
*/
//在硬件支持的前提下，前面s3c2410_nand_init_chip设置了硬件 ECC 的话，要实现这个函数，用于每次在读写操作前
//，通过设置对应的硬件寄存器的某些位，使得启用硬件 ECC ，这样在读写操作完成后，
//就可以去读取硬件校验产生出来的 ECC 数值了。 
static void s3c2410_nand_enable_hwecc(struct mtd_info *mtd, int mode)
{
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	unsigned long ctrl;

	ctrl = readl(info->regs + S3C2410_NFCONF);
	ctrl |= S3C2410_NFCONF_INITECC;
	writel(ctrl, info->regs + S3C2410_NFCONF);//使能硬件ECC的寄存器
}
/*
static void s3c2412_nand_enable_hwecc(struct mtd_info *mtd, int mode)
{
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	unsigned long ctrl;

	ctrl = readl(info->regs + S3C2440_NFCONT);
	writel(ctrl | S3C2412_NFCONT_INIT_MAIN_ECC, info->regs + S3C2440_NFCONT);
}

static void s3c2440_nand_enable_hwecc(struct mtd_info *mtd, int mode)
{
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	unsigned long ctrl;

	ctrl = readl(info->regs + S3C2440_NFCONT);
	writel(ctrl | S3C2440_NFCONT_INITECC, info->regs + S3C2440_NFCONT);
}
*/
//\如果s3c2410_nand_init_chip是上面提到的硬件 ECC 的话，就不用我们用软件去实现
//校验算法了，而是直接去读取硬件产生的 ECC 数值就可以了。 
static int s3c2410_nand_calculate_ecc(struct mtd_info *mtd, const u_char *dat, u_char *ecc_code)
{//使用硬件ECC时，则直接读取24位的ECC的值
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	ecc_code[0] = readb(info->regs + S3C2410_NFECC + 0);
	ecc_code[1] = readb(info->regs + S3C2410_NFECC + 1);
	ecc_code[2] = readb(info->regs + S3C2410_NFECC + 2);

	pr_debug("%s: returning ecc %02x%02x%02x\n", __func__,
		 ecc_code[0], ecc_code[1], ecc_code[2]);

	return 0;
}
/*
static int s3c2412_nand_calculate_ecc(struct mtd_info *mtd, const u_char *dat, u_char *ecc_code)
{
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	unsigned long ecc = readl(info->regs + S3C2412_NFMECC0);

	ecc_code[0] = ecc;
	ecc_code[1] = ecc >> 8;
	ecc_code[2] = ecc >> 16;

	pr_debug("calculate_ecc: returning ecc %02x,%02x,%02x\n", ecc_code[0], ecc_code[1], ecc_code[2]);

	return 0;
}

static int s3c2440_nand_calculate_ecc(struct mtd_info *mtd, const u_char *dat, u_char *ecc_code)
{
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	unsigned long ecc = readl(info->regs + S3C2440_NFMECC0);

	ecc_code[0] = ecc;
	ecc_code[1] = ecc >> 8;
	ecc_code[2] = ecc >> 16;

	pr_debug("%s: returning ecc %06lx\n", __func__, ecc & 0xffffff);

	return 0;
}

/* over-ride the standard functions for a little more speed. We can
 * use read/write block to move the data buffers to/from the controller
*/
//就是往你的 nand flash 的控制器中的 FIFO 读写数据。一般情况下，是 MTD 上层的操作，
//比如要读取一页的数据，那么在发送完相关的读命令和等待时间之后，就会调用到你底层
//的 read_buf ，去 nand Flash 的 FIFO 中，一点点把我们要的数据，读取出来，放到我们
//制定的内存的缓存中去。写操作也是类似，将我们内存中的数据，写到 Nand Flash 的 FIFO 中去。
static void s3c2410_nand_read_buf(struct mtd_info *mtd, u_char *buf, int len)
{
	struct nand_chip *this = mtd->priv;//this->IO_ADDR_R在s3c2410_nand_init_chip中初始化
	readsb(this->IO_ADDR_R, buf, len);//向对应的buf寄存器地址读数据
}
/*
static void s3c2440_nand_read_buf(struct mtd_info *mtd, u_char *buf, int len)
{
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	readsl(info->regs + S3C2440_NFDATA, buf, len >> 2);

	// cleanup if we've got less than a word to do 
	if (len & 3) {
		buf += len & ~3;

		for (; len & 3; len--)
			*buf++ = readb(info->regs + S3C2440_NFDATA);
	}
}
*/
//就是往你的 nand flash 的控制器中的 FIFO 读写数据。一般情况下，是 MTD 上层的操作，
//比如要读取一页的数据，那么在发送完相关的读命令和等待时间之后，就会调用到你底层
//的 read_buf ，去 nand Flash 的 FIFO 中，一点点把我们要的数据，读取出来，放到我们
//制定的内存的缓存中去。写操作也是类似，将我们内存中的数据，写到 Nand Flash 的 FIFO 中去。
static void s3c2410_nand_write_buf(struct mtd_info *mtd, const u_char *buf, int len)
{
	struct nand_chip *this = mtd->priv;//this->IO_ADDR_W在s3c2410_nand_init_chip中初始化
	writesb(this->IO_ADDR_W, buf, len);//向对应的buf寄存器地址写数据
}
/*
static void s3c2440_nand_write_buf(struct mtd_info *mtd, const u_char *buf, int len)
{
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	writesl(info->regs + S3C2440_NFDATA, buf, len >> 2);

	// cleanup any fractional write 
	if (len & 3) {
		buf += len & ~3;

		for (; len & 3; len--, buf++)
			writeb(*buf, info->regs + S3C2440_NFDATA);
	}
}

/* cpufreq driver support */

#ifdef CONFIG_CPU_FREQ

static int s3c2410_nand_cpufreq_transition(struct notifier_block *nb,
					  unsigned long val, void *data)
{
	struct s3c2410_nand_info *info;
	unsigned long newclk;

	info = container_of(nb, struct s3c2410_nand_info, freq_transition);
	newclk = clk_get_rate(info->clk);

	if ((val == CPUFREQ_POSTCHANGE && newclk < info->clk_rate) ||
	    (val == CPUFREQ_PRECHANGE && newclk > info->clk_rate)) {
		s3c2410_nand_setrate(info);
	}

	return 0;
}

static inline int s3c2410_nand_cpufreq_register(struct s3c2410_nand_info *info)
{
	info->freq_transition.notifier_call = s3c2410_nand_cpufreq_transition;

	return cpufreq_register_notifier(&info->freq_transition,
					 CPUFREQ_TRANSITION_NOTIFIER);
}

static inline void s3c2410_nand_cpufreq_deregister(struct s3c2410_nand_info *info)
{
	cpufreq_unregister_notifier(&info->freq_transition,
				    CPUFREQ_TRANSITION_NOTIFIER);
}

#else
static inline int s3c2410_nand_cpufreq_register(struct s3c2410_nand_info *info)
{
	return 0;
}

static inline void s3c2410_nand_cpufreq_deregister(struct s3c2410_nand_info *info)
{
}
#endif

/* device management functions */

static int s3c24xx_nand_remove(struct platform_device *pdev)
{
	struct s3c2410_nand_info *info = to_nand_info(pdev);

	platform_set_drvdata(pdev, NULL);

	if (info == NULL)
		return 0;

	s3c2410_nand_cpufreq_deregister(info);

	/* Release all our mtds  and their partitions, then go through
	 * freeing the resources used
	 */

	if (info->mtds != NULL) {
		struct s3c2410_nand_mtd *ptr = info->mtds;
		int mtdno;

		for (mtdno = 0; mtdno < info->mtd_count; mtdno++, ptr++) {
			pr_debug("releasing mtd %d (%p)\n", mtdno, ptr);
			nand_release(&ptr->mtd);
		}

		kfree(info->mtds);
	}

	/* free the common resources */

	if (info->clk != NULL && !IS_ERR(info->clk)) {
		if (!allow_clk_stop(info))
			clk_disable(info->clk);
		clk_put(info->clk);
	}

	if (info->regs != NULL) {
		iounmap(info->regs);
		info->regs = NULL;
	}

	if (info->area != NULL) {
		release_resource(info->area);
		kfree(info->area);
		info->area = NULL;
	}

	kfree(info);

	return 0;
}

#ifdef CONFIG_MTD_PARTITIONS
const char *part_probes[] = { "cmdlinepart", NULL };
static int s3c2410_nand_add_partition(struct s3c2410_nand_info *info,
				      struct s3c2410_nand_mtd *mtd,
				      struct s3c2410_nand_set *set)
{
	struct mtd_partition *part_info;
	int nr_part = 0;

	if (set == NULL)
		return add_mtd_device(&mtd->mtd);

	if (set->nr_partitions == 0) {
		mtd->mtd.name = set->name;
		nr_part = parse_mtd_partitions(&mtd->mtd, part_probes,
						&part_info, 0);
	} else {
		if (set->nr_partitions > 0 && set->partitions != NULL) {
			nr_part = set->nr_partitions;
			part_info = set->partitions;
		}
	}

	if (nr_part > 0 && part_info)
		return add_mtd_partitions(&mtd->mtd, part_info, nr_part);

	return add_mtd_device(&mtd->mtd);
}
#else
static int s3c2410_nand_add_partition(struct s3c2410_nand_info *info,
				      struct s3c2410_nand_mtd *mtd,
				      struct s3c2410_nand_set *set)
{
	return add_mtd_device(&mtd->mtd);
}
#endif

/**
 * s3c2410_nand_init_chip - initialise a single instance of an chip
 * @info: The base NAND controller the chip is on.
 * @nmtd: The new controller MTD instance to fill in.
 * @set: The information passed from the board specific platform data.
 *
 * Initialise the given @nmtd from the information in @info and @set. This
 * readies the structure for use with the MTD layer functions by ensuring
 * all pointers are setup and the necessary control routines selected.
 //初始化代表一片flash的struct nand_chip结构, nand flash 底层操作实现部分 */
static void s3c2410_nand_init_chip(struct s3c2410_nand_info *info,
				   struct s3c2410_nand_mtd *nmtd,
				   struct s3c2410_nand_set *set)
{
	struct nand_chip *chip = &nmtd->chip;
	void __iomem *regs = info->regs;//获取物理地址，用于寄存器操作

	chip->write_buf    = s3c2410_nand_write_buf;//（ 1 ） s3c2410_nand_write_buf 和 s3c2410_nand_read_buf ：这是两个最基本的操作函数，其功能，就是往你的 nand flash 的控制器中的 FIFO 读写数据。一般情况下，是 MTD 上层的操作，比如要读取一页的数据，那么在发送完相关的读命令和等待时间之后，就会调用到你底层的 read_buf ，去 nand Flash 的 FIFO 中，一点点把我们要的数据，读取出来，放到我们制定的内存的缓存中去。写操作也是类似，将我们内存中的数据，写到 Nand Flash 的 FIFO 中去。
	chip->read_buf     = s3c2410_nand_read_buf;
	chip->select_chip  = s3c2410_nand_select_chip;//（ 2 ） s3c2410_nand_select_chip ： 实现 Nand Flash 的片选。 
	chip->chip_delay   = 50;
	chip->priv	   = nmtd;
	chip->options	   = set->options;
	chip->controller   = &info->controller;

	switch (info->cpu_type) {
	case TYPE_S3C2410:
		/* nand flash 控制器中，一般都有对应的数据寄存器，用于给你往里面写数据，表示将要读取或写入多少个
		字节 (byte,u8)/ 字 (word,u32) ，所以，此处，你要给出地址，以便后面的操作所使用 */ 
		chip->IO_ADDR_W = regs + S3C2410_NFDATA;//写地址
		info->sel_reg   = regs + S3C2410_NFCONF;//控制寄存器
		info->sel_bit	= S3C2410_NFCONF_nFCE;
		chip->cmd_ctrl  = s3c2410_nand_hwcontrol;// 3 ） s3c2410_nand_hwcontrol ：给底层发送命令或地址，或者设置具体操作的模式，都是通过此函数。 
		chip->dev_ready = s3c2410_nand_devready;//（ 4 ） s3c2410_nand_devready ： Nand Flash 的一些操作，比如读一页数据，写入（编程）一页数据，擦除一个块，都是需要一定时间的，在命发送完成后，就是硬件开始忙着工作的时候了，而硬件什么时候完成这些操作，什么时候不忙了，变就绪了，就是通过这个函数去检查状态的。一般具体实现都是去读硬件的一个状态寄存器，其中某一位是否是 1 ，对应着是出于“就绪 / 不忙”还是“忙”的状态。这个寄存器，也就是我们前面分析时序图中的 R/B# 。 
		break;

	case TYPE_S3C2440:
		chip->IO_ADDR_W = regs + S3C2440_NFDATA;
		info->sel_reg   = regs + S3C2440_NFCONT;
		info->sel_bit	= S3C2440_NFCONT_nFCE;
		chip->cmd_ctrl  = s3c2440_nand_hwcontrol;
		chip->dev_ready = s3c2440_nand_devready;
		chip->read_buf  = s3c2440_nand_read_buf;
		chip->write_buf	= s3c2440_nand_write_buf;
		break;

	case TYPE_S3C2412:
		chip->IO_ADDR_W = regs + S3C2440_NFDATA;
		info->sel_reg   = regs + S3C2440_NFCONT;
		info->sel_bit	= S3C2412_NFCONT_nFCE0;
		chip->cmd_ctrl  = s3c2440_nand_hwcontrol;
		chip->dev_ready = s3c2412_nand_devready;

		if (readl(regs + S3C2410_NFCONF) & S3C2412_NFCONF_NANDBOOT)
			dev_info(info->device, "System booted from NAND\n");

		break;
  	}

	chip->IO_ADDR_R = chip->IO_ADDR_W;//读地址和写地址一样的

	nmtd->info	   = info;
	nmtd->mtd.priv	   = chip;
	nmtd->mtd.owner    = THIS_MODULE;
	//nand_scan函数中会调用struct nand_chip *this = mtd->priv取出该struct nand_chip结构
	nmtd->set	   = set;

	if (hardware_ecc) {//使用硬件ECC时，则直接读取24位的ECC的值
		chip->ecc.calculate = s3c2410_nand_calculate_ecc;
		chip->ecc.correct   = s3c2410_nand_correct_data;//（ 7 ） s3c2410_nand_correct_data ：当实际操作过程中，读取出来的数据所对应的硬件或软件计算出来的 ECC ，和从 oob 中读出来的 ECC 不一样的时候，就是说明数据有误了，就需要调用此函数去纠正错误。对于现在 SLC 常见的 ECC 算法来说，可以发现 2 位，纠正 1 位。如果错误大于 1 位，那么就无法纠正回来了。一般情况下，出错超过 1 位的，好像几率不大。至少我看到的不是很大。更复杂的情况和更加注重数据安全的情况下，一般是需要另外实现更高效和检错和纠错能力更强的 ECC 算法的。 
		/* 此处，多数情况下，你所用的 Nand Flash 的控制器，都是支持硬件 ECC 的，所以，此处设置硬件 ECC(HW_ECC) ，
		也是充分利用硬件的特性，而如果此处不用硬件去做的 ECC 的话，那么下面也会去设置成 NAND_ECC_SOFT ，系统会
		用默认的软件去做 ECC 校验，相比之下，比硬件 ECC 的效率就低很多，而你的 nand flash 的读写，也会相应地要慢不少 */ 
		chip->ecc.mode	    = NAND_ECC_HW;

		switch (info->cpu_type) {
		case TYPE_S3C2410:
			chip->ecc.hwctl	    = s3c2410_nand_enable_hwecc;//（ 5 ） s3c2410_nand_enable_hwecc ： 在硬件支持的前提下，前面设置了硬件 ECC 的话，要实现这个函数，用于每次在读写操作前，通过设置对应的硬件寄存器的某些位，使得启用硬件 ECC ，这样在读写操作完成后，就可以去读取硬件校验产生出来的 ECC 数值了。 
			chip->ecc.calculate = s3c2410_nand_calculate_ecc;//（ 6 ） s3c2410_nand_calculate_ecc ：如果是上面提到的硬件 ECC 的话，就不用我们用软件去实现校验算法了，而是直接去读取硬件产生的 ECC 数值就可以了。 
			break;

		case TYPE_S3C2412:
  			chip->ecc.hwctl     = s3c2412_nand_enable_hwecc;
  			chip->ecc.calculate = s3c2412_nand_calculate_ecc;
			break;

		case TYPE_S3C2440:
  			chip->ecc.hwctl     = s3c2440_nand_enable_hwecc;
  			chip->ecc.calculate = s3c2440_nand_calculate_ecc;
			break;

		}
	} 
	else //不使用硬件ECC时，则使用软件ECC
	{
		chip->ecc.mode	    = NAND_ECC_SOFT;//不使用硬件ECC时，则使用软件ECC
	}

	if (set->ecc_layout != NULL)
		chip->ecc.layout = set->ecc_layout;

	if (set->disable_ecc)
		chip->ecc.mode	= NAND_ECC_NONE;

	switch (chip->ecc.mode) {
	case NAND_ECC_NONE:
		dev_info(info->device, "NAND ECC disabled\n");
		break;
	case NAND_ECC_SOFT:
		dev_info(info->device, "NAND soft ECC\n");
		break;
	case NAND_ECC_HW:
		dev_info(info->device, "NAND hardware ECC\n");
		break;
	default:
		dev_info(info->device, "NAND ECC UNKNOWN\n");
		break;
	}

	/* If you use u-boot BBT creation code, specifying this flag will
	 * let the kernel fish out the BBT from the NAND, and also skip the
	 * full NAND scan that can take 1/2s or so. Little things... */
	if (set->flash_bbt)
		chip->options |= NAND_USE_FLASH_BBT | NAND_SKIP_BBTSCAN;
}

/**
 * s3c2410_nand_update_chip - post probe update
 * @info: The controller instance.
 * @nmtd: The driver version of the MTD instance.
 *
 * This routine is called after the chip probe has successfully completed
 * and the relevant per-chip information updated. This call ensure that
 * we update the internal state accordingly.
 *
 * The internal state is currently limited to the ECC state information.
*/
static void s3c2410_nand_update_chip(struct s3c2410_nand_info *info,
				     struct s3c2410_nand_mtd *nmtd)
{
	struct nand_chip *chip = &nmtd->chip;

	dev_dbg(info->device, "chip %p => page shift %d\n",
		chip, chip->page_shift);

	if (chip->ecc.mode != NAND_ECC_HW)
		return;

		/* change the behaviour depending on wether we are using
		 * the large or small page nand device */

	if (chip->page_shift > 10) {
		chip->ecc.size	    = 256;
		chip->ecc.bytes	    = 3;
	} else {
		chip->ecc.size	    = 512;
		chip->ecc.bytes	    = 3;
		chip->ecc.layout    = &nand_hw_eccoob;
	}
}

/* s3c24xx_nand_probe
 *
 * called by device layer when it finds a device matching
 * one our driver can handled. This code checks to see if
 * it can allocate all necessary resources then calls the
 * nand layer to look for devices
*/
//一、s3c2410nandflash控制器初始化步骤:===========================
        s3c2410_nand_init(&s3c2410_nand_driver)
        -> driver_register->bus_add_driver()->driver_attach->bus_for_each_dev(__driver_attach)->driver_probe_device()->dev->probe() [最后这个函数实质是s3c2410_nand_probe()]

        -> s3c2410_nand_probe()
                        -> s3c24xx_nand_probe()
                                -> s3c2410_nand_inithw() // 初始化nandflash控制器
                                        -> s3c2410_nand_init_chip()// 初始化s3c2410 nandflash驱动最底层的访问控制函数
                                            -> chip->write_buf = s3c2410_nand_write_buf;
                                            -> chip->read_buf = s3c2410_nand_read_buf;
                                            -> chip->select_chip = s3c2410_nand_select_chip;
                                            -> chip->cmd_ctrl = s3c2410_nand_hwcontrol()
                                        -> nand_scan()
                                        -> s3c2410_nand_add_partition()
                                ->add_mtd_device()
//一、s3c2410nandflash控制器初始化步骤:===========================

static int s3c24xx_nand_probe(struct platform_device *pdev)
{
	struct s3c2410_platform_nand *plat = to_nand_plat(pdev); //指向smdk_nand_info，定义了Nand控制时序的参数，分配几个mtd结构  
	enum s3c_cpu_type cpu_type; 
	//获取nand flash配置用结构体数据(dev.c中定义
	struct s3c2410_nand_mtd *nmtd;//包含下面两个成员：s3c2410_nand_info，s3c2410_nand_set	
	struct s3c2410_nand_info *info;
	struct s3c2410_nand_set *sets;
	
	struct resource *res;
	int err = 0;
	int size;
	int nr_sets;
	int setno;
	//获取设备ID，判断是2410，还是6410，还是210
	cpu_type = platform_get_device_id(pdev)->driver_data;

	pr_debug("s3c2410_nand_probe(%p)\n", pdev);

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (info == NULL) {
		dev_err(&pdev->dev, "no memory for flash info\n");
		err = -ENOMEM;
		goto exit_error;
	}
	//将info保存成平台总线设备的私有数据,以后调用platform_get_drvdata()就有用
	platform_set_drvdata(pdev, info);

	spin_lock_init(&info->controller.lock);//初始化自旋锁
	init_waitqueue_head(&info->controller.wq);//初始化等待队列

	/* get the clock source and enable it================================================ */
	info->clk = clk_get(&pdev->dev, "nand");
	if (IS_ERR(info->clk)) {
		dev_err(&pdev->dev, "failed to get clock\n");
		err = -ENOENT;
		goto exit_error;
	}

	clk_enable(info->clk);//用 clk_enable 打开 nand flash 控制器的 clock 时钟

	/* allocate and map the resource================================================== */
	/* currently we assume we have the one resource */
	res  = pdev->resource;//提取dev.c中定义的与设备相关的资源
	size = resource_size(res);//映射nand flash用到的寄存器
	//用 request_mem_region 去申请驱动所需要的一些内存等相关资源
	info->area = request_mem_region(res->start, size, pdev->name);

	if (info->area == NULL) {
		dev_err(&pdev->dev, "cannot reserve register region\n");
		err = -ENOENT;
		goto exit_error;
	}

	info->device     = &pdev->dev;
	info->platform   = plat;
	info->regs       = ioremap(res->start, size);//获取物理基地址
	info->cpu_type   = cpu_type;

	if (info->regs == NULL) {
		dev_err(&pdev->dev, "cannot reserve register region\n");
		err = -EIO;
		goto exit_error;
	}

	dev_dbg(&pdev->dev, "mapped registers at %p\n", info->regs);

	/* initialise the hardware====================================================== */
	//去初始化硬件相关的部分，主要是关于时钟频率的计算，以及启用 nand flash 控制器，使得硬件初始化好了，后面才能正常工作。
	err = s3c2410_nand_inithw(info);
	if (err != 0)
		goto exit_error;

	sets = (plat != NULL) ? plat->sets : NULL;
	nr_sets = (plat != NULL) ? plat->nr_sets : 1;
	//我的板上只有一块nand flash，配置信息见plat-sets，数目为1
	info->mtd_count = nr_sets;

	/* allocate our information */
	size = nr_sets * sizeof(*info->mtds);
	info->mtds = kzalloc(size, GFP_KERNEL);
	if (info->mtds == NULL) {
		dev_err(&pdev->dev, "failed to allocate mtd storage\n");
		err = -ENOMEM;
		goto exit_error;
	}

	/*需要多解释一下的，是这部分代码 initialise all possible chips */
	nmtd = info->mtds;//

	for (setno = 0; setno < nr_sets; setno++, nmtd++) {
		pr_debug("initialising set %d (%p, info %p)\n", setno, nmtd, info);
		/* （移植需要修改的硬件操作部分）调用 init chip 去挂载你的 nand 驱动的底层函数
		到 nand flash 的结构体中，以及设置对应的 ecc mode ，挂载 ecc 相关的函数 */ 
		s3c2410_nand_init_chip(info, nmtd, sets);//===========================//===========================
		/* scan_ident ，扫描 nand 设备，设置 nand flash 的默认函数，获得物理设备的具体型号以及对应各个特性参数，
		这部分算出来的一些值，对于 nand flash 来说，是最主要的参数，比如 nand falsh 的芯片的大小，块大小，页大小等。 */ 
		nmtd->scan_res = nand_scan_ident(&nmtd->mtd,//===========================
						 (sets) ? sets->nr_chips : 1,
						 NULL);

		if (nmtd->scan_res == 0) {
			s3c2410_nand_update_chip(info, nmtd);
			/* scan tail ，从名字就可以看出来，是扫描的后一阶段，此时，经过前面的 scan_ident ，我们已经获得对应
			nand flash 的硬件的各个参数，然后就可以在 scan tail 中，根据这些参数，去设置其他一些重要参数，
			尤其是 ecc 的 layout ，即 ecc 是如何在 oob 中摆放的，最后，再去进行一些初始化操作，主要是根据你的驱动，
			如果没有实现一些函数的话，那么就用系统默认的。 */ 
			nand_scan_tail(&nmtd->mtd);
			/* add partion ，根据你的 nand flash 的分区设置，去分区 */ 
			s3c2410_nand_add_partition(info, nmtd, sets);
		}

		if (sets != NULL)
			sets++;
	}

	err = s3c2410_nand_cpufreq_register(info);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to init cpufreq support\n");
		goto exit_error;
	}

	if (allow_clk_stop(info)) {
		dev_info(&pdev->dev, "clock idle support enabled\n");
		clk_disable(info->clk);
	}

	pr_debug("initialised ok\n");
	return 0;

 exit_error:
	s3c24xx_nand_remove(pdev);

	if (err == 0)
		err = -EINVAL;
	return err;
}

/* PM Support */
#ifdef CONFIG_PM

static int s3c24xx_nand_suspend(struct platform_device *dev, pm_message_t pm)
{
	struct s3c2410_nand_info *info = platform_get_drvdata(dev);

	if (info) {
		info->save_sel = readl(info->sel_reg);

		/* For the moment, we must ensure nFCE is high during
		 * the time we are suspended. This really should be
		 * handled by suspending the MTDs we are using, but
		 * that is currently not the case. */

		writel(info->save_sel | info->sel_bit, info->sel_reg);

		if (!allow_clk_stop(info))
			clk_disable(info->clk);
	}

	return 0;
}

static int s3c24xx_nand_resume(struct platform_device *dev)
{
	struct s3c2410_nand_info *info = platform_get_drvdata(dev);
	unsigned long sel;

	if (info) {
		clk_enable(info->clk);
		s3c2410_nand_inithw(info);

		/* Restore the state of the nFCE line. */

		sel = readl(info->sel_reg);
		sel &= ~info->sel_bit;
		sel |= info->save_sel & info->sel_bit;
		writel(sel, info->sel_reg);

		if (allow_clk_stop(info))
			clk_disable(info->clk);
	}

	return 0;
}

#else
#define s3c24xx_nand_suspend NULL
#define s3c24xx_nand_resume NULL
#endif

/* driver device registration */

static struct platform_device_id s3c24xx_driver_ids[] = {
	{
		.name		= "s3c2410-nand",
		.driver_data	= TYPE_S3C2410,
	}, {
		.name		= "s3c2440-nand",
		.driver_data	= TYPE_S3C2440,
	}, {
		.name		= "s3c2412-nand",
		.driver_data	= TYPE_S3C2412,
	}, {
		.name		= "s3c6400-nand",
		.driver_data	= TYPE_S3C2412, /* compatible with 2412 */
	},
	{ }
};

MODULE_DEVICE_TABLE(platform, s3c24xx_driver_ids);
/*对于上面这个结构体，没多少要解释的。从名字，就能看出来： 
（ 1 ） probe 就是系统“探测”，就是前面解释的整个过程，这个过程中的多数步骤，都是和你自己的 nand flash 相关的，尤其是那些硬件初始化部分，是你必须要自己实现的。 
（ 2 ） remove ，就是和 probe 对应的，“反初始化”相关的动作。主要是释放系统相关资源和关闭硬件的时钟等常见操作了。 
(3)suspend 和 resume ，对于很多没用到电源管理的情况下，至少对于我们刚开始写基本的驱动的时候，可以不用关心，放个空函数即可。 
*/
static struct platform_driver s3c24xx_nand_driver = {
	.probe		= s3c24xx_nand_probe,
	.remove		= s3c24xx_nand_remove,
	.suspend	= s3c24xx_nand_suspend,
	.resume		= s3c24xx_nand_resume,
	.id_table	= s3c24xx_driver_ids,
	.driver		= {
		.name	= "s3c24xx-nand",
		.owner	= THIS_MODULE,
	},
};

static int __init s3c2410_nand_init(void)
{
	printk("S3C24XX NAND Driver, (c) 2004 Simtec Electronics\n");

	return platform_driver_register(&s3c24xx_nand_driver);
}

static void __exit s3c2410_nand_exit(void)
{
	platform_driver_unregister(&s3c24xx_nand_driver);
}

//module_init(s3c2410_nand_init);
//module_exit(s3c2410_nand_exit);

//MODULE_LICENSE("GPL");
//MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
//MODULE_DESCRIPTION("S3C24XX MTD NAND driver");
