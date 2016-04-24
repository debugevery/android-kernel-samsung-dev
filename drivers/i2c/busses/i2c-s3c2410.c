/* linux/drivers/i2c/busses/i2c-s3c2410.c
 * 2410 I2C¿ØÖÆÆ÷×ÜÏßÇı¶¯£¬(Ô´ÂëÖĞÃ»ÓĞÉè±¸Çı¶¯£¬ÈçI2C×ÜÏßÉÏ¹ÒÔØµÄÉè±¸µÄÇı¶¯)

 <<ÓÃ»§Ó¦ÓÃ³ÌĞò-->i2c-dev.c-->i2c-core.c-->i2c-s3c2410.c>>
 
 ¾ßÌå¿ØÖÆÆ÷Ğ¾Æ¬µÄ IIC ¿ØÖÆ·½Ê½²»Í¬£¬ËùÒÔ¶Ô²»Í¬µÄ¿ØÖÆÆ÷ÒªÓĞ²»Í¬µÄÇı¶¯£¬
 ¶ø¶Ô S3C2410 CPU À´½²£¬ËüµÄÇı¶¯¾ÍÊÇ i2c-s3c2410.c¡£¸ÃÎÄ¼şÖ÷ÒªÊµÏÖ¶Ô
 ¿ØÖÆÆ÷µÄ³õÊ¼»¯£¬ È»ºóµ÷ÓÃºËĞÄ·şÎñ²ã°Ñ S3C2410 µÄ IIC ×ÜÏß¼ÓÈëµ½ Linux Kernel ÖĞ¡£
/*===========================================
	I2C×ÜÏßÇı¶¯Ä£¿éµÄ¼ÓÔØº¯ÊıÒªÍê³ÉÁ½¸ö¹¤×÷¡£ 
l  ³õÊ¼»¯I2CÊÊÅäÆ÷ËùÊ¹ÓÃµÄÓ²¼ş×ÊÔ´£¬ÈçÉêÇë I/OµØÖ·¡¢ÖĞ¶ÏºÅµÈ¡£ 
l  Í¨¹ıi2c_add_adapter()Ìí¼Ói2c_adapter µÄÊı¾İ½á¹¹£¬µ±È»Õâ¸ö i2c_adapter Êı
¾İ½á¹¹µÄ³ÉÔ±ÒÑ¾­±»xxxÊÊÅäÆ÷µÄÏàÓ¦º¯ÊıÖ¸ÕëËù³õÊ¼»¯¡£ 
I2C×ÜÏßÇı¶¯Ä£¿éµÄĞ¶ÔØº¯ÊıÒªÍê³ÉµÄ¹¤×÷Óë¼ÓÔØº¯ÊıÏà·´¡£ 
l  ÊÍ·ÅI2CÊÊÅäÆ÷ËùÊ¹ÓÃµÄÓ²¼ş×ÊÔ´£¬ÈçÊÍ·ÅI/O µØÖ·¡¢ÖĞ¶ÏºÅµÈ¡£ 
l  Í¨¹ıi2c_del_adapter()É¾³ıi2c_adapter µÄÊı¾İ½á¹¹¡£ 
´úÂëÇåµ¥15.10ËùÊ¾ÎªI2CÊÊÅäÆ÷Çı¶¯µÄÄ£¿é¼ÓÔØºÍĞ¶ÔØº¯ÊıµÄÄ£°å¡£

	ÎÒÃÇĞèÒªÎªÌØ¶¨µÄ I2C ÊÊÅäÆ÷ÊµÏÖÆäÍ¨ĞÅ·½·¨£¬Ö÷ÒªÊµÏÖ i2c_algorithm µÄ
master_xfer()º¯ÊıºÍfunctionality()º¯Êı¡£ 
functionality()º¯Êı·Ç³£¼òµ¥£¬ÓÃÓÚ·µ»ØalgorithmËùÖ§³ÖµÄÍ¨ĞÅĞ­Òé£¬ ÈçI2C_FUNC_I2C¡¢
I2C_FUNC_10BIT_ADDR ¡¢ I2C_FUNC_SMBUS_READ_BYTE ¡¢
I2C_FUNC_SMBUS_WRITE_BYTEµÈ¡£ 
master_xfer()º¯ÊıÔÚI2CÊÊÅäÆ÷ÉÏÍê³É´«µİ¸øËüµÄi2c_msgÊı×éÖĞµÄÃ¿¸öI2CÏûÏ¢£¬

	master_xfer()º¯ÊıµÄÊµÏÖÔÚĞÎÊ½ÉÏ»áºÜ¶àÑù£¬ ¼´±ãÊÇ Linux ÄÚºËÔ´´úÂëÖĞÒÑ¾­
¸ø³öµÄÒ»Ğ© I2C ×ÜÏßÇı¶¯µÄ master_xfer()º¯Êı£¬ÓÉÓÚÓÉ²»Í¬µÄ×éÖ¯»ò¸öÈËÍê³É£¬
·ç¸ñÉÏµÄ²î±ğÒ²·Ç³£´ó£¬²»Ò»¶¨ÄÜÓëÄ£°åÍêÈ«¶ÔÓ¦£¬Èç master_xfer()º¯ÊıÄ£°å¸ø
³öµÄÏûÏ¢´¦ÀíÊÇË³Ğò½øĞĞµÄ£¬¶øÓĞµÄÇı¶¯ÒÔÖĞ¶Ï·½Ê½À´Íê³ÉÕâ¸öÁ÷³Ì£¨15.5 ½ÚµÄ
ÊµÀı¼´ÊÇÈç´Ë£© ¡£²»¹Ü¾ßÌåÔõÃ´ÊµÊ©£¬Á÷³ÌµÄ±¾ÖÊ¶¼ÊÇ²»±äµÄ¡£ÒòÎªÕâ¸öÁ÷³Ì²»
ÒÔÇı¶¯¹¤³ÌÊ¦µÄÒâÖ¾Îª×ªÒÆ£¬×îÖÕÓÉ I2C ×ÜÏßÓ²¼şÉÏµÄÍ¨ĞÅĞ­Òé¾ö¶¨¡£ 2
================================================*/
/*ÆäËü2410Çı¶¯µÄmaster_xfer()º¯ÊıÄ£°åÖĞµÄ i2c_adapter_xxx_start()¡¢i2c_adapter_xxx_setaddr()¡¢
i2c_adapter_ xxx_wait_ack()¡¢ i2c_adapter_xxx_readbytes()¡¢i2c_adapter_xxx_writebytes()
ºÍ i2c_adapter_xxx_stop()º¯ÊıÓÃÓÚÍê³ÉÊÊÅäÆ÷µÄµ×²ãÓ²¼ş²Ù×÷£¬Óë I2C ÊÊÅäÆ÷ºÍ CPU
µÄ¾ßÌåÓ²¼şÖ±½ÓÏà¹Ø£¬ĞèÒªÓÉ¹¤³ÌÊ¦¸ù¾İĞ¾Æ¬µÄÊı¾İÊÖ²áÀ´ÊµÏÖ¡£ */
 /* Copyright (C) 2004,2005,2009 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C2410 I2C Controller
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
*/

//#include <linux/kernel.h>
//#include <linux/module.h>

//#include <linux/i2c.h>
//#include <linux/i2c-id.h>
//#include <linux/init.h>
//#include <linux/time.h>
//#include <linux/interrupt.h>
//#include <linux/delay.h>
//#include <linux/errno.h>
//#include <linux/err.h>
//#include <linux/platform_device.h>
//#include <linux/clk.h>
//#include <linux/cpufreq.h>
//#include <linux/slab.h>
//#include <linux/io.h>

//#include <asm/irq.h>

//#include <plat/regs-iic.h>
//#include <plat/iic.h>

/* i2c controller state */

enum s3c24xx_i2c_state {
	STATE_IDLE,
	STATE_START,
	STATE_READ,
	STATE_WRITE,
	STATE_STOP
};

enum s3c24xx_i2c_type {
	TYPE_S3C2410,
	TYPE_S3C2440,
};

struct s3c24xx_i2c {
        spinlock_t              lock;        //×ÔÑ¡Ëø(·ÀÖ¹×ÜÏß×ÊÔ´±»²¢·¢·ÃÎÊ)
        wait_queue_head_t       wait;        //µÈ´ı¶ÓÁĞ(µ±ÓĞÊı¾İĞèÒªÊÕ/·¢Ê±Æô¶¯×ÜÏß£¬È»ºóÊØºòÔÚµÈ´ı¶ÓÁĞ£¬Ö±µ½Êı¾İÊÕ/·¢½áÊøºó±»»½ĞÑ·µ»Ø)

	unsigned int		suspended:1;

        struct i2c_msg          *msg;        //i2cĞÅÏ¢Ö¸Õë
        unsigned int            msg_num;    //ĞèÒª´«ÊäµÄi2c msgÊı
        unsigned int            msg_idx;    //³É¹¦´«ÊäµÄi2c msgÊı
        unsigned int            msg_ptr;    //µ±Ç°i2c msgÄÚÖ¸Õë

        unsigned int            tx_setup;    //ÑÓÊ±Öµ(±£Ö¤×ÜÏßÆô¶¯Ê±Êı¾İÒÑ¾­´«Êäµ½×ÜÏßÉÏ)
	unsigned int		irq;

	enum s3c24xx_i2c_state	state;//i2c×ÜÏß×´Ì¬
	unsigned long		clkrate;

	void __iomem		*regs;
	struct clk		*clk;
	struct device		*dev;
	struct resource		*ioarea;
	struct i2c_adapter	adap;  //×ÜÏßÊÊÅäÆ÷(¸öÈË¾õµÃËü¸üÏñÉè±¸Çı¶¯ÖĞµÄÉè±¸¶ø·ÇÇı¶¯)

#ifdef CONFIG_CPU_FREQ
	struct notifier_block	freq_transition;
#endif
};

/* default platform data removed, dev should always carry data. */

/* s3c24xx_i2c_is2440()
 *
 * return true is this is an s3c2440ÅĞ¶ÏÊÇ·ñÎª2440Ö÷¿ØÖÆÆ÷
*/

static inline int s3c24xx_i2c_is2440(struct s3c24xx_i2c *i2c)
{
	struct platform_device *pdev = to_platform_device(i2c->dev);
	enum s3c24xx_i2c_type type;

	type = platform_get_device_id(pdev)->driver_data;
	return type == TYPE_S3C2440;
}


static inline void s3c24xx_i2c_disable_ack(struct s3c24xx_i2c *i2c)
{
	unsigned long tmp;

	tmp = readl(i2c->regs + S3C2410_IICCON);
	writel(tmp & ~S3C2410_IICCON_ACKEN, i2c->regs + S3C2410_IICCON);
}

static inline void s3c24xx_i2c_enable_ack(struct s3c24xx_i2c *i2c)
{
	unsigned long tmp;

	tmp = readl(i2c->regs + S3C2410_IICCON);
	writel(tmp | S3C2410_IICCON_ACKEN, i2c->regs + S3C2410_IICCON);
}

/* irq enable/disable functions */

static inline void s3c24xx_i2c_disable_irq(struct s3c24xx_i2c *i2c)
{
	unsigned long tmp;

	tmp = readl(i2c->regs + S3C2410_IICCON);
	writel(tmp & ~S3C2410_IICCON_IRQEN, i2c->regs + S3C2410_IICCON);
}

static inline void s3c24xx_i2c_enable_irq(struct s3c24xx_i2c *i2c)
{
	unsigned long tmp;

	tmp = readl(i2c->regs + S3C2410_IICCON);
	writel(tmp | S3C2410_IICCON_IRQEN, i2c->regs + S3C2410_IICCON);
}


/* s3c24xx_i2c_message_start
 *
 * put the start of a message onto the bus
*/
//s3c24xx_i2c_message_start()º¯ÊıĞ´ S3C2410 ÊÊÅäÆ÷¶ÔÓ¦µÄ¿ØÖÆ¼Ä´æÆ÷£¬Ïò I2C ´Ó
//Éè±¸´«µİ¿ªÊ¼Î»ºÍ´ÓÉè±¸µØÖ·¡£ 
static void s3c24xx_i2c_message_start(struct s3c24xx_i2c *i2c,
				      struct i2c_msg *msg)
{
	unsigned int addr = (msg->addr & 0x7f) << 1;
	unsigned long stat;
	unsigned long iiccon;

	stat = 0;
	stat |=  S3C2410_IICSTAT_TXRXEN;

	if (msg->flags & I2C_M_RD) {
		stat |= S3C2410_IICSTAT_MASTER_RX;
		addr |= 1;
	} else
		stat |= S3C2410_IICSTAT_MASTER_TX;

	if (msg->flags & I2C_M_REV_DIR_ADDR)
		addr ^= 1;

	/* todo - check for wether ack wanted or not */
	s3c24xx_i2c_enable_ack(i2c);//Èç¹ûÒªÊ¹ÄÜACK£¬ÔòÊ¹ÄÜ 

	iiccon = readl(i2c->regs + S3C2410_IICCON);
	writel(stat, i2c->regs + S3C2410_IICSTAT);

	dev_dbg(i2c->dev, "START: %08lx to IICSTAT, %02x to DS\n", stat, addr);
	writeb(addr, i2c->regs + S3C2410_IICDS);

	/* delay here to ensure the data byte has gotten onto the bus
	 * before the transaction is started */

	ndelay(i2c->tx_setup);

	dev_dbg(i2c->dev, "iiccon, %08lx\n", iiccon);
	writel(iiccon, i2c->regs + S3C2410_IICCON);

	stat |= S3C2410_IICSTAT_START;
	writel(stat, i2c->regs + S3C2410_IICSTAT);
}

/* s3c24xx_i2c_master_complete
 *
 * complete the message and wake up the caller, using the given return code,
 * or zero to mean ok.
*/
static inline void s3c24xx_i2c_master_complete(struct s3c24xx_i2c *i2c, int ret)
{//I2C´«ÊäÍê³É£¬±»s3c24xx_i2c_stopµ÷ÓÃ
	dev_dbg(i2c->dev, "master_complete %d\n", ret);

	i2c->msg_ptr = 0;
	i2c->msg = NULL;
	i2c->msg_idx++;
	i2c->msg_num = 0;
	if (ret)
		i2c->msg_idx = ret;

	wake_up(&i2c->wait);
}
static inline void s3c24xx_i2c_stop(struct s3c24xx_i2c *i2c, int ret)
{
	unsigned long iicstat = readl(i2c->regs + S3C2410_IICSTAT);

	dev_dbg(i2c->dev, "STOP\n");

	/* stop the transfer */
	iicstat &= ~S3C2410_IICSTAT_START;
	writel(iicstat, i2c->regs + S3C2410_IICSTAT);

	i2c->state = STATE_STOP;

	s3c24xx_i2c_master_complete(i2c, ret);
	s3c24xx_i2c_disable_irq(i2c);
}

/* helper functions to determine the current state in the set of
 * messages we are sending */

/* is_lastmsg()
 *
// * returns TRUE if the current message is the last in the set =======ÅĞ¶ÏÊÇ·ñÎªÏûÏ¢¼¯ÖĞµÄ×îºóÒ»¸öÏûÏ¢
*/

static inline int is_lastmsg(struct s3c24xx_i2c *i2c)
{
	return i2c->msg_idx >= (i2c->msg_num - 1);
}

/* is_msglast
 *
// * returns TRUE if we this is the last byte in the current message========ÅĞ¶ÏÊÇ·ñÎªÄ¿Ç°µÄÏûÏ¢µÄ×îºóÒ»¸ö×Ö½Ú
*/

static inline int is_msglast(struct s3c24xx_i2c *i2c)
{
	return i2c->msg_ptr == i2c->msg->len-1;
}

/* is_msgend
 *
// * returns TRUE if we reached the end of the current message===========ÅĞ¶ÏÊÇ·ñµ½´ïÏûÏ¢µÄ½áÎ²
*/

static inline int is_msgend(struct s3c24xx_i2c *i2c)
{
	return i2c->msg_ptr >= i2c->msg->len;
}

/* i2c_s3c_irq_nextbyte
 *
 * process an interrupt and work out what to do
 */
//ÖĞ¶Ï´¦Àíº¯Êıs3c24xx_i2c_irq()Ö÷ÒªÍ¨¹ıµ÷ÓÃi2s_s3c_irq_nextbyte()º¯Êı½øĞĞ´«Êä
//¹¤×÷µÄ½øÒ»²½ÍÆ½ø¡£i2s_s3c_irq_nextbyte()º¯ÊıÍ¨¹ı switch(i2c->state)Óï¾ä·Ö³É
//i2c->state µÄ²»Í¬×´Ì¬½øĞĞ´¦Àí£¬ÔÚÃ¿ÖÖ×´Ì¬ÏÂ£¬ÏÈ¼ì²é i2c->state µÄ×´Ì¬ÓëÓ²¼ş¼Ä´æ
//Æ÷Ó¦¸Ã´¦ÓÚµÄ×´Ì¬ÊÇ·ñÒ»ÖÂ£¬Èç¹û²»Ò»ÖÂ£¬ÔòÖ¤Ã÷ÓĞÎó£¬Ö±½Ó·µ»Ø¡£µ± I2C´¦ÓÚ¶Á×´
//Ì¬STATE_READ »òĞ´×´Ì¬STATE_WRITE Ê±£¬Í¨¹ı is_lastmsg()º¯ÊıÅĞ¶ÏÊÇ·ñ´«ÊäµÄ
//ÊÇ×îºóÒ»ÌõI2CÏûÏ¢£¬Èç¹ûÊÇ£¬Ôò²úÉúÍ£Ö¹Î»£¬·ñÔòÍ¨¹ı i2c->msg_idx++¡¢i2c->msg++
//ÍÆ½øµ½ÏÂÒ»ÌõÏûÏ¢¡£
static int i2c_s3c_irq_nextbyte(struct s3c24xx_i2c *i2c, unsigned long iicstat)
{
	unsigned long tmp;
	unsigned char byte;
	int ret = 0;

	switch (i2c->state) {

	case STATE_IDLE:
		dev_err(i2c->dev, "%s: called in STATE_IDLE\n", __func__);
		goto out;
		break;

	case STATE_STOP:
		dev_err(i2c->dev, "%s: called in STATE_STOP\n", __func__);
		s3c24xx_i2c_disable_irq(i2c);
		goto out_ack;

	case STATE_START:
		/* last thing we did was send a start condition on the
		 * bus, or started a new i2c message
		 */
		  // ÎÒÃÇ×î½ü×öµÄÒ»¼şÊÂÊÇÆô¶¯Ò»¸öĞÂI2CÏûÏ¢ 
		if (iicstat & S3C2410_IICSTAT_LASTBIT &&
		    !(i2c->msg->flags & I2C_M_IGNORE_NAK)) {
			/* ack was not received... */
			 // Ã»ÓĞÊÕµ½ACK  
			dev_dbg(i2c->dev, "ack was not received\n");
			s3c24xx_i2c_stop(i2c, -ENXIO);
			goto out_ack;
		}

		if (i2c->msg->flags & I2C_M_RD)
			i2c->state = STATE_READ;
		else
			i2c->state = STATE_WRITE;

		/* terminate the transfer if there is nothing to do
		 * as this is used by the i2c probe to find devices. */
		 // ½öÒ»ÌõÏûÏ¢£¬¶øÇÒ³¤¶ÈÎª0£¨Ö÷ÒªÓÃÓÚÊÊÅäÆ÷Ì½²â£©£¬·¢ËÍÍ£Ö¹Î» 
		if (is_lastmsg(i2c) && i2c->msg->len == 0) {
			s3c24xx_i2c_stop(i2c, 0);
			goto out_ack;
		}

		if (i2c->state == STATE_READ)
			goto prepare_read;

		/* fall through to the write state, as we will need to
		 * send a byte as well */

	case STATE_WRITE: // ½øÈëĞ´×´Ì¬  
		/* we are writing data to the device... check for the
		 * end of the message, and if so, work out what to do
		 */

		if (!(i2c->msg->flags & I2C_M_IGNORE_NAK)) {
			if (iicstat & S3C2410_IICSTAT_LASTBIT) {
				dev_dbg(i2c->dev, "WRITE: No Ack\n");

				s3c24xx_i2c_stop(i2c, -ECONNREFUSED);
				goto out_ack;
			}
		}

 retry_write:

		if (!is_msgend(i2c)) {
			byte = i2c->msg->buf[i2c->msg_ptr++];
			writeb(byte, i2c->regs + S3C2410_IICDS);

			/* delay after writing the byte to allow the
			 * data setup time on the bus, as writing the
			 * data to the register causes the first bit
			 * to appear on SDA, and SCL will change as
			 * soon as the interrupt is acknowledged */

			ndelay(i2c->tx_setup);

		} else if (!is_lastmsg(i2c)) {
			/* we need to go to the next i2c message */

			dev_dbg(i2c->dev, "WRITE: Next Message\n");
			 // ÍÆ½øµ½ÏÂÒ»ÌõÏûÏ¢  
			i2c->msg_ptr = 0;
			i2c->msg_idx++;
			i2c->msg++;

			/* check to see if we need to do another message */
			  // ¼ì²éÊÇ·ñÒªÎª¸ÃÏûÏ¢²úÉú¿ªÊ¼Î»  
			if (i2c->msg->flags & I2C_M_NOSTART) {

				if (i2c->msg->flags & I2C_M_RD) {
					/* cannot do this, the controller
					 * forces us to send a new START
					 * when we change direction */

					s3c24xx_i2c_stop(i2c, -EINVAL);
				}

				goto retry_write;
			} else {
				/* send the new start */
				 // ·¢ËÍĞÂµÄ¿ªÊ¼Î»  // send the new start 
				s3c24xx_i2c_message_start(i2c, i2c->msg);
				i2c->state = STATE_START;
			}

		} else {
			/* send stop */

			s3c24xx_i2c_stop(i2c, 0);
		}
		break;

	case STATE_READ: // ÓĞÒ»¸ö×Ö½Ú¿É¶Á£¬¿´ÊÇ·ñ»¹ÓĞÏûÏ¢Òª´¦Àí    
		/* we have a byte of data in the data register, do
		 * something with it, and then work out wether we are
		 * going to do any more read/write
		 */

		byte = readb(i2c->regs + S3C2410_IICDS);
		i2c->msg->buf[i2c->msg_ptr++] = byte;

 prepare_read:
		if (is_msglast(i2c)) {
			/* last byte of buffer */

			if (is_lastmsg(i2c))
				s3c24xx_i2c_disable_ack(i2c);

		} else if (is_msgend(i2c)) {
			/* ok, we've read the entire buffer, see if there
			 * is anything else we need to do */
			// »¹ÓĞÏûÏ¢Òª´¦ÀíÂğ?  
			if (is_lastmsg(i2c)) {
				/* last message, send stop and complete */
				dev_dbg(i2c->dev, "READ: Send Stop\n");

				s3c24xx_i2c_stop(i2c, 0);
			} else {// ÍÆ½øµ½ÏÂÒ»ÌõÏûÏ¢  
				/* go to the next transfer */
				dev_dbg(i2c->dev, "READ: Next Transfer\n");

				i2c->msg_ptr = 0;
				i2c->msg_idx++;
				i2c->msg++;
			}
		}

		break;
	}

	/* acknowlegde the IRQ and get back on with the work */

 out_ack: // irqÇå³ı  
	tmp = readl(i2c->regs + S3C2410_IICCON);
	tmp &= ~S3C2410_IICCON_IRQPEND;
	writel(tmp, i2c->regs + S3C2410_IICCON);
 out:
	return ret;
}

/* s3c24xx_i2c_irq
 *
// * top level IRQ servicing routine===========¶¥²ãÖĞ¶Ï·şÎñ³ÌĞò
//ÖĞ¶Ï´¦Àíº¯Êıs3c24xx_i2c_irq()Ö÷ÒªÍ¨¹ıµ÷ÓÃi2s_s3c_irq_nextbyte()º¯Êı½øĞĞ´«Êä
//¹¤×÷µÄ½øÒ»²½ÍÆ½ø¡£i2s_s3c_irq_nextbyte()º¯ÊıÍ¨¹ı switch(i2c->state)Óï¾ä·Ö³É
//i2c->state µÄ²»Í¬×´Ì¬½øĞĞ´¦Àí£¬ÔÚÃ¿ÖÖ×´Ì¬ÏÂ£¬ÏÈ¼ì²é i2c->state µÄ×´Ì¬ÓëÓ²¼ş¼Ä´æ
//Æ÷Ó¦¸Ã´¦ÓÚµÄ×´Ì¬ÊÇ·ñÒ»ÖÂ£¬Èç¹û²»Ò»ÖÂ£¬ÔòÖ¤Ã÷ÓĞÎó£¬Ö±½Ó·µ»Ø¡£µ± I2C´¦ÓÚ¶Á×´
//Ì¬STATE_READ »òĞ´×´Ì¬STATE_WRITE Ê±£¬Í¨¹ı is_lastmsg()º¯ÊıÅĞ¶ÏÊÇ·ñ´«ÊäµÄ
//ÊÇ×îºóÒ»ÌõI2CÏûÏ¢£¬Èç¹ûÊÇ£¬Ôò²úÉúÍ£Ö¹Î»£¬·ñÔòÍ¨¹ı i2c->msg_idx++¡¢i2c->msg++
//ÍÆ½øµ½ÏÂÒ»ÌõÏûÏ¢¡£ 

ÖĞ¶ÏÀ´È·¶¨µ±Ç°Êı¾İ·¢ËÍÍê³É¡£CPU½ÓÊÕÖĞ¶ÏÇëÇóºó£¬Ëü½«ĞÂµÄÊı¾İĞ´Èëµ½IICDS¼Ä´æÆ÷¡£
±£³ÖÖĞ¶ÏÀ´È·ÈÏĞÂµÄÊı¾İ½ÓÊÕÍê³É¡£CPU½ÓÊÕµ½ÖĞ¶ÏÇëÇóºó,Ëü´ÓIICDS¼Ä´æÆ÷¶ÁÈ¡Êı¾İ¡£*/
static irqreturn_t s3c24xx_i2c_irq(int irqno, void *dev_id)
{
	struct s3c24xx_i2c *i2c = dev_id;
	unsigned long status;
	unsigned long tmp;

	status = readl(i2c->regs + S3C2410_IICSTAT);

	if (status & S3C2410_IICSTAT_ARBITR) {
		/* deal with arbitration loss */
		dev_err(i2c->dev, "deal with arbitration loss\n");
	}

	if (i2c->state == STATE_IDLE) {
		dev_dbg(i2c->dev, "IRQ: error i2c->state == IDLE\n");

		tmp = readl(i2c->regs + S3C2410_IICCON);
		tmp &= ~S3C2410_IICCON_IRQPEND;
		writel(tmp, i2c->regs +  S3C2410_IICCON);
		goto out;
	}

	/* pretty much this leaves us with the fact that we've
	 * transmitted or received whatever byte we last sent */

	i2c_s3c_irq_nextbyte(i2c, status);

 out:
	return IRQ_HANDLED;
}


/* s3c24xx_i2c_set_master
 *
 * get the i2c bus for a master transaction==========Îª¿ØÖÆÆ÷´«Êä»ñÈ¡Ò»¸öI2C×ÜÏß£¬±»s3c24xx_i2c_doxferµ÷ÓÃ
*/
static int s3c24xx_i2c_set_master(struct s3c24xx_i2c *i2c)
{
	unsigned long iicstat;
	int timeout = 400;

	while (timeout-- > 0) {
		iicstat = readl(i2c->regs + S3C2410_IICSTAT);

		if (!(iicstat & S3C2410_IICSTAT_BUSBUSY))
			return 0;

		msleep(1);
	}

	writel(iicstat & ~S3C2410_IICSTAT_TXRXEN, i2c->regs + S3C2410_IICSTAT);
	if (!(readl(i2c->regs + S3C2410_IICSTAT) & S3C2410_IICSTAT_BUSBUSY))
		return 0;

	return -ETIMEDOUT;
}

/* s3c24xx_i2c_doxfer
*this starts an i2c transfer===========¿ªÊ¼I2C´«Êä£¬±»s3c24xx_i2c_xferµ÷ÓÃ
 * this starts an i2c transfer
*/
//s3c24xx_i2c_doxfer()Ê×ÏÈ½« S3C2410 µÄ I C ÊÊÅäÆ÷ÉèÖÃÎª I C Ö÷Éè±¸£¬Æäºó³õÊ¼
//»¯ s3c24xx_i2c ½á¹¹Ìå£¬Ê¹ÄÜ I2C ÖĞ¶Ï£¬²¢µ÷ÓÃ s3c24xx_i2c_message_start()º¯ÊıÆô¶¯
//I2CÏûÏ¢µÄ´«Êä¡£ 
static int s3c24xx_i2c_doxfer(struct s3c24xx_i2c *i2c,
			      struct i2c_msg *msgs, int num)
{
	unsigned long timeout;
	int ret;

	if (i2c->suspended)
		return -EIO;

	ret = s3c24xx_i2c_set_master(i2c);
	if (ret != 0) {
		dev_err(i2c->dev, "cannot get bus (error %d)\n", ret);
		ret = -EAGAIN;
		goto out;
	}

	spin_lock_irq(&i2c->lock);

	i2c->msg     = msgs;
	i2c->msg_num = num;
	i2c->msg_ptr = 0;
	i2c->msg_idx = 0;
	i2c->state   = STATE_START;

	s3c24xx_i2c_enable_irq(i2c);
	s3c24xx_i2c_message_start(i2c, msgs);
	spin_unlock_irq(&i2c->lock);

	timeout = wait_event_timeout(i2c->wait, i2c->msg_num == 0, HZ * 5);

	ret = i2c->msg_idx;

	/* having these next two as dev_err() makes life very
	 * noisy when doing an i2cdetect */

	if (timeout == 0)
		dev_dbg(i2c->dev, "timeout\n");
	else if (ret != num)
		dev_dbg(i2c->dev, "incomplete xfer (%d)\n", ret);

	/* ensure the stop has been through the bus */

	udelay(10);

 out:
	return ret;
}

/* s3c24xx_i2c_xfer
 *
 * first port of call from the i2c bus code when an message needs
 * transferring across the i2c bus.
//ÊµÏÖ IIC ×ÜÏßÊı¾İµÄ·¢ËÍºÍ½ÓÊÕ¡============================Ö÷½Ó¿Úº¯Êı£*/
//I2C×ÜÏßÍ¨ĞÅ´«Êäº¯Êı s3c24xx_i2c_xfer()£¬Õâ¸ö
//º¯Êı·Ç³£¹Ø¼ü£¬ËùÓĞ I2C ×ÜÏßÉÏ¶ÔÉè±¸µÄ·ÃÎÊ×îÖÕÓ¦¸ÃÓÉËüÀ´Íê³É£¬
static int s3c24xx_i2c_xfer(struct i2c_adapter *adap,
			struct i2c_msg *msgs, int num)
{
	struct s3c24xx_i2c *i2c = (struct s3c24xx_i2c *)adap->algo_data;
	int retry;
	int ret;

	clk_enable(i2c->clk);

	for (retry = 0; retry < adap->retries; retry++) {
		//Êıµ÷ÓÃ s3c24xx_i2c_doxfer()º¯Êı´«Êä I2C ÏûÏ¢
		ret = s3c24xx_i2c_doxfer(i2c, msgs, num);

		if (ret != -EAGAIN)
			goto out;

		dev_dbg(i2c->dev, "Retrying transmission (%d)\n", retry);

		udelay(100);
	}
	ret = -EREMOTEIO;
out:
	clk_disable(i2c->clk);

	return ret;
}

/* declare our i2c functionalityÓÃÓÚ·µ»ØalgorithmËùÖ§³ÖµÄÍ¨ĞÅĞ­Òé */
static u32 s3c24xx_i2c_func(struct i2c_adapter *adap)
{
	return I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL | I2C_FUNC_PROTOCOL_MANGLING;
}

/* i2c bus registration info =======£¨ÔÚÕâ¸ö×ÜÏßÇı¶¯ÖĞÒÑ¾­ÊµÏÖÁËÊÊÅäÆ÷ÁË£©*/
//IIC ×ÜÏßÍ¨ĞÅ´«ÊäËã·¨£¬¹ÜÀí IIC ¿ØÖÆÆ÷£¬ÊµÏÖ IIC ×ÜÏßÊı¾İµÄ·¢ËÍºÍ½ÓÊÕ¡£ 
static const struct i2c_algorithm s3c24xx_i2c_algorithm = {//==========×ÜÏßÍ¨ĞÅ·½·¨½á¹¹Ìå,Õë¶Ô2410
	.master_xfer		= s3c24xx_i2c_xfer,//ÊµÏÖ IIC ×ÜÏßÊı¾İµÄ·¢ËÍºÍ½ÓÊÕ¡£
	.functionality		= s3c24xx_i2c_func,//ÓÃÓÚ·µ»ØalgorithmËùÖ§³ÖµÄÍ¨ĞÅĞ­Òé
};

/* s3c24xx_i2c_calcdivisor
 *
 * return the divisor settings for a given frequency================»ñÈ¡·ÖÆµÒò×Ó
*/
static int s3c24xx_i2c_calcdivisor(unsigned long clkin, unsigned int wanted,
				   unsigned int *div1, unsigned int *divs)
{
	unsigned int calc_divs = clkin / wanted;
	unsigned int calc_div1;

	if (calc_divs > (16*16))
		calc_div1 = 512;
	else
		calc_div1 = 16;

	calc_divs += calc_div1-1;
	calc_divs /= calc_div1;

	if (calc_divs == 0)
		calc_divs = 1;
	if (calc_divs > 17)
		calc_divs = 17;

	*divs = calc_divs;
	*div1 = calc_div1;

	return clkin / (calc_divs * calc_div1);
}

/* s3c24xx_i2c_clockrate
 *
 * work out a divisor for the user requested frequency setting,
 * either by the requested frequency, or scanning the acceptable
 * range of frequencies until something is found
*/
static int s3c24xx_i2c_clockrate(struct s3c24xx_i2c *i2c, unsigned int *got)
{//ÉèÖÃÊ±ÖÓÆµÂÊ
	struct s3c2410_platform_i2c *pdata = i2c->dev->platform_data;
	unsigned long clkin = clk_get_rate(i2c->clk);
	unsigned int divs, div1;
	unsigned long target_frequency;
	u32 iiccon;
	int freq;

	i2c->clkrate = clkin;
	clkin /= 1000;		/* clkin now in KHz */

	dev_dbg(i2c->dev, "pdata desired frequency %lu\n", pdata->frequency);

	target_frequency = pdata->frequency ? pdata->frequency : 100000;

	target_frequency /= 1000; /* Target frequency now in KHz */

	freq = s3c24xx_i2c_calcdivisor(clkin, target_frequency, &div1, &divs);

	if (freq > target_frequency) {
		dev_err(i2c->dev,
			"Unable to achieve desired frequency %luKHz."	\
			" Lowest achievable %dKHz\n", target_frequency, freq);
		return -EINVAL;
	}

	*got = freq;

	iiccon = readl(i2c->regs + S3C2410_IICCON);
	iiccon &= ~(S3C2410_IICCON_SCALEMASK | S3C2410_IICCON_TXDIV_512);
	iiccon |= (divs-1);

	if (div1 == 512)
		iiccon |= S3C2410_IICCON_TXDIV_512;

	writel(iiccon, i2c->regs + S3C2410_IICCON);

	return 0;
}

#ifdef CONFIG_CPU_FREQ

#define freq_to_i2c(_n) container_of(_n, struct s3c24xx_i2c, freq_transition)

static int s3c24xx_i2c_cpufreq_transition(struct notifier_block *nb,
					  unsigned long val, void *data)
{//µ÷ÕûÊ±ÖÓÆµÂÊ
	struct s3c24xx_i2c *i2c = freq_to_i2c(nb);
	unsigned long flags;
	unsigned int got;
	int delta_f;
	int ret;

	clk_enable(i2c->clk);

	delta_f = clk_get_rate(i2c->clk) - i2c->clkrate;

	/* if we're post-change and the input clock has slowed down
	 * or at pre-change and the clock is about to speed up, then
	 * adjust our clock rate. <0 is slow, >0 speedup.
	 */

	if ((val == CPUFREQ_POSTCHANGE && delta_f < 0) ||
	    (val == CPUFREQ_PRECHANGE && delta_f > 0)) {
		spin_lock_irqsave(&i2c->lock, flags);
		ret = s3c24xx_i2c_clockrate(i2c, &got);
		spin_unlock_irqrestore(&i2c->lock, flags);

		if (ret < 0)
			dev_err(i2c->dev, "cannot find frequency\n");
		else
			dev_info(i2c->dev, "setting freq %d\n", got);
	}

	clk_disable(i2c->clk);

	return 0;
}

static inline int s3c24xx_i2c_register_cpufreq(struct s3c24xx_i2c *i2c)
{
	i2c->freq_transition.notifier_call = s3c24xx_i2c_cpufreq_transition;

	return cpufreq_register_notifier(&i2c->freq_transition,
					 CPUFREQ_TRANSITION_NOTIFIER);
}

static inline void s3c24xx_i2c_deregister_cpufreq(struct s3c24xx_i2c *i2c)
{
	cpufreq_unregister_notifier(&i2c->freq_transition,
				    CPUFREQ_TRANSITION_NOTIFIER);
}

#else
static inline int s3c24xx_i2c_register_cpufreq(struct s3c24xx_i2c *i2c)
{
	return 0;
}

static inline void s3c24xx_i2c_deregister_cpufreq(struct s3c24xx_i2c *i2c)
{
}
#endif

/* s3c24xx_i2c_init
 *
 * initialise the controller, set the IO lines and frequency
*/

static int s3c24xx_i2c_init(struct s3c24xx_i2c *i2c)
{
	unsigned long iicon = S3C2410_IICCON_IRQEN | S3C2410_IICCON_ACKEN;
	struct s3c2410_platform_i2c *pdata;
	unsigned int freq;

	/* get the plafrom data */

	pdata = i2c->dev->platform_data;

	/* inititalise the gpio */

	if (pdata->cfg_gpio)
		pdata->cfg_gpio(to_platform_device(i2c->dev));

	/* write slave address */

	writeb(pdata->slave_addr, i2c->regs + S3C2410_IICADD);

	dev_dbg(i2c->dev, "slave address 0x%02x\n", pdata->slave_addr);

	writel(iicon, i2c->regs + S3C2410_IICCON);

	/* we need to work out the divisors for the clock... */

	if (s3c24xx_i2c_clockrate(i2c, &freq) != 0) {
		writel(0, i2c->regs + S3C2410_IICCON);
		dev_err(i2c->dev, "cannot meet bus frequency required\n");
		return -EINVAL;
	}

	/* todo - check that the i2c lines aren't being dragged anywhere */

	dev_dbg(i2c->dev, "bus frequency set to %d KHz\n", freq);
	dev_dbg(i2c->dev, "S3C2410_IICCON=0x%02lx\n", iicon);

	dev_dbg(i2c->dev, "S3C2440_IICLC=%08x\n", pdata->sda_delay);
	writel(pdata->sda_delay, i2c->regs + S3C2440_IICLC);

	return 0;
}

/* s3c24xx_i2c_probe
 *
 * called by the bus driver when a suitable device is found
*/
//Ö÷Ìå¹¤×÷ÊÇÊ¹ÄÜÓ²¼ş²¢ÉêÇë I2CÊÊÅäÆ÷Ê¹ÓÃµÄ I/O µØÖ·¡¢ÖĞ¶ÏºÅµÈ£¬
//ÔÚÕâĞ©¹¤×÷¶¼Íê³ÉÎŞÎóºó£¬Í¨¹ı I2C ºËĞÄÌá¹©µÄ i2c_add_adapter()º¯ÊıÌí¼ÓÕâ¸öÊÊÅä
//Æ÷¡£ÒòÎª S3C2410 ÄÚ²¿¼¯³É I2C ¿ØÖÆÆ÷£¬¿ÉÒÔÈ·¶¨ I2C ÊÊÅäÆ÷Ò»¶¨´æÔÚ£¬
//s3c24xx_i2c_probe()º¯ÊıËäÈ»ÃüÃû¡°Ì½²â¡± £¬µ«Êµ¼ÊÃ»ÓĞÒ²²»±Ø½øĞĞÈÎºÎÌ½²â¹¤×÷£¬Ö®
//ËùÒÔÕâÑùÃüÃûÍêÈ«ÊÇÒ»ÖÖÉè¼ÆÏ°¹ß¡£ 

static int s3c24xx_i2c_probe(struct platform_device *pdev)
{
	struct s3c24xx_i2c *i2c;
	struct s3c2410_platform_i2c *pdata;
	struct resource *res;
	int ret;

	pdata = pdev->dev.platform_data;
	if (!pdata) {
		dev_err(&pdev->dev, "no platform data\n");
		return -EINVAL;
	}

	i2c = kzalloc(sizeof(struct s3c24xx_i2c), GFP_KERNEL);
	if (!i2c) {
		dev_err(&pdev->dev, "no memory for state\n");
		return -ENOMEM;
	}

	strlcpy(i2c->adap.name, "s3c2410-i2c", sizeof(i2c->adap.name));
	i2c->adap.owner   = THIS_MODULE;
	i2c->adap.algo    = &s3c24xx_i2c_algorithm;//£¬IIC ×ÜÏßÍ¨ĞÅ´«ÊäËã·¨£¬¹ÜÀí IIC ¿ØÖÆÆ÷£¬ÊµÏÖ IIC ×ÜÏßÊı¾İµÄ·¢ËÍºÍ½ÓÊÕ¡£ 
	i2c->adap.retries = 2;
	i2c->adap.class   = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	i2c->tx_setup     = 50;

	spin_lock_init(&i2c->lock);
	init_waitqueue_head(&i2c->wait);

	/* find the clock and enable it */

	i2c->dev = &pdev->dev;
	i2c->clk = clk_get(&pdev->dev, "i2c");

	if (IS_ERR(i2c->clk)) {
		dev_err(&pdev->dev, "cannot get clock\n");
		ret = -ENOENT;
		goto err_noclk;
	}

	dev_dbg(&pdev->dev, "clock source %p\n", i2c->clk);

	clk_enable(i2c->clk);

	/* map the registers Ó³Éä¼Ä´æÆ÷£¬´ÓÎïÀí¿Õ¼äÓ³Éäµ½ĞéÄâ¿Õ¼ä*/

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "cannot find IO resource\n");
		ret = -ENOENT;
		goto err_clk;
	}

	i2c->ioarea = request_mem_region(res->start, resource_size(res),
					 pdev->name);

	if (i2c->ioarea == NULL) {
		dev_err(&pdev->dev, "cannot request IO\n");
		ret = -ENXIO;
		goto err_clk;
	}

	i2c->regs = ioremap(res->start, resource_size(res));

	if (i2c->regs == NULL) {
		dev_err(&pdev->dev, "cannot map IO\n");
		ret = -ENXIO;
		goto err_ioarea;
	}

	dev_dbg(&pdev->dev, "registers %p (%p, %p)\n",
		i2c->regs, i2c->ioarea, res);

	/* setup info block for the i2c core */
	 // ÉèÖÃI2CµÄĞÅÏ¢¿é  
	i2c->adap.algo_data = i2c;
	i2c->adap.dev.parent = &pdev->dev;

	/* initialise the i2c controller³õÊ¼»¯ IIC ¿ØÖÆÆ÷ */

	ret = s3c24xx_i2c_init(i2c);
	if (ret != 0)
		goto err_iomap;

	/* find the IRQ for this unit (note, this relies on the init call to
	 * ensure no current IRQs pending
	 */
	i2c->irq = ret = platform_get_irq(pdev, 0);
	if (ret <= 0) {
		dev_err(&pdev->dev, "cannot find IRQ\n");
		goto err_iomap;
	}
//ÏòÏµÍ³ÉêÇëÖĞ¶Ï£¬ÖĞ¶Ï´¦Àíº¯ÊıÎª s3c24xx_i2c_irq¡£
	ret = request_irq(i2c->irq, s3c24xx_i2c_irq, IRQF_DISABLED,
			  dev_name(&pdev->dev), i2c);

	if (ret != 0) {
		dev_err(&pdev->dev, "cannot claim IRQ %d\n", i2c->irq);
		goto err_iomap;
	}

	ret = s3c24xx_i2c_register_cpufreq(i2c);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to register cpufreq notifier\n");
		goto err_irq;
	}

	/* Note, previous versions of the driver used i2c_add_adapter()
	 * to add the bus at any number. We now pass the bus number via
	 * the platform data, so if unset it will now default to always
	 * being bus 0.
	 */

	i2c->adap.nr = pdata->bus_num;

	ret = i2c_add_numbered_adapter(&i2c->adap);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to add bus to i2c core\n");
		goto err_cpufreq;
	}

	platform_set_drvdata(pdev, i2c);

	clk_disable(i2c->clk);

	dev_info(&pdev->dev, "%s: S3C I2C adapter\n", dev_name(&i2c->adap.dev));
	return 0;

 err_cpufreq:
	s3c24xx_i2c_deregister_cpufreq(i2c);

 err_irq:
	free_irq(i2c->irq, i2c);

 err_iomap:
	iounmap(i2c->regs);

 err_ioarea:
	release_resource(i2c->ioarea);
	kfree(i2c->ioarea);

 err_clk:
	clk_disable(i2c->clk);
	clk_put(i2c->clk);

 err_noclk:
	kfree(i2c);
	return ret;
}

/* s3c24xx_i2c_remove
 *
 * called when device is removed from the bus
*/

static int s3c24xx_i2c_remove(struct platform_device *pdev)
{
	struct s3c24xx_i2c *i2c = platform_get_drvdata(pdev);

	s3c24xx_i2c_deregister_cpufreq(i2c);

	i2c_del_adapter(&i2c->adap);
	free_irq(i2c->irq, i2c);

	clk_disable(i2c->clk);
	clk_put(i2c->clk);

	iounmap(i2c->regs);

	release_resource(i2c->ioarea);
	kfree(i2c->ioarea);
	kfree(i2c);

	return 0;
}

#ifdef CONFIG_PM
static int s3c24xx_i2c_suspend_noirq(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct s3c24xx_i2c *i2c = platform_get_drvdata(pdev);

	i2c->suspended = 1;

	return 0;
}

static int s3c24xx_i2c_resume(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct s3c24xx_i2c *i2c = platform_get_drvdata(pdev);

	i2c->suspended = 0;

	clk_enable(i2c->clk);
	s3c24xx_i2c_init(i2c);
	clk_disable(i2c->clk);

	return 0;
}

static const struct dev_pm_ops s3c24xx_i2c_dev_pm_ops = {
	.suspend_noirq = s3c24xx_i2c_suspend_noirq,
	.resume = s3c24xx_i2c_resume,
};

#define S3C24XX_DEV_PM_OPS (&s3c24xx_i2c_dev_pm_ops)
#else
#define S3C24XX_DEV_PM_OPS NULL
#endif

/* device driver for platform bus bits */

static struct platform_device_id s3c24xx_driver_ids[] = {
	{
		.name		= "s3c2410-i2c",
		.driver_data	= TYPE_S3C2410,
	}, {
		.name		= "s3c2440-i2c",
		.driver_data	= TYPE_S3C2440,
	}, { },
};
MODULE_DEVICE_TABLE(platform, s3c24xx_driver_ids);

static struct platform_driver s3c24xx_i2c_driver = {
	.probe		= s3c24xx_i2c_probe,
	.remove		= s3c24xx_i2c_remove,
	.id_table	= s3c24xx_driver_ids,
	.driver		= {
		.owner	= THIS_MODULE,
		.name	= "s3c-i2c",
		.pm	= S3C24XX_DEV_PM_OPS,
	},
};
//=============================================ZJZ
//I2CÊÊÅäÆ÷Çı¶¯±»×÷ÎªÒ»¸öµ¥¶ÀµÄÄ£¿é¼ÓÔØ½øÄÚºË£¬ÔÚÄ£¿éµÄ¼ÓÔØºÍĞ¶ÔØº¯ÊıÖĞ£¬
//Ö»Ğè×¢²áºÍ×¢ÏúÒ»¸öplatform_driver ½á¹¹Ìå
static int __init i2c_adap_s3c_init(void)
{
	return platform_driver_register(&s3c24xx_i2c_driver);
}
subsys_initcall(i2c_adap_s3c_init);

static void __exit i2c_adap_s3c_exit(void)
{
	platform_driver_unregister(&s3c24xx_i2c_driver);
}
//module_exit(i2c_adap_s3c_exit);

//MODULE_DESCRIPTION("S3C24XX I2C Bus driver");
//MODULE_AUTHOR("Ben Dooks, <ben@simtec.co.uk>");
//MODULE_LICENSE("GPL");
