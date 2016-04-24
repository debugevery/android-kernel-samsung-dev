//Linux-2.6.20的LCD驱动分析（一）[转] .
//分类： 嵌入式Linux驱动编写 2008-07-24 09:42 1150人阅读 评论(0) 收藏 举报 
// 
//一、让LCD显示可爱的小企鹅
//还是先说说环境吧，处理器为S3C2410，linux的版本当然是2.6.20的。下面先说说怎样让LCD上显示出可爱的小企鹅。最直接的步骤如下（记住不要问为什么哈～_～，一步一步跟着走就行了）：
//
//1.       添加s3c2410处理器的LCD控制寄存器的初始值，具体做法为在文件arch/arm/mach-s3c2410/mach-smdk2410.c中添加struct s3c2410fb_mach_info类型的寄存器描述讯息，如下所示：
  
  
  
//======================打开注释回车   /*=========================

static struct s3c2410fb_mach_info smdk2410_lcd_platdata = {

    .fixed_syncs=0,

    .type = S3C2410_LCDCON1_TFT,

    .width= 240,

    .height= 320,

    .xres = {

    .defval= 240,

        .min= 240,

        .max= 240,

    },

    .yres = {

        .defval= 320,

        .min= 320,

        .max= 320,

    },

    .bpp = {

        .defval= 16,

        .min= 16,

        .max= 16,

    },

    .regs = {

        .lcdcon1=  S3C2410_LCDCON1_TFT16BPP |        /

                            S3C2410_LCDCON1_TFT |             /

                            S3C2410_LCDCON1_CLKVAL(5) |      /

                            (0<<7),

 
        .lcdcon2=  S3C2410_LCDCON2_VBPD(2) |          /

                   S3C2410_LCDCON2_LINEVAL(320-1) |   /

                   S3C2410_LCDCON2_VFPD(2) |          /

                   S3C2410_LCDCON2_VSPW(4),

 
        .lcdcon3=  S3C2410_LCDCON3_HBPD(8) |          /

                   S3C2410_LCDCON3_HOZVAL(240-1) |    /

                   S3C2410_LCDCON3_HFPD(8),

 
        .lcdcon4=  S3C2410_LCDCON4_HSPW(6) |          /

                   S3C2410_LCDCON4_MVAL(13),

 
        .lcdcon5=  S3C2410_LCDCON5_FRM565 |

                   S3C2410_LCDCON5_HWSWP,

    },

    .gpcup= 0x0,

    .gpcup_mask= 0xFFFFFFFF,

    .gpccon= 0xaaaa56a9,

    .gpccon_mask= 0xFFFFFFFF,

 
    .gpdup= 0x0,

    .gpdup_mask= 0xFFFFFFFF,

    .gpdcon= 0xaaaaaaaa,

    .gpdcon_mask= 0xFFFFFFFF,

    .lpcsel= 0x00

};

 
//2. 通过s3c24xx_fb_set_platdata函数向内核注册上面的信息。具体做法为：修改s3c24xx_fb_set_platdata函数（当然也可以重新起名字），修改如下：（此函数在arch/arm/mach-s3c2410/devs.c中）
//
 
void __init s3c24xx_fb_set_platdata(struct s3c2410fb_mach_info *pd)

{

s3c_device_lcd.dev.platform_data = pd;

}

 
//然后在arch/arm/mach-s3c2410/mach-smdk2410.c的smdk2410_map_io函数中调用s3c24xx_fb_set_platdata( )，具体为：
//
//s3c24xx_fb_set_platdata(&smdk2410_lcd_platdata);
//
//注：此处未采用内核中提供的源函数，因为系统会崩溃，估计是它调用kmalloc函数引起的。
//
// 
//3. 在make menuconfig的时候配置Linux的logo选项，然后的时候在console选项中选上framebuffer console surpport，要不然看不到小企鹅。
//
//上面这些步骤均来源于网上，感谢您们的无私贡献！嘿嘿，到目前为止差不多也可以交差了，但我还想深入了解一下真正的驱动程序。呵呵，欲知后事如何且听下回分解。
//
//
//
//
//
//
//Linux-2.6.20的LCD驱动分析（二）[转] .
//分类： 嵌入式Linux驱动编写 2008-07-24 09:45 1871人阅读 评论(0) 收藏 举报 
//二、s3c2410fb_probe函数分析
//2.1 驱动的入口点
//摆在面前的第一个问题相信应该是，这个函数是从那里开始运行的。这里就应该从long long ago 开始了，打开drivers/video/s3c2410fb.c文件，然后找到s3c2410fb_init函数，先不管它里面是怎么回事，再把目光下移就会看到这样一串字符串module_init(s3c2410fb_init)，郁闷，这和S3C2410fb_probe有啥关系嘛？这个问题问的好！不要着急慢慢往下面走。先摸摸module_init是何方神圣再说，于是乎我就登陆了http://lxr.linux.no/linux+v2.6.20/网站，在上面一搜，原来module_init老家在include/linux/init.h，原来它居然还有两重身份，其原型如下：
#ifndef MODULE
……
#define //module_init(x) __initcall(x);                               ①
……
#else
……
#define //module_init(initfn)                                 /              ②
       static inline initcall_t __inittest(void)            /
       { return initfn; }                                         /
       int init_module(void) __attribute__((alias(#c)));
……
#endif
 
//从上面可以看出，module_init到底用哪个，就取决于MODULE了，那么MODULE的作用是什么呢？我们知道Linux可以将设备当作模块动态加进内核，也可以直接编译进内核，说到这里大概有点明白MODULE的作用了，不错！它就是要控制一个驱动加入内核的方式。定义了MODULE就表示将设备当作模块动态加入。所以上面的①表示将设备加进内核。在②中的__attribute__((alias(#initfn)))很有意思，这代表什么呢？主要alias就是属性的意思，它的英文意思是别名，可以在http://publib.boulder.ibm.com/infocenter/lnxpcomp/v8v101/index.jsp?topic=/com.ibm.xlcpp8l.doc/language/ref/fn_attrib_alias.htm找到它的详细说明，这里简单的说int init_module(void) __attribute__((alias(#initfn)));的意思为init_module是initfn的别名，或者init_module是initfn的一个连接，再简单一点说这个时候module_init宏基因突变成了init_module()了。对于第一种情况，__initcall(fn) 又被宏定义成了device_initcall(fn)，也就是说module_init(x)等于device_initcall(fn)。对于device_initcall(fn)又是一个宏定义，它被定义成了__define_initcall("6",fn,6)，至于这个宏表示什么意思，在这里就不啰嗦重复了，在Linux-2.6.20的cs8900驱动分析(一)这篇文章中有对它的揭秘。
//       上面啰嗦了这么多，最终是要说明只要用module_init申明了一个函数，该函数就会被Linux内核在适当的时机运行，这些时机包括在linux启动的do_initcalls()时调用（设备被编译进内核），或者在动态插入时调用。
//       回到上面的module_init(s3c2410fb_init)处，也就是说内核与buffer驱动发生关系的第一次地点是在s3c2410fb_init函数，该函数就只有一条语句
//platform_driver_register (&s3c2410fb_driver)；
//？？？？？？……
 
//2.2 platform是何许人也
//       platform可以理解成一种设备类型，就像字符设备、块设备和网络设备一样，而LCD就属于这种设备。对于platform设备Linux为应用添加了相关的接口，在这里只是简单的说说这些接口的用法，而不去深入探讨这些接口的实现（我现在还没有那个能力呢！）。说到这里，马上就有个问题涌上心头了，那就是Linux提供了那些接口呢？如果我们需要添加这些设备应该怎么样做呢？
//       platform中的相关数据结构是应用的关键，为了向内核添加一个platform设备，程序员应该填写两个数据结构platform_device 和platform_driver，这两个数据结构的定义都可以在include/linux/platform_device.h文件中找到。看看LCD驱动是怎么做的，第一步是填写platform_device，在arch/arm/mach-s3c2410/devs.c可以找到填写platform_device的代码，如下：
static u64 s3c_device_lcd_dmamask = 0xffffffffUL;
struct platform_device s3c_device_lcd = {
       .name               = "s3c2410-lcd",
       .id             = -1,
       .num_resources       = ARRAY_SIZE (s3c_lcd_resource),
       .resource   = s3c_lcd_resource,
       .dev              = {
              .dma_mask            = &s3c_device_lcd_dmamask,
              .coherent_dma_mask     = 0xffffffffUL
       }
};
//    这里面的各个数据成员的意思，在platform_device数据结构中有详细的说明，这里不赘述。上面的代码中的ARRAY_SIZE宏还是比较有意思的，其实是个c的编程技巧，这个技巧很有用哦！可以在include/linux/kernel.h中找到它的定义：
//#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
//该宏可以方便的求出一个数组中有多少数据成员，这在很多情况下是很有用的，比如对于   int a[]={1,5,65,23,12,20,3}数组，可以使用该宏求出a[]有7个元素。
//    另外，platform_device的另外一项重要成员是resource，在上面的代码中此域被赋予了s3c_lcd_resource，s3c_lcd_resource也可以在arch/arm/mach-s3c2410/devs.c找到。
static struct resource s3c_lcd_resource[] = {
       [0] = {
              .start = S3C24XX_PA_LCD,
              .end   = S3C24XX_PA_LCD + S3C24XX_SZ_LCD - 1,
              .flags = IORESOURCE_MEM,
       },
       [1] = {
              .start = IRQ_LCD,
              .end   = IRQ_LCD,
              .flags = IORESOURCE_IRQ,
       }
};
//struct resource结构实际上描述了该设备占用的硬件资源（如地址空间，中断号等s），s3c_lcd_resource描述了内存空间和中断分配情况。
//    最后在smdk2410_devices指针数组中添加上s3c_device_lcd的大名，Linux在初始化platform的时候就知道系统中有个s3c_device_lcd设备了。注意了这里只是向Linux描述了设备需要的资源情况，不代表内核会给这些资源的。如果设备要得到这些设备还需要在自己的初始化函数中去申请。
 
static struct platform_device *smdk2410_devices[] __initdata = {
       &s3c_device_usb,
       &s3c_device_lcd,
       &s3c_device_wdt,
       &s3c_device_i2c,
       &s3c_device_iis,
       &s3c_device_ts,
};
//说到这里，应该说向Linux添加一个platform设备应该很容易。
// 
//2.2 回到s3c2410fb_init
//终于把platform的相关知识啰嗦了一番，下面回到s3c2410fb_init函数所调用platform_driver_register(&s3c2410fb_driver)。简单地说platform_driver_register要将向内核注册一个platform设备的驱动，这里是要注册LCD设备。上面说过platform有两个重要的数据结构platform_device和platform_driver，现在是应该提到后者的时候了。platform_driver也在include/linux/platform_device.h中，它的各个成员应该再明白不过来吧！在LCD驱动程序（drivers/video/s3c2410fb.c）中定义了填充了platform_driver这个结构，如下：
static struct platform_driver s3c2410fb_driver = {
       .probe            = s3c2410fb_probe,
       .remove          = s3c2410fb_remove,
       .suspend  = s3c2410fb_suspend,
       .resume          = s3c2410fb_resume,
       .driver            = {
              .name      = "s3c2410-lcd",
              .owner    = THIS_MODULE,
       },
};
//可以看到该platform设备的驱动函数有s3c2410fb_probe、s3c2410fb_remove等等。通过platform_driver_register函数注册该设备的过程中，它会回调.probe函数，说到这里也就明白s3c2410fb_probe是在platform_driver_registe中回调的。到目前为止，经过二万五千里长征终于到达s3c2410fb_probe（LCD的驱动程序）了。
// 
//2.3 s3c2410fb_probe揭秘
//       对于该函数，我想最好的办法就是跟着程序一步一步的解释。OK，let’s go to ……
static int __init s3c2410fb_probe(struct platform_device *pdev)
{
       struct s3c2410 fb_info *info;  //s3c2410fb_info结构在driver/video/s3c2410fb.h中定义，
//可以说该结构记录了s3c2410fb驱动的所有信息。
       struct fb_info     *fbinfo;    // fb_info为内核提供的buffer驱动的接口数据结构, 每个帧缓冲驱动都对应一个这样的结构。s3c2410fb_probe的最终目的填充该结构，并向内核注册。
       struct s3c2410fb_hw *mregs;  // s3c2410fb_hw为描述LCD的硬件控制寄存器的结构体，
//在include/asm-arm/arch-s3c2410/fb.h可以找到它的原型。
……
 
       mach_info = pdev->dev.platform_data;  //这一步看来要多费些口舌了。mach_info是一个s3c2410fb_mach_info类型的指针，注意区分s3c2410fb_mach_info和s3c2410fb_info结构,简单地说前者只是用于描述LCD初始化时所用的值，而后者是描述整个LCD驱动的结构体。s3c2410fb_mach_info在include/asm-arm/arch-s3c2410/fb.h中定义，从他的位置可以看出它和平台相关，也即它不是内核认知的数据结构，这只是驱动程序设计者设计的结构。这里的主要疑问是什么呢？从下面的if语句可以看出如果mach_info等于NULL的话，整个驱动程序就退出了，这就引出了问题――pdev->dev.platform_data是在什么时候被初始化的呢？看来要回答这个问题，历史应该回到孙悟空大闹天宫的时候了。按住倒带键不放一直到本篇文章的第一部分，看看那个时候做了些什么。放在这里来解释第一部分的内容希望没有为时已晚。其实在内核启动init进程之前就会执行smdk2410_map_io( )函数（内核的启动分析就免了吧@_@），而在smdk2410_map_io( )中我们加入了
s3c24xx_fb_set_platdata (&smdk2410_lcd_platdata);
//这条语句，s3c24xx_fb_set_platdata()的实现为：
void __init s3c24xx_fb_set_platdata(struct s3c2410fb_mach_info *pd)
{
    s3c_device_lcd.dev.platform_data = pd;
}
//根据这些代码，可以清楚的看到s3c_device_lcd.dev.platform_data指向了smdk2410_lcd_platdata，而这个smdk2410_lcd_platdata就是一个s3c2410fb_mach_info的变量，它里面就存放了LCD驱动初始化需要的初始数据。当s3c2410fb_probe被回调时，所传给它的参数实际就是s3c_device_lcd的首地址，说到这里一切应该都明了了吧！好了，又撤了一通，现在假设这步成功，继续往下面走。
      if (mach_info == NULL) {
              dev_err(&pdev->dev,"no platform data for lcd, cannot attach/n");
              return -EINVAL;
       }
 
       mregs = &mach_info->regs;    //mregs指向硬件各控制寄存器的初始值，可参见第一部
//分的smdk2410_lcd_platdata变量。
 
       irq = platform_get_irq(pdev, 0);  //该函数获得中断号，该函数的实现是通过比较struct resource的flags域，得到irq中断号，在上2.1的时候提到s3c_lcd_resource[]，platform_get_irq函数检测到flags＝＝IORESOURCE_IRQ时就返回中断号IRQ_LCD。详细的内容请读它的源代码吧！
       if (irq < 0) {          //没有找到可用的中断号，返回-ENOENT
              dev_err(&pdev->dev, "no irq for device/n");
              return -ENOENT;
       }
 
       fbinfo = framebuffer_alloc(sizeof(struct s3c2410fb_info), &pdev->dev);  // framebuffer_alloc可以在include/linux/fb.h文件中找到其原型：struct fb_info *framebuffer_alloc(size_t size, struct device *dev); 它的功能是向内核申请一段大小为sizeof(struct fb_info) + size的空间，其中size的大小代表设备的私有数据空间，并用fb_info的par域指向该私有空间。
       if (!fbinfo) {
              return -ENOMEM;
       }
 
//以下开始做正经事了，填充fbinfo了。
       info = fbinfo->par;   //你中有我，我中有你！
       info->fb = fbinfo;
       platform_set_drvdata(pdev, fbinfo);           //该函数的实现非常简单，实际的操作为：pdev->dev.driver_data ＝ fbinfo，device结构的driver_data域指向驱动程序的私有数据空间。
 
       dprintk("devinit/n");
 
       strcpy(fbinfo->fix.id, driver_name);  
 
       memcpy(&info->regs, &mach_info->regs, sizeof(info->regs));
 
       // Stop the video and unset ENVID if set 
       info->regs.lcdcon1 &= ~S3C2410_LCDCON1_ENVID;
       lcdcon1 = readl(S3C2410_LCDCON1);
       writel(lcdcon1 & ~S3C2410_LCDCON1_ENVID, S3C2410_LCDCON1);//停止硬件
 
//以下的对fbinfo的填写就免了吧！对于fb_info结构的各个成员，在include/linux/fb文件中都有详细的说明，如果不知道说明的意思，就应该找些基本的知识读读了。在众多的初始化中，fbinfo->fbops = &s3c2410fb_ops;是值得一提的，变量s3c2410fb_ops 就在s3c2410fb.c中定义，它记录了该帧缓冲区驱动所支持的操作 
 
……
 
       for (i = 0; i < 256; i++)  //初始化调色板缓冲区
              info->palette_buffer[i] = PALETTE_BUFF_CLEAR;
 
       if (!request_mem_region((unsigned long)S3C24XX_VA_LCD, SZ_1M, "s3c2410-lcd")) {
// 向内核申请内存空间，如果request_mem_region返回0表示申请失败，此时程序跳到dealloc_fb处开始执行，该处会调用framebuffer_release释放刚才由framebuffer_alloc申请的fb_info空间 
              ret = -EBUSY;
              goto dealloc_fb;
       }
……
       ret = request_irq(irq, s3c2410fb_irq, IRQF_DISABLED, pdev->name, info);// 向内核注册中断，如果注册失败，程序跳转到release_mem处运行，此处释放fb_info和刚才由request_mem_region申请的内存空间 
       if (ret) {
              dev_err(&pdev->dev, "cannot get irq %d - err %d/n", irq, ret);
              ret = -EBUSY;
              goto release_mem;
       }
 
       info->clk = clk_get(NULL, "lcd");  //该函数得到时钟源，并与硬件紧密相连，对于我的
//板子，可以在arch/arm/mach-s3c2410/clock.c看到它的原型和实现。
       if (!info->clk || IS_ERR(info->clk)) {
              printk(KERN_ERR "failed to get lcd clock source/n");
              ret = -ENOENT;
              goto release_irq;  //该处释放上面申请的fb_info，内存，和irq资源
       }
 
       clk_enable(info->clk);   //打开时钟
       dprintk("got and enabled clock/n");
 
       msleep(1);          //运行得太久有点累了，去打个盹再说
 
       // Initialize video memory 
       ret = s3c2410fb_map_video_memory(info);//此函数就在s3c2410fb.c文件中被定义，它的作用是申请帧缓冲器内存空间 
       if (ret) {
              printk( KERN_ERR "Failed to allocate video RAM: %d/n", ret);
              ret = -ENOMEM;
              goto release_clock;            //释放所有已得到的资源
       }
       dprintk("got video memory/n");
 
       ret = s3c2410fb_init_registers(info);   //此函数也在s3c2410fb.c文件中定义，后面会分析
 
       ret = s3c2410fb_check_var(&fbinfo->var, fbinfo);   //此函数也在s3c2410fb.c文件中定义
 
       ret = register_framebuffer(fbinfo);  //神圣的时刻终于到来，向内核正式注册。
       if (ret < 0) {
              printk(KERN_ERR "Failed to register framebuffer device: %d/n", ret);
              goto free_video_memory; //不让注册真郁闷，那就释放所有的资源，出家算了！
       }
 
       // create device files 
       device_create_file(&pdev->dev, &dev_attr_debug); //为该设备创建一个在sysfs中的属性
 
       printk(KERN_INFO "fb%d: %s frame buffer device/n",
              fbinfo->node, fbinfo->fix.id);
 
       return 0;           //大功告成！
 
free_video_memory:
       s3c2410fb_unmap_video_memory(info);
release_clock:
       clk_disable(info->clk);
       clk_put(info->clk);
release_irq:
       free_irq(irq,info);
release_mem:
      release_mem_region((unsigned long)S3C24XX_VA_LCD, S3C24XX_SZ_LCD);
dealloc_fb:
       framebuffer_release(fbinfo);
       return ret;
}




//Linux-2.6.20的LCD驱动分析（三）[转] .
//分类： 嵌入式Linux驱动编写 2008-07-24 09:47 1869人阅读 评论(0) 收藏 举报 
// 
//三、解剖s3c2410fb_driver变量
//s3c2410fb_driver变量有什么作用呢？在前面的2.2节提到了它的定义，从它的原型可以看出 s3c2410fb_driver是个platform_driver类型的变量，前面的几个小节提到了从platform_driver的名字可以看出它应该是platform_device的驱动类型。为了方便阅读，这里再贴一次s3c2410fb_driver的定义：
static struct platform_driver s3c2410fb_driver = {

      .probe            = s3c2410fb_probe,

       .remove          = s3c2410fb_remove,

       .suspend  = s3c2410fb_suspend,

       .resume          = s3c2410fb_resume,

       .driver            = {

              .name      = "s3c2410-lcd",
              .owner    = THIS_MODULE,
       },
};
//从定义可以看出，该platform_device的驱动函数有s3c2410fb_probe， s3c2410fb_remove，s3c2410fb_suspend和s3c2410fb_suspend。.resource成员前面的章节有说明，.driver成员的值相信不用再说明了吧，再明白不过了。前面的章节，s3c2410fb_probe被比较详细的介绍，这节中的主要任务就是解释其他的几个函数。在解释他们之前，s3c2410fb_probe里面在该函数结尾的时候调用了几个函数没有说到，所以在这里补上。
// 
//3.1 s3c2410fb_probe余党
//       在s3c2410fb_probe中最好调用了s3c2410fb_init_registers和s3c2410fb_check_var函数，这里应该将他们交代清楚。很显然，s3c2410fb_init_registers是初始化相关寄存器。那么后者呢？这里先把 s3c2410fb_init_registers搞定再说。s3c2410fb_init_registers的定义与实现如下，先根据它的指向流程，一步一步解释：
 
static int s3c2410fb_init_registers(struct s3c2410fb_info *fbi)
{
       unsigned long flags;
 
       // Initialise LCD with values from haret 

 
       local_irq_save(flags);     // 关闭中断，在关闭中断前，中断的当前状态被保存在flags中，对于关闭中断的函数，linux内核有很多种，可以查阅相关的资料。
 
       // modify the gpio(s) with interrupts set (bjd) 

//下面的modify_gpio函数是修改处理器GPIO的工作模式，它的实现很简单，将第二个参数的值与第三个参数的反码按位与操作后，在写到第一个参数。这里的第一个参数实际就是硬件的GPIO控制器。
       modify_gpio(S3C2410_GPCUP,  mach_info->gpcup,  mach_info->gpcup_mask);

       modify_gpio(S3C2410_GPCCON, mach_info->gpccon, mach_info->gpccon_mask);

       modify_gpio(S3C2410_GPDUP,  mach_info->gpdup,  mach_info->gpdup_mask);

       modify_gpio(S3C2410_GPDCON, mach_info->gpdcon, mach_info->gpdcon_mask);

 
       local_irq_restore(flags);  //使能中断，并恢复以前的状态
  //下面的几个writel函数开始初始化LCD控制寄存器，它的值就是我们在smdk2410_lcd_platdata(arch/arm/mach-s3c2410/mach-smdk2410.c)中regs域的值。
       writel(fbi->regs.lcdcon1, S3C2410_LCDCON1);
       writel(fbi->regs.lcdcon2, S3C2410_LCDCON2);
       writel(fbi->regs.lcdcon3, S3C2410_LCDCON3);
       writel(fbi->regs.lcdcon4, S3C2410_LCDCON4);
       writel(fbi->regs.lcdcon5, S3C2410_LCDCON5);
 
      s3c2410fb_set_lcdaddr(fbi);    //该函数的主要作用是让处理器的LCD控制器的三个地址寄存器指向正确的位置，这个位置就是LCD的缓冲区，详细的情况可以参见s3c2410的用户手册。
……
       // Enable video by setting the ENVID bit to 1 这里打开video，在s3c2410fb_probe中被关闭了，这里打开

       fbi->regs.lcdcon1 |= S3C2410_LCDCON1_ENVID;
       writel(fbi->regs.lcdcon1, S3C2410_LCDCON1);
       return 0;
}
//OK，s3c2410fb_init_registers就简单介绍到这里。下面看看 s3c2410fb_check_var函数要干些什么事，要说到这个函数，还得提到fb_var_screeninfo结构类型，与它对应的是 fb_fix_screeninfo结构类型。这两个类型分别代表了显示屏的属性信息，这些信息可以分为可变属性信息（如：颜色深度，分辨率等）和不可变的信息（如帧缓冲的其实地址）。既然fb_var_screeninfo表示了可变的属下信息，那么这些可变信息就应该有一定范围，否则显示就会出问题，所以s3c2410fb_check_var函数的功能就是要在LCD的帧缓冲驱动开始运行之前将这些值初始到合法的范围内。知道了 s3c2410fb_check_var要做什么，再去阅读s3c2410fb_check_var函数的代码就没什么问题了。
// 
//3.2 s3c2410fb_remove
//       从这里开始将解释s3c2410fb_driver中的其他几个函数。那么就从s3c2410fb_remove开刀吧！顾名思义该函数就该知道，它要将这个platform设备从系统中移除，可以推测它应该释放掉所有的资源，包括内存空间，中断线等等。还是按照惯例，在它的实现代码中一步步的解释。
static int s3c2410fb_remove(struct platform_device *pdev)
{
       struct fb_info     *fbinfo = platform_get_drvdata(pdev);  //该函数从platform_device中，到fb_info信息

       struct s3c2410fb_info *info = fbinfo->par;  //得到私有数据
       int irq;
 
       s3c2410fb_stop_lcd(info);    //该函数停止LCD控制器，实现可以在s3c2410fb.c中找到
       msleep(1); //休息以下，等待LCD停止
 
       s3c2410fb_unmap_video_memory(info);   //该函数释放缓冲区
 
      if (info->clk) {          //停止时钟

             clk_disable(info->clk);
             clk_put(info->clk);
             info->clk = NULL;

       }
 
       irq = platform_get_irq(pdev, 0);     //得到中断线，以便释放
       free_irq(irq,info);    //释放该中断
       release_mem_region((unsigned long)S3C24XX_VA_LCD, S3C24XX_SZ_LCD); // 释放内存空间 
       unregister_framebuffer(fbinfo);       //向内核注销该帧缓冲
 
       return 0;
}
 
//3.3 s3c2410fb_suspend与s3c2410fb_resume
//       在实际的设备，常常可以看到LCD在不需要的时候进入休眠状态，当需要使用的时候又开始工作，比如手机，在不需要的时候LCD就熄灭，当需要使用的时候 LCD又被点亮。从实际中可以看出这对函数非常重要。虽然他们很重要，但不一定很复杂，下面看看它们是怎么样实现的。
// 
static int s3c2410fb_suspend(struct platform_device *dev, pm_message_t state)

{
       struct fb_info     *fbinfo = platform_get_drvdata(dev);  //这两条语句好面熟^_^

       struct s3c2410fb_info *info = fbinfo->par;
 
       s3c2410fb_stop_lcd(info);  //停止LCD
 
       // sleep before disabling the clock, we need to ensure

        * the LCD DMA engine is not going to get back on the bus

        * before the clock goes off again (bjd) 

 
       msleep(1);  //等待一下，因为LCD停止需要一点时间
       clk_disable(info->clk);  //关闭LCD的时钟
 
       return 0;
}
//^_^，下面的代码就不用解释了吧！
static int s3c2410fb_resume(struct platform_device *dev)
{
       struct fb_info     *fbinfo = platform_get_drvdata(dev);

       struct s3c2410fb_info *info = fbinfo->par;
 
       clk_enable(info->clk);
       msleep(1);
 
       s3c2410fb_init_registers(info);
 
       return 0;
}
 
//OK，到现在为止，对于platform device的相关驱动就over了。不过精彩的还在后头哦！
//





//Linux-2.6.20的LCD驱动分析（四）[转] .
//2008-07-24 09:49 807人阅读 评论(1) 收藏 举报 
// 
//四、s3c2410fb_ops变量详解
//      在上面的文字中，较为详细的解释了platform device相关的代码，通过上面的代码的执行，一个platform设备（framebuffer被当作了platform设备）就加载到内核中去了。就像一个PCI的网卡被加入到内核一样，不同的是PCI的网卡占用的是PCI总线，内核会直接支持它。而对于platform设备需要用上面软件的方法加载到内核，同PCI网卡一样，设备需要驱动程序，刚才只是将platform设备注册到内核中，现在它还需要驱动程序，本节中就来看看这些驱动。
//4.1 static struct fb_ops s3c2410fb_ops
//       对于s3c2410的framebuffer驱动支持的操作主要有s3c2410fb_ops变量中定义，该变量类型为struct fb_ops，该类型的定义在include/linux/fb.h文件中。它的相关解释可以在http://www.91linux.com/html/article/kernel/20071204/8805.html页面中找到，当然在fb.h中也有很详细的说明。下面看看对于s3c2410的驱动为该framebuffer提供了哪些操作。
//
static struct fb_ops s3c2410fb_ops = {

       .owner           = THIS_MODULE,

       .fb_check_var = s3c2410fb_check_var,
       .fb_set_par     = s3c2410fb_set_par,
       .fb_blank = s3c2410fb_blank,

       .fb_setcolreg   = s3c2410fb_setcolreg,
       .fb_fillrect      = cfb_fillrect,
       .fb_copyarea   = cfb_copyarea,
       .fb_imageblit   = cfb_imageblit,
};
//       上面的代码描述了支持的相关操作，下面主要会解释s3c2410****的函数，从.fb_fillrect开始的三个函数将不会被提及，当然也可以去看看它们的行为是什么。这里还有一个问题要说明一下，就是s3c2410fb_ops是在什么时候被注册的，这个问题的答案可以在 s3c2410fb_probe函数中找到，请查看s3c2410fb_probe分析的那一小节。
// 
//4.2.1 s3c2410fb_check_var
//       在上面的小节中提到对于一个LCD屏来说内核提供了两组数据结构来描述它，一组是可变属性（fb_var_screeninfo描述），另一组是不变属性（fb_fix_screeninfo描述）。对于可变属性，应该防止在操作的过程中出现超出法定范围的情况，因此内核应该可以调用相关函数来检测、并将这些属性固定在法定的范围内，完成这个操作的函数就是s3c2410_check_var。
//下面简单说明一下该函数要做的事情，在这里最好看着fb_var_screeninfo和fb_info的定义。
// 
static int s3c2410fb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)

{
       struct s3c2410fb_info *fbi = info->par; //得到驱动的私有数据信息，注意info-par的值
……
// 下面检查fb_var_screeninfo的xres和yres的值是否超出法定范围，如果查出将其设定为正确的值。
       if (var->yres > fbi->mach_info->yres.max)

              var->yres = fbi->mach_info->yres.max;

       else if (var->yres < fbi->mach_info->yres.min)

              var->yres = fbi->mach_info->yres.min;

 
       if (var->xres > fbi->mach_info->xres.max)

              var->yres = fbi->mach_info->xres.max;

       else if (var->xres < fbi->mach_info->xres.min)

              var->xres = fbi->mach_info->xres.min;

……
 
// 羡慕开始检查bpp（表示用多少位表示一个像素），如果不合法，将其设置正确
       if (var->bits_per_pixel > fbi->mach_info->bpp.max)

              var->bits_per_pixel = fbi->mach_info->bpp.max;

       else if (var->bits_per_pixel < fbi->mach_info->bpp.min)

              var->bits_per_pixel = fbi->mach_info->bpp.min;

 
       // 下面的代码根据bpp设置正确的颜色信息，代码略 

……
       }
       return 0;
}
 
//4.2.2 s3c2410fb_set_par
//       该函数的主要工作是重新设置驱动的私有数据信息，主要改变的属性有bpp和行的长度（以字节为单位）。这些属性值其实是存放在 fb_fix_screeninfo结构中的，前面说过这些值在运行基本是不会改变的，这些不可改变的值又可分为绝对不能改变和允许改变的两种类型，前一种的例子就是帧缓冲区的起始地址，后一种的例子就是在s3c2410fb_set_par函数中提到的属性。假如应用程序需要修改硬件的显示状态之类的操作，这个函数就显得十分重要。
// 
static int s3c2410fb_set_par(struct fb_info *info)
{
       struct s3c2410fb_info *fbi = info->par;              //得到私有数据信息
       struct fb_var_screeninfo *var = &info->var;    //可变的数据属性

 
       switch (var->bits_per_pixel)     //根据bpp设置不变属性信息的颜色模式
       {
              case 16:
                     fbi->fb->fix.visual = FB_VISUAL_TRUECOLOR;  //真彩色

                     break;
              case 1:
                      fbi->fb->fix.visual = FB_VISUAL_MONO01;   // 单色
                      break;
              default:
                      fbi->fb->fix.visual = FB_VISUAL_PSEUDOCOLOR;  //伪彩色
                      break;
       }
 
       fbi->fb->fix.line_length     = (var->width*var->bits_per_pixel)/8; //修改行长度信息（以字节为单位），计算方法是一行中的(像素总数 * 表达每个像素的位数)/8。

……
              s3c2410fb_activate_var(fbi, var);  //该函数实际是设置硬件寄存器，解释略。
       return 0;
}
//4.2.3 s3c2410fb_blank和s3c2410fb_setcolreg
//       对于s3c2410fb_blank函数实现的功能非常简单，而且也有较详细的说明，因此对它的说明就省略了。s3c2410fb_setcolreg函数的功能是设置颜色寄存器。它需要6个参数，分别代表寄存器编号，红色，绿色，蓝色，透明和fb_info结构。
static int s3c2410fb_setcolreg(unsigned regno,
                            unsigned red, unsigned green, unsigned blue,

                            unsigned transp, struct fb_info *info)
{
       struct s3c2410fb_info *fbi = info->par;          //得到私有数据信息
       unsigned int val;
……
       switch (fbi->fb->fix.visual) {
       case FB_VISUAL_TRUECOLOR:   //真彩色，使用了调色板
              // true-colour, use pseuo-palette 

              if (regno < 16) {
                     u32 *pal = fbi->fb->pseudo_palette;

 
                     val  = chan_to_field(red,   &fbi->fb->var.red);  //根据颜色值生成需要的数据
                     val |= chan_to_field(green, &fbi->fb->var.green);

                     val |= chan_to_field(blue,  &fbi->fb->var.blue);

 
                     pal[regno] = val;
              }
              break;
 
       case FB_VISUAL_PSEUDOCOLOR:    //伪彩色
              if (regno < 256) {
                     // 当前假设为 RGB 5-6-5 模式 

 
                     val  = ((red   >>  0) & 0xf800);

                     val |= ((green >>  5) & 0x07e0);

                     val |= ((blue  >> 11) & 0x001f);
 
                     writel(val, S3C2410_TFTPAL(regno));  //将此值直接写入寄存器
                     schedule_palette_update(fbi, regno, val);   //相关寄存器

              }
              break;
       default:
              return 1;   // unknown type 
       }
       return 0;
}
 
// 
//到目前为止，整个驱动的主要部分已经解释完毕了。最后还是得提一下中断处理函数s3c2410fb_irq，这个函数实现也比较短，它的主要调用了s3c2410fb_write_palette函数将它的功能是将调色板中的数据显示到LCD上。两个函数的实现也不难，这里就不再赘述。
//OK！good bye everyone！see you next time。

//                                         The End