/*======================================================================
    A globalfifo driver as an example of char device drivers  
    This example is to introduce poll,blocking and non-blocking access
      
    The initial developer of the original code is Baohua Song
    <author@linuxdriver.cn>. All Rights Reserved.
======================================================================*/
//#include <linux/module.h>
//#include <linux/types.h>
//#include <linux/fs.h>
//#include <linux/errno.h>
//#include <linux/mm.h>
//#include <linux/sched.h>
//#include <linux/init.h>
//#include <linux/cdev.h>
//#include <asm/io.h>
//#include <asm/system.h>
//#include <asm/uaccess.h>
//#include <linux/poll.h>

#define GLOBALFIFO_SIZE	0x1000	/*全局fifo最大4K字节*/
#define FIFO_CLEAR 0x1  /*清0全局内存的长度*/
#define GLOBALFIFO_MAJOR 253    /*预设的globalfifo的主设备号*/

static int globalfifo_major = GLOBALFIFO_MAJOR;
/*globalfifo设备结构体*/
struct globalfifo_dev                                     
{                                                        
  struct cdev cdev; /*cdev结构体*/                       
  unsigned int current_len;    /*fifo有效数据长度*/
  unsigned char mem[GLOBALFIFO_SIZE]; /*全局内存*/        
  struct semaphore sem; /*并发控制用的信号量*/           
  wait_queue_head_t r_wait; /*定义阻塞读用的等待 队列头*/     
  wait_queue_head_t w_wait; /*定义阻塞写用的等待 队列头*/     
};

struct globalfifo_dev *globalfifo_devp; /*设备结构体指针*/
/*文件打开函数*/
int globalfifo_open(struct inode *inode, struct file *filp)
{
  /*将设备结构体指针赋值给文件私有数据指针*/
  filp->private_data = globalfifo_devp;
  return 0;
}
/*文件释放函数*/
int globalfifo_release(struct inode *inode, struct file *filp)
{
  return 0;
}

/* ioctl设备控制函数 */
static int globalfifo_ioctl(struct inode *inodep, struct file *filp, unsigned
  int cmd, unsigned long arg)
{
  struct globalfifo_dev *dev = filp->private_data;/*获得设备结构体指针*/

  switch (cmd)
  {
    case FIFO_CLEAR:
    	down(&dev->sem); //获得信号量    	
      dev->current_len = 0;
      memset(dev->mem,0,GLOBALFIFO_SIZE);
      up(&dev->sem); //释放信号量
         
      printk(KERN_INFO "globalfifo is set to zero\n");      
      break;

    default:
      return  - EINVAL;
  }
  return 0;
}

//应用程序 poll, epoll, 和 select, 都用作查询对一个或多个文件描述符的读或写是否会阻塞，来调用内核的poll函数
static unsigned int globalfifo_poll(struct file *filp, poll_table *wait)//内核函数
{//轮询  非堵塞IO操作P185===P168==============================
  unsigned int mask = 0;
  struct globalfifo_dev *dev = filp->private_data; /*获得设备结构体指针*/
  
  down(&dev->sem);//获得信号量
  //阻塞IO意味着一直等待设备可访问后再访问.  非阻塞IO中使用POLL函数意味着查询设备是否可访问. 
  // 而异步通知则是意味着设备通知自身可访问实现了异步IO 
  poll_wait(filp, &dev->r_wait, wait);//添加读等待队列
  poll_wait(filp, &dev->w_wait, wait);  //
  /*fifo非空*/
  if (dev->current_len != 0)
  {
    mask |= POLLIN | POLLRDNORM; /*标示数据可读出*/
  }
  /*fifo非满*/
  if (dev->current_len != GLOBALFIFO_SIZE)
  {
    mask |= POLLOUT | POLLWRNORM; /*标示数据可写入*/
  }
     
  up(&dev->sem);//释放信号量
  return mask;
}


/*globalfifo读函数*/
static ssize_t globalfifo_read(struct file *filp, char __user *buf, size_t count,
  loff_t *ppos)
{
  int ret;
  struct globalfifo_dev *dev = filp->private_data; //获得设备结构体指针
  DECLARE_WAITQUEUE(wait, current); //定义等待队列：
//获得信号量。该函数将把sem的值减1，如果信号量sem的值非负，就直接返回，
  down(&dev->sem); //否则调用者将被挂起，直到别的任务释放该信号量才能继续往下运行。
  add_wait_queue(&dev->r_wait, &wait); //进入读等待队列头.只是把当前进程加入&wait等待队列， 但它也还在系统的运行队列中


  /* 等待FIFO非空 */
  //以下如果没有up(&dev->sem)和schedule()，则可用wait_event_interruptible(dev->r_wait,dev->current_len == 0)代替
  while  (dev->current_len == 0)//如果没有数据
  {
   	 if (filp->f_flags &O_NONBLOCK)//非阻塞
    	{
   		   ret =  - EAGAIN;
     		 goto out;//非阻塞则是跳到out处执行=====================================================
    	}  
	 //如果产生阻塞，则是执行下面的。===========================================================
 	  __set_current_state(TASK_INTERRUPTIBLE); //如果产生阻塞，则改变进程状态为睡眠
//这 条语句只是改变了进程的状态，并没有将进程置于睡眠，此时进程仍然占用CPU运行，直到如下调用shedule函数，进程才被明确置入睡眠等待状态，
//因为 睡眠的目的在于等待写进程写入数据，所以在调度schedule函数之前需要释放信号量，放弃对“临界区”的“霸占”，这就是up函数的作用。 	  
  	  up(&dev->sem);//释放信号量

   	 schedule(); //调度其他进程执行
//在调用schedule函数退出CPU后，下次唤醒后进入运行时将从schedule语句的下一条语句开始，即if (signal_pending(current)) 语句。   	 
   	 if (signal_pending(current))
   	 //如果是因为信号唤醒.检查当前进程是否有信号处理，返回不为0表示有信号需要处理。
    	{
    		  ret =  - ERESTARTSYS;//上层库函数会根据系统调用的ERESTARTSYS返回值重启该系统调用
//返回 -ERESTARTSYS 表示信号函数处理完毕后重新执行信号函数前的某个系统调用。也就是说，如果信号函数前有发生系统调
//用，在调度信号处理函数之前,内核会检查系统调用的返回值，看看是不是因为这个信号而中断了系统调用.
//如果返回值-ERESTARTSYS,并且当前调度的信号具备-ERESTARTSYS属性,系统就会在用户信号函数返回之后再执行该系统调用  	
 		  goto out2;
    	}

    	down(&dev->sem);//获得信号量
  }
//以上如果没有up(&dev->sem)和schedule()，则可用wait_event_interruptible(dev->r_wait,dev->current_len == 0)代替



  /* 拷贝到用户空间 */
  if (count > dev->current_len)
    count = dev->current_len;

  if (copy_to_user(buf, dev->mem, count))
  {
	    ret =  - EFAULT;
	    goto out;
  }
  else
  {
	    memcpy(dev->mem, dev->mem + count, dev->current_len - count); //fifo数据前移
	    dev->current_len -= count; //有效数据长度减少
	    printk(KERN_INFO "read %d bytes(s),current_len:%d\n", count, dev->current_len);
	     
	    wake_up_interruptible(&dev->w_wait); //唤醒写等待队列
	    
	    ret = count;
  }
  out: up(&dev->sem); //释放信号量
  out2:remove_wait_queue(&dev->w_wait, &wait); //从附属的等待队列头移除
  set_current_state(TASK_RUNNING);
  return ret;
}


/*globalfifo写操作*/
static ssize_t globalfifo_write(struct file *filp, const char __user *buf,
  size_t count, loff_t *ppos)
{
  struct globalfifo_dev *dev = filp->private_data; //获得设备结构体指针
  int ret;
  DECLARE_WAITQUEUE(wait, current); //定义等待队列，不是等待队列头

  down(&dev->sem); //获取信号量
  add_wait_queue(&dev->w_wait, &wait); //进入写等待队列头

  /* 等待FIFO非满 */
  //以下如果没有up(&dev->sem)和schedule()，则可用wait_event_interruptible(dev->r_wait,dev->current_len == 0)代替
  while  (dev->current_len == GLOBALFIFO_SIZE)
  {
    if (filp->f_flags &O_NONBLOCK)
    //如果是非阻塞访问
    {
      ret =  - EAGAIN;
      goto out;
    } 
    __set_current_state(TASK_INTERRUPTIBLE); //改变进程状态为睡眠
    up(&dev->sem);

    schedule(); //调度其他进程执行
    if (signal_pending(current))
    //如果是因为信号唤醒
    {
      ret =  - ERESTARTSYS;
      goto out2;
    }

    down(&dev->sem); //获得信号量
  }
//以上如果没有up(&dev->sem)和schedule()，则可用wait_event_interruptible(dev->r_wait,dev->current_len == 0)代替


  /*从用户空间拷贝到内核空间*/
  if (count > GLOBALFIFO_SIZE - dev->current_len)
    count = GLOBALFIFO_SIZE - dev->current_len;

  if (copy_from_user(dev->mem + dev->current_len, buf, count))
  {
    ret =  - EFAULT;
    goto out;
  }
  else
  {
    dev->current_len += count;
    printk(KERN_INFO "written %d bytes(s),current_len:%d\n", count, dev
      ->current_len);

    wake_up_interruptible(&dev->r_wait); //唤醒读等待队列
    
    ret = count;
  }

  out: up(&dev->sem); //释放信号量
  out2:remove_wait_queue(&dev->w_wait, &wait); //从附属的等待队列头移除
 set_current_state(TASK_RUNNING);//改变进程状态为运行
  return ret;
}


/*文件操作结构体*/
static const struct file_operations globalfifo_fops =
{
  .owner = THIS_MODULE,
  .read = globalfifo_read,
  .write = globalfifo_write,
  .ioctl = globalfifo_ioctl,
  .poll = globalfifo_poll,
  .open = globalfifo_open,
  .release = globalfifo_release,
};

/*初始化并注册cdev*/
static void globalfifo_setup_cdev(struct globalfifo_dev *dev, int index)
{
  int err, devno = MKDEV(globalfifo_major, index);

  cdev_init(&dev->cdev, &globalfifo_fops);
  dev->cdev.owner = THIS_MODULE;
  dev->cdev.ops = &globalfifo_fops;
  err = cdev_add(&dev->cdev, devno, 1);
  if (err)
    printk(KERN_NOTICE "Error %d adding LED%d", err, index);
}

/*设备驱动模块加载函数*/
int globalfifo_init(void)
{
  int ret;
  dev_t devno = MKDEV(globalfifo_major, 0);

  /* 申请设备号*/
  if (globalfifo_major)
    ret = register_chrdev_region(devno, 1, "globalfifo");
  else  /* 动态申请设备号 */
  {
    ret = alloc_chrdev_region(&devno, 0, 1, "globalfifo");
    globalfifo_major = MAJOR(devno);
  }
  if (ret < 0)
    return ret;
  /* 动态申请设备结构体的内存*/
  globalfifo_devp = kmalloc(sizeof(struct globalfifo_dev), GFP_KERNEL);
  if (!globalfifo_devp)    /*申请失败*/
  {
    ret =  - ENOMEM;
    goto fail_malloc;
  }

  memset(globalfifo_devp, 0, sizeof(struct globalfifo_dev));

  globalfifo_setup_cdev(globalfifo_devp, 0);

  init_MUTEX(&globalfifo_devp->sem);   /*初始化信号量*/
  init_waitqueue_head(&globalfifo_devp->r_wait); /*初始化读等待 队列头*/
  init_waitqueue_head(&globalfifo_devp->w_wait); /*初始化写等待 队列头*/

  return 0;

  fail_malloc: unregister_chrdev_region(devno, 1);
  return ret;
}


/*模块卸载函数*/
void globalfifo_exit(void)
{
  cdev_del(&globalfifo_devp->cdev);   /*注销cdev*/
  kfree(globalfifo_devp);     /*释放设备结构体内存*/
  unregister_chrdev_region(MKDEV(globalfifo_major, 0), 1); /*释放设备号*/
}

//MODULE_AUTHOR("Song Baohua");
//MODULE_LICENSE("Dual BSD/GPL");

module_param(globalfifo_major, int, S_IRUGO);

//module_init(globalfifo_init);
//module_exit(globalfifo_exit);
