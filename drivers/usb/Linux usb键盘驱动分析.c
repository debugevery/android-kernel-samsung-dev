// Linux usb键盘驱动分析 (2011-10-19 21:42) 
// 标签:  分析  键盘  Linux  class  分类： 设备驱动-USB 
// 
// 
// 
// 1. 指定USB键盘驱动所需的头文件: 

　　//#include <linux/kernel.h>//内核头文件，含有内核一些常用函数的原型定义// 

　　//#include <linux/slab.h>//定义内存分配的一些函数// 

　　//#include <linux/module.h>//模块编译必须的头文件// 

　　//#include <linux/input.h>//输入设备相关函数的头文件// 

　　//#include <linux/init.h>//linux初始化模块函数定义// 

　　//#include <linux/usb.h> //USB设备相关函数定义// 
//
//　　2. 定义键盘码表数组： 
//
//　　//使用第一套键盘扫描码表:A-1E;B-30;C-2E…// 
//
　　static unsigned char usb_kbd_keycode[256] = { 

　　0, 0, 0, 0, 30, 48, 46, 32, 18, 33, 34, 35, 23, 36, 37, 38, 

　　50, 49, 24, 25, 16, 19, 31, 20, 22, 47, 17, 45, 21, 44, 2, 3, 

　　4, 5, 6, 7, 8, 9, 10, 11, 28, 1, 14, 15, 57, 12, 13, 26, 

　　27, 43, 43, 39, 40, 41, 51, 52, 53, 58, 59, 60, 61, 62, 63, 64, 

　　65, 66, 67, 68, 87, 88, 99, 70,119,110,102,104,111,107,109,106, 

　　105,108,103, 69, 98, 55, 74, 78, 96, 79, 80, 81, 75, 76, 77, 71, 

　　72, 73, 82, 83, 86,127,116,117,183,184,185,186,187,188,189,190, 

　　191,192,193,194,134,138,130,132,128,129,131,137,133,135,136,113, 

　　115,114, 0, 0, 0,121, 0, 89, 93,124, 92, 94, 95, 0, 0, 0, 

　　122,123, 90, 91, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 

　　0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 

　　0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 

　　0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 

　　0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 

　　29, 42, 56,125, 97, 54,100,126,164,166,165,163,161,115,114,113, 

　　150,158,159,128,136,177,178,176,142,152,173,140 

　　}; 

//　　3. 编写设备ID表：
 static struct usb_device_id usb_kbd_id_table [] = { 
//
　　{ USB_INTERFACE_INFO(3, 1, 1) },//3,1,1分别表示接口类,接口子类,接口协议;3,1,1为键盘接口类;鼠标为3,1,2// 

　　{ } // Terminating entry // 

　　};//必须与0结束 

　　MODULE_DEVICE_TABLE (usb, usb_kbd_id_table);//指定设备ID表// 

//　　4. 定义USB键盘结构体： 
//
　　struct usb_kbd { 

　　struct input_dev *dev; //定义一个输入设备// 

　　struct usb_device *usbdev;//定义一个usb设备// 

　　unsigned char old[8]; //按键离开时所用之数据缓冲区// 

　　struct urb *irq//usb键盘之中断请求块//, *led//usb键盘之指示灯请求块//; 

　　unsigned char newleds;//目标指定灯状态// 

　　char name[128];//存放厂商名字及产品名字// 

　　char phys[64];//设备之节点// 

　　unsigned char *new;// 

//　　按键按下时所用之数据缓冲区// 
//
　　struct usb_ctrlrequest *cr;//控制请求结构// 

　　unsigned char *leds;//当前指示灯状态// 

　　dma_addr_t cr_dma; //控制请求DMA缓冲地址// 

　　dma_addr_t new_dma; //中断urb会使用该DMA缓冲区// 

　　dma_addr_t leds_dma; //指示灯DAM缓冲地址// 

　　}; 

//　　5. 编写USB键盘驱动结构(任何一个LINUX下的驱动都有个类似的驱动结构)： 
//
//　　//USB键盘驱动结构体// 

　　static struct usb_driver usb_kbd_driver = { 

　　.name = "usbkbd",//驱动名字// 

　　.probe = usb_kbd_probe,//驱动探测函数,加载时用到// 

　　.disconnect = usb_kbd_disconnect,//驱动断开函数,在卸载时用到，可选// 

　　.id_table = usb_kbd_id_table,//驱动设备ID表,用来指定设备或接口// 

　　}; 

//　　6. 编写模块加载函数(每个驱动都会有一个加载函数，由module_init调用)： 
//
//　　//驱动程序生命周期的开始点，向 USB core 注册这个键盘驱动程序。// 

　　static int __init usb_kbd_init(void) 

　　{ 

　　int result = usb_register(&usb_kbd_driver);//注册USB键盘驱动// 

　　if (result == 0) //注册失败// 

　　info(DRIVER_VERSION ":" DRIVER_DESC); 

　　return result; 

　　} 

//　　7. 编写模块卸载函数(每个驱动都会有一个卸载函数，由module_exit调用)： 
//
//　　// 驱动程序生命周期的结束点，向 USB core 注销这个键盘驱动程序。 // 

　　static void __exit usb_kbd_exit(void) 

　　{ 

　　printk("SUNWILL-USBKBD:usb_kbd_exit begin...\n"); 

　　usb_deregister(&usb_kbd_driver);//注销USB键盘驱动// 

　　} 

// 8 指定模块初始化函数(被指定的函数在insmod驱动时调用)： 

　　//module_init(usb_kbd_init); 

//　　9. 指定模块退出函数(被指定的函数在rmmod驱动时调用)： 
//
　　//module_exit(usb_kbd_exit); 

//　　10. 编写中断请求处理函数： 
//
//　　在介绍中断处理程序之前我们先来看看usb请求结结构体urb是什么样子的 

　　struct urb 

　　{ 

　　spinlock_t lock; // lock for URB,自旋锁，用于并发访问临界资源 

　　void *hcpriv;// private data for host controler与主机控制器相关数据,对USB内核层是透明的 

　　struct list_head urb_list;//list pointer to all active urbs 双向指针,用于将此USB联结到处于活动的URB双向链表中，在内核结构模型中很多地方都有到这个结构体，这个结构体有两个指针，一个指向下一个 list_head结构体，一个指向前一个list_head结构体，在进程列表，工作队列中都用到这个结构体。 

　　struct urb *next;// pointer to associated USB device 接受此ＵＲＢ的USB设备指针； 

　　unsigned int pipe;//pipe information 表示设备的某个端点和客户设备驱动程序之间的通道 

　　int status;// return status 返回状态 

　　unsigned int transfer_flags;//USB_DISABLE_SPD 拒绝短数据包，即比最大传输包长度小的数据包 

//　　这个变量可以被设置为许多不同的位值，取决与usb驱动程序对urb的具体操作，可以用的值包括 
//
//　　　　URB_SHORT_NOT_OK 该值说明任何可能发生的对于IN端点的间断的读取应该被usb核心当作是一个错误处理，该值只对用usb设备 
//
//　　读取的urb起作用。，对于写入urb没有意义 
//
//　　URB_ISO_ASAP 如果urb是等时的，当驱动程序想要该urb被调度时可以设置这个位，只要带宽允许它这么做，而且想要在此时设置urb 
//
//　　中的start_frame变量，如果一个等时的urb没有设置该位驱动程序必须制定start_frame的值，如果在传输的当时不能启动的话必须能够 
//
//　　正确的恢复。 
//
//　　URB_NO_TRANSFER_DMA_MAP 顾名思意这个时设置DMA缓冲区的，当urb使用DMA缓冲区的时候设置该位。usb核心使用 
//
//　　transfer_dma的变量所指向的缓冲区 
//
//　　　　URB_NO_SETUP_DMA_MAP 和URB_NO_TRANDFER_DMA_MAP位类似，该位用于控制带有已经设置好的DMA缓冲区的urb，如果它被设置了，USB 
//
//　　核心使用setup_dma变量所指向的缓冲区，而不是setup_packet变量 
//
//　　URB_ASYNC_UNLINK 如果该位被设置，对urb的usb_unlink_urb的调用几乎是立即返回，该urb的链接在后台被解开，否则此函数一直等 
//
//　　待urb被完全解开链接和结束才返回，使用该位时要小心，因为它可能会造成伴以调试的同步问题 
//
//　　　　URB_NO_FSBR 仅由UHCI USB主控制器驱动程序使用，指示它不要企图使用前端的总线回收逻辑。该位通常不应该被设置，因为带有 
//
//　　UBCI主控制器的及其会导致大量的CPU负荷，而PCI总线忙于等待一个设置了该位的URB 
//
//　　URB_ZERO_PACKET 如果该位被设置，一个批量输出urb以发送一个不包含的小数据包来结束，这是数据对齐到一个端点数据包边 
//
//　　界，一些断线的USB涉黑需要该位才能正确的工作。 
//
//　　URB_NO_INTERRUPT 如果该位被设置，当urb结束的时候，硬件肯那个不会产生一个中断，对该位的使用应当小心谨慎，只有把多个 
//
//　　urb排队到同一个端点时才使用。usb核心的函数使用该位来进行DMA缓冲区的传输。 
//
　　void *transfer_buffer;// associated data buffer 传输数据缓冲区，接收或发送设备的数据，它必须是物理连续的，不可换页的内存块，用kmalloc(,GFP_KERNEL)分配内核内存空间 

　　int transfer_buffer_length;//data buffer length transfer_buffer或者transfer_dma变量所指向的缓冲区长度，在任何时候一个urb只能用一个 

　　int actual_length;// actual data buffer length 当urb结束后，该变量被设置为urb所大宋的数据或者urb接收的实际数据长度 

　　int bandwidth;//bandwidth for this transfer request(INT or ISO),此请求每次占用一帧的带宽，只适合于用实时／中断传输 

　　unsigned char *setup_packet;//setup packet(control only)用于指向传输中控制命令的指针．只适用控制传输． 

　　int start_frame;// start frame(iso/irq only),此请求开始传输的帧号．中断传输的时候，表示返回启动此请求的第一次中断传输的帧号．实时传输的时候，指明处理第一个实时请求数据包的帧号，如果设置了USB_ISO_ASAP,此变量表示返回启动第一次实时传输的帧号 

　　int number_of_packets;//number of packets in this request (iso)此请求包含的数据包数，只适合实时传输，在urb被发送到usb核心之前必须被USB驱动程序设置 

　　int interval;// polling interval(irq only)urb被轮询的时间间隔，仅对中断或者等时传输有效，在urb被发送到usb核心之前必须由usb驱动程序设置； 

　　int error_count;//number of errors in this transfer(iso only)由usb核心设置，仅用于等时urb结束后，他表示报告了任何一种类型的错误的等时传输的数量。 

　　int timeout; 

　　void *context;// context for completion routine指向一个可以被usb驱动程序设置的数据块，它可以在结束处理程序历程中当urb被返回到驱动程序的时候使用。 

　　usb_complete_t complete;//pointer to completion routine,指向回调函数的指针，当数据完成的时候或者出现出错的时候usb核心调用此函 

//　　数，在该函数内，usb驱动程序可以检查urb，释放它，或者把它重新提交到两个一个传输中去 
//
　　usb_complete_t 定义如下 

　　typedef voud (*usb_complete_t)(struct urb * , struct pt_regs *); 

　　iso_packet_descriptor_t iso_frame_desc[0];//要进行实时传输的数据结构，每个结构表示一次数据传输 

　　int status 

//　　　　当urb结束之后，或者正在被usb核心处理时，该变量被设置为urb的当前状态，usb驱动程序可以安全第访问该变量的唯一适合就是在urb结束处理的历程中。该限制是为了防止当urb正在被usb核心处理时的竞态的发生。对于等是urb，该变量的一个成功之0表示urb室友已经被解开链接，如果在获取等时urb的详细状态。应该检查iso_frame_desc变量，该变量的有效值包含值： 
//
//　　　　0 urb传输成功 
//
//　　　　-ENOENT urb被usb_kill_urb调用终止 
//
//　　-ECONNRESET urb被usb_unlink_urn调用解开连接，urb的transfer_flags变量被设置为URB_ASYNC_URBLINK; 
//
//　　　　-EINPROGRESS urb仍然咋被usb主控制器处理，如果驱动程序中检查到该值，说明存在代码缺陷 
//
//　　-EPROTO urb发生了以下错误 
//
//　　在传输中发生了bitstuff错误 
//
//　　　　　　硬件没有及时接收到响应数据包 
//
//　　　　-EILSEQ urb在传输发生了CRC校验不匹配 
//
//　　-EPIPE 端点被中止，如果涉及的端点不是控制端点，可以调用usb_clear_halt函数来清楚该错误 
//
//　　-ECOMM 传输时数据的接收速度比它写到系统内存的速度快，该错误值仅发生在IN urb上 
//
//　　-ENOSR 传输时从系统内存获取的数据速度不够快，跟不上所要求的USB数据速率，该错误仅发生在OUT utb上 
//
//　　-EOVERFLOW urb发生“串扰(babble)”错误。“串扰”错误发生在端点接收了超过端点指定的数据包尺寸的数据时 
//
//　　-EREMOTEIO 仅发生在urb的transfer_flags变量设置为URB_SHORT_NOT_OK标识时。表示urb没有接收到所要求的全部数据量 
//
//　　-ENODEV USB设备已经从系统移出 
//
//　　-EXDEV 仅发生在等时urb上，表示传输仅部分完成，为了确定所传输的内容，驱动程序必须单看单个帧的状态 
//
//　　-EINVAL urb发生了很糟糕的事情，URB内核文档描述的该值，如果发生这种情况，那就退出系统，然后回家去 
//
//　　-ESHUTDOWN usb主控制器驱动程序发生了严重的错误，设备已经被禁止，或者已经从系统脱离，而urb在设备被移出之后提交，如果当urb被提交到设备的配置被改变，也可能发生这个错误。 
//
//　　一般来说，错误值-EPROTO ,-EILSSEQ 和 -EOVERFLOW表示设备，设备的固件或者吧设备连接到了计算机的电缆发生了硬件故障。 
//
//　　//中断请求处理函数，有中断请求到达时调用该函数// 
//
　　static void usb_kbd_irq(struct urb *urb, struct pt_regs *regs) 

　　{ 

　　struct usb_kbd *kbd = urb->context; 

　　int i; 

　　switch (urb->status) { 

　　case 0: // success // 

　　break; 

　　case -ECONNRESET: // unlink // 

　　case -ENOENT: 

　　case -ESHUTDOWN: 

　　return; 

　　// -EPIPE: should clear the halt // 

　　default: // error // 

　　goto resubmit; 

　　} 

　　//input_regs(kbd->dev, regs); 

　　// 

//不知道其用意, 注释掉该部分仍可正常工作// 

　　for (i = 0; i < 8; i++)//8次的值依次是:29-42-56-125-97-54-100-126// 

　　{ 

　　input_report_key(kbd->dev, usb_kbd_keycode[i + 224], (kbd->new[0] >> i) & 1); 

　　} 

////若同时只按下1个按键则在第[2]个字节,若同时有两个按键则第二个在第[3]字节，类推最多可有6个按键同时按下// 

　　for (i = 2; i < 8; i++) { 

////获取键盘离开的中断// 

　　if (kbd->old > 3 && memscan(kbd->new + 2, kbd->old, 6) == kbd->new + 8) {//同时没有该KEY的按下状态// 

　　if (usb_kbd_keycode[kbd->old]) 

　　{ 

　　input_report_key(kbd->dev, usb_kbd_keycode[kbd->old], 0); 

　　} 

　　else 

　　info("Unknown key (scancode %#x) released.", kbd->old); 

　　} 

　　// 

//获取键盘按下的中断// 

　　if (kbd->new > 3 && memscan(kbd->old + 2, kbd->new, 6) == kbd->old + 8) {//同时没有该KEY的离开状态// 

　　if (usb_kbd_keycode[kbd->new]) 

　　{ 

　　input_report_key(kbd->dev, usb_kbd_keycode[kbd->new], 1); 

　　} 

　　else 

　　info("Unknown key (scancode %#x) pressed.", kbd->new); 

　　} 

　　} 

//　　//同步设备,告知事件的接收者驱动已经发出了一个完整的报告// 
//
　　input_sync(kbd->dev); 

　　memcpy(kbd->old, kbd->new, 8);//防止未松开时被当成新的按键处理// 

　　resubmit: 

　　i = usb_submit_urb (urb, GFP_ATOMIC);//发送USB请求块// 

　　if (i) 

　　err ("can't resubmit intr, %s-%s/input0, status %d", 

　　kbd->usbdev->bus->bus_name, 

　　kbd->usbdev->devpath, i); 

　　} 

//　　11. 编写事件处理函数： 
//
//　　//事件处理函数// 

　　static int usb_kbd_event(struct input_dev *dev, unsigned int type, 

　　unsigned int code, int value) 

　　{ 

　　struct usb_kbd *kbd = dev->private; 

　　if (type != EV_LED) //不支持LED事件 // 

　　return -1; 

//　　//获取指示灯的目标状态// 
//
　　kbd->newleds = (!!test_bit(LED_KANA, dev->led) << 3) | (!!test_bit(LED_COMPOSE, dev->led) << 3) | 

　　(!!test_bit(LED_SCROLLL, dev->led) << 2) | (!!test_bit(LED_CAPSL, dev->led) << 1) | 

　　(!!test_bit(LED_NUML, dev->led)); 

　　if (kbd->led->status == -EINPROGRESS) 

　　return 0; 

　　// 

//　　指示灯状态已经是目标状态则不需要再做任何操作// 
//
　　if (*(kbd->leds) == kbd->newleds) 

　　return 0; 

　　*(kbd->leds) = kbd->newleds; 

　　kbd->led->dev = kbd->usbdev; 

////发送usb请求块// 

　　if (usb_submit_urb(kbd->led, GFP_ATOMIC)) 

　　err("usb_submit_urb(leds) failed"); 

　　return 0; 

　　} 

//　　12. 编写LED事件处理函数： 
//
//　　//接在event之后操作，该功能其实usb_kbd_event中已经有了，该函数的作用可能是防止event的操作失败，一般注释掉该函数中的所有行都可以正常工作// 

　　static void usb_kbd_led(struct urb *urb, struct pt_regs *regs) 

　　{ 

　　struct usb_kbd *kbd = urb->context; 

　　if (urb->status) 

　　warn("led urb status %d received", urb->status); 

　　if (*(kbd->leds) == kbd->newleds)// 

//指示灯状态已经是目标状态则不需要再做任何操作// 

　　return; 

　　*(kbd->leds) = kbd->newleds; 

　　kbd->led->dev = kbd->usbdev; 

　　if (usb_submit_urb(kbd->led, GFP_ATOMIC)) 

　　err("usb_submit_urb(leds) failed"); 

　　} 

//　　13. 编写USB设备打开函数: 
//
//　　//打开键盘设备时，开始提交在 probe 函数中构建的 urb，进入 urb 周期。 // 
//
　　static int usb_kbd_open(struct input_dev *dev) 

　　{ 

　　struct usb_kbd *kbd = dev->private; 

　　kbd->irq->dev = kbd->usbdev; 

　　if (usb_submit_urb(kbd->irq, GFP_KERNEL)) 

　　return -EIO; 

　　return 0; 

　　} 

//　　14. 编写USB设备关闭函数 
//
//　　//关闭键盘设备时，结束 urb 生命周期。 // 

　　static void usb_kbd_close(struct input_dev *dev) 

　　{ 

　　struct usb_kbd *kbd = dev->private; 

　　usb_kill_urb(kbd->irq); //取消kbd->irq这个usb请求块// 

　　} 

//　　15. 创建URB 
//
//　　//分配URB内存空间即创建URB// 
//
　　static int usb_kbd_alloc_mem(struct usb_device *dev, struct usb_kbd *kbd) 

　　{ 

　　if (!(kbd->irq = usb_alloc_urb(0, GFP_KERNEL))) 

　　return -1; 

　　if (!(kbd->led = usb_alloc_urb(0, GFP_KERNEL))) 

　　return -1; 

　　if (!(kbd->new = usb_buffer_alloc(dev, 8, GFP_ATOMIC, &kbd->new_dma))) 

　　return -1; 

　　if (!(kbd->cr = usb_buffer_alloc(dev, sizeof(struct usb_ctrlrequest), GFP_ATOMIC, &kbd->cr_dma))) 

　　return -1; 

　　if (!(kbd->leds = usb_buffer_alloc(dev, 1, GFP_ATOMIC, &kbd->leds_dma))) 

　　return -1; 

　　return 0; 

　　} 

//　　16. 销毁URB 
//
//　　//释放URB内存空间即销毁URB// 
//
　　static void usb_kbd_free_mem(struct usb_device *dev, struct usb_kbd *kbd) 

　　{ 

　　if (kbd->irq) 

　　usb_free_urb(kbd->irq); 

　　if (kbd->led) 

　　usb_free_urb(kbd->led); 

　　if (kbd->new) 

　　usb_buffer_free(dev, 8, kbd->new, kbd->new_dma); 

　　if (kbd->cr) 

　　usb_buffer_free(dev, sizeof(struct usb_ctrlrequest), kbd->cr, kbd->cr_dma); 

　　if (kbd->leds) 

　　usb_buffer_free(dev, 1, kbd->leds, kbd->leds_dma); 

　　} 

//　　17. USB键盘驱动探测函数: 
//
//　　//USB键盘驱动探测函数，初始化设备并指定一些处理函数的地址// 
//
　　static int usb_kbd_probe(struct usb_interface *iface, 

　　const struct usb_device_id *id) 

　　{ 

　　struct usb_device *dev = interface_to_usbdev(iface); 

　　struct usb_host_interface *interface; 

　　struct usb_endpoint_descriptor *endpoint; 

　　struct usb_kbd *kbd; 

　　struct input_dev *input_dev; 

　　int i, pipe, maxp; 

////当前选择的interface// 

　　interface = iface->cur_altsetting; 

//　　//键盘只有一个中断IN端点// 
//
　　if (interface->desc.bNumEndpoints != 1) 

　　return -ENODEV; 

　　//获取端点描述符// 

　　endpoint = &interface->endpoint[0].desc; 

　　if (!(endpoint->bEndpointAddress & USB_DIR_IN)) 

　　return -ENODEV; 

　　if ((endpoint->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) != USB_ENDPOINT_XFER_INT) 

　　return -ENODEV; 

////将endpoint设置为中断IN端点// 

　　pipe = usb_rcvintpipe(dev, endpoint->bEndpointAddress); 

////获取包的最大值// 

　　maxp = usb_maxpacket(dev, pipe, usb_pipeout(pipe)); 

　　kbd = kzalloc(sizeof(struct usb_kbd), GFP_KERNEL); 

　　input_dev = input_allocate_device(); 

　　if (!kbd || !input_dev) 

　　goto fail1; 

　　if (usb_kbd_alloc_mem(dev, kbd)) 

　　goto fail2; 

//// 填充 usb 设备结构体和输入设备结构体 // 

　　kbd->usbdev = dev; 

　　kbd->dev = input_dev; 

　　// 

//以"厂商名字 产品名字"的格式将其写入kbd->name// 

　　if (dev->manufacturer) 

　　strlcpy(kbd->name, dev->manufacturer, sizeof(kbd->name)); 

　　if (dev->product) { 

　　if (dev->manufacturer) 

　　strlcat(kbd->name, " ", sizeof(kbd->name)); 

　　strlcat(kbd->name, dev->product, sizeof(kbd->name)); 

　　} 

　　// 

//检测不到厂商名字// 

　　if (!strlen(kbd->name)) 

　　snprintf(kbd->name, sizeof(kbd->name), 

　　"USB HIDBP Keyboard %04x:%04x", 

　　le16_to_cpu(dev->descriptor.idVendor), 

　　le16_to_cpu(dev->descriptor.idProduct)); 

////设备链接地址// 

　　usb_make_path(dev, kbd->phys, sizeof(kbd->phys)); 

　　strlcpy(kbd->phys, "/input0", sizeof(kbd->phys)); 

　　input_dev->name = kbd->name; 

　　input_dev->phys = kbd->phys; 

　　// 

//　　* input_dev 中的 input_id 结构体，用来存储厂商、设备类型和设备的编号，这个函数是将设备描述符 
//
//　　* 中的编号赋给内嵌的输入子系统结构体 

　　// 

　　usb_to_input_id(dev, &input_dev->id); 

　　// cdev 是设备所属类别（class device） // 

　　input_dev->cdev.dev = &iface->dev; 

//　　// input_dev 的 private 数据项用于表示当前输入设备的种类，这里将键盘结构体对象赋给它 // 
//
　　input_dev->private = kbd; 

　　input_dev->evbit[0] = BIT(EV_KEY)//键码事件// | BIT(EV_LED)//LED事件// | BIT(EV_REP)//自动重覆数值//; 

　　input_dev->ledbit[0] = BIT(LED_NUML)//数字灯// | BIT(LED_CAPSL)//大小写灯// | BIT(LED_SCROLLL)//滚动灯// | BIT(LED_COMPOSE) | BIT(LED_KANA); 

　　for (i = 0; i < 255; i++) 

　　set_bit(usb_kbd_keycode, input_dev->keybit); 

　　clear_bit(0, input_dev->keybit); 

　　input_dev->event = usb_kbd_event;// 

//　　注册事件处理函数入口// 
//
　　input_dev->open = usb_kbd_open;//注册设备打开函数入口// 

　　input_dev->close = usb_kbd_close;//注册设备关闭函数入口// 

　　// 

//初始化中断URB// 

　　usb_fill_int_urb(kbd->irq//初始化kbd->irq这个urb//, dev//这个urb要发送到dev这个设备//, pipe//这个urb要发送到pipe这个端点//, 

　　kbd->new//指向缓冲的指针//, (maxp > 8 ? 8 : maxp)//缓冲长度//, 

　　usb_kbd_irq//这个urb完成时调用的处理函数//, kbd//指向数据块的指针，被添加到这个urb结构可被完成处理函数获取//, endpoint->bInterval//urb应当被调度的间隔//); 

　　kbd->irq->transfer_dma = kbd->new_dma; //指定urb需要传输的DMA缓冲区// 

　　kbd->irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;//本urb有一个DMA缓冲区需要传输// 

　　kbd->cr->bRequestType = USB_TYPE_CLASS | USB_RECIP_INTERFACE;//操作的是类接口对象// 

　　kbd->cr->bRequest = 0x09; //中断请求编号// 

　　kbd->cr->wValue = cpu_to_le16(0x200); 

　　kbd->cr->wIndex = cpu_to_le16(interface->desc.bInterfaceNumber);//接口号// 

　　kbd->cr->wLength = cpu_to_le16(1);//数据传输阶段传输多少个bytes// 

　　// 

//初始化控制URB// 

　　usb_fill_control_urb(kbd->led, dev, usb_sndctrlpipe(dev, 0), 

　　(void *) kbd->cr, kbd->leds, 1, 

　　usb_kbd_led, kbd); 

　　kbd->led->setup_dma = kbd->cr_dma; 

　　kbd->led->transfer_dma = kbd->leds_dma; 

　　kbd->led->transfer_flags |= (URB_NO_TRANSFER_DMA_MAP | URB_NO_SETUP_DMA_MAP//如果使用DMA传输则urb中setup_dma指针所指向的缓冲区是DMA缓冲区而不是 setup_packet所指向的缓冲区//); 

　　// 

//　　注册输入设备// 
//
　　input_register_device(kbd->dev); 

　　usb_set_intfdata(iface, kbd);//设置接口私有数据// 

　　return 0; 

　　fail2: usb_kbd_free_mem(dev, kbd); 

　　fail1: input_free_device(input_dev); 

　　kfree(kbd); 

　　return -ENOMEM; 

　　} 

//　　18. 编写断开连接的函数: 
//
//　　//断开连接(如键盘设备拔出)的处理函数// 

　　static void usb_kbd_disconnect(struct usb_interface *intf) 

　　{ 

　　struct usb_kbd *kbd = usb_get_intfdata (intf);//获取接口的私有数据给kbd// 

　　usb_set_intfdata(intf, NULL);//设置接口的私有数据为NULL// 

　　if (kbd) { 

　　usb_kill_urb(kbd->irq);//取消中断请求// 

　　input_unregister_device(kbd->dev);//注销设备// 

　　usb_kbd_free_mem(interface_to_usbdev(intf), kbd);//释放内存空间// 

　　kfree(kbd); 

　　} 

　　} 

//　　19. 编写Makefile: 
//
//　　############################## 
//
//　　#usbkdb Makefile for linux 
//
//　　############################## 
//
//　　obj-m:=usbkbd.o 
//
//　　KERNELDIR ?= /lib/modules/$(shell uname -r)/build 
//
//　　PWD:=$(shell pwd) 
//
//　　default: 
//
//　　$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
