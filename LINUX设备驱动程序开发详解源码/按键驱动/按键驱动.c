//12.1.2  按键驱动中的数据结构
//设备驱动中主要要设计的数据结构是设备结构体，按键的设备结构体中应包含一个缓冲区，因为多次按键可能无法被及时处理
//，可以用该缓冲区缓存按键。此外，在按键设备结构体中，还包含按键状态标志和一个实现过程中要借助的等待队列、cdev
//结构体。为了实现软件延时，定时器也是必要的，但可以不包含在设备结构体中。代码清单12.1给出了按键设备结构体及定
//时器。
//代码清单12.1  按键驱动的设备结构体、定时器
#define MAX_KEY_BUF 16 //按键缓冲区大小
typedef unsigned char KEY_RET;
//设备结构体：
 typedef struct keydev
{
    struct cdev cdev;     //cdev结构体
    unsigned int keyStatus[KEY_NUM];// //4个按键的按键状态
    KEY_RET buf[MAX_KEY_BUF]; //按键缓冲区
    unsigned int head, tail; //按键缓冲区头和尾
    wait_queue_head_t wq; //等待队列头
 } KEY_DEV;
 static struct timer_list key_timer[KEY_NUM];//4//按键去抖定时器
//在按键设备驱动中，可用一个结构体记录每个按键所对应的中断/GPIO引脚及键值，如代码清单12.2所示。
//代码清单12.2  按键硬件资源、键值信息结构体
  static struct key_info
  {
    int irq_no;     //中断号
    unsigned int gpio_port; //GPIO端口
    int key_no;    //键值
  } key_info_tab[4] =
  {
     /*按键所使用的CPU资源*/
    {
     IRQ_EINT10, GPIO_G2, 1
   }
 ，
   {
   IRQ_EINT13, GPIO_G5, 2
   }
   ,
   {
     IRQ_EINT14, GPIO_G6, 3
   }
   ,
   {
     IRQ_EINT15, GPIO_G7, 4
   }
   ,
 };
//按键设备驱动的文件操作结构体如代码清单12.3所示，主要实现了打开、释放和读函数，因为按键只是一个输入设备，所以
//不存在写函数。
//代码清单12.3  按键设备驱动文件操作结构体
static struct file_operations s3c2410_key_fops =
 {
  owner: THIS_MODULE, 
  open: s3c2410_key_open,  //启动设备
   release: s3c2410_key_release,  //关闭设备
  read: s3c2410_key_read,  //读取按键的键值
};
//12.1.3  按键驱动的模块加载和卸载函数
//按键设备作为一种字符设备，在其模块加载和卸载函数中分别包含了设备号申请和释放、cdev的添加和删除行为，在模块加
//载函数中，还需申请中断、初始化定时器和等待队列等，模块卸载函数完成相反的行为，代码清单12.4和12.5分别给出了按
//键设备驱动的模块加载和卸载函数，代码清单12.6和12.7分别给出了模块加载和卸载所调用的申请和释放4个中断的函数。
//代码清单12.4  按键设备驱动的模块加载函数
  static int __init s3c2410_key_init(void)
 {
   ...//申请设备号，添加cdev
  
    request_irqs(); //注册中断函数，不是request_irq函数
   keydev.head = keydev.tail = 0; //初始化结构体
   for (i = 0; i < KEY_NUM; i++)
     keydev.keyStatus[i] = KEYSTATUS_UP;
   init_waitqueue_head(&(keydev.wq)); //等待队列头

 //初始化定时器，实现软件的去抖动
   for (i = 0; i < KEY_NUM; i++)
     setup_timer(&key_timer[i], key_timer_handler, i);
   //把按键的序号作为传入定时器处理函数的参数
 }
//代码清单12.5  按键设备驱动的模块卸载函数
static void __exit s3c2410_key_exit(void)
{ 
 free_irqs(); //注销中断
 ...//释放设备号，删除cdev 
}
//代码清单12.6  按键设备驱动的中断申请函数
/*申请系统中断，中断方式为下降沿触发*/
static int request_irqs(void)
{
  struct key_info *k;
  int i;
  for (i = 0; i < sizeof(key_info_tab) / sizeof(key_info_tab[1]); i++)//安装所有中断函数
  {
    k = key_info_tab + i;
    set_external_irq(k->irq_no, EXT_LOWLEVEL, GPIO_PULLUP_DIS);
                   //设置低电平触发，没有这个函数是由驱动软件工程师写吗？
   if (request_irq(k->irq_no, &buttons_irq, SA_INTERRUPT, DEVICE_NAME, i))  
     {//申请中断，将按键序号作为参数传入中断服务程序
       return  - 1;
     }
   }
   return 0;
 }
//代码清单12.7  按键设备驱动的中断释放函数
/*释放中断*/
static void free_irqs(void)
{
  struct key_info *k;
  int i;
  for (i = 0; i < sizeof(key_info_tab) / sizeof(key_info_tab[1]); i++)
  {
    k = key_info_tab + i;
    free_irq(k->irq_no, buttons_irq); //释放中断
   }
 }
//12.1.4  按键设备驱动中断、定时器处理程序
//在键被按下后，将发生中断，在中断处理程序中，应该关闭中断进入查询模式，延迟20ms以实现去抖动，如代码清单12.8所
//示，这个中断处理过程只包含顶半部，无底半部�
�
//代码清单12.8  按键设备驱动的中断处理程序
 static void s3c2410_eint_key(int irq, void *dev_id, struct pt_regs *reg)
{
 int key = dev_id;
  disable_irq(key_info_tab[key].irq_no); //关中断，转入查询模式

 keydev.keyStatus[key] = KEYSTATUS_DOWNX;//状态为按下
 key_timer[key].expires == jiffies + KEY_TIMER_DELAY1;//延迟
 add_timer(&key_timer[key]); //启动定时器
}
//在定时器处理程序中，查询按键是否仍然被按下，如果是被按下的状态，则将该按键记录入缓冲区。同时启动新的定时器延迟
//，延迟一个相对于去抖更长的时间（如100ms），每次定时器到期后，查询按键是否仍然处于按下状态，如果是，则重新启用
//新的100ms延迟；若查询到已经没有按下，则认定键已抬起，这个时候应该开启对应按键的中断，等待新的按键。每次记录新
//的键值时，应唤醒等待队列。定时器处理流程如图12.3所示，代码清单如12.9所示。

//代码清单12.9  按键设备驱动的定时器处理函数
static void key_timer_handler(unsigned long data)
{
  int key = data;
  if (ISKEY_DOWN(key))
  {
    if (keydev.keyStatus[key] == KEYSTATUS_DOWNX)
    //从中断进入
    {
      keydev.keyStatus[key] = KEYSTATUS_DOWN;
       key_timer[key].expires == jiffies + KEY_TIMER_DELAY; //延迟
     keyEvent();   //记录键值，唤醒等待队列
       add_timer(&key_timer[key]);
     }
     else
     {
       key_timer[key].expires == jiffies + KEY_TIMER_DELAY; //延迟
       add_timer(&key_timer[key]);
     }
   }
   else       //键已抬起
{
     keydev.keyStatus[key] = KEYSTATUS_UP;
     enable_irq(key_info_tab[key].irq_no);
  }
}

//图12.3  定时器处理函数流程
//12.1.5  按键设备驱动的打开、释放函数
//按键设备驱动的打开和释放函数比较简单，主要是设置keydev.head、keydev.tail和按键事件函数指针keyEvent的值，如代码清单12.10所示。

///代码清单12.10  按键设备驱动的打开、释放函数
static int s3c2410_key_open(struct inode *inode, struct file *filp)
{
  keydev.head = keydev.tail = 0; //清空按键动作缓冲区
  keyEvent = keyEvent_raw; //函数指针指向按键处理函数keyEvent_raw
  return 0;
}

static int s3c2410_key_release(struct inode *inode, struct file *filp)
{
   keyEvent = keyEvent_dummy; //函数指针指向空函数
 return 0;
 }
//12.1.6  按键设备驱动读函数
//代码清单12.11给出了按键设备驱动的读函数，按键设备驱动的读函数主要提供对按键设备结构体中缓冲区的读并复制到用户
//空间。当keydev.head ! = keydev.tail时，意味着缓冲区有数据，使用copy_to_user()拷贝到用户空间，否则，根据用户空间
//是阻塞读还是非阻塞读，分为如下两种情况。
//l      若采用非阻塞读，则因为没有按键缓存，直接返回- EAGAIN；
//l      若采用阻塞读，则在keydev.wq等待队列上睡眠，直到有按键被记录入缓冲区后被唤醒。

//代码清单12.按键设备驱动的读函数
static ssize_t s3c2410_key_read(struct file *filp, char *buf, ssize_t count,
  loff_t*ppos)
{
  retry: if (keydev.head != keydev.tail)  //当前循环队列中有数据
  		{
   			 key_ret = keyRead(); //读取按键
    			copy_to_user(..); //把数据从内核空间传送到用户空间
 		 }
 	   else
 		{
 			if (filp->f_flags &O_NONBLOCK) //若用户采用非阻塞方式读取
    			 {
       			return  - EAGAIN;
     			}
    			 interruptible_sleep_on(&(keydev.wq));
     			  //用户采用阻塞方式读取，调用该函数使进程睡眠，在许多驱动程序中，并没有使用此函数，而是直接手工进程状态切换见P178
    			 goto	retry;
  		 }
	return 0;
 }
//MODULE_AUTHOR("Song Baohua");
//MODULE_LICENSE("Dual BSD/GPL");
module_param(globalfifo_major, int, S_IRUGO);
//module_init(globalfifo_init);
//module_exit(globalfifo_exit);

//最后，解释一下代码清单12.9第11行的keyEvent()函数和代码清单12.11的keyRead()函数。在设备驱动的打开函数中，
//keyEvent被赋值为keyEvent_raw，这个函数完成记录键值，并使用wait_up_interrupt(&(keydev.wq))语句唤醒
//s3c2410_key_read()第17行所期待的等待队列。而keyRead()函数则直接从按键缓冲区中读取键值。
