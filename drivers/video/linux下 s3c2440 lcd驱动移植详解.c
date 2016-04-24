//linux下 s3c2440 lcd驱动移植详解 .
//分类： linux设备驱动 linux C 2010-06-30 18:50 1877人阅读 评论(1) 收藏 举报 
//1. LCD工作的硬件需求： 
//   要使一块LCD正常的显示文字或图像，不仅需要LCD驱动器，而且还需要相应的LCD控制器。在通常情况下，生产厂商把LCD驱动器会以COF/COG的形式与LCD玻璃基板制作在一起，而LCD控制器则是由外部的电路来实现，现在很多的MCU内部都集成了LCD控制器，如S3C2410/2440等。通过LCD控制器就可以产生LCD驱动器所需要的控制信号来控制STN/TFT屏了。
// 
//2. S3C2440内部LCD控制器结构图： 
// 
//我们根据数据手册来描述一下这个集成在S3C2440内部的LCD控制器：
//a：LCD控制器由REGBANK、LCDCDMA、TIMEGEN、VIDPRCS寄存器组成；
//b：REGBANK由17个可编程的寄存器组和一块256*16的调色板内存组成，它们用来配置LCD控制器的；
//c：LCDCDMA是一个专用的DMA，它能自动地把在侦内存中的视频数据传送到LCD驱动器，通过使用这个DMA通道，视频数据在不需要CPU的干预的情况下显示在LCD屏上；
//d：VIDPRCS接收来自LCDCDMA的数据，将数据转换为合适的数据格式，比如说4/8位单扫，4位双扫显示模式，然后通过数据端口VD[23:0]传送视频数据到LCD驱动器；
//e：TIMEGEN由可编程的逻辑组成，他生成LCD驱动器需要的控制信号，比如VSYNC、HSYNC、VCLK和LEND等等，而这些控制信号又与REGBANK寄存器组中的LCDCON1/2/3/4/5的配置密切相关，通过不同的配置，TIMEGEN就能产生这些信号的不同形态，从而支持不同的LCD驱动器(即不同的STN/TFT屏)。
// 
//3. 常见TFT屏工作时序分析： 
// 
//LCD提供的外部接口信号： VSYNC/VFRAME/STV： 垂直同步信号(TFT)/帧同步信号(STN)/SEC TFT信号；
//HSYNC/VLINE/CPV： 水平同步信号(TFT)/行同步脉冲信号(STN)/SEC TFT信号；
//VCLK/LCD_HCLK： 象素时钟信号(TFT/STN)/SEC TFT信号；
//VD[23:0]： LCD像素数据输出端口(TFT/STN/SEC TFT)；
//VDEN/VM/TP： 数据使能信号(TFT)/LCD驱动交流偏置信号(STN)/SEC TFT 信号；
//LEND/STH： 行结束信号(TFT)/SEC TFT信号；
//LCD_LPCOE： SEC TFT OE信号；
//LCD_LPCREV： SEC TFT REV信号；
//LCD_LPCREVB： SEC TFT REVB信号。 
// 
//
// 
//所有显示器显示图像的原理都是从上到下，从左到右的。这是什么意思呢？这么说吧，一副图像可以看做是一个矩形，由很多排列整齐的点一行一行组成，这些点称之为像素。那么这幅图在LCD上的显示原理就是： A： 显示指针从矩形左上角的第一行第一个点开始，一个点一个点的在LCD上显示，在上面的时序图上用时间线表示就为VCLK，我们称之为像素时钟信号；
//B： 当显示指针一直显示到矩形的右边就结束这一行，那么这一行的动作在上面的时序图中就称之为1 Line；
//C： 接下来显示指针又回到矩形的左边从第二行开始显示，注意，显示指针在从第一行的右边回到第二行的左边是需要一定的时间的，我们称之为行切换；
//D： 如此类推，显示指针就这样一行一行的显示至矩形的右下角才把一副图显示完成。因此，这一行一行的显示在时间线上看，就是时序图上的HSYNC；
//E： 然而，LCD的显示并不是对一副图像快速的显示一下，为了持续和稳定的在LCD上显示，就需要切换到另一幅图上(另一幅图可以和上一副图一样或者不一样，目的只是为了将图像持续的显示在LCD上)。那么这一副一副的图像就称之为帧，在时序图上就表示为1 Frame，因此从时序图上可以看出1 Line只是1 Frame中的一行；
//F： 同样的，在帧与帧切换之间也是需要一定的时间的，我们称之为帧切换，那么LCD整个显示的过程在时间线上看，就可表示为时序图上的VSYNC。 
// 
//
// 
//上面时序图上各时钟延时参数的含义如下：(这些参数的值，LCD产生厂商会提供相应的数据手册) VBPD(vertical back porch)： 表示在一帧图像开始时，垂直同步信号以后的无效的行数，对应驱动中的upper_margin；
//VFBD(vertical front porch)： 表示在一帧图像结束后，垂直同步信号以前的无效的行数，对应驱动中的lower_margin；
//VSPW(vertical sync pulse width)： 表示垂直同步脉冲的宽度，用行数计算，对应驱动中的vsync_len；
//HBPD(horizontal back porch)： 表示从水平同步信号开始到一行的有效数据开始之间的VCLK的个数，对应驱动中的left_margin；
//HFPD(horizontal front porth)： 表示一行的有效数据结束到下一个水平同步信号开始之间的VCLK的个数，对应驱动中的right_margin；
//HSPW(horizontal sync pulse width)： 表示水平同步信号的宽度，用VCLK计算，对应驱动中的hsync_len； 
// 
//
// 
//对于以上这些参数的值将分别保存到REGBANK寄存器组中的LCDCON1/2/3/4/5寄存器中：(对寄存器的操作请查看S3c2440数据手册LCD部分) LCDCON1：17 - 8位CLKVAL 
//          6 - 5位扫描模式(对于STN屏:4位单/双扫、8位单扫) 
//          4 - 1位色位模式(1BPP、8BPP、16BPP等)
//
//LCDCON2：31 - 24位VBPD 
//         23 - 14位LINEVAL 
//         13 - 6位VFPD 
//          5 - 0位VSPW
//
//LCDCON3：25 - 19位HBPD 
//         18 - 8位HOZVAL 
//          7 - 0位HFPD
//
//LCDCON4： 7 - 0位HSPW
//
//LCDCON5： 
// 
//
// 
//4. 帧缓冲(FrameBuffer)： 
//   帧缓冲是Linux为显示设备提供的一个接口，它把一些显示设备描述成一个缓冲区，允许应用程序通过 FrameBuffer定义好的接口访问这些图形设备，从而不用去关心具体的硬件细节。对于帧缓冲设备而言，只要在显示缓冲区与显示点对应的区域写入颜色值，对应的颜色就会自动的在屏幕上显示。下面来看一下在不同色位模式下缓冲区与显示点的对应关系：
// 
//
//帧缓冲(FrameBuffer)设备驱动 ： 
// 
//     帧缓冲设备为标准的字符型设备，在Linux中主设备号29，定义在/include/linux/major.h中的FB_MAJOR，次设备号定义帧缓冲的个数，最大允许有32个FrameBuffer，定义在/include/linux/fb.h中的FB_MAX，对应于文件系统下/dev /fb%d设备文件。 
//1. 帧缓冲设备驱动在Linux子系统中的结构如下： 
// 
//我们从上面这幅图看，帧缓冲设备在Linux中也可以看做是一个完整的子系统，大体由fbmem.c和xxxfb.c组成。向上给应用程序提供完善的设备文件操作接口(即对FrameBuffer设备进行read、write、ioctl等操作)，接口在Linux提供的fbmem.c文件中实现；向下提供了硬件操作的接口，只是这些接口Linux并没有提供实现，因为这要根据具体的LCD控制器硬件进行设置，所以这就是我们要做的事情了(即xxxfb.c 部分的实现)。 
//
//2. 帧缓冲相关的重要数据结构： 
//   从帧缓冲设备驱动程序结构看，该驱动主要跟fb_info结构体有关，该结构体记录了帧缓冲设备的全部信息，包括设备的设置参数、状态以及对底层硬件操作的函数指针。在Linux 中，每一个帧缓冲设备都必须对应一个fb_info，fb_info在/linux/fb.h中的定义如下：(只列出重要的一些) 
//

//======================打开注释回车   /*========================= 

struct fb_info { 
    int node; 
    int flags; 
    struct fb_var_screeninfo var; //LCD可变参数结构体 
    struct fb_fix_screeninfo fix; //LCD固定参数结构体 
    struct fb_monspecs monspecs;  //LCD显示器标准 
    struct work_struct queue ;     //帧缓冲事件队列 
    struct fb_pixmap pixmap;      //图像硬件mapper 
    struct fb_pixmap sprite;      //光标硬件mapper 
    struct fb_cmap cmap;          //当前的颜色表 
    struct fb_videomode * mode;    //当前的显示模式 

# ifdef CONFIG_FB_BACKLIGHT
     struct backlight_device * bl_dev;//对应的背光设备  
    struct mutex bl_curve_mutex; 
    u8 bl_curve[ FB_BACKLIGHT_LEVELS] ;//背光调整  
# endif 
# ifdef CONFIG_FB_DEFERRED_IO
    struct delayed_work deferred_work; 
    struct fb_deferred_io * fbdefio; 
# endif 

    struct fb_ops * fbops; //对底层硬件操作的函数指针 
    struct device * device; 
    struct device * dev;    //fb设备 
    int class_flag;     
# ifdef CONFIG_FB_TILEBLITTING
    struct fb_tile_ops * tileops; //图块Blitting 
# endif 
    char __iomem * screen_base;    //虚拟基地址 
    unsigned long screen_size;    //LCD IO映射的虚拟内存大小 
    void * pseudo_palette;         //伪16色颜色表 
# define FBINFO_STATE_RUNNING    0
# define FBINFO_STATE_SUSPENDED  1
    u32 state;   //LCD的挂起或恢复状态 
    void * fbcon_par; 
    void * par;     
} ; 
 


//其中，比较重要的成员有struct fb_var_screeninfo var、struct fb_fix_screeninfo fix和struct fb_ops * fbops，他们也都是结构体。下面我们一个一个的来看。 
//
//fb_var_screeninfo结构体主要记录用户可以修改的控制器的参数，比如屏幕的分辨率和每个像素的比特数等，该结构体定义如下： 

struct fb_var_screeninfo { 
    __u32 xres;                 //可见屏幕一行有多少个像素点 
    __u32 yres;                 //可见屏幕一列有多少个像素点 
    __u32 xres_virtual;         //虚拟屏幕一行有多少个像素点         
    __u32 yres_virtual;         //虚拟屏幕一列有多少个像素点 
    __u32 xoffset;              //虚拟到可见屏幕之间的行偏移 
    __u32 yoffset;              //虚拟到可见屏幕之间的列偏移 
    __u32 bits_per_pixel;       //每个像素的位数即BPP 
    __u32 grayscale;            //非0时，指的是灰度 

    struct fb_bitfield red;     //fb缓存的R位域 
    struct fb_bitfield green;   //fb缓存的G位域 
    struct fb_bitfield blue;    //fb缓存的B位域 
    struct fb_bitfield transp;  //透明度     

    __u32 nonstd;               // != 0 非标准像素格式 
    __u32 activate;                 
    __u32 height;               //高度 
    __u32 width;                //宽度 
    __u32 accel_flags;     

    //定时：除了pixclock本身外，其他的都以像素时钟为单位 
    __u32 pixclock;             //像素时钟(皮秒) 
    __u32 left_margin;          //行切换，从同步到绘图之间的延迟 
    __u32 right_margin;         //行切换，从绘图到同步之间的延迟 
    __u32 upper_margin;         //帧切换，从同步到绘图之间的延迟 
    __u32 lower_margin;         //帧切换，从绘图到同步之间的延迟 
    __u32 hsync_len;            //水平同步的长度 
    __u32 vsync_len;            //垂直同步的长度 
    __u32 sync; 
    __u32 vmode; 
    __u32 rotate ; 
    __u32 reserved[ 5] ;          //保留 
} ; 
 


//而fb_fix_screeninfo结构体又主要记录用户不可以修改的控制器的参数，比如屏幕缓冲区的物理地址和长度等，该结构体的定义如下： 

struct fb_fix_screeninfo { 
    char id[ 16] ;                 //字符串形式的标示符  
    unsigned long smem_start;    //fb缓存的开始位置  
    __u32 smem_len;              //fb缓存的长度  
    __u32 type;                  //看FB_TYPE_*  
    __u32 type_aux;              //分界 
    __u32 visual;                //看FB_VISUAL_*  
    __u16 xpanstep;              //如果没有硬件panning就赋值为0  
    __u16 ypanstep;              //如果没有硬件panning就赋值为0  
    __u16 ywrapstep;             //如果没有硬件ywrap就赋值为0  
    __u32 line_length;           //一行的字节数  
    unsigned long mmio_start;    //内存映射IO的开始位置 
    __u32 mmio_len;              //内存映射IO的长度 
    __u32 accel; 
    __u16 reserved[ 3] ;           //保留 
} ; 
 


//fb_ops结构体是对底层硬件操作的函数指针，该结构体中定义了对硬件的操作有:(这里只列出了常用的操作) 

struct fb_ops { 

    struct module * owner; 

     //检查可变参数并进行设置 
    int ( * fb_check_var) ( struct fb_var_screeninfo * var, struct fb_info * info) ; 

     //根据设置的值进行更新，使之有效 
    int ( * fb_set_par) ( struct fb_info * info) ; 

     //设置颜色寄存器 
    int ( * fb_setcolreg) ( unsigned regno, unsigned red, unsigned green, 
             unsigned blue, unsigned transp, struct fb_info * info) ; 

     //显示空白 
    int ( * fb_blank) ( int blank, struct fb_info * info) ; 

     //矩形填充 
    void ( * fb_fillrect) ( struct fb_info * info, const struct fb_fillrect * rect) ; 

     //复制数据 
    void ( * fb_copyarea) ( struct fb_info * info, const struct fb_copyarea * region) ; 

     //图形填充 
    void ( * fb_imageblit) ( struct fb_info * info, const struct fb_image * image) ; 
} ; 
 

//3. 帧缓冲设备作为平台设备： 
//   在S3C2440中，LCD控制器被集成在芯片的内部作为一个相对独立的单元，所以Linux把它看做是一个平台设备，故在内核代码/arch/arm/plat-s3c24xx/devs.c 中定义有LCD相关的平台设备及资源，代码如下： 

// LCD Controller  

//LCD控制器的资源信息 
static struct resource s3c_lcd_resource[ ] = { 
    [ 0] = { 
        . start = S3C24XX_PA_LCD , //控制器IO端口开始地址jjj 
        . end = S3C24XX_PA_LCD + S3C24XX_SZ_LCD - 1 , //控制器IO端口结束地址 
        . flags = IORESOURCE_MEM , //标识为LCD控制器IO端口，在驱动中引用这个就表示引用IO端口 
    } , 
    [ 1] = { 
        . start = IRQ_LCD , //LCD中断 
        . end = IRQ_LCD, 
        . flags = IORESOURCE_IRQ , //标识为LCD中断 
    } 
} ; 

static u64 s3c_device_lcd_dmamask = 0xffffffffUL; 

struct platform_device s3c_device_lcd = { 
    . name         = "s3c2410-lcd" , //作为平台设备的LCD设备名 
    . id         = - 1, 
    . num_resources = ARRAY_SIZE( s3c_lcd_resource) , //资源数量 
    . resource     = s3c_lcd_resource , //引用上面定义的资源 
    . dev = { 
        . dma_mask = & s3c_device_lcd_dmamask, 
        . coherent_dma_mask = 0xffffffffUL
    } 
} ; 

//EXPORT_SYMBOL( s3c_device_lcd) ; //导出定义的LCD平台设备，好在mach-smdk2440.c的smdk2440_devices[]中添加到平台设备列表中 
 

//   除此之外，Linux还在/arch/arm/mach-s3c2410/include/mach/fb.h中为LCD平台设备定义了一个 s3c2410fb_mach_info结构体，该结构体主要是记录LCD的硬件参数信息(比如该结构体的s3c2410fb_display成员结构中就用于记录LCD的屏幕尺寸、屏幕信息、可变的屏幕参数、LCD配置寄存器等)，这样在写驱动的时候就直接使用这个结构体。下面，我们来看一下内核是如果使用这个结构体的。在/arch/arm/mach-s3c2440/mach-smdk2440.c 中定义有： 
//
// LCD driver info  

//LCD硬件的配置信息，注意这里我使用的LCD是NEC 3.5寸TFT屏，这些参数要根据具体的LCD屏进行设置 
static struct s3c2410fb_display smdk2440_lcd_cfg __initdata = { 
    . lcdcon5 = S3C2410_LCDCON5_FRM565 | 
               S3C2410_LCDCON5_INVVLINE | 
               S3C2410_LCDCON5_INVVFRAME | 
               S3C2410_LCDCON5_PWREN | 
               S3C2410_LCDCON5_HWSWP, 

    . type    = S3C2410_LCDCON1_TFT , //TFT类型 
//
    // NEC 3.5'''' 
    . width        = 240 , //屏幕宽度 
    . height       = 320 , //屏幕高度 


    //以下一些参数在上面的时序图分析中讲到过 
    . pixclock     = 100000 , //像素时钟 
    . xres         = 240 , //水平可见的有效像素 
    . yres         = 320 , //垂直可见的有效像素 
    . bpp          = 16 , //色位模式 
    . left_margin  = 19 , //行切换，从同步到绘图之间的延迟 
    . right_margin = 36 , //行切换，从绘图到同步之间的延迟 
    . hsync_len    = 5 , //水平同步的长度 
    . upper_margin = 1 , //帧切换，从同步到绘图之间的延迟 
    . lower_margin = 5 , //帧切换，从绘图到同步之间的延迟 
    . vsync_len    = 1 , //垂直同步的长度 
} ; 

 


 .lcdcon5 = S3C2410_LCDCON5_FRM565 |
               S3C2410_LCDCON5_INVVLINE |
               S3C2410_LCDCON5_INVVFRAME |
               S3C2410_LCDCON5_PWREN |
               S3C2410_LCDCON5_HWSWP,

        .type       = S3C2410_LCDCON1_TFT,
        .width      = 800,//屏幕宽度 
        .height     = 600,//屏幕高度 
        //.pixclock = 100000, // HCLK/10      //像素时钟 
        .pixclock   = 2000000, // HCLK/10    //像素时钟 
        .xres       = 800,   //水平可见的有效像素 
        .yres       = 600,  //垂直可见的有效像素 
        .bpp        = 16,   //色位模式 
        .left_margin    = 40, //2   //行切换，从同步到绘图之间的延迟 
        .right_margin   = 88, //2   //行切换，从绘图到同步之间的延迟 
        .hsync_len  = 128,    //41     //水平同步的长度 
        .upper_margin   = 20,  //2   //帧切换，从同步到绘图之间的延迟 
        .lower_margin   = 20,  //2   //帧切换，从绘图到同步之间的延迟 
        .vsync_len  = 10,   //10    //垂直同步的长度 

};

static struct s3c2410fb_mach_info smdk2440_fb_info __initdata = { 
    . displays        = & smdk2440_lcd_cfg , //应用上面定义的配置信息 
    . num_displays    = 1, 
    . default_display = 0, 

    . gpccon          = 0xaa955699, 
    . gpccon_mask     = 0xffc003cc, 
    . gpcup           = 0x0000ffff, 
    . gpcup_mask      = 0xffffffff, 
    . gpdcon          = 0xaa95aaa1, 
    . gpdcon_mask     = 0xffc0fff0, 
    . gpdup           = 0x0000faff, 
    . gpdup_mask      = 0xffffffff, 

    . lpcsel          = 0xf82, 
} ; 
 

  

//  从上面的代码来看，要使LCD控制器支持其他的LCD屏，重要的是根据LCD的数据手册修改以上这些参数的值。下面，我们再看一下在驱动中是如果引用到 s3c2410fb_mach_info结构体的(注意上面讲的是在内核中如何使用的)。在mach-smdk2440.c中有： 
//

//S3C2440初始化函数 
static void __init smdk2440_machine_init( void ) 
{ 

    //调用该函数将上面定义的LCD硬件信息保存到平台数据中 
    s3c24xx_fb_set_platdata( & smdk2440_fb_info) ; 
    
    s3c_i2c0_set_platdata( NULL ) ; 

    platform_add_devices( smdk2440_devices, ARRAY_SIZE( smdk2440_devices) ) ; 
    smdk_machine_init( ) ;    // 函数在arch/arm/plat-s3c24xx/common-smdk.c,初始化 
} 
 


s3c24xx_fb_set_platdata定义在 plat-s3c24xx/devs.c中： 

void __init s3c24xx_fb_set_platdata( struct s3c2410fb_mach_info * pd) 
{ 
    struct s3c2410fb_mach_info * npd; 

    npd = kmalloc( sizeof ( * npd) , GFP_KERNEL) ; 
    if ( npd) { 
        memcpy ( npd, pd, sizeof ( * npd) ) ; 

        //这里就是将内核中定义的s3c2410fb_mach_info结构体数据保存到LCD平台数据中，所以在写驱动的时候就可以直接在平台数据中获取s3c2410fb_mach_info结构体的数据(即LCD各种参数信息)进行操作 
        s3c_device_lcd. dev. platform_data = npd; 
    } else { 
        printk( KERN_ERR "no memory for LCD platform data/n" ) ; 
    } 
} 
 


   

// 最后：当编译好内核烧到目标板上时，屏闪比较厉害，通过查看屏的datasheet 得知，屏的时钟频率为33MHz,通过工式计算出clkdiv 值为0，最接近lcd 的时钟频率。文件是：drivers/video/s3c2440fb.c
//
clkdiv= 2; 
if (type == S3C2410_LCDCON1_TFT) {
s3c2410fb_calculate_tft_lcd_regs(info, &fbi->regs);
--clkdiv;
if (clkdiv < 0) 
clkdiv = 0; 
} else {
s3c2410fb_calculate_stn_lcd_regs(info, &fbi->regs);
if (clkdiv < 2) 
clkdiv = 2; 
} 

 

// 添加如下代码：clkdiv = 0;
//
//屏不闪了。
//
// 
//
// 
//
// 这里再讲一个小知识：不知大家有没有留意，在平台设备驱动中，platform_data可以保存各自平台设备实例的数据，但这些数据的类型都是不同的，为什么都可以保存？这就要看看platform_data的定义，定义在/linux/device.h中，void *platform_data是一个void类型的指针，在Linux中void可保存任何指针的数据类型。 
//
