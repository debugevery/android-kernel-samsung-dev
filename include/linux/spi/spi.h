/*
 * Copyright (C) 2005 David Brownell
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
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __LINUX_SPI_H
#define __LINUX_SPI_H

//#include <linux/device.h>
//#include <linux/mod_devicetable.h>
//#include <linux/slab.h>

/*
 * INTERFACES between SPI master-side drivers and SPI infrastructure.
 * (There's no SPI slave support for Linux yet...)
 */
extern struct bus_type spi_bus_type;

/**
 * struct spi_device - Master side proxy for an SPI slave device
 * @dev: Driver model representation of the device.
 * @master: SPI controller used with the device.
 * @max_speed_hz: Maximum clock rate to be used with this chip
 *	(on this board); may be changed by the device's driver.
 *	The spi_transfer.speed_hz can override this for each transfer.
 * @chip_select: Chipselect, distinguishing chips handled by @master.
 * @mode: The spi mode defines how data is clocked out and in.
 *	This may be changed by the device's driver.
 *	The "active low" default for chipselect mode can be overridden
 *	(by specifying SPI_CS_HIGH) as can the "MSB first" default for
 *	each word in a transfer (by specifying SPI_LSB_FIRST).
 * @bits_per_word: Data transfers involve one or more words; word sizes
 *	like eight or 12 bits are common.  In-memory wordsizes are
 *	powers of two bytes (e.g. 20 bit samples use 32 bits).
 *	This may be changed by the device's driver, or left at the
 *	default (0) indicating protocol words are eight bit bytes.
 *	The spi_transfer.bits_per_word can override this for each transfer.
 * @irq: Negative, or the number passed to request_irq() to receive
 *	interrupts from this device.
 * @controller_state: Controller's runtime state
 * @controller_data: Board-specific definitions for controller, such as
 *	FIFO initialization parameters; from board_info.controller_data
 * @modalias: Name of the driver to use with this device, or an alias
 *	for that name.  This appears in the sysfs "modalias" attribute
 *	for driver coldplugging, and in uevents used for hotplugging
 *
 * A @spi_device is used to interchange data between an SPI slave
 * (usually a discrete chip) and CPU memory.
 *
 * In @dev, the platform_data is used to hold information about this
 * device that's meaningful to the device's protocol driver, but not
 * to its controller.  One example might be an identifier for a chip
 * variant with slightly different functionality; another might be
 * information about how this particular board wires the chip's pins.
 1通常来说spi_device对应着SPI总线上某个特定的slave
 2依附于spi总线的设备都会有一个spi_device结构体来描述，结构中定义了设备的片选、模式、速率以及对应主机驱动的spi_master等。
 3而对于要操控的spi总线上的设备，其表述结构为：
 4虽然用户空间不需要直接用到spi_device结构体，但是这个结构体和用户空间的程序有密切的关系，理解它的成员有助于理解SPI设备节点的IOCTL命令，所以首先来介绍它。在内核中，每个spi_device代表一个物理的SPI设备。
*/
struct spi_device {
    struct device       dev;               //内嵌标准device结构体   
    struct spi_master   *master;         //spi主控制器   
    u32         max_speed_hz;              //时钟速率 
    //由于一个SPI总线上可以有多个SPI设备，因此需要片选号来区分它们，SPI控制器根据片选号来选择不同的片选线，从而实现每次只同一个设备通信。
    u8          chip_select;               //设备编号 , 片选号 
    //spi_device的mode成员有两个比特位含义很重要。SPI_CPHA选择对数据线采样的时机，0选择每个时钟周期的第一个沿跳变时采样数据，1选择第二个时钟沿采样数据；SPI_CPOL选择每个时钟周期开始的极性，0表示时钟以低电平开始，1选择高电平开始。这两个比特有四种组合，对应SPI_MODE_0～SPI_MODE_3。
    u8          mode;                      //模式   
#define	SPI_CPHA	0x01			 /* 采样的时钟相位/* clock phase */
#define	SPI_CPOL	0x02			 /* 时钟信号起始相位：高或者是低电平/* clock polarity */
#define	SPI_MODE_0	(0|0)			/* (original MicroWire) */
#define	SPI_MODE_1	(0|SPI_CPHA)
#define	SPI_MODE_2	(SPI_CPOL|0)
#define	SPI_MODE_3	(SPI_CPOL|SPI_CPHA)
#define	SPI_CS_HIGH	0x04			/*为1时片选的有效信号是高电平 chipselect active high? */
#define	SPI_LSB_FIRST	0x08			/*发送时低比特在前 per-word bits-on-wire */
#define	SPI_3WIRE	0x10			/* 输入输出信号使用同一根信号线SI/SO signals shared */
#define	SPI_LOOP	0x20			/* 回环模式loopback mode */
#define	SPI_NO_CS	0x40			/* 1 dev/bus, no chipselect */
#define	SPI_READY	0x80			/* slave pulls low to pause */
//bits_per_word这个成员指定每次读写的字长，单位是比特。虽然大部分SPI接口的字长是8或者16，仍然会有一些特殊的例子。需要说明的是，如果这个成员为零的话，默认使用8作为字长。
    u8          bits_per_word;   /* 每个通信字的字长（比特数）*/                           */
    int         irq;                        //中断号   
    void            *controller_state;        //控制状态   
    void            *controller_data;         //私有数据   
    char            modalias[SPI_NAME_SIZE];  //设备驱动的名字

	/*
	 * likely need more hooks for more protocol options affecting how
	 * the controller talks to each chip, like:
	 *  - memory packing (12 bit samples into low bits, others zeroed)
	 *  - priority
	 *  - drop chipselect after each word
	 *  - chipselect delays
	 *  - ...
	 */
};

static inline struct spi_device *to_spi_device(struct device *dev)
{
	return dev ? container_of(dev, struct spi_device, dev) : NULL;
}

/* most drivers won't need to care about device refcounting */
static inline struct spi_device *spi_dev_get(struct spi_device *spi)
{
	return (spi && get_device(&spi->dev)) ? spi : NULL;
}

static inline void spi_dev_put(struct spi_device *spi)
{
	if (spi)
		put_device(&spi->dev);
}

/* ctldata is for the bus_master driver's runtime state */
static inline void *spi_get_ctldata(struct spi_device *spi)
{
	return spi->controller_state;
}

static inline void spi_set_ctldata(struct spi_device *spi, void *state)
{
	spi->controller_state = state;
}

/* device driver data */

static inline void spi_set_drvdata(struct spi_device *spi, void *data)
{
	dev_set_drvdata(&spi->dev, data);
}

static inline void *spi_get_drvdata(struct spi_device *spi)
{
	return dev_get_drvdata(&spi->dev);
}

struct spi_message;



/**
 * struct spi_driver - Host side "protocol" driver
 * @id_table: List of SPI devices supported by this driver
 * @probe: Binds this driver to the spi device.  Drivers can verify
 *	that the device is actually present, and may need to configure
 *	characteristics (such as bits_per_word) which weren't needed for
 *	the initial configuration done during system setup.
 * @remove: Unbinds this driver from the spi device
 * @shutdown: Standard shutdown callback used during system state
 *	transitions such as powerdown/halt and kexec
 * @suspend: Standard suspend callback used during system state transitions
 * @resume: Standard resume callback used during system state transitions
 * @driver: SPI device drivers should initialize the name and owner
 *	field of this structure.
 *
 * This represents the kind of device driver that uses SPI messages to
 * interact with the hardware at the other end of a SPI link.  It's called
 * a "protocol" driver because it works through messages rather than talking
 * directly to SPI hardware (which is what the underlying SPI controller
 * driver does to pass those messages).  These protocols are defined in the
 * specification for the device(s) supported by the driver.
 *
 * As a rule, those device protocols represent the lowest level interface
 * supported by a driver, and it will support upper level interfaces too.
 * Examples of such upper levels include frameworks like MTD, networking,
 * MMC, RTC, filesystem character device nodes, and hardware monitoring.

 Driver是为device服务的，spi_driver注册时会扫描SPI bus上的设备，
 进行驱动和设备的绑定，probe函数用于驱动和设备匹配时被调用。
 从上面的结构体注释中我们可以知道，SPI的通信是通过消息队列机制，
 而不是像I2C那样通过与从设备进行对话的方式。*/
struct spi_driver {
	const struct spi_device_id *id_table;
	int			(*probe)(struct spi_device *spi);
	int			(*remove)(struct spi_device *spi);
	void			(*shutdown)(struct spi_device *spi);
	int			(*suspend)(struct spi_device *spi, pm_message_t mesg);
	int			(*resume)(struct spi_device *spi);
	struct device_driver	driver;
};

static inline struct spi_driver *to_spi_driver(struct device_driver *drv)
{
	return drv ? container_of(drv, struct spi_driver, driver) : NULL;
}

extern int spi_register_driver(struct spi_driver *sdrv);

/**
 * spi_unregister_driver - reverse effect of spi_register_driver
 * @sdrv: the driver to unregister
 * Context: can sleep
 */
static inline void spi_unregister_driver(struct spi_driver *sdrv)
{
	if (sdrv)
		driver_unregister(&sdrv->driver);
}


/**
 * struct spi_master - interface to SPI master controller
 * @dev: device interface to this driver
 * @bus_num: board-specific (and often SOC-specific) identifier for a
 *	given SPI controller.
 * @num_chipselect: chipselects are used to distinguish individual
 *	SPI slaves, and are numbered from zero to num_chipselects.
 *	each slave has a chipselect signal, but it's common that not
 *	every chipselect is connected to a slave.
 * @dma_alignment: SPI controller constraint on DMA buffers alignment.
 * @mode_bits: flags understood by this controller driver
 * @flags: other constraints relevant to this driver
 * @setup: updates the device mode and clocking records used by a
 *	device's SPI controller; protocol code may call this.  This
 *	must fail if an unrecognized or unsupported mode is requested.
 *	It's always safe to call this unless transfers are pending on
 *	the device whose settings are being modified.
 * @transfer: adds a message to the controller's transfer queue.
 * @cleanup: frees controller-specific state
 *
 * Each SPI master controller can communicate with one or more @spi_device
 * children.  These make a small bus, sharing MOSI, MISO and SCK signals
 * but not chip select signals.  Each device may be configured to use a
 * different clock rate, since those shared signals are ignored unless
 * the chip is selected.
 *
 * The driver for an SPI controller manages access to those devices through
 * a queue of spi_message transactions, copying data between CPU memory and
 * an SPI slave device.  For each such message it queues, it calls the
 * message's completion function when the transaction completes.
 一个控制器驱动可以用数据结构struct spi_master来描述。*/
struct spi_master {//一个控制器驱动可以用数据结构struct spi_master来描述。
	struct device	dev;//内嵌的标准dev结构

	/* other than negative (== assign one dynamically), bus_num is fully
	 * board-specific.  usually that simplifies to being SOC-specific.
	 * example:  one SOC has three SPI controllers, numbered 0..2,
	 * and one board's schematics might show it using SPI-2.  software
	 * would normally use bus_num=2 for that controller.
	 */
	s16			bus_num;//为该控制器对应的SPI总线号。如spi0,spi1

	/* chipselects will be integral to many controllers; some others
	 * might use board-specific GPIOs.
	 */
	u16			num_chipselect;//为该总线的对应的设备编号。cs对应挂接的spi_slaves

	/* some SPI controllers pose alignment requirements on DMAable
	 * buffers; let protocol drivers know about these requirements.
	 */
	u16			dma_alignment;//dma对其要求

	/* spi_device.mode flags understood by this controller driver */
	u16			mode_bits;//代表操作的spi_device.mode   

	/* other constraints relevant to this driver */
	u16			flags;
#define SPI_MASTER_HALF_DUPLEX	BIT(0)		/* can't do full duplex */
#define SPI_MASTER_NO_RX	BIT(1)		/* can't do buffer read */
#define SPI_MASTER_NO_TX	BIT(2)		/* can't do buffer write */

	/* Setup mode and clock, etc (spi driver may call many times).
	 *
	 * IMPORTANT:  this may be called when transfers to another
	 * device are active.  DO NOT UPDATE SHARED REGISTERS in ways
	 * which could break those transfers.
	 */
	int			(*setup)(struct spi_device *spi);//设置SPI总线的模式，时钟等的初始化函数。

	/* bidirectional bulk transfers
	 *
	 * + The transfer() method may not sleep; its main role is
	 *   just to add the message to the queue.
	 * + For now there's no remove-from-queue operation, or
	 *   any other request management
	 * + To a given spi_device, message queueing is pure fifo
	 *
	 * + The master's main job is to process its message queue,
	 *   selecting a chip then transferring data
	 * + If there are multiple spi_device children, the i/o queue
	 *   arbitration algorithm is unspecified (round robin, fifo,
	 *   priority, reservations, preemption, etc)
	 *
	 * + Chipselect stays active during the entire message
	 *   (unless modified by spi_transfer.cs_change != 0).
	 * + The message transfers use clock and SPI mode parameters
	 *   previously established by setup() for this device
	 */
	int			(*transfer)(struct spi_device *spi,
						struct spi_message *mesg);//实现SPI总线读写方法的函数。

	/* called on release() to free memory provided by spi_master */
	void			(*cleanup)(struct spi_device *spi);////注销时调用
};

static inline void *spi_master_get_devdata(struct spi_master *master)
{
	return dev_get_drvdata(&master->dev);
}

static inline void spi_master_set_devdata(struct spi_master *master, void *data)
{
	dev_set_drvdata(&master->dev, data);
}

static inline struct spi_master *spi_master_get(struct spi_master *master)
{
	if (!master || !get_device(&master->dev))
		return NULL;
	return master;
}

static inline void spi_master_put(struct spi_master *master)
{
	if (master)
		put_device(&master->dev);
}


/* the spi driver core manages memory for the spi_master classdev */
extern struct spi_master *
spi_alloc_master(struct device *host, unsigned size);

extern int spi_register_master(struct spi_master *master);
extern void spi_unregister_master(struct spi_master *master);

extern struct spi_master *spi_busnum_to_master(u16 busnum);

/*---------------------------------------------------------------------------*/

/*
 * I/O INTERFACE between SPI controller and protocol drivers
 *
 * Protocol drivers use a queue of spi_messages, each transferring data
 * between the controller and memory buffers.
 *
 * The spi_messages themselves consist of a series of read+write transfer
 * segments.  Those segments always read the same number of bits as they
 * write; but one or the other is easily ignored by passing a null buffer
 * pointer.  (This is unlike most types of I/O API, because SPI hardware
 * is full duplex.)
 *
 * NOTE:  Allocation of spi_transfer and spi_message memory is entirely
 * up to the protocol driver, which guarantees the integrity of both (as
 * well as the data buffers) for as long as the message is queued.
 */

/**
 * struct spi_transfer - a read/write buffer pair
 * @tx_buf: data to be written (dma-safe memory), or NULL
 * @rx_buf: data to be read (dma-safe memory), or NULL
 * @tx_dma: DMA address of tx_buf, if @spi_message.is_dma_mapped
 * @rx_dma: DMA address of rx_buf, if @spi_message.is_dma_mapped
 * @len: size of rx and tx buffers (in bytes)
 * @speed_hz: Select a speed other than the device default for this
 *      transfer. If 0 the default (from @spi_device) is used.
 * @bits_per_word: select a bits_per_word other than the device default
 *      for this transfer. If 0 the default (from @spi_device) is used.
 * @cs_change: affects chipselect after this transfer completes
 * @delay_usecs: microseconds to delay after this transfer before
 *	(optionally) changing the chipselect status, then starting
 *	the next transfer or completing this @spi_message.
 * @transfer_list: transfers are sequenced through @spi_message.transfers
 *
 * SPI transfers always write the same number of bytes as they read.
 * Protocol drivers should always provide @rx_buf and/or @tx_buf.
 * In some cases, they may also want to provide DMA addresses for
 * the data being transferred; that may reduce overhead, when the
 * underlying driver uses dma.
 *
 * If the transmit buffer is null, zeroes will be shifted out
 * while filling @rx_buf.  If the receive buffer is null, the data
 * shifted in will be discarded.  Only "len" bytes shift out (or in).
 * It's an error to try to shift out a partial word.  (For example, by
 * shifting out three bytes with word size of sixteen or twenty bits;
 * the former uses two bytes per word, the latter uses four bytes.)
 *
 * In-memory data values are always in native CPU byte order, translated
 * from the wire byte order (big-endian except with SPI_LSB_FIRST).  So
 * for example when bits_per_word is sixteen, buffers are 2N bytes long
 * (@len = 2N) and hold N sixteen bit words in CPU byte order.
 *
 * When the word size of the SPI transfer is not a power-of-two multiple
 * of eight bits, those in-memory words include extra bits.  In-memory
 * words are always seen by protocol drivers as right-justified, so the
 * undefined (rx) or unused (tx) bits are always the most significant bits.
 *
 * All SPI transfers start with the relevant chipselect active.  Normally
 * it stays selected until after the last transfer in a message.  Drivers
 * can affect the chipselect signal using cs_change.
 *
 * (i) If the transfer isn't the last one in the message, this flag is
 * used to make the chipselect briefly go inactive in the middle of the
 * message.  Toggling chipselect in this way may be needed to terminate
 * a chip command, letting a single spi_message perform all of group of
 * chip transactions together.
 *
 * (ii) When the transfer is the last one in the message, the chip may
 * stay selected until the next transfer.  On multi-device SPI busses
 * with nothing blocking messages going to other devices, this is just
 * a performance hint; starting a message to another device deselects
 * this one.  But in other cases, this can be used to ensure correctness.
 * Some devices need protocol transactions to be built from a series of
 * spi_message submissions, where the content of one message is determined
 * by the results of previous messages and where the whole transaction
 * ends when the chipselect goes intactive.
 *
 * The code that submits an spi_message (and its spi_transfers)
 * to the lower layers is responsible for managing its memory.
 * Zero-initialize every field you don't set up explicitly, to
 * insulate against future API updates.  After you submit a message
 * and its transfers, ignore them until its completion callback.
  一个spi_transfer是以某种特性如速率、延时及字长连续传输的最小单位。因为SPI是全双工总线，只要总线上有数据传输，则MOSI和MISO上同时有数据采样，对于SPI 控制器来说，其收发缓冲区中都有数据，但是对于SPI设备来说，其可以灵活的选择tx_buf和rx_buf的设置。当发送数据时，tx_buf必须设置为待发送的数据，rx_buf可以为null或者指向无用的缓冲区，即不关心MISO的数据。而当接收数据时，rx_buf必须指向接收缓冲区，而tx_buf可以为Null，则MOSI上为全0，或者tx_buf指向不会引起从设备异常相应的数据，len为待发送或者接收的数据长度，当然当采用DMAf方式传输时，必须初始化相应的DMA地址。当一系列spi_transfer构成一个spi_message时，cs_change的设置非常讲究。当cs_change为0即不变时，则可以连续对同一个设备进行数据收发；当cs_change为1时通常用来停止command的传输而随后进行数据接收。因此cs_change可以利用SPI总线构造复杂的通信协议。
        对于SPI总线协议来说，传输单位可以是4-32之间的任意bits，但对于SPI控制器来说，bits_per_word只能是8/16/32，即需要取整，待收发的数据在内存里都是以主机字节序右对齐存储，SPI控制器会自动根据传输单位及大小端进行转换。
 */
struct spi_transfer {
	/* it's ok if tx_buf == rx_buf (right?)
	 * for MicroWire, one buffer must be null
	 * buffers must work with dma_*map_single() calls, unless
	 *   spi_message.is_dma_mapped reports a pre-existing mapping
	 */
	const void	*tx_buf;
	void		*rx_buf;
	unsigned	len;

	dma_addr_t	tx_dma;
	dma_addr_t	rx_dma;

	unsigned	cs_change:1;
	u8		bits_per_word;
	u16		delay_usecs;
	u32		speed_hz;

	struct list_head transfer_list;
};

/**
 * struct spi_message - one multi-segment SPI transaction
 * @transfers: list of transfer segments in this transaction
 * @spi: SPI device to which the transaction is queued
 * @is_dma_mapped: if true, the caller provided both dma and cpu virtual
 *	addresses for each transfer buffer
 * @complete: called to report transaction completions
 * @context: the argument to complete() when it's called
 * @actual_length: the total number of bytes that were transferred in all
 *	successful segments
 * @status: zero for success, else negative errno
 * @queue: for use by whichever driver currently owns the message
 * @state: for use by whichever driver currently owns the message
 *
 * A @spi_message is used to execute an atomic sequence of data transfers,
 * each represented by a struct spi_transfer.  The sequence is "atomic"
 * in the sense that no other spi_message may use that SPI bus until that
 * sequence completes.  On some systems, many such sequences can execute as
 * as single programmed DMA transfer.  On all systems, these messages are
 * queued, and might complete after transactions to other devices.  Messages
 * sent to a given spi_device are alway executed in FIFO order.
 *
 * The code that submits an spi_message (and its spi_transfers)
 * to the lower layers is responsible for managing its memory.
 * Zero-initialize every field you don't set up explicitly, to
 * insulate against future API updates.  After you submit a message
 * and its transfers, ignore them until its completion callback.
spi_message 包含了一系列spi_transfer，在所有的spi_transfer发送完毕前，SPI总线一直被占据，其间不会出现总线冲突，因此一个spi_message是一个原子系列，这种特性非常利于复杂的SPI通信协议，如先发送命令字然后才能读取数据。所有的spi_message都按照FIFO顺序执行。
       还定义了需要发送的SPI设备，上下文信息context和传输完成后需要的回调函数complete等。
 */
struct spi_message {
	struct list_head	transfers;

	struct spi_device	*spi;

	unsigned		is_dma_mapped:1;

	/* REVISIT:  we might want a flag affecting the behavior of the
	 * last transfer ... allowing things like "read 16 bit length L"
	 * immediately followed by "read L bytes".  Basically imposing
	 * a specific message scheduling algorithm.
	 *
	 * Some controller drivers (message-at-a-time queue processing)
	 * could provide that as their default scheduling algorithm.  But
	 * others (with multi-message pipelines) could need a flag to
	 * tell them about such special cases.
	 */

	/* completion is reported through a callback */
	void			(*complete)(void *context);
	void			*context;
	unsigned		actual_length;
	int			status;

	/* for optional use by whatever driver currently owns the
	 * spi_message ...  between calls to spi_async and then later
	 * complete(), that's the spi_master controller driver.
	 */
	struct list_head	queue;
	void			*state;
};

static inline void spi_message_init(struct spi_message *m)
{
	memset(m, 0, sizeof *m);
	INIT_LIST_HEAD(&m->transfers);
}

static inline void
spi_message_add_tail(struct spi_transfer *t, struct spi_message *m)
{
	list_add_tail(&t->transfer_list, &m->transfers);
}

static inline void
spi_transfer_del(struct spi_transfer *t)
{
	list_del(&t->transfer_list);
}

/* It's fine to embed message and transaction structures in other data
 * structures so long as you don't free them while they're in use.
 */

static inline struct spi_message *spi_message_alloc(unsigned ntrans, gfp_t flags)
{
	struct spi_message *m;

	m = kzalloc(sizeof(struct spi_message)
			+ ntrans * sizeof(struct spi_transfer),
			flags);
	if (m) {
		int i;
		struct spi_transfer *t = (struct spi_transfer *)(m + 1);

		INIT_LIST_HEAD(&m->transfers);
		for (i = 0; i < ntrans; i++, t++)
			spi_message_add_tail(t, m);
	}
	return m;
}

static inline void spi_message_free(struct spi_message *m)
{
	kfree(m);
}

extern int spi_setup(struct spi_device *spi);
extern int spi_async(struct spi_device *spi, struct spi_message *message);

/*---------------------------------------------------------------------------*/

/* All these synchronous SPI transfer routines are utilities layered
 * over the core async transfer primitive.  Here, "synchronous" means
 * they will sleep uninterruptibly until the async transfer completes.
 */

extern int spi_sync(struct spi_device *spi, struct spi_message *message);

/**
 * spi_write - SPI synchronous write
 * @spi: device to which data will be written
 * @buf: data buffer
 * @len: data buffer size
 * Context: can sleep
 *
 * This writes the buffer and returns zero or a negative error code.
 * Callable only from contexts that can sleep.
 */
static inline int
spi_write(struct spi_device *spi, const u8 *buf, size_t len)
{
	struct spi_transfer	t = {
			.tx_buf		= buf,
			.len		= len,
		};
	struct spi_message	m;

	spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	return spi_sync(spi, &m);
}

/**
 * spi_read - SPI synchronous read
 * @spi: device from which data will be read
 * @buf: data buffer
 * @len: data buffer size
 * Context: can sleep
 *
 * This reads the buffer and returns zero or a negative error code.
 * Callable only from contexts that can sleep.
 */
static inline int
spi_read(struct spi_device *spi, u8 *buf, size_t len)
{
	struct spi_transfer	t = {
			.rx_buf		= buf,
			.len		= len,
		};
	struct spi_message	m;

	spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	return spi_sync(spi, &m);
}

/* this copies txbuf and rxbuf data; for small transfers only! */
extern int spi_write_then_read(struct spi_device *spi,
		const u8 *txbuf, unsigned n_tx,
		u8 *rxbuf, unsigned n_rx);

/**
 * spi_w8r8 - SPI synchronous 8 bit write followed by 8 bit read
 * @spi: device with which data will be exchanged
 * @cmd: command to be written before data is read back
 * Context: can sleep
 *
 * This returns the (unsigned) eight bit number returned by the
 * device, or else a negative error code.  Callable only from
 * contexts that can sleep.
 */
static inline ssize_t spi_w8r8(struct spi_device *spi, u8 cmd)
{
	ssize_t			status;
	u8			result;

	status = spi_write_then_read(spi, &cmd, 1, &result, 1);

	/* return negative errno or unsigned value */
	return (status < 0) ? status : result;
}

/**
 * spi_w8r16 - SPI synchronous 8 bit write followed by 16 bit read
 * @spi: device with which data will be exchanged
 * @cmd: command to be written before data is read back
 * Context: can sleep
 *
 * This returns the (unsigned) sixteen bit number returned by the
 * device, or else a negative error code.  Callable only from
 * contexts that can sleep.
 *
 * The number is returned in wire-order, which is at least sometimes
 * big-endian.
 */
static inline ssize_t spi_w8r16(struct spi_device *spi, u8 cmd)
{
	ssize_t			status;
	u16			result;

	status = spi_write_then_read(spi, &cmd, 1, (u8 *) &result, 2);

	/* return negative errno or unsigned value */
	return (status < 0) ? status : result;
}

/*---------------------------------------------------------------------------*/

/*
 * INTERFACE between board init code and SPI infrastructure.
 *
 * No SPI driver ever sees these SPI device table segments, but
 * it's how the SPI core (or adapters that get hotplugged) grows
 * the driver model tree.
 *
 * As a rule, SPI devices can't be probed.  Instead, board init code
 * provides a table listing the devices which are present, with enough
 * information to bind and set up the device's driver.  There's basic
 * support for nonstatic configurations too; enough to handle adding
 * parport adapters, or microcontrollers acting as USB-to-SPI bridges.
 */

/**
 * struct spi_board_info - board-specific template for a SPI device
 * @modalias: Initializes spi_device.modalias; identifies the driver.
 * @platform_data: Initializes spi_device.platform_data; the particular
 *	data stored there is driver-specific.
 * @controller_data: Initializes spi_device.controller_data; some
 *	controllers need hints about hardware setup, e.g. for DMA.
 * @irq: Initializes spi_device.irq; depends on how the board is wired.
 * @max_speed_hz: Initializes spi_device.max_speed_hz; based on limits
 *	from the chip datasheet and board-specific signal quality issues.
 * @bus_num: Identifies which spi_master parents the spi_device; unused
 *	by spi_new_device(), and otherwise depends on board wiring.
 * @chip_select: Initializes spi_device.chip_select; depends on how
 *	the board is wired.
 * @mode: Initializes spi_device.mode; based on the chip datasheet, board
 *	wiring (some devices support both 3WIRE and standard modes), and
 *	possibly presence of an inverter in the chipselect path.
 *
 * When adding new SPI devices to the device tree, these structures serve
 * as a partial device template.  They hold information which can't always
 * be determined by drivers.  Information that probe() can establish (such
 * as the default transfer wordsize) is not included here.
 *
 * These structures are used in two places.  Their primary role is to
 * be stored in tables of board-specific device descriptors, which are
 * declared early in board initialization and then used (much later) to
 * populate a controller's device tree after the that controller's driver
 * initializes.  A secondary (and atypical) role is as a parameter to
 * spi_new_device() call, which happens after those controller drivers
 * are active in some dynamic board configuration models.
 //1其中内嵌的描述spi设备的具体信息的结构struct spi_board_info为
2具体的spi外设信息linux spi 用 struct spi_board_info来描述，
3该结构体包含外设的片选号、总线号、模式以及传输速率等信息。在系统初始化时将会调用spi_register_board_info()来注册硬件信息。 
3结构体spi_board_info中挂在SPI总线上的设备的平台信息。
4在设备移植时填充结构体spi_board_info时移植的重要工作，同时还要调用函数spi_register_board_info()将
结构体boardinfo添加到链表board_list上
*/
struct spi_board_info {
	/* the device name and module name are coupled, like platform_bus;
	 * "modalias" is normally the driver name.
	 *
	 * platform_data goes to spi_device.dev.platform_data,
	 * controller_data goes to spi_device.controller_data,
	 * irq is copied too
	 */
	char		modalias[SPI_NAME_SIZE];//名字//设备spi_device在SPI总线spi_bus_type上匹配驱动的唯一标识。
	const void	*platform_data;//如同注释写的指向spi_device.dev.platform_data   
	void		*controller_data;//指向spi_device.controller_data   
	int		irq;//中断号  

	/* slower signaling on noisy or low voltage boards */
	u32		max_speed_hz;//最大的spi时钟频率


	/* bus_num is board specific and matches the bus_num of some
	 * spi_master that will probably be registered later.
	 *
	 * chip_select reflects how this chip is wired to that master;
	 * it's less than num_chipselect.
	 */
	u16		bus_num;//设备连接在spi控制器0上,/总线编号   
	u16		chip_select;//片选线号，在S5PC100的控制器驱动中没有使用它作为片选的依据，而是选择了下文controller_data里的方法。

	/* mode becomes spi_device.mode, and is essential for chips
	 * where the default of SPI_CS_HIGH = 0 is wrong.
	 */
	u8		mode;//CPOL=0, CPHA=0 此处选择具体数据传输模式

	/* ... may need additional spi_device chip config data here.
	 * avoid stuff protocol drivers can set; but include stuff
	 * needed to behave without being bound to a driver:
	 *  - quirks like clock rate mattering when not selected
	 */
};

#ifdef	CONFIG_SPI
extern int
spi_register_board_info(struct spi_board_info const *info, unsigned n);
#else
/* board init code may ignore whether SPI is configured or not */
static inline int
spi_register_board_info(struct spi_board_info const *info, unsigned n)
	{ return 0; }
#endif


/* If you're hotplugging an adapter with devices (parport, usb, etc)
 * use spi_new_device() to describe each device.  You can also call
 * spi_unregister_device() to start making that device vanish, but
 * normally that would be handled by spi_unregister_master().
 *
 * You can also use spi_alloc_device() and spi_add_device() to use a two
 * stage registration sequence for each spi_device.  This gives the caller
 * some more control over the spi_device structure before it is registered,
 * but requires that caller to initialize fields that would otherwise
 * be defined using the board info.
 */
extern struct spi_device *
spi_alloc_device(struct spi_master *master);

extern int
spi_add_device(struct spi_device *spi);

extern struct spi_device *
spi_new_device(struct spi_master *, struct spi_board_info *);

static inline void
spi_unregister_device(struct spi_device *spi)
{
	if (spi)
		device_unregister(&spi->dev);
}

extern const struct spi_device_id *
spi_get_device_id(const struct spi_device *sdev);

#endif /* __LINUX_SPI_H */
