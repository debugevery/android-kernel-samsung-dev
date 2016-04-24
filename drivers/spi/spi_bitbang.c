/**
 * spi_bitbang.c - polling/bitbanging SPI master controller driver utilities
 *	网上开源下载的，请替换成210里的C文件
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

//#include <linux/init.h>
//#include <linux/spinlock.h>
//#include <linux/workqueue.h>
//#include <linux/interrupt.h>
//#include <linux/delay.h>
//#include <linux/errno.h>
//#include <linux/platform_device.h>
//#include <linux/slab.h>

//#include <linux/spi/spi.h>
//#include <linux/spi/spi_bitbang.h>


/**----------------------------------------------------------------------*/

/**
 * FIRST PART (OPTIONAL):  word-at-a-time spi_transfer support.
 * Use this for GPIO or shift-register level hardware APIs.
 *
 * spi_bitbang_cs is in spi_device->controller_state, which is unavailable
 * to glue code.  These bitbang setup() and cleanup() routines are always
 * used, though maybe they're called from controller-aware code.
 *
 * chipselect() and friends may use use spi_device->controller_data and
 * controller registers as appropriate.
 *
 *
 * NOTE:  SPI controller pins can often be used as GPIO pins instead,
 * which means you could use a bitbang driver either to get hardware
 * working quickly, or testing for differences that aren't speed related.
 */

struct spi_bitbang_cs {
	unsigned	nsecs;	/** (clock cycle time)/2 */
	u32		(*txrx_word)(struct spi_device *spi, unsigned nsecs,
					u32 word, u8 bits);
	unsigned	(*txrx_bufs)(struct spi_device *,
					u32 (*txrx_word)(
						struct spi_device *spi,
						unsigned nsecs,
						u32 word, u8 bits),
					unsigned, struct spi_transfer *);
};

static unsigned bitbang_txrx_8(
	struct spi_device	*spi,
	u32			(*txrx_word)(struct spi_device *spi,
					unsigned nsecs,
					u32 word, u8 bits),
	unsigned		ns,
	struct spi_transfer	*t
) {
	unsigned		bits = spi->bits_per_word;
	unsigned		count = t->len;
	const u8		*tx = t->tx_buf;
	u8			*rx = t->rx_buf;

	while (likely(count > 0)) {
		u8		word = 0;

		if (tx)
			word = *tx++;
		word = txrx_word(spi, ns, word, bits);
		if (rx)
			*rx++ = word;
		count -= 1;
	}
	return t->len - count;
}

static unsigned bitbang_txrx_16(
	struct spi_device	*spi,
	u32			(*txrx_word)(struct spi_device *spi,
					unsigned nsecs,
					u32 word, u8 bits),
	unsigned		ns,
	struct spi_transfer	*t
) {
	unsigned		bits = spi->bits_per_word;
	unsigned		count = t->len;
	const u16		*tx = t->tx_buf;
	u16			*rx = t->rx_buf;

	while (likely(count > 1)) {
		u16		word = 0;

		if (tx)
			word = *tx++;
		word = txrx_word(spi, ns, word, bits);
		if (rx)
			*rx++ = word;
		count -= 2;
	}
	return t->len - count;
}

static unsigned bitbang_txrx_32(
	struct spi_device	*spi,
	u32			(*txrx_word)(struct spi_device *spi,
					unsigned nsecs,
					u32 word, u8 bits),
	unsigned		ns,
	struct spi_transfer	*t
) {
	unsigned		bits = spi->bits_per_word;
	unsigned		count = t->len;
	const u32		*tx = t->tx_buf;
	u32			*rx = t->rx_buf;

	while (likely(count > 3)) {
		u32		word = 0;

		if (tx)
			word = *tx++;
		word = txrx_word(spi, ns, word, bits);
		if (rx)
			*rx++ = word;
		count -= 4;
	}
	return t->len - count;
}

int spi_bitbang_setup_transfer(struct spi_device *spi, struct spi_transfer *t)
{
	struct spi_bitbang_cs	*cs = spi->controller_state;
	u8			bits_per_word;
	u32			hz;

	if (t) {
		bits_per_word = t->bits_per_word;
		hz = t->speed_hz;
	} else {
		bits_per_word = 0;
		hz = 0;
	}

	/** spi_transfer level calls that work per-word */
	if (!bits_per_word)
		bits_per_word = spi->bits_per_word;
	if (bits_per_word <= 8)
		cs->txrx_bufs = bitbang_txrx_8;
	else if (bits_per_word <= 16)
		cs->txrx_bufs = bitbang_txrx_16;
	else if (bits_per_word <= 32)
		cs->txrx_bufs = bitbang_txrx_32;
	else
		return -EINVAL;

	/** nsecs = (clock period)/2 */
	if (!hz)
		hz = spi->max_speed_hz;
	if (hz) {
		cs->nsecs = (1000000000/2) / hz;
		if (cs->nsecs > (MAX_UDELAY_MS * 1000 * 1000))
			return -EINVAL;
	}

	return 0;
}
//EXPORT_SYMBOL_GPL(spi_bitbang_setup_transfer);

/***
 * spi_bitbang_setup - default setup for per-word I/O loops
 */
int spi_bitbang_setup(struct spi_device *spi)
{
	struct spi_bitbang_cs	*cs = spi->controller_state;
	struct spi_bitbang	*bitbang;
	int			retval;
	unsigned long		flags;

	bitbang = spi_master_get_devdata(spi->master);

	if (!cs) {
		cs = kzalloc(sizeof *cs, GFP_KERNEL);
		if (!cs)
			return -ENOMEM;
		spi->controller_state = cs;
	}

	/** per-word shift register access, in hardware or bitbanging */
	cs->txrx_word = bitbang->txrx_word[spi->mode & (SPI_CPOL|SPI_CPHA)];
	if (!cs->txrx_word)
		return -EINVAL;

	retval = bitbang->setup_transfer(spi, NULL);
	if (retval < 0)
		return retval;

	dev_dbg(&spi->dev, "%s, %u nsec/bit\n", __func__, 2 * cs->nsecs);

	/** NOTE we _need_ to call chipselect() early, ideally with adapter
	 * setup, unless the hardware defaults cooperate to avoid confusion
	 * between normal (active low) and inverted chipselects.
	 */

	/** deselect chip (low or high) */
	spin_lock_irqsave(&bitbang->lock, flags);
	if (!bitbang->busy) {
		bitbang->chipselect(spi, BITBANG_CS_INACTIVE);
		ndelay(cs->nsecs);
	}
	spin_unlock_irqrestore(&bitbang->lock, flags);

	return 0;
}
//EXPORT_SYMBOL_GPL(spi_bitbang_setup);

/***
 * spi_bitbang_cleanup - default cleanup for per-word I/O loops
 */
void spi_bitbang_cleanup(struct spi_device *spi)
{
	kfree(spi->controller_state);
}
//EXPORT_SYMBOL_GPL(spi_bitbang_cleanup);

static int spi_bitbang_bufs(struct spi_device *spi, struct spi_transfer *t)
{
	struct spi_bitbang_cs	*cs = spi->controller_state;
	unsigned		nsecs = cs->nsecs;

	return cs->txrx_bufs(spi, cs->txrx_word, nsecs, t);
}

/**----------------------------------------------------------------------*/

/**
 * SECOND PART ... simple transfer queue runner.
 *
 * This costs a task context per controller, running the queue by
 * performing each transfer in sequence.  Smarter hardware can queue
 * several DMA transfers at once, and process several controller queues
 * in parallel; this driver doesn't match such hardware very well.
 *
 * Drivers can provide word-at-a-time i/o primitives, or provide
 * transfer-at-a-time ones to leverage dma or fifo hardware.
数据传输是SPI接口的任务，结构体master代表了一个接口，当一个spi_message从上层函数传递下来时，
master的成员函数bitbang->master->transfer将该数据传输任务添加到工作队列头。
queue_work(bitbang->workqueue, &bitbang->work);
函数bitbang->master->transfer()在上面已经讲解。
工作队列struct workqueue_struct *workqueue;的创建和 struct work_struct work的初始化都是在函数
spi_bitbang_start()中进行的。
INIT_WORK(&bitbang->work, bitbang_work); //bitbang_work是任务处理函数
bitbang->workqueue = create_singlethread_workqueue(dev_name(bitbang->master->dev.parent));
任务处理函数如下
 */
static void bitbang_work(struct work_struct *work)
{
	struct spi_bitbang	*bitbang =
		container_of(work, struct spi_bitbang, work););//获取bitbang结构体
	unsigned long		flags;
	int			(*setup_transfer)(struct spi_device *,
					struct spi_transfer *);

	setup_transfer = bitbang->setup_transfer;

	spin_lock_irqsave(&bitbang->lock, flags);
	bitbang->busy = 1;//置忙标志
	//每一次数据传输都传递下来一个spi_message，如果上一次的spi_message
	//还没处理完接下来的spi_message就挂接在 queue上等待处理 。
	while (!list_empty(&bitbang->queue)) {//遍历bitbang->queue链表
		struct spi_message	*m;
		struct spi_device	*spi;
		unsigned		nsecs;
		struct spi_transfer	*t = NULL;
		unsigned		tmp;
		unsigned		cs_change;
		int			status;
		int			do_setup = -1;

		m = container_of(bitbang->queue.next, struct spi_message,
				queue);//获取spi_message结构
		list_del_init(&m->queue);//把spi_messae从queue里删除
		spin_unlock_irqrestore(&bitbang->lock, flags);

		/** FIXME this is made-up ... the correct value is known to
		 * word-at-a-time bitbang code, and presumably chipselect()
		 * should enforce these requirements too?
		 */
		nsecs = 100;//spi传输模式设置和hw->set_cs之后的延时

		spi = m->spi;
		tmp = 0;
		cs_change = 1;//多段数据传输时，数据管理结构体挂于链表上，cs_change = 1表征最后一段要传输的数据
		status = 0;
		//每次数据传输，都将要传输的数据分成多个数据段，这些数据段由数据管理结构体
		//spi_transfer来管理。结构体spi_transfer又将挂在m->transfers。也就是说
		//每次数据传输都将要传输的数据包装成一个结构体spi_message传输下来。
		list_for_each_entry (t, &m->transfers, transfer_list) {//遍历spi_message上的每一个数据段
			//从spi_message结构的transfers链表中获取spi_transfer结构

			/** override speed or wordsize? */
			/* 本messae传输中，需要重设条件，调用setup_transfer函数 */
			if (t->speed_hz || t->bits_per_word)
				do_setup = 1;

			/** init (-1) or override (1) transfer params */
			if (do_setup != 0) {
				if (!setup_transfer) {
					status = -ENOPROTOOPT;
					break;
				}
				status = setup_transfer(spi, t);
				if (status < 0)
					break;
				if (do_setup == -1)
					do_setup = 0;
			}

			/** set up default clock polarity, and activate chip;
			 * this implicitly updates clock and spi modes as
			 * previously recorded for this device via setup().
			 * (and also deselects any other chip that might be
			 * selected ...)
			//多端数据传输时只需第一段数据传输时调用以下模式设置，将spi->mode
  			//写入SPI的模式控制寄存器。并调用函数hw->set_cs，片选设置。 
  			//在函数讲解函数spidev_ioctl()中的模式设置时讲到过。在那里  调用的函数chipselect(spi, BITBANG_CS_INACTIVE);  
  			//传递的传输是BITBANG_CS_INACTIVE是不能将数据传输模式spi->mode写入SPI控制寄存器的，不过在那里设置了  
  			//spi->mode的值。
*/
			if (cs_change) {
				bitbang->chipselect(spi, BITBANG_CS_ACTIVE);
				ndelay(nsecs);
			}
			cs_change = t->cs_change;
			if (!t->tx_buf && !t->rx_buf && t->len) {
				status = -EINVAL;
				break;
			}

			/** transfer data.  the lower level code handles any
			 * new dma mappings it needs. our caller always gave
			 * us dma-safe buffers.
			 */
			if (t->len) {
				/** REVISIT dma API still needs a designated
				 * DMA_ADDR_INVALID; ~0 might be better.
				 */
				if (!m->is_dma_mapped)
					t->rx_dma = t->tx_dma = 0;
				status = bitbang->txrx_bufs(spi, t);//调用s3c24xx_spi_txrx开始传输数据
			}
			if (status > 0)
				m->actual_length += status;//计算已传输数据长度
			if (status != t->len) {
				/** always report some kind of error */
				if (status >= 0)
					status = -EREMOTEIO;
				break;
			}
			status = 0;

			/** protocol tweaks before next transfer */
			if (t->delay_usecs)//延时等待一段数据传输完，因为一段数据要经过多次中断传输
				udelay(t->delay_usecs);

			if (!cs_change);//不用重新片选，继续下一个message的传输
				continue;
			if (t->transfer_list.next == &m->transfers)//链表遍历完毕，退出循环
				break;

			/** sometimes a short mid-message deselect of the chip
			 * may be needed to terminate a mode or command
			 */
			ndelay(nsecs);
			bitbang->chipselect(spi, BITBANG_CS_INACTIVE);//需要重新片选的话...
			ndelay(nsecs);
		}

		m->status = status;;//所用spi_message传输完毕
		m->complete(m->context);//应答返回变量，通知等待spi传输完毕的进程(具体来说就是spi_sync函数了)

		/** normally deactivate chipselect ... unless no error and
		 * cs_change has hinted that the next message will probably
		 * be for this chip too.
		 */
		if (!(status == 0 && cs_change)) {
			ndelay(nsecs);
			bitbang->chipselect(spi, BITBANG_CS_INACTIVE);
			ndelay(nsecs);
		}
		//重新获取自旋锁，遍历工作者队列的下一个工作
		spin_lock_irqsave(&bitbang->lock, flags);
	}
	bitbang->busy = 0;//处理完毕，清除忙标志
	spin_unlock_irqrestore(&bitbang->lock, flags);
}

/***
 * spi_bitbang_transfer - default submit to transfer queue
 好了，稍微总结一下：spi的读写请求通过：spi_transfer->spi_message->spi_bitbang添加
 bitbang->queue中，被bitbang->work反方向提取出来执行(后面会提到)。
 通过queue_work(bitbang->workqueue, &bitbang->work)把bitbang-work加入bitbang->workqueue后，
 在某个合适的时间， bitbang->work将被调度运行，bitbang_work函数将被调用：
*/
//spi数据的传输就是通过调用这个方法来实现的
int spi_bitbang_transfer(struct spi_device *spi, struct spi_message *m)
{
	struct spi_bitbang	*bitbang;
	unsigned long		flags;
	int			status = 0;

	m->actual_length = 0;
	m->status = -EINPROGRESS;

	bitbang = spi_master_get_devdata(spi->master);
	/*       * 还记得spi_alloc_master函数中调用spi_master_set_devdata把struct s3c24xx_spi结构存放起来吧?     
	* 而struct spi_bitbang结构正是struct s3c24xx_spi结构所包含的第一个结构       */

	spin_lock_irqsave(&bitbang->lock, flags);
	if (!spi->max_speed_hz)
		status = -ENETDOWN;
	else {
		list_add_tail(&m->queue, &bitbang->queue);//把message加入到bitang的等待队列中
		//将携带数据的结构体spi_message挂到bitbang->queue上。每一次数据传输都将要传输的数据包装成结构体spi_message传递
//下来。bitbang是完成数据传输的重要结构体。list_add_tail(&m->queue, &bitbang->queue); 
//将该传输任务添加到工作队列头bitbang->workqueue。接下来将调用任务处理函数进一步数据处理。
		queue_work(bitbang->workqueue, &bitbang->work);//把bitbang-work加入bitbang->workqueue中，调度运行
	}
	spin_unlock_irqrestore(&bitbang->lock, flags);

	return status;
}
//EXPORT_SYMBOL_GPL(spi_bitbang_transfer);

/**----------------------------------------------------------------------*/

/***
 * spi_bitbang_start - start up a polled/bitbanging SPI master driver
 * @bitbang: driver handle
 *
 * Caller should have zero-initialized all parts of the structure, and then
 * provided callbacks for chip selection and I/O loops.  If the master has
 * a transfer method, its final step should call spi_bitbang_transfer; or,
 * that's the default if the transfer routine is not initialized.  It should
 * also set up the bus number and number of chipselects.
 *
 * For i/o loops, provide callbacks either per-word (for bitbanging, or for
 * hardware that basically exposes a shift register) or per-spi_transfer
 * (which takes better advantage of hardware like fifos or DMA engines).
 *
 * Drivers using per-word I/O loops should use (or call) spi_bitbang_setup,
 * spi_bitbang_cleanup and spi_bitbang_setup_transfer to handle those spi
 * master methods.  Those methods are the defaults if the bitbang->txrx_bufs
 * routine isn't initialized.
 *
 * This routine registers the spi_master, which will process requests in a
 * dedicated task, keeping IRQs unblocked most of the time.  To stop
 * processing those requests, call spi_bitbang_stop().
 */
int spi_bitbang_start(struct spi_bitbang *bitbang)
{
	int	status;

	if (!bitbang->master || !bitbang->chipselect)
		return -EINVAL;
/*bitbang_work       
* 初始化a work，后面再create_singlethread_workqueue，      
* 等到有数据要传输的时候，在spi_bitbang_transfer函数中通过调用queue_work(bitbang->workqueue, &bitbang->work)      
* 把work扔进workqueue中调度运行      
* 这是内核的一贯做法，在mmc/sd驱动中也是这样处理的^_^       */
	INIT_WORK(&bitbang->work, bitbang_work);
	/* 初始化自旋锁和链表头，以后用到 */
	spin_lock_init(&bitbang->lock);
	INIT_LIST_HEAD(&bitbang->queue);

	if (!bitbang->master->mode_bits)
		bitbang->master->mode_bits = SPI_CPOL | SPI_CPHA | bitbang->flags;

	if (!bitbang->master->transfer)
		bitbang->master->transfer = spi_bitbang_transfer;;//spi数据的传输就是通过调用这个方法来实现的
	/* spi_s3c24xx.c驱动中有相应的txrx_bufs处理方法，在bitbang_work中被调用 */
	if (!bitbang->txrx_bufs) {
		bitbang->use_dma = 0;
		bitbang->txrx_bufs = spi_bitbang_bufs;
		if (!bitbang->master->setup) {
			if (!bitbang->setup_transfer)
				bitbang->setup_transfer =
					 spi_bitbang_setup_transfer;
			bitbang->master->setup = spi_bitbang_setup;
			bitbang->master->cleanup = spi_bitbang_cleanup;
		}/* spi_s3c24xx.c驱动中有相应的setup处理方法，在稍后的spi_new_device中被调用 */
	} else if (!bitbang->master->setup)
		return -EINVAL;

	/** this task is the only thing to touch the SPI bits */
	bitbang->busy = 0;
	/* 创建工作者进程 */
	bitbang->workqueue = create_singlethread_workqueue(
			dev_name(bitbang->master->dev.parent));
	if (bitbang->workqueue == NULL) {
		status = -EBUSY;
		goto err1;
	}

	/** driver may get busy before register() returns, especially
	 * if someone registered boardinfo for devices
	 */
	status = spi_register_master(bitbang->master);
	if (status < 0)
		goto err2;

	return status;

err2:
	destroy_workqueue(bitbang->workqueue);
err1:
	return status;
}
//EXPORT_SYMBOL_GPL(spi_bitbang_start);

/***
 * spi_bitbang_stop - stops the task providing spi communication
 */
int spi_bitbang_stop(struct spi_bitbang *bitbang)
{
	spi_unregister_master(bitbang->master);

	WARN_ON(!list_empty(&bitbang->queue));

	destroy_workqueue(bitbang->workqueue);

	return 0;
}
//EXPORT_SYMBOL_GPL(spi_bitbang_stop);

//MODULE_LICENSE("GPL");


