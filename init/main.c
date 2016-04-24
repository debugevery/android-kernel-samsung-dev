/*
 *  linux/init/main.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  GK 2/5/95  -  Changed to support mounting root fs via NFS
 *  Added initrd & change_root: Werner Almesberger & Hans Lermen, Feb '96
 *  Moan early if gcc is old, avoiding bogus kernels - Paul Gortmaker, May '96
 *  Simplified starting of init:  Michael A. Griffith <grif@acm.org> 
 */

//#include <linux/types.h>
//#include <linux/module.h>
//#include <linux/proc_fs.h>
//#include <linux/kernel.h>
//#include <linux/syscalls.h>
//#include <linux/stackprotector.h>
//#include <linux/string.h>
//#include <linux/ctype.h>
//#include <linux/delay.h>
//#include <linux/ioport.h>
//#include <linux/init.h>
//#include <linux/smp_lock.h>
//#include <linux/initrd.h>
//#include <linux/bootmem.h>
//#include <linux/acpi.h>
//#include <linux/tty.h>
//#include <linux/percpu.h>
//#include <linux/kmod.h>
//#include <linux/vmalloc.h>
//#include <linux/kernel_stat.h>
//#include <linux/start_kernel.h>
//#include <linux/security.h>
//#include <linux/smp.h>
//#include <linux/workqueue.h>
//#include <linux/profile.h>
//#include <linux/rcupdate.h>
//#include <linux/moduleparam.h>
//#include <linux/kallsyms.h>
//#include <linux/writeback.h>
//#include <linux/cpu.h>
//#include <linux/cpuset.h>
//#include <linux/cgroup.h>
//#include <linux/efi.h>
//#include <linux/tick.h>
//#include <linux/interrupt.h>
//#include <linux/taskstats_kern.h>
//#include <linux/delayacct.h>
//#include <linux/unistd.h>
//#include <linux/rmap.h>
//#include <linux/mempolicy.h>
//#include <linux/key.h>
//#include <linux/buffer_head.h>
//#include <linux/page_cgroup.h>
//#include <linux/debug_locks.h>
//#include <linux/debugobjects.h>
//#include <linux/lockdep.h>
//#include <linux/kmemleak.h>
//#include <linux/pid_namespace.h>
//#include <linux/device.h>
//#include <linux/kthread.h>
//#include <linux/sched.h>
//#include <linux/signal.h>
//#include <linux/idr.h>
//#include <linux/kgdb.h>
//#include <linux/ftrace.h>
//#include <linux/async.h>
//#include <linux/kmemcheck.h>
//#include <linux/kmemtrace.h>
//#include <linux/sfi.h>
//#include <linux/shmem_fs.h>
//#include <linux/slab.h>
//#include <trace/boot.h>

//#include <asm/io.h>
//#include <asm/bugs.h>
//#include <asm/setup.h>
//#include <asm/sections.h>
//#include <asm/cacheflush.h>

#ifdef CONFIG_X86_LOCAL_APIC
//#include <asm/smp.h>
#endif

static int kernel_init(void *);

extern void init_IRQ(void);
extern void fork_init(unsigned long);
extern void mca_init(void);
extern void sbus_init(void);
extern void prio_tree_init(void);
extern void radix_tree_init(void);
extern void free_initmem(void);
#ifndef CONFIG_DEBUG_RODATA
static inline void mark_rodata_ro(void) { }
#endif

#ifdef CONFIG_TC
extern void tc_init(void);
#endif

enum system_states system_state __read_mostly;
//EXPORT_SYMBOL(system_state);

/*
 * Boot command-line arguments启动命令行参数==================
 */
#define MAX_INIT_ARGS CONFIG_INIT_ENV_ARG_LIMIT
#define MAX_INIT_ENVS CONFIG_INIT_ENV_ARG_LIMIT

extern void time_init(void);
/* Default late time init is NULL. archs can override this later. */
void (*/* __initdata */ late_time_init)(void);
extern void softirq_init(void);

/* Untouched command line saved by arch-specific code. */
char /* __initdata */ boot_command_line[COMMAND_LINE_SIZE];
/* Untouched saved command line (eg. for /proc) */
char *saved_command_line;
/* Command line for parameter parsing */
static char *static_command_line;

static char *execute_command;
static char *ramdisk_execute_command;

#ifdef CONFIG_SMP
/* Setup configured maximum number of CPUs to activate */
unsigned int setup_max_cpus = NR_CPUS;
//EXPORT_SYMBOL(setup_max_cpus);


/*
 * Setup routine for controlling SMP activation
 *
 * Command-line option of "nosmp" or "maxcpus=0" will disable SMP
 * activation entirely (the MPS table probe still happens, though).
 *
 * Command-line option of "maxcpus=<NUM>", where <NUM> is an integer
 * greater than 0, limits the maximum number of CPUs activated in
 * SMP mode to <NUM>.
 */

void __weak arch_disable_smp_support(void) { }

static int __init nosmp(char *str)
{
	setup_max_cpus = 0;
	arch_disable_smp_support();

	return 0;
}

early_param("nosmp", nosmp);

/* this is hard limit */
static int __init nrcpus(char *str)
{
	int nr_cpus;

	get_option(&str, &nr_cpus);
	if (nr_cpus > 0 && nr_cpus < nr_cpu_ids)
		nr_cpu_ids = nr_cpus;

	return 0;
}

early_param("nr_cpus", nrcpus);

static int __init maxcpus(char *str)
{
	get_option(&str, &setup_max_cpus);
	if (setup_max_cpus == 0)
		arch_disable_smp_support();

	return 0;
}

early_param("maxcpus", maxcpus);
#else
static const unsigned int setup_max_cpus = NR_CPUS;
#endif

/*
 * If set, this is an indication to the drivers that reset the underlying
 * device before going ahead with the initialization otherwise driver might
 * rely on the BIOS and skip the reset operation.
 *
 * This is useful if kernel is booting in an unreliable environment.
 * For ex. kdump situaiton where previous kernel has crashed, BIOS has been
 * skipped and devices will be in unknown state.
 */
unsigned int reset_devices;
//EXPORT_SYMBOL(reset_devices);

static int __init set_reset_devices(char *str)
{
	reset_devices = 1;
	return 1;
}

__setup("reset_devices", set_reset_devices);

static char * argv_init[MAX_INIT_ARGS+2] = { "init", NULL, };
char * envp_init[MAX_INIT_ENVS+2] = { "HOME=/", "TERM=linux", NULL, };
static const char *panic_later, *panic_param;

extern struct obs_kernel_param __setup_start[], __setup_end[];

static int __init obsolete_checksetup(char *line)
{
	struct obs_kernel_param *p;
	int had_early_param = 0;

	p = __setup_start;
	do {
		int n = strlen(p->str);
		if (!strncmp(line, p->str, n)) {
			if (p->early) {
				/* Already done in parse_early_param?
				 * (Needs exact match on param part).
				 * Keep iterating, as we can have early
				 * params and __setups of same names 8( */
				if (line[n] == '\0' || line[n] == '=')
					had_early_param = 1;
			} else if (!p->setup_func) {
				printk(KERN_WARNING "Parameter %s is obsolete,"
				       " ignored\n", p->str);
				return 1;
			} else if (p->setup_func(line + n))
				return 1;
		}
		p++;
	} while (p < __setup_end);

	return had_early_param;
}

/*
 * This should be approx 2 Bo*oMips to start (note initial shift), and will
 * still work even if initially too large, it will just take slightly longer
 */
unsigned long loops_per_jiffy = (1<<12);

//EXPORT_SYMBOL(loops_per_jiffy);

static int __init debug_kernel(char *str)
{
	console_loglevel = 10;
	return 0;
}

static int __init quiet_kernel(char *str)
{
	console_loglevel = 4;
	return 0;
}

early_param("debug", debug_kernel);
early_param("quiet", quiet_kernel);

static int __init loglevel(char *str)
{
	get_option(&str, &console_loglevel);
	return 0;
}

early_param("loglevel", loglevel);

/*
 * Unknown boot options get handed to init, unless they look like
 * unused parameters (modprobe will find them in /proc/cmdline).
 */
static int __init unknown_bootoption(char *param, char *val)
{
	/* Change NUL term back to "=", to make "param" the whole string. */
	if (val) {
		/* param=val or param="val"? */
		if (val == param+strlen(param)+1)
			val[-1] = '=';
		else if (val == param+strlen(param)+2) {
			val[-2] = '=';
			memmove(val-1, val, strlen(val)+1);
			val--;
		} else
			BUG();
	}

	/* Handle obsolete-style parameters */
	if (obsolete_checksetup(param))
		return 0;

	/* Unused module parameter. */
	if (strchr(param, '.') && (!val || strchr(param, '.') < val))
		return 0;

	if (panic_later)
		return 0;

	if (val) {
		/* Environment option */
		unsigned int i;
		for (i = 0; envp_init[i]; i++) {
			if (i == MAX_INIT_ENVS) {
				panic_later = "Too many boot env vars at `%s'";
				panic_param = param;
			}
			if (!strncmp(param, envp_init[i], val - param))
				break;
		}
		envp_init[i] = param;
	} else {
		/* Command line option */
		unsigned int i;
		for (i = 0; argv_init[i]; i++) {
			if (i == MAX_INIT_ARGS) {
				panic_later = "Too many boot init vars at `%s'";
				panic_param = param;
			}
		}
		argv_init[i] = param;
	}
	return 0;
}

#ifdef CONFIG_DEBUG_PAGEALLOC
int __read_mostly debug_pagealloc_enabled = 0;
#endif

static int __init init_setup(char *str)
{
	unsigned int i;

	execute_command = str;
	/*
	 * In case LILO is going to boot us with default command line,
	 * it prepends "auto" before the whole cmdline which makes
	 * the shell think it should execute a script with such name.
	 * So we ignore all arguments entered _before_ init=... [MJ]
	 */
	for (i = 1; i < MAX_INIT_ARGS; i++)
		argv_init[i] = NULL;
	return 1;
}
__setup("init=", init_setup);

static int __init rdinit_setup(char *str)
{
	unsigned int i;

	ramdisk_execute_command = str;
	/* See "auto" comment in init_setup */
	for (i = 1; i < MAX_INIT_ARGS; i++)
		argv_init[i] = NULL;
	return 1;
}
__setup("rdinit=", rdinit_setup);

#ifndef CONFIG_SMP

#ifdef CONFIG_X86_LOCAL_APIC
static void __init smp_init(void)
{
	APIC_init_uniprocessor();
}
#else
#define smp_init()	do { } while (0)
#endif

static inline void setup_nr_cpu_ids(void) { }
static inline void smp_prepare_cpus(unsigned int maxcpus) { }

#else

/* Setup number of possible processor ids */
int nr_cpu_ids __read_mostly = NR_CPUS;
//EXPORT_SYMBOL(nr_cpu_ids);

/* An arch may set nr_cpu_ids earlier if needed, so this would be redundant */
static void __init setup_nr_cpu_ids(void)
{
	nr_cpu_ids = find_last_bit(cpumask_bits(cpu_possible_mask),NR_CPUS) + 1;
}

/* Called by boot processor to activate the rest. */
static void __init smp_init(void)
{
	unsigned int cpu;

	/* FIXME: This should be done in userspace --RR */
	for_each_present_cpu(cpu) {
		if (num_online_cpus() >= setup_max_cpus)
			break;
		if (!cpu_online(cpu))
			cpu_up(cpu);
	}

	/* Any cleanup work */
	printk(KERN_INFO "Brought up %ld CPUs\n", (long)num_online_cpus());
	smp_cpus_done(setup_max_cpus);
}

#endif

/*
 * We need to store the untouched command line for future reference.
 * We also need to store the touched command line since the parameter
 * parsing is performed in place, and we should allow a component to
 * store reference of name/value for future reference.
 */
static void __init setup_command_line(char *command_line)
{
	saved_command_line = alloc_bootmem(strlen (boot_command_line)+1);
	static_command_line = alloc_bootmem(strlen (command_line)+1);
	strcpy (saved_command_line, boot_command_line);
	strcpy (static_command_line, command_line);
}

/*
 * We need to finalize in a non-__init function or else race conditions
 * between the root thread and the init thread may cause start_kernel to
 * be reaped by free_initmem before the root thread has proceeded to
 * cpu_idle.
 *
 * gcc-3.4 accidentally inlines this function, so use noinline.
 */

static /* __initdata */ DECLARE_COMPLETION(kthreadd_done);

static noinline void __init_refok rest_init(void)
	__releases(kernel_lock)
{
	int pid;

	rcu_scheduler_starting();
	/*
	 * We need to spawn init first so that it obtains pid 1, however
	 * the init task will end up wanting to create kthreads, which, if
	 * we schedule it before we create kthreadd, will OOPS.
	 */
	kernel_thread(kernel_init, NULL, CLONE_FS | CLONE_SIGHAND);//启动init线程
	numa_default_policy();
	pid = kernel_thread(kthreadd, NULL, CLONE_FS | CLONE_FILES);
	rcu_read_lock();
	kthreadd_task = find_task_by_pid_ns(pid, &init_pid_ns);
	rcu_read_unlock();
	complete(&kthreadd_done);
	unlock_kernel();

	/*
	 * The boot idle thread must execute schedule()
	 * at least once to get things moving:
	 */
	init_idle_bootup_task(current);
	preempt_enable_no_resched();
	schedule();//启动调度器
	preempt_disable();

	/* Call into cpu_idle with preempt disabled */
	cpu_idle();//cpu空闲，实际上就是启动进程进入空闲状态，系统交给调度器来管理
}

/* Check for early params. */
static int __init do_early_param(char *param, char *val)
{
	struct obs_kernel_param *p;

	for (p = __setup_start; p < __setup_end; p++) {
		if ((p->early && strcmp(param, p->str) == 0) ||
		    (strcmp(param, "console") == 0 &&
		     strcmp(p->str, "earlycon") == 0)
		) {
			if (p->setup_func(val) != 0)
				printk(KERN_WARNING
				       "Malformed early option '%s'\n", param);
		}
	}
	/* We accept everything at this stage. */
	return 0;
}

void __init parse_early_options(char *cmdline)
{
	parse_args("early options", cmdline, NULL, 0, do_early_param);
}

/* Arch code calls this early on, or if not, just before other parsing. */
void __init parse_early_param(void)
{
	static /* __initdata */ int done = 0;
	static /* __initdata */ char tmp_cmdline[COMMAND_LINE_SIZE];

	if (done)
		return;

	/* All fall through to do_early_param. */
	strlcpy(tmp_cmdline, boot_command_line, COMMAND_LINE_SIZE);
	parse_early_options(tmp_cmdline);
	done = 1;
}

/*
 *	Activate the first processor.
 */

static void __init boot_cpu_init(void)
{
	int cpu = smp_processor_id();
	/* Mark the boot cpu "present", "online" etc for SMP and UP case */
	set_cpu_online(cpu, true);
	set_cpu_active(cpu, true);
	set_cpu_present(cpu, true);
	set_cpu_possible(cpu, true);
}

void __init __weak smp_setup_processor_id(void)
{
}

void __init __weak thread_info_cache_init(void)
{
}

/*
 * Set up kernel memory allocators
 */
static void __init mm_init(void)
{
	/*
	 * page_cgroup requires countinous pages as memmap
	 * and it's bigger than MAX_ORDER unless SPARSEMEM.
	 */
	page_cgroup_init_flatmem();
	mem_init();
	kmem_cache_init();
	pgtable_cache_init();
	vmalloc_init();
}
//内核的初始化过程由start_kernel函数开始，至第一个用户进程init结束，
//调用了一系列的初始化函数对所有的内核组件进行初始化。其中，start_kernel、
//rest_init、kernel_init、init_post等4个函数构成了整个初始化过程的主线。
asmlinkage void __init start_kernel(void)
{
	char * command_line;
	extern struct kernel_param __start___param[], __stop___param[];
        /*           
        * 当只有一个CPU的时候这个函数就什么都不做，但是如果有多个CPU的时候那么它就           
        * 返回在启动的时候的那个CPU的号           
        */ 
	smp_setup_processor_id();

	/*
	 * Need to run as early as possible, to initialize the
	 * lockdep hash:
	 */
	lockdep_init();
	debug_objects_early_init();

	/*
	 * Set up the the initial canary ASAP:
	 */
	boot_init_stack_canary();

	cgroup_init_early();
	/* 关闭当前CPU的中断 */ 
	local_irq_disable();
	early_boot_irqs_off();
	/*           
	* 每一个中断都有一个中断描述符（struct irq_desc）来进行描述，这个函数的           
	* 作用就是设置所有中断描述符的锁           
	*/ 
	early_init_irq_lock_class();

/*
 * Interrupts are still disabled. Do necessary setups, then
 * enable them
 */	
	lock_kernel();/* 获取大内核锁，锁定整个内核。 */ 
	tick_init();/* 如果定义了CONFIG_GENERIC_CLOCKEVENTS，则注册clockevents框架 */  
	boot_cpu_init();
	page_address_init();/* 初始化页地址，使用链表将其链接起来 */  
	printk(KERN_NOTICE "%s", linux_banner); /* 显示内核的版本信息 */ 
	/*           
	* 每种体系结构都有自己的setup_arch()函数，是体系结构相关的，具体编译哪个
	* 体系结构的setup_arch()函数,由源码树顶层目录下的Makefile中的ARCH变量决定
	函数原型在arch/arm/kernel/setup.c中 根据处理器、硬件平台具体型号设置系统。
	解析Linux系统命令行，设置0号进程（swapper进程）的内存描述结构init_mm，
	系统内存管理初始化，统计并注册系统各种资源，其他项目的初始化。*/  
	setup_arch(&command_line);//完成内存映像的初始化，其中command_line是从bootloader中传下来的。
	mm_init_owner(&init_mm, &init_task);
	setup_command_line(command_line);
	setup_nr_cpu_ids();
	setup_per_cpu_areas();/* 每个CPU分配pre-cpu结构内存， 并复制.data.percpu段的数据 */  
	smp_prepare_boot_cpu();	/* arch-specific boot-cpu hooks */

	build_all_zonelists(NULL);//建立系统内存页区（zone）链表。
	page_alloc_init();
	/* 打印Linux启动命令行参数 */ 
	printk(KERN_NOTICE "Kernel command line: %s\n", boot_command_line);
	parse_early_param();/* 对内核选项的两次解析 */  
	parse_args("Booting kernel", static_command_line, __start___param,
		   __stop___param - __start___param,
		   &unknown_bootoption);
	/*
	 * These use large bootmem allocations and must precede
	 * kmem_cache_init()
	 */
	pidhash_init();/* 初始化hash表，便于从进程的PID获得对应的进程描述符指针 .设置系统中每种pid hash表中的hash链表数的移位值全局变量pidhash_shift，将pidhash_shift设置为min(12);分别为每种hash表的连续hash链表表头结构空间申请内存，把申请到的内存虚拟基址分别传给pid_hash[n](n=0~3),并将每种hash表中的每个hash链表表头结构struct hlist_head中的first成员指针设置成NULL*/ 
	vfs_caches_init_early();/* 虚拟文件系统的初始化 */  
	sort_main_extable();/* slab初始化.将放在__start__ex_table到__stop__ex_table之间的*(__ex_table)区中的struct exception_table_entry型全局结构变量按insn成员变量值从小到大排序，即将可能导致缺页异常的指令按其指令二进制代码值从小到大排序。 */  
	/*           
	* trap_init函数完成对系统保留中断向量（异常、非屏蔽中断以及系统调用）
	* 的初始化，init_IRQ函数则完成其余中断向量的初始化           
	*/ 
	trap_init();//把放在.Lcvectors处的系统8个意外的入口跳转指令搬到高端中断向量0xffff0000处，再将从__stubs_start到__stubs_end之间的各种意外初始处理代码搬到0xffff0200处。刷新0xffff0000处1页范围的指令cache,将DOMAIN_USER的访问权限由DOMAIN_MANAGER权限改设置成DOMAIN_CLIENT权限。
	mm_init();//该函数执行完后不能再用像alloc_bootmem()、alloc_bootmem_low()、alloc_bootmem_pages()等申请低端内存的函数来申请内存，也就不能申请大块的连续物理内存了。
	/*
	 * Set up the scheduler prior starting any interrupts (such as the
	 * timer interrupt). Full topology setup happens at smp_init()
	 * time - but meanwhile we still have a functioning scheduler.
	 */
	sched_init();/* 进程调度器初始化 ,初始化每个处理器的可运行进程队列，设置系统初始化进程即0号进程。*/  
	/*
	 * Disable preemption - early bootup scheduling is extremely
	 * fragile until we cpu_idle() for the first time.
	 */
	preempt_disable();/* 禁止内核抢占 */  
	if (!irqs_disabled()) {/* 检查中断是否已经打开，如果已经打开，则关闭中断 */  
		printk(KERN_WARNING "start_kernel(): bug: interrupts were "
				"enabled *very* early, fixing it\n");
		local_irq_disable();
	}
	rcu_init();/* 初始化RCU(Read-Copy Update)机制.初始化当前CPU的读、复制、更新数据结构(struct rcu_data)全局变量per_cpu_rcu_data和per_cpu_rcu_bh_data。 */  
	radix_tree_init();
	/* init some links before init_ISA_irqs() */
	early_irq_init();
	init_IRQ();//初始化系统中支持的最大可能中断数的中断描述结构struct irqdesc变量数组irq_desc[NR_IRQS]，把每个结构变量irq_desc[n]都初始化为预先定义好的坏中断描述结构变量bad_irq_desc，并初始化该中断的连表表头成员结构变量pend.
	prio_tree_init();/* 初始化优先级树index_bits_to_maxindex数组 */  
	init_timers();/* 初始化定时器相关的数据结构.初始化当前出处理器的时间向量基本结构struct tvec_t_base_s全局变量per_cpu_tvec_bases,初始化per_cpu_tvec_bases的自旋锁成员变量lock。 */  
	hrtimers_init();/* 对高精度时钟进行初始化 */  
	softirq_init();//设置系统小任务软件中断行为函数描述结构变量softirq_vec[TASKLET_SOFTIRQ(=6)],将softirq_vec[6]的行动函数指针action指向tasklet_action()函数，参数指针设置为NULL.
	timekeeping_init();
	time_init();/* 初始化系统时钟源 .检查系统定时器描述结构struct sys_timer全局变量system_timer是否为空，如果是将其指向dummy_gettimeoffset()函数。 */  
	profile_init();/* 对内核的profile（一个内核性能调式工具）功能进行初始化 */  
	if (!irqs_disabled())
		printk(KERN_CRIT "start_kernel(): bug: interrupts were "
				 "enabled early\n");
	early_boot_irqs_on();
	local_irq_enable();//将处理器的当前系统状态寄存器CPSR的第7位清0，使能IRQ中断。

	/* Interrupts are enabled now so all GFP allocations are safe. */
	gfp_allowed_mask = __GFP_BITS_MASK;

	kmem_cache_init_late();//执行高速缓存内存管理即slab分配器相关初始化。

	/*
	 * HACK ALERT! This is early. We're enabling the console before
	 * we've done PCI setups etc, and console_init() must be aware of
	 * this. But we do want output early, in case something goes wrong.
	 */
	/*           
	* 初始化控制台以显示printk的内容，在此之前调用的printk
	* 只是把数据存到缓冲区里          
	*/ 
	console_init();
	if (panic_later)
		panic(panic_later, panic_param);
	/* 如果定义了CONFIG_LOCKDEP宏，则打印锁依赖信息，否则什么也不做 */  
	lockdep_info();

	/*
	 * Need to run this when irqs are enabled, because it wants
	 * to self-test [hard/soft]-irqs on/off lock inversion bugs
	 * too:
	 */
	locking_selftest();

#ifdef CONFIG_BLK_DEV_INITRD
	if (initrd_start && !initrd_below_start_ok &&
	    page_to_pfn(virt_to_page((void *)initrd_start)) < min_low_pfn) {
		printk(KERN_CRIT "initrd overwritten (0x%08lx < 0x%08lx) - "
		    "disabling it.\n",
		    page_to_pfn(virt_to_page((void *)initrd_start)),
		    min_low_pfn);
		initrd_start = 0;
	}
#endif
	page_cgroup_init();
	enable_debug_pagealloc();
	kmemtrace_init();
	kmemleak_init();
	debug_objects_mem_init();
	idr_init_cache();
	setup_per_cpu_pageset();
	numa_policy_init();
	if (late_time_init)
		late_time_init();
	sched_clock_init();
    /*           
    * 一个非常有趣的CPU性能测试函数，可以计算出CPU在1s内执行了多少次一个
    * 极短的循环，计算出来的值经过处理后得到BogoMIPS值（Bogo是Bogus的意思）
    */  	
	calibrate_delay();//计算机系统的BogMIPS数值，即处理器每秒钟执行的指令数。
	pidmap_init();
	anon_vma_init();//该函数调用kmem_cache_create（）函数，为匿名虚拟内存区域链表结构struct anon_vma创建高速缓存内存描述结构kmem_cache_t变量，为该变量命名为“anon_vma"，其对象的构造函数指针指向void anon_vma_ctor(void *data,kmem_cache_t *cachep,unsigned long flags)函数，析构函数指针空，将创建的kmem_cache_t结构变量地址传给全局指针anon_vma_chachep。
#ifdef CONFIG_X86
	if (efi_enabled)
		efi_enter_virtual_mode();
#endif
	thread_info_cache_init();
	cred_init();
	fork_init(totalram_pages);/* 根据物理内存大小计算允许创建进程的数量 */  
	proc_caches_init();
	buffer_init();//调用 kmem_cache_create("buffer_head", sizeof(struct buffer_head), 0, SLAB_PANIC, init_buffer_head, NULL)函数为缓冲区描述结构struct buffer_head创建高速缓存内存描述结构kmem_cache_t变量。
	key_init();
	security_init();//打印”安全架构v1.0.0被初始化“。如果没有定义系统哑元安全操作函数组结构全局变量dummy_security_ops,打印错误信息，返回I/O错误。
	dbg_late_init();
	vfs_caches_init(totalram_pages);
	signals_init();//调用kmem_cache_create("sigqueue", sizeof(struct sigqueue), __alignof__(struct sigqueue), SLAB_PANIC, NULL, NULL)函数为信号队列结构struct sigqueue创建高速缓存内存描述结构kmem_cache_t变量，名字叫”sigqueue“，不要求其对象按处理器硬件cache line大小对齐，没有定义其对象的构造和析构函数，将创建号的kmem_cache_t结构变量的地址传给全局指针sigqueue_cachep。
	/* rootfs populating might need page-writeback */
	page_writeback_init();//统计系统中所有内存节点的通用(NORMAL)内存页区中高页数水印值页数之外的额外内存总页数之和传给buffer_pages。
#ifdef CONFIG_PROC_FS
	proc_root_init();//只有在系统支持proc文件系统即配置了CONFIG_PROC_FS选项时才被调用。
#endif
	cgroup_init();
	cpuset_init();
	taskstats_init_early();
	delayacct_init();
    /*           
    * 测试该CPU的各种缺陷，记录检测到的缺陷，以便于内核的其他部分以后可以
    * 使用它们的工作。           
    */  
	check_bugs();

	acpi_early_init(); /* before LAPIC and SMP init */
	sfi_init_late();

	ftrace_init();

	/* Do the rest non-__init'ed, we're now alive */
	rest_init();/* 创建init进程.该函数创建init()内核进程即1号进程，然后是系统启动进程即0号进程空闲。 */  
}

/* Call all constructor functions linked into the kernel. */
static void __init do_ctors(void)
{
#ifdef CONFIG_CONSTRUCTORS
	ctor_fn_t *fn = (ctor_fn_t *) __ctors_start;

	for (; fn < (ctor_fn_t *) __ctors_end; fn++)
		(*fn)();
#endif
}

int initcall_debug;
core_param(initcall_debug, initcall_debug, bool, 0644);

static char msgbuf[64];
static struct boot_trace_call call;
static struct boot_trace_ret ret;

int do_one_initcall(initcall_t fn)
{
	int count = preempt_count();
	ktime_t calltime, delta, rettime;

	if (initcall_debug) {
		call.caller = task_pid_nr(current);
		printk("calling  %pF @ %i\n", fn, call.caller);
		calltime = ktime_get();
		trace_boot_call(&call, fn);
		enable_boot_trace();
	}

	ret.result = fn();

	if (initcall_debug) {
		disable_boot_trace();
		rettime = ktime_get();
		delta = ktime_sub(rettime, calltime);
		ret.duration = (unsigned long long) ktime_to_ns(delta) >> 10;
		trace_boot_ret(&ret, fn);
		printk("initcall %pF returned %d after %Ld usecs\n", fn,
			ret.result, ret.duration);
	}

	msgbuf[0] = 0;

	if (ret.result && ret.result != -ENODEV && initcall_debug)
		sprintf(msgbuf, "error code %d ", ret.result);

	if (preempt_count() != count) {
		strlcat(msgbuf, "preemption imbalance ", sizeof(msgbuf));
		preempt_count() = count;
	}
	if (irqs_disabled()) {
		strlcat(msgbuf, "disabled interrupts ", sizeof(msgbuf));
		local_irq_enable();
	}
	if (msgbuf[0]) {
		printk("initcall %pF returned with %s\n", fn, msgbuf);
	}

	return ret.result;
}


extern initcall_t __initcall_start[], __initcall_end[], __early_initcall_end[];

static void __init do_initcalls(void)
{
	initcall_t *fn;

	for (fn = __early_initcall_end; fn < __initcall_end; fn++)
		do_one_initcall(*fn);

	/* Make sure there is no pending stuff from the initcall sequence */
	flush_scheduled_work();
}

/*
 * Ok, the machine is now initialized. None of the devices
 * have been touched yet, but the CPU subsystem is up and
 * running, and memory and process management works.
 *
 * Now we can finally start doing some real work..
 */
static void __init do_basic_setup(void)
{
	init_workqueues();//初始化工作队列
	cpuset_init_smp();
	usermodehelper_init();//用户模式help程序
	init_tmpfs();
	driver_init(); //设备初始化
	init_irq_proc();
	do_ctors();
	do_initcalls();//非常重要的一个函数，会在这里执行驱动模块加载函数，也就module_init()的函数。
}

static void __init do_pre_smp_initcalls(void)
{
	initcall_t *fn;

	for (fn = __initcall_start; fn < __early_initcall_end; fn++)
		do_one_initcall(*fn);
}

static void run_init_process(char *init_filename)
{
	argv_init[0] = init_filename;
	kernel_execve(init_filename, argv_init, envp_init);
}

/* This is a non __init function. Force it to be noinline otherwise gcc
 * makes it inline to init() and it becomes part of init.text section
 */
static noinline int init_post(void)
	__releases(kernel_lock)
{
	/* need to finish all async __init code before freeing the memory */
	async_synchronize_full();
	free_initmem();
	unlock_kernel();
	mark_rodata_ro();
	system_state = SYSTEM_RUNNING;
	numa_default_policy();


	current->signal->flags |= SIGNAL_UNKILLABLE;

	if (ramdisk_execute_command) {
		run_init_process(ramdisk_execute_command);
		printk(KERN_WARNING "Failed to execute %s\n",
				ramdisk_execute_command);
	}

	/*
	 * We try each of these until one succeeds.
	 *
	 * The Bourne shell can be used instead of init if we are
	 * trying to recover a really broken machine.
	 */
	if (execute_command) {
		run_init_process(execute_command);
		printk(KERN_WARNING "Failed to execute %s.  Attempting "
					"defaults...\n", execute_command);
	}
	run_init_process("/sbin/init");
	run_init_process("/etc/init");
	run_init_process("/bin/init");
	run_init_process("/bin/sh");//启动shell

	panic("No init found.  Try passing init= option to kernel. "
	      "See Linux Documentation/init.txt for guidance.");
}

static int __init kernel_init(void * unused)
{
	/*
	 * Wait until kthreadd is all set-up.
	 */
	wait_for_completion(&kthreadd_done);
	lock_kernel();

	/*
	 * init can allocate pages on any node
	 */
	set_mems_allowed(node_states[N_HIGH_MEMORY]);
	/*
	 * init can run on any cpu.
	 */
	set_cpus_allowed_ptr(current, cpu_all_mask);
	/*
	 * Tell the world that we're going to be the grim
	 * reaper of innocent orphaned children.
	 *
	 * We don't want people to have to make incorrect
	 * assumptions about where in the task array this
	 * can be found.
	 */
	init_pid_ns.child_reaper = current;

	cad_pid = task_pid(current);

	smp_prepare_cpus(setup_max_cpus);

	do_pre_smp_initcalls();
	start_boot_trace();

	smp_init();
	sched_init_smp();

	do_basic_setup();//很重要的一个函数，做一些基本的设置

	/* Open the /dev/console on the rootfs, this should never fail */
	if (sys_open((const char __user *) "/dev/console", O_RDWR, 0) < 0)//打开终端
		printk(KERN_WARNING "Warning: unable to open an initial console.\n");

	(void) sys_dup(0);
	(void) sys_dup(0);
	/*
	 * check if there is an early userspace init.  If yes, let it do all
	 * the work
	 */

	if (!ramdisk_execute_command)
		ramdisk_execute_command = "/init";

	if (sys_access((const char __user *) ramdisk_execute_command, 0) != 0) {
		ramdisk_execute_command = NULL;
		prepare_namespace();
	}

	/*
	 * Ok, we have completed the initial bootup, and
	 * we're essentially up and running. Get rid of the
	 * initmem segments and start the user-mode stuff..
	 */

	init_post();
	return 0;
}
