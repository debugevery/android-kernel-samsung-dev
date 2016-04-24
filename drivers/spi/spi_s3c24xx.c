/* linux/drivers/spi/spi_s3c24xx.c
 * spi_s3c24xx.c是基于s3c24xx下相应的spi接口的控制器驱动程序
 * Copyright (c) 2006 Ben Dooks
 * Copyright 2006-2009 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
2 Linux SPI驱动总体架构
      在2.6的linux内核中，SPI的驱动架构可以分为如下三个层次：SPI 核心层、SPI控制器驱动层和SPI设备驱动层。
      Linux 中SPI驱动代码位于drivers/spi目录。
2.1 SPI核心层
      SPI核心层是Linux的SPI核心部分，提供了核心数据结构的定义、SPI控制器驱动和设备驱动的注册、注销管理等API。其为硬件平台无关层，向下屏蔽了物理总线控制器的差异，定义了统一的访问策略和接口；
      其向上提供了统一的接口，以便SPI设备驱动通过总线控制器进行数据收发。
      Linux中，SPI核心层的代码位于driver/spi/ spi.c。由于该层是平台无关层，本文将不再叙述，有兴趣可以查阅相关资料。
2.2 SPI控制器驱动层
      SPI控制器驱动层，每种处理器平台都有自己的控制器驱动，属于平台移植相关层。它的职责是为系统中每条SPI总线实现相应的读写方法。在物理上，每个SPI控制器可以连接若干个SPI从设备。
      在系统开机时，SPI控制器驱动被首先装载。一个控制器驱动用于支持一条特定的SPI总线的读写。一个控制器驱动可以用数据结构struct spi_master来描述。
2.3 SPI设备驱动层
      SPI设备驱动层为用户接口层，其为用户提供了通过SPI总线访问具体设备的接口。
      SPI设备驱动层可以用两个模块来描述，struct spi_driver和struct spi_device。
      

*/

//#include <linux/init.h>
//#include <linux/spinlock.h>
//#include <linux/workqueue.h>
//#include <linux/interrupt.h>
//#include <linux/delay.h>
//#include <linux/errno.h>
//#include <linux/err.h>
//#include <linux/clk.h>
//#include <linux/platform_device.h>
//#include <linux/gpio.h>
//#include <linux/io.h>
//#include <linux/slab.h>

//#include <linux/spi/spi.h>
//#include <linux/spi/spi_bitbang.h>

//#include <plat/regs-spi.h>
//#include <mach/spi.h>

//#include <plat/fiq.h>
//#include <asm/fiq.h>

//#include "spi_s3c24xx_fiq.h"

/**
 * s3c24xx_spi_devstate - per device data
 * @hz: Last frequency calculated for @sppre field.
 * @mode: Last mode setting for the @spcon field.
 * @spcon: Value to write to the SPCON register.
 * @sppre: Value to write to the SPPRE register.
 */
struct s3c24xx_spi_devstate {
	unsigned int	hz;
	unsigned int	mode;
	u8		spcon;
	u8		sppre;
};

enum spi_fiq_mode {
	FIQ_MODE_NONE	= 0,
	FIQ_MODE_TX	= 1,
	FIQ_MODE_RX	= 2,
	FIQ_MODE_TXRX	= 3,
};

struct s3c24xx_spi {
	/* bitbang has to be first */
	struct spi_bitbang	 bitbang;
	struct completion	 done;

	void __iomem		*regs;
	int			 irq;
	int			 len;
	int			 count;

	struct fiq_handler	 fiq_handler;
	enum spi_fiq_mode	 fiq_mode;
	unsigned char		 fiq_inuse;
	unsigned char		 fiq_claimed;

	void			(*set_cs)(struct s3c2410_spi_info *spi,
					  int cs, int pol);

	/* data buffers */
	const unsigned char	*tx;
	unsigned char		*rx;

	struct clk		*clk;
	struct resource		*ioarea;
	struct spi_master	*master;
	struct spi_device	*curdev;
	struct device		*dev;
	struct s3c2410_spi_info *pdata;
};


#define SPCON_DEFAULT (S3C2410_SPCON_MSTR | S3C2410_SPCON_SMOD_INT)
#define SPPIN_DEFAULT (S3C2410_SPPIN_KEEP)

static inline struct s3c24xx_spi *to_hw(struct spi_device *sdev)
{
	return spi_master_get_devdata(sdev->master);
}

static void s3c24xx_spi_gpiocs(struct s3c2410_spi_info *spi, int cs, int pol)
{
	gpio_set_value(spi->pin_cs, pol);
}

static void s3c24xx_spi_chipsel(struct spi_device *spi, int value)
{
	struct s3c24xx_spi_devstate *cs = spi->controller_state;
	struct s3c24xx_spi *hw = to_hw(spi);
	unsigned int cspol = spi->mode & SPI_CS_HIGH ? 1 : 0;

	/* change the chipselect state and the state of the spi engine clock */

	switch (value) {
	case BITBANG_CS_INACTIVE:/* 禁用spi(禁用片选) */
		hw->set_cs(hw->pdata, spi->chip_select, cspol^1);
		writeb(cs->spcon, hw->regs + S3C2410_SPCON);
		break;

	case BITBANG_CS_ACTIVE:
 /*      * 启用spi：根据需要设置寄存器并启用使能片选     
 * (如果spi_board_info中没有设置相应的mode选项的话，那就只能
 使用默认值SPPIN_DEFAULT和SPCON_DEFAULT了)     */	
		writeb(cs->spcon | S3C2410_SPCON_ENSCK,
		       hw->regs + S3C2410_SPCON);
		hw->set_cs(hw->pdata, spi->chip_select, cspol);
		break;
	}
}

static int s3c24xx_spi_update_state(struct spi_device *spi,
				    struct spi_transfer *t)
{
	struct s3c24xx_spi *hw = to_hw(spi);
	struct s3c24xx_spi_devstate *cs = spi->controller_state;
	unsigned int bpw;
	unsigned int hz;
	unsigned int div;
	unsigned long clk;

	bpw = t ? t->bits_per_word : spi->bits_per_word;
	hz  = t ? t->speed_hz : spi->max_speed_hz;

	if (!bpw)
		bpw = 8;

	if (!hz)
		hz = spi->max_speed_hz;

	if (bpw != 8) {
		dev_err(&spi->dev, "invalid bits-per-word (%d)\n", bpw);
		return -EINVAL;
	}

	if (spi->mode != cs->mode) {
		u8 spcon = SPCON_DEFAULT | S3C2410_SPCON_ENSCK;

		if (spi->mode & SPI_CPHA)
			spcon |= S3C2410_SPCON_CPHA_FMTB;

		if (spi->mode & SPI_CPOL)
			spcon |= S3C2410_SPCON_CPOL_HIGH;

		cs->mode = spi->mode;
		cs->spcon = spcon;
	}

	if (cs->hz != hz) {
		clk = clk_get_rate(hw->clk);
		div = DIV_ROUND_UP(clk, hz * 2) - 1;

		if (div > 255)
			div = 255;

		dev_dbg(&spi->dev, "pre-scaler=%d (wanted %d, got %ld)\n",
			div, hz, clk / (2 * (div + 1)));

		cs->hz = hz;
		cs->sppre = div;
	}

	return 0;
}

static int s3c24xx_spi_setupxfer(struct spi_device *spi,
				 struct spi_transfer *t)
{
	struct s3c24xx_spi_devstate *cs = spi->controller_state;
	struct s3c24xx_spi *hw = to_hw(spi);
	int ret;

	ret = s3c24xx_spi_update_state(spi, t);
	if (!ret)
		writeb(cs->sppre, hw->regs + S3C2410_SPPRE);//设置预分频值

	return ret;
}

static int s3c24xx_spi_setup(struct spi_device *spi)
{
	struct s3c24xx_spi_devstate *cs = spi->controller_state;
	struct s3c24xx_spi *hw = to_hw(spi);
	int ret;

	/* allocate settings on the first call */
	if (!cs) {
		cs = kzalloc(sizeof(struct s3c24xx_spi_devstate), GFP_KERNEL);
		if (!cs) {
			dev_err(&spi->dev, "no memory for controller state\n");
			return -ENOMEM;
		}

		cs->spcon = SPCON_DEFAULT;
		cs->hz = -1;
		spi->controller_state = cs;
	}

	/* initialise the state from the device */
	ret = s3c24xx_spi_update_state(spi, NULL);
	if (ret)
		return ret;

	spin_lock(&hw->bitbang.lock);
	if (!hw->bitbang.busy) {
		hw->bitbang.chipselect(spi, BITBANG_CS_INACTIVE);
		/* need to ndelay for 0.5 clocktick ? */
	}
	spin_unlock(&hw->bitbang.lock);

	return 0;
}

static void s3c24xx_spi_cleanup(struct spi_device *spi)
{
	kfree(spi->controller_state);
}

static inline unsigned int hw_txbyte(struct s3c24xx_spi *hw, int count)
{
	return hw->tx ? hw->tx[count] : 0;
}

#ifdef CONFIG_SPI_S3C24XX_FIQ
/* Support for FIQ based pseudo-DMA to improve the transfer speed.
 *
 * This code uses the assembly helper in spi_s3c24xx_spi.S which is
 * used by the FIQ core to move data between main memory and the peripheral
 * block. Since this is code running on the processor, there is no problem
 * with cache coherency of the buffers, so we can use any buffer we like.
 */

/**
 * struct spi_fiq_code - FIQ code and header
 * @length: The length of the code fragment, excluding this header.
 * @ack_offset: The offset from @data to the word to place the IRQ ACK bit at.
 * @data: The code itself to install as a FIQ handler.
 */
struct spi_fiq_code {
	u32	length;
	u32	ack_offset;
	u8	data[0];
};

extern struct spi_fiq_code s3c24xx_spi_fiq_txrx;
extern struct spi_fiq_code s3c24xx_spi_fiq_tx;
extern struct spi_fiq_code s3c24xx_spi_fiq_rx;

/**
 * ack_bit - turn IRQ into IRQ acknowledgement bit
 * @irq: The interrupt number
 *
 * Returns the bit to write to the interrupt acknowledge register.
 */
static inline u32 ack_bit(unsigned int irq)
{
	return 1 << (irq - IRQ_EINT0);
}

/**
 * s3c24xx_spi_tryfiq - attempt to claim and setup FIQ for transfer
 * @hw: The hardware state.
 *
 * Claim the FIQ handler (only one can be active at any one time) and
 * then setup the correct transfer code for this transfer.
 *
 * This call updates all the necessary state information if successful,
 * so the caller does not need to do anything more than start the transfer
 * as normal, since the IRQ will have been re-routed to the FIQ handler.
*/
void s3c24xx_spi_tryfiq(struct s3c24xx_spi *hw)
{
	struct pt_regs regs;
	enum spi_fiq_mode mode;
	struct spi_fiq_code *code;
	int ret;

	if (!hw->fiq_claimed) {
		/* try and claim fiq if we haven't got it, and if not
		 * then return and simply use another transfer method */

		ret = claim_fiq(&hw->fiq_handler);
		if (ret)
			return;
	}

	if (hw->tx && !hw->rx)
		mode = FIQ_MODE_TX;
	else if (hw->rx && !hw->tx)
		mode = FIQ_MODE_RX;
	else
		mode = FIQ_MODE_TXRX;

	regs.uregs[fiq_rspi] = (long)hw->regs;
	regs.uregs[fiq_rrx]  = (long)hw->rx;
	regs.uregs[fiq_rtx]  = (long)hw->tx + 1;
	regs.uregs[fiq_rcount] = hw->len - 1;
	regs.uregs[fiq_rirq] = (long)S3C24XX_VA_IRQ;

	set_fiq_regs(&regs);

	if (hw->fiq_mode != mode) {
		u32 *ack_ptr;

		hw->fiq_mode = mode;

		switch (mode) {
		case FIQ_MODE_TX:
			code = &s3c24xx_spi_fiq_tx;
			break;
		case FIQ_MODE_RX:
			code = &s3c24xx_spi_fiq_rx;
			break;
		case FIQ_MODE_TXRX:
			code = &s3c24xx_spi_fiq_txrx;
			break;
		default:
			code = NULL;
		}

		BUG_ON(!code);

		ack_ptr = (u32 *)&code->data[code->ack_offset];
		*ack_ptr = ack_bit(hw->irq);

		set_fiq_handler(&code->data, code->length);
	}

	s3c24xx_set_fiq(hw->irq, true);

	hw->fiq_mode = mode;
	hw->fiq_inuse = 1;
}

/**
 * s3c24xx_spi_fiqop - FIQ core code callback
 * @pw: Data registered with the handler
 * @release: Whether this is a release or a return.
 *
 * Called by the FIQ code when another module wants to use the FIQ, so
 * return whether we are currently using this or not and then update our
 * internal state.
 */
static int s3c24xx_spi_fiqop(void *pw, int release)
{
	struct s3c24xx_spi *hw = pw;
	int ret = 0;

	if (release) {
		if (hw->fiq_inuse)
			ret = -EBUSY;

		/* note, we do not need to unroute the FIQ, as the FIQ
		 * vector code de-routes it to signal the end of transfer */

		hw->fiq_mode = FIQ_MODE_NONE;
		hw->fiq_claimed = 0;
	} else {
		hw->fiq_claimed = 1;
	}

	return ret;
}

/**
 * s3c24xx_spi_initfiq - setup the information for the FIQ core
 * @hw: The hardware state.
 *
 * Setup the fiq_handler block to pass to the FIQ core.
 */
static inline void s3c24xx_spi_initfiq(struct s3c24xx_spi *hw)
{
	hw->fiq_handler.dev_id = hw;
	hw->fiq_handler.name = dev_name(hw->dev);
	hw->fiq_handler.fiq_op = s3c24xx_spi_fiqop;
}

/**
 * s3c24xx_spi_usefiq - return if we should be using FIQ.
 * @hw: The hardware state.
 *
 * Return true if the platform data specifies whether this channel is
 * allowed to use the FIQ.
 */
static inline bool s3c24xx_spi_usefiq(struct s3c24xx_spi *hw)
{
	return hw->pdata->use_fiq;
}

/**
 * s3c24xx_spi_usingfiq - return if channel is using FIQ
 * @spi: The hardware state.
 *
 * Return whether the channel is currently using the FIQ (separate from
 * whether the FIQ is claimed).
 */
static inline bool s3c24xx_spi_usingfiq(struct s3c24xx_spi *spi)
{
	return spi->fiq_inuse;
}
#else

static inline void s3c24xx_spi_initfiq(struct s3c24xx_spi *s) { }
static inline void s3c24xx_spi_tryfiq(struct s3c24xx_spi *s) { }
static inline bool s3c24xx_spi_usefiq(struct s3c24xx_spi *s) { return false; }
static inline bool s3c24xx_spi_usingfiq(struct s3c24xx_spi *s) { return false; }

#endif /* CONFIG_SPI_S3C24XX_FIQ */

static int s3c24xx_spi_txrx(struct spi_device *spi, struct spi_transfer *t)
{
	struct s3c24xx_spi *hw = to_hw(spi);
	//将要传输的数据段暂存到 hw->tx或hw->rx 中。
	hw->tx = t->tx_buf;//发送指针
    hw->rx = t->rx_buf;//接收指针
    hw->len = t->len;//需要发送/接收的数据数目
    hw->count = 0;//存放实际spi传输的数据数目

	init_completion(&hw->done);

	hw->fiq_inuse = 0;
	if (s3c24xx_spi_usefiq(hw) && t->len >= 3)
		s3c24xx_spi_tryfiq(hw);

	/* send the first byte */
	writeb(hw_txbyte(hw, 0), hw->regs + S3C2410_SPTDAT);
	 /*         * 非常有意思，这里虽然只发送第一字节，可是中断里会帮你发送完其它的字节(并接收数据)，         
	 * 直到所有的数据发送完毕且所要接收的数据接收完毕(首要)才返回         */
	wait_for_completion(&hw->done);
	return hw->count;
}
//数据传输结束中断
static irqreturn_t s3c24xx_spi_irq(int irq, void *dev)
{
	struct s3c24xx_spi *hw = dev;
	unsigned int spsta = readb(hw->regs + S3C2410_SPSTA);
	unsigned int count = hw->count;

	if (spsta & S3C2410_SPSTA_DCOL) {
		dev_dbg(hw->dev, "data-collision\n");//检测冲突
		complete(&hw->done);
		goto irq_done;
	}

	if (!(spsta & S3C2410_SPSTA_READY)) {//数据准备好。
		dev_dbg(hw->dev, "spi not ready for tx?\n");//设备忙
		complete(&hw->done);
		goto irq_done;
	}

	if (!s3c24xx_spi_usingfiq(hw)) {
		hw->count++;

		if (hw->rx)
			hw->rx[count] = readb(hw->regs + S3C2410_SPRDAT);//接收数据

		count++;

		if (count < hw->len)
			writeb(hw_txbyte(hw, count), hw->regs + S3C2410_SPTDAT);//发送其它数据(或空数据0xFF)
		else
			complete(&hw->done);//发送接收完毕，通知s3c24xx_spi_txrx函数
	} else {
		hw->count = hw->len;
		hw->fiq_inuse = 0;

		if (hw->rx)
			hw->rx[hw->len-1] = readb(hw->regs + S3C2410_SPRDAT);//写入数据。


		complete(&hw->done);
	}

 irq_done:
	return IRQ_HANDLED;
}

static void s3c24xx_spi_initialsetup(struct s3c24xx_spi *hw)
{
	/* for the moment, permanently enable the clock */

	clk_enable(hw->clk);

	/* program defaults into the registers */

	writeb(0xff, hw->regs + S3C2410_SPPRE);
	writeb(SPPIN_DEFAULT, hw->regs + S3C2410_SPPIN);
	writeb(SPCON_DEFAULT, hw->regs + S3C2410_SPCON);

	if (hw->pdata) {
		if (hw->set_cs == s3c24xx_spi_gpiocs)
			gpio_direction_output(hw->pdata->pin_cs, 1);

		if (hw->pdata->gpio_setup)
			hw->pdata->gpio_setup(hw->pdata, 1);
	}
}
//首先从spi驱动的检测函数进行分析.s3c24xx_spi_probe()函数会给spi_master的
//赋setup，transfer等初始化以及数据传输函数，为了能提高spi的传输速度，一般
//会采用DMA模式，最后使用了spi_register_master ()将spi控制器注册到spi core层，
static int __init s3c24xx_spi_probe(struct platform_device *pdev)
{
	struct s3c2410_spi_info *pdata;
	struct s3c24xx_spi *hw;
	struct spi_master *master;
	struct resource *res;
	int err = 0;
 /* pi_alloc_master函数申请了struct spi_master+struct s3c24xx_spi大小的数据，          */ 
 //spi_master代表了一个SPI接口。在一个设备驱动中都有一个与硬件紧密相关的文件，在这样的文件中都有一个
//重要的结构体，在硬件设备工作起来时这个结构体收集相关硬件信息，状态信息，和建立重要结构体等，
//在SPI驱动中在文件linux/drivers/spi/spi_s3c24xx.c中就有这样一个结构体s3c24xx_spi。
//此处便是为结构体spi_master和结构体s3c24xx_spi分配存储空间，并将s3c24xx_spi设为spi_master的drvdata。
	master = spi_alloc_master(&pdev->dev, sizeof(struct s3c24xx_spi));
	if (master == NULL) {
		dev_err(&pdev->dev, "No memory for spi_master\n");
		err = -ENOMEM;
		goto err_nomem;
	}
/* 填充struct spi_master结构 ,spi_master_get_devdata和spi_master_get分别
取出struct s3c24xx_spi和struct spi_master结构指针          */
	hw = spi_master_get_devdata(master);
	memset(hw, 0, sizeof(struct s3c24xx_spi));

	hw->master = spi_master_get(master);
	hw->pdata = pdata = pdev->dev.platform_data; //platform_data是驱动移植时要实现的重要结构体
	hw->dev = &pdev->dev;

	if (pdata == NULL) {
		dev_err(&pdev->dev, "No platform data supplied\n");
		err = -ENOENT;
		goto err_no_pdata;
	}

	platform_set_drvdata(pdev, hw);
	init_completion(&hw->done);

	/* initialise fiq handler */

	s3c24xx_spi_initfiq(hw);

	/* setup the master state. */

	/* the spi->mode bits understood by this driver: */
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	//一个接口对应一个master，一个master对应一条SPI总线，一条总线上可能挂有多个设备，num_chipselect 就表示该总线上的设备
	master->num_chipselect = hw->pdata->num_cs;
	master->bus_num = pdata->bus_num;//master->bus_num记录的是总线号

	/* setup the state for the bitbang driver */
	/* 填充hw->bitbang结构(hw->bitbang结构充当一个中间层，
	相当与input system的input_handle struct) */
	//结构体bitbang中包含了一些硬件操作函数和完成数据传输的工作队列。
	hw->bitbang.master         = hw->master;
	hw->bitbang.setup_transfer = s3c24xx_spi_setupxfer;
	hw->bitbang.chipselect     = s3c24xx_spi_chipsel;
	hw->bitbang.txrx_bufs      = s3c24xx_spi_txrx;

	hw->master->setup  = s3c24xx_spi_setup;
	hw->master->cleanup = s3c24xx_spi_cleanup;

	dev_dbg(hw->dev, "bitbang at %p\n", &hw->bitbang);

	/* find and map our resources */
	 /* 申请spi所用到的资源：io、irq、时钟等 */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "Cannot get IORESOURCE_MEM\n");
		err = -ENOENT;
		goto err_no_iores;
	}

	hw->ioarea = request_mem_region(res->start, resource_size(res),
					pdev->name);

	if (hw->ioarea == NULL) {
		dev_err(&pdev->dev, "Cannot reserve region\n");
		err = -ENXIO;
		goto err_no_iores;
	}

	hw->regs = ioremap(res->start, resource_size(res));
	if (hw->regs == NULL) {
		dev_err(&pdev->dev, "Cannot map IO\n");
		err = -ENXIO;
		goto err_no_iomap;
	}

	hw->irq = platform_get_irq(pdev, 0);
	if (hw->irq < 0) {
		dev_err(&pdev->dev, "No IRQ specified\n");
		err = -ENOENT;
		goto err_no_irq;
	}

	err = request_irq(hw->irq, s3c24xx_spi_irq, 0, pdev->name, hw);
	if (err) {
		dev_err(&pdev->dev, "Cannot claim IRQ\n");
		goto err_no_irq;
	}

	hw->clk = clk_get(&pdev->dev, "spi");
	if (IS_ERR(hw->clk)) {
		dev_err(&pdev->dev, "No clock for device\n");
		err = PTR_ERR(hw->clk);
		goto err_no_clk;
	}

	/* setup any gpio we can */
	/* 片选 */
	if (!pdata->set_cs) {
		if (pdata->pin_cs < 0) {
			dev_err(&pdev->dev, "No chipselect pin\n");
			goto err_register;
		}

		err = gpio_request(pdata->pin_cs, dev_name(&pdev->dev));
		if (err) {
			dev_err(&pdev->dev, "Failed to get gpio for cs\n");
			goto err_register;
		}

		hw->set_cs = s3c24xx_spi_gpiocs;
		gpio_direction_output(pdata->pin_cs, 1);
	} else
		hw->set_cs = pdata->set_cs;

	s3c24xx_spi_initialsetup(hw);

	/* register our spi controller */
	/* 最终通过调用spi_register_master来注册spi控制器(驱动) */
	err = spi_bitbang_start(&hw->bitbang);
	if (err) {
		dev_err(&pdev->dev, "Failed to register SPI master\n");
		goto err_register;
	}

	return 0;

 err_register:
	if (hw->set_cs == s3c24xx_spi_gpiocs)
		gpio_free(pdata->pin_cs);

	clk_disable(hw->clk);
	clk_put(hw->clk);

 err_no_clk:
	free_irq(hw->irq, hw);

 err_no_irq:
	iounmap(hw->regs);

 err_no_iomap:
	release_resource(hw->ioarea);
	kfree(hw->ioarea);

 err_no_iores:
 err_no_pdata:
	spi_master_put(hw->master);

 err_nomem:
	return err;
}

static int __exit s3c24xx_spi_remove(struct platform_device *dev)
{
	struct s3c24xx_spi *hw = platform_get_drvdata(dev);

	platform_set_drvdata(dev, NULL);

	spi_unregister_master(hw->master);

	clk_disable(hw->clk);
	clk_put(hw->clk);

	free_irq(hw->irq, hw);
	iounmap(hw->regs);

	if (hw->set_cs == s3c24xx_spi_gpiocs)
		gpio_free(hw->pdata->pin_cs);

	release_resource(hw->ioarea);
	kfree(hw->ioarea);

	spi_master_put(hw->master);
	return 0;
}


#ifdef CONFIG_PM

static int s3c24xx_spi_suspend(struct device *dev)
{
	struct s3c24xx_spi *hw = platform_get_drvdata(to_platform_device(dev));

	if (hw->pdata && hw->pdata->gpio_setup)
		hw->pdata->gpio_setup(hw->pdata, 0);

	clk_disable(hw->clk);
	return 0;
}

static int s3c24xx_spi_resume(struct device *dev)
{
	struct s3c24xx_spi *hw = platform_get_drvdata(to_platform_device(dev));

	s3c24xx_spi_initialsetup(hw);
	return 0;
}

static const struct dev_pm_ops s3c24xx_spi_pmops = {
	.suspend	= s3c24xx_spi_suspend,
	.resume		= s3c24xx_spi_resume,
};

#define S3C24XX_SPI_PMOPS &s3c24xx_spi_pmops
#else
#define S3C24XX_SPI_PMOPS NULL
#endif /* CONFIG_PM */

//MODULE_ALIAS("platform:s3c2410-spi");
static struct platform_driver s3c24xx_spi_driver = {
	.remove		= __exit_p(s3c24xx_spi_remove),
	.driver		= {
		.name	= "s3c2410-spi",
		.owner	= THIS_MODULE,
		.pm	= S3C24XX_SPI_PMOPS,
	},
};
/* 在内核启动时会调用函数s3c24xx_spi_init()，该函数先创建一个名字为"s3c2410-spi"的workqueue，第二章中提到过spi的数据传输是基于workqueue的，所以这边的初始化函数会首先创建一个workqueue。
   Workqueue创建成功后才会用函数platform_driver_probe()来注册Platform driver，该函数是带有probe函数的平台驱动注册函数，用于非hot-plug设备。
   注册时，会扫描platform bus上的所有设备，由于匹配因子name为" s3c2410-spi "，因此与4.1.1节中注册的Platform device匹配成功，于是函数omap2_mcspi_probe()将被调用，控制器device和driver将被绑定起来。*/
static int __init s3c24xx_spi_init(void)
{
        return platform_driver_probe(&s3c24xx_spi_driver, s3c24xx_spi_probe);
}

static void __exit s3c24xx_spi_exit(void)
{
        platform_driver_unregister(&s3c24xx_spi_driver);
}

//module_init(s3c24xx_spi_init);
//module_exit(s3c24xx_spi_exit);

//MODULE_DESCRIPTION("S3C24XX SPI Driver");
//MODULE_AUTHOR("Ben Dooks, <ben@simtec.co.uk>");
//MODULE_LICENSE("GPL");
