/*======================================================================
    A simple kernel module: "hello world"
         
    The initial developer of the original code is Baohua Song
    <author@linuxdriver.cn>. All Rights Reserved.
======================================================================*/
//#include <linux/init.h>
//#include <linux/module.h>
//(MODULE_LICENSE) 是用来告知内核, 该模块带有一个自由的许可证; 没有这样的说明, 在模块加载时内核会抱怨.  
//MODULE_LICENSE("Dual BSD/GPL");
static int hello_init(void)
{
  printk(KERN_INFO " Hello World enter\n");
  return 0;
}

static void hello_exit(void)
{
  printk(KERN_INFO " Hello World exit\n ");
}

//module_init(hello_init);
//module_exit(hello_exit);

//MODULE_AUTHOR("Song Baohua");
//MODULE_DESCRIPTION("A simple Hello World Module");
//MODULE_ALIAS("a simplest module");
