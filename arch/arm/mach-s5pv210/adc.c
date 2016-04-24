/* linux/arch/arm/mach-s5pv210/adc.c
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Copyright (c) 2004 Arnaud Patard <arnaud.patard@rtp-net.org>
 * iPAQ H1940 touchscreen support
 *
 * ChangeLog
 *
 * 2004-09-05: Herbert P枚tzl <herbert@13thfloor.at>
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
//#include <linux/miscdevice.h>
//#include <linux/clk.h>
//#include <linux/mutex.h>
//#include <linux/io.h>
//#include <linux/uaccess.h>

//#include <asm/irq.h>
//#include <mach/hardware.h>
//#include <linux/uaccess.h>

//#include <mach/regs-adc.h>
//#include <mach/adc.h>
//#include <mach/irqs.h>

#define ADC_MINOR	131
#define ADC_INPUT_PIN	_IOW('S', 0x0c, unsigned long)

#define ADC_WITH_TOUCHSCREEN

static struct clk	*adc_clock;

static void __iomem	*base_addr;
static int adc_port;
struct s3c_adc_mach_info *plat_data;

#ifdef ADC_WITH_TOUCHSCREEN
static DEFINE_MUTEX(adc_mutex);

static unsigned long data_for_ADCCON;
static unsigned long data_for_ADCTSC;

static void s3c_adc_save_SFR_on_ADC(void)
{//读取保存寄存器中的值
	data_for_ADCCON = readl(base_addr + S3C_ADCCON);
	data_for_ADCTSC = readl(base_addr + S3C_ADCTSC);
}

static void s3c_adc_restore_SFR_on_ADC(void)
{//写入保存寄存器中的值
	writel(data_for_ADCCON, base_addr + S3C_ADCCON);
	writel(data_for_ADCTSC, base_addr + S3C_ADCTSC);
}
#else
static struct resource	*adc_mem;
#endif

static int s3c_adc_open(struct inode *inode, struct file *file)
{
	return 0;
}

static unsigned int s3c_adc_convert(void)
{//进行ADC转换
	unsigned int adc_return = 0;
	unsigned long data0;
	unsigned long data1;

	writel((readl(base_addr + S3C_ADCCON) | S3C_ADCCON_PRSCEN) & ~S3C_ADCCON_STDBM,
		base_addr + S3C_ADCCON);

	writel((adc_port & 0xF), base_addr + S3C_ADCMUX);

	udelay(10);//延时

	writel(readl(base_addr + S3C_ADCCON) | S3C_ADCCON_ENABLE_START,
		base_addr + S3C_ADCCON);

	do {
		data0 = readl(base_addr + S3C_ADCCON);
	} while (!(data0 & S3C_ADCCON_ECFLG));//循环判断ADC转换完的状态位

	data1 = readl(base_addr + S3C_ADCDAT0);

	writel((readl(base_addr + S3C_ADCCON) | S3C_ADCCON_STDBM) & ~S3C_ADCCON_PRSCEN,
		base_addr + S3C_ADCCON);

	if (plat_data->resolution == 12)
		adc_return = data1 & S3C_ADCDAT0_XPDATA_MASK_12BIT;
	else
		adc_return = data1 & S3C_ADCDAT0_XPDATA_MASK;

	return adc_return;//返回转换值
}


int s3c_adc_get_adc_data(int channel)
{//获取ADC转换值
	int adc_value = 0;
	int cur_adc_port = 0;

#ifdef ADC_WITH_TOUCHSCREEN
	mutex_lock(&adc_mutex);
	s3c_adc_save_SFR_on_ADC();//读取寄存器中的值到全局变量中
#else
	mutex_lock(&adc_mutex);
#endif

	cur_adc_port = adc_port;
	adc_port = channel;

	adc_value = s3c_adc_convert();//返回ADC转换值

	adc_port = cur_adc_port;

#ifdef ADC_WITH_TOUCHSCREEN
	s3c_adc_restore_SFR_on_ADC();//写入值到ADC寄存器中
	mutex_unlock(&adc_mutex);
#else
	mutex_unlock(&adc_mutex);
#endif

	pr_debug("%s : Converted Value: %03d\n", __func__, adc_value);

	return adc_value;
}
//EXPORT_SYMBOL(s3c_adc_get_adc_data);

int s3c_adc_get(struct s3c_adc_request *req)
{//获取ADC转换值
	unsigned adc_channel = req->channel;
	int adc_value_ret = 0;

	adc_value_ret = s3c_adc_convert();//返回ADC转换值

	req->callback(adc_channel, req->param, adc_value_ret);

	return 0;
}
//EXPORT_SYMBOL(s3c_adc_get);

static ssize_t
s3c_adc_read(struct file *file, char __user *buffer,
		size_t size, loff_t *pos)
{
	int  adc_value = 0;

#ifdef ADC_WITH_TOUCHSCREEN
	mutex_lock(&adc_mutex);
	s3c_adc_save_SFR_on_ADC();//读取寄存器中的值到全局变量中
#endif
	printk(KERN_INFO "## delay: %d\n", readl(base_addr + S3C_ADCDLY));
	adc_value = s3c_adc_convert();//返回ADC转换值

#ifdef ADC_WITH_TOUCHSCREEN
	s3c_adc_restore_SFR_on_ADC();//写入值到ADC寄存器中
	mutex_unlock(&adc_mutex);
#endif

	if (copy_to_user(buffer, &adc_value, sizeof(unsigned int)))
		return -EFAULT;

	return sizeof(unsigned int);
}


static int s3c_adc_ioctl(struct inode *inode, struct file *file,
	unsigned int cmd, unsigned long arg)
{

	switch (cmd) {
	case ADC_INPUT_PIN:
		adc_port = (unsigned int) arg;

		if (adc_port >= 4)
			printk(KERN_WARNING
				" %d is already reserved for TouchScreen\n",
				adc_port);
		return 0;

	default:
		return -ENOIOCTLCMD;
	}
}

static const struct file_operations s3c_adc_fops = {//注册混杂设备
	.owner		= THIS_MODULE,
	.read		= s3c_adc_read,
	.open		= s3c_adc_open,
	.ioctl		= s3c_adc_ioctl,
};

static struct miscdevice s3c_adc_miscdev = {//混杂设备
	.minor		= ADC_MINOR,
	.name		= "adc",
	.fops		= &s3c_adc_fops,
};
//获取平台数据platform_data
static struct s3c_adc_mach_info *s3c_adc_get_platdata(struct device *dev)
{
	if (dev->platform_data != NULL)
		return (struct s3c_adc_mach_info *) dev->platform_data;
	else
		return 0;
}

/*
 * The functions for inserting/removing us as a module.
 */

static int __devinit s3c_adc_probe(struct platform_device *pdev)
{
	struct resource	*res;
	struct device *dev;
	int ret;
	int size;
	//获取平台设备资源
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	dev = &pdev->dev;

	if (res == NULL) {
		dev_err(dev, "no memory resource specified\n");
		return -ENOENT;
	}

	size = (res->end - res->start) + 1;

#if !defined(ADC_WITH_TOUCHSCREEN)
	adc_mem = request_mem_region(res->start, size, pdev->name);
	if (adc_mem == NULL) {	//请求内存
		dev_err(dev, "failed to get memory region\n");
		ret = -ENOENT;
		goto err_req;
	}
#endif
	//重映射
	base_addr = ioremap(res->start, size);
	if (base_addr ==  NULL) {
		dev_err(dev, "fail to ioremap() region\n");
		ret = -ENOENT;
		goto err_map;
	}
	//获取时钟
	adc_clock = clk_get(&pdev->dev, "adc");

	if (IS_ERR(adc_clock)) {
		dev_err(dev, "failed to fine ADC clock source\n");
		ret = PTR_ERR(adc_clock);
		goto err_clk;
	}
	//使能时钟
	clk_enable(adc_clock);

	/*获取平台数据 read platform data from device struct */
	//在mach-smdkc110.c已经设置平台数据：s3c_adc_set_platdata(&s3c_adc_platform)
	plat_data = s3c_adc_get_platdata(&pdev->dev);

	if ((plat_data->presc & 0xff) > 0)
		writel(S3C_ADCCON_PRSCEN |
		       S3C_ADCCON_PRSCVL(plat_data->presc & 0xff),
		       base_addr + S3C_ADCCON);
	else
		writel(0, base_addr + S3C_ADCCON);

	/*初始化相关寄存器 Initialise registers */
	if ((plat_data->delay & 0xffff) > 0)
		writel(plat_data->delay & 0xffff, base_addr + S3C_ADCDLY);

	if (plat_data->resolution == 12)
		writel(readl(base_addr + S3C_ADCCON) |
		       S3C_ADCCON_RESSEL_12BIT, base_addr + S3C_ADCCON);

	writel((readl(base_addr + S3C_ADCCON) | S3C_ADCCON_STDBM) & ~S3C_ADCCON_PRSCEN,
		base_addr + S3C_ADCCON);

	ret = misc_register(&s3c_adc_miscdev);//注册混杂设备
	if (ret) {
		printk(KERN_ERR "cannot register miscdev on minor=%d (%d)\n",
			ADC_MINOR, ret);
		goto err_clk;
	}

	return 0;

err_clk:
	clk_disable(adc_clock);	//禁止时钟
	clk_put(adc_clock);

err_map:
	iounmap(base_addr);

#if !defined(ADC_WITH_TOUCHSCREEN)
err_req:
	release_resource(adc_mem);
	kfree(adc_mem);
#endif

	return ret;
}


static int s3c_adc_remove(struct platform_device *dev)
{
	clk_disable(adc_clock);
	clk_put(adc_clock);
	return 0;
}

#ifdef CONFIG_PM
static unsigned int adccon, adctsc, adcdly;

static int s3c_adc_suspend(struct platform_device *dev, pm_message_t state)
{
	adccon = readl(base_addr + S3C_ADCCON);
	adctsc = readl(base_addr + S3C_ADCTSC);
	adcdly = readl(base_addr + S3C_ADCDLY);

	return 0;
}

static int s3c_adc_resume(struct platform_device *pdev)
{
	writel(adccon, base_addr + S3C_ADCCON);
	writel(adctsc, base_addr + S3C_ADCTSC);
	writel(adcdly, base_addr + S3C_ADCDLY);

	return 0;
}
#else
#define s3c_adc_suspend NULL
#define s3c_adc_resume  NULL
#endif

static struct platform_driver s3c_adc_driver = {
       .probe          = s3c_adc_probe,//注册混杂设备，并读写ADC
       .remove         = s3c_adc_remove,
       .suspend        = s3c_adc_suspend,//读取寄存器
       .resume         = s3c_adc_resume,//写入寄存器
       .driver		= {
		.owner	= THIS_MODULE,
		.name	= "s3c-adc",
	},
};

static char banner[] /* __initdata */ = KERN_INFO \
	"S5PV210 ADC driver, (c) 2010 Samsung Electronics\n";

int __init s3c_adc_init(void)
{
	printk(banner);
	return platform_driver_register(&s3c_adc_driver);
}

void __exit s3c_adc_exit(void)
{
	platform_driver_unregister(&s3c_adc_driver);
}

//module_init(s3c_adc_init);
//module_exit(s3c_adc_exit);

//MODULE_AUTHOR("dsfine.ha@samsung.com");
//MODULE_DESCRIPTION("S5PV210 ADC driver");
//MODULE_LICENSE("GPL");
