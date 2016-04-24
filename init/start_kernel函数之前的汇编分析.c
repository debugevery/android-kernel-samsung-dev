 在分析这段代码之前，我们必须先找到汇编代码的入口位置，也就是Bootloader启动linux时所跳转到的地址。内核一般被压缩后保存到FLASH上的，在Bootloader启动Linux之前必须先解压缩内核，关于内核解压缩部分请参照arch/arm/boot/compressed这里面的代码，这里就不细将了。

   在进入Linux汇编代码之前，Bootloader的执行影响CPU的状态，其状态一般为：

        1. CPU必须处于SVC(supervisor)模式,并且IRQ和FIQ中断都是禁止的;
        2. MMU(内存管理单元)必须是关闭的, 此时虚拟地址对物理地址;
        3. 数据cache(Data cache)必须是关闭的
        4. 指令cache(Instruction cache)可以是打开的,也可以是关闭的,这个没有强制要求;
        5. CPU 通用寄存器0 (r0)必须是 0;
        6. CPU 通用寄存器1 (r1)必须是 ARM Linux machine type（在后面会将到machine type）

        7. CPU 通用寄存器2 (r2) 必须是 kernel parameter list 的物理地址(parameter list 是由boot loader传递给kernel,用来描述设备信息属性的列表）

   Linux汇编的入口地址请看文件arch/arm/kernel/head.s，我们现在来看看文件里面的代码吧。

    __INIT
.type stext, #function
ENTRY(stext)
mov r12, r0
mov r0, #PSR_F_BIT | PSR_I_BIT | MODE_SVC @ make sure svc mode
msr cpsr_c, r0   @ and all irqs disabled
bl __lookup_processor_type

我们来分析一下__lookup_processor_type这里面的函数吧，次函数的还是在本文件夹当中。

__lookup_processor_type:
    adr r5, 2f
    ldmia r5, {r7, r9, r10}
    sub r5, r5, r10   @ convert addresses
    add r7, r7, r5   @ to our address space
    add r10, r9, r5
    mrc p15, 0, r9, c0, c0  @ get processor id
1: ldmia r10, {r5, r6, r8}  @ value, mask, mmuflags
    and r6, r6, r9   @ mask wanted bits
    teq r5, r6
    moveq pc, lr
    add r10, r10, #PROC_INFO_SZ  @ sizeof(proc_info_list)
    cmp r10, r7
    blt 1b
    mov r10, #0    @ unknown processor
    mov pc, lr

2: .long __proc_info_end
    .long __proc_info_begin
    .long 2b
    .long __arch_info_begin
    .long __arch_info_end

r5保存了标号2的地址，接着就把__proc_info_end到2b的地址对应的付给r7,r9,r10。后面的连续三行语句的作用就是实现地址的转换，这样r10就存放着__proc_info_start，r7存放着__proc_info_end。其实这两者是一个全局变量的，arch/arm/kernel/vmlinux.lds.s中是如下定义的：

   __proc_info_begin = .;
        *(.proc.info)
   __proc_info_end = .;

其实可以看到这里有个区域的，就是所有文件中的.proc.info段都是属于这个区域的，我们再来看看我刚才说那两个全局变量的结构体。

  在 include/asm-arm/procinfo.h 中:
        00029: struct proc_info_list {
        00030:         unsigned int                cpu_val;
        00031:         unsigned int                cpu_mask;
        00032:         unsigned long                __cpu_mm_mmu_flags;        /* used by head.S */
        00033:         unsigned long                __cpu_io_mmu_flags;        /* used by head.S */
        00034:         unsigned long                __cpu_flush;                /* used by head.S */
        00035:         const char                *arch_name;
        00036:         const char                *elf_name;
        00037:         unsigned int                elf_hwcap;
        00038:         const char                *cpu_name;
        00039:         struct processor        *proc;
        00040:         struct cpu_tlb_fns        *tlb;
        00041:         struct cpu_user_fns        *user;
        00042:         struct cpu_cache_fns        *cache;
        00043: };
我们来看看一个具体文件中的.proc.info段，代码如下：

在arch/arm/mm/proc-arm926.S 中:
        00464:         .section ".proc.info", #alloc, #execinstr
        00465: 
        00466:         .type        __arm926_proc_info,#object
        00467: __arm926_proc_info:
        00468:         .long        0x41069260                        @ ARM926EJ-S (v5TEJ)
        00469:         .long        0xff0ffff0
        00470:         .long   PMD_TYPE_SECT | /
        00471:                 PMD_SECT_BUFFERABLE | /
        00472:                 PMD_SECT_CACHEABLE | /
        00473:                 PMD_BIT4 | /
        00474:                 PMD_SECT_AP_WRITE | /
        00475:                 PMD_SECT_AP_READ
        00476:         .long   PMD_TYPE_SECT | /
        00477:                 PMD_BIT4 | /
        00478:                 PMD_SECT_AP_WRITE | /
        00479:                 PMD_SECT_AP_READ
        00480:         b        __arm926_setup
        00481:         .long        cpu_arch_name
        00482:         .long        cpu_elf_name
        00483:         .long        HWCAP_SWP|HWCAP_HALF|HWCAP_THUMB|HWCAP_FAST_MULT|HWCAP_VFP|HWCAP_EDSP|HWCAP_JAVA
        00484:         .long        cpu_arm926_name
        00485:         .long        arm926_processor_functions
        00486:         .long        v4wbi_tlb_fns
        00487:         .long        v4wb_user_fns
        00488:         .long        arm926_cache_fns
        00489:         .size        __arm926_proc_info, . - __arm926_proc_info

其实我们可以看出他们之间的联系，简单来说就是在arch/arm/kernel/vmlinux.lds.s文件中其实就是对struct proc_info_list 结构体全局变量 __proc_info_begin 、__proc_info_end 的初始化，或是定义。就是说每个文件可以有一个或是几个不同的定义，这样的文件还有很多个。每个定义代表一个处理器的信息，等下我们要通过这些信息来查看是否是我们系统支持的。

   现在回到我们刚才的代码位置：

   mrc p15, 0, r9, c0, c0  @ get processor id在r9里面存放着从硬件上获得的处理器型号。

   ldmia r10, {r5, r6, r8}  @ value, mask, mmuflags刚才在上面的代码分析中了解到，r10存放着系统支持的处理器信息的开始位置，每个处理器都会对应一个处理器信息，我们已经知道这些信息会存放在这样的struct proc_info_list 结构变量里，这里r10指向第一个。r5,r6,r8存放的内容就是处理器ID号、处理器ID号对应的屏蔽字、内存管理单元的第一级描述符控制字段。这些都是前面那个变量的成员，其中用稍后就可以看到了。

   and r6, r6, r9   @ mask wanted bits
   teq r5, r6

这里就对前两个成员进行了运用，先是和屏蔽字相与，结果与ID号相比较。

  moveq pc, lr
  add r10, r10, #PROC_INFO_SZ  @ sizeof(proc_info_list)
  cmp r10, r7
  blt 1b
  mov r10, #0    @ unknown processor
  mov pc, lr

下面的代码就是循环进行比较，知道找到与系统匹配的处理器，如果不匹配了，就说明这个系统不支持这样的处理器，返回后会直接跳转到错误位置的。一下就是返回后的代码。

  teq r10, #0    @ invalid processor?
  moveq r0, #'p'   @ yes, error 'p'
  beq __error
  bl __lookup_architecture_type

很简单，如果r10为0，就说明没有找到匹配的，如果找到的话，r10存放着与之匹配的处理器信息。接下来又要跳转__lookup_architecture_type，我们来看看这部分代码：

2: .long __proc_info_end
.long __proc_info_begin
.long 2b
.long __arch_info_begin
.long __arch_info_end

/*
* Lookup machine architecture in the linker-build list of architectures.
* Note that we can't use the absolute addresses for the __arch_info
* lists since we aren't running with the MMU on (and therefore, we are
* not in the correct address space).  We have to calculate the offset.
*
*  r1 = machine architecture number
* Returns:
*  r2, r3, r4 corrupted
*  r5 = physical start address of RAM
*  r6 = physical address of IO
*  r7 = byte offset into page tables for IO
*/
__lookup_architecture_type:
    adr r4, 2b
    ldmia r4, {r2, r3, r5, r6, r7} @ throw away r2, r3
    sub r5, r4, r5   @ convert addresses
    add r4, r6, r5   @ to our address space
    add r7, r7, r5
1: ldr r5, [r4]   @ get machine type
    teq r5, r1    @ matches loader number?
    beq 2f    @ found
    add r4, r4, #SIZEOF_MACHINE_DESC @ next machine_desc
    cmp r4, r7
    blt 1b
    mov r7, #0    @ unknown architecture
    mov pc, lr
2: ldmib r4, {r5, r6, r7}  @ found, get results
    mov pc, lr
其实仔细看看，会发现和上述的代码差不多，同样r4保存着上面标号2的地址，把r6,r7附上了 __arch_info_begin、__arch_info_end变量的地址，后面三句又是地址转换，重新确认后的地址保存在r7,r4上面。我们来看看这两个变量具体是什么。

__arch_info_begin 和 __arch_info_end是在 arch/arm/kernel/vmlinux.lds.S中:

        00034:                __arch_info_begin = .;
        00035:                        *(.arch.info.init)
        00036:                __arch_info_end = .;
这三行的意思是: __arch_info_begin 的位置上,放置所有文件中的 ".arch.info.init" 段的内容,然后紧接着是 __arch_info_end 的位置.我们来看看这两个变量的类型。（struct machine_desc）
        kernel 使用struct machine_desc 来描述 machine type.
        在 include/asm-arm/mach/arch.h 中:

        00017: struct machine_desc {
        00018:         /*
        00019:          * Note! The first four elements are used
        00020:          * by assembler code in head-armv.S
        00021:          */
        00022:         unsigned int                nr;                /* architecture number        */
        00023:         unsigned int                phys_io;        /* start of physical io        */
        00024:         unsigned int                io_pg_offst;        /* byte offset for io 
        00025:                                                  * page tabe entry        */
        00026: 
        00027:         const char                *name;                /* architecture name        */
        00028:         unsigned long                boot_params;        /* tagged list                */
        00029: 
        00030:         unsigned int                video_start;        /* start of video RAM        */
        00031:         unsigned int                video_end;        /* end of video RAM        */
        00032: 
        00033:         unsigned int                reserve_lp0 :1;        /* never has lp0        */
        00034:         unsigned int                reserve_lp1 :1;        /* never has lp1        */
        00035:         unsigned int                reserve_lp2 :1;        /* never has lp2        */
        00036:         unsigned int                soft_reboot :1;        /* soft reboot                */
        00037:         void                        (*fixup)(struct machine_desc *,
        00038:                                          struct tag *, char **,
        00039:                                          struct meminfo *);
        00040:         void                        (*map_io)(void);/* IO mapping function        */
        00041:         void                        (*init_irq)(void);
        00042:         struct sys_timer        *timer;                /* system tick timer        */
        00043:         void                        (*init_machine)(void);
        00044: };
        00050: #define MACHINE_START(_type,_name)                        /
        00051: static const struct machine_desc __mach_desc_##_type        /
        00052:  __attribute_used__                                        /
        00053:  __attribute__((__section__(".arch.info.init")) = {        /
        00054:         .nr                = MACH_TYPE_##_type,                /
        00055:         .name                = _name,
        00056: 
        00057: #define MACHINE_END                                /
        00058: };        
        
        内核中,一般使用宏MACHINE_START来定义machine type.
        对于at91, 在 arch/arm/mach-at91rm9200/board-ek.c 中:
        00137: MACHINE_START(AT91RM9200EK, "Atmel AT91RM9200-EK"
        00138:         /* Maintainer: SAN People/Atmel */
        00139:         .phys_io        = AT91_BASE_SYS,
        00140:         .io_pg_offst        = (AT91_VA_BASE_SYS >> 1 & 0xfffc,
        00141:         .boot_params        = AT91_SDRAM_BASE + 0x100,
        00142:         .timer                = &at91rm9200_timer,
        00143:         .map_io                = ek_map_io,
        00144:         .init_irq        = ek_init_irq,
        00145:         .init_machine        = ek_board_init,
        00146: MACHINE_END

其实和上述是差不多的，后面我就不再分析了，就是看看系统对这个arm板子架构是否支持。但是要注意这条语句ldmib r4, {r5, r6, r7}  @ found, get results这里很明显是说，如果找到的匹配的话就把某些信息进行保存，r5、r6、r7分别保存了系统物理内存基址、系统外设物理基址、I/O页偏移量。

    好了，现在来到的难点，也是重点。我们先返回到主程序当中往下接着看：

   teq r7, #0    @ invalid architecture?
   moveq r0, #'a'   @ yes, error 'a'
   beq __error
   bl __create_page_tables

会发现这里又要跳转到__create_page_tables这样的函数里面，这个函数主要做的工作就是创建页表。创建页表是通过函数 __create_page_tables 来实现的. 这里,我们使用的是arm的L1主页表,L1主页表也称为段页表(section page table)，L1 主页表将4 GB 的地址空间分成若干个1 MB的段(section),因此L1页表包含4096个页表项(section entry). 每个页表项是32 bits(4 bytes)，因而L1主页表占用 4096 *4 = 16k的内存空间.
下面我们来分析 __create_page_tables 函数:

         在 arch/arm/kernel/head.S 中:

00206:         .type        __create_page_tables, %function
00207: __create_page_tables:
00208:         pgtbl        r4                                @ page table address
00209: 
00210:         /*
00211:          * Clear the 16K level 1 swapper page table
00212:          */

上面注释明确说明了，建立页表后再清零。
00213:         mov        r0, r4
00214:         mov        r3, #0
00215:         add        r6, r0, #0x4000
00216: 1:     str        r3, [r0], #4
00217:         str        r3, [r0], #4
00218:         str        r3, [r0], #4
00219:         str        r3, [r0], #4
00220:         teq        r0, r6
00221:         bne        1b

这里要注意的是，r4保存着页表的物理基地址，从0x4000开始往后16KB都被清零了，这里将被用来存放一级页表的。
00222: 
00223:         ldr        r7, [r10, #PROCINFO_MM_MMUFLAGS] @ mm_mmuflags
00224: 
00225:         /*
00226:          * Create identity mapping for first MB of kernel to
00227:          * cater for the MMU enable.  This identity mapping
00228:          * will be removed by paging_init().  We use our current program
00229:          * counter to determine corresponding section base address.
00230:          */

上面注释说了，我们先建立1MB的映射，为了可以使能MMU，其实映射的建立就是往刚才的上述的16KB的空间里的某个单元添东西。231这个代码取出了当前指令所在的内存段，232这个代码给R3附上了这个段将来被映射所对应物理地址，最后把这个地址存放在16KB这个空间中对应的单元（每个1MB的段都会对应一个固定的单元）。这里的虚拟地址和物理地址的映射关系是一一对应的。
00231:         mov        r6, pc, lsr #20                        @ start of kernel section
00232:         orr        r3, r7, r6, lsl #20                @ flags + kernel base
00233:         str        r3, [r4, r6, lsl #2]                @ identity mapping
00234: 
/*
  * Now setup the pagetables for our kernel direct
  * mapped region.  We round TEXTADDR down to the
  * nearest megabyte boundary.  It is assumed that
  * the kernel fits within 4 contigous 1MB sections.
  */
add r0, r4,  #(TEXTADDR & 0xff000000) >> 18 @ start of kernel
str r3, [r0, #(TEXTADDR & 0x00f00000) >> 18]!
add r3, r3, #1 << 20
str r3, [r0, #4]!   @ KERNEL + 1MB
add r3, r3, #1 << 20
str r3, [r0, #4]!   @ KERNEL + 2MB
add r3, r3, #1 << 20
str r3, [r0, #4]   @ KERNEL + 3MB
由注释可以看出这段程序的功能就是建立内核开始连续4MB的物理地址到虚拟地址的映射关系，TEXTADDR=0xc0008000这个是内核存放的虚拟地址，前两句的功能就是求出内核虚拟地址所对应的段，把对应的段保存在r0里面。通过r0可以求得页表里面的哪个单元。这样就可以把当前代码所在段的后续段的物理地址都一次保存在这个单元和这个单元后的连续单元里面。

add r0, r4, #VIRT_OFFSET >> 18
add r2, r5, r8
str r2, [r0]

VIRT_OFFSET=PAGE_OFFSET=0xc0000000是系统虚拟地址的起始地址。这三条语句的功能就是建立这个虚拟地址到物理地址的映射。先找到这个虚拟地址所对应的段，接着就可以获得这个段在一级页表中对应的单元，r5就是系统物理内存基地址，这样这个单元里保存的就是这个基地址。简单来说就是建立了系统内存的起始地址的映射。

  到目前为止，一共映射了建立了6段的映射，起始这里的六段虚拟地址只是映射了4段物理地址，也就是说有3段虚拟地址映射1段物理地址，是重映射。这里是为什么，我就不多说了。为什么这样映射，后面会提到。关于#ifdef的内容我们忽略，这个和系统配置和调试有关系。

   当 __create_page_tables 返回之后此时,一些特定寄存器的值如下所示:
    r4 = pgtbl              (page table 的物理基地址)

    r10 = procinfo          (struct proc_info_list的基地址)

adr lr, __turn_mmu_on  @ return (PIC) address
add pc, r10, #12

可以看出这里为pc赋值，加上#12后就可以访问到__cpu_flush这个变量了，之前我们在__lookup_processor_type里面就给这个变量附上了值了，就是每个处理器的__xxx_setup()。这样我们就会跳转到这个函数来了。在我们需要在开启mmu之前,做一些必须的工作:清除ICache, 清除 DCache, 清除 Writebuffer, 清除TLB等.这些一般是通过cp15协处理器来实现的,并且是平台相关的. 这就是，__cpu_flush 需要做的工作.

下面我们来分析函数 __arm926_setup
        
        在 arch/arm/mm/proc-arm926.S 中:
00391:         .type        __arm926_setup, #function
00392: __arm926_setup:
00393:         mov        r0, #0
00394:         mcr        p15, 0, r0, c7, c7                @  清除(invalidate)Instruction Cache 和 Data Cache.
00395:         mcr        p15, 0, r0, c7, c10, 4                @ 清除(drain) Write Buffer.

如果有配置了MMU,则需要清除(invalidate)Instruction TLB 和Data TLB
接下来,是对控制寄存器c1进行配置,请参考 ARM926 TRM.
00396: #ifdef CONFIG_MMU
00397:         mcr        p15, 0, r0, c8, c7                @ invalidate I,D TLBs on v4
00398: #endif
00399: 
00400:

如果配置了Data Cache使用writethrough方式, 需要关掉write-back.
00401: #ifdef CONFIG_CPU_DCACHE_WRITETHROUGH
00402:         mov        r0, #4                                @ disable write-back on caches explicitly
00403:         mcr        p15, 7, r0, c15, c0, 0
00404: #endif 
00405: 
00406:         adr        r5, arm926_crval                @取arm926_crval的地址到r5中, arm926_crval 在第424行

这里我们需要看一下424和425行,其中用到了宏crval,crval是在 arch/arm/mm/proc-macro.S 中:

        00053:         .macro        crval, clear, mmuset, ucset
        00054: #ifdef CONFIG_MMU
        00055:         .word        /clear
        00056:         .word        /mmuset
        00057: #else
        00058:         .word        /clear
        00059:         .word        /ucset
        00060: #endif
        00061:         .endm

配合425行,我们可以看出,首先在arm926_crval的地址处存放了clear的值,然后接下来的地址存放了mmuset的值(对于配置了MMU的情况) 。所以,在407行中,我们将clear和mmuset的值分别存到了r5, r6中
00407:         ldmia        r5, {r5, r6}
00408:         mrc        p15, 0, r0, c1, c0                @ 获得控制寄存器c1的值
00409:         bic        r0, r0, r5                              @将r0中的 clear (r5) 对应的位都清除掉
00410:         orr        r0, r0, r6                              @设置r0中 mmuset (r6) 对应的位
00411: #ifdef CONFIG_CPU_CACHE_ROUND_ROBIN
00412:         orr        r0, r0, #0x4000                        @ .1.. .... .... ....
00413: #endif
00414:         mov        pc, lr                                     @取lr的值到pc中.
00415:         .size        __arm926_setup, . - __arm926_setup
00416: 
00417:         /*
00418:          *  R
00419:          * .RVI ZFRS BLDP WCAM
00420:          * .011 0001 ..11 0101
00421:          * 
00422:          */
00423:         .type        arm926_crval, #object
00424: arm926_crval:
00425:         crval        clear=0x00007f3f, mmuset=0x00003135, ucset=0x00001134

由于在跳转到setup函数之前，我们就把__turn_mmu_on标号保存到lr当中了，注意到414行代码。接下来就是跳转到__turn_mmu_on这个函数，我们来看看这个函数具体干些什么哦。

.align 5
.type __turn_mmu_on, %function
__turn_mmu_on:
ldr lr, __switch_data
#ifdef CONFIG_ALIGNMENT_TRAP（查看系统是否要求地址对齐检测）
orr r0, r0, #2   @ ...........A. @如果开启了这项功能的话，就使r0得bit1置1.
#endif
mcr p15, 0, r0, c1, c0, 0  @ 将r0写入cp15的c1寄存器当中，使能mmu和配置上述功能。
mrc p15, 0, r3, c0, c0, 0  @ 然后将cp15得c0寄存器，即主标识符寄存器的值读到r3里。与r9里的值相同。
mov r3, r3
mov r3, r3
mov pc, lr

接下来又跳转到__switch_data处，我们来看看它的代码：

00014:         .type        __switch_data, %object
00015: __switch_data:
00016:         .long        __mmap_switched
00017:         .long        __data_loc                        @ r4
00018:         .long        __data_start                        @ r5
00019:         .long        __bss_start                        @ r6
00020:         .long        _end                                @ r7
00021:         .long        processor_id                        @ r4
00022:         .long        __machine_arch_type                @ r5
00023:         .long        cr_alignment                        @ r6
00024:         .long        init_thread_union + THREAD_START_SP @ sp
第16 - 24行: 定义了一些地址,例如第16行存储的是 __mmap_switched 的地址, 第17行存储的是 __data_loc 的地址 ......可以看出它直接跳转到__mmap_switched，我们来看看它的代码：

.align 5
__mmap_switched:
adr r2, __switch_data + 4    @ 取 __switch_data + 4的地址到r2. 从上文可以看到这个地址就是第17行的地址.
ldmia r2, {r2, r3, r4, r5, r6, r7, r8, sp}  @依次取出从第17行到第20行的地址,存储到r2,r3,r4, r5, r6, r7,r8,sp 中.
        对照上文,我们可以得知: 
                r2 - __data_loc    @数据存放的位置
                r3 - __data_start  @数据存放的开始位置
                r4 - __bss_start    @bss的开始位置
                r5 - _end                @bss的结束位置，也就是内核结束位置

                r6 - processor_id

                r7 - __machine_arch_type

                r8 - cr_alignment

                sp - init_thread_union+THREAD_START_SP(init_thread_union+8912)也就是在系统创建第一个任务之前，将init_thread_union.init_thread_info作为系统启动过程的线程信息结构变量。

    cmp r2, r3    @比较 __data_loc 和 __data_start，如果不等，将__data_loc得数据复制到__data_start处。

1: cmpne r3, r4
    ldrne fp, [r2], #4
    strne fp, [r3], #4
    bne 1b

    mov fp, #0    @ 将 BSS之间的内存清零。 
1: cmp r4, r5
    strcc fp, [r4],#4
    bcc 1b

    str r9, [r6]   @ 赋给全局变量processor_id

    str r1, [r7]   @ 赋给全局变量__machine_arch_type

    bic r2, r0, #2   @ 将保存在r0的cp15德c1寄存器的值的bit1清零，再赋给r2。
    stmia r8, {r0, r2}   @ 很明显cr_alignment全局变量里面存放着r0，cr_no_alignment全局变量里面存放着r2的值。

    b start_kernel
好了，这样就全部讲完了，总结为以下：


        1. 确定 processor type                        (75 - 78行)
        2. 确定 machine type                        (79 - 81行)
        3. 创建页表                                (82行)     
        4. 调用平台特定的__cpu_flush函数        (在struct proc_info_list中)        (94 行)                            
        5. 开启mmu                                (93行)
        6. 切换数据                                 (91行)
        
        最终跳转到start_kernel                        (在__switch_data的结束的时候,调用了 b        start_kernel)
