//Linux�����豸����  
//WatchDog Timer����

//Introduction:
// 
//һ��Watchdog Timer��WDT����һ������������ʱ����Ը�λ�����ϵͳ��Ӳ����·��
//ͨ��һ���û��ռ��ػ����̻���������ʱ������ͨ��/dev/watchdog�����豸�ļ���֪ͨ�ں˵�watchdog�������û��ռ���Ȼ��������������һ��֪ͨ����ʱ������ͨ�������Ӳ��watchdogһ��������Ȼ��watchdogӦ���ٵȴ�һ��ʱ������λϵͳ������û��ռ�����⣨RAM�����ں�bug�ȣ�����֪ͨ����ֹͣ��Ȼ��Ӳ��watchdog���ڳ�ʱ��λϵͳ��
//Linux��watchdog API��һ���൱�ر�Ķ�������ͬ������ʵ���ǲ�ͬ�ģ�������ʱ�����ǲ����ݵġ�����ĵ�����Ҫ������ȥ˵���Ѿ����ֵ��÷�������ʹ�Ժ���������߰�����Ϊһ�ݲο���
// 
//��򵥵� API:
// 
//���е��豸������֧�ֵĻ����Ĳ���ģʽ��һ��/dev/watchdog���򿪣���watchdog������ҳ���ι����������һ��ʱ��֮�����������ʱ�䱻��Ϊtimeout��margin����򵥵�ι����������дһЩ���ݵ��豸��һ���ǳ��򵥵�watchdog�ػ����̿�������������ļ�������
//Documentation/watchdog/src/watchdog-simple.c
// 
//һ���߼�һЩ��������ι��֮ǰ�����ܻ�����һЩ���������飬����˵���HTTP�������Ƿ���Ȼ������Ӧ��
// 
//���豸�رյ�ʱ�򣬳���֧��"Magic Close"���ԡ�����watchdog���رա��Ⲣ������һ�������⣬����watchdog�ػ����̳�����bug���ұ����ˣ���ϵͳ��������������ˣ�ĳЩ����֧��"Disable watchdog shutdown on close", CONFIG_WATCHDOG_NOWAYOUT����ѡ��������ں˵�ʱ�����ѡ�����ΪY����һ��watchdog����������û�а취�ܹ�ֹͣ����������watchdog�ػ����̱�����ʱ��ϵͳ�Խ��ڳ�ʱ��������Watchdog�豸����Ҳ֧��nowayoutģ��������������ѡ��Ϳ���������ʱ���п��ơ�
// 
//Magic Close ����:
// 
//���һ������֧��"Magic Close"��������ڹر��ļ�ǰ��ħ���ַ�'V'�����͵�/dev/watchdog����������ֹͣwatchdog������û��ռ��ػ������ڹر��ļ�ǰû�з�������ַ�����������Ϊ�û��ռ���������ڹر�watchdogǰֹͣι����
//�����Ļ������û����һ����ʱ�������´�watchdog���򽫵���һ��������
// 
//ioctl API:
// 
//���б�׼������ҲӦ��֧��һ��ioctl API��
// 
//ι��ʹ��һ��ioctl��
//���е���������һ��ioctl�ӿ�֧������һ��ioctl���KEEPALIVE����� ioctl �����º�һ��дwatchdog�豸��ȫһ�������ԣ�����������ѭ�������滻Ϊ��
     while (1) {
        ioctl(fd, WDIOC_KEEPALIVE, 0);
        sleep(10);
     }
//ioctl�Ĳ��������ԡ�
// 
//���úͻ�ó�ʱֵ��
//����ĳЩ������˵�����ϲ�ʹ��SETTIMEOUT ioctl����ı�watchdog�ĳ�ʱֵ�ǿ��ܵģ���Щ���������ǵ�ѡ��������WDIOF_SETTIMEOUT��־��������һ����������Ϊ��λ�ĳ�ʱֵ����������ͬһ�������з���ʵ��ʹ�õĳ�ʱֵ�������ʱֵ��������Ӳ�������ƣ�����ͬ��������ĳ�ʱֵ
     int timeout = 45;
     ioctl(fd, WDIOC_SETTIMEOUT, &timeout);
     printf("The timeout was set to %d seconds\n", timeout);
//����豸�ĳ�ʱֵ������ֻ�ܵ����ӣ���������ӿ���ʵ�ʴ�ӡ"The timeout was set to 60 seconds"��
//�Դ�Linux 2.4.18�ںˣ�ͨ��GETTIMEOUT ioctl�����ѯ��ǰ��ʱֵҲ�ǿ��ܵģ�
     ioctl(fd, WDIOC_GETTIMEOUT, &timeout);
     printf("The timeout was is %d seconds\n", timeout);
// 
//Ԥ����
//Pretimeouts:
//һЩwatchdog��ʱ�������Ա�����Ϊ��������ʵ�ʸ�λϵͳǰ����һ�������������ͨ��һ��NMI���жϣ����������ơ��⽫����������λϵͳǰLinuxȥ��¼һЩ���õ���Ϣ������panic��Ϣ���ں�ת������
     pretimeout = 10;
     ioctl(fd, WDIOC_SETPRETIMEOUT, &pretimeout);
//ע�⣬Ԥ��ʱֵӦ����һ������ڳ�ʱֵ��ǰ��������������ֱ��Ԥ��ʱ��������
//���磬��������ó�ʱֵΪ60�룬Ԥ��ʱֵΪ10�룬��ôԤ��ʱ����50��󵽴����Ϊ0���ǽ�������Ԥ��ʱ����һ��get���ܣ�
     ioctl(fd, WDIOC_GETPRETIMEOUT, &timeout);
     printf("The pretimeout was is %d seconds\n", timeout);
//�������е�watchdog������֧��һ��Ԥ��ʱ�ġ�
// 
//�������ǰ������
//һЩwatchdog������һ������������ǰ��ʣ��ʱ��Ĺ��ܡ�WDIOC_GETTIMELEFT���Ƿ�������ǰ��������ioctl���
     ioctl(fd, WDIOC_GETTIMELEFT, &timeleft);
     printf("The timeout was is %d seconds\n", timeleft);
// 
//�������ӣ�
//Environmental monitoring:
// 
//���е�watchdog��������Ҫ�󷵻ظ������ϵͳ����Ϣ����Щ�����¶ȣ����Ⱥ͹���ˮƽ��⣬��ϡ���Ը�������һ������ϵͳ��ԭ��GETSUPPORT ioctl����������ѯ�豸������ʲô��
     struct watchdog_info ident;
     ioctl(fd, WDIOC_GETSUPPORT, &ident);
// 
//ident�ṹ�з��ص��ֶ��ǣ�
         identity     һ����ʶwatchdog�������ַ���
     firmware_version  ������õĻ������ǿ��Ĺ̼��汾
     options           һ�������豸֧��ʲô�ı�־
//options�ֶο����������λ����������GET_STATUS �� GET_BOOT_STATUS ioctls���Է���ʲô�������Ϣ��
// [FIXME -- Is this correct?]
// 
//WDIOF_OVERHEAT       ����CPU���ȶ���λ
//������һ�α�watchdog��λ�������¶ȹ��ߡ�
// 
//WDIOF_FANFAULT       ����ʧ��
//watchdog��⵽һ��ϵͳ����ʧ��
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
//S3C2440A SoC�뿴�Ź��йصļĴ���ֻ�����������Ź����ƼĴ���WDTCON�����Ź����ݼĴ���WDTDAT�Ϳ��Ź������Ĵ���WDTCNT��������ͬһʱ��ֻ����һ�����̴򿪣�������open����������������Ҳ���ǻ��һ���ź�������release���������н��������Ȼ����Ǹ����ں��ĵ��е�WDT API��������о����ܷḻ��ʵ�֡�
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

