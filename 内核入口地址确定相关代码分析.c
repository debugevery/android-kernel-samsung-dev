内核入口地址确定相关代码分析2011年03月03日 星期四 16:331. Bootloader及内核解压 
2. 内核启动方式介绍 
3. 内核启动地址的确定 
4. arch/armnommu/kernel/head-armv.S分析 
5. start_kernel()函数分析1. Bootloader及内核解压 
Bootloader将内核加载到内存中，设定一些寄存器，然后将控制权交由内核，该过程中，关闭MMU功能。通常，内核都是以压缩的方式存放，如zImage，这里有两种解压方法： 
使用内核自解压程序。 
arch/arm/boot/compressed/head.S或arch/arm/boot/compressed/head-xxxxx.S 
arch/arm/boot/compressed/misc.c 
在Bootloader中增加解压功能。 
使用该方法时内核不需要带有自解压功能，而使用Bootloader中的解压程序代替内核自解压程序。其工作过程与内核自解压过程相似：Bootloader把压缩方式的内核解压到内存中，然后跳转到内核入口处开始执行。2. 几种内核启动方式介绍 
XIP (EXECUTE IN PLACE) 是指直接从存放代码的位置上启动运行。 
2.1 非压缩，非XIP 
非XIP方式是指在运行之前需对代码进行重定位。该类型的内核以非压缩方式存放在Flash中，启动时由Bootloader加载到内存后运行。 
2.2 非压缩，XIP 
该 类型的内核以非压缩格式存放在ROM/Flash中，不需要加载到内存就能运行，Bootloader直接跳转到其存放地址执行。Data段复制和BSS 段清零的工作由内核自己完成。这种启动方式常用于内存空间有限的系统中，另外，程序在ROM/Flash中运行的速度相对较慢。 
2.3 RAM自解压 
压 缩格式的内核由开头一段自解压代码和压缩内核数据组成，由于以压缩格式存放，内核只能以非XIP方式运行。RAM自解压过程如下：压缩内核存放于 ROM/Flash中，Bootloader启动后加载到内存中的临时空间，然后跳转到压缩内核入口地址执行自解压代码，内核被解压到最终的目的地址然后 运行。压缩内核所占据的临时空间随后被Linux回收利用。这种方式的内核在嵌入式产品中较为常见。 
2.4 ROM自解压 
解压缩代 码也能够以XIP的方式在ROM/Flash中运行。ROM自解压过程如下：压缩内核存放在ROM/Flash中，不需要加载到内存就能运行， Bootloader直接跳转到其存放地址执行其自解压代码，将压缩内核解压到最终的目的地址并运行。ROM自解压方式存放的内核解压缩速度慢，而且也不 能节省内存空间。3. 内核启动地址的确定 
内核自解压方式 
Head.S/head-XXX.S获得内核解压后首地址ZREALADDR，然后解压内核，并把解压后的内核放在ZREALADDR的位置上，最后跳转到ZREALADDR地址上，开始真正的内核启动。arch/armnommu/boot/Makefile， 定义ZRELADDR和 ZTEXTADDR。ZTEXTADDR是自解压代码的起始地址，如果从内存启动内核，设置为0即可，如果从Rom/Flash启动，则设置 ZTEXTADDR为相应的值。ZRELADDR是内核解压缩后的执行地址。 
arch/armnommu/boot/compressed/vmlinux.ld,引用LOAD_ADDR和TEXT_START。 
arch/armnommu/boot/compressed/Makefile, 通过如下一行： 
SEDFLAGS = s/TEXT_START/$(ZTEXTADDR)/;s/LOAD_ADDR/$(ZRELADDR)/; 
使得TEXT_START = ZTEXTADDR，LOAD_ADDR = ZRELADDR。说明： 
执 行完decompress_kernel函数后,代码跳回head.S/head-XXX.S中,检查解压缩之后的kernel起始地址是否紧挨着 kernel image。如果是,beq call_kernel,执行解压后的kernel。如果解压缩之后的kernel起始地址不是紧挨着kernel image,则执行relocate,将其拷贝到紧接着kernel image的地方,然后跳转,执行解压后的kernel。Bootloader解压方式 
Bootloader把解压后的内核放在内存的TEXTADDR位置上，然后跳转到TEXTADDR位置上，开始内核启动。 
arch/armnommu/Makefile，一般设置TEXTADDR为PAGE_OFF+0x8000，如定义为0x00008000, 0xC0008000等。 
arch/armnommu/vmlinux.lds，引用TEXTADDR4. arch/armnommu/kernel/head-armv.S 
该 文件是内核最先执行的一个文件，包括内核入口ENTRY(stext)到start_kernel间的初始化代码，主要作用是检查CPU ID，Architecture Type，初始化BSS等操作，并跳到start_kernel函数。在执行前，处理器应满足以下状态： 
r0 - should be 0 
r1 - unique architecture number 
MMU - off 
I-cache - on or off 
D-cache – off/* 部分源代码分析 */ 
/* 内核入口点 */ 
ENTRY(stext) 
/* 程序状态，禁止FIQ、IRQ，设定SVC模式 */ 
mov r0, #F_BIT | I_BIT | MODE_SVC@ make sure svc mode 
/* 置当前程序状态寄存器 */ 
msr cpsr_c, r0 @ and all irqs disabled 
/* 判断CPU类型，查找运行的CPU ID值与Linux编译支持的ID值是否支持 */ 
bl __lookup_processor_type 
/* 跳到__error */ 
teq r10, #0 @ invalid processor? 
moveq r0, #''p'' @ yes, error ''p'' 
beq __error 
/* 判断体系类型，查看R1寄存器的Architecture Type值是否支持 */ 
bl __lookup_architecture_type 
/* 不支持，跳到出错 */ 
teq r7, #0 @ invalid architecture? 
moveq r0, #''a'' @ yes, error ''a'' 
beq __error 
/* 创建核心页表 */ 
bl __create_page_tables 
adr lr, __ret @ return address 
add pc, r10, #12 @ initialise processor 
/* 跳转到start_kernel函数 */ 
b start_kernel__lookup_processor_type 这个函数根据芯片的ID从proc.info获取proc_info_list结构，proc_info_list结构定义在include/asm- armnommu/proginfo.h中，该结构的数据定义在arch/armnommu/mm/proc-arm*.S文件中，ARM7TDMI系列 芯片的proc_info_list数据定义在arch/armnommu/mm/proc-arm6,7.S文件中。函数 __lookup_architecture_type从arch.info获取machine_desc结构，machine_desc结构定义在 include/asm-armnommu/mach/arch.h中，针对不同arch的数据定义在arch/armnommu/mach- */arch.c文件中。 
在这里如果知道processor_type和architecture_type,可以直接对相应寄存器进行赋值。5. start_kernel()函数分析 
下面对start_kernel()函数及其相关函数进行分析。 
5.1 lock_kernel() 
/* Getting the big kernel lock. 
* This cannot happen asynchronously, 
* so we only need to worry about other 
* CPU''s. 
*/ 
extern __inline__ void lock_kernel(void) 
{ 
if (!++current->lock_depth) 
spin_lock(&kernel_flag); 
} 
kernel_flag 是一个内核大自旋锁，所有进程都通过这个大锁来实现向内核态的迁移。只有获得这个大自旋锁的处理器可以进入内核，如中断处理程序等。在任何一对 lock_kernel／unlock_kernel函数里至多可以有一个程序占用CPU。进程的lock_depth成员初始化为-1，在 kerenl/fork.c文件中设置。在它小于0时（恒为 -1），进程不拥有内核锁；当大于或等于0时，进程得到内核锁。5.2 setup_arch() 
setup_arch()函数做体系相关的初始化工作，函数的定义在arch/armnommu/kernel/setup.c文件中，主要涉及下列主要函数及代码。 
5.2.1 setup_processor() 
该函数主要通过 
for (list = &__proc_info_begin; list < &__proc_info_end ; list++) 
if ((processor_id & list->cpu_mask) == list->cpu_val) 
break; 
这样一个循环来在.proc.info段中寻找匹配的processor_id，processor_id在head_armv.S文件 
中设置。5.2.2 setup_architecture(machine_arch_type) 
该函数获得体系结构的信息，返回mach-xxx/arch.c 文件中定义的machine结构体的指针，包含以下内容： 
MACHINE_START (xxx, “xxx”) 
MAINTAINER ("xxx") 
BOOT_MEM (xxx, xxx, xxx) 
FIXUP (xxx) 
MAPIO (xxx) 
INITIRQ (xxx) 
MACHINE_END5.2.3内存设置代码 
if (meminfo.nr_banks == 0) 
{ 
meminfo.nr_banks = 1; 
meminfo.bank[0].start = PHYS_OFFSET; 
meminfo.bank[0].size = MEM_SIZE; 
} 
meminfo 结构表明内存情况，是对物理内存结构meminfo的默认初始化。 nr_banks指定内存块的数量，bank指定每块内存的范围，PHYS _OFFSET指定某块内存块的开始地址，MEM_SIZE指定某块内存块长度。PHYS _OFFSET和MEM_SIZE都定义在include/asm-armnommu/arch-XXX/memory.h文件中，其中PHYS _OFFSET是内存的开始地址，MEM_SIZE就是内存的结束地址。这个结构在接下来内存的初始化代码中起重要作用。5.2.4 内核内存空间管理 
init_mm.start_code = (unsigned long) &_text; 内核代码段开始 
init_mm.end_code = (unsigned long) &_etext; 内核代码段结束 
init_mm.end_data = (unsigned long) &_edata; 内核数据段开始 
init_mm.brk = (unsigned long) &_end; 内核数据段结束每一个任务都有一个mm_struct结构管理其内存空间，init_mm 是内核的mm_struct。其中设置成员变量* mmap指向自己， 意味着内核只有一个内存管理结构，设置 pgd=swapper_pg_dir， 
swapper_pg_dir是内核的页目录，ARM体系结构的内核页目录大小定义为16k。init_mm定义了整个内核的内存空间，内核线程属于内核代码，同样使用内核空间，其访问内存空间的权限与内核一样。5.2.5 内存结构初始化 
bootmem_init (&meminfo)函数根据meminfo进行内存结构初始化。bootmem_init(&meminfo)函数中调用 reserve_node_zero(bootmap_pfn, bootmap_pages) 函数，这个函数的作用是保留一部分内存使之不能被动态分配。这些内存块包括： 
reserve_bootmem_node(pgdat, __pa(&_stext), &_end - &_stext); /*内核所占用地址空间*/ 
reserve_bootmem_node(pgdat, bootmap_pfn<[转载请注明出处，www.linuxforum.net，作者：张洪耿，patrick_zhg@hotmail.com]本文来自CSDN博客，转载请标明出处：http://blog.csdn.net/wxmtwfx/archive/2008/05/19/2457156.aspx 
