/* linux/arch/arm/mach-s3c64xx/mach-smdk6410.c
 *
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *	http://armlinux.simtec.co.uk/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
*/

//#include <linux/kernel.h>
//#include <linux/types.h>
//#include <linux/interrupt.h>
//#include <linux/list.h>
//#include <linux/timer.h>
//#include <linux/init.h>
//#include <linux/serial_core.h>
//#include <linux/platform_device.h>
//#include <linux/io.h>
//#include <linux/i2c.h>
//#include <linux/leds.h>
//#include <linux/fb.h>
//#include <linux/gpio.h>
//#include <linux/delay.h>
//#include <linux/smsc911x.h>
//#include <linux/regulator/fixed.h>

#ifdef CONFIG_SMDK6410_WM1190_EV1
//#include <linux/mfd/wm8350/core.h>
//#include <linux/mfd/wm8350/pmic.h>
#endif

#ifdef CONFIG_SMDK6410_WM1192_EV1
//#include <linux/mfd/wm831x/core.h>
//#include <linux/mfd/wm831x/pdata.h>
#endif

//#include <video/platform_lcd.h>

//#include <asm/mach/arch.h>
//#include <asm/mach/map.h>
//#include <asm/mach/irq.h>

//#include <mach/hardware.h>
//#include <mach/regs-fb.h>
//#include <mach/map.h>

//#include <asm/irq.h>
//#include <asm/mach-types.h>

//#include <plat/regs-serial.h>
//#include <mach/regs-modem.h>
//#include <mach/regs-gpio.h>
//#include <mach/regs-sys.h>
//#include <mach/regs-srom.h>
//#include <plat/iic.h>
//#include <plat/fb.h>
//#include <plat/gpio-cfg.h>

//#include <mach/s3c6410.h>
//#include <plat/clock.h>
//#include <plat/devs.h>
//#include <plat/cpu.h>
//#include <plat/adc.h>
//#include <plat/ts.h>

#define UCON S3C2410_UCON_DEFAULT | S3C2410_UCON_UCLK
#define ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
#define UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE
 /*
串口初始化结构体
UART的设置（UCONn、ULCONn、UFCONn寄存器等）
*/

static struct s3c2410_uartcfg smdk6410_uartcfgs[] /*__initdata */ = {
	[0] = {
		.hwport	     = 0,
		.flags	     = 0,
		.ucon	     = UCON, //时钟选择01 = EXT_UCLK0: DIV_VAL1) = (EXT_UCLK0 / (bps x 16) ) –1
         // | Tx中断类型level | Rx中断类型level | 开Rx超时中断 | 发送中断或轮询模式 | 接收中断或轮询模式
         //EXT_UCLK0 clock is external clock.(XpwmECLK PAD input) 为何是EXT_UCLK0?
		.ulcon	     = ULCON,//配置为8bit
		.ufcon	     = UFCON,// Tx FIFO Tri level 16byte | Rx FIFO Trigger level 8byte | Tx FIFO normal | Rx FIFO normal | FIFO enable

	},
	[1] = {
		.hwport	     = 1,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	},
	[2] = {
		.hwport	     = 2,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	},
	[3] = {
		.hwport	     = 3,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	},
};
//======================smdk6410_lcd_powerdev=========================================================
/* framebuffer and LCD setup. */

/* GPF15 = LCD backlight control
 * GPF13 => Panel power
 * GPN5 = LCD nRESET signal
 * PWM_TOUT1 => backlight brightness
 */

static void smdk6410_lcd_power_set(struct plat_lcd_data *pd,
				   unsigned int power)
{
	if (power) {
		gpio_direction_output(S3C64XX_GPF(13), 1);
		gpio_direction_output(S3C64XX_GPF(15), 1);

		/* fire nRESET on power up */
		gpio_direction_output(S3C64XX_GPN(5), 0);
		msleep(10);
		gpio_direction_output(S3C64XX_GPN(5), 1);
		msleep(1);
	} else {
		gpio_direction_output(S3C64XX_GPF(15), 0);
		gpio_direction_output(S3C64XX_GPF(13), 0);
	}
}

static struct plat_lcd_data smdk6410_lcd_power_data = {
	.set_power	= smdk6410_lcd_power_set,
};

static struct platform_device smdk6410_lcd_powerdev = {//平台设备
	.name			= "platform-lcd",
	.dev.parent		= &s3c_device_fb.dev,
	.dev.platform_data	= &smdk6410_lcd_power_data,
};




//===========================smdk6410_lcd_pdata====================================================
static struct s3c_fb_pd_win smdk6410_fb_win0 = {//显示参数设置
	/* this is to ensure we use win0 */
	.win_mode	= {
		.pixclock	= 41094,
		.left_margin	= 8,
		.right_margin	= 13,
		.upper_margin	= 7,
		.lower_margin	= 5,
		.hsync_len	= 3,
		.vsync_len	= 1,
		.xres		= 800,
		.yres		= 480,
	},
	.max_bpp	= 32,
	.default_bpp	= 16,
};

/* 405566 clocks per frame => 60Hz refresh requires 24333960Hz clock */
static struct s3c_fb_platdata smdk6410_lcd_pdata /*__initdata */ = {
	.setup_gpio	= s3c64xx_fb_gpio_setup_24bpp,//设置24灰度LCD的GPIO配置寄存器为LCD功能
	.win[0]		= &smdk6410_fb_win0,
	.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
	.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,
};
//==============================smdk6410_smsc911x=================================================


/*
 * Configuring Ethernet on SMDK6410
 *
 * Both CS8900A and LAN9115 chips share one chip select mediated by CFG6.
 * The constant address below corresponds to nCS1
 *
 *  1) Set CFGB2 p3 ON others off, no other CFGB selects "ethernet"
 *  2) CFG6 needs to be switched to "LAN9115" side
 */

static struct resource smdk6410_smsc911x_resources[] = {
	[0] = {
		.start = S3C64XX_PA_XM0CSN1,
		.end   = S3C64XX_PA_XM0CSN1 + SZ_64K - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = S3C_EINT(10),
		.end   = S3C_EINT(10),
		.flags = IORESOURCE_IRQ | IRQ_TYPE_LEVEL_LOW,
	},
};

static struct smsc911x_platform_config smdk6410_smsc911x_pdata = {
	.irq_polarity  = SMSC911X_IRQ_POLARITY_ACTIVE_LOW,
	.irq_type      = SMSC911X_IRQ_TYPE_OPEN_DRAIN,
	.flags         = SMSC911X_USE_32BIT | SMSC911X_FORCE_INTERNAL_PHY,
	.phy_interface = PHY_INTERFACE_MODE_MII,
};


static struct platform_device smdk6410_smsc911x = {//平台设备
	.name          = "smsc911x",
	.id            = -1,
	.num_resources = ARRAY_SIZE(smdk6410_smsc911x_resources),
	.resource      = &smdk6410_smsc911x_resources[0],
	.dev = {
		.platform_data = &smdk6410_smsc911x_pdata,
	},
};
//=========================smdk6410_b_pwr_5v======================================================
#ifdef CONFIG_REGULATOR
static struct regulator_consumer_supply smdk6410_b_pwr_5v_consumers[] = {
	{
		/* WM8580 */
		.supply = "PVDD",
		.dev_name = "0-001b",
	},
	{
		/* WM8580 */
		.supply = "AVDD",
		.dev_name = "0-001b",
	},
};

static struct regulator_init_data smdk6410_b_pwr_5v_data = {
	.constraints = {
		.always_on = 1,
	},
	.num_consumer_supplies = ARRAY_SIZE(smdk6410_b_pwr_5v_consumers),
	.consumer_supplies = smdk6410_b_pwr_5v_consumers,
};

static struct fixed_voltage_config smdk6410_b_pwr_5v_pdata = {
	.supply_name = "B_PWR_5V",
	.microvolts = 5000000,
	.init_data = &smdk6410_b_pwr_5v_data,
	.gpio = -EINVAL,
};

static struct platform_device smdk6410_b_pwr_5v = {//平台设备
	.name          = "reg-fixed-voltage",
	.id            = -1,
	.dev = {
		.platform_data = &smdk6410_b_pwr_5v_pdata,
	},
};
#endif
//===============================================================================
//我在这添加的dm9000地址映射
static struct map_desc smdk6410_iodesc[] = {};

//===============================================================================
//初始化的平台设备
/*内核启动后，首先构造链表将描述设备的platform_device构造组织起来，
得到一个设备的列表；当加载某个驱动程序的platform_driver结构时，
使用一些匹配函数来检查驱动程序能否支持这些设备，常用的检查方法很简单：比较驱动程序和设备的名称。
*/
static struct platform_device *smdk6410_devices[] /*__initdata */ = {//包含的平台设备数组
#ifdef CONFIG_SMDK6410_SD_CH0
	&s3c_device_hsmmc0,
#endif
#ifdef CONFIG_SMDK6410_SD_CH1
	&s3c_device_hsmmc1,
#endif
	&s3c_device_i2c0,
	&s3c_device_i2c1,
	&s3c_device_fb,
	&s3c_device_ohci,
	&s3c_device_usb_hsotg,
	&s3c64xx_device_iisv4,

#ifdef CONFIG_REGULATOR
	&smdk6410_b_pwr_5v,
#endif
	&smdk6410_lcd_powerdev,

	&smdk6410_smsc911x,
	&s3c_device_adc,
	&s3c_device_ts,
	&s3c_device_wdt,
};

//===============================================================================
#ifdef CONFIG_REGULATOR
/* ARM core */
static struct regulator_consumer_supply smdk6410_vddarm_consumers[] = {
	{
		.supply = "vddarm",
	}
};

/* VDDARM, BUCK1 on J5 *///这个data被置于 对应的 platform_device 的data字段中。
static struct regulator_init_data smdk6410_vddarm = {
	.constraints = {
		.name = "PVDD_ARM",
		.min_uV = 1000000,
		.max_uV = 1300000,
		.always_on = 1,
		.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE,
	},
	.num_consumer_supplies = ARRAY_SIZE(smdk6410_vddarm_consumers),
	.consumer_supplies = smdk6410_vddarm_consumers,
};

/* VDD_INT, BUCK2 on J5 */
static struct regulator_init_data smdk6410_vddint = {
	.constraints = {
		.name = "PVDD_INT",
		.min_uV = 1000000,
		.max_uV = 1200000,
		.always_on = 1,
		.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE,
	},
};

/* VDD_HI, LDO3 on J5 */
static struct regulator_init_data smdk6410_vddhi = {
	.constraints = {
		.name = "PVDD_HI",
		.always_on = 1,
	},
};

/* VDD_PLL, LDO2 on J5 */
static struct regulator_init_data smdk6410_vddpll = {
	.constraints = {
		.name = "PVDD_PLL",
		.always_on = 1,
	},
};

/* VDD_UH_MMC, LDO5 on J5 */
static struct regulator_init_data smdk6410_vdduh_mmc = {
	.constraints = {
		.name = "PVDD_UH/PVDD_MMC",
		.always_on = 1,
	},
};

/* VCCM3BT, LDO8 on J5 */
static struct regulator_init_data smdk6410_vccmc3bt = {
	.constraints = {
		.name = "PVCCM3BT",
		.always_on = 1,
	},
};

/* VCCM2MTV, LDO11 on J5 */
static struct regulator_init_data smdk6410_vccm2mtv = {
	.constraints = {
		.name = "PVCCM2MTV",
		.always_on = 1,
	},
};

/* VDD_LCD, LDO12 on J5 */
static struct regulator_init_data smdk6410_vddlcd = {
	.constraints = {
		.name = "PVDD_LCD",
		.always_on = 1,
	},
};

/* VDD_OTGI, LDO9 on J5 */
static struct regulator_init_data smdk6410_vddotgi = {
	.constraints = {
		.name = "PVDD_OTGI",
		.always_on = 1,
	},
};

/* VDD_OTG, LDO14 on J5 */
static struct regulator_init_data smdk6410_vddotg = {
	.constraints = {
		.name = "PVDD_OTG",
		.always_on = 1,
	},
};

/* VDD_ALIVE, LDO15 on J5 */
static struct regulator_init_data smdk6410_vddalive = {
	.constraints = {
		.name = "PVDD_ALIVE",
		.always_on = 1,
	},
};

/* VDD_AUDIO, VLDO_AUDIO on J5 */
static struct regulator_init_data smdk6410_vddaudio = {
	.constraints = {
		.name = "PVDD_AUDIO",
		.always_on = 1,
	},
};
#endif

#ifdef CONFIG_SMDK6410_WM1190_EV1
/* S3C64xx internal logic & PLL */
static struct regulator_init_data wm8350_dcdc1_data = {
	.constraints = {
		.name = "PVDD_INT/PVDD_PLL",
		.min_uV = 1200000,
		.max_uV = 1200000,
		.always_on = 1,
		.apply_uV = 1,
	},
};

/* Memory */
static struct regulator_init_data wm8350_dcdc3_data = {
	.constraints = {
		.name = "PVDD_MEM",
		.min_uV = 1800000,
		.max_uV = 1800000,
		.always_on = 1,
		.state_mem = {
			 .uV = 1800000,
			 .mode = REGULATOR_MODE_NORMAL,
			 .enabled = 1,
		},
		.initial_state = PM_SUSPEND_MEM,
	},
};

/* USB, EXT, PCM, ADC/DAC, USB, MMC */
static struct regulator_consumer_supply wm8350_dcdc4_consumers[] = {
	{
		/* WM8580 */
		.supply = "DVDD",
		.dev_name = "0-001b",
	},
};

static struct regulator_init_data wm8350_dcdc4_data = {
	.constraints = {
		.name = "PVDD_HI/PVDD_EXT/PVDD_SYS/PVCCM2MTV",
		.min_uV = 3000000,
		.max_uV = 3000000,
		.always_on = 1,
	},
	.num_consumer_supplies = ARRAY_SIZE(wm8350_dcdc4_consumers),
	.consumer_supplies = wm8350_dcdc4_consumers,
};

/* OTGi/1190-EV1 HPVDD & AVDD */
static struct regulator_init_data wm8350_ldo4_data = {
	.constraints = {
		.name = "PVDD_OTGI/HPVDD/AVDD",
		.min_uV = 1200000,
		.max_uV = 1200000,
		.apply_uV = 1,
		.always_on = 1,
	},
};

static struct {
	int regulator;////bak稳压器名称
	struct regulator_init_data *initdata;//bak初始化数据
} wm1190_regulators[] = {
	{ WM8350_DCDC_1, &wm8350_dcdc1_data },
	{ WM8350_DCDC_3, &wm8350_dcdc3_data },
	{ WM8350_DCDC_4, &wm8350_dcdc4_data },
	{ WM8350_DCDC_6, &smdk6410_vddarm },
	{ WM8350_LDO_1, &smdk6410_vddalive },
	{ WM8350_LDO_2, &smdk6410_vddotg },
	{ WM8350_LDO_3, &smdk6410_vddlcd },
	{ WM8350_LDO_4, &wm8350_ldo4_data },
};

static int __init smdk6410_wm8350_init(struct wm8350 *wm8350)
{
	int i;

	/* Configure the IRQ line */
	s3c_gpio_setpull(S3C64XX_GPN(12), S3C_GPIO_PULL_UP);

	/* Instantiate the regulators 初始化电源稳压器*/
	for (i = 0; i < ARRAY_SIZE(wm1190_regulators); i++)
		wm8350_register_regulator(wm8350,
					  wm1190_regulators[i].regulator,
					  wm1190_regulators[i].initdata);

	return 0;
}

static struct wm8350_platform_data /*__initdata */ smdk6410_wm8350_pdata = {
	.init = smdk6410_wm8350_init,
	.irq_high = 1,
	.irq_base = IRQ_BOARD_START,
};
#endif
//===============================================================================
#ifdef CONFIG_SMDK6410_WM1192_EV1
static struct gpio_led wm1192_pmic_leds[] = {
	{
		.name = "PMIC:red:power",
		.gpio = GPIO_BOARD_START + 3,
		.default_state = LEDS_GPIO_DEFSTATE_ON,
	},
};

static struct gpio_led_platform_data wm1192_pmic_led = {
	.num_leds = ARRAY_SIZE(wm1192_pmic_leds),
	.leds = wm1192_pmic_leds,
};

static struct platform_device wm1192_pmic_led_dev = {
	.name          = "leds-gpio",
	.id            = -1,
	.dev = {
		.platform_data = &wm1192_pmic_led,
	},
};

static int wm1192_pre_init(struct wm831x *wm831x)
{
	int ret;

	/* Configure the IRQ line */
	s3c_gpio_setpull(S3C64XX_GPN(12), S3C_GPIO_PULL_UP);

	ret = platform_device_register(&wm1192_pmic_led_dev);
	if (ret != 0)
		dev_err(wm831x->dev, "Failed to add PMIC LED: %d\n", ret);

	return 0;
}

static struct wm831x_backlight_pdata wm1192_backlight_pdata = {
	.isink = 1,
	.max_uA = 27554,
};

static struct regulator_init_data wm1192_dcdc3 = {
	.constraints = {
		.name = "PVDD_MEM/PVDD_GPS",
		.always_on = 1,
	},
};

static struct regulator_consumer_supply wm1192_ldo1_consumers[] = {
	{ .supply = "DVDD", .dev_name = "0-001b", },   /* WM8580 */
};

static struct regulator_init_data wm1192_ldo1 = {
	.constraints = {
		.name = "PVDD_LCD/PVDD_EXT",
		.always_on = 1,
	},
	.consumer_supplies = wm1192_ldo1_consumers,
	.num_consumer_supplies = ARRAY_SIZE(wm1192_ldo1_consumers),
};

static struct wm831x_status_pdata wm1192_led7_pdata = {
	.name = "LED7:green:",
};

static struct wm831x_status_pdata wm1192_led8_pdata = {
	.name = "LED8:green:",
};

static struct wm831x_pdata smdk6410_wm1192_pdata = {
	.pre_init = wm1192_pre_init,
	.irq_base = IRQ_BOARD_START,

	.backlight = &wm1192_backlight_pdata,
	.dcdc = {
		&smdk6410_vddarm,  /* DCDC1 */
		&smdk6410_vddint,  /* DCDC2 */
		&wm1192_dcdc3,
	},
	.gpio_base = GPIO_BOARD_START,
	.ldo = {
		 &wm1192_ldo1,        /* LDO1 */
		 &smdk6410_vdduh_mmc, /* LDO2 */
		 NULL,                /* LDO3 NC */
		 &smdk6410_vddotgi,   /* LDO4 */
		 &smdk6410_vddotg,    /* LDO5 */
		 &smdk6410_vddhi,     /* LDO6 */
		 &smdk6410_vddaudio,  /* LDO7 */
		 &smdk6410_vccm2mtv,  /* LDO8 */
		 &smdk6410_vddpll,    /* LDO9 */
		 &smdk6410_vccmc3bt,  /* LDO10 */
		 &smdk6410_vddalive,  /* LDO11 */
	},
	.status = {
		&wm1192_led7_pdata,
		&wm1192_led8_pdata,
	},
};
#endif
//===============================================================================
static struct i2c_board_info i2c_devs0[] /*__initdata */ = {//描述了板载的所有I2C设备信息
	{ I2C_BOARD_INFO("24c08", 0x50), },
	{ I2C_BOARD_INFO("wm8580", 0x1b), },

#ifdef CONFIG_SMDK6410_WM1192_EV1
	{ I2C_BOARD_INFO("wm8312", 0x34),
	  .platform_data = &smdk6410_wm1192_pdata,
	  .irq = S3C_EINT(12),
	},
#endif

#ifdef CONFIG_SMDK6410_WM1190_EV1
	{ I2C_BOARD_INFO("wm8350", 0x1a),
	  .platform_data = &smdk6410_wm8350_pdata,
	  .irq = S3C_EINT(12),
	},
#endif
};

static struct i2c_board_info i2c_devs1[] /*__initdata  */ = {
	{ I2C_BOARD_INFO("24c128", 0x57), },	/* Samsung S524AD0XD1 */
};

static struct s3c2410_ts_mach_info s3c_ts_platform /*__initdata  */  = {
	.delay			= 10000,
	.presc			= 49,
	.oversampling_shift	= 2,
};
//===============================================================================
static void __init smdk6410_map_io(void)
{
	u32 tmp;
	//主要是做外围设备的物理地址到虚拟地址的映射
	s3c64xx_init_io(smdk6410_iodesc, ARRAY_SIZE(smdk6410_iodesc));//调用linux/arch/arm/plat-s3c64xx/cpu.c中函数
	//频率的初始化
	s3c24xx_init_clocks(12000000);//初始化clock为12Mhz
	//串口的初始化：四个串口都默认设置了
	s3c24xx_init_uarts(smdk6410_uartcfgs, ARRAY_SIZE(smdk6410_uartcfgs));

	/* set the LCD type */
	//通过SPCON特殊端口功能寄存器设置LCD类型
	tmp = __raw_readl(S3C64XX_SPCON);//读取GPIO寄存器的值
	tmp &= ~S3C64XX_SPCON_LCD_SEL_MASK;
	tmp |= S3C64XX_SPCON_LCD_SEL_RGB;//设置GGB I/F类型
	__raw_writel(tmp, S3C64XX_SPCON);//写入值到寄存器

	/* remove the lcd bypass通过MIFPCON寄存器设置LCD旁路选择控制模式 */
	tmp = __raw_readl(S3C64XX_MODEM_MIFPCON);//读取GPIO寄存器的值
	tmp &= ~MIFPCON_LCD_BYPASS;
	__raw_writel(tmp, S3C64XX_MODEM_MIFPCON);//写入值到寄存器
}

static void __init smdk6410_machine_init(void)
{
	u32 cs1;

	s3c_i2c0_set_platdata(NULL);//将S3C2440上的I2C控制器进行了一些初始化，//设置默认值，但是并没有写入硬件寄存器�
	s3c_i2c1_set_platdata(NULL);//将S3C2440上的I2C控制器进行了一些初始化，//设置默认值，但是并没有写入硬件寄存器�
	//设置LCD平台数据参数
	s3c_fb_set_platdata(&smdk6410_lcd_pdata);

	s3c24xx_ts_set_platdata(&s3c_ts_platform);

	/* configure nCS1 width to 16 bits */
	/*通过__raw_readl,__raw_writel函数直接设置寄存器 configure nCS1 width to 16 bits */
	cs1 = __raw_readl(S3C64XX_SROM_BW) &          //读取GPIO寄存器的值
		    ~(S3C64XX_SROM_BW__CS_MASK << S3C64XX_SROM_BW__NCS1__SHIFT);
	cs1 |= ((1 << S3C64XX_SROM_BW__DATAWIDTH__SHIFT) |
		(1 << S3C64XX_SROM_BW__WAITENABLE__SHIFT) |
		(1 << S3C64XX_SROM_BW__BYTEENABLE__SHIFT)) <<
						   S3C64XX_SROM_BW__NCS1__SHIFT;
	__raw_writel(cs1, S3C64XX_SROM_BW);

	/* 通过__raw_readl,__raw_writel函数直接设置寄存器set timing for nCS1 suitable for ethernet chip */
	__raw_writel((0 << S3C64XX_SROM_BCX__PMC__SHIFT) |
		     (6 << S3C64XX_SROM_BCX__TACP__SHIFT) |
		     (4 << S3C64XX_SROM_BCX__TCAH__SHIFT) |
		     (1 << S3C64XX_SROM_BCX__TCOH__SHIFT) |
		     (0xe << S3C64XX_SROM_BCX__TACC__SHIFT) |
		     (4 << S3C64XX_SROM_BCX__TCOS__SHIFT) |
		     (0 << S3C64XX_SROM_BCX__TACS__SHIFT), S3C64XX_SROM_BC1);
/* 申请一个gpio，其实就是检查该gpio是否空闲，如果空闲就可以gpio则为你要申请的哪一个管脚，label则是为其取一个名字。*/
	gpio_request(S3C64XX_GPN(5), "LCD power");
	gpio_request(S3C64XX_GPF(13), "LCD power");
	gpio_request(S3C64XX_GPF(15), "LCD power");
	//这个函数注册static struct i2c_board_info结构，此结构是代替I2C设备的板级注册
	i2c_register_board_info(0, i2c_devs0, ARRAY_SIZE(i2c_devs0));//将一个i2c_board_info的结构体注册进系统
	i2c_register_board_info(1, i2c_devs1, ARRAY_SIZE(i2c_devs1));
	//注册smdk6410特有的设备
	platform_add_devices(smdk6410_devices, ARRAY_SIZE(smdk6410_devices));//bak添加多个平台设备
}

MACHINE_START(SMDK6410, "SMDK6410")
	/* Maintainer: Ben Dooks <ben@fluff.org> */
	.phys_io	= S3C_PA_UART & 0xfff00000,//bak串口的起始地址。要看你的板子，是不是物理io就是这个起始地址
	.io_pg_offst	= (((u32)S3C_VA_UART) >> 18) & 0xfffc,//io页表的偏移
	.boot_params	= S3C64XX_PA_SDRAM + 0x100,//启动参数页表的偏移
//重要的板级初始化函数
	.init_irq	= s3c6410_init_irq,//初始化IRQ中断
	.map_io		= smdk6410_map_io,//map_io成员即内核提供给用户的创建外设I/O资源到内核虚拟地址静态映射表的接口函数
	.init_machine	= smdk6410_machine_init,/////bak初始化平台
	.timer		= &s3c24xx_timer,//定时器
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
	.init_irq = s3c6410_init_irq,//中断初始化函数
	.map_io = smdk6410_map_io,//IO映射函数（在这里修改时钟频率）
	.init_machine = smdk6410_machine_init,
	.timer = &s3c24xx_timer,
};
*/
