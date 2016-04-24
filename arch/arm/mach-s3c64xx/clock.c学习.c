 //clock文件，初始化6410时钟

/* linux/arch/arm/plat-s3c64xx/clock.c
*
* Copyright 2008 Openmoko, Inc.
* Copyright 2008 Simtec Electronics
* Ben Dooks <ben@simtec.co.uk>
* http://armlinux.simtec.co.uk/
*
* S3C64XX Base clock support S3C64XX基础时钟支持
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*/
//首先来看头文件
#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/delay.h>
#include <linux/io.h>

#include <mach/hardware.h>
#include <mach/map.h>

//以下头文件和平台相关
#include <plat/regs-sys.h>   //S3C64XX system register definitions感觉没什么作用

#include <plat/regs-clock.h> 
//非常多的宏定义，和时钟、分频相关
/*从中可看出有HCLK、PCLK和SCLK
顺便贴下PLL介绍：支持三个PLL分别是APLL，MPLL和EPLL。
APLL为ARM提供时钟，产生ARMCLK，
MPLL为所有和AXI/AHB/APB相连的模块提供时钟，产生HCLK和PCLK，
EPLL为特殊的外设提供时钟，产生SCLK。*/

//以下三个头文件在plat-s3c中,看来是三星通用的

#include <plat/cpu.h>
//针对不同的处理器采用宏定义的方法做了区别
//定义了IODESC_ENT(x)宏，作用为建立IO映射表
/*//////////////////////////////引用2410资料解释/////////////////////////////////////////////////////
IODESC_ENT宏如下：
#define IODESC_ENT(x) { (unsigned long)S3C24XX_VA_##x, __phys_to_pfn(S3C24XX_PA_##x), S3C24XX_SZ_##x, MT_DEVICE }

展开后等价于：
static struct map_desc s3c2410_iodesc[] __initdata = {
{
.virtual = (unsigned long)S3C24XX_VA_ LCD),
.pfn = __phys_to_pfn(S3C24XX_PA_ LCD),
.length = S3C24XX_SZ_ LCD,
.type = MT_DEVICE
},
/////////////////////////////////////////////////////////////////////////////////////////////*/

#include <plat/devs.h>
/*该文件没啥好说的，以extern形式引用了一些platform_device结构体
eg：extern struct platform_device s3c_device_fb;
值得注意的地方是platform_device这个结构体，跟进去看看：
在platform_device.h文件中
struct platform_device {
const char * name;
int   id;
struct device dev;
u32   num_resources;
struct resource * resource;
};
这就是常见的平台设备结构体的原型了*/

#include <plat/clock.h>
/*该头文件包含了一个很大的clk结构体
struct clk {
struct list_head      list;
struct module        *owner;
struct clk           *parent;
const char           *name;
int        id;
int        usage;
unsigned long         rate;
unsigned long         ctrlbit;

int      (*enable)(struct clk *, int enable);
int      (*set_rate)(struct clk *c, unsigned long rate);
unsigned long     (*get_rate)(struct clk *c);
unsigned long     (*round_rate)(struct clk *c, unsigned long rate);
int      (*set_parent)(struct clk *c, struct clk *parent);
};
想不通为什么一个clk结构体都要有那么多的成员，不过该结构体对于本文件非常重要，
还引用很多该结构体的成员*/

//终于把头文件看完，开始看正文

//虽然结构体很复杂，但是填充的内容却很少
struct clk clk_27m = {
.name   = "clk_27m",
.id   = -1,
.rate   = 27000000,
};

//函数负责开关48M的clk，控制others寄存器的第16bit
static int clk_48m_ctrl(struct clk *clk, int enable)
{
unsigned long flags;
u32 val;
/* can't rely on clock lock, this register has other usages */
local_irq_save(flags);
val = __raw_readl(S3C64XX_OTHERS); //这个others寄存器，数据手册中还真的有
           //OTHERS 0x7E00_F900 R/W Others control register 0x0000_801E
if (enable)
   val |= S3C64XX_OTHERS_USBMASK;
//USB_SIG_MASK [16]
//USB signal mask to prevent unwanted leakage. (This bit must set before USB PHY is used.)
else
   val &= ~S3C64XX_OTHERS_USBMASK;
__raw_writel(val, S3C64XX_OTHERS);
local_irq_restore(flags);
return 0;
}

//48M时钟的结构体，多了个东西，enable，就是上面那个函数！
struct clk clk_48m = {
.name   = "clk_48m",
.id   = -1,
.rate   = 48000000,
.enable   = clk_48m_ctrl,
};

//inline函数貌似对时序要求比较高，看来这是个通用的时钟开关函数
static int inline s3c64xx_gate(void __iomem *reg, //
     struct clk *clk,      //传入clk结构体
     int enable)        //传入开关量
{
unsigned int ctrlbit = clk->ctrlbit;
u32 con;
con = __raw_readl(reg);
if (enable)
   con |= ctrlbit;
else
   con &= ~ctrlbit;
__raw_writel(con, reg);
return 0;
}

//pclk控制函数。。体会到了封装的感觉
static int s3c64xx_pclk_ctrl(struct clk *clk, int enable)
{
return s3c64xx_gate(S3C_PCLK_GATE, clk, enable);
}

//hclk控制函数
static int s3c64xx_hclk_ctrl(struct clk *clk, int enable)
{
return s3c64xx_gate(S3C_HCLK_GATE, clk, enable);
}
//sclk控制函数
int s3c64xx_sclk_ctrl(struct clk *clk, int enable)
{
return s3c64xx_gate(S3C_SCLK_GATE, clk, enable);
}
//时钟初始化结构体数组！init_clocks_disable，这儿为啥是disable？
//clk_h、clk_p的定义在plat-s3c/clock.c中
//nand、adc、i2c、iisx2、spix2、48Mx3、otg
static struct clk init_clocks_disable[] = {
{
   .name   = "nand",
   .id   = -1,
   .parent   = &clk_h, 
}, {
   .name   = "adc",
   .id   = -1,
   .parent   = &clk_p,
   .enable   = s3c64xx_pclk_ctrl,
   .ctrlbit = S3C_CLKCON_PCLK_TSADC,
}, {
   .name   = "i2c",
   .id   = -1,
   .parent   = &clk_p,
   .enable   = s3c64xx_pclk_ctrl,
   .ctrlbit = S3C_CLKCON_PCLK_IIC,
}, {
   .name   = "iis",
   .id   = 0,
   .parent   = &clk_p,
   .enable   = s3c64xx_pclk_ctrl,
   .ctrlbit = S3C_CLKCON_PCLK_IIS0,
}, {
   .name   = "iis",
   .id   = 1,
   .parent   = &clk_p,
   .enable   = s3c64xx_pclk_ctrl,
   .ctrlbit = S3C_CLKCON_PCLK_IIS1,
}, {
   .name   = "spi",
   .id   = 0,
   .parent   = &clk_p,
   .enable   = s3c64xx_pclk_ctrl,
   .ctrlbit = S3C_CLKCON_PCLK_SPI0,
}, {
   .name   = "spi",
   .id   = 1,
   .parent   = &clk_p,
   .enable   = s3c64xx_pclk_ctrl,
   .ctrlbit = S3C_CLKCON_PCLK_SPI1,
}, {
   .name   = "48m",
   .id   = 0,
   .parent   = &clk_48m,
   .enable   = s3c64xx_sclk_ctrl,
   .ctrlbit = S3C_CLKCON_SCLK_MMC0_48,
}, {
   .name   = "48m",
   .id   = 1,
   .parent   = &clk_48m,
   .enable   = s3c64xx_sclk_ctrl,
   .ctrlbit = S3C_CLKCON_SCLK_MMC1_48,
}, {
   .name   = "48m",
   .id   = 2,
   .parent   = &clk_48m,
   .enable   = s3c64xx_sclk_ctrl,
   .ctrlbit = S3C_CLKCON_SCLK_MMC2_48,
}, {
   .name    = "otg",
   .id    = -1,
   .parent = &clk_h,
   .enable = s3c64xx_hclk_ctrl,
   .ctrlbit = S3C_CLKCON_HCLK_USB
},
};

//又一个时钟初始化结构体数组 init_clocks
//lcd、gpio、host、hsmmcx3、timers、uartx4、rtc、watchdog、ac97
static struct clk init_clocks[] = {
{
   .name   = "lcd",
   .id   = -1,
   .parent   = &clk_h,
   .enable   = s3c64xx_hclk_ctrl,
   .ctrlbit = S3C_CLKCON_HCLK_LCD,
}, {
   .name   = "gpio",
   .id   = -1,
   .parent   = &clk_p,
   .enable   = s3c64xx_pclk_ctrl,
   .ctrlbit = S3C_CLKCON_PCLK_GPIO,
}, {
   .name   = "usb-host",
   .id   = -1,
   .parent   = &clk_h,
   .enable   = s3c64xx_hclk_ctrl,
   .ctrlbit = S3C_CLKCON_SCLK_UHOST,
},

{
   .name   = "hsmmc",
   .id   = 0,
   .parent   = &clk_h,
   .enable   = s3c64xx_hclk_ctrl,
   .ctrlbit = S3C_CLKCON_HCLK_HSMMC0,
}, {
   .name   = "hsmmc",
   .id   = 1,
   .parent   = &clk_h,
   .enable   = s3c64xx_hclk_ctrl,
   .ctrlbit = S3C_CLKCON_HCLK_HSMMC1,
}, {
   .name   = "hsmmc",
   .id   = 2,
   .parent   = &clk_h,
   .enable   = s3c64xx_hclk_ctrl,
   .ctrlbit = S3C_CLKCON_HCLK_HSMMC2,
},

{
   .name   = "timers",
   .id   = -1,
   .parent   = &clk_p,
   .enable   = s3c64xx_pclk_ctrl,
   .ctrlbit = S3C_CLKCON_PCLK_PWM,
}, {
   .name   = "uart",
   .id   = 0,
   .parent   = &clk_p,
   .enable   = s3c64xx_pclk_ctrl,
   .ctrlbit = S3C_CLKCON_PCLK_UART0,
}, {
   .name   = "uart",
   .id   = 1,
   .parent   = &clk_p,
   .enable   = s3c64xx_pclk_ctrl,
   .ctrlbit = S3C_CLKCON_PCLK_UART1,
}, {
   .name   = "uart",
   .id   = 2,
   .parent   = &clk_p,
   .enable   = s3c64xx_pclk_ctrl,
   .ctrlbit = S3C_CLKCON_PCLK_UART2,
}, {
   .name   = "uart",
   .id   = 3,
   .parent   = &clk_p,
   .enable   = s3c64xx_pclk_ctrl,
   .ctrlbit = S3C_CLKCON_PCLK_UART3,
}, {
   .name   = "rtc",
   .id   = -1,
   .parent   = &clk_p,
   .enable   = s3c64xx_pclk_ctrl,
   .ctrlbit = S3C_CLKCON_PCLK_RTC,
}, {
   .name   = "watchdog",
   .id   = -1,
   .parent   = &clk_p,
   .ctrlbit = S3C_CLKCON_PCLK_WDT,
}, {
   .name   = "ac97",
   .id   = -1,
   .parent   = &clk_p,
   .ctrlbit = S3C_CLKCON_PCLK_AC97,
}
};

//貌似是初始化时加载的clk结构体数组 clks
static struct clk *clks[] __initdata = {
&clk_ext, //plat-s3c/clock.c
&clk_epll, //plat-s3c/clock.c
&clk_27m,
&clk_48m,
};

//初始化时钟注册函数
void __init s3c64xx_register_clocks(void)
{
struct clk *clkp;
int ret;
int ptr;

s3c24xx_register_clocks(clks, ARRAY_SIZE(clks)); 
//还是在plat-s3c/clock.c，既然没法回避，就先看看
//clks就是上面那个，成员有4个 
//s3c24xx_register_clocks////////////////////////////////////////////////////////////////////
int s3c24xx_register_clocks(struct clk **clks, int nr_clks)
{
int fails = 0;
for (; nr_clks > 0; nr_clks--, clks++)    //应该循环4次，统计注册失败的次数
   {  
   if (s3c24xx_register_clock(*clks) < 0)
    fails++;
   }

return fails;
}
//s3c24xx_register_clock//////////////////////////////////////////////////////////////////////////////////////////////
//注意下面的函数和上面只有一个s的差别，真正注册时钟来了
int s3c24xx_register_clock(struct clk *clk)
{
clk->owner = THIS_MODULE;
if (clk->enable == NULL)
   clk->enable = clk_null_enable;

/* add to the list of available clocks */
/* Quick check to see if this clock has already been registered. */
BUG_ON(clk->list.prev != clk->list.next);
//BUG_ON这个宏很好玩，如果它不满足，说明肯定有BUG，系统会人为造一个oops出来，让你知道有问题。
//#define BUG_ON(condition) do { if (unlikely(condition)) BUG(); } while(0)

spin_lock(&clocks_lock);
list_add(&clk->list, &clocks);
spin_unlock(&clocks_lock);

return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////


clkp = init_clocks;
for (ptr = 0; ptr < ARRAY_SIZE(init_clocks); ptr++, clkp++) {
   ret = s3c24xx_register_clock(clkp);
   if (ret < 0) {
    printk(KERN_ERR "Failed to register clock %s (%d)/n",
          clkp->name, ret);
   }
}

clkp = init_clocks_disable;
for (ptr = 0; ptr < ARRAY_SIZE(init_clocks_disable); ptr++, clkp++) {

   ret = s3c24xx_register_clock(clkp);
   if (ret < 0) {
    printk(KERN_ERR "Failed to register clock %s (%d)/n",
          clkp->name, ret);
   }

   (clkp->enable)(clkp, 0); //看到这里终于明白为啥叫init disable了，在这里相当调用每个结构体成员的enable函数。
}

s3c_pwmclk_init(); //说来这个函数放这里怎么有点不正规的感觉啊，初始化pwm的clk?
       //不过前面的确没看到pwm的相关clk结构体呢
       //函数位于arch/arm/plat-s3c/pwm-clokc.c下次看吧
}
