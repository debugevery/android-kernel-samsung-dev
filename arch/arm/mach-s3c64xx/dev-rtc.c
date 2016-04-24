/* linux/arch/arm/plat-s3c64xx/dev-rtc.c
 *
 * Copyright 2009 by Maurus Cuelenaere <mcuelenaere@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

//#include <linux/kernel.h>
//#include <linux/string.h>
//#include <linux/platform_device.h>

//#include <mach/irqs.h>
//#include <mach/map.h>

//#include <plat/devs.h>
//定义了RTC平台设备使用的资源，这些资源在驱动中都会用到
static struct resource s3c_rtc_resource[] = {
	[0] = {//IO端口资源范围
		.start = S3C64XX_PA_RTC,
		.end   = S3C64XX_PA_RTC + 0xff,
		.flags = IORESOURCE_MEM,
	},
	[1] = {//RTC报警中断资源
		.start = IRQ_RTC_ALARM,
		.end   = IRQ_RTC_ALARM,
		.flags = IORESOURCE_IRQ,
	},
	[2] = {//TICK节拍时间中断资源
		.start = IRQ_RTC_TIC,
		.end   = IRQ_RTC_TIC,
		.flags = IORESOURCE_IRQ
	}
};

struct platform_device s3c_device_rtc = {//定义了RTC平台设备
	.name		  = "s3c64xx-rtc",//设备名称
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(s3c_rtc_resource),//资源数量
	.resource	  = s3c_rtc_resource,//引用上面定义的资源
};
//EXPORT_SYMBOL(s3c_device_rtc);
