//Linux-2.6.20��LCD����������һ��[ת] .
//���ࣺ Ƕ��ʽLinux������д 2008-07-24 09:42 1150���Ķ� ����(0) �ղ� �ٱ� 
// 
//һ����LCD��ʾ�ɰ���С���
//������˵˵�����ɣ�������ΪS3C2410��linux�İ汾��Ȼ��2.6.20�ġ�������˵˵������LCD����ʾ���ɰ���С��졣��ֱ�ӵĲ������£���ס��Ҫ��Ϊʲô����_����һ��һ�������߾����ˣ���
//
//1.       ���s3c2410��������LCD���ƼĴ����ĳ�ʼֵ����������Ϊ���ļ�arch/arm/mach-s3c2410/mach-smdk2410.c�����struct s3c2410fb_mach_info���͵ļĴ�������ѶϢ��������ʾ��
  
  
  
//======================��ע�ͻس�   /*=========================

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

 
//2. ͨ��s3c24xx_fb_set_platdata�������ں�ע���������Ϣ����������Ϊ���޸�s3c24xx_fb_set_platdata��������ȻҲ�������������֣����޸����£����˺�����arch/arm/mach-s3c2410/devs.c�У�
//
 
void __init s3c24xx_fb_set_platdata(struct s3c2410fb_mach_info *pd)

{

s3c_device_lcd.dev.platform_data = pd;

}

 
//Ȼ����arch/arm/mach-s3c2410/mach-smdk2410.c��smdk2410_map_io�����е���s3c24xx_fb_set_platdata( )������Ϊ��
//
//s3c24xx_fb_set_platdata(&smdk2410_lcd_platdata);
//
//ע���˴�δ�����ں����ṩ��Դ��������Ϊϵͳ�������������������kmalloc��������ġ�
//
// 
//3. ��make menuconfig��ʱ������Linux��logoѡ�Ȼ���ʱ����consoleѡ����ѡ��framebuffer console surpport��Ҫ��Ȼ������С��졣
//
//������Щ�������Դ�����ϣ���л���ǵ���˽���ף��ٺ٣���ĿǰΪֹ���Ҳ���Խ����ˣ����һ��������˽�һ���������������򡣺Ǻǣ���֪������������»طֽ⡣
//
//
//
//
//
//
//Linux-2.6.20��LCD��������������[ת] .
//���ࣺ Ƕ��ʽLinux������д 2008-07-24 09:45 1871���Ķ� ����(0) �ղ� �ٱ� 
//����s3c2410fb_probe��������
//2.1 ��������ڵ�
//������ǰ�ĵ�һ����������Ӧ���ǣ���������Ǵ����￪ʼ���еġ������Ӧ�ô�long long ago ��ʼ�ˣ���drivers/video/s3c2410fb.c�ļ���Ȼ���ҵ�s3c2410fb_init�������Ȳ�������������ô���£��ٰ�Ŀ�����ƾͻῴ������һ���ַ���module_init(s3c2410fb_init)�����ƣ����S3C2410fb_probe��ɶ��ϵ���������ʵĺã���Ҫ�ż������������ߡ�������module_init�Ǻη���ʥ��˵�����Ǻ��Ҿ͵�½��http://lxr.linux.no/linux+v2.6.20/��վ��������һ�ѣ�ԭ��module_init�ϼ���include/linux/init.h��ԭ������Ȼ����������ݣ���ԭ�����£�
#ifndef MODULE
����
#define //module_init(x) __initcall(x);                               ��
����
#else
����
#define //module_init(initfn)                                 /              ��
       static inline initcall_t __inittest(void)            /
       { return initfn; }                                         /
       int init_module(void) __attribute__((alias(#c)));
����
#endif
 
//��������Կ�����module_init�������ĸ�����ȡ����MODULE�ˣ���ôMODULE��������ʲô�أ�����֪��Linux���Խ��豸����ģ�鶯̬�ӽ��ںˣ�Ҳ����ֱ�ӱ�����ںˣ�˵���������е�����MODULE�������ˣ�����������Ҫ����һ�����������ں˵ķ�ʽ��������MODULE�ͱ�ʾ���豸����ģ�鶯̬���롣��������Ģٱ�ʾ���豸�ӽ��ںˡ��ڢ��е�__attribute__((alias(#initfn)))������˼�������ʲô�أ���Ҫalias�������Ե���˼������Ӣ����˼�Ǳ�����������http://publib.boulder.ibm.com/infocenter/lnxpcomp/v8v101/index.jsp?topic=/com.ibm.xlcpp8l.doc/language/ref/fn_attrib_alias.htm�ҵ�������ϸ˵��������򵥵�˵int init_module(void) __attribute__((alias(#initfn)));����˼Ϊinit_module��initfn�ı���������init_module��initfn��һ�����ӣ��ټ�һ��˵���ʱ��module_init�����ͻ�����init_module()�ˡ����ڵ�һ�������__initcall(fn) �ֱ��궨�����device_initcall(fn)��Ҳ����˵module_init(x)����device_initcall(fn)������device_initcall(fn)����һ���궨�壬�����������__define_initcall("6",fn,6)������������ʾʲô��˼��������Ͳ������ظ��ˣ���Linux-2.6.20��cs8900��������(һ)��ƪ�������ж����Ľ��ء�
//       ���憪������ô�࣬������Ҫ˵��ֻҪ��module_init������һ���������ú����ͻᱻLinux�ں����ʵ���ʱ�����У���Щʱ��������linux������do_initcalls()ʱ���ã��豸��������ںˣ��������ڶ�̬����ʱ���á�
//       �ص������module_init(s3c2410fb_init)����Ҳ����˵�ں���buffer����������ϵ�ĵ�һ�εص�����s3c2410fb_init�������ú�����ֻ��һ�����
//platform_driver_register (&s3c2410fb_driver)��
//����������������
 
//2.2 platform�Ǻ�����Ҳ
//       platform��������һ���豸���ͣ������ַ��豸�����豸�������豸һ������LCD�����������豸������platform�豸LinuxΪӦ���������صĽӿڣ�������ֻ�Ǽ򵥵�˵˵��Щ�ӿڵ��÷�������ȥ����̽����Щ�ӿڵ�ʵ�֣������ڻ�û���Ǹ������أ�����˵��������Ͼ��и�����ӿ����ͷ�ˣ��Ǿ���Linux�ṩ����Щ�ӿ��أ����������Ҫ�����Щ�豸Ӧ����ô�����أ�
//       platform�е�������ݽṹ��Ӧ�õĹؼ���Ϊ�����ں����һ��platform�豸������ԱӦ����д�������ݽṹplatform_device ��platform_driver�����������ݽṹ�Ķ��嶼������include/linux/platform_device.h�ļ����ҵ�������LCD��������ô���ģ���һ������дplatform_device����arch/arm/mach-s3c2410/devs.c�����ҵ���дplatform_device�Ĵ��룬���£�
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
//    ������ĸ������ݳ�Ա����˼����platform_device���ݽṹ������ϸ��˵�������ﲻ׸��������Ĵ����е�ARRAY_SIZE�껹�ǱȽ�����˼�ģ���ʵ�Ǹ�c�ı�̼��ɣ�������ɺ�����Ŷ��������include/linux/kernel.h���ҵ����Ķ��壺
//#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
//�ú���Է�������һ���������ж������ݳ�Ա�����ںܶ�������Ǻ����õģ��������   int a[]={1,5,65,23,12,20,3}���飬����ʹ�øú����a[]��7��Ԫ�ء�
//    ���⣬platform_device������һ����Ҫ��Ա��resource��������Ĵ����д��򱻸�����s3c_lcd_resource��s3c_lcd_resourceҲ������arch/arm/mach-s3c2410/devs.c�ҵ���
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
//struct resource�ṹʵ���������˸��豸ռ�õ�Ӳ����Դ�����ַ�ռ䣬�жϺŵ�s����s3c_lcd_resource�������ڴ�ռ���жϷ��������
//    �����smdk2410_devicesָ�������������s3c_device_lcd�Ĵ�����Linux�ڳ�ʼ��platform��ʱ���֪��ϵͳ���и�s3c_device_lcd�豸�ˡ�ע��������ֻ����Linux�������豸��Ҫ����Դ������������ں˻����Щ��Դ�ġ�����豸Ҫ�õ���Щ�豸����Ҫ���Լ��ĳ�ʼ��������ȥ���롣
 
static struct platform_device *smdk2410_devices[] __initdata = {
       &s3c_device_usb,
       &s3c_device_lcd,
       &s3c_device_wdt,
       &s3c_device_i2c,
       &s3c_device_iis,
       &s3c_device_ts,
};
//˵�����Ӧ��˵��Linux���һ��platform�豸Ӧ�ú����ס�
// 
//2.2 �ص�s3c2410fb_init
//���ڰ�platform�����֪ʶ������һ��������ص�s3c2410fb_init����������platform_driver_register(&s3c2410fb_driver)���򵥵�˵platform_driver_registerҪ�����ں�ע��һ��platform�豸��������������Ҫע��LCD�豸������˵��platform��������Ҫ�����ݽṹplatform_device��platform_driver��������Ӧ���ᵽ���ߵ�ʱ���ˡ�platform_driverҲ��include/linux/platform_device.h�У����ĸ�����ԱӦ�������ײ������ɣ���LCD��������drivers/video/s3c2410fb.c���ж����������platform_driver����ṹ�����£�
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
//���Կ�����platform�豸������������s3c2410fb_probe��s3c2410fb_remove�ȵȡ�ͨ��platform_driver_register����ע����豸�Ĺ����У�����ص�.probe������˵������Ҳ������s3c2410fb_probe����platform_driver_registe�лص��ġ���ĿǰΪֹ������������ǧ�ﳤ�����ڵ���s3c2410fb_probe��LCD�����������ˡ�
// 
//2.3 s3c2410fb_probe����
//       ���ڸú�����������õİ취���Ǹ��ų���һ��һ���Ľ��͡�OK��let��s go to ����
static int __init s3c2410fb_probe(struct platform_device *pdev)
{
       struct s3c2410 fb_info *info;  //s3c2410fb_info�ṹ��driver/video/s3c2410fb.h�ж��壬
//����˵�ýṹ��¼��s3c2410fb������������Ϣ��
       struct fb_info     *fbinfo;    // fb_infoΪ�ں��ṩ��buffer�����Ľӿ����ݽṹ, ÿ��֡������������Ӧһ�������Ľṹ��s3c2410fb_probe������Ŀ�����ýṹ�������ں�ע�ᡣ
       struct s3c2410fb_hw *mregs;  // s3c2410fb_hwΪ����LCD��Ӳ�����ƼĴ����Ľṹ�壬
//��include/asm-arm/arch-s3c2410/fb.h�����ҵ�����ԭ�͡�
����
 
       mach_info = pdev->dev.platform_data;  //��һ������Ҫ���Щ�����ˡ�mach_info��һ��s3c2410fb_mach_info���͵�ָ�룬ע������s3c2410fb_mach_info��s3c2410fb_info�ṹ,�򵥵�˵ǰ��ֻ����������LCD��ʼ��ʱ���õ�ֵ������������������LCD�����Ľṹ�塣s3c2410fb_mach_info��include/asm-arm/arch-s3c2410/fb.h�ж��壬������λ�ÿ��Կ�������ƽ̨��أ�Ҳ���������ں���֪�����ݽṹ����ֻ�����������������ƵĽṹ���������Ҫ������ʲô�أ��������if�����Կ������mach_info����NULL�Ļ�����������������˳��ˣ��������������D�Dpdev->dev.platform_data����ʲôʱ�򱻳�ʼ�����أ�����Ҫ�ش�������⣬��ʷӦ�ûص�����մ����칬��ʱ���ˡ���ס����������һֱ����ƪ���µĵ�һ���֣������Ǹ�ʱ������Щʲô���������������͵�һ���ֵ�����ϣ��û��Ϊʱ������ʵ���ں�����init����֮ǰ�ͻ�ִ��smdk2410_map_io( )�������ں˵��������������˰�@_@��������smdk2410_map_io( )�����Ǽ�����
s3c24xx_fb_set_platdata (&smdk2410_lcd_platdata);
//������䣬s3c24xx_fb_set_platdata()��ʵ��Ϊ��
void __init s3c24xx_fb_set_platdata(struct s3c2410fb_mach_info *pd)
{
    s3c_device_lcd.dev.platform_data = pd;
}
//������Щ���룬��������Ŀ���s3c_device_lcd.dev.platform_dataָ����smdk2410_lcd_platdata�������smdk2410_lcd_platdata����һ��s3c2410fb_mach_info�ı�����������ʹ����LCD������ʼ����Ҫ�ĳ�ʼ���ݡ���s3c2410fb_probe���ص�ʱ�����������Ĳ���ʵ�ʾ���s3c_device_lcd���׵�ַ��˵������һ��Ӧ�ö������˰ɣ����ˣ��ֳ���һͨ�����ڼ����ⲽ�ɹ��������������ߡ�
      if (mach_info == NULL) {
              dev_err(&pdev->dev,"no platform data for lcd, cannot attach/n");
              return -EINVAL;
       }
 
       mregs = &mach_info->regs;    //mregsָ��Ӳ�������ƼĴ����ĳ�ʼֵ���ɲμ���һ��
//�ֵ�smdk2410_lcd_platdata������
 
       irq = platform_get_irq(pdev, 0);  //�ú�������жϺţ��ú�����ʵ����ͨ���Ƚ�struct resource��flags�򣬵õ�irq�жϺţ�����2.1��ʱ���ᵽs3c_lcd_resource[]��platform_get_irq������⵽flags����IORESOURCE_IRQʱ�ͷ����жϺ�IRQ_LCD����ϸ�������������Դ����ɣ�
       if (irq < 0) {          //û���ҵ����õ��жϺţ�����-ENOENT
              dev_err(&pdev->dev, "no irq for device/n");
              return -ENOENT;
       }
 
       fbinfo = framebuffer_alloc(sizeof(struct s3c2410fb_info), &pdev->dev);  // framebuffer_alloc������include/linux/fb.h�ļ����ҵ���ԭ�ͣ�struct fb_info *framebuffer_alloc(size_t size, struct device *dev); ���Ĺ��������ں�����һ�δ�СΪsizeof(struct fb_info) + size�Ŀռ䣬����size�Ĵ�С�����豸��˽�����ݿռ䣬����fb_info��par��ָ���˽�пռ䡣
       if (!fbinfo) {
              return -ENOMEM;
       }
 
//���¿�ʼ���������ˣ����fbinfo�ˡ�
       info = fbinfo->par;   //�������ң��������㣡
       info->fb = fbinfo;
       platform_set_drvdata(pdev, fbinfo);           //�ú�����ʵ�ַǳ��򵥣�ʵ�ʵĲ���Ϊ��pdev->dev.driver_data �� fbinfo��device�ṹ��driver_data��ָ�����������˽�����ݿռ䡣
 
       dprintk("devinit/n");
 
       strcpy(fbinfo->fix.id, driver_name);  
 
       memcpy(&info->regs, &mach_info->regs, sizeof(info->regs));
 
       // Stop the video and unset ENVID if set 
       info->regs.lcdcon1 &= ~S3C2410_LCDCON1_ENVID;
       lcdcon1 = readl(S3C2410_LCDCON1);
       writel(lcdcon1 & ~S3C2410_LCDCON1_ENVID, S3C2410_LCDCON1);//ֹͣӲ��
 
//���µĶ�fbinfo����д�����˰ɣ�����fb_info�ṹ�ĸ�����Ա����include/linux/fb�ļ��ж�����ϸ��˵���������֪��˵������˼����Ӧ����Щ������֪ʶ�����ˡ����ڶ�ĳ�ʼ���У�fbinfo->fbops = &s3c2410fb_ops;��ֵ��һ��ģ�����s3c2410fb_ops ����s3c2410fb.c�ж��壬����¼�˸�֡������������֧�ֵĲ��� 
 
����
 
       for (i = 0; i < 256; i++)  //��ʼ����ɫ�建����
              info->palette_buffer[i] = PALETTE_BUFF_CLEAR;
 
       if (!request_mem_region((unsigned long)S3C24XX_VA_LCD, SZ_1M, "s3c2410-lcd")) {
// ���ں������ڴ�ռ䣬���request_mem_region����0��ʾ����ʧ�ܣ���ʱ��������dealloc_fb����ʼִ�У��ô������framebuffer_release�ͷŸղ���framebuffer_alloc�����fb_info�ռ� 
              ret = -EBUSY;
              goto dealloc_fb;
       }
����
       ret = request_irq(irq, s3c2410fb_irq, IRQF_DISABLED, pdev->name, info);// ���ں�ע���жϣ����ע��ʧ�ܣ�������ת��release_mem�����У��˴��ͷ�fb_info�͸ղ���request_mem_region������ڴ�ռ� 
       if (ret) {
              dev_err(&pdev->dev, "cannot get irq %d - err %d/n", irq, ret);
              ret = -EBUSY;
              goto release_mem;
       }
 
       info->clk = clk_get(NULL, "lcd");  //�ú����õ�ʱ��Դ������Ӳ�����������������ҵ�
//���ӣ�������arch/arm/mach-s3c2410/clock.c��������ԭ�ͺ�ʵ�֡�
       if (!info->clk || IS_ERR(info->clk)) {
              printk(KERN_ERR "failed to get lcd clock source/n");
              ret = -ENOENT;
              goto release_irq;  //�ô��ͷ����������fb_info���ڴ棬��irq��Դ
       }
 
       clk_enable(info->clk);   //��ʱ��
       dprintk("got and enabled clock/n");
 
       msleep(1);          //���е�̫���е����ˣ�ȥ�������˵
 
       // Initialize video memory 
       ret = s3c2410fb_map_video_memory(info);//�˺�������s3c2410fb.c�ļ��б����壬��������������֡�������ڴ�ռ� 
       if (ret) {
              printk( KERN_ERR "Failed to allocate video RAM: %d/n", ret);
              ret = -ENOMEM;
              goto release_clock;            //�ͷ������ѵõ�����Դ
       }
       dprintk("got video memory/n");
 
       ret = s3c2410fb_init_registers(info);   //�˺���Ҳ��s3c2410fb.c�ļ��ж��壬��������
 
       ret = s3c2410fb_check_var(&fbinfo->var, fbinfo);   //�˺���Ҳ��s3c2410fb.c�ļ��ж���
 
       ret = register_framebuffer(fbinfo);  //��ʥ��ʱ�����ڵ��������ں���ʽע�ᡣ
       if (ret < 0) {
              printk(KERN_ERR "Failed to register framebuffer device: %d/n", ret);
              goto free_video_memory; //����ע�������ƣ��Ǿ��ͷ����е���Դ���������ˣ�
       }
 
       // create device files 
       device_create_file(&pdev->dev, &dev_attr_debug); //Ϊ���豸����һ����sysfs�е�����
 
       printk(KERN_INFO "fb%d: %s frame buffer device/n",
              fbinfo->node, fbinfo->fix.id);
 
       return 0;           //�󹦸�ɣ�
 
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




//Linux-2.6.20��LCD��������������[ת] .
//���ࣺ Ƕ��ʽLinux������д 2008-07-24 09:47 1869���Ķ� ����(0) �ղ� �ٱ� 
// 
//��������s3c2410fb_driver����
//s3c2410fb_driver������ʲô�����أ���ǰ���2.2���ᵽ�����Ķ��壬������ԭ�Ϳ��Կ��� s3c2410fb_driver�Ǹ�platform_driver���͵ı�����ǰ��ļ���С���ᵽ�˴�platform_driver�����ֿ��Կ�����Ӧ����platform_device���������͡�Ϊ�˷����Ķ�����������һ��s3c2410fb_driver�Ķ��壺
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
//�Ӷ�����Կ�������platform_device������������s3c2410fb_probe�� s3c2410fb_remove��s3c2410fb_suspend��s3c2410fb_suspend��.resource��Աǰ����½���˵����.driver��Ա��ֵ���Ų�����˵���˰ɣ������ײ����ˡ�ǰ����½ڣ�s3c2410fb_probe���Ƚ���ϸ�Ľ��ܣ�����е���Ҫ������ǽ��������ļ����������ڽ�������֮ǰ��s3c2410fb_probe�����ڸú�����β��ʱ������˼�������û��˵�������������ﲹ�ϡ�
// 
//3.1 s3c2410fb_probe�൳
//       ��s3c2410fb_probe����õ�����s3c2410fb_init_registers��s3c2410fb_check_var����������Ӧ�ý����ǽ������������Ȼ��s3c2410fb_init_registers�ǳ�ʼ����ؼĴ�������ô�����أ������Ȱ� s3c2410fb_init_registers�㶨��˵��s3c2410fb_init_registers�Ķ�����ʵ�����£��ȸ�������ָ�����̣�һ��һ�����ͣ�
 
static int s3c2410fb_init_registers(struct s3c2410fb_info *fbi)
{
       unsigned long flags;
 
       // Initialise LCD with values from haret 

 
       local_irq_save(flags);     // �ر��жϣ��ڹر��ж�ǰ���жϵĵ�ǰ״̬��������flags�У����ڹر��жϵĺ�����linux�ں��кܶ��֣����Բ�����ص����ϡ�
 
       // modify the gpio(s) with interrupts set (bjd) 

//�����modify_gpio�������޸Ĵ�����GPIO�Ĺ���ģʽ������ʵ�ֺܼ򵥣����ڶ���������ֵ������������ķ��밴λ���������д����һ������������ĵ�һ������ʵ�ʾ���Ӳ����GPIO��������
       modify_gpio(S3C2410_GPCUP,  mach_info->gpcup,  mach_info->gpcup_mask);

       modify_gpio(S3C2410_GPCCON, mach_info->gpccon, mach_info->gpccon_mask);

       modify_gpio(S3C2410_GPDUP,  mach_info->gpdup,  mach_info->gpdup_mask);

       modify_gpio(S3C2410_GPDCON, mach_info->gpdcon, mach_info->gpdcon_mask);

 
       local_irq_restore(flags);  //ʹ���жϣ����ָ���ǰ��״̬
  //����ļ���writel������ʼ��ʼ��LCD���ƼĴ���������ֵ����������smdk2410_lcd_platdata(arch/arm/mach-s3c2410/mach-smdk2410.c)��regs���ֵ��
       writel(fbi->regs.lcdcon1, S3C2410_LCDCON1);
       writel(fbi->regs.lcdcon2, S3C2410_LCDCON2);
       writel(fbi->regs.lcdcon3, S3C2410_LCDCON3);
       writel(fbi->regs.lcdcon4, S3C2410_LCDCON4);
       writel(fbi->regs.lcdcon5, S3C2410_LCDCON5);
 
      s3c2410fb_set_lcdaddr(fbi);    //�ú�������Ҫ�������ô�������LCD��������������ַ�Ĵ���ָ����ȷ��λ�ã����λ�þ���LCD�Ļ���������ϸ��������Բμ�s3c2410���û��ֲᡣ
����
       // Enable video by setting the ENVID bit to 1 �����video����s3c2410fb_probe�б��ر��ˣ������

       fbi->regs.lcdcon1 |= S3C2410_LCDCON1_ENVID;
       writel(fbi->regs.lcdcon1, S3C2410_LCDCON1);
       return 0;
}
//OK��s3c2410fb_init_registers�ͼ򵥽��ܵ�������濴�� s3c2410fb_check_var����Ҫ��Щʲô�£�Ҫ˵����������������ᵽfb_var_screeninfo�ṹ���ͣ�������Ӧ���� fb_fix_screeninfo�ṹ���͡����������ͷֱ��������ʾ����������Ϣ����Щ��Ϣ���Է�Ϊ�ɱ�������Ϣ���磺��ɫ��ȣ��ֱ��ʵȣ��Ͳ��ɱ����Ϣ����֡�������ʵ��ַ������Ȼfb_var_screeninfo��ʾ�˿ɱ��������Ϣ����ô��Щ�ɱ���Ϣ��Ӧ����һ����Χ��������ʾ�ͻ�����⣬����s3c2410fb_check_var�����Ĺ��ܾ���Ҫ��LCD��֡����������ʼ����֮ǰ����Щֵ��ʼ���Ϸ��ķ�Χ�ڡ�֪���� s3c2410fb_check_varҪ��ʲô����ȥ�Ķ�s3c2410fb_check_var�����Ĵ����ûʲô�����ˡ�
// 
//3.2 s3c2410fb_remove
//       �����￪ʼ������s3c2410fb_driver�е�����������������ô�ʹ�s3c2410fb_remove�����ɣ�����˼��ú����͸�֪������Ҫ�����platform�豸��ϵͳ���Ƴ��������Ʋ���Ӧ���ͷŵ����е���Դ�������ڴ�ռ䣬�ж��ߵȵȡ����ǰ��չ�����������ʵ�ִ�����һ�����Ľ��͡�
static int s3c2410fb_remove(struct platform_device *pdev)
{
       struct fb_info     *fbinfo = platform_get_drvdata(pdev);  //�ú�����platform_device�У���fb_info��Ϣ

       struct s3c2410fb_info *info = fbinfo->par;  //�õ�˽������
       int irq;
 
       s3c2410fb_stop_lcd(info);    //�ú���ֹͣLCD��������ʵ�ֿ�����s3c2410fb.c���ҵ�
       msleep(1); //��Ϣ���£��ȴ�LCDֹͣ
 
       s3c2410fb_unmap_video_memory(info);   //�ú����ͷŻ�����
 
      if (info->clk) {          //ֹͣʱ��

             clk_disable(info->clk);
             clk_put(info->clk);
             info->clk = NULL;

       }
 
       irq = platform_get_irq(pdev, 0);     //�õ��ж��ߣ��Ա��ͷ�
       free_irq(irq,info);    //�ͷŸ��ж�
       release_mem_region((unsigned long)S3C24XX_VA_LCD, S3C24XX_SZ_LCD); // �ͷ��ڴ�ռ� 
       unregister_framebuffer(fbinfo);       //���ں�ע����֡����
 
       return 0;
}
 
//3.3 s3c2410fb_suspend��s3c2410fb_resume
//       ��ʵ�ʵ��豸���������Կ���LCD�ڲ���Ҫ��ʱ���������״̬������Ҫʹ�õ�ʱ���ֿ�ʼ�����������ֻ����ڲ���Ҫ��ʱ��LCD��Ϩ�𣬵���Ҫʹ�õ�ʱ�� LCD�ֱ���������ʵ���п��Կ�����Ժ����ǳ���Ҫ����Ȼ���Ǻ���Ҫ������һ���ܸ��ӣ����濴����������ô��ʵ�ֵġ�
// 
static int s3c2410fb_suspend(struct platform_device *dev, pm_message_t state)

{
       struct fb_info     *fbinfo = platform_get_drvdata(dev);  //��������������^_^

       struct s3c2410fb_info *info = fbinfo->par;
 
       s3c2410fb_stop_lcd(info);  //ֹͣLCD
 
       // sleep before disabling the clock, we need to ensure

        * the LCD DMA engine is not going to get back on the bus

        * before the clock goes off again (bjd) 

 
       msleep(1);  //�ȴ�һ�£���ΪLCDֹͣ��Ҫһ��ʱ��
       clk_disable(info->clk);  //�ر�LCD��ʱ��
 
       return 0;
}
//^_^������Ĵ���Ͳ��ý����˰ɣ�
static int s3c2410fb_resume(struct platform_device *dev)
{
       struct fb_info     *fbinfo = platform_get_drvdata(dev);

       struct s3c2410fb_info *info = fbinfo->par;
 
       clk_enable(info->clk);
       msleep(1);
 
       s3c2410fb_init_registers(info);
 
       return 0;
}
 
//OK��������Ϊֹ������platform device�����������over�ˡ��������ʵĻ��ں�ͷŶ��
//





//Linux-2.6.20��LCD�����������ģ�[ת] .
//2008-07-24 09:49 807���Ķ� ����(1) �ղ� �ٱ� 
// 
//�ġ�s3c2410fb_ops�������
//      ������������У���Ϊ��ϸ�Ľ�����platform device��صĴ��룬ͨ������Ĵ����ִ�У�һ��platform�豸��framebuffer��������platform�豸���ͼ��ص��ں���ȥ�ˡ�����һ��PCI�����������뵽�ں�һ������ͬ����PCI������ռ�õ���PCI���ߣ��ں˻�ֱ��֧������������platform�豸��Ҫ����������ķ������ص��ںˣ�ͬPCI����һ�����豸��Ҫ�������򣬸ղ�ֻ�ǽ�platform�豸ע�ᵽ�ں��У�����������Ҫ�������򣬱����о���������Щ������
//4.1 static struct fb_ops s3c2410fb_ops
//       ����s3c2410��framebuffer����֧�ֵĲ�����Ҫ��s3c2410fb_ops�����ж��壬�ñ�������Ϊstruct fb_ops�������͵Ķ�����include/linux/fb.h�ļ��С�������ؽ��Ϳ�����http://www.91linux.com/html/article/kernel/20071204/8805.htmlҳ�����ҵ�����Ȼ��fb.h��Ҳ�к���ϸ��˵�������濴������s3c2410������Ϊ��framebuffer�ṩ����Щ������
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
//       ����Ĵ���������֧�ֵ���ز�����������Ҫ�����s3c2410****�ĺ�������.fb_fillrect��ʼ���������������ᱻ�ἰ����ȻҲ����ȥ�������ǵ���Ϊ��ʲô�����ﻹ��һ������Ҫ˵��һ�£�����s3c2410fb_ops����ʲôʱ��ע��ģ��������Ĵ𰸿����� s3c2410fb_probe�������ҵ�����鿴s3c2410fb_probe��������һС�ڡ�
// 
//4.2.1 s3c2410fb_check_var
//       �������С�����ᵽ����һ��LCD����˵�ں��ṩ���������ݽṹ����������һ���ǿɱ����ԣ�fb_var_screeninfo����������һ���ǲ������ԣ�fb_fix_screeninfo�����������ڿɱ����ԣ�Ӧ�÷�ֹ�ڲ����Ĺ����г��ֳ���������Χ�����������ں�Ӧ�ÿ��Ե�����غ�������⡢������Щ���Թ̶��ڷ����ķ�Χ�ڣ������������ĺ�������s3c2410_check_var��
//�����˵��һ�¸ú���Ҫ�������飬��������ÿ���fb_var_screeninfo��fb_info�Ķ��塣
// 
static int s3c2410fb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)

{
       struct s3c2410fb_info *fbi = info->par; //�õ�������˽��������Ϣ��ע��info-par��ֵ
����
// ������fb_var_screeninfo��xres��yres��ֵ�Ƿ񳬳�������Χ�������������趨Ϊ��ȷ��ֵ��
       if (var->yres > fbi->mach_info->yres.max)

              var->yres = fbi->mach_info->yres.max;

       else if (var->yres < fbi->mach_info->yres.min)

              var->yres = fbi->mach_info->yres.min;

 
       if (var->xres > fbi->mach_info->xres.max)

              var->yres = fbi->mach_info->xres.max;

       else if (var->xres < fbi->mach_info->xres.min)

              var->xres = fbi->mach_info->xres.min;

����
 
// ��Ľ��ʼ���bpp����ʾ�ö���λ��ʾһ�����أ���������Ϸ�������������ȷ
       if (var->bits_per_pixel > fbi->mach_info->bpp.max)

              var->bits_per_pixel = fbi->mach_info->bpp.max;

       else if (var->bits_per_pixel < fbi->mach_info->bpp.min)

              var->bits_per_pixel = fbi->mach_info->bpp.min;

 
       // ����Ĵ������bpp������ȷ����ɫ��Ϣ�������� 

����
       }
       return 0;
}
 
//4.2.2 s3c2410fb_set_par
//       �ú�������Ҫ��������������������˽��������Ϣ����Ҫ�ı��������bpp���еĳ��ȣ����ֽ�Ϊ��λ������Щ����ֵ��ʵ�Ǵ���� fb_fix_screeninfo�ṹ�еģ�ǰ��˵����Щֵ�����л����ǲ���ı�ģ���Щ���ɸı��ֵ�ֿɷ�Ϊ���Բ��ܸı������ı���������ͣ�ǰһ�ֵ����Ӿ���֡����������ʼ��ַ����һ�ֵ����Ӿ�����s3c2410fb_set_par�������ᵽ�����ԡ�����Ӧ�ó�����Ҫ�޸�Ӳ������ʾ״̬֮��Ĳ���������������Ե�ʮ����Ҫ��
// 
static int s3c2410fb_set_par(struct fb_info *info)
{
       struct s3c2410fb_info *fbi = info->par;              //�õ�˽��������Ϣ
       struct fb_var_screeninfo *var = &info->var;    //�ɱ����������

 
       switch (var->bits_per_pixel)     //����bpp���ò���������Ϣ����ɫģʽ
       {
              case 16:
                     fbi->fb->fix.visual = FB_VISUAL_TRUECOLOR;  //���ɫ

                     break;
              case 1:
                      fbi->fb->fix.visual = FB_VISUAL_MONO01;   // ��ɫ
                      break;
              default:
                      fbi->fb->fix.visual = FB_VISUAL_PSEUDOCOLOR;  //α��ɫ
                      break;
       }
 
       fbi->fb->fix.line_length     = (var->width*var->bits_per_pixel)/8; //�޸��г�����Ϣ�����ֽ�Ϊ��λ�������㷽����һ���е�(�������� * ���ÿ�����ص�λ��)/8��

����
              s3c2410fb_activate_var(fbi, var);  //�ú���ʵ��������Ӳ���Ĵ����������ԡ�
       return 0;
}
//4.2.3 s3c2410fb_blank��s3c2410fb_setcolreg
//       ����s3c2410fb_blank����ʵ�ֵĹ��ܷǳ��򵥣�����Ҳ�н���ϸ��˵������˶�����˵����ʡ���ˡ�s3c2410fb_setcolreg�����Ĺ�����������ɫ�Ĵ���������Ҫ6���������ֱ����Ĵ�����ţ���ɫ����ɫ����ɫ��͸����fb_info�ṹ��
static int s3c2410fb_setcolreg(unsigned regno,
                            unsigned red, unsigned green, unsigned blue,

                            unsigned transp, struct fb_info *info)
{
       struct s3c2410fb_info *fbi = info->par;          //�õ�˽��������Ϣ
       unsigned int val;
����
       switch (fbi->fb->fix.visual) {
       case FB_VISUAL_TRUECOLOR:   //���ɫ��ʹ���˵�ɫ��
              // true-colour, use pseuo-palette 

              if (regno < 16) {
                     u32 *pal = fbi->fb->pseudo_palette;

 
                     val  = chan_to_field(red,   &fbi->fb->var.red);  //������ɫֵ������Ҫ������
                     val |= chan_to_field(green, &fbi->fb->var.green);

                     val |= chan_to_field(blue,  &fbi->fb->var.blue);

 
                     pal[regno] = val;
              }
              break;
 
       case FB_VISUAL_PSEUDOCOLOR:    //α��ɫ
              if (regno < 256) {
                     // ��ǰ����Ϊ RGB 5-6-5 ģʽ 

 
                     val  = ((red   >>  0) & 0xf800);

                     val |= ((green >>  5) & 0x07e0);

                     val |= ((blue  >> 11) & 0x001f);
 
                     writel(val, S3C2410_TFTPAL(regno));  //����ֱֵ��д��Ĵ���
                     schedule_palette_update(fbi, regno, val);   //��ؼĴ���

              }
              break;
       default:
              return 1;   // unknown type 
       }
       return 0;
}
 
// 
//��ĿǰΪֹ��������������Ҫ�����Ѿ���������ˡ�����ǵ���һ���жϴ�����s3c2410fb_irq���������ʵ��Ҳ�Ƚ϶̣�������Ҫ������s3c2410fb_write_palette���������Ĺ����ǽ���ɫ���е�������ʾ��LCD�ϡ�����������ʵ��Ҳ���ѣ�����Ͳ���׸����
//OK��good bye everyone��see you next time��

//                                         The End