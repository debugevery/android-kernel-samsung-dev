// Linux usb������������ (2011-10-19 21:42) 
// ��ǩ:  ����  ����  Linux  class  ���ࣺ �豸����-USB 
// 
// 
// 
// 1. ָ��USB�������������ͷ�ļ�: 

����//#include <linux/kernel.h>//�ں�ͷ�ļ��������ں�һЩ���ú�����ԭ�Ͷ���// 

����//#include <linux/slab.h>//�����ڴ�����һЩ����// 

����//#include <linux/module.h>//ģ���������ͷ�ļ�// 

����//#include <linux/input.h>//�����豸��غ�����ͷ�ļ�// 

����//#include <linux/init.h>//linux��ʼ��ģ�麯������// 

����//#include <linux/usb.h> //USB�豸��غ�������// 
//
//����2. �������������飺 
//
//����//ʹ�õ�һ�׼���ɨ�����:A-1E;B-30;C-2E��// 
//
����static unsigned char usb_kbd_keycode[256] = { 

����0, 0, 0, 0, 30, 48, 46, 32, 18, 33, 34, 35, 23, 36, 37, 38, 

����50, 49, 24, 25, 16, 19, 31, 20, 22, 47, 17, 45, 21, 44, 2, 3, 

����4, 5, 6, 7, 8, 9, 10, 11, 28, 1, 14, 15, 57, 12, 13, 26, 

����27, 43, 43, 39, 40, 41, 51, 52, 53, 58, 59, 60, 61, 62, 63, 64, 

����65, 66, 67, 68, 87, 88, 99, 70,119,110,102,104,111,107,109,106, 

����105,108,103, 69, 98, 55, 74, 78, 96, 79, 80, 81, 75, 76, 77, 71, 

����72, 73, 82, 83, 86,127,116,117,183,184,185,186,187,188,189,190, 

����191,192,193,194,134,138,130,132,128,129,131,137,133,135,136,113, 

����115,114, 0, 0, 0,121, 0, 89, 93,124, 92, 94, 95, 0, 0, 0, 

����122,123, 90, 91, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 

����0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 

����0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 

����0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 

����0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 

����29, 42, 56,125, 97, 54,100,126,164,166,165,163,161,115,114,113, 

����150,158,159,128,136,177,178,176,142,152,173,140 

����}; 

//����3. ��д�豸ID��
 static struct usb_device_id usb_kbd_id_table [] = { 
//
����{ USB_INTERFACE_INFO(3, 1, 1) },//3,1,1�ֱ��ʾ�ӿ���,�ӿ�����,�ӿ�Э��;3,1,1Ϊ���̽ӿ���;���Ϊ3,1,2// 

����{ } // Terminating entry // 

����};//������0���� 

����MODULE_DEVICE_TABLE (usb, usb_kbd_id_table);//ָ���豸ID��// 

//����4. ����USB���̽ṹ�壺 
//
����struct usb_kbd { 

����struct input_dev *dev; //����һ�������豸// 

����struct usb_device *usbdev;//����һ��usb�豸// 

����unsigned char old[8]; //�����뿪ʱ����֮���ݻ�����// 

����struct urb *irq//usb����֮�ж������//, *led//usb����ָ֮ʾ�������//; 

����unsigned char newleds;//Ŀ��ָ����״̬// 

����char name[128];//��ų������ּ���Ʒ����// 

����char phys[64];//�豸֮�ڵ�// 

����unsigned char *new;// 

//������������ʱ����֮���ݻ�����// 
//
����struct usb_ctrlrequest *cr;//��������ṹ// 

����unsigned char *leds;//��ǰָʾ��״̬// 

����dma_addr_t cr_dma; //��������DMA�����ַ// 

����dma_addr_t new_dma; //�ж�urb��ʹ�ø�DMA������// 

����dma_addr_t leds_dma; //ָʾ��DAM�����ַ// 

����}; 

//����5. ��дUSB���������ṹ(�κ�һ��LINUX�µ��������и����Ƶ������ṹ)�� 
//
//����//USB���������ṹ��// 

����static struct usb_driver usb_kbd_driver = { 

����.name = "usbkbd",//��������// 

����.probe = usb_kbd_probe,//����̽�⺯��,����ʱ�õ�// 

����.disconnect = usb_kbd_disconnect,//�����Ͽ�����,��ж��ʱ�õ�����ѡ// 

����.id_table = usb_kbd_id_table,//�����豸ID��,����ָ���豸��ӿ�// 

����}; 

//����6. ��дģ����غ���(ÿ������������һ�����غ�������module_init����)�� 
//
//����//���������������ڵĿ�ʼ�㣬�� USB core ע�����������������// 

����static int __init usb_kbd_init(void) 

����{ 

����int result = usb_register(&usb_kbd_driver);//ע��USB��������// 

����if (result == 0) //ע��ʧ��// 

����info(DRIVER_VERSION ":" DRIVER_DESC); 

����return result; 

����} 

//����7. ��дģ��ж�غ���(ÿ������������һ��ж�غ�������module_exit����)�� 
//
//����// ���������������ڵĽ����㣬�� USB core ע����������������� // 

����static void __exit usb_kbd_exit(void) 

����{ 

����printk("SUNWILL-USBKBD:usb_kbd_exit begin...\n"); 

����usb_deregister(&usb_kbd_driver);//ע��USB��������// 

����} 

// 8 ָ��ģ���ʼ������(��ָ���ĺ�����insmod����ʱ����)�� 

����//module_init(usb_kbd_init); 

//����9. ָ��ģ���˳�����(��ָ���ĺ�����rmmod����ʱ����)�� 
//
����//module_exit(usb_kbd_exit); 

//����10. ��д�ж����������� 
//
//�����ڽ����жϴ������֮ǰ������������usb�����ṹ��urb��ʲô���ӵ� 

����struct urb 

����{ 

����spinlock_t lock; // lock for URB,�����������ڲ��������ٽ���Դ 

����void *hcpriv;// private data for host controler�������������������,��USB�ں˲���͸���� 

����struct list_head urb_list;//list pointer to all active urbs ˫��ָ��,���ڽ���USB���ᵽ���ڻ��URB˫�������У����ں˽ṹģ���кܶ�ط����е�����ṹ�壬����ṹ��������ָ�룬һ��ָ����һ�� list_head�ṹ�壬һ��ָ��ǰһ��list_head�ṹ�壬�ڽ����б����������ж��õ�����ṹ�塣 

����struct urb *next;// pointer to associated USB device ���ܴˣգңµ�USB�豸ָ�룻 

����unsigned int pipe;//pipe information ��ʾ�豸��ĳ���˵�Ϳͻ��豸��������֮���ͨ�� 

����int status;// return status ����״̬ 

����unsigned int transfer_flags;//USB_DISABLE_SPD �ܾ������ݰ�����������������С�����ݰ� 

//��������������Ա�����Ϊ��಻ͬ��λֵ��ȡ����usb���������urb�ľ�������������õ�ֵ���� 
//
//��������URB_SHORT_NOT_OK ��ֵ˵���κο��ܷ����Ķ���IN�˵�ļ�ϵĶ�ȡӦ�ñ�usb���ĵ�����һ����������ֵֻ����usb�豸 
//
//������ȡ��urb�����á�������д��urbû������ 
//
//����URB_ISO_ASAP ���urb�ǵ�ʱ�ģ�������������Ҫ��urb������ʱ�����������λ��ֻҪ������������ô����������Ҫ�ڴ�ʱ����urb 
//
//�����е�start_frame���������һ����ʱ��urbû�����ø�λ������������ƶ�start_frame��ֵ������ڴ���ĵ�ʱ���������Ļ������ܹ� 
//
//������ȷ�Ļָ��� 
//
//����URB_NO_TRANSFER_DMA_MAP ����˼�����ʱ����DMA�������ģ���urbʹ��DMA��������ʱ�����ø�λ��usb����ʹ�� 
//
//����transfer_dma�ı�����ָ��Ļ����� 
//
//��������URB_NO_SETUP_DMA_MAP ��URB_NO_TRANDFER_DMA_MAPλ���ƣ���λ���ڿ��ƴ����Ѿ����úõ�DMA��������urb��������������ˣ�USB 
//
//��������ʹ��setup_dma������ָ��Ļ�������������setup_packet���� 
//
//����URB_ASYNC_UNLINK �����λ�����ã���urb��usb_unlink_urb�ĵ��ü������������أ���urb�������ں�̨���⿪������˺���һֱ�� 
//
//������urb����ȫ�⿪���Ӻͽ����ŷ��أ�ʹ�ø�λʱҪС�ģ���Ϊ�����ܻ���ɰ��Ե��Ե�ͬ������ 
//
//��������URB_NO_FSBR ����UHCI USB����������������ʹ�ã�ָʾ����Ҫ��ͼʹ��ǰ�˵����߻����߼�����λͨ����Ӧ�ñ����ã���Ϊ���� 
//
//����UBCI���������ļ���ᵼ�´�����CPU���ɣ���PCI����æ�ڵȴ�һ�������˸�λ��URB 
//
//����URB_ZERO_PACKET �����λ�����ã�һ���������urb�Է���һ����������С���ݰ����������������ݶ��뵽һ���˵����ݰ��� 
//
//�����磬һЩ���ߵ�USB�����Ҫ��λ������ȷ�Ĺ����� 
//
//����URB_NO_INTERRUPT �����λ�����ã���urb������ʱ��Ӳ�����Ǹ��������һ���жϣ��Ը�λ��ʹ��Ӧ��С�Ľ�����ֻ�аѶ�� 
//
//����urb�Ŷӵ�ͬһ���˵�ʱ��ʹ�á�usb���ĵĺ���ʹ�ø�λ������DMA�������Ĵ��䡣 
//
����void *transfer_buffer;// associated data buffer �������ݻ����������ջ����豸�����ݣ������������������ģ����ɻ�ҳ���ڴ�飬��kmalloc(,GFP_KERNEL)�����ں��ڴ�ռ� 

����int transfer_buffer_length;//data buffer length transfer_buffer����transfer_dma������ָ��Ļ��������ȣ����κ�ʱ��һ��urbֻ����һ�� 

����int actual_length;// actual data buffer length ��urb�����󣬸ñ���������Ϊurb�����ε����ݻ���urb���յ�ʵ�����ݳ��� 

����int bandwidth;//bandwidth for this transfer request(INT or ISO),������ÿ��ռ��һ֡�Ĵ���ֻ�ʺ�����ʵʱ���жϴ��� 

����unsigned char *setup_packet;//setup packet(control only)����ָ�����п��������ָ�룮ֻ���ÿ��ƴ��䣮 

����int start_frame;// start frame(iso/irq only),������ʼ�����֡�ţ��жϴ����ʱ�򣬱�ʾ��������������ĵ�һ���жϴ����֡�ţ�ʵʱ�����ʱ��ָ�������һ��ʵʱ�������ݰ���֡�ţ����������USB_ISO_ASAP,�˱�����ʾ����������һ��ʵʱ�����֡�� 

����int number_of_packets;//number of packets in this request (iso)��������������ݰ�����ֻ�ʺ�ʵʱ���䣬��urb�����͵�usb����֮ǰ���뱻USB������������ 

����int interval;// polling interval(irq only)urb����ѯ��ʱ�����������жϻ��ߵ�ʱ������Ч����urb�����͵�usb����֮ǰ������usb�����������ã� 

����int error_count;//number of errors in this transfer(iso only)��usb�������ã������ڵ�ʱurb����������ʾ�������κ�һ�����͵Ĵ���ĵ�ʱ����������� 

����int timeout; 

����void *context;// context for completion routineָ��һ�����Ա�usb�����������õ����ݿ飬�������ڽ���������������е�urb�����ص����������ʱ��ʹ�á� 

����usb_complete_t complete;//pointer to completion routine,ָ��ص�������ָ�룬��������ɵ�ʱ����߳��ֳ����ʱ��usb���ĵ��ô˺� 

//���������ڸú����ڣ�usb����������Լ��urb���ͷ��������߰��������ύ������һ��������ȥ 
//
����usb_complete_t �������� 

����typedef voud (*usb_complete_t)(struct urb * , struct pt_regs *); 

����iso_packet_descriptor_t iso_frame_desc[0];//Ҫ����ʵʱ��������ݽṹ��ÿ���ṹ��ʾһ�����ݴ��� 

����int status 

//����������urb����֮�󣬻������ڱ�usb���Ĵ���ʱ���ñ���������Ϊurb�ĵ�ǰ״̬��usb����������԰�ȫ�ڷ��ʸñ�����Ψһ�ʺϾ�����urb��������������С���������Ϊ�˷�ֹ��urb���ڱ�usb���Ĵ���ʱ�ľ�̬�ķ��������ڵ���urb���ñ�����һ���ɹ�֮0��ʾurb�����Ѿ����⿪���ӣ�����ڻ�ȡ��ʱurb����ϸ״̬��Ӧ�ü��iso_frame_desc�������ñ�������Чֵ����ֵ�� 
//
//��������0 urb����ɹ� 
//
//��������-ENOENT urb��usb_kill_urb������ֹ 
//
//����-ECONNRESET urb��usb_unlink_urn���ý⿪���ӣ�urb��transfer_flags����������ΪURB_ASYNC_URBLINK; 
//
//��������-EINPROGRESS urb��Ȼզ��usb������������������������м�鵽��ֵ��˵�����ڴ���ȱ�� 
//
//����-EPROTO urb���������´��� 
//
//�����ڴ����з�����bitstuff���� 
//
//������������Ӳ��û�м�ʱ���յ���Ӧ���ݰ� 
//
//��������-EILSEQ urb�ڴ��䷢����CRCУ�鲻ƥ�� 
//
//����-EPIPE �˵㱻��ֹ������漰�Ķ˵㲻�ǿ��ƶ˵㣬���Ե���usb_clear_halt����������ô��� 
//
//����-ECOMM ����ʱ���ݵĽ����ٶȱ���д��ϵͳ�ڴ���ٶȿ죬�ô���ֵ��������IN urb�� 
//
//����-ENOSR ����ʱ��ϵͳ�ڴ��ȡ�������ٶȲ����죬��������Ҫ���USB�������ʣ��ô����������OUT utb�� 
//
//����-EOVERFLOW urb����������(babble)�����󡣡����š��������ڶ˵�����˳����˵�ָ�������ݰ��ߴ������ʱ 
//
//����-EREMOTEIO ��������urb��transfer_flags��������ΪURB_SHORT_NOT_OK��ʶʱ����ʾurbû�н��յ���Ҫ���ȫ�������� 
//
//����-ENODEV USB�豸�Ѿ���ϵͳ�Ƴ� 
//
//����-EXDEV �������ڵ�ʱurb�ϣ���ʾ�����������ɣ�Ϊ��ȷ������������ݣ�����������뵥������֡��״̬ 
//
//����-EINVAL urb�����˺��������飬URB�ں��ĵ������ĸ�ֵ�������������������Ǿ��˳�ϵͳ��Ȼ��ؼ�ȥ 
//
//����-ESHUTDOWN usb�����������������������صĴ����豸�Ѿ�����ֹ�������Ѿ���ϵͳ���룬��urb���豸���Ƴ�֮���ύ�������urb���ύ���豸�����ñ��ı䣬Ҳ���ܷ���������� 
//
//����һ����˵������ֵ-EPROTO ,-EILSSEQ �� -EOVERFLOW��ʾ�豸���豸�Ĺ̼����߰��豸���ӵ��˼�����ĵ��·�����Ӳ�����ϡ� 
//
//����//�ж��������������ж����󵽴�ʱ���øú���// 
//
����static void usb_kbd_irq(struct urb *urb, struct pt_regs *regs) 

����{ 

����struct usb_kbd *kbd = urb->context; 

����int i; 

����switch (urb->status) { 

����case 0: // success // 

����break; 

����case -ECONNRESET: // unlink // 

����case -ENOENT: 

����case -ESHUTDOWN: 

����return; 

����// -EPIPE: should clear the halt // 

����default: // error // 

����goto resubmit; 

����} 

����//input_regs(kbd->dev, regs); 

����// 

//��֪��������, ע�͵��ò����Կ���������// 

����for (i = 0; i < 8; i++)//8�ε�ֵ������:29-42-56-125-97-54-100-126// 

����{ 

����input_report_key(kbd->dev, usb_kbd_keycode[i + 224], (kbd->new[0] >> i) & 1); 

����} 

////��ͬʱֻ����1���������ڵ�[2]���ֽ�,��ͬʱ������������ڶ����ڵ�[3]�ֽڣ�����������6������ͬʱ����// 

����for (i = 2; i < 8; i++) { 

////��ȡ�����뿪���ж�// 

����if (kbd->old > 3 && memscan(kbd->new + 2, kbd->old, 6) == kbd->new + 8) {//ͬʱû�и�KEY�İ���״̬// 

����if (usb_kbd_keycode[kbd->old]) 

����{ 

����input_report_key(kbd->dev, usb_kbd_keycode[kbd->old], 0); 

����} 

����else 

����info("Unknown key (scancode %#x) released.", kbd->old); 

����} 

����// 

//��ȡ���̰��µ��ж�// 

����if (kbd->new > 3 && memscan(kbd->old + 2, kbd->new, 6) == kbd->old + 8) {//ͬʱû�и�KEY���뿪״̬// 

����if (usb_kbd_keycode[kbd->new]) 

����{ 

����input_report_key(kbd->dev, usb_kbd_keycode[kbd->new], 1); 

����} 

����else 

����info("Unknown key (scancode %#x) pressed.", kbd->new); 

����} 

����} 

//����//ͬ���豸,��֪�¼��Ľ����������Ѿ�������һ�������ı���// 
//
����input_sync(kbd->dev); 

����memcpy(kbd->old, kbd->new, 8);//��ֹδ�ɿ�ʱ�������µİ�������// 

����resubmit: 

����i = usb_submit_urb (urb, GFP_ATOMIC);//����USB�����// 

����if (i) 

����err ("can't resubmit intr, %s-%s/input0, status %d", 

����kbd->usbdev->bus->bus_name, 

����kbd->usbdev->devpath, i); 

����} 

//����11. ��д�¼��������� 
//
//����//�¼�������// 

����static int usb_kbd_event(struct input_dev *dev, unsigned int type, 

����unsigned int code, int value) 

����{ 

����struct usb_kbd *kbd = dev->private; 

����if (type != EV_LED) //��֧��LED�¼� // 

����return -1; 

//����//��ȡָʾ�Ƶ�Ŀ��״̬// 
//
����kbd->newleds = (!!test_bit(LED_KANA, dev->led) << 3) | (!!test_bit(LED_COMPOSE, dev->led) << 3) | 

����(!!test_bit(LED_SCROLLL, dev->led) << 2) | (!!test_bit(LED_CAPSL, dev->led) << 1) | 

����(!!test_bit(LED_NUML, dev->led)); 

����if (kbd->led->status == -EINPROGRESS) 

����return 0; 

����// 

//����ָʾ��״̬�Ѿ���Ŀ��״̬����Ҫ�����κβ���// 
//
����if (*(kbd->leds) == kbd->newleds) 

����return 0; 

����*(kbd->leds) = kbd->newleds; 

����kbd->led->dev = kbd->usbdev; 

////����usb�����// 

����if (usb_submit_urb(kbd->led, GFP_ATOMIC)) 

����err("usb_submit_urb(leds) failed"); 

����return 0; 

����} 

//����12. ��дLED�¼��������� 
//
//����//����event֮��������ù�����ʵusb_kbd_event���Ѿ����ˣ��ú��������ÿ����Ƿ�ֹevent�Ĳ���ʧ�ܣ�һ��ע�͵��ú����е������ж�������������// 

����static void usb_kbd_led(struct urb *urb, struct pt_regs *regs) 

����{ 

����struct usb_kbd *kbd = urb->context; 

����if (urb->status) 

����warn("led urb status %d received", urb->status); 

����if (*(kbd->leds) == kbd->newleds)// 

//ָʾ��״̬�Ѿ���Ŀ��״̬����Ҫ�����κβ���// 

����return; 

����*(kbd->leds) = kbd->newleds; 

����kbd->led->dev = kbd->usbdev; 

����if (usb_submit_urb(kbd->led, GFP_ATOMIC)) 

����err("usb_submit_urb(leds) failed"); 

����} 

//����13. ��дUSB�豸�򿪺���: 
//
//����//�򿪼����豸ʱ����ʼ�ύ�� probe �����й����� urb������ urb ���ڡ� // 
//
����static int usb_kbd_open(struct input_dev *dev) 

����{ 

����struct usb_kbd *kbd = dev->private; 

����kbd->irq->dev = kbd->usbdev; 

����if (usb_submit_urb(kbd->irq, GFP_KERNEL)) 

����return -EIO; 

����return 0; 

����} 

//����14. ��дUSB�豸�رպ��� 
//
//����//�رռ����豸ʱ������ urb �������ڡ� // 

����static void usb_kbd_close(struct input_dev *dev) 

����{ 

����struct usb_kbd *kbd = dev->private; 

����usb_kill_urb(kbd->irq); //ȡ��kbd->irq���usb�����// 

����} 

//����15. ����URB 
//
//����//����URB�ڴ�ռ伴����URB// 
//
����static int usb_kbd_alloc_mem(struct usb_device *dev, struct usb_kbd *kbd) 

����{ 

����if (!(kbd->irq = usb_alloc_urb(0, GFP_KERNEL))) 

����return -1; 

����if (!(kbd->led = usb_alloc_urb(0, GFP_KERNEL))) 

����return -1; 

����if (!(kbd->new = usb_buffer_alloc(dev, 8, GFP_ATOMIC, &kbd->new_dma))) 

����return -1; 

����if (!(kbd->cr = usb_buffer_alloc(dev, sizeof(struct usb_ctrlrequest), GFP_ATOMIC, &kbd->cr_dma))) 

����return -1; 

����if (!(kbd->leds = usb_buffer_alloc(dev, 1, GFP_ATOMIC, &kbd->leds_dma))) 

����return -1; 

����return 0; 

����} 

//����16. ����URB 
//
//����//�ͷ�URB�ڴ�ռ伴����URB// 
//
����static void usb_kbd_free_mem(struct usb_device *dev, struct usb_kbd *kbd) 

����{ 

����if (kbd->irq) 

����usb_free_urb(kbd->irq); 

����if (kbd->led) 

����usb_free_urb(kbd->led); 

����if (kbd->new) 

����usb_buffer_free(dev, 8, kbd->new, kbd->new_dma); 

����if (kbd->cr) 

����usb_buffer_free(dev, sizeof(struct usb_ctrlrequest), kbd->cr, kbd->cr_dma); 

����if (kbd->leds) 

����usb_buffer_free(dev, 1, kbd->leds, kbd->leds_dma); 

����} 

//����17. USB��������̽�⺯��: 
//
//����//USB��������̽�⺯������ʼ���豸��ָ��һЩ�������ĵ�ַ// 
//
����static int usb_kbd_probe(struct usb_interface *iface, 

����const struct usb_device_id *id) 

����{ 

����struct usb_device *dev = interface_to_usbdev(iface); 

����struct usb_host_interface *interface; 

����struct usb_endpoint_descriptor *endpoint; 

����struct usb_kbd *kbd; 

����struct input_dev *input_dev; 

����int i, pipe, maxp; 

////��ǰѡ���interface// 

����interface = iface->cur_altsetting; 

//����//����ֻ��һ���ж�IN�˵�// 
//
����if (interface->desc.bNumEndpoints != 1) 

����return -ENODEV; 

����//��ȡ�˵�������// 

����endpoint = &interface->endpoint[0].desc; 

����if (!(endpoint->bEndpointAddress & USB_DIR_IN)) 

����return -ENODEV; 

����if ((endpoint->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) != USB_ENDPOINT_XFER_INT) 

����return -ENODEV; 

////��endpoint����Ϊ�ж�IN�˵�// 

����pipe = usb_rcvintpipe(dev, endpoint->bEndpointAddress); 

////��ȡ�������ֵ// 

����maxp = usb_maxpacket(dev, pipe, usb_pipeout(pipe)); 

����kbd = kzalloc(sizeof(struct usb_kbd), GFP_KERNEL); 

����input_dev = input_allocate_device(); 

����if (!kbd || !input_dev) 

����goto fail1; 

����if (usb_kbd_alloc_mem(dev, kbd)) 

����goto fail2; 

//// ��� usb �豸�ṹ��������豸�ṹ�� // 

����kbd->usbdev = dev; 

����kbd->dev = input_dev; 

����// 

//��"�������� ��Ʒ����"�ĸ�ʽ����д��kbd->name// 

����if (dev->manufacturer) 

����strlcpy(kbd->name, dev->manufacturer, sizeof(kbd->name)); 

����if (dev->product) { 

����if (dev->manufacturer) 

����strlcat(kbd->name, " ", sizeof(kbd->name)); 

����strlcat(kbd->name, dev->product, sizeof(kbd->name)); 

����} 

����// 

//��ⲻ����������// 

����if (!strlen(kbd->name)) 

����snprintf(kbd->name, sizeof(kbd->name), 

����"USB HIDBP Keyboard %04x:%04x", 

����le16_to_cpu(dev->descriptor.idVendor), 

����le16_to_cpu(dev->descriptor.idProduct)); 

////�豸���ӵ�ַ// 

����usb_make_path(dev, kbd->phys, sizeof(kbd->phys)); 

����strlcpy(kbd->phys, "/input0", sizeof(kbd->phys)); 

����input_dev->name = kbd->name; 

����input_dev->phys = kbd->phys; 

����// 

//����* input_dev �е� input_id �ṹ�壬�����洢���̡��豸���ͺ��豸�ı�ţ���������ǽ��豸������ 
//
//����* �еı�Ÿ�����Ƕ��������ϵͳ�ṹ�� 

����// 

����usb_to_input_id(dev, &input_dev->id); 

����// cdev ���豸�������class device�� // 

����input_dev->cdev.dev = &iface->dev; 

//����// input_dev �� private ���������ڱ�ʾ��ǰ�����豸�����࣬���ｫ���̽ṹ����󸳸��� // 
//
����input_dev->private = kbd; 

����input_dev->evbit[0] = BIT(EV_KEY)//�����¼�// | BIT(EV_LED)//LED�¼�// | BIT(EV_REP)//�Զ��ظ���ֵ//; 

����input_dev->ledbit[0] = BIT(LED_NUML)//���ֵ�// | BIT(LED_CAPSL)//��Сд��// | BIT(LED_SCROLLL)//������// | BIT(LED_COMPOSE) | BIT(LED_KANA); 

����for (i = 0; i < 255; i++) 

����set_bit(usb_kbd_keycode, input_dev->keybit); 

����clear_bit(0, input_dev->keybit); 

����input_dev->event = usb_kbd_event;// 

//����ע���¼����������// 
//
����input_dev->open = usb_kbd_open;//ע���豸�򿪺������// 

����input_dev->close = usb_kbd_close;//ע���豸�رպ������// 

����// 

//��ʼ���ж�URB// 

����usb_fill_int_urb(kbd->irq//��ʼ��kbd->irq���urb//, dev//���urbҪ���͵�dev����豸//, pipe//���urbҪ���͵�pipe����˵�//, 

����kbd->new//ָ�򻺳��ָ��//, (maxp > 8 ? 8 : maxp)//���峤��//, 

����usb_kbd_irq//���urb���ʱ���õĴ�����//, kbd//ָ�����ݿ��ָ�룬����ӵ����urb�ṹ�ɱ���ɴ�������ȡ//, endpoint->bInterval//urbӦ�������ȵļ��//); 

����kbd->irq->transfer_dma = kbd->new_dma; //ָ��urb��Ҫ�����DMA������// 

����kbd->irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;//��urb��һ��DMA��������Ҫ����// 

����kbd->cr->bRequestType = USB_TYPE_CLASS | USB_RECIP_INTERFACE;//����������ӿڶ���// 

����kbd->cr->bRequest = 0x09; //�ж�������// 

����kbd->cr->wValue = cpu_to_le16(0x200); 

����kbd->cr->wIndex = cpu_to_le16(interface->desc.bInterfaceNumber);//�ӿں�// 

����kbd->cr->wLength = cpu_to_le16(1);//���ݴ���׶δ�����ٸ�bytes// 

����// 

//��ʼ������URB// 

����usb_fill_control_urb(kbd->led, dev, usb_sndctrlpipe(dev, 0), 

����(void *) kbd->cr, kbd->leds, 1, 

����usb_kbd_led, kbd); 

����kbd->led->setup_dma = kbd->cr_dma; 

����kbd->led->transfer_dma = kbd->leds_dma; 

����kbd->led->transfer_flags |= (URB_NO_TRANSFER_DMA_MAP | URB_NO_SETUP_DMA_MAP//���ʹ��DMA������urb��setup_dmaָ����ָ��Ļ�������DMA������������ setup_packet��ָ��Ļ�����//); 

����// 

//����ע�������豸// 
//
����input_register_device(kbd->dev); 

����usb_set_intfdata(iface, kbd);//���ýӿ�˽������// 

����return 0; 

����fail2: usb_kbd_free_mem(dev, kbd); 

����fail1: input_free_device(input_dev); 

����kfree(kbd); 

����return -ENOMEM; 

����} 

//����18. ��д�Ͽ����ӵĺ���: 
//
//����//�Ͽ�����(������豸�γ�)�Ĵ�����// 

����static void usb_kbd_disconnect(struct usb_interface *intf) 

����{ 

����struct usb_kbd *kbd = usb_get_intfdata (intf);//��ȡ�ӿڵ�˽�����ݸ�kbd// 

����usb_set_intfdata(intf, NULL);//���ýӿڵ�˽������ΪNULL// 

����if (kbd) { 

����usb_kill_urb(kbd->irq);//ȡ���ж�����// 

����input_unregister_device(kbd->dev);//ע���豸// 

����usb_kbd_free_mem(interface_to_usbdev(intf), kbd);//�ͷ��ڴ�ռ�// 

����kfree(kbd); 

����} 

����} 

//����19. ��дMakefile: 
//
//����############################## 
//
//����#usbkdb Makefile for linux 
//
//����############################## 
//
//����obj-m:=usbkbd.o 
//
//����KERNELDIR ?= /lib/modules/$(shell uname -r)/build 
//
//����PWD:=$(shell pwd) 
//
//����default: 
//
//����$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
