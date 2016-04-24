Linux��������֮��-�����豸
2012��03��10�� ��Դ�������� ���ߣ����� �����48 �����壺�� �� С�� ��Ҫ����(0)

�����µ����� ��Linux�����а��޷�������廨���ŵ��豸����Ϊ�����豸(��miscdevice�ṹ�����)��miscdevice����һ�����豸��MISC_MAJOR(��10)�������豸�Ų�ͬ�����е�miscdevice�豸�γ���һ���������豸����ʱ�ں˸��ݴ��豸�Ų��Ҷ�Ӧ��miscdevice�豸��Ȼ�������file_operations�ṹ��ע����ļ������ӿڽ��в��������ں�����struct miscdevice��ʾmiscdevice�豸��Ȼ�������file_operations��
 ��Linux�����а��޷�������廨���ŵ��豸����Ϊ�����豸(��miscdevice�ṹ�����)��miscdevice����һ�����豸��MISC_MAJOR(��10)�������豸�Ų�ͬ�����е�miscdevice�豸�γ���һ���������豸����ʱ�ں˸��ݴ��豸�Ų��Ҷ�Ӧ��miscdevice�豸��Ȼ�������file_operations�ṹ��ע����ļ������ӿڽ��в��������ں�����struct miscdevice��ʾmiscdevice�豸��Ȼ�������file_operations�ṹ��ע����ļ������ӿڽ��в�����miscdevice��APIʵ����drivers/char/misc.c�С� 

�±�����������豸�Ľṹ�壺

 

view plaincopy to clipboardprint? 
struct miscdevice  {       
    int minor;                               //���豸��    
    const char *name;                        //�豸������       
    const struct file_operations *fops;     //�ļ�����     
    struct list_head list;                  //misc_list������ͷ   
    struct device *parent;                  //���豸(Linux�豸ģ���еĶ����ˣ�����)       
    struct device *this_device;             //��ǰ�豸����device_create�ķ���ֵ���±߻ῴ��   
};   
 

Ȼ��������misc��ϵͳ�ĳ�ʼ��������

 

view plaincopy to clipboardprint? 
static int __init misc_init(void)    
{    
    int err;    
   
#ifdef CONFIG_PROC_FS    
    /*����һ��proc�����*/   
    proc_create("misc", 0, NULL, &misc_proc_fops);                    
#endif    
    /*��/sys/class/Ŀ¼�´���һ����Ϊmisc����*/   
    misc_class = class_create(THIS_MODULE, "misc");    
    err = PTR_ERR(misc_class);    
    if (IS_ERR(misc_class))    
        goto fail_remove;    
    
    err = -EIO;   
    /*ע���豸�������豸�����豸��ΪMISC_MAJOR��Ϊ10���豸��Ϊmisc��misc_fops�ǲ��������ļ���*/    
    if (register_chrdev(MISC_MAJOR,"misc",&misc_fops))    
        goto fail_printk;    
    return 0;    
    
fail_printk:    
    printk("unable to get major %d for misc devices ", MISC_MAJOR);    
    class_destroy(misc_class);    
fail_remove:    
    remove_proc_entry("misc", NULL);    
    return err;    
}    
/*misc��Ϊһ����ϵͳ��ע�ᵽlinux�ں���*/   
subsys_initcall(misc_init);    
 

�±���register_chrdev������ʵ�֣�

 

view plaincopy to clipboardprint? 
int register_chrdev(unsigned int major, const char *name,   
            const struct file_operations *fops)   
{   
    struct char_device_struct *cd;   
    struct cdev *cdev;   
    char *s;   
    int err = -ENOMEM;   
    /*���豸����10�����豸��Ϊ��0��ʼ������256���豸*/   
    cd = __register_chrdev_region(major, 0, 256, name);   
    if (IS_ERR(cd))   
        return PTR_ERR(cd);   
    /*�����ַ��豸*/   
    cdev = cdev_alloc();   
    if (!cdev)   
        goto out2;   
   
    cdev->owner = fops->owner;   
    cdev->ops = fops;   
    /*Linux�豸ģ���е�,����kobject������*/   
    kobject_set_name(&cdev->kobj, "%s", name);   
    for (s = strchr(kobject_name(&cdev->kobj),'/'); s; s = strchr(s, '/'))   
        *s = '!';   
    /*������ַ��豸ע�ᵽϵͳ��*/      
    err = cdev_add(cdev, MKDEV(cd->major, 0), 256);   
    if (err)   
        goto out;   
   
    cd->cdev = cdev;   
   
    return major ? 0 : cd->major;   
out:   
    kobject_put(&cdev->kobj);   
out2:   
    kfree(__unregister_chrdev_region(cd->major, 0, 256));   
    return err;   
}   
 

����������豸�Ĳ��������ļ��ϣ�

 

view plaincopy to clipboardprint? 
static const struct file_operations misc_fops = {    
    .owner      = THIS_MODULE,    
    .open       = misc_open,    
};    
 

���Կ�������ֻ��һ���򿪺������û���miscdevice�豸��ͨ�����豸�Ŷ�Ӧ�Ĵ򿪺�����������������ҵ����豸�Ŷ�Ӧ����Ӧ�ľ����豸��open����������ʵ�����£�

 

view plaincopy to clipboardprint? 
static int misc_open(struct inode * inode, struct file * file)    
{    
    int minor = iminor(inode);    
    struct miscdevice *c;    
    int err = -ENODEV;    
    const struct file_operations *old_fops, *new_fops = NULL;    
       
    lock_kernel();    
    mutex_lock(&misc_mtx);    
    /*�ҵ����豸�Ŷ�Ӧ�Ĳ����������ϣ���new_fopsָ����������豸�Ĳ�����������*/   
    list_for_each_entry(c, &misc_list, list) {    
        if (c->minor == minor) {    
            new_fops = fops_get(c->fops);           
            break;    
        }    
    }    
            
    if (!new_fops) {    
        mutex_unlock(&misc_mtx);    
        /*���û���ҵ������������������豸�Ŷ�Ӧ��ģ��*/   
        request_module("char-major-%d-%d", MISC_MAJOR, minor);    
        mutex_lock(&misc_mtx);    
        /*���±���misc_list�������û���ҵ����˳���������new_fopsָ����������豸�Ĳ�����������*/   
        list_for_each_entry(c, &misc_list, list) {    
            if (c->minor == minor) {    
                new_fops = fops_get(c->fops);    
                break;    
            }    
        }    
        if (!new_fops)    
            goto fail;    
    }    
    
    err = 0;    
    /*����ɴ򿪺����ĵ�ַ*/   
    old_fops = file->f_op;    
    /*�����豸�ŵĲ�����������ָ��ָ������豸�Ĳ�����������*/   
    file->f_op = new_fops;    
    if (file->f_op->open) {   
        /*ʹ�þ����豸�Ĵ򿪺������豸*/    
        err=file->f_op->open(inode,file);    
        if (err) {    
            fops_put(file->f_op);    
            file->f_op = fops_get(old_fops);    
        }    
    }    
    fops_put(old_fops);    
fail:    
    mutex_unlock(&misc_mtx);    
    unlock_kernel();    
    return err;    
}    
��������misc��ϵͳ�����ṩ��������Ҫ��API,misc_register,misc_deregister�� 
 

 

view plaincopy to clipboardprint? 
int misc_register(struct miscdevice * misc)    
{    
    struct miscdevice *c;    
    dev_t dev;    
    int err = 0;    
    /*��ʼ��misc_list����*/   
    INIT_LIST_HEAD(&misc->list);    
    mutex_lock(&misc_mtx);    
    /*����misc_list������������豸����ǰ��û�б��ù���������豸���ѱ�ռ�����˳�*/   
    list_for_each_entry(c, &misc_list, list) {    
        if (c->minor == misc->minor) {    
            mutex_unlock(&misc_mtx);    
            return -EBUSY;    
        }    
    }    
    /*���Ƿ�����Ҫ��̬������豸��*/   
    if (misc->minor == MISC_DYNAMIC_MINOR) {   
        /*  
         *#define DYNAMIC_MINORS 64 /* like dynamic majors */   
         *static unsigned char misc_minors[DYNAMIC_MINORS / 8];    
         *�������һ�����豸�ŵ�λͼ��һ��64λ���±��Ǳ���ÿһλ��   
         *�����λΪ0����ʾû�б�ռ�У�����ʹ�ã�Ϊ1��ʾ��ռ�á�          
         */   
        int i = DYNAMIC_MINORS;    
        while (--i >= 0)    
            if ( (misc_minors[i>>3] & (1 << (i&7))) == 0)    
                break;    
        if (i<0) {    
            mutex_unlock(&misc_mtx);    
            return -EBUSY;    
        }    
        /*�õ�������豸��*/   
        misc->minor = i;                                            
    }    
    /*����λͼ����ӦλΪ1*/   
    if (misc->minor < DYNAMIC_MINORS)    
        misc_minors[misc->minor >> 3] |= 1 << (misc->minor & 7);    
    /*������豸��*/   
    dev = MKDEV(MISC_MAJOR, misc->minor);    
    /*��/dev�´����豸�ڵ㣬�������Щ��������û����ʽ����device_create��ȴ�������豸�ڵ��ԭ��*/   
    misc->this_device = device_create(misc_class, misc->parent, dev, NULL,    
                      "%s", misc->name);    
    if (IS_ERR(misc->this_device)) {    
        err = PTR_ERR(misc->this_device);    
        goto out;    
    }    
    
    /*   
     * Add it to the front, so that later devices can "override"   
     * earlier defaults   
     */    
    /*�����miscdevice��ӵ�misc_list������*/   
    list_add(&misc->list, &misc_list);    
 out:    
    mutex_unlock(&misc_mtx);    
    return err;    
}    
 

�����miscdevice��ж�غ�����

 

view plaincopy to clipboardprint? 
int misc_deregister(struct miscdevice *misc)    
{    
    int i = misc->minor;    
    
    if (list_empty(&misc->list))    
        return -EINVAL;    
    
    mutex_lock(&misc_mtx);    
    /*��misc_list������ɾ��miscdevice�豸*/   
    list_del(&misc->list);     
    /*ɾ���豸�ڵ�*/                             
    device_destroy(misc_class, MKDEV(MISC_MAJOR, misc->minor));              
    if (i < DYNAMIC_MINORS && i>0) {   
        /*�ͷ�λͼ��Ӧλ*/    
        misc_minors[i>>3] &= ~(1 << (misc->minor & 7));    
    }    
    mutex_unlock(&misc_mtx);    
    return 0;    
}    
 

�ܽ�һ��miscdevice������ע���ж�����̣�
misc_register:ƥ����豸��->�ҵ�һ��û��ռ�õĴ��豸��(�����Ҫ��̬����Ļ�)->�����豸��->�����豸�ļ�->miscdevice�ṹ����ӵ�misc_list�����С�
misc_deregister:��mist_list��ɾ��miscdevice->ɾ���豸�ļ�->λͼλ���㡣


