�ں���ڵ�ַȷ����ش������2011��03��03�� ������ 16:331. Bootloader���ں˽�ѹ 
2. �ں�������ʽ���� 
3. �ں�������ַ��ȷ�� 
4. arch/armnommu/kernel/head-armv.S���� 
5. start_kernel()��������1. Bootloader���ں˽�ѹ 
Bootloader���ں˼��ص��ڴ��У��趨һЩ�Ĵ�����Ȼ�󽫿���Ȩ�����ںˣ��ù����У��ر�MMU���ܡ�ͨ�����ں˶�����ѹ���ķ�ʽ��ţ���zImage�����������ֽ�ѹ������ 
ʹ���ں��Խ�ѹ���� 
arch/arm/boot/compressed/head.S��arch/arm/boot/compressed/head-xxxxx.S 
arch/arm/boot/compressed/misc.c 
��Bootloader�����ӽ�ѹ���ܡ� 
ʹ�ø÷���ʱ�ں˲���Ҫ�����Խ�ѹ���ܣ���ʹ��Bootloader�еĽ�ѹ��������ں��Խ�ѹ�����乤���������ں��Խ�ѹ�������ƣ�Bootloader��ѹ����ʽ���ں˽�ѹ���ڴ��У�Ȼ����ת���ں���ڴ���ʼִ�С�2. �����ں�������ʽ���� 
XIP (EXECUTE IN PLACE) ��ֱָ�ӴӴ�Ŵ����λ�����������С� 
2.1 ��ѹ������XIP 
��XIP��ʽ��ָ������֮ǰ��Դ�������ض�λ�������͵��ں��Է�ѹ����ʽ�����Flash�У�����ʱ��Bootloader���ص��ڴ�����С� 
2.2 ��ѹ����XIP 
�� ���͵��ں��Է�ѹ����ʽ�����ROM/Flash�У�����Ҫ���ص��ڴ�������У�Bootloaderֱ����ת�����ŵ�ִַ�С�Data�θ��ƺ�BSS ������Ĺ������ں��Լ���ɡ�����������ʽ�������ڴ�ռ����޵�ϵͳ�У����⣬������ROM/Flash�����е��ٶ���Խ����� 
2.3 RAM�Խ�ѹ 
ѹ ����ʽ���ں��ɿ�ͷһ���Խ�ѹ�����ѹ���ں�������ɣ�������ѹ����ʽ��ţ��ں�ֻ���Է�XIP��ʽ���С�RAM�Խ�ѹ�������£�ѹ���ں˴���� ROM/Flash�У�Bootloader��������ص��ڴ��е���ʱ�ռ䣬Ȼ����ת��ѹ���ں���ڵ�ִַ���Խ�ѹ���룬�ں˱���ѹ�����յ�Ŀ�ĵ�ַȻ�� ���С�ѹ���ں���ռ�ݵ���ʱ�ռ����Linux�������á����ַ�ʽ���ں���Ƕ��ʽ��Ʒ�н�Ϊ������ 
2.4 ROM�Խ�ѹ 
��ѹ���� ��Ҳ�ܹ���XIP�ķ�ʽ��ROM/Flash�����С�ROM�Խ�ѹ�������£�ѹ���ں˴����ROM/Flash�У�����Ҫ���ص��ڴ�������У� Bootloaderֱ����ת�����ŵ�ִַ�����Խ�ѹ���룬��ѹ���ں˽�ѹ�����յ�Ŀ�ĵ�ַ�����С�ROM�Խ�ѹ��ʽ��ŵ��ں˽�ѹ���ٶ���������Ҳ�� �ܽ�ʡ�ڴ�ռ䡣3. �ں�������ַ��ȷ�� 
�ں��Խ�ѹ��ʽ 
Head.S/head-XXX.S����ں˽�ѹ���׵�ַZREALADDR��Ȼ���ѹ�ںˣ����ѽ�ѹ����ں˷���ZREALADDR��λ���ϣ������ת��ZREALADDR��ַ�ϣ���ʼ�������ں�������arch/armnommu/boot/Makefile�� ����ZRELADDR�� ZTEXTADDR��ZTEXTADDR���Խ�ѹ�������ʼ��ַ��������ڴ������ںˣ�����Ϊ0���ɣ������Rom/Flash������������ ZTEXTADDRΪ��Ӧ��ֵ��ZRELADDR���ں˽�ѹ�����ִ�е�ַ�� 
arch/armnommu/boot/compressed/vmlinux.ld,����LOAD_ADDR��TEXT_START�� 
arch/armnommu/boot/compressed/Makefile, ͨ������һ�У� 
SEDFLAGS = s/TEXT_START/$(ZTEXTADDR)/;s/LOAD_ADDR/$(ZRELADDR)/; 
ʹ��TEXT_START = ZTEXTADDR��LOAD_ADDR = ZRELADDR��˵���� 
ִ ����decompress_kernel������,��������head.S/head-XXX.S��,����ѹ��֮���kernel��ʼ��ַ�Ƿ������ kernel image�������,beq call_kernel,ִ�н�ѹ���kernel�������ѹ��֮���kernel��ʼ��ַ���ǽ�����kernel image,��ִ��relocate,���俽����������kernel image�ĵط�,Ȼ����ת,ִ�н�ѹ���kernel��Bootloader��ѹ��ʽ 
Bootloader�ѽ�ѹ����ں˷����ڴ��TEXTADDRλ���ϣ�Ȼ����ת��TEXTADDRλ���ϣ���ʼ�ں������� 
arch/armnommu/Makefile��һ������TEXTADDRΪPAGE_OFF+0x8000���綨��Ϊ0x00008000, 0xC0008000�ȡ� 
arch/armnommu/vmlinux.lds������TEXTADDR4. arch/armnommu/kernel/head-armv.S 
�� �ļ����ں�����ִ�е�һ���ļ��������ں����ENTRY(stext)��start_kernel��ĳ�ʼ�����룬��Ҫ�����Ǽ��CPU ID��Architecture Type����ʼ��BSS�Ȳ�����������start_kernel��������ִ��ǰ��������Ӧ��������״̬�� 
r0 - should be 0 
r1 - unique architecture number 
MMU - off 
I-cache - on or off 
D-cache �C off/* ����Դ������� */ 
/* �ں���ڵ� */ 
ENTRY(stext) 
/* ����״̬����ֹFIQ��IRQ���趨SVCģʽ */ 
mov r0, #F_BIT | I_BIT | MODE_SVC@ make sure svc mode 
/* �õ�ǰ����״̬�Ĵ��� */ 
msr cpsr_c, r0 @ and all irqs disabled 
/* �ж�CPU���ͣ��������е�CPU IDֵ��Linux����֧�ֵ�IDֵ�Ƿ�֧�� */ 
bl __lookup_processor_type 
/* ����__error */ 
teq r10, #0 @ invalid processor? 
moveq r0, #''p'' @ yes, error ''p'' 
beq __error 
/* �ж���ϵ���ͣ��鿴R1�Ĵ�����Architecture Typeֵ�Ƿ�֧�� */ 
bl __lookup_architecture_type 
/* ��֧�֣��������� */ 
teq r7, #0 @ invalid architecture? 
moveq r0, #''a'' @ yes, error ''a'' 
beq __error 
/* ��������ҳ�� */ 
bl __create_page_tables 
adr lr, __ret @ return address 
add pc, r10, #12 @ initialise processor 
/* ��ת��start_kernel���� */ 
b start_kernel__lookup_processor_type �����������оƬ��ID��proc.info��ȡproc_info_list�ṹ��proc_info_list�ṹ������include/asm- armnommu/proginfo.h�У��ýṹ�����ݶ�����arch/armnommu/mm/proc-arm*.S�ļ��У�ARM7TDMIϵ�� оƬ��proc_info_list���ݶ�����arch/armnommu/mm/proc-arm6,7.S�ļ��С����� __lookup_architecture_type��arch.info��ȡmachine_desc�ṹ��machine_desc�ṹ������ include/asm-armnommu/mach/arch.h�У���Բ�ͬarch�����ݶ�����arch/armnommu/mach- */arch.c�ļ��С� 
���������֪��processor_type��architecture_type,����ֱ�Ӷ���Ӧ�Ĵ������и�ֵ��5. start_kernel()�������� 
�����start_kernel()����������غ������з����� 
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
kernel_flag ��һ���ں˴������������н��̶�ͨ�����������ʵ�����ں�̬��Ǩ�ơ�ֻ�л��������������Ĵ��������Խ����ںˣ����жϴ������ȡ����κ�һ�� lock_kernel��unlock_kernel���������������һ������ռ��CPU�����̵�lock_depth��Ա��ʼ��Ϊ-1���� kerenl/fork.c�ļ������á�����С��0ʱ����Ϊ -1�������̲�ӵ���ں����������ڻ����0ʱ�����̵õ��ں�����5.2 setup_arch() 
setup_arch()��������ϵ��صĳ�ʼ�������������Ķ�����arch/armnommu/kernel/setup.c�ļ��У���Ҫ�漰������Ҫ���������롣 
5.2.1 setup_processor() 
�ú�����Ҫͨ�� 
for (list = &__proc_info_begin; list < &__proc_info_end ; list++) 
if ((processor_id & list->cpu_mask) == list->cpu_val) 
break; 
����һ��ѭ������.proc.info����Ѱ��ƥ���processor_id��processor_id��head_armv.S�ļ� 
�����á�5.2.2 setup_architecture(machine_arch_type) 
�ú��������ϵ�ṹ����Ϣ������mach-xxx/arch.c �ļ��ж����machine�ṹ���ָ�룬�����������ݣ� 
MACHINE_START (xxx, ��xxx��) 
MAINTAINER ("xxx") 
BOOT_MEM (xxx, xxx, xxx) 
FIXUP (xxx) 
MAPIO (xxx) 
INITIRQ (xxx) 
MACHINE_END5.2.3�ڴ����ô��� 
if (meminfo.nr_banks == 0) 
{ 
meminfo.nr_banks = 1; 
meminfo.bank[0].start = PHYS_OFFSET; 
meminfo.bank[0].size = MEM_SIZE; 
} 
meminfo �ṹ�����ڴ�������Ƕ������ڴ�ṹmeminfo��Ĭ�ϳ�ʼ���� nr_banksָ���ڴ���������bankָ��ÿ���ڴ�ķ�Χ��PHYS _OFFSETָ��ĳ���ڴ��Ŀ�ʼ��ַ��MEM_SIZEָ��ĳ���ڴ�鳤�ȡ�PHYS _OFFSET��MEM_SIZE��������include/asm-armnommu/arch-XXX/memory.h�ļ��У�����PHYS _OFFSET���ڴ�Ŀ�ʼ��ַ��MEM_SIZE�����ڴ�Ľ�����ַ������ṹ�ڽ������ڴ�ĳ�ʼ������������Ҫ���á�5.2.4 �ں��ڴ�ռ���� 
init_mm.start_code = (unsigned long) &_text; �ں˴���ο�ʼ 
init_mm.end_code = (unsigned long) &_etext; �ں˴���ν��� 
init_mm.end_data = (unsigned long) &_edata; �ں����ݶο�ʼ 
init_mm.brk = (unsigned long) &_end; �ں����ݶν���ÿһ��������һ��mm_struct�ṹ�������ڴ�ռ䣬init_mm ���ں˵�mm_struct���������ó�Ա����* mmapָ���Լ��� ��ζ���ں�ֻ��һ���ڴ����ṹ������ pgd=swapper_pg_dir�� 
swapper_pg_dir���ں˵�ҳĿ¼��ARM��ϵ�ṹ���ں�ҳĿ¼��С����Ϊ16k��init_mm�����������ں˵��ڴ�ռ䣬�ں��߳������ں˴��룬ͬ��ʹ���ں˿ռ䣬������ڴ�ռ��Ȩ�����ں�һ����5.2.5 �ڴ�ṹ��ʼ�� 
bootmem_init (&meminfo)��������meminfo�����ڴ�ṹ��ʼ����bootmem_init(&meminfo)�����е��� reserve_node_zero(bootmap_pfn, bootmap_pages) ��������������������Ǳ���һ�����ڴ�ʹ֮���ܱ���̬���䡣��Щ�ڴ������� 
reserve_bootmem_node(pgdat, __pa(&_stext), &_end - &_stext); /*�ں���ռ�õ�ַ�ռ�*/ 
reserve_bootmem_node(pgdat, bootmap_pfn<[ת����ע��������www.linuxforum.net�����ߣ��ź鹢��patrick_zhg@hotmail.com]��������CSDN���ͣ�ת�������������http://blog.csdn.net/wxmtwfx/archive/2008/05/19/2457156.aspx 
