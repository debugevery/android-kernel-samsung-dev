/* linux/drivers/input/touchscreen/s3c-ts.c
 * ¼ûKconfig¿ÉÖªÖ§³ÖARCH_S3C2410 || ARCH_S3C64XX || ARCH_S5PV2XX || ARCH_S5P64XX || CPU_S5PV210 || CPU_S5PC110
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

/* Touchscreen default configuration==========Èç¹û°å¼¶ÉèÖÃÃ»ÓÐÕâ¸ö£¬ÔòÉèÖÃÄ¬ÈÏÉèÖÃ*/
struct s3c_ts_mach_info s3c_ts_default_cfg /* __initdata */ = {
	.delay			= 10000,
	.presc			= 49,
	.oversampling_shift	= 2,
	.resol_bit		= 10£¬
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


//ÕâÀï£¬¹Ø¼üµÄÄÚÈÝÊÇµ±updownµÄÖµÎª1£¬Ò²¼´´¥Ãþ±Ê°´ÏÂÊ±£¬»áµ÷ÓÃtouch_timer_fire(0);
//´¥ÃþÖÐ¶Ï´¦ÀíµÄ¾ßÌåÄÚÈÝ¶¼ÔÚtouch_timer_fireÖÐÁË£¬ÏÂÃæÀ´·ÖÎötouch_timer_fireµÄÄÚÈÝ¡£
static void touch_timer_fire(unigned long data)
{
	unsigned long data0;
	unsigned long data1;
	int updown;
	int x, y;
	//¶ÁÈ¡AD×ª»»Êý¾ÝµÄÖµ
	data0 = readl(ts_base+S3C_ADCDAT0);
	data1 = readl(ts_base+S3C_ADCDAT1);
	//ÅÐ¶Ïdata0,data1×î¸ßÎ»ÊÇ·ñÈÔÎª"0"£¬Îª¡°0¡±±íÊ¾´¥Ãþ±Ê×´Ì¬±£³ÖÎªdown
	updown = (!(data0 & S3C_ADCDAT0_UPDOWN)) &&
		 (!(data1 & S3C_ADCDAT1_UPDOWN));
     /*
       ¸üÐÂstylus×´Ì¬¼Ä´æÆ÷updown£º
       1 = down
       0 = up
      */
    /*
      touch_timer_fireÕâ¸öº¯ÊýÖ÷ÒªÊµÏÖÒÔÏÂ¹¦ÄÜ£º
      1¡¢stylus downµÄÊ±ºò£¬ÔÚÖÐ¶Ïº¯Êýstylus_updownÀïÃæ±»µ÷ÓÃ£¬
         ´ËÊ±»º´æÇøÃ»ÓÐÊý¾Ý£¬ts.countÎª0£¬ËùÒÔÖ»ÊÇ¼òµ¥µÄÉèÖÃad×ª»»µÄÄ£Ê½£¬È»ºó¿ªÆôad×ª»»¡£
      2¡¢µ«ADCÖÐ¶Ïº¯Êýstylus_action°Ñ»º³åÇøÌîÂúµÄÊ±ºò£¬×÷ÎªÖÐ¶Ïºó°ë¶Îº¯ÊýÉÔºó±»µ÷ÓÃ£¬
         ´ËÊ±ts.countÎª4£¬Ëã³öÆäÆ½¾ùÖµºó£¬½»¸øÊÂ¼þ´¦Àí²ã(Event Handler)´¦Àí£¬
         Ö÷ÒªÊÇÌîÐ´»º³å£¬È»ºó»½ÐÑµÈ´ýÊäÈëÊý¾ÝµÄ½ø³Ì¡£
      3¡¢stylusÌ§Æð£¬µÈµ½»º³åÇøÌîÂúºó(¿ÉÄÜ»á°üº¬Ò»Ð©ÎÞÓÃµÄÊý¾Ý)±»µ÷ÓÃ£¬
         ÕâÊ±ºòÅÐ¶Ï³östylus up£¬±¨¸æstylus upÊÂ¼þ£¬ÖØÐÂµÈ´ýstylus down¡£
   */
	if (updown) {
		if (ts->count) {//±£³ÖÎªdown£¬ÇÒ¼ÇÂ¼ÁËxpºÍypµÄÊý¾Ý£¬Ôò¶ÔÕâÐ©Êý¾Ý½øÐÐ´¦Àí
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
		//AUTOPST±íÊ¾Auto Sequential measurement of X-position, Y-position.
		writel(S3C_ADCTSC_PULL_UP_DISABLE | AUTOPST,
				ts_base + S3C_ADCTSC);
		// Æô¶¯D×ª»»£¬×ª»»ºó»á²úÉúÖÐ¶ÏIRQ_ADC	===================================================	
		writel(readl(ts_base+S3C_ADCCON) | S3C_ADCCON_ENABLE_START,
				ts_base + S3C_ADCCON);
	} else {
		// µ±´¥Ãþ±ÊÎªÌ§Æð×´Ì¬Ê±£¬±¨¸æÆä´¥Ãþ±Ê×´Ì¬
		ts->count = 0;
		input_report_abs(ts->dev, ABS_X, ts->xp);//ÏòÉÏ±¨¸æLCD×ø±êÎ»ÖÃ£¨x¡¢yµÄ¾ø¶Ô×ø±êÖµ£©
		input_report_abs(ts->dev, ABS_Y, ts->yp);
		input_report_abs(ts->dev, ABS_Z, 0);
		input_report_key(ts->dev, BTN_TOUCH, 0);//±¨¸æ°´¼üÊÂ¼þ¡ª¡ª´¥ÃþÊÂ¼þ
		input_sync(ts->dev);
		//Çå³ý´¥Ãþ±Ê°´ÏÂµÄÖÐ¶ÏÐÅºÅ
		writel(WAIT4INT(0), ts_base+S3C_ADCTSC);
	}
}

static struct timer_list touch_timer =
		TIMER_INITIALIZER(touch_timer_fire, 0, 0);

static irqreturn_t stylus_updown(int irqno, void *param)
{ //ÖÐ¶Ï´¦ÀíÉÏ°ë²¿·Ö===´¦Àí´¥ÃþµÄÖÐ¶Ï·þÎñ³ÌÐò=============ÅÐ¶Ï´¥ÃþÆÁÊÇ·ñ°´ÏÂµÄÖÐ¶Ï
	unsigned long data0;
	unsigned long data1;
	int updown;

	data0 = readl(ts_base + S3C_ADCDAT0);
	data1 = readl(ts_base + S3C_ADCDAT1);
	//ÅÐ¶Ïdata0,data1×î¸ßÎ»ÊÇ·ñÎª"0"£¬Îª0±íÊ¾°´ÏÂ
	updown = (!(data0 & S3C_ADCDAT0_UPDOWN)) &&
		 (!(data1 & S3C_ADCDAT1_UPDOWN));

	/* TODO we should never get an interrupt with updown set while
	 * the timer is running, but maybe we ought to verify that the
	 * timer isn't running anyways. */

	if (updown)//ÅÐ¶Ï´¥Ãþ±ÊÓÐÃ»ÓÐ°´ÏÂ£¬1±íÊ¾°´ÏÂ¡£
		touch_timer_fire(0);

	if (ts->s3c_adc_con == ADC_TYPE_2) { //Èç¹ûÎªS3C64XX»ò S5PC1XX
		__raw_writel(0x0, ts_base + S3C_ADCCLRWK);
		__raw_writel(0x0, ts_base + S3C_ADCCLRINT);
	}

	return IRQ_HANDLED;
}

// stylus_actionÎªÖÐ¶Ï´¦Àíº¯ÊýµÄÏÂ°ë²¿·Ö¡ª¡ªADC×ª»»µÄÖÐ¶Ï·þÎñ³ÌÐò¡£ÆäÄÚÈÝ½øÐÐµÄ²Ù×÷´ó²¿·ÖÊÇ»º³åÆ÷Êý¾ÝµÄÌî³ä£¬
//Èç£ºts->yp¡¢ts->xp¡¢ts->count¡¢S3C_ADCTSC¡¢S3C_ADCCON¡¢S3C_ADCCLRWK¡¢S3C_ADCCLRINT¡£ÆäÖÐts->yp¡¢ts->xp ÖÐ
//µÄÖµ¾­´¦Àíºó´«ÈëÉÏ²ã£»ts->count ×÷Îª±êÖ¾£»¶øS3C_ADCTSC¡¢S3C_ADCCON µÈÊÇ¶ÔAD×ª»»µÄ´¥ÃþÆÁ¿ØÖÆ¼Ä´æÆ÷ºÍÅäÖÃ¼Ä´æÆ÷µÈ¼Ä´æÆ÷½øÐÐ²Ù×÷¡£
static irqreturn_t stylus_action(int irqno, void *param)
{//ÖÐ¶Ï´¦ÀíÏÂ°ë²¿·Ö============´¥ÃþÆÁ°´ÏÂ»á²úÉúADC×ª»»µÄÖÐ¶Ï
	unsigned long data0;
	unsigned long data1;

	data0 = readl(ts_base + S3C_ADCDAT0);
	data1 = readl(ts_base + S3C_ADCDAT1);
	//Èç¹û×ª»»¾«¶ÈÎª12Î»£¬Ôò½øÐÐÏàµ±µÄÊý¾Ý´¦Àí
	if (ts->resol_bit == 12) {
#if defined(CONFIG_TOUCHSCREEN_NEW)
	//ÀÛ¼Ó×ª»»µÄ12Î»Êý¾Ý[11£º0]£¬¼ÇÂ¼x,yµãµÄÎ»ÖÃ£¨ÒòÎªÀÛ¼Ó£¬µ½ºóÃæÒªÈ¡Æ½¾ùÖµ£©¡£
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
	//¼ÇÂ¼ÀÛ¼ÓµÄ´ÎÊý
	ts->count++;
	//ÈôÀÛ¼ÓµÄ´ÎÊýÃ»ÓÐÒç³ö£¬ÔòAuto Sequential measurement²¢Æô¶¯AD×ª»»
	if (ts->count < (1<<ts->shift)) {        /* »º³åÇøÎ´Âú£¬ÔÙ´Î¼¤»îADC×ª»» */
		writel(S3C_ADCTSC_PULL_UP_DISABLE | AUTOPST,
				ts_base + S3C_ADCTSC);
		writel(readl(ts_base + S3C_ADCCON) | S3C_ADCCON_ENABLE_START,
				ts_base + S3C_ADCCON);
	} else {	        /* »º³åÇøÂú£¬¼¤»îÏÂ°ë²¿´¦Àí³ÌÐòtouch_timer_fire£¬´¦Àí½ÓÊÕÊý¾Ý */
		mod_timer(&touch_timer, jiffies + 1);//Èôtouch_timer³¬Ê±£¬ÔòÐÞ¸Ä¶¨Ê±Æ÷Îªjiffies+1
		writel(WAIT4INT(1), ts_base + S3C_ADCTSC);
	}
	//Èç¹ûÎªS3C64XX»ò S5PC1XX
	if (ts->s3c_adc_con == ADC_TYPE_2) {
		__raw_writel(0x0, ts_base+S3C_ADCCLRWK);
		__raw_writel(0x0, ts_base+S3C_ADCCLRINT);
	}
	return IRQ_HANDLED;
}

static struct s3c_ts_mach_info *s3c_ts_get_platdata(struct device *dev)
{
	if (dev->platform_data != NULL)//===================================Èç¹û°å¼¶Ã»ÓÐÉèÖÃ£¬ÔòÉèÖÃÄ¬ÈÏÉèÖÃ
		return (struct s3c_ts_mach_info *)dev->platform_data;//Ê¹ÓÃ°å¼¶ÉèÖÃ£

	return &s3c_ts_default_cfg;//Ê¹ÓÃÄ¬ÈÏÉèÖÃ
}

/*
 * The functions for inserting/removing us as a module.

 Ê¹ÓÃinput×ÓÏµÍ³µÄÒ»°ãÁ÷³ÌÎª£ºinput_allocate_device()ÉêÇëÒ»¸öinput_devÉè±¸¡ª¡ª>³õÊ¼»¯¸Ãinput_dev¡ª¡ª>
 input_register_device£¨£©Ïò×ÓÏµÍ³×¢²á¸ÃÉè±¸¡ª¡ª>ÖÐ¶ÏÊ±input_event£¨£©Ïò×ÓÏµÍ³±¨¸æÊÂ¼þ¡£´ËÁ÷³ÌÒ»Ä¿ÁËÈ»£¬
 ¼´Ê¹²»¿´input×ÓÏµÍ³£¬ÎÒÃÇ°´ÕÕËü¸ø³öµÄÒ»°ãÁ÷³ÌÒ²¿ÉÒÔ°Ñ×Ô¼ºÐ´µÄIOÇý¶¯¼ÓÈëµ½input×ÓÏµÍ³ÀïÈ¥£¬µ«
 input_event£¨£©Ìá½»ÍêÊý¾Ýºó£¬ÎÒÃÇµÄÊý¾ÝÈ¥ÄÄÁËÄØ£¬ÔõÃ´´¦ÀíÄØ£¬×Ü¾õµÃÔÆÀïÎíÀïµÄ£¬×ÜÏëÒ»Ì½¾¿¾¹¡£*/
static int __init s3c_ts_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct device *dev;
	struct input_dev *input_dev;
	struct s3c_ts_mach_info *s3c_ts_cfg;
	int ret, size;
	int irq_flags = 0;

	dev = &pdev->dev;
	//==================================³õÊ¼»¯ADCÄÚ´æÏà¹Ø*=======================================
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);//»ñÈ¡IOÄÚ´æ£¬¼ûstatic struct resource s3c_ts_resource[] = {
	if (res == NULL) {
		dev_err(dev, "no memory resource specified\n");
		return -ENOENT;
	}

	size = (res->end - res->start) + 1;//»ñÈ¡×ÊÔ´´óÐ¡£¬¼ûstatic struct resource s3c_ts_resource[] = {
	ts_mem = request_mem_region(res->start, size, pdev->name);//ÉêÇëÄÚ´æ£¬´Óres->start¿ªÊ¼£¬size´óÐ¡
	if (ts_mem == NULL) {
		dev_err(dev, "failed to get memory region\n");
		ret = -ENOENT;
		goto err_req;
	}

	ts_base = ioremap(res->start, size);//ÖØÓ³ÉäÎªÐéÄâµØÖ·£¬ÓÃÓÚÅäÖÃ¼Ä´æÆ÷
	if (ts_base == NULL) {
		dev_err(dev, "failed to ioremap() region\n");
		ret = -EINVAL;
		goto err_map;
	}

	ts_clock = clk_get(&pdev->dev, "adc");//»ñÈ¡Ê±ÖÓ£¬ÓÃÓÚÊ¹ÄÜÊ±ÖÓ,¼ûlinux/arch/arm/mach-s5pv210/clock.c  init_clocks_disable
	if (IS_ERR(ts_clock)) {
		dev_err(dev, "failed to find watchdog clock source\n");
		ret = PTR_ERR(ts_clock);
		goto err_clk;
	}

	clk_enable(ts_clock);
	//==================================³õÊ¼»¯ADC¼Ä´æÆ÷*=======================================
	s3c_ts_cfg = s3c_ts_get_platdata(&pdev->dev);//»ñÈ¡Æ½Ì¨Êý¾Ý
	if ((s3c_ts_cfg->presc & 0xff) > 0)
		writel(S3C_ADCCON_PRSCEN |S3C_ADCCON_PRSCVL(s3c_ts_cfg->presc & 0xFF),ts_base+S3C_ADCCON);//½«ÅäÖÃÐ´Èë¼Ä´æÆ÷S3C_ADCCONÖÐ
	else
		writel(0, ts_base + S3C_ADCCON);

	/* Initialise registers ===============³õÊ¼»¯ADC¼Ä´æÆ÷*/
	if ((s3c_ts_cfg->delay & 0xffff) > 0)
		writel(s3c_ts_cfg->delay & 0xffff, ts_base + S3C_ADCDLY);//½«ÑÓÊ±ÅäÖÃÐ´Èë¼Ä´æÆ÷

	if (s3c_ts_cfg->resol_bit == 12) {
		switch (s3c_ts_cfg->s3c_adc_con) {//Ñ¡ÔñADCÀàÐÍ
		case ADC_TYPE_2:
			writel(readl(ts_base + S3C_ADCCON) |
					S3C_ADCCON_RESSEL_12BIT,
					ts_base + S3C_ADCCON);//½«ÀàÐÍÅäÖÃÐ´Èë¼Ä´æÆ÷
			break;

		case ADC_TYPE_1:
			writel(readl(ts_base + S3C_ADCCON) |
					S3C_ADCCON_RESSEL_12BIT_1,
					ts_base + S3C_ADCCON);//½«ÀàÐÍÅäÖÃÐ´Èë¼Ä´æÆ÷
			break;

		default:
			dev_err(dev, "this type of AP isn't supported !\n");
			break;
		}
	}

	writel(WAIT4INT(0), ts_base + S3C_ADCTSC);
	//=================================³õÊ¼»¯ADCÏà¹ØÐÅÏ¢s3c_ts_info*========================================
	ts = kzalloc(sizeof(struct s3c_ts_info), GFP_KERNEL);

	input_dev = input_allocate_device();//ÉêÇë·ÖÅäÒ»¸öinput_devÉè±¸
	if (!input_dev) {
		ret = -ENOMEM;
		goto err_alloc;
	}

	ts->dev = input_dev;//=================================Í¨¹ý´ËÖµ×¢²áÊäÈëÉè±¸

	ts->dev->evbit[0] = BIT_MASK(EV_SYN) | BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	ts->dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

	if (s3c_ts_cfg->resol_bit == 12) {
		input_set_abs_params(ts->dev,
				ABS_X, X_COOR_MIN, X_COOR_MAX, X_COOR_FUZZ, 0);
		input_set_abs_params(ts->dev,
				ABS_Y, Y_COOR_MIN, Y_COOR_MAX, Y_COOR_FUZZ, 0);
	} else {
		input_set_abs_params(ts->dev, ABS_X, 0, 0x3FF, 0, 0);//Õâ¸öÊÇÉèÖÃad×ª»»µÄx×ø±ê
		input_set_abs_params(ts->dev, ABS_Y, 0, 0x3FF, 0, 0);//Õâ¸öÊÇÉèÖÃad×ª»»µÄy×ø±ê
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
	//=================================³õÊ¼»¯ADCÖÐ¶ÏÏà¹Ø*========================================
	/* For IRQ_PENDUP */
	ts_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);//»ñÈ¡ÖÐ¶ÏºÅ£¬¼ûstatic struct resource s3c_ts_resource[] = {
	if (ts_irq == NULL) {
		dev_err(dev, "no irq resource specified\n");
		ret = -ENOENT;
		goto err_irq;
	}

	ret = request_irq(ts_irq->start, stylus_updown, irq_flags, //ÖÐ¶Ï´¦ÀíÉÏ°ë²¿·Ö======ÅÐ¶Ï´¥ÃþÆÁÊÇ·ñ°´ÏÂµÄÖÐ¶Ï
			"s3c_updown", ts);
	if (ret != 0) {
		dev_err(dev, "s3c_ts.c: Could not allocate ts IRQ_PENDN !\n");
		ret = -EIO;
		goto err_irq;
	}

	/* For IRQ_ADC */
	ts_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 1);//»ñÈ¡ÖÐ¶ÏºÅ£¬¼ûstatic struct resource s3c_ts_resource[] = {
	if (ts_irq == NULL) {
		dev_err(dev, "no irq resource specified\n");
		ret = -ENOENT;
		goto err_irq;
	}

	ret = request_irq(ts_irq->start, stylus_action, irq_flags, //ÖÐ¶Ï´¦ÀíÏÂ°ë²¿·Ö=====´¥ÃþÆÁ°´ÏÂ»á²úÉúADC×ª»»µÄÖÐ¶Ï
			"s3c_action", ts);
	if (ret != 0) {
		dev_err(dev, "s3c_ts.c: Could not allocate ts IRQ_ADC !\n");
		ret =  -EIO;
		goto err_irq;
	}

	printk(KERN_INFO "%s got loaded successfully : %d bits\n",
			s3c_ts_name, s3c_ts_cfg->resol_bit);

	/* All went ok, so register to the input system ============×¢²áÊäÈëÉè±¸*/
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
