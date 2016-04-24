
//��ת+���䡿������ϵͳ--event�������gpio �������� .                                                                                                                                                            
//���ࣺ linux�ں���ֲ/���� 2009-09-08 09:32 1850���Ķ� ����(0) �ղ� �ٱ�                                                                                                                                        
//���ԣ�http://www.cnitblog.com/luofuchong/archive/2009/08/03/36157.html                                                                                                                                         
//                                                                                                                                                                    
//                                                                                                                                                                                                               
//                                                                                                                                                                    
//#####################################################################################################                                                                                                          
//��ǰ���о���һ��������ϵͳ��ԭ��,���˵ĸо���������ϵͳ�ܸ���.����ʵ�ں˿��������ⷽ���Ѿ����ú�������,                                                                                                        
//������ϵͳ��Ȼ���۸���,����ֻҪ���������������ϵͳ��һЩ���˼���,����Ҫʹ������������.                                                                                                                      
//                                                                                                                                                                    
//�������ں��Դ���gpio_keys����Ϊ��,����������ϵͳ��ʹ��.                                                                                                                                                        
//��Ҫ��ԭ����gpio_keys�����Ƚϼ��׶�,���ⲻ��û���˶��д�����,�����̵Ļ�����ÿһ�鿪�����϶����а�^_^                                                                                                         
//                                                                                                                                                                    
//������ǰ��ϰ��,�ȴ��µ��ϵ��о��ײ�����������ύ�����¼���:                                                                                                                                                   
//#####################################################################################################                                                                                                          
//                                                                                                                                                                    
//drivers/input/keyboard/gpio_keys.c:                                                                                                                                                                            
    
    
//===========================��ע�ͻس�    /*================================                                                                                                                                                                       

static int __devinit gpio_keys_probe (struct platform_device *pdev)                                                                                                                                            
{                                                                                                                                                                                                              
    struct gpio_keys_platform_data *pdata = pdev->dev.platform_data;                                                                                                                                           
    struct input_dev *input;                                                                                                                                                                                   
    int i, error;                                                                                                                                                                                              
                                                                                                                                                                    
    input = input_allocate_device();//����input_dev�ṹ                                                                                                                                                        
    if (!input)                                                                                                                                                                                                
        return -ENOMEM;                                                                                                                                                                                        
                                                                                                                                                                    
    platform_set_drvdata(pdev, input);//��input_dev�ṹ�ź�(�Ժ󷽱����)                                                                                                                                      
                                                                                                                                                                    
    input->evbit[0] = BIT(EV_KEY);//Ŀǰevent�����Ͳ�����32,������ῴ������evbit����Ĳ������Ƕ�evbit[0]�е�λ�����в���.                                                                                     
                                                                                                                                                                    
    input->name = pdev->name;                                                                                                                                                                                  
    input->phys = "gpio-keys/input0";                                                                                                                                                                          
    input->dev.parent = &pdev->dev;                                                                                                                                                                            
                                                                                                                                                                    
    input->id.bustype = BUS_HOST;                                                                                                                                                                              
    input->id.vendor = 0x0001;                                                                                                                                                                                 
    input->id.product = 0x0001;                                                                                                                                                                                
    input->id.version = 0x0100;                                                                                                                                                                                
                                                                                                                                                                    
    for (i = 0; i < pdata->nbuttons; i++) {                                                                                                                                                                    
        struct gpio_keys_button *button = &pdata->buttons[i];                                                                                                                                                  
        int irq = gpio_to_irq(button->gpio);                                                                                                                                                                   
        unsigned int type = button->type ?: EV_KEY;                                                                                                                                                            
                                                                                                                                                                    
        set_irq_type(irq, IRQ_TYPE_EDGE_BOTH);                                                                                                                                                                 
                                                                                                                                                                    
       // �����û���ָ����gpio_keys�������жϺ�ע���жϴ�����                                                                                                                                             
        error = request_irq(irq, gpio_keys_isr, IRQF_SAMPLE_RANDOM,                                                                                                                                            
                     button->desc ? button->desc : "gpio_keys",                                                                                                                                                
                     pdev);                                                                                                                                                                                    
        if (error) {                                                                                                                                                                                           
            printk(KERN_ERR "gpio-keys: unable to claim irq %d; error %d/n",                                                                                                                                   
                irq, error);                                                                                                                                                                                   
            goto fail;                                                                                                                                                                                         
        }                                                                                                                                                                                                      
                                                                                                                                                                    
        input_set_capability(input, type, button->code);                                                                                                                                                       
    }                                                                                                                                                                                                          
                                                                                                                                                                    
    error = input_register_device(input);//ע�������豸,���Ͷ�Ӧ��handler�������ҹ�                                                                                                                          
    if (error) {                                                                                                                                                                                               
        printk(KERN_ERR "Unable to register gpio-keys input device/n");                                                                                                                                        
        goto fail;                                                                                                                                                                                             
    }                                                                                                                                                                                                          
                                                                                                                                                                    
    return 0;                                                                                                                                                                                                  
                                                                                                                                                                    
 fail:                                                                                                                                                                                                         
    for (i = i - 1; i >= 0; i--)                                                                                                                                                                               
        free_irq(gpio_to_irq(pdata->buttons[i].gpio), pdev);                                                                                                                                                   
                                                                                                                                                                    
    input_free_device(input);                                                                                                                                                                                  
                                                                                                                                                                    
    return error;                                                                                                                                                                                              
}                                                                                                                                                                                                              
                                                                                                                                                                    
//                                                                                                                                                                    
//�ᵽinput_dev�ṹ,����̸һ���Ҷ����������:                                                                                                                                                                    
struct input_dev {                                                                                                                                                                                             
                                                                                                                                                                    
    void *private;                                                                                                                                                                                             
                                                                                                                                                                    
    const char *name;                                                                                                                                                                                          
    const char *phys;                                                                                                                                                                                          
    const char *uniq;                                                                                                                                                                                          
    struct input_id id;                                                                                                                                                                                        
                                                                                                                                                                    
   //                                                                                                                                                                                                         
   //  * ���ݸ��������źŵ���������������Ϊunsigned long ������,                                                                                                                                                 
   //  * �����ÿ1bit����һ���ź�����,                                                                                                                                                                           
   //  * �ں��л���������λ����λ��������ʾʱ��ķ����ͱ�����.                                                                                                                                                 
                                                                                                                                                                                                             
                                                                                                                                                                    
    unsigned long evbit[NBITS(EV_MAX)];                                                                                                                                                                        
    unsigned long keybit[NBITS(KEY_MAX)];                                                                                                                                                                      
    unsigned long relbit[NBITS(REL_MAX)];                                                                                                                                                                      
    unsigned long absbit[NBITS(ABS_MAX)];                                                                                                                                                                      
    unsigned long mscbit[NBITS(MSC_MAX)];                                                                                                                                                                      
    unsigned long ledbit[NBITS(LED_MAX)];                                                                                                                                                                      
    unsigned long sndbit[NBITS(SND_MAX)];                                                                                                                                                                      
    unsigned long ffbit[NBITS(FF_MAX)];                                                                                                                                                                        
    unsigned long swbit[NBITS(SW_MAX)];                                                                                                                                                                        
                                                                                                                                                                    
    .........................................                                                                                                                                                                  
};                                                                                                                                                                                                             
                                                                                                                                                                    
//*                                                                                                                                                                                                            
// * input_set_capability - mark device as capable of a certain event                                                                                                                                            
// * @dev: device that is capable of emitting or accepting event                                                                                                                                                 
// * @type: type of the event (EV_KEY, EV_REL, etc...)                                                                                                                                                           
// * @code: event code                                                                                                                                                                                           
// *                                                                                                                                                                                                             
// * In addition to setting up corresponding bit in appropriate capability                                                                                                                                       
// * bitmap the function also adjusts dev->evbit.                                                                                                                                                                
//                                                                                                                                                                                                             
                                                                                                                                                                    
// ��¼���豸������Щ�¼�����Ȥ(������д���)                                                                                                                                                                
void input_set_capability (struct input_dev *dev, unsigned int type, unsigned int code)                                                                                                                        
{                                                                                                                                                                                                              
    switch (type) {                                                                                                                                                                                            
    case EV_KEY:                                                                                                                                                                                               
        __set_bit(code, dev->keybit);//���簴��,Ӧ�ö���Щ��ֵ�İ������д���(�������������������)                                                                                                             
        break;                                                                                                                                                                                                 
                                                                                                                                                                    
    case EV_REL:                                                                                                                                                                                               
        __set_bit(code, dev->relbit);                                                                                                                                                                          
        break;                                                                                                                                                                                                 
                                                                                                                                                                    
    case EV_ABS:                                                                                                                                                                                               
        __set_bit(code, dev->absbit);                                                                                                                                                                          
        break;                                                                                                                                                                                                 
                                                                                                                                                                    
    case EV_MSC:                                                                                                                                                                                               
        __set_bit(code, dev->mscbit);                                                                                                                                                                          
        break;                                                                                                                                                                                                 
                                                                                                                                                                    
    case EV_SW:                                                                                                                                                                                                
        __set_bit(code, dev->swbit);                                                                                                                                                                           
        break;                                                                                                                                                                                                 
                                                                                                                                                                    
    case EV_LED:                                                                                                                                                                                               
        __set_bit(code, dev->ledbit);                                                                                                                                                                          
        break;                                                                                                                                                                                                 
                                                                                                                                                                    
    case EV_SND:                                                                                                                                                                                               
        __set_bit(code, dev->sndbit);                                                                                                                                                                          
        break;                                                                                                                                                                                                 
                                                                                                                                                                    
    case EV_FF:                                                                                                                                                                                                
        __set_bit(code, dev->ffbit);                                                                                                                                                                           
        break;                                                                                                                                                                                                 
                                                                                                                                                                    
    default:                                                                                                                                                                                                   
        printk(KERN_ERR                                                                                                                                                                                        
            "input_set_capability: unknown type %u (code %u)/n",                                                                                                                                               
            type, code);                                                                                                                                                                                       
        dump_stack();                                                                                                                                                                                          
        return;                                                                                                                                                                                                
    }                                                                                                                                                                                                          
                                                                                                                                                                    
    __set_bit(type, dev->evbit);//�о���ǰ���ظ���(ǰ��һ�����ù�һ����)                                                                                                                                       
}                                                                                                                                                                                                              
//EXPORT_SYMBOL(input_set_capability);                                                                                                                                                                           
                                                                                                                                                                    
                                                                                                                                                                    
static irqreturn_t gpio_keys_isr (int irq, void *dev_id)                                                                                                                                                       
{                                                                                                                                                                                                              
        int i;                                                                                                                                                                                                 
        struct platform_device *pdev = dev_id;                                                                                                                                                                 
        struct gpio_keys_platform_data *pdata = pdev->dev.platform_data;                                                                                                                                       
        struct input_dev *input = platform_get_drvdata(pdev);                                                                                                                                                  
                                                                                                                                                                    
        for (i = 0; i < pdata->nbuttons; i++) {                                                                                                                                                                
                struct gpio_keys_button *button = &pdata->buttons[i];                                                                                                                                          
                int gpio = button->gpio;                                                                                                                                                                       
                                                                                                                                                                    
                if (irq == gpio_to_irq(gpio)) {//�ж��ĸ���������?                                                                                                                                             
                        unsigned int type = button->type ?: EV_KEY;                                                                                                                                            
                        int state = (gpio_get_value(gpio) ? 1 : 0) ^ button->active_low;//��¼����״̬                                                                                                         
                                                                                                                                                                    
                        input_event(input, type, button->code, !!state);//�㱨�����¼�                                                                                                                         
                        input_sync(input);//�ȴ������¼��������                                                                                                                                               
                }                                                                                                                                                                                              
        }                                                                                                                                                                                                      
                                                                                                                                                                    
        return IRQ_HANDLED;                                                                                                                                                                                    
}                                                                                                                                                                                                              
                                                                                                                                                                    
                                                                                                                                                                    
//                                                                                                                                                                                                             
// * input_event() - report new input event                                                                                                                                                                      
// * @dev: device that generated the event                                                                                                                                                                       
// * @type: type of the event                                                                                                                                                                                    
// * @code: event code                                                                                                                                                                                           
// * @value: value of the event                                                                                                                                                                                  
// *                                                                                                                                                                                                             
// * This function should be used by drivers implementing various input devices                                                                                                                                  
// * See also input_inject_event()                                                                                                                                                                               
                                                                                                                                                                                                             
void input_event (struct input_dev *dev, unsigned int type, unsigned int code, int value)                                                                                                                      
{                                                                                                                                                                                                              
    struct input_handle *handle;                                                                                                                                                                               
                                                                                                                                                                    
    if (type > EV_MAX || !test_bit(type, dev->evbit))//�����жϸ��¼������Ƿ���Ч��Ϊ���豸������                                                                                                              
        return;                                                                                                                                                                                                
                                                                                                                                                                    
    add_input_randomness(type, code, value);                                                                                                                                                                   
                                                                                                                                                                    
    switch (type) {                                                                                                                                                                                            
                                                                                                                                                                    
        case EV_SYN:                                                                                                                                                                                           
            switch (code) {                                                                                                                                                                                    
                case SYN_CONFIG:                                                                                                                                                                               
                    if (dev->event)                                                                                                                                                                            
                        dev->event(dev, type, code, value);                                                                                                                                                    
                    break;                                                                                                                                                                                     
                                                                                                                                                                    
                case SYN_REPORT:                                                                                                                                                                               
                    if (dev->sync)                                                                                                                                                                             
                        return;                                                                                                                                                                                
                    dev->sync = 1;                                                                                                                                                                             
                    break;                                                                                                                                                                                     
            }                                                                                                                                                                                                  
            break;                                                                                                                                                                                             
                                                                                                                                                                    
        case EV_KEY:                                                                                                                                                                                           
           //                                                                                                                                                                                                 
           //  * ������Ҫ���㼸������:                                                                                                                                                                           
           //  * 1: ��ֵ��Ч(����������ļ�ֵ����Ч��Χ)                                                                                                                                                         
           //  * 2: ��ֵΪ�豸���ܽ���(���ڸ��豸��ӵ�еļ�ֵ��Χ)                                                                                                                                               
           //  * 3: ����״̬�ı���                                                                                                                                                                               
           //                                                                                                                                                                                                  
                                                                                                                                                                    
            if (code > KEY_MAX || !test_bit(code, dev->keybit) || !!test_bit(code, dev->key) == value)                                                                                                         
                return;                                                                                                                                                                                        
                                                                                                                                                                    
            if (value == 2)                                                                                                                                                                                    
                break;                                                                                                                                                                                         
                                                                                                                                                                    
            change_bit(code, dev->key);//�ı��Ӧ������״̬                                                                                                                                                    
                                                                                                                                                                    
           // �����ϣ������δ�ͷŵ�ʱ�򲻶ϻ㱨�����¼��Ļ���Ҫ�������(�ڼ򵥵�gpio_keys�����в���Ҫ���,��ʱ��ȥ����)                                                                                    
            if (test_bit(EV_REP, dev->evbit) && dev->rep[REP_PERIOD] && dev->rep[REP_DELAY] && dev->timer.data && value) {                                                                                     
                dev->repeat_key = code;                                                                                                                                                                        
                mod_timer(&dev->timer, jiffies + msecs_to_jiffies(dev->rep[REP_DELAY]));                                                                                                                       
            }                                                                                                                                                                                                  
                                                                                                                                                                    
            break;                                                                                                                                                                                             
........................................................                                                                                                                                                       
                                                                                                                                                                    
    if (type != EV_SYN)                                                                                                                                                                                        
        dev->sync = 0;                                                                                                                                                                                         
                                                                                                                                                                    
    if (dev->grab)                                                                                                                                                                                             
        dev->grab->handler->event(dev->grab, type, code, value);                                                                                                                                               
    else                                                                                                                                                                                                       
       //                                                                                                                                                                                                     
       //  * ѭ���������д�����豸��handle(event,mouse,ts,joy��),                                                                                                                                               
       //  * ����н��̴�����Щhandle(���ж�д),��������Ӧ��event�ӿ������㱨�������¼�.                                                                                                                     
                                                                                                                                                                                                             
        list_for_each_entry(handle, &dev->h_list, d_node)                                                                                                                                                      
            if (handle->open)                                                                                                                                                                                  
                handle->handler->event(handle, type, code, value);                                                                                                                                             
}                                                                                                                                                                                                              
//EXPORT_SYMBOL(input_event);                                                                                                                                                                                    
                                                                                                                                                                    
                                                                                                                                                                    
//#########################################################################                                                                                                                                      
//����,���������о�һ��event�����input�㱨���������������¼�������������.                                                                                                                                   
//#########################################################################                                                                                                                                      
//                                                                                                                                                                    
//drivers/input/evdev.c:                                                                                                                                                                                         
                                                                                                                                                                    
static struct input_handler evdev_handler = {                                                                                                                                                                  
        .event =        evdev_event,                                                                                                                                                                           
        .connect =      evdev_connect,                                                                                                                                                                         
        .disconnect =   evdev_disconnect,                                                                                                                                                                      
        .fops =         &evdev_fops,                                                                                                                                                                           
        .minor =        EVDEV_MINOR_BASE,                                                                                                                                                                      
        .name =         "evdev",                                                                                                                                                                               
        .id_table =     evdev_ids,                                                                                                                                                                             
};                                                                                                                                                                                                             
                                                                                                                                                                    
static void evdev_event (struct input_handle *handle, unsigned int type, unsigned int code, int value)                                                                                                         
{                                                                                                                                                                                                              
        struct evdev *evdev = handle->private;                                                                                                                                                                 
        struct evdev_client *client;                                                                                                                                                                           
                                                                                                                                                                    
        if (evdev->grab) {                                                                                                                                                                                     
                client = evdev->grab;                                                                                                                                                                          
                                                                                                                                                                    
                do_gettimeofday(&client->buffer[client->head].time);                                                                                                                                           
                client->buffer[client->head].type = type;                                                                                                                                                      
                client->buffer[client->head].code = code;                                                                                                                                                      
                client->buffer[client->head].value = value;                                                                                                                                                    
                client->head = (client->head + 1) & (EVDEV_BUFFER_SIZE - 1);                                                                                                                                   
                                                                                                                                                                    
                kill_fasync(&client->fasync, SIGIO, POLL_IN);                                                                                                                                                  
        } else                                                                                                                                                                                                 
                 // ����client_list�����е�client�ṹ(����Щ��evdev�Ľ���(�������^_^))                                                                                                                   
                list_for_each_entry(client, &evdev->client_list, node) {                                                                                                                                       
                           // ������������źŵ�struct input_event�ṹ(�¼�,����,����,��ֵ)                                                                                                               
                        do_gettimeofday(&client->buffer[client->head].time);                                                                                                                                   
                        client->buffer[client->head].type = type;                                                                                                                                              
                        client->buffer[client->head].code = code;                                                                                                                                              
                        client->buffer[client->head].value = value;                                                                                                                                            
                           // ����дָ��                                                                                                                                                                    
                        client->head = (client->head + 1) & (EVDEV_BUFFER_SIZE - 1);                                                                                                                           
                                                                                                                                                                    
                        kill_fasync(&client->fasync, SIGIO, POLL_IN);//֪ͨ����input_sync�Ľ���:�����¼����Ѵ������(֪ͨ�ײ�).                                                                                
                }                                                                                                                                                                                              
                                                                                                                                                                    
        wake_up_interruptible(&evdev->wait);//����˯����evdev->wait�ȴ����еȴ�������Ϣ�Ľ���(֪ͨ�ϲ�).                                                                                                       
}                                                                                                                                                                                                              
                                                                                                                                                                    
//###################################################################################                                                                                                                            
//����,����һ�������������¼��������,�����������ϵ��ϵ��������û�����λ�ȡ��������¼���.                                                                                                                      
//###################################################################################                                                                                                                            
                                                                                                                                                                    
                                                                                                                                                                    
static const struct file_operations evdev_fops = {                                                                                                                                                             
        .owner =        THIS_MODULE,                                                                                                                                                                           
        .read =         evdev_read,                                                                                                                                                                            
        .write =        evdev_write,                                                                                                                                                                           
        .poll =         evdev_poll,                                                                                                                                                                            
        .open =         evdev_open,                                                                                                                                                                            
        .release =      evdev_release,                                                                                                                                                                         
        .unlocked_ioctl = evdev_ioctl,                                                                                                                                                                         
#ifdef CONFIG_COMPAT                                                                                                                                                                                           
        .compat_ioctl = evdev_ioctl_compat,                                                                                                                                                                    
#endif                                                                                                                                                                                                         
        .fasync =       evdev_fasync,                                                                                                                                                                          
        .flush =        evdev_flush                                                                                                                                                                            
};                                                                                                                                                                                                             
                                                                                                                                                                    
                                                                                                                                                                    
static int evdev_open (struct inode *inode, struct file *file)                                                                                                                                                 
{                                                                                                                                                                                                              
        struct evdev_client *client;                                                                                                                                                                           
        struct evdev *evdev;                                                                                                                                                                                   
        int i = iminor(inode) - EVDEV_MINOR_BASE;                                                                                                                                                              
        int error;                                                                                                                                                                                             
                                                                                                                                                                    
        if (i >= EVDEV_MINORS)                                                                                                                                                                                 
                return -ENODEV;                                                                                                                                                                                
                                                                                                                                                                    
        evdev = evdev_table[i];                                                                                                                                                                                
                                                                                                                                                                    
        if (!evdev || !evdev->exist)                                                                                                                                                                           
                return -ENODEV;                                                                                                                                                                                
                                                                                                                                                                    
        client = kzalloc(sizeof(struct evdev_client), GFP_KERNEL);                                                                                                                                             
        if (!client)                                                                                                                                                                                           
                return -ENOMEM;                                                                                                                                                                                
                                                                                                                                                                    
        client->evdev = evdev;                                                                                                                                                                                 
        // ���evdev_client�ṹ������evdev->client_list��(���������¼�������ʱ����д�ýṹ�����ѽ��̶�ȡ)                                                                                                   
        list_add_tail(&client->node, &evdev->client_list);                                                                                                                                                     
                                                                                                                                                                    
        if (!evdev->open++ && evdev->exist) {                                                                                                                                                                  
                error = input_open_device(&evdev->handle);                                                                                                                                                     
                if (error) {                                                                                                                                                                                   
                        list_del(&client->node);                                                                                                                                                               
                        kfree(client);                                                                                                                                                                         
                        return error;                                                                                                                                                                          
                }                                                                                                                                                                                              
        }                                                                                                                                                                                                      
                                                                                                                                                                    
        file->private_data = client;//��ź�evdev_client�ṹ�����Ժ�ʹ��                                                                                                                                       
        return 0;                                                                                                                                                                                              
}                                                                                                                                                                                                              
                                                                                                                                                                    
                                                                                                                                                                    
static ssize_t evdev_read (struct file *file, char __user *buffer, size_t count, loff_t *ppos)                                                                                                                 
{                                                                                                                                                                                                              
        struct evdev_client *client = file->private_data;                                                                                                                                                      
        struct evdev *evdev = client->evdev;                                                                                                                                                                   
        int retval;                                                                                                                                                                                            
                                                                                                                                                                    
        if (count < evdev_event_size())//����ÿ�ζ�ȡ�����ݴ�С����һ����Ҫ��.                                                                                                                                 
                return -EINVAL;                                                                                                                                                                                
                                                                                                                                                                    
        if (client->head == client->tail && evdev->exist && (file->f_flags & O_NONBLOCK))//������û�����ݿɶ����豸�Ǵ��ڵ�,                                                                                   
                                                     // �������ΪNONBLOCK��ʽ����,��������.                                                                                                                     
                return -EAGAIN;                                                                                                                                                                                
                                                                                                                                                                    
        retval = wait_event_interruptible(evdev->wait,                                                                                                                                                         
                client->head != client->tail || !evdev->exist);//����ȴ����������ݿɶ����豸������(����ȥ)                                                                                                    
        if (retval)                                                                                                                                                                                            
                return retval;                                                                                                                                                                                 
                                                                                                                                                                    
        if (!evdev->exist)                                                                                                                                                                                     
                return -ENODEV;                                                                                                                                                                                
                                                                                                                                                                    
        while (client->head != client->tail && retval + evdev_event_size() <= count) {//���濪ʼ��ȡ����                                                                                                       
                                                                                                                                                                    
                struct input_event *event = (struct input_event *) client->buffer + client->tail;//��ȡ�����еĶ�ָ��                                                                                          
                                                                                                                                                                    
                if (evdev_event_to_user(buffer + retval, event))//�������ݸ��û�                                                                                                                               
                        return -EFAULT;                                                                                                                                                                        
                                                                                                                                                                    
                client->tail = (client->tail + 1) & (EVDEV_BUFFER_SIZE - 1);//���¶�ָ��                                                                                                                       
                retval += evdev_event_size();                                                                                                                                                                  
        }                                                                                                                                                                                                      
                                                                                                                                                                    
        return retval;                                                                                                                                                                                         
}                                                                                                                                                                                                              
                                                                                                                                                                    
//�Ǻ�,�����˰�,Ӧ�ó������������ȡ�����¼���^_^                                                                                                                                                                
//                                                                                                                                                                    
//######################################################################################################################################                                                                         
//��������gpio_keys��������������,ֻҪ�����������¼���ʱ�����ϲ�Ӧ�ó���㱨��ֵ����.                                                                                                                            
//����,����һЩ������豸(����led��)�������豸��˵(�������),�ϲ�Ӧ�ó���ͬ����������event������ȡ��ı���״̬.                                                                                                  
//�뿴���´���:                                                                                                                                                                                                  
//######################################################################################################################################                                                                         
//                                                                                                                                                                    
static ssize_t evdev_write (struct file *file, const char __user *buffer, size_t count, loff_t *ppos)                                                                                                          
{                                                                                                                                                                                                              
        struct evdev_client *client = file->private_data;                                                                                                                                                      
        struct evdev *evdev = client->evdev;                                                                                                                                                                   
        struct input_event event;                                                                                                                                                                              
        int retval = 0;                                                                                                                                                                                        
                                                                                                                                                                    
        if (!evdev->exist)                                                                                                                                                                                     
                return -ENODEV;                                                                                                                                                                                
                                                                                                                                                                    
        while (retval < count) {                                                                                                                                                                               
                                                                                                                                                                    
                if (evdev_event_from_user(buffer + retval, &event))//���û�����ȡ�¼��ṹ                                                                                                                      
                        return -EFAULT;                                                                                                                                                                        
                input_inject_event(&evdev->handle, event.type, event.code, event.value);//���ײ㷢���¼�                                                                                                       
                retval += evdev_event_size();                                                                                                                                                                  
        }                                                                                                                                                                                                      
                                                                                                                                                                    
        return retval;                                                                                                                                                                                         
}                                                                                                                                                                                                              
                                                                                                                                                                    
                                                                                                                                                                    
//*                                                                                                                                                                                                            
// * input_inject_event() - send input event from input handler                                                                                                                                                  
// * @handle: input handle to send event through                                                                                                                                                                 
// * @type: type of the event                                                                                                                                                                                    
// * @code: event code                                                                                                                                                                                           
// * @value: value of the event                                                                                                                                                                                  
// *                                                                                                                                                                                                             
// * Similar to input_event() but will ignore event if device is "grabbed" and handle                                                                                                                            
// * injecting event is not the one that owns the device.                                                                                                                                                        
                                                                                                                                                                                                             
void input_inject_event (struct input_handle *handle, unsigned int type, unsigned int code, int value)                                                                                                         
{                                                                                                                                                                                                              
        if (!handle->dev->grab || handle->dev->grab == handle)                                                                                                                                                 
                input_event(handle->dev, type, code, value);                                                                                                                                                   
}                                                                                                                                                                                                              
//EXPORT_SYMBOL(input_inject_event);                                                                                                                                                                             
                                                                                                                                                                    
//                                                                                                                                                                                                             
// * input_event() - report new input event                                                                                                                                                                      
// * @dev: device that generated the event                                                                                                                                                                       
// * @type: type of the event                                                                                                                                                                                    
// * @code: event code                                                                                                                                                                                           
// * @value: value of the event                                                                                                                                                                                  
// *                                                                                                                                                                                                             
// * This function should be used by drivers implementing various input devices                                                                                                                                  
// * See also input_inject_event()                                                                                                                                                                               
                                                                                                                                                                                                             
void input_event (struct input_dev *dev, unsigned int type, unsigned int code, int value)                                                                                                                      
{                                                                                                                                                                                                              
    struct input_handle *handle;                                                                                                                                                                               
                                                                                                                                                                    
    if (type > EV_MAX || !test_bit(type, dev->evbit))//�����жϸ��¼������Ƿ���Ч��Ϊ���豸������                                                                                                              
        return;                                                                                                                                                                                                
                                                                                                                                                                    
    add_input_randomness(type, code, value);                                                                                                                                                                   
                                                                                                                                                                    
    switch (type) {                                                                                                                                                                                            
                                                                                                                                                                    
        case EV_SYN:                                                                                                                                                                                           
            switch (code) {                                                                                                                                                                                    
                case SYN_CONFIG:                                                                                                                                                                               
                    if (dev->event)                                                                                                                                                                            
                        dev->event(dev, type, code, value);                                                                                                                                                    
                    break;                                                                                                                                                                                     
                                                                                                                                                                    
                case SYN_REPORT:                                                                                                                                                                               
                    if (dev->sync)                                                                                                                                                                             
                        return;                                                                                                                                                                                
                    dev->sync = 1;                                                                                                                                                                             
                    break;                                                                                                                                                                                     
            }                                                                                                                                                                                                  
            break;                                                                                                                                                                                             
                                                                                                                                                                    
.............................................................                                                                                                                                                  
        case EV_LED:                                                                                                                                                                                           
                                                                                                                                                                    
            if (code > LED_MAX || !test_bit(code, dev->ledbit) || !!test_bit(code, dev->led) == value)                                                                                                         
                return;                                                                                                                                                                                        
                                                                                                                                                                    
            change_bit(code, dev->led);                                                                                                                                                                        
                                                                                                                                                                    
            if (dev->event)                                                                                                                                                                                    
                dev->event(dev, type, code, value);                                                                                                                                                            
                                                                                                                                                                    
            break;                                                                                                                                                                                             
                                                                                                                                                                    
                                                                                                                                                                    
    if (type != EV_SYN)                                                                                                                                                                                        
        dev->sync = 0;                                                                                                                                                                                         
                                                                                                                                                                    
    if (dev->grab)                                                                                                                                                                                             
        dev->grab->handler->event(dev->grab, type, code, value);                                                                                                                                               
    else                                                                                                                                                                                                       
       //                                                                                                                                                                                                     
       //  * ѭ���������д�����豸��handle(event,mouse,ts,joy��),                                                                                                                                               
       //  * ����н��̴�����Щhandle(���ж�д),��������Ӧ��event�ӿ������㱨�������¼�.                                                                                                                     
                                                                                                                                                                                                             
        list_for_each_entry(handle, &dev->h_list, d_node)                                                                                                                                                      
            if (handle->open)                                                                                                                                                                                  
                handle->handler->event(handle, type, code, value);                                                                                                                                             
}                                                                                                                                                                                                              
//EXPORT_SYMBOL(input_event);                                                                                                                                                                                    
///                                                                                                                                                                    
///ע:                                                                                                                                                                                                            
///    ���ڼ򵥵�gpio_keys������û��ע���Լ���event�ӿ�,��ȻҲû�ж���LED�ƵĴ���,��event��ֻ�Ǽ򵥵����ϲ�㱨�����¼�(event��Ҳ�����ܰ��㴦�����led�豸,�԰�),�������ͨ��������ϵͳ����LED�Ĳ�����ʱ��ȥ�о�. 
///    (����豸LED�Ʋ�������������豸gpio_key��һ����.��Ȼ,�������ͨ�����gpio_keys�豸������led�ƵĻ�,�����޸����gpio_keys����,��ϸ�ɲο�driver/input/keyboardĿ¼�µ�����)                                  
///                                                                                                                                                                    
///                                                                                                                                                                                                               
///                                                                                                                                                                    
///�����䡿                                                                                                                                                                                                       
///                                                                                                                                                                    
///����û���жϹ��ܵ�gpio��������Ҫһ����ʱ������ѯ������״̬��������ϵͳ��׼��������һ���ṹ�����ڴ��ּ��̷�ʽ��                                                                                                 
///                                                                                                                                                                    
///struct input_polled_dev��                                                                                                                                                                                      
///                                                                                                                                                                    
///��ʹ��input_allocate_polled_device();����ʼ����ָ�롣                                                                                                                                                          
///                                                                                                                                                                    
///                                                                                                                                                                    
///���������Ƚ���Ҫ�ĳ�Ա��                                                                                                                                                                                       
///                                                                                                                                                                    
///poll����ѯ�ĺ���                                                                                                                                                                                               
///                                                                                                                                                                    
///poll_interval����ѯ������Ժ���Ϊ��λ��                                                                                                                                                                        
///                                                                                                                                                                    
//                                                                                                                                                                    
                                                                                                                                                                    
                                                                                                                                                                    
                                                                                                                                                                    
//��󣬵���input_register_polled_device������ע���������                                                                                                                                                       