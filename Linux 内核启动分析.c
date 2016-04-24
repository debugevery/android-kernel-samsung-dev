//zjz(){}
//�ں��������� (2010-11-12 09:57) 
//���ࣺ linux���� 
//
//
//
//ϵͳ������У�����ϵͳƽ̨�����ʦ�����Bootloader �ĵ���֮��ͽ���Kernel �ü���ֲ�Ľ׶Σ�
//��������Ҫ��һ����Kernel�����ĵ��ԣ��ڵ���Kernel ������ͨ����������������������쳣:

// Uncompressing Linux............................................................
// 
// ........................... done, booting the kernel.( �����ڴ˴�)
// 
//  
// 
// ע �⣺������arch/arm/boot/compressed/head.S�Ľ�ѹ���̣�������decompress_kernel()(ͬĿ¼��
// �� misc.c)->include/asm-arm/arch-xxx/uncompress.h��putc()ʵ�֡�������uboot�г�ʼ�� �ģ�
// �õ��������ַ����Ϊ��ʱ�ں˻�û��������
// 
// �� printascii���ǵ����˻�ࡣprintascii()λ��arch/arm/kernel/debug.S������Ҫ���������ַ��
// �������ַͨ ��machine_start�ṩ������صĺ���include/asm/arch-xxx/debug-macro.Sʵ�֣����������ˡ�
// 
// 10-05-14��ӣ�debug.s������Ҫ�ж�һ�µ�ǰ�Ƿ����mmu��Ȼ��ָ��uart�Ļ�ַ��
// �ڽ�ѹ�׶ε�head.s��mmu��1:1ӳ�䣬Ŀ���Ǽӿ��ٶȡ������ں˵�head.s������������mmu�ˣ���ʱ���������ַ�ˡ�
// 
// 
// 
// 
// 
// ���������쳣��������������ԭ���кܶ࣬�����EVM ��� Ӳ�������޸ģ��������FLASH �ռ��С��
// ��ַ���ͺţ�������SDRAM��DDR SDRAM �ռ��С����ַ���ͺţ������˾���Ƶ�ʵȣ����忨ID�Ų�֧�ֵȡ�
// ��ô��ν��е����ǣ���ʵ�����ֵ��Լ����Ƚ���Ч��
// 
// Kernel �������Լ���- ʹ��printascii() ��������start_kernel() ��û���� ����booting the kernel ֮
// ��Kernel ����ִ�е���start_kernel() ������ȷ��start_kernel() �з�ִ�о������俪ʼ�������
// ��printascii("start_kernel ��") ���������û�д�ӡ��start_kernel ����˵��start_kernel() û�����У�
// ��ô���ܵ�ԭ����Bootloader ���õ������������� Kernel ���ص�(DDR) SDRAM �ĵ�ַ����ȷ�� 
// Kernel ����ʱָ����(DDR) SDRAM ���е�ַ����ȷ�ȡ���������Ҫһ��һ���Ų���󣬵������Ų���
// �ϣ�ͨ����ӡ�� start_kernel �����ֱ�Ȼ�������ӡ��������Ϣ˵�� Kernel�� ���뵽start_kernel() ִ
// �У������ʱ�д���������ӡ�ͱȽϳɹ��ˣ������Ȼû�д�ӡ������Ϣ������Ҫ����һ�ֵ��Լ�����
// 
// �������޸ģ�init/main.c <<-

��

extern void printascii(const char*);     // Modify

asmlinkage void __init start_kernel(void)

{

    char * command_line;

    extern struct kernel_param __start___param[], __stop___param[];

    printascii("start_kernel ��");        // Modify

    smp_setup_processor_id();

// ��
// 
// ->>
// 
// Kernel �������Լ���- ʹ��printascii() ������ӡprintk() ������Ϣ �����Kernel�ѽ��뵽start_kernel() ִ
// �У���Ȼû��������Ϣ��ӡ������˵�����ڲ����ʳ�����Ŀ����ԱȽϴ�������Ϣ����ʱ���浽��
// ʱbuffer--printk_buf �еģ�����start_kernel() �л�Դ��ڲ��������³�ʼ��������ʼ����ɺ�
// �����ϵͳ������Ϣ���ӡ���������ܴ�ӡ˵�����ڴ��ڲ����ʳ�ʼ����ϵͳʱ��Դû�г�ʼ����ȷ��
// ͨ����ϵͳ ʱ��Դ��ʵ�ʵľ���Ƶ�ʲ�һ�µ��µģ�ͨ���Ų�ͽ����������ϵͳ������Ϣ����
// ��ȷ��ӡ�ġ�Ϊ�˰���������⣬����ʹ�� printascii() ��ӡprintk_buf ���ݡ���������
// ��printascii ������ӡ��ϵͳ��Ϣ��Ԥ���ϵͳ��Ϣ���бȽϣ��Ӷ��ӿ�������Ľ��ȡ�
// 
// �������޸ģ�kernel/printk.c   <<-
// 
��

extern void printascii(const char*);    // Modify

static char printk_buf[1024];           // Modify

asmlinkage int printk(const char *fmt, ...)

{

    va_list args;

    int r;

    va_start(args, fmt);

    r = vprintk(fmt, args);

    va_end(args);

    printascii(printk_buf);            // Modify

    return r;

}

��

static int recursion_bug;

static int new_text_line = 1;

//static char printk_buf[1024];        // Modify

��

// ->>
// 
// ������Kernel �ü���ֲ����������Ҫ�������������Լ��������ʹ�ý���������Ч�ʵ�������
// ����Ӳ��ƽ̨������ARM �����������͵�CPU ��Ҳ�������ĸ� Kernel �汾����Linux-2.6.24 ��
// Linux-2.6.30 �� �����Բ����������������Լ������ʵ�����⡣Ϊ��֧��printascii() ������
// ��Ҫ�� Kernel �ü��У�make menuconfig �����Kernel hacking ->[*]Kernel low - level debugging functions ��֧�֡�
// 
// �ҵĲ���:
// 
// 1/ ������/kernel/head.s����Ӵ�ӡ���Ƿ��ܵ�mmu����ǰ:




__turn_mmu_on:

    //��ӡһ���ַ�a


    mov r9,r0

    mov r0,'a'

    bl printascii //�ú���λ��arch/arm/kernel/debug.s�������� include/mach/debug-macro.S

    mov r0,r9
    //���ڿ���mmu
    mov    r0, r0
    mcr    p15, 0, r0, c1, c0, 0        @ write control reg
    mrc    p15, 0, r3, c0, c0, 0        @ read id reg
    mov    r3, r3
    mov    r3, r3
    mov    pc, r13    /*ʵ�ʵ�����__switch_data,��head-common.s*/




// 2/ һ�㰴¥�Ϸ���,��startkernel�Ϳ��Դ�ӡ����,���:�ڵ�һ�����Դ�ӡ,������mmu���ܴ�ӡ,
// �Ǿ����������ַӳ������,��������Ҹ���2����....
// 
// 3/ �����û�з�Ӧ����Ҫ��鴮�ڴ�ӡ�Ƕ� debug-macro.S �Ƿ��������ˡ�
// 
// 
// �ܽ�һ��:
// 
// /compressed/head.s��/kernel/head.s�����ϲ��ø�,���ļ�ͷ,2001��д��,��֪����.�Ǻ�.
// 
==========================================================================================


// 2.4�ں��������̼��������̵��Է������ߣ�����������  ��Դ������԰  ����ʱ�䣺2010-08-18 09:51  
// bios���ں˿������ڴ�󣬽�ִ��Ȩ�޽����ںˡ�һ��Ƕ��ʽʹ�õ�zImage��ʽ�����ָ�ʽ���׵�ַ��
// һ��δѹ���Ŀ�ִ�д�����ڣ����δѹ���Ĵ�����Ҫ����һ�ǽ�ѹ�������Ǳ�����bios����Ĳ���ת��
// �ںˡ���ô������̵���ش��뼰�ļ����£�2410Ϊ������
// 
// arch/arm/boot/compressed/head.s 
// 
// ---����C����-->
// 
// arch/arm/boot/compressed/misc.c��decompress_kernel()
// ������ѹ�ںˡ�
// 
// ---��ת����ѹ���ں˵Ŀ�ִ�д���-->arch/arm/kernel/head-armv.s ��ʼ��
// 
// ---��ת���ں˵�C�����-->init/main.c��asmlinkage void __init start_kernel(void)
// 
//  
// 
// ���Է��������ں˵�console_init();����������֮ǰprintk�������ں�����Ч����˵��ӡ��������
// ʹ�õĴ�������Ϊbios�����á�console_init();������init/main.c�ļ���start_kernel(void)����
// �б����ã��ر�����ڵ����������֮ǰ�ں�ʹ����printk������û��ʵ�ʵĴ�ӡ��������ڳ�ʼ
// ��console��ǰ���printk���ݶ������ӡ������
// 
// 1.head.s ������misc.c�ļ�����C����д������Ϣ�������head.s�û��bl����
// 
// 2.head-armv.s ����Ҫ��������
// 
// a.�����ں˴�err�������
// 
// Kernel hacking  --->  
// 
//   [*] Kernel debugging 
// 
//   [*]   Verbose kernel error messages 
// 
//   [*]   Kernel low-level debugging functions 
// 
// b.�����ļ������еĻ��__err���빦��
// 
//  
// 
// �ο��������ϣ�
// 
// linux2.4��������(1)---�ں�������ַ��ȷ�� vmlinux LOAD_ADDR ZRELADDR
// 
// http://blog.chinaunix.net/u/31100/showart_244622.html 
// 
// ================================ 
// 
// Author: taoyuetao
// Email: tao_yuetao@yahoo.com.cn 
// Blog: taoyuetao.cublog.cn 
// 
// 2006-11-03 
// 
// ================================ 
// 
// �ں˱������ӹ���������vmlinux.lds�ļ�����armΪ��vmlinux.lds�ļ�λ��kernel/arch/arm/vmlinux.lds��
// ���Ǹ��ļ�����vmlinux-armv.lds.in���ɵģ����ݱ���ѡ��Ĳ�ͬԴ�ļ���������vmlinux-armo.lds.in��
// vmlinux-armv-xip.lds.in�� 
// 
// vmlinux-armv.lds�����ɹ�����kernel/arch/arm/Makefile�� 
// 
// (��2.6��û���ҵ����,��/arch/arm/boot/Makefile) 
// 
// LDSCRIPT     = arch/arm/vmlinux-armv.lds.in 
// 
// arch/arm/vmlinux.lds: arch/arm/Makefile $(LDSCRIPT) \
// $(wildcard include/config/cpu/32.h) \
// $(wildcard include/config/cpu/26.h) \
// $(wildcard include/config/arch/*.h)
// @echo '  Generating $@' 
// @sed 's/TEXTADDR/$(TEXTADDR)/;s/DATAADDR/$(DATAADDR)/' $(LDSCRIPT) >$@ 
// 
// vmlinux-armv.lds.in�ļ������ݣ� 
// 
// OUTPUT_ARCH(arm)
// ENTRY(stext)
// SECTIONS
// {
//     . = TEXTADDR;
//     .init : {           /* Init code and data       */
//         _stext = .;
//         __init_begin = .;
//             *(.text.init)
//         __proc_info_begin = .;
//             *(.proc.info)
//         __proc_info_end = .;
//         __arch_info_begin = .;
//             *(.arch.info)
//         __arch_info_end = .;
//         __tagtable_begin = .;
//             *(.taglist)
//         __tagtable_end = .;
//             *(.data.init)
//         . = ALIGN(16);
//         __setup_start = .;
//             *(.setup.init)
//         __setup_end = .;
//         __initcall_start = .;
//             *(.initcall.init)
//         __initcall_end = .;
//         . = ALIGN(4096);
//         __init_end = .;
//     }
// ����TEXTADDR�����ں������������ַ��������kernel/arch/arm/Makefile�У�
// ifeq ($(CONFIG_CPU_32),y)
// PROCESSOR    = armv
// TEXTADDR     = 0xC0008000
// LDSCRIPT     = arch/arm/vmlinux-armv.lds.in
// endif
// ��Ҫע����������������ַ�����������ַ�� 
// 
// һ������¶�������vmlinux���ٶ��ں˽���ѹ����ΪzImage��ѹ����Ŀ¼��kernel/arch/arm/boot��
// ���ص�flash�е���ѹ�����zImage�ļ���zImage����ѹ�����vmlinux�ͽ�ѹ��������ɣ�����ͼ��ʾ�� 
// 
//             |-----------------|\    |-----------------|
//             |                    | \   |                    |
//             |                    |  \  | decompress code |
//             |     vmlinux        \  |-----------------|    zImage
//             |                    |    \|                    |
//             |                    |     |                    |
//             |                    |     |                    |    
//             |                    |     |                    |
//             |                    |    /|-----------------|
//             |                    |   /
//             |                    |  /
//             |                    | /
//             |-----------------|/
// zImage���ӽű�Ҳ����vmlinux.lds��λ��kernel/arch/arm/boot/compressed��
// ����ͬһĿ¼�µ�vmlinux.lds.in�ļ����ɵģ��������£�
// OUTPUT_ARCH(arm)
// ENTRY(_start)
// SECTIONS
// {
//    . = LOAD_ADDR;   //�����2.6���Ѿ�ȥ���� 
//    _load_addr = .;    //Ҳȥ��
//    . = TEXT_START;
//    _text = .;
//    .text : {
//      _start = .;
// ����LOAD_ADDR����zImage�н�ѹ�������ramƫ�Ƶ�ַ��TEXT_START���ں�ram������ƫ�Ƶ�ַ�������ַ�������ַ��
// ��kernel/arch/arm/boot/Makefile�ļ��ж����ˣ�
// ZTEXTADDR   =0
// ZRELADDR     = 0xa0008000  //�����2.6����makefile.boot���� 
// 
// ZTEXTADDR���ǽ�ѹ�������ramƫ�Ƶ�ַ��ZRELADDR���ں�ram������ƫ�Ƶ�ַ�����￴��ָ��ZTEXTADDR�ĵ�ַΪ0��
// �����ǲ���ȷ�ģ���Ϊ�ҵ�ƽ̨�ϵ�ram��ʼ��ַ��0xa0000000����Makefile�ļ��п����˶Ըõ�ַ���õļ���ע�ͣ�
// # We now have a PIC decompressor implementation.  Decompressors running
// # from RAM should not define ZTEXTADDR.  Decompressors running directly
// # from ROM or Flash must define ZTEXTADDR (preferably via the config)
// ������ʶ���������ram�н��н�ѹ��ʱ������ָ������ram�е����е�ַ���������flash�оͱ���ָ�����ĵ�ַ������
// ���ｫZTEXTADDRָ��Ϊ0��Ҳ����û������ָ����ַ�� 
// 
// ��kernel/arch/arm/boot/compressed/Makefile�ļ���һ�нű��� 
// 
// SEDFLAGS    = s/TEXT_START/$(ZTEXTADDR)/;s/LOAD_ADDR/$(ZRELADDR)/;s/BSS_START/$(ZBSSADDR)/ 
// 
// //2.6��Ϊs/TEXT_START/$(ZTEXTADDR)/;s/BSS_START/$(ZBSSADDR)/ 
// 
// ʹ��TEXT_START = ZTEXTADDR��LOAD_ADDR = ZRELADDR�� 
// 
// ����vmlinux.lds�����ɹ������£�
// vmlinux.lds:    vmlinux.lds.in Makefile $(TOPDIR)/arch/$(ARCH)/boot/Makefile $(TOPDIR)/.config
// @sed "$(SEDFLAGS)" < vmlinux.lds.in > $@
// ���Ͼ����Ҷ��ں�������ַ�ķ������ܽ�һ���ں�������ַ�����ã�
// 1������kernel/arch/arm/Makefile�ļ��е�
//    TEXTADDR     = 0xC0008000 //2.6��ʱû�ҵ� 
//    �ں������������ַ
// 2������kernel/arch/arm/boot/Makefile�ļ��е�
//    ZRELADDR     = 0xa0008000
//    �ں������������ַ
//    �����Ҫ��flash����������Ҫ����
//    ZTEXTADDR��ַ�� 
// 
//   
// 
// linux2.4��������(2)---�ں˽�ѹ������ compress booting kernel 
// 
================================ 

// Author: taoyuetao
// Email: tao_yuetao@yahoo.com.cn 
// Blog: taoyuetao.cublog.cn 
// 
// 2006-11-06 
// 
// ================================ 
// 
// �ں�ѹ���ͽ�ѹ�����붼��Ŀ¼kernel/arch/arm/boot/compressed��
// ������ɺ󽫲���vmlinux��head.o��misc.o��head-xscale.o��piggy.o�⼸���ļ���
// head.o���ں˵�ͷ���ļ��������ʼ���ã�
// misc.o����Ҫ�����ں˵Ľ�ѹ����������head.o֮��
// head-xscale.o�ļ���Ҫ���Xscale�ĳ�ʼ������������ʱ��head.o�ϲ���
// piggy.o��һ���м��ļ�����ʵ��һ��ѹ�����ں�(kernel/vmlinux)��ֻ����û�кͳ�ʼ���ļ�����ѹ�ļ����Ӷ��ѣ�
// vmlinux��(û�У���lw��zImage��ѹ�������ں�)ѹ�������ںˣ�������piggy.o��head.o��misc.o��head-xscale.o��ɵġ� 
// 
// ( 
// 
// 2.6�У���compressed/makefile������� 
// 
// #����vmlinux����
// targets       := vmlinux vmlinux.lds piggy.gz piggy.o font.o font.c \
//          head.o misc.o $(OBJS) 
// 
// ) 
// 
// ��BootLoader���ϵͳ�������Ժ󲢽�Linux �ں˵����ڴ�֮�󣬵���bootLinux()��
// �����������ת��kernel����ʼλ�á����kernelû��ѹ�����Ϳ��������ˡ�
// ���kernelѹ��������Ҫ���н�ѹ����ѹ������kernelͷ���н�ѹ����
// ѹ������kernel��ڵ�һ���ļ�Դ��λ����arch/arm/boot/compressed/head.S��
// �������ú���decompress_kernel()������������ļ�arch/arm/boot/compressed/misc.c�У�
// decompress_kernel()�ֵ���proc_decomp_setup(),arch_decomp_setup()�������ã�
// Ȼ��ʹ���ڴ�ӡ����Ϣ��Uncompressing Linux...���󣬵���gunzip()�����ں˷���ָ����λ�á� 
// 
// ���·���head.S�ļ���
// (1)���ڸ���Arm CPU��DEBUG����趨��ͨ���������ͳһ������
// (2)����kernel��ʼ�ͽ�����ַ������architecture ID��
// (3)�����ARM2���ϵ�CPU�У��õ�����ͨ�û�ģʽ�������������û�ģʽ��Ȼ����жϡ�
// (4)����LC0�ṹdelta offset���ж��Ƿ���Ҫ�����ں˵�ַ(r0����ƫ�������ж�r0�Ƿ�Ϊ��)��
//    �����Ƿ���Ҫ�����ں˵�ַ������Ϊ��Ҫ����arch/arm/boot/Makefile��arch/arm/boot/compressed/Makefile
//    ��arch/arm/boot/compressed/vmlinux.lds.in�����ļ�����Ҫ��vmlinux.lds.in�����ļ�����Ҫ�ε�λ�ã�
//    LOAD_ADDR(_load_addr)��0xA0008000��������TEXT_START(_text��_start)��λ��ֻ��Ϊ0��BSS_START(__bss_start)��ALIGN(4)��
//    ���������Ľ�������ڣ����ں˽�ѹ�����з�ʽ��Ҳ����˵���ں˽�ѹǰ�����ڴ�(RAM)�л�����FLASH�ϣ�
//    ��Ϊ������ǵ�BOOTLOADER��ѹ���ں�(zImage)�Ƶ���RAM��0xA0008000λ�ã����ǵ�ѹ���ں������ڴ�(RAM)��0xA0008000��ַ��ʼ ˳�����У�
//    ������ǵ�r0��õ�ƫ�����������ַ(0xA0008000)���������Ĺ�����Ҫ���ں˾������Ե�ַת��Ϊ�ڴ�������ַ���������ں˵�ַ��
// (5)��Ҫ�����ں˵�ַ����r0��ƫ�����ӵ�BSS region��GOT table�С�
// (6)���bss��ջ�ռ�r2��r3��
// (7)����C����������Ҫ�Ļ��棬������64K��ջ�ռ䡣
// (8)��ʱr2�ǻ���Ľ�����ַ��r4��kernel�����ִ�е�ַ��r5��kernel�����ļ��Ŀ�ʼ��ַ������Ƿ��ַ�г�ͻ��
//    ��r5����r2��ʹdecompress���kernel��ַ����64K��ջ֮��
// (9)�����ļ�misc.c�ĺ���decompress_kernel()����ѹ�ں��ڻ�������ĵط�(r2��ַ֮��)����ʱ���Ĵ���ֵ�����±仯��
//    r0Ϊ��ѹ��kernel�Ĵ�С
//    r4Ϊkernelִ��ʱ�ĵ�ַ
//    r5Ϊ��ѹ��kernel����ʼ��ַ
//    r6ΪCPU����ֵ(processor ID)
//    r7Ϊϵͳ����ֵ(architecture ID)
// (10)��reloc_start���뿽��֮kernel֮��(r5+r0֮��)������������棬����ִ��reloc_start��
// (11)reloc_start��r5��ʼ��kernel������r4��ַ����
// (12)���cache���ݣ��ر�cache����r7��architecture ID����r1��ִ��r4��ʼ��kernel���롣 
// 
// ����򵥽���һ�½�ѹ�����̣�Ҳ���Ǻ���decompress_kernelʵ�ֵĹ��ܣ�
// ��ѹ������λ��kernel/lib/inflate.c��inflate.c�Ǵ�gzipԴ�����з�������ġ�������һЩ��ȫ�����ݵ�ֱ�����á�
// ��ʹ��ʱ��Ҫֱ��Ƕ�뵽�����С�gzipѹ���ļ�ʱ������ǰ32K�ֽڵķ�Χ��Ѱ���ظ����ַ������б��룬 
// �ڽ�ѹʱ��Ҫһ������Ϊ32K�ֽڵĽ�ѹ��������������Ϊwindow[WSIZE]��inflate.cʹ��get_byte()��ȡ�����ļ���
// ��������ɺ������Ч�ʡ����뻺����ָ����붨��Ϊinptr��inflate.c�ж�֮�м���������inflate.c����flush_window()
// �����window�������еĽ�ѹ�����ֽڴ���ÿ�����������outcnt������ʾ����flush_window()�У����� 
// �������ֽڴ�����CRC����ˢ��crc�������ڵ���gunzip()��ʼ��ѹ֮ǰ������makecrc()��ʼ��CRC�����
// ���gunzip()����0��ʾ��ѹ�ɹ��� 
// 
// �������ں������Ŀ�ʼ���ῴ�������������
// Uncompressing Linux...done, booting the kernel.
// ��Ҳ����decompress_kernel�����ڲ�����ģ���������puts()����ַ�����
// puts����kernel/include/asm-arm/arch-pxa/uncompress.h��ʵ�ֵġ� 
// 
// ִ�����ѹ���̣��ٷ��ص�head.S�У������ںˣ� 
// 
// call_kernel:    bl  cache_clean_flush
//          bl  cache_off
//          mov r0, #0
//          mov r1, r7          @ restore architecture number
//          mov pc, r4          @ call kernel
// ����Ϳ�ʼ�������ں��ˡ� 
// 
// ��������CSDN���ͣ�ת�������������http://blog.csdn.net/lanmanck/archive/2009/06/18/4278724.aspx 
// 
//   
// 
// linux2.4��������(2)---�ں˽�ѹ������(��,����ϸ) compress booting kernel 
// 
// ��:http://blog.csdn.net/BoySKung/archive/2008/12/05/3448083.aspx# 
// 
// �ļ�:linux-2.6.20.6/arch/arm/boot/compressed/head.S 
// ��ͷ��һ�κ궨�壬����ֻ������һ�Σ�����һ��gnu arm���ĺ궨�� 
// #elif defined(CONFIG_ARCH_S3C2410) 
//               .macro loadsp, rb 
//               mov \rb, #0x50000000 
//               add  \rb, \rb, #0x4000 * CONFIG_S3C2410_LOWLEVEL_UART_PORT 
//               .endm 
// #else 
// ���ﶨ����һ���꣬������loadsp��rb�������Ĳ�������Ĳ����ڱ�����ʱ����ӡ�\��,�磺 
// mov \rb, #0x50000000. 
// �궨�����֮������һ���Σ� 
//               .section ".start", #alloc, #execinstr 
// ����εĶ����� .start��#alloc��ʾSection contains allocated data, #execinstr��ʾSection contains executable instructions. 
// /* 
// * sort out different calling conventions 
// */ 
//               .align 
// start: 
//               .type       start,#function /*.typeָ��start��������Ǻ�������*/ 
//               .rept 8 
//               mov r0, r0 //���������ظ�8�Σ��൱��nop������Ϊʲô����������������� 
//               .endr 
//               b     1f 
//               .word      0x016f2818           @ Magic numbers to help the loader 
//               .word      start               @ absolute load/run zImage address 
//               .word      _edata                   @ zImage end address 
// 1:            mov r7, r1                    @ save architecture ID 
//               mov r8, r2                    @ save atags pointer 
// r1��r2�зֱ�������bootloader���ݹ�����architecture ID��ָ�����б��ָ�롣���ｫ�����������ȱ��档 
// #ifndef __ARM_ARCH_2__ 
//               /* 
//                * Booting from Angel - need to enter SVC mode and disable 
//                * FIQs/IRQs (numeric definitions from angel arm.h source). 
//                * We only do this if we were in user mode on entry. 
//                */ 
// ��ȡcpsr���ж��Ƿ���������supervisorģʽ������u-boot����kernel��ϵͳ�Ѿ�����SVC32ģʽ��������angel��������userģʽ������Ҫ��������ָ�֮�����ٴ�ȷ���жϹرգ������cpsrд�� 
// Angel �� ARM �ĵ���Э��,�����õ� MULTI-ICE �õ��� RDI ͨѶЭ��, ANGLE ��Ҫ�ڰ������� פ������,Ȼ��ͨ�� ���ھͿ��Ե����� 
// �������һ�°�����. 
// ������������ ARM Ŀ���һ�ֻ��ƣ��ɽ�����Ӧ�ó�����������/������� 
// ���������е������������� ���磬ʹ�ô˻��ƿ������� C ���еĺ������� 
// printf() �� scanf()����ʹ����������Ļ�ͼ��̣���������Ŀ��ϵͳ���䱸��Ļ�� 
// ���̡� 
// ��������ͨ��һ�鶨��õ����ָ��� swi����ʵ�ֵģ���Щָ��ͨ������� 
// �������쳣�� Ӧ�ó��������Ӧ�İ��������ã�Ȼ����Դ�������쳣�� �� 
// �Դ����ṩ������֮��ı���ͨ�š� 
//               mrs  r2, cpsr          @ get current mode 
//               tst    r2, #3                    @ not user? 
//               bne  not_angel 
// ��������ʵ������������ ARM Ŀ��֮�����õ��� I/O ���ܣ� 
//               mov r0, #0x17              @ angel_SWIreason_EnterSVC 
//               swi  0x123456              @ angel_SWI_ARM 
// 0x17��angel_SWIreason_EnterSVC������������������������Ϊ�����û�ģʽ��ͨ�������� CPSR �е������ж�����λ�����������жϡ�0x123456��armָ��İ������������ 
// not_angel:  //����ͨ��angel���Խ����ں� 
//               mrs  r2, cpsr          @ turn off interrupts to 
//               orr   r2, r2, #0xc0         @ prevent angel from running 
//               msr  cpsr_c, r2   //���ｫcpsr��I��Fλ�ֱ��á�1�����ر�IRQ��FIQ 
// #else 
//               teqp pc, #0x0c000003          @ turn off interrupts 
// ���� TEQP PC,#(��ģʽ���) ���ı�ģʽ 
// #endif 
// ���������һЩ��������صĴ������ӵ����λ�ã�Ҳ����arch/arm/boot/compressed/head-xxx.S�ļ��еĴ��롣���Ǹ��ļ�����I/D cache�Լ�MMU����һЩ���� 
// /* 
//                * Note that some cache flushing and other stuff may 
//                * be needed here - is there an Angel SWI call for this? 
//                */ 
//               /* 
//                * some architecture specific code can be inserted 
//                * by the linker here, but it should preserve r7, r8, and r9. 
//                */ 
//               .text 
//               adr   r0, LC0 //��ǰ����ʱLC0�������ڵ�ַλ�� 
//               ldmia       r0, {r1, r2, r3, r4, r5, r6, ip, sp} 
//               subs r0, r0, r1        @ calculate the delta offset //�����õ�ǰ���е�ַ�����ӵ�ַ 
//                                           @ if delta is zero, we are   //��ƫ����������r0�С� 
//               beq  not_relocated         @ running at the address we 
//                                           @ were linked at. 
// �����⼸�д��������жϴ����Ƿ��Ѿ��ض�λ���ڴ��У�LC0���������288�ж��塣 
//               .type       LC0, #object 
// LC0:              .word      LC0               @ r1 //���Ҫ���ص�r1�е�LC0������ʱLC0�ĵ�ַ 
//               .word      __bss_start            @ r2 
//               .word      _end                     @ r3 
//               .word      zreladdr          @ r4 
//               .word      _start                    @ r5 
//               .word      _got_start              @ r6 
//               .word      _got_end        @ ip 
//               .word      user_stack+4096           @ sp 
// ͨ����ǰ����ʱLC0�ĵ�ַ�������������ӵĵ�ַ���бȽ��жϡ�������������������ӵĵ�ַ�ϡ� 
// ����������������ӵĵ�ַ�ϣ�������Ĵ���������� 
//               /* 
//                * We're running at a different address.  We need to fix 
//                * up various pointers: 
//                *   r5 - zImage base address 
//                *   r6 - GOT start 
//                *   ip - GOT end 
//                */ 
//               add  r5, r5, r0 //�޸��ں�ӳ�����ַ 
//               add  r6, r6, r0 
//               add  ip, ip, r0 //�޸�got�����ʼ�ͽ���λ�� 
// #ifndef CONFIG_ZBOOT_ROM 
//               /*��û�ж���CONFIG_ZBOOT_ROM����ʱ���е�����ȫλ���޹ش��� 
// λ���޹ش��룬Ҳ���ǲ����о��Ե�ַѰַ������Ϊ�˱�����Ե�ַ��ȷ�� 
// ��Ҫ��bss���Լ���ջ�ĵ�ַ�����е��� 
//                * If we're running fully PIC === CONFIG_ZBOOT_ROM = n, 
//                * we need to fix up pointers into the BSS region. 
//                *   r2 - BSS start 
//                *   r3 - BSS end 
//                *   sp - stack pointer 
//                */ 
//               add  r2, r2, r0 
//               add  r3, r3, r0 
//               add  sp, sp, r0 
//               /* 
//                * Relocate all entries in the GOT table. 
//                */ 
// 1:            ldr   r1, [r6, #0]            @ relocate entries in the GOT 
//               add  r1, r1, r0        @ table.  This fixes up the 
//               str   r1, [r6], #4            @ C references. 
//               cmp r6, ip 
//               blo   1b 
// #else //��������CONFIG_ZBOOT_ROM��ֻ��got������bss������ķ��Ž����ض�λ 
// //ΪʲôҪ�������أ�����Ҳ����� 
//               /* 
//                * Relocate entries in the GOT table.  We only relocate 
//                * the entries that are outside the (relocated) BSS region. 
//                */ 
// 1:            ldr   r1, [r6, #0]            @ relocate entries in the GOT 
//               cmp r1, r2                    @ entry < bss_start || 
//               cmphs     r3, r1                    @ _end < entry 
//               addlo       r1, r1, r0        @ table.  This fixes up the 
//               str   r1, [r6], #4            @ C references. 
//               cmp r6, ip 
//               blo   1b 
// #endif 
// ������е�ǰ���е�ַ�����ӵ�ַ��ȣ���������ض�λ��ֱ�����bss�� 
// not_relocated: mov r0, #0 
// 1:            str   r0, [r2], #4            @ clear bss 
//               str   r0, [r2], #4 
//               str   r0, [r2], #4 
//               str   r0, [r2], #4 
//               cmp r2, r3 
//               blo   1b 
// ֮����ת��cache_on�� 
//               /* 
//                * The C runtime environment should now be setup 
//                * sufficiently.  Turn the cache on, set up some 
//                * pointers, and start decompressing. 
//                */ 
//               bl     cache_on 
// cache_on��327�ж��� 
//               .align       5 
// cache_on:       mov r3, #8                    @ cache_on function 
//               b     call_cache_fn 
// ��r3��ֵ��Ϊ8��ʲô���أ�����ῴ������������ת��call_cache_fn����������Ķ�����512�� 
// call_cache_fn: adr   r12, proc_types  //��proc_types�ĵ�ַ���ص�r12�� 
// #ifdef CONFIG_CPU_CP15 
//               mrc p15, 0, r6, c0, c0   @ get processor ID 
// #else 
//               ldr   r6, =CONFIG_PROCESSOR_ID 
// #endif 
// 1:            ldr   r1, [r12, #0]          @ get value 
//               ldr   r2, [r12, #4]          @ get mask 
//               eor   r1, r1, r6        @ (real ^ match) 
//               tst    r1, r2                    @       & mask 
//               addeq      pc, r12, r3             @ call cache function 
//               add  r12, r12, #4*5 
//               b     1b 
// ��һ�δ������Ȼ�õ�ǰ������id��Ȼ���proc_types��Ҳ���Ǵ��������ͱ����õĴ�����id���бȽϣ����ҵ���Ӧ�Ĵ������󣬾ͼ��ض�Ӧ��cache�������� 
// addeq      pc, r12, r3             @ call cache function 
// �����õ�������˵��r3������ֵ��8��Ҳ����һ��ƫ������r12�д洢����ĳ����������ش���ģ��Ļ���ַ�� 
// proc_type�Ķ������£���541�� 
//               .type       proc_types,#object 
// proc_types: 
//               .word      0x41560600           @ ARM6/610 
//               .word      0xffffffe0 
//               b     __arm6_mmu_cache_off      @ works, but slow 
//               b     __arm6_mmu_cache_off 
//               mov pc, lr 
// @           b     __arm6_mmu_cache_on              @ untested 
// @           b     __arm6_mmu_cache_off 
// @           b     __armv3_mmu_cache_flush 
//               .word      0x00000000           @ old ARM ID 
//               .word      0x0000f000 
//               mov pc, lr 
//               mov pc, lr 
//               mov pc, lr 
//               .word      0x41007000           @ ARM7/710 
//               .word      0xfff8fe00 
//               b     __arm7_mmu_cache_off 
//               b     __arm7_mmu_cache_off 
//               mov pc, lr 
//               .word      0x41807200           @ ARM720T (writethrough) 
//               .word      0xffffff00 
//               b     __armv4_mmu_cache_on 
//               b     __armv4_mmu_cache_off 
//               mov pc, lr 
//               .word      0x41007400           @ ARM74x 
//               .word      0xff00ff00 
//               b     __armv3_mpu_cache_on 
//               b     __armv3_mpu_cache_off 
//               b     __armv3_mpu_cache_flush 
//               .word      0x41009400           @ ARM94x 
//               .word      0xff00ff00 
//               b     __armv4_mpu_cache_on 
//               b     __armv4_mpu_cache_off 
//               b     __armv4_mpu_cache_flush 
//               .word      0x00007000           @ ARM7 IDs 
//               .word      0x0000f000 
//               mov pc, lr 
//               mov pc, lr 
//               mov pc, lr 
//               @ Everything from here on will be the new ID system. 
//               .word      0x4401a100           @ sa110 / sa1100 
//               .word      0xffffffe0 
//               b     __armv4_mmu_cache_on 
//               b     __armv4_mmu_cache_off 
//               b     __armv4_mmu_cache_flush 
//               .word      0x6901b110           @ sa1110 
//               .word      0xfffffff0 
//               b     __armv4_mmu_cache_on 
//               b     __armv4_mmu_cache_off 
//               b     __armv4_mmu_cache_flush 
//               @ These match on the architecture ID 
//               .word      0x00020000    @ ARMv4T //�����������Ҫ�ҵ�arm920t�Ĵ���������� 
//               .word      0x000f0000        //�ݣ�ƫ��8��պ���b   __armv4_mmu_cache_on 
//               b     __armv4_mmu_cache_on  //ָ��ĵ�ַ 
//               b     __armv4_mmu_cache_off 
//               b     __armv4_mmu_cache_flush 
//               .word      0x00050000           @ ARMv5TE 
//               .word      0x000f0000 
//               b     __armv4_mmu_cache_on 
//               b     __armv4_mmu_cache_off 
//               b     __armv4_mmu_cache_flush 
//               .word      0x00060000           @ ARMv5TEJ 
//               .word      0x000f0000 
//               b     __armv4_mmu_cache_on 
//               b     __armv4_mmu_cache_off 
//               b     __armv4_mmu_cache_flush 
//               .word      0x0007b000           @ ARMv6 
//               .word      0x0007f000 
//               b     __armv4_mmu_cache_on 
//               b     __armv4_mmu_cache_off 
//               b     __armv6_mmu_cache_flush 
//               .word      0                   @ unrecognised type 
//               .word      0 
//               mov pc, lr 
//               mov pc, lr 
//               mov pc, lr 
//               .size proc_types, . - proc_types 
// ���ҵ��Һ����Ǵ������󣬾͵�����Ӧ�Ĵ��������Ҹ������ǵ�arm920t������������Ӧ�õ���__armv4_mmu_cache_on,������ָ����605�� 
//               .word      0x00020000           @ ARMv4T 
//               .word      0x000f0000 
//               b     __armv4_mmu_cache_on 
//               b     __armv4_mmu_cache_off 
//               b     __armv4_mmu_cache_flush 
// __armv4_mmu_cache_on����424�ж��壬 
// __armv4_mmu_cache_on: 
//               mov r12, lr 
//               bl     __setup_mmu 
//               mov r0, #0 
//               mcr p15, 0, r0, c7, c10, 4     @ drain write buffer 
//               mcr p15, 0, r0, c8, c7, 0      @ flush I,D TLBs 
//               mrc p15, 0, r0, c1, c0, 0      @ read control reg 
//               orr   r0, r0, #0x5000             @ I-cache enable, RR cache replacement 
//               orr   r0, r0, #0x0030    
//               bl     __common_mmu_cache_on 
//               mov r0, #0 
//               mcr p15, 0, r0, c8, c7, 0      @ flush I,D TLBs 
//               mov pc, r12  //���ص�cache_on 
// ��������ת��__setup_mmu��Ȼ�����write buffer��I/Dcache��TLB.���Ŵ�i-cache������ΪRound-robin replacement������__common_mmu_cache_on,��mmu��d-cache.��ҳ�����ַ������ʿ���д��Э�������Ĵ��� c2��c3. __common_mmu_cache_on������������450�С� 
// __common_mmu_cache_on: 
// #ifndef DEBUG 
//               orr   r0, r0, #0x000d             @ Write buffer, mmu 
// #endif 
//               mov r1, #-1 //-1�Ĳ�����ffff ffff, 
//               mcr p15, 0, r3, c2, c0, 0      @ load page table pointer 
//               mcr p15, 0, r1, c3, c0, 0      @ load domain access control //��domain access control�Ĵ� 
//               b     1f                                 //ȫ���á�1�� 
//               .align       5                   @ cache line aligned 
// 1:            mcr p15, 0, r0, c1, c0, 0      @ load control register 
//               mrc p15, 0, r0, c1, c0, 0      @ and read it back to 
//               sub  pc, lr, r0, lsr #32    @ properly flush pipeline 
// ��ռ����һ��__setup_mmu���������������386�� 
// __setup_mmu:       sub  r3, r4, #16384        @ Page directory size 
//               bic   r3, r3, #0xff          @ Align the pointer 
//               bic   r3, r3, #0x3f00 
// ����r4�д�����ں�ִ�е�ַ����16K��һ��ҳ���������ں�ִ�е�ַ�����16K�ռ������ͨ�� sub  r3, r4, #16384  ���16K�ռ���ֽ�ҳ�����ʼ��ַ����16K�������r3�С���ttb�ĵ�14λ���㡣 
// /* 
// * Initialise the page tables, turning on the cacheable and bufferable 
// * bits for the RAM area only. 
// */ 
// //��ʼ��ҳ������RAM�ռ����cacheable ��bufferableλ 
//               mov r0, r3 
//               mov r9, r0, lsr #18 
//               mov r9, r9, lsl #18         @ start of RAM 
//               add  r10, r9, #0x10000000    @ a reasonable RAM size 
// �����⼸�а�һ��ҳ�����ʼ��ַ������r0�У���ͨ��r0���һ��ram��ʼ��ַ��256K���룩�����������ʼ��ַ��ʼ��256M ram�ռ��Ӧ����������C��Bλ���á�1�� (�ο�arm920t datasheet 3.3.3, table 3-2 level one descryiptor bits), r9��r10�д��������ڴ����ʼ��ַ�ͽ�����ַ 
//               mov r1, #0x12 //һ����������bit[1:0]Ϊ10����ʾ����һ��section��������bit[4] 
// //Ϊ1���ο�arm9205 datasheet 3.3.3 table 3-2 level one 
// //descryiptor bits����ʱbit[8:5]��Ϊ0��ѡ����D0�� 
//               orr   r1, r1, #3 << 10 //һ����������access permission bits bit[11:10]Ϊ11. �� 
//                          //all access types permitted in both modes 
// // (�ο�arm920t datasheet 3.3.3, table 3-2 level 
// //one descryiptor bits, 3.6, table 3-11 interpreting access 
// // permission(AP) bit) 
//               add  r2, r3, #16384  //һ����������Ľ�����ַ�����r2�С� 
// 1:            cmp r1, r9                    @ if virt > start of RAM 
//               orrhs       r1, r1, #0x0c         @ set cacheable, bufferable 
//               cmp r1, r10                  @ if virt > end of RAM 
//               bichs       r1, r1, #0x0c         @ clear cacheable, bufferable 
//               str   r1, [r0], #4            @ 1:1 mapping 
//               add  r1, r1, #1048576 
//               teq   r0, r2 
//               bne  1b 
// ������ξ��Ƕ�һ����������ҳ���ĳ�ʼ�������ȱȽ�����������������ĵ�ַ�Ƿ����Ǹ�256M�Ŀռ��У�������������������Ӧ���ڴ������� cacheable ,bufferable�����������noncacheable, nonbufferable.Ȼ��������д��һ��һ�������������ڣ�����һ������������ڵ�ַ��4����ָ����һ��1M section�Ļ���ַ�����ҳ�����δ��ʼ���꣬�������ʼ���� 
// һ����������ĸ�12λ��ÿ��setcion�Ļ���ַ����������4096��section��һ��ҳ���СΪ16K��ÿ��ҳ�����������ռ4�ֽڣ��պÿ�������4096�������������������ӳ����4096*1M = 4G�Ŀռ䡣 
// /* 
// * If ever we are running from Flash, then we surely want the cache 
// * to be enabled also for our execution instance...  We map 2MB of it 
// * so there is no map overlap problem for up to 1 MB compressed kernel. 
// * If the execution is in RAM then we would only be duplicating the above. 
// */ 
//               mov r1, #0x1e 
//               orr   r1, r1, #3 << 10 //�����н�������bit[11:10] bit[4:1]��λ��(�ο�arm920t 
// // datasheet 3.3.3, table 3-2 level one descryiptor bits) 
//               mov r2, pc, lsr #20 
//               orr   r1, r1, r2, lsl #20  //����ǰ��ַ��1M���룬����r1�е����ݽ���γ�һ�� 
//                             //������ǰָ������section���������� 
//               add  r0, r3, r2, lsl #2   //r3Ϊ�ղŽ�����һ�������������ʼ��ַ��ͨ������ǰ�� 
// //ַ(pc)�ĸ�12λ������λ(�γ�14λ����)��r3�еĵ�ַ 
//                             // (��14λΪ0)����γ�һ��4�ֽڶ���ĵ�ַ����� 
//                             //��ַҲ��16K��һ�����������ڡ���ǰ��ַ��Ӧ�� 
//                             //��������һ��ҳ���е�λ�� 
//               str   r1, [r0], #4 
//               add  r1, r1, #1048576 
//               str   r1, [r0]          //���ｫ�����γɵ�������������������һ��section���� 
// //д������4�ֽڶ����ַ����һ��ҳ��������Ϊr2���� 
// //2λ�� 
//               mov pc, lr       //���أ����ô˺���ʱ������ָ�����һ���mov   r0, #0�ĵ� 
//                        //ַ������lr�� 
// ������е���1:1��ӳ�䣬�����ַ�������ַ��һ���� 
// __common_mmu_cache_on:ִ����󷵻ص�bl cache_on��һ��ָ�226�У� 
//               mov r1, sp                    @ malloc space above stack 
//               add  r2, sp, #0x10000    @ 64k max 
// /* 
// * Check to see if we will overwrite ourselves. 
// *   r4 = final kernel address 
// *   r5 = start of this image 
// *   r2 = end of malloc space (and therefore this image) 
// * We basically want: 
// *   r4 >= r2 -> OK 
// *   r4 + image length <= r5 -> OK 
// */ 
//               cmp r4, r2 
//               bhs  wont_overwrite 
//               sub  r3, sp, r5        @ > compressed kernel size 
//               add  r0, r4, r3, lsl #2      @ allow for 4x expansion 
//               cmp r0, r5 
//               bls   wont_overwrite 
// ��δ��������ڶ�ջ��ȷ����64K��malloc�ռ䣬�ռ����ʼ��ַ�ͽ�����ַ�ֱ�����r1��r2�С�Ȼ���ж������ں˵�ַ��Ҳ���ǽ�ѹ���ں˵���ʼ��ַ���Ƿ����malloc�ռ�Ľ�����ַ��������ھ�����wont_overwriteִ�У�wont_overwrite��������ὲ�������򣬼�������ں˵�ַ�ӽ�ѹ���ں˴�С��Ҳ���ǽ�ѹ���ں˵Ľ�����ַ���Ƿ�С������δ��ѹ�ں�ӳ�����ʼ��ַ��С��Ҳ������wont_owerwriteִ�С����������������������㣬���������ִ�С� 
//               mov r5, r2                    @ decompress after malloc space 
//               mov r0, r5 
//               mov r3, r7 
//               bl     decompress_kernel 
// ���ｫ��ѹ���ں˵���ʼ��ַ��Ϊmalloc�ռ�Ľ�����ַ��Ȼ���Ѵ�����id����ʼʱ������r7�У����浽r3�У����� decompress_kernel��ʼ��ѹ�ںˡ�����������ĸ������ֱ�����r0-r3�У�����arch/arm/boot/compressed /misc.c�ж��塣 
//               add  r0, r0, #127 
//               bic   r0, r0, #127           @ align the kernel length 
// /* 
// * r0     = decompressed kernel length 
// * r1-r3  = unused 
// * r4     = kernel execution address 
// * r5     = decompressed kernel start 
// * r6     = processor ID 
// * r7     = architecture ID 
// * r8     = atags pointer 
// * r9-r14 = corrupted 
// */ 
//               add  r1, r5, r0        @ end of decompressed kernel 
//               adr   r2, reloc_start 
//               ldr   r3, LC1 
//               add  r3, r2, r3 
// 1:            ldmia       r2!, {r9 - r14}              @ copy relocation code 
//               stmia       r1!, {r9 - r14} 
//               ldmia       r2!, {r9 - r14} 
//               stmia       r1!, {r9 - r14} 
//               cmp r2, r3 
//               blo   1b 
// �������ȼ������ѹ���ں˵Ĵ�С��Ȼ������Ľ����ض�λ 
//               bl     cache_clean_flush 
//               add  pc, r5, r0        @ call relocation code 
// �ض�λ������������ѹ���ں˵���ʼ����ʼִ�У������н�ѹ���ں�֮ǰ���ȵ����� 
// cache_clean_flush�����������������Ķ����ڵ�700�� 
// cache_clean_flush: 
//               mov r3, #16 
//               b     call_cache_fn 
// ��ʵ�����ֵ�����call_cache_fn���������ע�⣬����r3��ֵΪ16��call_cache_fn���������ǰ���н��⣬���濴����r3Ϊ16ʱ����õ��ĸ�����,�ص�proc_types�������Ķ��壬�����ҵ���������صĴ��������603�п�ʼ 
//               .word      0x00020000           @ ARMv4T 
//               .word      0x000f0000 
//               b     __armv4_mmu_cache_on 
//               b     __armv4_mmu_cache_off 
//               b     __armv4_mmu_cache_flush 
// ��ƫ����Ϊ16ʱ��������b       __armv4_mmu_cache_flush����ָ�����__armv4_mmu_cache_flush������������Ķ�����730�� 
// __armv4_mmu_cache_flush: 
//               mov r2, #64*1024         @ default: 32K dcache size (*2) 
//               mov r11, #32         @ default: 32 byte line size 
//               mrc p15, 0, r3, c0, c0, 1      @ read cache type 
//               teq   r3, r6                    @ cache ID register present? 
//               beq  no_cache_id 
//               mov r1, r3, lsr #18 
//               and  r1, r1, #7  //���Dsize�е�size 
//               mov r2, #1024 
//               mov r2, r2, lsl r1           @ base dcache size *2//���dcache�ֽڴ�С 
//               tst    r3, #1 << 14          @ test M bit 
//               addne      r2, r2, r2, lsr #1     @ +1/2 size if M == 1 
//               mov r3, r3, lsr #12 
//               and  r3, r3, #3  //��������Dsize�� cache line�ĳ���len 
//               mov r11, #8 
//               mov r11, r11, lsl r3 @ cache line size in bytes //cache line���ֽڳ��� 
// no_cache_id: 
//               bic   r1, pc, #63            @ align to longest cache line 
//               add  r2, r1, r2 
// 1:            ldr   r3, [r1], r11           @ s/w flush D cache �����ָʲô�أ��� 
//               teq   r1, r2 
//               bne  1b 
// �����⼸������ʲô�أ�ΪʲôҪ��ô���أ� 
//               mcr p15, 0, r1, c7, c5, 0      @ flush I cache 
//               mcr p15, 0, r1, c7, c6, 0      @ flush D cache 
//               mcr p15, 0, r1, c7, c10, 4     @ drain WB 
//               mov pc, lr 
// ������Ҫ����ˢ��I/Dcache��д���塣 
// ���濴��ǰ���ᵽ��wont_overwrite���������������282�ж��� 
// wont_overwrite:     mov r0, r4 
//               mov r3, r7 
//               bl     decompress_kernel 
//               b     call_kernel 
// ͬ�������������ú�decompress_kernel�Ĳ�����Ȼ�����decompress_kernel��ѹ�ں�ӳ��Ȼ�����call_kernel�������˺�����491�ж��� 
// call_kernel:     bl     cache_clean_flush 
//               bl     cache_off 
//               mov r0, #0                    @ must be zero 
//               mov r1, r7                    @ restore architecture number 
//               mov r2, r8                    @ restore atags pointer 
//               mov pc, r4                    @ call kernel 
// ����Ҳ���ȵ���cache_clean_flushˢ��i/d-cache��Ȼ�����cashe_off������������úò�����������ѹ����ں�ִ�С� 
// cashe_off������644�ж��� 
// cache_off:      mov r3, #12                  @ cache_off function 
//               b     call_cache_fn 
// ͬ�����ǵ���call_cache_fn������ע�⣬����r3��ֵ��12��Ҳ����ƫ������12������ͨ��call_cache_fn�ҵ�603�е�һ�δ��� 
//               .word      0x00020000           @ ARMv4T 
//               .word      0x000f0000 
//               b     __armv4_mmu_cache_on 
//               b     __armv4_mmu_cache_off 
//               b     __armv4_mmu_cache_flush 
// �������ƫ������12�����Խ�ִ��b       __armv4_mmu_cache_offָ�����__armv4_mmu_cache_off���������������665�ж��塣 
// __armv4_mmu_cache_off: 
//               mrc p15, 0, r0, c1, c0 
//               bic   r0, r0, #0x000d 
//               mcr p15, 0, r0, c1, c0   @ turn MMU and cache off 
//               mov r0, #0 
//               mcr p15, 0, r0, c7, c7   @ invalidate whole cache v4 
//               mcr p15, 0, r0, c8, c7   @ invalidate whole TLB v4 
//               mov pc, lr 
// �������ȶ����ƼĴ�����Ȼ��ر�icache��mmu������ʹȫ��cache��tlb��Ч�� 
// �����ܽ�һ���ڽ����ѹ����ں����ǰ������Щʲô����ѹ���kernel�����arch/arm/kernel/head.S�У��� 
// ���ȱ����uboot�д���Ĳ�����Ȼ���ִ��һ�δ�������صĴ���λ��arch/arm/boot/compressed/head-xxx.S�У���δ�����������û�з���������ֲ�ں�ʱ�����δ����������������Ż��ж�һ��Ҫ��Ҫ�ض�λ�����������ǲ���Ҫ�ض�λ�����Կ�ʼ��bss�����㡣֮���ʼ��ҳ������1:1ӳ�䡣��Ϊ��cacheǰ�����mmu�����������ȶ�ҳ����г�ʼ����Ȼ���mmu��cache����Щ��׼���ú��ж�һ�½�ѹ�ں��Ƿ�Ḳ��δ��ѹ���ں�ӳ������ᣬ�����һЩ������Ȼ��ʼ��ѹ�ںˣ�������ᣬ��ֱ�ӽ�ѹ�������ˢ��cache���ر�mmu��dcache,ʹ cache��tlb������Ч��������ѹ����ں����ִ��arm��ص��ں˴��롣
// 
// 
// ========================================================================================================================
// 
// Linux �ں�����������ת�� Linux �ں��������� 
// 
// 1.       �ں�������ַ
// 1.1.   ���ʽ���
// ZTEXTADDR
// 
// ��ѹ�������еĿ�ʼ��ַ��û�������ַ�������ַ֮�֣���Ϊ��ʱMMU���ڹر�״̬�������ַ��һ��ʱRAM�ĵ�ַ��������֧�ֶ�дѰַ��flash�ȴ洢�н顣
// 
// Start address of decompressor. here's no point in talking about virtual or physical addresses here, since the MMU will be off at the time when you call the decompressor code. You normally call   the kernel at this address to start it booting. This doesn't have to be located in RAM, it can be in flash or other read-only or      read-write addressable medium.
// 
//  
// 
// ZRELADDR
// 
//        �ں�������RAM�еĵ�ַ��ѹ�����ں�ӳ�񱻽�ѹ�������ַ��Ȼ��ִ�С�
// 
// This is the address where the decompressed kernel will be written, and eventually executed. The following constraint must be valid:
// 
//  
// 
//               __virt_to_phys(TEXTADDR) == ZRELADDR
// 
//        The initial part of the kernel is carefully coded to be position independent.
// 
//  
// 
// TEXTADDR
// 
//        �ں������������ַ����ZRELADDR���Ӧ��һ���ں������������ַΪRAM�ĵ�һ��bank��ַ����0x8000��
// 
//        TEXTADDR = PAGE_OFFSET + TEXTOFFST
// 
//  
// 
//        Virtual start address of kernel, normally PAGE_OFFSET + 0x8000.This is where the kernel image ends up.  With the latest kernels, it must be located at 32768 bytes into a 128MB region.  Previous kernels placed a restriction of 256MB here.
// 
//  
// 
// TEXTOFFSET
// 
//        �ں�ƫ�Ƶ�ַ����arch/arm/makefile���趨��
// 
//  
// 
// PHYS_OFFSET
// 
//        RAM��һ��bank��������ʼ��ַ��
// 
// Physical start address of the first bank of RAM.
// 
//  
// 
// PAGE_OFFSET
// 
// RAM��һ��bank��������ʼ��ַ��
// 
//        Virtual start address of the first bank of RAM.  During the kernel
// 
//        boot phase, virtual address PAGE_OFFSET will be mapped to physical
// 
//        address PHYS_OFFSET, along with any other mappings you supply.
// 
//        This should be the same value as TASK_SIZE.
// 
//  
// 
// 1.2.   �ں�������ַȷ��
// �ں�����������ַ��bootp.lds������ Bootp.lds : arch/arm/bootp
// 
// OUTPUT_ARCH(arm)
// 
// ENTRY(_start)
// 
// SECTIONS
// 
// {
// 
//   . = 0;
// 
//   .text : {
// 
//    _stext = .;
// 
//    *(.start)
// 
//    *(.text)
// 
//    initrd_size = initrd_end - initrd_start;
// 
//    _etext = .;
// 
//   }
// 
// }
// 
// ���� .= 0����ȷ����ѹ�������еĿ�ʼ��ַ��0x0��λ�á�ZTEXTADDR��ֵ���������ֵ��ѡȡ��
// 
//  
// 
// Makefile : arch/arm/boot/compressed
// 
//  
// 
// ����趨�ں˴�ROM�������Ļ���������make menuconfig �����ý��������ý�ѹ�������ʼ��ַ�������ѹ�������ʼ��ַΪ0x0��ʵ���ϣ�Ĭ�ϴ�ROM����ʱ����ѹ�������ʼ��ַҲ��0x0��
// 
//  
// 
// feq ($(CONFIG_ZBOOT_ROM),y)
// 
// ZTEXTADDR := $(CONFIG_ZBOOT_ROM_TEXT)
// 
// ZBSSADDR    := $(CONFIG_ZBOOT_ROM_BSS)
// 
// else
// 
// ZTEXTADDR :=0                                                       ZBSSADDR := ALIGN(4)
// 
// endif
// 
//  
// 
// SEDFLAGS    = s/TEXT_START/$(ZTEXTADDR)/;s/BSS_START/$(ZBSSADDR)/                                                                                                                                              
// 
// ����
// 
// $(obj)/vmlinux.lds: $(obj)/vmlinux.lds.in arch/arm/mach-s3c2410/Makefile .config
// 
//        @sed "$(SEDFLAGS)" < $< > $@
// 
//  
// 
// @sed "$(SEDFLAGS)" < $< > $@ ����TEXT_START�趨ΪZTEXTADDR��TEXT_START��arch/arm/boot/compressed /vmlinux.lds.in �б������趨��ѹ�������ʼ��ַ��
// 
// OUTPUT_ARCH(arm)
// 
// ENTRY(_start)
// 
// SECTIONS
// 
// {
// 
//   . = TEXT_START;   
// 
//   _text = .;
// 
//  
// 
//   .text : {
// 
//     _start = .;
// 
//     *(.start)
// 
//     *(.text)
// 
// *(.text.*)
// 
// ����
// 
//   }
// 
// }
// 
//  
// 
// �ں˵ı�������vmlinux.lds��vmlinux.lds��vmlinux.lds.s ���ɡ������������Կ����ں������������ַ������ΪPAGE_OFFSET + TEXT_OFFSET�����ں������������ַZRELADDR��arch/arm/boot/Makefile���趨��
// 
//  
// 
// OUTPUT_ARCH(arm)
// 
// ENTRY(stext)
// 
// SECTIONS
// 
// {
// 
// #ifdef CONFIG_XIP_KERNEL
// 
//        . = XIP_VIRT_ADDR(CONFIG_XIP_PHYS_ADDR);
// 
// #else
// 
//        . = PAGE_OFFSET + TEXT_OFFSET;    
// 
// #endif
// 
//        .init : {                  /* Init code and data             */
// 
//               _stext = .;
// 
//                      _sinittext = .;
// 
//                      *(.init.text)
// 
//                      _einittext = .;
// 
// ����
// 
//        }
// 
// }
// 
//  
// 
//  
// 
// # arch/arm/boot/Makefile
// 
// # Note: the following conditions must always be true:
// 
// #   ZRELADDR == virt_to_phys(PAGE_OFFSET + TEXT_OFFSET)
// 
// #   PARAMS_PHYS must be within 4MB of ZRELADDR
// 
// #   INITRD_PHYS must be in RAM
// 
// ZRELADDR    := $(zreladdr-y)                                       
// 
// #---> zrealaddr-y is specified with 0x30008000 in arch/arm/boot/makefile.boot
// 
// PARAMS_PHYS := $(params_phys-y)
// 
// INITRD_PHYS := $(initrd_phys-y)
// 
//  
// 
// export ZRELADDR INITRD_PHYS PARAMS_PHYS
// 
//  
// 
// ͨ���������������ں�ӳ���ɲ���-a, -e��������ڵ�ַΪZRELADDR����ֵ������ZRELADDR    := $(zreladdr-y)ָ����
// 
//  
// 
// quiet_cmd_uimage= UIMAGE  $@                                                                      
// 
//       cmd_uimage = $(CONFIG_SHELL) $(MKIMAGE) -A arm -O linux -T kernel /
// 
//                  -C none -a $(ZRELADDR) -e $(ZRELADDR) /
// 
//                  -n 'Linux-$(KERNELRELEASE)' -d $< $@
// 
// 1.3.   С��
// �����������֪����linux�ں˱�bootloader������RAM�󣬽�ѹ�����ZTEXTADDR��ʼ���У���δ�������λ���޹ص�PIC�����ں˱���ѹ����ZREALADDR����Ҳ�����ں������������ַ������Ӧ�أ��ں������������ַ���趨ΪTEXTADDR����������������
// 
// TEXTADDR = PAGE_OFFSET + TEXT_OFFSET
// 
// �ں������������ַ�������ַ��������������
// 
// ZRELADDR == virt_to_phys(PAGE_OFFSET + TEXT_OFFSET)= virt_to_phys(TEXTADDR)
// 
//  
// 
// �ٶ�������Ϊsmdk2410�����У�
// 
// �ں������������ַ
// 
// TEXTADDR     = 0xC0008000
// 
// �ں������������ַ   
// 
// ZRELADDR     = 0x30008000
// 
// ���ֱ�Ӵ�flash����������Ҫ����ZTEXTADDR��ַ��
// 
//  
// 
// 2.       �ں��������̷���
// �ں��������̾���������Է�Ϊ�����׶Σ��ں�ӳ�����������linux�ں���ģ��ĳ�ʼ����
// 
// start
//  
// Decompress_kernel()
//  
// Call_kernel
//  
// Stext:
//  
// Prepare_namespace
//  
// Do_basic_setup
//  
// init
//  
// Rest_init
//  
// Setup_arch  ����
//  
// Start_kernel
//  
// _enable_mmu
//  
// Execve(��/sbin/init��))
//  
// �ں���������ͼ
// 
// 2.1.   �ں�ӳ���������
// ��׶ε���Ҫ������ʵ��ѹ���ں˵Ľ�ѹ�ͽ����ں˴������ڡ�
// 
// Bootloader���ϵͳ�������ں�ӳ�񱻵����ڴ�ָ���������ַZTEXTADDR�����͵��ں�ӳ���������������ѹ����VMlinux��ɡ�����������ں�֮ǰ��Ҫ�Ȱ��ں˽�ѹ�����ں�ӳ�����ڵĵ�һ�����������������������arch/arm/boot/compressed /head.S�ļ��С�
// 
// Head.S�ļ���Ҫ������ʵ��ѹ���ں˵Ľ�ѹ����ת���ں�vmlinux�ں˵���ڡ�Decompress_kernel(): arch/arm/boot/compressed/misc.c ��call_kernel����������ʵ�����������ܡ��ڵ���decompress_kernel()��ѹ�ں�֮ǰ����Ҫȷ����ѹ����ں˴��벻�Ḳ�ǵ�ԭ�����ں�ӳ���Լ��趨�ں˴������ڵ�ַZREALADDR��
// 
//               .text
// 
//               adr   r0, LC0
// 
//               ldmia       r0, {r1, r2, r3, r4, r5, r6, ip, sp}
// 
//               .type       LC0, #object
// 
//  
// 
// LC0:              .word      LC0               @ r1
// 
//               .word      __bss_start            @ r2
// 
//               .word      _end                     @ r3
// 
//               .word      zreladdr          @ r4
// 
//               .word      _start                    @ r5
// 
//               .word      _got_start              @ r6
// 
//               .word      _got_end        @ ip
// 
//               .word      user_stack+4096           @ sp
// 
// ������δ���õ��ں˴������ڵ�ַ��������r4�С�
// 
//  
// 
// /*
// 
//  * Check to see if we will overwrite ourselves.
// 
//  *   r4 = final kernel address
// 
//  *   r5 = start of this image
// 
//  *   r2 = end of malloc space (and therefore this image)
// 
//  * We basically want:

 *   r4 >= r2 -> OK

 *   r4 + image length <= r5 -> OK

 */

              cmp r4, r2

              bhs  wont_overwrite

              add  r0, r4, #4096*1024 @ 4MB largest kernel size

              cmp r0, r5

              bls   wont_overwrite

              mov r5, r2                    @ decompress after malloc space

              mov r0, r5

              mov r3, r7

              bl     decompress_kernel

              b     call_kernel

 

��������жϽ�ѹ����ں˴���᲻�Ḳ��ԭ�����ں�ӳ��Ȼ������ں˽�ѹ������decompress_kernel()��

 

ulg

decompress_kernel(ulg output_start, ulg free_mem_ptr_p, ulg free_mem_ptr_end_p,

                int arch_id)

{

       output_data            = (uch *)output_start;    /* ָ���ں�ִ�е�ַ��������r4��*/

       free_mem_ptr        = free_mem_ptr_p;

       free_mem_ptr_end = free_mem_ptr_end_p;

       __machine_arch_type    = arch_id;

 

       arch_decomp_setup();  /*��ѹ��ǰ�ĳ�ʼ�������ã��������ڲ��������õ�*/

 

       makecrc();           /*CRCУ��*/

       putstr("Uncompressing Linux...");

       gunzip();            /*���ý�ѹ������*/

       putstr(" done, booting the kernel./n");

       return output_ptr;

}

 

���ں�ӳ���ѹ��ZERALADDR��ַ�󣬵���call_kernel���������ں˴������ڵ�ַ��

call_kernel:     bl     cache_clean_flush

              bl     cache_off

              mov r0, #0                    @ must be zero

              mov r1, r7                    @ restore architecture number

              mov r2, r8                    @ restore atags pointer

              mov pc, r4                    @ call kernel

����֪��r4�Ĵ����ڱ�������ں˵�ִ�е�ַ��mov pc, r4ʹ�ó���ָ��ָ�����ں˵�ִ�е�ַ���������潫�����ں˴���ִ�н׶Ρ�

2.2.   linux�ں���ģ��ĳ�ʼ��
2.2.1. Ԥ������
�����������ں˴��룬����ִ�е�Ҳ��һ������head.S��arch/arm/kernel/�����ļ���ͬʱhead.SҲ������ͬĿ¼��head-common.S��arch/arm/kernel/�����������ļ�����������Ҫ�������漸�����

         �ж�CPU���ͣ��������е�CPU IDֵ��Linux����֧�ֵ�IDֵ�Ƿ�֧��

         �ж���ϵ���ͣ��鿴R1�Ĵ�����Architecture Typeֵ�Ƿ�֧��

         ����ҳ��

         ����MMU

         ��ת��start_kernel()���ں���ģ���ʼ������

 

ע: ��ʱ���Ը����ӳ���ʵ����ϸ���Եķ�����

2.2.2. �ں˸���ģ���ʼ��
Start_kernel������Linux�ں�ͨ�õĳ�ʼ�����������۶���ʲô��ϵ�ṹ��Linux����Ҫִ�����������Start_kernel()�������ں˳�ʼ���Ļ������̡����水�պ������ں�ģ���ʼ�����Ⱥ�˳����з�����

start_kernel����λ��init/main.c

asmlinkage void __init start_kernel(void)

{

       char * command_line;

       extern struct kernel_param __start___param[], __stop___param[];

 

smp_setup_processor_id();   /*ָ����ǰ��cpu���߼��ţ����������Ӧ�ڶԳƶദ���������ã���ϵͳ��ֻ��һ��cpu��������˺���Ϊ�գ�ʲôҲ����*/

 

lockdep_init();            /* ��ʼ��lockdep hash �� */

 

 

/* ��ʼ��irq */

       local_irq_disable();        

       early_boot_irqs_off();      

       early_init_irq_lock_class();

 

 

/* �����ںˡ�����cpu��״̬Ϊ��present��,��online����״̬����ʼ��ҳ����ӡ�ں˰汾�ŵ���Ϣ��������ϵ�ṹ��Ϊcpu���������ڴ�ռ� ���ڴ��ڼ��ж���Ȼ���ڹر�״̬*/

       lock_kernel();

       boot_cpu_init();

       page_address_init();

       printk(KERN_NOTICE);

       printk(linux_banner);

       setup_arch(&command_line);

       setup_per_cpu_areas();

       smp_prepare_boot_cpu();     /* arch-specific boot-cpu hooks */

 

       /*�ڴ��κ��ж�֮ǰ�򿪵����� */

       sched_init();

 

/*�ر�������ռ���ܣ���Ϊ���ڵĵ��������ܱȽϴ�����ֱ����һ�ε���cpu_idle()*/

       preempt_disable();

 

    /* �����ڴ���������ڵ㣬���ڵ�cpu�ڵ���Ϊ1 */

       build_all_zonelists();

 

/* ��֪ͨ��ÿ��CPU������ÿ��CPU���ڴ�״̬*/

       page_alloc_init();

 

       /* ��������û�������*/

printk(KERN_NOTICE "Kernel command line: %s/n", saved_command_line);

       parse_early_param();

    /* ����������� */

       parse_args("Booting kernel", command_line, __start___param,

                 __stop___param - __start___param,

                 &unknown_bootoption);

 

    /* �����ں˴������쳣�� */

       sort_main_extable();

 

       unwind_init();

 

    /*���������ź��ж��� */

       trap_init();

 

 

       /*��ʼ���ں��еĶ�-����-���£�Read-Copy-Update RCU)��ϵͳ */

       rcu_init();

 

    /*��ʼ��IRQ */

       init_IRQ();

 

       /* ���տ������ϵ������ڴ��ʼ��pid hash�� */

       pidhash_init();

 

    /*��ʼ����ʱ�� */

       init_timers();

 

              /* �߽�����&�߾��ȵļ�ʱ�� (high resolution)��ʼ�� */

       hrtimers_init();

 

       /*��ʼ�����ж� */

       softirq_init();

 

       /* ��ʼ��ʱ����Դ����ͨ��ʱ����ֵ */

       timekeeping_init();

 

       /* ��ʼ��ϵͳʱ��*/

time_init();

 

/*Ϊ�ں˷����ڴ��Դ洢�ռ�������*/

       profile_init();

 

       /* ���ж� */

       if (!irqs_disabled())

              printk("start_kernel(): bug: interrupts were enabled early/n");

       early_boot_irqs_on();

       local_irq_enable();

 

       /*

        * HACK ALERT! This is early. We're enabling the console before

        * we've done PCI setups etc, and console_init() must be aware of

        * this. But we do want output early, in case something goes wrong.

        */

       /* ��ʼ������̨��Ϊ���ܹ�����ذ������ԣ���ʾϵͳ��������Ϣ*/

       console_init();

       if (panic_later)

              panic(panic_later, panic_param);

 

       /*���������CONFIG_LOCKDEP�꣬���ӡ��������Ϣ������ʲôҲ���� */

       lockdep_info();

 

       /*

        * Need to run this when irqs are enabled, because it wants

        * to self-test [hard/soft]-irqs on/off lock inversion bugs

        * too:

        */

/* �������CONFIG_DEBUG_LOCKING_API_SELFTESTS�꣬��locking_selftest()��һ���պ���������ִ�����Բ�*/

       locking_selftest();

 

#ifdef CONFIG_BLK_DEV_INITRD

       if (initrd_start && !initrd_below_start_ok &&

                     initrd_start < min_low_pfn << PAGE_SHIFT) {

              printk(KERN_CRIT "initrd overwritten (0x%08lx < 0x%08lx) - "

                  "disabling it./n",initrd_start,min_low_pfn << PAGE_SHIFT);

              initrd_start = 0;

       }

#endif

 

/* 

(1)dcache_init()����SLAB���棬�û��汣��Ŀ¼�������������汾������dentry_cache�������̷����ļ���Ŀ¼ʱ���漰��Ŀ¼���ж��Ŀ¼������ɣ�Ŀ¼���������������ÿ�������������ġ�Ŀ¼����ṹ���ļ���Ŀ¼������������������������������ͨ����Ŀ¼����Ը�����ҵ������Ӧ��������� 

(2)inode_init()��ʼ����ϣ���������͵ȴ����ж�ͷ���ö�ͷ����ں�Ҫ����Ĺ�ϣ������㡣 

(3)file_init()ȷ����ÿ�������ظ�zhogn���ļ������������ڴ��� 

(4)mnt_init()�����˱���vfsmount��������Ϊmnt_cache�Ļ��棬VFS������Э�����ɸ��������ļ�ϵͳ��������Ҳ���� mount_hashtable���У��ö��д��mnt_cache�����õĿ��ٷ��ʶ���Ȼ������̷�����������ʼ��sysfs�ļ�ϵͳ������root �ļ�ϵͳ��

      */

       vfs_caches_init_early();

 

       cpuset_init_early();

 

/* Mem_init()����Ϊmem_map�е�����������ǲ��Ҵ�ӡ�������ڴ�Ĵ�С�����������ϵͳ�ĸ�������������ڴ��ִ�� */

       mem_init();

 

       /* ��ʼ��cache��ص����������ڳ�ʼ��ҳ���������smp_init()֮ǰִ�� */

kmem_cache_init();

 

/* Ϊ�߼���Ϊ0��cpu��ʼ��ҳ�档�����smp����£�ֻҪcpu����Ϊonline̬���˺����ͻ�ִ�� */

setup_per_cpu_pageset();

 

       /* numa�ڴ��������ʼ�� */

numa_policy_init();

 

       /* �ڴ��ʼ������� */

       if (late_time_init)

              late_time_init();

 

 

/*���㲢��ӡ���������"BogoMips"��ֵ����ֵ������������һ��ʱ�ӽ����ڿ��Է���ִ�ж��ٸ�delay().�Բ�ͬ�ٶȵĴ�������cali_brate_delay()������ӳٴ�Լ��ͬ*/

       calibrate_delay();

 

       /* ��ʼ��pidmap_array,����pid��0����ǰ���� */

       pidmap_init();

 

       /* ��ʼ��ҳ����ٻ��� */

       pgtable_cache_init();

 

       /*��ʼ�����ȼ���index_bits_to_maxindex����*/

       prio_tree_init();

 

       /*����anon_vma�ṹ����slab����*/

       anon_vma_init();

 

#ifdef CONFIG_X86

       if (efi_enabled)

              efi_enter_virtual_mode();

#endif

 

/*���ݿ����ڴ��С�������û�������uid_cache����ʼ������߳���max_threads��Ϊinit_task����RLIMIT_NPROC��ֵΪmax_threads/2 */

       fork_init(num_physpages);

 

/*�������ֿ黺����������VFS, VM��*/

       proc_caches_init();

       buffer_init();

       unnamed_dev_init();

       key_init();

       security_init();

       vfs_caches_init(num_physpages);

       radix_tree_init();

       signals_init();

       /* rootfs populating might need page-writeback */

       page_writeback_init();

#ifdef CONFIG_PROC_FS

       proc_root_init();

#endif

       cpuset_init();

       taskstats_init_early();

       delayacct_init();

 

/*��������ʵ�ǵ���check_writebuffer_bugs()��������Ƿ��������ַ���������� */

       check_bugs();


       /* advanced configuration and power management interface */

       acpi_early_init(); /* before LAPIC and SMP init */

 

       /* Do the rest non-__init'ed, we're now alive */

 

       /* ����init���̣�ɾ���ں���������idle�߳� */

       rest_init();

}  
 / 
// ����init���̺󣬽�ִ��init()����������ɹҽӸ��ļ�ϵͳ����ʼ���豸�����������û��ռ��init���̡���sunny �����о��ⲿ�֣�
// 
// ==============================��һƪ====================================
// ժ Ҫ�� Ƕ��ʽ Linux �Ŀ���ֲ��ʹ�����ǿ����ڸ��ֵ��Ӳ�Ʒ�Ͽ���������Ӱ�����ڲ� 
// ͬ��ϵ�ṹ�Ĵ�������˵Linux����������Ҳ������ͬ��������S3C2410 ARM������Ϊ���� 
// ��ϸ������ϵͳ�ϵ�� bootloader��ִ�����̼� ARM Linux���������̡� 
// �ؼ��ʣ�ARM Linux bootloader �������� 
// ��ͼ����ţ�TP316 
// 1. �� �� 
// Linux ����������ն�������ѧ��ѧ�� Linus Torvalds��1991 �꿪�������ģ�֮���� 
// GNU��֧���£�Linux ����˾޴�ķ�չ����Ȼ Linux ������ PC ���ϵ��ռ��̶�Զ����΢ 
// ��� Windows ����ϵͳ�������ķ�չ�ٶ�֮�졢�û��������������࣬Ҳ��΢���������� 
// �ӵġ�����Щ���� Linux ��Ƕ��ʽ�����Ѹ�ͷ�չ�����Ǹ� Linux ע�����µĻ����� 
// һ��Ƕ��ʽ Linux ϵͳ������Ƕȿ����Է�Ϊ�ĸ�����[1] 
// ���������س���bootloader���� 
// Linux �ںˣ��ļ�ϵͳ��Ӧ�ó��� 
// ���� bootloader��ϵͳ������λ�Ժ�ִ�еĵ�һ�δ��룬����Ҫ������ʼ���������� 
// ���裬Ȼ����� Linux �ںˡ�Linux �ں������ϵͳ�ĳ�ʼ��֮����Ҫ����ĳ���ļ�ϵͳ�� 
// Ϊ���ļ�ϵͳ��Root Filesystem�������ļ�ϵͳ�� Linux ϵͳ�ĺ�����ɲ��֣���������Ϊ 
// Linux ϵͳ���ļ������ݵĴ洢����ͨ����������ϵͳ�����ļ�������Ӧ���������Ҫ�� 
// �⡣Ӧ�ó������˵��Ƕ��ʽϵͳ�ġ���ꡱ������ʵ�ֵĹ���ͨ��������Ƹ�Ƕ��ʽϵͳ 
// ��Ҫ�ﵽ��Ŀ�ꡣ���û��Ӧ�ó����֧�֣��κ�Ӳ������ƾ�����Ƕ��ʽϵͳ��û��ʵ�� 
// ���塣 
// �����Ϸ������ǿ��Կ��� bootloader �� Linux �ں���Ƕ��ʽϵͳ�еĹ�ϵ�����á� 
// Bootloader�����й�������Ȼ���г�ʼ��ϵͳ��ִ���û��������������ã������������ 
// ���ܾ���Ϊ������ Linux �ںˡ���Ƕ��ʽϵͳ�����Ĺ����У��ܴ�һ���־������ǻ��� 
// bootloader �� Linux �ں˵Ŀ�������ֲ�ϡ������������˽� bootloader ִ�����̺� Linux 
// ���������̣�����������ȷ��������������Ĺ������Ӷ�����Ƕ��ʽϵͳ�Ŀ������̡����� 
// ���Ǳ��ĵ���Ҫ�о������ݡ� 
// 2. Bootloader 
// 2.1 Bootloader�ĸ�������� 
// Bootloader��Ƕ��ʽϵͳ���������س�������ϵͳ�ϵ�����еĵ�һ�γ��������� 
// ������ PC ���ϵ� BIOS������ɶ�ϵͳ�ĳ�ʼ������֮�����Ὣ����ʧ�Դ洢����ͨ�� 
// �� Flash�� DOC �ȣ��е�Linux �ں˿����� RAM ��ȥ��Ȼ����ת���ں˵ĵ�һ��ָ��� 
// ��ִ�У��Ӷ����� Linux �ںˡ� 
// �ɴ˿ɼ���bootloader �� Linux �ں������ܲ��ɷֵ���ϵ��Ҫ��������˽� Linux�ں� 
// ���������̣����Ǳ����ȵ���ʶ bootloader��ִ�й��̣��������ܶ�Ƕ��ʽϵͳ����������
// ���������������ա� 
// 2.2 Bootloader��ִ�й��� 
// ��ͬ�Ĵ������ϵ��λ��ִ�еĵ�һ��ָ���ַ������ͬ������ ARM ��������˵�� 
// �õ�ַΪ 0x00000000������һ���Ƕ��ʽϵͳ��ͨ���� Flash �ȷ���ʧ�Դ洢��ӳ�䵽��� 
// ��ַ������ bootloader��λ�ڸô洢������ǰ�ˣ�����ϵͳ�ϵ��λ��ִ�еĵ�һ�γ��� 
// ���� bootloader������Ϊ�洢 bootloader�Ĵ洢����ͬ��bootloader��ִ�й���Ҳ������ͬ�� 
// ���潫��������� 
// Ƕ��ʽϵͳ�й㷺���õķ���ʧ�Դ洢��ͨ���� Flash���� Flash �ַ�Ϊ Nor Flash �� 
// Nand Flash ���֡� ����֮��Ĳ�ͬ���ڣ� Nor Flash ֧��оƬ��ִ�У�XIP�� eXecute In Place���� 
// �������������Flash��ֱ��ִ�ж����ؿ�����RAM��ȥִ�С���Nand Flash����֧��XIP�� 
// ����Ҫ��ִ�� Nand Flash �ϵĴ��룬�����Ƚ��俽���� RAM��ȥ��Ȼ������ RAM ��ȥִ 
// �С� 
// ʵ��Ӧ���е� bootloader�������蹦�ܵĲ�ͬ������Ƶúܸ��ӣ�����ɻ����ĳ�ʼ�� 
// ϵͳ�͵��� Linux �ں˵Ȼ��������⣬������ִ�кܶ��û����������������� Linux �� 
// ���������� Flash �����ȣ�Ҳ������Ƶúܼ򵥣�ֻ���������Ĺ��ܡ���Ϊ���ܴﵽ���� 
// Linux �ں˵�Ŀ�ģ����е� bootloader������߱����¹���[2] 
// �� 
// 1) ��ʼ�� RAM 
// ��Ϊ Linux �ں�һ�㶼���� RAM �����У������ڵ��� Linux �ں�֮ǰ bootloader ���� 
// ���úͳ�ʼ�� RAM��Ϊ���� Linux�ں�����׼������ʼ�� RAM ������������� CPU �Ŀ� 
// �ƼĴ����������Ա�������ʹ�� RAM �Լ����RAM ��С�ȡ� 
// 2) ��ʼ������ 
// ������ Linux ���������������ŷǳ���Ҫ�����ã����� Linux�ں˺��û������ķ�ʽ֮ 
// һ��Linux �����������п��Խ���Ϣͨ������������������������˽� Linux ���������̡� 
// ��Ȼ�������� bootloader ����Ҫ��ɵĹ���������ͨ�����������Ϣ�ǵ��� bootloader �� 
// Linux �ں˵�ǿ�����Ĺ��ߣ�����һ��� bootloader ������ִ�й����г�ʼ��һ��������Ϊ 
// ���Զ˿ڡ� 
// 3) ��⴦�������� 
// Bootloader�ڵ��� Linux�ں�ǰ������ϵͳ�Ĵ��������ͣ������䱣�浽ĳ�������� 
// �ṩ�� Linux �ںˡ�Linux �ں������������л���ݸô��������͵�����Ӧ�ĳ�ʼ������ 
// 4) ���� Linux�������� 
// Bootloader��ִ�й����б������úͳ�ʼ�� Linux ���ں�����������Ŀǰ������������ 
// ��Ҫ�������ַ�ʽ����ͨ�� struct param_struct ��struct tag������б�tagged list�����ֽ� 
// �����ݡ�struct param_struct ��һ�ֱȽ��ϵĲ������ݷ�ʽ���� 2.4 �汾��ǰ���ں���ʹ�ý� 
// �ࡣ�� 2.4 �汾�Ժ� Linux �ں˻����ϲ��ñ���б�ķ�ʽ����Ϊ�˱��ֺ���ǰ�汾�ļ��� 
// �ԣ�����֧�� struct param_struct �������ݷ�ʽ��ֻ�������ں�����������������ת���ɱ� 
// ���б�ʽ�� 
// ����б�ʽ���ֱȽ��µĲ������ݷ�ʽ���������� ATAG_CORE ��ʼ������ 
// ATAG_NONE ��β���м���Ը�����Ҫ���������б�Linux�ں������������л���ݸ��� 
// ������������Ӧ�ĳ�ʼ�������� 
// 5) ���� Linux�ں�ӳ�� 
// Bootloader��ɵ����һ������ǵ��� Linux�ںˡ���� Linux �ں˴���� Flash �У� 
// ���ҿ�ֱ�����������У������ Flash ָ Nor Flash������ô��ֱ����ת���ں���ȥִ�С� 
// �������� Flash ��ִ�д�������������ƣ������ٶ�ҲԶ���� RAM �죬����һ���Ƕ 
// ��ʽϵͳ���ǽ� Linux�ں˿����� RAM �У�Ȼ����ת�� RAM ��ȥִ�С� 
// ������������������� Linux �ں�ִ��֮ǰ CUP�ļĴ���������������������r0��0�� 
// r1�����������ͣ�r2������б��� RAM�еĵ�ַ�� 
// 
// 3. Linux�ں˵��������� 
// 
//   �� bootloader�� Linux �ں�ӳ�񿽱��� RAM �Ժ󣬿���ͨ�������������� Linux �ںˣ� 
// call_linux(0, machine_type, kernel_params_base)�� 
// ���У�machine_tpye �� bootloader�������Ĵ��������ͣ� kernel_params_base �������� 
// ���� RAM �ĵ�ַ��ͨ�����ַ�ʽ�� Linux ������Ҫ�Ĳ����� bootloader���ݵ��ںˡ� 
// Linux �ں�������ӳ��һ���Ƿ�ѹ���ںˣ��� Image����һ��������ѹ���汾���� 
// zImage�������ں�ӳ��Ĳ�ͬ��Linux �ں˵������ڿ�ʼ�׶�Ҳ������ͬ��zImage �� Image 
// ����ѹ���γɵģ��������Ĵ�С�� Image С����Ϊ����ʹ�� zImage�����������Ŀ�ͷ���� 
// ��ѹ���Ĵ��룬�� zImage ��ѹ��֮�����ִ�У��������ִ���ٶȱ� Image Ҫ���������� 
// ��Ƕ��ʽϵͳ�Ĵ洢������һ��Ƚ�С������ zImage ����ռ�ý��ٵĴ洢�ռ䣬������� 
// һ�������ϵĴ���Ҳ��ֵ�õġ�����һ���Ƕ��ʽϵͳ������ѹ���ں˵ķ�ʽ�� 
// ���� ARM ϵ�д�������˵��zImage ����ڳ���Ϊ arch/arm/boot/compressed/head.S�� 
// ������������¹��������� MMU �� Cache������ decompress_kernel()��ѹ�ںˣ����ͨ�� 
// ���� call_kernel()�����ѹ���ں� Image �����������潫��������ڴ�֮�� Linux �ں˵��� 
// �����̡� 
// 3.1 Linux�ں���� 
// Linux ��ѹ���ں˵����λ���ļ�/arch/arm/kernel/head-armv.S �е� stext �Ρ��öεĻ� 
// ��ַ����ѹ���ں˽�ѹ�����ת��ַ�����ϵͳ�м��ص��ں��Ƿ�ѹ���� Image����ô 
// bootloader���ں˴� Flash�п����� RAM ��ֱ�������õ�ַ�����Ӷ����� Linux �ںˡ� 
// ��ͬ��ϵ�ṹ�� Linux ϵͳ������ļ��ǲ�ͬ�ģ�������Ϊ���ļ��������ϵ�ṹ�� 
// �أ�����һ����û�����Ա�д[3] 
// ���Ի��� ARM ����� Linux ϵͳ��˵�����ļ����� 
// head-armv.S���ó���ͨ�����Ҵ������ں����ͺʹ��������͵�����Ӧ�ĳ�ʼ���������ٽ� 
// ��ҳ�������ת�� start_kernel()������ʼ�ں˵ĳ�ʼ�������� 
// ��⴦�����ں��������ڻ���Ӻ���__lookup_processor_type����ɵġ�ͨ�����´��� 
// ��ʵ�ֶ����ĵ��ã� 
// bl __lookup_processor_type�� 
// __lookup_processor_type���ý�������ԭ����ʱ���Ὣ���ؽ�����浽�Ĵ����С����� 
// r8 ������ҳ��ı�־λ��r9 �����˴������� ID �ţ�r10 �������봦������ص� stru 
// proc_info_list �ṹ��ַ�� 
// ��⴦�����������ڻ���Ӻ��� __lookup_architecture_type ����ɵġ��� 
// __lookup_processor_type���ƣ���ͨ�����룺��bl __lookup_processor_type����ʵ�ֶ����ĵ� 
// �á��ú�������ʱ���Ὣ���ؽṹ������ r5��r6 �� r7 �����Ĵ����С����� r5 ������ RAM 
// ����ʼ����ַ��r6 ������ I/O����ַ��r7 ������ I/O��ҳ��ƫ�Ƶ�ַ�� 
// ����⴦�����ں˺ʹ��������ͽ����󣬽�����__create_page_tables �Ӻ���������ҳ 
// ������Ҫ���Ĺ������ǽ� RAM ����ַ��ʼ�� 4M �ռ�������ַӳ�䵽 0xC0000000 �� 
// ʼ�������ַ�����Ա��ߵ� S3C2410 ��������ԣ�RAM ���ӵ������ַ 0x30000000 ���� 
// ������ __create_page_tables ������ 0x30000000 �� 0x30400000 �����ַ��ӳ�䵽 
// 0xC0000000��0xC0400000 �����ַ���� 
// �����еĳ�ʼ������֮��ʹ�����´��������� C �������ں��� start_kernel()������ 
// ʼ֮����ں˳�ʼ�������� 
// b SYMBOL_NAME(start_kernel) 
// 3.2 start_kernel���� 
// start_kernel������ Linux ƽ̨����ϵͳ�ں˳�ʼ�������ں���������Ҫ���ʣ����� 
// Ӳ��ƽ̨��صĳ�ʼ���������ڽ���һϵ�����ں���صĳ�ʼ���󣬵��õ�һ���û����̣� 
// init ���̲��ȴ��û����̵�ִ�У��������� Linux �ں˱�������ϡ��ú��������ľ��幤�� 
// ��[4][5] 
// �� 
// 1) ���� setup_arch()������������ϵ�ṹ��صĵ�һ����ʼ�������� 
// �Բ�ͬ����ϵ�ṹ��˵�ú����в�ͬ�Ķ��塣���� ARM ƽ̨���ԣ��ú��������� 
// arch/arm/kernel/Setup.c��������ͨ���������Ĵ��������ͽ��д������ں˵ĳ�ʼ����Ȼ�� 
// ͨ�� bootmem_init()��������ϵͳ����� meminfo �ṹ�����ڴ�ṹ�ĳ�ʼ���������� 
// paging_init()���� MMU�������ں�ҳ��ӳ�����е������ڴ�� IO�ռ䡣 
// 2) �����쳣������ͳ�ʼ���жϴ������� 
// 3) ��ʼ��ϵͳ���Ľ��̵�������ʱ���жϴ�����ƣ� 
// 4) ��ʼ�����ڿ���̨��serial-console���� 
// ARM-Linux �ڳ�ʼ��������һ�㶼���ʼ��һ��������Ϊ�ں˵Ŀ���̨�������ں��� 
// ���������оͿ���ͨ�����������Ϣ�Ա㿪���߻��û��˽�ϵͳ���������̡� 
// 5) �����ͳ�ʼ��ϵͳ cache��Ϊ�����ڴ���û����ṩ���棬����;��̬�ڴ���䣬������ 
// ��ϵͳ��VirtualFile System����ҳ���档 
// 6) ��ʼ���ڴ��������ڴ��С�����ں�ռ�õ��ڴ������ 
// 7) ��ʼ��ϵͳ�Ľ��̼�ͨ�Ż��ƣ�IPC���� 
// ���������еĳ�ʼ������������start_kernel()��������� rest_init()�������������� 
// ��ʼ������������ϵͳ�ĵ�һ�����̣�init �����������ں˵�������Init �������Ƚ���һϵ 
// �е�Ӳ����ʼ����Ȼ��ͨ�������д��ݹ����Ĳ������ظ��ļ�ϵͳ����� init ���̻�ִ���� 
// �����ݹ����ġ�init������������ִ���û�ָ�����������ִ�����¼�������֮һ�� 
// execve("/sbin/init",argv_init,envp_init); 
// execve("/etc/init",argv_init,envp_init); 
// execve("/bin/init",argv_init,envp_init); 
// execve("/bin/sh",argv_init,envp_init)�� 
// �����еĳ�ʼ������������cpu_idle()�����ᱻ������ʹϵͳ�������ã�idle��״̬�� 
//�ȴ��û������ִ�С����ˣ����� Linux �ں�������ϡ� 
