/* linux/arch/arm/mach-s5pv210/mach-smdkc110.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

//#include <linux/kernel.h>
//#include <linux/types.h>
//#include <linux/init.h>
//#include <linux/serial_core.h>
//#include <linux/gpio.h>
//#include <linux/gpio_event.h>
//#include <linux/videodev2.h>
//#include <linux/i2c.h>
//#include <linux/i2c-gpio.h>
//#include <linux/regulator/consumer.h>
#if defined(CONFIG_SMDKC110_REV03) || defined(CONFIG_SMDKV210_REV02)
//#include <linux/mfd/max8998.h>
#else
//#include <linux/mfd/max8698.h>
#endif
//#include <linux/clk.h>
//#include <linux/delay.h>
//#include <linux/usb/ch9.h>
//#include <linux/pwm_backlight.h>
//#include <linux/spi/spi.h>
//#include <linux/spi/spi_gpio.h>
//#include <linux/clk.h>
//#include <linux/usb/ch9.h>
//#include <linux/input.h>
//#include <linux/irq.h>
//#include <linux/skbuff.h>
//#include <linux/console.h>

//#include <asm/mach/arch.h>
//#include <asm/mach/map.h>
//#include <asm/setup.h>
//#include <asm/mach-types.h>
//#include <asm/system.h>

//#include <mach/map.h>
//#include <mach/regs-clock.h>
//#include <mach/regs-mem.h>
//#include <mach/gpio.h>
//#include <mach/gpio-smdkc110.h>
//#include <mach/regs-gpio.h>
//#include <mach/ts-s3c.h>
//#include <mach/adc.h>
//#include <mach/param.h>
//#include <mach/system.h>

#ifdef CONFIG_S3C64XX_DEV_SPI
//#include <plat/s3c64xx-spi.h>
//#include <mach/spi-clocks.h>
#endif

//#include <linux/usb/gadget.h>

//#include <plat/media.h>
//#include <mach/media.h>

#ifdef CONFIG_ANDROID_PMEM
//#include <linux/android_pmem.h>
//#include <plat/media.h>
//#include <mach/media.h>
#endif

#ifdef CONFIG_S5PV210_POWER_DOMAIN
//#include <mach/power-domain.h>
#endif

#ifdef CONFIG_VIDEO_S5K4BA
//#include <media/s5k4ba_platform.h>
#undef	CAM_ITU_CH_B
#define	CAM_ITU_CH_A
#endif

#ifdef CONFIG_VIDEO_S5K4EA
//#include <media/s5k4ea_platform.h>
#endif

//#include <plat/regs-serial.h>
//#include <plat/s5pv210.h>
//#include <plat/devs.h>
//#include <plat/cpu.h>
//#include <plat/fb.h>
//#include <plat/mfc.h>
//#include <plat/iic.h>
//#include <plat/pm.h>

//#include <plat/sdhci.h>
//#include <plat/fimc.h>
//#include <plat/csis.h>
//#include <plat/jpeg.h>
//#include <plat/clock.h>
//#include <plat/regs-otg.h>
//#include <../../../drivers/video/samsung/s3cfb.h>

extern void s3c_sdhci_set_platdata(void);
//=======================================================================================================================

/* Following are default values for UCON, ULCON and UFCON UART registers */
/*
串口初始化结构体
UART的设置（UCONn、ULCONn、UFCONn寄存器等）
*/
#define S5PV210_UCON_DEFAULT	(S3C2410_UCON_TXILEVEL |	\
				 S3C2410_UCON_RXILEVEL |	\
				 S3C2410_UCON_TXIRQMODE |	\
				 S3C2410_UCON_RXIRQMODE |	\
				 S3C2410_UCON_RXFIFO_TOI |	\
				 S3C2443_UCON_RXERR_IRQEN)

#define S5PV210_ULCON_DEFAULT	S3C2410_LCON_CS8

#define S5PV210_UFCON_DEFAULT	(S3C2410_UFCON_FIFOMODE |	\
				 S5PV210_UFCON_TXTRIG4 |	\
				 S5PV210_UFCON_RXTRIG4)
//由s3c24xx_init_uarts初始化。内核配置选项CONFIG_DEBUG_S3C_UART=2，则使用COM2来调试
static struct s3c2410_uartcfg smdkc110_uartcfgs[] /* __initdata */ = {
	{
		.hwport		= 0,
		.flags		= 0,
		.ucon		= S5PV210_UCON_DEFAULT,//UCON :时钟选择01 = EXT_UCLK0: DIV_VAL1) = (EXT_UCLK0 / (bps x 16) ) –1
         // | Tx中断类型level | Rx中断类型level | 开Rx超时中断 | 发送中断或轮询模式 | 接收中断或轮询模式
         //EXT_UCLK0 clock is external clock.(XpwmECLK PAD input) 为何是EXT_UCLK0?
		.ulcon		= S5PV210_ULCON_DEFAULT,//ULCON:配置为8bit
		.ufcon		= S5PV210_UFCON_DEFAULT,//UFCON: Tx FIFO Tri level 16byte | Rx FIFO Trigger level 8byte | Tx FIFO normal | Rx FIFO normal | FIFO enable
	},
	{
		.hwport		= 1,
		.flags		= 0,
		.ucon		= S5PV210_UCON_DEFAULT,
		.ulcon		= S5PV210_ULCON_DEFAULT,
		.ufcon		= S5PV210_UFCON_DEFAULT,
	},
#ifndef CONFIG_FIQ_DEBUGGER
	{
		.hwport		= 2,
		.flags		= 0,
		.ucon		= S5PV210_UCON_DEFAULT,
		.ulcon		= S5PV210_ULCON_DEFAULT,
		.ufcon		= S5PV210_UFCON_DEFAULT,
	},
#endif
	{
		.hwport		= 3,
		.flags		= 0,
		.ucon		= S5PV210_UCON_DEFAULT,
		.ulcon		= S5PV210_ULCON_DEFAULT,
		.ufcon		= S5PV210_UFCON_DEFAULT,
	},
};
//=======================================================================================================================

#define LCD_800480//默认LCD分辨率
//#define VGA_800600
//#define VGA_1024768

#ifdef LCD_800480
#define S5PV210_LCD_WIDTH 800
#define S5PV210_LCD_HEIGHT 480
#endif 

#ifdef VGA_800600
#define S5PV210_LCD_WIDTH 800
#define S5PV210_LCD_HEIGHT 600
#endif 

#ifdef VGA_1024768
#define S5PV210_LCD_WIDTH 1024
#define S5PV210_LCD_HEIGHT 768
#endif
//FIMC---------
//#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC0 (6144 * SZ_1K)
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC0 (24576 * SZ_1K)
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC1 (9900 * SZ_1K)
//#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC2 (6144 * SZ_1K)
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC2 (24576 * SZ_1K)
//MFC---------
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_MFC0 (36864 * SZ_1K)
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_MFC1 (36864 * SZ_1K)
//FIMD---------
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMD (S5PV210_LCD_WIDTH * \
					     S5PV210_LCD_HEIGHT * 4 * \
					     CONFIG_FB_S3C_NR_BUFFERS)
// xxs
//#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_JPEG (8192 * SZ_1K)
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_JPEG (12000 * SZ_1K)

/* 1920 * 1080 * 4 (RGBA)
 * - framesize == 1080p : 1920 * 1080 * 2(16bpp) * 2(double buffer) = 8MB
 * - framesize <  1080p : 1080 *  720 * 4(32bpp) * 2(double buffer) = under 8MB
 **/
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_G2D (8192 * SZ_1K)
#define  S5PV210_VIDEO_SAMSUNG_MEMSIZE_TEXSTREAM (3000 * SZ_1K)
#define  S5PV210_ANDROID_PMEM_MEMSIZE_PMEM_GPU1 (3300 * SZ_1K)
//=======================================================================================================================
static struct s5p_media_device smdkc110_media_devs[] = {
	[0] = {
		.id = S5P_MDEV_MFC,
		.name = "mfc",
		.bank = 0,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_MFC0,
		.paddr = 0,
	},
	[1] = {
		.id = S5P_MDEV_MFC,
		.name = "mfc",
		.bank = 1,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_MFC1,
		.paddr = 0,
	},
	[2] = {
		.id = S5P_MDEV_FIMC0,
		.name = "fimc0",
		.bank = 1,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC0,
		.paddr = 0,
	},
	[3] = {
		.id = S5P_MDEV_FIMC1,
		.name = "fimc1",
		.bank = 1,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC1,
		.paddr = 0,
	},
	[4] = {
		.id = S5P_MDEV_FIMC2,
		.name = "fimc2",// Fully Interactive Mobile Camera （完全交互式移动摄像机）
		.bank = 1,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMC2,
		.paddr = 0,
	},
	[5] = {
		.id = S5P_MDEV_JPEG,
		.name = "jpeg",
		.bank = 0,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_JPEG,
		.paddr = 0,
	},
	[6] = {
		.id = S5P_MDEV_FIMD,
		.name = "fimd",// Fully Interactive Mobile Display （完全交互式移动显示设备）
		.bank = 1,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_FIMD,
		.paddr = 0,
	},
	[7] = {
		.id = S5P_MDEV_TEXSTREAM,
		.name = "texstream",
		.bank = 1,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_TEXSTREAM,
		.paddr = 0,
	},
	[8] = {
		.id = S5P_MDEV_PMEM_GPU1,
		.name = "pmem_gpu1",
		.bank = 0, /* OneDRAM */
		.memsize = S5PV210_ANDROID_PMEM_MEMSIZE_PMEM_GPU1,
		.paddr = 0,
	},
	[9] = {
		.id = S5P_MDEV_G2D,
		.name = "g2d",
		.bank = 0,
		.memsize = S5PV210_VIDEO_SAMSUNG_MEMSIZE_G2D,
		.paddr = 0,
	},
};
//=======================================================================================================================
static struct regulator_consumer_supply ldo3_consumer[] = {
	REGULATOR_SUPPLY("pd_io", "s3c-usbgadget")
};

static struct regulator_consumer_supply ldo4_consumer[] = {
	{   .supply = "vddmipi", },
};

static struct regulator_consumer_supply ldo6_consumer[] = {
	{   .supply = "vddlcd", },
};

static struct regulator_consumer_supply ldo7_consumer[] = {
	{   .supply = "vddmodem", },
};

static struct regulator_consumer_supply ldo8_consumer[] = {
	REGULATOR_SUPPLY("pd_core", "s3c-usbgadget")
};

static struct regulator_consumer_supply buck1_consumer[] = {
	{   .supply = "vddarm", },
};

static struct regulator_consumer_supply buck2_consumer[] = {
	{   .supply = "vddint", },
};

static struct regulator_init_data smdkc110_ldo2_data = {
	.constraints	= {
		.name		= "VALIVE_1.1V",
		.min_uV		= 1100000,
		.max_uV		= 1100000,
		.apply_uV	= 1,
		.always_on	= 1,
		.state_mem	= {
			.enabled = 1,
		},
	},
};

static struct regulator_init_data smdkc110_ldo3_data = {
	.constraints	= {
		.name		= "VUOTG_D_1.1V/VUHOST_D_1.1V",
		.min_uV		= 1100000,
		.max_uV		= 1100000,
		.apply_uV	= 1,
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		.state_mem	= {
			.disabled = 1,
		},
	},
	.num_consumer_supplies	= ARRAY_SIZE(ldo3_consumer),
	.consumer_supplies	= ldo3_consumer,
};

static struct regulator_init_data smdkc110_ldo4_data = {
	.constraints	= {
		.name		= "V_MIPI_1.8V",
		.min_uV		= 1800000,
		.max_uV		= 1800000,
		.apply_uV	= 1,
		.always_on	= 1,
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		.state_mem	= {
			.disabled = 1,
		},
	},
	.num_consumer_supplies	= ARRAY_SIZE(ldo4_consumer),
	.consumer_supplies	= ldo4_consumer,
};

static struct regulator_init_data smdkc110_ldo5_data = {
	.constraints	= {
		.name		= "VMMC_2.8V/VEXT_2.8V",
		.min_uV		= 2800000,
		.max_uV		= 2800000,
		.apply_uV	= 1,
		.always_on	= 1,
		.state_mem	= {
			.enabled = 1,
		},
	},
};

static struct regulator_init_data smdkc110_ldo6_data = {
	.constraints	= {
		.name		= "VCC_2.6V",
		.min_uV		= 2600000,
		.max_uV		= 2600000,
		.apply_uV	= 1,
		.always_on	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_STATUS,
		.state_mem	 = {
			.disabled = 1,
		},
	},
	.num_consumer_supplies	= ARRAY_SIZE(ldo6_consumer),
	.consumer_supplies	= ldo6_consumer,
};

static struct regulator_init_data smdkc110_ldo7_data = {
	.constraints	= {
		.name		= "VDAC_2.8V",
		.min_uV		= 2800000,
		.max_uV		= 2800000,
		.apply_uV	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_STATUS,
		.state_mem	= {
			.enabled = 1,
		},
	},
	.num_consumer_supplies  = ARRAY_SIZE(ldo7_consumer),
	.consumer_supplies  = ldo7_consumer,
};

static struct regulator_init_data smdkc110_ldo8_data = {
	.constraints	= {
		.name		= "VUOTG_A_3.3V/VUHOST_A_3.3V",
		.min_uV		= 3300000,
		.max_uV		= 3300000,
		.apply_uV	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_STATUS,
		.state_mem	= {
			.enabled = 1,
		},
	},
	.num_consumer_supplies	= ARRAY_SIZE(ldo8_consumer),
	.consumer_supplies	= ldo8_consumer,
};

static struct regulator_init_data smdkc110_ldo9_data = {
	.constraints	= {
		.name		= "{VADC/VSYS/VKEY}_2.8V",
		.min_uV		= 2800000,
		.max_uV		= 2800000,
		.apply_uV	= 1,
		.always_on	= 1,
		.state_mem	= {
			.enabled = 1,
		},
	},
};

static struct regulator_init_data smdkc110_buck1_data = {
	.constraints	= {
		.name		= "VCC_ARM",
		.min_uV		= 750000,
		.max_uV		= 1500000,
		.apply_uV	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE |
				  REGULATOR_CHANGE_STATUS,
		.state_mem	= {
			.uV	= 1250000,
			.mode	= REGULATOR_MODE_NORMAL,
			.disabled = 1,
		},
	},
	.num_consumer_supplies	= ARRAY_SIZE(buck1_consumer),
	.consumer_supplies	= buck1_consumer,
};

static struct regulator_init_data smdkc110_buck2_data = {
	.constraints	= {
		.name		= "VCC_INTERNAL",
		.min_uV		= 950000,
		.max_uV		= 1200000,
		.valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE |
				  REGULATOR_CHANGE_STATUS,
		.state_mem	= {
			.uV	= 1100000,
			.mode	= REGULATOR_MODE_NORMAL,
			.disabled = 1,
		},
	},
	.num_consumer_supplies  = ARRAY_SIZE(buck2_consumer),
	.consumer_supplies  = buck2_consumer,
};

static struct regulator_init_data smdkc110_buck3_data = {
	.constraints	= {
		.name		= "VCC_MEM",
		.min_uV		= 1800000,
		.max_uV		= 1800000,
		.always_on	= 1,
		.apply_uV	= 1,
		.state_mem	= {
			.uV	= 1800000,
			.mode	= REGULATOR_MODE_NORMAL,
			.enabled = 1,
		},
	},
};

#if defined(CONFIG_SMDKC110_REV03) || defined(CONFIG_SMDKV210_REV02)
static struct max8998_regulator_data smdkc110_regulators[] = {
	{ MAX8998_LDO2,  &smdkc110_ldo2_data },
	{ MAX8998_LDO3,  &smdkc110_ldo3_data },
	{ MAX8998_LDO4,  &smdkc110_ldo4_data },
	{ MAX8998_LDO5,  &smdkc110_ldo5_data },
	{ MAX8998_LDO6,  &smdkc110_ldo6_data },
	{ MAX8998_LDO7,  &smdkc110_ldo7_data },
	{ MAX8998_LDO8,  &smdkc110_ldo8_data },
	{ MAX8998_LDO9,  &smdkc110_ldo9_data },
	{ MAX8998_BUCK1, &smdkc110_buck1_data },
	{ MAX8998_BUCK2, &smdkc110_buck2_data },
	{ MAX8998_BUCK3, &smdkc110_buck3_data },
};

static struct max8998_platform_data max8998_pdata = {
	.num_regulators	= ARRAY_SIZE(smdkc110_regulators),
	.regulators	= smdkc110_regulators,
	.charger	= NULL,
};
#else
static struct max8698_regulator_data smdkc110_regulators[] = {
	{ MAX8698_LDO2,  &smdkc110_ldo2_data },
	{ MAX8698_LDO3,  &smdkc110_ldo3_data },
	{ MAX8698_LDO4,  &smdkc110_ldo4_data },
	{ MAX8698_LDO5,  &smdkc110_ldo5_data },
	{ MAX8698_LDO6,  &smdkc110_ldo6_data },
	{ MAX8698_LDO7,  &smdkc110_ldo7_data },
	{ MAX8698_LDO8,  &smdkc110_ldo8_data },
	{ MAX8698_LDO9,  &smdkc110_ldo9_data },
	{ MAX8698_BUCK1, &smdkc110_buck1_data },
	{ MAX8698_BUCK2, &smdkc110_buck2_data },
	{ MAX8698_BUCK3, &smdkc110_buck3_data },
};

static struct max8698_platform_data max8698_pdata = {
	.num_regulators = ARRAY_SIZE(smdkc110_regulators),
	.regulators     = smdkc110_regulators,

	/* 1GHz default voltage */
	.dvsarm1        = 0xa,  /* 1.25v */
	.dvsarm2        = 0x9,  /* 1.20V */
	.dvsarm3        = 0x6,  /* 1.05V */
	.dvsarm4        = 0x4,  /* 0.95V */
	.dvsint1        = 0x7,  /* 1.10v */
	.dvsint2        = 0x5,  /* 1.00V */

	.set1       = S5PV210_GPH1(6),
	.set2       = S5PV210_GPH1(7),
	.set3       = S5PV210_GPH0(4),
};
#endif
//=======================================================================================================================
//设置MMC的时钟，进行分频
static void __init smdkc110_setup_clocks(void)
{
	struct clk *pclk;
	struct clk *clk;

#ifdef CONFIG_S3C_DEV_HSMMC
	/* set MMC0 clock */
	clk = clk_get(&s3c_device_hsmmc0.dev, "sclk_mmc");
	pclk = clk_get(NULL, "mout_mpll");
	clk_set_parent(clk, pclk);
	clk_set_rate(clk, 50*MHZ);

	pr_info("%s: %s: source is %s, rate is %ld\n",
				__func__, clk->name, clk->parent->name,
				clk_get_rate(clk));
#endif

#ifdef CONFIG_S3C_DEV_HSMMC1
	/* set MMC1 clock */
	clk = clk_get(&s3c_device_hsmmc1.dev, "sclk_mmc");
	pclk = clk_get(NULL, "mout_mpll");
	clk_set_parent(clk, pclk);
	clk_set_rate(clk, 50*MHZ);

	pr_info("%s: %s: source is %s, rate is %ld\n",
				__func__, clk->name, clk->parent->name,
				clk_get_rate(clk));
#endif

#ifdef CONFIG_S3C_DEV_HSMMC2
	/* set MMC2 clock */
	clk = clk_get(&s3c_device_hsmmc2.dev, "sclk_mmc");
	pclk = clk_get(NULL, "mout_mpll");
	clk_set_parent(clk, pclk);
	clk_set_rate(clk, 50*MHZ);

	pr_info("%s: %s: source is %s, rate is %ld\n",
				__func__, clk->name, clk->parent->name,
				clk_get_rate(clk));
#endif

#ifdef CONFIG_S3C_DEV_HSMMC3
	/* set MMC3 clock */
	clk = clk_get(&s3c_device_hsmmc3.dev, "sclk_mmc");
	pclk = clk_get(NULL, "mout_mpll");
	clk_set_parent(clk, pclk);
	clk_set_rate(clk, 50*MHZ);

	pr_info("%s: %s: source is %s, rate is %ld\n",
				__func__, clk->name, clk->parent->name,
			 clk_get_rate(clk));
#endif
}

//=======================================================================================================================
#if defined(CONFIG_TOUCHSCREEN_S3C)////用于设置触摸屏信息

/* Touch srcreen */
static struct resource s3c_ts_resource[] = {
	[0] = {
		.start = S3C_PA_ADC,
		.end   = S3C_PA_ADC + SZ_4K - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_PENDN,
		.end   = IRQ_PENDN,
		.flags = IORESOURCE_IRQ,
	},
	[2] = {
		.start = IRQ_ADC,
		.end   = IRQ_ADC,
		.flags = IORESOURCE_IRQ,
	}
};

struct platform_device s3c_device_ts = {
	.name		  = "s3c-ts",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(s3c_ts_resource),
	.resource	  = s3c_ts_resource,
};
//=============平台设备相关数据platform_data
static struct s3c_ts_mach_info s3c_ts_platform /* __initdata */ = {
	.delay                  = 10000,//AD转换延时
	.presc                  = 49,//分频
	.oversampling_shift     = 2,// 采样的数据
	.resol_bit              = 12,//转换精度
	.s3c_adc_con            = ADC_TYPE_2,
};
//将TS进行了函数参数（上面结构信息）的一些初始化，
//设置默认值，但是并没有写入硬件寄存器，仅仅是保存在platform_data中
void __init s3c_ts_set_platdata(struct s3c_ts_mach_info *pd)
{
	struct s3c_ts_mach_info *npd;

	npd = kmalloc(sizeof(*npd), GFP_KERNEL);
	if (npd) {
		memcpy(npd, pd, sizeof(*npd));//将pd结构体信息复制到npd内存中
		s3c_device_ts.dev.platform_data = npd;//将pd指针赋值
	} else {
		pr_err("no memory for Touchscreen platform data\n");
	}
}
#endif
//=======================================================================================================================
#if defined(CONFIG_KEYPAD_S3C) || defined(CONFIG_KEYPAD_S3C_MODULE)
#if defined(CONFIG_KEYPAD_S3C_MSM)
void s3c_setup_keypad_cfg_gpio(void)
{
	unsigned int gpio;
	unsigned int end;

	/* gpio setting for KP_COL0 */
	s3c_gpio_cfgpin(S5PV210_GPJ1(5), S3C_GPIO_SFN(3));
	s3c_gpio_setpull(S5PV210_GPJ1(5), S3C_GPIO_PULL_NONE);

	/* gpio setting for KP_COL1 ~ KP_COL7 and KP_ROW0 */
	end = S5PV210_GPJ2(8);
	for (gpio = S5PV210_GPJ2(0); gpio < end; gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}

	/* gpio setting for KP_ROW1 ~ KP_ROW8 */
	end = S5PV210_GPJ3(8);
	for (gpio = S5PV210_GPJ3(0); gpio < end; gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}

	/* gpio setting for KP_ROW9 ~ KP_ROW13 */
	end = S5PV210_GPJ4(5);
	for (gpio = S5PV210_GPJ4(0); gpio < end; gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}
}
#else//被drivers/input/keyboard/s3c-keypad.c调用===========设置相关寄存器
void s3c_setup_keypad_cfg_gpio(int rows, int columns)
{
	unsigned int gpio;
	unsigned int end;

	end = S5PV210_GPH3(rows);

	/* Set all the necessary GPH2 pins to special-function 0 */
	for (gpio = S5PV210_GPH3(0); gpio < end; gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
	}

	end = S5PV210_GPH2(columns);

	/* Set all the necessary GPK pins to special-function 0 */
	for (gpio = S5PV210_GPH2(0); gpio < end; gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(3));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}
}
#endif /* if defined(CONFIG_KEYPAD_S3C_MSM)*/
//EXPORT_SYMBOL(s3c_setup_keypad_cfg_gpio);
#endif
//=======================================================================================================================
#ifdef CONFIG_DM9000//设置相关寄存器
static void __init smdkc110_dm9000_set(void)
{
	unsigned int tmp;

	tmp = ((0<<28)|(0<<24)|(5<<16)|(0<<12)|(0<<8)|(0<<4)|(0<<0));
	__raw_writel(tmp, (S5P_SROM_BW+0x18));

	tmp = __raw_readl(S5P_SROM_BW);
	tmp &= ~(0xf << 20);

	tmp |= (0x1 << 20); /* dm9000 16bit */
	__raw_writel(tmp, S5P_SROM_BW);

	tmp = __raw_readl(S5PV210_MP01CON);
	tmp &= ~(0xf << 20);
	tmp |= (2 << 20);

	__raw_writel(tmp, S5PV210_MP01CON);
}
#endif
//=======================================================================================================================
#ifdef CONFIG_FB_S3C_LTE480WV//三星4.8寸液晶屏LTE480WV

#ifdef LCD_800480
static struct s3cfb_lcd lte480wv = {//三星4.8寸液晶屏LTE480WV
#if 0
	.width = S5PV210_LCD_WIDTH,
	.height = S5PV210_LCD_HEIGHT,
	.bpp = 24,
	.freq = 60,

	.timing = {
		.h_fp = 8,
		.h_bp = 13,
		.h_sw = 3,
		.v_fp = 5,
		.v_fpe = 1,
		.v_bp = 7,
		.v_bpe = 1,
		.v_sw = 1,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 1,
		.inv_vsync = 1,
		.inv_vden = 0,
	},
#else
	.width	= S5PV210_LCD_WIDTH,//屏幕宽度
	.height	= S5PV210_LCD_HEIGHT,//屏幕高度
	//以下一些参数在上面的时序图分析中讲到过,各参数的值请跟据具体的LCD屏数据手册结合上面时序分析来设定
	.bpp	= 24,//色位模式
	.freq	= 60,//像素时钟

	.timing = {//时序相关参数-----------------------------------------
		.h_fp	= 8,//行切换，从同步到绘图之间的延迟
		.h_bp	= 40,//行切换，从绘图到同步之间的延迟
		.h_sw	= 3,//水平同步的长度
		.v_fp	= 5,//帧切换，从同步到绘图之间的延迟
		.v_fpe	= 1,//帧切换，从绘图到同步之间的延迟
		.v_bp	= 22,
		.v_bpe	= 1,
		.v_sw	= 1,//垂直同步的长度
	},

	.polarity = {//极性是否反转-----------------------------------------
		.rise_vclk	= 0,
		.inv_hsync	= 1,
		.inv_vsync	= 1,
		.inv_vden	= 0,
	},
#endif
};
#endif

#ifdef VGA_800600
static struct s3cfb_lcd lte480wv = {//三星4.8寸液晶屏LTE480WV
	.width	= S5PV210_LCD_WIDTH,
	.height	= S5PV210_LCD_HEIGHT,
	.bpp	= 24,
	.freq	= 60,

	.timing = {
		.h_fp	= 5,
		.h_bp	= 452,
		.h_sw	= 10,
		.v_fp	= 2,
		.v_fpe	= 1,
		.v_bp	= 24,
		.v_bpe	= 1,
		.v_sw	= 3,
	},

	.polarity = {
		.rise_vclk	= 1,
		.inv_hsync	= 1,
		.inv_vsync	= 1,
		.inv_vden	= 0,
	},
};
#endif

#ifdef VGA_1024768
static struct s3cfb_lcd lte480wv = {//三星4.8寸液晶屏LTE480WV
	.width	= S5PV210_LCD_WIDTH,
	.height	= S5PV210_LCD_HEIGHT,
	.bpp	= 24,
	.freq	= 60,

	.timing = {
		.h_fp	= 2,
		.h_bp	= 510,
		.h_sw	= 60,
		.v_fp	= 5,
		.v_fpe	= 1,
		.v_bp	= 29,
		.v_bpe	= 1,
                .v_sw	= 3,
	},

	.polarity = {
		.rise_vclk	= 1,
		.inv_hsync	= 1,
		.inv_vsync	= 1,
		.inv_vden	= 0,
	},
};
#endif

static void lte480wv_cfg_gpio(struct platform_device *pdev)
{//三星4.8寸液晶屏LTE480WV
	int i;

	for (i = 0; i < 8; i++) {
		s3c_gpio_cfgpin(S5PV210_GPF0(i), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(S5PV210_GPF0(i), S3C_GPIO_PULL_NONE);
	}

	for (i = 0; i < 8; i++) {
		s3c_gpio_cfgpin(S5PV210_GPF1(i), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(S5PV210_GPF1(i), S3C_GPIO_PULL_NONE);
	}

	for (i = 0; i < 8; i++) {
		s3c_gpio_cfgpin(S5PV210_GPF2(i), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(S5PV210_GPF2(i), S3C_GPIO_PULL_NONE);
	}

	for (i = 0; i < 4; i++) {
		s3c_gpio_cfgpin(S5PV210_GPF3(i), S3C_GPIO_SFN(2));
		s3c_gpio_setpull(S5PV210_GPF3(i), S3C_GPIO_PULL_NONE);
	}

	/* mDNIe SEL: why we shall write 0x2 ? */
	writel(0x2, S5P_MDNIE_SEL);

	/* drive strength to max */
	writel(0xffffffff, S5PV210_GPF0_BASE + 0xc);
	writel(0xffffffff, S5PV210_GPF1_BASE + 0xc);
	writel(0xffffffff, S5PV210_GPF2_BASE + 0xc);
	writel(0x000000ff, S5PV210_GPF3_BASE + 0xc);
}

#define S5PV210_GPD_0_0_TOUT_0  (0x2)
#define S5PV210_GPD_0_1_TOUT_1  (0x2 << 4)
#define S5PV210_GPD_0_2_TOUT_2  (0x2 << 8)
#define S5PV210_GPD_0_3_TOUT_3  (0x2 << 12)
static int lte480wv_backlight_on(struct platform_device *pdev)
{//三星4.8寸液晶屏LTE480WV
	int err;

	err = gpio_request(S5PV210_GPD0(3), "GPD0");

	if (err) {
		printk(KERN_ERR "failed to request GPD0 for "
			"lcd backlight control\n");
		return err;
	}

	gpio_direction_output(S5PV210_GPD0(3), 1);

	s3c_gpio_cfgpin(S5PV210_GPD0(3), S5PV210_GPD_0_3_TOUT_3);

	gpio_free(S5PV210_GPD0(3));
	return 0;
}

static int lte480wv_backlight_off(struct platform_device *pdev, int onoff)
{//三星4.8寸液晶屏LTE480WV
	int err;

	err = gpio_request(S5PV210_GPD0(3), "GPD0");

	if (err) {
		printk(KERN_ERR "failed to request GPD0 for "
				"lcd backlight control\n");
		return err;
	}

	gpio_direction_output(S5PV210_GPD0(3), 0);
	gpio_free(S5PV210_GPD0(3));
	return 0;
}

static int lte480wv_reset_lcd(struct platform_device *pdev)
{//三星4.8寸液晶屏LTE480WV
	int err;

	err = gpio_request(S5PV210_GPH0(6), "GPH0");
	if (err) {
		printk(KERN_ERR "failed to request GPH0 for "
				"lcd reset control\n");
		return err;
	}

	gpio_direction_output(S5PV210_GPH0(6), 1);
	mdelay(100);

	gpio_set_value(S5PV210_GPH0(6), 0);
	mdelay(10);

	gpio_set_value(S5PV210_GPH0(6), 1);
	mdelay(10);

	gpio_free(S5PV210_GPH0(6));

	return 0;
}
//三星4.8寸液晶屏LTE480WV============平台设备相关数据platform_data
static struct s3c_platform_fb lte480wv_fb_data /* __initdata */ = {
	.hw_ver	= 0x62,
	.nr_wins = 5,
	.default_win = CONFIG_FB_S3C_DEFAULT_WINDOW,
	.swap = FB_SWAP_WORD | FB_SWAP_HWORD,

	.lcd = &lte480wv,
	.cfg_gpio	= lte480wv_cfg_gpio,
	.backlight_on	= lte480wv_backlight_on,
	.backlight_onoff    = lte480wv_backlight_off,
	.reset_lcd	= lte480wv_reset_lcd,
};
#endif
//=======================================================================================================================
#ifdef CONFIG_S3C64XX_DEV_SPI

#define SMDK_MMCSPI_CS 0
static struct s3c64xx_spi_csinfo smdk_spi0_csi[] = {
	[SMDK_MMCSPI_CS] = {
		.line = S5PV210_GPB(1),
		.set_level = gpio_set_value,
		.fb_delay = 0x0,
	},
};

static struct s3c64xx_spi_csinfo smdk_spi1_csi[] = {
	[SMDK_MMCSPI_CS] = {
		.line = S5PV210_GPB(5),
		.set_level = gpio_set_value,
		.fb_delay = 0x0,
	},
};
/*这边定义了2个SPI控制器的Platform device，id分别为“0，1”，
name都为“spidev”，变量resource中定义了适配器的寄存器基地址。*/
static struct spi_board_info s3c_spi_devs[] /* __initdata */ = {
	[0] = {
		.modalias        = "spidev",	 /* device node name *///对应spidev.c中的"spidev",并调用probe函数进行匹配
		.mode            = SPI_MODE_0,	/* 此处选择具体数据传输模式CPOL=0, CPHA=0 */
		.max_speed_hz    = 10000000,//默认//最大的spi时钟频率
		/* Connected to SPI-0 as 1st Slave */
		.bus_num         = 0,//设备连接在spi控制器0上
		.irq             = IRQ_SPI0,
		.chip_select     = 0,//片选线号，在S5PC100的控制器驱动中没有使用它作为片选的依据，而是选择了下文controller_data里的方法
		.controller_data = &smdk_spi0_csi[SMDK_MMCSPI_CS],
	},
	[1] = {
		.modalias        = "spidev",	/* device node name */
		.mode            = SPI_MODE_0,	/* CPOL=0, CPHA=0 */
		.max_speed_hz    = 10000000,
		/* Connected to SPI-1 as 1st Slave */
		.bus_num         = 1,
		.irq             = IRQ_SPI1,
		.chip_select     = 0,
		.controller_data = &smdk_spi1_csi[SMDK_MMCSPI_CS],
	},
};
#endif
//=======================================================================================================================
#ifdef CONFIG_HAVE_PWM
struct s3c_pwm_data {
	/* PWM output port */
	unsigned int gpio_no;
	const char  *gpio_name;
	unsigned int gpio_set_value;
};

struct s3c_pwm_data pwm_data[] = {
	{
		.gpio_no    = S5PV210_GPD0(0),
		.gpio_name  = "GPD",
		.gpio_set_value = S5PV210_GPD_0_0_TOUT_0,
	}, {
		.gpio_no    = S5PV210_GPD0(1),
		.gpio_name  = "GPD",
		.gpio_set_value = S5PV210_GPD_0_1_TOUT_1,
	}, {
		.gpio_no    = S5PV210_GPD0(2),
		.gpio_name      = "GPD",
		.gpio_set_value = S5PV210_GPD_0_2_TOUT_2,
	}, {
		.gpio_no    = S5PV210_GPD0(3),
		.gpio_name      = "GPD",
		.gpio_set_value = S5PV210_GPD_0_3_TOUT_3,
	}
};
#endif

#if defined(CONFIG_BACKLIGHT_PWM)
static struct platform_pwm_backlight_data smdk_backlight_data = {
	.pwm_id  = 3,
	.max_brightness = 255,
	.dft_brightness = 255,
	.pwm_period_ns  = 25000,
};

static struct platform_device smdk_backlight_device = {
	.name      = "pwm-backlight",
	.id        = -1,
	.dev        = {
		.parent = &s3c_device_timer[3].dev,
		.platform_data = &smdk_backlight_data,
	},
};

static void __init smdk_backlight_register(void)
{
	int ret;
#ifdef CONFIG_HAVE_PWM
	int i, ntimer;

	/* Timer GPIO Set */
	ntimer = ARRAY_SIZE(pwm_data);
	for (i = 0; i < ntimer; i++) {
		if (gpio_is_valid(pwm_data[i].gpio_no)) {
			ret = gpio_request(pwm_data[i].gpio_no,
				pwm_data[i].gpio_name);
			if (ret) {
				printk(KERN_ERR "failed to get GPIO for PWM\n");
				return;
			}
			s3c_gpio_cfgpin(pwm_data[i].gpio_no,
				pwm_data[i].gpio_set_value);

			gpio_free(pwm_data[i].gpio_no);
		}
	}
#endif
	ret = platform_device_register(&smdk_backlight_device);
	if (ret)
		printk(KERN_ERR "smdk: failed to register backlight device: %d\n", ret);
}
#endif
//=======================================================================================================================
#ifdef CONFIG_S5P_ADC//平台设备相关数据platform_data
static struct s3c_adc_mach_info s3c_adc_platform /* __initdata */ = {
	/* s5pc110 support 12-bit resolution */
	.delay  = 10000,
	.presc  = 49,
	.resolution = 12,
};
#endif
//=======================================================================================================================
/*
 * External camera reset
 * Because the most of cameras take i2c bus signal, so that
 * you have to reset at the boot time for other i2c slave devices.
 * This function also called at fimc_init_camera()
 * Do optimization for cameras on your platform.
*/
#ifdef CAM_ITU_CH_A
static int smdkv210_cam0_power(int onoff)
{
	int err;
	/* Camera A */
	err = gpio_request(GPIO_PS_VOUT, "GPH0");
	if (err)
		printk(KERN_ERR "failed to request GPH0 for CAM_2V8\n");

	s3c_gpio_setpull(GPIO_PS_VOUT, S3C_GPIO_PULL_NONE);
	gpio_direction_output(GPIO_PS_VOUT, 0);
	gpio_direction_output(GPIO_PS_VOUT, 1);
	gpio_free(GPIO_PS_VOUT);

	return 0;
}
#else
static int smdkv210_cam1_power(int onoff)
{
	int err;

	/* S/W workaround for the SMDK_CAM4_type board
	 * When SMDK_CAM4 type module is initialized at power reset,
	 * it needs the cam_mclk.
	 *
	 * Now cam_mclk is set as below, need only set the gpio mux.
	 * CAM_SRC1 = 0x0006000, CLK_DIV1 = 0x00070400.
	 * cam_mclk source is SCLKMPLL, and divider value is 8.
	*/

	/* gpio mux select the cam_mclk */
	err = gpio_request(GPIO_PS_ON, "GPJ1");
	if (err)
		printk(KERN_ERR "failed to request GPJ1 for CAM_2V8\n");

	s3c_gpio_setpull(GPIO_PS_ON, S3C_GPIO_PULL_NONE);
	s3c_gpio_cfgpin(GPIO_PS_ON, (0x3<<16));


	/* Camera B */
	err = gpio_request(GPIO_BUCK_1_EN_A, "GPH0");
	if (err)
		printk(KERN_ERR "failed to request GPH0 for CAM_2V8\n");

	s3c_gpio_setpull(GPIO_BUCK_1_EN_A, S3C_GPIO_PULL_NONE);
	gpio_direction_output(GPIO_BUCK_1_EN_A, 0);
	gpio_direction_output(GPIO_BUCK_1_EN_A, 1);

	udelay(1000);

	gpio_free(GPIO_PS_ON);
	gpio_free(GPIO_BUCK_1_EN_A);

	return 0;
}
#endif
static int s5k5ba_power_en(int onoff)
{
	if (onoff) {
#ifdef CAM_ITU_CH_A
		smdkv210_cam0_power(onoff);
#else
		smdkv210_cam1_power(onoff);
#endif
	} else {
#ifdef CAM_ITU_CH_A
		smdkv210_cam0_power(onoff);
#else
		smdkv210_cam1_power(onoff);
#endif
	}

	return 0;
}

#ifdef CONFIG_VIDEO_S5K4EA
/* Set for MIPI-CSI Camera module Power Enable */
static int smdkv210_mipi_cam_pwr_en(int enabled)
{
	int err;

	err = gpio_request(S5PV210_GPH1(2), "GPH1");
	if (err)
		printk(KERN_ERR "#### failed to request(GPH1)for CAM_2V8\n");

	s3c_gpio_setpull(S5PV210_GPH1(2), S3C_GPIO_PULL_NONE);
	gpio_direction_output(S5PV210_GPH1(2), enabled);
	gpio_free(S5PV210_GPH1(2));

	return 0;
}

/* Set for MIPI-CSI Camera module Reset */
static int smdkv210_mipi_cam_rstn(int enabled)
{
	int err;

	err = gpio_request(S5PV210_GPH0(3), "GPH0");
	if (err)
		printk(KERN_ERR "#### failed to reset(GPH0) for MIPI CAM\n");

	s3c_gpio_setpull(S5PV210_GPH0(3), S3C_GPIO_PULL_NONE);
	gpio_direction_output(S5PV210_GPH0(3), enabled);
	gpio_free(S5PV210_GPH0(3));

	return 0;
}

/* MIPI-CSI Camera module Power up/down sequence */
static int smdkv210_mipi_cam_power(int on)
{
	if (on) {
		smdkv210_mipi_cam_pwr_en(1);
		mdelay(5);
		smdkv210_mipi_cam_rstn(1);
	} else {
		smdkv210_mipi_cam_rstn(0);
		mdelay(5);
		smdkv210_mipi_cam_pwr_en(0);
	}
	return 0;
}
#endif

#ifdef CONFIG_VIDEO_S5K4BA
static struct s5k4ba_platform_data s5k4ba_plat = {
	.default_width = 1600,
	.default_height = 1200,
	.pixelformat = V4L2_PIX_FMT_UYVY,
	.freq = 44000000,
	.is_mipi = 0,
};

static struct i2c_board_info  s5k4ba_i2c_info = {
	I2C_BOARD_INFO("S5K4BA", 0x2d),
	.platform_data = &s5k4ba_plat,
};

static struct s3c_platform_camera s5k4ba = {
	#ifdef CAM_ITU_CH_A
	.id		= CAMERA_PAR_A,
	#else
	.id		= CAMERA_PAR_B,
	#endif
	.type		= CAM_TYPE_ITU,
	.fmt		= ITU_601_YCBCR422_8BIT,
	.order422	= CAM_ORDER422_8BIT_YCRYCB,
	.i2c_busnum	= 0,
	.info		= &s5k4ba_i2c_info,
	.pixelformat	= V4L2_PIX_FMT_UYVY,
	.srclk_name	= "mout_mpll",
	/* .srclk_name	= "xusbxti", */
	.clk_name	= "sclk_cam1",
	.clk_rate	= 44000000,
	.line_length	= 1920,
	.width		= 1600,
	.height		= 1200,
	.window		= {
		.left	= 0,
		.top	= 0,
		.width	= 1600,
		.height	= 1200,
	},

	/* Polarity */
	.inv_pclk	= 0,
	.inv_vsync	= 1,
	.inv_href	= 0,
	.inv_hsync	= 0,

	.initialized	= 0,
	.cam_power	= s5k5ba_power_en,
};
#endif

/* 2 MIPI Cameras */
#ifdef CONFIG_VIDEO_S5K4EA
static struct s5k4ea_platform_data s5k4ea_plat = {
	.default_width = 1920,
	.default_height = 1080,
	.pixelformat = V4L2_PIX_FMT_UYVY,
	.freq = 24000000,
	.is_mipi = 1,
};

static struct i2c_board_info  s5k4ea_i2c_info = {
	I2C_BOARD_INFO("S5K4EA", 0x2d),
	.platform_data = &s5k4ea_plat,
};

static struct s3c_platform_camera s5k4ea = {
	.id		= CAMERA_CSI_C,
	.type		= CAM_TYPE_MIPI,
	.fmt		= MIPI_CSI_YCBCR422_8BIT,
	.order422	= CAM_ORDER422_8BIT_CBYCRY,
	.i2c_busnum	= 0,
	.info		= &s5k4ea_i2c_info,
	.pixelformat	= V4L2_PIX_FMT_UYVY,
	.srclk_name	= "mout_mpll",
	.clk_name	= "sclk_cam0",
	/* .clk_name	= "sclk_cam1", */
	.clk_rate	= 48000000,
	.line_length	= 1920,
	.width		= 1920,
	.height		= 1080,
	.window		= {
		.left	= 0,
		.top	= 0,
		.width	= 1920,
		.height	= 1080,
	},

	.mipi_lanes	= 2,
	.mipi_settle	= 12,
	.mipi_align	= 32,

	/* Polarity */
	.inv_pclk	= 0,
	.inv_vsync	= 1,
	.inv_href	= 0,
	.inv_hsync	= 0,

	.initialized	= 0,
	.cam_power	= smdkv210_mipi_cam_power,
};
#endif

/* Interface setting 平台设备相关数据platform_data*/
static struct s3c_platform_fimc fimc_plat_lsi = {
	.srclk_name	= "mout_mpll",
	.clk_name	= "sclk_fimc",
	.lclk_name	= "sclk_fimc_lclk",
	.clk_rate	= 166750000,
#if defined(CONFIG_VIDEO_S5K4EA)
	.default_cam	= CAMERA_CSI_C,
#else
#ifdef CAM_ITU_CH_A
	.default_cam	= CAMERA_PAR_A,
#else
	.default_cam	= CAMERA_PAR_B,
#endif
#endif
	.camera		= {
#ifdef CONFIG_VIDEO_S5K4ECGX
			&s5k4ecgx,
#endif
#ifdef CONFIG_VIDEO_S5KA3DFX
			&s5ka3dfx,
#endif
#ifdef CONFIG_VIDEO_S5K4BA
			&s5k4ba,
#endif
#ifdef CONFIG_VIDEO_S5K4EA
			&s5k4ea,
#endif
	},
	.hw_ver		= 0x43,
};
//=======================================================================================================================
#ifdef CONFIG_VIDEO_JPEG_V2//平台设备相关数据platform_data
static struct s3c_platform_jpeg jpeg_plat /* __initdata */ = {
	.max_main_width	        = 1600,
	.max_main_height	= 1200,
	.max_thumb_width	= 320,
	.max_thumb_height	= 240,
};
#endif
//=======================================================================================================================
//描述了板载的所有I2C设备信息
/* I2C0 */
static struct i2c_board_info i2c_devs0[] /* __initdata */ = {
#ifdef CONFIG_SND_SOC_WM8580
	{
		I2C_BOARD_INFO("wm8580", 0x1b),
	},
#endif
};

/* I2C1 */
static struct i2c_board_info i2c_devs1[] /* __initdata */ = {
#ifdef CONFIG_VIDEO_TV20
	{
		I2C_BOARD_INFO("s5p_ddc", (0x74>>1)),
	},
#endif
};

/* I2C2 */
static struct i2c_board_info i2c_devs2[] /* __initdata */ = {
	{
#if defined(CONFIG_SMDKC110_REV03) || defined(CONFIG_SMDKV210_REV02)
		/* The address is 0xCC used since SRAD = 0 */
		I2C_BOARD_INFO("max8998", (0xCC >> 1)),
		.platform_data = &max8998_pdata,//电池测量平台数据
#else
		/* The address is 0xCC used since SRAD = 0 */
		I2C_BOARD_INFO("max8698", (0xCC >> 1)),
		.platform_data = &max8698_pdata,
#endif
	},
};
//=======================================================================================================================
#define S5PV210_PS_HOLD_CONTROL_REG (S3C_VA_SYS+0xE81C)
static void smdkc110_power_off(void)
{
	/* PS_HOLD output High --> Low */
	writel(readl(S5PV210_PS_HOLD_CONTROL_REG) & 0xFFFFFEFF,
			S5PV210_PS_HOLD_CONTROL_REG);

	while (1);
}
//=======================================================================================================================
#ifdef CONFIG_BATTERY_S3C
struct platform_device sec_device_battery = {
	.name   = "sec-fake-battery",
	.id = -1,
};
#endif
//=======================================================================================================================
#ifdef CONFIG_ANDROID_PMEM
static struct android_pmem_platform_data pmem_gpu1_pdata = {
	.name = "pmem_gpu1",
	.no_allocator = 1,
	.cached = 1,
	.buffered = 1,
	.start = 0,
	.size = 0,
};

static struct platform_device pmem_gpu1_device = {
	.name = "android_pmem",
	.id = 1,
	.dev = { .platform_data = &pmem_gpu1_pdata },
};
static void __init android_pmem_set_platdata(void)
{
	pmem_gpu1_pdata.start =
		(u32)s5p_get_media_memory_bank(S5P_MDEV_PMEM_GPU1, 0);
	pmem_gpu1_pdata.size =
		(u32)s5p_get_media_memsize_bank(S5P_MDEV_PMEM_GPU1, 0);
}
#endif
//=======================================================================================================================

//初始化的平台设备
/*内核启动后，首先构造链表将描述设备的platform_device构造组织起来，
得到一个设备的列表；当加载某个驱动程序的platform_driver结构时，
使用一些匹配函数来检查驱动程序能否支持这些设备，常用的检查方法很简单：比较驱动程序和设备的名称。
*/
static struct platform_device *smdkc110_devices[] /* __initdata */ = {
								// name  |  platform_driver  |   dev_driver
#ifdef CONFIG_FIQ_DEBUGGER
	&s5pv210_device_fiqdbg_uart2,
#endif
#ifdef CONFIG_MTD_ONENAND
	&s5pc110_device_onenand,//"s5pc110-onenand" | drivers\mtd\onenand\Samsung.c | drivers/mtd/mtdchar.c  drivers/mtd/mtdblock.c
#endif
#ifdef CONFIG_MTD_NAND
	&s3c_device_nand,//"s5pv210-nand "  |  rivers/mtd/nand/s3c_nand.c  | drivers/mtd/mtdchar.c  drivers/mtd/mtdblock.c
#endif
	&s5p_device_rtc,//"s3c64xx-rtc"  |  drivers/rtc/rtc-s3c.c  |  Rtc-dev.c (drivers\rtc)
#ifdef CONFIG_SND_S3C64XX_SOC_I2S_V4
	&s5pv210_device_iis0,//"s3c64xx-iis" |  S3c64xx-i2s.c (sound\soc\s3c24xx)  | 
#endif
#ifdef CONFIG_SND_S3C_SOC_AC97
	&s5pv210_device_ac97,//"s3c-ac97"  |  S3c-ac97.c (sound\soc\s3c24xx)  | 
#endif
#ifdef CONFIG_SND_S3C_SOC_PCM
	&s5pv210_device_pcm0,//"samsung-pcm" | S3c-pcm.c (sound\soc\s3c24xx) | 
#endif
#ifdef CONFIG_SND_SOC_SPDIF
	&s5pv210_device_spdif,
#endif
	&s3c_device_wdt,

#ifdef CONFIG_FB_S3C
	&s3c_device_fb,//LCD 的FB设备:"s3cfb"| drivers/video/samsung/s3cfb.c | drivers/video/fbmem.c
#endif
#ifdef CONFIG_DM9000
	&s5p_device_dm9000,//"dm9000" | Dm9000.c (drivers\net) | 
#endif

#ifdef CONFIG_VIDEO_MFC50
	&s3c_device_mfc,
#endif
#ifdef CONFIG_TOUCHSCREEN_S3C
	&s3c_device_ts,//"s3c-ts"  |  Ts-s3c.c (drivers\input\touchscreen)  | 
#endif
	&s3c_device_keypad,//"s3c-keypad" | S3c-keypad.c (drivers\input\keyboard) |
#ifdef CONFIG_S5P_ADC
	&s3c_device_adc,//"s3c-adc" | Adc.c (arch\arm\mach-s5pv210)  |  
#endif
#ifdef CONFIG_VIDEO_FIMC//Fully Interactive Mobile Camera （完全交互式移动摄像机）
	&s3c_device_fimc0,
	&s3c_device_fimc1,
	&s3c_device_fimc2,
#endif
#ifdef CONFIG_VIDEO_FIMC_MIPI
	&s3c_device_csis,//"s3c-csis"  |  Csis.c (drivers\media\video\samsung\fimc) | 
#endif
#ifdef CONFIG_VIDEO_JPEG_V2
	&s3c_device_jpeg,
#endif
#ifdef CONFIG_VIDEO_G2D
	&s3c_device_g2d,
#endif
#ifdef CONFIG_VIDEO_TV20
	&s5p_device_tvout,
	&s5p_device_cec,
	&s5p_device_hpd,
#endif

	&s3c_device_g3d,
	&s3c_device_lcd,

	&s3c_device_i2c0,//"s3c2410-i2c"  | I2c-s3c2410.c (drivers\i2c\busses)  |  I2c-dev.c (drivers\i2c)
#ifdef CONFIG_S3C_DEV_I2C1
	&s3c_device_i2c1,//"s3c2410-i2c"  | I2c-s3c2410.c (drivers\i2c\busses)  |  I2c-dev.c (drivers\i2c)
#endif
#ifdef CONFIG_S3C_DEV_I2C2
	&s3c_device_i2c2,//"s3c2410-i2c"  | I2c-s3c2410.c (drivers\i2c\busses)  |  I2c-dev.c (drivers\i2c)
#endif

#ifdef CONFIG_USB_EHCI_HCD
	&s3c_device_usb_ehci,
#endif
#ifdef CONFIG_USB_OHCI_HCD
	&s3c_device_usb_ohci,
#endif

#ifdef CONFIG_USB_GADGET
	&s3c_device_usbgadget,//"s3c-usbgadget"  |  S3c_udc_otg.c (drivers\usb\gadget)  | 
#endif
#ifdef CONFIG_USB_ANDROID
	&s3c_device_android_usb, //"android_usb" | Android.c (drivers\usb\gadget)  | 
#ifdef CONFIG_USB_ANDROID_MASS_STORAGE
	&s3c_device_usb_mass_storage,//"usb_mass_storage"  |  F_mass_storage.c (drivers\usb\gadget) | 
#endif
#ifdef CONFIG_USB_ANDROID_RNDIS
	&s3c_device_rndis,//"rndis"  |  F_rndis.c (drivers\usb\gadget)  | 
#endif
#endif
#ifdef CONFIG_BATTERY_S3C
	&sec_device_battery,//"sec-fake-battery"  |  S3c_fake_battery.c (drivers\power)	|  
#endif
#ifdef CONFIG_S3C_DEV_HSMMC
	&s3c_device_hsmmc0,//"s3c-sdhci"  | Sdhci-s3c.c (drivers\mmc\host)  | 
#endif
#ifdef CONFIG_S3C_DEV_HSMMC1
	&s3c_device_hsmmc1,
#endif
#ifdef CONFIG_S3C_DEV_HSMMC2
	&s3c_device_hsmmc2,
#endif
#ifdef CONFIG_S3C_DEV_HSMMC3
	&s3c_device_hsmmc3,
#endif

#ifdef CONFIG_S3C64XX_DEV_SPI
	&s5pv210_device_spi0,//"s3c64xx-spi"  | Spi_s3c64xx.c (drivers\spi)  |  /driver/spi/spidev.c
	&s5pv210_device_spi1,
#endif
#ifdef CONFIG_S5PV210_POWER_DOMAIN//===========需要电源管理单元
	&s5pv210_pd_audio,
	&s5pv210_pd_cam,
	&s5pv210_pd_tv,
	&s5pv210_pd_lcd,//LCD的电源设备
	&s5pv210_pd_g3d,
	&s5pv210_pd_mfc,
#endif

#ifdef CONFIG_HAVE_PWM
	&s3c_device_timer[0],
	&s3c_device_timer[1],
	&s3c_device_timer[2],
	&s3c_device_timer[3],
#endif
};
//=============================================================
static void __init smdkc110_map_io(void)
{
	//主要是做外围设备的物理地址到虚拟地址的映射
	s5p_init_io(NULL, 0, S5P_VA_CHIPID);//调用linux/arch/arm/plat-s3c64xx/cpu.c中函数
	//频率的初始化
	s3c24xx_init_clocks(24000000);	
	s5pv210_gpiolib_init();
	//串口的初始化：四个串口都默认设置了
	s3c24xx_init_uarts(smdkc110_uartcfgs, ARRAY_SIZE(smdkc110_uartcfgs));
	s5p_reserve_bootmem(smdkc110_media_devs, ARRAY_SIZE(smdkc110_media_devs));
#ifdef CONFIG_MTD_ONENAND
	s5pc110_device_onenand.name = "s5pc110-onenand";
#endif
#ifdef CONFIG_MTD_NAND
	s3c_device_nand.name = "s5pv210-nand";
#endif
	s5p_device_rtc.name = "smdkc110-rtc";
}

unsigned int pm_debug_scratchpad;

static void __init sound_init(void)
{
	u32 reg;

	reg = __raw_readl(S5P_CLK_OUT);
	reg &= ~(0x1f << 12);
	reg &= ~(0xf << 20);
	reg |= 0x12 << 12;
	reg |= 0x1  << 20;
	__raw_writel(reg, S5P_CLK_OUT);

	reg = __raw_readl(S5P_OTHERS);
	reg &= ~(0x3 << 8);
	reg |= 0x0 << 8;
	__raw_writel(reg, S5P_OTHERS);
}

#ifdef CONFIG_VIDEO_TV20
static void s3c_set_qos(void)
{
	/* VP QoS */
	__raw_writel(0x00400001, S5P_VA_DMC0 + 0xC8);
	__raw_writel(0x387F0022, S5P_VA_DMC0 + 0xCC);
	/* MIXER QoS */
	__raw_writel(0x00400001, S5P_VA_DMC0 + 0xD0);
	__raw_writel(0x3FFF0062, S5P_VA_DMC0 + 0xD4);
	/* LCD1 QoS */
	__raw_writel(0x00800001, S5P_VA_DMC1 + 0x90);
	__raw_writel(0x3FFF005B, S5P_VA_DMC1 + 0x94);
	/* LCD2 QoS */
	__raw_writel(0x00800001, S5P_VA_DMC1 + 0x98);
	__raw_writel(0x3FFF015B, S5P_VA_DMC1 + 0x9C);
	/* VP QoS */
	__raw_writel(0x00400001, S5P_VA_DMC1 + 0xC8);
	__raw_writel(0x387F002B, S5P_VA_DMC1 + 0xCC);
	/* DRAM Controller QoS */
	__raw_writel(((__raw_readl(S5P_VA_DMC0)&~(0xFFF<<16))|(0x100<<16)),
			S5P_VA_DMC0 + 0x0);
	__raw_writel(((__raw_readl(S5P_VA_DMC1)&~(0xFFF<<16))|(0x100<<16)),
			S5P_VA_DMC1 + 0x0);
	/* BUS QoS AXI_DSYS Control */
	__raw_writel(0x00000007, S5P_VA_BUS_AXI_DSYS + 0x400);
	__raw_writel(0x00000007, S5P_VA_BUS_AXI_DSYS + 0x420);
	__raw_writel(0x00000030, S5P_VA_BUS_AXI_DSYS + 0x404);
	__raw_writel(0x00000030, S5P_VA_BUS_AXI_DSYS + 0x424);
}
#endif

static bool console_flushed;

static void flush_console(void)
{
	if (console_flushed)
		return;

	console_flushed = true;

	printk("\n");
	pr_emerg("Restarting %s\n", linux_banner);
	if (!try_acquire_console_sem()) {
		release_console_sem();
		return;
	}

	mdelay(50);

	local_irq_disable();
	if (try_acquire_console_sem())
		pr_emerg("flush_console: console was locked! busting!\n");
	else
		pr_emerg("flush_console: console was locked!\n");
	release_console_sem();
}

static void smdkc110_pm_restart(char mode, const char *cmd)
{
	flush_console();
	arm_machine_restart(mode, cmd);
}

static void __init smdkc110_machine_init(void)
{
	arm_pm_restart = smdkc110_pm_restart;

	s3c_usb_set_serial();
	//注册smdk6410特有的设备
	platform_add_devices(smdkc110_devices, ARRAY_SIZE(smdkc110_devices));
#ifdef CONFIG_ANDROID_PMEM//选择性注册此平台设备
	platform_device_register(&pmem_gpu1_device);
#endif
	pm_power_off = smdkc110_power_off ;

#ifdef CONFIG_ANDROID_PMEM
	android_pmem_set_platdata();//类似s3c_ts_set_platdata,设置平台设备相关数据
#endif
	/* i2c */
	//将S3C2440上的I2C控制器进行了一些初始化，
	//设置默认值，但是并没有写入硬件寄存器�
	//仅仅是保存在s3c2410_platform_i2c结构体
	s3c_i2c0_set_platdata(NULL);
	s3c_i2c1_set_platdata(NULL);//类似s3c_ts_set_platdata,设置平台设备相关数据
	s3c_i2c2_set_platdata(NULL);

	sound_init();
	
	//这个函数注册static struct i2c_board_info结构，此结构是代替I2C设备的板级注册
	i2c_register_board_info(0, i2c_devs0, ARRAY_SIZE(i2c_devs0));
	i2c_register_board_info(1, i2c_devs1, ARRAY_SIZE(i2c_devs1));
	i2c_register_board_info(2, i2c_devs2, ARRAY_SIZE(i2c_devs2));

#ifdef CONFIG_DM9000
	smdkc110_dm9000_set();
#endif
//=====================================LCD所有信息就是一个指针赋值给device->platform_data,不管信息有多少
#ifdef CONFIG_FB_S3C_LTE480WV
	s3cfb_set_platdata(&lte480wv_fb_data);//类似s3c_ts_set_platdata,设置平台设备相关数据
#endif

	/* spi */
#ifdef CONFIG_S3C64XX_DEV_SPI
	if (!gpio_request(S5PV210_GPB(1), "SPI_CS0")) {
		gpio_direction_output(S5PV210_GPB(1), 1);
		s3c_gpio_cfgpin(S5PV210_GPB(1), S3C_GPIO_SFN(1));
		s3c_gpio_setpull(S5PV210_GPB(1), S3C_GPIO_PULL_UP);
		s5pv210_spi_set_info(0, S5PV210_SPI_SRCCLK_PCLK,
			ARRAY_SIZE(smdk_spi0_csi));
	}
	if (!gpio_request(S5PV210_GPB(5), "SPI_CS1")) {
		gpio_direction_output(S5PV210_GPB(5), 1);
		s3c_gpio_cfgpin(S5PV210_GPB(5), S3C_GPIO_SFN(1));
		s3c_gpio_setpull(S5PV210_GPB(5), S3C_GPIO_PULL_UP);
		s5pv210_spi_set_info(1, S5PV210_SPI_SRCCLK_PCLK,
			ARRAY_SIZE(smdk_spi1_csi));
	}
	/*将spi Platform device注册到Platform总线上，完成注册后，寄存器的基地址等
	信息会在设备树中描述了，此后只需利用platform_get_resource等标准接口自
	动获取即可，实现了驱动和资源的分离。把spi_board_info注册要链表board_list上。*/
	spi_register_board_info(s3c_spi_devs, ARRAY_SIZE(s3c_spi_devs));
#endif

#if defined(CONFIG_TOUCHSCREEN_S3C)
	//将TS进行了函数参数的一些初始化，
	//设置默认值，但是并没有写入硬件寄存器，仅仅是保存在platform_data中
	s3c_ts_set_platdata(&s3c_ts_platform);//函数和参数在一起，容易理解
#endif

#if defined(CONFIG_S5P_ADC)
	s3c_adc_set_platdata(&s3c_adc_platform);//类似s3c_ts_set_platdata,设置平台设备相关数据
#endif

#if defined(CONFIG_PM)
	s3c_pm_init();
#endif

#ifdef CONFIG_VIDEO_FIMC
	/* fimc :Fully Interactive Mobile Camera （FIMC完全交互式移动摄像机）*/
	s3c_fimc0_set_platdata(&fimc_plat_lsi);//类似s3c_ts_set_platdata,设置平台设备相关数据
	s3c_fimc1_set_platdata(&fimc_plat_lsi);
	s3c_fimc2_set_platdata(&fimc_plat_lsi);
	/* external camera */
	/* smdkv210_cam0_power(1); */
	/* smdkv210_cam1_power(1); */
#endif

#ifdef CONFIG_VIDEO_FIMC_MIPI
	s3c_csis_set_platdata(NULL);//类似s3c_ts_set_platdata,设置平台设备相关数据
#endif

#ifdef CONFIG_VIDEO_JPEG_V2
	s3c_jpeg_set_platdata(&jpeg_plat);//类似s3c_ts_set_platdata,设置平台设备相关数据
#endif

#ifdef CONFIG_VIDEO_MFC50
	/* mfc */
	s3c_mfc_set_platdata(NULL);//类似s3c_ts_set_platdata,设置平台设备相关数据
#endif

#ifdef CONFIG_VIDEO_TV20
	s3c_set_qos();
#endif

#ifdef CONFIG_S3C_DEV_HSMMC
	s5pv210_default_sdhci0();//类似s3c_ts_set_platdata,设置方式不同,同样设置平台设备相关数据
#endif
#ifdef CONFIG_S3C_DEV_HSMMC1
	s5pv210_default_sdhci1();//类似s3c_ts_set_platdata,设置方式不同,同样设置平台设备相关数据
#endif
#ifdef CONFIG_S3C_DEV_HSMMC2
	s5pv210_default_sdhci2();//类似s3c_ts_set_platdata,设置方式不同,同样设置平台设备相关数据
#endif
#ifdef CONFIG_S3C_DEV_HSMMC3
	s5pv210_default_sdhci3();//类似s3c_ts_set_platdata,设置方式不同,同样设置平台设备相关数据
#endif
#ifdef CONFIG_S5PV210_SETUP_SDHCI
	s3c_sdhci_set_platdata();//类似s3c_ts_set_platdata,设置平台设备相关数据
#endif

#ifdef CONFIG_BACKLIGHT_PWM
	smdk_backlight_register();//设置smdk_backlight_device平台设备
#endif

	regulator_has_full_constraints();

	smdkc110_setup_clocks();
}

#ifdef CONFIG_USB_SUPPORT
/* Initializes OTG Phy. */
void otg_phy_init(void)
{
	/* USB PHY0 Enable */
	writel(readl(S5P_USB_PHY_CONTROL) | (0x1<<0),
			S5P_USB_PHY_CONTROL);
	writel((readl(S3C_USBOTG_PHYPWR) & ~(0x3<<3) & ~(0x1<<0)) | (0x1<<5),
			S3C_USBOTG_PHYPWR);
	writel((readl(S3C_USBOTG_PHYCLK) & ~(0x5<<2)) | (0x3<<0),
			S3C_USBOTG_PHYCLK);
	writel((readl(S3C_USBOTG_RSTCON) & ~(0x3<<1)) | (0x1<<0),
			S3C_USBOTG_RSTCON);
	msleep(1);
	writel(readl(S3C_USBOTG_RSTCON) & ~(0x7<<0),
			S3C_USBOTG_RSTCON);
	msleep(1);

	/* rising/falling time */
	writel(readl(S3C_USBOTG_PHYTUNE) | (0x1<<20),
			S3C_USBOTG_PHYTUNE);

	/* set DC level as 6 (6%) */
	writel((readl(S3C_USBOTG_PHYTUNE) & ~(0xf)) | (0x1<<2) | (0x1<<1),
			S3C_USBOTG_PHYTUNE);
}
//EXPORT_SYMBOL(otg_phy_init);

/* USB Control request data struct must be located here for DMA transfer */
struct usb_ctrlrequest usb_ctrl __attribute__((aligned(64)));

/* OTG PHY Power Off */
void otg_phy_off(void)
{
	writel(readl(S3C_USBOTG_PHYPWR) | (0x3<<3),
			S3C_USBOTG_PHYPWR);
	writel(readl(S5P_USB_PHY_CONTROL) & ~(1<<0),
			S5P_USB_PHY_CONTROL);
}
//EXPORT_SYMBOL(otg_phy_off);

void usb_host_phy_init(void)
{
	struct clk *otg_clk;

	otg_clk = clk_get(NULL, "otg");
	clk_enable(otg_clk);

	if (readl(S5P_USB_PHY_CONTROL) & (0x1<<1))
		return;

	__raw_writel(__raw_readl(S5P_USB_PHY_CONTROL) | (0x1<<1),
			S5P_USB_PHY_CONTROL);
	__raw_writel((__raw_readl(S3C_USBOTG_PHYPWR)
			& ~(0x1<<7) & ~(0x1<<6)) | (0x1<<8) | (0x1<<5),
			S3C_USBOTG_PHYPWR);
	__raw_writel((__raw_readl(S3C_USBOTG_PHYCLK) & ~(0x1<<7)) | (0x3<<0),
			S3C_USBOTG_PHYCLK);
	__raw_writel((__raw_readl(S3C_USBOTG_RSTCON)) | (0x1<<4) | (0x1<<3),
			S3C_USBOTG_RSTCON);
	__raw_writel(__raw_readl(S3C_USBOTG_RSTCON) & ~(0x1<<4) & ~(0x1<<3),
			S3C_USBOTG_RSTCON);
}
//EXPORT_SYMBOL(usb_host_phy_init);

void usb_host_phy_off(void)
{
	__raw_writel(__raw_readl(S3C_USBOTG_PHYPWR) | (0x1<<7)|(0x1<<6),
			S3C_USBOTG_PHYPWR);
	__raw_writel(__raw_readl(S5P_USB_PHY_CONTROL) & ~(1<<1),
			S5P_USB_PHY_CONTROL);
}
//EXPORT_SYMBOL(usb_host_phy_off);
#endif

void s3c_setup_uart_cfg_gpio(unsigned char port)
{
}
//EXPORT_SYMBOL(s3c_setup_uart_cfg_gpio);

#ifdef CONFIG_MACH_SMDKC110
MACHINE_START(SMDKC110, "SMDKC110")
#elif CONFIG_MACH_SMDKV210
MACHINE_START(SMDKV210, "SMDKV210")
#endif
	/* Maintainer: Kukjin Kim <kgene.kim@samsung.com> */
	.phys_io	= S3C_PA_UART & 0xfff00000,//bak串口的起始地址。要看你的板子，是不是物理io就是这个起始地址
	.io_pg_offst	= (((u32)S3C_VA_UART) >> 18) & 0xfffc,//io页表的偏移
	.boot_params	= S5P_PA_SDRAM + 0x100,//启动参数页表的偏移
	//重要的板级初始化函数
	.init_irq	= s5pv210_init_irq,//初始化IRQ中断
	.map_io		= smdkc110_map_io,//map_io成员即内核提供给用户的创建外设I/O资源到内核虚拟地址静态映射表的接口函数
	.init_machine	= smdkc110_machine_init,//bak初始化平台
	.timer		= &s5p_systimer,//定时器
MACHINE_END
/*
按定义展开后：
static const struct machine_desc __mach_desc_SMDK6410 \
 __used \
 __attribute__((__section__(".arch.info.init"))) = {
	.nr = MACH_TYPE_SMDK6410,//开发板在linux中的机器号。
	.name = "SMDK6410",//开发板名称
	.phys_io = S3C_PA_UART & 0xfff00000,//起始IO物理地址
	.io_pg_offst = (((u32)S3C_VA_UART) >> 18) & 0xfffc,
	.boot_params = S3C64XX_PA_SDRAM + 0x100,//内核启动参数的地址
	.init_irq = s5pv210_init_irq,//中断初始化函数
	.map_io = smdkc110_map_io,//IO映射函数（在这里修改时钟频率）
	.init_machine = smdkc110_machine_init,
	.timer = &s5p_systimer,
};
*/
