/*
    i2c-dev.c - i2c-bus driver, char device interface
	实现了 I2C 适配器设备文件的功能，每一个 I2C 适配器都被分配一个设备
	
	(源码中没有设备驱动，如I2C总线上挂载的设备的驱动)
	
<<用户应用程序-->i2c-dev.c-->i2c-core.c-->i2c-s3c2410.c>>

	这一层主要是调用核心服务层实现对在总线上的设备的操作。 另外实现了提供给用户
级应用程序的用户操作总线的接口，应用程序可以通过该设备对这条总线上的设备进行控制。

	i2c-dev.c并没有针对特定的设备而设计， 只是提供了通用的 read()、 write()和 ioctl()
	等接口，应用层可以借用这些接口访问挂接在适配器上的 I2C设备的存储空间或寄存
	器，并控制I2C设备的工作方式。

15.4.4   Linux的i2c-dev.c文件分析 
i2c-dev.c文件完全可以被看作一个I2C设备驱动， 其结构与 15.4.1～15.4.3小节的
描述是基本一致的，不过，它实现的一个 i2c_client 是虚拟、临时的，随着设备文件
的打开而产生，并随设备文件的关闭而撤销，并没有被添加到 i2c_adapter 的 clients
链表中。i2c-dev.c 针对每个 I2C 适配器生成一个主设备号为 89 的设备文件，实现了
i2c_driver 的成员函数以及文件操作接口，所以i2c-dev.c的主体是“i2c_driver 成员函
数  + 字符设备驱动” 。 
i2c-dev.c中提供i2cdev_read()、 i2cdev_write()函数来对应用户空间要使用的read()
和 write()文件操作接口，这两个函数分别调用 I2C 核心的 i2c_master_recv()和
i2c_master_send()函数来构造一条 I2C 消息并引发适配器 algorithm 通信函数的调用，
完成消息的传输，对应于如图 15.7所示的时序。但是，很遗憾，大多数稍微复杂一点
I2C 设备的读写流程并不对应于一条消息，往往需要两条甚至更多的消息来进行一次
读写周期（即如图 15.8 所示的重复开始位 RepStart 模式） ，这种情况下，在应用层仍
然调用read()、write()文件API来读写I2C设备，将不能正确地读写。许多工程师碰到
过类似的问题，往往经过相当长时间的调试都没法解决 I2C设备的读写，连错误的原
因也无法找到，显然是对i2cdev_read()和i2cdev_write()函数的作用有所误解。 
鉴于上述原因，i2c-dev.c 中 i2cdev_read()和 i2cdev_write()函数不具备太强的通用
性，没有太大的实用价值，只能适用于非RepStart模式的情况。对于两条以上消息组
成的读写，在用户空间需要组织i2c_msg消息数组并调用 I2C_RDWR  IOCTL命令。
代码清单15.21 所示为 i2cdev_ioctl()函数的框架， 其中详细列出了 I2C_RDWR命令的
处理过程。 
    Copyright (C) 1995-97 Simon G. Vogl
    Copyright (C) 1998-99 Frodo Looijaard <frodol@dds.nl>
    Copyright (C) 2003 Greg Kroah-Hartman <greg@kroah.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

/* Note that this is a complete rewrite of Simon Vogl's i2c-dev module.
   But I have used so much of his original code and ideas that it seems
   only fair to recognize him as co-author -- Frodo */

/* The I2C_RDWR ioctl code is written by Kolja Waschk <waschk@telos.de> */

//#include <linux/kernel.h>
//#include <linux/module.h>
//#include <linux/fs.h>
//#include <linux/slab.h>
//#include <linux/init.h>
//#include <linux/list.h>
//#include <linux/i2c.h>
//#include <linux/i2c-dev.h>
//#include <linux/jiffies.h>
//#include <linux/uaccess.h>

static struct i2c_driver i2cdev_driver;

/*
 * An i2c_dev represents an i2c_adapter ... an I2C or SMBus master, not a
 * slave (i2c_client) with which messages will be exchanged.  It's coupled
 * with a character special file which is accessed by user mode drivers.
 *
 * The list of i2c_dev structures is parallel to the i2c_adapter lists
 * maintained by the driver model, and is updated using notifications
 * delivered to the i2cdev_driver.
 */
struct i2c_dev {
	struct list_head list;
	struct i2c_adapter *adap;
	struct device *dev;
};

#define I2C_MINORS	256
static LIST_HEAD(i2c_dev_list);
static DEFINE_SPINLOCK(i2c_dev_list_lock);

static struct i2c_dev *i2c_dev_get_by_minor(unsigned index)
{
	struct i2c_dev *i2c_dev;

	spin_lock(&i2c_dev_list_lock);
	list_for_each_entry(i2c_dev, &i2c_dev_list, list) {
		if (i2c_dev->adap->nr == index)
			goto found;
	}
	i2c_dev = NULL;
found:
	spin_unlock(&i2c_dev_list_lock);
	return i2c_dev;
}

static struct i2c_dev *get_free_i2c_dev(struct i2c_adapter *adap)
{
	struct i2c_dev *i2c_dev;

	if (adap->nr >= I2C_MINORS) {
		printk(KERN_ERR "i2c-dev: Out of device minors (%d)\n",
		       adap->nr);
		return ERR_PTR(-ENODEV);
	}

	i2c_dev = kzalloc(sizeof(*i2c_dev), GFP_KERNEL);
	if (!i2c_dev)
		return ERR_PTR(-ENOMEM);
	i2c_dev->adap = adap;

	spin_lock(&i2c_dev_list_lock);
	list_add_tail(&i2c_dev->list, &i2c_dev_list);
	spin_unlock(&i2c_dev_list_lock);
	return i2c_dev;
}

static void return_i2c_dev(struct i2c_dev *i2c_dev)
{
	spin_lock(&i2c_dev_list_lock);
	list_del(&i2c_dev->list);
	spin_unlock(&i2c_dev_list_lock);
	kfree(i2c_dev);
}

static ssize_t show_adapter_name(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct i2c_dev *i2c_dev = i2c_dev_get_by_minor(MINOR(dev->devt));

	if (!i2c_dev)
		return -ENODEV;
	return sprintf(buf, "%s\n", i2c_dev->adap->name);
}
static DEVICE_ATTR(name, S_IRUGO, show_adapter_name, NULL);

/* ------------------------------------------------------------------------- */

/*
 * After opening an instance of this character special file, a file
 * descriptor starts out associated only with an i2c_adapter (and bus).
 *
 * Using the I2C_RDWR ioctl(), you can then *immediately* issue i2c_msg
 * traffic to any devices on the bus used by that adapter.  That's because
 * the i2c_msg vectors embed all the addressing information they need, and
 * are submitted directly to an i2c_adapter.  However, SMBus-only adapters
 * don't support that interface.
 *
 * To use read()/write() system calls on that file descriptor, or to use
 * SMBus interfaces (and work with SMBus-only hosts!), you must first issue
 * an I2C_SLAVE (or I2C_SLAVE_FORCE) ioctl.  That configures an anonymous
 * (never registered) i2c_client so it holds the addressing information
 * needed by those system calls and by this SMBus interface.
 */

static ssize_t i2cdev_read(struct file *file, char __user *buf, size_t count,
		loff_t *offset)
{
	char *tmp;
	int ret;

	struct i2c_client *client = file->private_data;

	if (count > 8192)
		count = 8192;

	tmp = kmalloc(count, GFP_KERNEL);
	if (tmp == NULL)
		return -ENOMEM;

	pr_debug("i2c-dev: i2c-%d reading %zu bytes.\n",
		iminor(file->f_path.dentry->d_inode), count);

	ret = i2c_master_recv(client, tmp, count);//启动总线，从器件读数据
	if (ret >= 0)
		ret = copy_to_user(buf, tmp, count) ? -EFAULT : ret;
	kfree(tmp);
	return ret;
}

static ssize_t i2cdev_write(struct file *file, const char __user *buf,
		size_t count, loff_t *offset)
{
	int ret;
	char *tmp;
	struct i2c_client *client = file->private_data;

	if (count > 8192)
		count = 8192;

	tmp = kmalloc(count, GFP_KERNEL);
	if (tmp == NULL)
		return -ENOMEM;
	if (copy_from_user(tmp, buf, count)) {
		kfree(tmp);
		return -EFAULT;
	}

	pr_debug("i2c-dev: i2c-%d writing %zu bytes.\n",
		iminor(file->f_path.dentry->d_inode), count);

	ret = i2c_master_send(client, tmp, count);//启动总线，将要写的数据发送给器件。
	kfree(tmp);
	return ret;
}

static int i2cdev_check(struct device *dev, void *addrp)
{
	struct i2c_client *client = i2c_verify_client(dev);

	if (!client || client->addr != *(unsigned int *)addrp)
		return 0;

	return dev->driver ? -EBUSY : 0;
}

/* This address checking function differs from the one in i2c-core
   in that it considers an address with a registered device, but no
   driver bound to it, as NOT busy. */
static int i2cdev_check_addr(struct i2c_adapter *adapter, unsigned int addr)
{
	return device_for_each_child(&adapter->dev, &addr, i2cdev_check);
}

static noinline int i2cdev_ioctl_rdrw(struct i2c_client *client,
		unsigned long arg)
{
	struct i2c_rdwr_ioctl_data rdwr_arg;
	struct i2c_msg *rdwr_pa;
	u8 __user **data_ptrs;
	int i, res;
	//arg是从用户空间传过来的TP_data，rdwr_arg是用户空间，但&rdwr_arg是内核空间，但不知为啥没有先申请内核内存。 
	if (copy_from_user(&rdwr_arg,(struct i2c_rdwr_ioctl_data __user *)arg,sizeof(rdwr_arg)))
		return -EFAULT;

	/* 一次传入的消息太多 Put an arbitrary limit on the number of messages that can
	 * be sent at once */
	if (rdwr_arg.nmsgs > I2C_RDRW_IOCTL_MAX_MSGS)
		return -EINVAL;
	 /*获得用户空间传入的消息数组 */
	rdwr_pa = (struct i2c_msg *)kmalloc(rdwr_arg.nmsgs * sizeof(struct i2c_msg),GFP_KERNEL);//申请了结构体i2c_msg大小的内核内存，这里要注意一点，申请的内存是装载i2c_msg这个结构体的，其成员buf为指针，申请的内核内存只是装载指针变量的，所以此指针所指向的空间还是用户空间内存
	if (!rdwr_pa)
		return -ENOMEM;

	if (copy_from_user(rdwr_pa, rdwr_arg.msgs,rdwr_arg.nmsgs * sizeof(struct i2c_msg))) {//将要操作的数据用用户层复制到内核层
		kfree(rdwr_pa);
		return -EFAULT;
	}
	//申请一组指针，每一个元素指向一个msg包，这里也是申请的是装载指针变量的内核内存，所以指针指向的空间仍然是用户空间
	data_ptrs = kmalloc(rdwr_arg.nmsgs * sizeof(u8 __user *), GFP_KERNEL);
	if (data_ptrs == NULL) {
		kfree(rdwr_pa);
		return -ENOMEM;
	}

	res = 0;
	for (i = 0; i < rdwr_arg.nmsgs; i++) {
		/* Limit the size of the message to a sane amount;
		 * and don't let length change either. */
		 /* 限制消息的长度 */ 
		if ((rdwr_pa[i].len > 8192) ||(rdwr_pa[i].flags & I2C_M_RECV_LEN)) {//要操作的数据不能大于8K
			res = -EINVAL;
			break;
		}
		data_ptrs[i] = (u8 __user *)rdwr_pa[i].buf;//指针和用户层数据缓存关联
		rdwr_pa[i].buf = kmalloc(rdwr_pa[i].len, GFP_KERNEL);//根据长度申请内存，注意，此时buf地址关联上的是新申请的内存的地址
		if (rdwr_pa[i].buf == NULL) {
			res = -ENOMEM;
			break;
		}
		//将要操作的用户数据COPY到内核缓存中
        //如果是读操作，那么这里复制的数据是没有意义的
        //如果是写操作，那么这里就将要写入的数据给复制进了缓存中了
		if (copy_from_user(rdwr_pa[i].buf, data_ptrs[i],
				   rdwr_pa[i].len)) {
				++i; /* Needs to be kfreed too */
				res = -EFAULT;
			break;
		}
	}
	if (res < 0) {
		int j;
		for (j = 0; j < i; ++j)
			kfree(rdwr_pa[j].buf);
		kfree(data_ptrs);
		kfree(rdwr_pa);
		return res;
	}
	 /*把这些消息交给通信方法去处理*/ 
	res = i2c_transfer(client->adapter, rdwr_pa, rdwr_arg.nmsgs);//传输数据
	while (i-- > 0) { /*如果是读消息，把值复制到用户空间*/ //如果是读操作，则把数据复制出来
		if (res >= 0 && (rdwr_pa[i].flags & I2C_M_RD)) {
			if (copy_to_user(data_ptrs[i], rdwr_pa[i].buf,
					 rdwr_pa[i].len))
				res = -EFAULT;
		}
		kfree(rdwr_pa[i].buf);
	}
	kfree(data_ptrs);//释放内存
	kfree(rdwr_pa);
	return res;
}

static noinline int i2cdev_ioctl_smbus(struct i2c_client *client,
		unsigned long arg)
{
	struct i2c_smbus_ioctl_data data_arg;
	union i2c_smbus_data temp;
	int datasize, res;

	if (copy_from_user(&data_arg,
			   (struct i2c_smbus_ioctl_data __user *) arg,
			   sizeof(struct i2c_smbus_ioctl_data)))
		return -EFAULT;
	if ((data_arg.size != I2C_SMBUS_BYTE) &&
	    (data_arg.size != I2C_SMBUS_QUICK) &&
	    (data_arg.size != I2C_SMBUS_BYTE_DATA) &&
	    (data_arg.size != I2C_SMBUS_WORD_DATA) &&
	    (data_arg.size != I2C_SMBUS_PROC_CALL) &&
	    (data_arg.size != I2C_SMBUS_BLOCK_DATA) &&
	    (data_arg.size != I2C_SMBUS_I2C_BLOCK_BROKEN) &&
	    (data_arg.size != I2C_SMBUS_I2C_BLOCK_DATA) &&
	    (data_arg.size != I2C_SMBUS_BLOCK_PROC_CALL)) {
		dev_dbg(&client->adapter->dev,
			"size out of range (%x) in ioctl I2C_SMBUS.\n",
			data_arg.size);
		return -EINVAL;
	}
	/* Note that I2C_SMBUS_READ and I2C_SMBUS_WRITE are 0 and 1,
	   so the check is valid if size==I2C_SMBUS_QUICK too. */
	if ((data_arg.read_write != I2C_SMBUS_READ) &&
	    (data_arg.read_write != I2C_SMBUS_WRITE)) {
		dev_dbg(&client->adapter->dev,
			"read_write out of range (%x) in ioctl I2C_SMBUS.\n",
			data_arg.read_write);
		return -EINVAL;
	}

	/* Note that command values are always valid! */

	if ((data_arg.size == I2C_SMBUS_QUICK) ||
	    ((data_arg.size == I2C_SMBUS_BYTE) &&
	    (data_arg.read_write == I2C_SMBUS_WRITE)))
		/* These are special: we do not use data */
		return i2c_smbus_xfer(client->adapter, client->addr,
				      client->flags, data_arg.read_write,
				      data_arg.command, data_arg.size, NULL);

	if (data_arg.data == NULL) {
		dev_dbg(&client->adapter->dev,
			"data is NULL pointer in ioctl I2C_SMBUS.\n");
		return -EINVAL;
	}

	if ((data_arg.size == I2C_SMBUS_BYTE_DATA) ||
	    (data_arg.size == I2C_SMBUS_BYTE))
		datasize = sizeof(data_arg.data->byte);
	else if ((data_arg.size == I2C_SMBUS_WORD_DATA) ||
		 (data_arg.size == I2C_SMBUS_PROC_CALL))
		datasize = sizeof(data_arg.data->word);
	else /* size == smbus block, i2c block, or block proc. call */
		datasize = sizeof(data_arg.data->block);

	if ((data_arg.size == I2C_SMBUS_PROC_CALL) ||
	    (data_arg.size == I2C_SMBUS_BLOCK_PROC_CALL) ||
	    (data_arg.size == I2C_SMBUS_I2C_BLOCK_DATA) ||
	    (data_arg.read_write == I2C_SMBUS_WRITE)) {
		if (copy_from_user(&temp, data_arg.data, datasize))
			return -EFAULT;
	}
	if (data_arg.size == I2C_SMBUS_I2C_BLOCK_BROKEN) {
		/* Convert old I2C block commands to the new
		   convention. This preserves binary compatibility. */
		data_arg.size = I2C_SMBUS_I2C_BLOCK_DATA;
		if (data_arg.read_write == I2C_SMBUS_READ)
			temp.block[0] = I2C_SMBUS_BLOCK_MAX;
	}
	res = i2c_smbus_xfer(client->adapter, client->addr, client->flags,
	      data_arg.read_write, data_arg.command, data_arg.size, &temp);
	if (!res && ((data_arg.size == I2C_SMBUS_PROC_CALL) ||
		     (data_arg.size == I2C_SMBUS_BLOCK_PROC_CALL) ||
		     (data_arg.read_write == I2C_SMBUS_READ))) {
		if (copy_to_user(data_arg.data, &temp, datasize))
			return -EFAULT;
	}
	return res;
}

static long i2cdev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)//应用传进来的命令cmd和数据arg
{
	struct i2c_client *client = file->private_data;//获取私有数据
	unsigned long funcs;

	dev_dbg(&client->adapter->dev, "ioctl, cmd=0x%02x, arg=0x%02lx\n",cmd, arg);//打印信息到设备的LOG中

	switch (cmd) {//根据不同的命令做响应
	case I2C_SLAVE:
	case I2C_SLAVE_FORCE://通过 ioctl 函数设置器件的地址:应用使用res = ioctl(fd, I2C_SLAVE_FORCE, CHIP_ADDR); 
		/* NOTE:  devices set up to work with "new style" drivers
		 * can't use I2C_SLAVE, even when the device node is not
		 * bound to a driver.  Only I2C_SLAVE_FORCE will work.
		 *
		 * Setting the PEC flag here won't affect kernel drivers,
		 * which will be using the i2c_client node registered with
		 * the driver model core.  Likewise, when that client has
		 * the PEC flag already set, the i2c-dev driver won't see
		 * (or use) this setting.
		 */
		if ((arg > 0x3ff) ||
		    (((client->flags & I2C_M_TEN) == 0) && arg > 0x7f))
			return -EINVAL;
		if (cmd == I2C_SLAVE && i2cdev_check_addr(client->adapter, arg))
			return -EBUSY;
		/* REVISIT: address could become busy later */
		client->addr = arg;
		return 0;
	case I2C_TENBIT://设置标志，启用 10位模式，和禁止 10 位模式。
		if (arg)
			client->flags |= I2C_M_TEN;
		else
			client->flags &= ~I2C_M_TEN;
		return 0;
	case I2C_PEC:
		if (arg)
			client->flags |= I2C_CLIENT_PEC;
		else
			client->flags &= ~I2C_CLIENT_PEC;
		return 0;
	case I2C_FUNCS:
		funcs = i2c_get_functionality(client->adapter);
		return put_user(funcs, (unsigned long __user *)arg);

	case I2C_RDWR://设备的读写操作，注意传入参数的类型
		return i2cdev_ioctl_rdrw(client, arg);

	case I2C_SMBUS:
		return i2cdev_ioctl_smbus(client, arg);

	case I2C_RETRIES://设置重发次数
		client->adapter->retries = arg;
		break;
	case I2C_TIMEOUT://设置超时时间
		/* For historical reasons, user-space sets the timeout
		 * value in units of 10 ms.
		 */
		client->adapter->timeout = msecs_to_jiffies(arg * 10);
		break;
	default:
		/* NOTE:  returning a fault code here could cause trouble
		 * in buggy userspace code.  Some old kernel bugs returned
		 * zero in this case, and userspace code might accidentally
		 * have depended on that bug.
		 */
		return -ENOTTY;
	}
	return 0;
}

static int i2cdev_open(struct inode *inode, struct file *file)
{
	unsigned int minor = iminor(inode);//得到次设备号。
	struct i2c_client *client;
	struct i2c_adapter *adap;
	struct i2c_dev *i2c_dev;

	i2c_dev = i2c_dev_get_by_minor(minor);//通过次设备号，找到相应的设备。  
	if (!i2c_dev)
		return -ENODEV;

	adap = i2c_get_adapter(i2c_dev->adap->nr);//得到与该次设备相关联的 IIC 总线适配器i2c_adapter。
	if (!adap)
		return -ENODEV;

	/* This creates an anonymous i2c_client, which may later be
	 * pointed to some address using I2C_SLAVE or I2C_SLAVE_FORCE.
	 *
	 * This client is ** NEVER REGISTERED ** with the driver model
	 * or I2C core code!!  It just holds private copies of addressing
	 * information and maybe a PEC flag.
	 */
	client = kzalloc(sizeof(*client), GFP_KERNEL);//申请内存，并初始化i2c_client
	if (!client) {
		i2c_put_adapter(adap);
		return -ENOMEM;
	}
	snprintf(client->name, I2C_NAME_SIZE, "i2c-dev %d", adap->nr);
	client->driver = &i2cdev_driver;

	client->adapter = adap;
	file->private_data = client;//将i2c_client赋值给文件私有数据private_data,以后操作文件都要使用它

	return 0;
}

static int i2cdev_release(struct inode *inode, struct file *file)
{
	struct i2c_client *client = file->private_data;

	i2c_put_adapter(client->adapter);
	kfree(client);
	file->private_data = NULL;

	return 0;
}

static const struct file_operations i2cdev_fops = {
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.read		= i2cdev_read,
	.write		= i2cdev_write,
	.unlocked_ioctl	= i2cdev_ioctl,
	.open		= i2cdev_open,
	.release	= i2cdev_release,
};

/* ------------------------------------------------------------------------- */

/*
 * The legacy "i2cdev_driver" is used primarily to get notifications when
 * I2C adapters are added or removed, so that each one gets an i2c_dev
 * and is thus made available to userspace driver code.
 */

static struct class *i2c_dev_class;

static int i2cdev_attach_adapter(struct i2c_adapter *adap)
{
	struct i2c_dev *i2c_dev;
	int res;

	i2c_dev = get_free_i2c_dev(adap);
	if (IS_ERR(i2c_dev))
		return PTR_ERR(i2c_dev);

	/* register this i2c device with the driver core */
	i2c_dev->dev = device_create(i2c_dev_class, &adap->dev,
				     MKDEV(I2C_MAJOR, adap->nr), NULL,
				     "i2c-%d", adap->nr);
	if (IS_ERR(i2c_dev->dev)) {
		res = PTR_ERR(i2c_dev->dev);
		goto error;
	}
	res = device_create_file(i2c_dev->dev, &dev_attr_name);
	if (res)
		goto error_destroy;

	pr_debug("i2c-dev: adapter [%s] registered as minor %d\n",
		 adap->name, adap->nr);
	return 0;
error_destroy:
	device_destroy(i2c_dev_class, MKDEV(I2C_MAJOR, adap->nr));
error:
	return_i2c_dev(i2c_dev);
	return res;
}

static int i2cdev_detach_adapter(struct i2c_adapter *adap)
{
	struct i2c_dev *i2c_dev;

	i2c_dev = i2c_dev_get_by_minor(adap->nr);
	if (!i2c_dev) /* attach_adapter must have failed */
		return 0;

	device_remove_file(i2c_dev->dev, &dev_attr_name);
	return_i2c_dev(i2c_dev);
	device_destroy(i2c_dev_class, MKDEV(I2C_MAJOR, adap->nr));

	pr_debug("i2c-dev: adapter [%s] unregistered\n", adap->name);
	return 0;
}

static struct i2c_driver i2cdev_driver = {
	.driver = {
		.name	= "dev_driver",
	},
	.attach_adapter	= i2cdev_attach_adapter,
	.detach_adapter	= i2cdev_detach_adapter,
};

/* ------------------------------------------------------------------------- */

/*
 * module load/unload record keeping
 */

static int __init i2c_dev_init(void)
{
	int res;

	printk(KERN_INFO "i2c /dev entries driver\n");

	res = register_chrdev(I2C_MAJOR, "i2c", &i2cdev_fops);
	if (res)
		goto out;

	i2c_dev_class = class_create(THIS_MODULE, "i2c-dev");
	if (IS_ERR(i2c_dev_class)) {
		res = PTR_ERR(i2c_dev_class);
		goto out_unreg_chrdev;
	}

	res = i2c_add_driver(&i2cdev_driver);//================调用iic-core.c
	if (res)
		goto out_unreg_class;

	return 0;

out_unreg_class:
	class_destroy(i2c_dev_class);
out_unreg_chrdev:
	unregister_chrdev(I2C_MAJOR, "i2c");
out:
	printk(KERN_ERR "%s: Driver Initialisation failed\n", __FILE__);
	return res;
}

static void __exit i2c_dev_exit(void)
{
	i2c_del_driver(&i2cdev_driver);//================调用core.c
	class_destroy(i2c_dev_class);
	unregister_chrdev(I2C_MAJOR, "i2c");
}

//MODULE_AUTHOR("Frodo Looijaard <frodol@dds.nl> and "
		"Simon G. Vogl <simon@tk.uni-linz.ac.at>");
//MODULE_DESCRIPTION("I2C /dev entries driver");
//MODULE_LICENSE("GPL");

//module_init(i2c_dev_init);
//module_exit(i2c_dev_exit);
