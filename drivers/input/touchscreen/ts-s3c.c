/* linux/drivers/input/touchscreen/s3c-ts.c
 * 见Kconfig可知支持ARCH_S3C2410 || ARCH_S3C64XX || ARCH_S5PV2XX || ARCH_S5P64XX || CPU_S5PV210 || CPU_S5PC110
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Copyright (c) 2004 Arnaud Patard <arnaud.patard@rtp-net.org>
 * iPAQ H1940 touchscreen support
 *
 * ChangeLog
 *
 * 2004-09-05: Herbert Potzl <herbert@13thfloor.at>
 *	- added clock (de-)allocation code
 *
 * 2005-03-06: Arnaud Patard <arnaud.patard@rtp-net.org>
 *      - h1940_ -> s3c24xx (this driver is now also used on the n30
 *        machines :P)
 *      - Debug messages are now enabled with the config option
 *        TOUCHSCREEN_S3C_DEBUG
 *      - Changed the way the value are read
 *      - Input subsystem should now work
 *      - Use ioremap and readl/writel
 *
 * 2005-03-23: Arnaud Patard <arnaud.patard@rtp-net.org>
 *      - Make use of some undocumented features of the touchscreen
 *        controller
 *
 * 2006-09-05: Ryu Euiyoul <ryu.real@gmail.com>
 *      - added power management suspend and resume code
 *
 */

//#include <linux/errno.h>
//#include <linux/kernel.h>
//#include <linux/module.h>
//#include <linux/slab.h>
//#include <linux/input.h>
//#include <linux/init.h>
//#include <linux/serio.h>
//#include <linux/delay.h>
//#include <linux/platform_device.h>
//#include <linux/clk.h>
#ifdef CONFIG_HAS_EARLYSUSPEND
//#include <linux/earlysuspend.h>
#endif
//#include <linux/io.h>
//#include <asm/irq.h>
//#include <mach/hardware.h>

//#include <mach/regs-adc.h>
//#include <mach/ts-s3c.h>
//#include <mach/irqs.h>

#define CONFIG_CPU_S5PV210_EVT1

#ifdef CONFIG_CPU_S5PV210_EVT1
#define X_COOR_MIN	100
#define X_COOR_MAX	3980
#define X_COOR_FUZZ	32
#define Y_COOR_MIN	200
#define Y_COOR_MAX	3760
#define Y_COOR_FUZZ	32
#endif

/* For ts->dev.id.version */
#define S3C_TSVERSION	0x0101

#define WAIT4INT(x)	(((x)<<8) | \
			S3C_ADCTSC_YM_SEN | S3C_ADCTSC_YP_SEN | \
			S3C_ADCTSC_XP_SEN | S3C_ADCTSC_XY_PST(3))

#define AUTOPST	(S3C_ADCTSC_YM_SEN | S3C_ADCTSC_YP_SEN | \
		 S3C_ADCTSC_XP_SEN | S3C_ADCTSC_AUTO_PST | \
		 S3C_ADCTSC_XY_PST(0))

#ifdef CONFIG_HAS_EARLYSUSPEND
static void ts_early_suspend(struct early_suspend *h);
static void ts_late_resume(struct early_suspend *h);
#endif

/* Touchscreen default configuration==========如果板级设置没有这个，则设置默认设置*/
struct s3c_ts_mach_info s3c_ts_default_cfg /* __initdata */ = {
	.delay			= 10000,
	.presc			= 49,
	.oversampling_shift	= 2,
	.resol_bit		= 10，
};

/*
 * Definitions & global arrays.
 */
static char *s3c_ts_name = "S5P TouchScreen";
static void __iomem		*ts_base;
static struct resource		*ts_mem;
static struct resource		*ts_irq;
static struct clk		*ts_clock;
static struct s3c_ts_info	*ts;


//这里，关键的内容是当updown的值为1，也即触摸笔按下时，会调用touch_timer_fire(0);
//触摸中断处理的具体内容都在touch_timer_fire中了，下面来分析touch_timer_fire的内容。
static void touch_timer_fire(unigned long data)
{
	unsigned long data0;
	unsigned long data1;
	int updown;
	int x, y;
	//读取AD转换数据的值
	data0 = readl(ts_base+S3C_ADCDAT0);
	data1 = readl(ts_base+S3C_ADCDAT1);
	//判断data0,data1最高位是否仍为"0"，为“0”表示触摸笔状态保持为down
	updown = (!(data0 & S3C_ADCDAT0_UPDOWN)) &&
		 (!(data1 & S3C_ADCDAT1_UPDOWN));
     /*
       更新stylus状态寄存器updown：
       1 = down
       0 = up
      */
    /*
      touch_timer_fire这个函数主要实现以下功能：
      1、stylus down的时候，在中断函数stylus_updown里面被调用，
         此时缓存区没有数据，ts.count为0，所以只是简单的设置ad转换的模式，然后开启ad转换。
      2、但ADC中断函数stylus_action把缓冲区填满的时候，作为中断后半段函数稍后被调用，
         此时ts.count为4，算出其平均值后，交给事件处理层(Event Handler)处理，
         主要是填写缓冲，然后唤醒等待输入数据的进程。
      3、stylus抬起，等到缓冲区填满后(可能会包含一些无用的数据)被调用，
         这时候判断出stylus up，报告stylus up事件，重新等待stylus down。
   */
	if (updown) {
		if (ts->count) {//保持为down，且记录了xp和yp的数据，则对这些数据进行处理
			x = (int)ts->xp/ts->count;
			y = (int)ts->yp/ts->count;
#ifdef CONFIG_FB_S3C_LTE480WV
			y = 4000 - y;
#endif
			input_report_abs(ts->dev, ABS_X, x);
			input_report_abs(ts->dev, ABS_Y, y);
			input_report_abs(ts->dev, ABS_Z, 0);
			input_report_key(ts->dev, BTN_TOUCH, 1);
			input_sync(ts->dev);
		}

		ts->xp = 0;
		ts->yp = 0;
		ts->count = 0;
		//AUTOPST表示Auto Sequential measurement of X-position, Y-position.
		writel(S3C_ADCTSC_PULL_UP_DISABLE | AUTOPST,
				ts_base + S3C_ADCTSC);
		// 启动D转换，转换后会产生中断IRQ_ADC	===================================================	
		writel(readl(ts_base+S3C_ADCCON) | S3C_ADCCON_ENABLE_START,
				ts_base + S3C_ADCCON);
	} else {
		// 当触摸笔为抬起状态时，报告其触摸笔状态
		ts->count = 0;
		input_report_abs(ts->dev, ABS_X, ts->xp);//向上报告LCD坐标位置（x、y的绝对坐标值）
		input_report_abs(ts->dev, ABS_Y, ts->yp);
		input_report_abs(ts->dev, ABS_Z, 0);
		input_report_key(ts->dev, BTN_TOUCH, 0);//报告按键事件——触摸事件
		input_sync(ts->dev);
		//清除触摸笔按下的中断信号
		writel(WAIT4INT(0), ts_base+S3C_ADCTSC);
	}
}

static struct timer_list touch_timer =
		TIMER_INITIALIZER(touch_timer_fire, 0, 0);

static irqreturn_t stylus_updown(int irqno, void *param)
{ //中断处理上半部分===处理触摸的中断服务程序=============判断触摸屏是否按下的中断
	unsigned long data0;
	unsigned long data1;
	int updown;

	data0 = readl(ts_base + S3C_ADCDAT0);
	data1 = readl(ts_base + S3C_ADCDAT1);
	//判断data0,data1最高位是否为"0"，为0表示按下
	updown = (!(data0 & S3C_ADCDAT0_UPDOWN)) &&
		 (!(data1 & S3C_ADCDAT1_UPDOWN));

	/* TODO we should never get an interrupt with updown set while
	 * the timer is running, but maybe we ought to verify that the
	 * timer isn't running anyways. */

	if (updown)//判断触摸笔有没有按下，1表示按下。
		touch_timer_fire(0);

	if (ts->s3c_adc_con == ADC_TYPE_2) { //如果为S3C64XX或 S5PC1XX
		__raw_writel(0x0, ts_base + S3C_ADCCLRWK);
		__raw_writel(0x0, ts_base + S3C_ADCCLRINT);
	}

	return IRQ_HANDLED;
}

// stylus_action为中断处理函数的下半部分——ADC转换的中断服务程序。其内容进行的操作大部分是缓冲器数据的填充，
//如：ts->yp、ts->xp、ts->count、S3C_ADCTSC、S3C_ADCCON、S3C_ADCCLRWK、S3C_ADCCLRINT。其中ts->yp、ts->xp 中
//的值经处理后传入上层；ts->count 作为标志；而S3C_ADCTSC、S3C_ADCCON 等是对AD转换的触摸屏控制寄存器和配置寄存器等寄存器进行操作。
static irqreturn_t stylus_action(int irqno, void *param)
{//中断处理下半部分============触摸屏按下会产生ADC转换的中断
	unsigned long data0;
	unsigned long data1;

	data0 = readl(ts_base + S3C_ADCDAT0);
	data1 = readl(ts_base + S3C_ADCDAT1);
	//如果转换精度为12位，则进行相当的数据处理
	if (ts->resol_bit == 12) {
#if defined(CONFIG_TOUCHSCREEN_NEW)
	//累加转换的12位数据[11：0]，记录x,y点的位置（因为累加，到后面要取平均值）。
		ts->yp += S3C_ADCDAT0_XPDATA_MASK_12BIT -
			(data0 & S3C_ADCDAT0_XPDATA_MASK_12BIT);
		ts->xp += S3C_ADCDAT1_YPDATA_MASK_12BIT -
			(data1 & S3C_ADCDAT1_YPDATA_MASK_12BIT);
#else
		ts->xp += S3C_ADCDAT0_XPDATA_MASK_12BIT -
			(data0 & S3C_ADCDAT0_XPDATA_MASK_12BIT);
		ts->yp += data1 & S3C_ADCDAT1_YPDATA_MASK_12BIT;
#endif
	} else {
#if defined(CONFIG_TOUCHSCREEN_NEW)
		ts->yp += S3C_ADCDAT0_XPDATA_MASK -
			(data0 & S3C_ADCDAT0_XPDATA_MASK);
		ts->xp += S3C_ADCDAT1_YPDATA_MASK -
			(data1 & S3C_ADCDAT1_YPDATA_MASK);
#else
		ts->xp += data0 & S3C_ADCDAT0_XPDATA_MASK;
		ts->yp += data1 & S3C_ADCDAT1_YPDATA_MASK;
#endif
	}
	//记录累加的次数
	ts->count++;
	//若累加的次数没有溢出，则Auto Sequential measurement并启动AD转换
	if (ts->count < (1<<ts->shift)) {        /* 缓冲区未满，再次激活ADC转换 */
		writel(S3C_ADCTSC_PULL_UP_DISABLE | AUTOPST,
				ts_base + S3C_ADCTSC);
		writel(readl(ts_base + S3C_ADCCON) | S3C_ADCCON_ENABLE_START,
				ts_base + S3C_ADCCON);
	} else {	        /* 缓冲区满，激活下半部处理程序touch_timer_fire，处理接收数据 */
		mod_timer(&touch_timer, jiffies + 1);//若touch_timer超时，则修改定时器为jiffies+1
		writel(WAIT4INT(1), ts_base + S3C_ADCTSC);
	}
	//如果为S3C64XX或 S5PC1XX
	if (ts->s3c_adc_con == ADC_TYPE_2) {
		__raw_writel(0x0, ts_base+S3C_ADCCLRWK);
		__raw_writel(0x0, ts_base+S3C_ADCCLRINT);
	}
	return IRQ_HANDLED;
}

static struct s3c_ts_mach_info *s3c_ts_get_platdata(struct device *dev)
{
	if (dev->platform_data != NULL)//===================================如果板级没有设置，则设置默认设置
		return (struct s3c_ts_mach_info *)dev->platform_data;//使用板级设置�

	return &s3c_ts_default_cfg;//使用默认设置
}

/*
 * The functions for inserting/removing us as a module.

 使用input子系统的一般流程为：input_allocate_device()申请一个input_dev设备——>初始化该input_dev——>
 input_register_device（）向子系统注册该设备——>中断时input_event（）向子系统报告事件。此流程一目了然，
 即使不看input子系统，我们按照它给出的一般流程也可以把自己写的IO驱动加入到input子系统里去，但
 input_event（）提交完数据后，我们的数据去哪了呢，怎么处理呢，总觉得云里雾里的，总想一探究竟。*/
static int __init s3c_ts_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct device *dev;
	struct input_dev *input_dev;
	struct s3c_ts_mach_info *s3c_ts_cfg;
	int ret, size;
	int irq_flags = 0;

	dev = &pdev->dev;
	//==================================初始化ADC内存相关*=======================================
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);//获取IO内存，见static struct resource s3c_ts_resource[] = {
	if (res == NULL) {
		dev_err(dev, "no memory resource specified\n");
		return -ENOENT;
	}

	size = (res->end - res->start) + 1;//获取资源大小，见static struct resource s3c_ts_resource[] = {
	ts_mem = request_mem_region(res->start, size, pdev->name);//申请内存，从res->start开始，size大小
	if (ts_mem == NULL) {
		dev_err(dev, "failed to get memory region\n");
		ret = -ENOENT;
		goto err_req;
	}

	ts_base = ioremap(res->start, size);//重映射为虚拟地址，用于配置寄存器
	if (ts_base == NULL) {
		dev_err(dev, "failed to ioremap() region\n");
		ret = -EINVAL;
		goto err_map;
	}

	ts_clock = clk_get(&pdev->dev, "adc");//获取时钟，用于使能时钟,见linux/arch/arm/mach-s5pv210/clock.c  init_clocks_disable
	if (IS_ERR(ts_clock)) {
		dev_err(dev, "failed to find watchdog clock source\n");
		ret = PTR_ERR(ts_clock);
		goto err_clk;
	}

	clk_enable(ts_clock);
	//==================================初始化ADC寄存器*=======================================
	s3c_ts_cfg = s3c_ts_get_platdata(&pdev->dev);//获取平台数据
	if ((s3c_ts_cfg->presc & 0xff) > 0)
		writel(S3C_ADCCON_PRSCEN |S3C_ADCCON_PRSCVL(s3c_ts_cfg->presc & 0xFF),ts_base+S3C_ADCCON);//将配置写入寄存器S3C_ADCCON中
	else
		writel(0, ts_base + S3C_ADCCON);

	/* Initialise registers ===============初始化ADC寄存器*/
	if ((s3c_ts_cfg->delay & 0xffff) > 0)
		writel(s3c_ts_cfg->delay & 0xffff, ts_base + S3C_ADCDLY);//将延时配置写入寄存器

	if (s3c_ts_cfg->resol_bit == 12) {
		switch (s3c_ts_cfg->s3c_adc_con) {//选择ADC类型
		case ADC_TYPE_2:
			writel(readl(ts_base + S3C_ADCCON) |
					S3C_ADCCON_RESSEL_12BIT,
					ts_base + S3C_ADCCON);//将类型配置写入寄存器
			break;

		case ADC_TYPE_1:
			writel(readl(ts_base + S3C_ADCCON) |
					S3C_ADCCON_RESSEL_12BIT_1,
					ts_base + S3C_ADCCON);//将类型配置写入寄存器
			break;

		default:
			dev_err(dev, "this type of AP isn't supported !\n");
			break;
		}
	}

	writel(WAIT4INT(0), ts_base + S3C_ADCTSC);
	//=================================初始化ADC相关信息s3c_ts_info*========================================
	ts = kzalloc(sizeof(struct s3c_ts_info), GFP_KERNEL);

	input_dev = input_allocate_device();//申请分配一个input_dev设备
	if (!input_dev) {
		ret = -ENOMEM;
		goto err_alloc;
	}

	ts->dev = input_dev;//=================================通过此值注册输入设备

	ts->dev->evbit[0] = BIT_MASK(EV_SYN) | BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	ts->dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

	if (s3c_ts_cfg->resol_bit == 12) {
		input_set_abs_params(ts->dev,
				ABS_X, X_COOR_MIN, X_COOR_MAX, X_COOR_FUZZ, 0);
		input_set_abs_params(ts->dev,
				ABS_Y, Y_COOR_MIN, Y_COOR_MAX, Y_COOR_FUZZ, 0);
	} else {
		input_set_abs_params(ts->dev, ABS_X, 0, 0x3FF, 0, 0);//这个是设置ad转换的x坐标
		input_set_abs_params(ts->dev, ABS_Y, 0, 0x3FF, 0, 0);//这个是设置ad转换的y坐标
	}

	input_set_abs_params(ts->dev, ABS_PRESSURE, 0, 1, 0, 0);

	sprintf(ts->phys, "input(ts)");

	ts->dev->name = s3c_ts_name;
	ts->dev->phys = ts->phys;
	ts->dev->id.bustype = BUS_RS232;
	ts->dev->id.vendor = 0xDEAD;
	ts->dev->id.product = 0xBEEF;
	ts->dev->id.version = S3C_TSVERSION;

	ts->shift = s3c_ts_cfg->oversampling_shift;
	ts->resol_bit = s3c_ts_cfg->resol_bit;
	ts->s3c_adc_con = s3c_ts_cfg->s3c_adc_con;

#ifdef CONFIG_HAS_EARLYSUSPEND
	ts->early_suspend.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN + 1;
	ts->early_suspend.suspend = ts_early_suspend;
	ts->early_suspend.resume = ts_late_resume;
	register_early_suspend(&ts->early_suspend);
#endif
	//=================================初始化ADC中断相关*========================================
	/* For IRQ_PENDUP */
	ts_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);//获取中断号，见static struct resource s3c_ts_resource[] = {
	if (ts_irq == NULL) {
		dev_err(dev, "no irq resource specified\n");
		ret = -ENOENT;
		goto err_irq;
	}

	ret = request_irq(ts_irq->start, stylus_updown, irq_flags, //中断处理上半部分======判断触摸屏是否按下的中断
			"s3c_updown", ts);
	if (ret != 0) {
		dev_err(dev, "s3c_ts.c: Could not allocate ts IRQ_PENDN !\n");
		ret = -EIO;
		goto err_irq;
	}

	/* For IRQ_ADC */
	ts_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 1);//获取中断号，见static struct resource s3c_ts_resource[] = {
	if (ts_irq == NULL) {
		dev_err(dev, "no irq resource specified\n");
		ret = -ENOENT;
		goto err_irq;
	}

	ret = request_irq(ts_irq->start, stylus_action, irq_flags, //中断处理下半部分=====触摸屏按下会产生ADC转换的中断
			"s3c_action", ts);
	if (ret != 0) {
		dev_err(dev, "s3c_ts.c: Could not allocate ts IRQ_ADC !\n");
		ret =  -EIO;
		goto err_irq;
	}

	printk(KERN_INFO "%s got loaded successfully : %d bits\n",
			s3c_ts_name, s3c_ts_cfg->resol_bit);

	/* All went ok, so register to the input system ============注册输入设备*/
	ret = input_register_device(ts->dev);
	if (ret) {
		dev_err(dev, "Could not register input device(touchscreen)!\n");
		ret = -EIO;
		goto fail;
	}

	return 0;

fail:
	free_irq(ts_irq->start, ts->dev);
	free_irq(ts_irq->end, ts->dev);

err_irq:
	input_free_device(input_dev);
	kfree(ts);

err_alloc:
	clk_disable(ts_clock);
	clk_put(ts_clock);

err_clk:
	iounmap(ts_base);

err_map:
	release_resource(ts_mem);
	kfree(ts_mem);

err_req:
	return ret;
}

static int s3c_ts_remove(struct platform_device *dev)
{
	printk(KERN_INFO "s3c_ts_remove() of TS called !\n");

	disable_irq(IRQ_ADC);
	disable_irq(IRQ_PENDN);

	free_irq(IRQ_PENDN, ts->dev);
	free_irq(IRQ_ADC, ts->dev);

	if (ts_clock) {
		clk_disable(ts_clock);
		clk_put(ts_clock);
		ts_clock = NULL;
	}

#ifdef CONFIG_HAS_EARLYSUSPEND
     unregister_early_suspend(&ts->early_suspend);
#endif

	input_unregister_device(ts->dev);
	iounmap(ts_base);

	return 0;
}

#ifdef CONFIG_PM
static unsigned int adccon, adctsc, adcdly;

static int s3c_ts_suspend(struct platform_device *dev, pm_message_t state)
{
	adccon = readl(ts_base+S3C_ADCCON);
	adctsc = readl(ts_base+S3C_ADCTSC);
	adcdly = readl(ts_base+S3C_ADCDLY);

	disable_irq(IRQ_ADC);
	disable_irq(IRQ_PENDN);

	clk_disable(ts_clock);

	return 0;
}

static int s3c_ts_resume(struct platform_device *pdev)
{
	clk_enable(ts_clock);

	writel(adccon, ts_base+S3C_ADCCON);
	writel(adctsc, ts_base+S3C_ADCTSC);
	writel(adcdly, ts_base+S3C_ADCDLY);
	writel(WAIT4INT(0), ts_base+S3C_ADCTSC);

	enable_irq(IRQ_ADC);
	enable_irq(IRQ_PENDN);

	return 0;
}
#else
#define s3c_ts_suspend NULL
#define s3c_ts_resume  NULL
#endif

#ifdef CONFIG_HAS_EARLYSUSPEND
static void ts_early_suspend(struct early_suspend *h)
{
	struct s3c_ts_info *ts;
	ts = container_of(h, struct s3c_ts_info, early_suspend);
	s3c_ts_suspend(NULL, PMSG_SUSPEND);
}

static void ts_late_resume(struct early_suspend *h)
{
	struct s3c_ts_info *ts;
	ts = container_of(h, struct s3c_ts_info, early_suspend);
	s3c_ts_resume(NULL);
}
#endif

static struct platform_driver s3c_ts_driver = {
       .probe          = s3c_ts_probe,
       .remove         = s3c_ts_remove,
       .suspend        = s3c_ts_suspend,
       .resume         = s3c_ts_resume,
       .driver		= {
		.owner	= THIS_MODULE,
		.name	= "s3c-ts",
	},
};

static char banner[] /* __initdata */ = KERN_INFO \
		"S5P Touchscreen driver, (c) 2008 Samsung Electronics\n";

static int __init s3c_ts_init(void)
{
	printk(banner);
	return platform_driver_register(&s3c_ts_driver);
}

static void __exit s3c_ts_exit(void)
{
	platform_driver_unregister(&s3c_ts_driver);
}

//module_init(s3c_ts_init);
//module_exit(s3c_ts_exit);

//MODULE_AUTHOR("Samsung AP");
//MODULE_DESCRIPTION("S5P touchscreen driver");
//MODULE_LICENSE("GPL");
