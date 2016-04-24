 //clock�ļ�����ʼ��6410ʱ��

/* linux/arch/arm/plat-s3c64xx/clock.c
*
* Copyright 2008 Openmoko, Inc.
* Copyright 2008 Simtec Electronics
* Ben Dooks <ben@simtec.co.uk>
* http://armlinux.simtec.co.uk/
*
* S3C64XX Base clock support S3C64XX����ʱ��֧��
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*/
//��������ͷ�ļ�
#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/delay.h>
#include <linux/io.h>

#include <mach/hardware.h>
#include <mach/map.h>

//����ͷ�ļ���ƽ̨���
#include <plat/regs-sys.h>   //S3C64XX system register definitions�о�ûʲô����

#include <plat/regs-clock.h> 
//�ǳ���ĺ궨�壬��ʱ�ӡ���Ƶ���
/*���пɿ�����HCLK��PCLK��SCLK
˳������PLL���ܣ�֧������PLL�ֱ���APLL��MPLL��EPLL��
APLLΪARM�ṩʱ�ӣ�����ARMCLK��
MPLLΪ���к�AXI/AHB/APB������ģ���ṩʱ�ӣ�����HCLK��PCLK��
EPLLΪ����������ṩʱ�ӣ�����SCLK��*/

//��������ͷ�ļ���plat-s3c��,����������ͨ�õ�

#include <plat/cpu.h>
//��Բ�ͬ�Ĵ��������ú궨��ķ�����������
//������IODESC_ENT(x)�꣬����Ϊ����IOӳ���
/*//////////////////////////////����2410���Ͻ���/////////////////////////////////////////////////////
IODESC_ENT�����£�
#define IODESC_ENT(x) { (unsigned long)S3C24XX_VA_##x, __phys_to_pfn(S3C24XX_PA_##x), S3C24XX_SZ_##x, MT_DEVICE }

չ����ȼ��ڣ�
static struct map_desc s3c2410_iodesc[] __initdata = {
{
.virtual = (unsigned long)S3C24XX_VA_ LCD),
.pfn = __phys_to_pfn(S3C24XX_PA_ LCD),
.length = S3C24XX_SZ_ LCD,
.type = MT_DEVICE
},
/////////////////////////////////////////////////////////////////////////////////////////////*/

#include <plat/devs.h>
/*���ļ�ûɶ��˵�ģ���extern��ʽ������һЩplatform_device�ṹ��
eg��extern struct platform_device s3c_device_fb;
ֵ��ע��ĵط���platform_device����ṹ�壬����ȥ������
��platform_device.h�ļ���
struct platform_device {
const char * name;
int   id;
struct device dev;
u32   num_resources;
struct resource * resource;
};
����ǳ�����ƽ̨�豸�ṹ���ԭ����*/

#include <plat/clock.h>
/*��ͷ�ļ�������һ���ܴ��clk�ṹ��
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
�벻ͨΪʲôһ��clk�ṹ�嶼Ҫ����ô��ĳ�Ա�������ýṹ����ڱ��ļ��ǳ���Ҫ��
�����úܶ�ýṹ��ĳ�Ա*/

//���ڰ�ͷ�ļ����꣬��ʼ������

//��Ȼ�ṹ��ܸ��ӣ�������������ȴ����
struct clk clk_27m = {
.name   = "clk_27m",
.id   = -1,
.rate   = 27000000,
};

//�������𿪹�48M��clk������others�Ĵ����ĵ�16bit
static int clk_48m_ctrl(struct clk *clk, int enable)
{
unsigned long flags;
u32 val;
/* can't rely on clock lock, this register has other usages */
local_irq_save(flags);
val = __raw_readl(S3C64XX_OTHERS); //���others�Ĵ����������ֲ��л������
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

//48Mʱ�ӵĽṹ�壬���˸�������enable�����������Ǹ�������
struct clk clk_48m = {
.name   = "clk_48m",
.id   = -1,
.rate   = 48000000,
.enable   = clk_48m_ctrl,
};

//inline����ò�ƶ�ʱ��Ҫ��Ƚϸߣ��������Ǹ�ͨ�õ�ʱ�ӿ��غ���
static int inline s3c64xx_gate(void __iomem *reg, //
     struct clk *clk,      //����clk�ṹ��
     int enable)        //���뿪����
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

//pclk���ƺ���������ᵽ�˷�װ�ĸо�
static int s3c64xx_pclk_ctrl(struct clk *clk, int enable)
{
return s3c64xx_gate(S3C_PCLK_GATE, clk, enable);
}

//hclk���ƺ���
static int s3c64xx_hclk_ctrl(struct clk *clk, int enable)
{
return s3c64xx_gate(S3C_HCLK_GATE, clk, enable);
}
//sclk���ƺ���
int s3c64xx_sclk_ctrl(struct clk *clk, int enable)
{
return s3c64xx_gate(S3C_SCLK_GATE, clk, enable);
}
//ʱ�ӳ�ʼ���ṹ�����飡init_clocks_disable�����Ϊɶ��disable��
//clk_h��clk_p�Ķ�����plat-s3c/clock.c��
//nand��adc��i2c��iisx2��spix2��48Mx3��otg
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

//��һ��ʱ�ӳ�ʼ���ṹ������ init_clocks
//lcd��gpio��host��hsmmcx3��timers��uartx4��rtc��watchdog��ac97
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

//ò���ǳ�ʼ��ʱ���ص�clk�ṹ������ clks
static struct clk *clks[] __initdata = {
&clk_ext, //plat-s3c/clock.c
&clk_epll, //plat-s3c/clock.c
&clk_27m,
&clk_48m,
};

//��ʼ��ʱ��ע�ắ��
void __init s3c64xx_register_clocks(void)
{
struct clk *clkp;
int ret;
int ptr;

s3c24xx_register_clocks(clks, ARRAY_SIZE(clks)); 
//������plat-s3c/clock.c����Ȼû���رܣ����ȿ���
//clks���������Ǹ�����Ա��4�� 
//s3c24xx_register_clocks////////////////////////////////////////////////////////////////////
int s3c24xx_register_clocks(struct clk **clks, int nr_clks)
{
int fails = 0;
for (; nr_clks > 0; nr_clks--, clks++)    //Ӧ��ѭ��4�Σ�ͳ��ע��ʧ�ܵĴ���
   {  
   if (s3c24xx_register_clock(*clks) < 0)
    fails++;
   }

return fails;
}
//s3c24xx_register_clock//////////////////////////////////////////////////////////////////////////////////////////////
//ע������ĺ���������ֻ��һ��s�Ĳ������ע��ʱ������
int s3c24xx_register_clock(struct clk *clk)
{
clk->owner = THIS_MODULE;
if (clk->enable == NULL)
   clk->enable = clk_null_enable;

/* add to the list of available clocks */
/* Quick check to see if this clock has already been registered. */
BUG_ON(clk->list.prev != clk->list.next);
//BUG_ON�����ܺ��棬����������㣬˵���϶���BUG��ϵͳ����Ϊ��һ��oops����������֪�������⡣
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

   (clkp->enable)(clkp, 0); //����������������Ϊɶ��init disable�ˣ��������൱����ÿ���ṹ���Ա��enable������
}

s3c_pwmclk_init(); //˵�����������������ô�е㲻����ĸо�������ʼ��pwm��clk?
       //����ǰ���ȷû����pwm�����clk�ṹ����
       //����λ��arch/arm/plat-s3c/pwm-clokc.c�´ο���
}
