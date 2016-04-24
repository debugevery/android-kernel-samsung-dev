
//【转+补充】输入子系统--event层分析，gpio 键盘驱动 .                                                                                                                                                            
//分类： linux内核移植/驱动 2009-09-08 09:32 1850人阅读 评论(0) 收藏 举报                                                                                                                                        
//来自：http://www.cnitblog.com/luofuchong/archive/2009/08/03/36157.html                                                                                                                                         
//                                                                                                                                                                    
//                                                                                                                                                                                                               
//                                                                                                                                                                    
//#####################################################################################################                                                                                                          
//早前曾研究了一下输入子系统的原理,给人的感觉是输入子系统很复杂.但其实内核开发者在这方面已经做得很完善了,                                                                                                        
//输入子系统虽然错综复杂,但是只要我们领会了输入子系统的一些设计思想后,我们要使用它并非难事.                                                                                                                      
//                                                                                                                                                                    
//以下以内核自带的gpio_keys驱动为例,介绍输入子系统的使用.                                                                                                                                                        
//主要的原因是gpio_keys驱动比较简单易懂,另外不是没个人都有触摸屏,但键盘的话相信每一块开发板上都配有吧^_^                                                                                                         
//                                                                                                                                                                    
//按照以前的习惯,先从下到上的研究底层驱动是如何提交输入事件的:                                                                                                                                                   
//#####################################################################################################                                                                                                          
//                                                                                                                                                                    
//drivers/input/keyboard/gpio_keys.c:                                                                                                                                                                            
    
    
//===========================打开注释回车    /*================================                                                                                                                                                                       

static int __devinit gpio_keys_probe (struct platform_device *pdev)                                                                                                                                            
{                                                                                                                                                                                                              
    struct gpio_keys_platform_data *pdata = pdev->dev.platform_data;                                                                                                                                           
    struct input_dev *input;                                                                                                                                                                                   
    int i, error;                                                                                                                                                                                              
                                                                                                                                                                    
    input = input_allocate_device();//申请input_dev结构                                                                                                                                                        
    if (!input)                                                                                                                                                                                                
        return -ENOMEM;                                                                                                                                                                                        
                                                                                                                                                                    
    platform_set_drvdata(pdev, input);//把input_dev结构放好(以后方便调用)                                                                                                                                      
                                                                                                                                                                    
    input->evbit[0] = BIT(EV_KEY);//目前event的类型不操作32,所以你会看到对于evbit数组的操作都是对evbit[0]中的位来进行操作.                                                                                     
                                                                                                                                                                    
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
                                                                                                                                                                    
       // 根据用户所指定的gpio_keys来申请中断和注册中断处理函数                                                                                                                                             
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
                                                                                                                                                                    
    error = input_register_device(input);//注册输入设备,并和对应的handler处理函数挂钩                                                                                                                          
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
//提到input_dev结构,以下谈一下我对于它的理解:                                                                                                                                                                    
struct input_dev {                                                                                                                                                                                             
                                                                                                                                                                    
    void *private;                                                                                                                                                                                             
                                                                                                                                                                    
    const char *name;                                                                                                                                                                                          
    const char *phys;                                                                                                                                                                                          
    const char *uniq;                                                                                                                                                                                          
    struct input_id id;                                                                                                                                                                                        
                                                                                                                                                                    
   //                                                                                                                                                                                                         
   //  * 根据各种输入信号的类型来建立类型为unsigned long 的数组,                                                                                                                                                 
   //  * 数组的每1bit代表一种信号类型,                                                                                                                                                                           
   //  * 内核中会对其进行置位或清位操作来表示时间的发生和被处理.                                                                                                                                                 
                                                                                                                                                                                                             
                                                                                                                                                                    
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
                                                                                                                                                                    
// 记录本设备对于哪些事件感兴趣(对其进行处理)                                                                                                                                                                
void input_set_capability (struct input_dev *dev, unsigned int type, unsigned int code)                                                                                                                        
{                                                                                                                                                                                                              
    switch (type) {                                                                                                                                                                                            
    case EV_KEY:                                                                                                                                                                                               
        __set_bit(code, dev->keybit);//比如按键,应该对哪些键值的按键进行处理(对于其它按键不予理睬)                                                                                                             
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
                                                                                                                                                                    
    __set_bit(type, dev->evbit);//感觉和前面重复了(前面一经配置过一次了)                                                                                                                                       
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
                                                                                                                                                                    
                if (irq == gpio_to_irq(gpio)) {//判断哪个键被按了?                                                                                                                                             
                        unsigned int type = button->type ?: EV_KEY;                                                                                                                                            
                        int state = (gpio_get_value(gpio) ? 1 : 0) ^ button->active_low;//记录按键状态                                                                                                         
                                                                                                                                                                    
                        input_event(input, type, button->code, !!state);//汇报输入事件                                                                                                                         
                        input_sync(input);//等待输入事件处理完成                                                                                                                                               
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
                                                                                                                                                                    
    if (type > EV_MAX || !test_bit(type, dev->evbit))//首先判断该事件类型是否有效且为该设备所接受                                                                                                              
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
           //  * 这里需要满足几个条件:                                                                                                                                                                           
           //  * 1: 键值有效(不超出定义的键值的有效范围)                                                                                                                                                         
           //  * 2: 键值为设备所能接受(属于该设备所拥有的键值范围)                                                                                                                                               
           //  * 3: 按键状态改变了                                                                                                                                                                               
           //                                                                                                                                                                                                  
                                                                                                                                                                    
            if (code > KEY_MAX || !test_bit(code, dev->keybit) || !!test_bit(code, dev->key) == value)                                                                                                         
                return;                                                                                                                                                                                        
                                                                                                                                                                    
            if (value == 2)                                                                                                                                                                                    
                break;                                                                                                                                                                                         
                                                                                                                                                                    
            change_bit(code, dev->key);//改变对应按键的状态                                                                                                                                                    
                                                                                                                                                                    
           // 如果你希望按键未释放的时候不断汇报按键事件的话需要以下这个(在简单的gpio_keys驱动中不需要这个,暂时不去分析)                                                                                    
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
       //  * 循环调用所有处理该设备的handle(event,mouse,ts,joy等),                                                                                                                                               
       //  * 如果有进程打开了这些handle(进行读写),则调用其对应的event接口向气汇报该输入事件.                                                                                                                     
                                                                                                                                                                                                             
        list_for_each_entry(handle, &dev->h_list, d_node)                                                                                                                                                      
            if (handle->open)                                                                                                                                                                                  
                handle->handler->event(handle, type, code, value);                                                                                                                                             
}                                                                                                                                                                                                              
//EXPORT_SYMBOL(input_event);                                                                                                                                                                                    
                                                                                                                                                                    
                                                                                                                                                                    
//#########################################################################                                                                                                                                      
//好了,下面再来研究一下event层对于input层报告的这个键盘输入事件是如何来处理的.                                                                                                                                   
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
                 // 遍厉client_list链表中的client结构(代表些打开evdev的进程(个人理解^_^))                                                                                                                   
                list_for_each_entry(client, &evdev->client_list, node) {                                                                                                                                       
                           // 填充代表该输入信号的struct input_event结构(事件,类型,键码,键值)                                                                                                               
                        do_gettimeofday(&client->buffer[client->head].time);                                                                                                                                   
                        client->buffer[client->head].type = type;                                                                                                                                              
                        client->buffer[client->head].code = code;                                                                                                                                              
                        client->buffer[client->head].value = value;                                                                                                                                            
                           // 更新写指针                                                                                                                                                                    
                        client->head = (client->head + 1) & (EVDEV_BUFFER_SIZE - 1);                                                                                                                           
                                                                                                                                                                    
                        kill_fasync(&client->fasync, SIGIO, POLL_IN);//通知调用input_sync的进程:输入事件经已处理完毕(通知底层).                                                                                
                }                                                                                                                                                                                              
                                                                                                                                                                    
        wake_up_interruptible(&evdev->wait);//唤醒睡眠在evdev->wait等待队列等待输入信息的进程(通知上层).                                                                                                       
}                                                                                                                                                                                                              
                                                                                                                                                                    
//###################################################################################                                                                                                                            
//好了,至此一个按键的输入事件处理完毕,现在再来从上到上的来看看用户是如何获取这个输入事件的.                                                                                                                      
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
        // 添加evdev_client结构到链表evdev->client_list中(好让输入事件到来的时候填写该结构并唤醒进程读取)                                                                                                   
        list_add_tail(&client->node, &evdev->client_list);                                                                                                                                                     
                                                                                                                                                                    
        if (!evdev->open++ && evdev->exist) {                                                                                                                                                                  
                error = input_open_device(&evdev->handle);                                                                                                                                                     
                if (error) {                                                                                                                                                                                   
                        list_del(&client->node);                                                                                                                                                               
                        kfree(client);                                                                                                                                                                         
                        return error;                                                                                                                                                                          
                }                                                                                                                                                                                              
        }                                                                                                                                                                                                      
                                                                                                                                                                    
        file->private_data = client;//存放好evdev_client结构方便以后使用                                                                                                                                       
        return 0;                                                                                                                                                                                              
}                                                                                                                                                                                                              
                                                                                                                                                                    
                                                                                                                                                                    
static ssize_t evdev_read (struct file *file, char __user *buffer, size_t count, loff_t *ppos)                                                                                                                 
{                                                                                                                                                                                                              
        struct evdev_client *client = file->private_data;                                                                                                                                                      
        struct evdev *evdev = client->evdev;                                                                                                                                                                   
        int retval;                                                                                                                                                                                            
                                                                                                                                                                    
        if (count < evdev_event_size())//对于每次读取的数据大小是有一定的要求.                                                                                                                                 
                return -EINVAL;                                                                                                                                                                                
                                                                                                                                                                    
        if (client->head == client->tail && evdev->exist && (file->f_flags & O_NONBLOCK))//缓存中没有数据可读且设备是存在的,                                                                                   
                                                     // 如果设置为NONBLOCK方式来读,立即返回.                                                                                                                     
                return -EAGAIN;                                                                                                                                                                                
                                                                                                                                                                    
        retval = wait_event_interruptible(evdev->wait,                                                                                                                                                         
                client->head != client->tail || !evdev->exist);//否则等待缓存有数据可读或设备不存在(被移去)                                                                                                    
        if (retval)                                                                                                                                                                                            
                return retval;                                                                                                                                                                                 
                                                                                                                                                                    
        if (!evdev->exist)                                                                                                                                                                                     
                return -ENODEV;                                                                                                                                                                                
                                                                                                                                                                    
        while (client->head != client->tail && retval + evdev_event_size() <= count) {//下面开始读取数据                                                                                                       
                                                                                                                                                                    
                struct input_event *event = (struct input_event *) client->buffer + client->tail;//获取缓存中的读指针                                                                                          
                                                                                                                                                                    
                if (evdev_event_to_user(buffer + retval, event))//返回数据给用户                                                                                                                               
                        return -EFAULT;                                                                                                                                                                        
                                                                                                                                                                    
                client->tail = (client->tail + 1) & (EVDEV_BUFFER_SIZE - 1);//更新读指针                                                                                                                       
                retval += evdev_event_size();                                                                                                                                                                  
        }                                                                                                                                                                                                      
                                                                                                                                                                    
        return retval;                                                                                                                                                                                         
}                                                                                                                                                                                                              
                                                                                                                                                                    
//呵呵,看到了吧,应用程序就是这样获取输入事件的^_^                                                                                                                                                                
//                                                                                                                                                                    
//######################################################################################################################################                                                                         
//本来对于gpio_keys这样的驱动程序,只要当发生按键事件的时候向上层应用程序汇报键值即可.                                                                                                                            
//不过,对于一些带输出设备(例如led灯)的输入设备来说(例如键盘),上层应用程序同样可以利用event层来读取或改变其状态.                                                                                                  
//请看以下代码:                                                                                                                                                                                                  
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
                                                                                                                                                                    
                if (evdev_event_from_user(buffer + retval, &event))//从用户处获取事件结构                                                                                                                      
                        return -EFAULT;                                                                                                                                                                        
                input_inject_event(&evdev->handle, event.type, event.code, event.value);//往底层发送事件                                                                                                       
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
                                                                                                                                                                    
    if (type > EV_MAX || !test_bit(type, dev->evbit))//首先判断该事件类型是否有效且为该设备所接受                                                                                                              
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
       //  * 循环调用所有处理该设备的handle(event,mouse,ts,joy等),                                                                                                                                               
       //  * 如果有进程打开了这些handle(进行读写),则调用其对应的event接口向气汇报该输入事件.                                                                                                                     
                                                                                                                                                                                                             
        list_for_each_entry(handle, &dev->h_list, d_node)                                                                                                                                                      
            if (handle->open)                                                                                                                                                                                  
                handle->handler->event(handle, type, code, value);                                                                                                                                             
}                                                                                                                                                                                                              
//EXPORT_SYMBOL(input_event);                                                                                                                                                                                    
///                                                                                                                                                                    
///注:                                                                                                                                                                                                            
///    鉴于简单的gpio_keys驱动中没有注册自己的event接口,当然也没有对于LED灯的处理,而event层只是简单的向上层汇报输入事件(event层也不可能帮你处理你的led设备,对吧),所以这个通过输入子系统控制LED的部分暂时不去研究. 
///    (输出设备LED灯不属于这个输入设备gpio_key的一部分.当然,如果你想通过这个gpio_keys设备来控制led灯的话,可以修改这个gpio_keys驱动,详细可参考driver/input/keyboard目录下的驱动)                                  
///                                                                                                                                                                    
///                                                                                                                                                                                                               
///                                                                                                                                                                    
///【补充】                                                                                                                                                                                                       
///                                                                                                                                                                    
///对于没有中断功能的gpio，可能需要一个定时器来轮询其输入状态，不过，系统还准备了另外一个结构体用于此种键盘方式：                                                                                                 
///                                                                                                                                                                    
///struct input_polled_dev；                                                                                                                                                                                      
///                                                                                                                                                                    
///并使用input_allocate_polled_device();来初始化其指针。                                                                                                                                                          
///                                                                                                                                                                    
///                                                                                                                                                                    
///其中两个比较重要的成员：                                                                                                                                                                                       
///                                                                                                                                                                    
///poll：查询的函数                                                                                                                                                                                               
///                                                                                                                                                                    
///poll_interval：查询间隔，以毫秒为单位。                                                                                                                                                                        
///                                                                                                                                                                    
//                                                                                                                                                                    
                                                                                                                                                                    
                                                                                                                                                                    
                                                                                                                                                                    
//最后，调用input_register_polled_device（）来注册该驱动。                                                                                                                                                       