/*======================================================================
    A kernel module: book
    This example is to introduce module params
         
    The initial developer of the original code is Baohua Song
    <author@linuxdriver.cn>. All Rights Reserved.
======================================================================*/
//#include <linux/init.h>                                
//#include <linux/module.h>                                
//MODULE_LICENSE("Dual BSD/GPL");                                
 //moudle_param 宏定义来声明, 它定义在 moduleparam.h. module_param 使用
//了 3 个参数: 变量名, 它的类型, 以及一个权限掩码用来做一个辅助的 sysfs 
//入口. 这个宏定义应当放在任何函数之外, 典型地是出现在源文件的前面                               
static char *book_name = "dissecting Linux Device Driver";              
static int num = 4000;                                
                                
static int book_init(void)                                
{                                
	printk(KERN_INFO " book name:%s\n",book_name);                        
	printk(KERN_INFO " book num:%d\n",num);                               
	return 0;                                
}                                
static void book_exit(void)                                
{                                
	printk(KERN_INFO " Book module exit\n ");                            
}                                
//module_init(book_init);                                
//module_exit(book_exit);                                
module_param(num, int, S_IRUGO);     //moudle_param 宏定义来声明 static int num = 4000;                              
module_param(book_name, charp, S_IRUGO);
                                
//MODULE_AUTHOR("Song Baohua, author@linuxdriver.cn");
//MODULE_DESCRIPTION("A simple Module for testing module params");
MODULE_VERSION("V1.0");
