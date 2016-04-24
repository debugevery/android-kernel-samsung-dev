 �ڷ�����δ���֮ǰ�����Ǳ������ҵ�����������λ�ã�Ҳ����Bootloader����linuxʱ����ת���ĵ�ַ���ں�һ�㱻ѹ���󱣴浽FLASH�ϵģ���Bootloader����Linux֮ǰ�����Ƚ�ѹ���ںˣ������ں˽�ѹ�����������arch/arm/boot/compressed������Ĵ��룬����Ͳ�ϸ���ˡ�

   �ڽ���Linux������֮ǰ��Bootloader��ִ��Ӱ��CPU��״̬����״̬һ��Ϊ��

        1. CPU���봦��SVC(supervisor)ģʽ,����IRQ��FIQ�ж϶��ǽ�ֹ��;
        2. MMU(�ڴ����Ԫ)�����ǹرյ�, ��ʱ�����ַ�������ַ;
        3. ����cache(Data cache)�����ǹرյ�
        4. ָ��cache(Instruction cache)�����Ǵ򿪵�,Ҳ�����ǹرյ�,���û��ǿ��Ҫ��;
        5. CPU ͨ�üĴ���0 (r0)������ 0;
        6. CPU ͨ�üĴ���1 (r1)������ ARM Linux machine type���ں���Ὣ��machine type��

        7. CPU ͨ�üĴ���2 (r2) ������ kernel parameter list �������ַ(parameter list ����boot loader���ݸ�kernel,���������豸��Ϣ���Ե��б�

   Linux������ڵ�ַ�뿴�ļ�arch/arm/kernel/head.s�����������������ļ�����Ĵ���ɡ�

    __INIT
.type stext, #function
ENTRY(stext)
mov r12, r0
mov r0, #PSR_F_BIT | PSR_I_BIT | MODE_SVC @ make sure svc mode
msr cpsr_c, r0   @ and all irqs disabled
bl __lookup_processor_type

����������һ��__lookup_processor_type������ĺ����ɣ��κ����Ļ����ڱ��ļ��е��С�

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

r5�����˱��2�ĵ�ַ�����žͰ�__proc_info_end��2b�ĵ�ַ��Ӧ�ĸ���r7,r9,r10����������������������þ���ʵ�ֵ�ַ��ת��������r10�ʹ����__proc_info_start��r7�����__proc_info_end����ʵ��������һ��ȫ�ֱ����ģ�arch/arm/kernel/vmlinux.lds.s�������¶���ģ�

   __proc_info_begin = .;
        *(.proc.info)
   __proc_info_end = .;

��ʵ���Կ��������и�����ģ����������ļ��е�.proc.info�ζ��������������ģ��������������Ҹղ�˵������ȫ�ֱ����Ľṹ�塣

  �� include/asm-arm/procinfo.h ��:
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
����������һ�������ļ��е�.proc.info�Σ��������£�

��arch/arm/mm/proc-arm926.S ��:
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

��ʵ���ǿ��Կ�������֮�����ϵ������˵������arch/arm/kernel/vmlinux.lds.s�ļ�����ʵ���Ƕ�struct proc_info_list �ṹ��ȫ�ֱ��� __proc_info_begin ��__proc_info_end �ĳ�ʼ�������Ƕ��塣����˵ÿ���ļ�������һ�����Ǽ�����ͬ�Ķ��壬�������ļ����кܶ����ÿ���������һ������������Ϣ����������Ҫͨ����Щ��Ϣ���鿴�Ƿ�������ϵͳ֧�ֵġ�

   ���ڻص����ǸղŵĴ���λ�ã�

   mrc p15, 0, r9, c0, c0  @ get processor id��r9�������Ŵ�Ӳ���ϻ�õĴ������ͺš�

   ldmia r10, {r5, r6, r8}  @ value, mask, mmuflags�ղ�������Ĵ���������˽⵽��r10�����ϵͳ֧�ֵĴ�������Ϣ�Ŀ�ʼλ�ã�ÿ�������������Ӧһ����������Ϣ�������Ѿ�֪����Щ��Ϣ������������struct proc_info_list �ṹ���������r10ָ���һ����r5,r6,r8��ŵ����ݾ��Ǵ�����ID�š�������ID�Ŷ�Ӧ�������֡��ڴ����Ԫ�ĵ�һ�������������ֶΡ���Щ����ǰ���Ǹ������ĳ�Ա���������Ժ�Ϳ��Կ����ˡ�

   and r6, r6, r9   @ mask wanted bits
   teq r5, r6

����Ͷ�ǰ������Ա���������ã����Ǻ����������룬�����ID����Ƚϡ�

  moveq pc, lr
  add r10, r10, #PROC_INFO_SZ  @ sizeof(proc_info_list)
  cmp r10, r7
  blt 1b
  mov r10, #0    @ unknown processor
  mov pc, lr

����Ĵ������ѭ�����бȽϣ�֪���ҵ���ϵͳƥ��Ĵ������������ƥ���ˣ���˵�����ϵͳ��֧�������Ĵ����������غ��ֱ����ת������λ�õġ�һ�¾��Ƿ��غ�Ĵ��롣

  teq r10, #0    @ invalid processor?
  moveq r0, #'p'   @ yes, error 'p'
  beq __error
  bl __lookup_architecture_type

�ܼ򵥣����r10Ϊ0����˵��û���ҵ�ƥ��ģ�����ҵ��Ļ���r10�������֮ƥ��Ĵ�������Ϣ����������Ҫ��ת__lookup_architecture_type�������������ⲿ�ִ��룺

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
��ʵ��ϸ�������ᷢ�ֺ������Ĵ����࣬ͬ��r4������������2�ĵ�ַ����r6,r7������ __arch_info_begin��__arch_info_end�����ĵ�ַ�������������ǵ�ַת��������ȷ�Ϻ�ĵ�ַ������r7,r4���档��������������������������ʲô��

__arch_info_begin �� __arch_info_end���� arch/arm/kernel/vmlinux.lds.S��:

        00034:                __arch_info_begin = .;
        00035:                        *(.arch.info.init)
        00036:                __arch_info_end = .;
�����е���˼��: __arch_info_begin ��λ����,���������ļ��е� ".arch.info.init" �ε�����,Ȼ��������� __arch_info_end ��λ��.�������������������������͡���struct machine_desc��
        kernel ʹ��struct machine_desc ������ machine type.
        �� include/asm-arm/mach/arch.h ��:

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
        
        �ں���,һ��ʹ�ú�MACHINE_START������machine type.
        ����at91, �� arch/arm/mach-at91rm9200/board-ek.c ��:
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

��ʵ�������ǲ��ģ������ҾͲ��ٷ����ˣ����ǿ���ϵͳ�����arm���Ӽܹ��Ƿ�֧�֡�����Ҫע���������ldmib r4, {r5, r6, r7}  @ found, get results�����������˵������ҵ���ƥ��Ļ��Ͱ�ĳЩ��Ϣ���б��棬r5��r6��r7�ֱ𱣴���ϵͳ�����ڴ��ַ��ϵͳ���������ַ��I/Oҳƫ������

    ���ˣ������������ѵ㣬Ҳ���ص㡣�����ȷ��ص������������½��ſ���

   teq r7, #0    @ invalid architecture?
   moveq r0, #'a'   @ yes, error 'a'
   beq __error
   bl __create_page_tables

�ᷢ��������Ҫ��ת��__create_page_tables�����ĺ������棬���������Ҫ���Ĺ������Ǵ���ҳ������ҳ����ͨ������ __create_page_tables ��ʵ�ֵ�. ����,����ʹ�õ���arm��L1��ҳ��,L1��ҳ��Ҳ��Ϊ��ҳ��(section page table)��L1 ��ҳ��4 GB �ĵ�ַ�ռ�ֳ����ɸ�1 MB�Ķ�(section),���L1ҳ�����4096��ҳ����(section entry). ÿ��ҳ������32 bits(4 bytes)�����L1��ҳ��ռ�� 4096 *4 = 16k���ڴ�ռ�.
�������������� __create_page_tables ����:

         �� arch/arm/kernel/head.S ��:

00206:         .type        __create_page_tables, %function
00207: __create_page_tables:
00208:         pgtbl        r4                                @ page table address
00209: 
00210:         /*
00211:          * Clear the 16K level 1 swapper page table
00212:          */

����ע����ȷ˵���ˣ�����ҳ��������㡣
00213:         mov        r0, r4
00214:         mov        r3, #0
00215:         add        r6, r0, #0x4000
00216: 1:     str        r3, [r0], #4
00217:         str        r3, [r0], #4
00218:         str        r3, [r0], #4
00219:         str        r3, [r0], #4
00220:         teq        r0, r6
00221:         bne        1b

����Ҫע����ǣ�r4������ҳ����������ַ����0x4000��ʼ����16KB���������ˣ����ｫ���������һ��ҳ��ġ�
00222: 
00223:         ldr        r7, [r10, #PROCINFO_MM_MMUFLAGS] @ mm_mmuflags
00224: 
00225:         /*
00226:          * Create identity mapping for first MB of kernel to
00227:          * cater for the MMU enable.  This identity mapping
00228:          * will be removed by paging_init().  We use our current program
00229:          * counter to determine corresponding section base address.
00230:          */

����ע��˵�ˣ������Ƚ���1MB��ӳ�䣬Ϊ�˿���ʹ��MMU����ʵӳ��Ľ����������ղŵ�������16KB�Ŀռ����ĳ����Ԫ������231�������ȡ���˵�ǰָ�����ڵ��ڴ�Σ�232��������R3����������ν�����ӳ������Ӧ�����ַ�����������ַ�����16KB����ռ��ж�Ӧ�ĵ�Ԫ��ÿ��1MB�Ķζ����Ӧһ���̶��ĵ�Ԫ��������������ַ�������ַ��ӳ���ϵ��һһ��Ӧ�ġ�
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
��ע�Ϳ��Կ�����γ���Ĺ��ܾ��ǽ����ں˿�ʼ����4MB�������ַ�������ַ��ӳ���ϵ��TEXTADDR=0xc0008000������ں˴�ŵ������ַ��ǰ����Ĺ��ܾ�������ں������ַ����Ӧ�ĶΣ��Ѷ�Ӧ�Ķα�����r0���档ͨ��r0�������ҳ��������ĸ���Ԫ�������Ϳ��԰ѵ�ǰ�������ڶεĺ����ε������ַ��һ�α����������Ԫ�������Ԫ���������Ԫ���档

add r0, r4, #VIRT_OFFSET >> 18
add r2, r5, r8
str r2, [r0]

VIRT_OFFSET=PAGE_OFFSET=0xc0000000��ϵͳ�����ַ����ʼ��ַ�����������Ĺ��ܾ��ǽ�����������ַ�������ַ��ӳ�䡣���ҵ���������ַ����Ӧ�ĶΣ����žͿ��Ի���������һ��ҳ���ж�Ӧ�ĵ�Ԫ��r5����ϵͳ�����ڴ����ַ�����������Ԫ�ﱣ��ľ����������ַ������˵���ǽ�����ϵͳ�ڴ����ʼ��ַ��ӳ�䡣

  ��ĿǰΪֹ��һ��ӳ���˽�����6�ε�ӳ�䣬��ʼ��������������ַֻ��ӳ����4�������ַ��Ҳ����˵��3�������ַӳ��1�������ַ������ӳ�䡣������Ϊʲô���ҾͲ���˵�ˡ�Ϊʲô����ӳ�䣬������ᵽ������#ifdef���������Ǻ��ԣ������ϵͳ���ú͵����й�ϵ��

   �� __create_page_tables ����֮���ʱ,һЩ�ض��Ĵ�����ֵ������ʾ:
    r4 = pgtbl              (page table ���������ַ)

    r10 = procinfo          (struct proc_info_list�Ļ���ַ)

adr lr, __turn_mmu_on  @ return (PIC) address
add pc, r10, #12

���Կ�������Ϊpc��ֵ������#12��Ϳ��Է��ʵ�__cpu_flush��������ˣ�֮ǰ������__lookup_processor_type����͸��������������ֵ�ˣ�����ÿ����������__xxx_setup()���������Ǿͻ���ת������������ˡ���������Ҫ�ڿ���mmu֮ǰ,��һЩ����Ĺ���:���ICache, ��� DCache, ��� Writebuffer, ���TLB��.��Щһ����ͨ��cp15Э��������ʵ�ֵ�,������ƽ̨��ص�. ����ǣ�__cpu_flush ��Ҫ���Ĺ���.

������������������ __arm926_setup
        
        �� arch/arm/mm/proc-arm926.S ��:
00391:         .type        __arm926_setup, #function
00392: __arm926_setup:
00393:         mov        r0, #0
00394:         mcr        p15, 0, r0, c7, c7                @  ���(invalidate)Instruction Cache �� Data Cache.
00395:         mcr        p15, 0, r0, c7, c10, 4                @ ���(drain) Write Buffer.

�����������MMU,����Ҫ���(invalidate)Instruction TLB ��Data TLB
������,�ǶԿ��ƼĴ���c1��������,��ο� ARM926 TRM.
00396: #ifdef CONFIG_MMU
00397:         mcr        p15, 0, r0, c8, c7                @ invalidate I,D TLBs on v4
00398: #endif
00399: 
00400:

���������Data Cacheʹ��writethrough��ʽ, ��Ҫ�ص�write-back.
00401: #ifdef CONFIG_CPU_DCACHE_WRITETHROUGH
00402:         mov        r0, #4                                @ disable write-back on caches explicitly
00403:         mcr        p15, 7, r0, c15, c0, 0
00404: #endif 
00405: 
00406:         adr        r5, arm926_crval                @ȡarm926_crval�ĵ�ַ��r5��, arm926_crval �ڵ�424��

����������Ҫ��һ��424��425��,�����õ��˺�crval,crval���� arch/arm/mm/proc-macro.S ��:

        00053:         .macro        crval, clear, mmuset, ucset
        00054: #ifdef CONFIG_MMU
        00055:         .word        /clear
        00056:         .word        /mmuset
        00057: #else
        00058:         .word        /clear
        00059:         .word        /ucset
        00060: #endif
        00061:         .endm

���425��,���ǿ��Կ���,������arm926_crval�ĵ�ַ�������clear��ֵ,Ȼ��������ĵ�ַ�����mmuset��ֵ(����������MMU�����) ������,��407����,���ǽ�clear��mmuset��ֵ�ֱ�浽��r5, r6��
00407:         ldmia        r5, {r5, r6}
00408:         mrc        p15, 0, r0, c1, c0                @ ��ÿ��ƼĴ���c1��ֵ
00409:         bic        r0, r0, r5                              @��r0�е� clear (r5) ��Ӧ��λ�������
00410:         orr        r0, r0, r6                              @����r0�� mmuset (r6) ��Ӧ��λ
00411: #ifdef CONFIG_CPU_CACHE_ROUND_ROBIN
00412:         orr        r0, r0, #0x4000                        @ .1.. .... .... ....
00413: #endif
00414:         mov        pc, lr                                     @ȡlr��ֵ��pc��.
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

��������ת��setup����֮ǰ�����ǾͰ�__turn_mmu_on��ű��浽lr�����ˣ�ע�⵽414�д��롣������������ת��__turn_mmu_on�������������������������������ЩʲôŶ��

.align 5
.type __turn_mmu_on, %function
__turn_mmu_on:
ldr lr, __switch_data
#ifdef CONFIG_ALIGNMENT_TRAP���鿴ϵͳ�Ƿ�Ҫ���ַ�����⣩
orr r0, r0, #2   @ ...........A. @�������������ܵĻ�����ʹr0��bit1��1.
#endif
mcr p15, 0, r0, c1, c0, 0  @ ��r0д��cp15��c1�Ĵ������У�ʹ��mmu�������������ܡ�
mrc p15, 0, r3, c0, c0, 0  @ Ȼ��cp15��c0�Ĵ�����������ʶ���Ĵ�����ֵ����r3���r9���ֵ��ͬ��
mov r3, r3
mov r3, r3
mov pc, lr

����������ת��__switch_data�����������������Ĵ��룺

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
��16 - 24��: ������һЩ��ַ,�����16�д洢���� __mmap_switched �ĵ�ַ, ��17�д洢���� __data_loc �ĵ�ַ ......���Կ�����ֱ����ת��__mmap_switched���������������Ĵ��룺

.align 5
__mmap_switched:
adr r2, __switch_data + 4    @ ȡ __switch_data + 4�ĵ�ַ��r2. �����Ŀ��Կ��������ַ���ǵ�17�еĵ�ַ.
ldmia r2, {r2, r3, r4, r5, r6, r7, r8, sp}  @����ȡ���ӵ�17�е���20�еĵ�ַ,�洢��r2,r3,r4, r5, r6, r7,r8,sp ��.
        ��������,���ǿ��Ե�֪: 
                r2 - __data_loc    @���ݴ�ŵ�λ��
                r3 - __data_start  @���ݴ�ŵĿ�ʼλ��
                r4 - __bss_start    @bss�Ŀ�ʼλ��
                r5 - _end                @bss�Ľ���λ�ã�Ҳ�����ں˽���λ��

                r6 - processor_id

                r7 - __machine_arch_type

                r8 - cr_alignment

                sp - init_thread_union+THREAD_START_SP(init_thread_union+8912)Ҳ������ϵͳ������һ������֮ǰ����init_thread_union.init_thread_info��Ϊϵͳ�������̵��߳���Ϣ�ṹ������

    cmp r2, r3    @�Ƚ� __data_loc �� __data_start��������ȣ���__data_loc�����ݸ��Ƶ�__data_start����

1: cmpne r3, r4
    ldrne fp, [r2], #4
    strne fp, [r3], #4
    bne 1b

    mov fp, #0    @ �� BSS֮����ڴ����㡣 
1: cmp r4, r5
    strcc fp, [r4],#4
    bcc 1b

    str r9, [r6]   @ ����ȫ�ֱ���processor_id

    str r1, [r7]   @ ����ȫ�ֱ���__machine_arch_type

    bic r2, r0, #2   @ ��������r0��cp15��c1�Ĵ�����ֵ��bit1���㣬�ٸ���r2��
    stmia r8, {r0, r2}   @ ������cr_alignmentȫ�ֱ�����������r0��cr_no_alignmentȫ�ֱ�����������r2��ֵ��

    b start_kernel
���ˣ�������ȫ�������ˣ��ܽ�Ϊ���£�


        1. ȷ�� processor type                        (75 - 78��)
        2. ȷ�� machine type                        (79 - 81��)
        3. ����ҳ��                                (82��)     
        4. ����ƽ̨�ض���__cpu_flush����        (��struct proc_info_list��)        (94 ��)                            
        5. ����mmu                                (93��)
        6. �л�����                                 (91��)
        
        ������ת��start_kernel                        (��__switch_data�Ľ�����ʱ��,������ b        start_kernel)
