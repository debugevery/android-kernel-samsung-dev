//zjz(){}
//内核启动调试 (2010-11-12 09:57) 
//分类： linux开发 
//
//
//
//系统搭建过程中，对于系统平台搭建工程师在完成Bootloader 的调试之后就进入Kernel 裁减移植的阶段，
//其中最重要的一步是Kernel启动的调试，在调试Kernel 过程中通常遇到最常见的问题是启动异常:

// Uncompressing Linux............................................................
// 
// ........................... done, booting the kernel.( 挂死在此处)
// 
//  
// 
// 注 意：这里是arch/arm/boot/compressed/head.S的解压过程，调用了decompress_kernel()(同目录下
// 的 misc.c)->include/asm-arm/arch-xxx/uncompress.h的putc()实现。这是在uboot中初始化 的，
// 用的是物理地址，因为此时内核还没有起来。
// 
// 而 printascii则是调用了汇编。printascii()位于arch/arm/kernel/debug.S，他需要调用虚拟地址，
// 此虚拟地址通 过machine_start提供，而相关的宏在include/asm/arch-xxx/debug-macro.S实现，这下明白了。
// 
// 10-05-14添加：debug.s里面需要判断一下当前是否打开了mmu，然后指定uart的基址。
// 在解压阶段的head.s，mmu是1:1映射，目的是加快速度。到了内核的head.s，就是真正的mmu了，此时就是虚拟地址了。
// 
// 
// 
// 
// 
// 导致驱动异常（启动挂死）的原因有很多，如基于EVM 板的 硬件做了修改（如更改了FLASH 空间大小、
// 地址和型号，更改了SDRAM、DDR SDRAM 空间大小、地址和型号，更改了晶振频率等），板卡ID号不支持等。
// 那么如何进行调试那，其实有两种调试技术比较有效。
// 
// Kernel 启动调试技术- 使用printascii() 函数跟踪start_kernel() 有没运行 ，在booting the kernel 之
// 后Kernel 最先执行的是start_kernel() 函数，确认start_kernel() 有否执行就是在其开始代码段添
// 加printascii("start_kernel …") ，如果串口没有打印出start_kernel …，说明start_kernel() 没有运行，
// 那么可能的原因有Bootloader 配置的启动参数错误、 Kernel 加载到(DDR) SDRAM 的地址不正确， 
// Kernel 编译时指定的(DDR) SDRAM 运行地址不正确等。这样就需要一项一项排查错误，当错误被排查完
// 毕，通常打印出 start_kernel …是种必然，如果打印出这仪信息说明 Kernel已 进入到start_kernel() 执
// 行，如果此时有串口启动打印就比较成功了，如果仍然没有打印启动信息，就需要另外一种调试技术。
// 
// 附代码修改：init/main.c <<-

…

extern void printascii(const char*);     // Modify

asmlinkage void __init start_kernel(void)

{

    char * command_line;

    extern struct kernel_param __start___param[], __stop___param[];

    printascii("start_kernel …");        // Modify

    smp_setup_processor_id();

// …
// 
// ->>
// 
// Kernel 启动调试技术- 使用printascii() 函数打印printk() 缓存信息 ，如果Kernel已进入到start_kernel() 执
// 行，仍然没有启动信息打印出来，说明串口波特率出问题的可能性比较大，启动信息是暂时缓存到临
// 时buffer--printk_buf 中的，进入start_kernel() 中会对串口波特率重新初始化，当初始化完成后，
// 缓存的系统启动信息便打印出来，不能打印说明用于串口波特率初始化的系统时钟源没有初始化正确，
// 通常是系统 时钟源和实际的晶振频率不一致导致的，通常排查和解决这个问题后，系统启动信息是能
// 正确打印的。为了帮助解决问题，可以使用 printascii() 打印printk_buf 内容。这样就能
// 把printascii （）打印的系统信息和预想的系统信息进行比较，从而加快解决问题的进度。
// 
// 附代码修改：kernel/printk.c   <<-
// 
…

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

…

static int recursion_bug;

static int new_text_line = 1;

//static char printk_buf[1024];        // Modify

…

// ->>
// 
// 如上是Kernel 裁减移植过程中最重要的两个启动调试技术，灵活使用将带来工作效率的提升，
// 不管硬件平台是那种ARM 或者其它类型的CPU ，也不管是哪个 Kernel 版本（如Linux-2.6.24 、
// Linux-2.6.30 等 都可以采用这两个启动调试技术解决实际问题。为了支持printascii() 函数，
// 需要在 Kernel 裁减中（make menuconfig ）添加Kernel hacking ->[*]Kernel low - level debugging functions 的支持。
// 
// 我的补充:
// 
// 1/ 可以在/kernel/head.s里添加打印看是否跑到mmu开启前:




__turn_mmu_on:

    //打印一个字符a


    mov r9,r0

    mov r0,'a'

    bl printascii //该函数位于arch/arm/kernel/debug.s，调用了 include/mach/debug-macro.S

    mov r0,r9
    //现在开启mmu
    mov    r0, r0
    mcr    p15, 0, r0, c1, c0, 0        @ write control reg
    mrc    p15, 0, r3, c0, c0, 0        @ read id reg
    mov    r3, r3
    mov    r3, r3
    mov    pc, r13    /*实际调用了__switch_data,在head-common.s*/




// 2/ 一般按楼上方法,在startkernel就可以打印出来,如果:在第一步可以打印,而开启mmu后不能打印,
// 那绝对是虚拟地址映射问题,这个问题我搞了2天了....
// 
// 3/ 如果还没有反应，就要检查串口打印那段 debug-macro.S 是否有问题了。
// 
// 
// 总结一下:
// 
// /compressed/head.s和/kernel/head.s基本上不用改,看文件头,2001年写的,就知道了.呵呵.
// 
==========================================================================================


// 2.4内核启动流程及启动过程调试方法作者：城市守望者  来源：博客园  发布时间：2010-08-18 09:51  
// bios将内核拷贝到内存后，将执行权限交给内核。一般嵌入式使用的zImage格式。此种格式的首地址是
// 一个未压缩的可执行代码入口，这段未压缩的代码主要功能一是解压缩，二是保护好bios传入的参数转给
// 内核。那么这个过程的相关代码及文件如下（2410为例）：
// 
// arch/arm/boot/compressed/head.s 
// 
// ---调用C函数-->
// 
// arch/arm/boot/compressed/misc.c的decompress_kernel()
// 函数解压内核。
// 
// ---跳转到解压后内核的可执行代码-->arch/arm/kernel/head-armv.s 初始化
// 
// ---跳转到内核的C代码段-->init/main.c的asmlinkage void __init start_kernel(void)
// 
//  
// 
// 调试方法：在内核的console_init();函数被调用之前printk函数在内核中无效或者说打印不出来，
// 使用的串口配置为bios所设置。console_init();函数在init/main.c文件的start_kernel(void)函数
// 中被调用，特别的是在调用这个函数之前内核使用了printk，但是没有实际的打印输出，但在初始
// 化console后前面的printk内容都将会打印出来。
// 
// 1.head.s ：可在misc.c文件中用C函数写调试信息输出，在head.s用汇编bl调用
// 
// 2.head-armv.s ：需要两个操作
// 
// a.配置内核打开err输出功能
// 
// Kernel hacking  --->  
// 
//   [*] Kernel debugging 
// 
//   [*]   Verbose kernel error messages 
// 
//   [*]   Kernel low-level debugging functions 
// 
// b.调用文件中现有的汇编__err输入功能
// 
//  
// 
// 参考网友资料：
// 
// linux2.4启动分析(1)---内核启动地址的确定 vmlinux LOAD_ADDR ZRELADDR
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
// 内核编译链接过程是依靠vmlinux.lds文件，以arm为例vmlinux.lds文件位于kernel/arch/arm/vmlinux.lds，
// 但是该文件是由vmlinux-armv.lds.in生成的，根据编译选项的不同源文件还可以是vmlinux-armo.lds.in，
// vmlinux-armv-xip.lds.in。 
// 
// vmlinux-armv.lds的生成过程在kernel/arch/arm/Makefile中 
// 
// (在2.6中没有找到这个,在/arch/arm/boot/Makefile) 
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
// vmlinux-armv.lds.in文件的内容： 
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
// 其中TEXTADDR就是内核启动的虚拟地址，定义在kernel/arch/arm/Makefile中：
// ifeq ($(CONFIG_CPU_32),y)
// PROCESSOR    = armv
// TEXTADDR     = 0xC0008000
// LDSCRIPT     = arch/arm/vmlinux-armv.lds.in
// endif
// 需要注意的是这里是虚拟地址而不是物理地址。 
// 
// 一般情况下都在生成vmlinux后，再对内核进行压缩成为zImage，压缩的目录是kernel/arch/arm/boot。
// 下载到flash中的是压缩后的zImage文件，zImage是由压缩后的vmlinux和解压缩程序组成，如下图所示： 
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
// zImage链接脚本也叫做vmlinux.lds，位于kernel/arch/arm/boot/compressed。
// 是由同一目录下的vmlinux.lds.in文件生成的，内容如下：
// OUTPUT_ARCH(arm)
// ENTRY(_start)
// SECTIONS
// {
//    . = LOAD_ADDR;   //这个在2.6中已经去掉了 
//    _load_addr = .;    //也去掉
//    . = TEXT_START;
//    _text = .;
//    .text : {
//      _start = .;
// 其中LOAD_ADDR就是zImage中解压缩代码的ram偏移地址，TEXT_START是内核ram启动的偏移地址，这个地址是物理地址。
// 在kernel/arch/arm/boot/Makefile文件中定义了：
// ZTEXTADDR   =0
// ZRELADDR     = 0xa0008000  //这个在2.6中是makefile.boot定义 
// 
// ZTEXTADDR就是解压缩代码的ram偏移地址，ZRELADDR是内核ram启动的偏移地址，这里看到指定ZTEXTADDR的地址为0，
// 明显是不正确的，因为我的平台上的ram起始地址是0xa0000000，在Makefile文件中看到了对该地址设置的几行注释：
// # We now have a PIC decompressor implementation.  Decompressors running
// # from RAM should not define ZTEXTADDR.  Decompressors running directly
// # from ROM or Flash must define ZTEXTADDR (preferably via the config)
// 他的意识是如果是在ram中进行解压缩时，不用指定它在ram中的运行地址，如果是在flash中就必须指定他的地址。所以
// 这里将ZTEXTADDR指定为0，也就是没有真正指定地址。 
// 
// 在kernel/arch/arm/boot/compressed/Makefile文件有一行脚本： 
// 
// SEDFLAGS    = s/TEXT_START/$(ZTEXTADDR)/;s/LOAD_ADDR/$(ZRELADDR)/;s/BSS_START/$(ZBSSADDR)/ 
// 
// //2.6改为s/TEXT_START/$(ZTEXTADDR)/;s/BSS_START/$(ZBSSADDR)/ 
// 
// 使得TEXT_START = ZTEXTADDR，LOAD_ADDR = ZRELADDR。 
// 
// 这样vmlinux.lds的生成过程如下：
// vmlinux.lds:    vmlinux.lds.in Makefile $(TOPDIR)/arch/$(ARCH)/boot/Makefile $(TOPDIR)/.config
// @sed "$(SEDFLAGS)" < vmlinux.lds.in > $@
// 以上就是我对内核启动地址的分析，总结一下内核启动地址的设置：
// 1、设置kernel/arch/arm/Makefile文件中的
//    TEXTADDR     = 0xC0008000 //2.6暂时没找到 
//    内核启动的虚拟地址
// 2、设置kernel/arch/arm/boot/Makefile文件中的
//    ZRELADDR     = 0xa0008000
//    内核启动的物理地址
//    如果需要从flash中启动还需要设置
//    ZTEXTADDR地址。 
// 
//   
// 
// linux2.4启动分析(2)---内核解压缩过程 compress booting kernel 
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
// 内核压缩和解压缩代码都在目录kernel/arch/arm/boot/compressed，
// 编译完成后将产生vmlinux、head.o、misc.o、head-xscale.o、piggy.o这几个文件，
// head.o是内核的头部文件，负责初始设置；
// misc.o将主要负责内核的解压工作，它在head.o之后；
// head-xscale.o文件主要针对Xscale的初始化，将在链接时与head.o合并；
// piggy.o是一个中间文件，其实是一个压缩的内核(kernel/vmlinux)，只不过没有和初始化文件及解压文件链接而已；
// vmlinux是(没有－－lw：zImage是压缩过的内核)压缩过的内核，就是由piggy.o、head.o、misc.o、head-xscale.o组成的。 
// 
// ( 
// 
// 2.6中，在compressed/makefile里，定义了 
// 
// #生成vmlinux镜像
// targets       := vmlinux vmlinux.lds piggy.gz piggy.o font.o font.c \
//          head.o misc.o $(OBJS) 
// 
// ) 
// 
// 在BootLoader完成系统的引导以后并将Linux 内核调入内存之后，调用bootLinux()，
// 这个函数将跳转到kernel的起始位置。如果kernel没有压缩，就可以启动了。
// 如果kernel压缩过，则要进行解压，在压缩过的kernel头部有解压程序。
// 压缩过得kernel入口第一个文件源码位置在arch/arm/boot/compressed/head.S。
// 它将调用函数decompress_kernel()，这个函数在文件arch/arm/boot/compressed/misc.c中，
// decompress_kernel()又调用proc_decomp_setup(),arch_decomp_setup()进行设置，
// 然后使用在打印出信息“Uncompressing Linux...”后，调用gunzip()。将内核放于指定的位置。 
// 
// 以下分析head.S文件：
// (1)对于各种Arm CPU的DEBUG输出设定，通过定义宏来统一操作。
// (2)设置kernel开始和结束地址，保存architecture ID。
// (3)如果在ARM2以上的CPU中，用的是普通用户模式，则升到超级用户模式，然后关中断。
// (4)分析LC0结构delta offset，判断是否需要重载内核地址(r0存入偏移量，判断r0是否为零)。
//    这里是否需要重载内核地址，我以为主要分析arch/arm/boot/Makefile、arch/arm/boot/compressed/Makefile
//    和arch/arm/boot/compressed/vmlinux.lds.in三个文件，主要看vmlinux.lds.in链接文件的主要段的位置，
//    LOAD_ADDR(_load_addr)＝0xA0008000，而对于TEXT_START(_text、_start)的位置只设为0，BSS_START(__bss_start)＝ALIGN(4)。
//    对于这样的结果依赖于，对内核解压的运行方式，也就是说，内核解压前是在内存(RAM)中还是在FLASH上，
//    因为这里，我们的BOOTLOADER将压缩内核(zImage)移到了RAM的0xA0008000位置，我们的压缩内核是在内存(RAM)从0xA0008000地址开始 顺序排列，
//    因此我们的r0获得的偏移量是载入地址(0xA0008000)。接下来的工作是要把内核镜像的相对地址转化为内存的物理地址，即重载内核地址。
// (5)需要重载内核地址，将r0的偏移量加到BSS region和GOT table中。
// (6)清空bss堆栈空间r2－r3。
// (7)建立C程序运行需要的缓存，并赋于64K的栈空间。
// (8)这时r2是缓存的结束地址，r4是kernel的最后执行地址，r5是kernel境象文件的开始地址。检查是否地址有冲突。
//    将r5等于r2，使decompress后的kernel地址就在64K的栈之后。
// (9)调用文件misc.c的函数decompress_kernel()，解压内核于缓存结束的地方(r2地址之后)。此时各寄存器值有如下变化：
//    r0为解压后kernel的大小
//    r4为kernel执行时的地址
//    r5为解压后kernel的起始地址
//    r6为CPU类型值(processor ID)
//    r7为系统类型值(architecture ID)
// (10)将reloc_start代码拷贝之kernel之后(r5+r0之后)，首先清除缓存，而后执行reloc_start。
// (11)reloc_start将r5开始的kernel重载于r4地址处。
// (12)清除cache内容，关闭cache，将r7中architecture ID赋于r1，执行r4开始的kernel代码。 
// 
// 下面简单介绍一下解压缩过程，也就是函数decompress_kernel实现的功能：
// 解压缩代码位于kernel/lib/inflate.c，inflate.c是从gzip源程序中分离出来的。包含了一些对全局数据的直接引用。
// 在使用时需要直接嵌入到代码中。gzip压缩文件时总是在前32K字节的范围内寻找重复的字符串进行编码， 
// 在解压时需要一个至少为32K字节的解压缓冲区，它定义为window[WSIZE]。inflate.c使用get_byte()读取输入文件，
// 它被定义成宏来提高效率。输入缓冲区指针必须定义为inptr，inflate.c中对之有减量操作。inflate.c调用flush_window()
// 来输出window缓冲区中的解压出的字节串，每次输出长度用outcnt变量表示。在flush_window()中，还必 
// 须对输出字节串计算CRC并且刷新crc变量。在调用gunzip()开始解压之前，调用makecrc()初始化CRC计算表。
// 最后gunzip()返回0表示解压成功。 
// 
// 我们在内核启动的开始都会看到这样的输出：
// Uncompressing Linux...done, booting the kernel.
// 这也是由decompress_kernel函数内部输出的，它调用了puts()输出字符串，
// puts是在kernel/include/asm-arm/arch-pxa/uncompress.h中实现的。 
// 
// 执行完解压过程，再返回到head.S中，启动内核： 
// 
// call_kernel:    bl  cache_clean_flush
//          bl  cache_off
//          mov r0, #0
//          mov r1, r7          @ restore architecture number
//          mov pc, r4          @ call kernel
// 下面就开始真正的内核了。 
// 
// 本文来自CSDN博客，转载请标明出处：http://blog.csdn.net/lanmanck/archive/2009/06/18/4278724.aspx 
// 
//   
// 
// linux2.4启动分析(2)---内核解压缩过程(续,更详细) compress booting kernel 
// 
// 自:http://blog.csdn.net/BoySKung/archive/2008/12/05/3448083.aspx# 
// 
// 文件:linux-2.6.20.6/arch/arm/boot/compressed/head.S 
// 开头有一段宏定义，我们只看其中一段，分析一下gnu arm汇编的宏定义 
// #elif defined(CONFIG_ARCH_S3C2410) 
//               .macro loadsp, rb 
//               mov \rb, #0x50000000 
//               add  \rb, \rb, #0x4000 * CONFIG_S3C2410_LOWLEVEL_UART_PORT 
//               .endm 
// #else 
// 这里定义了一个宏，宏名是loadsp，rb是这个宏的参数。宏的参数在被引用时必须加”\”,如： 
// mov \rb, #0x50000000. 
// 宏定义结束之后定义了一个段， 
//               .section ".start", #alloc, #execinstr 
// 这个段的段名是 .start，#alloc表示Section contains allocated data, #execinstr表示Section contains executable instructions. 
// /* 
// * sort out different calling conventions 
// */ 
//               .align 
// start: 
//               .type       start,#function /*.type指定start这个符号是函数类型*/ 
//               .rept 8 
//               mov r0, r0 //将此命令重复8次，相当于nop，这里为什么这样做还不清楚？？ 
//               .endr 
//               b     1f 
//               .word      0x016f2818           @ Magic numbers to help the loader 
//               .word      start               @ absolute load/run zImage address 
//               .word      _edata                   @ zImage end address 
// 1:            mov r7, r1                    @ save architecture ID 
//               mov r8, r2                    @ save atags pointer 
// r1和r2中分别存放着由bootloader传递过来的architecture ID和指向标记列表的指针。这里将这两个参数先保存。 
// #ifndef __ARM_ARCH_2__ 
//               /* 
//                * Booting from Angel - need to enter SVC mode and disable 
//                * FIQs/IRQs (numeric definitions from angel arm.h source). 
//                * We only do this if we were in user mode on entry. 
//                */ 
// 读取cpsr并判断是否处理器处于supervisor模式——从u-boot进入kernel，系统已经处于SVC32模式；而利用angel进入则处于user模式，还需要额外两条指令。之后是再次确认中断关闭，并完成cpsr写入 
// Angel 是 ARM 的调试协议,现在用的 MULTI-ICE 用的是 RDI 通讯协议, ANGLE 需要在板子上有 驻留程序,然后通过 串口就可以调试了 
// 这里介绍一下半主机. 
// 半主机是用于 ARM 目标的一种机制，可将来自应用程序代码的输入/输出请求 
// 传送至运行调试器的主机。 例如，使用此机制可以启用 C 库中的函数，如 
// printf() 和 scanf()，来使用主机的屏幕和键盘，而不是在目标系统上配备屏幕和 
// 键盘。 
// 半主机是通过一组定义好的软件指令（如 swi）来实现的，这些指令通过程序控 
// 制生成异常。 应用程序调用相应的半主机调用，然后调试代理处理该异常。 调 
// 试代理提供与主机之间的必需通信。 
//               mrs  r2, cpsr          @ get current mode 
//               tst    r2, #3                    @ not user? 
//               bne  not_angel 
// 下面两行实现了在主机和 ARM 目标之间启用调试 I/O 功能， 
//               mov r0, #0x17              @ angel_SWIreason_EnterSVC 
//               swi  0x123456              @ angel_SWI_ARM 
// 0x17是angel_SWIreason_EnterSVC半主机操作，将处理器设置为超级用户模式，通过设置新 CPSR 中的两个中断掩码位来禁用所有中断。0x123456是arm指令集的半主机操作编号 
// not_angel:  //不是通过angel调试进入内核 
//               mrs  r2, cpsr          @ turn off interrupts to 
//               orr   r2, r2, #0xc0         @ prevent angel from running 
//               msr  cpsr_c, r2   //这里将cpsr中I、F位分别置“1”，关闭IRQ和FIQ 
// #else 
//               teqp pc, #0x0c000003          @ turn off interrupts 
// 常用 TEQP PC,#(新模式编号) 来改变模式 
// #endif 
// 链接器会把一些处理器相关的代码链接到这个位置，也就是arch/arm/boot/compressed/head-xxx.S文件中的代码。在那个文件里会对I/D cache以及MMU进行一些操作 
// /* 
//                * Note that some cache flushing and other stuff may 
//                * be needed here - is there an Angel SWI call for this? 
//                */ 
//               /* 
//                * some architecture specific code can be inserted 
//                * by the linker here, but it should preserve r7, r8, and r9. 
//                */ 
//               .text 
//               adr   r0, LC0 //当前运行时LC0符号所在地址位置 
//               ldmia       r0, {r1, r2, r3, r4, r5, r6, ip, sp} 
//               subs r0, r0, r1        @ calculate the delta offset //这里获得当前运行地址与链接地址 
//                                           @ if delta is zero, we are   //的偏移量，存入r0中。 
//               beq  not_relocated         @ running at the address we 
//                                           @ were linked at. 
// 上面这几行代码用于判断代码是否已经重定位到内存中，LC0这个符号在288行定义。 
//               .type       LC0, #object 
// LC0:              .word      LC0               @ r1 //这个要加载到r1中的LC0是链接时LC0的地址 
//               .word      __bss_start            @ r2 
//               .word      _end                     @ r3 
//               .word      zreladdr          @ r4 
//               .word      _start                    @ r5 
//               .word      _got_start              @ r6 
//               .word      _got_end        @ ip 
//               .word      user_stack+4096           @ sp 
// 通过当前运行时LC0的地址与链接器所链接的地址进行比较判断。若相等则是运行在链接的地址上。 
// 如果不是运行在链接的地址上，则下面的代码必须运行 
//               /* 
//                * We're running at a different address.  We need to fix 
//                * up various pointers: 
//                *   r5 - zImage base address 
//                *   r6 - GOT start 
//                *   ip - GOT end 
//                */ 
//               add  r5, r5, r0 //修改内核映像基地址 
//               add  r6, r6, r0 
//               add  ip, ip, r0 //修改got表的起始和结束位置 
// #ifndef CONFIG_ZBOOT_ROM 
//               /*若没有定义CONFIG_ZBOOT_ROM，此时运行的是完全位置无关代码 
// 位置无关代码，也就是不能有绝对地址寻址。所以为了保持相对地址正确， 
// 需要将bss段以及堆栈的地址都进行调整 
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
// #else //若定义了CONFIG_ZBOOT_ROM，只对got表中在bss段以外的符号进行重定位 
// //为什么要这样做呢？？我也不清楚 
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
// 如果运行当前运行地址和链接地址相等，则不需进行重定位。直接清除bss段 
// not_relocated: mov r0, #0 
// 1:            str   r0, [r2], #4            @ clear bss 
//               str   r0, [r2], #4 
//               str   r0, [r2], #4 
//               str   r0, [r2], #4 
//               cmp r2, r3 
//               blo   1b 
// 之后跳转到cache_on处 
//               /* 
//                * The C runtime environment should now be setup 
//                * sufficiently.  Turn the cache on, set up some 
//                * pointers, and start decompressing. 
//                */ 
//               bl     cache_on 
// cache_on在327行定义 
//               .align       5 
// cache_on:       mov r3, #8                    @ cache_on function 
//               b     call_cache_fn 
// 把r3的值设为8有什么用呢？下面会看到。这里又跳转到call_cache_fn。这个函数的定义在512行 
// call_cache_fn: adr   r12, proc_types  //把proc_types的地址加载到r12中 
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
// 这一段代码首先获得当前处理器id，然后查proc_types表，也就是处理器类型表与获得的处理器id进行比较，当找到相应的处理器后，就加载对应的cache处理函数。 
// addeq      pc, r12, r3             @ call cache function 
// 这里用到了上面说的r3，他的值是8，也就是一个偏移量，r12中存储的是某个处理器相关处理模块的基地址。 
// proc_type的定义如下，在541行 
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
//               .word      0x00020000    @ ARMv4T //这个就是我们要找的arm920t的处理器相关数 
//               .word      0x000f0000        //据，偏移8后刚好是b   __armv4_mmu_cache_on 
//               b     __armv4_mmu_cache_on  //指令的地址 
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
// 当找到我和我们处理器后，就调用相应的处理函数，我根据我们的arm920t处理器，这里应该调用__armv4_mmu_cache_on,这句调用指令在605行 
//               .word      0x00020000           @ ARMv4T 
//               .word      0x000f0000 
//               b     __armv4_mmu_cache_on 
//               b     __armv4_mmu_cache_off 
//               b     __armv4_mmu_cache_flush 
// __armv4_mmu_cache_on的在424行定义， 
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
//               mov pc, r12  //返回到cache_on 
// 这里首跳转到__setup_mmu，然后清空write buffer、I/Dcache、TLB.接着打开i-cache，设置为Round-robin replacement。调用__common_mmu_cache_on,打开mmu和d-cache.把页表基地址和域访问控制写入协处理器寄存器 c2、c3. __common_mmu_cache_on函数数定义在450行。 
// __common_mmu_cache_on: 
// #ifndef DEBUG 
//               orr   r0, r0, #0x000d             @ Write buffer, mmu 
// #endif 
//               mov r1, #-1 //-1的补码是ffff ffff, 
//               mcr p15, 0, r3, c2, c0, 0      @ load page table pointer 
//               mcr p15, 0, r1, c3, c0, 0      @ load domain access control //将domain access control寄存 
//               b     1f                                 //全部置’1’ 
//               .align       5                   @ cache line aligned 
// 1:            mcr p15, 0, r0, c1, c0, 0      @ load control register 
//               mrc p15, 0, r0, c1, c0, 0      @ and read it back to 
//               sub  pc, lr, r0, lsr #32    @ properly flush pipeline 
// 重占来看一下__setup_mmu这个函数，定义在386行 
// __setup_mmu:       sub  r3, r4, #16384        @ Page directory size 
//               bic   r3, r3, #0xff          @ Align the pointer 
//               bic   r3, r3, #0x3f00 
// 这里r4中存放着内核执行地址，将16K的一级页表放在这个内核执行地址下面的16K空间里，上面通过 sub  r3, r4, #16384  获得16K空间后，又将页表的起始地址进行16K对齐放在r3中。即ttb的低14位清零。 
// /* 
// * Initialise the page tables, turning on the cacheable and bufferable 
// * bits for the RAM area only. 
// */ 
// //初始化页表，并在RAM空间里打开cacheable 和bufferable位 
//               mov r0, r3 
//               mov r9, r0, lsr #18 
//               mov r9, r9, lsl #18         @ start of RAM 
//               add  r10, r9, #0x10000000    @ a reasonable RAM size 
// 上面这几行把一级页表的起始地址保存在r0中，并通过r0获得一个ram起始地址（256K对齐），并从这个起始地址开始的256M ram空间对应的描述符的C和B位均置”1” (参考arm920t datasheet 3.3.3, table 3-2 level one descryiptor bits), r9和r10中存放了这段内存的起始地址和结束地址 
//               mov r1, #0x12 //一级描述符的bit[1:0]为10，表示这是一个section描述符。bit[4] 
// //为1（参考arm9205 datasheet 3.3.3 table 3-2 level one 
// //descryiptor bits）此时bit[8:5]均为0，选择了D0域。 
//               orr   r1, r1, #3 << 10 //一级描述符的access permission bits bit[11:10]为11. 即 
//                          //all access types permitted in both modes 
// // (参考arm920t datasheet 3.3.3, table 3-2 level 
// //one descryiptor bits, 3.6, table 3-11 interpreting access 
// // permission(AP) bit) 
//               add  r2, r3, #16384  //一级描述符表的结束地址存放在r2中。 
// 1:            cmp r1, r9                    @ if virt > start of RAM 
//               orrhs       r1, r1, #0x0c         @ set cacheable, bufferable 
//               cmp r1, r10                  @ if virt > end of RAM 
//               bichs       r1, r1, #0x0c         @ clear cacheable, bufferable 
//               str   r1, [r0], #4            @ 1:1 mapping 
//               add  r1, r1, #1048576 
//               teq   r0, r2 
//               bne  1b 
// 上面这段就是对一级描述符表（页表）的初始化，首先比较这个描述符所描述的地址是否在那个256M的空间中，如果在则这个描述符对应的内存区域是 cacheable ,bufferable。如果不在则noncacheable, nonbufferable.然后将描述符写入一个一级描述符表的入口，并将一级描述符表入口地址加4，而指向下一个1M section的基地址。如果页表入口未初始化完，则继续初始化。 
// 一级描述符表的高12位是每个setcion的基地址，可以描述4096个section。一级页表大小为16K，每个页表项，即描述符占4字节，刚好可以容纳4096个描述符，所以这里就映射了4096*1M = 4G的空间。 
// /* 
// * If ever we are running from Flash, then we surely want the cache 
// * to be enabled also for our execution instance...  We map 2MB of it 
// * so there is no map overlap problem for up to 1 MB compressed kernel. 
// * If the execution is in RAM then we would only be duplicating the above. 
// */ 
//               mov r1, #0x1e 
//               orr   r1, r1, #3 << 10 //这两行将描述的bit[11:10] bit[4:1]置位，(参考arm920t 
// // datasheet 3.3.3, table 3-2 level one descryiptor bits) 
//               mov r2, pc, lsr #20 
//               orr   r1, r1, r2, lsl #20  //将当前地址进1M对齐，并与r1中的内容结合形成一个 
//                             //描述当前指令所在section的描述符。 
//               add  r0, r3, r2, lsl #2   //r3为刚才建立的一级描述符表的起始地址。通过将当前地 
// //址(pc)的高12位左移两位(形成14位索引)与r3中的地址 
//                             // (低14位为0)相加形成一个4字节对齐的地址，这个 
//                             //地址也在16K的一级描述符表内。当前地址对应的 
//                             //描述符在一级页表中的位置 
//               str   r1, [r0], #4 
//               add  r1, r1, #1048576 
//               str   r1, [r0]          //这里将上面形成的描述符及其连续的下一个section描述 
// //写入上面4字节对齐地址处（一级页表中索引为r2左移 
// //2位） 
//               mov pc, lr       //返回，调用此函数时，调用指令的下一语句mov   r0, #0的地 
//                        //址保存在lr中 
// 这里进行的是1:1的映射，物理地址和虚拟地址是一样。 
// __common_mmu_cache_on:执行完后返回到bl cache_on下一条指令处226行， 
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
// 这段代码首先在堆栈上确定了64K的malloc空间，空间的起始地址和结束地址分别存放在r1、r2中。然后判断最终内核地址，也就是解压后内核的起始地址，是否大于malloc空间的结束地址，如果大于就跳到wont_overwrite执行，wont_overwrite函数后面会讲到。否则，检查最终内核地址加解压后内核大小，也就是解压后内核的结束地址，是否小于现在未解压内核映像的起始地址。小于也会跳到wont_owerwrite执行。如两这两个条件都不满足，则继续往下执行。 
//               mov r5, r2                    @ decompress after malloc space 
//               mov r0, r5 
//               mov r3, r7 
//               bl     decompress_kernel 
// 这里将解压后内核的起始地址设为malloc空间的结束地址。然后后把处理器id（开始时保存在r7中）保存到r3中，调用 decompress_kernel开始解压内核。这个函数的四个参数分别存放在r0-r3中，它在arch/arm/boot/compressed /misc.c中定义。 
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
// 这里首先计算出解压后内核的大小，然后对它的进行重定位 
//               bl     cache_clean_flush 
//               add  pc, r5, r0        @ call relocation code 
// 重定位结束后跳到解压后内核的起始处开始执行，在运行解压后内核之前，先调用了 
// cache_clean_flush这个函数。这个函数的定义在第700行 
// cache_clean_flush: 
//               mov r3, #16 
//               b     call_cache_fn 
// 其实这里又调用了call_cache_fn这个函数，注意，这里r3的值为16，call_cache_fn这个函数在前面有讲解，下面看看当r3为16时会调用到哪个函数,回到proc_types这个对像的定义，最终找到处理器相关的处理代码在603行开始 
//               .word      0x00020000           @ ARMv4T 
//               .word      0x000f0000 
//               b     __armv4_mmu_cache_on 
//               b     __armv4_mmu_cache_off 
//               b     __armv4_mmu_cache_flush 
// 当偏移量为16时，会跳到b       __armv4_mmu_cache_flush这条指令，调用__armv4_mmu_cache_flush这个函数，它的定义在730行 
// __armv4_mmu_cache_flush: 
//               mov r2, #64*1024         @ default: 32K dcache size (*2) 
//               mov r11, #32         @ default: 32 byte line size 
//               mrc p15, 0, r3, c0, c0, 1      @ read cache type 
//               teq   r3, r6                    @ cache ID register present? 
//               beq  no_cache_id 
//               mov r1, r3, lsr #18 
//               and  r1, r1, #7  //获得Dsize中的size 
//               mov r2, #1024 
//               mov r2, r2, lsl r1           @ base dcache size *2//获得dcache字节大小 
//               tst    r3, #1 << 14          @ test M bit 
//               addne      r2, r2, r2, lsr #1     @ +1/2 size if M == 1 
//               mov r3, r3, lsr #12 
//               and  r3, r3, #3  //上两句获得Dsize中 cache line的长度len 
//               mov r11, #8 
//               mov r11, r11, lsl r3 @ cache line size in bytes //cache line的字节长度 
// no_cache_id: 
//               bic   r1, pc, #63            @ align to longest cache line 
//               add  r2, r1, r2 
// 1:            ldr   r3, [r1], r11           @ s/w flush D cache 这个是指什么呢？？ 
//               teq   r1, r2 
//               bne  1b 
// 上面这几句做了什么呢？为什么要这么做呢？ 
//               mcr p15, 0, r1, c7, c5, 0      @ flush I cache 
//               mcr p15, 0, r1, c7, c6, 0      @ flush D cache 
//               mcr p15, 0, r1, c7, c10, 4     @ drain WB 
//               mov pc, lr 
// 这里主要还是刷新I/Dcache和写缓冲。 
// 下面看看前面提到的wont_overwrite函数。这个函数在282行定义 
// wont_overwrite:     mov r0, r4 
//               mov r3, r7 
//               bl     decompress_kernel 
//               b     call_kernel 
// 同样，这里先设置好decompress_kernel的参数，然后调用decompress_kernel解压内核映像。然后调用call_kernel函数。此函数在491行定义 
// call_kernel:     bl     cache_clean_flush 
//               bl     cache_off 
//               mov r0, #0                    @ must be zero 
//               mov r1, r7                    @ restore architecture number 
//               mov r2, r8                    @ restore atags pointer 
//               mov pc, r4                    @ call kernel 
// 这里也是先调用cache_clean_flush刷新i/d-cache，然后调用cashe_off函数。最后设置好参数，跳到解压后的内核执行。 
// cashe_off函数在644行定义 
// cache_off:      mov r3, #12                  @ cache_off function 
//               b     call_cache_fn 
// 同样又是调用call_cache_fn函数，注意，这里r3的值是12，也就是偏移量是12，最终通过call_cache_fn找到603行的一段代码 
//               .word      0x00020000           @ ARMv4T 
//               .word      0x000f0000 
//               b     __armv4_mmu_cache_on 
//               b     __armv4_mmu_cache_off 
//               b     __armv4_mmu_cache_flush 
// 因这里的偏移量是12，所以将执行b       __armv4_mmu_cache_off指令，调用__armv4_mmu_cache_off函数，这个函数在665行定义。 
// __armv4_mmu_cache_off: 
//               mrc p15, 0, r0, c1, c0 
//               bic   r0, r0, #0x000d 
//               mcr p15, 0, r0, c1, c0   @ turn MMU and cache off 
//               mov r0, #0 
//               mcr p15, 0, r0, c7, c7   @ invalidate whole cache v4 
//               mcr p15, 0, r0, c8, c7   @ invalidate whole TLB v4 
//               mov pc, lr 
// 这里首先读控制寄存器，然后关闭icache和mmu，接着使全部cache和tlb无效。 
// 现在总结一下在进入解压后的内核入口前都做了些什么（解压后的kernel入口在arch/arm/kernel/head.S中）： 
// 首先保存从uboot中传入的参数，然后会执行一段处理器相关的代码位于arch/arm/boot/compressed/head-xxx.S中，这段代码我们这里没有分析，在移植内核时会对这段代码作出分析。接着会判断一下要不要重定位，我们这里是不需要重定位，所以开始对bss段清零。之后初始化页表，进行1:1映射。因为打开cache前必须打开mmu，所以这里先对页表进行初始化，然后打开mmu和cache。这些都准备好后，判断一下解压内核是否会覆盖未解压的内核映像。如果会，则进行一些调整，然后开始解压内核；如果不会，则直接解压。最后是刷新cache，关闭mmu和dcache,使 cache和tlb内容无效，跳到解压后的内核入口执行arm相关的内核代码。
// 
// 
// ========================================================================================================================
// 
// Linux 内核启动分析（转） Linux 内核启动分析 
// 
// 1.       内核启动地址
// 1.1.   名词解释
// ZTEXTADDR
// 
// 解压代码运行的开始地址。没有物理地址和虚拟地址之分，因为此时MMU处于关闭状态。这个地址不一定时RAM的地址，可以是支持读写寻址的flash等存储中介。
// 
// Start address of decompressor. here's no point in talking about virtual or physical addresses here, since the MMU will be off at the time when you call the decompressor code. You normally call   the kernel at this address to start it booting. This doesn't have to be located in RAM, it can be in flash or other read-only or      read-write addressable medium.
// 
//  
// 
// ZRELADDR
// 
//        内核启动在RAM中的地址。压缩的内核映像被解压到这个地址，然后执行。
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
//        内核启动的虚拟地址，与ZRELADDR相对应。一般内核启动的虚拟地址为RAM的第一个bank地址加上0x8000。
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
//        内核偏移地址。在arch/arm/makefile中设定。
// 
//  
// 
// PHYS_OFFSET
// 
//        RAM第一个bank的物理起始地址。
// 
// Physical start address of the first bank of RAM.
// 
//  
// 
// PAGE_OFFSET
// 
// RAM第一个bank的虚拟起始地址。
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
// 1.2.   内核启动地址确定
// 内核启动引导地址由bootp.lds决定。 Bootp.lds : arch/arm/bootp
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
// 由上 .= 0可以确定解压代码运行的开始地址在0x0的位置。ZTEXTADDR的值决定了这个值得选取。
// 
//  
// 
// Makefile : arch/arm/boot/compressed
// 
//  
// 
// 如果设定内核从ROM中启动的话，可以在make menuconfig 的配置界面中设置解压代码的起始地址，否则解压代码的起始地址为0x0。实际上，默认从ROM启动时，解压代码的起始地址也是0x0。
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
// ……
// 
// $(obj)/vmlinux.lds: $(obj)/vmlinux.lds.in arch/arm/mach-s3c2410/Makefile .config
// 
//        @sed "$(SEDFLAGS)" < $< > $@
// 
//  
// 
// @sed "$(SEDFLAGS)" < $< > $@ 规则将TEXT_START设定为ZTEXTADDR。TEXT_START在arch/arm/boot/compressed /vmlinux.lds.in 中被用来设定解压代码的起始地址。
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
// ……
// 
//   }
// 
// }
// 
//  
// 
// 内核的编译依靠vmlinux.lds，vmlinux.lds由vmlinux.lds.s 生成。从下面代码可以看出内核启动的虚拟地址被设置为PAGE_OFFSET + TEXT_OFFSET，而内核启动的物理地址ZRELADDR在arch/arm/boot/Makefile中设定。
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
// ……
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
// 通过下面的命令编译内核映像，由参数-a, -e设置其入口地址为ZRELADDR，此值在上面ZRELADDR    := $(zreladdr-y)指定。
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
// 1.3.   小结
// 从上面分析可知道，linux内核被bootloader拷贝到RAM后，解压代码从ZTEXTADDR开始运行（这段代码是与位置无关的PIC）。内核被解压缩到ZREALADDR处，也就是内核启动的物理地址处。相应地，内核启动的虚拟地址被设定为TEXTADDR，满足如下条件：
// 
// TEXTADDR = PAGE_OFFSET + TEXT_OFFSET
// 
// 内核启动的物理地址和虚拟地址满足入下条件：
// 
// ZRELADDR == virt_to_phys(PAGE_OFFSET + TEXT_OFFSET)= virt_to_phys(TEXTADDR)
// 
//  
// 
// 假定开发板为smdk2410，则有：
// 
// 内核启动的虚拟地址
// 
// TEXTADDR     = 0xC0008000
// 
// 内核启动的物理地址   
// 
// ZRELADDR     = 0x30008000
// 
// 如果直接从flash中启动还需要设置ZTEXTADDR地址。
// 
//  
// 
// 2.       内核启动过程分析
// 内核启动过程经过大体可以分为两个阶段：内核映像的自引导；linux内核子模块的初始化。
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
// Setup_arch  ……
//  
// Start_kernel
//  
// _enable_mmu
//  
// Execve(“/sbin/init”))
//  
// 内核启动流程图
// 
// 2.1.   内核映像的自引导
// 这阶段的主要工作是实现压缩内核的解压和进入内核代码的入口。
// 
// Bootloader完成系统引导后，内核映像被调入内存指定的物理地址ZTEXTADDR。典型的内核映像由自引导程序和压缩的VMlinux组成。因此在启动内核之前需要先把内核解压缩。内核映像的入口的第一条代码就是自引导程序。它在arch/arm/boot/compressed /head.S文件中。
// 
// Head.S文件主要功能是实现压缩内核的解压和跳转到内核vmlinux内核的入口。Decompress_kernel(): arch/arm/boot/compressed/misc.c 和call_kernel这两个函数实现了上述功能。在调用decompress_kernel()解压内核之前，需要确保解压后的内核代码不会覆盖掉原来的内核映像。以及设定内核代码的入口地址ZREALADDR。
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
// 上面这段代码得到内核代码的入口地址，保存在r4中。
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

 

上面代码判断解压后的内核代码会不会覆盖原来的内核映像，然后调用内核解压缩函数decompress_kernel()。

 

ulg

decompress_kernel(ulg output_start, ulg free_mem_ptr_p, ulg free_mem_ptr_end_p,

                int arch_id)

{

       output_data            = (uch *)output_start;    /* 指定内核执行地址，保存在r4中*/

       free_mem_ptr        = free_mem_ptr_p;

       free_mem_ptr_end = free_mem_ptr_end_p;

       __machine_arch_type    = arch_id;

 

       arch_decomp_setup();  /*解压缩前的初始化和设置，包括串口波特率设置等*/

 

       makecrc();           /*CRC校验*/

       putstr("Uncompressing Linux...");

       gunzip();            /*调用解压缩函数*/

       putstr(" done, booting the kernel./n");

       return output_ptr;

}

 

把内核映像解压到ZERALADDR地址后，调用call_kernel函数进入内核代码的入口地址。

call_kernel:     bl     cache_clean_flush

              bl     cache_off

              mov r0, #0                    @ must be zero

              mov r1, r7                    @ restore architecture number

              mov r2, r8                    @ restore atags pointer

              mov pc, r4                    @ call kernel

我们知道r4寄存器内保存的是内核的执行地址，mov pc, r4使得程序指针指向了内核的执行地址，所以下面将进入内核代码执行阶段。

2.2.   linux内核子模块的初始化
2.2.1. 预备工作
进入真正的内核代码，首先执行的也是一个叫做head.S（arch/arm/kernel/）的文件。同时head.S也包含了同目录下head-common.S（arch/arm/kernel/）。这两个文件联合起来主要负责下面几项工作：

         判断CPU类型，查找运行的CPU ID值与Linux编译支持的ID值是否支持

         判断体系类型，查看R1寄存器的Architecture Type值是否支持

         创建页表

         开启MMU

         跳转到start_kernel()（内核子模块初始化程序）

 

注: 暂时不对各个子程序实现作细节性的分析。

2.2.2. 内核各子模块初始化
Start_kernel函数是Linux内核通用的初始化函数。无论对于什么体系结构的Linux，都要执行这个函数。Start_kernel()函数是内核初始化的基本过程。下面按照函数对内核模块初始化的先后顺序进行分析。

start_kernel函数位于init/main.c

asmlinkage void __init start_kernel(void)

{

       char * command_line;

       extern struct kernel_param __start___param[], __stop___param[];

 

smp_setup_processor_id();   /*指定当前的cpu的逻辑号，这个函数对应于对称多处理器的设置，当系统中只有一个cpu的情况，此函数为空，什么也不做*/

 

lockdep_init();            /* 初始化lockdep hash 表 */

 

 

/* 初始化irq */

       local_irq_disable();        

       early_boot_irqs_off();      

       early_init_irq_lock_class();

 

 

/* 锁定内核、设置cpu的状态为’present’,’online’等状态、初始化页表、打印内核版本号等信息、设置体系结构、为cpu分配启动内存空间 ，在此期间中断仍然处于关闭状态*/

       lock_kernel();

       boot_cpu_init();

       page_address_init();

       printk(KERN_NOTICE);

       printk(linux_banner);

       setup_arch(&command_line);

       setup_per_cpu_areas();

       smp_prepare_boot_cpu();     /* arch-specific boot-cpu hooks */

 

       /*在打开任何中断之前打开调度器 */

       sched_init();

 

/*关闭任务抢占功能，因为早期的调度器功能比较脆弱，直到第一次调用cpu_idle()*/

       preempt_disable();

 

    /* 建立内存区域链表节点，对于单cpu节点数为1 */

       build_all_zonelists();

 

/* 发通知给每个CPU，处理每个CPU的内存状态*/

       page_alloc_init();

 

       /* 分析早期没命令参数*/

printk(KERN_NOTICE "Kernel command line: %s/n", saved_command_line);

       parse_early_param();

    /* 分析命令参数 */

       parse_args("Booting kernel", command_line, __start___param,

                 __stop___param - __start___param,

                 &unknown_bootoption);

 

    /* 排序内核创建的异常表 */

       sort_main_extable();

 

       unwind_init();

 

    /*设置陷阱门和中断门 */

       trap_init();

 

 

       /*初始化内核中的读-拷贝-更新（Read-Copy-Update RCU)子系统 */

       rcu_init();

 

    /*初始化IRQ */

       init_IRQ();

 

       /* 按照开发办上的物理内存初始化pid hash表 */

       pidhash_init();

 

    /*初始化计时器 */

       init_timers();

 

              /* 高解析度&高精度的计时器 (high resolution)初始化 */

       hrtimers_init();

 

       /*初始化软中断 */

       softirq_init();

 

       /* 初始化时钟资源和普通计时器的值 */

       timekeeping_init();

 

       /* 初始化系统时间*/

time_init();

 

/*为内核分配内存以存储收集的数据*/

       profile_init();

 

       /* 开中断 */

       if (!irqs_disabled())

              printk("start_kernel(): bug: interrupts were enabled early/n");

       early_boot_irqs_on();

       local_irq_enable();

 

       /*

        * HACK ALERT! This is early. We're enabling the console before

        * we've done PCI setups etc, and console_init() must be aware of

        * this. But we do want output early, in case something goes wrong.

        */

       /* 初始化控制台，为了能够尽早地帮助调试，显示系统引导的信息*/

       console_init();

       if (panic_later)

              panic(panic_later, panic_param);

 

       /*如果定义了CONFIG_LOCKDEP宏，则打印锁依赖信息，否则什么也不做 */

       lockdep_info();

 

       /*

        * Need to run this when irqs are enabled, because it wants

        * to self-test [hard/soft]-irqs on/off lock inversion bugs

        * too:

        */

/* 如果定义CONFIG_DEBUG_LOCKING_API_SELFTESTS宏，则locking_selftest()是一个空函数，否则执行锁自测*/

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

(1)dcache_init()创建SLAB缓存，该缓存保存目录项描述符。传存本身被称作dentry_cache。当进程访问文件或目录时所涉及的目录名有多个目录分量组成，目录项描述符就是针对每个分量而创建的。目录项各结构把文件或目录分量与其索引结点结合起来，因而可以通过该目录项可以更快地找到与其对应的索引结点 

(2)inode_init()初始化哈希表索引结点和等待队列对头，该队头存放内核要锁存的哈希索引结点。 

(3)file_init()确定给每个进程呢个zhogn的文件所分配的最大内存量 

(4)mnt_init()创建了保存vfsmount对象且名为mnt_cache的缓存，VFS利用这协对吸纳给来挂载文件系统。该例程也创建 mount_hashtable队列，该队列存放mnt_cache中引用的快速访问对象。然后该例程发出调用来初始化sysfs文件系统并挂载root 文件系统。

      */

       vfs_caches_init_early();

 

       cpuset_init_early();

 

/* Mem_init()函数为mem_map中的自由区作标记并且打印出自由内存的大小。这个函数在系统的各个部分申请过内存后执行 */

       mem_init();

 

       /* 初始化cache相关的链表，函数在初始化页表分配器后smp_init()之前执行 */

kmem_cache_init();

 

/* 为逻辑号为0的cpu初始化页面。如果是smp情况下，只要cpu表现为online态，此函数就会执行 */

setup_per_cpu_pageset();

 

       /* numa内存策略器初始化 */

numa_policy_init();

 

       /* 内存初始化后调用 */

       if (late_time_init)

              late_time_init();

 

 

/*计算并打印许多著名的"BogoMips"的值，该值度量处理器在一个时钟节拍内可以反复执行多少个delay().对不同速度的处理器，cali_brate_delay()允许的延迟大约相同*/

       calibrate_delay();

 

       /* 初始化pidmap_array,分配pid＝0给当前进程 */

       pidmap_init();

 

       /* 初始化页表高速缓存 */

       pgtable_cache_init();

 

       /*初始化优先级树index_bits_to_maxindex数组*/

       prio_tree_init();

 

       /*创建anon_vma结构对象slab缓存*/

       anon_vma_init();

 

#ifdef CONFIG_X86

       if (efi_enabled)

              efi_enter_virtual_mode();

#endif

 

/*根据可用内存大小来建立用户缓冲区uid_cache，初始化最大线程数max_threads，为init_task配置RLIMIT_NPROC的值为max_threads/2 */

       fork_init(num_physpages);

 

/*建立各种块缓冲区，比如VFS, VM等*/

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

 

/*检查错误，其实是调用check_writebuffer_bugs()函数检查是否有物理地址混淆的现象 */

       check_bugs();


       /* advanced configuration and power management interface */

       acpi_early_init(); /* before LAPIC and SMP init */

 

       /* Do the rest non-__init'ed, we're now alive */

 

       /* 创建init进程，删除内核锁，启动idle线程 */

       rest_init();

}  
 / 
// 进入init进程后，将执行init()函数负责完成挂接根文件系统、初始化设备驱动和启动用户空间的init进程。（sunny 负责研究这部分）
// 
// ==============================另一篇====================================
// 摘 要： 嵌入式 Linux 的可移植性使得我们可以在各种电子产品上看到它的身影。对于不 
// 同体系结构的处理器来说Linux的启动过程也有所不同。本文以S3C2410 ARM处理器为例， 
// 详细分析了系统上电后 bootloader的执行流程及 ARM Linux的启动过程。 
// 关键词：ARM Linux bootloader 启动过程 
// 中图分类号：TP316 
// 1. 引 言 
// Linux 最初是由瑞典赫尔辛基大学的学生 Linus Torvalds在1991 年开发出来的，之后在 
// GNU的支持下，Linux 获得了巨大的发展。虽然 Linux 在桌面 PC 机上的普及程度远不及微 
// 软的 Windows 操作系统，但它的发展速度之快、用户数量的日益增多，也是微软所不能轻 
// 视的。而近些年来 Linux 在嵌入式领域的迅猛发展，更是给 Linux 注入了新的活力。 
// 一个嵌入式 Linux 系统从软件角度看可以分为四个部分[1] 
// ：引导加载程序（bootloader）， 
// Linux 内核，文件系统，应用程序。 
// 其中 bootloader是系统启动或复位以后执行的第一段代码，它主要用来初始化处理器及 
// 外设，然后调用 Linux 内核。Linux 内核在完成系统的初始化之后需要挂载某个文件系统做 
// 为根文件系统（Root Filesystem）。根文件系统是 Linux 系统的核心组成部分，它可以做为 
// Linux 系统中文件和数据的存储区域，通常它还包括系统配置文件和运行应用软件所需要的 
// 库。应用程序可以说是嵌入式系统的“灵魂”，它所实现的功能通常就是设计该嵌入式系统 
// 所要达到的目标。如果没有应用程序的支持，任何硬件上设计精良的嵌入式系统都没有实用 
// 意义。 
// 从以上分析我们可以看出 bootloader 和 Linux 内核在嵌入式系统中的关系和作用。 
// Bootloader在运行过程中虽然具有初始化系统和执行用户输入的命令等作用，但它最根本的 
// 功能就是为了启动 Linux 内核。在嵌入式系统开发的过程中，很大一部分精力都是花在 
// bootloader 和 Linux 内核的开发或移植上。如果能清楚的了解 bootloader 执行流程和 Linux 
// 的启动过程，将有助于明确开发过程中所需的工作，从而加速嵌入式系统的开发过程。而这 
// 正是本文的所要研究的内容。 
// 2. Bootloader 
// 2.1 Bootloader的概念和作用 
// Bootloader是嵌入式系统的引导加载程序，它是系统上电后运行的第一段程序，其作用 
// 类似于 PC 机上的 BIOS。在完成对系统的初始化任务之后，它会将非易失性存储器（通常 
// 是 Flash或 DOC 等）中的Linux 内核拷贝到 RAM 中去，然后跳转到内核的第一条指令处继 
// 续执行，从而启动 Linux 内核。 
// 由此可见，bootloader 和 Linux 内核有着密不可分的联系，要想清楚的了解 Linux内核 
// 的启动过程，我们必须先得认识 bootloader的执行过程，这样才能对嵌入式系统的整个启动
// 过程有清晰的掌握。 
// 2.2 Bootloader的执行过程 
// 不同的处理器上电或复位后执行的第一条指令地址并不相同，对于 ARM 处理器来说， 
// 该地址为 0x00000000。对于一般的嵌入式系统，通常把 Flash 等非易失性存储器映射到这个 
// 地址处，而 bootloader就位于该存储器的最前端，所以系统上电或复位后执行的第一段程序 
// 便是 bootloader。而因为存储 bootloader的存储器不同，bootloader的执行过程也并不相同， 
// 下面将具体分析。 
// 嵌入式系统中广泛采用的非易失性存储器通常是 Flash，而 Flash 又分为 Nor Flash 和 
// Nand Flash 两种。 它们之间的不同在于： Nor Flash 支持芯片内执行（XIP， eXecute In Place）， 
// 这样代码可以在Flash上直接执行而不必拷贝到RAM中去执行。而Nand Flash并不支持XIP， 
// 所以要想执行 Nand Flash 上的代码，必须先将其拷贝到 RAM中去，然后跳到 RAM 中去执 
// 行。 
// 实际应用中的 bootloader根据所需功能的不同可以设计得很复杂，除完成基本的初始化 
// 系统和调用 Linux 内核等基本任务外，还可以执行很多用户输入的命令，比如设置 Linux 启 
// 动参数，给 Flash 分区等；也可以设计得很简单，只完成最基本的功能。但为了能达到启动 
// Linux 内核的目的，所有的 bootloader都必须具备以下功能[2] 
// ： 
// 1) 初始化 RAM 
// 因为 Linux 内核一般都会在 RAM 中运行，所以在调用 Linux 内核之前 bootloader 必须 
// 设置和初始化 RAM，为调用 Linux内核做好准备。初始化 RAM 的任务包括设置 CPU 的控 
// 制寄存器参数，以便能正常使用 RAM 以及检测RAM 大小等。 
// 2) 初始化串口 
// 串口在 Linux 的启动过程中有着非常重要的作用，它是 Linux内核和用户交互的方式之 
// 一。Linux 在启动过程中可以将信息通过串口输出，这样便可清楚的了解 Linux 的启动过程。 
// 虽然它并不是 bootloader 必须要完成的工作，但是通过串口输出信息是调试 bootloader 和 
// Linux 内核的强有力的工具，所以一般的 bootloader 都会在执行过程中初始化一个串口做为 
// 调试端口。 
// 3) 检测处理器类型 
// Bootloader在调用 Linux内核前必须检测系统的处理器类型，并将其保存到某个常量中 
// 提供给 Linux 内核。Linux 内核在启动过程中会根据该处理器类型调用相应的初始化程序。 
// 4) 设置 Linux启动参数 
// Bootloader在执行过程中必须设置和初始化 Linux 的内核启动参数。目前传递启动参数 
// 主要采用两种方式：即通过 struct param_struct 和struct tag（标记列表，tagged list）两种结 
// 构传递。struct param_struct 是一种比较老的参数传递方式，在 2.4 版本以前的内核中使用较 
// 多。从 2.4 版本以后 Linux 内核基本上采用标记列表的方式。但为了保持和以前版本的兼容 
// 性，它仍支持 struct param_struct 参数传递方式，只不过在内核启动过程中它将被转换成标 
// 记列表方式。 
// 标记列表方式是种比较新的参数传递方式，它必须以 ATAG_CORE 开始，并以 
// ATAG_NONE 结尾。中间可以根据需要加入其他列表。Linux内核在启动过程中会根据该启 
// 动参数进行相应的初始化工作。 
// 5) 调用 Linux内核映像 
// Bootloader完成的最后一项工作便是调用 Linux内核。如果 Linux 内核存放在 Flash 中， 
// 并且可直接在上面运行（这里的 Flash 指 Nor Flash），那么可直接跳转到内核中去执行。 
// 但由于在 Flash 中执行代码会有种种限制，而且速度也远不及 RAM 快，所以一般的嵌 
// 入式系统都是将 Linux内核拷贝到 RAM 中，然后跳转到 RAM 中去执行。 
// 不论哪种情况，在跳到 Linux 内核执行之前 CUP的寄存器必须满足以下条件：r0＝0， 
// r1＝处理器类型，r2＝标记列表在 RAM中的地址。 
// 
// 3. Linux内核的启动过程 
// 
//   在 bootloader将 Linux 内核映像拷贝到 RAM 以后，可以通过下例代码启动 Linux 内核： 
// call_linux(0, machine_type, kernel_params_base)。 
// 其中，machine_tpye 是 bootloader检测出来的处理器类型， kernel_params_base 是启动参 
// 数在 RAM 的地址。通过这种方式将 Linux 启动需要的参数从 bootloader传递到内核。 
// Linux 内核有两种映像：一种是非压缩内核，叫 Image，另一种是它的压缩版本，叫 
// zImage。根据内核映像的不同，Linux 内核的启动在开始阶段也有所不同。zImage 是 Image 
// 经过压缩形成的，所以它的大小比 Image 小。但为了能使用 zImage，必须在它的开头加上 
// 解压缩的代码，将 zImage 解压缩之后才能执行，因此它的执行速度比 Image 要慢。但考虑 
// 到嵌入式系统的存储空容量一般比较小，采用 zImage 可以占用较少的存储空间，因此牺牲 
// 一点性能上的代价也是值得的。所以一般的嵌入式系统均采用压缩内核的方式。 
// 对于 ARM 系列处理器来说，zImage 的入口程序即为 arch/arm/boot/compressed/head.S。 
// 它依次完成以下工作：开启 MMU 和 Cache，调用 decompress_kernel()解压内核，最后通过 
// 调用 call_kernel()进入非压缩内核 Image 的启动。下面将具体分析在此之后 Linux 内核的启 
// 动过程。 
// 3.1 Linux内核入口 
// Linux 非压缩内核的入口位于文件/arch/arm/kernel/head-armv.S 中的 stext 段。该段的基 
// 地址就是压缩内核解压后的跳转地址。如果系统中加载的内核是非压缩的 Image，那么 
// bootloader将内核从 Flash中拷贝到 RAM 后将直接跳到该地址处，从而启动 Linux 内核。 
// 不同体系结构的 Linux 系统的入口文件是不同的，而且因为该文件与具体体系结构有 
// 关，所以一般均用汇编语言编写[3] 
// 。对基于 ARM 处理的 Linux 系统来说，该文件就是 
// head-armv.S。该程序通过查找处理器内核类型和处理器类型调用相应的初始化函数，再建 
// 立页表，最后跳转到 start_kernel()函数开始内核的初始化工作。 
// 检测处理器内核类型是在汇编子函数__lookup_processor_type中完成的。通过以下代码 
// 可实现对它的调用： 
// bl __lookup_processor_type。 
// __lookup_processor_type调用结束返回原程序时，会将返回结果保存到寄存器中。其中 
// r8 保存了页表的标志位，r9 保存了处理器的 ID 号，r10 保存了与处理器相关的 stru 
// proc_info_list 结构地址。 
// 检测处理器类型是在汇编子函数 __lookup_architecture_type 中完成的。与 
// __lookup_processor_type类似，它通过代码：“bl __lookup_processor_type”来实现对它的调 
// 用。该函数返回时，会将返回结构保存在 r5、r6 和 r7 三个寄存器中。其中 r5 保存了 RAM 
// 的起始基地址，r6 保存了 I/O基地址，r7 保存了 I/O的页表偏移地址。 
// 当检测处理器内核和处理器类型结束后，将调用__create_page_tables 子函数来建立页 
// 表，它所要做的工作就是将 RAM 基地址开始的 4M 空间的物理地址映射到 0xC0000000 开 
// 始的虚拟地址处。对笔者的 S3C2410 开发板而言，RAM 连接到物理地址 0x30000000 处， 
// 当调用 __create_page_tables 结束后 0x30000000 ～ 0x30400000 物理地址将映射到 
// 0xC0000000～0xC0400000 虚拟地址处。 
// 当所有的初始化结束之后，使用如下代码来跳到 C 程序的入口函数 start_kernel()处，开 
// 始之后的内核初始化工作： 
// b SYMBOL_NAME(start_kernel) 
// 3.2 start_kernel函数 
// start_kernel是所有 Linux 平台进入系统内核初始化后的入口函数，它主要完成剩余的与 
// 硬件平台相关的初始化工作，在进行一系列与内核相关的初始化后，调用第一个用户进程－ 
// init 进程并等待用户进程的执行，这样整个 Linux 内核便启动完毕。该函数所做的具体工作 
// 有[4][5] 
// ： 
// 1) 调用 setup_arch()函数进行与体系结构相关的第一个初始化工作； 
// 对不同的体系结构来说该函数有不同的定义。对于 ARM 平台而言，该函数定义在 
// arch/arm/kernel/Setup.c。它首先通过检测出来的处理器类型进行处理器内核的初始化，然后 
// 通过 bootmem_init()函数根据系统定义的 meminfo 结构进行内存结构的初始化，最后调用 
// paging_init()开启 MMU，创建内核页表，映射所有的物理内存和 IO空间。 
// 2) 创建异常向量表和初始化中断处理函数； 
// 3) 初始化系统核心进程调度器和时钟中断处理机制； 
// 4) 初始化串口控制台（serial-console）； 
// ARM-Linux 在初始化过程中一般都会初始化一个串口做为内核的控制台，这样内核在 
// 启动过程中就可以通过串口输出信息以便开发者或用户了解系统的启动进程。 
// 5) 创建和初始化系统 cache，为各种内存调用机制提供缓存，包括;动态内存分配，虚拟文 
// 件系统（VirtualFile System）及页缓存。 
// 6) 初始化内存管理，检测内存大小及被内核占用的内存情况； 
// 7) 初始化系统的进程间通信机制（IPC）； 
// 当以上所有的初始化工作结束后，start_kernel()函数会调用 rest_init()函数来进行最后的 
// 初始化，包括创建系统的第一个进程－init 进程来结束内核的启动。Init 进程首先进行一系 
// 列的硬件初始化，然后通过命令行传递过来的参数挂载根文件系统。最后 init 进程会执行用 
// 户传递过来的“init＝”启动参数执行用户指定的命令，或者执行以下几个进程之一： 
// execve("/sbin/init",argv_init,envp_init); 
// execve("/etc/init",argv_init,envp_init); 
// execve("/bin/init",argv_init,envp_init); 
// execve("/bin/sh",argv_init,envp_init)。 
// 当所有的初始化工作结束后，cpu_idle()函数会被调用来使系统处于闲置（idle）状态并 
//等待用户程序的执行。至此，整个 Linux 内核启动完毕。 
