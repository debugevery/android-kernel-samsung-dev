//Linux混杂设备驱动  
//WatchDog Timer驱动

//Introduction:
// 
//一个Watchdog Timer（WDT）是一个在软件出错的时候可以复位计算机系统的硬件电路。
//通常一个用户空间守护进程会在正常的时间间隔内通过/dev/watchdog特殊设备文件来通知内核的watchdog驱动，用户空间仍然正常。当这样的一个通知发生时，驱动通常会告诉硬件watchdog一切正常，然后watchdog应该再等待一段时间来复位系统。如果用户空间出问题（RAM错误，内核bug等），则通知将会停止，然后硬件watchdog将在超时后复位系统。
//Linux的watchdog API是一个相当特别的东西，不同的驱动实现是不同的，而且有时部分是不兼容的。这个文档正是要尝试着去说明已经出现的用法，并且使以后的驱动作者把它作为一份参考。
// 
//最简单的 API:
// 
//所有的设备驱动都支持的基本的操作模式，一旦/dev/watchdog被打开，则watchdog激活，并且除非喂狗，否则将在一段时间之后重启，这个时间被称为timeout或margin。最简单的喂狗方法就是写一些数据到设备。一个非常简单的watchdog守护进程看起来就像这个文件这样：
//Documentation/watchdog/src/watchdog-simple.c
// 
//一个高级一些的驱动在喂狗之前，可能还会做一些其他的事情，比如说检查HTTP服务器是否依然可以相应。
// 
//当设备关闭的时候，除非支持"Magic Close"特性。否则watchdog被关闭。这并不总是一个好主意，比如watchdog守护进程出现了bug并且崩溃了，则系统将不会重启。因此，某些驱动支持"Disable watchdog shutdown on close", CONFIG_WATCHDOG_NOWAYOUT配置选项。当编译内核的时候这个选项被设置为Y，则一旦watchdog被启动，则将没有办法能够停止。这样，则当watchdog守护进程崩溃的时候，系统仍将在超时后重启。Watchdog设备常常也支持nowayout模块参数，这样这个选项就可以在运行时进行控制。
// 
//Magic Close 特性:
// 
//如果一个驱动支持"Magic Close"，则除非在关闭文件前，魔幻字符'V'被发送到/dev/watchdog，驱动将不停止watchdog。如果用户空间守护进程在关闭文件前没有发送这个字符，则驱动认为用户空间崩溃，并在关闭watchdog前停止喂狗。
//这样的话，如果没有在一定的时间内重新打开watchdog，则将导致一个重启。
// 
//ioctl API:
// 
//所有标准的驱动也应该支持一个ioctl API。
// 
//喂狗使用一个ioctl：
//所有的驱动都有一个ioctl接口支持至少一个ioctl命令，KEEPALIVE。这个 ioctl 做的事和一个写watchdog设备完全一样，所以，上面程序的主循环可以替换为：
     while (1) {
        ioctl(fd, WDIOC_KEEPALIVE, 0);
        sleep(10);
     }
//ioctl的参数被忽略。
// 
//设置和获得超时值：
//对于某些驱动来说，在上层使用SETTIMEOUT ioctl命令改变watchdog的超时值是可能的，那些驱动在他们的选项与中有WDIOF_SETTIMEOUT标志。参数是一个代表以秒为单位的超时值，驱动将在同一个变量中返回实际使用的超时值，这个超时值可能由于硬件的限制，而不同于所请求的超时值
     int timeout = 45;
     ioctl(fd, WDIOC_SETTIMEOUT, &timeout);
     printf("The timeout was set to %d seconds\n", timeout);
//如果设备的超时值的粒度只能到分钟，则这个例子可能实际打印"The timeout was set to 60 seconds"。
//自从Linux 2.4.18内核，通过GETTIMEOUT ioctl命令查询当前超时值也是可能的：
     ioctl(fd, WDIOC_GETTIMEOUT, &timeout);
     printf("The timeout was is %d seconds\n", timeout);
// 
//预处理：
//Pretimeouts:
//一些watchdog定时器，可以被设置为，在他们实际复位系统前，有一个触发。这可能通过一个NMI，中断，或其他机制。这将允许在它复位系统前Linux去记录一些有用的信息（比如panic信息和内核转储）。
     pretimeout = 10;
     ioctl(fd, WDIOC_SETPRETIMEOUT, &pretimeout);
//注意，预超时值应该是一个相对于超时值提前的秒数。而不是直到预超时的秒数。
//比如，如果你设置超时值为60秒，预超时值为10秒，那么预超时将在50秒后到达。设置为0则是禁用它。预超时还有一个get功能：
     ioctl(fd, WDIOC_GETPRETIMEOUT, &timeout);
     printf("The pretimeout was is %d seconds\n", timeout);
//不是所有的watchdog驱动都支持一个预超时的。
// 
//获得重启前的秒数
//一些watchdog驱动有一个报告在重启前的剩余时间的功能。WDIOC_GETTIMELEFT就是返回重启前的秒数的ioctl命令。
     ioctl(fd, WDIOC_GETTIMELEFT, &timeleft);
     printf("The timeout was is %d seconds\n", timeleft);
// 
//环境监视：
//Environmental monitoring:
// 
//所有的watchdog驱动都被要求返回更多关于系统的信息，有些返回温度，风扇和功率水平监测，依稀可以告诉你上一次重启系统的原因。GETSUPPORT ioctl可以用来查询设备可以做什么：
     struct watchdog_info ident;
     ioctl(fd, WDIOC_GETSUPPORT, &ident);
// 
//ident结构中返回的字段是：
         identity     一个标识watchdog驱动的字符串
     firmware_version  如果可用的话，就是卡的固件版本
     options           一个描述设备支持什么的标志
//options字段可以有下面的位集，和描述GET_STATUS 和 GET_BOOT_STATUS ioctls可以返回什么种类的信息。
// [FIXME -- Is this correct?]
// 
//WDIOF_OVERHEAT       由于CPU过热而复位
//机器上一次被watchdog复位是由于温度过高。
// 
//WDIOF_FANFAULT       风扇失灵
//watchdog监测到一个系统风扇失灵
// 
//WDIOF_EXTERN1     External relay 1
// 
//External monitoring relay/source 1 was triggered. Controllers intended for real world applications include external monitoring pins that will trigger a reset.
// 
     WDIOF_EXTERN2     External relay 2
// 
//External monitoring relay/source 2 was triggered
// 
     WDIOF_POWERUNDER  Power bad/power fault
// 
//The machine is showing an undervoltage status
// 
     WDIOF_CARDRESET      Card previously reset the CPU
// 
//The last reboot was caused by the watchdog card
// 
     WDIOF_POWEROVER      Power over voltage
// 
//The machine is showing an overvoltage status. Note that if one level is
//under and one over both bits will be set - this may seem odd but makes
//sense.
// 
     WDIOF_KEEPALIVEPING  Keep alive ping reply
// 
//The watchdog saw a keepalive ping since it was last queried.
// 
     WDIOF_SETTIMEOUT  Can set/get the timeout
// 
//The watchdog can do pretimeouts.
// 
     WDIOF_PRETIMEOUT  Pretimeout (in seconds), get/set
// 
// 
//For those drivers that return any bits set in the option field, the
//GETSTATUS and GETBOOTSTATUS ioctls can be used to ask for the current
//status, and the status at the last reboot, respectively.  
// 
     int flags;
     ioctl(fd, WDIOC_GETSTATUS, &flags);
// 
     or
// 
     ioctl(fd, WDIOC_GETBOOTSTATUS, &flags);
// 
//Note that not all devices support these two calls, and some only
//support the GETBOOTSTATUS call.
// 
//Some drivers can measure the temperature using the GETTEMP ioctl.  The
//returned value is the temperature in degrees fahrenheit.
// 
     int temperature;
     ioctl(fd, WDIOC_GETTEMP, &temperature);
// 
//Finally the SETOPTIONS ioctl can be used to control some aspects of
//the cards operation; right now the pcwd driver is the only one
//supporting this ioctl.
// 
     int options = 0;
     ioctl(fd, WDIOC_SETOPTIONS, options);
// 
//The following options are available:
// 
     WDIOS_DISABLECARD Turn off the watchdog timer
     WDIOS_ENABLECARD  Turn on the watchdog timer
     WDIOS_TEMPPANIC      Kernel panic on temperature trip
// 
//[FIXME -- better explanations]
// 
// 
//S3C2440A SoC与看门狗有关的寄存器只有三个：看门狗控制寄存器WDTCON，看门狗数据寄存器WDTDAT和看门狗计数寄存器WDTCNT。驱动在同一时间只允许一个进程打开，所以在open（）方法中锁定，也就是获得一个信号量，在release（）方法中解除锁定。然后就是根据内核文档中的WDT API的语义进行尽可能丰富的实现。
//#include <linux/init.h>
//#include <linux/module.h>
//#include <linux/miscdevice.h>
//#include <linux/watchdog.h>
//#include <linux/fs.h>
//#include <linux/ioport.h>
//#include <asm/io.h>
//#include <linux/moduleparam.h>
//#include <linux/semaphore.h>
//#include <asm/uaccess.h>
//#include "s3c2440wdt.h"
void *wdtmem = NULL;
int nowayout = NOWAYOUT;
int closetag = 0;
module_param(nowayout, int, S_IRUGO);
unsigned int wdt_timeout = DEFAULT_WATCHDOG_TIMEOUT;
struct semaphore sem;
static int s3c2440wdt_open(struct inode *inode, struct file *filp)
{
   down_interruptible(&sem);
   iowrite32(wdt_timeout, wdtmem + WDTDAT);
   iowrite32(wdt_timeout, wdtmem + WDTCNT);
   iowrite32(DEFAULT_WDTCON, wdtmem + WDTCON);
   return 0;
}
//static int s3c2440wdt_close(struct inode *inode, struct file *filp)
{
   unsigned int wdtdat = 0;
   /* If CONFIG_WATCHDOG_NOWAYOUT is chosen during kernel
      configuration, do not disable the watchdog even if the 
      application desires to close it.
   */
   if(nowayout)
     return 0;
   if(closetag == 0)
     return 0;
#ifndef CONFIG_WATCHDOG_NOWAYOUT
   /*Disable watchdog */
   wdtdat = ioread32(wdtmem + WDTCON);
   wdtdat &= ~(1 << WENABLE_SHIFT);
   iowrite32(wdtdat, wdtmem + WDTCON);
#endif
   up(&sem);
   return 0;
}
//static ssize_t s3c2440wdt_write(struct file *filp, const char __user *buf, size_t count, loff_t *pos)
{
   char usrdata = 0;
   copy_from_user(&usrdata, buf, sizeof(usrdata));
   if(usrdata == MAGIC_CHAR){
     closetag = 1;
   }else {
     closetag = 0;
   }
   iowrite32(wdt_timeout, wdtmem + WDTCNT);
   return 0;
}
//static int s3c2440wdt_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
   unsigned int realtimeout = 0;
   int timeout;
   struct watchdog_info *ident;
   switch(cmd){
   case WDIOC_KEEPALIVE:
     /* Write to the watchdog.Application can invoke
        this ioctl instead of writing to the device */
     iowrite32(wdt_timeout, wdtmem + WDTCNT);
     break;
   case WDIOC_SETTIMEOUT:
     copy_from_user(&timeout, (int *)arg, sizeof(int));
     if(timeout > 40)
       timeout = 40;
     copy_to_user((int *)arg, &timeout, sizeof(int));
     wdt_timeout = ((unsigned int)timeout) * PER_SECOND;
     break;
   case WDIOC_GETTIMEOUT:
     timeout = (int)(wdt_timeout / PER_SECOND);
     copy_to_user((int *)arg, &timeout, sizeof(int));
     break;
   case WDIOC_GETTIMELEFT:
     realtimeout = ioread32(wdtmem + WDTCNT);
     realtimeout /= PER_SECOND;
     timeout = (int)realtimeout;
     copy_to_user((int *)arg, &timeout, sizeof(int));
     break;
   case WDIOC_GETSUPPORT:
     ident = kmalloc(sizeof(*ident), GFP_KERNEL);
     if(ident == NULL){
       printk(KERN_NOTICE "s3c2440wdt get memory failure.\n");
       return -EINVAL;
     }
     memset(ident, 0, sizeof(*ident));
     sprintf(ident->identity, "%s", "s3c2440wdt");
     ident->options = WDIOF_SETTIMEOUT | WDIOF_MAGICCLOSE | WDIOF_KEEPALIVEPING;
     copy_to_user((char *)arg, ident, sizeof(*ident));
     break;
   default:
     return -ENOTTY;
   }
   return 0;
}
// 
//struct file_operations s3c2440wdt_fops = {
   .owner = THIS_MODULE,
   .open = s3c2440wdt_open,
   .release = s3c2440wdt_close,
   .write = s3c2440wdt_write,
   .ioctl = s3c2440wdt_ioctl,
};
//static struct miscdevice s3c2440_wdt_dev = {
   .minor = WATCHDOG_MINOR,
   .name = "s3c2440wdt",
   .fops = &s3c2440wdt_fops,
   .nodename = "watchdog",
};
// 
//static int s3c2440wdt_init(void)
{
   if(request_mem_region(WDTMEMBASE, WDTMEMLEN, "s3c2440wdt") == NULL){
     printk(KERN_ALERT "Get wdt register memory failure.\n");
     return -EBUSY;
   }
   wdtmem = ioremap(WDTMEMBASE, WDTMEMLEN);
   init_MUTEX(&sem);
   misc_register(&s3c2440_wdt_dev);
   printk(KERN_ALERT "The initialization has been completed successfully!\n");
   return 0;
}
// 
static void s3c2440wdt_exit(void)
{
   misc_deregister(&s3c2440_wdt_dev);
   iounmap(wdtmem);
   release_mem_region(WDTMEMBASE, WDTMEMLEN);
   printk(KERN_ALERT "modoule s3c2440wdt eixt.\n");
}
// 
//module_init(s3c2440wdt_init);
//module_exit(s3c2440wdt_exit);
// 
//MODULE_LICENSE("Dual BSD/GPL");
//MODULE_AUTHOR("Hanpfei, hanpfei@gmail.com");
//MODULE_DESCRIPTION("The drivers for mini2440's watch dog timer.");
module_VERSION("v1.0");
module_ALIAS("mini2440-wdt");
// 
// 

