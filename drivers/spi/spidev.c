/*
 * spidev.c -- simple synchronous userspace interface to SPI devices
 *
 * Copyright (C) 2006 SWAPP
 *	Andrea Paterniani <a.paterniani@swapp-eng.it>
 * Copyright (C) 2007 David Brownell (simplification, cleanup)
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
 6 用户空间的支持
和I2C一样，SPI也具有一个通用的设备的动程序，通过一个带有操作集file_operations的标准字符设备驱动为用户空间提供了访问接口。
此驱动模型是针对SPI设备的，只有注册board info时modalias是”spidev”的才能由此驱动访问。访问各个slave的基本框架是一致的，具体的差异将由从设备号来体现，代码部分位于drivers/spi/spidev.c。
=================================================================
  /driver/spi/spidev.c是linux内核提供的一个spi通用驱动。如果不想写具体的spi芯片驱动，使用这个驱动能给我们带来很多便利，非常方便。在内核代码下的Documentation/spi/spidev是对spidev的描述。其中还提供一个spidev_test.c的测试程序。
       使用很简单，只要在你的BSP代码中将spi_board_info的modalias定义为.modalias    = "spidev"，这样设备启动后就可以在/dev看到spidev0.0字样. 0.0 就是bus_num.chip_select（对应BSP中的设置）
       spidev注册成字符设备，可以方便的使用其提供的标准read/write/ioctl功能函数对设备进行读写设置操作。设备的全双工半双工都得以实现。具体使用可以细看spidev.c或借鉴spidev_test.c
=================================================================
1.3、 用户接口层

      drivers/spi/spidev.c向spi_bus_type总线上添加名为spidev的驱动，它的probe函数创建设备结点供用户调用，它的ioctrl提供给

       用户读写寄存器或收发数据；

       spidev驱动和sam_spi驱动都需要维护一个共同master结构体，spidev最终通过sam_spi实现底层的传输。

       spi_device和spi_add_device在spi.c中定义，它通过master定位一个具体的硬件设备，通过modalias找到它对应的驱动；这样在

       sys/bus/spi/devices下看到的设备名为spi0.0可能不和驱动名spidev相同，但是设备结构体中有master和modalias，它会根据

       modalias找到驱动。

测试程序在Documentation/spi/spidev_test.c
===========================================================
这部分代码相当于注册了一个spi实际driver，既是核心平台无关代码，又是个具体实例，我们来看下一下具体做了什么，也好学习一spi_driver的各部分具体都需要做些什么
==========================================================
为了在用户空间获得和SPI设备直接通信的设备节点，必须有两个条件要满足：首先要有SPI控制器驱动，其次是要在内核初始化的时候注册一个spi_board_info，它的modalias成员必须为“spidev”。有了这两个条件，就可以和SPI设备进行通信了。控制器的驱动一般由芯片厂家提供，开发者只需提供第二个条件。
*/

//#include <linux/init.h>
//#include <linux/module.h>
//#include <linux/ioctl.h>
//#include <linux/fs.h>
//#include <linux/device.h>
//#include <linux/err.h>
//#include <linux/list.h>
//#include <linux/errno.h>
//#include <linux/mutex.h>
//#include <linux/slab.h>

//#include <linux/spi/spi.h>
//#include <linux/spi/spidev.h>

//#include <asm/uaccess.h>


/*
 * This supports acccess to SPI devices using normal userspace I/O calls.
 * Note that while traditional UNIX/POSIX I/O semantics are half duplex,
 * and often mask message boundaries, full SPI support requires full duplex
 * transfers.  There are several kinds of internal message boundaries to
 * handle chipselect management and other protocol options.
 *
 * SPI has a character major number assigned.  We allocate minor numbers
 * dynamically using a bitmask.  You must use hotplug tools, such as udev
 * (or mdev with busybox) to create and destroy the /dev/spidevB.C device
 * nodes, since there is no fixed association of minor numbers with any
 * particular SPI bus or device.
 */
#define SPIDEV_MAJOR			153	/* assigned */
#define N_SPI_MINORS			32	/* ... up to 256 */

static DECLARE_BITMAP(minors, N_SPI_MINORS);


/* Bit masks for spi_device.mode management.  Note that incorrect
 * settings for some settings can cause *lots* of trouble for other
 * devices on a shared bus:
 *
 *  - CS_HIGH ... this device will be active when it shouldn't be
 *  - 3WIRE ... when active, it won't behave as it should
 *  - NO_CS ... there will be no explicit message boundaries; this
 *	is completely incompatible with the shared bus model
 *  - READY ... transfers may proceed when they shouldn't.
 *
 * REVISIT should changing those flags be privileged?
 */
#define SPI_MODE_MASK		(SPI_CPHA | SPI_CPOL | SPI_CS_HIGH \
				| SPI_LSB_FIRST | SPI_3WIRE | SPI_LOOP \
				| SPI_NO_CS | SPI_READY)
				
//对于spi设备结构更高层次的表述结构：
struct spidev_data {
	dev_t			devt;
	spinlock_t		spi_lock;
	struct spi_device	*spi;//指向spi设备结构
	struct list_head	device_entry;//spi设备链表device_list挂接点

	/* buffer is NULL unless this device is open (users > 0) */
	struct mutex		buf_lock;
	unsigned		users;
	u8			*buffer;
};

static LIST_HEAD(device_list);
static DEFINE_MUTEX(device_list_lock);

static unsigned bufsiz = 4096;
module_param(bufsiz, uint, S_IRUGO);
MODULE_PARM_DESC(bufsiz, "data bytes in biggest supported SPI message");

/*-------------------------------------------------------------------------*/

/*
 * We can't use the standard synchronous wrappers for file I/O; we
 * need to protect against async removal of the underlying spi_device.
 */
static void spidev_complete(void *arg)
{
	complete(arg);
}

static ssize_t
spidev_sync(struct spidev_data *spidev, struct spi_message *message)
{
	DECLARE_COMPLETION_ONSTACK(done);//设置个完成量
	int status;
	//spi_message上挂接的所有数据段传输完毕时该函数调用函数complete(arg);通知数据传输完成。
	message->complete = spidev_complete;
	 //在底层的数据传输函数中会调用函数spidev_complete来通知数据传输完成，在此留一标记
	message->context = &done;

	spin_lock_irq(&spidev->spi_lock);
	if (spidev->spi == NULL)
		status = -ESHUTDOWN;
	else//继续调用spi_async函数
		status = spi_async(spidev->spi, message);
	spin_unlock_irq(&spidev->spi_lock);

	if (status == 0) {//等待完成 
		wait_for_completion(&done);
		status = message->status;
		if (status == 0)
			status = message->actual_length;
	}
	return status;
}

static inline ssize_t
spidev_sync_write(struct spidev_data *spidev, size_t len)
{
	struct spi_transfer	t = {
			.tx_buf		= spidev->buffer,
			.len		= len,
		};
	struct spi_message	m;

	spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	return spidev_sync(spidev, &m);
}

static inline ssize_t
spidev_sync_read(struct spidev_data *spidev, size_t len)
{
	struct spi_transfer	t = {//临时传输操作结构
			.rx_buf		= spidev->buffer,
			.len		= len,
		};
	struct spi_message	m;//传输所用的信息结构   

	spi_message_init(&m);//初始化该结构   
	spi_message_add_tail(&t, &m);//加到请求队列尾 
	return spidev_sync(spidev, &m);//调用spidev_sync继续 
}

/*-------------------------------------------------------------------------*/

/* Read-only message with current device setup */
static ssize_t
spidev_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	struct spidev_data	*spidev;
	ssize_t			status = 0;

	/* chipselect only toggles at start or end of operation */
	if (count > bufsiz)
		return -EMSGSIZE;
	//得到传递的结构   
	spidev = filp->private_data;

	mutex_lock(&spidev->buf_lock);
	status = spidev_sync_read(spidev, count); //调用具体的读函数 
	if (status > 0) {
		unsigned long	missing;
		//将得到的信息传递给用户
		missing = copy_to_user(buf, spidev->buffer, status);
		if (missing == status)
			status = -EFAULT;
		else
			status = status - missing;
	}
	mutex_unlock(&spidev->buf_lock);

	return status;
}

/* Write-only message with current device setup */
static ssize_t
spidev_write(struct file *filp, const char __user *buf,
		size_t count, loff_t *f_pos)
{
	struct spidev_data	*spidev;
	ssize_t			status = 0;
	unsigned long		missing;

	/* chipselect only toggles at start or end of operation */
	if (count > bufsiz)
		return -EMSGSIZE;

	spidev = filp->private_data;

	mutex_lock(&spidev->buf_lock);
	missing = copy_from_user(spidev->buffer, buf, count);
	if (missing == 0) {
		status = spidev_sync_write(spidev, count);
	} else
		status = -EFAULT;
	mutex_unlock(&spidev->buf_lock);

	return status;
}
//该函数的功能是将用户空间传来的数据段包装成spi_message并继续向下传递。
static int spidev_message(struct spidev_data *spidev,
		struct spi_ioc_transfer *u_xfers, unsigned n_xfers)
{
	struct spi_message	msg;
	struct spi_transfer	*k_xfers;
	struct spi_transfer	*k_tmp;
	struct spi_ioc_transfer *u_tmp;
	unsigned		n, total;
	u8			*buf;
	int			status = -EFAULT;

	spi_message_init(&msg);
	k_xfers = kcalloc(n_xfers, sizeof(*k_tmp), GFP_KERNEL);//每个 spi_transfer代表一段要传输的数据
	if (k_xfers == NULL)
		return -ENOMEM;

	/* Construct spi_message, copying any tx data to bounce buffer.
	 * We walk the array of user-provided transfers, using each one
	 * to initialize a kernel version of the same transfer.
	 */
	buf = spidev->buffer;
	total = 0;
	for (n = n_xfers, k_tmp = k_xfers, u_tmp = u_xfers;
			n;
			n--, k_tmp++, u_tmp++) {
		k_tmp->len = u_tmp->len;
		//将要传输的数据分成n个数据段每个数据段用一个spi_transfer管理，u_xfers为用户空间传来的数据段
		total += k_tmp->len;//要传输的数据总量
		if (total > bufsiz) {
			status = -EMSGSIZE;
			goto done;
		}

		if (u_tmp->rx_buf) {//需要接收则分给一段用于接收数据的内存
			k_tmp->rx_buf = buf;
			if (!access_ok(VERIFY_WRITE, (u8 __user *)
						(uintptr_t) u_tmp->rx_buf,
						u_tmp->len))
				goto done;
		}
		if (u_tmp->tx_buf) {//与用于接收数据的内存是同一段内存，同一段内存可以同时
			k_tmp->tx_buf = buf;//用于存储待发送的数据和存储接收来的数据。
			if (copy_from_user(buf, (const u8 __user *)
						(uintptr_t) u_tmp->tx_buf,
					u_tmp->len))
				goto done;
		}
		buf += k_tmp->len;//指向下一段内存

		k_tmp->cs_change = !!u_tmp->cs_change;//双非操作取其逻辑值
		k_tmp->bits_per_word = u_tmp->bits_per_word;
		k_tmp->delay_usecs = u_tmp->delay_usecs;//一段数据的完全传输需要一定时间的等待
		k_tmp->speed_hz = u_tmp->speed_hz;//在启动函数setup_transfer中用到
#ifdef VERBOSE
		dev_dbg(&spidev->spi->dev,
			"  xfer len %zd %s%s%s%dbits %u usec %uHz\n",
			u_tmp->len,
			u_tmp->rx_buf ? "rx " : "",
			u_tmp->tx_buf ? "tx " : "",
			u_tmp->cs_change ? "cs " : "",
			u_tmp->bits_per_word ? : spidev->spi->bits_per_word,
			u_tmp->delay_usecs,
			u_tmp->speed_hz ? : spidev->spi->max_speed_hz);
#endif
		spi_message_add_tail(k_tmp, &msg);//将用于数据传输的数据段挂在msg上
	}

	status = spidev_sync(spidev, &msg);//调用底层函数进行数据传输
	if (status < 0)
		goto done;

	/* copy any rx data out of bounce buffer */
	buf = spidev->buffer;
	for (n = n_xfers, u_tmp = u_xfers; n; n--, u_tmp++) {
		if (u_tmp->rx_buf) {
			if (__copy_to_user((u8 __user *)
					(uintptr_t) u_tmp->rx_buf, buf,//分段向用户空间传输数据
					u_tmp->len)) {
				status = -EFAULT;
				goto done;
			}
		}
		buf += u_tmp->len;
	}
	status = total;

done:
	kfree(k_xfers);
	return status;
}

static long
spidev_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	int			err = 0;
	int			retval = 0;
	struct spidev_data	*spidev;
	struct spi_device	*spi;
	u32			tmp;
	unsigned		n_ioc;
	struct spi_ioc_transfer	*ioc;

	/* Check type and command number */
	if (_IOC_TYPE(cmd) != SPI_IOC_MAGIC)
		return -ENOTTY;
	
	/* Check access direction once here; don't repeat below.
	 * IOC_DIR is from the user perspective, while access_ok is
	 * from the kernel perspective; so they look reversed.
	 *///检测命令的幻数是否为SPI_IOC_MAGIC（"k"）_IOC_TYPE(cmd)获取命令幻数
	if (_IOC_DIR(cmd) & _IOC_READ)//检测数据传输方向是否为读
		err = !access_ok(VERIFY_WRITE,//检测要被写入数据的用户空间是否有效
				(void __user *)arg, _IOC_SIZE(cmd));
	if (err == 0 && _IOC_DIR(cmd) & _IOC_WRITE)
		err = !access_ok(VERIFY_READ,
				(void __user *)arg, _IOC_SIZE(cmd));
	if (err)
		return -EFAULT;

	/* guard against device removal before, or while,
	 * we issue this ioctl.
	 */
	spidev = filp->private_data;
	spin_lock_irq(&spidev->spi_lock);
	spi = spi_dev_get(spidev->spi);//获取spi_device并增加其引用计数
	spin_unlock_irq(&spidev->spi_lock);

	if (spi == NULL)
		return -ESHUTDOWN;

	/* use the buffer lock here for triple duty:
	 *  - prevent I/O (from us) so calling spi_setup() is safe;
	 *  - prevent concurrent SPI_IOC_WR_* from morphing
	 *    data fields while SPI_IOC_RD_* reads them;
	 *  - SPI_IOC_MESSAGE needs the buffer locked "normally".
	 */
	mutex_lock(&spidev->buf_lock);

	switch (cmd) {
	/* read requests */
	case SPI_IOC_RD_MODE://读取spi传输模式
		retval = __put_user(spi->mode & SPI_MODE_MASK,
					(__u8 __user *)arg);
		break;
	case SPI_IOC_RD_LSB_FIRST://读取数据传输顺序（高位在前还是低位在前）
		retval = __put_user((spi->mode & SPI_LSB_FIRST) ?  1 : 0,
					(__u8 __user *)arg);
		break;
	case SPI_IOC_RD_BITS_PER_WORD://读取每次传输数据的位数
		retval = __put_user(spi->bits_per_word, (__u8 __user *)arg);
		break;
	case SPI_IOC_RD_MAX_SPEED_HZ://读取数据传输速度
		retval = __put_user(spi->max_speed_hz, (__u32 __user *)arg);
		break;

	/* write requests */
	case SPI_IOC_WR_MODE://设定数据传输的spi模式
		retval = __get_user(tmp, (u8 __user *)arg);
		if (retval == 0) {
			u8	save = spi->mode;

			if (tmp & ~SPI_MODE_MASK) {
				retval = -EINVAL;
				break;
			}

			tmp |= spi->mode & ~SPI_MODE_MASK;
			spi->mode = (u8)tmp;
			retval = spi_setup(spi);//将设定的模式写入控制寄存器中
			if (retval < 0)
				spi->mode = save;
			else
				dev_dbg(&spi->dev, "spi mode %02x\n", tmp);
		}
		break;
	case SPI_IOC_WR_LSB_FIRST://设置数据传输时高位在前或是低位在前
		retval = __get_user(tmp, (__u8 __user *)arg);
		if (retval == 0) {
			u8	save = spi->mode;

			if (tmp)
				spi->mode |= SPI_LSB_FIRST;
			else
				spi->mode &= ~SPI_LSB_FIRST;
			retval = spi_setup(spi);//将设定的模式写入控制寄存器中
			if (retval < 0)
				spi->mode = save;
			else
				dev_dbg(&spi->dev, "%csb first\n",
						tmp ? 'l' : 'm');
		}
		break;
	case SPI_IOC_WR_BITS_PER_WORD://设定传输位数
		retval = __get_user(tmp, (__u8 __user *)arg);
		if (retval == 0) {
			u8	save = spi->bits_per_word;

			spi->bits_per_word = tmp;
			retval = spi_setup(spi);//将设定的模式写入寄存器中  
			if (retval < 0)
				spi->bits_per_word = save;
			else
				dev_dbg(&spi->dev, "%d bits per word\n", tmp);
		}
		break;
	case SPI_IOC_WR_MAX_SPEED_HZ://设定最大传输速度
		retval = __get_user(tmp, (__u32 __user *)arg);
		if (retval == 0) {
			u32	save = spi->max_speed_hz;

			spi->max_speed_hz = tmp;
			retval = spi_setup(spi);//将设定的模式写入寄存器中
			if (retval < 0)
				spi->max_speed_hz = save;
			else
				dev_dbg(&spi->dev, "%d Hz (max)\n", tmp);
		}
		break;

	default:
		/* segmented and/or full-duplex I/O request */
		if (_IOC_NR(cmd) != _IOC_NR(SPI_IOC_MESSAGE(0))//查看是否为数据传输命令
				|| _IOC_DIR(cmd) != _IOC_WRITE) {
			retval = -ENOTTY;
			break;
		}
		//_IOC_SIZE(cmd)从命令参数中解析出用户数据大小
		tmp = _IOC_SIZE(cmd);
		if ((tmp % sizeof(struct spi_ioc_transfer)) != 0) {
			retval = -EINVAL;
			break;
		}
		n_ioc = tmp / sizeof(struct spi_ioc_transfer); //将要传输的数据分成n个传输数据段

		if (n_ioc == 0)
			break;

		/* copy into scratch area */
		ioc = kmalloc(tmp, GFP_KERNEL);//获取n个数据段的数据管理结构体的内存空间
		if (!ioc) {
			retval = -ENOMEM;
			break;
		}
		if (__copy_from_user(ioc, (void __user *)arg, tmp)) {//从用户空间获取数据管理结构体的初始化值
			kfree(ioc);
			retval = -EFAULT;
			break;
		}

		/* translate to spi_message, execute */
		retval = spidev_message(spidev, ioc, n_ioc);//数据传输       
		kfree(ioc);
		break;
	}

	mutex_unlock(&spidev->buf_lock);
	spi_dev_put(spi);
	return retval;
}
/* Open操作是用户空间程序和内核驱动交互的第一步，首先会遍历device_list链表，然后根据设备节点号进行匹配查找对应的spidev_data节点从而找到相应的从设备，然后给spidev分配buffer空间，最后filp的private_data被赋值为spidev，而最终返回给用户空间的就是这个struct file结构体。对于SPI 驱动来说，用户空间所获得的就是spidev这个关键信息，在其中可以找到所有有关的信息如spidev的SPI设备。
       用open函数将spidev设备打开以后，就可以通过ioctl函数的各种命令来对modalias为”spidev”的SPI设备进行读写等操作，也可以通过 read和write函数完成对SPI设备的读写。
       对SPI设备的具体操作在这里不再具体阐述，可以参看spidev.c源代码。
*/
static int spidev_open(struct inode *inode, struct file *filp)
{
	struct spidev_data	*spidev;
	int			status = -ENXIO;

	mutex_lock(&device_list_lock);
	//遍历spi设备链表device_list，根据设备号找到spidev_data结构
	list_for_each_entry(spidev, &device_list, device_entry) {
		if (spidev->devt == inode->i_rdev) {
			status = 0;
			break;
		}
	}
	if (status == 0) {//buffer为空，为其申请内存
		if (!spidev->buffer) {
			spidev->buffer = kmalloc(bufsiz, GFP_KERNEL);
			if (!spidev->buffer) {
				dev_dbg(&spidev->spi->dev, "open/ENOMEM\n");
				status = -ENOMEM;
			}
		}
		if (status == 0) {//设备用户使用量+1
			spidev->users++;
			filp->private_data = spidev;//传到filp的私有成员，在read，write的时候可以从其得到该结构   
			nonseekable_open(inode, filp);
		}
	} else
		pr_debug("spidev: nothing for minor %d\n", iminor(inode));

	mutex_unlock(&device_list_lock);
	return status;
}

static int spidev_release(struct inode *inode, struct file *filp)
{
	struct spidev_data	*spidev;
	int			status = 0;

	mutex_lock(&device_list_lock);
	spidev = filp->private_data;
	filp->private_data = NULL;

	/* last close? */
	spidev->users--;
	if (!spidev->users) {
		int		dofree;

		kfree(spidev->buffer);
		spidev->buffer = NULL;

		/* ... after we unbound from the underlying device? */
		spin_lock_irq(&spidev->spi_lock);
		dofree = (spidev->spi == NULL);
		spin_unlock_irq(&spidev->spi_lock);

		if (dofree)
			kfree(spidev);
	}
	mutex_unlock(&device_list_lock);

	return status;
}
/*该操作集是用户空间访问该字符设备的接口。
然后调用函数spi_register_driver(&spidev_spi)将spidev_spi 驱动注册到SPI 核心层中，spidev_spi驱动注册过程中会扫描SPI总线上的所有SPI设备，一旦扫描到关键字modalias为”spidev”的SPI设备时，则与该SPI驱动匹配，匹配函数spidev_probe()被调用，
        */
static const struct file_operations spidev_fops = {
	.owner =	THIS_MODULE,
	/* REVISIT switch to aio primitives, so that userspace
	 * gets more complete API coverage.  It'll simplify things
	 * too, except for the locking.
	 */
	.write =	spidev_write,
	.read =		spidev_read,
	.unlocked_ioctl = spidev_ioctl,
	.open =		spidev_open,
	.release =	spidev_release,
};

/*-------------------------------------------------------------------------*/

/* The main reason to have this class is to make mdev/udev create the
 * /dev/spidevB.C character device nodes exposing our userspace API.
 * It also simplifies memory management.
 */

static struct class *spidev_class;

/*-------------------------------------------------------------------------*/

static int __devinit spidev_probe(struct spi_device *spi)//匹配modalias字段为"spidev"的spi的设备
{
	struct spidev_data	*spidev;
	int			status;
	unsigned long		minor;

	/* Allocate driver data */
	//申请spidev_data所需内存，前面已经讲过该结构
	spidev = kzalloc(sizeof(*spidev), GFP_KERNEL);
	if (!spidev)
		return -ENOMEM;

	/* Initialize the driver data */
	spidev->spi = spi;
	spin_lock_init(&spidev->spi_lock);
	mutex_init(&spidev->buf_lock);

	INIT_LIST_HEAD(&spidev->device_entry);

	/* If we can allocate a minor number, hook up this device.
	 * Reusing minors is fine so long as udev or mdev is working.
	 */
	mutex_lock(&device_list_lock);
	//找到一个最小的次设备号//addr为内存区的起始地址，size为要查找的最大长度
	minor = find_first_zero_bit(minors, N_SPI_MINORS);
	if (minor < N_SPI_MINORS) {
		struct device *dev;
		//下面两句用于在sys/class/spidev下产生类似于spidev%d.%d形式的节点，
		//这样，udev等工具就可以自动在dev下创建相应设备号的设备节点  
		spidev->devt = MKDEV(SPIDEV_MAJOR, minor);
		dev = device_create(spidev_class, &spi->dev, spidev->devt,
				    spidev, "spidev%d.%d",
				    spi->master->bus_num, spi->chip_select);
		status = IS_ERR(dev) ? PTR_ERR(dev) : 0;
	} else {
		dev_dbg(&spi->dev, "no minor number available!\n");
		status = -ENODEV;
	}	
	//如果成功标明刚才的次设备号已被占用,并且将该设备挂接到device_list链表
	if (status == 0) {
		set_bit(minor, minors);
		list_add(&spidev->device_entry, &device_list);
	}
	mutex_unlock(&device_list_lock);
	//设置spi->dev->p = spidev   
	if (status == 0)
		spi_set_drvdata(spi, spidev);
	else
		kfree(spidev);

	return status;
}

static int __devexit spidev_remove(struct spi_device *spi)
{
	struct spidev_data	*spidev = spi_get_drvdata(spi);

	/* make sure ops on existing fds can abort cleanly */
	spin_lock_irq(&spidev->spi_lock);
	spidev->spi = NULL;
	spi_set_drvdata(spi, NULL);
	spin_unlock_irq(&spidev->spi_lock);

	/* prevent new opens */
	mutex_lock(&device_list_lock);
	list_del(&spidev->device_entry);
	device_destroy(spidev_class, spidev->devt);
	clear_bit(MINOR(spidev->devt), minors);
	if (spidev->users == 0)
		kfree(spidev);
	mutex_unlock(&device_list_lock);

	return 0;
}

static struct spi_driver spidev_spi_driver = {
	.driver = {
		.name =		"spidev",//匹配modalias字段为"spidev"的spi的设备，见Mach-smdkc110.c (arch\arm\mach-s5pv210)
		.owner =	THIS_MODULE,
	},
	.probe =	spidev_probe,
	.remove =	__devexit_p(spidev_remove),

	/* NOTE:  suspend/resume methods are not necessary here.
	 * We don't do anything except pass the requests to/from
	 * the underlying controller.  The refrigerator handles
	 * most issues; the controller driver handles the rest.
	 */
};

/*-------------------------------------------------------------------------*/

static int __init spidev_init(void)
{
	int status;

	/* Claim our 256 reserved device numbers.  Then register a class
	 * that will key udev/mdev to add/remove /dev nodes.  Last, register
	 * the driver which manages those device numbers.
	 */
	BUILD_BUG_ON(N_SPI_MINORS > 256);
	//首先注册了一个主设备号为SPIDEV_MAJOR，操作集为spidev_fops，名字为“spi”的字符设备。在文件drivers/spi/spidev.c中，SPI_MAJOR被定义为153。
	status = register_chrdev(SPIDEV_MAJOR, "spi", &spidev_fops);
	if (status < 0)
		return status;
	//在sys/class下创建spidev类
	spidev_class = class_create(THIS_MODULE, "spidev");
	if (IS_ERR(spidev_class)) {
		unregister_chrdev(SPIDEV_MAJOR, spidev_spi_driver.driver.name);//使用"spidev"(即spidev_spi_driver.driver.name) 注销字符设备
		return PTR_ERR(spidev_class);
	}
	 /*注册spidev的driver,可与modalias字段为"spidev"的spi_device匹配*/  
	status = spi_register_driver(&spidev_spi_driver);
	if (status < 0) {
		class_destroy(spidev_class);
		unregister_chrdev(SPIDEV_MAJOR, spidev_spi_driver.driver.name);
	}
	return status;
}
//module_init(spidev_init);

static void __exit spidev_exit(void)
{
	spi_unregister_driver(&spidev_spi_driver);
	class_destroy(spidev_class);
	unregister_chrdev(SPIDEV_MAJOR, spidev_spi_driver.driver.name);
}
//module_exit(spidev_exit);

//MODULE_AUTHOR("Andrea Paterniani, <a.paterniani@swapp-eng.it>");
//MODULE_DESCRIPTION("User mode SPI device interface");
//MODULE_LICENSE("GPL");
//MODULE_ALIAS("spi:spidev");
