//linux�� s3c2440 lcd������ֲ��� .
//���ࣺ linux�豸���� linux C 2010-06-30 18:50 1877���Ķ� ����(1) �ղ� �ٱ� 
//1. LCD������Ӳ������ 
//   Ҫʹһ��LCD��������ʾ���ֻ�ͼ�񣬲�����ҪLCD�����������һ���Ҫ��Ӧ��LCD����������ͨ������£��������̰�LCD����������COF/COG����ʽ��LCD��������������һ�𣬶�LCD�������������ⲿ�ĵ�·��ʵ�֣����ںܶ��MCU�ڲ���������LCD����������S3C2410/2440�ȡ�ͨ��LCD�������Ϳ��Բ���LCD����������Ҫ�Ŀ����ź�������STN/TFT���ˡ�
// 
//2. S3C2440�ڲ�LCD�������ṹͼ�� 
// 
//���Ǹ��������ֲ�������һ�����������S3C2440�ڲ���LCD��������
//a��LCD��������REGBANK��LCDCDMA��TIMEGEN��VIDPRCS�Ĵ�����ɣ�
//b��REGBANK��17���ɱ�̵ļĴ������һ��256*16�ĵ�ɫ���ڴ���ɣ�������������LCD�������ģ�
//c��LCDCDMA��һ��ר�õ�DMA�������Զ��ذ������ڴ��е���Ƶ���ݴ��͵�LCD��������ͨ��ʹ�����DMAͨ������Ƶ�����ڲ���ҪCPU�ĸ�Ԥ���������ʾ��LCD���ϣ�
//d��VIDPRCS��������LCDCDMA�����ݣ�������ת��Ϊ���ʵ����ݸ�ʽ������˵4/8λ��ɨ��4λ˫ɨ��ʾģʽ��Ȼ��ͨ�����ݶ˿�VD[23:0]������Ƶ���ݵ�LCD��������
//e��TIMEGEN�ɿɱ�̵��߼���ɣ�������LCD��������Ҫ�Ŀ����źţ�����VSYNC��HSYNC��VCLK��LEND�ȵȣ�����Щ�����ź�����REGBANK�Ĵ������е�LCDCON1/2/3/4/5������������أ�ͨ����ͬ�����ã�TIMEGEN���ܲ�����Щ�źŵĲ�ͬ��̬���Ӷ�֧�ֲ�ͬ��LCD������(����ͬ��STN/TFT��)��
// 
//3. ����TFT������ʱ������� 
// 
//LCD�ṩ���ⲿ�ӿ��źţ� VSYNC/VFRAME/STV�� ��ֱͬ���ź�(TFT)/֡ͬ���ź�(STN)/SEC TFT�źţ�
//HSYNC/VLINE/CPV�� ˮƽͬ���ź�(TFT)/��ͬ�������ź�(STN)/SEC TFT�źţ�
//VCLK/LCD_HCLK�� ����ʱ���ź�(TFT/STN)/SEC TFT�źţ�
//VD[23:0]�� LCD������������˿�(TFT/STN/SEC TFT)��
//VDEN/VM/TP�� ����ʹ���ź�(TFT)/LCD��������ƫ���ź�(STN)/SEC TFT �źţ�
//LEND/STH�� �н����ź�(TFT)/SEC TFT�źţ�
//LCD_LPCOE�� SEC TFT OE�źţ�
//LCD_LPCREV�� SEC TFT REV�źţ�
//LCD_LPCREVB�� SEC TFT REVB�źš� 
// 
//
// 
//������ʾ����ʾͼ���ԭ���Ǵ��ϵ��£������ҵġ�����ʲô��˼�أ���ô˵�ɣ�һ��ͼ����Կ�����һ�����Σ��ɺܶ���������ĵ�һ��һ����ɣ���Щ���֮Ϊ���ء���ô���ͼ��LCD�ϵ���ʾԭ����ǣ� A�� ��ʾָ��Ӿ������Ͻǵĵ�һ�е�һ���㿪ʼ��һ����һ�������LCD����ʾ���������ʱ��ͼ����ʱ���߱�ʾ��ΪVCLK�����ǳ�֮Ϊ����ʱ���źţ�
//B�� ����ʾָ��һֱ��ʾ�����ε��ұ߾ͽ�����һ�У���ô��һ�еĶ����������ʱ��ͼ�оͳ�֮Ϊ1 Line��
//C�� ��������ʾָ���ֻص����ε���ߴӵڶ��п�ʼ��ʾ��ע�⣬��ʾָ���ڴӵ�һ�е��ұ߻ص��ڶ��е��������Ҫһ����ʱ��ģ����ǳ�֮Ϊ���л���
//D�� ������ƣ���ʾָ�������һ��һ�е���ʾ�����ε����½ǲŰ�һ��ͼ��ʾ��ɡ���ˣ���һ��һ�е���ʾ��ʱ�����Ͽ�������ʱ��ͼ�ϵ�HSYNC��
//E�� Ȼ����LCD����ʾ�����Ƕ�һ��ͼ����ٵ���ʾһ�£�Ϊ�˳������ȶ�����LCD����ʾ������Ҫ�л�����һ��ͼ��(��һ��ͼ���Ժ���һ��ͼһ�����߲�һ����Ŀ��ֻ��Ϊ�˽�ͼ���������ʾ��LCD��)����ô��һ��һ����ͼ��ͳ�֮Ϊ֡����ʱ��ͼ�Ͼͱ�ʾΪ1 Frame����˴�ʱ��ͼ�Ͽ��Կ���1 Lineֻ��1 Frame�е�һ�У�
//F�� ͬ���ģ���֡��֡�л�֮��Ҳ����Ҫһ����ʱ��ģ����ǳ�֮Ϊ֡�л�����ôLCD������ʾ�Ĺ�����ʱ�����Ͽ����Ϳɱ�ʾΪʱ��ͼ�ϵ�VSYNC�� 
// 
//
// 
//����ʱ��ͼ�ϸ�ʱ����ʱ�����ĺ������£�(��Щ������ֵ��LCD�������̻��ṩ��Ӧ�������ֲ�) VBPD(vertical back porch)�� ��ʾ��һ֡ͼ��ʼʱ����ֱͬ���ź��Ժ����Ч����������Ӧ�����е�upper_margin��
//VFBD(vertical front porch)�� ��ʾ��һ֡ͼ������󣬴�ֱͬ���ź���ǰ����Ч����������Ӧ�����е�lower_margin��
//VSPW(vertical sync pulse width)�� ��ʾ��ֱͬ������Ŀ�ȣ����������㣬��Ӧ�����е�vsync_len��
//HBPD(horizontal back porch)�� ��ʾ��ˮƽͬ���źſ�ʼ��һ�е���Ч���ݿ�ʼ֮���VCLK�ĸ�������Ӧ�����е�left_margin��
//HFPD(horizontal front porth)�� ��ʾһ�е���Ч���ݽ�������һ��ˮƽͬ���źſ�ʼ֮���VCLK�ĸ�������Ӧ�����е�right_margin��
//HSPW(horizontal sync pulse width)�� ��ʾˮƽͬ���źŵĿ�ȣ���VCLK���㣬��Ӧ�����е�hsync_len�� 
// 
//
// 
//����������Щ������ֵ���ֱ𱣴浽REGBANK�Ĵ������е�LCDCON1/2/3/4/5�Ĵ����У�(�ԼĴ����Ĳ�����鿴S3c2440�����ֲ�LCD����) LCDCON1��17 - 8λCLKVAL 
//          6 - 5λɨ��ģʽ(����STN��:4λ��/˫ɨ��8λ��ɨ) 
//          4 - 1λɫλģʽ(1BPP��8BPP��16BPP��)
//
//LCDCON2��31 - 24λVBPD 
//         23 - 14λLINEVAL 
//         13 - 6λVFPD 
//          5 - 0λVSPW
//
//LCDCON3��25 - 19λHBPD 
//         18 - 8λHOZVAL 
//          7 - 0λHFPD
//
//LCDCON4�� 7 - 0λHSPW
//
//LCDCON5�� 
// 
//
// 
//4. ֡����(FrameBuffer)�� 
//   ֡������LinuxΪ��ʾ�豸�ṩ��һ���ӿڣ�����һЩ��ʾ�豸������һ��������������Ӧ�ó���ͨ�� FrameBuffer����õĽӿڷ�����Щͼ���豸���Ӷ�����ȥ���ľ����Ӳ��ϸ�ڡ�����֡�����豸���ԣ�ֻҪ����ʾ����������ʾ���Ӧ������д����ɫֵ����Ӧ����ɫ�ͻ��Զ�������Ļ����ʾ����������һ���ڲ�ͬɫλģʽ�»���������ʾ��Ķ�Ӧ��ϵ��
// 
//
//֡����(FrameBuffer)�豸���� �� 
// 
//     ֡�����豸Ϊ��׼���ַ����豸����Linux�����豸��29��������/include/linux/major.h�е�FB_MAJOR�����豸�Ŷ���֡����ĸ��������������32��FrameBuffer��������/include/linux/fb.h�е�FB_MAX����Ӧ���ļ�ϵͳ��/dev /fb%d�豸�ļ��� 
//1. ֡�����豸������Linux��ϵͳ�еĽṹ���£� 
// 
//���Ǵ��������ͼ����֡�����豸��Linux��Ҳ���Կ�����һ����������ϵͳ��������fbmem.c��xxxfb.c��ɡ����ϸ�Ӧ�ó����ṩ���Ƶ��豸�ļ������ӿ�(����FrameBuffer�豸����read��write��ioctl�Ȳ���)���ӿ���Linux�ṩ��fbmem.c�ļ���ʵ�֣������ṩ��Ӳ�������Ľӿڣ�ֻ����Щ�ӿ�Linux��û���ṩʵ�֣���Ϊ��Ҫ���ݾ����LCD������Ӳ���������ã��������������Ҫ����������(��xxxfb.c ���ֵ�ʵ��)�� 
//
//2. ֡������ص���Ҫ���ݽṹ�� 
//   ��֡�����豸��������ṹ������������Ҫ��fb_info�ṹ���йأ��ýṹ���¼��֡�����豸��ȫ����Ϣ�������豸�����ò�����״̬�Լ��Եײ�Ӳ�������ĺ���ָ�롣��Linux �У�ÿһ��֡�����豸�������Ӧһ��fb_info��fb_info��/linux/fb.h�еĶ������£�(ֻ�г���Ҫ��һЩ) 
//

//======================��ע�ͻس�   /*========================= 

struct fb_info { 
    int node; 
    int flags; 
    struct fb_var_screeninfo var; //LCD�ɱ�����ṹ�� 
    struct fb_fix_screeninfo fix; //LCD�̶������ṹ�� 
    struct fb_monspecs monspecs;  //LCD��ʾ����׼ 
    struct work_struct queue ;     //֡�����¼����� 
    struct fb_pixmap pixmap;      //ͼ��Ӳ��mapper 
    struct fb_pixmap sprite;      //���Ӳ��mapper 
    struct fb_cmap cmap;          //��ǰ����ɫ�� 
    struct fb_videomode * mode;    //��ǰ����ʾģʽ 

# ifdef CONFIG_FB_BACKLIGHT
     struct backlight_device * bl_dev;//��Ӧ�ı����豸  
    struct mutex bl_curve_mutex; 
    u8 bl_curve[ FB_BACKLIGHT_LEVELS] ;//�������  
# endif 
# ifdef CONFIG_FB_DEFERRED_IO
    struct delayed_work deferred_work; 
    struct fb_deferred_io * fbdefio; 
# endif 

    struct fb_ops * fbops; //�Եײ�Ӳ�������ĺ���ָ�� 
    struct device * device; 
    struct device * dev;    //fb�豸 
    int class_flag;     
# ifdef CONFIG_FB_TILEBLITTING
    struct fb_tile_ops * tileops; //ͼ��Blitting 
# endif 
    char __iomem * screen_base;    //�������ַ 
    unsigned long screen_size;    //LCD IOӳ��������ڴ��С 
    void * pseudo_palette;         //α16ɫ��ɫ�� 
# define FBINFO_STATE_RUNNING    0
# define FBINFO_STATE_SUSPENDED  1
    u32 state;   //LCD�Ĺ����ָ�״̬ 
    void * fbcon_par; 
    void * par;     
} ; 
 


//���У��Ƚ���Ҫ�ĳ�Ա��struct fb_var_screeninfo var��struct fb_fix_screeninfo fix��struct fb_ops * fbops������Ҳ���ǽṹ�塣��������һ��һ���������� 
//
//fb_var_screeninfo�ṹ����Ҫ��¼�û������޸ĵĿ������Ĳ�����������Ļ�ķֱ��ʺ�ÿ�����صı������ȣ��ýṹ�嶨�����£� 

struct fb_var_screeninfo { 
    __u32 xres;                 //�ɼ���Ļһ���ж��ٸ����ص� 
    __u32 yres;                 //�ɼ���Ļһ���ж��ٸ����ص� 
    __u32 xres_virtual;         //������Ļһ���ж��ٸ����ص�         
    __u32 yres_virtual;         //������Ļһ���ж��ٸ����ص� 
    __u32 xoffset;              //���⵽�ɼ���Ļ֮�����ƫ�� 
    __u32 yoffset;              //���⵽�ɼ���Ļ֮�����ƫ�� 
    __u32 bits_per_pixel;       //ÿ�����ص�λ����BPP 
    __u32 grayscale;            //��0ʱ��ָ���ǻҶ� 

    struct fb_bitfield red;     //fb�����Rλ�� 
    struct fb_bitfield green;   //fb�����Gλ�� 
    struct fb_bitfield blue;    //fb�����Bλ�� 
    struct fb_bitfield transp;  //͸����     

    __u32 nonstd;               // != 0 �Ǳ�׼���ظ�ʽ 
    __u32 activate;                 
    __u32 height;               //�߶� 
    __u32 width;                //��� 
    __u32 accel_flags;     

    //��ʱ������pixclock�����⣬�����Ķ�������ʱ��Ϊ��λ 
    __u32 pixclock;             //����ʱ��(Ƥ��) 
    __u32 left_margin;          //���л�����ͬ������ͼ֮����ӳ� 
    __u32 right_margin;         //���л����ӻ�ͼ��ͬ��֮����ӳ� 
    __u32 upper_margin;         //֡�л�����ͬ������ͼ֮����ӳ� 
    __u32 lower_margin;         //֡�л����ӻ�ͼ��ͬ��֮����ӳ� 
    __u32 hsync_len;            //ˮƽͬ���ĳ��� 
    __u32 vsync_len;            //��ֱͬ���ĳ��� 
    __u32 sync; 
    __u32 vmode; 
    __u32 rotate ; 
    __u32 reserved[ 5] ;          //���� 
} ; 
 


//��fb_fix_screeninfo�ṹ������Ҫ��¼�û��������޸ĵĿ������Ĳ�����������Ļ�������������ַ�ͳ��ȵȣ��ýṹ��Ķ������£� 

struct fb_fix_screeninfo { 
    char id[ 16] ;                 //�ַ�����ʽ�ı�ʾ��  
    unsigned long smem_start;    //fb����Ŀ�ʼλ��  
    __u32 smem_len;              //fb����ĳ���  
    __u32 type;                  //��FB_TYPE_*  
    __u32 type_aux;              //�ֽ� 
    __u32 visual;                //��FB_VISUAL_*  
    __u16 xpanstep;              //���û��Ӳ��panning�͸�ֵΪ0  
    __u16 ypanstep;              //���û��Ӳ��panning�͸�ֵΪ0  
    __u16 ywrapstep;             //���û��Ӳ��ywrap�͸�ֵΪ0  
    __u32 line_length;           //һ�е��ֽ���  
    unsigned long mmio_start;    //�ڴ�ӳ��IO�Ŀ�ʼλ�� 
    __u32 mmio_len;              //�ڴ�ӳ��IO�ĳ��� 
    __u32 accel; 
    __u16 reserved[ 3] ;           //���� 
} ; 
 


//fb_ops�ṹ���ǶԵײ�Ӳ�������ĺ���ָ�룬�ýṹ���ж����˶�Ӳ���Ĳ�����:(����ֻ�г��˳��õĲ���) 

struct fb_ops { 

    struct module * owner; 

     //���ɱ�������������� 
    int ( * fb_check_var) ( struct fb_var_screeninfo * var, struct fb_info * info) ; 

     //�������õ�ֵ���и��£�ʹ֮��Ч 
    int ( * fb_set_par) ( struct fb_info * info) ; 

     //������ɫ�Ĵ��� 
    int ( * fb_setcolreg) ( unsigned regno, unsigned red, unsigned green, 
             unsigned blue, unsigned transp, struct fb_info * info) ; 

     //��ʾ�հ� 
    int ( * fb_blank) ( int blank, struct fb_info * info) ; 

     //������� 
    void ( * fb_fillrect) ( struct fb_info * info, const struct fb_fillrect * rect) ; 

     //�������� 
    void ( * fb_copyarea) ( struct fb_info * info, const struct fb_copyarea * region) ; 

     //ͼ����� 
    void ( * fb_imageblit) ( struct fb_info * info, const struct fb_image * image) ; 
} ; 
 

//3. ֡�����豸��Ϊƽ̨�豸�� 
//   ��S3C2440�У�LCD��������������оƬ���ڲ���Ϊһ����Զ����ĵ�Ԫ������Linux����������һ��ƽ̨�豸�������ں˴���/arch/arm/plat-s3c24xx/devs.c �ж�����LCD��ص�ƽ̨�豸����Դ���������£� 

// LCD Controller  

//LCD����������Դ��Ϣ 
static struct resource s3c_lcd_resource[ ] = { 
    [ 0] = { 
        . start = S3C24XX_PA_LCD , //������IO�˿ڿ�ʼ��ַjjj 
        . end = S3C24XX_PA_LCD + S3C24XX_SZ_LCD - 1 , //������IO�˿ڽ�����ַ 
        . flags = IORESOURCE_MEM , //��ʶΪLCD������IO�˿ڣ�����������������ͱ�ʾ����IO�˿� 
    } , 
    [ 1] = { 
        . start = IRQ_LCD , //LCD�ж� 
        . end = IRQ_LCD, 
        . flags = IORESOURCE_IRQ , //��ʶΪLCD�ж� 
    } 
} ; 

static u64 s3c_device_lcd_dmamask = 0xffffffffUL; 

struct platform_device s3c_device_lcd = { 
    . name         = "s3c2410-lcd" , //��Ϊƽ̨�豸��LCD�豸�� 
    . id         = - 1, 
    . num_resources = ARRAY_SIZE( s3c_lcd_resource) , //��Դ���� 
    . resource     = s3c_lcd_resource , //�������涨�����Դ 
    . dev = { 
        . dma_mask = & s3c_device_lcd_dmamask, 
        . coherent_dma_mask = 0xffffffffUL
    } 
} ; 

//EXPORT_SYMBOL( s3c_device_lcd) ; //���������LCDƽ̨�豸������mach-smdk2440.c��smdk2440_devices[]����ӵ�ƽ̨�豸�б��� 
 

//   ����֮�⣬Linux����/arch/arm/mach-s3c2410/include/mach/fb.h��ΪLCDƽ̨�豸������һ�� s3c2410fb_mach_info�ṹ�壬�ýṹ����Ҫ�Ǽ�¼LCD��Ӳ��������Ϣ(����ýṹ���s3c2410fb_display��Ա�ṹ�о����ڼ�¼LCD����Ļ�ߴ硢��Ļ��Ϣ���ɱ����Ļ������LCD���üĴ�����)��������д������ʱ���ֱ��ʹ������ṹ�塣���棬��������һ���ں������ʹ������ṹ��ġ���/arch/arm/mach-s3c2440/mach-smdk2440.c �ж����У� 
//
// LCD driver info  

//LCDӲ����������Ϣ��ע��������ʹ�õ�LCD��NEC 3.5��TFT������Щ����Ҫ���ݾ����LCD���������� 
static struct s3c2410fb_display smdk2440_lcd_cfg __initdata = { 
    . lcdcon5 = S3C2410_LCDCON5_FRM565 | 
               S3C2410_LCDCON5_INVVLINE | 
               S3C2410_LCDCON5_INVVFRAME | 
               S3C2410_LCDCON5_PWREN | 
               S3C2410_LCDCON5_HWSWP, 

    . type    = S3C2410_LCDCON1_TFT , //TFT���� 
//
    // NEC 3.5'''' 
    . width        = 240 , //��Ļ��� 
    . height       = 320 , //��Ļ�߶� 


    //����һЩ�����������ʱ��ͼ�����н����� 
    . pixclock     = 100000 , //����ʱ�� 
    . xres         = 240 , //ˮƽ�ɼ�����Ч���� 
    . yres         = 320 , //��ֱ�ɼ�����Ч���� 
    . bpp          = 16 , //ɫλģʽ 
    . left_margin  = 19 , //���л�����ͬ������ͼ֮����ӳ� 
    . right_margin = 36 , //���л����ӻ�ͼ��ͬ��֮����ӳ� 
    . hsync_len    = 5 , //ˮƽͬ���ĳ��� 
    . upper_margin = 1 , //֡�л�����ͬ������ͼ֮����ӳ� 
    . lower_margin = 5 , //֡�л����ӻ�ͼ��ͬ��֮����ӳ� 
    . vsync_len    = 1 , //��ֱͬ���ĳ��� 
} ; 

 


 .lcdcon5 = S3C2410_LCDCON5_FRM565 |
               S3C2410_LCDCON5_INVVLINE |
               S3C2410_LCDCON5_INVVFRAME |
               S3C2410_LCDCON5_PWREN |
               S3C2410_LCDCON5_HWSWP,

        .type       = S3C2410_LCDCON1_TFT,
        .width      = 800,//��Ļ��� 
        .height     = 600,//��Ļ�߶� 
        //.pixclock = 100000, // HCLK/10      //����ʱ�� 
        .pixclock   = 2000000, // HCLK/10    //����ʱ�� 
        .xres       = 800,   //ˮƽ�ɼ�����Ч���� 
        .yres       = 600,  //��ֱ�ɼ�����Ч���� 
        .bpp        = 16,   //ɫλģʽ 
        .left_margin    = 40, //2   //���л�����ͬ������ͼ֮����ӳ� 
        .right_margin   = 88, //2   //���л����ӻ�ͼ��ͬ��֮����ӳ� 
        .hsync_len  = 128,    //41     //ˮƽͬ���ĳ��� 
        .upper_margin   = 20,  //2   //֡�л�����ͬ������ͼ֮����ӳ� 
        .lower_margin   = 20,  //2   //֡�л����ӻ�ͼ��ͬ��֮����ӳ� 
        .vsync_len  = 10,   //10    //��ֱͬ���ĳ��� 

};

static struct s3c2410fb_mach_info smdk2440_fb_info __initdata = { 
    . displays        = & smdk2440_lcd_cfg , //Ӧ�����涨���������Ϣ 
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
 

  

//  ������Ĵ���������ҪʹLCD������֧��������LCD������Ҫ���Ǹ���LCD�������ֲ��޸�������Щ������ֵ�����棬�����ٿ�һ������������������õ� s3c2410fb_mach_info�ṹ���(ע�����潲�������ں������ʹ�õ�)����mach-smdk2440.c���У� 
//

//S3C2440��ʼ������ 
static void __init smdk2440_machine_init( void ) 
{ 

    //���øú��������涨���LCDӲ����Ϣ���浽ƽ̨������ 
    s3c24xx_fb_set_platdata( & smdk2440_fb_info) ; 
    
    s3c_i2c0_set_platdata( NULL ) ; 

    platform_add_devices( smdk2440_devices, ARRAY_SIZE( smdk2440_devices) ) ; 
    smdk_machine_init( ) ;    // ������arch/arm/plat-s3c24xx/common-smdk.c,��ʼ�� 
} 
 


s3c24xx_fb_set_platdata������ plat-s3c24xx/devs.c�У� 

void __init s3c24xx_fb_set_platdata( struct s3c2410fb_mach_info * pd) 
{ 
    struct s3c2410fb_mach_info * npd; 

    npd = kmalloc( sizeof ( * npd) , GFP_KERNEL) ; 
    if ( npd) { 
        memcpy ( npd, pd, sizeof ( * npd) ) ; 

        //������ǽ��ں��ж����s3c2410fb_mach_info�ṹ�����ݱ��浽LCDƽ̨�����У�������д������ʱ��Ϳ���ֱ����ƽ̨�����л�ȡs3c2410fb_mach_info�ṹ�������(��LCD���ֲ�����Ϣ)���в��� 
        s3c_device_lcd. dev. platform_data = npd; 
    } else { 
        printk( KERN_ERR "no memory for LCD platform data/n" ) ; 
    } 
} 
 


   

// ��󣺵�������ں��յ�Ŀ�����ʱ�������Ƚ�������ͨ���鿴����datasheet ��֪������ʱ��Ƶ��Ϊ33MHz,ͨ����ʽ�����clkdiv ֵΪ0����ӽ�lcd ��ʱ��Ƶ�ʡ��ļ��ǣ�drivers/video/s3c2440fb.c
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

 

// ������´��룺clkdiv = 0;
//
//�������ˡ�
//
// 
//
// 
//
// �����ٽ�һ��С֪ʶ����֪�����û�����⣬��ƽ̨�豸�����У�platform_data���Ա������ƽ̨�豸ʵ�������ݣ�����Щ���ݵ����Ͷ��ǲ�ͬ�ģ�Ϊʲô�����Ա��棿���Ҫ����platform_data�Ķ��壬������/linux/device.h�У�void *platform_data��һ��void���͵�ָ�룬��Linux��void�ɱ����κ�ָ����������͡� 
//
