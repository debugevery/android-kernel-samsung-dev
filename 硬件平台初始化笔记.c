Ӳ��ƽ̨��ʼ���ʼ����ߣ�yd2763132 �ύ���ڣ�2010-1-4 14:48:00  | ����:linux | ��������497 
������һ����֪����оƬ�����ֲ�أ�Ӧѡ��ͬһ�ں˵�оƬ��ʹ�ã������оƬ����arch/arm/mach-xxx����include/asm-arm/arch-xxx��,֮��Ÿ��ݾ���оƬ���������޸���Ӧ���ļ���Makefile�Լ�Kconfig.����ֲ��������Ҫ�˽�bootloader������Ȩ�ƽ����ں�ʱ����Ӳ��ƽ̨��ص��ں�����δ���ġ�
���� uboot��cpu��־�ź�������������arch/arm/kernel/head.s
������head.s������Ϊsvrģʽ���ҽ�ֹfir��irq��Ȼ�����__lookup_processor_type���bootloader���ݵ�cpu id���Ƿ��ں�֧���ڵ���__lookup_machine_type����·���ź��Ƿ��ں�֧�֣��ڵ���__create_page_tables��0x30004000-0x30008000����ҳ��:Ϊ��MMUʹ���Ժ����������Ƚ���ƽ̹ӳ�伴�����ַ�������ַ��ͬ��MMUʹ�ܺ�Ϊ���ں˹�����ʱ����һ��4Mҳ���ڴ��׵�ַӳ�䵽�ں������ַ0xc0000000
����(0xc0000000��1M�� 0x30000000 0xc0100000��1M�� 0x30100000
����0xc0200000��1M�� 0x30200000 0xc0300000��1M�� 0x30300000
���� ��ת��init/main.c�е�start_kernel()
���� �ڴ˺����е���setup_arch����(arch/arm/kernel/setup.c)��������ܹ��йص����á������м����Ƚ���Ҫ�����ݽṹ
����
�������ߵ�·��������� 
����struct machine_desc { / ��arch/arm/mach-s3c2410/mach-smdk2410.c��ʹ�ú궨�� 
���� unsigned int nr; //��·����� / MACHINE_START(SMDK2410, "SMDK2410") 
���� unsigned int phys_ram; //�ڴ���ʼ�����ַ / MACHINE_END
���� unsigned int phys_io;//io�ڴ������ַ / ����������ݽṹ������.arch.info.init���й��ں�ʹ�ÿ�
���� unsigned int io_pg_offst;//io�ڴ�ҳ��ƫ��ֵ / ��arch/arm/kernel/vmlinux.lds.S���������Ϣ 
���� const char *name;//�豸���� /
���� unsigned long boot_params;//bootloader���ݲ����������ַ 
���� unsigned int video_start;//��ƵRAM��ʼ��ַ
���� unsigned int video_end; //��ƵRAM������ַ
���� unsigned int reserve_lp0 :1; 
���� unsigned int reserve_lp1 :1; 
���� unsigned int reserve_lp2 :1;//���õ�3����ӡ�� 
���� unsigned int soft_reboot :1;//������ 
���� void (*fixup)(struct machine_desc *, 
���� struct tag *, char **, 
���� struct meminfo *); 
���� void (*map_io)(void); //Ϊ��·��������ƽ̨�豸������̬ӳ��ҳ��͸��ֳ�ʼ������
���� void (*init_irq)(void); //�жϳ�ʼ��
���� struct sys_timer *timer;//ϵͳtick��ʼ��
���� void (*init_machine)(void); //�豸��ʼ��һ�����ע��ƽ̨�豸��LED�����Լ���Դ��ʼ��
����ע��ƽ̨�豸���Է��� init_machine�����У�Ҳ����ͨ��cpu.c�е�arch_initcall(s3c_arch_init)��ע�᣻һ��Ͼõ��ں˲��ú�һ�֣������µ��ں˲���ǰһ����ע��ƽ̨�豸
����};
����
��������bootloader���ݸ��ں˲�����ʹ�õĽṹ�� �˽ṹ���ʹ�÷������£�
����struct tag { ��ATAG_CORE��ͷ����ATAG_NONE��β���м������������ֵ
���� struct tag_header hdr; //���ͷ static struct init_tags {
����//struct tag_header { u32 size; u32 tag; }; struct tag_header hdr1;
���� union { struct tag_core core;
���� struct tag_core core; //���ļ����� struct tag_header hdr2;
����/////////////////////// struct tag_mem32 mem;
����struct tag_core { struct tag_header hdr3;
���� u32 flags; //bit 0 �C 1���ظ��ļ�ϵͳΪֻ�� } init_tags __initdata = {
���� bit 1 �C unused { tag_size(tag_core), ATAG_CORE },//��ATAG_CORE��ʼ
���� bit 2 - 0 = load ramdisk { 1, PAGE_SIZE, 0xff },//1��ʾ���ļ�ϵͳֻ�� Ϊʹ�ô�����ҳ��С ���ļ�ϵͳ����/���豸��
���� bit 3 - 0 = prompt for ramdisk { tag_size(tag_mem32), ATAG_MEM },//�ڴ��־
���� u32 pagesize; //ҳ��С { MEM_SIZE, PHYS_OFFSET }//�ڴ�����
���� u32 rootdev; //���ļ�ϵͳ����/���豸�� { 0, ATAG_NONE } //��ATAG_NONE����
����};////////////////////////////
���� struct tag_mem32 mem; //�ڴ����
���� struct tag_videotext videotext; //VGA�ӿ����
���� struct tag_ramdisk ramdisk; //ramdisk���
���� struct tag_initrd initrd; // initrd���
���� struct tag_serialnr serialnr; //������
���� struct tag_revision revision; //����汾��
���� struct tag_videolfb videolfb; //framebuffersֵ
���� struct tag_cmdline cmdline; //��������
���� struct tag_acorn acorn; //�������ֲ�����
���� struct tag_memclk memclk; 
���� } u; 
����};
����
����������̬ӳ�����ݽṹ����Ƕ��ʽ��һ�㽫SOC�ڵĿ�������Ƭ���ڴ��Լ�ROM������������Ⱦ�̬ӳ�䲢Ϊ֮����ҳ���Է���ʹ�ã���map_io��������ɴ󲿷־�̬ӳ�䡣һ�㽫Ƭ�ڿ�������ΪIO�ڴ�ʹ�ã����þ�̬ӳ�������ʡ�
����struct map_desc { 
���� unsigned long virtual; //�����ַ
���� unsigned long physical; //�����ַ
���� unsigned long length; //����
���� unsigned int type; //���͹�8��MT_DEVICE MT_CACHECLEAN MT_MINICLEAN MT_LOW_VECTORS
���� //MT_HIGH_VECTORS MT_MEMORY MT_ROM MT_IXP2000_DEVICE
����}; 
����//�ڷ���ƽ̨�豸�����Ĺ����з���һ�����⣬�ڳ�ʼ���������ѽ�����Ƭ�ڿ��ƼĴ�����̬ӳ�䣻����������������ͨ��ioremap(res->start, size)�ֽ������ַ��̬ӳ����һ�飬���������ַָ��ͬһ�����ַ�������ͻ��
����
����//�����ڴ����õ����ݽṹ����Ƕ��ʽϵͳ��һ����Ϊһ��bank����һ���ڵ�
����struct meminfo { 
���� int nr_banks;//cpu bank�� 
���� struct { 
���� unsigned long start; //�ڴ���ʼ��ַ
���� unsigned long size; //��С
���� int node; //�ڵ���
���� } bank[NR_BANKS];//armһ��bank��8�� 
����};�ҵĿ�������Ϊstruct meminfo meminfo __initdata = { 1,{0x30000000,0x4000000,0},{}, };����������ˡ�
����
���� �ں�֧����ν��NUMA�ṹ����������ϵͳ�Ĵ洢�ռ�ֳɼ����������Ľڵ㣬�ڵ�ʹ��pglist_data�����������ڵ��ַ�Ϊzone��������������zone_dma��СΪ16MΪISA DMA�ܷ��� zone_normal��СΪ16-896M�ں˿�ֱ��ӳ�� zone_highmem ��С����896MΪҳcache���û�������ʹ�á���UMA��ϵ�ṹ����ֻ��һ����̬��pg_data_t�ṹcontig_page_data ;��NUMAϵͳ��˵��ǳ��������䣬NUMAϵͳ��һ�������Զ�ӦLinux�洢�����е�һ�����
����
����typedef struct pglist_data { 
���� struct zone node_zones[MAX_NR_ZONES]; 
���� //�ý���zone���ͣ�һ�����ZONE_HIGHMEM��ZONE_NORMAL��ZONE_DMA���� 
���� struct zonelist node_zonelists[GFP_ZONETYPES]; 
���� //����ʱ�ڴ�ʱzone������������free_area_init_core() 
���� //ͨ��page_alloc.c�е�build_zonelists()����zone��˳�� 
���� int nr_zones;//�ýڵ��zone�� 
����#ifdef CONFIG_FLAT_NODE_MEM_MAP 
���� struct page *node_mem_map;//���� struct page ����ĵ�һҳ 
����#endif 
���� unsigned long node_start//�ý�����ʼ�����ַ 
���� struct bootmem_data *bdat_pfn;//bootmen�⹹�����ַ 
���� unsigned long node_present_pages; //���нڵ������ҳ������ 
���� unsigned long node_spanned_pages; //���нڵ������ҳ��Χ��������С�����ն��� 
���� int node_id;//�ý���zone�������Դ�1��3�����������еĽ�㶼��Ҫ��3��zone 
���� struct pglist_data *pgdat_next; 
���� //��UMA��ϵ�ṹ����ֻ��һ����̬��pg_data_t�ṹcontig_page_data 
���� //��NUMAϵͳ��˵��ǳ��������䣬NUMAϵͳ��һ�������Զ�ӦLinux�洢�����е�һ����� 
���� wait_queue_head_t kswapd_wait;//ʹ�ô˽ڵ�Ľ��̶���ͷ 
���� struct task_struct *kswapd;//����ʹ�õĽ���ָ�� 
���� int kswapd_max_order;//��ͬʱ���øýڵ���������� 
����} pg_data_t;
���� �ڴ���ҳ��ʱ����bootmap�ڴ������������ڴ�����ҳ����й������ڷ���ҳ�档��������ϵͳ����ʱʹ�ã���buddy���ڴ����ϵͳ��ʼ����ɺ󽫲���ʹ�á������˼���ǽ�SDRAM�Ŀ��ô洢�ռ�ֳ����ҳ��ÿҳ�Ĵ�СΪ4K���ڷ���ʱ��ҳΪ��λ���䣬���䷽���Ǵӵ�������ֱ���ҵ�һ���������������СҪ��Ŀ���ҳ��Ϊֹ���ں˽����е�bootmem_data����ȫ�ֱ���contig_bootmem_data�������Ա���ơ��ں��н�contig_bootmem_dataָ��contig_page_data-> bdat_pfn
����typedef struct bootmem_data { 
���� unsigned long node_boot_start;//�ڴ���ʼ�����ַ 
���� unsigned long node_low_pfn;//����ҳ�� 
���� void *node_bootmem_map;//λӳ��ҳ���ַ
���� ///////////////////////////////////////���ڿ��ٷ��� 
���� unsigned long last_offset;//��ʣ�´�����ҳ�� 
���� unsigned long last_pos;//���ڷ���ָ�����ڵ�ҳ��� 
���� unsigned long last_success;//�Ѿ��ɹ��������ҳ�� 
���� 
����} bootmem_data_t;
���� ��setup_arch�������ȵ���setup_machine������ñ�������������Ϣstruct machine_desc�ĵ�ַ��λ��.arch.info.init),
����ͨ��mdesc->boot_params���bootloader���͹������ں�����������������ַ��ת��Ϊ�����ַ.�ٵ���parse_tags������ATAG_CORE���ø��ļ�ϵͳ��ֻ���͸��ļ���/���豸�ţ���ATAG_MEM�ǽ��ڴ�������Ϣ���Ƶ�һ��meminfo�ṹ�����Թ��ں˽���ҳ��֮�ã���ATAG_CMDLINE�ǽ���������������Ƹ�default_command_line���飬���������ı�־���Բ��պ�����⡣Ȼ��Text and read-only data�׵�ַ�ͽ�����ַ�����ݶν�����ַ���ں˽�����ַ�ֱ𸶸�init_mm�ṹ�е�start_code end_code end_data brk��Ա��ʹ��.ÿһ��������һ��mm_struct�ṹ���������ڴ�ռ䣬init_mm ���ں˵�mm_struct���������ó�Ա����* mmapָ���Լ�������linux/sched.h�е�mm_struct�� ��ζ���ں�ֻ��һ���ڴ����ṹ������* pgd=swapper_pg_dir�� swapper_pg_dir���ں˵�ҳ���׵�ַ����arm��ϵ�ṹ��16k�� ����init_mm����������kernel���ڴ�ռ䡣 
���� ����parse_cmdline�����������ֺ󱣴浽command_line�������Թ��ں�ʹ�ã�
���� paging_init����Ϊ���е�ӳ�佨����Ӧ��ҳ���˺����ǳ���Ҫ�ں����ص������
���� request_standard_resources����Ϊ�ں˴�������� ��Ƶ�ʹ�ӡ���豸����ϵͳ��Դ��
���� cpu_init()Ϊsmp�е�cpu���ö�ջ��
���� ��mdesc->init_irq����init_arch_irq ,��mdesc->timer ����system_timer,�� mdesc->init_machine����init_machine��ֱ����.initcall.init���й�rest_init()�е�do_initcalls�������ã�
�������������������������������������������������������������������������������������������������������������� 
���� paging_init������Ҫ��bootmem_init memtable_init mdesc->map_io free_area_init_node�ĸ�������������е�ҳ��ӳ�������
���� truct node_info { 
���� unsigned int start;//��ʼҳ�� 
���� unsigned int end;//����ҳ�� 
���� int bootmap_pages;//һ��λָ��һ��ҳ�Ƿ�ӳ�� 
���� }
���� ��bootmem_init ���ȵ���find_memend_and_nodes����ʹ��struct meminfo�е�������дnode_info�������ڵ����node_infoʹ֮online���Ҽ��㱣������λ���������ҳ����ʹ��find_bootmap_pfn���������ں˽��������һҳ��Ϊ����λӳ���ҳ�棻ʹ��init_bootmem_node������ɽ�ȫ�ֱ���contig_bootmem_dataָ��contig_page_data-> bdat_pfn��������ҳ������Ϊ��ʹ��״̬��ʹ��free_bootmem_node_bank�����ͷ�����bootmemҳ�漴�����ڴ�ʹ֮Ϊ����״̬��ʹ��
����reserve_node_zero�������ڴ��е�ҳ�� �ں� λӳ��ҳ�� ��Ϊ����״̬������Ϊ����״̬����0x30000000-0x30003fffΪ���ã�0x30004000-0x30007fff���ã�0x30008000-&_endΪ���ã�&_end+1Ϊ���ã�&_end+2-0x34000000Ϊ����״̬��
���� Linux�ں˲�������ҳ��ӳ�伴PGD PMD PTE,pgd����L1����2048��ÿ����ԱΪ8bytes, PMD��Ϊ�м����pteҳ�����ַ��pteҳ��ӳ��4K�ռ� linux pte��Ҫ���h/w pteʹ�õĽ����memtable_init�ȵ���build_mem_type_table() ����cpu��ID�ŵ���һ��ҳ�������������ʹ��alloc_bootmem_low_pages���һ����ʹ��ҳ�棬ʹ��clear_mapping���0xc0000000��0xffffffff��Ӧ��pmdҳ�������е��ں˿ռ䣩��ʹ��create_mapping������д�ڴ���Ӧ������1 2��ҳ�����������ɿɲο����򣩣���ʹ��vectors_high()�ж��Ƿ�Ϊ���ж�������������0xffff0000Ϊ��ʼ�����ַ������̬ӳ�䣬��֮Ϊ���ж�����ʱ��0x00000000Ϊ��ʼ�����ַ������̬ӳ��.�����е���arch/arm/mm/proc-arm920.S �е�
���� CPU_arm920_set_pte������pteҳ��
���� mdesc->map_io����Ϊstruct machine_desc�еĳ�Աmap_io���ȵ���s3c24xx_init_io����Ϊ����Ҫ�Ŀ��ƿ�ľ�̬ӳ�佨��ҳ����������IRQ MEMCTRL USBHOST DMA CLKPWR LCD NAND UART TIMER USBDEV WATCHDOG
����IIC IIS GPIO RTC ADC SPI SDI CS8900��ʹ��s3c24xx_init_clocks��������fclk pclk fclkʱ�Ӳ�ʹ�ܸ�����ģ��ʱ�ӣ�
����ʹ��s3c24xx_init_uarts���������е�uart�豸���浽s3c24xx_uart_devs[3]������ʹ�á����еľ�̬ӳ��ҳ���ǵ���iotable_init��������д�ġ�
���� free_area_init_node�ϸ�������mm/page_alloc.c�����Ϊ�ڵ����ҳ���ʼ��pgdat��
����////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
���������жϳ�ʼ�������£�
���� ��start_kernel()��ͨ������setup_arch(&command_line)ʹ��init_arch_irq = mdesc->init_irq;��ָ��smdk2410_init_irq������·���жϳ�ʼ����������init_arch_irqָ�룬�ڵ��ú���init_IRQ()�����жϳ�ʼ�����������ڴ˺����н���init_arch_irq()����жϳ�ʼ������ִ��smdk2410_init_irq()������
���� ���жϲ�������������Ҫ�Ľṹ��struct irqchip��struct irqdesc
���� struct irqchip { �ýṹ�����жϵĲ����������� 
���� void (*ack)(unsigned int); //�����ж�Դ�����������
���� void (*mask)(unsigned int); //���������жϺŶ�Ӧ���ж�ʹ��λ
���� void (*unmask)(unsigned int); //����ʹ���ж�
���� int (*retrigger)(unsigned int); //�ٴδ����жϺ���
���� int (*set_type)(unsigned int, unsigned int); //�����ж����� �½��� ������ �͵�λ �ߵ�λ�ȵ�
���� int (*set_wake)(unsigned int, unsigned int); //�����жϾ��л��ѵ�Դ����
����#ifdef CONFIG_SMP 
���� void (*set_cpu)(struct irqdesc *desc, unsigned int irq, unsigned int cpu); // ��CPU�ж����ã����Ǻ����������
����#endif 
����};
����
����struct irqdesc { //ÿ���ж�Դ��Ӧһ���ýṹ����ȫ��������һ��ȫ��������
���� irq_handler_t handle;//�ж�ģʽ������ 
���� struct irqchip *chip; //�жϲ�������������
���� struct irqaction *action; //�ж϶����ṹ�壬���ж���Ӧ���ɸýṹ�������жϲ����������������handle��ͬ
���� struct list_head pend;//�������ж����� 
���� void *chipdata; 
���� void *data; 
���� unsigned int disable_depth; 
����
���� unsigned int triggered: 1;//�ж��Ѵ�����־ 
���� unsigned int running : 1;//�ж������� 
���� unsigned int pending : 1;//�ж��ѹ��ر�־ 
���� unsigned int probing : 1; /* IRQ in use for a probe */ 
���� unsigned int probe_ok : 1;//���ʾ���жϿ�̽�� 
���� unsigned int valid : 1; //��ʾ���жϿ��� 
���� unsigned int noautoenable : 1; //��ʾ�����Զ�enable���ж� 
���� unsigned int unused :25; 
���� struct proc_dir_entry *procdir; //proc�ļ�ϵͳ����ڵ�ַ��������ʾ�ж���Դ 
����
����#ifdef CONFIG_SMP 
���� cpumask_t affinity; 
���� unsigned int cpu; 
����#endif 
���� /* 
���� * IRQ lock detection 
���� */ 
���� unsigned int lck_cnt; 
���� unsigned int lck_pc; 
���� unsigned int lck_jif; 
����};
����struct irqaction {//ÿ���ж�Դ��Ҫ�����ýṹȻ����ص�action�����ϣ����action�����жϹ����䴦���ж�ʵ�ʺ��� 
���� irqreturn_t (*handler)(int, void *, struct pt_regs *);//�жϴ��������� irq_handler_t handle��ͬ 
���� unsigned long flags;//�жϱ�־ 
���� cpumask_t mask;//�����ж��� 
���� const char *name;//�ж����� 
���� void *dev_id;//�豸��ʶ�����ڱ�Ƕ���豸����ͬһ��irq 
���� struct irqaction *next;//����action�����ϣ����жϹ���ʱ�������Ӷ���жϴ����� 
���� int irq;//�жϺ� 
���� struct proc_dir_entry *dir; //proc�ļ�ϵͳĿ¼��ַ
����};���жϴ���ʵ�����ڲ����ýṹ�塣
�������е��жϺŶ���Ӧһ��struct irqdesc �������еĽṹ�嶼������ȫ�ֱ���irq_desc�ϡ�������Ƚ�irq_desc�е�����struct irqdesc ��ʼ��Ϊ�����жϽṹ�壬��ȫ�����������磺
���� for (irq = 0, desc = irq_desc; irq < NR_IRQS; irq++, desc++) { 
���� *desc = bad_irq_desc;//�����irq_descע��Ϊ�����ж� 
���� INIT_LIST_HEAD(&desc->pend); //����ָ��}
����
����s3c24xx_init_irq��Ҫʱ��ɽ� irq_desc��Ա���¸�ֵ�����Ƚ����жϵ��ⲿ�ж�����Ĵ�������������жϵ�Դ���ҼĴ������ж����ҼĴ��������Ȼ���ٽ�����irq_desc��IRQ_BATT_FLT��IRQ_ADCPARENT����Ӧ�Ľṹ���ʼ������
����set_irq_chip(irqno, &s3c_irq_level_chip);//����irqdesc->chip��Ա�����жϲ������� 
����set_irq_handler(irqno, do_level_IRQ);//��ʼ�� irqdesc-> handle��Ա���������жϴ�����
��������ʱ���һ���ж�Դ���ԣ��������ж����ⲿ�ж��Լ������жϷֱ�������ͬ���ĳ�ʼ��������
���� �жϳ�ʼ�����ǽ����е��ж������жϺŽ��䱣�浽ȫ������irq_desc�� ����ͷ��ʼ��ʼ����chip handle probe_ok valid noautoenable��Ա������ ��Ҫ��action��Ա��Ҫ�ж�ע����ܳ�ʼ����
���� int request_irq(unsigned int irq, irqreturn_t (*handler)(int, void *, struct pt_regs *), 
���� unsigned long irq_flags, const char * devname, void *dev_id) 
����{ 
���� unsigned long retval; 
���� struct irqaction *action; 
���� if (irq >= NR_IRQS || !irq_desc[irq].valid || !handler || 
���� (irq_flags & SA_SHIRQ && !dev_id)) 
���� return -EINVAL; 
���� action = (struct irqaction *)kmalloc(sizeof(struct irqaction), GFP_KERNEL);//����ռ� 
���� if (!action) 
���� return -ENOMEM; 
����
���� action->handler = handler; //�жϴ�����
���� action->flags = irq_flags; //�жϱ�־
���� cpus_clear(action->mask);//mask=0 
���� action->name = devname; //�豸����
���� action->next = NULL; //����
���� action->dev_id = dev_id;//�жϺ�����2������ 
���� retval = setup_irq(irq, action);//��������action�ڸ�irq_desc�е��жϳ�Ա�ṹ 
����
���� if (retval) 
���� kfree(action); 
���� return retval; 
����}���ж����뺯���Ǵ�������ʼ��irqdesc-> action��Ա.
���� ��ô�����е��жϴ���������irqdesc-> action-> handler������α����õ���?
���� �ڳ�ʼ��handlerʱ���ѽ�do_level_IRQ��do_edge_IRQ������irqdesc->handler�����ж���Ӧ���ں˽�����irqdesc->handler��������do_level_IRQ��do_edge_IRQ����������жϵ�Դ���ҼĴ������ж����ҼĴ�������ͨ��
����__do_irq(irq, desc->action, regs)����__do_irq�������ڴ˺����н� desc->action��ȡ���жϴ��������ò�ִ�У�Ҫ����һ��ϸ�ڣ��жϴ���ɹ���һ��Ҫ����IRQ_HANDLED���������__do_irq�������������£�
����...........
����do { 
���� ret = action->handler(irq, action->dev_id, regs);//�����жϴ����� 
���� if (ret == IRQ_HANDLED)//�жϴ���ɹ� 
���� status |= action->flags; 
���� retval |= ret; 
���� action = action->next;//��Ϊ�����ж�ʱ��ִ��������һ���������������Ƴ� 
���� } while (action);
����ע�⣺
���� �ڱ�д����ʱ�й��жϵĲ����Ǿ���Ҫ�õ��ģ��ں��������Ѿ���д��һЩ�ж����ú������Է���Ĺ�ʹ��,����gpio�������ú������ʹ��Ч�����á�
����void disable_irq(unsigned int); //�ر���Ӧ�жϺ��ж�
����void enable_irq(unsigned int);//������Ӧ�жϺ��ж�
����int set_irq_type(unsigned int irq, unsigned int type);//�����ж�Ϊ���ִ���ģʽ
����void disable_irq_wake(unsigned int irq); //��ֹ�жϻ��ѹ���
����void enable_irq_wake(unsigned int irq);//ʹ���жϻ��ѹ���
