// Linux MMC/SD/SDIO体系结构                                                                                                                                                                                                                                                                     
// [日期：2011-03-12] 来源：Linux社区  作者：yuanyou                                                                                                                                                                                                                                             
// 有关MMC/SD/SDIO相关的知识这里就不多讲了，请参考相关资料。这里主要涉及Linux下MMC相关内容。                                                                                                                                                                                                     
// 内核版本(2.6.36)                                                                                                                                                                                                                                                                              
// 首先说一下Linux相关MMC的代码分布，主要有两个目录，一个头文件目录和一个源代码目录。                                                                                                                                                                                                            
// 分别位置如下：                                                                                                                                                                                                                                                                                
// include/linux/mmc                                                                                                                                                                                                                                                                             
// drivers/mmc                                                                                                                                                                                                                                                                                   
// 要阅读MMC相关代码就必须要看这两个目录。在drivers/mmc目录下分别有三个子目录，其将对应接下来要讲的MMC的体系结构。这三个子目录分别为：                                                                                                                                                           
//                                                                                                                                                                                                                                                                                               
//  card                                                                                                                                                                                                                                                                                         
//  core                                                                                                                                                                                                                                                                                         
//  host                                                                                                                                                                                                                                                                                         
//                                                                                                                                                                                                                                                                                               
// 它们的内容后面讲到体系结构时自然就明了了。                                                                                                                                                                                                                                                    
//  现在来说说MMC的体系结构，其分为三层                                                                                                                                                                                                                                                          
//                                                                                                                                                                                                                                                                                               
//         /dev下设备文件访问MMC/SD/SDIO                                                                                                                                                                                                                                                         
// 用户空间             |                                                                                                                                                                                                                                                                        
// ---------------------|-----------------------------------------------------                                                                                                                                                                                                                   
// 内核空间            \ /                                                                                                                                                                                                                                                                       
//          MMC Card层(对应具体的设备驱动，如MMC/SD卡块设备驱动，SDIO UART)                                                                                                                                                                                                                      
//                      |                                                                                                                                                                                                                                                                        
//                     \ /                                                                                                                                                                                                                                                                       
//           MMC core层(为上次设备驱动实现提供操作接口，和下层host注册提供机制)                                                                                                                                                                                                                  
//                      |                                                                                                                                                                                                                                                                        
//                     \ /                                                                                                                                                                                                                                                                       
//            Host层(具体MMC/SD/SDIO控制器驱动层。如S3C2440 MMC/SD控制器驱动)                                                                                                                                                                                                                    
//                      |                                                                                                                                                                                                                                                                        
//                     \ /                                                                                                                                                                                                                                                                       
// -----------------------------------------------------------------------------                                                                                                                                                                                                                 
//                     硬件层                                                                                                                                                                                                                                                                    
//                                                                                                                                                                                                                                                                                               
// 对于我们来说，编写MMC/SD卡相关驱动主要涉及的就是Host层，其余层不用考虑。
// 对于SDIO设备除了Host层以外，还有可能要编写MMC Card层的设备驱动。 

// 编写Host层驱动，主要是填充mmc_host结构体相关内容和实现mmc_host_ops结构体中的函数。
// 最后调用mmc_add_host向MMC core注册host驱动。可以参考S3C24XX的HOST驱动程
// 序(drivers/mmc/host/s3cmci.c,s3cmci.h),上层MMC Core主要调用mmc_host_ops中的
// 函数来实现与硬件交互。如下是mmc_host_ops结构体里面的函数：
  struct mmc_host_ops {                                                                                                                                                                                                                                                                       
    //使能和禁止HOST控制器                                                                                                                                                                                                                                                                  
    int (*enable)(struct mmc_host *host);                                                                                                                                                                                                                                                     
    int (*disable)(struct mmc_host *host, int lazy);                                                                                                                                                                                                                                          
        //这个是关键的函数，所有对MMC/SD的操作，包括发命令和读数据，都通过该接口来实现，
        //所以实现该接口时要处理是命令还是数据操作，另外要考虑是否使用DMA来进行数据传输。                                                                                                                     
    void    (*request)(struct mmc_host *host, struct mmc_request *req);                                                                                                                                                                                                                       
        //用来设置MMC/SD的时钟，电压等操作                                                                                                                                                                                                                                                  
    void    (*set_ios)(struct mmc_host *host, struct mmc_ios *ios);                                                                                                                                                                                                                           
        //检查MMC/SD是否写保护了                                                                                                                                                                                                                                                            
    int    (*get_ro)(struct mmc_host *host);                                                                                                                                                                                                                                                  
        //检查mmc/sd的插入和拔出                                                                                                                                                                                                                                                            
    int    (*get_cd)(struct mmc_host *host);                                                                                                                                                                                                                                                  
    void    (*enable_sdio_irq)(struct mmc_host *host, int enable);                                                                                                                                                                                                                            
    // optional callback for HC quirks                                                                                                                                                                                                                                                      
    void    (*init_card)(struct mmc_host *host, struct mmc_card *card);                                                                                                                                                                                                                       
};                                                                                                                                                                                                                                                                                            
//===============================================================================
// 接下来说说MMC Core层。
// 该层主要实现了几个结构体函数指针，用来构建整个MMC设备驱动模型。它们是：
struct bus_type mmc_bus_type  //mmc总线，用来管理sd/mmc卡设备和驱动 
struct mmc_bus_ops mmc_ops    //MMC卡总线操作函数，主要是在电源管理方面

struct mmc_bus_ops mmc_sd_ops  //SD卡总线操作函数，主要是在电源管理方面

struct mmc_bus_ops mmc_sdio_ops  //SDIO总线操作函数，主要是在电源管理方面
struct bus_type sdio_bus_type  //SDIO另外定义了一条总线

// core.c文件中实现了几个关键的函数，用来提供给上层MMC Card调用和对SD/MMC卡的侦测函数以及初始化。
// 供给上层MMC Card调用主要有：
void mmc_wait_for_req(struct mmc_host *host, struct mmc_request *mrq);
 int mmc_wait_for_cmd(struct mmc_host *host, struct mmc_command *cmd, int retries);
// mmc card层就是通过这些函数来操作mmc/sd卡。而这些函数最终调用的是mmc_host_ops 结构体中的request函数来
//进行具体的操作。
// 
// 对SD/MMC卡的侦测函数以及初始化，主要实现在
void mmc_rescan(struct work_struct *work);// 函数中。
// host层在调用mmc_add_host时会引发该函数的调用，侦测/初始化顺序为：

// 先SDIO接口
  //
     * First we search for SDIO...
     
    err = mmc_send_io_op_cond(host, 0, &ocr);
    if (!err) {
        if (mmc_attach_sdio(host, ocr)) {
   ...

//在SD:
//  //
     * ...then normal SD...
     
    err = mmc_send_app_op_cond(host, 0, &ocr);
    if (!err) {
        if (mmc_attach_sd(host, ocr))

//最后是MMC：
 //
     * ...and finally MMC.
     
    err = mmc_send_op_cond(host, 0, &ocr);
    if (!err) {
        if (mmc_attach_mmc(host, ocr))
//
//其中mmc_attach_xxx函数就是用来完成侦测和初始化的，选择相应的总线操作函数，并产生struct mmc_card结构体，
//并填充其内容，最后注册一个mmc_card(代表着一个设备)，并在注册中由mmc_bus_type结构体的match和probe函数
//来查找到适合该设备的驱动(这个又牵涉到设备驱动模型，可以查看设备驱动模型相关内容，了解设备和驱动匹配的
//过程)，这里将匹配到mmc card层的MMC_Block(MMC块设备驱动程序，由 struct mmc_driver代表)。在完成设备侦测
//和初始化以后，以后的操作就是mmc card层中相关的设备驱动程序发出的了。
//===============================================================================
//再说说MMC card层，该层主要实现具体的设备驱动程序，如MMC块设备驱动程序，通过mmc_register_driver注册。
//如果是SDIO就有可能是其它字符设备驱动程序了，其通过调用sdio_register_driver来注册设备驱动。
//
//总体概括来说：
//host层提供驱动相关MMC/SD/SDIO控制器的功能。
//Core层提供了具体MMC/SD/SDIO设备侦测和初始化功能，以及电源管理方面的内容和通用的操作功能。
//Card为实现具体的设备驱动层。
//这样的分层结构在Linux设备驱动中非常常见，如I2C,SPI等都提供了这样的驱动模型。
//
//===============================================================================
//最后简单说说SDIO相关部分。在core层注册了新的sdio_bus_type总线，并且定义了新的sdio_driver来代表sdio设备
//驱动，并定义了struct sdio_func来代表设备。所以在SDIO设备除了struct mmc_card来代表设备以外，
//还有struct sdio_func来代表具体功能设备。所以在mmc_attach_sdio函数中除了注册mmc_card以外，还注册
//了sdio_func。具体代码如下：
int mmc_attach_sdio(struct mmc_host *host, u32 ocr);
{
   ....
  //
     * First add the card to the driver model...
     
    err = mmc_add_card(host->card);
    if (err)
        goto remove_added;

    //
     * ...then the SDIO functions.
     
    for (i = 0;i < funcs;i++) {
        err = sdio_add_func(host->card->sdio_func[i]);
        if (err)
            goto remove_added;
    }
    ....
}
//所以它除了调用mmc_bus_type结构体的match和probe函数来查找到适合该设备的驱动外，也调用sdio_bus_type结构体
//的match和probe函数来查找到适合该设备的驱动。


// =================================================================================================
// SD/MMC/SDIO 概念区分概要 (2010-01-13 13:58)                                                                                                                                                                                                   
// 分类： Linux驱动                                                                                                                                                                                                                              
// SD（Secure Digital）与 MMC（Multimedia Card）                                                                                                                                                                                                 
//                                                                                                                                                                                                                                               
// SD 是一种 flash memory card 的标准，也就是一般常见的 SD 记忆卡，而 MMC 则是较早的一种记忆卡标准，目前已经被 SD 标准所取代。在维基百科上有相当详细的 SD/MMC 规格说明：[http://zh.wikipedia.org/wiki/Secure_Digital]。                          
//                                                                                                                                                                                                                                               
// SDIO（Secure Digital I/O）                                                                                                                                                                                                                    
//                                                                                                                                                                                                                                               
// SDIO 是目前我们比较关心的技术，SDIO 故名思义，就是 SD 的 I/O 接口（interface）的意思，不过这样解释可能还有点抽像。更具体的说明，SD 本来是记忆卡的标准，但是现在也可以把 SD 拿来插上一些外围接口使用，这样的技术便是 SDIO。                    
//                                                                                                                                                                                                                                               
// 所以 SDIO 本身是一种相当单纯的技术，透过 SD 的 I/O 接脚来连接外部外围，并且透过 SD 上的 I/O 数据接位与这些外围传输数据，而且 SD 协会会员也推出很完整的 SDIO stack 驱动程序，使得 SDIO 外围（我们称为 SDIO 卡）的开发与应用变得相当热门。      
//                                                                                                                                                                                                                                               
// 现在已经有非常多的手机或是手持装置都支持 SDIO 的功能（SD 标准原本就是针对 mobile device 而制定），而且许多 SDIO 外围也都被开发出来，让手机外接外围更加容易，并且开发上更有弹性（不需要内建外围）。目前常见的 SDIO 外围（SDIO 卡）有：         
//                                                                                                                                                                                                                                               
// Wi-Fi card（无线网络卡）                                                                                                                                                                                                                      
// CMOS sensor card（照相模块）                                                                                                                                                                                                                  
// GPS card                                                                                                                                                                                                                                      
// GSM/GPRS modem card                                                                                                                                                                                                                           
// Bluetooth card                                                                                                                                                                                                                                
// Radio/TV card（很好玩）                                                                                                                                                                                                                       
// SDIO 的应用将是未来嵌入式系统最重要的接口技术之一，并且也会取代目前 GPIO 式的 SPI 接口。                                                                                                                                                      
//                                                                                                                                                                                                                                               
// SD/SDIO 的传输模式                                                                                                                                                                                                                            
//                                                                                                                                                                                                                                               
// SD 传输模式有以下 3 种：                                                                                                                                                                                                                      
//                                                                                                                                                                                                                                               
// SPI mode（required）                                                                                                                                                                                                                          
// 1-bit mode                                                                                                                                                                                                                                    
// 4-bit mode                                                                                                                                                                                                                                    
// SDIO 同样也支持以上 3 种传输模式。依据 SD 标准，所有的 SD（记忆卡）与 SDIO（外围）都必须支持 SPI mode，因此 SPI mode 是「required」。此外，早期的 MMC 卡（使用 SPI 传输）也能接到 SD 插糟（SD slot），并且使用 SPI mode 或 1-bit mode 来读取。
//                                                                                                                                                                                                                                               
// SD 的 MMC Mode                                                                                                                                                                                                                                
//                                                                                                                                                                                                                                               
// SD 也能读取 MMC 内存，虽然 MMC 标准上提到，MMC 内存不见得要支持 SPI mode（但是一定要支持 1-bit mode），但是市面上能看到的 MMC 卡其实都有支持 SPI mode。因此，我们可以把 SD 设定成 SPI mode 的传输方式来读取 MMC 记忆卡。                      
//                                                                                                                                                                                                                                               
// SD 的 MMC Mode 就是用来读取 MMC 卡的一种传输模式。不过，SD 的 MMC Mode 虽然也是使用 SPI mode，但其物理特性仍是有差异的：                                                                                                                      
//                                                                                                                                                                                                                                               
// MMC 的 SPI mode 最大传输速率为 20 Mbit/s；                                                                                                                                                                                                    
// SD 的 SPI mode 最大传输速率为 25 Mbit/s。                                                                                                                                                                                                     
// 为避免混淆，有时也用 SPI/MMC mode 与 SPI/SD mode 的写法来做清楚区别。                                                                                                                                                                         
//                                                                                                                                                                                                                                               
