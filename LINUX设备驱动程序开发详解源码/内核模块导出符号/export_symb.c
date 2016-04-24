/*======================================================================
    A simple kernel module to introduce export symbol
         
    The initial developer of the original code is Baohua Song
    <author@linuxdriver.cn>. All Rights Reserved.
======================================================================*/
//#include <linux/init.h>                                
//#include <linux/module.h>                                
//MODULE_LICENSE("Dual BSD/GPL");                                
                                
int add_integar(int a,int b)                                
{                                
	return a+b;                             
} 
                               
int sub_integar(int a,int b)                                
{                                
	return a-b;                             
}                            
//宏定义的任一个使得给定的符号在模块外可用. _GPL 版本的宏定义只能使
//符号对 GPL 许可的模块可用. 符号必须在模块文件的全局部分输出, 在任何函
//数之外, 因为宏定义扩展成一个特殊用途的并被期望是全局存取的变量的声明.
//EXPORT_SYMBOL(add_integar);
//EXPORT_SYMBOL(sub_integar);