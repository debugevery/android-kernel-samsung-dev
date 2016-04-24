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
 6 �û��ռ��֧��
��I2Cһ����SPIҲ����һ��ͨ�õ��豸�Ķ�����ͨ��һ�����в�����file_operations�ı�׼�ַ��豸����Ϊ�û��ռ��ṩ�˷��ʽӿڡ�
������ģ�������SPI�豸�ģ�ֻ��ע��board infoʱmodalias�ǡ�spidev���Ĳ����ɴ��������ʡ����ʸ���slave�Ļ��������һ�µģ�����Ĳ��콫�ɴ��豸�������֣����벿��λ��drivers/spi/spidev.c��
=================================================================
  /driver/spi/spidev.c��linux�ں��ṩ��һ��spiͨ���������������д�����spiоƬ������ʹ����������ܸ����Ǵ����ܶ�������ǳ����㡣���ں˴����µ�Documentation/spi/spidev�Ƕ�spidev�����������л��ṩһ��spidev_test.c�Ĳ��Գ���
       ʹ�úܼ򵥣�ֻҪ�����BSP�����н�spi_board_info��modalias����Ϊ.modalias    = "spidev"�������豸������Ϳ�����/dev����spidev0.0����. 0.0 ����bus_num.chip_select����ӦBSP�е����ã�
       spidevע����ַ��豸�����Է����ʹ�����ṩ�ı�׼read/write/ioctl���ܺ������豸���ж�д���ò������豸��ȫ˫����˫��������ʵ�֡�����ʹ�ÿ���ϸ��spidev.c����spidev_test.c
=================================================================
1.3�� �û��ӿڲ�

      drivers/spi/spidev.c��spi_bus_type�����������Ϊspidev������������probe���������豸��㹩�û����ã�����ioctrl�ṩ��

       �û���д�Ĵ������շ����ݣ�

       spidev������sam_spi��������Ҫά��һ����ͬmaster�ṹ�壬spidev����ͨ��sam_spiʵ�ֵײ�Ĵ��䡣

       spi_device��spi_add_device��spi.c�ж��壬��ͨ��master��λһ�������Ӳ���豸��ͨ��modalias�ҵ�����Ӧ��������������

       sys/bus/spi/devices�¿������豸��Ϊspi0.0���ܲ���������spidev��ͬ�������豸�ṹ������master��modalias���������

       modalias�ҵ�������

���Գ�����Documentation/spi/spidev_test.c
===========================================================
�ⲿ�ִ����൱��ע����һ��spiʵ��driver�����Ǻ���ƽ̨�޹ش��룬���Ǹ�����ʵ��������������һ�¾�������ʲô��Ҳ��ѧϰһspi_driver�ĸ����־��嶼��Ҫ��Щʲô
==========================================================
Ϊ�����û��ռ��ú�SPI�豸ֱ��ͨ�ŵ��豸�ڵ㣬��������������Ҫ���㣺����Ҫ��SPI�����������������Ҫ���ں˳�ʼ����ʱ��ע��һ��spi_board_info������modalias��Ա����Ϊ��spidev���������������������Ϳ��Ժ�SPI�豸����ͨ���ˡ�������������һ����оƬ�����ṩ��������ֻ���ṩ�ڶ���������
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
				
//����spi�豸�ṹ���߲�εı����ṹ��
struct spidev_data {
	dev_t			devt;
	spinlock_t		spi_lock;
	struct spi_device	*spi;//ָ��spi�豸�ṹ
	struct list_head	device_entry;//spi�豸����device_list�ҽӵ�

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
	DECLARE_COMPLETION_ONSTACK(done);//���ø������
	int status;
	//spi_message�Ϲҽӵ��������ݶδ������ʱ�ú������ú���complete(arg);֪ͨ���ݴ�����ɡ�
	message->complete = spidev_complete;
	 //�ڵײ�����ݴ��亯���л���ú���spidev_complete��֪ͨ���ݴ�����ɣ��ڴ���һ���
	message->context = &done;

	spin_lock_irq(&spidev->spi_lock);
	if (spidev->spi == NULL)
		status = -ESHUTDOWN;
	else//��������spi_async����
		status = spi_async(spidev->spi, message);
	spin_unlock_irq(&spidev->spi_lock);

	if (status == 0) {//�ȴ���� 
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
	struct spi_transfer	t = {//��ʱ��������ṹ
			.rx_buf		= spidev->buffer,
			.len		= len,
		};
	struct spi_message	m;//�������õ���Ϣ�ṹ   

	spi_message_init(&m);//��ʼ���ýṹ   
	spi_message_add_tail(&t, &m);//�ӵ��������β 
	return spidev_sync(spidev, &m);//����spidev_sync���� 
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
	//�õ����ݵĽṹ   
	spidev = filp->private_data;

	mutex_lock(&spidev->buf_lock);
	status = spidev_sync_read(spidev, count); //���þ���Ķ����� 
	if (status > 0) {
		unsigned long	missing;
		//���õ�����Ϣ���ݸ��û�
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
//�ú����Ĺ����ǽ��û��ռ䴫�������ݶΰ�װ��spi_message���������´��ݡ�
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
	k_xfers = kcalloc(n_xfers, sizeof(*k_tmp), GFP_KERNEL);//ÿ�� spi_transfer����һ��Ҫ���������
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
		//��Ҫ��������ݷֳ�n�����ݶ�ÿ�����ݶ���һ��spi_transfer����u_xfersΪ�û��ռ䴫�������ݶ�
		total += k_tmp->len;//Ҫ�������������
		if (total > bufsiz) {
			status = -EMSGSIZE;
			goto done;
		}

		if (u_tmp->rx_buf) {//��Ҫ������ָ�һ�����ڽ������ݵ��ڴ�
			k_tmp->rx_buf = buf;
			if (!access_ok(VERIFY_WRITE, (u8 __user *)
						(uintptr_t) u_tmp->rx_buf,
						u_tmp->len))
				goto done;
		}
		if (u_tmp->tx_buf) {//�����ڽ������ݵ��ڴ���ͬһ���ڴ棬ͬһ���ڴ����ͬʱ
			k_tmp->tx_buf = buf;//���ڴ洢�����͵����ݺʹ洢�����������ݡ�
			if (copy_from_user(buf, (const u8 __user *)
						(uintptr_t) u_tmp->tx_buf,
					u_tmp->len))
				goto done;
		}
		buf += k_tmp->len;//ָ����һ���ڴ�

		k_tmp->cs_change = !!u_tmp->cs_change;//˫�ǲ���ȡ���߼�ֵ
		k_tmp->bits_per_word = u_tmp->bits_per_word;
		k_tmp->delay_usecs = u_tmp->delay_usecs;//һ�����ݵ���ȫ������Ҫһ��ʱ��ĵȴ�
		k_tmp->speed_hz = u_tmp->speed_hz;//����������setup_transfer���õ�
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
		spi_message_add_tail(k_tmp, &msg);//���������ݴ�������ݶι���msg��
	}

	status = spidev_sync(spidev, &msg);//���õײ㺯���������ݴ���
	if (status < 0)
		goto done;

	/* copy any rx data out of bounce buffer */
	buf = spidev->buffer;
	for (n = n_xfers, u_tmp = u_xfers; n; n--, u_tmp++) {
		if (u_tmp->rx_buf) {
			if (__copy_to_user((u8 __user *)
					(uintptr_t) u_tmp->rx_buf, buf,//�ֶ����û��ռ䴫������
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
	 *///�������Ļ����Ƿ�ΪSPI_IOC_MAGIC��"k"��_IOC_TYPE(cmd)��ȡ�������
	if (_IOC_DIR(cmd) & _IOC_READ)//������ݴ��䷽���Ƿ�Ϊ��
		err = !access_ok(VERIFY_WRITE,//���Ҫ��д�����ݵ��û��ռ��Ƿ���Ч
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
	spi = spi_dev_get(spidev->spi);//��ȡspi_device�����������ü���
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
	case SPI_IOC_RD_MODE://��ȡspi����ģʽ
		retval = __put_user(spi->mode & SPI_MODE_MASK,
					(__u8 __user *)arg);
		break;
	case SPI_IOC_RD_LSB_FIRST://��ȡ���ݴ���˳�򣨸�λ��ǰ���ǵ�λ��ǰ��
		retval = __put_user((spi->mode & SPI_LSB_FIRST) ?  1 : 0,
					(__u8 __user *)arg);
		break;
	case SPI_IOC_RD_BITS_PER_WORD://��ȡÿ�δ������ݵ�λ��
		retval = __put_user(spi->bits_per_word, (__u8 __user *)arg);
		break;
	case SPI_IOC_RD_MAX_SPEED_HZ://��ȡ���ݴ����ٶ�
		retval = __put_user(spi->max_speed_hz, (__u32 __user *)arg);
		break;

	/* write requests */
	case SPI_IOC_WR_MODE://�趨���ݴ����spiģʽ
		retval = __get_user(tmp, (u8 __user *)arg);
		if (retval == 0) {
			u8	save = spi->mode;

			if (tmp & ~SPI_MODE_MASK) {
				retval = -EINVAL;
				break;
			}

			tmp |= spi->mode & ~SPI_MODE_MASK;
			spi->mode = (u8)tmp;
			retval = spi_setup(spi);//���趨��ģʽд����ƼĴ�����
			if (retval < 0)
				spi->mode = save;
			else
				dev_dbg(&spi->dev, "spi mode %02x\n", tmp);
		}
		break;
	case SPI_IOC_WR_LSB_FIRST://�������ݴ���ʱ��λ��ǰ���ǵ�λ��ǰ
		retval = __get_user(tmp, (__u8 __user *)arg);
		if (retval == 0) {
			u8	save = spi->mode;

			if (tmp)
				spi->mode |= SPI_LSB_FIRST;
			else
				spi->mode &= ~SPI_LSB_FIRST;
			retval = spi_setup(spi);//���趨��ģʽд����ƼĴ�����
			if (retval < 0)
				spi->mode = save;
			else
				dev_dbg(&spi->dev, "%csb first\n",
						tmp ? 'l' : 'm');
		}
		break;
	case SPI_IOC_WR_BITS_PER_WORD://�趨����λ��
		retval = __get_user(tmp, (__u8 __user *)arg);
		if (retval == 0) {
			u8	save = spi->bits_per_word;

			spi->bits_per_word = tmp;
			retval = spi_setup(spi);//���趨��ģʽд��Ĵ�����  
			if (retval < 0)
				spi->bits_per_word = save;
			else
				dev_dbg(&spi->dev, "%d bits per word\n", tmp);
		}
		break;
	case SPI_IOC_WR_MAX_SPEED_HZ://�趨������ٶ�
		retval = __get_user(tmp, (__u32 __user *)arg);
		if (retval == 0) {
			u32	save = spi->max_speed_hz;

			spi->max_speed_hz = tmp;
			retval = spi_setup(spi);//���趨��ģʽд��Ĵ�����
			if (retval < 0)
				spi->max_speed_hz = save;
			else
				dev_dbg(&spi->dev, "%d Hz (max)\n", tmp);
		}
		break;

	default:
		/* segmented and/or full-duplex I/O request */
		if (_IOC_NR(cmd) != _IOC_NR(SPI_IOC_MESSAGE(0))//�鿴�Ƿ�Ϊ���ݴ�������
				|| _IOC_DIR(cmd) != _IOC_WRITE) {
			retval = -ENOTTY;
			break;
		}
		//_IOC_SIZE(cmd)����������н������û����ݴ�С
		tmp = _IOC_SIZE(cmd);
		if ((tmp % sizeof(struct spi_ioc_transfer)) != 0) {
			retval = -EINVAL;
			break;
		}
		n_ioc = tmp / sizeof(struct spi_ioc_transfer); //��Ҫ��������ݷֳ�n���������ݶ�

		if (n_ioc == 0)
			break;

		/* copy into scratch area */
		ioc = kmalloc(tmp, GFP_KERNEL);//��ȡn�����ݶε����ݹ���ṹ����ڴ�ռ�
		if (!ioc) {
			retval = -ENOMEM;
			break;
		}
		if (__copy_from_user(ioc, (void __user *)arg, tmp)) {//���û��ռ��ȡ���ݹ���ṹ��ĳ�ʼ��ֵ
			kfree(ioc);
			retval = -EFAULT;
			break;
		}

		/* translate to spi_message, execute */
		retval = spidev_message(spidev, ioc, n_ioc);//���ݴ���       
		kfree(ioc);
		break;
	}

	mutex_unlock(&spidev->buf_lock);
	spi_dev_put(spi);
	return retval;
}
/* Open�������û��ռ������ں����������ĵ�һ�������Ȼ����device_list����Ȼ������豸�ڵ�Ž���ƥ����Ҷ�Ӧ��spidev_data�ڵ�Ӷ��ҵ���Ӧ�Ĵ��豸��Ȼ���spidev����buffer�ռ䣬���filp��private_data����ֵΪspidev�������շ��ظ��û��ռ�ľ������struct file�ṹ�塣����SPI ������˵���û��ռ�����õľ���spidev����ؼ���Ϣ�������п����ҵ������йص���Ϣ��spidev��SPI�豸��
       ��open������spidev�豸���Ժ󣬾Ϳ���ͨ��ioctl�����ĸ�����������modaliasΪ��spidev����SPI�豸���ж�д�Ȳ�����Ҳ����ͨ�� read��write������ɶ�SPI�豸�Ķ�д��
       ��SPI�豸�ľ�����������ﲻ�پ�����������Բο�spidev.cԴ���롣
*/
static int spidev_open(struct inode *inode, struct file *filp)
{
	struct spidev_data	*spidev;
	int			status = -ENXIO;

	mutex_lock(&device_list_lock);
	//����spi�豸����device_list�������豸���ҵ�spidev_data�ṹ
	list_for_each_entry(spidev, &device_list, device_entry) {
		if (spidev->devt == inode->i_rdev) {
			status = 0;
			break;
		}
	}
	if (status == 0) {//bufferΪ�գ�Ϊ�������ڴ�
		if (!spidev->buffer) {
			spidev->buffer = kmalloc(bufsiz, GFP_KERNEL);
			if (!spidev->buffer) {
				dev_dbg(&spidev->spi->dev, "open/ENOMEM\n");
				status = -ENOMEM;
			}
		}
		if (status == 0) {//�豸�û�ʹ����+1
			spidev->users++;
			filp->private_data = spidev;//����filp��˽�г�Ա����read��write��ʱ����Դ���õ��ýṹ   
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
/*�ò��������û��ռ���ʸ��ַ��豸�Ľӿڡ�
Ȼ����ú���spi_register_driver(&spidev_spi)��spidev_spi ����ע�ᵽSPI ���Ĳ��У�spidev_spi����ע������л�ɨ��SPI�����ϵ�����SPI�豸��һ��ɨ�赽�ؼ���modaliasΪ��spidev����SPI�豸ʱ�������SPI����ƥ�䣬ƥ�亯��spidev_probe()�����ã�
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

static int __devinit spidev_probe(struct spi_device *spi)//ƥ��modalias�ֶ�Ϊ"spidev"��spi���豸
{
	struct spidev_data	*spidev;
	int			status;
	unsigned long		minor;

	/* Allocate driver data */
	//����spidev_data�����ڴ棬ǰ���Ѿ������ýṹ
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
	//�ҵ�һ����С�Ĵ��豸��//addrΪ�ڴ�������ʼ��ַ��sizeΪҪ���ҵ���󳤶�
	minor = find_first_zero_bit(minors, N_SPI_MINORS);
	if (minor < N_SPI_MINORS) {
		struct device *dev;
		//��������������sys/class/spidev�²���������spidev%d.%d��ʽ�Ľڵ㣬
		//������udev�ȹ��߾Ϳ����Զ���dev�´�����Ӧ�豸�ŵ��豸�ڵ�  
		spidev->devt = MKDEV(SPIDEV_MAJOR, minor);
		dev = device_create(spidev_class, &spi->dev, spidev->devt,
				    spidev, "spidev%d.%d",
				    spi->master->bus_num, spi->chip_select);
		status = IS_ERR(dev) ? PTR_ERR(dev) : 0;
	} else {
		dev_dbg(&spi->dev, "no minor number available!\n");
		status = -ENODEV;
	}	
	//����ɹ������ղŵĴ��豸���ѱ�ռ��,���ҽ����豸�ҽӵ�device_list����
	if (status == 0) {
		set_bit(minor, minors);
		list_add(&spidev->device_entry, &device_list);
	}
	mutex_unlock(&device_list_lock);
	//����spi->dev->p = spidev   
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
		.name =		"spidev",//ƥ��modalias�ֶ�Ϊ"spidev"��spi���豸����Mach-smdkc110.c (arch\arm\mach-s5pv210)
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
	//����ע����һ�����豸��ΪSPIDEV_MAJOR��������Ϊspidev_fops������Ϊ��spi�����ַ��豸�����ļ�drivers/spi/spidev.c�У�SPI_MAJOR������Ϊ153��
	status = register_chrdev(SPIDEV_MAJOR, "spi", &spidev_fops);
	if (status < 0)
		return status;
	//��sys/class�´���spidev��
	spidev_class = class_create(THIS_MODULE, "spidev");
	if (IS_ERR(spidev_class)) {
		unregister_chrdev(SPIDEV_MAJOR, spidev_spi_driver.driver.name);//ʹ��"spidev"(��spidev_spi_driver.driver.name) ע���ַ��豸
		return PTR_ERR(spidev_class);
	}
	 /*ע��spidev��driver,����modalias�ֶ�Ϊ"spidev"��spi_deviceƥ��*/  
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
