//EXPORT_SYMBOL and //EXPORT_SYMBOL_GPL 
 
 
1.//EXPORT_SYMBOL
//EXPORT_SYMBOL( my_pub_func);
��Ԥ����׶λ����Ϊ:
extern void *__crc_my_pub_func __attribute__((weak)); 
static const unsigned long __kcrctab_my_pub_func __attribute__((__used__)) __attribute__((section("__kcrctab" ""), unused)) = (unsigned long) &__crc_my_pub_func; 
static const char __kstrtab_my_pub_func[] __attribute__((section("__ksymtab_strings"))) = "" "my_pub_func"; 
static const struct kernel_symbol __ksymtab_my_pub_func __attribute__((__used__)) __attribute__((section("__ksymtab" ""), unused)) = { (unsigned long)&my_pub_func, __kstrtab_my_pub_func };
����Ȼ__ksymtab_my_pub_func�洢��my_pub_func�ĵ�ַ�ͷ�����Ϣ,�÷��Ŷ�Ӧ�ĵ�ַ
ֻ��insmod��Ż�ȷ��;
__ksymtab_my_pub_func�����ӵ�__ksymtab section,__ksymtab section�е��������ݾ͹�����
�ں�"����"�ķ��ű�,�������insmod ʱ����õ�.2./proc/kallsyms
cat /proc/kallsyms���ӡ���ں˵�ǰ�ķ��ű�,����:
...
d8834a24 t snd_free_sgbuf_pages [snd_page_alloc]
c0180d7a U create_proc_entry [snd_page_alloc]
d88341d8 T snd_dma_free_pages [snd_page_alloc]
c013d858 U __get_free_pages [snd_page_alloc]
d8834ab5 t snd_malloc_sgbuf_pages [snd_page_alloc]
c014f906 U kmem_cache_alloc [snd_page_alloc]
c0106dcd U dma_alloc_coherent [snd_page_alloc]
...
���е�һ���Ǹ÷������ں˵�ַ�ռ��еĵ�ַ;�ڶ����Ƿ�������,Сд��ʾ
�ֲ�����,��д��ʾȫ�ַ���,���庬��ο�man nm; �����б�ʾ�����ַ���. 
����ֻ��ʾ//EXPORT_SYMBOL,EXPROT_SYMBOL_GPL������ķ��š�3.System.map�ں˷����ļ�
ͨ��more /boot/System.map ���Բ鿴�ں˷����б�
������ʾ������ں˺��������ں��еķ��ţ�ģ���е�Ҫ���в鿴��4.ͨ��nm vmlinuxҲ���Բ鿴�ں˷����б�
������ʾ������ں˺��������ں��еķ��ţ�ģ���е�Ҫ���в鿴��5.ͨ��nm module_name���Բ鿴ģ��ķ����б�
���ǵõ�����Ե�ַ��ֻ�м��غ�Ż������Ե�ַ�����磺e1000ģ�飬���e1000�еķ��ž���//EXPORT_SYMBOL�����ȼ��غ����ǿ���ͨ��more /boot/System.map��nm vmlinux����鿴��������û��EXPORT_SYMBOL�ģ���Ŀǰ��֪����ô�鿴��������飺
1.��֤//EXPORT_SYMBOL
ģ��hello.c�������£�
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
     Makefile�����ļ����£�
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
     11     $(RM) .*.cmd *.mod.c *.o *.ko -r .tmp*make; insmod hello.ko֮��ͨ��dmesg�����н����
__kcrctab_per_cpu__hrtimer_bases = 1ac19564
__kstrtab_per_cpu__hrtimer_bases = per_cpu__hrtimer_bases
__ksymtab_per_cpu__hrtimer_bases value = c0279ea0, name = per_cpu__hrtimer_basesͨ��nm vmlinux | grep per_cpu__hrtimer_bases���ǿ��Կ������µĶ�Ӧ��ϵ��
1ac19564 A __crc_per_cpu__hrtimer_bases
c02678b4 r __kcrctab_per_cpu__hrtimer_bases
c026926b r __kstrtab_per_cpu__hrtimer_bases
c0265018 r __ksymtab_per_cpu__hrtimer_bases
c0279ea0 d per_cpu__hrtimer_bases�Ա������������ݡ�
��ʵ��ֻ��Ϊ����֤һ��EXPROT_SYMBOL.
2.1.//EXPORT_SYMBOL��//EXPORT_SYMBOL_GPL������
ģ��1��hello.c
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
ģ��2��hello2.c
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
    ���ȱ��������ģ�飺hello.ko, hello2.ko
    A.��hello2.c��ע�͵�//MODULE_LICENSE("GPL")��function2()���У���insmod hello.koȻ��insmod hello2.ko��һ��������
    B.��insmod hello2.koȻ��insmod hello.ko�����г�����Ϣ��ͨ��dmesg�鿴��ʾ���£�hello2: Unknown symbol function1
    C.��hello2.c�д�function2()����insmod hello.koȻ��insmod hello2.ko��ģ��hello2.ko�޷����أ���ʾ������Ϣ��insmod: error inserting 'hello2.ko': -1 File exists��ͨ��dmesg�鿴��ʾ���£�hello2: Unknown symbol function2����hello2.c�д�//MODULE_LICENSE("GPL")������MODULE_LICENSE("Dual BSD/GPL")����insmod hello.koȻ��insmod hello2.ko��һ��������

����˵//EXPORT_SYMBOL_GPL�ķ��ű���Ҫ��MODULE_LICENSE("GPL")������MODULE_LICENSE("Dual BSD/GPL")֮�������ģ�������á�����MODULE_LICENSE("char")�е�char�������������ַ�����������û��MODULE_LICENSEЧ��һ����
    D.û�п�//MODULE_LICENSE�ں˴��룬��һ��ȥ�ж����롣
 
 
