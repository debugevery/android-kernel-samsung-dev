硬件平台初始化笔记作者：yd2763132 提交日期：2010-1-4 14:48:00  | 分类:linux | 访问量：497 
　　对一个不知名的芯片如何移植呢？应选择同一内核的芯片来使用，仿造该芯片生成arch/arm/mach-xxx包和include/asm-arm/arch-xxx包,之后才根据具体芯片的配置来修改相应的文件和Makefile以及Kconfig.在移植过程中需要了解bootloader将控制权移交给内核时，与硬件平台相关的内核是如何处理的。
　　 uboot将cpu标志号和启动参数传给arch/arm/kernel/head.s
　　在head.s中设置为svr模式并且禁止fir和irq，然后调用__lookup_processor_type检测bootloader传递的cpu id号是否被内核支持在调用__lookup_machine_type检测电路板信号是否被内核支持；在调用__create_page_tables在0x30004000-0x30008000建立页表:为了MMU使能以后正常工作先建立平坦映射即虚拟地址和物理地址相同；MMU使能后为了内核工作临时建立一个4M页表将内存首地址映射到内核虚拟地址0xc0000000
　　(0xc0000000（1M） 0x30000000 0xc0100000（1M） 0x30100000
　　0xc0200000（1M） 0x30200000 0xc0300000（1M） 0x30300000
　　 跳转到init/main.c中的start_kernel()
　　 在此函数中调用setup_arch函数(arch/arm/kernel/setup.c)来设置与架构有关的设置。这里有几个比较重要的数据结构
　　
　　描诉电路板相关配置 
　　struct machine_desc { / 在arch/arm/mach-s3c2410/mach-smdk2410.c中使用宏定义 
　　 unsigned int nr; //电路板序号 / MACHINE_START(SMDK2410, "SMDK2410") 
　　 unsigned int phys_ram; //内存起始物理地址 / MACHINE_END
　　 unsigned int phys_io;//io内存物理地址 / 来定义此数据结构保存在.arch.info.init段中供内核使用可
　　 unsigned int io_pg_offst;//io内存页表偏移值 / 在arch/arm/kernel/vmlinux.lds.S查找相关信息 
　　 const char *name;//设备名称 /
　　 unsigned long boot_params;//bootloader传递参数首物理地址 
　　 unsigned int video_start;//视频RAM起始地址
　　 unsigned int video_end; //视频RAM结束地址
　　 unsigned int reserve_lp0 :1; 
　　 unsigned int reserve_lp1 :1; 
　　 unsigned int reserve_lp2 :1;//设置的3个打印口 
　　 unsigned int soft_reboot :1;//软重启 
　　 void (*fixup)(struct machine_desc *, 
　　 struct tag *, char **, 
　　 struct meminfo *); 
　　 void (*map_io)(void); //为电路板上所有平台设备建立静态映射页表和各种初始化设置
　　 void (*init_irq)(void); //中断初始化
　　 struct sys_timer *timer;//系统tick初始化
　　 void (*init_machine)(void); //设备初始化一般完成注册平台设备和LED配置以及电源初始化
　　注册平台设备可以方在 init_machine函数中，也可以通过cpu.c中的arch_initcall(s3c_arch_init)来注册；一般较久的内核采用后一种，而较新的内核采用前一种来注册平台设备
　　};
　　
　　保存bootloader传递给内核参数所使用的结构体 此结构体的使用方法如下：
　　struct tag { 以ATAG_CORE开头，以ATAG_NONE结尾在中间加上其他描述值
　　 struct tag_header hdr; //旗标头 static struct init_tags {
　　//struct tag_header { u32 size; u32 tag; }; struct tag_header hdr1;
　　 union { struct tag_core core;
　　 struct tag_core core; //根文件描诉 struct tag_header hdr2;
　　/////////////////////// struct tag_mem32 mem;
　　struct tag_core { struct tag_header hdr3;
　　 u32 flags; //bit 0 – 1挂载根文件系统为只读 } init_tags __initdata = {
　　 bit 1 – unused { tag_size(tag_core), ATAG_CORE },//以ATAG_CORE开始
　　 bit 2 - 0 = load ramdisk { 1, PAGE_SIZE, 0xff },//1表示根文件系统只读 为使用处理器页大小 根文件系统的主/次设备号
　　 bit 3 - 0 = prompt for ramdisk { tag_size(tag_mem32), ATAG_MEM },//内存标志
　　 u32 pagesize; //页大小 { MEM_SIZE, PHYS_OFFSET }//内存描述
　　 u32 rootdev; //根文件系统的主/次设备号 { 0, ATAG_NONE } //以ATAG_NONE结束
　　};////////////////////////////
　　 struct tag_mem32 mem; //内存相关
　　 struct tag_videotext videotext; //VGA接口相关
　　 struct tag_ramdisk ramdisk; //ramdisk相关
　　 struct tag_initrd initrd; // initrd相关
　　 struct tag_serialnr serialnr; //串口数
　　 struct tag_revision revision; //主板版本号
　　 struct tag_videolfb videolfb; //framebuffers值
　　 struct tag_cmdline cmdline; //启动命令
　　 struct tag_acorn acorn; //以下两种不常用
　　 struct tag_memclk memclk; 
　　 } u; 
　　};
　　
　　描述静态映射数据结构，在嵌入式中一般将SOC内的控制器和片外内存以及ROM和网络控制器先静态映射并为之建立页表以方便使用，在map_io函数中完成大部分静态映射。一般将片内控制器作为IO内存使用，利用静态映射来访问。
　　struct map_desc { 
　　 unsigned long virtual; //虚拟地址
　　 unsigned long physical; //物理地址
　　 unsigned long length; //长度
　　 unsigned int type; //类型供8中MT_DEVICE MT_CACHECLEAN MT_MINICLEAN MT_LOW_VECTORS
　　 //MT_HIGH_VECTORS MT_MEMORY MT_ROM MT_IXP2000_DEVICE
　　}; 
　　//在分析平台设备驱动的过程中发现一个问题，在初始化过程中已将所用片内控制寄存器静态映射；但是在驱动程序中通过ioremap(res->start, size)又将物理地址动态映射了一遍，但两虚拟地址指向同一物理地址不会起冲突。
　　
　　//描诉内存配置的数据结构，在嵌入式系统中一般设为一个bank数，一个节点
　　struct meminfo { 
　　 int nr_banks;//cpu bank数 
　　 struct { 
　　 unsigned long start; //内存起始地址
　　 unsigned long size; //大小
　　 int node; //节点数
　　 } bank[NR_BANKS];//arm一般bank有8个 
　　};我的开发板设为struct meminfo meminfo __initdata = { 1,{0x30000000,0x4000000,0},{}, };这样简洁明了。
　　
　　 内核支持所谓的NUMA结构，它将整个系统的存储空间分成几个不连续的节点，节点使用pglist_data进行描述，节点又分为zone，其有三种类型zone_dma大小为16M为ISA DMA能访问 zone_normal大小为16-896M内核可直接映射 zone_highmem 大小大于896M为页cache和用户进程所使用。对UMA体系结构，则只有一个静态的pg_data_t结构contig_page_data ;对NUMA系统来说则非常容易扩充，NUMA系统中一个结点可以对应Linux存储描述中的一个结点
　　
　　typedef struct pglist_data { 
　　 struct zone node_zones[MAX_NR_ZONES]; 
　　 //该结点的zone类型，一般包括ZONE_HIGHMEM、ZONE_NORMAL和ZONE_DMA三类 
　　 struct zonelist node_zonelists[GFP_ZONETYPES]; 
　　 //分配时内存时zone的排序。它是由free_area_init_core() 
　　 //通过page_alloc.c中的build_zonelists()设置zone的顺序 
　　 int nr_zones;//该节点的zone数 
　　#ifdef CONFIG_FLAT_NODE_MEM_MAP 
　　 struct page *node_mem_map;//它是 struct page 数组的第一页 
　　#endif 
　　 unsigned long node_start//该结点的起始物理地址 
　　 struct bootmem_data *bdat_pfn;//bootmen解构链表地址 
　　 unsigned long node_present_pages; //所有节点的物理页的总数 
　　 unsigned long node_spanned_pages; //所有节点的物理页范围的整个大小（含空洞） 
　　 int node_id;//该结点的zone个数可以从1到3但并不是所有的结点都需要有3个zone 
　　 struct pglist_data *pgdat_next; 
　　 //对UMA体系结构，则只有一个静态的pg_data_t结构contig_page_data 
　　 //对NUMA系统来说则非常容易扩充，NUMA系统中一个结点可以对应Linux存储描述中的一个结点 
　　 wait_queue_head_t kswapd_wait;//使用此节点的进程队列头 
　　 struct task_struct *kswapd;//正在使用的进程指针 
　　 int kswapd_max_order;//可同时调用该节点的最大进程数 
　　} pg_data_t;
　　 在创建页表时采用bootmap内存分配策略来对内存所有页面进行管理并用于分配页面。它用于在系统启动时使用，在buddy等内存分配系统初始化完成后将不再使用。其基本思想是将SDRAM的可用存储空间分成许多页，每页的大小为4K，在分配时以页为单位分配，分配方法是从低往高找直到找到一块或连续多块满足大小要求的空闲页面为止。内核将所有的bootmem_data放在全局变量contig_bootmem_data链表里以便控制。内核中将contig_bootmem_data指向contig_page_data-> bdat_pfn
　　typedef struct bootmem_data { 
　　 unsigned long node_boot_start;//内存起始物理地址 
　　 unsigned long node_low_pfn;//结束页号 
　　 void *node_bootmem_map;//位映射页面地址
　　 ///////////////////////////////////////用于快速分配 
　　 unsigned long last_offset;//还剩下待分配页数 
　　 unsigned long last_pos;//现在分配指针所在的页面号 
　　 unsigned long last_success;//已经成功分配的总页数 
　　 
　　} bootmem_data_t;
　　 在setup_arch（）中先调用setup_machine（）获得保存主板配置信息struct machine_desc的地址（位于.arch.info.init),
　　通过mdesc->boot_params获得bootloader传送过来的内核启动参数存放物理地址并转换为虚拟地址.再调用parse_tags（）将ATAG_CORE设置根文件系统非只读和根文件主/次设备号，将ATAG_MEM是将内存所有信息复制到一个meminfo结构体中以供内核建立页表之用，将ATAG_CMDLINE是将启动命令参数复制给default_command_line数组，对于其他的标志可以参照函数理解。然后将Text and read-only data首地址和结束地址，数据段结束地址，内核结束地址分别付给init_mm结构中的start_code end_code end_data brk成员供使用.每一个任务都有一个mm_struct结构管理任务内存空间，init_mm 是内核的mm_struct，其中设置成员变量* mmap指向自己，（见linux/sched.h中的mm_struct） 意味着内核只有一个内存管理结构，设置* pgd=swapper_pg_dir， swapper_pg_dir是内核的页表首地址，在arm体系结构有16k， 所以init_mm定义了整个kernel的内存空间。 
　　 调用parse_cmdline（）将命令拆分后保存到command_line数组中以供内核使用；
　　 paging_init（）为所有的映射建立相应的页表，此函数非常重要在后面重点分析；
　　 request_standard_resources（）为内核代码和数据 视频和打印机设备申请系统资源；
　　 cpu_init()为smp中的cpu设置堆栈；
　　 将mdesc->init_irq付给init_arch_irq ,将mdesc->timer 付给system_timer,将 mdesc->init_machine付给init_machine后分别放入.initcall.init段中供rest_init()中的do_initcalls（）调用；
　　＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃＃ 
　　 paging_init（）主要由bootmem_init memtable_init mdesc->map_io free_area_init_node四个大函数来完成所有的页面映射情况。
　　 truct node_info { 
　　 unsigned int start;//起始页号 
　　 unsigned int end;//结束页号 
　　 int bootmap_pages;//一个位指明一个页是否被映射 
　　 }
　　 在bootmem_init 中先调用find_memend_and_nodes（）使用struct meminfo中的数据填写node_info，即将节点加入node_info使之online并且计算保存所有位隐射所需的页数；使用find_bootmap_pfn（）设置内核结束后的下一页作为保存位映射的页面；使用init_bootmem_node（）完成将全局变量contig_bootmem_data指向contig_page_data-> bdat_pfn并将所有页面设置为已使用状态；使用free_bootmem_node_bank（）释放所有bootmem页面即整个内存使之为可用状态；使用
　　reserve_node_zero（）将内存中的页表 内核 位映射页面 设为已用状态其他均为可用状态，即0x30000000-0x30003fff为可用，0x30004000-0x30007fff已用，0x30008000-&_end为已用；&_end+1为已用；&_end+2-0x34000000为可用状态。
　　 Linux内核采用三级页表映射即PGD PMD PTE,pgd代表L1且有2048个每个成员为8bytes, PMD作为中间项保存pte页表基地址，pte页表映射4K空间 linux pte是要配合h/w pte使用的结果。memtable_init先调用build_mem_type_table() 根据cpu的ID号调整一级页表配置情况；在使用alloc_bootmem_low_pages获得一个可使用页面，使用clear_mapping清除0xc0000000～0xffffffff对应的pmd页表（即所有的内核空间），使用create_mapping（）填写内存相应的所有1 2级页表（具体如何完成可参考程序）；再使用vectors_high()判断是否为高中断向量，是则以0xffff0000为起始虚拟地址创建静态映射，反之为低中断向量时以0x00000000为起始虚拟地址创建静态映射.程序中调用arch/arm/mm/proc-arm920.S 中的
　　 CPU_arm920_set_pte来设置pte页表。
　　 mdesc->map_io函数为struct machine_desc中的成员map_io，先调用s3c24xx_init_io（）为所需要的控制块的静态映射建立页表，常见的有IRQ MEMCTRL USBHOST DMA CLKPWR LCD NAND UART TIMER USBDEV WATCHDOG
　　IIC IIS GPIO RTC ADC SPI SDI CS8900；使用s3c24xx_init_clocks（）设置fclk pclk fclk时钟并使能各控制模块时钟；
　　使用s3c24xx_init_uarts（）将所有的uart设备保存到s3c24xx_uart_devs[3]供驱动使用。其中的静态映射页表是调用iotable_init（）来填写的。
　　 free_area_init_node较复杂其在mm/page_alloc.c中完成为节点分配页面初始化pgdat。
　　////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
　　对于中断初始化有如下：
　　 在start_kernel()中通过函数setup_arch(&command_line)使用init_arch_irq = mdesc->init_irq;（指向smdk2410_init_irq）将电路板中断初始化函数付给init_arch_irq指针，在调用函数init_IRQ()进行中断初始化操作，而在此函数中将调init_arch_irq()完成中断初始化，即执行smdk2410_init_irq()函数。
　　 在中断操作中有两个重要的结构体struct irqchip和struct irqdesc
　　 struct irqchip { 该结构体是中断的操作函数集合 
　　 void (*ack)(unsigned int); //用于中断源悬挂清除函数
　　 void (*mask)(unsigned int); //用于屏蔽中断号对应的中断使能位
　　 void (*unmask)(unsigned int); //用于使能中断
　　 int (*retrigger)(unsigned int); //再次触发中断函数
　　 int (*set_type)(unsigned int, unsigned int); //设置中断类型 下降沿 上升沿 低电位 高电位等等
　　 int (*set_wake)(unsigned int, unsigned int); //设置中断具有唤醒电源功能
　　#ifdef CONFIG_SMP 
　　 void (*set_cpu)(struct irqdesc *desc, unsigned int irq, unsigned int cpu); // 多CPU中断设置，不是很清楚？？？
　　#endif 
　　};
　　
　　struct irqdesc { //每个中断源对应一个该结构，且全部链接在一个全局数组上
　　 irq_handler_t handle;//中断模式处理函数 
　　 struct irqchip *chip; //中断操作函数集合体
　　 struct irqaction *action; //中断动作结构体，即中断相应后由该结构来链接中断操作函数，与上面的handle不同
　　 struct list_head pend;//已申请中断链表 
　　 void *chipdata; 
　　 void *data; 
　　 unsigned int disable_depth; 
　　
　　 unsigned int triggered: 1;//中断已触发标志 
　　 unsigned int running : 1;//中断在运行 
　　 unsigned int pending : 1;//中断已挂载标志 
　　 unsigned int probing : 1; /* IRQ in use for a probe */ 
　　 unsigned int probe_ok : 1;//则表示此中断可探测 
　　 unsigned int valid : 1; //表示此中断可用 
　　 unsigned int noautoenable : 1; //表示不能自动enable此中断 
　　 unsigned int unused :25; 
　　 struct proc_dir_entry *procdir; //proc文件系统的入口地址，用于显示中断资源 
　　
　　#ifdef CONFIG_SMP 
　　 cpumask_t affinity; 
　　 unsigned int cpu; 
　　#endif 
　　 /* 
　　 * IRQ lock detection 
　　 */ 
　　 unsigned int lck_cnt; 
　　 unsigned int lck_pc; 
　　 unsigned int lck_jif; 
　　};
　　struct irqaction {//每个中断源都要创建该结构然后挂载到action队列上，多个action构成中断共享，其处理中断实质函数 
　　 irqreturn_t (*handler)(int, void *, struct pt_regs *);//中断处理函数，与 irq_handler_t handle不同 
　　 unsigned long flags;//中断标志 
　　 cpumask_t mask;//屏蔽中断数 
　　 const char *name;//中断名称 
　　 void *dev_id;//设备标识，用于标记多个设备共享同一个irq 
　　 struct irqaction *next;//挂在action队列上，在中断共享时可以链接多个中断处理函数 
　　 int irq;//中断号 
　　 struct proc_dir_entry *dir; //proc文件系统目录地址
　　};即中断处理实际是在操作该结构体。
　　所有的中断号都对应一个struct irqdesc ，且所有的结构体都链接在全局变量irq_desc上。在起初先将irq_desc中的所有struct irqdesc 初始化为哑铃中断结构体，并全部链接起来如：
　　 for (irq = 0, desc = irq_desc; irq < NR_IRQS; irq++, desc++) { 
　　 *desc = bad_irq_desc;//起初将irq_desc注册为哑铃中断 
　　 INIT_LIST_HEAD(&desc->pend); //链接指针}
　　
　　s3c24xx_init_irq主要时完成将 irq_desc成员重新赋值，其先将子中断的外部中断请求寄存器清除，级联中断的源悬挂寄存器和中断悬挂寄存器清除；然后再将数组irq_desc从IRQ_BATT_FLT到IRQ_ADCPARENT所对应的结构体初始化即：
　　set_irq_chip(irqno, &s3c_irq_level_chip);//设置irqdesc->chip成员用于中断操作函数 
　　set_irq_handler(irqno, do_level_IRQ);//初始化 irqdesc-> handle成员用于链接中断处理函数
　　以上时针对一级中断源而言，对于子中断如外部中断以及级联中断分别作上述同样的初始化操作。
　　 中断初始化就是将所有的中断依据中断号将其保存到全局数组irq_desc中 并从头开始初始化其chip handle probe_ok valid noautoenable成员，而最 重要的action成员需要中断注册才能初始化。
　　 int request_irq(unsigned int irq, irqreturn_t (*handler)(int, void *, struct pt_regs *), 
　　 unsigned long irq_flags, const char * devname, void *dev_id) 
　　{ 
　　 unsigned long retval; 
　　 struct irqaction *action; 
　　 if (irq >= NR_IRQS || !irq_desc[irq].valid || !handler || 
　　 (irq_flags & SA_SHIRQ && !dev_id)) 
　　 return -EINVAL; 
　　 action = (struct irqaction *)kmalloc(sizeof(struct irqaction), GFP_KERNEL);//分配空间 
　　 if (!action) 
　　 return -ENOMEM; 
　　
　　 action->handler = handler; //中断处理函数
　　 action->flags = irq_flags; //中断标志
　　 cpus_clear(action->mask);//mask=0 
　　 action->name = devname; //设备名称
　　 action->next = NULL; //链接
　　 action->dev_id = dev_id;//中断函数第2个参数 
　　 retval = setup_irq(irq, action);//将建立的action于给irq_desc中的中断成员结构 
　　
　　 if (retval) 
　　 kfree(action); 
　　 return retval; 
　　}即中断申请函数是创建并初始化irqdesc-> action成员.
　　 那么驱动中的中断处理函数付给irqdesc-> action-> handler后是如何被调用的呢?
　　 在初始化handler时，已将do_level_IRQ或do_edge_IRQ付给了irqdesc->handler，当中断相应后内核将调用irqdesc->handler函数，而do_level_IRQ或do_edge_IRQ都先是清除中断的源悬挂寄存器和中断悬挂寄存器后再通过
　　__do_irq(irq, desc->action, regs)调用__do_irq函数，在此函数中将 desc->action获取的中断处理函数调用并执行，要足以一个细节：中断处理成功后一定要返回IRQ_HANDLED，否则出错。__do_irq处理代码大致如下：
　　...........
　　do { 
　　 ret = action->handler(irq, action->dev_id, regs);//调用中断处理函数 
　　 if (ret == IRQ_HANDLED)//中断处理成功 
　　 status |= action->flags; 
　　 retval |= ret; 
　　 action = action->next;//若为共享中断时则执行链表下一个处理函数，非则推出 
　　 } while (action);
　　注意：
　　 在编写驱动时有关中断的操作是经常要用到的，内核驱动中已经编写了一些中断配置函数可以方便的供使用,其与gpio操作配置函数配合使用效果更好。
　　void disable_irq(unsigned int); //关闭相应中断号中断
　　void enable_irq(unsigned int);//开启相应中断号中断
　　int set_irq_type(unsigned int irq, unsigned int type);//设置中断为何种触发模式
　　void disable_irq_wake(unsigned int irq); //禁止中断唤醒功能
　　void enable_irq_wake(unsigned int irq);//使能中断唤醒功能
