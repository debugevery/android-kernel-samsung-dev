#ifndef	__SPI_BITBANG_H
#define	__SPI_BITBANG_H

//#include <linux/workqueue.h>

struct spi_bitbang {
	struct workqueue_struct	*workqueue; //工作队列头
	struct work_struct	work; //每一次数据传输都传递下来一个spi_message，都向工作队列头添加一个任务。
//挂接spi_message，如果上一次的spi_message还没处理完接下来的spi_message就挂接在 queue上等待处理。
	spinlock_t		lock;
	struct list_head	queue;
	u8			busy; //忙碌标识。
	u8			use_dma;
	u8			flags;		/* extra spi->mode support */

	struct spi_master	*master;

	/* setup_transfer() changes clock and/or wordsize to match settings
	 * for this transfer; zeroes restore defaults from spi_device.
	 *///一下三个函数都是在函数s3c24xx_spi_probe()中被初始化的。
	int	(*setup_transfer)(struct spi_device *spi, //设置数据传输波特率
			struct spi_transfer *t);

	void	(*chipselect)(struct spi_device *spi, int is_on);//将数据传输模式写入控制寄存器。
#define	BITBANG_CS_ACTIVE	1	/* normally nCS, active low */
#define	BITBANG_CS_INACTIVE	0

	/* txrx_bufs() may handle dma mapping for transfers that don't
	 * already have one (transfer.{tx,rx}_dma is zero), or use PIO
	 //向SPTDAT中写入要传输的第一个数据，数据传输是通过中断方式完成的，只要进行一次中断触发，以后向SPTDAT中写数据的工作就在中断处理函数中进行。
*/
	int	(*txrx_bufs)(struct spi_device *spi, struct spi_transfer *t);

	/* txrx_word[SPI_MODE_*]() just looks like a shift register */
	u32	(*txrx_word[4])(struct spi_device *spi,
			unsigned nsecs,
			u32 word, u8 bits);
};

/* you can call these default bitbang->master methods from your custom
 * methods, if you like.
 */
extern int spi_bitbang_setup(struct spi_device *spi);
extern void spi_bitbang_cleanup(struct spi_device *spi);
extern int spi_bitbang_transfer(struct spi_device *spi, struct spi_message *m);
extern int spi_bitbang_setup_transfer(struct spi_device *spi,
				      struct spi_transfer *t);

/* start or stop queue processing */
extern int spi_bitbang_start(struct spi_bitbang *spi);
extern int spi_bitbang_stop(struct spi_bitbang *spi);

#endif	/* __SPI_BITBANG_H */
