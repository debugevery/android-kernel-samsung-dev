// Linux��Щ�¶�֮����Sysfs                                                                                   
//                                                                                                            
//                                                                                                            
//                                                                                                            
//                                                                                                            
//                                                                                                            
// Linux��Щ�¶�                                                                                              
// ϵ�д���                                                                                                   
// ֮                                                                                                         
// ����Sysfs                                                                                                  
//                                                                                                            
//                                                                                                            
//                                                                                                            
//                                                                                                            
//                                                                                                            
//                                                                                                            
//                                                                                                            
//                                                                                                            
// ��ԭ��Ϊblog.csdn.net/fudan_abc �ϵġ�linux ��Щ�¶�֮����Sysfs�������������µĻ�������������Ŀ���        
// ���������ͣ�Ҳ����email ��ilttv.cn@gmail.com                                                               
//                                                                                                            
// �� 1  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                               
// Ŀ¼                                                                                                       
//                                                                                                            
// ����.....................................................3                                                 
// Sysfs��̽................................................3                                                 
// Linus�豸�ײ�ģ��........................................5                                                 
// �豸ģ���ϲ�����.........................................8                                                 
// ����һlddbus ............................................10                                                
// ������sculld ............................................14                                                
// �ļ�ϵͳ................................................17                                                 
// Dentry��inode ...........................................19                                                
// һ��ɢɢ������pathwalk ..................................23                                                
// Sysfs�ļ�ϵͳģ��.......................................25                                                 
// Sysfs����Ŀ¼...........................................27                                                 
// Sysfs������ͨ�ļ�.......................................31                                                 
// Sysfs�����ļ�������.....................................33                                                 
// Sysfs������ͨ�ļ�����...................................36                                                 
// ���....................................................40                                                 
//                                                                                                            
// �� 2  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                               
//                                                                                                            
// ����                                                                                                       
//       ���������˼��Ȼ����д�������ĵײ����������塣��˵�ҽ���linux                                      
// ����Ҳ��2���ˣ���ѧϰlinux��ȫ����Ȥ����Ϊ�Ҿ�����linux�ȽϿᣬ�Ƚ�                                        
// �������꿴��һƪ��linux����windows�����£������Ժ�������Ѫ���ڣ�����                                       
// �Ͱ�windows��ɾ�ˡ���������ʵ�ڲ�ϰ�ߣ���Ϊû���������ˡ�����֮�£�ֻ                                      
// ����װ����windows����ʱ�Ҿ���һ��Ը������һ��Ҫ������Ѷ�ڲ�����Ӧë��                                      
// ϯ���٣���ȫ����linux�û�Ҳ�ܶ��ϵ�������ѧ����ḻ��ʣ���ֻ��һ��                                      
// ���ã�������ʱ���ԣ��һ��ʱ��Ϳ���linux����鼮�������Ǿ�����������                                    
// ÿ�ο���һ���׶ξͷ����ˡ��ȸ���һ��ʱ�䣬�������ã������ˣ�ֻ�Ǵ��֪                                     
// ������ôһ���¡������ܽ�ѧϰlinux�Ĺؼ��ǣ����ö࿴����֮�Ժ㡣��Ҳ��                                      
// �Լ���linux�ں˵��ĵ�д������Ӧ�����˼׵ĺ��٣�����ȥ����Ϸ����Ƭ����                                      
// BBS�������羲��������̤̤ʵʵ�����飬д�����¡��������������꣬��ȱ                                      
// ��̤̤ʵʵ��������ˡ�                                                                                     
//         ����ҪдһЩ�ļ�ϵͳ��صģ����ldd3(linux device driver 3)��                                      
// ��ʾ������(��Ҫ��lddbus��sculld�ļ���)�����������ļ�ϵͳsysfs��ʹ��                                        
// ���ں���2.6.10��                                                                                           
// Ŀ�꣺����豸ģ�ͺ�sysfs�ļ�ϵͳ                                                                          
// ��ӭ��λ���ѷ��ʼ�ָ�������ۣ�������                                                                       
// linux.fans.afu@gmail.com                                                                                   
// ֪�к�һ������������˵��                                                                                   
//                                                                                                            
// Sysfs��̽                                                                                                  
//                                                                                                            
// "sysfs is a ram-based filesystem initially based on ramfs. It provides                                     
// a means                                                                                                    
// to export kernel data structures, their attributes, and the linkages                                       
// between them to                                                                                            
// userspace.�� --- documentation/filesystems/sysfs.txt                                                       
// �����Ȱ�documentation/filesystems/sysfs.txt��һ�顣�ĵ����ֶ���������                                      
// �������������ˡ�Sysfs�ļ�ϵͳ��һ��������proc�ļ�ϵͳ�������ļ�ϵͳ��                                      
// �� 3  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                               
// ���ڽ�ϵͳ�е��豸��֯�ɲ�νṹ�������û�ģʽ�����ṩ��ϸ���ں����ݽ�                                     
// ����Ϣ��                                                                                                   
//                                                                                                            
// ȥ/sys��һ����                                                                                             
// localhost:/sys#ls /sys/                                                                                    
// block/ bus/ class/ devices/ firmware/ kernel/ module/ power/                                               
// BlockĿ¼���������еĿ��豸                                                                                
// DevicesĿ¼������ϵͳ���е��豸���������豸�ҽӵ�����������֯�ɲ�ν�                                      
// ��                                                                                                         
// BusĿ¼������ϵͳ�����е���������                                                                          
// DriversĿ¼�������ں���������ע����豸��������                                                            
// ClassĿ¼��ϵͳ�е��豸���ͣ��������豸�������豸�ȣ�                                                      
// sys�����Ŀ¼���ļ���ӳ����̨������ϵͳ״��������bus��                                                     
// localhost:/sys/bus#ls                                                                                      
// i2c/ ide/ pci/ pci express/ platform/ pnp/ scsi/ serio/ usb/                                               
// ����Ͱ�����ϵͳ�õ���һϵ�����ߣ�����pci, ide, scsi, usb�ȵȡ�������                                      
// ������usb�ļ����з�����ʹ�õ�U�̣�USB������Ϣ��                                                          
// ����Ҫ����һ���ļ�ϵͳ������Ҫ֪������ļ�ϵͳ����Ϣ��Դ�������ν��                                     
// Ϣ��Դ��ָ�ļ���֯��ŵĵص㡣���磬���ǹ���һ��������                                                     
// mount -t vfat /dev/hda2 /mnt/C                                                                             
// ���Ǿ�֪��������/mnt/C�µ���һ��vfat���͵��ļ�ϵͳ��������Ϣ��Դ����                                       
// ��һ��Ӳ�̵ĵ�2��������                                                                                    
// ���ǣ�����ܸ���û��ȥ���Ĺ�sysfs�Ĺ��ع��̣��������������صġ�                                            
// mount -t sysfs sysfs /sys                                                                                  
// ms������������Ϣ��Դ���ġ�sysfs��һ�������ļ�ϵͳ����û��һ��ʵ�ʴ��                                      
// �ļ��Ľ��ʡ��ϵ��������ˡ������֮��sysfs����Ϣ��Դ��kobject��ν�                                       
// ������һ��sysfs�ļ������Ƕ�̬�Ĵ�kobject�ṹ��ȡ��Ϣ�������ļ���                                           
// ���ԣ����ȣ���Ҫ�Ƚ�һ��sysfs�ļ�ϵͳ����Ϣ��Դ -- kobject��νṹ��                                       
// kobject��νṹ����linux���豸ģ�͡�                                                                       
// Ī��ǰ·��֪��������˭�˲�ʶ���� �ơ����ʡ� �𶭴�                                                         
//                                                                                                            
// �� 4  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                               
// Linus�豸�ײ�ģ��                                                                                          
// ����linux�豸ģ��������һЩ��������Щ�����Ҿ������������壬�������޸�                                      
// ������                                                                                                   
// ��1 Kobject                                                                                                
// Kobject ��Linux 2.6������µ��豸������ƣ����ں�����struct kobject                                        
// ��ʾ��ͨ��������ݽṹʹ�����豸�ڵײ㶼����ͳһ�Ľӿڣ�kobject�ṩ��                                      
// ���Ķ�������ǹ���Linux2.6�豸ģ�͵ĺ��Ľṹ������sysfs�ļ�ϵͳ��                                        
// �ܹ�����ÿ�����ں���ע���kobject���󶼶�Ӧ��sysfs�ļ�ϵͳ�е�һ��Ŀ                                       
// ¼��Kobject������豸ģ�͵Ļ����ṹ��������C++�еĻ��࣬��Ƕ���ڸ���                                       
// �Ķ���Ķ�����--��ν������--���������豸ģ�͵��������bus,devices,                                         
// drivers ���ǵ��͵���������Щ��������ͨ��kobject���������ˣ��γ���һ��                                      
// ��״�ṹ�������״�ṹ����/sys���Ӧ��                                                                     
// kobject �ṹΪһЩ������ݽṹ����ϵͳ�ṩ�˻����Ķ����������������                                     
// ���ܵ��ظ�ʵ�֡���Щ���ܰ���                                                                               
// - �������ü���.                                                                                            
// - ά����������(����).                                                                                      
// - ��������.                                                                                                
// - ���û��ռ�ı�ʾ.                                                                                        
// Kobject�ṹ����Ϊ��                                                                                        
struct kobject {                                                                                           
char * k name; ָ���豸���Ƶ�ָ��                                                                          
char name[KOBJ NAME LEN]; �豸����                                                                         
struct kref kref; �������ü���                                                                             
struct list head entry; �ҽӵ�����kset��ȥ�ĵ�Ԫ                                                           
struct kobject * parent; ָ�򸸶����ָ��                                                                  
struct kset * kset; ����kset��ָ��                                                                         
struct kobj type * ktype; ָ�������������������ָ��                                                       
struct dentry * dentry; sysfs�ļ�ϵͳ����ö����Ӧ���ļ��ڵ�·��ָ��                                      
};                                                                                                         
// ���е�kref���ʾ�ö������õļ������ں�ͨ��krefʵ�ֶ������ü�������                                       
// �ں��ṩ��������kobject_get()��kobject_put()�ֱ��������Ӻͼ������ü�                                       
// ���������ü���Ϊ0ʱ�����иö���ʹ�õ���Դ�ͷš�Ktype ����һ��ָ��kobj                                      
// type�ṹ��ָ�룬��ʾ�ö�������͡�                                                                         
// ��غ���                                                                                                   
// void kobject_init(struct kobject * kobj)��kobject��ʼ��������                                              
// int kobject_set_name(struct kobject *kobj, const char *format, ...)��                                      
// ����ָ��kobject�����ơ�                                                                                    
// struct kobject *kobject_get(struct kobject *kobj)����kobj ���������                                       
// ������1��ͬʱ���ظö����ָ�롣                                                                            
// void kobject_put(struct kobject * kobj)�� ��kobj��������ü�����1��                                        
// �� 5  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                               
// ������ü�����Ϊ0�������kobject release()�ͷŸ�kobject����                                              
// int kobject_add(struct kobject * kobj)����kobj�������Linux�豸��Ρ�                                      
// �ҽӸ�kobject����kset��list���У����Ӹ�Ŀ¼����kobject�����ü�����                                       
// ����parentָ���Ŀ¼�´����ļ��ڵ㣬�������������ں˶����hotplug��                                        
// ����                                                                                                       
// int kobject_register(struct kobject * kobj)��kobjectע�ắ����ͨ����                                       
// ��kobject init()��ʼ��kobj���ٵ���kobject_add()��ɸ��ں˶����ע�ᡣ                                      
// void kobject_del(struct kobject * kobj)����Linux�豸���(hierarchy)                                        
// ��ɾ��kobj����                                                                                           
// void kobject_unregister(struct kobject * kobj)��kobjectע����������                                        
// kobject register()�෴�������ȵ���kobject del���豸�����ɾ���ö���                                      
// �ٵ���kobject put()���ٸö�������ü�����������ü�����Ϊ0�����ͷ�                                         
// kobject����                                                                                              
//                                                                                                            
// ��2 Kobj type                                                                                              
struct kobj_type {                                                                                         
void (*release)(struct kobject *);                                                                         
struct sysfs_ops * sysfs_ops;                                                                              
struct attribute ** default_attrs;                                                                         
};                                                                                                         
// Kobj type���ݽṹ����������һ��release���������ͷ�kobjectռ�õ���                                        
// Դ�� һ��sysfs opsָ��ָ��sysfs�������һ��sysfs�ļ�ϵͳȱʡ�����б�                                     
// Sysfs�����������������store()��show()�����û�̬��ȡ����ʱ��show()��                                       
// �������ã��ú�������ָ������ֵ����buffer�з��ظ��û�̬����store()��                                        
// �����ڴ洢�û�̬���������ֵ��                                                                             
attribute                                                                                                  
struct attribute {                                                                                         
char * name;                                                                                               
struct module * owner;                                                                                     
mode_t mode;                                                                                               
};                                                                                                         
// attribute, ���ԡ������ļ�����ʽ�����sysfs��Ŀ¼���С���kobject��Ӧ                                        
// ��Ŀ¼���档�ļ�                                                                                           
// ������name���ļ���д�ķ�����Ӧ��kobj type�е�sysfs ops��                                                   
//                                                                                                            
// ��3. kset                                                                                                  
// kset����Ҫ���ǽ����ϲ�(sub-system)���²��(kobject)�Ĺ����ԡ�kobject                                       
// Ҳ���������˷ֱ�������������һ�����ͣ�Ȼ����/sys �½�����ȷ��Ŀ¼λ�á�                                    
// ��kset ������Ȩ�Ƚϸߣ�kobject���������ѵ�*kset �ҵ�����������kset��                                       
// �K��*ktype ָ����ԓkset�µ�ktype�����Ǜ]�ж���kset���Ż���ktype��                                        
// ����ϵ��Kobjectͨ��kset��֯�ɲ�λ��Ľṹ��kset�Ǿ�����ͬ���͵�                                            
// kobject�ļ��ϣ����ں�����kset���ݽṹ��ʾ������Ϊ��                                                        
struct kset {                                                                                              
�� 6  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                               
struct subsystem * subsys; ���ڵ�subsystem��ָ��                                                           
struct kobj type * ktype; ָ���kset����������������ָ��                                                   
struct list head list; �������Ӹ�kset������kobject������ͷ                                                 
struct kobject kobj; Ƕ���kobject                                                                         
struct kset hotplug ops * hotplug ops; ָ���Ȳ�β������ָ��                                              
};                                                                                                         
// ������kset�е�����kobject����֯��һ��˫��ѭ������list�����Ǹ�����                                        
// ��ͷ��Ktype��ָ��һ��kobj type�ṹ������kset�е�����kobject����                                          
// ��ʾ��Щ��������͡�Kset���ݽṹ����Ƕ��һ��kobject������kobj���                                        
// ʾ���������������kset ��kobject�����parent���ָ�������Ƕ�Ķ���                                       
// ���⣬kset��������kobjά�����ü�����kset�����ü���ʵ���Ͼ�����Ƕ��                                         
// kobject��������ü�����                                                                                    
// ��ͼ1��kset��kobject�Ĺ�ϵͼ                                                                               
//                                                                                                            
//                                                                                                            
//                                                                                                            
// ���ͼ�ܾ��䣬����ӳ������kobject�����������                                                              
// ��غ���                                                                                                   
// ��kobject ���ƣ�kset_init()���ָ��kset�ĳ�ʼ���� kset_get()��kset_put()                                   
// �ֱ����Ӻͼ���kset��������ü�����Kset_add()��kset_del()�����ֱ�ʵ��                                       
// ��ָ��keset��������豸��κʹ�����ɾ����kset_register()�������kset                                       
// ��ע���kset_unregister()���������kset��ע����                                                            
// ��4 subsystem                                                                                              
// ����fkset �ǹ���kobject �ļ��ϣ�ͬ��subsystem ���ǹ���kset �ļ��ϡ�                                     
// ������ϵͳ��ĳһ���豸��ϵͳ����block subsys��ʾ���еĿ��豸����Ӧ��                                       
// sysfs�ļ�ϵͳ�е�blockĿ¼�����Ƶģ�devices subsys��Ӧ��sysfs�е�                                          
// devicesĿ¼������ϵͳ�����е��豸��Subsystem��struct subsystem���ݽ�                                       
// ������������Ϊ��                                                                                           
struct subsystem {                                                                                         
�� 7  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                               
struct kset kset; ��Ƕ��kset����                                                                           
struct rw semaphore rwsem; ��������ź���                                                                  
};                                                                                                         
// ���Կ�����subsystem��kset��������Ƕ���һ���ź����������ں����Ĵ���                                        
// �У�subsystem�Ѿ���ȫ��ksetȡ���ˡ�                                                                        
// ÿ��kset����ĳ��subsystem��ͨ������kset�ṹ�е�subsys��ָ��ָ����                                          
// subsystem���Խ�һ��kset���뵽��subsystem�����йҽӵ�ͬһsubsystem                                          
// ��kset����ͬһ��rwsem�ź���������ͬ������kset�е�����                                                    
// ��غ���                                                                                                   
subsystem��һ�����Ƶĺ������ֱ��ǣ�                                                                        
void subsystem_init(struct subsystem *subsys);                                                             
int subsystem_register(struct subsystem *subsys);                                                          
void subsystem_unregister(struct subsystem *subsys);                                                       
struct subsystem *subsys_get(struct subsystem *subsys)                                                     
void subsys_put(struct subsystem *subsys);                                                                 
// ������Щ�������÷������ں���ľ�������ϸ�������������һ�����ܡ�                                           
//                                                                                                            
// �豸ģ���ϲ�����                                                                                           
// ��1 bus                                                                                                    
// ϵͳ��������struct bus_type����������Ϊ��                                                                  
struct bus_type {                                                                                          
char * name; �������͵�����                                                                                
struct subsystem subsys; ���������ص�subsystem                                                           
struct kset drivers; �������������ص��������򼯺�                                                        
struct kset devices; ���йҽ��ڸ������ϵ��豸����                                                          
struct bus attribute * bus_attrs; ��������                                                                 
struct device attribute * dev_attrs; �豸����                                                              
struct driver attribute * drv_attrs; ������������                                                          
int (*match)(struct device * dev, struct device_driver * drv);                                             
int (*hotplug) (struct device *dev, char **envp, int num_envp, char                                        
*buffer, int buffer_size);                                                                                 
int (*suspend)(struct device * dev, u32 state);                                                            
int (*resume)(struct device * dev);                                                                        
}��                                                                                                        
// ÿ��bus_type������Ƕһ��subsystem����bus_subsys�������ϵͳ������                                      
// �������͵�subsystem����ÿ��bus_type���󶼶�Ӧ/sys/busĿ¼�µ�һ����                                      
// Ŀ¼����PCI�������Ͷ�Ӧ��/sys/bus/pci����ÿ��������Ŀ¼�¶�����������                                      
// Ŀ¼��devices��drivers���ֱ��Ӧ��bus type�ṹ�е�devices��drivers�򣩡�                                   
// ����devices��Ŀ¼���������ڸ������ϵ������豸����driversĿ¼���������                                     
// �� 8  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                               
// ���߹�������������������device_driver�������ƣ�bus_type�ṹ��������                                      
// ��������match()��hotplug()�ȣ�������Ӧ���Ȳ�Ρ����弴�κ͵�Դ�����¼���                                   
//                                                                                                            
// ��2 device                                                                                                 
// ϵͳ�е���һ�豸���豸ģ���ж���һ��device�������������Ӧ�����ݽṹ                                       
struct device                                                                                              
����Ϊ��                                                                                                   
struct device {                                                                                            
struct list_head g_list;                                                                                   
struct list_head node;                                                                                     
struct list_head bus_list;                                                                                 
struct list_head driver_list;                                                                              
struct list_head children;                                                                                 
struct device *parent;                                                                                     
struct kobject kobj;                                                                                       
char bus_id[BUS_ID_SIZE];                                                                                  
struct bus_type *bus;                                                                                      
struct device_driver *driver;                                                                              
void *driver_data;                                                                                         
// Several fields omitted //                                                                               
};                                                                                                         
// g_list ����device����ҽӵ�ȫ���豸�����У����е�device���󶼰�����                                        
// devices subsys�У�����֯�ɲ�νṹ��Node�򽫸ö���ҽӵ����ֵܶ������                                     
// ���У���bus list�����ڽ����ӵ���ͬ�����ϵ��豸��֯������driver list                                      
// ��ͬһ�����������������豸��֯Ϊ�������⣬children��ָ���device                                     
// �����Ӷ�������ͷ��parent����ָ�򸸶���Device������Ƕһ��kobject��                                      
// ���������ü�������ͨ����ʵ���豸��νṹ��Driver��ָ�������豸��                                     
// ����������󣬶�driver data�����ṩ��������������ݡ�Bus�������豸����                                     
// �ӵ�                                                                                                       
// �������͡�                                                                                                 
//                                                                                                            
// �ں��ṩ����Ӧ�ĺ������ڲ���device��������device_register()������                                        
// һ���µ�device��������豸ģ�ͣ����Զ���/sys/devices�´���һ����Ӧ��                                       
// Ŀ¼��device_unregister()����෴�Ĳ�����ע���豸����get_device()��                                      
// put_device()�ֱ�����������豸��������ü�����ͨ��device�ṹ������ʹ                                       
// �ã����ǰ����ڸ���Ľṹ����Ϊһ���ӽṹʹ�ã���������PCI�豸��struct                                      
// pci_dev����������ldd_dev,���е�dev�����һ��device����                                                   
//                                                                                                            
// ��3. driver                                                                                                
// ϵͳ�е�ÿ������������һ��device_driver������������Ӧ�����ݽṹ����Ϊ��                                    
struct device_driver {                                                                                     
char *name; �豸�������������                                                                             
�� 9  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                               
struct bus_type *bus; ��������������豸�ҽӵ���������                                                     
struct kobject kobj; ��Ƕkobject����                                                                       
struct list_head devices; ��������������豸����ͷ                                                         
int (*probe)(struct device *dev); ָ���豸̽�⺯��������̽���豸�Ƿ��                                     
�Ա��������������                                                                                         
int (*remove)(struct device *dev); ����ɾ���豸�ĺ���                                                      
// some fields omitted//                                                                                   
}��                                                                                                        
// ��device �ṹ���ƣ�device_driver����������Ƕ��kobject����ʵ�����ü���                                      
// ����Ͳ�νṹ��֯���ں��ṩ���Ƶĺ������ڲ���device_driver������                                        
// get_driver()�������ü�����driver_register()�������豸ģ�Ͳ����µ�                                          
// driver����ͬʱ��sysfs�ļ�ϵͳ�д�����Ӧ��Ŀ¼��device_driver()�ṹ��                                     
// �����������������ڴ����Ȱβ塢���弴�ú͵�Դ�����¼���                                                     
// ��������Ըո��оٳ�����һЩ�����ݽṹ���е��ܿ��գ���Ī�����û��ϵ��                                   
// �ҽ����������������������ˡ�                                                                               
//                                                                                                            
// ����һ lddbus                                                                                              
// ���ˣ���ð�ldd3��examples��������������Ȼû�������ˡ�                                                     
// ���������Ǵ��������֣�                                                                                     
// localhost:/home/XX/examples/lddbus#insmod lddbus.ko                                                        
// ��ʱ�ٿ�/sys/bus/ ��ʱ�Ͷ���һ���ļ���ldd��������ļ�������������                                          
// /sys/bus/ldd/                                                                                              
// |--device                                                                                                  
// |--driver                                                                                                  
// `--version                                                                                                 
// localhost:/sys/bus/ldd#cat version                                                                         
// $Revision: 1.9$                                                                                            
//                                                                                                            
// ���ʾϵͳ�ж���һ������ldd���������͡�ͬʱ�ٿ�/sys/device/��Ҳ�����һ��ldd0����                          
// ���С����ʾϵͳ�ж���һ������ldd0��Ӳ����                                                                 
// ��lddbus.c�У� ������һ�����ߺ�Ӳ������                                                                    
struct bus_type ldd_bus_type = {                                                                           
        .name = "ldd",                                                                                     
        .match = ldd_match,                                                                                
        .hotplug  = ldd_hotplug,                                                                           
};                                                                                                         
struct device ldd_bus = {                                                                                  
        .bus_id   = "ldd0",                                                                                
�� 10  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
        .release  = ldd_bus_release                                                                        
};                                                                                                         
lddbusģ���ʼ��ʱ�����������                                                                             
static int __init ldd_bus_init(void)                                                                       
{                                                                                                          
        int ret;                                                                                           
        ret = bus_register(&ldd_bus_type);                                                                 
        if (ret)                                                                                           
                return ret;                                                                                
        if (bus_create_file(&ldd_bus_type, &bus_attr_version))                                             
                printk(KERN_NOTICE "Unable to create version attribute\n");                                
        ret = device_register(&ldd_bus);                                                                   
        if (ret)                                                                                           
                printk(KERN_NOTICE "Unable to register ldd0\n");                                           
        return ret;                                                                                        
}                                                                                                          
// ��ʵ���ǵ���������ע�ắ����bus_register(),  device_register()��bus_create_file()����                      
// sysfs�´���һ���ļ��С�                                                                                    
// bus_register()�� ��ϵͳע��ldd_bus_type����������͡� bus_create_file()���������sysfs                     
// �д���һ���ļ���device_register()ϵͳע��ldd_bus���Ӳ�����͡�                                             
// ע�����֮�����ǾͿ�����sysfs�¿�����Ӧ����Ϣ��                                                          
// ����������ȥ����ϸ����bus_register�Ĵ��롣                                                                 
    688 int bus_register(struct bus_type * bus)                                                            
    689 {                                                                                                  
    690         int retval;                                                                                
    691                                                                                                    
    692         retval = kobject_set_name(&bus->subsys.kset.kobj, "%s", bus->name);                        
    693         if (retval)                                                                                
    694                 goto out;                                                                          
    695                                                                                                    
    696         subsys_set_kset(bus, bus_subsys);                                                          
    697         retval = subsystem_register(&bus->subsys);                                                 
    698         if (retval)                                                                                
    699                 goto out;                                                                          
    700                                                                                                    
    701         kobject_set_name(&bus->devices.kobj, "devices");                                           
    702         bus->devices.subsys = &bus->subsys;                                                        
    703         retval = kset_register(&bus->devices);                                                     
    704         if (retval)                                                                                
    705                 goto bus_devices_fail;                                                             
    706                                                                                                    
�� 11  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
    707         kobject_set_name(&bus->drivers.kobj, "drivers");                                           
    708         bus->drivers.subsys = &bus->subsys;                                                        
    709         bus->drivers.ktype = &ktype_driver;                                                        
    710         retval = kset_register(&bus->drivers);                                                     
    711         if (retval)                                                                                
    712                 goto bus_drivers_fail;                                                             
    713         bus_add_attrs(bus);                                                                        
    714                                                                                                    
    715         pr_debug("bus type '%s' registered\n", bus->name);                                         
    716         return 0;                                                                                  
    717                                                                                                    
    718 bus_drivers_fail:                                                                                  
    719         kset_unregister(&bus->devices);                                                            
    720 bus_devices_fail:                                                                                  
    721         subsystem_unregister(&bus->subsys);                                                        
    722 out:                                                                                               
    723         return retval;                                                                             
    724 }                                                                                                  
// 692-700�Ƕ�bus->subsys�Ĳ����� 701-705�ǲ���bus->devices��706-710�ǲ���bus->drivers��                      
// 692 kobject_set_name()����bus->subsys.kset.kobj�����֡��˺����ܼ򵥣����ǵ���                              
// vsnprintf()���˲��г���                                                                                    
//                                                                                                            
// 696 subsys_set_kset(bus, bus subsys)                                                                       
// #define subsys_set_kset(obj,_subsys)  (obj)->subsys.kset.kobj.kset = &(_subsys).kset                       
//                                                                                                            
// �����ȿ���bus_subsys�Ķ��壬����һ��subsystem���͵�ȫ�ֱ�������driver/base/bus.c                           
// �У�decl subsys(bus, &ktype bus, NULL); ��/include/linux/kobject.h ���У�decl subsys                       
// ��ԭ�ͣ�                                                                                                   
// #define decl_subsys(_name,_type,_hotplug_ops) \                                                            
// struct subsystem _name##_subsys = { \                                                                      
// .kset = { \                                                                                                
// .kobj = { .name = __stringify(_name) }, \                                                                  
// .ktype = _type, \                                                                                          
// .hotplug_ops =_hotplug_ops, \                                                                              
// } \                                                                                                        
// }                                                                                                          
// ���൱��                                                                                                   
// struct subsystem bus_subsys = { \                                                                          
// .kset = { \                                                                                                
// .kobj = { .name = ��bus�� }, \                                                                             
// .ktype = ktype_bus, \                                                                                      
// .hotplug_ops =NULL, \                                                                                      
// } \                                                                                                        
// }                                                                                                          
// �� 12  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
// ����ktype bus�������£�                                                                                    
// static struct kobj_type ktype_bus = {                                                                      
// .sysfs_ops = &bus_sysfs_ops,                                                                               
// };                                                                                                         
//                                                                                                            
// 697 subsystem_register(&bus->subsys)��������ȫ�ֵ�bus_subsys���Ǽǡ�, ���Լ����뵽                         
// bus_subsys��������ȥ��                                                                                     
// subsystem_register() -> kset_add() -> kobject_add()                                                        
    155 int kobject_add(struct kobject * kobj)                                                             
    156 {                                                                                                  
    157         int error = 0;                                                                             
    158         struct kobject * parent;                                                                   
    159                                                                                                    
    160         if (!(kobj = kobject_get(kobj)))                                                           
    161                 return -ENOENT;                                                                    
    162         if (!kobj->k_name)                                                                         
    163                 kobj->k_name = kobj->name;                                                         
    164         parent = kobject_get(kobj->parent);                                                        
    165                                                                                                    
    166         pr_debug("kobject %s: registering. parent: %s, set: %s\n",                                 
    167                  kobject_name(kobj), parent ? kobject_name(parent) : "<NULL>",                     
    168                  kobj->kset ? kobj->kset->kobj.name : "<NULL>" );                                  
    169                                                                                                    
    170         if (kobj->kset) {                                                                          
    171                 down_write(&kobj->kset->subsys->rwsem);                                            
    172                                                                                                    
    173                 if (!parent)                                                                       
    174                         parent = kobject_get(&kobj->kset->kobj);                                   
    175                                                                                                    
    176                 list_add_tail(&kobj->entry,&kobj->kset->list);                                     
    177                 up_write(&kobj->kset->subsys->rwsem);                                              
    178         }                                                                                          
    179         kobj->parent = parent;                                                                     
    180                                                                                                    
    181         error = create_dir(kobj);                                                                  
    182         if (error) {                                                                               
    183                 // unlink does the kobject_put() for us //                                         
    184                 unlink(kobj);                                                                      
    185                 if (parent)                                                                        
    186                         kobject_put(parent);                                                       
    187         } else {                                                                                   
    188                 kobject_hotplug(kobj, KOBJ_ADD);                                                   
    189         }                                                                                          
    190                                                                                                    
�� 13  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
    191         return error;                                                                              
    192 }                                                                                                  
                                                                                                           
// �����170-178���ǰ��Լ����뵽�����ϼ�kset�С�����ע�⵽��kobject_add()������181                            
// �е�����create_dir(kobj)�� ���������������sysfs�´���һ���ļ��С� �ɼ�kobject��sysfs                      
// ��ͬʱ���µġ�                                                                                             
//                                                                                                            
// kset_register(&bus->devices) ��kset_register(&bus->drivers)�������ƣ� ��bus->devices                       
// ���kset���뵽bus->subsys���subsystem��ȥ������γ�ͼ1�Ĳ�νṹ��                                        
//                                                                                                            
// ͼ1��lddbus kobject��νṹ                                                                                
//                                                                                                            
// ͬ�����ǿ��Կ���device_register()�Ĵ��룬��Ҳ����devices_subsys���subsystemע                           
// �ᣬ����γ������Ľṹ��ͼ1���ơ�                                                                          
// ĿǰΪֹ������֪������ν��xx_register����������ͨ������Ƕ��kobject�����Ӧ��                               
// subsystem������kset�Ĳ�νṹ��ȥ�������Ϳ���ͨ��һЩȫ�ֵı����ҵ������ˡ�                                
//                                                                                                            
// ������ sculld                                                                                              
// �����ٰ� sculld �Ĵ���Ҳ����һ�£��ȿ���ʼ����                                                             
// sculld_init()                                                                                              
// �� 14  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
//              -> register_ldd_driver()                                                                      
//                          ->driver_register()                                                               
//                                             ->bus_add_driver()                                             
//              -> register_ldd_device()                                                                      
//                          ->device_register()                                                               
//                                            ->device_add()                                                  
//                                                              ->kobject_add()                               
//                                                              ->bus_add_device()                            
// ����ע���������� bus_add_driver()                                                                          
    532 int bus_add_driver(struct device_driver * drv)                                                     
    533 {                                                                                                  
    534         struct bus_type * bus = get_bus(drv->bus);                                                 
    535         int error = 0;                                                                             
    536                                                                                                    
    537         if (bus) {                                                                                 
    538                 pr_debug("bus %s: add driver %s\n", bus->name, drv->name);                         
    539                 error = kobject_set_name(&drv->kobj, "%s", drv->name);                             
    540                 if (error) {                                                                       
    541                         put_bus(bus);                                                              
    542                         return error;                                                              
    543                 }                                                                                  
    544                 drv->kobj.kset = &bus->drivers;                                                    
    545                 if ((error = kobject_register(&drv->kobj))) {                                      
    546                         put_bus(bus);                                                              
    547                         return error;                                                              
    548                 }                                                                                  
    549                                                                                                    
    550                 down_write(&bus->subsys.rwsem);                                                    
    551                 driver_attach(drv);                                                                
    552                 up_write(&bus->subsys.rwsem);                                                      
    553                 module_add_driver(drv->owner, drv);                                                
    554                                                                                                    
    555                 driver_add_attrs(bus, drv);                                                        
    556         }                                                                                          
    557         return error;                                                                              
    558 }                                                                                                  
    559                                                                                                    
                                                                                                           
// 545��kobject_register()��kobject_add()��࣬����ע�ᣬ���Լ�kobject ���ӵ��ں�                           
// ��ȥ��                                                                                                     
// 551��driver_attach(drv); ��������Ѱ�ң���û���豸��������� driver ������                                  
                                                                                                           
    353 void driver_attach(struct device_driver * drv)                                                     
    354 {                                                                                                  
�� 15  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
    355         struct bus_type * bus = drv->bus;                                                          
    356         struct list_head * entry;                                                                  
    357         int error;                                                                                 
    358                                                                                                    
    359         if (!bus->match)                                                                           
    360                 return;                                                                            
    361                                                                                                    
    362         list_for_each(entry, &bus->devices.list) {                                                 
    363                 struct device * dev = container_of(entry, struct device, bus_list);                
    364                 if (!dev->driver) {                                                                
    365                         error = driver_probe_device(drv, dev);                                     
    366                         if (error && (error != -ENODEV))                                           
    367                                 // driver matched but the probe failed //                          
    368                                 printk(KERN_WARNING                                                
    369                                     "%s: probe of %s failed with error %d\n",                      
    370                                     drv->name, dev->bus_id, error);                                
    371                 }                                                                                  
    372         }                                                                                          
    373 }                                                                                                  
                                                                                                           
Ȼ��ע���豸��                                                                                             
    455 int bus_add_device(struct device * dev)                                                            
    456 {                                                                                                  
    457         struct bus_type * bus = get_bus(dev->bus);                                                 
    458         int error = 0;                                                                             
    459                                                                                                    
    460         if (bus) {                                                                                 
    461                 down_write(&dev->bus->subsys.rwsem);                                               
    462                 pr_debug("bus %s: add device %s\n", bus->name,                                     
dev->bus_id);                                                                                              
    463                 list_add_tail(&dev->bus_list, &dev->bus->devices.list);                            
    464                     465                 up_write(&dev->bus->subsys.rwsem);                         
    466                 device_add_attrs(bus, dev);                                                        
    467                 sysfs_create_link(&bus->devices.kobj, &dev->kobj,                                  
dev->bus_id);                                                                                              
    468         }                                                                                          
    469         return error;                                                                              
    470 }                                                                                                  
// 463�����豸���������ߵ� devices.list �����С�                                                              
// 464��device_attach(dev)�� driver_attach()���Ӧ���������ߵ�������Ѱ�ң�����û��һ                          
// �� driver ����������豸��                                                                                 
// 467��������һ�����ӡ�                                                                                      
//                                                                                                            
// ����γɵ� kobject ��νṹ��ͼ��ʾ��                                                                      
// �� 16  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
//                                                                                                            
//                                                                                                            
//                                                                                                            
// �仯                                                                                                       
// �ƻ��ϲ��ϱ仯����ǰ���ں˰汾�Ѿ��� 2.6.22 �ˣ����в������ݽṹ���˱䶯������                             
// subsystem������ݽṹ�Ѿ�û���ˣ���ȫ��ksetȡ���ˡ�����ԭ���ϲ�û�б䣬����Ϊ��                            
// ѧϰ֪ʶ��һ���棬����Ҫ����ѧϰ������ֻҪ���˷��������ǲſ�"�Բ���Ӧ���"��                               
// 17������Ҫ�ٿ��ˣ������ֶ���ˣ��¶�Ĭ���밢��˹Ҳ�����ˣ�����Ͱ����ˡ���г�����                         
// �������ϣ����������������������ڰ��豸ģ�ͽ�����ϣ����������� sysfs ���֡�                              
// ���治֪�δ�ȥ���һ�����Ц���硣 �ơ��޻����ⶼ����ׯ                                                      
//                                                                                                            
// �ļ�ϵͳ                                                                                                   
// �����������ǽ��� sysfs ���֡�����                                                                          
// kobject_add()->create_dir()->sysfs_create_dir()                                                            
// bus create file->sysfs create file()                                                                       
// . . .                                                                                                      
// ��Щ sysfs ��������Ļ��                                                                                    
// ˵���ˣ�sysfs �������� VFS�Ľӿ�ȥ��д kobject �Ĳ�νṹ�������������ļ�ϵͳ������                        
// �� 17  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
// sysfs �����ݾ��� fs/sysfs/�¡� kobject �Ĳ�νṹ�ĸ�����ɾ��������Щ���߰����                            
// XX_register()�Ǹɵ����顣                                                                                  
// �� kobject_add()���棬������sysfs_create_dir()�������ǿ�������������� create�ġ�                          
    135 int sysfs_create_dir(struct kobject * kobj)                                                        
    136 {                                                                                                  
    137         struct dentry * dentry = NULL;                                                             
    138         struct dentry * parent;                                                                    
    139         int error = 0;                                                                             
    140                                                                                                    
    141         BUG_ON(!kobj);                                                                             
    142                                                                                                    
    143         if (kobj->parent)                                                                          
    144                 parent = kobj->parent->dentry;                                                     
    145         else if (sysfs_mount && sysfs_mount->mnt_sb)                                               
    146                 parent = sysfs_mount->mnt_sb->s_root;                                              
    147         else                                                                                       
    148                 return -EFAULT;                                                                    
    149                                                                                                    
    150         error = create_dir(kobj,parent,kobject_name(kobj),&dentry);                                
    151         if (!error)                                                                                
    152                 kobj->dentry = dentry;                                                             
    153         return error;                                                                              
    154 }                                                                                                  
// ���㿴����ôЩ�¶������� dentry ���ֵ�ʱ����һ���е������󡣳�Ȼ����һ��Ϊ������ͻ                       
// Ȼ���ֵ�����е��ֻţ������δ֪�Ŀ־������������ģ������������Թ����������Ǳ���                       
// һ�ž�η������Ϳ����ˡ������ linux������ʼ�ռ��ţ�δ֪�϶��ǿ��Ա�̽�������ġ�����                       
// ���������ģ�������������д�����ģ���Ȼд�ó������ǾͿ϶����ö����Բ��𣬳�Զ��....��                       
// ���ǽ��ܽ����ļ�ϵͳ�Ļ���֪ʶ�ȡ�                                                                         
// �ļ�ϵͳ                                                                                                   
// �ļ�ϵͳ�Ǹ���ģ���㷺�ĸ��"�ļ�"�����˵����ָ�����ļ���������⣬����������֯��                       
// ����ش洢���κν���(�����ڴ�)��һ����Ϣ��linux �����е���Դ���������ļ������û�ͨ��                       
// һ��ͳһ���ļ�ϵͳ�������棬Ҳ����ͬһ��ϵͳ���ã������ڲ�ͬ�ļ�ϵͳ���ļ����в�����                       
// �������Ϳ��Զ��û��������ظ��ֲ�ͬ�ļ�ϵͳ��ʵ��ϸ�ڣ�Ϊ�û������ṩ��һ��ͳһ�ģ���                       
// ��ģ�������ļ�ϵͳ���棬�������ν"VFS(Virtual Filesystem Switch)"������������                         
// �Ľӿھ���һ�麯��������                                                                                   
//                                                                                                            
// ����Ҫʵ��һ���ļ�ϵͳ����Ҫʵ�� VFS�������һϵ�нӿڣ�file_operations,                                   
// dentry_operations, inode_operations�ȣ����ϲ���á�file_operations �Ƕ�ÿ��������                          
// ���Ķ�д������dentry_operations, inode_operations���Ƕ��ļ������ԣ�������֣�����                          
// ��ɾ���Ĳ�����                                                                                             
// �� 18  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
struct file_operations {                                                                                   
ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);                                          
ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);                                   
int (*open) (struct inode *, struct file *);                                                               
...                                                                                                        
};                                                                                                         
struct dentry_operations {                                                                                 
...                                                                                                        
};                                                                                                         
struct inode_operations {                                                                                  
int (*create) (struct inode *,struct dentry *,int, struct nameidata *);                                    
struct dentry * (*lookup) (struct inode *,struct dentry *, struct nameidata *);                            
int (*link) (struct dentry *,struct inode *,struct dentry *);                                              
int (*mkdir) (struct inode *,struct dentry *,int);                                                         
int (*rmdir) (struct inode *,struct dentry *);                                                             
...}                                                                                                       
// �ٸ����ӣ�����дC ����open(��hello.c��, O_RDONLY)����ͨ��ϵͳ���õ�������������                          
//                                                                                                            
// open() ->       //�û��ռ�//                                                                               
// -> ϵͳ����->                                                                                              
// sys_open() -> filp_open()-> dentry_open() ->  file_operations->open()           //                         
// �ں˿ռ�//                                                                                                 
// ��ͬ���ļ�ϵͳ�����ò�ͬ��file_operations->open()����sysfs�¾���sysfs_open_file()��                        
//                                                                                                            
// Dentry �� inode                                                                                            
// �����ڽ�����Ҫ����ȥ����һ���ļ��أ�������Ŀ¼��(dentry)�������ڵ�(inode)�����ǵĶ�                        
// ������:                                                                                                    
struct dentry {                                                                                            
struct inode                                *d_inode; // Where the name belongs to -                       
NULL is                                                                                                    
struct dentry                                *d_parent; // parent directory //                             
struct list_head                          d_child; // child of parent list //                              
struct dentry_operations          *d_op;                                                                   
struct super_block                     *d_sb; // The root of the dentry tree //                            
void                                     *d_fsdata; // fs-specific data //                                 
unsigned char                  d_iname[DNAME_INLINE_LEN_MIN]; // small names //                            
......                                                                                                     
};                                                                                                         
�� 19  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
struct inode {                                                                                             
unsigned long                     i_ino;                                                                   
atomic_t                               i_count;                                                            
umode_t                               i_mode;                                                              
unsigned int                        i_nlink;                                                               
uid_t                                      i_uid;                                                          
gid_t                                      i_gid;                                                          
dev_t                                     i_rdev;                                                          
loff_t                                      i_size;                                                        
struct timespec                   i_atime;                                                                 
unsigned long                     i_blocks;                                                                
unsigned short                    i_bytes;                                                                 
unsigned char                      _sock;                                                                  
12                                                                                                         
struct inode_operations *i_op;                                                                             
struct file_operations *i_fop; // former ->i_op->default_file_ops //                                       
struct super_block *i_sb;                                                                                  
......                                                                                                     
};                                                                                                         
//         ��ν"�ļ�", ���ǰ�һ������ʽ�洢�ڽ����ϵ���Ϣ�� ����һ���ļ���ʵ������������                      
// ����Ϣ��һ�Ǵ洢�����ݱ��������йظ��ļ�����֯�͹������Ϣ�����ڴ���, ÿ���ļ�����                       
// һ��dentry(Ŀ¼��)��inode(�����ڵ�)�ṹ��dentry��¼���ļ������ϼ�Ŀ¼����Ϣ��������                        
// �γ�����������������״�ṹ�����йظ��ļ�����֯�͹������Ϣ��Ҫ���inode���棬����¼                        
// ���ļ��ڴ洢�����ϵ�λ����ֲ��� ͬʱdentry->d_inodeָ����Ӧ��inode�ṹ�� dentry��inode                    
// �Ƕ��һ�Ĺ�ϵ����Ϊ�п���һ���ļ��кü����ļ���(Ӳ����, hard link, ���Բο������ҳ                       
// http://www.ugrad.cs.ubc.ca/~cs219/CourseNotes/Unix/commands-links.html)��                                  
// ���е�dentry��d_parent��d_child�������������γ���������Ϥ����״�ṹ��                                      
// inode����������������ϵ��ļ���ͨ��inode���Եõ�һ�����飬��������¼���ļ����ݵ�                         
// λ�ã�����ļ�λ��Ӳ�̵ĵ�3��8��10�飬��ô�����������ݾ���3,8,10���������ڵ��                           
// inode->i_ino����ͬһ���ļ�ϵͳ����Ψһ�ģ��ں�ֻҪ����i_ino���Ϳ��Լ��������Ӧ��                          
// inode�ڽ����ϵ�λ�á���Ӳ����˵������i_ino�Ϳ��Լ��������Ӧ��inode�����ĸ���                              
// (block)���Ӷ��ҵ���Ӧ��inode�ṹ����������inode�����޷����������е��ļ�ϵͳ������                          
// ĳһ���ض����ļ�ϵͳ���ԣ� ����ext3�� ���ڴ�����ext3_inode_info������ ����һ������inode                    
// ��"����"��                                                                                                 
struct ext3_inode_info {                                                                                   
               __le32 i_data[15];                                                                          
               ......                                                                                      
               struct inode vfs_inode;                                                                     
};                                                                                                         
// le32 i data[15]������������һ�������ᵽ���Ǹ����顣                                                      
// �� 20  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
// ע�⣬��ңԶ��2.4�ĹŴ�����ͬ�ļ�ϵͳ�����ڵ���ڴ�ӳ��(ext3_inode_info��                                  
// reiserfs_inode_info��msdos_inode_info ...)������һ��union��Ƕ��inode���ݽṹ�е�.                          
// ��inode��Ϊһ�ַǳ����������ݽṹ���ԣ�������̫���ˣ������ڿ��ٵķ���ͻ��ա����Ǻ�                        
// ��������container_of(...)���ַ����󣬾Ͱ�union�Ƶ����ⲿ�����ǿ���������container                          
// of(inode, struct ext3_inode_info, vfs_inode)����inode�������õ����"����"��                                
// dentry��inode�վ��������ڴ��еģ����ǵ�ԭʼ��Ϣ����Ҫ��һ�����塣����ϵ�֮����                          
// �������ˣ�����������������                                                                                 
// �ļ����Է�Ϊ�����ļ����豸�ļ����������ļ����֡��豸�ļ����Ҳ���                                         
// �����ļ�                                                                                                   
// �ʹ����ļ����ԣ� dentry��inode�������ڴ洢����(����)�ϡ� ������ext3�����Ĵ����ļ���˵��                    
// �洢�����е�Ŀ¼��������ڵ��������£�                                                                     
struct ext3_inode {                                                                                        
__le16 i_mode; // File mode //                                                                             
__le16 i_uid; // Low 16 bits of Owner Uid //                                                               
__le32 i_size; // Size in bytes //                                                                         
__le32 i_atime; // Access time //                                                                          
__le32 i_ctime; // Creation time //                                                                        
__le32 i_mtime; // Modification time //                                                                    
__le32 i_dtime; // Deletion Time //                                                                        
__le16 i_gid; // Low 16 bits of Group Id //                                                                
__le16 i_links_count; // Links count //                                                                    
......                                                                                                     
__le32 i_block[EXT2_N_BLOCKS];// Pointers to blocks //                                                     
......                                                                                                     
}                                                                                                          
struct ext3_dir_entry_2 {                                                                                  
__u32 inode; // Inode number //                                                                            
__u16 rec_len; // Directory entry length //                                                                
__u8 name_len; // Name length //                                                                           
__u8 file_type;                                                                                            
char name[EXT3_NAME_LEN]; // File name //                                                                  
};                                                                                                         
// le32 i block[EXT2 N BLOCKS];// Pointers to blocks //                                                       
// i_block����ָʾ���ļ�����������ŵĵص�(��Ӳ���ϵ�λ��)��                                                  
// ext3_inode�Ƿ��������ڵ�������ext3_dir_entry_2�����ļ����ݵ���ʽ�����������������                         
// ֻҪ֪����ino������ext3_inode��С��֪�����ǾͿ��Լ����ext3_inode�������ڵ�����λ                          
// ��( ino * sizeof(ext3_inode) )�����õ���ext3_inode�����Ǹ���i_block�Ϳ���֪�����                          
// �ļ������ݴ�ŵĵص㡣��������ext3_inode�����ݶ��뵽ext3_inode_info�еĺ�����                              
// �� 21  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
// ext3_read_inode()����һ����100 block��Ӳ��Ϊ����һ���ļ�ϵͳ����֯���ִ�������ͼ��                         
// λͼ���е�ÿһλ��ʾÿһ����Ӧ�Ķ�����û�б�ʹ�á�                                                         
//                                                                                                            
//                                                                                                            
// �����ļ�                                                                                                   
// �����ļ����ڴ�����inode��dentry���ݽṹ�����ǲ�һ���ڴ洢��������"�����ڵ�"�����ϵ�                        
// ֮���ȷ�������ˣ����Բ���Ҫʲô���塣����һ�������ļ���ʱ������������������ϵͳ�ڲ�                       
// ��һ���Ĺ�����ʱ���ɵģ�����ڴ����ռ����ӹ������ġ�sysfs������ǵ��͵������ļ�����                        
// �洢����Ϣ������ϵͳ��̬�����ɵģ�����̬�İ���������������Ӳ����Դ�������sysfs��д                        
// ���൱����kobject��νṹ��ȡ���ݡ�                                                                        
// ����ע��, ����̸��Ŀ¼��������ڵ�ʱ�������ֺ��塣һ�����ڴ洢����(Ӳ��)�е�(��                            
// ext3_inode)�� һ�������ڴ��еģ������Ǹ�����ǰ�����ɵġ� �ڴ��еı�ʾ����dentry��inode��                   
// ����VFS�е�һ�㣬����ʲô�����ļ�ϵͳ��������ڴ����������Ķ���dentry��inode�ṹ��                         
// ����ʹ�ò�ͬ���ļ�ϵͳ�����ǽ����Ǹ��Ե��ļ���Ϣ������ dentry��inode��ȥ��������                         
// �ڸ߲���˵�����ǾͿ��Բ����ĵײ��ʵ�֣�����ʹ�õĶ���һϵ�б�׼�ĺ������á������                         
// VFS�ľ��裬ʵ���Ͼ����������                                                                            
// �����ڽ����д�һ���ļ�F��ʵ���Ͼ���Ҫ���ڴ��н���F��dentry,��inode�ṹ��������                           
// ������̽ṹ��ϵ������VFS�ж���Ľӿڸ�����������������һ����������ͼ������ͼ֮��                        
// �ļ�ϵͳ������ÿ�찮���һЩ֮����ѧ�ѣ����ѳ���֮�ڸ�������ʳ�ã��̹����ġ�                               
//                                                                                                            
// �� 22  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
//                                                                                                            
//                                                                                                            
// һ��ɢɢ������pathwalk                                                                                     
// ǰ��˵����ֻҪ֪���ļ��������ڵ�ţ��Ϳ��Եõ��Ǹ��ļ������������ڲ����ļ�ʱ����û��                       
// ˵˭�����������ڵ���������ļ�������ֻ֪���ļ������ѡ����������"��г"�������أ�linux                      
// ��Ŀ¼Ҳ����һ���ļ��������¼���ļ����������ڵ�ŵĶ�Ӧ��ϵ�������� ext3 �ļ�ϵͳ�У�                     
// ����ļ���һ��Ŀ¼����ô�������ݾ���һϵ�� ext3_dir_entry_2�Ľṹ                                          
//                                                                                                            
struct ext3_dir_entry_2 {                                                                                  
__u32 inode; // Inode number //                                                                            
__u16 rec_len; // Directory entry length //                                                                
__u8 name_len; // Name length //                                                                           
__u8 file_type;                                                                                            
�� 23  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
char name[EXT3_NAME_LEN]; // File name //                                                                  
};                                                                                                         
                                                                                                           
// �ٸ����ӣ�����Ҫ��/home/test/hello.c�����ȣ��ҵ���/�������������ݣ��ҵ���Ϊ"home"                        
// ���ļ��������ڵ�ţ���/home���"�ļ�"���������ݣ��ҵ���Ϊ "test" �ĵ��ļ�������                          
// �ڵ�ţ�ͬ���ٴ��ļ�"/home/test"���ҵ��ҵ���Ϊ"hello.c�����ļ��������ڵ�ţ����                       
// �͵õ�/home/test/hello.c�ˡ������ path_walk()������ԭ��                                                 
// ���У�����һ���ļ��е�inode����һ���ļ�������ȡ���ļ���inode�ṹ�ĺ������ͽ�lookup��                       
// ���� inode_operations����ĺ�����                                                                          
// struct dentry * (*lookup) (struct inode *,struct dentry *, struct nameidata *);                            
// lookup������˼�壬���ǲ��ң��������� test ����ļ����£���û�н� hello.c ���ļ�����                      
// �Ļ����ʹӴ洢�����ж�ȡ�� inode �ṹ������ dentry->d_inodeָ���������ԣ�����ֻҪ                          
// ֪�����ļ���·�������֣��ܿ��ԴӸ�Ŀ¼��ʼ��һ��һ��������ߣ���λ��ĳһ���ļ���                           
// superblock �� vfsmount                                                                                     
// ��������Ҫ�����������ݽṹ��superblock�� vfsmount��super_block �ṹ�Ǵ����о����                          
// �ļ�ϵͳ�����������һ���ṹ��ÿһ���ļ�ϵͳʵ��������һ��Ӧ super_block �ṹ������                        
// ÿһ�� ext2�ķ�������һ�� super_block �ṹ������¼�˸��ļ�ϵͳʵ��(����)��ĳЩ����                         
// �Ե���Ϣ��������ļ�ϵͳʵ�����ļ�ϵͳ���ͣ��ж�󣬴�����ÿһ��Ĵ�С, ���о���                           
// super_operations������ inode��dentryһ����ֻ��ĳЩ�������ڴ��е�ӳ�񡣾� ext2�ļ�                          
// ϵͳ���ԣ��豸�ϵĳ�����Ϊ ext2_super_block������ sysfs��������ļ�ϵͳ����һ�޶�, ��                      
// ��ֻ�ܱ� mount һ�Σ�sysfs�� super_block �ṹ�� sysfs_sb��sysfs_sbҲ�Ƕ�̬�Ĵ���                           
// �������ɵġ�                                                                                               
//                                                                                                            
// ����Ҫ��һ�� super_operations����Ҳ���� VFS��һ���ӿڡ�ʵ��һ���ļ�ϵͳ                                    
// file_operations, dentry_operations, inode_operations, super_operations���ĸ��ṹ                           
// ��Ҫʵ�֡�                                                                                                 
// ��һ���豸��װ��һ��Ŀ¼�ڵ�ʱҪ��һ�� vfsmount����Ϊ���Ӽ���vfsmount�ṹ������                            
// �£�                                                                                                       
struct vfsmount {                                                                                          
              struct list_head mnt_hash;                                                                   
              struct vfsmount *mnt_parent; // fs we are mounted on //                                      
              struct dentry *mnt_mountpoint; // dentry of mountpoint //                                    
              struct dentry *mnt_root; // root of the mounted tree //                                      
              struct super_block *mnt_sb; // pointer to superblock //                                      
              ..........                                                                                   
}                                                                                                          
// ����ĳ���ļ�ϵͳʵ�����ڴ��� super_block�� vfsmount����Ψһ�ġ����磬���ǽ�ĳ����                          
// ��Ӳ�̷���mount -t vfat /dev/hda2 /mnt/d��ʵ���Ͼ����½�һ��vfsmount �ṹ��Ϊ��                            
// �Ӽ���vfsmount->mnt_sb = /dev/hda2�ĳ�����ṹ��vfsmount->mntroot =                                        
// /dev/hda2��"��"Ŀ¼�� dentry��vfsmount->mnt_mountpoint = /mnt/d ��                                         
// �� 24  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
// dentry�� vfsmount->mnt_parent = /mnt/d�������ļ�ϵͳ�� vfsmount�����Ұ������                              
// ���� vfsmount����һ��ȫ�ֵ�hash�� mount_hashtable�С�                                                      
// �Ӷ����ǾͿ��Դ��ܸ���/����ʼ������ dentry �����ҡ���������һ��ĳ��Ŀ¼�� dentry�Ǳ�                       
// mount�˵ģ���ô���Ǿʹ� mount_hashtable����ȥѰ����Ӧ�� vfsmount�ṹ (������                               
// lookup_mnt())��Ȼ�����ǵõ�vfsmount ->mnt_root���Ϳ����ҵ� mount �ڸ�Ŀ¼����                              
// ��ϵͳ��"��"dentry�ṹ��Ȼ���ּ��������ߣ��Ϳ��Գ�ͨ�����ˡ�                                               
// ���� path_walk()�Ĵ����ҾͲ����ˣ�̫���ˡ���ʵ����ԭ�����ȥ�����ܼ򵥣��������»�                         
// ��ࡣ�ҵ�����ǿ���������������ı�������pathwalk������ǰ���Ǹ��ٹ�·��������                         
// Ţ�����С·�����Ƕ�Ҫ�ߵ��ס�                                                                             
//                                                                                                            
// Sysfs�ļ�ϵͳģ��                                                                                          
// ��� Linus �ں� C++����C++��һ�����ģ�horrible�����ԡ�������Ϊ�д���������׼�ĳ�                         
// ��Ա��ʹ�ö�ʹ����������õײ����⣬������������Щ�׳ա�����ģ�͡�����ţ�˾���ţ�����찢��                 
// �� fs/sysfs/���棬��ȥmakefile������ 8���ļ������У� bin.c, file.c, dir.c, symblink.c                      
// �ֱ�������� sysfs�ļ�ϵͳ�е��ļ�����Ϊ�������ļ�����ͨ�ļ���Ŀ¼����������ʱ�ĸ���                       
// �� file operations �ṹ���ʵ�֡�inode.c ���� inode oprations ��ʵ�֣����д�����ɾ��                       
// inode��mount.c ������ sysfs�ĳ�ʼ��������sysfs.h����ͷ�ļ��������к�����ԭ�Σ�����                         
// �� extern ��ȥ��                                                                                           
// sysfs ���ļ�ϵͳ������д����Ϣ�Ǵ���� kobject���У���ôdentry������� kobject��ϵ                         
// �������أ���ͨ�� sysfs_dirent��                                                                            
// sysfs_dirent                                                                                               
// sysfs �ļ�ϵͳ���Լ��� dirent �ṹ��dirent = directory entry (Ŀ¼ʵ��)��sysfs �У�ÿ                      
// һ�� dentry��Ӧ��һ�� dirent �ṹ��dentry->d _fsdata��һ�� void ��ָ�룬��ָ��                             
// sysfs_dirent�ṹ��                                                                                         
struct sysfs_dirent {                                                                                      
            atomic_t               s_count;                                                                
            struct list_head  s_sibling;                                                                   
            struct list_head  s_children;                                                                  
            void *                    s_element;                                                           
            int                          s_type;                                                           
            umode_t             s_mode;                                                                    
            struct dentry *     s_dentry;                                                                  
            struct iattr *         s_iattr;                                                                
            atomic_t              s_event;                                                                 
};                                                                                                         
// �� 25  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
// s_count �����ü�����s_sibling��s_children ָ������Щ sysfs_dirent ����һ����״�ṹ��                       
// s_type��˵������� dirent���������:                                                                       
#define SYSFS_ROOT 0x0001                                                                                  
#define SYSFS_DIR 0x0002                                                                                   
#define SYSFS_KOBJ_ATTR 0x0004                                                                             
#define SYSFS_KOBJ_BIN_ATTR 0x0008                                                                         
#define SYSFS_KOBJ_LINK 0x0020                                                                             
// s_element ����ָ����Ӧ�� s_type���͵����ݽṹ����DIR(���� kobject��һ�� kobject                            
// ��Ӧһ�� DIR)��KOBJ_ATTR(attribute���ԣ�����һ���ļ�)��sysfs_dirent�� kobject��                            
// sysfs ��ϵ��һ���м����ӽṹ����ͨ�� s_sibling��s_children ���ӳ�һ����νṹ��������                      
// �Ĳ�νṹ�� sysfs��ȫһ�µģ�������һ������ kobject �� dentry�ṹ�����Ӽ���                               
// �ٸ������ܽ�һ����Щ���ݽṹ�����ӹ�ϵ����sysfs�е��ļ��ṹ����                                            
// /sys/bus/ldd/                                                                                              
// |--device                                                                                                  
// |--driver                                                                                                  
// `--version                                                                                                 
// ����Ӧ�� dentry��dirent��kobject ������ͼ��ͼ 1��2��3                                                      
//                                                                                                            
// �� 26  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
// ͼ 1: dentry ����ͼ                                                                                        
//                                                                                                            
// ͼ 2: dirent����ͼ                                                                                         
//                                                                                                            
// ͼ 3: kobject ����ͼ                                                                                       
// �Ա�һ�¿��Է��ֲ�֮ͬ������version ������bus_create_file()�������ļ�����Ի���ԣ�ֻ                        
// ͣ����sysfs_dirent��һ�㡣                                                                                 
//                                                                                                            
// ���� sysfs �µ��ļ��ж��ԣ�denrty, dirent, kobject֮��ͨ��ָ���໥��ϵ������                               
// dentry->d_fsdata = &dirent;                                                                                
// dirent->element = &kobject;                                                                                
// kobject->dentry = &dentry;                                                                                 
//                                                                                                            
// Sysfs����Ŀ¼                                                                                              
// ÿ����������һ�� kobject �ṹ��ʱ��ͬʱ����/sys �´���һ��Ŀ¼��                                         
// kobject_add()  ->  create_dir() -> sysfs_create_dir()                                                      
// ��ʱ���һ������꣬kernel����ĸ��»����Ǻܿ�ģ����ǵ�Ŀ���Ƕ��ô��뱳���ԭ��֪                         
// ʶ����Ի��ѧ���Ҳ��뽲��̫ϸ����Ϊ���� sysfs�Ĳ��ִ� 2.6.10������ 2.6.22�Ѿ����˺�                         
// ���ˡ���������ܹ�û�䡣д���ĵ�Ŀ�������������ҵ�˼·��һ�飬��sysfs ����һ��������                       
// ����ʶ��Ȼ���Լ��Ϳ���ȥ�����µĴ����ˡ����µĴ���϶���Ч�ʸ��ߣ������߼���������                         
// �� 27  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
// sysfs_create_dir()����ͼ����:                                                                              
//                      -> create_dir()                                                                       
//                                           -> *d = sysfs_get_dentry()                                       
//                                                                -> lookup_hash()                            
//                                                                                     -> __lookup_hash()     
//                                                                                     -> cached_lookup()     
//                                                                                     -> new = d_alloc(base, 
// name);                                                                                                     
//                                                                                     ->                     
// inode->i_op->lookup(inode, new, nd)                                                                        
//                                           -> sysfs_create(*d, mode, init_dir)                              
//                                                                -> sysfs_new_inode(mode)                    
//                                                                -> init_dir(inode); \\ Call back            
// function                                                                                                   
//                                           -> sysfs_make_dirent()                                           
//                                                                -> sysfs_new_dirent()                       
//                                                                -> dentry->d_fsdata = sysfs_get(sd);        
//                                                                -> dentry->d_op =                           
// &sysfs_dentry_ops;                                                                                         
//                                           -> (*d)->d_op = &sysfs_dentry_ops;                               
    135 int sysfs_create_dir(struct kobject * kobj)                                                        
    136 {                                                                                                  
    137         struct dentry * dentry = NULL;                                                             
    138         struct dentry * parent;                                                                    
    139         int error = 0;                                                                             
    140                                                                                                    
    141         BUG_ON(!kobj);                                                                             
    142                                                                                                    
    143         if (kobj->parent)                                                                          
    144                 parent = kobj->parent->dentry;                                                     
    145         else if (sysfs_mount && sysfs_mount->mnt_sb)                                               
    146                 parent = sysfs_mount->mnt_sb->s_root;                                              
    147         else                                                                                       
    148                 return -EFAULT;                                                                    
    149                                                                                                    
    150         error = create_dir(kobj,parent,kobject_name(kobj),&dentry);                                
    151         if (!error)                                                                                
    152                 kobj->dentry = dentry;                                                             
    153         return error;                                                                              
    154 }                                                                                                  
143-148�����ҵ������� kobject���ٵ���create_dir()��                                                        
     95 static int create_dir(struct kobject * k, struct dentry * p,                                       
     96                       const char * n, struct dentry ** d)                                          
�� 28  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
     97 {                                                                                                  
     98         int error;                                                                                 
     99         umode_t mode = S_IFDIR| S_IRWXU | S_IRUGO | S_IXUGO;                                       
    100                                                                                                    
    101         down(&p->d_inode->i_sem);                                                                  
    102         *d = sysfs_get_dentry(p,n);                                                                
    103         if (!IS_ERR(*d)) {                                                                         
    104                 error = sysfs_create(*d, mode, init_dir);                                          
    105                 if (!error) {                                                                      
    106                         error = sysfs_make_dirent(p->d_fsdata, *d, k, mode,                        
    107                                                 SYSFS_DIR);                                        
    108                         if (!error) {                                                              
    109                                 p->d_inode->i_nlink++;                                             
    110                                 (*d)->d_op = &sysfs_dentry_ops;                                    
    111                                 d_rehash(*d);                                                      
    112                         }                                                                          
    113                 }                                                                                  
    114                 if (error && (error != -EEXIST))                                                   
    115                         d_drop(*d);                                                                
    116                 dput(*d);                                                                          
    117         } else                                                                                     
    118                 error = PTR_ERR(*d);                                                               
    119         up(&p->d_inode->i_sem);                                                                    
    120         return error;                                                                              
    121 }                                                                                                  
// 99�У����á��ļ��� ���ԣ�101��ȡ�ź�����                                                                   
// (1)sysfs_get_dentry()                                                                                      
// 102�� sysfs_get_dentry()�����������Ǹ��ݸ��� dentry ���ļ����õ� dentry�ṹ������                          
// �ڻ������ң�����ҵ��ͷ��أ��Ҳ������� d_alloc()�½�һ�� dentry �ṹ���������½��ļ�                       
// �У���������Ȼ��û�еģ�����Ҫ�� d_alloc()���½�һ�����������ǵ��� lookup ����������                       
// �����¡�                                                                                                   
struct inode_operations sysfs_dir_inode_operations = {                                                     
             .lookup = sysfs_lookup,                                                                       
};                                                                                                         
                                                                                                           
    204 static struct dentry * sysfs_lookup(struct inode *dir, struct dentry *dentry,                      
    205                                 struct nameidata *nd)                                              
    206 {                                                                                                  
    207         struct sysfs_dirent * parent_sd = dentry->d_parent->d_fsdata;                              
    208         struct sysfs_dirent * sd;                                                                  
    209         int err = 0;                                                                               
    210                                                                                                    
    211         list_for_each_entry(sd, &parent_sd->s_children, s_sibling) {                               
�� 29  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
    212                 if (sd->s_type & SYSFS_NOT_PINNED) {                                               
    213                         const unsigned char * name = sysfs_get_name(sd);                           
    214                                                                                                    
    215                         if (strcmp(name, dentry->d_name.name))                                     
    216                                 continue;                                                          
    217                                                                                                    
    218                         if (sd->s_type & SYSFS_KOBJ_LINK)                                          
    219                                 err = sysfs_attach_link(sd, dentry);                               
    220                         else                                                                       
    221                                 err = sysfs_attach_attr(sd, dentry);                               
    222                         break;                                                                     
    223                 }                                                                                  
    224         }                                                                                          
    225                                                                                                    
    226         return ERR_PTR(err);                                                                       
    227 }                                                                                                  
                                                                                                           
// ǰ�潲�� lookup���������á����� inode ������ļ����²�����û����Ϊ dentry.d                                
// name.name���ļ�������У��ͽ����Ӧ�� inode�ṹ����Ϣ�������ж��������������½�                            
// ���ļ��У����� lookup����������������������û���¡������һ����̲�ס�����һ��                            
// lookup������                                                                                               
//                                                                                                            
// sysfs �ļ�ϵͳ�У��ļ��е� inode �� dentry�ṹһֱ���Ǵ������ڴ��еģ����Բ����ٽ���                       
// ��ȡ�ˡ����ļ������ӵ� inode ������û�еģ���Ҫ�������ж���������� 212������жϵ�                        
// ���á����Կ�����������ļ��У�ѭ������ɶ��û����                                                           
// #define SYSFS_NOT_PINNED \                                                                                 
// (SYSFS_KOBJ_ATTR | SYSFS_KOBJ_BIN_ATTR | SYSFS_KOBJ_LINK)                                                  
// ���� sysfs�� lookup��������֮ͬ���������ļ�ϵͳ�� ext3 ��ʽ����ͨ�ļ��� inode������                        
// ������֮ʱ���Ѿ������ˡ����ǣ�sysfs��һ�������ڴ�����ͨ�ļ�ʱ��ֻ���ȴ���һ��                              
// sysfs_dirent�ṹ������inode �Ĺ������Ƴٵ� lookup��������ɵġ�����һ��                                    
// sysfs_create_file()�ῴ����һ�㡣                                                                          
//                                                                                                            
// sysfs_attach_attr()��sysfs_attach_link()�����þ��Ǹ���dentry��sysfs_dirent�½�һ                           
// �� inode��                                                                                                 
//                                                                                                            
// ��֮������ͨ�� sysfs_get_dentry()�õ���һ���½��� dentry �ṹ��                                            
// (2)sysfs_create()���� (104��)                                                                              
// sysfs_create()->sysfs_new_inode(mode) -> new_inode(sysfs_sb)                                               
// ����һ���µ������ڵ� inode��sysfs_sb �� sysfs �ĳ�����(super_block)�ṹ��mode����                          
// inode �����ԣ�����¼��������Ϣ�����磬�ļ�����(���ļ��У����ӣ�������ͨ�ļ�)��inode                        
// �������ߣ�����ʱ��ȵȡ�                                                                                   
// �� 30  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
// (3)sysfs make dirent()���� (104 ��)                                                                        
// ���ˣ����ǵõ���һ�� dirent�ṹ,��ʼ�����ٰ������ӵ��ϲ�Ŀ¼�� sysfs_dirent��                              
// s_children������ȥ�� sysfs_make_dirent()Ϊ�ո��½�������dentry����һ��dirent�ṹ��                         
// ���� dentry�� dirent��ϵ������                                                                             
// (4)�ܽ�                                                                                                    
// �� sysfs�´���һ��Ŀ¼���ṩ�ĺ����� sysfs_create_dir()��������dentry, dirent, inode                       
// �ṹ, ����֮������ӹ�ϵ��ͼ                                                                               
// 1                                                                                                          
//                                                                                                            
//                                                                                                            
// Sysfs������ͨ�ļ�                                                                                          
// �������İ������÷з����������������ô�ˣ�                                                           
// sysfs �ļ�ϵͳ�У���ͨ�ļ���Ӧ�� kobject �е����ԡ��� sysfs_create_file()���������£�                      
// sysfs_create_file(struct kobject * kobj, const struct attribute * attr)                                    
// �� 31  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
// �������Ĳ����� kobj�� attr�����У�kobject ��Ӧ�����ļ��У�attribute��Ӧ���Ǹ��ļ���                        
// �µ��ļ���                                                                                                 
// int sysfs_create_file(struct kobject * kobj, const struct attribute * attr)                                
// {                                                                                                          
//                     BUG_ON(!kobj || !kobj->dentry || !attr);                                               
//                     return sysfs_add_file(kobj->dentry, attr, SYSFS_KOBJ_ATTR);                            
// }                                                                                                          
// ��ֱ�ӵ��� sysfs_add_file()                                                                                
int sysfs_add_file(struct dentry * dir, const struct attribute * attr, int type)                           
{                                                                                                          
                    struct sysfs_dirent * parent_sd = dir->d_fsdata;                                       
                    umode_t mode = (attr->mode & S_IALLUGO) | S_IFREG;                                     
                    int error = 0;                                                                         
                    down(&dir->d_inode->i_sem);                                                            
                    error = sysfs_make_dirent(parent_sd, NULL, (void *) attr, mode,                        
type);                                                                                                     
                    up(&dir->d_inode->i_sem);                                                              
                    return error;                                                                          
}                                                                                                          
int sysfs_make_dirent(struct sysfs_dirent * parent_sd, struct dentry * dentry,                             
   void * element, umode_t mode, int type)                                                                 
{                                                                                                          
                  struct sysfs_dirent * sd;                                                                
                  sd = sysfs_new_dirent(parent_sd, element);                                               
                  if (!sd)                                                                                 
                                    return -ENOMEM;                                                        
                  sd->s_mode = mode;                                                                       
                  sd->s_type = type;                                                                       
                  sd->s_dentry = dentry;                                                                   
                  if (dentry) {                                                                            
                                    dentry->d_fsdata = sysfs_get(sd);                                      
                                    dentry->d_op = &sysfs_dentry_ops;                                      
                  }                                                                                        
                  return 0;                                                                                
}                                                                                                          
// sysfs_create_file()�����ǵ����� sysfs_make_dirent()������һ�� sysfs_dirent�ṹ����                         
// sysfs_create_dir()��ͬ��������û���� sysfs�ļ�ϵͳ�´��� inode �ṹ����������ͺ�                        
// �ˣ���sysfs_lookup()->sysfs_attach_attr()������ɵġ�                                                      
//                                                                                                            
// �� 32  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
// Sysfs�����ļ�������                                                                                        
// �ϻ�����˵������δ����ļ��к��ļ������Ƿ��֣��� sysfs�У�inode ������ô��Ҫ��������                       
// Ϊ������Ҫ��д����Ϣ�Ѿ������ڴ��У������Ѿ��γ��˲�νṹ������ֻ���� dentry���Ϳ�                        
// �� dentry->fsdata�������ҵ����Ƕ�Щ��Ϣ����Դ ---  sysfs_dirent�ṹ����Ҳ���Ҿ�����                        
// ��Ҫ�о� sysfs ��ԭ��֮һ����Ϊ���򵥣����Ҳ��漰�����Ӳ�����������Ǵ���������У�                        
// ���ǿ��԰��ļ�ϵͳ�е�һЩ�������ݽṹ������������������Զ�ȡ sysfs�ļ����ļ��е���                       
// ��Ϊ���ӣ������ļ��������̡���ô����д�����й��� symblink�Ķ�����ȫ�����Դ������ˡ�                        
// �����½��ļ���ʱ��������                                                                                   
//  inode->i_op = &sysfs_dir_inode_operations;                                                                
//  inode->i_fop = &sysfs_dir_operations;                                                                     
struct file_operations sysfs_dir_operations = {                                                            
        .open = sysfs_dir_open,                                                                            
        .release = sysfs_dir_close,                                                                        
        .llseek = sysfs_dir_lseek,                                                                         
        .read = generic_read_dir,                                                                          
        .readdir = sysfs_readdir,                                                                          
};                                                                                                         
��һ����̵ĳ�������ʵ�顣                                                                                 
//#include<sys/types.h>                                                                                      
//#include<dirent.h>                                                                                         
//#include<unistd.h>                                                                                         
int main(){                                                                                                
              DIR * dir;                                                                                   
              struct dirent *ptr;                                                                          
              dir = opendir("/sys/bus/");                                                                  
              while((ptr = readdir(dir))!=NULL){                                                           
                            printf("d_name :%s ",ptr->d_name);                                             
              }                                                                                            
              closedir(dir);                                                                               
              return -1;                                                                                   
}                                                                                                          
// ���û��ռ䣬�� gcc ����ִ�м��ɡ���������������������ʲô��                                                
// (1)sysfs_dir_open()                                                                                        
// ���Ǹ��û��ռ�ĳ��� opendir()��glibc�ĺ����� glibcҲ���������ı�׼c�⡣ ����opendir                     
// ()�������sysfs dir open ()����ͷ�ģ��ǻ���ȥ�� glibc �Ĵ��롣�ҾͲ��������...glibc ��                    
// �Դ� gnu ����վ���Լ�����Դ���룬���롣���� gdb ���ԣ��Ϳ��Կ��ø������                                   
// ������������:                                                                                              
// opendir("/sys/bus/") -> //�û��ռ�//                                                                       
// �� 33  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
// -> ϵͳ����->                                                                                              
// sys_open() -> filp_open()-> dentry_open() -> sysfs_dir_open()//�ں˿ռ�//                                  
static int sysfs_dir_open(struct inode *inode, struct file *file)                                          
{                                                                                                          
            struct dentry * dentry = file->f_dentry;                                                       
            struct sysfs_dirent * parent_sd = dentry->d_fsdata;                                            
            down(&dentry->d_inode->i_sem);                                                                 
            file->private_data = sysfs_new_dirent(parent_sd, NULL);                                        
            up(&dentry->d_inode->i_sem);                                                                   
            return file->private_data ? 0 : -ENOMEM;                                                       
}                                                                                                          
// �ں˿ռ�:�½�һ��dirent�ṹ�� ���븸����dentry�У���������ַ������file->private_data                       
// �С���� dirent �ľ������ô���ὲ��                                                                       
// �û��ռ�:�½���һ�� DIR �ṹ��DIR�ṹ���¡�                                                                
// #define __dirstream DIR                                                                                    
struct __dirstream                                                                                         
{                                                                                                          
             int fd; // File descriptor. //                                                                
             char *data; // Directory block. //                                                            
             size_t allocation; // Space allocated for the block. //                                       
             size_t size; // Total valid data in the block. //                                             
             size_t offset; // Current offset into the block. //                                           
             off_t filepos; // Position of next entry to read. //                                          
             __libc_lock_define (, lock) // Mutex lock for this structure. //                              
};                                                                                                         
// (2)sysfs_readdir()                                                                                         
// �������£�                                                                                                 
//                                                                                                            
// readdir(dir) -> getdents() ->//�û��ռ�//                                                                  
// -> ϵͳ����->                                                                                              
// sys32 readdir() -> vfs readdir() -> sysfs readdir()//�ں˿ռ�//                                            
// readdir(dir)��������е㸴�ӣ���Ȼ��main ������� whileѭ���У� readdir��ִ���˶�Σ�                      
// ���ǿ��� glibc ����Ĵ���                                                                                  
// readdir(dir){                                                                                              
//                 ......                                                                                     
//                 if (dirp->offset >= dirp->size){                                                           
//                 ......                                                                                     
//                 getdents()                                                                                 
//                 ......                                                                                     
//                 }                                                                                          
// �� 34  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
// ......                                                                                                     
// }                                                                                                          
// ʵ���ϣ�getdents() -> ... -> sysfs_readdir()ֻ�����������Σ�getdents()һ�ξͰ�����                         
// �����ݶ����꣬����DIR�ṹ���У�readdir()ֻ�Ǵ� DIR �ṹ����ÿ��ȡ��һ����                                  
// DIR(dirstream)�ṹ����һ���������ص�����filldir �����þ������������������ݡ��ڶ���                       
// ���� getdents()���û���DIR ��������ݶ����ˣ��������ֵ��� getdents()�������                               
// getdents()�ط���NULL��                                                                                     
static int sysfs_readdir(struct file * filp, void * dirent, filldir_t filldir)                             
{                                                                                                          
             struct dentry *dentry = filp->f_dentry;                                                       
             struct sysfs_dirent * parent_sd = dentry->d_fsdata;                                           
             struct sysfs_dirent *cursor = filp->private_data;                                             
             struct list_head *p, *q = &cursor->s_sibling;                                                 
             ino_t ino;                                                                                    
             int i = filp->f_pos;                                                                          
             switch (i) {                                                                                  
                          case 0:                                                                          
                          ino = dentry->d_inode->i_ino;                                                    
                          if (filldir(dirent, ".", 1, i, ino, DT_DIR) < 0)                                 
                                       break;                                                              
                          filp->f_pos++;                                                                   
                          i++;                                                                             
                          // fallthrough //                                                                
                          case 1:                                                                          
                          ino = parent_ino(dentry);                                                        
                          if (filldir(dirent, "..", 2, i, ino, DT_DIR) < 0)                                
                                       break;                                                              
                          filp->f_pos++;                                                                   
                          i++;                                                                             
                          // fallthrough //                                                                
                          default:                                                                         
                          if (filp->f_pos == 2) {                                                          
                                       list_del(q);                                                        
                                       list_add(q, &parent_sd->s_children);                                
                          }                                                                                
                          for (p=q->next; p!= &parent_sd->s_children; p=p->next) {                         
                                       struct sysfs_dirent *next;                                          
                                       const char * name;                                                  
                                       int len;                                                            
                                       next = list_entry(p, struct sysfs_dirent, s_sibling);               
                                       if (!next->s_element)                                               
                                                    continue;                                              
                                       name = sysfs_get_name(next);                                        
�� 35  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
                                       len = strlen(name);                                                 
                                       if (next->s_dentry)                                                 
                                                    ino = next->s_dentry->d_inode->i_ino;                  
                                       else                                                                
                                                    ino = iunique(sysfs_sb, 2);                            
                                       if (filldir(dirent, name, len, filp->f_pos, ino,dt_type(n           
ext)) < 0)                                                                                                 
                                                    return 0;                                              
                                       list_del(q);                                                        
                                       list_add(q, p);                                                     
                                       p = q;                                                              
                                       filp->f_pos++;                                                      
                          }                                                                                
             }                                                                                             
return 0;                                                                                                  
}                                                                                                          
// �� sysfs_readdir()��ʵ�ܼ򵥣������Ǵ����ǵ��� sysfs_dir_open()ʱ�½���һ��                                
// sysfs_dirent�ṹ��ʼ��������ǰ dentry->dirent�µ������� sysfs_dirent�ṹ���������֣�                       
// �ٻص����� filldir()���ļ������ļ����͵���Ϣ������һ���ĸ�ʽд��ĳ����������                               
// һ�����͵� filldir()���� filldir64()���������õİ�һ����ʽ�򻺳���д���ݣ��ٰ����ݸ��Ƶ�                   
// �û��ռ�ȥ��                                                                                               
//                                                                                                            
// Sysfs������ͨ�ļ�����                                                                                      
// ���ϻ�һ�����������С��������                                                                             
// #include <stdio.h>                                                                                         
// #include <fcntl.h>                                                                                         
// #include <unistd.h>                                                                                        
int main(){                                                                                                
              char *name = "/sys/bus/ldd/version";                                                         
              char buf[500];                                                                               
              int fd;                                                                                      
              int size;                                                                                    
              fd = open(name, O_RDONLY);                                                                   
              printf("fd:%d ",fd);                                                                         
              size = read(fd,buf,sizeof(buf));                                                             
              printf("size:%d ",size);                                                                     
              printf("%s",buf);                                                                            
              close(fd);                                                                                   
�� 36  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
              return -1;                                                                                   
}                                                                                                          
                                                                                                           
// (1)sysfs_open_file()                                                                                       
// open() ->//�û��ռ�//                                                                                      
// -> ϵͳ����->                                                                                              
// sys_open() -> filp_open()-> dentry_open() -> sysfs_open_file()//�ں˿ռ�//                                 
//                                                                                                            
static int sysfs_open_file(struct inode * inode, struct file * filp)                                       
{                                                                                                          
             return check_perm(inode,filp);                                                                
}                                                                                                          
static int check_perm(struct inode * inode, struct file * file)                                            
{                                                                                                          
    struct kobject *kobj = sysfs_get_kobject(file->f_dentry->d_parent);                                    
    struct attribute * attr = to_attr(file->f_dentry);                                                     
    struct sysfs_buffer * buffer;                                                                          
    struct sysfs_ops * ops = NULL;                                                                         
    int error = 0;                                                                                         
                                                                                                           
    if (!kobj || !attr)                                                                                    
        goto Einval;                                                                                       
                                                                                                           
    // Grab the module reference for this attribute if we have one //                                      
    if (!try_module_get(attr->owner)) {                                                                    
        error = -ENODEV;                                                                                   
        goto Done;                                                                                         
    }                                                                                                      
                                                                                                           
    // if the kobject has no ktype, then we assume that it is a subsystem                                  
     * itself, and use ops for it.                                                                         
     //                                                                                                    
    if (kobj->kset && kobj->kset->ktype)                                                                   
        ops = kobj->kset->ktype->sysfs_ops;                                                                
    else if (kobj->ktype)                                                                                  
        ops = kobj->ktype->sysfs_ops;                                                                      
    else                                                                                                   
        ops = &subsys_sysfs_ops;                                                                           
                                                                                                           
    // No sysfs operations, either from having no subsystem,                                               
     * or the subsystem have no operations.                                                                
     //                                                                                                    
�� 37  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
    if (!ops)                                                                                              
        goto Eaccess;                                                                                      
                                                                                                           
    // File needs write support.                                                                           
     * The inode's perms must say it's ok,                                                                 
     * and we must have a store method.                                                                    
     //                                                                                                    
    if (file->f_mode & FMODE_WRITE) {                                                                      
                                                                                                           
        if (!(inode->i_mode & S_IWUGO) || !ops->store)                                                     
            goto Eaccess;                                                                                  
                                                                                                           
    }                                                                                                      
                                                                                                           
    // File needs read support.                                                                            
     * The inode's perms must say it's ok, and we there                                                    
     * must be a show method for it.                                                                       
     //                                                                                                    
    if (file->f_mode & FMODE_READ) {                                                                       
        if (!(inode->i_mode & S_IRUGO) || !ops->show)                                                      
            goto Eaccess;                                                                                  
    }                                                                                                      
                                                                                                           
    // No error? Great, allocate a buffer for the file, and store it                                       
     * it in file->private_data for easy access.                                                           
     //                                                                                                    
    buffer = kmalloc(sizeof(struct sysfs_buffer),GFP_KERNEL);                                              
    if (buffer) {                                                                                          
        memset(buffer,0,sizeof(struct sysfs_buffer));                                                      
        init_MUTEX(&buffer->sem);                                                                          
        buffer->needs_read_fill = 1;                                                                       
        buffer->ops = ops;                                                                                 
        file->private_data = buffer;                                                                       
    } else                                                                                                 
        error = -ENOMEM;                                                                                   
    goto Done;                                                                                             
                                                                                                           
 Einval:                                                                                                   
    error = -EINVAL;                                                                                       
    goto Done;                                                                                             
 Eaccess:                                                                                                  
    error = -EACCES;                                                                                       
    module_put(attr->owner);                                                                               
 Done:                                                                                                     
�� 38  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
    if (error && kobj)                                                                                     
        kobject_put(kobj);                                                                                 
    return error;                                                                                          
}                                                                                                          
// check_perm()���һ��Ȩ�ޣ�����һ�� sysfs�Ļ����� sysfs_buffer buffer����������                             
// sysfs_ops sysfs_buffer->ops����������������sysfs_buffer->ops�����ó�                                   
// bus_sysfs_ops�������file->private_data = buffer��                                                         
// (2)sysfs read file()                                                                                       
//                                                                                                            
// �������£�                                                                                                 
// read()->//�û��ռ�//                                                                                       
// -> ϵͳ����->                                                                                              
// sys_read() -> vfs_read() -> sysfs_read_file()//�ں˿ռ�//                                                  
// ���� sysfs_read_file()������                                                                               
 static ssize_t                                                                                             
sysfs_read_file(struct file *file, char __user *buf, size_t count, loff_t *ppos)                           
{                                                                                                          
    struct sysfs_buffer * buffer = file->private_data;                                                     
    ssize_t retval = 0;                                                                                    
                                                                                                           
    down(&buffer->sem);                                                                                    
    if (buffer->needs_read_fill) {                                                                         
        if ((retval = fill_read_buffer(file->f_dentry,buffer)))                                            
            goto out;                                                                                      
    }                                                                                                      
    pr_debug("%s: count = %d, ppos = %lld, buf = %s ",                                                     
         __FUNCTION__,count,*ppos,buffer->page);                                                           
    retval = flush_read_buffer(buffer,buf,count,ppos);                                                     
out:                                                                                                       
    up(&buffer->sem);                                                                                      
    return retval;                                                                                         
}                                                                                                          
// ˳�� sysfs_read_file()�����ߣ�                                                                             
// sysfs_read_file()                                                                                          
//               ---> fill_read_buffer()                                                                      
//                             ---> sysfs_buffer->bus_sysfs_ops->bus_attr_show()                              
//                                         ---> bus_attribute->show_bus_version() //ע�������                
// ���������� lddbus.c ���涨���                                                                             
//               ---> flush_read_buffer()                                                                     
// fill_read_buffer()���������Ķ����������ݶ��� sysfs ����Ļ����� sysfs_buffer��                             
// flush_read_buffer()�ǰѻ�����copy���û��ռ䡣��ϸ�����ҾͲ����ˡ�                                          
// �� 39  ҳ  �� 40  ҳ Linux��Щ�¶�֮����Sysfs                                                              
//                                                                                                            
// ���                                                                                                       
//        ���� sysfs �Ľ��ܾ͵�����ıʲ��������Ĭ��ϣ����д����Щ���˶Դ������������                   
// �������Ѷ���������һ���£�д����������һ���¡�д������Ѫ...����д�ù����У�����ʹ��                        
// ����������һ�㣬�����߼����������㲻���������棬ѧϰlinux�ں���õķ�������Reading                       
// the f**king source code�� �Ƽ���source insight�����룬��� KDB���ԣ�ͦ����ġ���                           
// �⣬���� linux �ں˴��룬��ð�glibc �Ĵ���Ҳ�����������Լ�����һ�顣�����Ļ������û�                      
// �ռ�Ϳ����� gdb����ĵ��ԡ�                                                                               
//          ��������ȥĸУ BBS�����������һ�䣬�������������С mm�ǵ�"�������"�� "XX                       
// ���� XX�����Ը�Ƚ�"�Ȼ��⣬������������������Ҫ�ǻ첻��ȥ�ˣ�����ȥ�������ˣ����                         
// ��������ǰ;���ˡ����߾�ȥдд����£���ʲô���ƣ���Ĺ�ʼǣ�Ҳ��һ���֣���ֻҪ��                       
// ̫�࣬д��Խ���棬Խ���죬������Խ�ࡣ��Ҳ��ϲ���������Ǻ���ʵ����̫�����ˡ�����Ͱ�                       
// ���ˣ�17��Ҳ��Ҫ�ٿ��ˣ�����ͦ��ġ��ؼ��������Լ������顣                                                 
//         ��л��ҵ�֧�֣�ֻҪ���˿������Ǿͻ������ȥ����Ȼ�Ƚ����࣬���������塣��ģ�                     
// ����ǣ�������ȴ���������˼���ˡ������������ݱ��裬�������֣���ᷢ�֣���Դ����͸�                       
// �����»�һ���򵥡�                                                                                         
// �� ����                                                                                                    
// �� ʵ��                                                                                                    
// ֪�к�һ                                                                                                   
//                                                                                                            
// �� 40  ҳ  �� 40  ҳ                                                                                       