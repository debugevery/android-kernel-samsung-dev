// Linux  ��Щ�¶�֮���� Block��                                                                                                                                         
// �� 1 ҳ �� 117  ҳ                                                                                                                                                    
//                                                                                                                                                                       
//                                                                                                                                                                       
//                                                                                                                                                                       
//                                                                                                                                                                       
// Linux��Щ�¶�                                                                                                                                                         
// ϵ�д���                                                                                                                                                              
// ֮                                                                                                                                                                    
// ����Block��                                                                                                                                                           
//                                                                                                                                                                       
// �Ӵ��Block��,                                                                                                                                                        
// ����Linux�ں�2.6.22.1��Block IO layer�Ĺ���                                                                                                                           
// ��ԭ��Ϊblog.csdn.net/fudan_abc �ϵġ�linux ��Щ�¶�֮����Block�㡷�����������µĻ�������������Ŀ���                                                                 
// ���������ͣ�Ҳ����email ��ilttv.cn@gmail.com   Linux  ��Щ�¶�֮���� Block��                                                                                          
// �� 2 ҳ �� 117  ҳ                                                                                                                                                    
// Ŀ¼                                                                                                                                                                  
// Ŀ¼..................................................................................................................................................2               
// ����..................................................................................................................................................3               
// Block��ϵͳ�ĳ�ʼ��.....................................................................................................................4                             
// ע��һ�����豸����.......................................................................................................................9                            
// ��������һ��Ϸ,�ڴ�����Ϊ�İ�?..............................................................................................12                                        
// Ũ�����Ǿ���?(һ)........................................................................................................................14                           
// Ũ�����Ǿ���?(��)........................................................................................................................19                           
// Ũ�����Ǿ���?(��)........................................................................................................................35                           
// scsi�����ǰ������(һ)................................................................................................................47                              
// scsi�����ǰ������(��)................................................................................................................57                              
// scsi�����ǰ������(��)................................................................................................................77                              
// scsi�����ǰ������(��)................................................................................................................84                              
// ��˵�е��ڴ�ӳ��(��)..................................................................................................................98                              
// ��˵�е��ڴ�ӳ��(��)................................................................................................................113 Linux  ��Щ�¶�֮���� Block�� 
// �� 3 ҳ �� 117  ҳ                                                                                                                                                    
//                                                                                                                                                                       
// ����                                                                                                                                                                  
// �ܾ���ǰ,�컹������,ˮҲ���̵�,ׯ���ǳ��ڵ����,�����ǿ��Է��ĳԵ�,���ӻ�����è��,                                                                                    
// ��ͥ�ǽ����,�ϴ����Ƚ���,������ֻ������,ҩ�ǿ����β���,ҽ���Ǿ������˵�,��                                                                                     
// ��Ӱ�ǲ���Ҫ�㵼��˯����,������Ҫ���·���,ǷǮ��Ҫ����,���ӵİְ�����ȷ��,ѧУ��                                                                                      
// ��ͼ��Ǯ��,�׳��ǲ��ܵ����ڵ�,�������ǲ��ܹ���ͷ��,�о����е�Ů�ľ���Ů��.��ʱ��                                                                                      
// Block �㻹��һ���ָ����� drivers/Ŀ¼��һ���ָ����� fs/Ŀ¼�µ�.                                                                                                      
// ������һ�ж�����.2005 ������,Block ������ drivers/�� fs/Ŀ¼,�� 2.6.15 ���ں˿�ʼ,����                                                                              
// Ŀ¼��������һ������ block ��Ŀ¼,�ں�Ŀ¼�ṹ����������������:                                                                                                     
// localhost-1:/usr/src/linux-2.6.22.1 # ls                                                                                                                              
// COPYING  Documentation  MAINTAINERS  README  arch   crypto   fs       init                                                                                            
// kernel  mm   scripts   sound  CREDITS  Kbuild Makefile  REPORTING-BUGS  block                                                                                         
// drivers  include  ipc   lib     net  security  usr                                                                                                                    
// ���� block Ŀ¼,���Թ⿴һ��:                                                                                                                                         
// localhost:/usr/src/linux-2.6.22.1/block # ls                                                                                                                          
// Kconfig          Makefile      blktrace.c     deadline-iosched.c  genhd.c  ll_rw_blk.c                                                                                
// scsi_ioctl.c                                                                                                                                                          
// Kconfig.iosched  as-iosched.c  cfq-iosched.c  elevator.c          ioctl.c  noop-iosched.c                                                                             
// �� wc ����ͳ��һ��:                                                                                                                                                   
// localhost:/usr/src/linux-2.6.22.1/block # wc -l *                                                                                                                     
//     54 Kconfig                                                                                                                                                        
//     73 Kconfig.iosched                                                                                                                                                
//     12 Makefile                                                                                                                                                       
//   1485 as-iosched.c                                                                                                                                                   
//    562 blktrace.c                                                                                                                                                     
//   2254 cfq-iosched.c                                                                                                                                                  
//    485 deadline-iosched.c                                                                                                                                             
//   1160 elevator.c                                                                                                                                                     
//    831 genhd.c                                                                                                                                                        
//    304 ioctl.c                                                                                                                                                        
//   4117 ll_rw_blk.c                                                                                                                                                    
//    118 noop-iosched.c                                                                                                                                                 
//    654 scsi_ioctl.c                                                                                                                                                   
//  12109 total                                                                                                                                                          
// һ���ǧ����.�������ǲ���ÿ���ļ���ȥ��.                                                                                                                              
// �Ϲ��,�ȿ�һ�� Makefile �� Kconfig,                                                                                                                                  
// localhost:/usr/src/linux-2.6.22.1/block # cat Makefile                                                                                                                
// #                                                                                                                                                                     
// # Makefile for the kernel block layer                                                                                                                                 
// #                                                                                                                                                                     
//   Linux  ��Щ�¶�֮���� Block��                                                                                                                                       
// �� 4 ҳ �� 117  ҳ                                                                                                                                                    
// obj-$(CONFIG_BLOCK) := elevator.o ll_rw_blk.o ioctl.o genhd.o scsi_ioctl.o                                                                                            
//                                                                                                                                                                       
// obj-$(CONFIG_IOSCHED_NOOP)      += noop-iosched.o                                                                                                                     
// obj-$(CONFIG_IOSCHED_AS)        += as-iosched.o                                                                                                                       
// obj-$(CONFIG_IOSCHED_DEADLINE)  += deadline-iosched.o                                                                                                                 
// obj-$(CONFIG_IOSCHED_CFQ)       += cfq-iosched.o                                                                                                                      
//                                                                                                                                                                       
// obj-$(CONFIG_BLK_DEV_IO_TRACE)  += blktrace.o                                                                                                                         
// ����Ȼ,�����ڵ���վ��ߺ����˵���»����˵���λ�����ĸ��Ƕ�Ҳ֪��,��������Ҫ��һ��                                                                                      
// ѡ���� CONFIG_BLOCK,��ʣ�¼������ǿ�һ�� Kconfig �Լ� Kconfig.iosched ��֪��,�Ǻ�                                                                                     
// IO�����㷨�йص�,����һ��ÿ���㷨��Ҫ���,������һ�־ʹպ���.                                                                                                         
// ��ô����Block��ϵͳ�������������?һ·�������ֵ����Ų����ҵ�,��block/genhd.c����                                                                                      
// ��ôһ��:                                                                                                                                                             
//     363 subsys_initcall(genhd_device_init);                                                                                                                           
// ���Ժ�����,genhd_device_init ��Ϊ�����ƿ����µĴ�Ļ.                                                                                                                  
//                                                                                                                                                                       
// Block��ϵͳ�ĳ�ʼ��                                                                                                                                                   
// �������Ǵ� genhd_device_init()��ʼ����.                                                                                                                               
    350 static int __init genhd_device_init(void)                                                                                                                     
    351 {                                                                                                                                                             
    352         int err;                                                                                                                                              
    353                                                                                                                                                               
    354         bdev_map = kobj_map_init(base_probe, &block_subsys_lock);                                                                                             
    355         blk_dev_init();                                                                                                                                       
    356         err = subsystem_register(&block_subsys);                                                                                                              
    357         if (err < 0)                                                                                                                                          
    358                 printk(KERN_WARNING "%s: subsystem_register error: %d\n",                                                                                     
    359                         __FUNCTION__, err);                                                                                                                   
    360         return err;                                                                                                                                           
    361 }                                                                                                                                                             
// �����ʼ�������������ۼ�,Ȼ��,�����Ӱ<<ʮ�ְ�>>����˵��һ��,��ʱ�򿴵��Ĳ�һ                                                                                       
// �������,��Ĳ�һ�����ĵ�.�����һ�û���̵�ʱ��,�Ҿ���˵��Block��ϵͳ�������ε�                                                                                      
// ����,�պ������� ll_rw_blk.c �������ε����,Ҳ����ʱ��,���Ǹ����,����,����������ʮ                                                                                  
// �����������������,���ڳɹ��ı���������ӹ��!�������ڵ���Ҫ�뿴���������治                                                                                        
// �Ǽ����׵��¶�.                                                                                                                                                       
// ���ȹ�ע���� block/ll_rw_blk.c �е�blk_dev_init().                                                                                                                    
   3700 int __init blk_dev_init(void)                                                                                                                                 
   3701 {                                                                                                                                                             
   3702         int i;                                                                                                                                                
   3703                                                                                                                                                               
   3704         kblockd_workqueue = create_workqueue("kblockd"); Linux  ��Щ�¶�֮���� Block��                                                                        
�� 5 ҳ �� 117  ҳ                                                                                                                                                    
   3705         if (!kblockd_workqueue)                                                                                                                               
   3706                 panic("Failed to create kblockd\n");                                                                                                          
   3707                                                                                                                                                               
   3708         request_cachep = kmem_cache_create("blkdev_requests",                                                                                                 
   3709                         sizeof(struct request), 0, SLAB_PANIC, NULL, NULL);                                                                                   
   3710                                                                                                                                                               
   3711         requestq_cachep = kmem_cache_create("blkdev_queue",                                                                                                   
   3712                          sizeof(request_queue_t), 0, SLAB_PANIC, NULL,                                                                                        
NULL);                                                                                                                                                                
   3713                                                                                                                                                               
   3714         iocontext_cachep = kmem_cache_create("blkdev_ioc",                                                                                                    
   3715                         sizeof(struct io_context), 0, SLAB_PANIC, NULL,                                                                                       
NULL);                                                                                                                                                                
   3716                                                                                                                                                               
   3717         for_each_possible_cpu(i)                                                                                                                              
   3718                 INIT_LIST_HEAD(&per_cpu(blk_cpu_done, i));                                                                                                    
   3719                                                                                                                                                               
   3720         open_softirq(BLOCK_SOFTIRQ, blk_done_softirq, NULL);                                                                                                  
   3721         register_hotcpu_notifier(&blk_cpu_notifier);                                                                                                          
   3722                                                                                                                                                               
   3723         blk_max_low_pfn = max_low_pfn - 1;                                                                                                                    
   3724         blk_max_pfn = max_pfn - 1;                                                                                                                            
   3725                                                                                                                                                               
   3726         return 0;                                                                                                                                             
   3727 }                                                                                                                                                             
// ���������Ȼ����,������������������ɿ����������,��ô����ȫ���ʸ��ڼ�������д��                                                                                      
// �Լ���ͨ Linux,��Ȼ������ɶҲ������д������ͨҲ������,�Ҿ���ô�ɵ�,����ǽ���.                                                                                        
// ���ȵ�һ������,create_workqueue()�ɵ�ʲô������Ҳ���Ǻ����,�����㲻Ҫ����ÿ����                                                                                    
// �� ps ������̵�ʱ���㶼�ܿ���һ������ kblockd �������.����:                                                                                                       
// [root@localhost ~]# ps -el | grep kblockd                                                                                                                             
// 1 S     0    80     2  0  70  -5 -     0 worker ?        00:00:00 kblockd/0                                                                                           
// 1 S     0    81     2  0  70  -5 -     0 worker ?        00:00:00 kblockd/1                                                                                           
// 1 S     0    82     2  0  70  -5 -     0 worker ?        00:00:00 kblockd/2                                                                                           
// 1 S     0    83     2  0  70  -5 -     0 worker ?        00:00:00 kblockd/3                                                                                           
// 1 S     0    84     2  0  70  -5 -     0 worker ?        00:00:00 kblockd/4                                                                                           
// 1 S     0    85     2  0  70  -5 -     0 worker ?        00:00:00 kblockd/5                                                                                           
// 1 S     0    86     2  0  70  -5 -     0 worker ?        00:00:00 kblockd/6                                                                                           
// 1 S     0    87     2  0  70  -5 -     0 worker ?        00:00:00 kblockd/7                                                                                           
// ������� kblockd ֮������ 8 ��,����Ϊ�ҵĻ������� 8 ��������.                                                                                                         
// ���ﷵ��ֵ������ kblocked_workqueue:                                                                                                                                  
//      64 static struct workqueue_struct *kblockd_workqueue;                                                                                                            
// ������,����kmem_cache_create()���ǵ�Ȼ�����ǳ��μ�����,�����������ǲ�����һ��Ч��.                                                                                    
// ���Ƽ�����ķ�����ʹ�� cat /proc/slabinfo ��һ��,�������������ʾ��������Ϣ̫���˵�,                                                                                  
// ��������������,�����Ҹ�������һ��,�� kdb ��ʹ�� slab ����.��Ȼ,Ŀ����һ����,����Ϊ��Linux  ��Щ�¶�֮���� Block��                                                     
// �� 6 ҳ �� 117  ҳ                                                                                                                                                    
// չʾ�� slab �ڴ�ķ���.������ kmem_cache_create ������ڴ�Ķ������������˰���.����                                                                                   
// ��������� blkdev_ioc,blkdev_requests,blkdev_queue.                                                                                                                   
// [0]kdb> slab                                                                                                                                                          
// name              actobj   nobj   size ob/sl pg/sl actsl   nsl                                                                                                        
// isofs_inode_cache      0      0    608    6    1      0      0                                                                                                        
// ext2_inode_cache       0      0    720    5    1      0      0                                                                                                        
// ext2_xattr             0      0     88   44    1      0      0                                                                                                        
// dnotify_cache          2     92     40   92    1      1      1                                                                                                        
// dquot                  0      0    256   15    1      0      0                                                                                                        
// eventpoll_pwq          1     53     72   53    1      1      1                                                                                                        
// eventpoll_epi          1     20    192   20    1      1      1                                                                                                        
// inotify_event_cache      0      0     40   92    1      0      0                                                                                                      
// inotify_watch_cache      1     53     72   53    1      1      1                                                                                                      
// kioctx                 0      0    320   12    1      0      0                                                                                                        
// kiocb                  0      0    256   15    1      0      0                                                                                                        
// fasync_cache           0      0     24  144    1      0      0                                                                                                        
// shmem_inode_cache    446    500    752    5    1    100    100                                                                                                        
// posix_timers_cache      0      0    128   30    1      0      0                                                                                                       
// uid_cache              8     30    128   30    1      1      1                                                                                                        
// ip_mrt_cache           0      0    128   30    1      0      0                                                                                                        
// tcp_bind_bucket       11    112     32  112    1      1      1                                                                                                        
// inet_peer_cache        0      0    128   30    1      0      0                                                                                                        
// secpath_cache          0      0     64   59    1      0      0                                                                                                        
// xfrm_dst_cache         0      0    384   10    1      0      0                                                                                                        
// ip_dst_cache          89    160    384   10    1     16     16                                                                                                        
// arp_cache              3     15    256   15    1      1      1                                                                                                        
// RAW                    9     10    768    5    1      2      2                                                                                                        
// UDP                   10     20    768    5    1      4      4                                                                                                        
// tw_sock_TCP            0      0    192   20    1      0      0                                                                                                        
// request_sock_TCP       0      0    128   30    1      0      0                                                                                                        
// TCP                   11     15   1536    5    2      3      3                                                                                                        
// blkdev_ioc            36    335     56   67    1      5      5                                                                                                        
// blkdev_queue          26     35   1576    5    2      7      7                                                                                                        
// blkdev_requests       77    168    272   14    1     12     12                                                                                                        
// ��Ȼ,�����������˺ܶ�ɾ��,����϶����г��ü�ҳ��.��˵���Ƕ��ܱ��˳��������е�ս                                                                                       
// ����,�����е� VIP,���ǱϾ���Ƥû����������ʦ��ô��,�Ͳ�����ô������.                                                                                                  
// 3717��,for_each_possible_cpu,���ÿ��cpu��ѭ��,����Ȼ,�����ߵ�����,smp�Ĵ���Ҳ����                                                                                    
// ��ȥ�Ӵ�һ����.��Ȼ���Ƕ����� smp,������������������,�����е��϶�׼�����˲��¹�,                                                                                      
// ��ʱ�˿�,���ǲ��ò�ȥ��� smp.                                                                                                                                        
// ������,open_softirq.��Ҳ��һ���ǻҼ��ĺ�����.���������ǿ���ʹ�����ж�����,��������                                                                                    
// �������� BLOCK_SOFTIRQ.׼ȷһ��˵ open_softirq �������ǳ�ʼ�� softirq.����������                                                                                      
// softirq�ĺ������պ����ǻ������raise_softirq()����raise_softirq_irqoff(),����������softirq                                                                            
// ��ʱ��,�������ﴫ�ݽ�ȥ�� blk_done_softirq()�����ͻᱻִ��.���˺�,����.                                                                                             
// Ȼ����,register_hotcpu_notifier().��ʵ˵,���û��һ��������ʡ�͵ĵ�,���������!����,��Linux  ��Щ�¶�֮���� Block��                                                   
// �� 7 ҳ �� 117  ҳ                                                                                                                                                    
// ����ô�����֮����ᷢ��,��ǰ������������Ըе�һ������,��Ϊ��ʵ��̫ǰ����,����                                                                                       
// ����Ϊ��֧�� CPU ���Ȳ��.Ҫ�����Ĵ���������,������ڱ����ں˵�ʱ��򿪱��뿪��                                                                                       
// CONFIG_HOTPLUG_CPU,������ֻ��һ���պ���.�����ҽ��������㲻������ô�Ըе�ѡ                                                                                            
// ���,��Ϊ��Ȳ�������ΰ,Ҳ����١��Ϊ.                                                                                                                                 
// ʣ������,max_low_pfn��ʾLow Memory����������ҳ֡��,(Page frame number of the last                                                                                   
// page frame directly mapped by the kernel(low memory))ȷ�е�˵��Low memory����������                                                                                 
// ҳ֡�ż��� 1.max_pfn ��ʾ���������ڴ�����һ�����õ�ҳ֡��(Page frame number of the                                                                                  
// last usable page frame),ȷ�е�˵ҲӦ�������һ�����õ�ҳ֡�ż��� 1.�������ȡ���ǲ���                                                                                 
// ���,Ҳ������Ϊ���,�������ﵱ block ��ҲҪ����Щ�����ʱ������ȼ����� 1.��ν��                                                                                      
// Low Memory,����Щ32λ�Ļ�����,���ҵļ�����,��ԼҲ����ָ��896M���µĲ���.������                                                                                        
// ������������� kdb �����һ�� max_low_pfn ���������ֵ.                                                                                                               
// [5]kdb> md max_low_pfn                                                                                                                                                
// c0809900 00038000 00000847 00100000 00000000   ....G...........                                                                                                       
// c0809910 00000000 00000000 00000000 00000000   ................                                                                                                       
// c0809920 00000000 00000000 00000000 00000000   ................                                                                                                       
// c0809930 00000000 00000000 00000000 00000000   ................                                                                                                       
// c0809940 0040029b 00000000 00000000 00000000   ..@.............                                                                                                       
// c0809950 00000000 00000000 00000000 00000000   ................                                                                                                       
// c0809960 00000000 00038000 00000000 00000180   ................                                                                                                       
// c0809970 00003135 030f6000 c06a2700 c06a2700   51...`...'j..'j.                                                                                                       
// ����,���Կ��� max_low_pfn ��ֵ��0x38000,����ʮ���ƾ��� 229376,���� Page Size,4k,�õ�                                                                                  
// 917504,���� 1024 �Ӷ��ѵ�λ���� M,�õ� 896,���Ժ���Ȼ,max_low_pfn ��־���� 896M ��                                                                                    
// �ϵ���һ�� page.�� blk_max_low_pfn������һ,���ÿ���������ʵ.                                                                                                          
// ������blk_dev_init()�����ٻص�genhd_device_init()����,����Ȼ,���ﻹ�������������ǲ�û                                                                                 
// �н�,һ����kobj_map_init(),һ����subsystem_register().���֮��,��ʵ���߸��������,ע��                                                                                
// һ����ϵͳ,�� Block ��ϵͳ.����ǰ��,��ʵ��ũ��ɽȪ,�е���.                                                                                                            
// ���������ں˴�����ᾪ�ȵķ���,�����ں˴�������� kobj_map_init()������Ȼֻ������                                                                                     
// ������.                                                                                                                                                               
// localhost:/usr/src/linux-2.6.22.1 # grep -r kobj_map_init *                                                                                                           
// block/genhd.c:  bdev_map = kobj_map_init(base_probe, &block_subsys_lock);                                                                                             
// drivers/base/map.c:struct kobj_map *kobj_map_init(kobj_probe_t *base_probe, struct mutex                                                                              
// *lock)                                                                                                                                                                
// fs/char_dev.c:  cdev_map = kobj_map_init(base_probe, &chrdevs_lock);                                                                                                  
// include/linux/kobj_map.h:struct kobj_map *kobj_map_init(kobj_probe_t *, struct mutex *);                                                                              
// ���Կ���,���������� drivers/base/map.c,�� include/linux/kobj_map.h ����������,����������                                                                              
// �ط����� block/genhd.c �� fs/char_dev.c,ǰ�����������������������.Ϊ���˽����������                                                                                 
// ��ʲô,������Ҫ����ʶһЩ�ṹ��,��һ��Ҫ��ʶ�ľ��� struct kobj_map,������                                                                                             
// drivers/base/map.c:                                                                                                                                                   
     19 struct kobj_map {                                                                                                                                             
     20         struct probe {                                                                                                                                        
     21                 struct probe *next;                                                                                                                           
     22                 dev_t dev;                                                                                                                                    
     23                 unsigned long range;                                                                                                                          
     24                 struct module *owner; Linux  ��Щ�¶�֮���� Block��                                                                                           
�� 8 ҳ �� 117  ҳ                                                                                                                                                    
     25                 kobj_probe_t *get;                                                                                                                            
     26                 int (*lock)(dev_t, void *);                                                                                                                   
     27                 void *data;                                                                                                                                   
     28         } *probes[255];                                                                                                                                       
     29         struct mutex *lock;                                                                                                                                   
     30 };                                                                                                                                                            
���������õ��� bdev_map ���� struct kobj_map �ṹ��ָ��,�Ͷ����� block/genhd.c:                                                                                       
    137 static struct kobj_map *bdev_map;                                                                                                                             
�� kobj_map_init()�Ķ����������ӵ�:                                                                                                                                   
    136 struct kobj_map *kobj_map_init(kobj_probe_t *base_probe, struct mutex *lock)                                                                                  
    137 {                                                                                                                                                             
    138         struct kobj_map *p = kmalloc(sizeof(struct kobj_map), GFP_KERNEL);                                                                                    
    139         struct probe *base = kzalloc(sizeof(*base), GFP_KERNEL);                                                                                              
    140         int i;                                                                                                                                                
    141                                                                                                                                                               
    142         if ((p == NULL) || (base == NULL)) {                                                                                                                  
    143                 kfree(p);                                                                                                                                     
    144                 kfree(base);                                                                                                                                  
    145                 return NULL;                                                                                                                                  
    146         }                                                                                                                                                     
    147                                                                                                                                                               
    148         base->dev = 1;                                                                                                                                        
    149         base->range = ~0;                                                                                                                                     
    150         base->get = base_probe;                                                                                                                               
    151         for (i = 0; i < 255; i++)                                                                                                                             
    152                 p->probes[i] = base;                                                                                                                          
    153         p->lock = lock;                                                                                                                                       
    154         return p;                                                                                                                                             
    155 }                                                                                                                                                             
// ���ó�,������һ�� struct kobj_map ��ָ�� p,Ȼ����󷵻ص�Ҳ�� p,������һ�ж��׸���                                                                                  
// bdev_kmap.�����������ɵ������޷Ǿ�����bdev_kmap->probes[]����ȫ������base.����֮,                                                                                     
// ���ǵ� get ָ��ȫ���������������ﴫ�ݽ����� base_probe ����,�������Ҳ���ܶ�,����                                                                                     
block/genhd.c:                                                                                                                                                        
    342 static struct kobject *base_probe(dev_t dev, int *part, void *data)                                                                                           
    343 {                                                                                                                                                             
    344         if (request_module("block-major-%d-%d", MAJOR(dev), MINOR(dev)) > 0)                                                                                  
    345                 // Make old-style 2.4 aliases work //                                                                                                         
    346                 request_module("block-major-%d", MAJOR(dev));                                                                                                 
    347         return NULL;                                                                                                                                          
    348 }                                                                                                                                                             
// ��������������ֵֹ�,��������������ȴֻʹ�����е�һ��,����ķ���ֵ������ struct                                                                                       
// kobject*ʵ����ȴƫƫֻ���� NULL.������������ɵ������������ڸ������Ƕ�����,����                                                                                       
// ����ѧ��ͬ�����γ̰�����ú�,�ҿ���Χ�����Ƕ���һ���������˷���������,ÿ���˶�                                                                                      
// �ֵֹ�,У԰�������ͬ������ζ��.������������ǹ�,�ܻ����е��߼�,ÿһ��ѧ��Ǯ����Linux  ��Щ�¶�֮���� Block��                                                         
// �� 9 ҳ �� 117  ҳ                                                                                                                                                    
// ʦ�Ǳ�<<C++������ƽ̳�>>�����˶���ܿ�����,����˳��������� C++�Ļ�����������                                                                                        
// �ֺ������ص�����.û��,���ֱ������ȷ��,�պ����ǻ᳹�����׵�.                                                                                                          
//                                                                                                                                                                       
// ע��һ�����豸����                                                                                                                                                    
// ������block��ϵͳ�ĳ�ʼ��֮��,����һ����ã��,Ҳ��շת����,Ҳ���������,����ȫ��֪                                                                                     
// ����һ������ô��,����˼��,˼�����Һ��й���δ��,�ǻ�����,�������,���ھ���,�� scsi                                                                                     
// disk ����ͬ������������,��Ϊ scsi disk �Ǳ߻������� block ������ṩ�ĺ���,��������                                                                                 
// ���������������Щ���������Ǹ�ʲô��.                                                                                                                                 
// ��һ��������Ȼ���� register_blkdev().                                                                                                                                 
     55 int register_blkdev(unsigned int major, const char *name)                                                                                                     
     56 {                                                                                                                                                             
     57         struct blk_major_name **n, *p;                                                                                                                        
     58         int index, ret = 0;                                                                                                                                   
     59                                                                                                                                                               
     60         mutex_lock(&block_subsys_lock);                                                                                                                       
     61                                                                                                                                                               
     62         // temporary //                                                                                                                                       
     63         if (major == 0) {                                                                                                                                     
     64                 for (index = ARRAY_SIZE(major_names)-1; index > 0; index--) {                                                                                 
     65                         if (major_names[index] == NULL)                                                                                                       
     66                                 break;                                                                                                                        
     67                 }                                                                                                                                             
     68                                                                                                                                                               
     69                 if (index == 0) {                                                                                                                             
     70                         printk("register_blkdev: failed to get major for %s\n",                                                                               
     71                                name);                                                                                                                         
     72                         ret = -EBUSY;                                                                                                                         
     73                         goto out;                                                                                                                             
     74                 }                                                                                                                                             
     75                 major = index;                                                                                                                                
     76                 ret = major;                                                                                                                                  
     77         }                                                                                                                                                     
     78                                                                                                                                                               
     79         p = kmalloc(sizeof(struct blk_major_name), GFP_KERNEL);                                                                                               
     80         if (p == NULL) {                                                                                                                                      
     81                 ret = -ENOMEM;                                                                                                                                
     82                 goto out;                                                                                                                                     
     83         }                                                                                                                                                     
     84                                                                                                                                                               
     85         p->major = major;                                                                                                                                     
     86         strlcpy(p->name, name, sizeof(p->name)); Linux  ��Щ�¶�֮���� Block��                                                                                
�� 10  ҳ �� 117  ҳ                                                                                                                                                  
     87         p->next = NULL;                                                                                                                                       
     88         index = major_to_index(major);                                                                                                                        
     89                                                                                                                                                               
     90         for (n = &major_names[index]; *n; n = &(*n)->next) {                                                                                                  
     91                 if ((*n)->major == major)                                                                                                                     
     92                         break;                                                                                                                                
     93         }                                                                                                                                                     
     94         if (!*n)                                                                                                                                              
     95                 *n = p;                                                                                                                                       
     96         else                                                                                                                                                  
     97                 ret = -EBUSY;                                                                                                                                 
     98                                                                                                                                                               
     99         if (ret < 0) {                                                                                                                                        
    100                 printk("register_blkdev: cannot get major %d for %s\n",                                                                                       
    101                        major, name);                                                                                                                          
    102                 kfree(p);                                                                                                                                     
    103         }                                                                                                                                                     
    104 out:                                                                                                                                                          
    105         mutex_unlock(&block_subsys_lock);                                                                                                                     
    106         return ret;                                                                                                                                           
    107 }                                                                                                                                                             
�� sd �Ǳߵ��������������,������ָ�������豸���˵�.����֮,����� major �Ƿ���ֵ,��                                                                                   
struct blk_major_name�Ķ���Ҳ�� block/genhd.c ��:                                                                                                                     
     27 static struct blk_major_name {                                                                                                                                
     28         struct blk_major_name *next;                                                                                                                          
     29         int major;                                                                                                                                            
     30         char name[16];                                                                                                                                        
     31 } *major_names[BLKDEV_MAJOR_HASH_SIZE];                                                                                                                       
// ע������˳�㶨����һ������ major_names,��������Ҳ�õ���.                                                                                                              
// ������ BLKDEV_MAJOR_HASH_SIZE ������ include/linux/fs.h:                                                                                                              
   1575 #define BLKDEV_MAJOR_HASH_SIZE  255                                                                                                                           
// ������ major_names[]�� 255 ��Ԫ��,����֮,���Ƕ����� 255 ��ָ��.                                                                                                       
// �� 88 �������������ͬ������ block/genhd.c:                                                                                                                           
     33 // index in the above - for now: assume no multimajor ranges //                                                                                               
     34 static inline int major_to_index(int major)                                                                                                                   
     35 {                                                                                                                                                             
     36         return major % BLKDEV_MAJOR_HASH_SIZE;                                                                                                                
     37 }                                                                                                                                                             
// �������Ǵ��ݵ� major�� 8,��ô major_to_index���� 8.                                                                                                                   
// �������,register_blkdev()������������������,Ϊ�� 255 ��ָ���ҵ�����.������ 79 �е�                                                                                 
// ��kmalloc����һ��struct blk_major_name�ṹ�岢����pָ����,������Ϊp��ֵ,��n��ָ                                                                                       
// �� major_names[index],���� index ���� 8,��ô n ��ָ�� major_names[8],һ��ʼ���϶�Ϊ��,                                                                                
// ����ֱ��ִ�� 94 �в����� 95 ��,���ǾͰѸ���ֵ�� p ���Ǹ��ṹ�帳���� major_names[8],                                                                                  
// ���,major_names[8]�ͼ��� majorҲ�� name ��,name ���ǡ�sd��. Linux  ��Щ�¶�֮���� Block��                                                                            
// �� 11  ҳ  �� 117 ҳ                                                                                                                                                  
// ��ô��ʱ�˿̵�Ч����ʲô?������,������/dev/Ŀ¼������ sda,sdb ֮����ļ�,����ͨ��                                                                                     
// /proc/devices�ܹ�����������豸����ע����.                                                                                                                            
// localhost:/usr/src/linux-2.6.22.1 # cat /proc/devices                                                                                                                 
// Character devices:                                                                                                                                                    
  1 mem                                                                                                                                                               
  2 pty                                                                                                                                                               
  3 ttyp                                                                                                                                                              
  4 /dev/vc/0                                                                                                                                                         
  4 tty                                                                                                                                                               
  4 ttyS                                                                                                                                                              
  5 /dev/tty                                                                                                                                                          
  5 /dev/console                                                                                                                                                      
  5 /dev/ptmx                                                                                                                                                         
  7 vcs                                                                                                                                                               
 10 misc                                                                                                                                                              
 13 input                                                                                                                                                             
 21 sg                                                                                                                                                                
 29 fb                                                                                                                                                                
128 ptm                                                                                                                                                               
136 pts                                                                                                                                                               
162 raw                                                                                                                                                               
180 usb                                                                                                                                                               
189 usb_device                                                                                                                                                        
254 megaraid_sas_ioctl                                                                                                                                                
                                                                                                                                                                      
Block devices:                                                                                                                                                        
  1 ramdisk                                                                                                                                                           
  3 ide0                                                                                                                                                              
  7 loop                                                                                                                                                              
  8 sd                                                                                                                                                                
  9 md                                                                                                                                                                
 65 sd                                                                                                                                                                
 66 sd                                                                                                                                                                
 67 sd                                                                                                                                                                
 68 sd                                                                                                                                                                
 69 sd                                                                                                                                                                
 70 sd                                                                                                                                                                
 71 sd                                                                                                                                                                
128 sd                                                                                                                                                                
129 sd                                                                                                                                                                
130 sd                                                                                                                                                                
131 sd                                                                                                                                                                
132 sd                                                                                                                                                                
133 sd Linux  ��Щ�¶�֮���� Block��                                                                                                                                  
�� 12  ҳ �� 117  ҳ                                                                                                                                                  
134 sd                                                                                                                                                                
135 sd                                                                                                                                                                
253 device-mapper                                                                                                                                                     
254 mdp                                                                                                                                                               
                                                                                                                                                                      
��������һ��Ϸ,�ڴ�����Ϊ�İ�?                                                                                                                                        
��һ������,alloc_disk().��sd.c �����Ǵ��ݽ����Ĳ����� 16.                                                                                                             
    720 struct gendisk *alloc_disk(int minors)                                                                                                                        
    721 {                                                                                                                                                             
    722         return alloc_disk_node(minors, -1);                                                                                                                   
    723 }                                                                                                                                                             
    724                                                                                                                                                               
    725 struct gendisk *alloc_disk_node(int minors, int node_id)                                                                                                      
    726 {                                                                                                                                                             
    727         struct gendisk *disk;                                                                                                                                 
    728                                                                                                                                                               
    729         disk = kmalloc_node(sizeof(struct gendisk), GFP_KERNEL, node_id);                                                                                     
    730         if (disk) {                                                                                                                                           
    731                 memset(disk, 0, sizeof(struct gendisk));                                                                                                      
    732                 if (!init_disk_stats(disk)) {                                                                                                                 
    733                         kfree(disk);                                                                                                                          
    734                         return NULL;                                                                                                                          
    735                 }                                                                                                                                             
    736                 if (minors > 1) {                                                                                                                             
    737                         int size = (minors - 1) * sizeof(struct hd_struct *);                                                                                 
    738                         disk->part = kmalloc_node(size, GFP_KERNEL,                                                                                           
node_id);                                                                                                                                                             
    739                         if (!disk->part) {                                                                                                                    
    740                                 kfree(disk);                                                                                                                  
    741                                 return NULL;                                                                                                                  
    742                         }                                                                                                                                     
    743                         memset(disk->part, 0, size);                                                                                                          
    744                 }                                                                                                                                             
    745                 disk->minors = minors;                                                                                                                        
    746                 kobj_set_kset_s(disk,block_subsys);                                                                                                           
    747                 kobject_init(&disk->kobj);                                                                                                                    
    748                 rand_initialize_disk(disk);                                                                                                                   
    749                 INIT_WORK(&disk->async_notify,                                                                                                                
    750                         media_change_notify_thread);                                                                                                          
    751         }                                                                                                                                                     
    752         return disk; Linux  ��Щ�¶�֮���� Block��                                                                                                            
�� 13  ҳ �� 117  ҳ                                                                                                                                                  
    753 }                                                                                                                                                             
// ������������������������һ��struct gendisk�ṹ��.��������,����ṹ�������������                                                                                    
// ��������Ҫ�Ľṹ��֮һ,���� include/linux/genhd.h:                                                                                                                    
    113 struct gendisk {                                                                                                                                              
    114         int major;                      // major number of driver //                                                                                          
    115         int first_minor;                                                                                                                                      
    116         int minors;                     // maximum number of minors, =1 for                                                                                   
    117                                          * disks that can't be partitioned. //                                                                                
    118         char disk_name[32];             // name of major driver //                                                                                            
    119         struct hd_struct **part;        // [indexed by minor] //                                                                                              
    120         int part_uevent_suppress;                                                                                                                             
    121         struct block_device_operations *fops;                                                                                                                 
    122         struct request_queue *queue;                                                                                                                          
    123         void *private_data;                                                                                                                                   
    124         sector_t capacity;                                                                                                                                    
    125                                                                                                                                                               
    126         int flags;                                                                                                                                            
    127         struct device *driverfs_dev;                                                                                                                          
    128         struct kobject kobj;                                                                                                                                  
    129         struct kobject *holder_dir;                                                                                                                           
    130         struct kobject *slave_dir;                                                                                                                            
    131                                                                                                                                                               
    132         struct timer_rand_state *random;                                                                                                                      
    133         int policy;                                                                                                                                           
    134                                                                                                                                                               
    135         atomic_t sync_io;               // RAID //                                                                                                            
    136         unsigned long stamp;                                                                                                                                  
    137         int in_flight;                                                                                                                                        
    138 #ifdef  CONFIG_SMP                                                                                                                                            
    139         struct disk_stats *dkstats;                                                                                                                           
    140 #else                                                                                                                                                         
    141         struct disk_stats dkstats;                                                                                                                            
    142 #endif                                                                                                                                                        
    143         struct work_struct async_notify;                                                                                                                      
    144 };                                                                                                                                                            
// ��Ϊminors���Ǹ�����16,����736�е�if���϶��������.����size����15��sizeof(struct                                                                                    
// hd_struct *),��part���ǿ�����struct hd_struct�Ķ���ָ��,�������ǿ���kmalloc_node(),���                                                                               
// �����е�node/node_id��Щ����ָ����NUMA�����еĽڵ�,����������Щ�����Ͳ���Ӵ�                                                                                         
// NUMA ������˵ kmalloc_node()�͵��� kmalloc(),����������ľ��������ڴ沢�ҳ�ʼ��Ϊ                                                                                     
// 0.Ҫ˵����һ����,part ���� partition����˼,�պ������������ǳ�˵�ķ����Ľ�ɫ.                                                                                          
// Ȼ��,disk->minors����Ϊ�� 16.                                                                                                                                         
// 746 ��,kobj_set_kset_s(),block_subsys ������ǰ��ע�����ϵͳ,�����ݽṹ��˵,���Ķ�����                                                                                
// ��,���� block/genhd.c:                                                                                                                                                
//      20 struct kset block_subsys; Linux  ��Щ�¶�֮���� Block��                                                                                                       
// �� 14  ҳ �� 117  ҳ                                                                                                                                                  
// ��ʵҲ����һ�� struct kset.������� kobj_set_kset_s �����þ����� disk ��Ӧ kobject �� kset                                                                            
// ���� block_subsys.Ҳ����˵�� kobject �ҵ����� kset.(����㻹�ǵõ������������� Sysfs ��                                                                               
// ������ kobject �� kset ���������۵Ļ�,�㲻�᲻�����������ͼ.)�� kobject_init()��ʼ��һ                                                                               
// �� kobject,�������ͨ�����ǳ����������� kobject ��kset ֮��.                                                                                                          
// ���ѡ�����δ�족�������,��˵���д��벢���Ƕ���һ���ṹ��.��������һ������,������                                                                                     
// �Ƕ���.����ϸһ��,�ƺ�����ǵ�,�����ȷ������,�����岢��������,Linux �ں˴����ȷ                                                                                     
// ������ʵʵ����ټ�,һ��С�ľͻῴ����,д����ĸ��Ƕ���Ȼ�����ϱ�����թ�ĵ���.��                                                                                       
// Ը����ֻ�ǽ�˱�����Ƕ���ʵ���Ĳ�����,�Ͼ�������ͷ,ֻ�мٻ������,��Ķ��Ǽ�                                                                                       
// ��.��ô������������?ͬһ���ļ���:                                                                                                                                     
//     610 decl_subsys(block, &ktype_block, &block_uevent_ops);                                                                                                          
// ��� decl_subsys ���� include/linux/kobject.h:                                                                                                                        
    173 #define decl_subsys(_name,_type,_uevent_ops) \                                                                                                                
    174 struct kset _name##_subsys = { \                                                                                                                              
    175         .kobj = { .name = __stringify(_name) }, \                                                                                                             
    176         .ktype = _type, \                                                                                                                                     
    177         .uevent_ops =_uevent_ops, \                                                                                                                           
    178 }                                                                                                                                                             
��������Ķ���,����֪��,���ǵ�Ч������������ôһ������:                                                                                                             
    174 struct kset block_subsys = { \                                                                                                                                
    175         .kobj = { .name = __stringify(block) }, \                                                                                                             
    176         .ktype = &ktype_block, \                                                                                                                              
    177         .uevent_ops = &block_uevent_ops, \                                                                                                                    
    178 }                                                                                                                                                             
// ������Ϊ������ôһ������,������Ϊ�������ǰѡ�block������ block_subsys �� kobj �� name                                                                                 
// ��Ա,���Ե������� block ��ϵͳ��ʼ����ʱ����� subsystem_register(&block_subsys)֮��,                                                                                 
// ���ǲŻ���/sys/Ŀ¼���濴����block����Ŀ¼.                                                                                                                           
// localhost:~ # ls /sys/                                                                                                                                                
// block  bus  class  devices  firmware  fs  kernel  module  power                                                                                                       
// 749 ��,��ʼ��һ����������.��ʱ���õ���������.                                                                                                                         
// ����,alloc_disk_node �ͽ�����,�Ӷ� alloc_disk Ҳ�ͷ�����.                                                                                                             
//                                                                                                                                                                       
// Ũ�����Ǿ���?(һ)                                                                                                                                                     
// ��,���ڴ���,���ڴ���;��������,�����ڴ���.��仰�ǳ��е���.����˵���е���,��,�Ҳ���                                                                                    
// ��ô��Ϊ.����Ϊ�������ڴ���һ�߿� A Ƭһ�߿�����,���Զ���仰�������,��ʵ������                                                                                      
// ��������������ڴ��Ͽ�����ʱ���ӵ�����,˵��������,һ��Ҳ������,�����ǵ��ҿ���                                                                                         
// add_disk()����ޱȱ�̬�ĺ�����ʱ��.�Ҳ����п�,�ϵ���ʹ������,����ʹ����;�ϵ���ʹ                                                                                    
// �˷��,����ʹ�俴 Linux �ں˴���.                                                                                                                                     
    175 ///                                                                                                                                                           
    176 * add_disk - add partitioning information to kernel list                                                                                                      
    177 * @disk: per-device partitioning information                                                                                                                  
    178 * Linux  ��Щ�¶�֮���� Block��                                                                                                                               
�� 15  ҳ �� 117  ҳ                                                                                                                                                  
    179 * This function registers the partitioning information in @disk                                                                                               
    180 * with the kernel.                                                                                                                                            
    181 //                                                                                                                                                            
    182 void add_disk(struct gendisk *disk)                                                                                                                           
    183 {                                                                                                                                                             
    184         disk->flags |= GENHD_FL_UP;                                                                                                                           
    185         blk_register_region(MKDEV(disk->major, disk->first_minor),                                                                                            
    186                             disk->minors, NULL, exact_match, exact_lock, disk);                                                                               
    187         register_disk(disk);                                                                                                                                  
    188         blk_register_queue(disk);                                                                                                                             
    189 }                                                                                                                                                             
// ��ʵ˵����һ��ʼ�����������ֻ�����д����ʱ��,�Ҽ���ϲ������.���ܿ��Ҿͷ����Լ�                                                                                      
// ���뷨 Too Simple, Sometimes Naive ��.���������Ȼֻ�����д���,���ǳ�������,��������                                                                                  
// ����,һ����һ��ק,�ҽ�������,д����ĸ��Ƕ��б�Ҫд����Ũ����ĺ���ô?Ҫ��������                                                                                      
// ��ʦҲ��������ô���ְ�?                                                                                                                                               
// ͷһ��,blk_register_region,���� block/genhd.c:                                                                                                                        
    139 //                                                                                                                                                            
    140 * Register device numbers dev..(dev+range-1)                                                                                                                  
    141 * range must be nonzero                                                                                                                                       
    142 * The hash chain is sorted on range, so that subranges can override.                                                                                          
    143 //                                                                                                                                                            
    144 void blk_register_region(dev_t dev, unsigned long range, struct module *module,                                                                               
    145                          struct kobject *(*probe)(dev_t, int *, void *),                                                                                      
    146                          int (*lock)(dev_t, void *), void *data)                                                                                              
    147 {                                                                                                                                                             
    148         kobj_map(bdev_map, dev, range, module, probe, lock, data);                                                                                            
    149 }                                                                                                                                                             
���� kobj_map()��ʵ��Զ��������,������ drivers/base/map.c:                                                                                                            
     32 int kobj_map(struct kobj_map *domain, dev_t dev, unsigned long range,                                                                                         
     33              struct module *module, kobj_probe_t *probe,                                                                                                      
     34               int (*lock)(dev_t, void *), void *data)                                                                                                         
     35 {                                                                                                                                                             
     36         unsigned n = MAJOR(dev + range - 1) - MAJOR(dev) + 1;                                                                                                 
     37         unsigned index = MAJOR(dev);                                                                                                                          
     38         unsigned i;                                                                                                                                           
     39         struct probe *p;                                                                                                                                      
     40                                                                                                                                                               
     41         if (n > 255)                                                                                                                                          
     42                 n = 255;                                                                                                                                      
     43                                                                                                                                                               
     44         p = kmalloc(sizeof(struct probe) * n, GFP_KERNEL);                                                                                                    
     45                                                                                                                                                               
     46         if (p == NULL)                                                                                                                                        
     47                 return -ENOMEM; Linux  ��Щ�¶�֮���� Block��                                                                                                 
�� 16  ҳ �� 117  ҳ                                                                                                                                                  
     48                                                                                                                                                               
     49         for (i = 0; i < n; i++, p++) {                                                                                                                        
     50                 p->owner = module;                                                                                                                            
     51                 p->get = probe;                                                                                                                               
     52                 p->lock = lock;                                                                                                                               
     53                 p->dev = dev;                                                                                                                                 
     54                 p->range = range;                                                                                                                             
     55                 p->data = data;                                                                                                                               
     56         }                                                                                                                                                     
     57         mutex_lock(domain->lock);                                                                                                                             
     58         for (i = 0, p -= n; i < n; i++, p++, index++) {                                                                                                       
     59                 struct probe **s = &domain->probes[index % 255];                                                                                              
     60                 while (*s && (*s)->range < range)                                                                                                             
     61                         s = &(*s)->next;                                                                                                                      
     62                 p->next = *s;                                                                                                                                 
     63                 *s = p;                                                                                                                                       
     64         }                                                                                                                                                     
     65         mutex_unlock(domain->lock);                                                                                                                           
     66         return 0;                                                                                                                                             
     67 }                                                                                                                                                             
// ������ǵ�sd_probe��������,������sd_probe()��˵��,first_minor�޷Ǿ���0,16,32,48����                                                                                   
// һϵ�е���,�� minors ���� 16,����֮�����������ǵ������� range ���� 16,��������� n ֻ                                                                                 
// ���� 1.                                                                                                                                                               
// Domain ���� bdev_map,�������Ǽ��㲻������Ҳ�ܲµ�,�����������ҪĿ�ľ���Ϊ                                                                                            
// bdev_map��probes���ָ�����鸳ֵ,�������ǵ�major��8,��ô�������Ϊprobes[8]��ֵ.                                                                                      
// �Ա��β�ʵ�ο��Կ���,����Ϊ get ָ�븳���� exact_match().�������ͬ��������                                                                                           
// block/genhd.c:                                                                                                                                                        
    160 static struct kobject *exact_match(dev_t dev, int *part, void *data)                                                                                          
    161 {                                                                                                                                                             
   162         struct gendisk *p = data;                                                                                                                              
    163         return &p->kobj;                                                                                                                                      
    164 }                                                                                                                                                             
// ��,����˵���ǵ� index ����˵ major number�� 8 �Ļ�,��ô��֮��,bdev_map->probes[8]����                                                                                 
// Ӧ�� get ָ���ָ���� exact_match.                                                                                                                                    
// ͬʱ,data ָ�븳���� disk,�� struct gendisk ָ��disk.                                                                                                                 
// ��ʵ˵,����������ȫ��������ô��������,����˵ blk_register_region �������������ʲô                                                                                   
// ��ֵ������ȫ���ֲ�����.������ʵ���� Linux ��ʵ�ֵ�һ�ֹ����豸�ŵĻ���,����������                                                                                     
// ��˵�еĹ�ϣ���������豸��,��ϣ����ŵ���֪��,���ڲ���,�����ǵ�Ŀ����Ϊ��ͨ��                                                                                       
// ������һ���豸�ž���Ѹ�ٵõ�������Ӧ�� kobject ָ��,���ڿ��豸��˵,�õ� kobject ��Ϊ                                                                                  
// �˵õ����Ӧ�� gendisk.                                                                                                                                               
// ��ôʲôʱ�����Ҫ��������?Ok,������ִ�� fdisk �Cl /dev/sda,�Ӷ�openϵͳ���û���˵��                                                                                  
// �� sys_open �ᱻִ��,�����һ·����,��ᷢ�ֵ���������һ������ get_gendisk()�ĺ�����                                                                                  
// ����.�������ʵ����Ҳ��������߶����,����block/genhd.c:                                                                                                              
    203  Linux  ��Щ�¶�֮���� Block��                                                                                                                             
// �� 17  ҳ �� 117  ҳ                                                                                                                                                  
//     204 * get_gendisk - get partitioning information for a given device                                                                                               
//     205 * @dev: device to get partitioning information for                                                                                                            
//     206 *                                                                                                                                                             
//     207 * This function gets the structure containing partitioning                                                                                                    
//     208 * information for the given device @dev.                                                                                                                      
//     209                                                                                                                                                             
    210 struct gendisk *get_gendisk(dev_t dev, int *part)                                                                                                             
    211 {                                                                                                                                                             
    212         struct kobject *kobj = kobj_lookup(bdev_map, dev, part);                                                                                              
    213         return kobj ? to_disk(kobj) : NULL;                                                                                                                   
    214 }                                                                                                                                                             
// ������������ kobj_lookup().���� drivers/base/map.c:                                                                                                                   
     96 struct kobject *kobj_lookup(struct kobj_map *domain, dev_t dev, int *index)                                                                                   
     97 {                                                                                                                                                             
     98         struct kobject *kobj;                                                                                                                                 
     99         struct probe *p;                                                                                                                                      
    100         unsigned long best = ~0UL;                                                                                                                            
    101                                                                                                                                                               
    102 retry:                                                                                                                                                        
    103         mutex_lock(domain->lock);                                                                                                                             
    104         for (p = domain->probes[MAJOR(dev) % 255]; p; p = p->next) {                                                                                          
    105                 struct kobject *(*probe)(dev_t, int *, void *);                                                                                               
    106                 struct module *owner;                                                                                                                         
   107                 void *data;                                                                                                                                    
    108                                                                                                                                                               
    109                 if (p->dev > dev || p->dev + p->range - 1 < dev)                                                                                              
    110                         continue;                                                                                                                             
    111                 if (p->range - 1 >= best)                                                                                                                     
    112                         break;                                                                                                                                
    113                 if (!try_module_get(p->owner))                                                                                                                
    114                         continue;                                                                                                                             
    115                 owner = p->owner;                                                                                                                             
    116                 data = p->data;                                                                                                                               
    117                 probe = p->get;                                                                                                                               
    118                 best = p->range - 1;                                                                                                                          
   119                 *index = dev - p->dev;                                                                                                                         
    120                 if (p->lock && p->lock(dev, data) < 0) {                                                                                                      
    121                         module_put(owner);                                                                                                                    
    122                         continue;                                                                                                                             
    123                 }                                                                                                                                             
    124                 mutex_unlock(domain->lock);                                                                                                                   
    125                 kobj = probe(dev, index, data);                                                                                                               
    126                 // Currently ->owner protects _only_ ->probe() itself. //                                                                                     
    127                 module_put(owner); Linux  ��Щ�¶�֮���� Block��                                                                                              
�� 18  ҳ �� 117  ҳ                                                                                                                                                  
    128                 if (kobj)                                                                                                                                     
    129                         return kobj;                                                                                                                          
    130                 goto retry;                                                                                                                                   
    131         }                                                                                                                                                     
    132         mutex_unlock(domain->lock);                                                                                                                           
    133         return NULL;                                                                                                                                          
    134 }                                                                                                                                                             
// ������������ԼԼ�ĸо���,kobj_map_init()�� kobj_map()�Լ� kobj_lookup()��һ��ϵ�е�,                                                                                  
// ���Ƕ���Ϊ Linux �豸�Ź�������,�ͺñ����,������,�������һ��ϵ�е�,���Ƕ���Ϊ                                                                                     
// ����Ƭ�г������.����,kobj_map_init �ṩ����һ���Է���,����ʹ���ǽ����� bdev_map ��                                                                                   
// �� struct kobj_map.Ȼ�� kobj_map ��ÿ���� blk_register_region �б����õ�,Ȼ��,��������                                                                              
// �ͷ׵�������,���� blk_register_region()�ĵط����治��,���һ��������һ���,���������                                                                                 
// ��add_disk�е���ֻ������֮һ,�����ı���RAID�����Ǳ�,���������Ǳ�,�����е������                                                                                       
// blk_register_region ������,�� kobj_lookup()������ʲô�������?���ṩ����ʵ���ۺ����.                                                                                 
// �����豸��������˳�ʼ������,�������ں���վ���˽Ÿ�,����һ���豸�ļ��������Ӧ,                                                                                       
// ����ļ��������/devĿ¼��.�ڲ��õĽ���,��openϵͳ������ͼ�򿪿��豸�ļ���ʱ���                                                                                      
// �������,��׼ȷ��˵,sys_open ���� filp_open Ȼ���� dentry_open(),���ջ��ҵ�                                                                                           
// blkdev_open,blkdev_open ����� do_open,do_open()����� get_gendisk(),Ҫ������������,                                                                                
// ���ȿ�һ�� dev_t ����ṹ.dev_t ʵ���Ͼ��� u32,Ҳ������ 32 �� bits.ǰ�����ǿ�����                                                                                     
// MKDEV,MAJOR,������ include/linux/kdev_t.h:                                                                                                                            
      4 #define MINORBITS       20                                                                                                                                    
      5 #define MINORMASK       ((1U << MINORBITS) - 1)                                                                                                               
     6                                                                                                                                                                
      7 #define MAJOR(dev)      ((unsigned int) ((dev) >> MINORBITS))                                                                                                 
      8 #define MINOR(dev)      ((unsigned int) ((dev) & MINORMASK))                                                                                                  
      9 #define MKDEV(ma,mi)    (((ma) << MINORBITS) | (mi))                                                                                                          
// ͨ���⼸����,���ǲ��ѿ���dev_t��������,32��bits,���и�12λ��������¼�豸�����豸                                                                                      
// ��,�� 20 λ������¼�豸�Ĵ��豸��.�� MKDEV ���ǽ���һ���豸��.ma �������豸��,mi                                                                                      
// ������豸��,ma ���� 20 λ�ٺ� mi ���,������,MAJOR ���Ǵ� dev ��ȡ���豸��,MINOR                                                                                     
// ���Ǵ� dev��ȡ���豸��.����˵��,������������Ƥ���Ķ�֪����ô������.                                                                                                   
// ��һ���豸���� Linux ������ʱ,����������һ����ס֤��,����� dev_t,����Ȼ,ÿ���˵ľ�                                                                                   
// ס֤�Ų�һ��,����Ψһ��.(Ϊʲô��˵�����֤��?��Ϊ��ס֤��ζ�ŵ��豸�뿪 Linux ϵ                                                                                     
// ͳ��ʱ��Ϳ�������,���������������豸��������.)����һ���豸�ļ���ʱ��,���豸����                                                                                      
// ȷ����,������ÿ�ν���һ���ļ����Ὠ��һ���ṹ�����,������struct inode,��struct inode                                                                                 
// ӵ�г�Ա dev_t i_dev,�����պ����Ǵ� struct inode �Ϳ��Եõ����豸�� dev_t,������                                                                                      
// kobj_map��һϵ�к���ʹ�����ǿ��Դ�dev_t�ҵ���Ӧ��kobject,Ȼ���һ����Ϊ��������,                                                                                      
// ���ǲ��ɱ������Ҫ���ʴ��̶�Ӧ��gendisk�ṹ��ָ��,��get_gendisk()��������ʱ��Ӧ��                                                                                     
// ��������ī�ǳ���.���ǿ��� get_gendisk()����������,dev_t dev�� int *part,ǰ�߾����豸��,                                                                               
// �����ߴ��ݵ���һ��ָ��,���ʾʲô��?���ʾ,                                                                                                                           
// 1.       �������豸�Ŷ�Ӧ����һ������,��ô part ������������������ı��.                                                                                           
// 2.       �������豸�Ŷ�Ӧ���������豸������ĳ������,��ô part ��ֻҪ���ó� 0�� ok ��.                                                                               
// ��ô�õ� gendisk ��Ŀ������ʲô��?����ע�⵽ struct gendisk ��һ����Ա,struct                                                                                         
// block_device_operations *fops,�����ָ�������������ִ�в�����,ÿһ�����豸������׼                                                                                   
// ������ôһ���ṹ��,���������� sd�ж�����Ǹ�: Linux  ��Щ�¶�֮���� Block��                                                                                           
// �� 19  ҳ �� 117  ҳ                                                                                                                                                  
    872 static struct block_device_operations sd_fops = {                                                                                                             
    873         .owner                  = THIS_MODULE,                                                                                                                
    874         .open                   = sd_open,                                                                                                                    
    875         .release                = sd_release,                                                                                                                 
    876         .ioctl                  = sd_ioctl,                                                                                                                   
    877         .getgeo                 = sd_getgeo,                                                                                                                  
    878 #ifdef CONFIG_COMPAT                                                                                                                                          
    879         .compat_ioctl           = sd_compat_ioctl,                                                                                                            
    880 #endif                                                                                                                                                        
    881         .media_changed          = sd_media_changed,                                                                                                           
    882         .revalidate_disk        = sd_revalidate_disk,                                                                                                         
    883 };                                                                                                                                                            
// ������Ϊ��������������ϵ,���ǲ���һ��һ���� sys_open �����ߵ� sd_open,Ҳ���ܴ��û�                                                                                    
// ��һ��һ���ߵ����豸������,��ͬ�������ܹ����Ϻ�һ������������.                                                                                                      
//                                                                                                                                                                       
// Ũ�����Ǿ���?(��)                                                                                                                                                     
// �ڶ���,register_disk,��ͷ��С,������ңԶ�� fs/partitions/check.c:                                                                                                     
    473 // Not exported, helper to add_disk(). //                                                                                                                     
    474 void register_disk(struct gendisk *disk)                                                                                                                      
    475 {                                                                                                                                                             
    476         struct block_device *bdev;                                                                                                                            
    477         char *s;                                                                                                                                              
    478         int i;                                                                                                                                                
    479         struct hd_struct *p;                                                                                                                                  
    480         int err;                                                                                                                                              
    481                                                                                                                                                               
    482         strlcpy(disk->kobj.name,disk->disk_name,KOBJ_NAME_LEN);                                                                                               
    483         // ewww... some of these buggers have / in name... //                                                                                                 
    484         s = strchr(disk->kobj.name, '/');                                                                                                                     
    485         if (s)                                                                                                                                                
    486                 *s = '!';                                                                                                                                     
    487         if ((err = kobject_add(&disk->kobj)))                                                                                                                 
    488                 return;                                                                                                                                       
    489         err = disk_sysfs_symlinks(disk);                                                                                                                      
    490         if (err) {                                                                                                                                            
    491                 kobject_del(&disk->kobj);                                                                                                                     
    492                 return;                                                                                                                                       
    493         }                                                                                                                                                     
    494         disk_sysfs_add_subdirs(disk);                                                                                                                         
    495                                                                                                                                                               
    496         // No minors to use for partitions // Linux  ��Щ�¶�֮���� Block��                                                                                   
�� 20  ҳ �� 117  ҳ                                                                                                                                                  
    497         if (disk->minors == 1)                                                                                                                                
    498                 goto exit;                                                                                                                                    
    499                                                                                                                                                               
    500         // No such device (e.g., media were just removed) //                                                                                                  
    501         if (!get_capacity(disk))                                                                                                                              
    502                 goto exit;                                                                                                                                    
    503                                                                                                                                                               
    504         bdev = bdget_disk(disk, 0);                                                                                                                           
    505         if (!bdev)                                                                                                                                            
    506                 goto exit;                                                                                                                                    
    507                                                                                                                                                               
    508         // scan partition table, but suppress uevents //                                                                                                      
    509         bdev->bd_invalidated = 1;                                                                                                                             
    510         disk->part_uevent_suppress = 1;                                                                                                                       
    511         err = blkdev_get(bdev, FMODE_READ, 0);                                                                                                                
    512         disk->part_uevent_suppress = 0;                                                                                                                       
513         if (err < 0)                                                                                                                                              
    514                 goto exit;                                                                                                                                    
    515         blkdev_put(bdev);                                                                                                                                     
    516                                                                                                                                                               
    517 exit:                                                                                                                                                         
    518         // announce disk after possible partitions are already created //                                                                                     
    519         kobject_uevent(&disk->kobj, KOBJ_ADD);                                                                                                                
    520                                                                                                                                                               
    521         // announce possible partitions //                                                                                                                    
    522         for (i = 1; i < disk->minors; i++) {                                                                                                                  
    523                 p = disk->part[i-1];                                                                                                                          
    524                 if (!p || !p->nr_sects)                                                                                                                       
    525                         continue;                                                                                                                             
    526                 kobject_uevent(&p->kobj, KOBJ_ADD);                                                                                                           
    527         }                                                                                                                                                     
    528 }                                                                                                                                                             
// ����㲻�� Linux 2.6 ��ͳһ�豸ģ��,����Ҫ������δ�����ƹ�Ǻ.������������<<����                                                                                     
// Sysfs>>�ж� kobject ����Ķ������˽���.�����������ǲ������뵽 kobject ��صĺ����ڲ�                                                                                  
// ��ȥ,Ҳ�������뵽 sysfs �ṩ�ĺ����ڲ�,�㵽Ϊֹ.                                                                                                                      
// ���� 487 ����� kobject_add �������Ǻ�ֱ�۵�,��Sysfs ��Ϊ�����̽�һ����Ŀ¼.�ͱ���                                                                                  
// ������ЩĿ¼�е��Ǹ�sdf,����Ϊ�ҵ�U�̶�������,��Ҫ�ǰ��������kobject_add������                                                                                       
// ��ע�͵�,��֤��Ϳ�������� sdfĿ¼.                                                                                                                                  
// [root@lfg2 ~]# ls /sys/block/                                                                                                                                         
// md0   ram1   ram11  ram13  ram15  ram3  ram5  ram7  ram9  sdb  sdd  sdf ram0                                                                                          
// ram10  ram12  ram14  ram2   ram4  ram6  ram8  sda   sdc  sde  sdg                                                                                                     
// ��ʱ�����ѡ�����ʧ�������������:                                                                                                                                   
// ��һ,Ϊʲôkobject_add��ôһ����,���ɵ������Ŀ¼�����־ͽ�����sdf��,�����������?��                                                                                  
// ���ǵ��� sd_probe ����������һ������ô,��ʱ���ǿ��Ǿ��ļ���� disk_name ��,��Linux  ��Щ�¶�֮���� Block��                                                            
// �� 21  ҳ �� 117  ҳ                                                                                                                                                  
// disk_name ���� struct gendisk ��һ����Ա,�������ǿ��� 482 �����ǰ� disk_name ����                                                                                     
// kobj.name,�����Ϊʲô���ǵ��� kobject_add ���һ�� kobject ��ʱ��,�������־������ǵ�                                                                                 
// ʱ�� disk_name.                                                                                                                                                       
// �ڶ�,Ϊʲô���ɵ������Ŀ¼����/sys/block Ŀ¼����,�������ڱ��λ��?���ǵ���                                                                                          
// alloc_disk_node ���������� struct gendisk ���龰ô?�Ǿ� kobj_set_kset_s(disk,block_subsys)                                                                            
// ���ľ����� disk ��Ӧ�� kobject ������ block_subsys ��Ӧ�� kobject ����.�����Ϊʲô����                                                                               
// ���������� kobject ��ʱ��,������Ȼ�ľͻ���/sys/block ��Ŀ¼���潨���ļ�.                                                                                            
// ������, disk_sysfs_symlinks���� fs/partitions/check.c,���������Ȼ����,���ǱȽ�ǳ���׶�.                                                                              
    429 static int disk_sysfs_symlinks(struct gendisk *disk)                                                                                                          
    430 {                                                                                                                                                             
    431         struct device *target = get_device(disk->driverfs_dev);                                                                                               
    432         int err;                                                                                                                                              
    433         char *disk_name = NULL;                                                                                                                               
    434                                                                                                                                                               
    435         if (target) {                                                                                                                                         
    436                 disk_name = make_block_name(disk);                                                                                                            
    437                 if (!disk_name) {                                                                                                                             
    438                         err = -ENOMEM;                                                                                                                        
    439                         goto err_out;                                                                                                                         
    440                 }                                                                                                                                             
    441                                                                                                                                                               
    442                 err = sysfs_create_link(&disk->kobj, &target->kobj, "device");                                                                                
    443                 if (err)                                                                                                                                      
    444                         goto err_out_disk_name;                                                                                                               
    445                                                                                                                                                               
    446                 err = sysfs_create_link(&target->kobj, &disk->kobj, disk_name);                                                                               
    447                 if (err)                                                                                                                                      
    448                         goto err_out_dev_link;                                                                                                                
    449         }                                                                                                                                                     
    450                                                                                                                                                               
    451         err = sysfs_create_link(&disk->kobj, &block_subsys.kobj,                                                                                              
    452                                 "subsystem");                                                                                                                 
    453         if (err)                                                                                                                                              
    454                 goto err_out_disk_name_lnk;                                                                                                                   
    455                                                                                                                                                               
    456         kfree(disk_name);                                                                                                                                     
    457                                                                                                                                                               
    458         return 0;                                                                                                                                             
    459                                                                                                                                                               
    460 err_out_disk_name_lnk:                                                                                                                                        
    461         if (target) {                                                                                                                                         
    462                 sysfs_remove_link(&target->kobj, disk_name);                                                                                                  
    463 err_out_dev_link:                                                                                                                                             
    464                 sysfs_remove_link(&disk->kobj, "device"); Linux  ��Щ�¶�֮���� Block��                                                                       
�� 22  ҳ �� 117  ҳ                                                                                                                                                  
    465 err_out_disk_name:                                                                                                                                            
    466                 kfree(disk_name);                                                                                                                             
    467 err_out:                                                                                                                                                      
    468                 put_device(target);                                                                                                                           
    469         }                                                                                                                                                     
    470         return err;                                                                                                                                           
    471 }                                                                                                                                                             
// ������ʵ��Ч��������������.�������ǿ����������� U �̻���/sys/block/sdf ��������Щ                                                                                   
// ����:                                                                                                                                                                 
// [root@localhost ~]# ls /sys/block/sdf/                                                                                                                                
// capability  dev  device  holders  queue  range  removable  size  slaves  stat  subsystem                                                                              
// uevent                                                                                                                                                                
// 442 �е� sysfs_create_link��ôһ�д����ľ���������� device ����������ļ�.����������                                                                                 
// ���ӵ�����ȥ��?                                                                                                                                                       
// [root@localhost ~]# ls -l /sys/block/sdf/device                                                                                                                       
// lrwxrwxrwx 1 root root 0 Dec 13 07:09 /sys/block/sdf/device                                                                                                           
// -> ../../devices/pci0000:00/0000:00:1d.7/usb4/4-4/4-4:1.0/host24/target24:0:0/24:0:0:0                                                                                
// �� 446 ����� sysfs_create_link ����Ǳ��ֽ���һ��������,�ָ����ӻ�����.                                                                                              
// [root@localhost~]# ls                                                                                                                                                 
// /sys/devices/pci0000\:00/0000\:00\:1d.7/usb4/4-4/4-4\:1.0/host24/target24\:0\:0/24\:0\:0\:0/                                                                          
// block:sdf driver ioerr_cnt model rescan scsi_generic:sg7  timeout bus             generic                                                                             
// iorequest_cnt  power        rev                   scsi_level        type delete                                                                                       
// iocounterbits  max_sectors    queue_depth  scsi_device:24:0:0:0  state       uevent                                                                                   
// device_blocked  iodone_cnt     modalias       queue_type   scsi_disk:24:0:0:0                                                                                         
// subsystem  vendor                                                                                                                                                     
// ������,������� block:sdf.                                                                                                                                            
// [root@localhost~]# ls -l                                                                                                                                              
// /sys/devices/pci0000\:00/0000\:00\:1d.7/usb4/4-4/4-4\:1.0/host24/target24\:0\:0/24\:0\:0\:0/block\:                                                                   
// sdf                                                                                                                                                                   
// lrwxrwxrwx 1 root root 0 Dec 13 21:16                                                                                                                                 
// /sys/devices/pci0000:00/0000:00:1d.7/usb4/4-4/4-4:1.0/host24/target24:0:0/24:0:0:0/block:sdf                                                                          
// -> ../../../../../../../../../block/sdf                                                                                                                               
// ������͵�������������������,���Ǳ���һ���ļ����ӵ��������,�������һ���ļ�����                                                                                      
// �������Ǳ�.                                                                                                                                                           
// Ȼ��451���ٴε���sysfs_create_link.��κ���Ȼ,���ɵ���/sys/block/sdf/subsystem�������                                                                                
// ���ļ�.                                                                                                                                                               
// [root@localhost ~]# ls -l /sys/block/sdf/subsystem                                                                                                                    
// lrwxrwxrwx 1 root root 0 Dec 13 07:09 /sys/block/sdf/subsystem -> ../../block                                                                                         
// ���������ļ�������֮��,disk_sysfs_symlinks Ҳ�ͽ���������ʹ��.������һ��������                                                                                        
// disk_sysfs_add_subdirs.ͬ������ fs/partitions/check.c:                                                                                                                
    342 static inline void disk_sysfs_add_subdirs(struct gendisk *disk)                                                                                               
    343 {                                                                                                                                                             
    344         struct kobject *k;                                                                                                                                    
    345 Linux  ��Щ�¶�֮���� Block��                                                                                                                                 
�� 23  ҳ �� 117  ҳ                                                                                                                                                  
    346         k = kobject_get(&disk->kobj);                                                                                                                         
    347         disk->holder_dir = kobject_add_dir(k, "holders");                                                                                                     
    348         disk->slave_dir = kobject_add_dir(k, "slaves");                                                                                                       
    349         kobject_put(k);                                                                                                                                       
    350 }                                                                                                                                                             
// �����������ͼ̫������,���ź�������⵹���ݳ�����Ʊ�Ļ�ţ���Ƕ��ܿ���,�޷Ǿ���                                                                                      
// ���� holders�� slaves������Ŀ¼.                                                                                                                                      
// 504 ��,bdget_disk,����һ����������,<<Thinking in C++>>������������������ö�����ͷ                                                                                    
// �ļ���,��������������� include/linux/genhd.h:                                                                                                                        
    433 static inline struct block_device *bdget_disk(struct gendisk *disk, int index)                                                                                
    434 {                                                                                                                                                             
    435         return bdget(MKDEV(disk->major, disk->first_minor) + index);                                                                                          
    436 }                                                                                                                                                             
����һ�����������ĵ���.bdget ���� fs/block_dev.c:                                                                                                                     
    554 struct block_device *bdget(dev_t dev)                                                                                                                         
    555 {                                                                                                                                                             
    556         struct block_device *bdev;                                                                                                                            
    557         struct inode *inode;                                                                                                                                  
    558                                                                                                                                                               
    559         inode = iget5_locked(bd_mnt->mnt_sb, hash(dev),                                                                                                       
    560                         bdev_test, bdev_set, &dev);                                                                                                           
    561                                                                                                                                                               
    562         if (!inode)                                                                                                                                           
    563                 return NULL;                                                                                                                                  
    564                                                                                                                                                               
    565         bdev = &BDEV_I(inode)->bdev;                                                                                                                          
    566                                                                                                                                                               
    567         if (inode->i_state & I_NEW) {                                                                                                                         
    568                 bdev->bd_contains = NULL;                                                                                                                     
    569                 bdev->bd_inode = inode;                                                                                                                       
    570                 bdev->bd_block_size = (1 << inode->i_blkbits);                                                                                                
    571                 bdev->bd_part_count = 0;                                                                                                                      
    572                 bdev->bd_invalidated = 0;                                                                                                                     
    573                 inode->i_mode = S_IFBLK;                                                                                                                      
    574                 inode->i_rdev = dev;                                                                                                                          
    575                 inode->i_bdev = bdev;                                                                                                                         
    576                 inode->i_data.a_ops = &def_blk_aops;                                                                                                          
    577                 mapping_set_gfp_mask(&inode->i_data, GFP_USER);                                                                                               
    578                 inode->i_data.backing_dev_info = &default_backing_dev_info;                                                                                   
    579                 spin_lock(&bdev_lock);                                                                                                                        
    580                 list_add(&bdev->bd_list, &all_bdevs);                                                                                                         
    581                 spin_unlock(&bdev_lock);                                                                                                                      
    582                 unlock_new_inode(inode);                                                                                                                      
    583         } Linux  ��Щ�¶�֮���� Block��                                                                                                                       
�� 24  ҳ �� 117  ҳ                                                                                                                                                  
    584         return bdev;                                                                                                                                          
    585 }                                                                                                                                                             
// ���ǻ������н����а�,һ����������������̬�Ľṹ����.struct block_device��struct inode.                                                                                
// �� include/linux/fs.h �ж�������ôһ���ṹ��:                                                                                                                         
    460 struct block_device {                                                                                                                                         
    461         dev_t                   bd_dev;  // not a kdev_t - it's a search key //                                                                               
    462         struct inode *          bd_inode;       // will die //                                                                                                
    463         int                     bd_openers;                                                                                                                   
    464         struct mutex            bd_mutex;       // open/close mutex //                                                                                        
    465         struct semaphore        bd_mount_sem;                                                                                                                 
    466         struct list_head        bd_inodes;                                                                                                                    
    467         void *                  bd_holder;                                                                                                                    
    468         int                     bd_holders;                                                                                                                   
    469 #ifdef CONFIG_SYSFS                                                                                                                                           
    470         struct list_head        bd_holder_list;                                                                                                               
    471 #endif                                                                                                                                                        
    472         struct block_device *   bd_contains;                                                                                                                  
    473         unsigned                bd_block_size;                                                                                                                
    474         struct hd_struct *      bd_part;                                                                                                                      
    475         // number of times partitions within this device have been opened. //                                                                                 
    476         unsigned                bd_part_count;                                                                                                                
    477         int                     bd_invalidated;                                                                                                               
    478         struct gendisk *        bd_disk;                                                                                                                      
    479         struct list_head        bd_list;                                                                                                                      
    480         struct backing_dev_info *bd_inode_backing_dev_info;                                                                                                   
    481         //                                                                                                                                                    
    482          * Private data.  You must have bd_claim'ed the block_device                                                                                          
    483          * to use this.  NOTE:  bd_claim allows an owner to claim                                                                                             
    484          * the same device multiple times, the owner must take special                                                                                        
    485          * care to not mess up bd_private for that case.                                                                                                      
    486          //                                                                                                                                                   
    487         unsigned long           bd_private;                                                                                                                   
    488 };                                                                                                                                                            
// ������,Linux ��ÿһ�� Block �豸������ôһ���ṹ�������ʾ,���������˱���������                                                                                     
// ��������.inode ���ǲ����彲,��������ͦ����һ���ṹ���� struct bdev_inode,                                                                                             
     29 struct bdev_inode {                                                                                                                                           
     30         struct block_device bdev;                                                                                                                             
     31         struct inode vfs_inode;                                                                                                                               
     32 };                                                                                                                                                            
// ��������̬�Ľṹ����������ͱ���˵�������̬�Ľṹ��.                                                                                                                 
// ��������Ϊ��������һֱ�õ��ơ��ĸ��Ƕ�����,bdev_inode ����û���ֹ�,��������?����˵                                                                                    
// ������Ҫ������,��Ҫ�������Ի�,��������Ϻܶ����鶼��������Ͽ���������.�����㿴                                                                                       
// BDEV_I,��������������� fs/block_dev.c:                                                                                                                               
     34 static inline struct bdev_inode *BDEV_I(struct inode *inode) Linux  ��Щ�¶�֮���� Block��                                                                    
�� 25  ҳ �� 117  ҳ                                                                                                                                                  
     35 {                                                                                                                                                             
     36         return container_of(inode, struct bdev_inode, vfs_inode);                                                                                             
     37 }                                                                                                                                                             
// ����Ȼ,�� inode �õ���Ӧ�� bdev_inode.���� 565 �����&BDEV_I(inode)->bdev ��ʾ�ľ���                                                                                  
// inode ��Ӧ��bdev_inode�ĳ�Ա struct block_device bdev.                                                                                                                
// ���ǽṹ������ⶫ�����񹫹�����,ֻ��ȴ��ͻ��Զ����������ǰ,����Ҫ��ȥ����Ż�                                                                                      
// ��.iget5_locked���Ǹ���������,�����������fs/inode.c,������Ȼ����ȥ���뿴��,ֻ�ܸ�                                                                                  
// ����,���������ôһִ��,���Ǿͼ��� inode ���� block_device ��.���Ҷ��ڵ�һ�������                                                                                    
// inode,��i_state��Ա��������I_NEW���flag��,����bdget()������,567����һ��if�����                                                                                      
// Ҫ��ִ�е�.��һ��if�������þ��ǳ�ʼ��inode�ṹ��ָ��inode�Լ�block_device�ṹ                                                                                       
// ��ָ�� bdev.���������շ��ص�Ҳ���� bdev.��Ҫǿ��һ��,bdev ���Ǵ���һ�̿�ʼ��ʽ����                                                                                    
// �����ǵĹ����е�.                                                                                                                                                     
// �ص� register_disk()��,��������.��һ���������ĺ����� blkdev_get,���� fs/block_dev.c:                                                                                  
   1206 static int __blkdev_get(struct block_device *bdev, mode_t mode, unsigned flags,                                                                               
   1207                         int for_part)                                                                                                                         
   1208 {                                                                                                                                                             
   1209         //                                                                                                                                                    
   1210          * This crockload is due to bad choice of ->open() type.                                                                                              
   1211          * It will go away.                                                                                                                                   
   1212          * For now, block device ->open() routine must _not_                                                                                                  
   1213          * examine anything in 'inode' argument except ->i_rdev.                                                                                              
   1214          //                                                                                                                                                   
   1215         struct file fake_file = {};                                                                                                                           
   1216         struct dentry fake_dentry = {};                                                                                                                       
   1217         fake_file.f_mode = mode;                                                                                                                              
   1218         fake_file.f_flags = flags;                                                                                                                            
   1219         fake_file.f_path.dentry = &fake_dentry;                                                                                                               
   1220         fake_dentry.d_inode = bdev->bd_inode;                                                                                                                 
   1221                                                                                                                                                               
   1222         return do_open(bdev, &fake_file, for_part);                                                                                                           
   1223 }                                                                                                                                                             
   1224                                                                                                                                                               
   1225 int blkdev_get(struct block_device *bdev, mode_t mode, unsigned flags)                                                                                        
   1226 {                                                                                                                                                             
   1227         return __blkdev_get(bdev, mode, flags, 0);                                                                                                            
   1228 }                                                                                                                                                             
// ���� blkdev_get ���õ���__blkdev_get,����������������һ����������.                                                                                                    
// ����Ȼ,������Ҫ����ȴ�� do_open,����ͬһ���ļ�.                                                                                                                       
   1103 //                                                                                                                                                            
   1104  * bd_mutex locking:                                                                                                                                          
   1105  *                                                                                                                                                            
   1106  *  mutex_lock(part->bd_mutex)                                                                                                                                
   1107  *    mutex_lock_nested(whole->bd_mutex, 1)                                                                                                                   
   1108  // Linux  ��Щ�¶�֮���� Block��                                                                                                                             
�� 26  ҳ �� 117  ҳ                                                                                                                                                  
   1109                                                                                                                                                               
   1110 static int do_open(struct block_device *bdev, struct file *file, int for_part)                                                                                
   1111 {                                                                                                                                                             
   1112         struct module *owner = NULL;                                                                                                                          
   1113         struct gendisk *disk;                                                                                                                                 
   1114         int ret = -ENXIO;                                                                                                                                     
   1115         int part;                                                                                                                                             
   1116                                                                                                                                                               
   1117         file->f_mapping = bdev->bd_inode->i_mapping;                                                                                                          
   1118         lock_kernel();                                                                                                                                        
   1119         disk = get_gendisk(bdev->bd_dev, &part);                                                                                                              
   1120         if (!disk) {                                                                                                                                          
   1121                 unlock_kernel();                                                                                                                              
   1122                 bdput(bdev);                                                                                                                                  
   1123                 return ret;                                                                                                                                   
   1124         }                                                                                                                                                     
   1125         owner = disk->fops->owner;                                                                                                                            
   1126                                                                                                                                                               
   1127         mutex_lock_nested(&bdev->bd_mutex, for_part);                                                                                                         
   1128         if (!bdev->bd_openers) {                                                                                                                              
   1129                 bdev->bd_disk = disk;                                                                                                                         
   1130                 bdev->bd_contains = bdev;                                                                                                                     
   1131                 if (!part) {                                                                                                                                  
   1132                         struct backing_dev_info *bdi;                                                                                                         
   1133                         if (disk->fops->open) {                                                                                                               
   1134                                 ret = disk->fops->open(bdev->bd_inode, file);                                                                                 
   1135                                 if (ret)                                                                                                                      
   1136                                         goto out_first;                                                                                                       
   1137                         }                                                                                                                                     
   1138                         if (!bdev->bd_openers) {                                                                                                              
   1139                                                                                                                                                               
bd_set_size(bdev,(loff_t)get_capacity(disk)<<9);                                                                                                                      
   1140                                 bdi = blk_get_backing_dev_info(bdev);                                                                                         
   1141                                 if (bdi == NULL)                                                                                                              
   1142                                         bdi = &default_backing_dev_info;                                                                                      
   1143                                 bdev->bd_inode->i_data.backing_dev_info =                                                                                     
bdi;                                                                                                                                                                  
   1144                         }                                                                                                                                     
   1145                         if (bdev->bd_invalidated)                                                                                                             
   1146                                 rescan_partitions(disk, bdev);                                                                                                
   1147                 } else {                                                                                                                                      
   1148                         struct hd_struct *p;                                                                                                                  
   1149                         struct block_device *whole;                                                                                                           
   1150                         whole = bdget_disk(disk, 0); Linux  ��Щ�¶�֮���� Block��                                                                            
�� 27  ҳ �� 117  ҳ                                                                                                                                                  
   1151                         ret = -ENOMEM;                                                                                                                        
   1152                         if (!whole)                                                                                                                           
   1153                                 goto out_first;                                                                                                               
   1154                         BUG_ON(for_part);                                                                                                                     
   1155                         ret = __blkdev_get(whole, file->f_mode, file->f_flags, 1);                                                                            
   1156                         if (ret)                                                                                                                              
   1157                                 goto out_first;                                                                                                               
   1158                         bdev->bd_contains = whole;                                                                                                            
   1159                         p = disk->part[part - 1];                                                                                                             
   1160                         bdev->bd_inode->i_data.backing_dev_info =                                                                                             
   1161                            whole->bd_inode->i_data.backing_dev_info;                                                                                          
   1162                          if (!(disk->flags & GENHD_FL_UP) || !p || !p->nr_sects)                                                                              
{                                                                                                                                                                     
   1163                                 ret = -ENXIO;                                                                                                                 
   1164                                 goto out_first;                                                                                                               
   1165                         }                                                                                                                                     
   1166                         kobject_get(&p->kobj);                                                                                                                
   1167                         bdev->bd_part = p;                                                                                                                    
   1168                         bd_set_size(bdev, (loff_t) p->nr_sects << 9);                                                                                         
   1169                 }                                                                                                                                             
   1170         } else {                                                                                                                                              
   1171                 put_disk(disk);                                                                                                                               
   1172                 module_put(owner);                                                                                                                            
   1173                 if (bdev->bd_contains == bdev) {                                                                                                              
   1174                         if (bdev->bd_disk->fops->open) {                                                                                                      
   1175                                 ret =                                                                                                                         
bdev->bd_disk->fops->open(bdev->bd_inode, file);                                                                                                                      
   1176                                 if (ret)                                                                                                                      
   1177                                         goto out;                                                                                                             
   1178                         }                                                                                                                                     
   1179                         if (bdev->bd_invalidated)                                                                                                             
   1180                                 rescan_partitions(bdev->bd_disk, bdev);                                                                                       
   1181                 }                                                                                                                                             
   1182         }                                                                                                                                                     
   1183         bdev->bd_openers++;                                                                                                                                   
   1184         if (for_part)                                                                                                                                         
   1185                 bdev->bd_part_count++;                                                                                                                        
   1186         mutex_unlock(&bdev->bd_mutex);                                                                                                                        
   1187         unlock_kernel();                                                                                                                                      
   1188         return 0;                                                                                                                                             
   1189                                                                                                                                                               
   1190 out_first:                                                                                                                                                    
   1191         bdev->bd_disk = NULL;                                                                                                                                 
   1192         bdev->bd_inode->i_data.backing_dev_info = &default_backing_dev_info; Linux  ��Щ�¶�֮���� Block��                                                    
�� 28  ҳ �� 117  ҳ                                                                                                                                                  
   1193         if (bdev != bdev->bd_contains)                                                                                                                        
   1194                 __blkdev_put(bdev->bd_contains, 1);                                                                                                           
   1195         bdev->bd_contains = NULL;                                                                                                                             
   1196         put_disk(disk);                                                                                                                                       
   1197         module_put(owner);                                                                                                                                    
   1198 out:                                                                                                                                                          
   1199         mutex_unlock(&bdev->bd_mutex);                                                                                                                        
   1200         unlock_kernel();                                                                                                                                      
   1201         if (ret)                                                                                                                                              
   1202                 bdput(bdev);                                                                                                                                  
   1203         return ret;                                                                                                                                           
   1204 }                                                                                                                                                             
// ����.�ں˺���û�����̬,ֻ�и���̬.                                                                                                                                   
// һ��ʼ��ʱ��,bd_openers �Ǳ���ʼ��Ϊ�� 0,����1128 ��� if�����Ҫ��ִ�е�.bd_openers                                                                                  
// Ϊ 0 ��ʾһ���ļ���û�б��򿪹�.                                                                                                                                      
// һ��ʼ���ǻ�û���漰����������Ϣ,����һ��ʼ����ֻ�� sda �������,��û��                                                                                               
// sda1,sda2,sda3����Щ����.��ʱ�����ǵ��� get_gendisk �õ��� part һ���� 0.���� 1131 �е�                                                                               
// if ���Ҳ��ִ��.�� disk->fops->open ������,���� sd_open.(��Ϊ������ sd_probe ����������                                                                               
// �� gd->fops����&sd_fops.)                                                                                                                                             
// ����ʱ�˿�����ִ��sd_openʵ�����ǲ���ʲô�����¶���.������ǲ���һ�¿���sd_open                                                                                       
// �ܲ���ִ��,�����ִ��,��ô�ͷ��� 0.��������Ͳ���ִ��,�Ǿ͸Ͻ��㱨����.                                                                                               
// ���������м�������,��Ҫ��һЩ��ֵ,��ʱ��Ʈ��.�ȵ��ʵ���ʱ����Ҫ�����ٻ�����.                                                                                          
// �� 1146 ����� rescan_partitions()��Ȼ������Ҫ����,���������ڵ��� blkdev_get ֮ǰ��                                                                                   
// bd_invalidated ����Ϊ�� 1,��������������һ���ᱻִ��.����һ�̿�ʼ������Ϣ��������                                                                                   
// �ǵ�����.����������� fs/partitions/check.c:                                                                                                                          
    530 int rescan_partitions(struct gendisk *disk, struct block_device *bdev)                                                                                        
    531 {                                                                                                                                                             
    532         struct parsed_partitions *state;                                                                                                                      
    533         int p, res;                                                                                                                                           
    534                                                                                                                                                               
    535         if (bdev->bd_part_count)                                                                                                                              
    536                 return -EBUSY;                                                                                                                                
    537         res = invalidate_partition(disk, 0);                                                                                                                  
    538         if (res)                                                                                                                                              
    539                 return res;                                                                                                                                   
    540         bdev->bd_invalidated = 0;                                                                                                                             
    541         for (p = 1; p < disk->minors; p++)                                                                                                                    
    542                 delete_partition(disk, p);                                                                                                                    
    543         if (disk->fops->revalidate_disk)                                                                                                                      
    544                 disk->fops->revalidate_disk(disk);                                                                                                            
    545         if (!get_capacity(disk) || !(state = check_partition(disk, bdev)))                                                                                    
    546                 return 0;                                                                                                                                     
    547         if (IS_ERR(state))       // I/O error reading the partition table //                                                                                  
    548                 return -EIO; Linux  ��Щ�¶�֮���� Block��                                                                                                    
�� 29  ҳ �� 117  ҳ                                                                                                                                                  
    549         for (p = 1; p < state->limit; p++) {                                                                                                                  
    550                 sector_t size = state->parts[p].size;                                                                                                         
    551                 sector_t from = state->parts[p].from;                                                                                                         
    552                 if (!size)                                                                                                                                    
    553                         continue;                                                                                                                             
    554                  if (from + size > get_capacity(disk)) {                                                                                                      
    555                         printk(" %s: p%d exceeds device capacity\n",                                                                                          
    556                                 disk->disk_name, p);                                                                                                          
    557                 }                                                                                                                                             
    558                 add_partition(disk, p, from, size, state->parts[p].flags);                                                                                    
    559 #ifdef CONFIG_BLK_DEV_MD                                                                                                                                      
    560                 if (state->parts[p].flags & ADDPART_FLAG_RAID)                                                                                                
    561                         md_autodetect_dev(bdev->bd_dev+p);                                                                                                    
    562 #endif                                                                                                                                                        
    563         }                                                                                                                                                     
    564         kfree(state);                                                                                                                                         
    565         return 0;                                                                                                                                             
    566 }                                                                                                                                                             
// ��ʵ��������һ�д��붼����Ҳ֪����������ڸ���,��������˵��,�������ִ�й���,��                                                                                       
// �ڷ�������Ϣ���Ǿ��㶼����.���ڷ���,�������� struct hd_struct ��ô���ṹ������ʾ��,��                                                                                 
// struct hd_struct Ҳ���� struct gendisk �ĳ�Ա,�����Ǹ�����ָ��.һ��ʼ���ָ�벢����ָ,��                                                                              
// ��˵һ��ʼ���ǲ�û��Ϊ struct hd_struct ����ռ�,�����Ҽ�ʹ�������������                                                                                             
// delete_partition �����Ĵ�����ҲӦ��֪��,��ʱ�˿�,��ʲôҲ�����.                                                                                                      
    352 void delete_partition(struct gendisk *disk, int part)                                                                                                         
    353 {                                                                                                                                                             
    354         struct hd_struct *p = disk->part[part-1];                                                                                                             
    355         if (!p)                                                                                                                                               
    356                 return;                                                                                                                                       
    357         if (!p->nr_sects)                                                                                                                                     
    358                 return;                                                                                                                                       
    359         disk->part[part-1] = NULL;                                                                                                                            
    360         p->start_sect = 0;                                                                                                                                    
    361         p->nr_sects = 0;                                                                                                                                      
    362         p->ios[0] = p->ios[1] = 0;                                                                                                                            
    363         p->sectors[0] = p->sectors[1] = 0;                                                                                                                    
    364         sysfs_remove_link(&p->kobj, "subsystem");                                                                                                             
    365         kobject_unregister(p->holder_dir);                                                                                                                    
    366         kobject_uevent(&p->kobj, KOBJ_REMOVE);                                                                                                                
    367         kobject_del(&p->kobj);                                                                                                                                
    368         kobject_put(&p->kobj);                                                                                                                                
    369 }                                                                                                                                                             
// ��revalidate_diskָ��ָ��ľ���sd_revalidate_disk,������������ڽ���sd��ʱ���������                                                                                  
// ������.�� sd_probe ���� add_disk ֮ǰ,���Ѿ�ִ�й��������,����ֻ��������ִ��һ�ΰ�                                                                                   
// ��. Linux  ��Щ�¶�֮���� Block��                                                                                                                                     
// �� 30  ҳ �� 117  ҳ                                                                                                                                                  
// ����,get_capacity().û�б�����������򵥵ĺ�����.���� include/linux/genhd.h:                                                                                          
    254 static inline sector_t get_capacity(struct gendisk *disk)                                                                                                     
    255 {                                                                                                                                                             
    256         return disk->capacity;                                                                                                                                
    257 }                                                                                                                                                             
�� check_partition ����΢����һЩ��,���� fs/partitions/check.c:                                                                                                       
    156 static struct parsed_partitions *                                                                                                                             
    157 check_partition(struct gendisk *hd, struct block_device *bdev)                                                                                                
    158 {                                                                                                                                                             
    159         struct parsed_partitions *state;                                                                                                                      
    160         int i, res, err;                                                                                                                                      
    161                                                                                                                                                               
    162         state = kmalloc(sizeof(struct parsed_partitions), GFP_KERNEL);                                                                                        
    163         if (!state)                                                                                                                                           
    164                 return NULL;                                                                                                                                  
    165                                                                                                                                                               
    166         disk_name(hd, 0, state->name);                                                                                                                        
    167         printk(KERN_INFO " %s:", state->name);                                                                                                                
    168         if (isdigit(state->name[strlen(state->name)-1]))                                                                                                      
    169                 sprintf(state->name, "p");                                                                                                                    
    170                                                                                                                                                               
    171         state->limit = hd->minors;                                                                                                                            
    172         i = res = err = 0;                                                                                                                                    
    173         while (!res && check_part[i]) {                                                                                                                       
    174                 memset(&state->parts, 0, sizeof(state->parts));                                                                                               
    175                 res = check_part[i++](state, bdev);                                                                                                           
    176                 if (res < 0) {                                                                                                                                
    177                         // We have hit an I/O error which we don't report now.                                                                                
    178                         * But record it, and let the others do their job.                                                                                     
    179                         //                                                                                                                                    
    180                         err = res;                                                                                                                            
    181                         res = 0;                                                                                                                              
    182                 }                                                                                                                                             
    183                                                                                                                                                               
    184         }                                                                                                                                                     
    185         if (res > 0)                                                                                                                                          
    186                 return state;                                                                                                                                 
    187         if (err)                                                                                                                                              
    188         // The partition is unrecognized. So report I/O errors if there were any //                                                                           
    189                 res = err;                                                                                                                                    
    190         if (!res)                                                                                                                                             
    191                 printk(" unknown partition table\n");                                                                                                         
    192         else if (warn_no_part)                                                                                                                                
    193                 printk(" unable to read partition table\n"); Linux  ��Щ�¶�֮���� Block��                                                                    
�� 31  ҳ �� 117  ҳ                                                                                                                                                  
    194         kfree(state);                                                                                                                                         
    195         return ERR_PTR(res);                                                                                                                                  
    196 }                                                                                                                                                             
// ����,struct parsed_partitions�ṹ�嶨���� fs/partitions/check.h��ôһ��ͷ�ļ���:                                                                                      
      8 enum { MAX_PART = 256 };                                                                                                                                      
      9                                                                                                                                                               
     10 struct parsed_partitions {                                                                                                                                    
     11         char name[BDEVNAME_SIZE];                                                                                                                             
     12         struct {                                                                                                                                              
     13                 sector_t from;                                                                                                                                
     14                 sector_t size;                                                                                                                                
     15                 int flags;                                                                                                                                    
     16         } parts[MAX_PART];                                                                                                                                    
     17         int next;                                                                                                                                             
     18         int limit;                                                                                                                                            
     19 };                                                                                                                                                            
����ṹ��������������¼������Ϣ��.                                                                                                                                   
�� 173 ����� check_part �Ǻ�������?�� fs/partitions/check.c ���ҵ�����:                                                                                              
     43 int warn_no_part = 1; //This is ugly: should make genhd removable media aware//                                                                               
     44                                                                                                                                                               
     45 static int (*check_part[])(struct parsed_partitions *, struct block_device *) = {                                                                             
     46         //                                                                                                                                                    
     47          * Probe partition formats with tables at disk address 0                                                                                              
     48          * that also have an ADFS boot block at 0xdc0.                                                                                                        
     49          //                                                                                                                                                   
     50 #ifdef CONFIG_ACORN_PARTITION_ICS                                                                                                                             
     51         adfspart_check_ICS,                                                                                                                                   
     52 #endif                                                                                                                                                        
     53 #ifdef CONFIG_ACORN_PARTITION_POWERTEC                                                                                                                        
     54         adfspart_check_POWERTEC,                                                                                                                              
     55 #endif                                                                                                                                                        
     56 #ifdef CONFIG_ACORN_PARTITION_EESOX                                                                                                                           
     57         adfspart_check_EESOX,                                                                                                                                 
     58 #endif                                                                                                                                                        
     59                                                                                                                                                               
     60         //                                                                                                                                                    
     61          * Now move on to formats that only have partition info at                                                                                            
     62          * disk address 0xdc0.  Since these may also have stale                                                                                               
     63          * PC/BIOS partition tables, they need to come before                                                                                                 
     64          * the msdos entry.                                                                                                                                   
     65          //                                                                                                                                                   
     66 #ifdef CONFIG_ACORN_PARTITION_CUMANA                                                                                                                          
     67         adfspart_check_CUMANA,                                                                                                                                
     68 #endif Linux  ��Щ�¶�֮���� Block��                                                                                                                          
�� 32  ҳ �� 117  ҳ                                                                                                                                                  
     69 #ifdef CONFIG_ACORN_PARTITION_ADFS                                                                                                                            
     70         adfspart_check_ADFS,                                                                                                                                  
     71 #endif                                                                                                                                                        
     72                                                                                                                                                               
     73 #ifdef CONFIG_EFI_PARTITION                                                                                                                                   
     74         efi_partition,          // this must come before msdos //                                                                                             
     75 #endif                                                                                                                                                        
     76 #ifdef CONFIG_SGI_PARTITION                                                                                                                                   
     77         sgi_partition,                                                                                                                                        
     78 #endif                                                                                                                                                        
     79 #ifdef CONFIG_LDM_PARTITION                                                                                                                                   
     80         ldm_partition,          // this must come before msdos //                                                                                             
     81 #endif                                                                                                                                                        
     82 #ifdef CONFIG_MSDOS_PARTITION                                                                                                                                 
     83         msdos_partition,                                                                                                                                      
     84 #endif                                                                                                                                                        
     85 #ifdef CONFIG_OSF_PARTITION                                                                                                                                   
     86         osf_partition,                                                                                                                                        
     87 #endif                                                                                                                                                        
     88 #ifdef CONFIG_SUN_PARTITION                                                                                                                                   
     89         sun_partition,                                                                                                                                        
     90 #endif                                                                                                                                                        
     91 #ifdef CONFIG_AMIGA_PARTITION                                                                                                                                 
     92         amiga_partition,                                                                                                                                      
     93 #endif                                                                                                                                                        
     94 #ifdef CONFIG_ATARI_PARTITION                                                                                                                                 
     95         atari_partition,                                                                                                                                      
     96 #endif                                                                                                                                                        
     97 #ifdef CONFIG_MAC_PARTITION                                                                                                                                   
     98         mac_partition,                                                                                                                                        
     99 #endif                                                                                                                                                        
    100 #ifdef CONFIG_ULTRIX_PARTITION                                                                                                                                
    101         ultrix_partition,                                                                                                                                     
    102 #endif                                                                                                                                                        
    103 #ifdef CONFIG_IBM_PARTITION                                                                                                                                   
    104         ibm_partition,                                                                                                                                        
    105 #endif                                                                                                                                                        
    106 #ifdef CONFIG_KARMA_PARTITION                                                                                                                                 
    107         karma_partition,                                                                                                                                      
    108 #endif                                                                                                                                                        
    109 #ifdef CONFIG_SYSV68_PARTITION                                                                                                                                
    110         sysv68_partition,                                                                                                                                     
    111 #endif                                                                                                                                                        
    112         NULL Linux  ��Щ�¶�֮���� Block��                                                                                                                    
�� 33  ҳ �� 117  ҳ                                                                                                                                                  
    113 };                                                                                                                                                            
// �üһ�,һ���Ӷ�������ô�ຯ��,Ҫ��ÿ����Ҫ���������軹Ҫ��Ҫ����.Ҳ���˸��Ƕ���                                                                                       
// �����ĸ�����ѧ������Ա,Ҫ��Ȼ����������ȥ��.                                                                                                                          
// ��������ܻ�û����ô��,���ǲ�����ĳЩý��һ��ÿ�ζ��ѿ����ʵ,������ÿ��ĺ�ˮ��                                                                                      
// �ɺ������϶��ǰ���һ��,������ǲ��������Լ����׻���˼�������?���µ������ʵ��                                                                                        
// �öԸ�,���������ר���о��������ʽ��,������һ�Ѻ�����һ��Ҳ���ÿ�.�����������                                                                                       
// ���������ʽ��,��ô fs/partitions Ŀ¼������ļ���͵���ϸ������,���ָ�ʽ�Ķ���,���                                                                                  
// ���Լ���Ҫ�Ŀ���.                                                                                                                                                     
localhost:/usr/src/linux-2.6.22.1 # ls fs/partitions/                                                                                                                 
Kconfig   acorn.h  atari.c  check.h  ibm.c    karma.h  mac.c    msdos.h  sgi.c  sun.h                                                                                 
ultrix.c Makefile  amiga.c  atari.h  efi.c    ibm.h    ldm.c    mac.h    osf.c    sgi.h                                                                               
sysv68.c  ultrix.h acorn.c   amiga.h  check.c  efi.h    karma.c  ldm.h    msdos.c  osf.h                                                                              
sun.c  sysv68.h                                                                                                                                                       
// ����������˵����,������ô���������Ŀ�ľ���һ��,Ϊ���ҵ�������Ϣ.�������շ�����                                                                                       
// Ϣ���ǻᱻ��¼���Ǹ� struct parsed_partitions �ṹ���ָ��.�����������Ǿͻ��õ����е�                                                                                 
// ��Ϣ,�������� size ��,from��,��Щ��������˼��������.                                                                                                                  
// Ȼ�����Ǿ������� add_partition,��Ȼ������ fs/partitions/check.c:                                                                                                      
    371 void add_partition(struct gendisk *disk, int part, sector_t start, sector_t len, int flags)                                                                   
    372 {                                                                                                                                                             
    373         struct hd_struct *p;                                                                                                                                  
    374                                                                                                                                                               
    375         p = kmalloc(sizeof(*p), GFP_KERNEL);                                                                                                                  
    376         if (!p)                                                                                                                                               
    377                 return;                                                                                                                                       
    378                                                                                                                                                               
    379         memset(p, 0, sizeof(*p));                                                                                                                             
    380         p->start_sect = start;                                                                                                                                
    381         p->nr_sects = len;                                                                                                                                    
    382         p->partno = part;                                                                                                                                     
    383         p->policy = disk->policy;                                                                                                                             
    384                                                                                                                                                               
    385         if (isdigit(disk->kobj.name[strlen(disk->kobj.name)-1]))                                                                                              
    386                                                                                                                                                               
snprintf(p->kobj.name,KOBJ_NAME_LEN,"%sp%d",disk->kobj.name,part);                                                                                                    
    387         else                                                                                                                                                  
    388                                                                                                                                                               
snprintf(p->kobj.name,KOBJ_NAME_LEN,"%s%d",disk->kobj.name,part);                                                                                                     
    389         p->kobj.parent = &disk->kobj;                                                                                                                         
    390         p->kobj.ktype = &ktype_part;                                                                                                                          
    391         kobject_init(&p->kobj);                                                                                                                               
    392         kobject_add(&p->kobj);                                                                                                                                
    393         if (!disk->part_uevent_suppress)                                                                                                                      
    394                 kobject_uevent(&p->kobj, KOBJ_ADD);                                                                                                           
    395         sysfs_create_link(&p->kobj, &block_subsys.kobj, "subsystem"); Linux  ��Щ�¶�֮���� Block��                                                           
�� 34  ҳ �� 117  ҳ                                                                                                                                                  
    396         if (flags & ADDPART_FLAG_WHOLEDISK) {                                                                                                                 
    397                 static struct attribute addpartattr = {                                                                                                       
    398                         .name = "whole_disk",                                                                                                                 
    399                         .mode = S_IRUSR | S_IRGRP | S_IROTH,                                                                                                  
    400                         .owner = THIS_MODULE,                                                                                                                 
    401                 };                                                                                                                                            
    402                                                                                                                                                               
    403                 sysfs_create_file(&p->kobj, &addpartattr);                                                                                                    
    404         }                                                                                                                                                     
    405         partition_sysfs_add_subdir(p);                                                                                                                        
    406         disk->part[part-1] = p;                                                                                                                               
    407 }                                                                                                                                                             
/// ����֮ǰ�ľ���,�����ٿ���Щ kobject ��ص�,sysfs ��صĺ��������׶���.                                                                                                
/// 389�����p->kobj.parent = &disk->kobj��֤�����ǽ��������ɵĶ����ڸղŵ�Ŀ¼֮��,��                                                                                    
/// sda1,sda2,���� sda Ŀ¼��.                                                                                                                                            
/// [root@localhost tedkdb]# ls /sys/block/sda/                                                                                                                           
/// capability  device   queue  removable  sda10   sda12  sda14  sda2  sda5  sda7  sda9                                                                                   
/// slaves  subsystem dev         holders  range  sda1       sda11  sda13  sda15  sda3                                                                                    
/// sda6  sda8  size  stat    uevent                                                                                                                                      
/// �� 395 �� sysfs_create_link ��Ч��Ҳ����Ȼ,                                                                                                                           
/// [root@localhost tedkdb]# ls -l /sys/block/sda/sda1/subsystem                                                                                                          
/// lrwxrwxrwx 1 root root 0 Dec 13 03:15 /sys/block/sda/sda1/subsystem -> ../../../block                                                                                 
/// �� partition_sysfs_add_subdirҲûʲô��˵��,���� fs/partitions/check.c:                                                                                               
    333 static inline void partition_sysfs_add_subdir(struct hd_struct *p)                                                                                            
    334 {                                                                                                                                                             
    335         struct kobject *k;                                                                                                                                    
    336                                                                                                                                                               
    337         k = kobject_get(&p->kobj);                                                                                                                            
    338         p->holder_dir = kobject_add_dir(k, "holders");                                                                                                        
    339         kobject_put(k);                                                                                                                                       
    340 }                                                                                                                                                             
// ����� holders��Ŀ¼.                                                                                                                                                 
// [root@localhost tedkdb]# ls /sys/block/sda/sda1/                                                                                                                      
// dev  holders  size  start  stat  subsystem  uevent                                                                                                                    
// ���,�����Ǽ�ס�������������һ������,��p�ĸ�����Ա�����˸�ֵ,���ں����Ľ�β����                                                                                      
// disk->part[part-1]ָ���� p.Ҳ����˵,�Ӵ��Ժ�,struct hd_struct ���ָ���������Ӧ��������                                                                              
// ��,�������ǿյ�.                                                                                                                                                      
// ������,rescan_partitions()�������,�ص� do_open()��.1183 ��,�� bd_openers ������ü�����                                                                              
// ��1,���for_part��ֵ,��ô��������Ӧ�����ü���Ҳ��1.Ȼ��do_openҲ�ͻ������Ľ�����,                                                                                     
// �����ŵ����һ��,__blkdev_get��blkdev_get��̷���.blkdev_put��blkdev_get���������                                                                                    
// ���෴,���ǾͲ�����,ֻ����Ҫע��,���Ѹղ�������ȥ�����������ü��������˻�ȥ.                                                                                          
// ���,register_disk()�е��õ����һ���������� kobject_uevent(),�����������֪ͨ�û��ռ�                                                                                
// �Ľ��� udevd,���������¼�������,�����ʹ�õķ��а���ȷ������ udev �������ļ�(���                                                                                     
// /etc/udev/Ŀ¼��),��ô��Ч��������/dev Ŀ¼����������Ӧ���豸�ļ�.����: Linux  ��Щ�¶�֮���� Block��                                                                 
// �� 35  ҳ �� 117  ҳ                                                                                                                                                  
// [root@localhost tedkdb]# ls /dev/sda*                                                                                                                                 
// /dev/sda   /dev/sda10  /dev/sda12  /dev/sda14  /dev/sda2  /dev/sda5  /dev/sda7  /dev/sda9                                                                             
// /dev/sda1  /dev/sda11  /dev/sda13  /dev/sda15  /dev/sda3  /dev/sda6  /dev/sda8                                                                                        
// ����Ϊʲô,�����ȥ�Ķ����� udev��֪ʶ,�����û��ռ�ĳ���,���ǾͲ���˵��.                                                                                             
//                                                                                                                                                                       
// Ũ�����Ǿ���?(��)                                                                                                                                                     
// ������,blk_register_queue().                                                                                                                                          
   4079 int blk_register_queue(struct gendisk *disk)                                                                                                                  
   4080 {                                                                                                                                                             
   4081         int ret;                                                                                                                                              
   4082                                                                                                                                                               
   4083         request_queue_t *q = disk->queue;                                                                                                                     
   4084                                                                                                                                                               
   4085          if (!q || !q->request_fn)                                                                                                                            
   4086                 return -ENXIO;                                                                                                                                
   4087                                                                                                                                                               
   4088         q->kobj.parent = kobject_get(&disk->kobj);                                                                                                            
   4089                                                                                                                                                               
   4090         ret = kobject_add(&q->kobj);                                                                                                                          
   4091         if (ret < 0)                                                                                                                                          
   4092                 return ret;                                                                                                                                   
   4093                                                                                                                                                               
   4094         kobject_uevent(&q->kobj, KOBJ_ADD);                                                                                                                   
   4095                                                                                                                                                               
   4096         ret = elv_register_queue(q);                                                                                                                          
   4097         if (ret) {                                                                                                                                            
   4098                 kobject_uevent(&q->kobj, KOBJ_REMOVE);                                                                                                        
   4099                 kobject_del(&q->kobj);                                                                                                                        
   4100                 return ret;                                                                                                                                   
   4101         }                                                                                                                                                     
   4102                                                                                                                                                               
   4103         return 0;                                                                                                                                             
   4104 }                                                                                                                                                             
// ����,4090 ����� kobject_add �ܺý���,��/sys/block/sda/Ŀ¼�����ֶ�һ����Ŀ¼����,����                                                                                
// ����,��� q ������ʲô?�������ǰ� disk->queue ��������,�� disk->queue ����ʲô��?�ع�                                                                                 
// ͷȥ�� sd_probe(),��ʱ��������ôһ��,                                                                                                                                 
//    1662         gd->queue = sdkp->device->request_queue;                                                                                                              
// �� sdkp �� struct scsi_disk �ṹ��ָ��,�� device ��Ա�� struct scsi_device ָ��,��ô���                                                                              
// request_queue��?��struct request_queue�ṹ��ָ��,��ʾ����һ���������.�����Ǵ��Ķ���                                                                                  
// ����?һ·�������ֵ��ǿ��ܻ�µ�,��ʵ�� scsi �豸������ usb �豸������һ������ͬ��,                                                                                    
// �����ǵ� probe ����������֮ǰ,���Ĳ�ʵ�����Ѿ�Ϊ����������๤����.���� usb �Ǳ߾�Linux  ��Щ�¶�֮���� Block��                                                       
// �� 36  ҳ �� 117  ҳ                                                                                                                                                  
// ��Ϊ usb �豸���� usb_device �ṹ�����,�����Ҳ�����,������ scsi_device �ṹ�����,                                                                                 
// Ϊ����һЩ��Ա������ֵ,�����оͰ���������������.                                                                                                                    
// ׼ȷ��˵,�� scsi ����ɨ���ʱ��,ÿ��̽�⵽һ���豸,�ͻ���� scsi_alloc_sdev()����,���                                                                                
// �������������˵,���ǿ��Ը��������,�������һ������ scsi_alloc_queue()�ĺ���.�����                                                                                  
// �����漰���ܶ� block ���ṩ�ĺ���,�������ǲ��ò������￪ʼ����,����                                                                                                   
drivers/scsi/scsi_lib.c:                                                                                                                                              
   1569 struct request_queue *__scsi_alloc_queue(struct Scsi_Host *shost,                                                                                             
   1570                                          request_fn_proc *request_fn)                                                                                         
   1571 {                                                                                                                                                             
   1572         struct request_queue *q;                                                                                                                              
   1573                                                                                                                                                               
   1574         q = blk_init_queue(request_fn, NULL);                                                                                                                 
   1575         if (!q)                                                                                                                                               
   1576                 return NULL;                                                                                                                                  
   1577                                                                                                                                                               
   1578         blk_queue_max_hw_segments(q, shost->sg_tablesize);                                                                                                    
   1579         blk_queue_max_phys_segments(q, SCSI_MAX_PHYS_SEGMENTS);                                                                                               
   1580         blk_queue_max_sectors(q, shost->max_sectors);                                                                                                         
   1581         blk_queue_bounce_limit(q, scsi_calculate_bounce_limit(shost));                                                                                        
   1582         blk_queue_segment_boundary(q, shost->dma_boundary);                                                                                                   
   1583                                                                                                                                                               
   1584         if (!shost->use_clustering)                                                                                                                           
   1585                 clear_bit(QUEUE_FLAG_CLUSTER, &q->queue_flags);                                                                                               
   1586         return q;                                                                                                                                             
   1587 }                                                                                                                                                             
   1588 ////////EXPORT_SYMBOL(__scsi_alloc_queue);                                                                                                                            
   1589                                                                                                                                                               
   1590 struct request_queue *scsi_alloc_queue(struct scsi_device *sdev)                                                                                              
   1591 {                                                                                                                                                             
   1592         struct request_queue *q;                                                                                                                              
   1593                                                                                                                                                               
   1594         q = __scsi_alloc_queue(sdev->host, scsi_request_fn);                                                                                                  
   1595         if (!q)                                                                                                                                               
   1596                 return NULL;                                                                                                                                  
   1597                                                                                                                                                               
   1598         blk_queue_prep_rq(q, scsi_prep_fn);                                                                                                                   
   1599         blk_queue_issue_flush_fn(q, scsi_issue_flush_fn);                                                                                                     
   1600         blk_queue_softirq_done(q, scsi_softirq_done);                                                                                                         
   1601         return q;                                                                                                                                             
   1602 }                                                                                                                                                             
// ������������Ϊ���ù�ϵ����һ�����˳���.                                                                                                                               
// ��������Ҫ���ĺ���Ȼ���� blk_init_queue(),������ block/ll_rw_blk.c:                                                                                                   
//    1860 ///                                                                                                                                                           
//    1861  * blk_init_queue  - prepare a request queue for use with a block device Linux  ��Щ�¶�֮���� Block��                                                        
// �� 37  ҳ �� 117  ҳ                                                                                                                                                  
//    1862  * @rfn:  The function to be called to process requests that have been                                                                                        
//    1863  *        placed on the queue.                                                                                                                                
//    1864  * @lock: Request queue spin lock                                                                                                                             
//    1865  *                                                                                                                                                            
//    1866  * Description:                                                                                                                                               
//    1867  *    If a block device wishes to use the standard request handling procedures,                                                                               
//    1868  *    which sorts requests and coalesces adjacent requests, then it must                                                                                      
//    1869  *    call blk_init_queue().  The function @rfn will be called when there                                                                                     
//    1870  *    are requests on the queue that need to be processed.  If the device                                                                                     
//    1871  *    supports plugging, then @rfn may not be called immediately when requests                                                                                
//    1872  *    are available on the queue, but may be called at some time later instead.                                                                               
//    1873  *    Plugged queues are generally unplugged when a buffer belonging to one                                                                                   
//    1874  *    of the requests on the queue is needed, or due to memory pressure.                                                                                      
//    1875  *                                                                                                                                                            
//    1876  *    @rfn is not required, or even expected, to remove all requests off the                                                                                  
//    1877  *    queue, but only as many as it can handle at a time.  If it does leave                                                                                   
//    1878  *    requests on the queue, it is responsible for arranging that the requests                                                                                
//    1879  *    get dealt with eventually.                                                                                                                              
//    1880  *                                                                                                                                                            
//    1881  *    The queue spin lock must be held while manipulating the requests on the                                                                                 
//    1882  *    request queue; this lock will be taken also from interrupt context, so irq                                                                              
//    1883  *    disabling is needed for it.                                                                                                                             
//    1884  *                                                                                                                                                            
//    1885  *    Function returns a pointer to the initialized request queue, or NULL if                                                                                 
//    1886  *    it didn't succeed.                                                                                                                                      
//    1887  *                                                                                                                                                            
//    1888  * Note:                                                                                                                                                      
//    1889  *    blk_init_queue() must be paired with a blk_cleanup_queue() call                                                                                         
//    1890  *    when the block device is deactivated (such as at module unload).                                                                                        
//    1891  ///                                                                                                                                                          
   1892                                                                                                                                                               
   1893 request_queue_t *blk_init_queue(request_fn_proc *rfn, spinlock_t *lock)                                                                                       
   1894 {                                                                                                                                                             
   1895         return blk_init_queue_node(rfn, lock, -1);                                                                                                            
   1896 }                                                                                                                                                             
   1897 ////////EXPORT_SYMBOL(blk_init_queue);                                                                                                                                
   1898                                                                                                                                                               
   1899 request_queue_t *                                                                                                                                             
   1900 blk_init_queue_node(request_fn_proc *rfn, spinlock_t *lock, int node_id)                                                                                      
   1901 {                                                                                                                                                             
   1902         request_queue_t *q = blk_alloc_queue_node(GFP_KERNEL, node_id);                                                                                       
   1903                                                                                                                                                               
   1904         if (!q)                                                                                                                                               
   1905                 return NULL; Linux  ��Щ�¶�֮���� Block��                                                                                                    
�� 38  ҳ �� 117  ҳ                                                                                                                                                  
   1906                                                                                                                                                               
   1907         q->node = node_id;                                                                                                                                    
   1908         if (blk_init_free_list(q)) {                                                                                                                          
   1909                 kmem_cache_free(requestq_cachep, q);                                                                                                          
   1910                 return NULL;                                                                                                                                  
   1911         }                                                                                                                                                     
   1912                                                                                                                                                               
   1913         //                                                                                                                                                    
   1914          * if caller didn't supply a lock, they get per-queue locking with                                                                                    
   1915          * our embedded lock                                                                                                                                  
   1916          //                                                                                                                                                   
   1917         if (!lock) {                                                                                                                                          
   1918                 spin_lock_init(&q->__queue_lock);                                                                                                             
   1919                 lock = &q->__queue_lock;                                                                                                                      
   1920         }                                                                                                                                                     
   1921                                                                                                                                                               
   1922         q->request_fn           = rfn;                                                                                                                        
   1923         q->prep_rq_fn           = NULL;                                                                                                                       
   1924         q->unplug_fn            = generic_unplug_device;                                                                                                      
   1925         q->queue_flags          = (1 << QUEUE_FLAG_CLUSTER);                                                                                                  
   1926         q->queue_lock           = lock;                                                                                                                       
   1927                                                                                                                                                               
   1928         blk_queue_segment_boundary(q, 0xffffffff);                                                                                                            
   1929                                                                                                                                                               
   1930         blk_queue_make_request(q, __make_request);                                                                                                            
   1931         blk_queue_max_segment_size(q, MAX_SEGMENT_SIZE);                                                                                                      
   1932                                                                                                                                                               
   1933         blk_queue_max_hw_segments(q, MAX_HW_SEGMENTS);                                                                                                        
   1934         blk_queue_max_phys_segments(q, MAX_PHYS_SEGMENTS);                                                                                                    
   1935                                                                                                                                                               
   1936         q->sg_reserved_size = INT_MAX;                                                                                                                        
   1937                                                                                                                                                               
   1938         //                                                                                                                                                    
   1939          * all done                                                                                                                                           
   1940          //                                                                                                                                                   
   1941         if (!elevator_init(q, NULL)) {                                                                                                                        
   1942                 blk_queue_congestion_threshold(q);                                                                                                            
   1943                 return q;                                                                                                                                     
   1944         }                                                                                                                                                     
   1945                                                                                                                                                               
   1946         blk_put_queue(q);                                                                                                                                     
   1947         return NULL;                                                                                                                                          
   1948 }                                                                                                                                                             
// ����Щ�������ܿ���,��������Ŀǰ��Ҫ��ע����ʵֻ�����е�ĳ��������.�������Linux  ��Щ�¶�֮���� Block��                                                             
// �� 39  ҳ �� 117  ҳ                                                                                                                                                  
blk_alloc_queue_node��elevator_init().ǰ������block/ll_rw_blk.c,����������block/elevator.c:                                                                           
   1836 request_queue_t *blk_alloc_queue_node(gfp_t gfp_mask, int node_id)                                                                                            
   1837 {                                                                                                                                                             
   1838         request_queue_t *q;                                                                                                                                   
   1839                                                                                                                                                               
   1840         q = kmem_cache_alloc_node(requestq_cachep, gfp_mask, node_id);                                                                                        
   1841         if (!q)                                                                                                                                               
   1842                 return NULL;                                                                                                                                  
   1843                                                                                                                                                               
   1844         memset(q, 0, sizeof(*q));                                                                                                                             
   1845         init_timer(&q->unplug_timer);                                                                                                                         
   1846                                                                                                                                                               
   1847         snprintf(q->kobj.name, KOBJ_NAME_LEN, "%s", "queue");                                                                                                 
   1848         q->kobj.ktype = &queue_ktype;                                                                                                                         
   1849         kobject_init(&q->kobj);                                                                                                                               
   1850                                                                                                                                                               
   1851         q->backing_dev_info.unplug_io_fn = blk_backing_dev_unplug;                                                                                            
   1852         q->backing_dev_info.unplug_io_data = q;                                                                                                               
   1853                                                                                                                                                               
   1854         mutex_init(&q->sysfs_lock);                                                                                                                           
   1855                                                                                                                                                               
   1856         return q;                                                                                                                                             
   1857 }                                                                                                                                                             
// ���ǵñ���������ʱ�ڽ����Ǹ�blk_dev_init��,��ʱ���ǵ���kmem_cache_create()������һ                                                                                    
// ���ڴ�� request_cachep,���ھ͸�������.�����������������һ�� struct request_queue_t ��                                                                               
// ����Ŀռ�,����ָ�� q,Ȼ�� 1844 �г�ʼ��Ϊ 0.�� 1847 ���� q �� kobj.name ���ڡ�queue��,��                                                                             
// ����Ϊʲô���������/sys/block/sda/Ŀ¼�����ܿ���һ��������queue����Ŀ¼.                                                                                             
// [root@localhost ~]# ls /sys/block/sda/                                                                                                                                
// capability  device   queue  removable  sda10   sda12  sda14  sda2  sda5  sda7  sda9                                                                                   
// slaves  subsystem dev         holders  range  sda1       sda11  sda13  sda15  sda3                                                                                    
// sda6  sda8  size  stat    uevent                                                                                                                                      
// ����� queue Ŀ¼�����������ʲô��?                                                                                                                                  
// [root@localhost ~]# ls /sys/block/sda/queue/                                                                                                                          
// iosched  max_hw_sectors_kb  max_sectors_kb  nr_requests  read_ahead_kb  scheduler                                                                                     
// �⼸���ļ���������?ע�� 1848 ���Ǹ� queue_ktype.                                                                                                                      
   4073 static struct kobj_type queue_ktype = {                                                                                                                       
   4074         .sysfs_ops      = &queue_sysfs_ops,                                                                                                                   
   4075         .default_attrs  = default_attrs,                                                                                                                      
   4076         .release        = blk_release_queue,                                                                                                                  
   4077 };                                                                                                                                                            
// ������涮�豸ģ��,��ô��һ����ȥ�鿴��� default_attrs��ʲô,                                                                                                        
   3988 static struct queue_sysfs_entry queue_requests_entry = {                                                                                                      
   3989         .attr = {.name = "nr_requests", .mode = S_IRUGO | S_IWUSR },                                                                                          
   3990         .show = queue_requests_show, Linux  ��Щ�¶�֮���� Block��                                                                                            
�� 40  ҳ �� 117  ҳ                                                                                                                                                  
   3991         .store = queue_requests_store,                                                                                                                        
   3992 };                                                                                                                                                            
   3993                                                                                                                                                               
   3994 static struct queue_sysfs_entry queue_ra_entry = {                                                                                                            
   3995         .attr = {.name = "read_ahead_kb", .mode = S_IRUGO | S_IWUSR },                                                                                        
   3996         .show = queue_ra_show,                                                                                                                                
   3997         .store = queue_ra_store,                                                                                                                              
   3998 };                                                                                                                                                            
   3999                                                                                                                                                               
   4000 static struct queue_sysfs_entry queue_max_sectors_entry = {                                                                                                   
   4001         .attr = {.name = "max_sectors_kb", .mode = S_IRUGO | S_IWUSR },                                                                                       
   4002         .show = queue_max_sectors_show,                                                                                                                       
   4003         .store = queue_max_sectors_store,                                                                                                                     
   4004 };                                                                                                                                                            
   4005                                                                                                                                                               
   4006 static struct queue_sysfs_entry queue_max_hw_sectors_entry = {                                                                                                
   4007         .attr = {.name = "max_hw_sectors_kb", .mode = S_IRUGO },                                                                                              
   4008         .show = queue_max_hw_sectors_show,                                                                                                                    
   4009 };                                                                                                                                                            
   4010                                                                                                                                                               
   4011 static struct queue_sysfs_entry queue_iosched_entry = {                                                                                                       
   4012         .attr = {.name = "scheduler", .mode = S_IRUGO | S_IWUSR },                                                                                            
   4013         .show = elv_iosched_show,                                                                                                                             
   4014         .store = elv_iosched_store,                                                                                                                           
   4015 };                                                                                                                                                            
   4016                                                                                                                                                               
   4017 static struct attribute *default_attrs[] = {                                                                                                                  
   4018         &queue_requests_entry.attr,                                                                                                                           
   4019         &queue_ra_entry.attr,                                                                                                                                 
   4020         &queue_max_hw_sectors_entry.attr,                                                                                                                     
   4021         &queue_max_sectors_entry.attr,                                                                                                                        
   4022         &queue_iosched_entry.attr,                                                                                                                            
   4023         NULL,                                                                                                                                                 
   4024 };                                                                                                                                                            
// ��������?��һ��ָ������,�����豸ģ�͵�������˵,��Щ���Ƕ�����һЩ����,kobject ����                                                                                    
// ��,������Щ���Ե�name�ǲ��Ǻ͸ղ��Ǹ�queueĿ¼������ļ�������һ����?û��,queue                                                                                       
// Ŀ¼����ÿ���ļ����Ǻ�������Щ����һһ��Ӧ��.������һ����������,������ iosched,��                                                                                     
// ����һ���ļ�,����һ��Ŀ¼.                                                                                                                                            
// [root@localhost ~]# ls -l /sys/block/sdf/queue/                                                                                                                       
// total 0                                                                                                                                                               
// drwxr-xr-x 2 root root    0 Dec 14 02:46 iosched                                                                                                                      
// -r--r--r-- 1 root root 4096 Dec 14 06:21 max_hw_sectors_kb                                                                                                            
// -rw-r--r-- 1 root root 4096 Dec 14 06:21 max_sectors_kb                                                                                                               
// -rw-r--r-- 1 root root 4096 Dec 14 06:21 nr_requests Linux  ��Щ�¶�֮���� Block��                                                                                    
// �� 41  ҳ �� 117  ҳ                                                                                                                                                  
// -rw-r--r-- 1 root root 4096 Dec 14 06:21 read_ahead_kb                                                                                                                
// -rw-r--r-- 1 root root 4096 Dec 14 06:21 scheduler                                                                                                                    
// [root@localhost ~]# ls /sys/block/sdf/queue/iosched/                                                                                                                  
// back_seek_max      fifo_expire_async  quantum      slice_async_rq  slice_sync                                                                                         
// back_seek_penalty  fifo_expire_sync   slice_async  slice_idle                                                                                                         
// �������Ŀ¼,����������һ������,elevator_init(),���� block/elevator.c:                                                                                                
    220 int elevator_init(request_queue_t *q, char *name)                                                                                                             
    221 {                                                                                                                                                             
    222         struct elevator_type *e = NULL;                                                                                                                       
    223         struct elevator_queue *eq;                                                                                                                            
    224         int ret = 0;                                                                                                                                          
    225         void *data;                                                                                                                                           
    226                                                                                                                                                               
    227         INIT_LIST_HEAD(&q->queue_head);                                                                                                                       
    228         q->last_merge = NULL;                                                                                                                                 
    229         q->end_sector = 0;                                                                                                                                    
    230         q->boundary_rq = NULL;                                                                                                                                
    231                                                                                                                                                               
    232         if (name && !(e = elevator_get(name)))                                                                                                                
    233                 return -EINVAL;                                                                                                                               
    234                                                                                                                                                               
    235         if (!e && *chosen_elevator && !(e = elevator_get(chosen_elevator)))                                                                                   
    236                 printk("I/O scheduler %s not found\n", chosen_elevator);                                                                                      
    237                                                                                                                                                               
    238         if (!e && !(e = elevator_get(CONFIG_DEFAULT_IOSCHED))) {                                                                                              
    239                 printk("Default I/O scheduler not found, using no-op\n");                                                                                     
    240                 e = elevator_get("noop");                                                                                                                     
    241         }                                                                                                                                                     
    242                                                                                                                                                               
    243         eq = elevator_alloc(q, e);                                                                                                                            
    244         if (!eq)                                                                                                                                              
    245                 return -ENOMEM;                                                                                                                               
    246                                                                                                                                                               
    247         data = elevator_init_queue(q, eq);                                                                                                                    
    248         if (!data) {                                                                                                                                          
    249                 kobject_put(&eq->kobj);                                                                                                                       
    250                 return -ENOMEM;                                                                                                                               
    251         }                                                                                                                                                     
    252                                                                                                                                                               
    253         elevator_attach(q, eq, data);                                                                                                                         
    254         return ret;                                                                                                                                           
    255 }                                                                                                                                                             
�ص��ע elevator_alloc().                                                                                                                                            
    179 static elevator_t *elevator_alloc(request_queue_t *q, struct elevator_type *e) Linux  ��Щ�¶�֮���� Block��                                                  
�� 42  ҳ �� 117  ҳ                                                                                                                                                  
    180 {                                                                                                                                                             
    181         elevator_t *eq;                                                                                                                                       
    182         int i;                                                                                                                                                
    183                                                                                                                                                               
    184         eq = kmalloc_node(sizeof(elevator_t), GFP_KERNEL, q->node);                                                                                           
    185         if (unlikely(!eq))                                                                                                                                    
    186                 goto err;                                                                                                                                     
    187                                                                                                                                                               
    188         memset(eq, 0, sizeof(*eq));                                                                                                                           
    189         eq->ops = &e->ops;                                                                                                                                    
    190         eq->elevator_type = e;                                                                                                                                
    191         kobject_init(&eq->kobj);                                                                                                                              
    192         snprintf(eq->kobj.name, KOBJ_NAME_LEN, "%s", "iosched");                                                                                              
    193         eq->kobj.ktype = &elv_ktype;                                                                                                                          
    194         mutex_init(&eq->sysfs_lock);                                                                                                                          
    195                                                                                                                                                               
    196         eq->hash = kmalloc_node(sizeof(struct hlist_head) * ELV_HASH_ENTRIES,                                                                                 
    197                                         GFP_KERNEL, q->node);                                                                                                 
    198         if (!eq->hash)                                                                                                                                        
    199                 goto err;                                                                                                                                     
    200                                                                                                                                                               
    201         for (i = 0; i < ELV_HASH_ENTRIES; i++)                                                                                                                
    202                 INIT_HLIST_HEAD(&eq->hash[i]);                                                                                                                
    203                                                                                                                                                               
    204         return eq;                                                                                                                                            
    205 err:                                                                                                                                                          
    206         kfree(eq);                                                                                                                                            
    207         elevator_put(e);                                                                                                                                      
    208         return NULL;                                                                                                                                          
    209 }                                                                                                                                                             
// �޷Ǿ�������һ�� struct elevator_t �ṹ������Ŀռ䲢�ҳ�ʼ��Ϊ 0.                                                                                                    
// ����������������Ȥ����192��,����Ȼ,������Ϊ�����eq��kobj��name����Ϊ��iosched��,                                                                                     
// �Ż��������� queue Ŀ¼�¿����Ǹ���iosched����Ŀ¼.                                                                                                                   
// �������Ŀ¼����Щ���߰�����ļ�������������?����������� elv_register_queue()����,                                                                                   
// ��������� blk_register_queue()�е��õĺ���.                                                                                                                          
    931 int elv_register_queue(struct request_queue *q)                                                                                                               
    932 {                                                                                                                                                             
    933         elevator_t *e = q->elevator;                                                                                                                          
    934         int error;                                                                                                                                            
    935                                                                                                                                                               
    936         e->kobj.parent = &q->kobj;                                                                                                                            
    937                                                                                                                                                               
    938         error = kobject_add(&e->kobj);                                                                                                                        
    939         if (!error) { Linux  ��Щ�¶�֮���� Block��                                                                                                           
�� 43  ҳ �� 117  ҳ                                                                                                                                                  
    940                 struct elv_fs_entry *attr = e->elevator_type->elevator_attrs;                                                                                 
    941                 if (attr) {                                                                                                                                   
    942                         while (attr->attr.name) {                                                                                                             
    943                                 if (sysfs_create_file(&e->kobj, &attr->attr))                                                                                 
    944                                         break;                                                                                                                
    945                                 attr++;                                                                                                                       
    946                         }                                                                                                                                     
    947                 }                                                                                                                                             
    948                 kobject_uevent(&e->kobj, KOBJ_ADD);                                                                                                           
    949         }                                                                                                                                                     
    950         return error;                                                                                                                                         
    951 }                                                                                                                                                             
// 936 �б�֤��,iosched �ǳ����� queue Ŀ¼�¶����ǳ����ڱ�ĵط�,�� 942 ����� while ѭ                                                                                 
// �����Ǵ��� iosched Ŀ¼������ô���ļ���.������������� attr ������ʲô,������ָ����                                                                                   
// e->elevator_type->elevator_attrs,���ڸղ��Ǹ� elevator_alloc()������,190 ��,���ǿ�����                                                                                
// eq->elevator_type�������� e,������ elevator_init(),�������� e������ʲô.                                                                                              
// ����,��������blk_init_queue_node()�е���elevator_init��ʱ��,���ݵĵڶ���������NULL,                                                                                   
// �� name ָ���� NULL.                                                                                                                                                  
// ��ô������,235 �к� 238�������� if������ e��ȡֵ������Ҫ.����������,��˵�еĵ���                                                                                    
// �㷨Ҳ���ò�������.                                                                                                                                                   
// ��˵,�� Linux �������Ҫ��дһЩ��������,����Ҫ����һ�� block device request.���                                                                                     
// request ����������������������Լ�����������.(��,����Ҫ������Ҫд)������һ���豸��                                                                                    
// ˵,���������Ȼ��Ӧ��ʹ��ĳ�����ݽṹ���洢����,����Ȼ���ǻ�ʹ�ö���,����,Linux��                                                                                     
// Ϊÿ�����豸׼����һ���������,����ν�� request queue.ÿ���յ�һ������,�Ͱ������뵽                                                                                   
// request queue���������ȥ.                                                                                                                                            
// ��ô������һ������,����˵�������кü�ʮ������,��ô˭��ִ��˭��ִ����?�ǲ���˭��                                                                                       
// �ύ����ִ��˭?����.������Ҫ����,������̵����ܾͻ�����.                                                                                                            
// ����˵Ӣ������,���Ҽ��ж���������,һ������ 38 ��Ӣ������,���˵������һ������һ��                                                                                     
// �ͳ�һ������һ���ͳ�һ������һ���ͳ���,��ô����������һ���Ǻ�����,��Ϊ��ԱҪ��                                                                                      
// ͣ�ı���,ÿ��һ�������͵ý���һ�γ����Ͷ�,��Ա�׷�ƣ�ڱ���,״̬�����޷���֤,��ô                                                                                      
// ������õ��������ʲô?����,������������,���������ͳ�,��ô�������������⼸������                                                                                      
// ��ս���ڼ���Ա�ǲ��ð�������������;��,���������ļ����ͳ���,��ô��������������,                                                                                       
// �����������ĸ������Ŀͳ�,���ֱַ�������,����,������,������,��ô�����������,������                                                                                    
// ������������������,�������ֺ��߰���������������,������;�ķ�ʱ������,��ô�����                                                                                       
// ��������ʲô��?��ȥ����˹��������,Ȼ��ȥ��������������,Ȼ�����ۻ�����˹��������,                                                                                      
// ��Ȼ����ɱ��������ȥս������,����Ȼ�����������������,�������ν��ħ������.��                                                                                       
// �����̵ĺû����п���Ӱ��һ֧��ӵ�ս��.                                                                                                                               
// �����̵���Ҳ�����.��ͷ��������ȥ�Ǻܷ�ʱ���,�������һ��Ҫ���������ڡ�����˹�ء�,                                                                                   
// ��һ��Ҫ�����������ڡ������֡�,���´��ֻص�������˹�ء�,Ȼ����ȥ���������֡�,������Ȼ��                                                                               
// Ӱ����̵�����.������������ܹ��ı�����˳��,�ܹ���ǰ�����η��ʵ��������������ڵ�                                                                                      
// λ��,��ô�������ʽ���ߴ��̵�����.�����������Ľ��� IO������.(The I/O Scheduler)                                                                                   
// IO ������������Ŀ����ϣ���ô�ͷ�ܹ�������һ�������ƶ�,�ƶ�������������������,��                                                                                       
// ǡǡ������ʵ�����еĵ���ģ��,���� IO ������Ҳ����������.(elevator)����Ӧ���㷨Ҳ��                                                                                    
// �����������㷨.��Linux��IO���ȵĵ����㷨�кü���,һ������as(Anticipatory),һ������Linux  ��Щ�¶�֮���� Block��                                                       
// �� 44  ҳ �� 117  ҳ                                                                                                                                                  
// cfq(Complete Fairness Queueing),һ������ deadline,����һ������ noop(No Operation).����ʹ                                                                              
// �������㷨���ǿ�����������ʱ��ͨ���ں˲��� elevator ��ָ��.�������ҵ� grub �����ļ�                                                                                   
// �о��������ù�:                                                                                                                                                       
// ###Don't change this comment - YaST2 identifier: Original name: linux###                                                                                              
// title Linux                                                                                                                                                           
//     kernel (hd0,0)/vmlinuz root=/dev/sda3 selinux=0 resume=/dev/sda2 splash=silent                                                                                    
// elevator=cfq showopts console=ttyS0,9600 console=tty0                                                                                                                 
//     initrd (hd0,0)/initrd                                                                                                                                             
// �� elevator=cfq,��� cfq �㷨�������ǵ� IO �����������õ��㷨.����һ��������Ҳ���Ե�                                                                                  
// ����Ϊĳ���豸ָ���������õ� IO �����㷨,���ͨ���޸���/sys/block/sda/queue/Ŀ¼����                                                                                  
// �� scheduler�ļ�.�������ǿ����ȿ�һ���ҵ����Ӳ��:                                                                                                                    
// [root@localhost ~]# cat /sys/block/sda/queue/scheduler                                                                                                                
// noop anticipatory deadline [cfq]                                                                                                                                      
// ���Կ�������������õ��� cfq.                                                                                                                                         
// Ok,���ڻ�����ϸ˵�⼸���㷨��ʱ��,���ǽ��ŸղŵĻ���,���� elevator_init().                                                                                            
// ���� chosen_elevator�Ƕ����� block/elevator.c �е�һ���ַ���.                                                                                                         
//     160 static char chosen_elevator[16];                                                                                                                              
// ����ַ�������������¼�������� elevator��.���û������,�Ǿ�û��ֵ.                                                                                                    
// �� CONFIG_DEFAULT_IOSCHED ��һ������ѡ��.������һ�ַ���,�ڱ����ں˵�ʱ������                                                                                          
// ��,�����ҵ��� cfq.                                                                                                                                                    
//     119 CONFIG_DEFAULT_IOSCHED="cfq"                                                                                                                                  
// �㵱ȻҲ����ѡ����������,������ϲ����,ϲ���ĸ���ѡ���ĸ�.�ҵĽ�����,ϲ���ľ�Ҫӵ                                                                                      
// ����,��Ҫ���½��.��֮����ַ����ᴫ�ݸ� elevator_get ������� block/elevator.c �ĺ���:                                                                               
    133 static struct elevator_type *elevator_get(const char *name)                                                                                                   
    134 {                                                                                                                                                             
    135         struct elevator_type *e;                                                                                                                              
    136                                                                                                                                                               
    137         spin_lock(&elv_list_lock);                                                                                                                            
    138                                                                                                                                                               
    139         e = elevator_find(name);                                                                                                                              
    140         if (e && !try_module_get(e->elevator_owner))                                                                                                          
    141                 e = NULL;                                                                                                                                     
    142                                                                                                                                                               
    143         spin_unlock(&elv_list_lock);                                                                                                                          
    144                                                                                                                                                               
    145         return e;                                                                                                                                             
    146 }                                                                                                                                                             
���� elevator_find()Ҳ����ͬһ���ļ�.                                                                                                                                 
    112 static struct elevator_type *elevator_find(const char *name)                                                                                                  
    113 {                                                                                                                                                             
    114         struct elevator_type *e;                                                                                                                              
    115         struct list_head *entry;                                                                                                                              
    116                                                                                                                                                               
    117         list_for_each(entry, &elv_list) { Linux  ��Щ�¶�֮���� Block��                                                                                       
�� 45  ҳ �� 117  ҳ                                                                                                                                                  
    118                                                                                                                                                               
    119                 e = list_entry(entry, struct elevator_type, list);                                                                                            
    120                                                                                                                                                               
    121                 if (!strcmp(e->elevator_name, name))                                                                                                          
    122                         return e;                                                                                                                             
    123         }                                                                                                                                                     
    124                                                                                                                                                               
    125         return NULL;                                                                                                                                          
    126 }                                                                                                                                                             
// &elv_list ��ʲô?����,���������������������Ǽ��Է��޶�֪�� elv_list һ����һ������.��                                                                                 
// ���������������ʲô������?��ʵ��,�¹����������㷨�е���һ��,����ʽ��̨�ݳ�֮ǰ,                                                                                      
// ����Ҫ��һЩ��ʼ��,��ʼ����������ʵ�һ������ǵ��� elv_register()������ע����                                                                                    
// ��.�����ע����Ҫ������ elv_list ����������Ǽ�.                                                                                                                      
    965 int elv_register(struct elevator_type *e)                                                                                                                     
    966 {                                                                                                                                                             
    967         char *def = "";                                                                                                                                       
    968                                                                                                                                                               
    969         spin_lock(&elv_list_lock);                                                                                                                            
    970         BUG_ON(elevator_find(e->elevator_name));                                                                                                              
    971         list_add_tail(&e->list, &elv_list);                                                                                                                   
    972         spin_unlock(&elv_list_lock);                                                                                                                          
    973                                                                                                                                                               
    974         if (!strcmp(e->elevator_name, chosen_elevator) ||                                                                                                     
    975                         (!*chosen_elevator &&                                                                                                                 
    976                          !strcmp(e->elevator_name,                                                                                                            
CONFIG_DEFAULT_IOSCHED)))                                                                                                                                             
    977                                 def = " (default)";                                                                                                           
    978                                                                                                                                                               
    979         printk(KERN_INFO "io scheduler %s registered%s\n", e->elevator_name,                                                                                  
def);                                                                                                                                                                 
    980         return 0;                                                                                                                                             
    981 }                                                                                                                                                             
// ���� list_add_tail ��������.��ô��� elevator_type �ṹ���ִ�����ʲô��?��������,������                                                                               
// ��һ�ֵ����㷨������,������� cfq,�� cfq-iosched.c �ļ���,�Ͷ�������ôһ���ṹ�����                                                                                  
// iosched_cfq.                                                                                                                                                          
   2188 static struct elevator_type iosched_cfq = {                                                                                                                   
   2189         .ops = {                                                                                                                                              
   2190                 .elevator_merge_fn =            cfq_merge,                                                                                                    
   2191                 .elevator_merged_fn =           cfq_merged_request,                                                                                           
   2192                 .elevator_merge_req_fn =        cfq_merged_requests,                                                                                          
   2193                 .elevator_allow_merge_fn =      cfq_allow_merge,                                                                                              
   2194                 .elevator_dispatch_fn =         cfq_dispatch_requests,                                                                                        
   2195                 .elevator_add_req_fn =          cfq_insert_request,                                                                                           
   2196                 .elevator_activate_req_fn =     cfq_activate_request, Linux  ��Щ�¶�֮���� Block��                                                           
�� 46  ҳ �� 117  ҳ                                                                                                                                                  
   2197                 .elevator_deactivate_req_fn =   cfq_deactivate_request,                                                                                       
   2198                 .elevator_queue_empty_fn =      cfq_queue_empty,                                                                                              
   2199                .elevator_completed_req_fn =    cfq_completed_request,                                                                                         
   2200                 .elevator_former_req_fn =       elv_rb_former_request,                                                                                        
   2201                 .elevator_latter_req_fn =       elv_rb_latter_request,                                                                                        
   2202                 .elevator_set_req_fn =          cfq_set_request,                                                                                              
   2203                 .elevator_put_req_fn =          cfq_put_request,                                                                                              
   2204                 .elevator_may_queue_fn =        cfq_may_queue,                                                                                                
   2205                 .elevator_init_fn =             cfq_init_queue,                                                                                               
   2206                 .elevator_exit_fn =             cfq_exit_queue,                                                                                               
   2207                 .trim =                         cfq_free_io_context,                                                                                          
   2208         },                                                                                                                                                    
   2209         .elevator_attrs =       cfq_attrs,                                                                                                                    
   2210         .elevator_name =        "cfq",                                                                                                                        
   2211         .elevator_owner =       THIS_MODULE,                                                                                                                  
   2212 };                                                                                                                                                            
ͬ��,���ǿ����ҵ�,����noop,Ҳ�����Ƶı���.                                                                                                                            
     87 static struct elevator_type elevator_noop = {                                                                                                                 
     88         .ops = {                                                                                                                                              
     89              .elevator_merge_req_fn          = noop_merged_requests,                                                                                          
     90                 .elevator_dispatch_fn           = noop_dispatch,                                                                                              
     91                 .elevator_add_req_fn            = noop_add_request,                                                                                           
     92                 .elevator_queue_empty_fn        = noop_queue_empty,                                                                                           
     93                 .elevator_former_req_fn         = noop_former_request,                                                                                        
     94                 .elevator_latter_req_fn         = noop_latter_request,                                                                                        
     95                 .elevator_init_fn               = noop_init_queue,                                                                                            
     96                 .elevator_exit_fn               = noop_exit_queue,                                                                                            
     97         },                                                                                                                                                    
     98         .elevator_name = "noop",                                                                                                                              
     99         .elevator_owner = THIS_MODULE,                                                                                                                        
    100 };                                                                                                                                                            
// ����,���Ǿ�֪�����e������Ҫ�õ�ʲô��,�����ʲô��û����,��ô��ֻ��ѡ��������                                                                                      
// ��,noop.���ǵ����������������� elv_register_queue()���Ǹ� e->elevator_type ��ɶ��.������                                                                              
// Ҫ����e->elevator_type->elevator_attrs.����cfq,����Ȼ,������cfq_attrs.��block/cfq-iosched.c                                                                           
// ��:                                                                                                                                                                   
   2175 static struct elv_fs_entry cfq_attrs[] = {                                                                                                                    
   2176         CFQ_ATTR(quantum),                                                                                                                                    
   2177         CFQ_ATTR(fifo_expire_sync),                                                                                                                           
   2178         CFQ_ATTR(fifo_expire_async),                                                                                                                          
   2179         CFQ_ATTR(back_seek_max),                                                                                                                              
   2180         CFQ_ATTR(back_seek_penalty),                                                                                                                          
   2181         CFQ_ATTR(slice_sync),                                                                                                                                 
   2182         CFQ_ATTR(slice_async),                                                                                                                                
   2183         CFQ_ATTR(slice_async_rq), Linux  ��Щ�¶�֮���� Block��                                                                                               
�� 47  ҳ �� 117  ҳ                                                                                                                                                  
   2184         CFQ_ATTR(slice_idle),                                                                                                                                 
   2185         __ATTR_NULL                                                                                                                                           
   2186 };                                                                                                                                                            
// ����,�Ǹ� while ѭ���� sysfs_create_file �Ĺ���������������������Ԫ�ص����ֽ���һ��                                                                                 
// ���ļ�.��������������/sys/block/sdf/queue/iosched/Ŀ¼���濴������Щ�ļ�.                                                                                             
// ����,elv_register_queue �����ǽ�����,�Ӷ� blk_register_queue()Ҳ�ͽ�����,�� add_disk ���                                                                             
// ����ĺ������ڴ󹦸��.��һ�̿�ʼ,�������豸�����Ĵ���̨���Ѿ������.���� sd �Ǳ�                                                                                     
// ��˵,sd_probe �����ڽ��� add_disk֮�������.                                                                                                                          
// ����֮��,�����������һ����,�Ҳ��ò�����,add_disk �������,���ֻ�����д���ĺ���,                                                                                    
// �ܺ�,��ǿ��.д����Ͼ�����д�����籾,��������<<һ������>>���һ�䡱�Ұ��㡱,��Ҫ��                                                                                    
// ��ʮ������ڹ��,�ǲŽ�һ�������!                                                                                                                                      
//                                                                                                                                                                       
// scsi �����ǰ������(һ)                                                                                                                                               
// �������ǿ��豸Ҳ����,����Ҳ����,Ҫ�ύ����Ҳ�Ϳ��Կ�ʼ�ύ��.�Ǿ����������о�һ                                                                                       
// ������ύ������δ��������.�������Ƕ���������,���������Щ���߰���Ĵ�������                                                                                      
// �Ͳ������.                                                                                                                                                           
// ��Ȼ��scsi���̾���,���scsi��߷��͵���scsi����,���Ǵ�block�߾͵ñ��request,Ȼ��                                                                                     
// �ߵ� usb-storage �Ǳ��ֵñ�� scsi ����.����֮,���������� scsi ����Ҫ��������.                                                                                        
// ���������Ǵ�sd�Ǳߺܳ��õ�һ��������ʼ,��������scsi����������ڹ��컯��֮�±�͵                                                                                       
// �������ı���� request,����������� scsi_execute_req().����drivers/scsi/scsi_lib.c:                                                                                   
    216 int scsi_execute_req(struct scsi_device *sdev, const unsigned char *cmd,                                                                                      
    217                      int data_direction, void *buffer, unsigned bufflen,                                                                                      
    218                      struct scsi_sense_hdr *sshdr, int timeout, int retries)                                                                                  
    219 {                                                                                                                                                             
    220         char *sense = NULL;                                                                                                                                   
    221         int result;                                                                                                                                           
    222                                                                                                                                                               
    223         if (sshdr) {                                                                                                                                          
    224                 sense = kzalloc(SCSI_SENSE_BUFFERSIZE, GFP_NOIO);                                                                                             
    225                 if (!sense)                                                                                                                                   
    226                         return DRIVER_ERROR << 24;                                                                                                            
    227         }                                                                                                                                                     
    228         result = scsi_execute(sdev, cmd, data_direction, buffer, bufflen,                                                                                     
    229                               sense, timeout, retries, 0);                                                                                                    
    230         if (sshdr)                                                                                                                                            
    231                 scsi_normalize_sense(sense, SCSI_SENSE_BUFFERSIZE, sshdr);                                                                                    
    232                                                                                                                                                               
    233         kfree(sense);                                                                                                                                         
    234         return result;                                                                                                                                        
    235 }                                                                                                                                                             
// ����������Ҫ��ע�ľ���һ������,scsi_execute(),����ͬһ���ļ�. Linux  ��Щ�¶�֮���� Block��                                                                           
// �� 48  ҳ �� 117  ҳ                                                                                                                                                  
    164 ///                                                                                                                                                           
//    165  * scsi_execute - insert request and wait for the result                                                                                                      
//    166  * @sdev:       scsi device                                                                                                                                   
//    167  * @cmd:        scsi command                                                                                                                                  
//    168  * @data_direction: data direction                                                                                                                            
//    169  * @buffer:     data buffer                                                                                                                                   
//    170  * @bufflen:    len of buffer                                                                                                                                 
//    171  * @sense:      optional sense buffer                                                                                                                         
//    172  * @timeout:    request timeout in seconds                                                                                                                    
//    173  * @retries:    number of times to retry request                                                                                                              
//    174  * @flags:      or into request flags;                                                                                                                        
//    175  *                                                                                                                                                            
//    176  * returns the req->errors value which is the scsi_cmnd result                                                                                                
//    177  * field.                                                                                                                                                     
//    178  ///                                                                                                                                                          
    179 int scsi_execute(struct scsi_device *sdev, const unsigned char *cmd,                                                                                          
    180                  int data_direction, void *buffer, unsigned bufflen,                                                                                          
    181                  unsigned char *sense, int timeout, int retries, int flags)                                                                                   
    182 {                                                                                                                                                             
    183         struct request *req;                                                                                                                                  
    184         int write = (data_direction == DMA_TO_DEVICE);                                                                                                        
    185         int ret = DRIVER_ERROR << 24;                                                                                                                         
    186                                                                                                                                                               
    187         req = blk_get_request(sdev->request_queue, write, __GFP_WAIT);                                                                                        
    188                                                                                                                                                               
    189         if (bufflen &&  blk_rq_map_kern(sdev->request_queue, req,                                                                                             
    190                                         buffer, bufflen, __GFP_WAIT))                                                                                         
    191                 goto out;                                                                                                                                     
    192                                                                                                                                                               
    193         req->cmd_len = COMMAND_SIZE(cmd[0]);                                                                                                                  
    194         memcpy(req->cmd, cmd, req->cmd_len);                                                                                                                  
    195         req->sense = sense;                                                                                                                                   
    196         req->sense_len = 0;                                                                                                                                   
    197         req->retries = retries;                                                                                                                               
    198         req->timeout = timeout;                                                                                                                               
    199         req->cmd_type = REQ_TYPE_BLOCK_PC;                                                                                                                    
    200         req->cmd_flags |= flags | REQ_QUIET | REQ_PREEMPT;                                                                                                    
    201                                                                                                                                                               
    202         //                                                                                                                                                    
    203          * head injection *required* here otherwise quiesce won't work                                                                                        
204          //                                                                                                                                                       
    205         blk_execute_rq(req->q, NULL, req, 1);                                                                                                                 
    206                                                                                                                                                               
    207         ret = req->errors; Linux  ��Щ�¶�֮���� Block��                                                                                                      
�� 49  ҳ �� 117  ҳ                                                                                                                                                  
    208  out:                                                                                                                                                         
    209         blk_put_request(req);                                                                                                                                 
    210                                                                                                                                                               
    211         return ret;                                                                                                                                           
    212 }                                                                                                                                                             
//���ȱ����õ��� blk_get_request.����block/ll_rw_blk.c:                                                                                                                 
   2215 struct request *blk_get_request(request_queue_t *q, int rw, gfp_t gfp_mask)                                                                                   
   2216 {                                                                                                                                                             
   2217         struct request *rq;                                                                                                                                   
   2218                                                                                                                                                               
   2219         BUG_ON(rw != READ && rw != WRITE);                                                                                                                    
   2220                                                                                                                                                               
   2221         spin_lock_irq(q->queue_lock);                                                                                                                         
   2222         if (gfp_mask & __GFP_WAIT) {                                                                                                                          
   2223                 rq = get_request_wait(q, rw, NULL);                                                                                                           
   2224         } else {                                                                                                                                              
   2225                 rq = get_request(q, rw, NULL, gfp_mask);                                                                                                      
   2226                 if (!rq)                                                                                                                                      
   2227                         spin_unlock_irq(q->queue_lock);                                                                                                       
   2228         }                                                                                                                                                     
   2229         // q->queue_lock is unlocked at this point //                                                                                                         
   2230                                                                                                                                                               
   2231         return rq;                                                                                                                                            
   2232 }                                                                                                                                                             
//ע�⵽���ǵ������������ʱ��,�ڶ�������ȷʵ��__GFP_WAIT.���� 2223 �лᱻִ                                                                                            
//��.get_request_wait()����ͬһ���ļ�:                                                                                                                                  
   2173 static struct request *get_request_wait(request_queue_t *q, int rw_flags,                                                                                     
   2174                                         struct bio *bio)                                                                                                      
   2175 {                                                                                                                                                             
   2176         const int rw = rw_flags & 0x01;                                                                                                                       
   2177         struct request *rq;                                                                                                                                   
   2178                                                                                                                                                               
   2179         rq = get_request(q, rw_flags, bio, GFP_NOIO);                                                                                                         
   2180         while (!rq) {                                                                                                                                         
   2181                 DEFINE_WAIT(wait);                                                                                                                            
   2182                 struct request_list *rl = &q->rq;                                                                                                             
   2183                                                                                                                                                               
   2184                 prepare_to_wait_exclusive(&rl->wait[rw], &wait,                                                                                               
   2185                                 TASK_UNINTERRUPTIBLE);                                                                                                        
   2186                                                                                                                                                               
   2187                 rq = get_request(q, rw_flags, bio, GFP_NOIO);                                                                                                 
   2188                                                                                                                                                               
   2189                 if (!rq) {                                                                                                                                    
   2190                         struct io_context *ioc; Linux  ��Щ�¶�֮���� Block��                                                                                 
�� 50  ҳ �� 117  ҳ                                                                                                                                                  
   2191                                                                                                                                                               
   2192                          blk_add_trace_generic(q, bio, rw, BLK_TA_SLEEPRQ);                                                                                   
   2193                                                                                                                                                               
   2194                         __generic_unplug_device(q);                                                                                                           
   2195                         spin_unlock_irq(q->queue_lock);                                                                                                       
   2196                         io_schedule();                                                                                                                        
   2197                                                                                                                                                               
   2198                         //                                                                                                                                    
   2199                          * After sleeping, we become a "batching" process and                                                                                 
   2200                          * will be able to allocate at least one request, and                                                                                 
   2201                          * up to a big batch of them for a small period time.                                                                                 
   2202                          * See ioc_batching, ioc_set_batching                                                                                                 
   2203                          //                                                                                                                                   
   2204                         ioc = current_io_context(GFP_NOIO, q->node);                                                                                          
   2205                         ioc_set_batching(q, ioc);                                                                                                             
   2206                                                                                                                                                               
   2207                         spin_lock_irq(q->queue_lock);                                                                                                         
   2208                 }                                                                                                                                             
   2209                 finish_wait(&rl->wait[rw], &wait);                                                                                                            
   2210         }                                                                                                                                                     
   2211                                                                                                                                                               
   2212         return rq;                                                                                                                                            
   2213 }                                                                                                                                                             
�����������õ����� get_request(),��Ȼ������ͬһ���ļ�.                                                                                                                
   2063 //                                                                                                                                                            
   2064  * Get a free request, queue_lock must be held.                                                                                                               
   2065  * Returns NULL on failure, with queue_lock held.                                                                                                             
   2066  * Returns !NULL on success, with queue_lock *not held*.                                                                                                      
   2067  //                                                                                                                                                           
   2068 static struct request *get_request(request_queue_t *q, int rw_flags,                                                                                          
   2069                                    struct bio *bio, gfp_t gfp_mask)                                                                                           
   2070 {                                                                                                                                                             
   2071         struct request *rq = NULL;                                                                                                                            
   2072         struct request_list *rl = &q->rq;                                                                                                                     
   2073         struct io_context *ioc = NULL;                                                                                                                        
   2074         const int rw = rw_flags & 0x01;                                                                                                                       
   2075         int may_queue, priv;                                                                                                                                  
   2076                                                                                                                                                               
   2077         may_queue = elv_may_queue(q, rw_flags);                                                                                                               
   2078         if (may_queue == ELV_MQUEUE_NO)                                                                                                                       
   2079                 goto rq_starved;                                                                                                                              
   2080                                                                                                                                                               
   2081         if (rl->count[rw]+1 >= queue_congestion_on_threshold(q)) {                                                                                            
   2082                  if (rl->count[rw]+1 >= q->nr_requests) { Linux  ��Щ�¶�֮���� Block��                                                                       
�� 51  ҳ �� 117  ҳ                                                                                                                                                  
   2083                         ioc = current_io_context(GFP_ATOMIC, q->node);                                                                                        
   2084                         //                                                                                                                                    
   2085                          * The queue will fill after this allocation, so set                                                                                  
   2086                          * it as full, and mark this process as "batching".                                                                                   
   2087                          * This process will be allowed to complete a batch of                                                                                
   2088                          * requests, others will be blocked.                                                                                                  
   2089                          //                                                                                                                                   
   2090                         if (!blk_queue_full(q, rw)) {                                                                                                         
   2091                                 ioc_set_batching(q, ioc);                                                                                                     
   2092                                 blk_set_queue_full(q, rw);                                                                                                    
   2093                         } else {                                                                                                                              
   2094                                 if (may_queue != ELV_MQUEUE_MUST                                                                                              
   2095                                                 && !ioc_batching(q, ioc)) {                                                                                   
   2096                                         //                                                                                                                    
   2097                                          * The queue is full and the allocating                                                                               
   2098                                          * process is not a "batcher", and not                                                                                
   2099                                          * exempted by the IO scheduler                                                                                       
   2100                                          //                                                                                                                   
   2101                                         goto out;                                                                                                             
   2102                                 }                                                                                                                             
   2103                         }                                                                                                                                     
   2104                 }                                                                                                                                             
   2105                 blk_set_queue_congested(q, rw);                                                                                                               
   2106         }                                                                                                                                                     
   2107                                                                                                                                                               
   2108         //                                                                                                                                                    
   2109          * Only allow batching queuers to allocate up to 50% over the defined                                                                                 
   2110          * limit of requests, otherwise we could have thousands of requests                                                                                   
   2111          * allocated with any setting of ->nr_requests                                                                                                        
   2112          //                                                                                                                                                   
   2113         if (rl->count[rw] >= (3 * q->nr_requests / 2))                                                                                                        
   2114                 goto out;                                                                                                                                     
   2115                                                                                                                                                               
   2116         rl->count[rw]++;                                                                                                                                      
   2117         rl->starved[rw] = 0;                                                                                                                                  
   2118                                                                                                                                                               
   2119         priv = !test_bit(QUEUE_FLAG_ELVSWITCH, &q->queue_flags);                                                                                              
   2120         if (priv)                                                                                                                                             
   2121                 rl->elvpriv++;                                                                                                                                
   2122                                                                                                                                                               
   2123         spin_unlock_irq(q->queue_lock);                                                                                                                       
   2124                                                                                                                                                               
   2125         rq = blk_alloc_request(q, rw_flags, priv, gfp_mask);                                                                                                  
   2126         if (unlikely(!rq)) { Linux  ��Щ�¶�֮���� Block��                                                                                                    
�� 52  ҳ �� 117  ҳ                                                                                                                                                  
   2127                 //                                                                                                                                            
   2128                  * Allocation failed presumably due to memory. Undo anything                                                                                  
   2129                  * we might have messed up.                                                                                                                   
   2130                  *                                                                                                                                            
   2131                  * Allocating task should really be put onto the front of the                                                                                 
   2132                  * wait queue, but this is pretty rare.                                                                                                       
   2133                  //                                                                                                                                           
   2134                 spin_lock_irq(q->queue_lock);                                                                                                                 
   2135                 freed_request(q, rw, priv);                                                                                                                   
   2136                                                                                                                                                               
   2137                 //                                                                                                                                            
   2138                  * in the very unlikely event that allocation failed and no                                                                                   
   2139                  * requests for this direction was pending, mark us starved                                                                                   
   2140                  * so that freeing of a request in the other direction will                                                                                   
   2141                  * notice us. another possible fix would be to split the                                                                                      
   2142                  * rq mempool into READ and WRITE                                                                                                             
   2143                  //                                                                                                                                           
   2144 rq_starved:                                                                                                                                                   
   2145                  if (unlikely(rl->count[rw] == 0))                                                                                                            
   2146                         rl->starved[rw] = 1;                                                                                                                  
   2147                                                                                                                                                               
   2148                 goto out;                                                                                                                                     
   2149         }                                                                                                                                                     
   2150                                                                                                                                                               
   2151         //                                                                                                                                                    
   2152          * ioc may be NULL here, and ioc_batching will be false. That's                                                                                       
   2153          * OK, if the queue is under the request limit then requests need                                                                                     
   2154          * not count toward the nr_batch_requests limit. There will always                                                                                    
   2155          * be some limit enforced by BLK_BATCH_TIME.                                                                                                          
   2156          //                                                                                                                                                   
   2157         if (ioc_batching(q, ioc))                                                                                                                             
   2158                 ioc->nr_batch_requests--;                                                                                                                     
   2159                                                                                                                                                               
   2160         rq_init(q, rq);                                                                                                                                       
   2161                                                                                                                                                               
   2162         blk_add_trace_generic(q, bio, rw, BLK_TA_GETRQ);                                                                                                      
   2163 out:                                                                                                                                                          
   2164         return rq;                                                                                                                                            
   2165 }                                                                                                                                                             
��� elv_may_queue ����block/elevator.c:                                                                                                                              
    848 int elv_may_queue(request_queue_t *q, int rw)                                                                                                                 
    849 {                                                                                                                                                             
    850         elevator_t *e = q->elevator;                                                                                                                          
    851 Linux  ��Щ�¶�֮���� Block��                                                                                                                                 
�� 53  ҳ �� 117  ҳ                                                                                                                                                  
    852         if (e->ops->elevator_may_queue_fn)                                                                                                                    
    853                 return e->ops->elevator_may_queue_fn(q, rw);                                                                                                  
    854                                                                                                                                                               
    855         return ELV_MQUEUE_MAY;                                                                                                                                
    856 }                                                                                                                                                             
// �������ǵ��Ǹ�elevator_t�ṹ������ǵ���������elevator_init()�е���elevator_alloc()����                                                                               
// ��.����ops��Ȼ�Ǻ;������ǲ��������ֵ����й�ϵ��.��������Ϊ�˼�����,��һ���                                                                                      
// Ҫ����ѡ��,ѡ��noop��,���������ԭʼ�Ļ���.��һ���������� elevator_type.                                                                                          
     87 static struct elevator_type elevator_noop = {                                                                                                                 
     88         .ops = {                                                                                                                                              
     89              .elevator_merge_req_fn          = noop_merged_requests,                                                                                          
     90                 .elevator_dispatch_fn           = noop_dispatch,                                                                                              
     91                 .elevator_add_req_fn            = noop_add_request,                                                                                           
     92                 .elevator_queue_empty_fn        = noop_queue_empty,                                                                                           
     93                 .elevator_former_req_fn         = noop_former_request,                                                                                        
     94                 .elevator_latter_req_fn         = noop_latter_request,                                                                                        
     95                 .elevator_init_fn               = noop_init_queue,                                                                                            
     96                 .elevator_exit_fn               = noop_exit_queue,                                                                                            
     97         },                                                                                                                                                    
     98         .elevator_name = "noop",                                                                                                                              
     99         .elevator_owner = THIS_MODULE,                                                                                                                        
    100 };                                                                                                                                                            
// �ǲ��Ǿ��úܿ���.  ��������ѡ������� noop �ĵ���,elevator_may_queue_fn ������û�ж�                                                                                  
// �尥.��Ȼ�������������޳�,����˭�����ǲ����������ڵ��й���?ֻҪ���ǹ�����,������,                                                                                     
// ���޳�,�����,��ν�ĵ��µ��߲��ǡ���ס�,���Ŀ�������,��ȫ������ͻ�ƵĻ���.                                                                                           
// ����һ������ֵ ELV_MQUEUE_MAY,���Ƿ��ص� get_request()����.rl ����ʲô��?2072 ��                                                                                      
// ��������ָ���� q->rq.������һ��Σ����ͷ,�Ҳ��ò����һ�����ӵĽṹ����,������                                                                                         
// request_queue,���߽� request_queue_t,������ include/linux/blkdev.h:                                                                                                   
     38 struct request_queue;                                                                                                                                         
     39 typedef struct request_queue request_queue_t;                                                                                                                 
    360 struct request_queue                                                                                                                                          
    361 {                                                                                                                                                             
    362         //                                                                                                                                                    
    363          * Together with queue_head for cacheline sharing                                                                                                     
    364          //                                                                                                                                                   
    365         struct list_head        queue_head;                                                                                                                   
    366         struct request          *last_merge;                                                                                                                  
    367         elevator_t              *elevator;                                                                                                                    
    368                                                                                                                                                               
    369         //                                                                                                                                                    
    370          * the queue request freelist, one for reads and one for writes                                                                                       
    371          //                                                                                                                                                   
    372         struct request_list     rq;                                                                                                                           
    373 Linux  ��Щ�¶�֮���� Block��                                                                                                                                 
�� 54  ҳ �� 117  ҳ                                                                                                                                                  
    374         request_fn_proc         *request_fn;                                                                                                                  
    375         make_request_fn         *make_request_fn;                                                                                                             
    376         prep_rq_fn              *prep_rq_fn;                                                                                                                  
    377         unplug_fn               *unplug_fn;                                                                                                                   
    378         merge_bvec_fn           *merge_bvec_fn;                                                                                                               
    379         issue_flush_fn          *issue_flush_fn;                                                                                                              
    380         prepare_flush_fn        *prepare_flush_fn;                                                                                                            
    381         softirq_done_fn         *softirq_done_fn;                                                                                                             
    382                                                                                                                                                               
    383         //                                                                                                                                                    
    384          * Dispatch queue sorting                                                                                                                             
    385          //                                                                                                                                                   
    386         sector_t                end_sector;                                                                                                                   
    387         struct request          *boundary_rq;                                                                                                                 
    388                                                                                                                                                               
    389         //                                                                                                                                                    
    390          * Auto-unplugging state                                                                                                                              
    391          //                                                                                                                                                   
    392         struct timer_list       unplug_timer;                                                                                                                 
    393         int                     unplug_thresh;  // After this many requests //                                                                                
394         unsigned long           unplug_delay;   // After this many jiffies //                                                                                     
    395         struct work_struct      unplug_work;                                                                                                                  
    396                                                                                                                                                               
    397         struct backing_dev_info backing_dev_info;                                                                                                             
    398                                                                                                                                                               
    399         //                                                                                                                                                    
    400          * The queue owner gets to use this for whatever they like.                                                                                           
    401          * ll_rw_blk doesn't touch it.                                                                                                                        
    402          //                                                                                                                                                   
    403         void                    *queuedata;                                                                                                                   
    404                                                                                                                                                               
    405         //                                                                                                                                                    
    406          * queue needs bounce pages for pages above this limit                                                                                                
    407          //                                                                                                                                                   
    408         unsigned long           bounce_pfn;                                                                                                                   
    409         gfp_t                   bounce_gfp;                                                                                                                   
    410                                                                                                                                                               
    411         //                                                                                                                                                    
    412          * various queue flags, see QUEUE_* below                                                                                                             
    413          //                                                                                                                                                   
    414         unsigned long           queue_flags;                                                                                                                  
    415                                                                                                                                                               
    416         //                                                                                                                                                    
    417          * protects queue structures from reentrancy. ->__queue_lock should Linux  ��Щ�¶�֮���� Block��                                                     
�� 55  ҳ �� 117  ҳ                                                                                                                                                  
    418          * _never_ be used directly, it is queue private. always use                                                                                          
    419          * ->queue_lock.                                                                                                                                      
    420          //                                                                                                                                                   
    421         spinlock_t              __queue_lock;                                                                                                                 
    422         spinlock_t              *queue_lock;                                                                                                                  
    423                                                                                                                                                               
    424         //                                                                                                                                                    
    425          * queue kobject                                                                                                                                      
    426          //                                                                                                                                                   
    427         struct kobject kobj;                                                                                                                                  
    428                                                                                                                                                               
    429         //                                                                                                                                                    
    430          * queue settings                                                                                                                                     
    431          //                                                                                                                                                   
    432         unsigned long           nr_requests;    // Max # of requests //                                                                                       
    433         unsigned int            nr_congestion_on;                                                                                                             
    434         unsigned int            nr_congestion_off;                                                                                                            
435         unsigned int            nr_batching;                                                                                                                      
    436                                                                                                                                                               
    437         unsigned int            max_sectors;                                                                                                                  
    438         unsigned int            max_hw_sectors;                                                                                                               
    439         unsigned short          max_phys_segments;                                                                                                            
    440         unsigned short          max_hw_segments;                                                                                                              
    441         unsigned short          hardsect_size;                                                                                                                
    442         unsigned int            max_segment_size;                                                                                                             
    443                                                                                                                                                               
    444         unsigned long           seg_boundary_mask;                                                                                                            
    445         unsigned int            dma_alignment;                                                                                                                
    446                                                                                                                                                               
    447         struct blk_queue_tag    *queue_tags;                                                                                                                  
    448                                                                                                                                                               
    449         unsigned int            nr_sorted;                                                                                                                    
    450         unsigned int            in_flight;                                                                                                                    
    451                                                                                                                                                               
    452         //                                                                                                                                                    
    453          * sg stuff                                                                                                                                           
    454          //                                                                                                                                                   
    455         unsigned int            sg_timeout;                                                                                                                   
    456         unsigned int            sg_reserved_size;                                                                                                             
    457         int                     node;                                                                                                                         
    458 #ifdef CONFIG_BLK_DEV_IO_TRACE                                                                                                                                
    459         struct blk_trace        *blk_trace;                                                                                                                   
    460 #endif                                                                                                                                                        
    461         // Linux  ��Щ�¶�֮���� Block��                                                                                                                      
�� 56  ҳ �� 117  ҳ                                                                                                                                                  
    462          * reserved for flush operations                                                                                                                      
    463          //                                                                                                                                                   
    464         unsigned int            ordered, next_ordered, ordseq;                                                                                                
    465         int                     orderr, ordcolor;                                                                                                             
    466         struct request          pre_flush_rq, bar_rq, post_flush_rq;                                                                                          
    467         struct request          *orig_bar_rq;                                                                                                                 
    468         unsigned int            bi_size;                                                                                                                      
    469                                                                                                                                                               
    470         struct mutex            sysfs_lock;                                                                                                                   
    471 };                                                                                                                                                            
�������ǿ����� rq ��ʵ�� struct request_list �ṹ�����.����ṹ�嶨����ͬһ���ļ�.                                                                                   
    131 struct request_list {                                                                                                                                         
    132         int count[2];                                                                                                                                         
    133         int starved[2];                                                                                                                                       
    134         int elvpriv;                                                                                                                                          
    135         mempool_t *rq_pool;                                                                                                                                   
    136         wait_queue_head_t wait[2];                                                                                                                            
    137 };                                                                                                                                                            
// ������Щ�������ڶ����뿴,�����뿴��ֻ�����еļ�������,��һ���� 2125 ��                                                                                                
// blk_alloc_request().���� ll_rw_blk.c:                                                                                                                                 
   1970 static struct request *                                                                                                                                       
   1971 blk_alloc_request(request_queue_t *q, int rw, int priv, gfp_t gfp_mask)                                                                                       
   1972 {                                                                                                                                                             
   1973         struct request *rq = mempool_alloc(q->rq.rq_pool, gfp_mask);                                                                                          
   1974                                                                                                                                                               
   1975         if (!rq)                                                                                                                                              
   1976                 return NULL;                                                                                                                                  
   1977                                                                                                                                                               
   1978         //                                                                                                                                                    
   1979          * first three bits are identical in rq->cmd_flags and bio->bi_rw,                                                                                    
   1980          * see bio.h and blkdev.h                                                                                                                             
   1981          //                                                                                                                                                   
   1982         rq->cmd_flags = rw | REQ_ALLOCED;                                                                                                                     
   1983                                                                                                                                                               
   1984         if (priv) {                                                                                                                                           
   1985                 if (unlikely(elv_set_request(q, rq, gfp_mask))) {                                                                                             
   1986                         mempool_free(rq, q->rq.rq_pool);                                                                                                      
   1987                         return NULL;                                                                                                                          
   1988                 }                                                                                                                                             
   1989                 rq->cmd_flags |= REQ_ELVPRIV;                                                                                                                 
   1990         }                                                                                                                                                     
   1991                                                                                                                                                               
   1992         return rq;                                                                                                                                            
   1993 } Linux  ��Щ�¶�֮���� Block��                                                                                                                               
// �� 57  ҳ �� 117  ҳ                                                                                                                                                  
// �������ǲ���û�й�ϵ,�������Ǵ�1972�п��Կ�������������һ��struct request�Ľṹ��                                                                                     
// ָ��,���仰˵,��ǰ,�����Ѿ������������,����û��ʵ���Ե�Ԫ��,����һ����,��������һ                                                                                    
// �������� request.��Ȼ���ڻ�û�н��뵽������ȥ,����ֻ��������¶���.                                                                                                   
// ��һ�� rq_init().                                                                                                                                                     
    238 static void rq_init(request_queue_t *q, struct request *rq)                                                                                                   
    239 {                                                                                                                                                             
    240         INIT_LIST_HEAD(&rq->queuelist);                                                                                                                       
    241         INIT_LIST_HEAD(&rq->donelist);                                                                                                                        
    242                                                                                                                                                               
    243         rq->errors = 0;                                                                                                                                       
    244         rq->bio = rq->biotail = NULL;                                                                                                                         
    245         INIT_HLIST_NODE(&rq->hash);                                                                                                                           
    246         RB_CLEAR_NODE(&rq->rb_node);                                                                                                                          
    247         rq->ioprio = 0;                                                                                                                                       
    248         rq->buffer = NULL;                                                                                                                                    
    249         rq->ref_count = 1;                                                                                                                                    
    250         rq->q = q;                                                                                                                                            
    251         rq->special = NULL;                                                                                                                                   
    252         rq->data_len = 0;                                                                                                                                     
    253         rq->data = NULL;                                                                                                                                      
    254         rq->nr_phys_segments = 0;                                                                                                                             
    255         rq->sense = NULL;                                                                                                                                     
    256         rq->end_io = NULL;                                                                                                                                    
    257         rq->end_io_data = NULL;                                                                                                                               
    258         rq->completion_data = NULL;                                                                                                                           
    259 }                                                                                                                                                             
// ��������ڸ�ʲô������˵,�ֶ������´��������̵Ĵ��趼֪��,�Ը������ rq ���г�ʼ                                                                                      
// ��.                                                                                                                                                                   
// Ȼ��,get_request()�Ϳ������ĵķ�����,���������,get_request_wait()Ҳ����ŷ���,�ٽ�                                                                                   
// ��,blk_get_request()Ҳ�ͷ�����.����Ҳ��������ó�ʼ���õ� req �ص� scsi_execute()��ȥ,��                                                                              
// ������һ�δ��������������ĵ�,�� req �������ĸ�ֵ.���� req->cmd_len,req->cmd �ȵ�,                                                                                   
// �������������ϵ�.����֮,���ǵ� scsi ������������� request ����ˮ��,�Ӵ�����֮�䲻��                                                                                  
// ����ǰ���֡�ˮ����ס�仨��Ư��,�仨�߲���ˮ�����硱�Ĺ�ϵ,�������䵽��һ�پ���һ��                                                                                    
// �����Ǳ�Ϊ��Ĺ�ϵ.                                                                                                                                                   
// ����,����˵�һ�α���,�� scsi ��� request �ı���.                                                                                                                  
//                                                                                                                                                                       
// scsi �����ǰ������(��)                                                                                                                                               
// һ�������Ǳ�Ϊ��Ĺ�ϵ��������,�Ϳ��Կ�ʼִ��������.���� blk_execute_rq(),����                                                                                        
// block/ll_rw_blk.c:                                                                                                                                                    
//    2605 ///                                                                                                                                                           
//    2606  * blk_execute_rq - insert a request into queue for execution Linux  ��Щ�¶�֮���� Block��                                                                   
// �� 58  ҳ �� 117  ҳ                                                                                                                                                  
//    2607  * @q:          queue to insert the request in                                                                                                                
//    2608  * @bd_disk:    matching gendisk                                                                                                                              
//    2609  * @rq:         request to insert                                                                                                                             
//    2610  * @at_head:    insert request at head or tail of queue                                                                                                       
//    2611  *                                                                                                                                                            
//    2612  * Description:                                                                                                                                               
//    2613  *    Insert a fully prepared request at the back of the io scheduler queue                                                                                   
//    2614  *    for execution and wait for completion.                                                                                                                  
//    2615  //                                                                                                                                                           
   2616 int blk_execute_rq(request_queue_t *q, struct gendisk *bd_disk,                                                                                               
   2617                    struct request *rq, int at_head)                                                                                                           
   2618 {                                                                                                                                                             
   2619         DECLARE_COMPLETION_ONSTACK(wait);                                                                                                                     
   2620         char sense[SCSI_SENSE_BUFFERSIZE];                                                                                                                    
   2621         int err = 0;                                                                                                                                          
   2622                                                                                                                                                               
   2623         //                                                                                                                                                    
   2624          * we need an extra reference to the request, so we can look at                                                                                       
   2625          * it after io completion                                                                                                                             
   2626          //                                                                                                                                                   
   2627          rq->ref_count++;                                                                                                                                     
   2628                                                                                                                                                               
   2629         if (!rq->sense) {                                                                                                                                     
   2630                 memset(sense, 0, sizeof(sense));                                                                                                              
   2631                 rq->sense = sense;                                                                                                                            
   2632                 rq->sense_len = 0;                                                                                                                            
   2633         }                                                                                                                                                     
   2634                                                                                                                                                               
   2635         rq->end_io_data = &wait;                                                                                                                              
   2636         blk_execute_rq_nowait(q, bd_disk, rq, at_head, blk_end_sync_rq);                                                                                      
   2637         wait_for_completion(&wait);                                                                                                                           
   2638                                                                                                                                                               
   2639         if (rq->errors)                                                                                                                                       
   2640                 err = -EIO;                                                                                                                                   
   2641                                                                                                                                                               
   2642         return err;                                                                                                                                           
   2643 }                                                                                                                                                             
// ��ȥ��Щ���ڴ�����Ĵ���,�����������������Ĵ����������, blk_execute_rq_nowait                                                                                    
// �� wait_for_completion.�ȿ�ǰ��,����block/ll_rw_blk.c:                                                                                                                
//    2576 ///                                                                                                                                                           
//    2577  * blk_execute_rq_nowait - insert a request into queue for execution                                                                                          
//    2578  * @q:          queue to insert the request in                                                                                                                
//    2579  * @bd_disk:    matching gendisk                                                                                                                              
//    2580  * @rq:         request to insert Linux  ��Щ�¶�֮���� Block��                                                                                               
// �� 59  ҳ �� 117  ҳ                                                                                                                                                  
//    2581  * @at_head:    insert request at head or tail of queue                                                                                                       
//    2582  * @done:       I/O completion handler                                                                                                                        
//    2583  *                                                                                                                                                            
//    2584  * Description:                                                                                                                                               
//    2585  *    Insert a fully prepared request at the back of the io scheduler queue                                                                                   
//    2586  *    for execution.  Don't wait for completion.                                                                                                              
   2587  //                                                                                                                                                           
   2588 void blk_execute_rq_nowait(request_queue_t *q, struct gendisk *bd_disk,                                                                                       
   2589                            struct request *rq, int at_head,                                                                                                   
   2590                            rq_end_io_fn *done)                                                                                                                
   2591 {                                                                                                                                                             
   2592         int where = at_head ? ELEVATOR_INSERT_FRONT :                                                                                                         
ELEVATOR_INSERT_BACK;                                                                                                                                                 
   2593                                                                                                                                                               
   2594         rq->rq_disk = bd_disk;                                                                                                                                
   2595         rq->cmd_flags |= REQ_NOMERGE;                                                                                                                         
   2596         rq->end_io = done;                                                                                                                                    
   2597         WARN_ON(irqs_disabled());                                                                                                                             
   2598         spin_lock_irq(q->queue_lock);                                                                                                                         
   2599         __elv_add_request(q, rq, where, 1);                                                                                                                   
   2600         __generic_unplug_device(q);                                                                                                                           
   2601         spin_unlock_irq(q->queue_lock);                                                                                                                       
   2602 }                                                                                                                                                             
// ���� at_head�Ǳ�ʾ���Ĳ�.(����,�ò��ỹ��һ��������ʾ��ʲô���Ʋ��.)                                                                                                 
// �� where ������¼ at_head ��ֵ.�����������������,at_head �Ǵ� scsi_execute()�е���                                                                                   
// blk_execute_rq ��ʱ�򴫵�������,��ʱ�������õ��� 1.���� where ������Ϊ                                                                                                
// ELEVATOR_INSERT_FRONT.�⼸�������� include/linux/elevator.h:                                                                                                          
//     155 //                                                                                                                                                            
//     156  * Insertion selection                                                                                                                                        
    157  //                                                                                                                                                           
    158 #define ELEVATOR_INSERT_FRONT   1                                                                                                                             
    159 #define ELEVATOR_INSERT_BACK    2                                                                                                                             
    160 #define ELEVATOR_INSERT_SORT    3                                                                                                                             
    161 #define ELEVATOR_INSERT_REQUEUE 4                                                                                                                             
// ������,���Ǹ������Ǵ�ǰ���,���㲻��̫��̬.��ô������� where ���ǽ�����һ������,                                                                                     
// ��__elv_add_request.����block/elevator.c:                                                                                                                             
    646 void __elv_add_request(request_queue_t *q, struct request *rq, int where,                                                                                     
    647                        int plug)                                                                                                                              
    648 {                                                                                                                                                             
    649         if (q->ordcolor)                                                                                                                                      
    650                 rq->cmd_flags |= REQ_ORDERED_COLOR;                                                                                                           
    651                                                                                                                                                               
    652         if (rq->cmd_flags & (REQ_SOFTBARRIER | REQ_HARDBARRIER)) {                                                                                            
    653                 // Linux  ��Щ�¶�֮���� Block��                                                                                                              
�� 60  ҳ �� 117  ҳ                                                                                                                                                  
    654                  * toggle ordered color                                                                                                                       
    655                  //                                                                                                                                           
    656                 if (blk_barrier_rq(rq))                                                                                                                       
    657                         q->ordcolor ^= 1;                                                                                                                     
    658                                                                                                                                                               
    659                 //                                                                                                                                            
    660                  * barriers implicitly indicate back insertion                                                                                                
    661                  //                                                                                                                                           
    662                 if (where == ELEVATOR_INSERT_SORT)                                                                                                            
    663                         where = ELEVATOR_INSERT_BACK;                                                                                                         
    664                                                                                                                                                               
    665                 //                                                                                                                                            
    666                  * this request is scheduling boundary, update                                                                                                
    667                  * end_sector                                                                                                                                 
    668                  //                                                                                                                                           
    669                 if (blk_fs_request(rq)) {                                                                                                                     
    670                          q->end_sector = rq_end_sector(rq);                                                                                                   
    671                         q->boundary_rq = rq;                                                                                                                  
    672                 }                                                                                                                                             
    673         } else if (!(rq->cmd_flags & REQ_ELVPRIV) && where ==                                                                                                 
ELEVATOR_INSERT_SORT)                                                                                                                                                 
    674                 where = ELEVATOR_INSERT_BACK;                                                                                                                 
    675                                                                                                                                                               
    676         if (plug)                                                                                                                                             
    677                 blk_plug_device(q);                                                                                                                           
    678                                                                                                                                                               
    679         elv_insert(q, rq, where);                                                                                                                             
    680 }                                                                                                                                                             
// ����Ĳ��� plug ���� 1,���� blk_plug_device()�ᱻִ��.�����Ȳ����������.                                                                                             
// ������,ǰ�涼�������޹�,ֱ���������һ����� elv_insert().                                                                                                            
    548 void elv_insert(request_queue_t *q, struct request *rq, int where)                                                                                            
    549 {                                                                                                                                                             
    550         struct list_head *pos;                                                                                                                                
    551         unsigned ordseq;                                                                                                                                      
    552         int unplug_it = 1;                                                                                                                                    
    553                                                                                                                                                               
    554         blk_add_trace_rq(q, rq, BLK_TA_INSERT);                                                                                                               
    555                                                                                                                                                               
    556         rq->q = q;                                                                                                                                            
    557                                                                                                                                                               
    558         switch (where) {                                                                                                                                      
    559         case ELEVATOR_INSERT_FRONT:                                                                                                                           
    560                 rq->cmd_flags |= REQ_SOFTBARRIER;                                                                                                             
    561 Linux  ��Щ�¶�֮���� Block��                                                                                                                                 
�� 61  ҳ �� 117  ҳ                                                                                                                                                  
    562                 list_add(&rq->queuelist, &q->queue_head);                                                                                                     
    563                 break;                                                                                                                                        
    564                                                                                                                                                               
    565         case ELEVATOR_INSERT_BACK:                                                                                                                            
    566                 rq->cmd_flags |= REQ_SOFTBARRIER;                                                                                                             
    567                 elv_drain_elevator(q);                                                                                                                        
    568                 list_add_tail(&rq->queuelist, &q->queue_head);                                                                                                
    569                 //                                                                                                                                            
    570                  * We kick the queue here for the following reasons.                                                                                          
    571                  * - The elevator might have returned NULL previously                                                                                         
    572                  *   to delay requests and returned them now.  As the                                                                                         
    573                  *   queue wasn't empty before this request, ll_rw_blk                                                                                        
    574                  *   won't run the queue on return, resulting in hang.                                                                                        
    575                  * - Usually, back inserted requests won't be merged                                                                                          
    576                  *   with anything.  There's no point in delaying queue                                                                                       
    577                  *   processing.                                                                                                                              
    578                  //                                                                                                                                           
    579                 blk_remove_plug(q);                                                                                                                           
    580                 q->request_fn(q);                                                                                                                             
    581                 break;                                                                                                                                        
    582                                                                                                                                                               
    583         case ELEVATOR_INSERT_SORT:                                                                                                                            
    584                 BUG_ON(!blk_fs_request(rq));                                                                                                                  
    585                 rq->cmd_flags |= REQ_SORTED;                                                                                                                  
    586                 q->nr_sorted++;                                                                                                                               
587                 if (rq_mergeable(rq)) {                                                                                                                           
    588                         elv_rqhash_add(q, rq);                                                                                                                
    589                         if (!q->last_merge)                                                                                                                   
    590                                 q->last_merge = rq;                                                                                                           
    591                 }                                                                                                                                             
    592                                                                                                                                                               
    593                 //                                                                                                                                            
    594                  * Some ioscheds (cfq) run q->request_fn directly, so                                                                                         
    595                  * rq cannot be accessed after calling                                                                                                        
    596                  * elevator_add_req_fn.                                                                                                                       
    597                  //                                                                                                                                           
    598                 q->elevator->ops->elevator_add_req_fn(q, rq);                                                                                                 
    599                 break;                                                                                                                                        
    600                                                                                                                                                               
    601         case ELEVATOR_INSERT_REQUEUE:                                                                                                                         
    602                 //                                                                                                                                            
    603                  * If ordered flush isn't in progress, we do front                                                                                            
    604                  * insertion; otherwise, requests should be requeued                                                                                          
    605                  * in ordseq order. Linux  ��Щ�¶�֮���� Block��                                                                                             
�� 62  ҳ �� 117  ҳ                                                                                                                                                  
    606                  //                                                                                                                                           
    607                 rq->cmd_flags |= REQ_SOFTBARRIER;                                                                                                             
    608                                                                                                                                                               
    609                 //                                                                                                                                            
    610                  * Most requeues happen because of a busy condition,                                                                                          
    611                  * don't force unplug of the queue for that case.                                                                                             
    612                  //                                                                                                                                           
    613                 unplug_it = 0;                                                                                                                                
    614                                                                                                                                                               
    615                 if (q->ordseq == 0) {                                                                                                                         
    616                         list_add(&rq->queuelist, &q->queue_head);                                                                                             
    617                         break;                                                                                                                                
    618                 }                                                                                                                                             
    619                                                                                                                                                               
    620                 ordseq = blk_ordered_req_seq(rq);                                                                                                             
    621                                                                                                                                                               
    622                 list_for_each(pos, &q->queue_head) {                                                                                                          
    623                         struct request *pos_rq = list_entry_rq(pos);                                                                                          
    624                         if (ordseq <= blk_ordered_req_seq(pos_rq))                                                                                            
    625                                 break;                                                                                                                        
    626                 }                                                                                                                                             
    627                                                                                                                                                               
    628                 list_add_tail(&rq->queuelist, pos);                                                                                                           
    629                 break;                                                                                                                                        
    630                                                                                                                                                               
    631         default:                                                                                                                                              
    632                 printk(KERN_ERR "%s: bad insertion point %d\n",                                                                                               
    633                        __FUNCTION__, where);                                                                                                                  
    634                 BUG();                                                                                                                                        
    635         }                                                                                                                                                     
    636                                                                                                                                                               
    637         if (unplug_it && blk_queue_plugged(q)) {                                                                                                              
    638                 int nrq = q->rq.count[READ] + q->rq.count[WRITE]                                                                                              
    639                         - q->in_flight;                                                                                                                       
    640                                                                                                                                                               
    641                 if (nrq >= q->unplug_thresh)                                                                                                                  
    642                         __generic_unplug_device(q);                                                                                                           
    643         }                                                                                                                                                     
    644 }                                                                                                                                                             
// ���������Ǵ�ǰ���,��������ִ�� 562 ����� list_add,struct request ��һ����Ա struct                                                                                  
// list_head queuelist,�� struct request_queue ��һ����Ա struct list_head queue_head,�������Ǿ�                                                                         
// ��ǰ�߲��뵽����������������������.Ȼ�����Ǿͷ�����.                                                                                                                
// �ص� blk_execute_rq_nowait()��,��һ�������õĺ�����__generic_unplug_device,��Ȼ������                                                                                 
// block/ll_rw_blk.c: Linux  ��Щ�¶�֮���� Block��                                                                                                                      
// �� 63  ҳ �� 117  ҳ                                                                                                                                                  
//    1586 //                                                                                                                                                            
//    1587  * remove the plug and let it rip..                                                                                                                           
//    1588  //                                                                                                                                                           
   1589 void __generic_unplug_device(request_queue_t *q)                                                                                                              
   1590 {                                                                                                                                                             
   1591         if (unlikely(blk_queue_stopped(q)))                                                                                                                   
   1592                 return;                                                                                                                                       
   1593                                                                                                                                                               
   1594         if (!blk_remove_plug(q))                                                                                                                              
   1595                 return;                                                                                                                                       
   1596                                                                                                                                                               
   1597         q->request_fn(q);                                                                                                                                     
   1598 }                                                                                                                                                             
// ��ʵ���п���ľ��� 1597 �е������ request_fn,struct request_queue �е�һ����Ա                                                                                       
// request_fn_proc *request_fn,������ request_fn_proc,��ʵ���� typedef ��С����,����                                                                                     
// include/linux/blkdev.h:                                                                                                                                               
//     334 typedef void (request_fn_proc) (request_queue_t *q);                                                                                                          
// ��ô���request_fn�Ƕ�����?���ǵõ����Ǹ�scsi��ϵͳ��������еĺ�����ô?û��,����                                                                                     
// __scsi_alloc_queue(),���������� scsi_alloc_queue(),���ڵ��õ�ʱ��ʹ������������:                                                                                    
   1590 struct request_queue *scsi_alloc_queue(struct scsi_device *sdev)                                                                                              
   1591 {                                                                                                                                                             
   1592         struct request_queue *q;                                                                                                                              
   1593                                                                                                                                                               
   1594         q = __scsi_alloc_queue(sdev->host, scsi_request_fn);                                                                                                  
   1595         if (!q)                                                                                                                                               
   1596                 return NULL;                                                                                                                                  
   1597                                                                                                                                                               
   1598         blk_queue_prep_rq(q, scsi_prep_fn);                                                                                                                   
   1599         blk_queue_issue_flush_fn(q, scsi_issue_flush_fn);                                                                                                     
   1600         blk_queue_softirq_done(q, scsi_softirq_done);                                                                                                         
   1601         return q;                                                                                                                                             
   1602 }                                                                                                                                                             
// ��,�������scsi_request_fn(),��ôһ������ָ��ͨ�����δ��ݲ�������blk_init_queue_node()                                                                                
// �б������� q->request_fn.��������������Ҫ���ĵ��� scsi_request_fn.                                                                                                    
// �ڿ� scsi_request_fn ֮ǰ,ע������ 1598 ����1560��Ҳ�Ǹ�����������ָ��,                                                                                               
    132 ///                                                                                                                                                           
    133  * blk_queue_prep_rq - set a prepare_request function for queue                                                                                               
    134  * @q:          queue                                                                                                                                         
    135  * @pfn:        prepare_request function                                                                                                                      
    136  *                                                                                                                                                            
    137  * It's possible for a queue to register a prepare_request callback which                                                                                     
    138  * is invoked before the request is handed to the request_fn. The goal of                                                                                     
    139  * the function is to prepare a request for I/O, it can be used to build a                                                                                    
    140  * cdb from the request data for instance. Linux  ��Щ�¶�֮���� Block��                                                                                      
�� 64  ҳ �� 117  ҳ                                                                                                                                                  
    141  *                                                                                                                                                            
    142  //                                                                                                                                                           
    143 void blk_queue_prep_rq(request_queue_t *q, prep_rq_fn *pfn)                                                                                                   
    144 {                                                                                                                                                             
    145         q->prep_rq_fn = pfn;                                                                                                                                  
146 }                                                                                                                                                                 
    303 ///                                                                                                                                                           
    304  * blk_queue_issue_flush_fn - set function for issuing a flush                                                                                                
    305  * @q:     the request queue                                                                                                                                  
    306  * @iff:   the function to be called issuing the flush                                                                                                        
    307  *                                                                                                                                                            
    308  * Description:                                                                                                                                               
    309  *   If a driver supports issuing a flush command, the support is notified                                                                                    
    310  *   to the block layer by defining it through this call.                                                                                                     
    311  *                                                                                                                                                            
    312  ///                                                                                                                                                          
    313 void blk_queue_issue_flush_fn(request_queue_t *q, issue_flush_fn *iff)                                                                                        
    314 {                                                                                                                                                             
    315         q->issue_flush_fn = iff;                                                                                                                              
316 }                                                                                                                                                                 
    173 void blk_queue_softirq_done(request_queue_t *q, softirq_done_fn *fn)                                                                                          
    174 {                                                                                                                                                             
    175         q->softirq_done_fn = fn;                                                                                                                              
    176 }                                                                                                                                                             
// �ֱ��ǰ� scsi_prep_fn ������ q->prep_rq_fn,�� scsi_issue_flush_fn ������ q->issue_flush_fn,                                                                           
// �� scsi_softirq_done������ q->softirq_done_fn.������ scsi_prep_fn �������Ͼͻ��õ�.                                                                                   
// ��,�����Ǽ���ǰ��Ļ���,���� scsi_request_fn().                                                                                                                       
   1411 //                                                                                                                                                            
   1412  * Function:    scsi_request_fn()                                                                                                                             
   1413  *                                                                                                                                                            
   1414  * Purpose:     Main strategy routine for SCSI.                                                                                                               
   1415  *                                                                                                                                                            
   1416  * Arguments:   q       - Pointer to actual queue.                                                                                                            
   1417  *                                                                                                                                                            
   1418  * Returns:     Nothing                                                                                                                                       
   1419  *                                                                                                                                                            
   1420  * Lock status: IO request lock assumed to be held when called.                                                                                               
   1421  //                                                                                                                                                           
   1422 static void scsi_request_fn(struct request_queue *q)                                                                                                          
   1423 {                                                                                                                                                             
   1424         struct scsi_device *sdev = q->queuedata;                                                                                                              
   1425         struct Scsi_Host *shost;                                                                                                                              
   1426         struct scsi_cmnd *cmd;                                                                                                                                
   1427         struct request *req; Linux  ��Щ�¶�֮���� Block��                                                                                                    
�� 65  ҳ �� 117  ҳ                                                                                                                                                  
   1428                                                                                                                                                               
   1429         if (!sdev) {                                                                                                                                          
   1430                 printk("scsi: killing requests for dead queue\n");                                                                                            
   1431                  while ((req = elv_next_request(q)) != NULL)                                                                                                  
   1432                         scsi_kill_request(req, q);                                                                                                            
   1433                 return;                                                                                                                                       
   1434         }                                                                                                                                                     
   1435                                                                                                                                                               
   1436         if(!get_device(&sdev->sdev_gendev))                                                                                                                   
   1437                 // We must be tearing the block queue down already //                                                                                         
   1438                 return;                                                                                                                                       
   1439                                                                                                                                                               
   1440         //                                                                                                                                                    
   1441          * To start with, we keep looping until the queue is empty, or until                                                                                  
   1442          * the host is no longer able to accept any more requests.                                                                                            
   1443          //                                                                                                                                                   
   1444         shost = sdev->host;                                                                                                                                   
   1445         while (!blk_queue_plugged(q)) {                                                                                                                       
   1446                 int rtn;                                                                                                                                      
   1447                 //                                                                                                                                            
   1448                  * get next queueable request.  We do this early to make sure                                                                                 
   1449                  * that the request is fully prepared even if we cannot                                                                                       
   1450                  * accept it.                                                                                                                                 
   1451                  //                                                                                                                                           
   1452                 req = elv_next_request(q);                                                                                                                    
   1453                  if (!req || !scsi_dev_queue_ready(q, sdev))                                                                                                  
   1454                         break;                                                                                                                                
   1455                                                                                                                                                               
   1456                  if (unlikely(!scsi_device_online(sdev))) {                                                                                                   
   1457                         sdev_printk(KERN_ERR, sdev,                                                                                                           
   1458                                     "rejecting I/O to offline device\n");                                                                                     
   1459                         scsi_kill_request(req, q);                                                                                                            
   1460                         continue;                                                                                                                             
   1461                 }                                                                                                                                             
   1462                                                                                                                                                               
   1463                                                                                                                                                               
   1464                 //                                                                                                                                            
   1465                  * Remove the request from the request list.                                                                                                  
   1466                  //                                                                                                                                           
   1467                 if (!(blk_queue_tagged(q) && !blk_queue_start_tag(q, req)))                                                                                   
   1468                         blkdev_dequeue_request(req);                                                                                                          
   1469                 sdev->device_busy++;                                                                                                                          
   1470                                                                                                                                                               
   1471                 spin_unlock(q->queue_lock); Linux  ��Щ�¶�֮���� Block��                                                                                     
�� 66  ҳ �� 117  ҳ                                                                                                                                                  
   1472                 cmd = req->special;                                                                                                                           
   1473                 if (unlikely(cmd == NULL)) {                                                                                                                  
   1474                         printk(KERN_CRIT "impossible request in %s.\n"                                                                                        
   1475                                          "please mail a stack trace to "                                                                                      
   1476                                          "linux-scsi@vger.kernel.org\n",                                                                                      
   1477                                          __FUNCTION__);                                                                                                       
   1478                         blk_dump_rq_flags(req, "foo");                                                                                                        
   1479                         BUG();                                                                                                                                
   1480                 }                                                                                                                                             
   1481                 spin_lock(shost->host_lock);                                                                                                                  
   1482                                                                                                                                                               
   1483                 if (!scsi_host_queue_ready(q, shost, sdev))                                                                                                   
   1484                         goto not_ready;                                                                                                                       
   1485                 if (sdev->single_lun) {                                                                                                                       
   1486                         if (scsi_target(sdev)->starget_sdev_user &&                                                                                           
   1487                             scsi_target(sdev)->starget_sdev_user != sdev)                                                                                     
   1488                                 goto not_ready;                                                                                                               
   1489                         scsi_target(sdev)->starget_sdev_user = sdev;                                                                                          
   1490                 }                                                                                                                                             
   1491                 shost->host_busy++;                                                                                                                           
   1492                                                                                                                                                               
   1493                 //                                                                                                                                            
   1494                  * XXX(hch): This is rather suboptimal, scsi_dispatch_cmd will                                                                                
   1495                  *              take the lock again.                                                                                                          
   1496                  //                                                                                                                                           
   1497                 spin_unlock_irq(shost->host_lock);                                                                                                            
   1498                                                                                                                                                               
   1499                 //                                                                                                                                            
   1500                  * Finally, initialize any error handling parameters, and set up                                                                              
   1501                  * the timers for timeouts.                                                                                                                   
   1502                  //                                                                                                                                           
   1503                 scsi_init_cmd_errh(cmd);                                                                                                                      
   1504                                                                                                                                                               
   1505                 //                                                                                                                                            
   1506                  * Dispatch the command to the low-level driver.                                                                                              
   1507                  //                                                                                                                                           
   1508                 rtn = scsi_dispatch_cmd(cmd);                                                                                                                 
   1509                 spin_lock_irq(q->queue_lock);                                                                                                                 
   1510                 if(rtn) {                                                                                                                                     
   1511                         // we're refusing the command; because of                                                                                             
   1512                          * the way locks get dropped, we need to                                                                                              
   1513                          * check here if plugging is required //                                                                                              
   1514                         if(sdev->device_busy == 0)                                                                                                            
   1515                                 blk_plug_device(q); Linux  ��Щ�¶�֮���� Block��                                                                             
�� 67  ҳ �� 117  ҳ                                                                                                                                                  
   1516                                                                                                                                                               
   1517                         break;                                                                                                                                
   1518                 }                                                                                                                                             
   1519         }                                                                                                                                                     
   1520                                                                                                                                                               
   1521         goto out;                                                                                                                                             
   1522                                                                                                                                                               
   1523  not_ready:                                                                                                                                                   
   1524         spin_unlock_irq(shost->host_lock);                                                                                                                    
   1525                                                                                                                                                               
   1526         //                                                                                                                                                    
   1527          * lock q, handle tag, requeue req, and decrement device_busy. We                                                                                     
   1528          * must return with queue_lock held.                                                                                                                  
   1529          *                                                                                                                                                    
   1530          * Decrementing device_busy without checking it is OK, as all such                                                                                    
   1531          * cases (host limits or settings) should run the queue at some                                                                                       
   1532          * later time.                                                                                                                                        
   1533          //                                                                                                                                                   
   1534         spin_lock_irq(q->queue_lock);                                                                                                                         
   1535         blk_requeue_request(q, req);                                                                                                                          
   1536         sdev->device_busy--;                                                                                                                                  
   1537         if(sdev->device_busy == 0)                                                                                                                            
   1538                 blk_plug_device(q);                                                                                                                           
   1539  out:                                                                                                                                                         
   1540         // must be careful here...if we trigger the ->remove() function                                                                                       
   1541          * we cannot be holding the q lock //                                                                                                                 
   1542         spin_unlock_irq(q->queue_lock);                                                                                                                       
   1543         put_device(&sdev->sdev_gendev);                                                                                                                       
   1544         spin_lock_irq(q->queue_lock);                                                                                                                         
   1545 }                                                                                                                                                             
���ȹ�ע elv_next_request().���� block/elevator.c:                                                                                                                    
    712 struct request *elv_next_request(request_queue_t *q)                                                                                                          
    713 {                                                                                                                                                             
    714         struct request *rq;                                                                                                                                   
    715         int ret;                                                                                                                                              
    716                                                                                                                                                               
    717         while ((rq = __elv_next_request(q)) != NULL) {                                                                                                        
    718                  if (!(rq->cmd_flags & REQ_STARTED)) {                                                                                                        
    719                         //                                                                                                                                    
    720                          * This is the first time the device driver                                                                                           
    721                          * sees this request (possibly after                                                                                                  
    722                          * requeueing).  Notify IO scheduler.                                                                                                 
    723                          //                                                                                                                                   
    724                         if (blk_sorted_rq(rq)) Linux  ��Щ�¶�֮���� Block��                                                                                  
�� 68  ҳ �� 117  ҳ                                                                                                                                                  
    725                                 elv_activate_rq(q, rq);                                                                                                       
    726                                                                                                                                                               
    727                         //                                                                                                                                    
    728                          * just mark as started even if we don't start                                                                                        
    729                          * it, a request that has been delayed should                                                                                         
    730                          * not be passed by new incoming requests                                                                                             
    731                          //                                                                                                                                   
    732                         rq->cmd_flags |= REQ_STARTED;                                                                                                         
    733                         blk_add_trace_rq(q, rq, BLK_TA_ISSUE);                                                                                                
    734                 }                                                                                                                                             
    735                                                                                                                                                               
    736                 if (!q->boundary_rq || q->boundary_rq == rq) {                                                                                                
    737                          q->end_sector = rq_end_sector(rq);                                                                                                   
    738                         q->boundary_rq = NULL;                                                                                                                
    739                 }                                                                                                                                             
    740                                                                                                                                                               
    741                 if ((rq->cmd_flags & REQ_DONTPREP) || !q->prep_rq_fn)                                                                                         
    742                         break;                                                                                                                                
    743                                                                                                                                                               
    744                 ret = q->prep_rq_fn(q, rq);                                                                                                                   
    745                 if (ret == BLKPREP_OK) {                                                                                                                      
    746                         break;                                                                                                                                
    747                 } else if (ret == BLKPREP_DEFER) {                                                                                                            
    748                         //                                                                                                                                    
    749                          * the request may have been (partially) prepped.                                                                                     
    750                          * we need to keep this request in the front to                                                                                       
    751                          * avoid resource deadlock.  REQ_STARTED will                                                                                         
752                          * prevent other fs requests from passing this one.                                                                                       
    753                          //                                                                                                                                   
    754                         rq = NULL;                                                                                                                            
    755                         break;                                                                                                                                
    756                 } else if (ret == BLKPREP_KILL) {                                                                                                             
    757                         int nr_bytes = rq->hard_nr_sectors << 9;                                                                                              
    758                                                                                                                                                               
    759                         if (!nr_bytes)                                                                                                                        
    760                                 nr_bytes = rq->data_len;                                                                                                      
    761                                                                                                                                                               
    762                         blkdev_dequeue_request(rq);                                                                                                           
    763                         rq->cmd_flags |= REQ_QUIET;                                                                                                           
    764                         end_that_request_chunk(rq, 0, nr_bytes);                                                                                              
    765                         end_that_request_last(rq, 0);                                                                                                         
    766                 } else {                                                                                                                                      
    767                         printk(KERN_ERR "%s: bad return=%d\n",                                                                                                
// __FUNCTION__, Linux  ��Щ�¶�֮���� Block��                                                                                                                           
// �� 69  ҳ �� 117  ҳ                                                                                                                                                  
    768                                                                 ret);                                                                                         
    769                         break;                                                                                                                                
    770                 }                                                                                                                                             
    771         }                                                                                                                                                     
    772                                                                                                                                                               
    773         return rq;                                                                                                                                            
    774 }                                                                                                                                                             
// �����õ�__elv_next_request()��Ȼ���� block/elevator.c:                                                                                                                
    696 static inline struct request *__elv_next_request(request_queue_t *q)                                                                                          
    697 {                                                                                                                                                             
    698         struct request *rq;                                                                                                                                   
    699                                                                                                                                                               
    700         while (1) {                                                                                                                                           
    701                 while (!list_empty(&q->queue_head)) {                                                                                                         
    702                         rq = list_entry_rq(q->queue_head.next);                                                                                               
    703                         if (blk_do_ordered(q, &rq))                                                                                                           
    704                                 return rq;                                                                                                                    
    705                 }                                                                                                                                             
    706                                                                                                                                                               
    707                 if (!q->elevator->ops->elevator_dispatch_fn(q, 0))                                                                                            
    708                         return NULL;                                                                                                                          
    709         }                                                                                                                                                     
    710 }                                                                                                                                                             
// �������Ǹղ��Ǹ����ʵĲ��붯��,���� q->queue_head ������Ϊ��.���Դ���ȡ��һ��                                                                                         
// request ��.                                                                                                                                                           
// ������ blk_do_ordered(),���� block/ll_rw_blk.c:                                                                                                                       
    478 int blk_do_ordered(request_queue_t *q, struct request **rqp)                                                                                                  
    479 {                                                                                                                                                             
    480         struct request *rq = *rqp;                                                                                                                            
    481         int is_barrier = blk_fs_request(rq) && blk_barrier_rq(rq);                                                                                            
    482                                                                                                                                                               
    483         if (!q->ordseq) {                                                                                                                                     
    484                 if (!is_barrier)                                                                                                                              
    485                         return 1;                                                                                                                             
    486                                                                                                                                                               
    487                 if (q->next_ordered != QUEUE_ORDERED_NONE) {                                                                                                  
    488                         *rqp = start_ordered(q, rq);                                                                                                          
    489                         return 1;                                                                                                                             
    490                 } else {                                                                                                                                      
    491                         //                                                                                                                                    
    492                          * This can happen when the queue switches to                                                                                         
    493                          * ORDERED_NONE while this request is on it.                                                                                          
    494                          //                                                                                                                                   
    495                         blkdev_dequeue_request(rq); Linux  ��Щ�¶�֮���� Block��                                                                             
�� 70  ҳ �� 117  ҳ                                                                                                                                                  
    496                         end_that_request_first(rq, -EOPNOTSUPP,                                                                                               
    497                                                rq->hard_nr_sectors);                                                                                          
    498                         end_that_request_last(rq, -EOPNOTSUPP);                                                                                               
    499                         *rqp = NULL;                                                                                                                          
    500                         return 0;                                                                                                                             
    501                 }                                                                                                                                             
    502         }                                                                                                                                                     
    503                                                                                                                                                               
    504         //                                                                                                                                                    
    505          * Ordered sequence in progress                                                                                                                       
    506          //                                                                                                                                                   
    507                                                                                                                                                               
    508         // Special requests are not subject to ordering rules. //                                                                                             
    509         if (!blk_fs_request(rq) &&                                                                                                                            
    510             rq != &q->pre_flush_rq && rq != &q->post_flush_rq)                                                                                                
    511                 return 1;                                                                                                                                     
    512                                                                                                                                                               
    513         if (q->ordered & QUEUE_ORDERED_TAG) {                                                                                                                 
    514                 // Ordered by tag.  Blocking the next barrier is enough. //                                                                                   
    515                  if (is_barrier && rq != &q->bar_rq)                                                                                                          
    516                         *rqp = NULL;                                                                                                                          
    517         } else {                                                                                                                                              
    518                 // Ordered by draining.  Wait for turn. //                                                                                                    
    519                 WARN_ON(blk_ordered_req_seq(rq) < blk_ordered_cur_seq(q));                                                                                    
520                 if (blk_ordered_req_seq(rq) > blk_ordered_cur_seq(q))                                                                                             
    521                         *rqp = NULL;                                                                                                                          
    522         }                                                                                                                                                     
    523                                                                                                                                                               
    524         return 1;                                                                                                                                             
    525 }                                                                                                                                                             
// ���ȿ�һ�� blk_fs_request,                                                                                                                                            
//     528 #define blk_fs_request(rq)       ((rq)->cmd_type == REQ_TYPE_FS)                                                                                              
// ����Ȼ,���ǵ�����������һ��.                                                                                                                                        
// ���������������������,is_barrier һ���� 0.����,blk_do_ordered ������˵,ֱ�ӷ��� 1.��ô                                                                               
// �ص�__elv_next_request �Ժ�,703 ����� if �����������,����Ҳ���Ƿ��� rq.�������Ǹ�                                                                                   
// elevator_dispatch_fn ʵ����������������������ǲ���ִ�е�.��һ����,���Ǵ�                                                                                             
// __elv_next_request����,�ص�elv_next_request()��ʱ��,ֻҪrequest queue���ǿյ�,��ô����                                                                                
// ֵ���Ƕ���ͷ���Ǹ� request.                                                                                                                                           
// ����������,cmd_flags ��ʵ�������������� REQ_STARTED ��Ҳ��������,732 ��,��������                                                                                      
// ��ִ�� 732��֮ǰ,��� flag ��û�����õ�.���,if�����������.                                                                                                          
// �� blk_sorted_rq ����һ����,���� include/linux/blkdev.h:                                                                                                              
//     543 #define blk_sorted_rq(rq)        ((rq)->cmd_flags & REQ_SORTED)                                                                                               
// ����Ȼ,����Ҳ����û�����ù���� flag,�������ﲻ�����ǵ���.                                                                                                            
// ��Ȼ��,���� noop,����ִ����һ������Ҳû������,��Ϊ��� elv_activate_rq()����Linux  ��Щ�¶�֮���� Block��                                                             
// �� 71  ҳ �� 117  ҳ                                                                                                                                                  
block/elevator.c:                                                                                                                                                     
    272 static void elv_activate_rq(request_queue_t *q, struct request *rq)                                                                                           
    273 {                                                                                                                                                             
    274         elevator_t *e = q->elevator;                                                                                                                          
    275                                                                                                                                                               
    276         if (e->ops->elevator_activate_req_fn)                                                                                                                 
    277                  e->ops->elevator_activate_req_fn(q, rq);                                                                                                     
    278 }                                                                                                                                                             
// ������֪��,���� noop ��˵,������û�����ָ��,�������ǲ�׼������.                                                                                                      
// ��ʱ��,�������� REQ_STARTED ��� flag.                                                                                                                                
// �ʼ������ elevator_init()��,����ôһ��:                                                                                                                            
//     230         q->boundary_rq = NULL;                                                                                                                                
// ���� rq_end_sector�ᱻִ��,����ʵҲֻ��һ���ܼ򵥵ĺ�.                                                                                                                
//     172 #define rq_end_sector(rq)        ((rq)->sector + (rq)->nr_sectors)                                                                                            
// ͬʱ,boundary_rq ���Ǳ���Ϊ NULL.                                                                                                                                     
// ������,�������ǰ� prep_rq_fn ������ scsi_prep_fn,��������Ҫ��һ����� scsi_prep_fn(),��                                                                               
// ������ drivers/scsi/scsi_lib.c�ĺ���.                                                                                                                                 
   1176 static int scsi_prep_fn(struct request_queue *q, struct request *req)                                                                                         
   1177 {                                                                                                                                                             
   1178         struct scsi_device *sdev = q->queuedata;                                                                                                              
   1179         int ret = BLKPREP_OK;                                                                                                                                 
   1180                                                                                                                                                               
   1181         //                                                                                                                                                    
   1182          * If the device is not in running state we will reject some                                                                                          
   1183          * or all commands.                                                                                                                                   
   1184          //                                                                                                                                                   
   1185         if (unlikely(sdev->sdev_state != SDEV_RUNNING)) {                                                                                                     
   1186                 switch (sdev->sdev_state) {                                                                                                                   
   1187                 case SDEV_OFFLINE:                                                                                                                            
   1188                         //                                                                                                                                    
   1189                          * If the device is offline we refuse to process any                                                                                  
   1190                          * commands.  The device must be brought online                                                                                       
   1191                          * before trying any recovery commands.                                                                                               
   1192                          //                                                                                                                                   
   1193                         sdev_printk(KERN_ERR, sdev,                                                                                                           
   1194                                     "rejecting I/O to offline device\n");                                                                                     
   1195                         ret = BLKPREP_KILL;                                                                                                                   
   1196                         break;                                                                                                                                
   1197                 case SDEV_DEL:                                                                                                                                
   1198                         //                                                                                                                                    
   1199                          * If the device is fully deleted, we refuse to                                                                                       
   1200                          * process any commands as well.                                                                                                      
   1201                          //                                                                                                                                   
   1202                         sdev_printk(KERN_ERR, sdev, Linux  ��Щ�¶�֮���� Block��                                                                             
�� 72  ҳ �� 117  ҳ                                                                                                                                                  
   1203                                     "rejecting I/O to dead device\n");                                                                                        
   1204                         ret = BLKPREP_KILL;                                                                                                                   
   1205                         break;                                                                                                                                
   1206                 case SDEV_QUIESCE:                                                                                                                            
   1207                 case SDEV_BLOCK:                                                                                                                              
   1208                         //                                                                                                                                    
   1209                          * If the devices is blocked we defer normal commands.                                                                                
   1210                          //                                                                                                                                   
   1211                         if (!(req->cmd_flags & REQ_PREEMPT))                                                                                                  
   1212                                 ret = BLKPREP_DEFER;                                                                                                          
   1213                         break;                                                                                                                                
   1214                 default:                                                                                                                                      
   1215                         //                                                                                                                                    
   1216                          * For any other not fully online state we only allow                                                                                 
   1217                          * special commands.  In particular any user initiated                                                                                
   1218                          * command is not allowed.                                                                                                            
   1219                          //                                                                                                                                   
   1220                         if (!(req->cmd_flags & REQ_PREEMPT))                                                                                                  
   1221                                 ret = BLKPREP_KILL;                                                                                                           
   1222                         break;                                                                                                                                
   1223                 }                                                                                                                                             
   1224                                                                                                                                                               
   1225                 if (ret != BLKPREP_OK)                                                                                                                        
   1226                         goto out;                                                                                                                             
   1227         }                                                                                                                                                     
   1228                                                                                                                                                               
   1229         switch (req->cmd_type) {                                                                                                                              
   1230         case REQ_TYPE_BLOCK_PC:                                                                                                                               
   1231                 ret = scsi_setup_blk_pc_cmnd(sdev, req);                                                                                                      
   1232                 break;                                                                                                                                        
   1233         case REQ_TYPE_FS:                                                                                                                                     
   1234                 ret = scsi_setup_fs_cmnd(sdev, req);                                                                                                          
   1235                 break;                                                                                                                                        
   1236         default:                                                                                                                                              
   1237                 //                                                                                                                                            
   1238                  * All other command types are not supported.                                                                                                 
   1239                  *                                                                                                                                            
   1240                  * Note that these days the SCSI subsystem does not use                                                                                       
   1241                  * REQ_TYPE_SPECIAL requests anymore.  These are only used                                                                                    
   1242                  * (directly or via blk_insert_request) by non-SCSI drivers.                                                                                  
   1243                  //                                                                                                                                           
   1244                 blk_dump_rq_flags(req, "SCSI bad req");                                                                                                       
   1245                 ret = BLKPREP_KILL;                                                                                                                           
   1246                 break; Linux  ��Щ�¶�֮���� Block��                                                                                                          
�� 73  ҳ �� 117  ҳ                                                                                                                                                  
   1247         }                                                                                                                                                     
   1248                                                                                                                                                               
   1249  out:                                                                                                                                                         
   1250         switch (ret) {                                                                                                                                        
   1251         case BLKPREP_KILL:                                                                                                                                    
   1252                 req->errors = DID_NO_CONNECT << 16;                                                                                                           
   1253                 break;                                                                                                                                        
   1254         case BLKPREP_DEFER:                                                                                                                                   
   1255                 //                                                                                                                                            
   1256                  * If we defer, the elv_next_request() returns NULL, but the                                                                                  
   1257                  * queue must be restarted, so we plug here if no returning                                                                                   
   1258                  * command will automatically do that.                                                                                                        
   1259                  //                                                                                                                                           
   1260                 if (sdev->device_busy == 0)                                                                                                                   
   1261                         blk_plug_device(q);                                                                                                                   
   1262                 break;                                                                                                                                        
   1263         default:                                                                                                                                              
   1264                 req->cmd_flags |= REQ_DONTPREP;                                                                                                               
   1265         }                                                                                                                                                     
   1266                                                                                                                                                               
   1267         return ret;                                                                                                                                           
   1268 }                                                                                                                                                             
// ����·,���ǻ��ߵ� 1229 ����� switch ���,���һ���� scsi ��������Ͷ�ִ�в�ͬ�ĺ���,                                                                                 
// scsi_setup_blk_pc_cmnd����scsi_setup_fs_cmnd.��ô����cmd_type������ʲô��?��������                                                                                    
// �̵�����,�̼ǵ����� scsi_execute()������ôһ��,                                                                                                                       
    199         req->cmd_type = REQ_TYPE_BLOCK_PC;                                                                                                                    
// ����,ûʲô��˵��.���ǻ�ִ�� scsi_setup_blk_pc_cmnd,���� drivers/scsi/scsi_lib.c:                                                                                     
   1090 static int scsi_setup_blk_pc_cmnd(struct scsi_device *sdev, struct request *req)                                                                              
   1091 {                                                                                                                                                             
   1092         struct scsi_cmnd *cmd;                                                                                                                                
   1093                                                                                                                                                               
   1094         cmd = scsi_get_cmd_from_req(sdev, req);                                                                                                               
   1095         if (unlikely(!cmd))                                                                                                                                   
   1096                 return BLKPREP_DEFER;                                                                                                                         
   1097                                                                                                                                                               
   1098         //                                                                                                                                                    
   1099          * BLOCK_PC requests may transfer data, in which case they must                                                                                       
   1100          * a bio attached to them.  Or they might contain a SCSI command                                                                                      
   1101          * that does not transfer data, in which case they may optionally                                                                                     
   1102          * submit a request without an attached bio.                                                                                                          
   1103          //                                                                                                                                                   
   1104         if (req->bio) {                                                                                                                                       
   1105                 int ret;                                                                                                                                      
   1106 Linux  ��Щ�¶�֮���� Block��                                                                                                                                 
�� 74  ҳ �� 117  ҳ                                                                                                                                                  
   1107                 BUG_ON(!req->nr_phys_segments);                                                                                                               
   1108                                                                                                                                                               
   1109                 ret = scsi_init_io(cmd);                                                                                                                      
   1110                 if (unlikely(ret))                                                                                                                            
   1111                         return ret;                                                                                                                           
   1112         } else {                                                                                                                                              
   1113                 BUG_ON(req->data_len);                                                                                                                        
   1114                 BUG_ON(req->data);                                                                                                                            
   1115                                                                                                                                                               
   1116                 cmd->request_bufflen = 0;                                                                                                                     
   1117                 cmd->request_buffer = NULL;                                                                                                                   
   1118                 cmd->use_sg = 0;                                                                                                                              
   1119                 req->buffer = NULL;                                                                                                                           
   1120         }                                                                                                                                                     
   1121                                                                                                                                                               
   1122         BUILD_BUG_ON(sizeof(req->cmd) > sizeof(cmd->cmnd));                                                                                                   
   1123         memcpy(cmd->cmnd, req->cmd, sizeof(cmd->cmnd));                                                                                                       
   1124         cmd->cmd_len = req->cmd_len;                                                                                                                          
   1125         if (!req->data_len)                                                                                                                                   
   1126                 cmd->sc_data_direction = DMA_NONE;                                                                                                            
   1127         else if (rq_data_dir(req) == WRITE)                                                                                                                   
   1128                 cmd->sc_data_direction = DMA_TO_DEVICE;                                                                                                       
   1129         else                                                                                                                                                  
   1130                 cmd->sc_data_direction = DMA_FROM_DEVICE;                                                                                                     
   1131                                                                                                                                                               
   1132         cmd->transfersize = req->data_len;                                                                                                                    
   1133         cmd->allowed = req->retries;                                                                                                                          
   1134         cmd->timeout_per_command = req->timeout;                                                                                                              
   1135         cmd->done = scsi_blk_pc_done;                                                                                                                         
   1136         return BLKPREP_OK;                                                                                                                                    
   1137 }                                                                                                                                                             
// ����������㻹�� scsi cmd ������γɵ���������Ļ�,��ô���Ŵ˿�,��Ӧ�û������˰�,                                                                                     
// �����ǵ�����usb-storage�Ǹ������п�������sc_data_direction���жϵ�ʱ��,�㲻������                                                                                   
// ֵ������趨��,��ô�˿�,������������չ��������ǰ,����Ѿ��ҿ��������������Ű�.                                                                                      
// ����,�����Ļ�,�������� BLKPREP_OK.prep ��ʾ prepare ����˼,�����ǵ�ĸ��˵����׼��                                                                                     
// ����˼,���BLKPREP_OK��˵��׼������,����˵׼������.��scsi_prep_fn()Ҳ���������                                                                                       
// ֵ,����֮ǰ��������cmd_flags�е�REQ_DONTPREP.(ע��elv_next_request()����741����                                                                                       
// �ϵľ�����û����� flag.)                                                                                                                                             
// �ص� elv_next_request()��,���ڷ���ֵ�� BLKPREP_OK,���� 746 �����Ǿ� break ��.����֮,                                                                                  
// ����ȡ����һ��request,����Ϊ֮׼������scsi����,������һ���͸���ִ�����������.����                                                                                    
// ���ǲ���Ҫ���� elv_next_request()������.�������ڻص��� scsi_request_fn(),��Ψ�����̹��                                                                               
// �Ĵ�Ϸ�ľ������������ڵ�������һ��,������������ֺγ����������?������Ψ���˵                                                                                        
// ��Ȼ���̺��Ƶ���,�������������.����������Զ�����������,��֪��ʱ���Ǹ�ͷ,�ⲻ,��                                                                                     
// ���� elv_next_request,��Ҫ����һ��,��ֻ��һ��,��������,1467 ��,һ�����һ������,����Linux  ��Щ�¶�֮���� Block��                                                     
// �� 75  ҳ �� 117  ҳ                                                                                                                                                  
// blk_queue_tagged,����include/linux/blkdev.h:                                                                                                                          
//     524 #define blk_queue_tagged(q)     test_bit(QUEUE_FLAG_QUEUED,                                                                                                   
// &(q)->queue_flags)                                                                                                                                                    
// �������� blk_queue_start_tag,���� block/ll_rw_blk.c:                                                                                                                  
//    1104 ///                                                                                                                                                           
//    1105  * blk_queue_start_tag - find a free tag and assign it                                                                                                        
//    1106  * @q:  the request queue for the device                                                                                                                      
//    1107  * @rq:  the block request that needs tagging                                                                                                                 
//    1108  *                                                                                                                                                            
//    1109  *  Description:                                                                                                                                              
//    1110  *    This can either be used as a stand-alone helper, or possibly be                                                                                         
//    1111  *    assigned as the queue &prep_rq_fn (in which case &struct request                                                                                        
//    1112  *    automagically gets a tag assigned). Note that this function                                                                                             
//    1113  *    assumes that any type of request can be queued! if this is not                                                                                          
//    1114  *    true for your device, you must check the request type before                                                                                            
//    1115  *    calling this function.  The request will also be removed from                                                                                           
//    1116  *    the request queue, so it's the drivers responsibility to readd                                                                                          
//    1117  *    it if it should need to be restarted for some reason.                                                                                                   
//    1118  *                                                                                                                                                            
//    1119  *  Notes:                                                                                                                                                    
//    1120  *   queue lock must be held.                                                                                                                                 
   1121  ///                                                                                                                                                          
   1122 int blk_queue_start_tag(request_queue_t *q, struct request *rq)                                                                                               
   1123 {                                                                                                                                                             
   1124         struct blk_queue_tag *bqt = q->queue_tags;                                                                                                            
   1125         int tag;                                                                                                                                              
   1126                                                                                                                                                               
   1127         if (unlikely((rq->cmd_flags & REQ_QUEUED))) {                                                                                                         
   1128                 printk(KERN_ERR                                                                                                                               
   1129                        "%s: request %p for device [%s] already tagged %d",                                                                                    
   1130                        __FUNCTION__, rq,                                                                                                                      
   1131                        rq->rq_disk ? rq->rq_disk->disk_name : "?", rq->tag);                                                                                  
   1132                 BUG();                                                                                                                                        
   1133         }                                                                                                                                                     
   1134                                                                                                                                                               
   1135         //                                                                                                                                                    
   1136          * Protect against shared tag maps, as we may not have exclusive                                                                                      
   1137          * access to the tag map.                                                                                                                             
   1138          //                                                                                                                                                   
   1139         do {                                                                                                                                                  
   1140                 tag = find_first_zero_bit(bqt->tag_map, bqt->max_depth);                                                                                      
   1141                 if (tag >= bqt->max_depth)                                                                                                                    
   1142                         return 1;                                                                                                                             
   1143 Linux  ��Щ�¶�֮���� Block��                                                                                                                                 
�� 76  ҳ �� 117  ҳ                                                                                                                                                  
   1144         } while (test_and_set_bit(tag, bqt->tag_map));                                                                                                        
   1145                                                                                                                                                               
   1146         rq->cmd_flags |= REQ_QUEUED;                                                                                                                          
   1147         rq->tag = tag;                                                                                                                                        
   1148         bqt->tag_index[tag] = rq;                                                                                                                             
   1149         blkdev_dequeue_request(rq);                                                                                                                           
   1150         list_add(&rq->queuelist, &bqt->busy_list);                                                                                                            
   1151         bqt->busy++;                                                                                                                                          
   1152         return 0;                                                                                                                                             
   1153 }                                                                                                                                                             
// �������Ǵ��������˵,�����������ķ���ֵ���� 0.                                                                                                                        
// Ҳ���,��һ������ blkdev_dequeue_request()�ͻᱻִ��.���� include/linux/blkdev.h:                                                                                     
    725 static inline void blkdev_dequeue_request(struct request *req)                                                                                                
    726 {                                                                                                                                                             
    727         elv_dequeue_request(req->q, req);                                                                                                                     
    728 }                                                                                                                                                             
�� elv_dequeue_request ���� block/elevator.c:                                                                                                                         
    778 void elv_dequeue_request(request_queue_t *q, struct request *rq)                                                                                              
    779 {                                                                                                                                                             
    780         BUG_ON(list_empty(&rq->queuelist));                                                                                                                   
    781         BUG_ON(ELV_ON_HASH(rq));                                                                                                                              
    782                                                                                                                                                               
    783         list_del_init(&rq->queuelist);                                                                                                                        
    784                                                                                                                                                               
    785         //                                                                                                                                                    
    786          * the time frame between a request being removed from the lists                                                                                      
    787          * and to it is freed is accounted as io that is in progress at                                                                                       
    788          * the driver side.                                                                                                                                   
    789          //                                                                                                                                                   
    790         if (blk_account_rq(rq))                                                                                                                               
    791                 q->in_flight++;                                                                                                                               
    792 }                                                                                                                                                             
// ������������������뱻���õĹ�ϵ,��Ȼ��� request �Ѿ�û�������ü�ֵ,�����Ѿ���                                                                                     
// �����ϵõ���������Ҫ�� scsi ����,��ô������ȫ���Թ��Ӳ���жĥɱ¿��.list_del_init ����                                                                                
// �� request ��request queue������ɾ����.                                                                                                                               
// ��������� blk_account_rq Ҳ��һ������ include/linux/blkdev.h�ĺ�:                                                                                                    
//     536 #define blk_account_rq(rq)       (blk_rq_started(rq) && blk_fs_request(rq))                                                                                   
// ����Ȼ,���ٵڶ������������ǲ������.���Բ��ö�˵,������� elv_dequeue_request.                                                                                        
// ������ʱ��ȥִ�� scsi������.���Ե��� scsi_dispatch_cmd().                                                                                                             
//  Linux  ��Щ�¶�֮���� Block��                                                                                                                                        
// �� 77  ҳ �� 117  ҳ                                                                                                                                                  
// scsi �����ǰ������(��)                                                                                                                                               
// ��һ����Ϊ��Ҫ�ĺ����� scsi_dispatch_cmd,���� drivers/scsi/scsi.c:                                                                                                    
//     459 //                                                                                                                                                            
//     460  * Function:    scsi_dispatch_command                                                                                                                         
//     461  *                                                                                                                                                            
//     462  * Purpose:     Dispatch a command to the low-level driver.                                                                                                   
//     463  *                                                                                                                                                            
//     464  * Arguments:   cmd - command block we are dispatching.                                                                                                       
//     465  *                                                                                                                                                            
//     466  * Notes:                                                                                                                                                     
//     467  //                                                                                                                                                           
    468 int scsi_dispatch_cmd(struct scsi_cmnd *cmd)                                                                                                                  
    469 {                                                                                                                                                             
    470         struct Scsi_Host *host = cmd->device->host;                                                                                                           
    471         unsigned long flags = 0;                                                                                                                              
    472         unsigned long timeout;                                                                                                                                
    473         int rtn = 0;                                                                                                                                          
    474                                                                                                                                                               
    475         // check if the device is still usable //                                                                                                             
    476         if (unlikely(cmd->device->sdev_state == SDEV_DEL)) {                                                                                                  
    477                 // in SDEV_DEL we error all commands. DID_NO_CONNECT                                                                                          
    478                  * returns an immediate error upwards, and signals                                                                                            
    479                  * that the device is no longer present //                                                                                                    
    480                 cmd->result = DID_NO_CONNECT << 16;                                                                                                           
    481                 atomic_inc(&cmd->device->iorequest_cnt);                                                                                                      
    482                 __scsi_done(cmd);                                                                                                                             
    483                 // return 0 (because the command has been processed) //                                                                                       
    484                 goto out;                                                                                                                                     
    485         }                                                                                                                                                     
    486                                                                                                                                                               
    487         // Check to see if the scsi lld put this device into state SDEV_BLOCK. //                                                                             
    488         if (unlikely(cmd->device->sdev_state == SDEV_BLOCK)) {                                                                                                
    489                 //                                                                                                                                            
    490                  * in SDEV_BLOCK, the command is just put back on the device                                                                                  
    491                  * queue.  The suspend state has already blocked the queue so                                                                                 
    492                  * future requests should not occur until the device                                                                                          
    493                  * transitions out of the suspend state.                                                                                                      
    494                  //                                                                                                                                           
    495                 scsi_queue_insert(cmd, SCSI_MLQUEUE_DEVICE_BUSY);                                                                                             
    496                                                                                                                                                               
    497                 SCSI_LOG_MLQUEUE(3, printk("queuecommand : device                                                                                             
blocked \n")); Linux  ��Щ�¶�֮���� Block��                                                                                                                          
�� 78  ҳ �� 117  ҳ                                                                                                                                                  
    498                                                                                                                                                               
    499                 //                                                                                                                                            
    500                  * NOTE: rtn is still zero here because we don't need the                                                                                     
    501                  * queue to be plugged on return (it's already stopped)                                                                                       
    502                  //                                                                                                                                           
    503                 goto out;                                                                                                                                     
    504         }                                                                                                                                                     
    505                                                                                                                                                               
    506         //                                                                                                                                                    
    507          * If SCSI-2 or lower, store the LUN value in cmnd.                                                                                                   
    508          //                                                                                                                                                   
    509         if (cmd->device->scsi_level <= SCSI_2 &&                                                                                                              
    510             cmd->device->scsi_level != SCSI_UNKNOWN) {                                                                                                        
    511                 cmd->cmnd[1] = (cmd->cmnd[1] & 0x1f) |                                                                                                        
    512                                (cmd->device->lun << 5 & 0xe0);                                                                                                
    513         }                                                                                                                                                     
    514                                                                                                                                                               
    515         //                                                                                                                                                    
    516          * We will wait MIN_RESET_DELAY clock ticks after the last reset so                                                                                   
    517          * we can avoid the drive not being ready.                                                                                                            
    518          //                                                                                                                                                   
    519         timeout = host->last_reset + MIN_RESET_DELAY;                                                                                                         
    520                                                                                                                                                               
    521         if (host->resetting && time_before(jiffies, timeout)) {                                                                                               
    522                 int ticks_remaining = timeout - jiffies;                                                                                                      
    523                 //                                                                                                                                            
    524                  * NOTE: This may be executed from within an interrupt                                                                                        
    525                  * handler!  This is bad, but for now, it'll do.  The irq                                                                                     
    526                  * level of the interrupt handler has been masked out by the                                                                                  
    527                  * platform dependent interrupt handling code already, so the                                                                                 
    528                  * sti() here will not cause another call to the SCSI host's                                                                                  
    529                  * interrupt handler (assuming there is one irq-level per                                                                                     
    530                  * host).                                                                                                                                     
    531                  //                                                                                                                                           
    532                 while (--ticks_remaining >= 0)                                                                                                                
    533                         mdelay(1 + 999 / HZ);                                                                                                                 
    534                 host->resetting = 0;                                                                                                                          
    535         }                                                                                                                                                     
    536                                                                                                                                                               
    537         //                                                                                                                                                    
    538          * AK: unlikely race here: for some reason the timer could                                                                                            
    539          * expire before the serial number is set up below.                                                                                                   
540          //                                                                                                                                                       
    541         scsi_add_timer(cmd, cmd->timeout_per_command, scsi_times_out); Linux  ��Щ�¶�֮���� Block��                                                          
�� 79  ҳ �� 117  ҳ                                                                                                                                                  
    542                                                                                                                                                               
    543         scsi_log_send(cmd);                                                                                                                                   
    544                                                                                                                                                               
    545         //                                                                                                                                                    
    546          * We will use a queued command if possible, otherwise we will                                                                                        
    547          * emulate the queuing and calling of completion function ourselves.                                                                                  
    548          //                                                                                                                                                   
    549         atomic_inc(&cmd->device->iorequest_cnt);                                                                                                              
    550                                                                                                                                                               
    551         //                                                                                                                                                    
    552          * Before we queue this command, check if the command                                                                                                 
    553          * length exceeds what the host adapter can handle.                                                                                                   
    554          //                                                                                                                                                   
    555         if (CDB_SIZE(cmd) > cmd->device->host->max_cmd_len) {                                                                                                 
    556                 SCSI_LOG_MLQUEUE(3,                                                                                                                           
    557                                 printk("queuecommand : command too                                                                                            
long.\n"));                                                                                                                                                           
    558                 cmd->result = (DID_ABORT << 16);                                                                                                              
    559                                                                                                                                                               
    560                 scsi_done(cmd);                                                                                                                               
    561                 goto out;                                                                                                                                     
    562         }                                                                                                                                                     
    563                                                                                                                                                               
    564         spin_lock_irqsave(host->host_lock, flags);                                                                                                            
    565         scsi_cmd_get_serial(host, cmd);                                                                                                                       
    566                                                                                                                                                               
    567         if (unlikely(host->shost_state == SHOST_DEL)) {                                                                                                       
    568                 cmd->result = (DID_NO_CONNECT << 16);                                                                                                         
    569                 scsi_done(cmd);                                                                                                                               
    570         } else {                                                                                                                                              
    571                 rtn = host->hostt->queuecommand(cmd, scsi_done);                                                                                              
    572         }                                                                                                                                                     
    573         spin_unlock_irqrestore(host->host_lock, flags);                                                                                                       
    574         if (rtn) {                                                                                                                                            
    575                 if (scsi_delete_timer(cmd)) {                                                                                                                 
    576                         atomic_inc(&cmd->device->iodone_cnt);                                                                                                 
    577                         scsi_queue_insert(cmd,                                                                                                                
    578                                           (rtn ==                                                                                                             
SCSI_MLQUEUE_DEVICE_BUSY) ?                                                                                                                                           
    579                                           rtn :                                                                                                               
SCSI_MLQUEUE_HOST_BUSY);                                                                                                                                              
    580                 }                                                                                                                                             
581                 SCSI_LOG_MLQUEUE(3,                                                                                                                               
    582                     printk("queuecommand : request rejected\n")); Linux  ��Щ�¶�֮���� Block��                                                               
�� 80  ҳ �� 117  ҳ                                                                                                                                                  
    583         }                                                                                                                                                     
    584                                                                                                                                                               
    585  out:                                                                                                                                                         
    586         SCSI_LOG_MLQUEUE(3, printk("leaving scsi_dispatch_cmnd()\n"));                                                                                        
    587         return rtn;                                                                                                                                           
    588 }                                                                                                                                                             
// һ·�������ֵ�һ����һ�۾Ϳ��������������ڴ���һ�д������571�Ǹ�queuecommand()                                                                                       
// �ĵ���.��Ϊ��֮�����Ǿ�֪���÷���ʲô��.������� U ��������˵,����ʹ�����ӹ�ȥ                                                                                      
// ��ʼִ��.������ʵ�ʵ�scsi������,���Ӧ�������е�queuecommandҲ�ᱻ����,ʣ�µ���                                                                                       
// �����ǾͲ��ò�����.��������� queuecommand ���� 0.���ǽ����� scsi_dispatch_cmd Ҳ��                                                                                   
// �� 0.����������ִ����һ�� scsi ������.                                                                                                                                
// �� scsi_request_fn() �Ƿ�������ÿ� while ѭ���������Ƿ����� , ����͵ÿ�                                                                                             
// blk_queue_plugged()����ɫ��.��ô���Ǵ�������������,ʲô��queue plugged?���ǵ����ɽ                                                                                   
// �ʰԸ�����plugged������������˼,��˵������������ʲô��˼?����˵,���Ļ������°��                                                                                      
// ����,������ĳ����ų�һ����һ��,���ǿ��ܰ��춼ǰ������,��ͽ�����,����˵�³�,Ҳ                                                                                     
// ������.Ϊ������ʹ��һ�� flag ����־�³����,���� include/linux/blkdev.h:                                                                                              
//     523 #define blk_queue_plugged(q)    test_bit(QUEUE_FLAG_PLUGGED,                                                                                                  
// &(q)->queue_flags)                                                                                                                                                    
// �ı������� flag �ĺ���������,һ��������,һ����ȡ��.                                                                                                                 
// �������õ��� blk_plug_device.                                                                                                                                         
//    1542 //                                                                                                                                                            
//    1543  * "plug" the device if there are no outstanding requests: this will                                                                                          
//    1544  * force the transfer to start only after we have put all the requests                                                                                        
//    1545  * on the list.                                                                                                                                               
//    1546  *                                                                                                                                                            
//    1547  * This is called with interrupts off and no requests on the queue and                                                                                        
//    1548  * with the queue lock held.                                                                                                                                  
//    1549  //                                                                                                                                                           
   1550 void blk_plug_device(request_queue_t *q)                                                                                                                      
   1551 {                                                                                                                                                             
   1552          WARN_ON(!irqs_disabled());                                                                                                                           
   1553                                                                                                                                                               
   1554         //                                                                                                                                                    
   1555      * don't plug a stopped queue, it must be paired with blk_start_queue()                                                                                   
   1556          * which will restart the queueing                                                                                                                    
   1557          //                                                                                                                                                   
   1558         if (blk_queue_stopped(q))                                                                                                                             
   1559                 return;                                                                                                                                       
   1560                                                                                                                                                               
   1561         if (!test_and_set_bit(QUEUE_FLAG_PLUGGED, &q->queue_flags)) {                                                                                         
   1562                 mod_timer(&q->unplug_timer, jiffies + q->unplug_delay);                                                                                       
   1563                 blk_add_trace_generic(q, NULL, 0, BLK_TA_PLUG);                                                                                               
   1564         }                                                                                                                                                     
   1565 } Linux  ��Щ�¶�֮���� Block��                                                                                                                               
�� 81  ҳ �� 117  ҳ                                                                                                                                                  
����ȡ������ blk_remove_plug().                                                                                                                                       
   1569 //                                                                                                                                                            
   1570  * remove the queue from the plugged list, if present. called with                                                                                            
   1571  * queue lock held and interrupts disabled.                                                                                                                   
   1572  //                                                                                                                                                           
   1573 int blk_remove_plug(request_queue_t *q)                                                                                                                       
   1574 {                                                                                                                                                             
   1575          WARN_ON(!irqs_disabled());                                                                                                                           
   1576                                                                                                                                                               
   1577         if (!test_and_clear_bit(QUEUE_FLAG_PLUGGED, &q->queue_flags))                                                                                         
   1578                 return 0;                                                                                                                                     
   1579                                                                                                                                                               
   1580         del_timer(&q->unplug_timer);                                                                                                                          
   1581         return 1;                                                                                                                                             
   1582 }                                                                                                                                                             
// ������ǰ�ߵĵط�����,�������Ǽ�����__elv_add_request,����ĸ�����int plug�Ϳ��Կ���                                                                                   
// �Ƿ���� blk_plug_device(),���������� blk_execute_rq_nowait()�е���__elv_add_request()��                                                                              
// ʱ�򴫵ݵ� plug ���� 1.                                                                                                                                               
// ��һ����,���� blk_remove_plug �ĵط�Ҳ�жദ.����__generic_unplug_device()����֮һ.��                                                                                 
// �������������������,ʵ���ϲ�û��������� flag,��� scsi_request_fn()�ͻᱻִ��.                                                                                      
// ��ô��д����������������Ϊ��ʲô��?����ͷ,��������,�ҿ��������Ϊ�˽ٸ���ƶ,����                                                                                      
// ɱ��,�ҿ��������Ϊ����������,������Ů�˺��ӳ�ǽ,�һ����������Ϊ�˷��پ���.Ȼ��,                                                                                     
// �ܳ�һ��ʱ���Ҷ�û�취������˱�д������������Ϊ��ʲô?                                                                                                               
// ��������,�����������,�����㾭����������������,��ᷢ�־����н��ϵ�������,����                                                                                      
// ĳλ�쵼��Ҫ����,����ĳλ�쵼��Ҫ����,������԰� blk_plug_device()����ɽ���,��                                                                                       
// blk_remove_plug ����ɿ���.����Ҫ���н�,ǰ��������û�н���,����֮,û���迨,��                                                                                         
// QUEUE_FLAG_PLUGGED ��� flag ���൱�ڡ�����,���������оͲ���ǰ����,û������п�                                                                                       
// ��ǰ��.֮������Ҫ�迨,����Ϊȷʵ���������,��ʱ��ȷʵ�����ö���ǰ��.                                                                                                  
// ��ô�������ǻ���������������������,mod_timer �� del_timer,���Ǹ���ʹ��?���ǵ�                                                                                         
// kblockd ô?�������Ǵ������Ǹ��������� kblockd_workqueue,���������ó�����ʱ����.��                                                                                     
// ���ǰѾ�ͷ���ص����� blk_init_queue_node().�������������������,��������ֻ��������                                                                                    
// ����������������صļ���:                                                                                                                                             
   1922         q->request_fn           = rfn;                                                                                                                        
   1923         q->prep_rq_fn           = NULL;                                                                                                                       
   1924         q->unplug_fn            = generic_unplug_device;                                                                                                      
   1925         q->queue_flags          = (1 << QUEUE_FLAG_CLUSTER);                                                                                                  
   1926         q->queue_lock           = lock;                                                                                                                       
   1927                                                                                                                                                               
   1928         blk_queue_segment_boundary(q, 0xffffffff);                                                                                                            
   1929                                                                                                                                                               
   1930         blk_queue_make_request(q, __make_request);                                                                                                            
// ���� q->unplug_fn �������� generic_unplug_device.��һ�����Ҫ,�Ժ���õ�.                                                                                             
// Ȼ������ blk_queue_make_request().���������ʱ���ǲ�û�н���.���� block/ll_rw_block.c:                                                                                
//     180 /// Linux  ��Щ�¶�֮���� Block��                                                                                                                             
// �� 82  ҳ �� 117  ҳ                                                                                                                                                  
//     181  * blk_queue_make_request - define an alternate make_request function for a device                                                                            
//     182  * @q:  the request queue for the device to be affected                                                                                                       
//     183  * @mfn: the alternate make_request function                                                                                                                  
//     184  *                                                                                                                                                            
//     185  * Description:                                                                                                                                               
//     186  *    The normal way for &struct bios to be passed to a device                                                                                                
//     187  *    driver is for them to be collected into requests on a request                                                                                           
//     188  *    queue, and then to allow the device driver to select requests                                                                                           
//     189  *    off that queue when it is ready.  This works well for many block                                                                                        
//     190  *    devices. However some block devices (typically virtual devices                                                                                          
//     191  *    such as md or lvm) do not benefit from the processing on the                                                                                            
//     192  *    request queue, and are served best by having the requests passed                                                                                        
//     193  *    directly to them.  This can be achieved by providing a function                                                                                         
//     194  *    to blk_queue_make_request().                                                                                                                            
//     195  *                                                                                                                                                            
//     196  * Caveat:                                                                                                                                                    
//     197  *    The driver that does this *must* be able to deal appropriately                                                                                          
//     198  *    with buffers in "highmemory". This can be accomplished by either calling                                                                                
//     199  *    __bio_kmap_atomic() to get a temporary kernel mapping, or by calling                                                                                    
//     200  *    blk_queue_bounce() to create a buffer in normal memory.                                                                                                 
//     201  ///                                                                                                                                                          
    202 void blk_queue_make_request(request_queue_t * q, make_request_fn * mfn)                                                                                       
    203 {                                                                                                                                                             
    204         //                                                                                                                                                    
    205          * set defaults                                                                                                                                       
    206          //                                                                                                                                                   
    207         q->nr_requests = BLKDEV_MAX_RQ;                                                                                                                       
    208         blk_queue_max_phys_segments(q, MAX_PHYS_SEGMENTS);                                                                                                    
    209         blk_queue_max_hw_segments(q, MAX_HW_SEGMENTS);                                                                                                        
    210         q->make_request_fn = mfn;                                                                                                                             
    211         q->backing_dev_info.ra_pages = (VM_MAX_READAHEAD * 1024) /                                                                                            
PAGE_CACHE_SIZE;                                                                                                                                                      
    212         q->backing_dev_info.state = 0;                                                                                                                        
    213         q->backing_dev_info.capabilities = BDI_CAP_MAP_COPY;                                                                                                  
    214         blk_queue_max_sectors(q, SAFE_MAX_SECTORS);                                                                                                           
    215         blk_queue_hardsect_size(q, 512);                                                                                                                      
    216         blk_queue_dma_alignment(q, 511);                                                                                                                      
    217         blk_queue_congestion_threshold(q);                                                                                                                    
    218         q->nr_batching = BLK_BATCH_REQ;                                                                                                                       
    219                                                                                                                                                               
    220         q->unplug_thresh = 4;           // hmm //                                                                                                             
    221         q->unplug_delay = (3 * HZ) / 1000;      // 3 milliseconds //                                                                                          
222         if (q->unplug_delay == 0)                                                                                                                                 
    223                 q->unplug_delay = 1; Linux  ��Щ�¶�֮���� Block��                                                                                            
�� 83  ҳ �� 117  ҳ                                                                                                                                                  
    224                                                                                                                                                               
    225         INIT_WORK(&q->unplug_work, blk_unplug_work);                                                                                                          
    226                                                                                                                                                               
    227         q->unplug_timer.function = blk_unplug_timeout;                                                                                                        
    228         q->unplug_timer.data = (unsigned long)q;                                                                                                              
    229                                                                                                                                                               
    230         //                                                                                                                                                    
    231          * by default assume old behaviour and bounce for any highmem page                                                                                    
    232          //                                                                                                                                                   
    233         blk_queue_bounce_limit(q, BLK_BOUNCE_HIGH);                                                                                                           
    234 }                                                                                                                                                             
// �����ص��ע������unplug��Ϊ���ֵĳ�Ա.������INIT_WORK,��ʹ��һ��unplug_work����                                                                                      
// ������ִ��,blk_unplug_work ��������ͻᱻִ��.�� unplug_timer ��ôһ��ֵ,���Ǿ�֪��,                                                                                  
// һ����������,һ������ʱ�䵽��,blk_unplug_timeout ��������ͻᱻִ��.������Ϊ������                                                                                    
// ���� unplug_delay Ϊ 3ms,ʹ�����ӵ� timeout ���� 3ms,һ����������,3ms ֮��                                                                                            
// blk_unplug_timeout �ͻᱻִ��.����������� block/ll_rw_blk.c:                                                                                                         
   1646 static void blk_unplug_timeout(unsigned long data)                                                                                                            
   1647 {                                                                                                                                                             
   1648         request_queue_t *q = (request_queue_t *)data;                                                                                                         
   1649                                                                                                                                                               
   1650         blk_add_trace_pdu_int(q, BLK_TA_UNPLUG_TIMER, NULL,                                                                                                   
   1651                                 q->rq.count[READ] + q->rq.count[WRITE]);                                                                                      
   1652                                                                                                                                                               
   1653         kblockd_schedule_work(&q->unplug_work);                                                                                                               
   1654 }                                                                                                                                                             
// ���Կ���,��ʵ����ִ�� kblockd_schedule_work,����֮,���������õĺ�������                                                                                               
// blk_unplug_work().                                                                                                                                                    
   1636 static void blk_unplug_work(struct work_struct *work)                                                                                                         
   1637 {                                                                                                                                                             
   1638         request_queue_t *q = container_of(work, request_queue_t, unplug_work);                                                                                
   1639                                                                                                                                                               
   1640         blk_add_trace_pdu_int(q, BLK_TA_UNPLUG_IO, NULL,                                                                                                      
   1641                                 q->rq.count[READ] + q->rq.count[WRITE]);                                                                                      
   1642                                                                                                                                                               
   1643         q->unplug_fn(q);                                                                                                                                      
   1644 }                                                                                                                                                             
// ���ղ�����˵��,unplug_fn �������� generic_unplug_device.��������Ҫִ�е���                                                                                            
// generic_unplug_device.����������ֳ���ʲô����?                                                                                                                       
//    1601 ///                                                                                                                                                           
//    1602  * generic_unplug_device - fire a request queue                                                                                                               
//    1603  * @q:    The &request_queue_t in question                                                                                                                    
//    1604  *                                                                                                                                                            
//    1605  * Description:                                                                                                                                               
//    1606  *   Linux uses plugging to build bigger requests queues before letting Linux  ��Щ�¶�֮���� Block��                                                         
// �� 84  ҳ �� 117  ҳ                                                                                                                                                  
//    1607  *   the device have at them. If a queue is plugged, the I/O scheduler                                                                                        
//    1608  *   is still adding and merging requests on the queue. Once the queue                                                                                        
//    1609  *   gets unplugged, the request_fn defined for the queue is invoked and                                                                                      
//    1610  *   transfers started.                                                                                                                                       
   1611  ///                                                                                                                                                          
   1612 void generic_unplug_device(request_queue_t *q)                                                                                                                
   1613 {                                                                                                                                                             
   1614         spin_lock_irq(q->queue_lock);                                                                                                                         
   1615         __generic_unplug_device(q);                                                                                                                           
   1616         spin_unlock_irq(q->queue_lock);                                                                                                                       
   1617 }                                                                                                                                                             
// Ŷ,ŤŤ��������,��ʵ���ǵ���__generic_unplug_device.���ع�ͷȥ���������,����֪��,                                                                                  
// ��Ҳ�޷Ǿ��ǵ�������������,blk_remove_plug �� request_fn.���������ǻ����Ͼ�������.��                                                                                  
// ��һ�¾���:                                                                                                                                                           
// 1.        blk_plug_device()�������.                                                                                                                                  
// 2.        blk_remove_plug()������.                                                                                                                                  
// 3.         ���ǽ����ⶫ����,Ҳ����ʱ�����Ƶ�,�Ͼ������־������ش�Ҳ�Ƕ�ʱ���,һ                                                                                  
// ���бϾ������ʱ�仹�ǵñ�֤��·��ͨ.�����ڽ��ϵ�ʱ��,����һ����ʱ��,unplug_timer,                                                                                    
// (�� mod_timer),һ��ʱ�䵽�˾��Զ�ִ�� blk_remove_plug ȥ���.                                                                                                         
// 4.         ���ڽ����ʱ��Ͳ�Ҫ���ǰ������ʱ�����ص�.(�� del_timer)                                                                                                  
// 5.         ���֮����� request_fn()��ʼ��������е���һ������,����˵������ʼ�ָ�ǰ��.                                                                                
// Ok,�������Ǿ������������������������ĺ�����.���,���⻰,����unplug��plug,�Ҿ���                                                                                     
// �����еĵ����� activate�� deactivate,����˵�����붳��,���߼򵥵�˵,�����.                                                                                            
//                                                                                                                                                                       
// scsi �����ǰ������(��)                                                                                                                                               
//                                                                                                                                                                       
// ��Ȼ,while ѭ������Ҳ��������Ϊ 1453 �е��������ж�.���� req ���û����,��һ���ÿ�                                                                                    
// scsi_dev_queue_ready()�ķ���ֵ,�������ֵΪ 0,��ô break Ҳ�ᱻִ��,�Ӷ�����ѭ��.                                                                                     
   1270 //                                                                                                                                                            
   1271  * scsi_dev_queue_ready: if we can send requests to sdev, return 1 else                                                                                       
   1272  * return 0.                                                                                                                                                  
   1273  *                                                                                                                                                            
   1274  * Called with the queue_lock held.                                                                                                                           
   1275  //                                                                                                                                                           
   1276 static inline int scsi_dev_queue_ready(struct request_queue *q,                                                                                               
   1277                                   struct scsi_device *sdev)                                                                                                   
   1278 {                                                                                                                                                             
   1279         if (sdev->device_busy >= sdev->queue_depth)                                                                                                           
   1280                 return 0;                                                                                                                                     
   1281         if (sdev->device_busy == 0 && sdev->device_blocked) {                                                                                                 
   1282                 // Linux  ��Щ�¶�֮���� Block��                                                                                                              
�� 85  ҳ �� 117  ҳ                                                                                                                                                  
   1283                  * unblock after device_blocked iterates to zero                                                                                              
   1284                  //                                                                                                                                           
   1285                  if (--sdev->device_blocked == 0) {                                                                                                           
   1286                         SCSI_LOG_MLQUEUE(3,                                                                                                                   
   1287                                    sdev_printk(KERN_INFO, sdev,                                                                                               
   1288                                    "unblocking device at zero depth\n"));                                                                                     
   1289                 } else {                                                                                                                                      
   1290                         blk_plug_device(q);                                                                                                                   
   1291                         return 0;                                                                                                                             
   1292                 }                                                                                                                                             
   1293         }                                                                                                                                                     
   1294         if (sdev->device_blocked)                                                                                                                             
   1295                 return 0;                                                                                                                                     
   1296                                                                                                                                                               
   1297         return 1;                                                                                                                                             
   1298 }                                                                                                                                                             
// ������Ҫ�жϵ��� device_busy.��� flag ���������,˵����������ִ����,����˵�����Ѿ�                                                                                   
// ���ݵ��˵ײ�����.���,�����ڵ��� scsi_dispatch_cmd ֮ǰ������ device_busy,��1469��.                                                                                   
// ��һ�� flag �� device_blocked.��� flag �Ǹ�����������豸�����ٽ����µ�������,��Ϊ��                                                                                 
// ʮ�а˾������ڴ�������.������������ flag ��ֵΪ 0.����������� scsi_queue_insert()��                                                                                
// ��.������ʾһ��,scsi �豸����� flag ���ṩ�� sysfs �Ľӿڵ�,������ǿ���ͨ�� sysfs �Ľ�                                                                              
// �ڿ�һ���豸�����ֵ,�����о������� scsi �豸�����������ֵ,���Կ������� 0,Ӧ��˵��                                                                                   
// �����ĳ�̬.                                                                                                                                                           
// [root@localhost ~]# ls /sys/bus/scsi/devices/                                                                                                                         
// 0:0:8:0/ 0:2:0:0/ 1:0:0:0/ 2:0:0:0/                                                                                                                                   
// [root@localhost ~]# ls /sys/bus/scsi/devices/2\:0\:0\:0/                                                                                                              
// block:sdb/  iocounterbits        modalias             rev                  subsystem/                                                                                 
// bus/  iodone_cnt          model                scsi_device:2:0:0:0/ timeout delete                                                                                    
// ioerr_cnt   queue_depth          scsi_disk:2:0:0:0/   type device_blocked                                                                                             
// iorequest_cnt        queue_type           scsi_level           uevent driver/                                                                                         
// max_sectors     rescan           state                vendor                                                                                                          
// [root@localhost ~]# cat /sys/bus/scsi/devices/2\:0\:0\:0/device_blocked                                                                                               
// 0                                                                                                                                                                     
// [root@localhost ~]# cat /sys/bus/scsi/devices/0\:0\:8\:0/device_blocked                                                                                               
// 0                                                                                                                                                                     
// �������������,scsi_dev_queue_ready()�����ķ���ֵ���� 1,��һ��������ע����˵������.                                                                                   
// ������ν�ĳ�̬,ָ���ǵ���ִ��һ������,���Ҫִ�ж������,����˵�����ύ�˶��                                                                                         
// request,��ô device_busy �ͻ�һ�δε��� 1469 ������,�Ӷ�ʹ�� device_busy �п��ܽ�����                                                                                 
// queue_depth,������ scsi_dev_queue_ready()�ͻ᷵�� 0,�Ӷ� scsi_request_fn()���п��ܽ���,                                                                               
// ��֮�� ,__generic_unplug_device Ҳ������ , ֮�� blk_execute_rq_nowait() ���� , �ص�                                                                                   
// blk_execute_rq()��,ִ�� wait_for_completion(),���Ǿ�˯����,�ȴ���,������Ϸ����,����Ӧ��                                                                               
// ���ҵ�һ�� complete()�����������,��ô���������������?���� blk_end_sync_rq.                                                                                        
// ���ѡ���ʧ��ʧ�ߡ��ǳ�����������ô֪����.˵������,���ǵ����ǵ�ʱ�� usb-storage ��˵                                                                                 
// ���Ǹ�scsi_doneô?����ִ�����˾ͻ�call scsi_done.��scsi_done����drivers/scsi/scsi.c,����Linux  ��Щ�¶�֮���� Block��                                                 
// �� 86  ҳ �� 117  ҳ                                                                                                                                                  
// Ȼ������������ǵ�ͻ�ƿ�,�����ҵ�����������ͺñȹ����ҵ��˸�־��,�ͺñ�����֥                                                                                      
// �ҵ���������:                                                                                                                                                         
//     608 ///                                                                                                                                                           
//     609  * scsi_done - Enqueue the finished SCSI command into the done queue.                                                                                         
//     610  * @cmd: The SCSI Command for which a low-level device driver (LLDD) gives                                                                                    
//     611  * ownership back to SCSI Core -- i.e. the LLDD has finished with it.                                                                                         
//     612  *                                                                                                                                                            
//     613  * This function is the mid-level's (SCSI Core) interrupt routine, which                                                                                      
//     614  * regains ownership of the SCSI command (de facto) from a LLDD, and enqueues                                                                                 
//     615  * the command to the done queue for further processing.                                                                                                      
//     616  *                                                                                                                                                            
//     617  * This is the producer of the done queue who enqueues at the tail.                                                                                           
//     618  *                                                                                                                                                            
//     619  * This function is interrupt context safe.                                                                                                                   
//     620  //                                                                                                                                                           
    621 static void scsi_done(struct scsi_cmnd *cmd)                                                                                                                  
    622 {                                                                                                                                                             
//     623         //                                                                                                                                                    
//     624          * We don't have to worry about this one timing out any more.                                                                                         
//     625          * If we are unable to remove the timer, then the command                                                                                             
//     626          * has already timed out.  In which case, we have no choice but to                                                                                    
//     627          * let the timeout function run, as we have no idea where in fact                                                                                     
//     628          * that function could really be.  It might be on another processor,                                                                                  
//     629          * etc, etc.                                                                                                                                          
//     630          //                                                                                                                                                   
    631         if (!scsi_delete_timer(cmd))                                                                                                                          
    632                 return;                                                                                                                                       
    633         __scsi_done(cmd);                                                                                                                                     
    634 }                                                                                                                                                             
���������������ͬһ�ļ���__scsi_done,                                                                                                                                
    636 // Private entry to scsi_done() to complete a command when the timer                                                                                          
    637  * isn't running --- used by scsi_times_out //                                                                                                                
    638 void __scsi_done(struct scsi_cmnd *cmd)                                                                                                                       
    639 {                                                                                                                                                             
    640         struct request *rq = cmd->request;                                                                                                                    
    641                                                                                                                                                               
    642         //                                                                                                                                                    
    643          * Set the serial numbers back to zero                                                                                                                
    644          //                                                                                                                                                   
    645         cmd->serial_number = 0;                                                                                                                               
    646                                                                                                                                                               
    647         atomic_inc(&cmd->device->iodone_cnt);                                                                                                                 
    648         if (cmd->result)                                                                                                                                      
    649                 atomic_inc(&cmd->device->ioerr_cnt); Linux  ��Щ�¶�֮���� Block��                                                                            
�� 87  ҳ �� 117  ҳ                                                                                                                                                  
    650                                                                                                                                                               
    651         BUG_ON(!rq);                                                                                                                                          
    652                                                                                                                                                               
//    653         //                                                                                                                                                    
//    654          * The uptodate/nbytes values don't matter, as we allow partial                                                                                       
//    655          * completes and thus will check this in the softirq callback                                                                                         
    656          //                                                                                                                                                   
    657         rq->completion_data = cmd;                                                                                                                            
    658         blk_complete_request(rq);                                                                                                                             
    659 }                                                                                                                                                             
//������Ƕ�������,�͹��������� blk_complete_request().                                                                                                               
//   3588 ///                                                                                                                                                           
//   3589  * blk_complete_request - end I/O on a request                                                                                                                
//   3590  * @req:      the request being processed                                                                                                                     
//   3591  *                                                                                                                                                            
//   3592  * Description:                                                                                                                                               
//   3593  *     Ends all I/O on a request. It does not handle partial completions,                                                                                     
//   3594  *     unless the driver actually implements this in its completion callback                                                                                  
//   3595  *     through requeueing. Theh actual completion happens out-of-order,                                                                                       
//   3596  *     through a softirq handler. The user must have registered a completion                                                                                  
//   3597  *     callback through blk_queue_softirq_done().                                                                                                             
//   3598  ///                                                                                                                                                          
   3599                                                                                                                                                               
   3600 void blk_complete_request(struct request *req)                                                                                                                
   3601 {                                                                                                                                                             
   3602         struct list_head *cpu_list;                                                                                                                           
   3603         unsigned long flags;                                                                                                                                  
   3604                                                                                                                                                               
   3605         BUG_ON(!req->q->softirq_done_fn);                                                                                                                     
   3606                                                                                                                                                               
   3607         local_irq_save(flags);                                                                                                                                
   3608                                                                                                                                                               
   3609         cpu_list = &__get_cpu_var(blk_cpu_done);                                                                                                              
   3610         list_add_tail(&req->donelist, cpu_list);                                                                                                              
   3611         raise_softirq_irqoff(BLOCK_SOFTIRQ);                                                                                                                  
   3612                                                                                                                                                               
   3613         local_irq_restore(flags);                                                                                                                             
//   3614 }                                                                                                                                                             
//���������ǲ���,�͹�һ�����raise_softirq_irqoff().�ںܾúܾ���ǰ,��һ������,�������ֽ�                                                                                
//�� blk_dev_init().��������������µ���Դ.�������������������������ôһ��,                                                                                            
//   3720         open_softirq(BLOCK_SOFTIRQ, blk_done_softirq, NULL);                                                                                                  
//��ʱ���Ǿ�˵��,�������ľ��ǳ�ʼ����һ��softirq,��BLOCK_SOFTIRQ.���Ұ���softirq                                                                                      
//���� blk_done_softirq,��Ҫ����������ж�,���ǵ�ʱҲ˵��,ֻҪ���� raise_softirq_irqoff()��                                                                             
//��.������������Ҳ����������.��Ҳ����ζ��,blk_done_softirq�ᱻ����. Linux  ��Щ�¶�֮���� Block��                                                                      
//�� 88  ҳ �� 117  ҳ                                                                                                                                                  
   3542 //                                                                                                                                                            
   3543  * splice the completion data to a local structure and hand off to                                                                                            
   3544  * process_completion_queue() to complete the requests                                                                                                        
   3545  //                                                                                                                                                           
   3546 static void blk_done_softirq(struct softirq_action *h)                                                                                                        
   3547 {                                                                                                                                                             
   3548         struct list_head *cpu_list, local_list;                                                                                                               
   3549                                                                                                                                                               
   3550         local_irq_disable();                                                                                                                                  
   3551         cpu_list = &__get_cpu_var(blk_cpu_done);                                                                                                              
   3552         list_replace_init(cpu_list, &local_list);                                                                                                             
   3553         local_irq_enable();                                                                                                                                   
   3554                                                                                                                                                               
   3555         while (!list_empty(&local_list)) {                                                                                                                    
   3556                 struct request *rq = list_entry(local_list.next, struct request,                                                                              
donelist);                                                                                                                                                            
   3557                                                                                                                                                               
   3558                 list_del_init(&rq->donelist);                                                                                                                 
   3559                  rq->q->softirq_done_fn(rq);                                                                                                                  
   3560         }                                                                                                                                                     
   3561 }                                                                                                                                                             
// ����� softirq_done_fn ��ʲô��?��Ҫ˵�㲻֪��,��ʵ����Ҳ����.����������Ҳ��Ҫ��,��                                                                                   
// ���ķ��ձ��Ǽ���̫��,�����������׿���.�� scsi_alloc_queue ��,���ǵ���                                                                                               
// blk_queue_softirq_done �� scsi_softirq_done ������ q->softirq_done_fn,���Ե�������,������                                                                             
// �ľ��� scsi_softirq_done.                                                                                                                                             
   1376 static void scsi_softirq_done(struct request *rq)                                                                                                             
   1377 {                                                                                                                                                             
   1378         struct scsi_cmnd *cmd = rq->completion_data;                                                                                                          
   1379         unsigned long wait_for = (cmd->allowed + 1) * cmd->timeout_per_command;                                                                               
   1380         int disposition;                                                                                                                                      
   1381                                                                                                                                                               
   1382         INIT_LIST_HEAD(&cmd->eh_entry);                                                                                                                       
   1383                                                                                                                                                               
   1384         disposition = scsi_decide_disposition(cmd);                                                                                                           
   1385         if (disposition != SUCCESS &&                                                                                                                         
   1386             time_before(cmd->jiffies_at_alloc + wait_for, jiffies)) {                                                                                         
   1387                 sdev_printk(KERN_ERR, cmd->device,                                                                                                            
   1388                             "timing out command, waited %lus\n",                                                                                              
   1389                             wait_for/HZ);                                                                                                                     
   1390                 disposition = SUCCESS;                                                                                                                        
   1391         }                                                                                                                                                     
   1392                                                                                                                                                               
   1393         scsi_log_completion(cmd, disposition);                                                                                                                
   1394 Linux  ��Щ�¶�֮���� Block��                                                                                                                                 
�� 89  ҳ �� 117  ҳ                                                                                                                                                  
   1395         switch (disposition) {                                                                                                                                
   1396                 case SUCCESS:                                                                                                                                 
   1397                         scsi_finish_command(cmd);                                                                                                             
   1398                         break;                                                                                                                                
   1399                 case NEEDS_RETRY:                                                                                                                             
   1400                         scsi_queue_insert(cmd, SCSI_MLQUEUE_EH_RETRY);                                                                                        
   1401                         break;                                                                                                                                
   1402                 case ADD_TO_MLQUEUE:                                                                                                                          
   1403                         scsi_queue_insert(cmd,                                                                                                                
SCSI_MLQUEUE_DEVICE_BUSY);                                                                                                                                            
   1404                         break;                                                                                                                                
   1405                 default:                                                                                                                                      
   1406                         if (!scsi_eh_scmd_add(cmd, 0))                                                                                                        
   1407                                 scsi_finish_command(cmd);                                                                                                     
   1408         }                                                                                                                                                     
   1409 }                                                                                                                                                             
//�����Ҷ�˵,��Ҳ֪��,scsi_softirq_done����� scsi_finish_command,���� drivers/scsi/scsi.c:                                                                             
//    661 //                                                                                                                                                            
//    662  * Function:    scsi_finish_command                                                                                                                           
//    663  *                                                                                                                                                            
//    664  * Purpose:     Pass command off to upper layer for finishing of I/O                                                                                          
//    665  *              request, waking processes that are waiting on results,                                                                                        
//    666  *              etc.                                                                                                                                          
//    667  //                                                                                                                                                           
    668 void scsi_finish_command(struct scsi_cmnd *cmd)                                                                                                               
    669 {                                                                                                                                                             
    670         struct scsi_device *sdev = cmd->device;                                                                                                               
    671         struct Scsi_Host *shost = sdev->host;                                                                                                                 
    672                                                                                                                                                               
    673         scsi_device_unbusy(sdev);                                                                                                                             
    674                                                                                                                                                               
    675         //                                                                                                                                                    
    676          * Clear the flags which say that the device/host is no longer                                                                                        
    677          * capable of accepting new commands.  These are set in scsi_queue.c                                                                                  
    678          * for both the queue full condition on a device, and for a                                                                                           
    679          * host full condition on the host.                                                                                                                   
    680          *                                                                                                                                                    
    681          * XXX(hch): What about locking?                                                                                                                      
    682          //                                                                                                                                                   
    683         shost->host_blocked = 0;                                                                                                                              
    684         sdev->device_blocked = 0;                                                                                                                             
    685                                                                                                                                                               
    686         //                                                                                                                                                    
    687          * If we have valid sense information, then some kind of recovery Linux  ��Щ�¶�֮���� Block��                                                       
�� 90  ҳ �� 117  ҳ                                                                                                                                                  
    688          * must have taken place.  Make a note of this.                                                                                                       
    689          //                                                                                                                                                   
    690         if (SCSI_SENSE_VALID(cmd))                                                                                                                            
    691                 cmd->result |= (DRIVER_SENSE << 24);                                                                                                          
    692                                                                                                                                                               
    693         SCSI_LOG_MLCOMPLETE(4, sdev_printk(KERN_INFO, sdev,                                                                                                   
    694                                 "Notifying upper driver of completion "                                                                                       
    695                                 "(result %x)\n", cmd->result));                                                                                               
    696                                                                                                                                                               
    697         cmd->done(cmd);                                                                                                                                       
    698 }                                                                                                                                                             
//Ҳ����˵,cmd->done �ᱻ����,�Ӷ�������Ļ������ scsi_blk_pc_done �ᱻ����.��Ϊ,����                                                                                  
//�� scsi_setup_blk_pc_cmnd()������ôһ��,                                                                                                                              
//   1135         cmd->done = scsi_blk_pc_done;                                                                                                                         
//�� scsi_blk_pc_done ����drivers/scsi/scsi_lib.c:                                                                                                                      
   1078 static void scsi_blk_pc_done(struct scsi_cmnd *cmd)                                                                                                           
   1079 {                                                                                                                                                             
   1080         BUG_ON(!blk_pc_request(cmd->request));                                                                                                                
   1081         //                                                                                                                                                    
   1082          * This will complete the whole command with uptodate=1 so                                                                                            
   1083          * as far as the block layer is concerned the command completed                                                                                       
   1084          * successfully. Since this is a REQ_BLOCK_PC command the                                                                                             
   1085          * caller should check the request's errors value                                                                                                     
   1086          //                                                                                                                                                   
   1087         scsi_io_completion(cmd, cmd->request_bufflen);                                                                                                        
   1088 }                                                                                                                                                             
//���� drivers/scsi/scsi_lib.c:                                                                                                                                         
//    789 //                                                                                                                                                            
//    790  * Function:    scsi_io_completion()                                                                                                                          
//    791  *                                                                                                                                                            
//    792  * Purpose:     Completion processing for block device I/O requests.                                                                                          
//    793  *                                                                                                                                                            
//    794  * Arguments:   cmd   - command that is finished.                                                                                                             
//    795  *                                                                                                                                                            
//    796  * Lock status: Assumed that no lock is held upon entry.                                                                                                      
//    797  *                                                                                                                                                            
//    798  * Returns:     Nothing                                                                                                                                       
//    799  *                                                                                                                                                            
//    800  * Notes:       This function is matched in terms of capabilities to                                                                                          
//    801  *              the function that created the scatter-gather list.                                                                                            
//    802  *              In other words, if there are no bounce buffers                                                                                                
//    803  *              (the normal case for most drivers), we don't need                                                                                             
//    804  *              the logic to deal with cleaning up afterwards.                                                                                                
//    805  * Linux  ��Щ�¶�֮���� Block��                                                                                                                              
//�� 91  ҳ �� 117  ҳ                                                                                                                                                  
//    806  *              We must do one of several things here:                                                                                                        
//    807  *                                                                                                                                                            
//    808  *              a) Call scsi_end_request.  This will finish off the                                                                                           
//    809  *                 specified number of sectors.  If we are done, the                                                                                          
//    810  *                 command block will be released, and the queue                                                                                              
//    811  *                 function will be goosed.  If we are not done, then                                                                                         
//    812  *                 scsi_end_request will directly goose the queue.                                                                                            
//    813  *                                                                                                                                                            
//    814  *              b) We can just use scsi_requeue_command() here.  This would                                                                                   
//    815  *                 be used if we just wanted to retry, for example.                                                                                           
    816  //                                                                                                                                                           
    817 void scsi_io_completion(struct scsi_cmnd *cmd, unsigned int good_bytes)                                                                                       
    818 {                                                                                                                                                             
    819         int result = cmd->result;                                                                                                                             
    820         int this_count = cmd->request_bufflen;                                                                                                                
    821         request_queue_t *q = cmd->device->request_queue;                                                                                                      
    822         struct request *req = cmd->request;                                                                                                                   
    823         int clear_errors = 1;                                                                                                                                 
    824         struct scsi_sense_hdr sshdr;                                                                                                                          
    825         int sense_valid = 0;                                                                                                                                  
    826         int sense_deferred = 0;                                                                                                                               
    827                                                                                                                                                               
    828         scsi_release_buffers(cmd);                                                                                                                            
    829                                                                                                                                                               
    830         if (result) {                                                                                                                                         
    831                 sense_valid = scsi_command_normalize_sense(cmd, &sshdr);                                                                                      
    832                 if (sense_valid)                                                                                                                              
    833                         sense_deferred = scsi_sense_is_deferred(&sshdr);                                                                                      
    834         }                                                                                                                                                     
    835                                                                                                                                                               
    836         if (blk_pc_request(req)) { // SG_IO ioctl from block level //                                                                                         
    837                 req->errors = result;                                                                                                                         
    838                 if (result) {                                                                                                                                 
    839                         clear_errors = 0;                                                                                                                     
    840                         if (sense_valid && req->sense) {                                                                                                      
    841                                 //                                                                                                                            
    842                                  * SG_IO wants current and deferred errors                                                                                    
    843                                  //                                                                                                                           
    844                                 int len = 8 + cmd->sense_buffer[7];                                                                                           
    845                                                                                                                                                               
    846                                 if (len > SCSI_SENSE_BUFFERSIZE)                                                                                              
    847                                         len = SCSI_SENSE_BUFFERSIZE;                                                                                          
    848                                 memcpy(req->sense, cmd->sense_buffer,  len);                                                                                  
    849                                 req->sense_len = len; Linux  ��Щ�¶�֮���� Block��                                                                           
�� 92  ҳ �� 117  ҳ                                                                                                                                                  
    850                         }                                                                                                                                     
    851                 }                                                                                                                                             
    852                 req->data_len = cmd->resid;                                                                                                                   
    853         }                                                                                                                                                     
    854                                                                                                                                                               
    855         //                                                                                                                                                    
    856          * Next deal with any sectors which we were able to correctly                                                                                         
    857          * handle.                                                                                                                                            
    858          //                                                                                                                                                   
    859         SCSI_LOG_HLCOMPLETE(1, printk("%ld sectors total, "                                                                                                   
    860                                       "%d bytes done.\n",                                                                                                     
    861                                       req->nr_sectors, good_bytes));                                                                                          
    862         SCSI_LOG_HLCOMPLETE(1, printk("use_sg is %d\n", cmd->use_sg));                                                                                        
    863                                                                                                                                                               
    864         if (clear_errors)                                                                                                                                     
    865                 req->errors = 0;                                                                                                                              
    866                                                                                                                                                               
    867         // A number of bytes were successfully read.  If there                                                                                                
    868          * are leftovers and there is some kind of error                                                                                                      
    869          * (result != 0), retry the rest.                                                                                                                     
    870          //                                                                                                                                                   
871         if (scsi_end_request(cmd, 1, good_bytes, result == 0) == NULL)                                                                                            
    872                 return;                                                                                                                                       
    873                                                                                                                                                               
    874         // good_bytes = 0, or (inclusive) there were leftovers and                                                                                            
    875          * result = 0, so scsi_end_request couldn't retry.                                                                                                    
    876          //                                                                                                                                                   
    877         if (sense_valid && !sense_deferred) {                                                                                                                 
    878                 switch (sshdr.sense_key) {                                                                                                                    
    879                 case UNIT_ATTENTION:                                                                                                                          
    880                         if (cmd->device->removable) {                                                                                                         
    881                                 // Detected disc change.  Set a bit                                                                                           
    882                                  * and quietly refuse further access.                                                                                         
    883                                  //                                                                                                                           
    884                                 cmd->device->changed = 1;                                                                                                     
    885                                 scsi_end_request(cmd, 0, this_count, 1);                                                                                      
    886                                 return;                                                                                                                       
    887                         } else {                                                                                                                              
    888                                 // Must have been a power glitch, or a                                                                                        
    889                                  * bus reset.  Could not have been a                                                                                          
    890                                  * media change, so we just retry the                                                                                         
    891                                  * request and see what happens.                                                                                              
    892                                  //                                                                                                                           
    893                                 scsi_requeue_command(q, cmd); Linux  ��Щ�¶�֮���� Block��                                                                   
�� 93  ҳ �� 117  ҳ                                                                                                                                                  
    894                                 return;                                                                                                                       
    895                         }                                                                                                                                     
    896                         break;                                                                                                                                
    897                 case ILLEGAL_REQUEST:                                                                                                                         
    898                         // If we had an ILLEGAL REQUEST returned, then                                                                                        
    899                          * we may have performed an unsupported                                                                                               
    900                          * command.  The only thing this should be                                                                                            
    901                          * would be a ten byte read where only a six                                                                                          
    902                          * byte read was supported.  Also, on a system                                                                                        
    903                          * where READ CAPACITY failed, we may have                                                                                            
    904                          * read past the end of the disk.                                                                                                     
    905                          //                                                                                                                                   
    906                         if ((cmd->device->use_10_for_rw &&                                                                                                    
    907                             sshdr.asc == 0x20 && sshdr.ascq == 0x00) &&                                                                                       
    908                             (cmd->cmnd[0] == READ_10 ||                                                                                                       
    909                              cmd->cmnd[0] == WRITE_10)) {                                                                                                     
    910                                 cmd->device->use_10_for_rw = 0;                                                                                               
    911                                 // This will cause a retry with a                                                                                             
912                                  * 6-byte command.                                                                                                                
    913                                  //                                                                                                                           
    914                                 scsi_requeue_command(q, cmd);                                                                                                 
    915                                 return;                                                                                                                       
    916                         } else {                                                                                                                              
    917                                 scsi_end_request(cmd, 0, this_count, 1);                                                                                      
    918                                 return;                                                                                                                       
    919                         }                                                                                                                                     
    920                         break;                                                                                                                                
    921                 case NOT_READY:                                                                                                                               
    922                         // If the device is in the process of becoming                                                                                        
    923                          * ready, or has a temporary blockage, retry.                                                                                         
    924                          //                                                                                                                                   
    925                         if (sshdr.asc == 0x04) {                                                                                                              
    926                                 switch (sshdr.ascq) {                                                                                                         
    927                                 case 0x01: // becoming ready //                                                                                               
    928                                 case 0x04: // format in progress //                                                                                           
    929                                 case 0x05: // rebuild in progress //                                                                                          
    930                                 case 0x06: // recalculation in progress //                                                                                    
    931                                 case 0x07: // operation in progress //                                                                                        
    932                                 case 0x08: // Long write in progress //                                                                                       
    933                                 case 0x09: // self test in progress //                                                                                        
    934                                         scsi_requeue_command(q, cmd);                                                                                         
    935                                         return;                                                                                                               
    936                                 default:                                                                                                                      
    937                                         break; Linux  ��Щ�¶�֮���� Block��                                                                                  
�� 94  ҳ �� 117  ҳ                                                                                                                                                  
    938                                 }                                                                                                                             
    939                         }                                                                                                                                     
    940                         if (!(req->cmd_flags & REQ_QUIET)) {                                                                                                  
    941                                 scmd_printk(KERN_INFO, cmd,                                                                                                   
    942                                             "Device not ready: ");                                                                                            
    943                                 scsi_print_sense_hdr("", &sshdr);                                                                                             
    944                         }                                                                                                                                     
    945                         scsi_end_request(cmd, 0, this_count, 1);                                                                                              
    946                         return;                                                                                                                               
    947                 case VOLUME_OVERFLOW:                                                                                                                         
    948                         if (!(req->cmd_flags & REQ_QUIET)) {                                                                                                  
    949                                 scmd_printk(KERN_INFO, cmd,                                                                                                   
    950                                             "Volume overflow, CDB: ");                                                                                        
    951                                 __scsi_print_command(cmd->cmnd);                                                                                              
    952                                 scsi_print_sense("", cmd);                                                                                                    
    953                         }                                                                                                                                     
    954                         // See SSC3rXX or current. //                                                                                                         
    955                         scsi_end_request(cmd, 0, this_count, 1);                                                                                              
    956                         return;                                                                                                                               
    957                 default:                                                                                                                                      
    958                         break;                                                                                                                                
    959                 }                                                                                                                                             
    960         }                                                                                                                                                     
    961         if (host_byte(result) == DID_RESET) {                                                                                                                 
    962                 // Third party bus reset or reset for error recovery                                                                                          
    963                  * reasons.  Just retry the request and see what                                                                                              
    964                  * happens.                                                                                                                                   
    965                  //                                                                                                                                           
    966                 scsi_requeue_command(q, cmd);                                                                                                                 
    967                 return;                                                                                                                                       
    968         }                                                                                                                                                     
    969         if (result) {                                                                                                                                         
    970                 if (!(req->cmd_flags & REQ_QUIET)) {                                                                                                          
    971                         scsi_print_result(cmd);                                                                                                               
    972                         if (driver_byte(result) & DRIVER_SENSE)                                                                                               
    973                                 scsi_print_sense("", cmd);                                                                                                    
    974                 }                                                                                                                                             
    975         }                                                                                                                                                     
    976         scsi_end_request(cmd, 0, this_count, !result);                                                                                                        
    977 }                                                                                                                                                             
//����һ�����˷�ָ�ĺ���.����ʲô�������˵��.ֱ���������һ��,scsi_end_request().����                                                                                  
//drivers/scsi_lib.c:                                                                                                                                                   
//    632 //                                                                                                                                                            
//    633  * Function:    scsi_end_request() Linux  ��Щ�¶�֮���� Block��                                                                                              
//�� 95  ҳ �� 117  ҳ                                                                                                                                                  
//    634  *                                                                                                                                                            
//    635  * Purpose:     Post-processing of completed commands (usually invoked at end                                                                                 
//    636  *              of upper level post-processing and scsi_io_completion).                                                                                       
//    637  *                                                                                                                                                            
//    638  * Arguments:   cmd      - command that is complete.                                                                                                          
//    639  *              uptodate - 1 if I/O indicates success, <= 0 for I/O error.                                                                                    
//    640  *              bytes    - number of bytes of completed I/O                                                                                                   
//    641  *              requeue  - indicates whether we should requeue leftovers.                                                                                     
//    642  *                                                                                                                                                            
//    643  * Lock status: Assumed that lock is not held upon entry.                                                                                                     
//    644  *                                                                                                                                                            
//    645  * Returns:     cmd if requeue required, NULL otherwise.                                                                                                      
//    646  *                                                                                                                                                            
//    647  * Notes:       This is called for block device requests in order to                                                                                          
//    648  *              mark some number of sectors as complete.                                                                                                      
//    649  *                                                                                                                                                            
//    650  *              We are guaranteeing that the request queue will be goosed                                                                                     
//    651  *              at some point during this call.                                                                                                               
//    652  * Notes:       If cmd was requeued, upon return it will be a stale pointer.                                                                                  
    653  //                                                                                                                                                           
    654 static struct scsi_cmnd *scsi_end_request(struct scsi_cmnd *cmd, int uptodate,                                                                                
    655                                           int bytes, int requeue)                                                                                             
    656 {                                                                                                                                                             
    657         request_queue_t *q = cmd->device->request_queue;                                                                                                      
    658         struct request *req = cmd->request;                                                                                                                   
    659         unsigned long flags;                                                                                                                                  
    660                                                                                                                                                               
    661         //                                                                                                                                                    
    662          * If there are blocks left over at the end, set up the command                                                                                       
    663          * to queue the remainder of them.                                                                                                                    
    664          //                                                                                                                                                   
    665         if (end_that_request_chunk(req, uptodate, bytes)) {                                                                                                   
    666                 int leftover = (req->hard_nr_sectors << 9);                                                                                                   
    667                                                                                                                                                               
    668                 if (blk_pc_request(req))                                                                                                                      
    669                         leftover = req->data_len;                                                                                                             
    670                                                                                                                                                               
    671                 // kill remainder if no retrys //                                                                                                             
    672                 if (!uptodate && blk_noretry_request(req))                                                                                                    
673                         end_that_request_chunk(req, 0, leftover);                                                                                                 
    674                 else {                                                                                                                                        
    675                         if (requeue) {                                                                                                                        
    676                                 //                                                                                                                            
    677                                  * Bleah.  Leftovers again.  Stick the Linux  ��Щ�¶�֮���� Block��                                                          
�� 96  ҳ �� 117  ҳ                                                                                                                                                  
    678                                  * leftovers in the front of the                                                                                              
    679                                  * queue, and goose the queue again.                                                                                          
    680                                  //                                                                                                                           
    681                                 scsi_requeue_command(q, cmd);                                                                                                 
    682                                 cmd = NULL;                                                                                                                   
    683                         }                                                                                                                                     
    684                         return cmd;                                                                                                                           
    685                 }                                                                                                                                             
    686         }                                                                                                                                                     
    687                                                                                                                                                               
    688         add_disk_randomness(req->rq_disk);                                                                                                                    
    689                                                                                                                                                               
    690         spin_lock_irqsave(q->queue_lock, flags);                                                                                                              
    691         if (blk_rq_tagged(req))                                                                                                                               
    692                 blk_queue_end_tag(q, req);                                                                                                                    
    693         end_that_request_last(req, uptodate);                                                                                                                 
    694         spin_unlock_irqrestore(q->queue_lock, flags);                                                                                                         
    695                                                                                                                                                               
    696         //                                                                                                                                                    
    697          * This will goose the queue request function at the end, so we don't                                                                                 
    698          * need to worry about launching another command.                                                                                                     
    699          //                                                                                                                                                   
    700         scsi_next_command(cmd);                                                                                                                               
    701         return NULL;                                                                                                                                          
    702 }                                                                                                                                                             
����������Ҫ���ĵ�,��693 �� end_that_request_last.                                                                                                                    
   3618 //                                                                                                                                                            
   3619  * queue lock must be held                                                                                                                                    
   3620  //                                                                                                                                                           
   3621 void end_that_request_last(struct request *req, int uptodate)                                                                                                 
   3622 {                                                                                                                                                             
   3623         struct gendisk *disk = req->rq_disk;                                                                                                                  
   3624         int error;                                                                                                                                            
   3625                                                                                                                                                               
   3626         //                                                                                                                                                    
   3627          * extend uptodate bool to allow < 0 value to be direct io error                                                                                      
   3628          //                                                                                                                                                   
   3629         error = 0;                                                                                                                                            
   3630         if (end_io_error(uptodate))                                                                                                                           
   3631                 error = !uptodate ? -EIO : uptodate;                                                                                                          
   3632                                                                                                                                                               
   3633         if (unlikely(laptop_mode) && blk_fs_request(req))                                                                                                     
   3634                 laptop_io_completion();                                                                                                                       
   3635 Linux  ��Щ�¶�֮���� Block��                                                                                                                                 
�� 97  ҳ �� 117  ҳ                                                                                                                                                  
   3636         //                                                                                                                                                    
   3637          * Account IO completion.  bar_rq isn't accounted as a normal                                                                                         
   3638          * IO on queueing nor completion.  Accounting the containing                                                                                          
   3639          * request is enough.                                                                                                                                 
   3640          //                                                                                                                                                   
   3641         if (disk && blk_fs_request(req) && req != &req->q->bar_rq) {                                                                                          
   3642                 unsigned long duration = jiffies - req->start_time;                                                                                           
   3643                 const int rw = rq_data_dir(req);                                                                                                              
   3644                                                                                                                                                               
   3645                 __disk_stat_inc(disk, ios[rw]);                                                                                                               
   3646                 __disk_stat_add(disk, ticks[rw], duration);                                                                                                   
   3647                 disk_round_stats(disk);                                                                                                                       
   3648                 disk->in_flight--;                                                                                                                            
   3649         }                                                                                                                                                     
   3650         if (req->end_io)                                                                                                                                      
   3651                  req->end_io(req, error);                                                                                                                     
   3652         else                                                                                                                                                  
   3653                 __blk_put_request(req->q, req);                                                                                                               
   3654 }                                                                                                                                                             
//����,3651 ����� end_io ����ؼ��Ĵ���.Ҳ������������������������ end_io,���ǲ�Ҫ��,                                                                                  
//������.�� blk_execute_rq_nowait()��,������һ��                                                                                                                        
//   2596         rq->end_io = done;                                                                                                                                    
//��done����������ĵ��ĸ�����.���������ڵ������������ʱ��,��blk_execute_rq��,����                                                                                     
//������д��:                                                                                                                                                           
//   2636         blk_execute_rq_nowait(q, bd_disk, rq, at_head, blk_end_sync_rq);                                                                                      
//Ҳ����˵,rq->end_io �������� blk_end_sync_rq.                                                                                                                         
//   2786 ///                                                                                                                                                           
//   2787  * blk_end_sync_rq - executes a completion event on a request                                                                                                 
//   2788  * @rq: request to complete                                                                                                                                   
//   2789  * @error: end io status of the request                                                                                                                       
   2790  //                                                                                                                                                           
   2791 void blk_end_sync_rq(struct request *rq, int error)                                                                                                           
   2792 {                                                                                                                                                             
   2793         struct completion *waiting = rq->end_io_data;                                                                                                         
   2794                                                                                                                                                               
   2795         rq->end_io_data = NULL;                                                                                                                               
   2796         __blk_put_request(rq->q, rq);                                                                                                                         
   2797                                                                                                                                                               
   2798         //                                                                                                                                                    
   2799          * complete last, if this is a stack request the process (and thus                                                                                    
   2800          * the rq pointer) could be invalid right after this complete()                                                                                       
   2801          //                                                                                                                                                   
   2802         complete(waiting);                                                                                                                                    
   2803 } Linux  ��Щ�¶�֮���� Block��                                                                                                                               
// �� 98  ҳ �� 117  ҳ                                                                                                                                                  
// ���������ҵ����װ��Ŀɰ����మ�������� complete().��ô���ȷ���� waiting ����                                                                                   
// �� wait ��?����һ����� waiting,��ʱ�� blk_execute_rq ��������:                                                                                                       
//    2635         rq->end_io_data = &wait;                                                                                                                              
// ��������������:                                                                                                                                                       
//    2793         struct completion *waiting = rq->end_io_data;                                                                                                         
// �ɴ˿�֪����û�и�����,�Ͼ�������֪,���ǿ��Ը�����,��Ƣ���򲻿���,д�������                                                                                      
// �Ӳ�����.                                                                                                                                                             
// ����,blk_execute_rq ������,Ȼ��Ѹ�ٷ���.���������� scsi_execute �ķ��غ�                                                                                            
// scsi_execute_req �ķ���.��һ��,һ�� scsi �������ڴ��޵������յ���,�������� scsi ���                                                                                
// request ���ɱ�,Ҳ������ request �� scsi ���������.���������������ʹ��.������˵,������                                                                               
// һ���þ�,�������������Ψһ�Ľ��.                                                                                                                                    
//                                                                                                                                                                       
// ��˵�е��ڴ�ӳ��(��)                                                                                                                                                  
// ���������л����������׳�������,�ܲ��ܲ�Ҫϴ��,�����Ȼ�ȥ֮������������,����ͬ��                                                                                     
// ��������������.�� 2007 �� 10 �� 17��,�μ�ʮ�ߴ�ĸ����������������ѧУУ���ƽ�����                                                                                   
// ��ת��ѧ��������.                                                                                                                                                     
// ���籩���Ƕ���һ�¼�������ǿ�ҵķ�̺����,Ȼ���Ҿ��ô�ɲ������,��ʵ��,ѧ����                                                                                       
// ���뷨���ƴ���,ʵ���̺���һ����̵�˼��,����� Linux �е��ڴ�ӳ���˼��.Linux �о�                                                                                    
// �������������,һ�����û��ռ�� buffer,һ�����ں˿ռ�� buffer,һ��������Ӧ�ó���,һ                                                                                  
// �������豸����,����ԭ��û����ϵ,����ֻ����Զ�����Ტ��,ֻ������Ĳ������,�ͷ·�                                                                                      
// ���ϵ�С���ˮ�����,Ҳ���������,��������������������?                                                                                                               
// �����һ����ķ�������ӳ��,���Ʋ�������������,ͨ��ӳ��,��ʹ�������й�ϵ��.����Ϊ                                                                                      
// ʲôҪ��ǰ�ߺͺ�����ϵ������?����Ұ� user buffer ���������е�ѧ��,���� kernel buffer                                                                                 
// �����ƽ���У��,��ô��ܿ����֪��,֮����ѧ��Ҫ�ͻ�У������,��������Ϊ��У����ô                                                                                       
// ����������,������Ϊ���������׳�������,��ô����˭���Ա����������׳���?��ϸһ���                                                                                       
// ֪��,�豸���������õ�?���������豸,û��,���������ǲ����豸����,�����豸.����,Ӧ��                                                                                     
// ����֮����Ը������� user buffer��kernel bufferӳ������,ǡǡ����Ϊ kernel buffer���豸                                                                                
// ��������ϵ.����,�� kernel buffer ����,����ͬ���豸����.                                                                                                               
// ������ Block �����������������.�������������� blk_rq_map_user �� blk_rq_map_kern.��                                                                                  
// �߶����� block/ll_rw_block.c.�����Ƿ��� sd ģ��ʱ,˵�� ioctl ʱ,�������ʵ���ϵ��õ���                                                                                
// sg_io(),�� sg_io()��������Ҫ���� blk_rq_map_user����,���������������������.                                                                                          
//    2394 ///                                                                                                                                                           
//    2395  * blk_rq_map_user - map user data to a request, for REQ_BLOCK_PC usage                                                                                       
//    2396  * @q:          request queue where request should be inserted                                                                                                
//    2397  * @rq:         request structure to fill                                                                                                                     
//    2398  * @ubuf:       the user buffer                                                                                                                               
//    2399  * @len:        length of user data                                                                                                                           
//    2400  *                                                                                                                                                            
//    2401  * Description:                                                                                                                                               
//    2402  *    Data will be mapped directly for zero copy io, if possible. Otherwise                                                                                   
//    2403  *    a kernel bounce buffer is used. Linux  ��Щ�¶�֮���� Block��                                                                                           
// �� 99  ҳ �� 117  ҳ                                                                                                                                                  
//    2404  *                                                                                                                                                            
//    2405  *    A matching blk_rq_unmap_user() must be issued at the end of io, while                                                                                   
//    2406  *    still in process context.                                                                                                                               
//    2407  *                                                                                                                                                            
//    2408  *    Note: The mapped bio may need to be bounced through blk_queue_bounce()                                                                                  
//    2409  *    before being submitted to the device, as pages mapped may be out of                                                                                     
//    2410  *    reach. It's the callers responsibility to make sure this happens. The                                                                                   
//    2411  *    original bio must be passed back in to blk_rq_unmap_user() for proper                                                                                   
//    2412  *    unmapping.                                                                                                                                              
//    2413  //                                                                                                                                                           
   2414 int blk_rq_map_user(request_queue_t *q, struct request *rq, void __user *ubuf,                                                                                
   2415                     unsigned long len)                                                                                                                        
   2416 {                                                                                                                                                             
   2417         unsigned long bytes_read = 0;                                                                                                                         
   2418         struct bio *bio = NULL;                                                                                                                               
   2419         int ret;                                                                                                                                              
   2420                                                                                                                                                               
   2421         if (len > (q->max_hw_sectors << 9))                                                                                                                   
   2422                 return -EINVAL;                                                                                                                               
   2423         if (!len || !ubuf)                                                                                                                                    
   2424                 return -EINVAL;                                                                                                                               
   2425                                                                                                                                                               
   2426         while (bytes_read != len) {                                                                                                                           
   2427                 unsigned long map_len, end, start;                                                                                                            
   2428                                                                                                                                                               
   2429                 map_len = min_t(unsigned long, len - bytes_read,                                                                                              
BIO_MAX_SIZE);                                                                                                                                                        
   2430                 end = ((unsigned long)ubuf + map_len + PAGE_SIZE - 1)                                                                                         
   2431                                                                 >>                                                                                            
PAGE_SHIFT;                                                                                                                                                           
   2432                 start = (unsigned long)ubuf >> PAGE_SHIFT;                                                                                                    
   2433                                                                                                                                                               
   2434                 //                                                                                                                                            
   2435                  * A bad offset could cause us to require BIO_MAX_PAGES + 1                                                                                   
   2436                  * pages. If this happens we just lower the requested                                                                                         
   2437                  * mapping len by a page so that we can fit                                                                                                   
   2438                  //                                                                                                                                           
   2439                 if (end - start > BIO_MAX_PAGES)                                                                                                              
   2440                         map_len -= PAGE_SIZE;                                                                                                                 
   2441                                                                                                                                                               
   2442                 ret = __blk_rq_map_user(q, rq, ubuf, map_len);                                                                                                
   2443                 if (ret < 0)                                                                                                                                  
   2444                         goto unmap_rq;                                                                                                                        
   2445                 if (!bio) Linux  ��Щ�¶�֮���� Block��                                                                                                       
�� 100 ҳ �� 117  ҳ                                                                                                                                                  
   2446                         bio = rq->bio;                                                                                                                        
   2447                 bytes_read += ret;                                                                                                                            
   2448                 ubuf += ret;                                                                                                                                  
   2449         }                                                                                                                                                     
   2450                                                                                                                                                               
   2451         rq->buffer = rq->data = NULL;                                                                                                                         
   2452         return 0;                                                                                                                                             
   2453 unmap_rq:                                                                                                                                                     
   2454         blk_rq_unmap_user(bio);                                                                                                                               
   2455         return ret;                                                                                                                                           
   2456 }                                                                                                                                                             
// ��������Ĳ��� ubuf ���Ǳ���,���Ǵ��û��ռ䴫�������Ǹ� user buffer,��Ի user-space                                                                                   
// buffer,��len���Ǹ� buffer �ĳ���.                                                                                                                                     
// Ҳ��������͸ý� struct bio ��.������������ṹ���� Generic Block Layer������������                                                                                 
// ���������������Ľṹ��֮һ.����������һ�����ڽ��еĿ��豸 I/O ����.����� Linux                                                                                     
// �鼮����һ����Ķ�������ṹ���������ϸ�Ľ���,����Ϊ 80 �����ǲ�����Ҫ����,����                                                                                      
// ��Ҫ�沨����,����Ҫ׷���Լ��ĸ���,�����������ǲ�������ؽ�����ṹ��,ֻ�Ǹ�����,                                                                                      
// ������ include/linux/bio.h:                                                                                                                                           
//      68 //                                                                                                                                                            
//      69  * main unit of I/O for the block layer and lower layers (ie drivers and                                                                                      
//      70  * stacking drivers)                                                                                                                                          
     71  //                                                                                                                                                           
     72 struct bio {                                                                                                                                                  
     73         sector_t                bi_sector;      // device address in 512 byte                                                                                 
     74                                                    sectors //                                                                                                 
     75         struct bio              *bi_next;       // request queue link //                                                                                      
     76         struct block_device     *bi_bdev;                                                                                                                     
     77         unsigned long           bi_flags;       // status, command, etc //                                                                                    
     78         unsigned long           bi_rw;          // bottom bits READ/WRITE,                                                                                    
     79                                                  * top bits priority                                                                                          
     80                                                  //                                                                                                           
     81                                                                                                                                                               
     82         unsigned short          bi_vcnt;        // how many bio_vec's //                                                                                      
     83         unsigned short          bi_idx;         // current index into bvl_vec //                                                                              
     84                                                                                                                                                               
     85         // Number of segments in this BIO after                                                                                                               
     86          * physical address coalescing is performed.                                                                                                          
     87          //                                                                                                                                                   
     88         unsigned short          bi_phys_segments;                                                                                                             
     89                                                                                                                                                               
     90         // Number of segments after physical and DMA remapping                                                                                                
     91          * hardware coalescing is performed.                                                                                                                  
     92          //                                                                                                                                                   
     93         unsigned short          bi_hw_segments; Linux  ��Щ�¶�֮���� Block��                                                                                 
�� 101 ҳ �� 117  ҳ                                                                                                                                                  
     94                                                                                                                                                               
     95         unsigned int            bi_size;        // residual I/O count //                                                                                      
     96                                                                                                                                                               
     97         //                                                                                                                                                    
     98          * To keep track of the max hw size, we account for the                                                                                               
     99          * sizes of the first and last virtually mergeable segments                                                                                           
    100          * in this bio                                                                                                                                        
    101          //                                                                                                                                                   
    102         unsigned int            bi_hw_front_size;                                                                                                             
    103         unsigned int            bi_hw_back_size;                                                                                                              
    104                                                                                                                                                               
    105         unsigned int            bi_max_vecs;    // max bvl_vecs we can hold //                                                                                
    106                                                                                                                                                               
    107         struct bio_vec          *bi_io_vec;     // the actual vec list //                                                                                     
    108                                                                                                                                                               
    109         bio_end_io_t            *bi_end_io;                                                                                                                   
    110         atomic_t                bi_cnt;         // pin count //                                                                                               
    111                                                                                                                                                               
    112         void                    *bi_private;                                                                                                                  
    113                                                                                                                                                               
    114         bio_destructor_t        *bi_destructor; // destructor //                                                                                              
    115 };                                                                                                                                                            
// �����Ĵ��ڲ����ǹ�����,����request������ϵ��.struct request����һ����Աstruct bio *bio,                                                                               
// �����ľ������ request �� bio ��,��Ϊһ�� request ������� I/O ����.�� blk_rq_map_user ��                                                                             
// ��Ҫ�������ǽ��� user buffer�� bio֮���ӳ��,���幤������__blk_rq_map_user����ɵ�.                                                                                   
   2341 static int __blk_rq_map_user(request_queue_t *q, struct request *rq,                                                                                          
   2342                              void __user *ubuf, unsigned int len)                                                                                             
   2343 {                                                                                                                                                             
   2344         unsigned long uaddr;                                                                                                                                  
   2345         struct bio *bio, *orig_bio;                                                                                                                           
   2346         int reading, ret;                                                                                                                                     
   2347                                                                                                                                                               
   2348         reading = rq_data_dir(rq) == READ;                                                                                                                    
   2349                                                                                                                                                               
   2350         //                                                                                                                                                    
   2351          * if alignment requirement is satisfied, map in user pages for                                                                                       
   2352          * direct dma. else, set up kernel bounce buffers                                                                                                     
   2353          //                                                                                                                                                   
   2354         uaddr = (unsigned long) ubuf;                                                                                                                         
   2355         if (!(uaddr & queue_dma_alignment(q)) && !(len &                                                                                                      
queue_dma_alignment(q)))                                                                                                                                              
   2356                 bio = bio_map_user(q, NULL, uaddr, len, reading);                                                                                             
   2357         else                                                                                                                                                  
   2358                 bio = bio_copy_user(q, uaddr, len, reading); Linux  ��Щ�¶�֮���� Block��                                                                    
�� 102 ҳ �� 117  ҳ                                                                                                                                                  
   2359                                                                                                                                                               
   2360         if (IS_ERR(bio))                                                                                                                                      
   2361                 return PTR_ERR(bio);                                                                                                                          
   2362                                                                                                                                                               
   2363         orig_bio = bio;                                                                                                                                       
   2364         blk_queue_bounce(q, &bio);                                                                                                                            
   2365                                                                                                                                                               
   2366         //                                                                                                                                                    
   2367          * We link the bounce buffer in and could have to traverse it                                                                                         
   2368          * later so we have to get a ref to prevent it from being freed                                                                                       
   2369          //                                                                                                                                                   
   2370         bio_get(bio);                                                                                                                                         
   2371                                                                                                                                                               
   2372         if (!rq->bio)                                                                                                                                         
   2373                 blk_rq_bio_prep(q, rq, bio);                                                                                                                  
   2374         else if (!ll_back_merge_fn(q, rq, bio)) {                                                                                                             
   2375                 ret = -EINVAL;                                                                                                                                
   2376                 goto unmap_bio;                                                                                                                               
   2377         } else {                                                                                                                                              
   2378                 rq->biotail->bi_next = bio;                                                                                                                   
   2379                 rq->biotail = bio;                                                                                                                            
   2380                                                                                                                                                               
   2381                 rq->data_len += bio->bi_size;                                                                                                                 
   2382         }                                                                                                                                                     
   2383                                                                                                                                                               
   2384         return bio->bi_size;                                                                                                                                  
   2385                                                                                                                                                               
   2386 unmap_bio:                                                                                                                                                    
   2387         // if it was boucned we must call the end io function //                                                                                              
   2388         bio_endio(bio, bio->bi_size, 0);                                                                                                                      
   2389         __blk_rq_unmap_user(orig_bio);                                                                                                                        
   2390         bio_put(bio);                                                                                                                                         
   2391         return ret;                                                                                                                                           
   2392 }                                                                                                                                                             
// ������ĿǰΪֹ,bio ��ֻ��һ��������翵�ָ��,������ʵ,˭Ϊ���������ڴ���?�����ǽ�                                                                                      
// ������,��һ��������Ҫ��ע���� bio_map_user().uaddr �� ubuf �������ַ,�������������                                                                                  
// ���е��ֽڶ���Ҫ��,�� bio_map_user()�ᱻ����.(������Ҫ���� bio_copy_user()��������ν                                                                                  
// �� bounce buffer,����.)�ú������� fs/bio.c:                                                                                                                           
//     713 ///                                                                                                                                                           
//     714  *      bio_map_user    -       map user address into bio                                                                                                     
//     715  *      @q: the request_queue_t for the bio                                                                                                                   
//     716  *      @bdev: destination block device                                                                                                                       
//     717  *      @uaddr: start of user address                                                                                                                         
//     718  *      @len: length in bytes Linux  ��Щ�¶�֮���� Block��                                                                                                   
// �� 103 ҳ �� 117  ҳ                                                                                                                                                  
//     719  *      @write_to_vm: bool indicating writing to pages or not                                                                                                 
//     720  *                                                                                                                                                            
//     721  *      Map the user space address into a bio suitable for io to a block                                                                                      
//     722  *      device. Returns an error pointer in case of error.                                                                                                    
//     723  //                                                                                                                                                           
    724 struct bio *bio_map_user(request_queue_t *q, struct block_device *bdev,                                                                                       
    725                          unsigned long uaddr, unsigned int len, int write_to_vm)                                                                              
    726 {                                                                                                                                                             
    727         struct sg_iovec iov;                                                                                                                                  
    728                                                                                                                                                               
    729         iov.iov_base = (void __user *)uaddr;                                                                                                                  
    730         iov.iov_len = len;                                                                                                                                    
    731                                                                                                                                                               
    732         return bio_map_user_iov(q, bdev, &iov, 1, write_to_vm);                                                                                               
    733 }                                                                                                                                                             
// �ߵ�����,struct sg_iovec������ʶ,��ϸ����һ��,��sd�н�ioctl��ʱ��������������ṹ��,                                                                                  
// �����ľ���һ��scatter-gather�����Ա.iovec����io vector����˼,��IO����,����˵һ����                                                                                   
// ����ַ�ͳ�����ɵĽṹ��.                                                                                                                                             
// ���ں����ĸ�������,ע����˵�ú����,����ע��Ҳ˵�����������Ŀ��,����֪�������                                                                                       
// ��������һ��������һ�� IO ������ bio ָ��.���������ɻ���� bio_map_user_iov().������                                                                                  
// תս�� bio_map_user_iov().ͬ������ fs/bio.c:                                                                                                                          
//     735 ///                                                                                                                                                           
//     736  *      bio_map_user_iov - map user sg_iovec table into bio                                                                                                   
//     737  *      @q: the request_queue_t for the bio                                                                                                                   
//     738  *      @bdev: destination block device                                                                                                                       
//     739  *      @iov:   the iovec.                                                                                                                                    
//     740  *      @iov_count: number of elements in the iovec                                                                                                           
//     741  *      @write_to_vm: bool indicating writing to pages or not                                                                                                 
//     742  *                                                                                                                                                            
//     743  *      Map the user space address into a bio suitable for io to a block                                                                                      
//     744  *      device. Returns an error pointer in case of error.                                                                                                    
    745  //                                                                                                                                                           
    746 struct bio *bio_map_user_iov(request_queue_t *q, struct block_device *bdev,                                                                                   
    747                              struct sg_iovec *iov, int iov_count,                                                                                             
    748                              int write_to_vm)                                                                                                                 
    749 {                                                                                                                                                             
    750         struct bio *bio;                                                                                                                                      
    751                                                                                                                                                               
    752         bio = __bio_map_user_iov(q, bdev, iov, iov_count, write_to_vm);                                                                                       
    753                                                                                                                                                               
    754         if (IS_ERR(bio))                                                                                                                                      
    755                 return bio;                                                                                                                                   
    756                                                                                                                                                               
    757         // Linux  ��Щ�¶�֮���� Block��                                                                                                                      
//�� 104 ҳ �� 117  ҳ                                                                                                                                                  
//    758          * subtle -- if __bio_map_user() ended up bouncing a bio,                                                                                             
//    759          * it would normally disappear when its bi_end_io is run.                                                                                             
//    760          * however, we need it for the unmap, so grab an extra                                                                                                
//    761          * reference to it                                                                                                                                    
    762          //                                                                                                                                                   
    763         bio_get(bio);                                                                                                                                         
    764                                                                                                                                                               
    765         return bio;                                                                                                                                           
    766 }                                                                                                                                                             
�������յ�,��������__bio_map_user_iov().                                                                                                                              
    603 static struct bio *__bio_map_user_iov(request_queue_t *q,                                                                                                     
    604                                       struct block_device *bdev,                                                                                              
    605                                       struct sg_iovec *iov, int iov_count,                                                                                    
    606                                       int write_to_vm)                                                                                                        
    607 {                                                                                                                                                             
    608         int i, j;                                                                                                                                             
    609         int nr_pages = 0;                                                                                                                                     
    610         struct page **pages;                                                                                                                                  
    611         struct bio *bio;                                                                                                                                      
    612         int cur_page = 0;                                                                                                                                     
    613         int ret, offset;                                                                                                                                      
    614                                                                                                                                                               
    615         for (i = 0; i < iov_count; i++) {                                                                                                                     
    616                 unsigned long uaddr = (unsigned long)iov[i].iov_base;                                                                                         
    617                 unsigned long len = iov[i].iov_len;                                                                                                           
    618                 unsigned long end = (uaddr + len + PAGE_SIZE - 1) >>                                                                                          
PAGE_SHIFT;                                                                                                                                                           
    619                 unsigned long start = uaddr >> PAGE_SHIFT;                                                                                                    
    620                                                                                                                                                               
    621                 nr_pages += end - start;                                                                                                                      
    622                 //                                                                                                                                            
    623                  * buffer must be aligned to at least hardsector size for now                                                                                 
    624                  //                                                                                                                                           
    625                 if (uaddr & queue_dma_alignment(q))                                                                                                           
    626                         return ERR_PTR(-EINVAL);                                                                                                              
    627         }                                                                                                                                                     
    628                                                                                                                                                               
    629         if (!nr_pages)                                                                                                                                        
    630                 return ERR_PTR(-EINVAL);                                                                                                                      
    631                                                                                                                                                               
    632         bio = bio_alloc(GFP_KERNEL, nr_pages);                                                                                                                
    633         if (!bio)                                                                                                                                             
    634                 return ERR_PTR(-ENOMEM);                                                                                                                      
    635 Linux  ��Щ�¶�֮���� Block��                                                                                                                                 
�� 105 ҳ �� 117  ҳ                                                                                                                                                  
    636         ret = -ENOMEM;                                                                                                                                        
    637         pages = kcalloc(nr_pages, sizeof(struct page *), GFP_KERNEL);                                                                                         
    638         if (!pages)                                                                                                                                           
    639                 goto out;                                                                                                                                     
    640                                                                                                                                                               
    641         for (i = 0; i < iov_count; i++) {                                                                                                                     
    642                 unsigned long uaddr = (unsigned long)iov[i].iov_base;                                                                                         
    643                 unsigned long len = iov[i].iov_len;                                                                                                           
    644                 unsigned long end = (uaddr + len + PAGE_SIZE - 1) >>                                                                                          
PAGE_SHIFT;                                                                                                                                                           
    645                 unsigned long start = uaddr >> PAGE_SHIFT;                                                                                                    
    646                 const int local_nr_pages = end - start;                                                                                                       
    647                 const int page_limit = cur_page + local_nr_pages;                                                                                             
    648                                                                                                                                                               
    649                 down_read(&current->mm->mmap_sem);                                                                                                            
    650                 ret = get_user_pages(current, current->mm, uaddr,                                                                                             
    651                                      local_nr_pages,                                                                                                          
    652                                      write_to_vm, 0, &pages[cur_page],                                                                                        
NULL);                                                                                                                                                                
    653                 up_read(&current->mm->mmap_sem);                                                                                                              
    654                                                                                                                                                               
    655                 if (ret < local_nr_pages) {                                                                                                                   
    656                         ret = -EFAULT;                                                                                                                        
    657                         goto out_unmap;                                                                                                                       
    658                 }                                                                                                                                             
    659                                                                                                                                                               
    660                 offset = uaddr & ~PAGE_MASK;                                                                                                                  
    661                 for (j = cur_page; j < page_limit; j++) {                                                                                                     
    662                         unsigned int bytes = PAGE_SIZE - offset;                                                                                              
    663                                                                                                                                                               
    664                         if (len <= 0)                                                                                                                         
    665                                 break;                                                                                                                        
    666                                                                                                                                                               
    667                         if (bytes > len)                                                                                                                      
    668                                 bytes = len;                                                                                                                  
    669                                                                                                                                                               
    670                         //                                                                                                                                    
    671                          * sorry...                                                                                                                           
    672                          //                                                                                                                                   
    673                         if (bio_add_pc_page(q, bio, pages[j], bytes, offset) <                                                                                
    674                                             bytes)                                                                                                            
    675                                 break;                                                                                                                        
    676                                                                                                                                                               
    677                         len -= bytes; Linux  ��Щ�¶�֮���� Block��                                                                                           
�� 106 ҳ �� 117  ҳ                                                                                                                                                  
    678                         offset = 0;                                                                                                                           
    679                 }                                                                                                                                             
    680                                                                                                                                                               
    681                 cur_page = j;                                                                                                                                 
    682                 //                                                                                                                                            
    683                  * release the pages we didn't map into the bio, if any                                                                                       
    684                  //                                                                                                                                           
    685                 while (j < page_limit)                                                                                                                        
    686                         page_cache_release(pages[j++]);                                                                                                       
    687         }                                                                                                                                                     
    688                                                                                                                                                               
    689         kfree(pages);                                                                                                                                         
    690                                                                                                                                                               
    691         //                                                                                                                                                    
    692          * set data direction, and check if mapped pages need bouncing                                                                                        
    693          //                                                                                                                                                   
    694         if (!write_to_vm)                                                                                                                                     
    695                 bio->bi_rw |= (1 << BIO_RW);                                                                                                                  
    696                                                                                                                                                               
    697         bio->bi_bdev = bdev;                                                                                                                                  
    698         bio->bi_flags |= (1 << BIO_USER_MAPPED);                                                                                                              
    699         return bio;                                                                                                                                           
    700                                                                                                                                                               
    701  out_unmap:                                                                                                                                                   
    702         for (i = 0; i < nr_pages; i++) {                                                                                                                      
    703                 if(!pages[i])                                                                                                                                 
    704                         break;                                                                                                                                
    705                 page_cache_release(pages[i]);                                                                                                                 
    706         }                                                                                                                                                     
    707  out:                                                                                                                                                         
    708         kfree(pages);                                                                                                                                         
    709         bio_put(bio);                                                                                                                                         
    710         return ERR_PTR(ret);                                                                                                                                  
    711 }                                                                                                                                                             
// 632 ��,bio_alloc(),�����˰�,������,�ڴ��������������,bio �Ӵ�վ������.                                                                                               
// ���Ǳ����Բ�������,���ǰ��Ÿ������ǿ����벻���쾡�²�ʹ��.                                                                                                            
// ���Լ������� bio_alloc,���� fs/bio.c:                                                                                                                                 
    187 struct bio *bio_alloc(gfp_t gfp_mask, int nr_iovecs)                                                                                                          
    188 {                                                                                                                                                             
    189         struct bio *bio = bio_alloc_bioset(gfp_mask, nr_iovecs, fs_bio_set);                                                                                  
    190                                                                                                                                                               
    191         if (bio)                                                                                                                                              
    192                 bio->bi_destructor = bio_fs_destructor;                                                                                                       
    193 Linux  ��Щ�¶�֮���� Block��                                                                                                                                 
�� 107 ҳ �� 117  ҳ                                                                                                                                                  
    194         return bio;                                                                                                                                           
    195 }                                                                                                                                                             
//��ʵ���ǵ��� bio_alloc_bioset(),����ͬһ���ļ�:                                                                                                                       
//    147 ///                                                                                                                                                           
//    148  * bio_alloc_bioset - allocate a bio for I/O                                                                                                                  
//    149  * @gfp_mask:   the GFP_ mask given to the slab allocator                                                                                                     
//    150  * @nr_iovecs:  number of iovecs to pre-allocate                                                                                                              
//    151  * @bs:         the bio_set to allocate from                                                                                                                  
//    152  *                                                                                                                                                            
//    153  * Description:                                                                                                                                               
//    154  *   bio_alloc_bioset will first try it's on mempool to satisfy the allocation.                                                                               
//    155  *   If %__GFP_WAIT is set then we will block on the internal pool waiting                                                                                    
//    156  *   for a &struct bio to become free.                                                                                                                        
//    157  *                                                                                                                                                            
//    158  *   allocate bio and iovecs from the memory pools specified by the                                                                                           
//    159  *   bio_set structure.                                                                                                                                       
//    160  ///                                                                                                                                                          
    161 struct bio *bio_alloc_bioset(gfp_t gfp_mask, int nr_iovecs, struct bio_set *bs)                                                                               
    162 {                                                                                                                                                             
    163         struct bio *bio = mempool_alloc(bs->bio_pool, gfp_mask);                                                                                              
    164                                                                                                                                                               
    165         if (likely(bio)) {                                                                                                                                    
    166                 struct bio_vec *bvl = NULL;                                                                                                                   
    167                                                                                                                                                               
    168                 bio_init(bio);                                                                                                                                
    169                 if (likely(nr_iovecs)) {                                                                                                                      
    170                         unsigned long idx = 0; // shut up gcc //                                                                                              
    171                                                                                                                                                               
    172                         bvl = bvec_alloc_bs(gfp_mask, nr_iovecs, &idx, bs);                                                                                   
    173                         if (unlikely(!bvl)) {                                                                                                                 
    174                                 mempool_free(bio, bs->bio_pool);                                                                                              
    175                                 bio = NULL;                                                                                                                   
    176                                 goto out;                                                                                                                     
    177                         }                                                                                                                                     
    178                         bio->bi_flags |= idx << BIO_POOL_OFFSET;                                                                                              
    179                         bio->bi_max_vecs = bvec_slabs[idx].nr_vecs;                                                                                           
    180                 }                                                                                                                                             
    181                 bio->bi_io_vec = bvl;                                                                                                                         
    182         }                                                                                                                                                     
    183 out:                                                                                                                                                          
    184         return bio;                                                                                                                                           
    185 }                                                                                                                                                             
// ������������Ͼ�������ô������.mempool_alloc ����ȷ�ĸ�������,Ϊ bio �������ڴ�,��                                                                                    
// ���� bio_init()Ϊ�����˳�ʼ��.����ϸ�ڲ���˵��,Ψһ��Ҫ��ע����,nr_iovecs,һ·������Linux  ��Щ�¶�֮���� Block��                                                     
// �� 108 ҳ �� 117  ҳ                                                                                                                                                  
// ��, __bio_map_user_iov()�а� nr_pages�����˸��� bio_alloc(),�� 615 �е�627 �ж�nr_pages                                                                               
// �����˼���,ͨ��һ�� for ѭ���ۼ�,ѭ�������� iov_count,ÿ���׼ӵ��� end �� start �Ĳ�ֵ.                                                                               
// ����Ȼ,���յ� nr_pages ���� iov ��������Ӧ�� page ������,�� iov ��__bio_map_user_iov ��                                                                               
// ����������,��һ����,����Ȼ,iov_count �������� iov �����Ԫ�ظ���,���� bio_map_user ��                                                                                 
// ���� bio_map_user_iov ʱ���ݵĵ����������� 1,���� iov_count ���� 1.������Щ������Ҫ,                                                                                  
// ��Ҫ�������������� bio ��.���ǽ��� bio_alloc,�ص�__bio_map_user_iov �м���������,637                                                                                  
// ��,��������һ������,pages,һ������ָ��,ڤڤ�ио����⽫����һ��ָ������.                                                                                              
// ��������,������һ�� for ѭ��.�� get_user_pages �ǻ�� page ������.��һ�д���Ӧ�������                                                                                
// ���ʵĴ���.����һ����,�û��ռ�� buffer ���ں˿ռ佨������Ե.�����Ǵ��������ͼ˵                                                                                     
// ��.                                                                                                                                                                   
// Bio ������Ҫ�ĳ�Ա���� bi_io_vec �� bi_vcnt.bi_io_vec ��һ�� struct bio_vec ָ��,���ߵĶ�                                                                             
// ���� include/linux/bio.h ��:                                                                                                                                          
     54 //                                                                                                                                                            
     55  * was unsigned short, but we might as well be ready for > 64kB I/O pages                                                                                     
     56  //                                                                                                                                                           
     57 struct bio_vec {                                                                                                                                              
     58         struct page     *bv_page;                                                                                                                             
     59         unsigned int    bv_len; Linux  ��Щ�¶�֮���� Block��                                                                                                 
�� 109 ҳ �� 117  ҳ                                                                                                                                                  
     60         unsigned int    bv_offset;                                                                                                                            
     61 };                                                                                                                                                            
// �� bi_io_vecʵ�������Ǵ�����һ�� struct bio_vec������,bi_vcnt ����������Ԫ�ظ���.��                                                                                 
// ͼ�п���������,bio_vec�еĳ�Աbv_pageָ�����һ����ӳ���page.������ӳ���ǡǡ��                                                                                      
// �Ǹղſ��������ΰ���get_user_pages()����,��������Щ��page���û��ռ��buffer��ϵ                                                                                     
// ������.��bio_add_pc_page()������bv_pageָ����Ӧ��page.֮����Ҫ��page���û��ռ��                                                                                      
// bufferӳ������,��ԭ������block��ֻ��bio�����û��ռ��user buffer,block�����Щ����                                                                                    
// ��������� bio ��������,���ǿɲ�����ʲô�û��ռ䲻�û��ռ�,���Ǿ͹��Լ��� bio,����                                                                                    
// ��֪��ÿһ�� request ��Ӧһ�� bio.                                                                                                                                    
// ���� get_user_pages����,��ԭ���� include/linux/mm.h ��:                                                                                                               
//     795 int get_user_pages(struct task_struct *tsk, struct mm_struct *mm, unsigned long start,                                                                        
//     796                 int len, int write, int force, struct page **pages, struct                                                                                    
// vm_area_struct **vmas);                                                                                                                                               
// ������,start�� len ������������������ user-space buffer,(���� len �ĵ�λ��page,��len���                                                                              
// Ϊ 3 �ͱ�ʾ 3 �� page.)��������Ŀ�ľ��ǰ���� user-space buffer ӳ�䵽�ں˿ռ�,�� pages                                                                               
// �� vmas ��������������.���� pages ��һ������ָ��,����֮����ʵ����һ��ָ������,��                                                                                    
// ������һȺ page ָ��,��Ⱥ page ָ��ָ���������� user-space buffer.��������ķ���ֵ��                                                                                
// ʵ��ӳ���˼��� pages.(The return value is the number of pages actually mapped.)�� vmas ����                                                                           
// ���ù���,�����������ﴫ�ݽ�ȥ���� NULL,������������ʲô����.                                                                                                          
// ������ get_user_pages ����Լ���,����ÿһ���ɹ������˱�����һ��(����)Ů��,����                                                                                    
// �ű���ʦ,������������ʦ,���������ʦ,ÿһ�� Linux ���̱�����һ��ҳ��.�ڽ��̴�                                                                                     
// ����ʱ��������ַ�ռ��н����Լ���ҳ��,���� x86 ����,ҳ����һ���� 1024 ��,ÿһ���                                                                                    
// �Ա���һ�� page,���� page �Ƿ�����������ڴ�����?��ͺ���˵��.���ǲ����� page table                                                                                   
// �е� 1024 ��˵�� 1024 ��ָ��,�� 1024 ��ָ�붼�� 32 �� bits,�����о���һλ������ Present                                                                               
// λ,��Ϊ 1 ��˵���� page�����������ڴ���,��Ϊ0 ��˵�������������ڴ���.                                                                                                 
// ��ô���������� get_user_pages ��ʲô��ϵ��?get_user_pages �Ĳ��� start �� len ��������                                                                              
// ���Ե�ַ,�� x86 ��˵,���Ե�ַһ�� 32 �� bits,����ʮ���� bits ��Ϊ����,bit31-bit22 ��Ϊ                                                                                
// Directory,����˵ Page Directory �е�����,bit21-bit12 ��Ϊ Table,����˵ Page Table �е���                                                                              
// ��,bit11-bit0 ���� Offset.������һ�������ַ,����˵���Ե�ַ,���൱�ڸ��������� Page                                                                                   
// Directory�е�λ��,����������Page Table�е�λ��,Ҳ����˵������һ��Page.�������Page                                                                                    
// �������ڴ���,��ô��˵,�������������?�������,��ʱ�� get_user_pages()����Ӣ�۱�ɫ,��                                                                                  
// ������һ�� Page Frame,����Ӧ������ҳ��.��֮��,��������ַ�������к�̨�������ַ                                                                                      
// ��,��Ϊ�������ַ��������,������Ӧ�ó���Ϳ��Է�������,���豸����Ҳ���Է�������,                                                                                      
// ֻ�����豸����������ֱ�ӷ�����Щ����ַ,����ǰ��˵��,Block ��ֻ�� bio,���� page,����                                                                                   
// �����ַ,����������������� bio_add_pc_page(),����� page�� bio ��ϵ����.                                                                                             
// �������� bio_add_pc_page,������ fs/bio.c:                                                                                                                             
//     414 ///                                                                                                                                                           
//     415  *      bio_add_pc_page -       attempt to add page to bio                                                                                                    
//     416  *      @q: the target queue                                                                                                                                  
//     417  *      @bio: destination bio                                                                                                                                 
//     418  *      @page: page to add                                                                                                                                    
//     419  *      @len: vec entry length                                                                                                                                
//     420  *      @offset: vec entry offset                                                                                                                             
//     421  * Linux  ��Щ�¶�֮���� Block��                                                                                                                              
// �� 110  ҳ  �� 117  ҳ                                                                                                                                                
//     422  *      Attempt to add a page to the bio_vec maplist. This can fail for a                                                                                     
//     423  *      number of reasons, such as the bio being full or target block                                                                                         
//     424  *      device limitations. The target block device must allow bio's                                                                                          
//     425  *      smaller than PAGE_SIZE, so it is always possible to add a single                                                                                      
//     426  *      page to an empty bio. This should only be used by REQ_PC bios.                                                                                        
//     427  //                                                                                                                                                           
    428 int bio_add_pc_page(request_queue_t *q, struct bio *bio, struct page *page,                                                                                   
    429                     unsigned int len, unsigned int offset)                                                                                                    
    430 {                                                                                                                                                             
    431         return __bio_add_page(q, bio, page, len, offset, q->max_hw_sectors);                                                                                  
    432 }                                                                                                                                                             
��__bio_add_pages����ͬһ���ļ�.                                                                                                                                      
    318 static int __bio_add_page(request_queue_t *q, struct bio *bio, struct page                                                                                    
    319                           *page, unsigned int len, unsigned int offset,                                                                                       
    320                           unsigned short max_sectors)                                                                                                         
    321 {                                                                                                                                                             
    322         int retried_segments = 0;                                                                                                                             
    323         struct bio_vec *bvec;                                                                                                                                 
    324                                                                                                                                                               
    325         //                                                                                                                                                    
    326          * cloned bio must not modify vec list                                                                                                                
    327          //                                                                                                                                                   
    328         if (unlikely(bio_flagged(bio, BIO_CLONED)))                                                                                                           
    329                 return 0;                                                                                                                                     
    330                                                                                                                                                               
    331         if (((bio->bi_size + len) >> 9) > max_sectors)                                                                                                        
    332                 return 0;                                                                                                                                     
    333                                                                                                                                                               
    334         //                                                                                                                                                    
    335          * For filesystems with a blocksize smaller than the pagesize                                                                                         
    336          * we will often be called with the same page as last time and                                                                                        
    337          * a consecutive offset.  Optimize this special case.                                                                                                 
    338          //                                                                                                                                                   
    339         if (bio->bi_vcnt > 0) {                                                                                                                               
    340                 struct bio_vec *prev = &bio->bi_io_vec[bio->bi_vcnt - 1];                                                                                     
    341                                                                                                                                                               
    342                 if (page == prev->bv_page &&                                                                                                                  
    343                     offset == prev->bv_offset + prev->bv_len) {                                                                                               
    344                         prev->bv_len += len;                                                                                                                  
    345                         if (q->merge_bvec_fn &&                                                                                                               
    346                             q->merge_bvec_fn(q, bio, prev) < len) {                                                                                           
    347                                 prev->bv_len -= len;                                                                                                          
    348                                 return 0;                                                                                                                     
    349                         } Linux  ��Щ�¶�֮���� Block��                                                                                                       
�� 111  ҳ �� 117  ҳ                                                                                                                                                 
    350                                                                                                                                                               
    351                         goto done;                                                                                                                            
    352                 }                                                                                                                                             
    353         }                                                                                                                                                     
    354                                                                                                                                                               
    355         if (bio->bi_vcnt >= bio->bi_max_vecs)                                                                                                                 
    356                 return 0;                                                                                                                                     
    357                                                                                                                                                               
    358         //                                                                                                                                                    
    359          * we might lose a segment or two here, but rather that than                                                                                          
    360          * make this too complex.                                                                                                                             
    361          //                                                                                                                                                   
    362                                                                                                                                                               
    363         while (bio->bi_phys_segments >= q->max_phys_segments                                                                                                  
    364                || bio->bi_hw_segments >= q->max_hw_segments                                                                                                   
    365                || BIOVEC_VIRT_OVERSIZE(bio->bi_size)) {                                                                                                       
366                                                                                                                                                                   
    367                 if (retried_segments)                                                                                                                         
    368                         return 0;                                                                                                                             
    369                                                                                                                                                               
    370                 retried_segments = 1;                                                                                                                         
    371                 blk_recount_segments(q, bio);                                                                                                                 
    372         }                                                                                                                                                     
    373                                                                                                                                                               
    374         //                                                                                                                                                    
    375          * setup the new entry, we might clear it again later if we                                                                                           
    376          * cannot add the page                                                                                                                                
    377          //                                                                                                                                                   
    378         bvec = &bio->bi_io_vec[bio->bi_vcnt];                                                                                                                 
    379         bvec->bv_page = page;                                                                                                                                 
    380         bvec->bv_len = len;                                                                                                                                   
    381         bvec->bv_offset = offset;                                                                                                                             
    382                                                                                                                                                               
    383         //                                                                                                                                                    
    384          * if queue has other restrictions (eg varying max sector size                                                                                        
    385          * depending on offset), it can specify a merge_bvec_fn in the                                                                                        
    386          * queue to get further control                                                                                                                       
    387          //                                                                                                                                                   
    388         if (q->merge_bvec_fn) {                                                                                                                               
    389                 //                                                                                                                                            
    390                  * merge_bvec_fn() returns number of bytes it can accept                                                                                      
    391                  * at this offset                                                                                                                             
    392                  //                                                                                                                                           
    393                 if (q->merge_bvec_fn(q, bio, bvec) < len) { Linux  ��Щ�¶�֮���� Block��                                                                     
�� 112  ҳ  �� 117  ҳ                                                                                                                                                
    394                         bvec->bv_page = NULL;                                                                                                                 
    395                         bvec->bv_len = 0;                                                                                                                     
    396                         bvec->bv_offset = 0;                                                                                                                  
    397                         return 0;                                                                                                                             
    398                 }                                                                                                                                             
    399         }                                                                                                                                                     
    400                                                                                                                                                               
    401         // If we may be able to merge these biovecs, force a recount //                                                                                       
    402         if (bio->bi_vcnt && (BIOVEC_PHYS_MERGEABLE(bvec-1, bvec) ||                                                                                           
    403             BIOVEC_VIRT_MERGEABLE(bvec-1, bvec)))                                                                                                             
    404                 bio->bi_flags &= ~(1 << BIO_SEG_VALID);                                                                                                       
    405                                                                                                                                                               
    406         bio->bi_vcnt++;                                                                                                                                       
    407         bio->bi_phys_segments++;                                                                                                                              
    408         bio->bi_hw_segments++;                                                                                                                                
    409  done:                                                                                                                                                        
    410         bio->bi_size += len;                                                                                                                                  
    411         return len;                                                                                                                                           
    412 }                                                                                                                                                             
// Block ��ܶණ������Ϊ Raid �����,������������ merge_bvec_fn ����ָ��,������ͨ��                                                                                   
// Ӳ��������˵,��û����ôһ����ָ���,����˵���ָ��ָ����ǿ���.��������˼����û                                                                                       
// ����������Ļ�,__bio_add_pages ��������ͱ�úܼ���,�������Ǻܿ���.�����������                                                                                     
// ����Ĵ������378�е�381�ж�bvec�ĸ�ֵ,�Լ�406�е�410�ж�bio�ĸ�ֵ.��������                                                                                           
// һ��,ע��410�������ֵ,bio->bi_size����len���ۼ�,�������ϸ׷��һ�¾ͻᷢ��,��ʵ��                                                                                    
// ��תȥ,���bio->bi_size��������û��ռ䴫�����Ǹ� len.                                                                                                                
// ����__bio_map_user_iov()��,661�е�679�����forѭ��,�����������е���Щpagesһ����                                                                                      
// ��ȫ�����뵽 bio ������ bi_io_vec����ȥ,��ÿһ�� bv_page ������ָ.                                                                                                    
// Ȼ��,�� 699 ��,__bio_map_user_iov()��������,���صľ��� bio.������,bio_map_user_iov()��                                                                                
// bio_map_user()Ҳ�Ⱥ󷵻�,����ֵҲ������� bio.�������ǻص���__blk_rq_map_user()��.                                                                                    
// ����,���Ǹղ�Ҳ������,bio ������,bio �� pages Ҳ����������ϵ,bio �� user buffer Ҳ������                                                                              
// ����ϵ,������͹�����?����Ȼ bio ��Ӧ�ú� request ������ϵ��,û���뵽 request �е� bio                                                                                
// �ɲ������õ� bio,request �� bio ֮��Ĺ�ϵ����ͼ��ʾ:                                                                                                                 
//  Linux  ��Щ�¶�֮���� Block��                                                                                                                                        
// �� 113  ҳ  �� 117  ҳ                                                                                                                                                
// ���������ľ��� 2373 �е��õ�blk_rq_bio_prep()����,���� block/ll_rw_blk.c:                                                                                         
   3669 void blk_rq_bio_prep(request_queue_t *q, struct request *rq, struct bio *bio)                                                                                 
   3670 {                                                                                                                                                             
   3671         // first two bits are identical in rq->cmd_flags and bio->bi_rw //                                                                                    
   3672         rq->cmd_flags |= (bio->bi_rw & 3);                                                                                                                    
   3673                                                                                                                                                               
   3674         rq->nr_phys_segments = bio_phys_segments(q, bio);                                                                                                     
   3675         rq->nr_hw_segments = bio_hw_segments(q, bio);                                                                                                         
   3676         rq->current_nr_sectors = bio_cur_sectors(bio);                                                                                                        
   3677         rq->hard_cur_sectors = rq->current_nr_sectors;                                                                                                        
   3678         rq->hard_nr_sectors = rq->nr_sectors = bio_sectors(bio);                                                                                              
   3679         rq->buffer = bio_data(bio);                                                                                                                           
   3680         rq->data_len = bio->bi_size;                                                                                                                          
   3681                                                                                                                                                               
   3682         rq->bio = rq->biotail = bio;                                                                                                                          
   3683 }                                                                                                                                                             
// ������ bio ��ʽ���� rq.                                                                                                                                               
// �ص�__blk_rq_map_user(),Ҳ�÷�����,2384 ��,���ص��� bio->bi_size.�ղ�˵����,���������                                                                                
// ���ռ䴫�����Ǹ� user buffer�ĳ���.                                                                                                                                   
// ���ص� blk_rq_map_user()��,�����������Ҳ�ý�����,�����Ļ������������ 0.���������                                                                                   
// ���ӳ�乤�̾����ǽ�����.Ȼ�����ѡ����д�峤���������,��Щ��bioʲôʱ���õ���?                                                                                    
// ��ʱ�ڽ� scsi �����ʱ�����û��ô˵��?��ʵ��ʱ�ڽ� scsi �����ʱ��,����ôһ����                                                                                      
// ��,scsi_setup_blk_pc_cmnd,�������1104�о����ж�req->bio�Ƿ�ΪNULL,�����ΪNULL,                                                                                      
// ������������Ӧ�Ĵ���,һ������ scsi_init_io()�ĺ����ᱻ����,�Ὠ��һ�� scatter-gather                                                                                
// ����������� bio �е����� bi_io_vec���Ӧ.                                                                                                                            
//                                                                                                                                                                       
// ��˵�е��ڴ�ӳ��(��)                                                                                                                                                  
// ��������������һ����ӳ�䡱����,blk_rq_map_kern().���������豸�����ڲ����� scsi                                                                                        
// mid-levelҪ����scsi������豸��ʱ��,���ǻ�����������.��������,�����ڽ�scsi�����                                                                                    
// ʱ�� , �� scsi_execute_req() ������ scsi_execute() ֮�� ,scsi_execute() �оͻ����                                                                                    
// blk_rq_map_kern()����.�����������Ӧ�÷��� 0,�ڵ���� scsi_execute()��,189 ��,�ж����                                                                                
// bufflen��Ϊ0��blk_rq_map_kern()Ҳ��Ϊ0,�ͺ�����ԥ����������,֮������˹���,����Ϊ,                                                                                    
// ���bufflen��Ϊ0,��˵�����scsi������Ҫ��������,��Ȼ��Ҫ��������,����Ҫ�õ�bio��                                                                                      
// ֧��,�� blk_rq_map_kern ������������ rq �� bio,bio �� pages �����ֽ���.���ķ���ֵ���                                                                               
// ��Ϊ 0,�����˵��������,��ô��Ȼ��������,scsi ����Ҳ��û��Ҫ����ִ����.                                                                                               
// Ok,��������Ĵ����,blk_rq_map_kern(),���� block/ll_rw_blk.c:                                                                                                         
//    2543 ///                                                                                                                                                           
//    2544  * blk_rq_map_kern - map kernel data to a request, for REQ_BLOCK_PC usage                                                                                     
//    2545  * @q:          request queue where request should be inserted                                                                                                
//    2546  * @rq:         request to fill                                                                                                                               
//    2547  * @kbuf:       the kernel buffer Linux  ��Щ�¶�֮���� Block��                                                                                               
// �� 114  ҳ  �� 117  ҳ                                                                                                                                                
//    2548  * @len:        length of user data                                                                                                                           
//    2549  * @gfp_mask:   memory allocation flags                                                                                                                       
//    2550  //                                                                                                                                                           
   2551 int blk_rq_map_kern(request_queue_t *q, struct request *rq, void *kbuf,                                                                                       
   2552                     unsigned int len, gfp_t gfp_mask)                                                                                                         
   2553 {                                                                                                                                                             
   2554         struct bio *bio;                                                                                                                                      
   2555                                                                                                                                                               
   2556         if (len > (q->max_hw_sectors << 9))                                                                                                                   
   2557                 return -EINVAL;                                                                                                                               
   2558         if (!len || !kbuf)                                                                                                                                    
   2559                 return -EINVAL;                                                                                                                               
   2560                                                                                                                                                               
   2561         bio = bio_map_kern(q, kbuf, len, gfp_mask);                                                                                                           
   2562         if (IS_ERR(bio))                                                                                                                                      
   2563                 return PTR_ERR(bio);                                                                                                                          
   2564                                                                                                                                                               
   2565          if (rq_data_dir(rq) == WRITE)                                                                                                                        
   2566                 bio->bi_rw |= (1 << BIO_RW);                                                                                                                  
   2567                                                                                                                                                               
   2568         blk_rq_bio_prep(q, rq, bio);                                                                                                                          
   2569         blk_queue_bounce(q, &rq->bio);                                                                                                                        
   2570         rq->buffer = rq->data = NULL;                                                                                                                         
   2571         return 0;                                                                                                                                             
   2572 }                                                                                                                                                             
// �� blk_rq_map_user()��ͬ����,����� kbuf ���ں˿ռ�� buffer.����һ�����˴�������۾�                                                                                 
// �ĺ���,��Ϊ��Ȼ kbuf ���ں˿ռ�� buffer,�� request Ҳ�Ǵ������ں˿ռ�,��ô��Ҷ���һ                                                                                 
// �����ϻ��,����ӳ��֮˵?��ʵ��,��Ȼ��������Գơ�map��,������ map ����û�й�ϵ,һ��                                                                                   
// �����ʵ������ǰ�map����ʻ���associate,û��Ҫ��map��ôһ����ƭ�ԵĴ�.����д����                                                                                       
// ������ô������Ҳû�취,�Ͼ�������ܻƺܱ�����ʱ��,�������ϵͳ���ڹ�������,�ڸ�                                                                                       
// ����.���� CCTV,��Ȼ�������Լ���������,��Ȼ���������ڼٽ�����,������������û�д�                                                                                       
// ����κ�����.��Ϊ�˸�<<������������Ŀ�������涨>>��̨����,��ϧ�������յ�����                                                                                        
// ��С������ȫ������˵��,�Դ���˵���������Ĵ�����ΰ�������ȷ��.������ֻ�������                                                                                        
// 13 ��ĺ����ܵ��˺�,ֻ�������籩����ͬ�����,ֻ���ô�Ҹ��������ʶ���Ǹ���ν��                                                                                       
// ȫ����������ߵĽ�Ŀ��������һ��ƭ�ӵ��ݵĻ��Զ��.                                                                                                                   
// Ok,�¹ܼٲ���,ֻ�п�����������.����,bio_map_kern()���� fs/bio.c:                                                                                                      
//     848 ///                                                                                                                                                           
//     849  *      bio_map_kern    -       map kernel address into bio                                                                                                   
//     850  *      @q: the request_queue_t for the bio                                                                                                                   
//     851  *      @data: pointer to buffer to map                                                                                                                       
//     852  *      @len: length in bytes                                                                                                                                 
//     853  *      @gfp_mask: allocation flags for bio allocation                                                                                                        
//     854  *                                                                                                                                                            
//     855  *      Map the kernel address into a bio suitable for io to a block Linux  ��Щ�¶�֮���� Block��                                                            
// �� 115  ҳ  �� 117  ҳ                                                                                                                                                
//     856  *      device. Returns an error pointer in case of error.                                                                                                    
    857  //                                                                                                                                                           
    858 struct bio *bio_map_kern(request_queue_t *q, void *data, unsigned int len,                                                                                    
    859                          gfp_t gfp_mask)                                                                                                                      
    860 {                                                                                                                                                             
    861         struct bio *bio;                                                                                                                                      
    862                                                                                                                                                               
    863         bio = __bio_map_kern(q, data, len, gfp_mask);                                                                                                         
    864         if (IS_ERR(bio))                                                                                                                                      
    865                 return bio;                                                                                                                                   
    866                                                                                                                                                               
    867         if (bio->bi_size == len)                                                                                                                              
    868                 return bio;                                                                                                                                   
    869                                                                                                                                                               
    870         //                                                                                                                                                    
    871          * Don't support partial mappings.                                                                                                                    
    872          //                                                                                                                                                   
    873         bio_put(bio);                                                                                                                                         
    874         return ERR_PTR(-EINVAL);                                                                                                                              
    875 }                                                                                                                                                             
__bio_map_kern()������ fs/bio.c:                                                                                                                                      
    811 static struct bio *__bio_map_kern(request_queue_t *q, void *data,                                                                                             
    812                                   unsigned int len, gfp_t gfp_mask)                                                                                           
    813 {                                                                                                                                                             
    814         unsigned long kaddr = (unsigned long)data;                                                                                                            
    815         unsigned long end = (kaddr + len + PAGE_SIZE - 1) >> PAGE_SHIFT;                                                                                      
    816         unsigned long start = kaddr >> PAGE_SHIFT;                                                                                                            
    817         const int nr_pages = end - start;                                                                                                                     
    818         int offset, i;                                                                                                                                        
    819         struct bio *bio;                                                                                                                                      
    820                                                                                                                                                               
    821         bio = bio_alloc(gfp_mask, nr_pages);                                                                                                                  
    822         if (!bio)                                                                                                                                             
    823                 return ERR_PTR(-ENOMEM);                                                                                                                      
    824                                                                                                                                                               
    825         offset = offset_in_page(kaddr);                                                                                                                       
    826         for (i = 0; i < nr_pages; i++) {                                                                                                                      
    827                 unsigned int bytes = PAGE_SIZE - offset;                                                                                                      
    828                                                                                                                                                               
    829                 if (len <= 0)                                                                                                                                 
    830                         break;                                                                                                                                
    831                                                                                                                                                               
    832                 if (bytes > len)                                                                                                                              
    833                         bytes = len; Linux  ��Щ�¶�֮���� Block��                                                                                            
�� 116  ҳ  �� 117  ҳ                                                                                                                                                
    834                                                                                                                                                               
    835                 if (bio_add_pc_page(q, bio, virt_to_page(data), bytes,                                                                                        
    836                                     offset) < bytes)                                                                                                          
    837                         break;                                                                                                                                
    838                                                                                                                                                               
    839                 data += bytes;                                                                                                                                
    840                 len -= bytes;                                                                                                                                 
    841                 offset = 0;                                                                                                                                   
    842         }                                                                                                                                                     
    843                                                                                                                                                               
    844         bio->bi_end_io = bio_map_kern_endio;                                                                                                                  
    845         return bio;                                                                                                                                           
    846 }                                                                                                                                                             
// ��ϸ�Ա�һ�����������__bio_map_user_iov(),���ѷ���,���ʵĲ�ͬ���ǲ����Ǹ�                                                                                            
// get_user_page()����,�����������������һ����.һ������ bio_alloc ������ bio ���ڴ�,һ��                                                                                
// ���� bio_add_pc_page()���� bio ��pages ����ϵ����.                                                                                                                    
// ˵���ڴ��������⻰,virt_to_page(),�����ǰ�һ�������ַת��Ϊһ�� page.ע�������                                                                                    
// data ʵ���Ͼ���ǰ�� blk_rq_map_kern()���������Ǹ� kbuf,�������׷�ݹ�ȥ,ȥ��                                                                                          
// scsi_execute()�����ص�scsi_execute_req(),����ȥ����Щ����scsi_execute_req()�ĵط�,������                                                                              
// sd ģ����,sd_revalidate_disk()������,����ôһ��,                                                                                                                      
   1518         buffer = kmalloc(SD_BUF_SIZE, GFP_KERNEL | __GFP_DMA);                                                                                                
������ôһ��,                                                                                                                                                         
   1540                 sd_read_capacity(sdkp, buffer);                                                                                                               
// ������֪�� sd_read_capacity()����� scsi_execute_req()��ִ�� Read Capacity ����.�������                                                                              
// kernel-space �� buffer �������Դ����������� kmalloc.���� x86 ϵͳ��˵,����ڴ������                                                                                
// ��ӳ�����ں˿ռ���Ǹ�896M���µ��ڴ�.��Ϊvirt_to_page�������Ӳ��Ҫ��,���Ĳ�����                                                                                      
// ���������Χ�ڵ��ڴ�.                                                                                                                                                 
// ���,844 ��,bio�ĳ�Աbi_end_ioָ�����һ������,��������������bio��Ӧ��io������                                                                                      
// ����ʱ�򱻵���.��������֪��,�ڲ��õĿ��Կ����Ľ�����ĳһ��,bio_map_kern_endio()��                                                                                     
// ���ᱻ����.���������������ʲô�����°���,���� fs/bio.c:                                                                                                              
    801 static int bio_map_kern_endio(struct bio *bio, unsigned int bytes_done, int err)                                                                              
    802 {                                                                                                                                                             
    803         if (bio->bi_size)                                                                                                                                     
    804                 return 1;                                                                                                                                     
    805                                                                                                                                                               
    806         bio_put(bio);                                                                                                                                         
    807         return 0;                                                                                                                                             
    808 }                                                                                                                                                             
// ������bio_map_kern()֮��,�ص�blk_rq_map_kern().һ��Ҫ����blk_rq_bio_prep()����bio��                                                                                   
// rq ��ϵ����.��֮����� blk_queue_bounce()��Ϊ�˽��� bounce buffer,��buffer pages ���ʺ�                                                                               
// ��� I/O������ʱ����Ҫ���� bounce buffer,�����豸����������,ֻ�ܷ���ĳЩ pages.                                                                                       
// ����һ����Linux��ͬ��Hugh Dickins�Ļ�˵����,it is substituting bounce buffers if the buffer                                                                           
// pages are unsuited to this I/O,e.g. device limited in the address range of pages it can access.����                                                                   
// blk_queue_bounce ���ǾͲ���˵��.�Ͼ������������Ҫ�õ�.�����Ҫ bounce buffer,��ô��Linux  ��Щ�¶�֮���� Block��                                                     
// �� 117  ҳ  �� 117  ҳ                                                                                                                                                
// struct request_queue�п�������,��Ϊ����һ����Ա,unsigned long bounce_pfn,��Ҫ���õĿ�                                                                                 
// �Ե��ú��� blk_queue_bounce_limit()������.��������ǰ�濴����__scsi_alloc_queue()����,                                                                                 
// �͵����� blk_queue_bounce_limit().                                                                                                                                    
//    1581         blk_queue_bounce_limit(q, scsi_calculate_bounce_limit(shost));                                                                                        
// ��������ʮ��İ��Ծ���,��������רҵ�İ���ˮ׼,��ô�����ȥ�������                                                                                                
// scsi_calculate_bounce_limit,������� drivers/scsi/scsi_lib.c �еĺ���.                                                                                                
   1547 u64 scsi_calculate_bounce_limit(struct Scsi_Host *shost)                                                                                                      
   1548 {                                                                                                                                                             
   1549         struct device *host_dev;                                                                                                                              
   1550         u64 bounce_limit = 0xffffffff;                                                                                                                        
   1551                                                                                                                                                               
   1552         if (shost->unchecked_isa_dma)                                                                                                                         
   1553                 return BLK_BOUNCE_ISA;                                                                                                                        
   1554         //                                                                                                                                                    
   1555          * Platforms with virtual-DMA translation                                                                                                             
   1556          * hardware have no practical limit.                                                                                                                  
   1557          //                                                                                                                                                   
   1558         if (!PCI_DMA_BUS_IS_PHYS)                                                                                                                             
   1559                 return BLK_BOUNCE_ANY;                                                                                                                        
   1560                                                                                                                                                               
   1561         host_dev = scsi_get_device(shost);                                                                                                                    
   1562         if (host_dev && host_dev->dma_mask)                                                                                                                   
   1563                 bounce_limit = *host_dev->dma_mask;                                                                                                           
   1564                                                                                                                                                               
   1565         return bounce_limit;                                                                                                                                  
   1566 }                                                                                                                                                             
// �����϶��� scsi �豸��˵,��Ҫ����Ҫ bounce buffer,��Ҫ���� scsi host ˵����,��Ϊ scsi ����                                                                            
// ����,host��һ��֮��,device�Ǵ�����host��.�ͺñ��ű����ЩŮ�����ܲ��ܱ�����,�ܲ���                                                                                    
// �ӵ����߱�ɵ�����,�ܲ��ܴӵ����߱�ɵ�����,�ؼ������ű�˵����,��Ϊ����ޱ������                                                                                       
// �ӷ�������̨Ϸ��,���������ǻ����ű�.                                                                                                                                  
// ����ܽ�һ��,blk_rq_map_user()�� blk_rq_map_kern(),��ʵ�һ����Ǿ仰,map ������õò�                                                                                  
// �Ǻܺ���,����һ��Ӧ�ý� associate,��Ϊ��������������,ӳ�䲢��������Ҫ��,����Ҫ����                                                                                    
// ��ϵ,����˵�¹������û��ռ��buffer�����ں˿ռ��buffer,��Block�㶼����,��ֻ��bio,                                                                                    
// �ҵ���Щ����ֻ�� bio �򽻵�.�������������Ҳ�ܳ���,�ͱ�����ϵĳ���Ա���г�����                                                                                     
// �ڲ�Ʊ��ʱ��,��������м���,���ǵ�̬��һ����ֻ��֤������.��������û���������ǵ�                                                                                       
// ���������������Ļ���,��λ�г�������Ǹ�ֻ�а������,�Ǹ�����һ�źͲм���Ʊһ��                                                                                      
// �۸��Ʊ��������ʱ,˵���Ǿ���������Ļ�:������ֻ��֤������!�вм�֤���ǲм���,û                                                                                      
// �вм�֤��ô��֤�����ǲм��˰�?��                                                                                                                                     
// ���ڿ�Դ��������û����ô����,�����ǿ���,��Ȼ����Ҫ���� bio,���� buffer,���ǱϾ� bio                                                                                   
// ���Ժ� page ����ϵ,page ���Ժ����Ե�ַ����ϵ,�����������ǵĽ����������ͨ��������                                                                                     
// ������ buffer ����˵�� buffer ����Ӧ�ĵ�ַ�� bio ��ϵ����,����Ǹ���,��ӳ��ֻ�Ǵﵽ��                                                                                 
// һĿ������ȡ���ֶ�,����ֻ���û��ռ�� buffer ���д�����.(��Ȼ�����ϲ����ţ�Ǽ�,��                                                                                    
// ��Ҳ����˵�ں˿ռ�� buffer Ҳ��ӳ����˵�,��Ϊ kmalloc()������ڴ汾�����ӳ�����                                                                                   
// ���ڴ�,�����ⶼ����ν.)                                                                                                                                               