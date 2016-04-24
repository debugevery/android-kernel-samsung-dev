//EXPORT_SYMBOL and //EXPORT_SYMBOL_GPL 
 
 
1.//EXPORT_SYMBOL
//EXPORT_SYMBOL( my_pub_func);
在预编译阶段会解析为:
extern void *__crc_my_pub_func __attribute__((weak)); 
static const unsigned long __kcrctab_my_pub_func __attribute__((__used__)) __attribute__((section("__kcrctab" ""), unused)) = (unsigned long) &__crc_my_pub_func; 
static const char __kstrtab_my_pub_func[] __attribute__((section("__ksymtab_strings"))) = "" "my_pub_func"; 
static const struct kernel_symbol __ksymtab_my_pub_func __attribute__((__used__)) __attribute__((section("__ksymtab" ""), unused)) = { (unsigned long)&my_pub_func, __kstrtab_my_pub_func };
很显然__ksymtab_my_pub_func存储了my_pub_func的地址和符号信息,该符号对应的地址
只有insmod后才会确定;
__ksymtab_my_pub_func会链接到__ksymtab section,__ksymtab section中的所有内容就构成了
内核"导出"的符号表,这个表在insmod 时候会用到.2./proc/kallsyms
cat /proc/kallsyms会打印出内核当前的符号表,例如:
...
d8834a24 t snd_free_sgbuf_pages [snd_page_alloc]
c0180d7a U create_proc_entry [snd_page_alloc]
d88341d8 T snd_dma_free_pages [snd_page_alloc]
c013d858 U __get_free_pages [snd_page_alloc]
d8834ab5 t snd_malloc_sgbuf_pages [snd_page_alloc]
c014f906 U kmem_cache_alloc [snd_page_alloc]
c0106dcd U dma_alloc_coherent [snd_page_alloc]
...
其中第一列是该符号在内核地址空间中的地址;第二列是符号属性,小写表示
局部符号,大写表示全局符号,具体含义参考man nm; 第三列表示符号字符串. 
这里只显示//EXPORT_SYMBOL,EXPROT_SYMBOL_GPL处理过的符号。3.System.map内核符号文件
通过more /boot/System.map 可以查看内核符号列表。
可以显示编译好内核后所有在内核中的符号，模块中的要另行查看。4.通过nm vmlinux也可以查看内核符号列表
可以显示编译好内核后所有在内核中的符号，模块中的要另行查看。5.通过nm module_name可以查看模块的符号列表
但是得到是相对地址，只有加载后才会分配绝对地址。比如：e1000模块，如果e1000中的符号经过//EXPORT_SYMBOL处理，等加载后，我们可以通过more /boot/System.map和nm vmlinux命令查看到，但是没有EXPORT_SYMBOL的，我目前不知道怎么查看。另个试验：
1.验证//EXPORT_SYMBOL
模块hello.c代码如下：
      1 //#include <linux/module.h>
      2 //#include <linux/kernel.h>
      3
      4 static int __init a_init_module(void)
      5 {
      6     unsigned long *__kcrctab_per_cpu__hrtimer_bases = 0xc02678b4;
      7     unsigned char *__kstrtab_per_cpu__hrtimer_bases = 0xc026926b;
      8     struct kernel_symbol *__ksymtab_per_cpu__hrtimer_bases = 0xc0265018;
      9
     10     printk("__kcrctab_per_cpu__hrtimer_bases = %08x\n", *__kcrctab_per_cpu__hrtimer_bases);
     11     printk("__kstrtab_per_cpu__hrtimer_bases = %s\n", __kstrtab_per_cpu__hrtimer_bases);
     12     printk("__ksymtab_per_cpu__hrtimer_bases value = %08x, name = %s\n", __ksymtab_per_cpu__hrtimer_bases->value,\
     13     __ksymtab_per_cpu__hrtimer_bases->name);
     14
     15     return 0;
     16 }
     17
     18 static void __exit a_cleanup_module(void)
     19 {
     20     printk("Bye, Bye\n");
     21 }
      22 //module_init(a_init_module);
     23 //module_exit(a_cleanup_module);     
     Makefile配置文件如下：
      1 #
      2 # Makefile for hello.c file
      3 #
      4 KDIR:=/lib/modules/$(shell uname -r)/build
      5
      6 obj-m:=hello.o
      7
      8 default:
      9     $(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
     10 clean:
     11     $(RM) .*.cmd *.mod.c *.o *.ko -r .tmp*make; insmod hello.ko之后通过dmesg的运行结果：
__kcrctab_per_cpu__hrtimer_bases = 1ac19564
__kstrtab_per_cpu__hrtimer_bases = per_cpu__hrtimer_bases
__ksymtab_per_cpu__hrtimer_bases value = c0279ea0, name = per_cpu__hrtimer_bases通过nm vmlinux | grep per_cpu__hrtimer_bases我们可以看到如下的对应关系：
1ac19564 A __crc_per_cpu__hrtimer_bases
c02678b4 r __kcrctab_per_cpu__hrtimer_bases
c026926b r __kstrtab_per_cpu__hrtimer_bases
c0265018 r __ksymtab_per_cpu__hrtimer_bases
c0279ea0 d per_cpu__hrtimer_bases对比如上两列数据。
本实验只是为了验证一下EXPROT_SYMBOL.
2.1.//EXPORT_SYMBOL和//EXPORT_SYMBOL_GPL的区别
模块1：hello.c
      1 //#include <linux/module.h>
      2 //#include <linux/kernel.h>
      3
      4 void function1(void)
      5 {
      6     printk("hello wold\n");
      7 }
      8 //EXPORT_SYMBOL(function1);
      9
     10 void function2(void)
     11 {
     12     printk("hello wold again\n");
     13 }
     14 //EXPORT_SYMBOL_GPL(function2);
     15
     16
     17 static int __init a_init_module(void)
     18 {
     19     return 0;
     20 }
     21
     22 static void __exit a_cleanup_module(void)
     23 {
     24     printk("<1>Bye, Bye\n");
     25
     26 }
     27
     28 //module_init(a_init_module);
     29 //module_exit(a_cleanup_module);
模块2：hello2.c
    1 //#include <linux/module.h>
      2 //#include <linux/kernel.h>
      3
      4 //MODULE_LICENSE("GPL");
      5
      6 static int __init a_init_module(void)
      7 {
      8     function1();
      9 //    function2();
     10     return 0;
     11 }
     12
     13 static void __exit a_cleanup_module(void)
     14 {
     15     printk("<1>Bye, Bye\n");
     16
     17 }
     18
     19 //module_init(a_init_module);
     20 //module_exit(a_cleanup_module);    
    首先编译后两个模块：hello.ko, hello2.ko
    A.在hello2.c中注释掉//MODULE_LICENSE("GPL")和function2()两行，先insmod hello.ko然后insmod hello2.ko，一切正常。
    B.先insmod hello2.ko然后insmod hello.ko，会有出错信息，通过dmesg查看显示如下：hello2: Unknown symbol function1
    C.在hello2.c中打开function2()，先insmod hello.ko然后insmod hello2.ko，模块hello2.ko无法加载，显示如下信息：insmod: error inserting 'hello2.ko': -1 File exists，通过dmesg查看显示如下：hello2: Unknown symbol function2。在hello2.c中打开//MODULE_LICENSE("GPL")或者用MODULE_LICENSE("Dual BSD/GPL")，先insmod hello.ko然后insmod hello2.ko，一切正常。

所以说//EXPORT_SYMBOL_GPL的符号必须要用MODULE_LICENSE("GPL")或者用MODULE_LICENSE("Dual BSD/GPL")之后才能在模块中引用。而且MODULE_LICENSE("char")中的char不可以是任意字符，否则错误和没有MODULE_LICENSE效果一样。
    D.没有看//MODULE_LICENSE内核代码，下一步去研读代码。
 
 
