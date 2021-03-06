/* linux/arch/arm/plat-s3c/dev-i2c0.c
 *
 * Copyright 2008-2009 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *	http://armlinux.simtec.co.uk/
 *
 * S3C series device definition for i2c device 0
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

//#include <linux/gfp.h>
//#include <linux/kernel.h>
//#include <linux/string.h>
//#include <linux/platform_device.h>
//#include <linux/clk.h>
//#include <linux/err.h>

//#include <mach/irqs.h>
//#include <mach/map.h>

//#include <plat/regs-iic.h>
//#include <plat/iic.h>
//#include <plat/devs.h>
//#include <plat/cpu.h>

//#include <asm/io.h>

static struct resource s3c_i2c_resource[] = {
	[0] = {
		.start = S3C_PA_IIC,
		.end   = S3C_PA_IIC + SZ_4K - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_IIC,
		.end   = IRQ_IIC,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device s3c_device_i2c0 = {//I2C平台设备
	.name		  = "s3c2410-i2c",
	.id		  = 0,
	.num_resources	  = ARRAY_SIZE(s3c_i2c_resource),
	.resource	  = s3c_i2c_resource,
};

static struct s3c2410_platform_i2c default_i2c_data0 /* __initdata */ = {
	.flags		= 0,
	.slave_addr	= 0x10,
	.frequency	= 400*1000,
	.sda_delay	= S3C2410_IICLC_SDA_DELAY15 | S3C2410_IICLC_FILTER_ON,
};
//将S3C2440上的I2C控制器进行了一些初始化，但是并没有写入硬件寄存器，
//仅仅是保存在了s3c2410_platform_i2c结构体中。
void __init s3c_i2c0_set_platdata(struct s3c2410_platform_i2c *pd)
{
	struct s3c2410_platform_i2c *npd;

	if (!pd)
		pd = &default_i2c_data0;//设置默认值
	//将pd结构体信息复制到npd内存中
	npd = kmemdup(pd, sizeof(struct s3c2410_platform_i2c), GFP_KERNEL);
	if (!npd)
		printk(KERN_ERR "%s: no memory for platform data\n", __func__);
	else if (!npd->cfg_gpio)
		npd->cfg_gpio = s3c_i2c0_cfg_gpio;//配置I2C控制器GPIO函数指针

	s3c_device_i2c0.dev.platform_data = npd;
}

void s3c_i2c0_force_stop()
{
	void __iomem *regs;
	struct clk *clk;
	unsigned long iicstat;

	regs = ioremap(S3C_PA_IIC, SZ_4K);
	if(regs == NULL) {
		printk(KERN_ERR "%s, cannot request IO\n", __func__);
		return;
	}

	clk = clk_get(&s3c_device_i2c0.dev, "i2c");
	if(clk == NULL || IS_ERR(clk)) {
		printk(KERN_ERR "%s, cannot get cloock\n", __func__);
		return;
	}

	clk_enable(clk);
	iicstat = readl(regs + S3C2410_IICSTAT);
	writel(iicstat & ~S3C2410_IICSTAT_TXRXEN, regs + S3C2410_IICSTAT);
	clk_disable(clk);

	iounmap(regs);
}
//EXPORT_SYMBOL(s3c_i2c0_force_stop);

