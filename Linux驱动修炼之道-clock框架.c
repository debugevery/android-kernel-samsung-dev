Linux驱动修炼之道-clock框架 .
分类： linux驱动编程 2011-05-17 10:16 1394人阅读 评论(4) 收藏 举报 
努力成为linux kernel hacker的人李万鹏原创作品，为梦而战。转载请标明出处

http://blog.csdn.net/woshixingaaa/archive/2011/05/17/6426203.aspx

内核启动时，会调用s3c24xx_register_clock函数注册很多时钟，所谓注册，就是在一个链表中保存各种"struct clk*"结构指针，这些"struct clk"结构有:clk_f(表示FCLK)，clk_h(表示HCLK)，clk_p(表示PCLK)等。然后可以通过clk_get_rate函数获得获得某类时钟频率。下面到内核中分析一下源码，这里跟踪内核启动时clock system的初始化过程：

[c-sharp] view plaincopyprint?
01.asmlinkage void __init start_kernel(void)  
02.{  
03.    ............  
04.    setup_arch(&command_line);  
05.    ............  
06.}  
asmlinkage void __init start_kernel(void)
{
	............
	setup_arch(&command_line);
	............
} 

start_kernel调用了setup_arch(&command_line)：

[c-sharp] view plaincopyprint?
01.void __init setup_arch(char **cmdline_p)  
02.{  
03.    ..........  
04.    paging_init(mdesc);  
05.    ..........  
06.}  
void __init setup_arch(char **cmdline_p)
{
	..........
	paging_init(mdesc);
	..........
} 

setup_arch调用了paging_init(mdesc)：

[c-sharp] view plaincopyprint?
01.void __init paging_init(struct machine_desc *mdesc){  
02.    .............  
03.    devicemaps_init(mdesc);  
04.    .............  
05.}  
void __init paging_init(struct machine_desc *mdesc){
	.............
	devicemaps_init(mdesc);
	.............
} 

paging_init调用了devicemaps_init(mdesc)：

[c-sharp] view plaincopyprint?
01.static void __init devicemaps_init(struct machine_desc *mdesc)  
02.{  
03.    ....................  
04.    /*这里调用具体体系结构的map_io函数*/  
05.    if (mdesc->map_io)  
06.        mdesc->map_io();  
07.    ...................   
08.}  
static void __init devicemaps_init(struct machine_desc *mdesc)
{
	....................
	/*这里调用具体体系结构的map_io函数*/
	if (mdesc->map_io)
		mdesc->map_io();
	...................	
} 

在我们板子的文件中查到这个map_io函数：

[c-sharp] view plaincopyprint?
01.static void __init smdk2440_map_io(void)  
02.{  
03.    s3c24xx_init_io(smdk2440_iodesc, ARRAY_SIZE(smdk2440_iodesc));  
04.    s3c24xx_init_clocks(12000000);  
05.    s3c24xx_init_uarts(smdk2440_uartcfgs, ARRAY_SIZE(smdk2440_uartcfgs));  
06.}  
static void __init smdk2440_map_io(void)
{
	s3c24xx_init_io(smdk2440_iodesc, ARRAY_SIZE(smdk2440_iodesc));
	s3c24xx_init_clocks(12000000);
	s3c24xx_init_uarts(smdk2440_uartcfgs, ARRAY_SIZE(smdk2440_uartcfgs));
} 

这个函数有一句s3c24xx_init_clocks(12000000);跟踪进去：

[c-sharp] view plaincopyprint?
01./* s3c24xx_init_clocks 
02. * 
03. * Initialise the clock subsystem and associated information from the 
04. * given master crystal value. 
05. * 
06. * xtal  = 0 -> use default PLL crystal value (normally 12MHz) 
07. *      != 0 -> PLL crystal value in Hz 
08.*/  
09.  
10.void __init s3c24xx_init_clocks(int xtal)  
11.{  
12.    if (xtal == 0)  
13.        xtal = 12*1000*1000;  
14.  
15.    if (cpu == NULL)  
16.        panic("s3c24xx_init_clocks: no cpu setup?/n");  
17.  
18.    if (cpu->init_clocks == NULL)  
19.        panic("s3c24xx_init_clocks: cpu has no clock init/n");  
20.    else  
21.        (cpu->init_clocks)(xtal);  
22.}  
/* s3c24xx_init_clocks
 *
 * Initialise the clock subsystem and associated information from the
 * given master crystal value.
 *
 * xtal  = 0 -> use default PLL crystal value (normally 12MHz)
 *      != 0 -> PLL crystal value in Hz
*/

void __init s3c24xx_init_clocks(int xtal)
{
	if (xtal == 0)
		xtal = 12*1000*1000;

	if (cpu == NULL)
		panic("s3c24xx_init_clocks: no cpu setup?/n");

	if (cpu->init_clocks == NULL)
		panic("s3c24xx_init_clocks: cpu has no clock init/n");
	else
		(cpu->init_clocks)(xtal);
} 

这个函数是设置晶振的频率为12M，也就是我板子上的晶振12M。注意这里最后一句：(cpu->init_clocks)(xtal);我们要查看cpu_table了。

[c-sharp] view plaincopyprint?
01.static struct cpu_table cpu_ids[] __initdata = {  
02.    ......................  
03.    {  
04.        .idcode     = 0x32440001,  
05.        .idmask     = 0xffffffff,  
06.        .map_io     = s3c244x_map_io,  
07.        .init_clocks    = s3c244x_init_clocks,  
08.        .init_uarts = s3c244x_init_uarts,  
09.        .init       = s3c2440_init,  
10.        .name       = name_s3c2440a  
11.    },  
12.    .....................  
13.};  
static struct cpu_table cpu_ids[] __initdata = {
	......................
	{
		.idcode		= 0x32440001,
		.idmask		= 0xffffffff,
		.map_io		= s3c244x_map_io,
		.init_clocks	= s3c244x_init_clocks,
		.init_uarts	= s3c244x_init_uarts,
		.init		= s3c2440_init,
		.name		= name_s3c2440a
	},
	.....................
}; 

在cpu_table中可以找到这个init_clocks函数，也就是我们苦苦寻觅的clock system初始化函数了，真是众里寻他千百度，那人却在灯火阑珊处。

[c-sharp] view plaincopyprint?
01.void __init s3c244x_init_clocks(int xtal)  
02.{  
03.    /* initialise the clocks here, to allow other things like the 
04.     * console to use them, and to add new ones after the initialisation 
05.     */  
06.  
07.    s3c24xx_register_baseclocks(xtal);  
08.    s3c244x_setup_clocks();  
09.    s3c2410_baseclk_add();  
10.}  
void __init s3c244x_init_clocks(int xtal)
{
	/* initialise the clocks here, to allow other things like the
	 * console to use them, and to add new ones after the initialisation
	 */

	s3c24xx_register_baseclocks(xtal);
	s3c244x_setup_clocks();
	s3c2410_baseclk_add();
} 

这个s3c244x_init_clocks完成了clock system全部的初始化工作。现在一个一个来分析里边的3个函数。s3c24xx_register_baseclocks()函数在arch/arm/plat-s3c/clock.c中实现如下：这里对基本的时钟clk_xtal,clk_mpll,clk_upll,clk_f,clk_h,clk_p进行了注册。

[c-sharp] view plaincopyprint?
01.int __init s3c24xx_register_baseclocks(unsigned long xtal)  
02.{  
03.    printk(KERN_INFO "S3C24XX Clocks, (c) 2004 Simtec Electronics/n");  
04.    clk_xtal.rate = xtal;  
05.    /* register our clocks */  
06.  
07.    if (s3c24xx_register_clock(&clk_xtal) < 0)  
08.        printk(KERN_ERR "failed to register master xtal/n");  
09.  
10.    if (s3c24xx_register_clock(&clk_mpll) < 0)  
11.        printk(KERN_ERR "failed to register mpll clock/n");  
12.  
13.    if (s3c24xx_register_clock(&clk_upll) < 0)  
14.        printk(KERN_ERR "failed to register upll clock/n");  
15.  
16.    if (s3c24xx_register_clock(&clk_f) < 0)  
17.        printk(KERN_ERR "failed to register cpu fclk/n");  
18.  
19.    if (s3c24xx_register_clock(&clk_h) < 0)  
20.        printk(KERN_ERR "failed to register cpu hclk/n");  
21.  
22.    if (s3c24xx_register_clock(&clk_p) < 0)  
23.        printk(KERN_ERR "failed to register cpu pclk/n");  
24.  
25.    return 0;  
26.}  
int __init s3c24xx_register_baseclocks(unsigned long xtal)
{
	printk(KERN_INFO "S3C24XX Clocks, (c) 2004 Simtec Electronics/n");
	clk_xtal.rate = xtal;
	/* register our clocks */

	if (s3c24xx_register_clock(&clk_xtal) < 0)
		printk(KERN_ERR "failed to register master xtal/n");

	if (s3c24xx_register_clock(&clk_mpll) < 0)
		printk(KERN_ERR "failed to register mpll clock/n");

	if (s3c24xx_register_clock(&clk_upll) < 0)
		printk(KERN_ERR "failed to register upll clock/n");

	if (s3c24xx_register_clock(&clk_f) < 0)
		printk(KERN_ERR "failed to register cpu fclk/n");

	if (s3c24xx_register_clock(&clk_h) < 0)
		printk(KERN_ERR "failed to register cpu hclk/n");

	if (s3c24xx_register_clock(&clk_p) < 0)
		printk(KERN_ERR "failed to register cpu pclk/n");

	return 0;
} 

下边看一下这个注册函数，主要任务就是把struct clk结构添加到clocks链表中。

[c-sharp] view plaincopyprint?
01./* clock information */  
02.static LIST_HEAD(clocks);  
/* clock information */
static LIST_HEAD(clocks); 

这个是链表的头的注册函数。注册的struct clk结构体都要添加到这个clocks链表中。

[c-sharp] view plaincopyprint?
01./* initialise the clock system */  
02.  
03.int s3c24xx_register_clock(struct clk *clk)  
04.{  
05.    .........  
06.    list_add(&clk->list, &clocks);  
07.    .........  
08.}  
/* initialise the clock system */

int s3c24xx_register_clock(struct clk *clk)
{
	.........
	list_add(&clk->list, &clocks);
	.........
} 

现在来看第二个函数：它的任务就是设置fclk，hclk，pclk，相信如果认真写过arm裸机程序的人一定很容易看懂下边的代码了，可以对照s3c2440的手册来看的。

[c-sharp] view plaincopyprint?
01.void __init_or_cpufreq s3c244x_setup_clocks(void)  
02.{  
03.    .................  
04.    s3c24xx_setup_clocks(fclk, hclk, pclk);  
05.}  
void __init_or_cpufreq s3c244x_setup_clocks(void)
{
	.................
	s3c24xx_setup_clocks(fclk, hclk, pclk);
} 

这里调用了一个s3c24xx_setup_clocks函数，下面看它的实现：

[c-sharp] view plaincopyprint?
01./* initalise all the clocks */  
02.void __init_or_cpufreq s3c24xx_setup_clocks(unsigned long fclk,  
03.                       unsigned long hclk,  
04.                       unsigned long pclk)  
05.{  
06.    clk_upll.rate = s3c24xx_get_pll(__raw_readl(S3C2410_UPLLCON),  
07.                    clk_xtal.rate);  
08.  
09.    clk_mpll.rate = fclk;  
10.    clk_h.rate = hclk;  
11.    clk_p.rate = pclk;  
12.    clk_f.rate = fclk;  
13.}  
/* initalise all the clocks */
void __init_or_cpufreq s3c24xx_setup_clocks(unsigned long fclk,
					   unsigned long hclk,
					   unsigned long pclk)
{
	clk_upll.rate = s3c24xx_get_pll(__raw_readl(S3C2410_UPLLCON),
					clk_xtal.rate);

	clk_mpll.rate = fclk;
	clk_h.rate = hclk;
	clk_p.rate = pclk;
	clk_f.rate = fclk;
} 

就是把得到的fclk,hclk,pclk赋值相应结构体。
下面来看第三个函数，这个主要就是对外设的struct clk进行注册。这个函数一共分两部分，有两个数组，一个是init_clocks，也就是在boot时需要提供时钟的，一个是init_clocks_disable，这里的每个成员都是在boot的时候需要disable时钟的。这两个数组分别进行注册，但是注册init_clocks_disable数组中成员的for循环中调用了s3c2410_clkcon_enable(clkp, 0);也就是将相应的clk disable掉。

[c-sharp] view plaincopyprint?
01.int __init s3c2410_baseclk_add(void)   
02.{   
03.    unsigned long clkslow = __raw_readl(S3C2410_CLKSLOW);   
04.    unsigned long clkcon  = __raw_readl(S3C2410_CLKCON);   
05.    struct clk *clkp;   
06.    struct clk *xtal;   
07.    int ret;   
08.    int ptr;   
09.   
10.    clk_upll.enable = s3c2410_upll_enable;   
11.   
12.    if (s3c24xx_register_clock(&clk_usb_bus) < 0)   
13.        printk(KERN_ERR "failed to register usb bus clock/n");   
14.   
15.    /* register clocks from clock array */   
16.   
17.    clkp = init_clocks;   
18.    for (ptr = 0; ptr < ARRAY_SIZE(init_clocks); ptr++, clkp++) {   
19.        /* ensure that we note the clock state */   
20.   
21.        clkp->usage = clkcon & clkp->ctrlbit ? 1 : 0;   
22.   
23.        ret = s3c24xx_register_clock(clkp);   
24.        if (ret < 0) {   
25.            printk(KERN_ERR "Failed to register clock %s (%d)/n",   
26.                   clkp->name, ret);   
27.        }   
28.    }   
29.   
30.    /* We must be careful disabling the clocks we are not intending to  
31.     * be using at boot time, as subsystems such as the LCD which do  
32.     * their own DMA requests to the bus can cause the system to lockup  
33.     * if they where in the middle of requesting bus access.  
34.     *  
35.     * Disabling the LCD clock if the LCD is active is very dangerous,  
36.     * and therefore the bootloader should be careful to not enable  
37.     * the LCD clock if it is not needed.  
38.    */   
39.   
40.    /* install (and disable) the clocks we do not need immediately */   
41.   
42.    clkp = init_clocks_disable;   
43.    for (ptr = 0; ptr < ARRAY_SIZE(init_clocks_disable); ptr++, clkp++) {   
44.   
45.        ret = s3c24xx_register_clock(clkp);   
46.        if (ret < 0) {   
47.            printk(KERN_ERR "Failed to register clock %s (%d)/n",   
48.                   clkp->name, ret);   
49.        }   
50.   
51.        s3c2410_clkcon_enable(clkp, 0);   
52.    }   
53.   
54.    /* show the clock-slow value */   
55.   
56.    xtal = clk_get(NULL, "xtal");   
57.   
58.    printk("CLOCK: Slow mode (%ld.%ld MHz), %s, MPLL %s, UPLL %s/n",   
59.           print_mhz(clk_get_rate(xtal) /   
60.             ( 2 * S3C2410_CLKSLOW_GET_SLOWVAL(clkslow))),   
61.           (clkslow & S3C2410_CLKSLOW_SLOW) ? "slow" : "fast",   
62.           (clkslow & S3C2410_CLKSLOW_MPLL_OFF) ? "off" : "on",   
63.           (clkslow & S3C2410_CLKSLOW_UCLK_OFF) ? "off" : "on");   
64.   
65.    s3c_pwmclk_init();   
66.    return 0;   
67.}  
int __init s3c2410_baseclk_add(void) 
{ 
	unsigned long clkslow = __raw_readl(S3C2410_CLKSLOW); 
	unsigned long clkcon  = __raw_readl(S3C2410_CLKCON); 
	struct clk *clkp; 
	struct clk *xtal; 
	int ret; 
	int ptr; 
 
	clk_upll.enable = s3c2410_upll_enable; 
 
	if (s3c24xx_register_clock(&clk_usb_bus) < 0) 
		printk(KERN_ERR "failed to register usb bus clock/n"); 
 
	/* register clocks from clock array */ 
 
	clkp = init_clocks; 
	for (ptr = 0; ptr < ARRAY_SIZE(init_clocks); ptr++, clkp++) { 
		/* ensure that we note the clock state */ 
 
		clkp->usage = clkcon & clkp->ctrlbit ? 1 : 0; 
 
		ret = s3c24xx_register_clock(clkp); 
		if (ret < 0) { 
			printk(KERN_ERR "Failed to register clock %s (%d)/n", 
			       clkp->name, ret); 
		} 
	} 
 
	/* We must be careful disabling the clocks we are not intending to 
	 * be using at boot time, as subsystems such as the LCD which do 
	 * their own DMA requests to the bus can cause the system to lockup 
	 * if they where in the middle of requesting bus access. 
	 * 
	 * Disabling the LCD clock if the LCD is active is very dangerous, 
	 * and therefore the bootloader should be careful to not enable 
	 * the LCD clock if it is not needed. 
	*/ 
 
	/* install (and disable) the clocks we do not need immediately */ 
 
	clkp = init_clocks_disable; 
	for (ptr = 0; ptr < ARRAY_SIZE(init_clocks_disable); ptr++, clkp++) { 
 
		ret = s3c24xx_register_clock(clkp); 
		if (ret < 0) { 
			printk(KERN_ERR "Failed to register clock %s (%d)/n", 
			       clkp->name, ret); 
		} 
 
		s3c2410_clkcon_enable(clkp, 0); 
	} 
 
	/* show the clock-slow value */ 
 
	xtal = clk_get(NULL, "xtal"); 
 
	printk("CLOCK: Slow mode (%ld.%ld MHz), %s, MPLL %s, UPLL %s/n", 
	       print_mhz(clk_get_rate(xtal) / 
			 ( 2 * S3C2410_CLKSLOW_GET_SLOWVAL(clkslow))), 
	       (clkslow & S3C2410_CLKSLOW_SLOW) ? "slow" : "fast", 
	       (clkslow & S3C2410_CLKSLOW_MPLL_OFF) ? "off" : "on", 
	       (clkslow & S3C2410_CLKSLOW_UCLK_OFF) ? "off" : "on"); 
 
	s3c_pwmclk_init(); 
	return 0; 
} 

在arch/arm/plat-s3c/clock.c中实现了clock system对外提供的接口：

[c-sharp] view plaincopyprint?
01./*则加模块的引用计数*/  
02.struct clk *clk_get(struct device *dev, const char *id)；  
03./*减少模块的引用计数*/  
04.void clk_put(struct clk *clk)；  
05./*使能某个模块的时钟，比如ADC模块等*/  
06.int clk_enable(struct clk *clk)；  
07./*禁止模块的时钟*/  
08.void clk_disable(struct clk *clk)；  
09./*获得某类时钟频率*/  
10.unsigned long clk_get_rate(struct clk *clk)；  
11./*设置某类部件的时钟(比如设置CAM接口时钟)*/  
12.int clk_set_rate(struct clk *clk, unsigned long rate)；  
13./*获得父clk*/  
14.struct clk *clk_get_parent(struct clk *clk)；  
15./*设置父clk*/  
16.int clk_set_parent(struct clk *clk, struct clk *parent)；  
