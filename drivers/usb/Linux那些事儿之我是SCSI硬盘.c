// Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                                          
//                                                                                                                                                         
//                                                                                                                                                         
//                                                                                                                                                         
//                                                                                                                                                         
// Linux��Щ�¶�                                                                                                                                           
// ϵ�д���                                                                                                                                                
// ֮                                                                                                                                                      
// ����SCSIӲ��                                                                                                                                            
// SCSI disk�����������,                                                                                                                                  
// 2.6.22.1,ΪSCSI��ϵͳ�������̵�.                                                                                                                        
//                                                                                                                                                         
// ��ԭ��Ϊblog.csdn.net/fudan_abc �ϵġ�linux ��Щ�¶�֮SCSIӲ�̡������������µĻ�������������Ŀ���                                                      
// ���������ͣ�Ҳ����email ��ilttv.cn@gmail.com                                                                                                            
// �� 1  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                      
// Ŀ¼                                                                                                                                                    
// Ŀ¼..................................................................................................................................................2 
// ����..................................................................................................................................................3 
// ��򵥵���ʼ��...............................................................................................................................4          
// ��Ȼprobe .........................................................................................................................................9    
// ���̴����㶯����! .......................................................................................................................17             
// ������ɽ(һ) ..................................................................................................................................26       
// ������ɽ(��) ..................................................................................................................................33       
// ������ɽ(��) ..................................................................................................................................37       
// ��Ӧ�ò�������ioctl......................................................................................................................44             
// �� 2  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                      
//                                                                                                                                                         
// ����                                                                                                                                                    
//                                                                                                                                                         
// ��һ����������:"��Ҫ��ʹ��,ҽ���������,��ʹ��˭�����ΰ�?"������˵:"��ֻ���Լ���                                                                        
// �Լ���."Ҳ����Ϊ����,ÿ���˶���һ�������Լ�������ʹ�ķ���.�Ⱦ�,����,����,��޻�Ц,                                                                      
// �������߿�,������,��������,����һ�ַ������ӱ�������ʹ.�ҵķ�����д����α������                                                                        
// ����.                                                                                                                                                   
// ����дЩʲô��?��Ȼ����д��USB,��Ȼ����д��PCI,��ô�����дSCSI,�������������                                                                          
// ��������.                                                                                                                                               
// ��˵���ǹ�˾��,��������ôЩ������,��̨û��SCSI�豸?SCSIӲ��,SCSI����,���ָ�����                                                                         
// SCSI�豸�ڻ����ﶼ���ҵ�.������û��SCSI�豸,�ͺñȳ���Ů����û������ӱ.������һ                                                                         
// ֱ�ܺ������֪��,֮������Щ�� SCSI ������ô��,�ǲ�����Ϊ�����ߺ�ܽ�ؽ��� S ����                                                                       
// һ������һ������һ������?�������ֺ�����,�ҿ�ʼ��̽��SCSI��ϵͳ�ĵ�·,����������                                                                         
// �Ӽ򵥵�ʵ����ʼ,����򵥵�ʵ������ SCSI Ӳ��(SCSI DISK).                                                                                               
// д SCSI Ӳ����������ʵ����Ҳ�Ƕ� usb-storage ��һ������.SCSI Ӳ��������Ӧ��һ��ģ                                                                       
// ��,sd_mod.o.usb-storage Ҫ�������Ⱦ͵����������� scsi ��ģ��,һ���� scsi ����ģ��                                                                       
// scsi_mod.o,һ��������� scsi Ӳ�̵�����ģ�� sd_mod.o.                                                                                                   
// ����·,�������Ǵ� drivers/scsi Ŀ¼������� Kconfig �ļ������������ scsi disk ��.                                                                      
//      58 config BLK_DEV_SD                                                                                                                               
//      59         tristate "SCSI disk support"                                                                                                            
//      60         depends on SCSI                                                                                                                         
//      61         ---help---                                                                                                                              
//      62           If you want to use SCSI hard disks, Fibre Channel disks,                                                                              
//      63           Serial ATA (SATA) or Parallel ATA (PATA) hard disks,                                                                                  
//      64           USB storage or the SCSI or parallel port version of                                                                                   
//      65           the IOMEGA ZIP drive, say Y and read the SCSI-HOWTO,                                                                                  
//      66           the Disk-HOWTO and the Multi-Disk-HOWTO, available from                                                                               
//      67           <http://www.tldp.org/docs.html#howto>. This is NOT for SCSI                                                                           
//      68           CD-ROMs.                                                                                                                              
//      69                                                                                                                                                 
//      70           To compile this driver as a module, choose M here and read                                                                            
//      71           <file:Documentation/scsi/scsi.txt>.                                                                                                   
//      72           The module will be called sd_mod.                                                                                                     
//      73                                                                                                                                                 
//      74           Do not compile this driver as a module if your root file system                                                                       
//      75           (the one containing the directory /) is located on a SCSI disk.                                                                       
//      76           In this case, do not compile the driver for your SCSI host adapter                                                                    
//      77           (below) as a module either.                                                                                                           
// �����depends on SCSI��˵�ľ��� scsi core.��������,scsi �ܵÿ�,ȫƾ core ����.���е� scsi ģ                                                            
// �鶼�ǻ��� scsi core ��.                                                                                                                                
// ������ Makefile,drivers/scsi Ŀ¼�µ� Makefile,�������� 190 ��,��������������ע�������                                                                 
// �� 3  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                      
// ���⼸��,                                                                                                                                               
//     140 obj-$(CONFIG_BLK_DEV_SD)        += sd_mod.o                                                                                                     
//     141 obj-$(CONFIG_BLK_DEV_SR)        += sr_mod.o                                                                                                     
//     142 obj-$(CONFIG_CHR_DEV_SG)        += sg.o                                                                                                         
//     143 obj-$(CONFIG_CHR_DEV_SCH)       += ch.o                                                                                                         
//     144                                                                                                                                                 
//     145 # This goes last, so that "real" scsi devices probe earlier                                                                                     
//     146 obj-$(CONFIG_SCSI_DEBUG)        += scsi_debug.o                                                                                                 
//     147                                                                                                                                                 
//     148 obj-$(CONFIG_SCSI_WAIT_SCAN)    += scsi_wait_scan.o                                                                                             
//     149                                                                                                                                                 
//     150 scsi_mod-y                      += scsi.o hosts.o scsi_ioctl.o constants.o \                                                                    
//     151                                    scsicam.o scsi_error.o scsi_lib.o \                                                                          
//     152                                    scsi_scan.o scsi_sysfs.o \                                                                                   
//     153                                    scsi_devinfo.o                                                                                               
//     154 scsi_mod-$(CONFIG_SCSI_NETLINK) += scsi_netlink.o                                                                                               
//     155 scsi_mod-$(CONFIG_SYSCTL)       += scsi_sysctl.o                                                                                                
//     156 scsi_mod-$(CONFIG_SCSI_PROC_FS) += scsi_proc.o                                                                                                  
//     157                                                                                                                                                 
//     158 scsi_tgt-y                      += scsi_tgt_lib.o scsi_tgt_if.o                                                                                 
//     159                                                                                                                                                 
//     160 sd_mod-objs     := sd.o                                                                                                                         
// 140 �к� 160 ��,���������㹻�ľ�ϲ.��Ϊ SCSI Disk ������ֻ��һ���ļ�,sd.c.���ǳ�һ��                                                                    
// ����ļ��ж��,                                                                                                                                         
// localhost:/usr/src/linux-2.6.22.1/drivers/scsi # wc -l sd.c                                                                                             
// 1903 sd.c                                                                                                                                               
// ���� 1903 ��,��һ��ģ��ֻ����ô�㳤��ʱ��,һ·�������ֵ��ǿ����Ѿ���������������                                                                        
// ���ϲ�˰�.���������������,�������������ڶ���Ķ��,�����ڳ̶ȵ���ǳ;���������                                                                        
// �����������Ķ��,�����ڱ�����ѧ˼�����ǳ.                                                                                                              
//                                                                                                                                                         
// ��򵥵���ʼ��                                                                                                                                          
// ����ãã�˺���,���ҵ���������,                                                                                                                          
//    1886 module_init(init_sd);                                                                                                                           
//    1887 module_exit(exit_sd);                                                                                                                           
// ��Ҫ����������������,�����������¾���Χ����drivers/sd.c��ôһ���ļ�չ��,���Գ�����                                                                      
// ��������֮��,������������ļ�.                                                                                                                          
//    1831 ///                                                                                                                                             
//    1832  *      init_sd - entry point for this driver (both when built in or when                                                                       
//    1833  *      a module).                                                                                                                              
//    1834  *                                                                                                                                              
//    1835  *      Note: this function registers this driver with the scsi mid-level.                                                                      
// �� 4  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                      
//    1836  ///                                                                                                                                            
   1837 static int __init init_sd(void)                                                                                                                 
   1838 {                                                                                                                                               
   1839         int majors = 0, i, err;                                                                                                                 
   1840                                                                                                                                                 
   1841         SCSI_LOG_HLQUEUE(3, printk("init_sd: sd driver entry point\n"));                                                                        
   1842                                                                                                                                                 
   1843         for (i = 0; i < SD_MAJORS; i++)                                                                                                         
   1844                 if (register_blkdev(sd_major(i), "sd") == 0)                                                                                    
   1845                         majors++;                                                                                                               
   1846                                                                                                                                                 
   1847         if (!majors)                                                                                                                            
   1848                 return -ENODEV;                                                                                                                 
   1849                                                                                                                                                 
   1850         err = class_register(&sd_disk_class);                                                                                                   
   1851         if (err)                                                                                                                                
   1852                 goto err_out;                                                                                                                   
   1853                                                                                                                                                 
   1854         err = scsi_register_driver(&sd_template.gendrv);                                                                                        
   1855         if (err)                                                                                                                                
   1856                 goto err_out_class;                                                                                                             
   1857                                                                                                                                                 
   1858         return 0;                                                                                                                               
   1859                                                                                                                                                 
   1860 err_out_class:                                                                                                                                  
   1861         class_unregister(&sd_disk_class);                                                                                                       
   1862 err_out:                                                                                                                                        
   1863         for (i = 0; i < SD_MAJORS; i++)                                                                                                         
   1864                 unregister_blkdev(sd_major(i), "sd");                                                                                           
   1865         return err;                                                                                                                             
   1866 }                                                                                                                                               
   1867                                                                                                                                                 
   1868 ///                                                                                                                                             
   1869  *      exit_sd - exit point for this driver (when it is a module).                                                                             
   1870  *                                                                                                                                              
   1871  *      Note: this function unregisters this driver from the scsi mid-level.                                                                    
   1872  ///                                                                                                                                            
   1873 static void __exit exit_sd(void)                                                                                                                
   1874 {                                                                                                                                               
   1875         int i;                                                                                                                                  
   1876                                                                                                                                                 
   1877         SCSI_LOG_HLQUEUE(3, printk("exit_sd: exiting sd driver\n"));                                                                            
   1878                                                                                                                                                 
   1879         scsi_unregister_driver(&sd_template.gendrv);                                                                                            
�� 5  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                      
   1880         class_unregister(&sd_disk_class);                                                                                                       
   1881                                                                                                                                                 
   1882         for (i = 0; i < SD_MAJORS; i++)                                                                                                         
   1883                 unregister_blkdev(sd_major(i), "sd");                                                                                           
   1884 }                                                                                                                                               
// ûʲô�ر��,һ����ע��ע������.                                                                                                                        
// ����,register_blkdev,ע��һ�����豸.�������Ҳ���ǹǻҼ�����,N ��ǰ�������������.��                                                                    
// ʱ�������������Ϊ���������ֻ�������豸,���豸,�ַ��豸,�����豸.�����������粢                                                                        
// ����ô��,����Ҳ������ô��,����,��,�ܼ�,��,�ܼ�,������ȴ����.                                                                                  
// ��������һ�����������Ч��,����sd_mod ֮ǰ,                                                                                                             
// localhost:~ # cat /proc/devices                                                                                                                         
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
 29 fb                                                                                                                                                  
128 ptm                                                                                                                                                 
136 pts                                                                                                                                                 
                                                                                                                                                        
Block devices:                                                                                                                                          
  1 ramdisk                                                                                                                                             
  3 ide0                                                                                                                                                
  7 loop                                                                                                                                                
  9 md                                                                                                                                                  
253 device-mapper                                                                                                                                       
254 mdp                                                                                                                                                 
��ͨ������������������� scsi_mod �� sd_mod ֮��,                                                                                                       
localhost:~ # modprobe scsi_mod                                                                                                                         
localhost:~ # modprobe sd_mod                                                                                                                           
localhost:~ # cat /proc/devices                                                                                                                         
Character devices:                                                                                                                                      
  1 mem                                                                                                                                                 
  2 pty                                                                                                                                                 
  3 ttyp                                                                                                                                                
  4 /dev/vc/0                                                                                                                                           
�� 6  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                      
  4 tty                                                                                                                                                 
  4 ttyS                                                                                                                                                
  5 /dev/tty                                                                                                                                            
  5 /dev/console                                                                                                                                        
  5 /dev/ptmx                                                                                                                                           
  7 vcs                                                                                                                                                 
 10 misc                                                                                                                                                
 13 input                                                                                                                                               
 29 fb                                                                                                                                                  
128 ptm                                                                                                                                                 
136 pts                                                                                                                                                 
                                                                                                                                                        
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
133 sd                                                                                                                                                  
134 sd                                                                                                                                                  
135 sd                                                                                                                                                  
253 device-mapper                                                                                                                                       
254 mdp                                                                                                                                                 
// ���Կ���,����һ������ sd �ļһ�.                                                                                                                        
// ������ֵĺ�SD_MAJORSʵ���ϱ�����Ϊ16.���Ծ���16��ѭ��֮��,���ǿ��������sd                                                                             
// ���� 16 ��.                                                                                                                                             
// ������˵��Щ��������ô����,����˹��������й��Ϸ�������Χһ��,ÿ�����ҷ�һƬ��,                                                                         
// ��Linux�����е����豸��Ҳ�Ǳ����ָ������豸���Ϸ�.����,8,65-71,136-143��ô��16��                                                                        
// ����ͱ� scsi disk ����ռ��.sd_major()�����ķ���ֵ������ 16������.ÿ�����豸�ſ��Դ�                                                                    
// 256 �����豸��.                                                                                                                                         
// 1850 ��, class_register,���е�Ч������,                                                                                                                 
// localhost:~ # ls /sys/class/                                                                                                                            
// �� 7  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                      
// backlight  dma  graphics  input  mem  misc  net  pci_bus  scsi_device  scsi_disk                                                                        
// scsi_host  spi_master  tty  vc  vtconsole                                                                                                               
// ������������ scsi_disk��ô?�����class_register���ɵĺ���.                                                                                            
// �� 1854 ��,scsi_register_driver ���ǳ������ע��һ�� scsi �豸����.ΰ����豸ģ�͸�����                                                                 
// �Ƕ���ÿ���豸����,��һ����֮��Ӧ�� struct device_driver �ṹ��,��Ϊ�����ָ����豸��                                                                    
// ��������ص�,������ϵͳ���Զ����Լ��Ľṹ��,Ȼ��� struct device_driver ����������                                                                      
// C++�л������չ��һ��.����scsi��ϵͳ,����������struct scsi_driver,����ṹ�屾��                                                                    
// ���� include/scsi/scsi_driver.h:                                                                                                                        
     10 struct scsi_driver {                                                                                                                            
     11         struct module           *owner;                                                                                                         
     12         struct device_driver    gendrv;                                                                                                         
     13                                                                                                                                                 
     14         int (*init_command)(struct scsi_cmnd *);                                                                                                
     15         void (*rescan)(struct device *);                                                                                                        
     16         int (*issue_flush)(struct device *, sector_t *);                                                                                        
     17         int (*prepare_flush)(struct request_queue *, struct request *);                                                                         
     18 };                                                                                                                                              
������Ҳ��Ȼ������һ�� scsi_driver�Ľṹ��ʵ��.�������ֽ��� sd_template.                                                                                
    232 static struct scsi_driver sd_template = {                                                                                                       
    233         .owner                  = THIS_MODULE,                                                                                                  
    234         .gendrv = {                                                                                                                             
    235                 .name           = "sd",                                                                                                         
    236                 .probe          = sd_probe,                                                                                                     
    237                 .remove         = sd_remove,                                                                                                    
    238                 .suspend        = sd_suspend,                                                                                                   
    239                 .resume         = sd_resume,                                                                                                    
    240                 .shutdown       = sd_shutdown,                                                                                                  
    241         },                                                                                                                                      
    242         .rescan                 = sd_rescan,                                                                                                    
    243         .init_command           = sd_init_command,                                                                                              
    244         .issue_flush            = sd_issue_flush,                                                                                               
    245 };                                                                                                                                              
// ������,gendrv ���� struct device_driver�Ľṹ�����.������ôһע��,��ֱ��Ч������:                                                                      
// localhost:~ # ls /sys/bus/scsi/drivers/                                                                                                                 
// sd                                                                                                                                                      
// �����������������෴�ľ��� exit_sd()�е���������                                                                                                      
// ,scsi_unregister_driver,class_unregister,unregister_blkdev.������벻���Ҷ�˵,�������⻪��                                                              
// �����ſ�����������Ǽ�λ���Ƕ�Ҳ��������ô����.                                                                                                         
// Okay ��,�����ʼ������ô��,����ô������.��� uhci-hcd ���Ǹ���ʼ��,�����ȷ�򵥵�                                                                     
// ������.ʵ��ʵ˵,SCSI Ӳ������ȷʵ��ͦ�򵥵�.��һ�����Ǿʹ� sd_probe ��������,ĳ����                                                                     
// ����˵,�� sd_mod �Ĵ�������Ƕ� scsi ��ϵͳ������.                                                                                                      
//                                                                                                                                                         
// �� 8  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                      
// ��Ȼ probe                                                                                                                                              
// ��Ȼscsi disk����,�����������Ϊscsi disk���ģ��ÿ����������init_sd()һ����,��ô��                                                                   
// ֻ��˵���������ֱ�֩��ҧ�˾���Ϊ�Լ���֩����,���׵����˾���Ϊ�Լ���������,����һ                                                                        
// �θ�ѹ�����Ϊ�Լ������ϼ.�㲻��?��������sd_probe,��������Ͳ�����ô��.                                                                              
//    1566 ///                                                                                                                                             
//    1567  *      sd_probe - called during driver initialization and whenever a                                                                           
//    1568  *      new scsi device is attached to the system. It is called once                                                                            
//    1569  *      for each scsi device (not just disks) present.                                                                                          
//    1570  *      @dev: pointer to device object                                                                                                          
//    1571  *                                                                                                                                              
//    1572  *      Returns 0 if successful (or not interested in this scsi device                                                                          
//    1573  *      (e.g. scanner)); 1 when there is an error.                                                                                              
//    1574  *                                                                                                                                              
//    1575  *      Note: this function is invoked from the scsi mid-level.                                                                                 
//    1576  *      This function sets up the mapping between a given                                                                                       
//    1577  *      <host,channel,id,lun> (found in sdp) and new device name                                                                                
//    1578  *      (e.g. /dev/sda). More precisely it is the block device major                                                                            
//    1579  *      and minor number that is chosen here.                                                                                                   
//    1580  *                                                                                                                                              
//    1581  *      Assume sd_attach is not re-entrant (for time being)                                                                                     
//    1582  *      Also think about sd_attach() and sd_remove() running coincidentally.                                                                    
//    1583  ///                                                                                                                                            
   1584 static int sd_probe(struct device *dev)                                                                                                         
   1585 {                                                                                                                                               
   1586         struct scsi_device *sdp = to_scsi_device(dev);                                                                                          
   1587         struct scsi_disk *sdkp;                                                                                                                 
   1588         struct gendisk *gd;                                                                                                                     
   1589         u32 index;                                                                                                                              
   1590         int error;                                                                                                                              
   1591                                                                                                                                                 
   1592         error = -ENODEV;                                                                                                                        
   1593         if (sdp->type != TYPE_DISK && sdp->type != TYPE_MOD &&                                                                                  
sdp->type != TYPE_RBC)                                                                                                                                  
   1594                 goto out;                                                                                                                       
   1595                                                                                                                                                 
   1596         SCSI_LOG_HLQUEUE(3, sdev_printk(KERN_INFO, sdp,                                                                                         
   1597                                         "sd_attach\n"));                                                                                        
   1598                                                                                                                                                 
   1599         error = -ENOMEM;                                                                                                                        
   1600         sdkp = kzalloc(sizeof(*sdkp), GFP_KERNEL);                                                                                              
   1601         if (!sdkp)                                                                                                                              
   1602                 goto out;                                                                                                                       
�� 9  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                      
   1603                                                                                                                                                 
   1604         gd = alloc_disk(16);                                                                                                                    
   1605         if (!gd)                                                                                                                                
   1606                 goto out_free;                                                                                                                  
   1607                                                                                                                                                 
   1608         if (!idr_pre_get(&sd_index_idr, GFP_KERNEL))                                                                                            
   1609                 goto out_put;                                                                                                                   
   1610                                                                                                                                                 
   1611         spin_lock(&sd_index_lock);                                                                                                              
   1612         error = idr_get_new(&sd_index_idr, NULL, &index);                                                                                       
   1613         spin_unlock(&sd_index_lock);                                                                                                            
   1614                                                                                                                                                 
   1615         if (index >= SD_MAX_DISKS)                                                                                                              
   1616                 error = -EBUSY;                                                                                                                 
   1617         if (error)                                                                                                                              
   1618                 goto out_put;                                                                                                                   
   1619                                                                                                                                                 
   1620         sdkp->device = sdp;                                                                                                                     
   1621         sdkp->driver = &sd_template;                                                                                                            
   1622         sdkp->disk = gd;                                                                                                                        
   1623         sdkp->index = index;                                                                                                                    
   1624         sdkp->openers = 0;                                                                                                                      
   1625                                                                                                                                                 
   1626         if (!sdp->timeout) {                                                                                                                    
   1627                 if (sdp->type != TYPE_MOD)                                                                                                      
   1628                         sdp->timeout = SD_TIMEOUT;                                                                                              
   1629                 else                                                                                                                            
   1630                         sdp->timeout = SD_MOD_TIMEOUT;                                                                                          
   1631         }                                                                                                                                       
   1632                                                                                                                                                 
   1633         class_device_initialize(&sdkp->cdev);                                                                                                   
   1634         sdkp->cdev.dev = &sdp->sdev_gendev;                                                                                                     
   1635         sdkp->cdev.class = &sd_disk_class;                                                                                                      
   1636         strncpy(sdkp->cdev.class_id, sdp->sdev_gendev.bus_id, BUS_ID_SIZE);                                                                     
   1637                                                                                                                                                 
   1638         if (class_device_add(&sdkp->cdev))                                                                                                      
   1639                 goto out_put;                                                                                                                   
   1640                                                                                                                                                 
   1641         get_device(&sdp->sdev_gendev);                                                                                                          
   1642                                                                                                                                                 
   1643         gd->major = sd_major((index & 0xf0) >> 4);                                                                                              
   1644         gd->first_minor = ((index & 0xf) << 4) | (index & 0xfff00);                                                                             
   1645         gd->minors = 16;                                                                                                                        
   1646         gd->fops = &sd_fops;                                                                                                                    
�� 10  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
   1647                                                                                                                                                 
   1648         if (index < 26) {                                                                                                                       
   1649                 sprintf(gd->disk_name, "sd%c", 'a' + index % 26);                                                                               
   1650         } else if (index < (26 + 1) * 26) {                                                                                                     
   1651                 sprintf(gd->disk_name, "sd%c%c",                                                                                                
   1652                         'a' + index / 26 - 1,'a' + index % 26);                                                                                 
   1653         } else {                                                                                                                                
   1654                 const unsigned int m1 = (index / 26 - 1) / 26 - 1;                                                                              
   1655                 const unsigned int m2 = (index / 26 - 1) % 26;                                                                                  
   1656                 const unsigned int m3 =  index % 26;                                                                                            
   1657                 sprintf(gd->disk_name, "sd%c%c%c",                                                                                              
   1658                         'a' + m1, 'a' + m2, 'a' + m3);                                                                                          
   1659         }                                                                                                                                       
   1660                                                                                                                                                 
   1661         gd->private_data = &sdkp->driver;                                                                                                       
   1662         gd->queue = sdkp->device->request_queue;                                                                                                
   1663                                                                                                                                                 
   1664         sd_revalidate_disk(gd);                                                                                                                 
   1665                                                                                                                                                 
   1666         gd->driverfs_dev = &sdp->sdev_gendev;                                                                                                   
   1667         gd->flags = GENHD_FL_DRIVERFS;                                                                                                          
   1668         if (sdp->removable)                                                                                                                     
   1669                 gd->flags |= GENHD_FL_REMOVABLE;                                                                                                
   1670                                                                                                                                                 
   1671         dev_set_drvdata(dev, sdkp);                                                                                                             
   1672         add_disk(gd);                                                                                                                           
   1673                                                                                                                                                 
   1674         sd_printk(KERN_NOTICE, sdkp, "Attached SCSI %sdisk\n",                                                                                  
   1675                   sdp->removable ? "removable " : "");                                                                                          
   1676                                                                                                                                                 
   1677         return 0;                                                                                                                               
   1678                                                                                                                                                 
   1679  out_put:                                                                                                                                       
   1680         put_disk(gd);                                                                                                                           
   1681  out_free:                                                                                                                                      
   1682         kfree(sdkp);                                                                                                                            
   1683  out:                                                                                                                                           
   1684         return error;                                                                                                                           
   1685 }                                                                                                                                               
// ������ǲ�����������,��������ô֪���Լ��������Ҹ�����?������ǲ��� probe,��������                                                                       
// ô֪���豸�����Ĺ��������չ������?                                                                                                                     
// ����,����Ϊscsi device ׼��һ��ָ��,struct scsi_device *sdp,Ϊ scsi disk ׼��һ��ָ��,struct                                                            
// scsi_disk *sdkp,����,�¹���scsiӲ�̻���ideӲ��,���ٲ���һ���ṹ��struct gendisk,������                                                                  
// ��׼����һ��ָ�� struct gendisk *gd.                                                                                                                    
// �� 11  ҳ �� 54 ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                       
// һ·�������ֵ���һ��֪��,sd_probe ������ scsi ���Ĳ����,����Ҳ�� scsi mid-level ����                                                                   
// ��.scsi mid-level �ڵ��� sd_probe ֮ǰ,�Ѿ�Ϊ��� scsi �豸׼������ struct device,struct                                                                
// scsi_device,�Ѿ�Ϊ���������˳�ʼ��,�������� struct device *dev ��Ϊ�������ݽ������Ǿ�                                                                   
// ����ֱ���������ĳ�Ա��.                                                                                                                                 
// �ⲻ,1593��,�Ϳ�ʼ�ж�sdp->type,����struct scsi_device�ṹ���еĳ�Աchar type,��������                                                                  
// �����scsi�豸���������͵�,scsi�豸�廨����,��ֻ�������г�������������sd_mod��֧                                                                        
// �ֵ�.��������������Ϥ�ĵ��� TYPE_DISK,��������ͨ�� scsi ����,�� TYPE_MOD ��ʾ��                                                                         
// �ǴŹ���(Magneto-Optical disk),һ�ֲ��ü���ʹų���ͬ���õĴŹⷽʽ�洢����ʵ�ֵ�                                                                       
// ����,��ۺ� 3.5 Ӣ����������,����Ҳ��֪��,���Բ���˵��.����,TYPE_RBC Ҳ����������                                                                       
// ��,RBC ��ʾReduced Block Commands,���Ľ����,���Ҳ���ض�˵.                                                                                          
// 1600 ��,Ϊ sdkp �����ڴ�.struct scsi_disk ������ include/scsi/sd.h:                                                                                     
     34 struct scsi_disk {                                                                                                                              
     35         struct scsi_driver *driver;     // always &sd_template //                                                                               
     36         struct scsi_device *device;                                                                                                             
     37         struct class_device cdev;                                                                                                               
     38         struct gendisk  *disk;                                                                                                                  
     39         unsigned int    openers;        // protected by BKL for now, yuck //                                                                    
     40         sector_t        capacity;       // size in 512-byte sectors //                                                                          
     41         u32             index;                                                                                                                  
     42         u8              media_present;                                                                                                          
     43         u8              write_prot;                                                                                                             
     44         unsigned        WCE : 1;        // state of disk WCE bit //                                                                             
     45         unsigned        RCD : 1;        // state of disk RCD bit, unused //                                                                     
     46         unsigned        DPOFUA : 1;     // state of disk DPOFUA bit //                                                                          
     47 };                                                                                                                                              
// ������,�ƺ�����һ�� scsi disk �ܼ�,��ʵ�㲻Ҫ����,ǰ�����ǻ��ᵽ��һ���ṹ�� struct                                                                   
// gendisk,����ṹ������һ�����صĵط�,include/linux/genhd.h:                                                                                             
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
�� 12  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
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
// ����,struct scsi_disk �� struct gendisk ������Ϊ��������һ�����,scsi_disk �� scsi ר��,��                                                              
// gendisk �е� gen ��ʾ general,����Ӣ���ļ��Ķ�֪��,���ʾͨ��,�� scsi ѽ,ide ѽ,��һﶼ                                                                
// �����õ�.                                                                                                                                               
// ���� 1604 ��,alloc_disk ����Ϊ���Ƿ���һ�� gendisk.                                                                                                     
// ���ǽ����� 1608 �е� sd_index_idr����Щѧ����.                                                                                                          
// �������Ǳ�����ר��һ������������ idr��.������ 89 �����ǿ���������ôһ��,                                                                                
//      89 static DEFINE_IDR(sd_index_idr);                                                                                                                
// �ⱻ��������һ�� IDR.ӡ���д����ϸտ�ѧ��ʱ��,�����п�ʼ����һƪ���½�����idr��-                                                                        
// integer ID management,ר�Ŷ� idr ������һЩ����,��ƪ���������Ƿ����� LWN(Linux                                                                          
// Weekly News)����.�����ٲ����µ���һֱ����������,����,��ˮ,����Ϸ,����ֱ������,��Ȼ                                                                      
// ��֪��Ϊʲô����������� idr,ֻ�����¶����ĸо�����һ����������һЩС�����Ĺ���,                                                                        
// ������˵,�����ں��ж�����һЩ����,�������еĺ�������������һ���ļ���,�� lib/idr.c,��                                                                    
// ������ʵ��������Ȼ���ض�˵,˵���˾�δ������������,����ֻ������ʵ��Ч��.                                                                                 
// ʵ��������һ���������������� lib/idr.c �ĺ���,���߸�ȷ�е�˵���ĸ�,��Ϊ���������                                                                       
// DEFINE_IDR Ҳ��һ�������İ�װ,�ܵ���˵,���������Ҫʹ�� idr ����,���Ǿ���Ҫ���ȵ�                                                                       
// �� idr_init ����,����ʹ��������� DEFINE_IDR,�����ǳ�ʼ��,Ҳ��������һ�� idr ����,��                                                                    
// ʵ��������һ�� struct idr �ṹ�����.Ȼ��ʹ����������,һ���� idr_pre_get(),һ����                                                                       
// idr_get_new(),�������պ������� idr �Ѿ�û�����ü�ֵ��,��������Ե�����һ����                                                                          
// ��,idr_remove()����ɹ��Ӳ��ŵĹ���.                                                                                                                    
// ���ǿ��� 1608 �е��� idr_pre_get(),���һ��������������֮ǰ��ʼ����&sd_index_idr,�ڶ�                                                                   
// ��������һ������,����������ÿһ�������ڴ�ʱһ��,ͨ�����ݵľ��� GFP_KERNEL.���                                                                          
// �����е����ڲ�ͬ����,������ 0 ��ʾ����,���ط� 0 �ű�ʾ����,���͵ĳ��ʽ����.                                                                            
// ��1612��,idr_get_new(),���ǻ����һ��available��ID��,�����ڵ�����������,����������                                                                      
// �� index,�ڶ�����������̫����,���ݸ� NULL �Ϳ�����.һ������������ 0.                                                                                    
// �� index ����С�� SD_MAX_DISKS,����궨���� include/scsi/sd.h:                                                                                          
//      12  * This is limited by the naming scheme enforced in sd_probe,                                                                                   
//      13  * add another character to it if you really need more disks.                                                                                   
//      14  //                                                                                                                                             
//      15 #define SD_MAX_DISKS    (((26 * 26) + 26 + 1) * 26)                                                                                             
// �� 13  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
// ������껹��Ϳ϶�������.���������,������ʱ,��Ҳ����һ��,�ɶ�����������ͷ��,��Ҳ                                                                       
// ������,Ҳ����ԥ,Ҳ������,������һ��������������,26 �������Ӣ����ĸ�ĸ���,��������                                                                      
// �����Ͼ��ܿ���,Linux �ж� scsi disk �������������������� 26 ��Ӣ����ĸ.                                                                                 
// ������Ϳ�1643��1659��,��һ��ͬʱҲ����idr�ľ���.������ᷢ��,gd->disk_nameһ��                                                                         
// ���� sda-sdz ֮��,�������� sdaa �� sdzz ֮��,�������� sdaaa �� sdzzz ֮��.��һ��,�ǲ�����                                                               
// ������Ϊ SD_MAX_DISKS ��.�� index ��ȡֵ��Χ����[0,SD_MAX_DISKS)֮��,ֻȡ����.                                                                          
// ������˵,�����ֻ��һ��Ӳ��,��ô���ܿ�������,/dev/sda,������ж��Ӳ��,����������                                                                       
// ����������е�һ��,                                                                                                                                     
// localhost:~ # fdisk -l                                                                                                                                  
//                                                                                                                                                         
// Disk /dev/sda: 146.1 GB, 146163105792 bytes                                                                                                             
// 255 heads, 63 sectors/track, 17769 cylinders                                                                                                            
// Units = cylinders of 16065 * 512 = 8225280 bytes                                                                                                        
//                                                                                                                                                         
//    Device Boot      Start         End      Blocks   Id  System                                                                                          
// /dev/sda1               1         266     2136613+  83  Linux                                                                                           
// /dev/sda2            2879       17769   119611957+  83  Linux                                                                                           
// /dev/sda3   *         267        1572    10490445   83  Linux                                                                                           
// /dev/sda4            1573        2878    10490445   82  Linux swap / Solaris                                                                            
//                                                                                                                                                         
// Partition table entries are not in disk order                                                                                                           
//                                                                                                                                                         
// Disk /dev/sdb: 5368 MB, 5368709120 bytes                                                                                                                
// 166 heads, 62 sectors/track, 1018 cylinders                                                                                                             
// Units = cylinders of 10292 * 512 = 5269504 bytes                                                                                                        
//                                                                                                                                                         
//    Device Boot      Start         End      Blocks   Id  System                                                                                          
//                                                                                                                                                         
// Disk /dev/sdc: 5368 MB, 5368709120 bytes                                                                                                                
// 166 heads, 62 sectors/track, 1018 cylinders                                                                                                             
// Units = cylinders of 10292 * 512 = 5269504 bytes                                                                                                        
//                                                                                                                                                         
//    Device Boot      Start         End      Blocks   Id  System                                                                                          
//                                                                                                                                                         
// Disk /dev/sdd: 5368 MB, 5368709120 bytes                                                                                                                
// 166 heads, 62 sectors/track, 1018 cylinders                                                                                                             
// Units = cylinders of 10292 * 512 = 5269504 bytes                                                                                                        
//                                                                                                                                                         
//    Device Boot      Start         End      Blocks   Id  System                                                                                          
//                                                                                                                                                         
// Disk /dev/sde: 5368 MB, 5368709120 bytes                                                                                                                
// 166 heads, 62 sectors/track, 1018 cylinders                                                                                                             
// Units = cylinders of 10292 * 512 = 5269504 bytes                                                                                                        
//                                                                                                                                                         
// �� 14  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
//    Device Boot      Start         End      Blocks   Id  System                                                                                          
// ����������ҵĻ������� 5 �� scsi Ӳ��,��ô���ǵ����ֱַ��� sda,sdb,sdc,sdd,sde,�������                                                                 
// ������ıȽϱ�̬,һ̨��������� 30 ��Ӳ��,��ôûɶ˵��,���Ǿͻ����α�����Ϊ                                                                             
// sda,sdb,��,sdx,sdy,sdz,�⻹����,ֻ��26��,��������Ӳ�����ƾͽ���sdaa,sdab,sdac,sdad,�ܹ�                                                                 
// ����30��.�����������⻹������̬,���Ҫ��ս����,���Ҫplay zhuangbility,��ô������                                                                     
// ��sdaa��sdzz֮��,Linux����������sdaaa,sdaab,��,һֱ��sdzzz.��֮,��Linux��,������                                                                      
// ��ʹ�õ�Ӳ������������ SD_MAX_DISKS ��.��Ȼ,�һ��Ƿ�Ȱ��,����ô��,�Ͼ���������                                                                          
// Ի��:��Īװ B,װ B ������!��                                                                                                                            
// ���������Թ�����,1643 ��,gd->major ������ֵ,�Դ����Ž����԰ĳ��֪����С��˾�����                                                                      
// ���ǵ���������ʱ������������������ֵ��֮��,������̵ķ�ʡ�Լ�Ϊ�ε���û�кú�ѧϰ                                                                       
// ̷��ǿ��ʦ�Ǳ�<<C �������>>�е�λ����.ʹ��˼ʹ֮��,�������ܿ�����ǰ�������,��                                                                         
// Ȼ�������ǵ�������� sd_majorΪ����?                                                                                                                    
//     247 //                                                                                                                                              
//     248  * Device no to disk mapping:                                                                                                                   
//     249  *                                                                                                                                              
//     250  *       major         disc2     disc  p1                                                                                                       
//     251  *   |............|.............|....|....| <- dev_t                                                                                            
//     252  *    31        20 19          8 7  4 3  0                                                                                                      
//     253  *                                                                                                                                              
//     254  * Inside a major, we have 16k disks, however mapped non-                                                                                       
//     255  * contiguously. The first 16 disks are for major0, the next                                                                                    
//     256  * ones with major1, ... Disk 256 is for major0 again, disk 272                                                                                 
//     257  * for major1, ...                                                                                                                              
//     258  * As we stay compatible with our numbering scheme, we can reuse                                                                                
//     259  * the well-know SCSI majors 8, 65--71, 136--143.                                                                                               
    260  //                                                                                                                                             
    261 static int sd_major(int major_idx)                                                                                                              
    262 {                                                                                                                                               
    263         switch (major_idx) {                                                                                                                    
    264         case 0:                                                                                                                                 
    265                 return SCSI_DISK0_MAJOR;                                                                                                        
    266         case 1 ... 7:                                                                                                                           
    267                 return SCSI_DISK1_MAJOR + major_idx - 1;                                                                                        
    268         case 8 ... 15:                                                                                                                          
    269                 return SCSI_DISK8_MAJOR + major_idx - 8;                                                                                        
    270         default:                                                                                                                                
    271                 BUG();                                                                                                                          
    272                 return 0;       // shut up gcc //                                                                                               
    273         }                                                                                                                                       
    274 }                                                                                                                                               
// ������ͦ����,��ʵ��Ȼ,����ǰ��˵��,scsi disk�����豸�����Ѿ��̶����˵�,�����ǹϷ���                                                                     
// 8,65-71,128-135 �⼸����,���� SCSI_DISK0_MAJOR ���� 8,SCSI_DISK1_MAJOR ����                                                                             
// 65,SCSI_DISK8_MAJOR ���� 128.sd_major()���ܵĲ������� index �� bit4 �� bit7,����ȡֵ                                                                    
// ��Χ��Ȼ����0��15,��Ҳ����sd_major()��switch/case����жϵķ�Χ,��ʵ����major_idx                                                                       
// �� 15  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
// �������豸�ŵ�һ������,��˵�������16�����豸���������ϼ�.��first_minor���Ƕ�Ӧ��                                                                       
// �� index �ĵ�һ�����豸��,���ǿ����ô��뷨�õ�,�� index Ϊ 0,�� first_minor Ϊ 0,�� index                                                               
// Ϊ 1,�� first_minor Ϊ 16,�� index Ϊ 2,�� first_minor Ϊ 32.��һ����,minor �����ʾ�� index                                                            
// ���ж��ٸ����豸��,�����Ҷ���һ����,����16.����ͨ�������������Ҳ�ܿ���:                                                                              
// [root@localhost ~]# cat /proc/partitions                                                                                                                
// major minor  #blocks  name                                                                                                                              
//                                                                                                                                                         
//    8     0  285474816 sda                                                                                                                               
//    8     1    2104483 sda1                                                                                                                              
//    8     2   16779892 sda2                                                                                                                              
//    8     3          1 sda3                                                                                                                              
//    8     5   20972826 sda5                                                                                                                              
//    8     6   20482843 sda6                                                                                                                              
//    8     7   20482843 sda7                                                                                                                              
//    8     8   10241406 sda8                                                                                                                              
//    8     9   20482843 sda9                                                                                                                              
//    8    10   20482843 sda10                                                                                                                             
//    8    11   20482843 sda11                                                                                                                             
//    8    12   20482843 sda12                                                                                                                             
//    8    13   20482843 sda13                                                                                                                             
//    8    14   20482843 sda14                                                                                                                             
//    8    15   20482843 sda15                                                                                                                             
//    8    16    5242880 sdb                                                                                                                               
//    8    32    5242880 sdc                                                                                                                               
//    8    48    5242880 sdd                                                                                                                               
//    8    64    5242880 sde                                                                                                                               
// ����Ȼ,����sda,����豸�Ǵ�0��ʼ,����sdb,���豸�Ŵ�16��ʼ,����sdc,���32��ʼ,sdd                                                                        
// ���48��ʼ,ÿ��index����˵ÿ��disk_name������16�����豸��.Ҳ���һ��SCSIӲ��                                                                            
// ������� 15������.                                                                                                                                      
// ����֮��,sd_probe����Ҫ����Щ�򵥵ĸ�ֵ��.��ȻҲ��ȫ��,����1633�е�1639����һ��,                                                                        
// ����Ч������������豸�������� sysfs �� class��Ŀ¼����,���������������:                                                                               
// localhost:~ # cat /sys/class/scsi_device/                                                                                                               
// 0:0:8:0/ 0:2:0:0/ 1:0:0:0/ 1:0:0:1/ 1:0:0:2/ 1:0:0:3/                                                                                                   
// ÿһ�� scsi�豸�������ռ��һ����Ŀ¼.                                                                                                                  
// 1641 �����get_device ���ö�˵,����һ�� struct device �ĵ�һ��,�������ü���.�Ժ��õ�                                                                  
// ʱ����Ȼ����һ����Եĺ��� put_device ������.                                                                                                           
// 1671��,dev_set_drvdata,��������dev->driver_data����sdkp,����struct device��ָ��dev��                                                                    
// struct scsi_disk ��ָ�� sdkp ����ϵ����.�������ν�����Ѷ���·����,��ϵ��������Խ��,��                                                                  
// ��ʹ��������Խ����.                                                                                                                                     
// ���,�ر�����������ֵ.��һ����,1621 ��,�� sdkp->driver ����&sd_template,��һ���� 1646                                                                   
// ��,�� gd->fops ����&sd_fops.�����и�ֵ�������������µ�����,������ 1979 ���Ǹ�������                                                                     
// һλ�������й����Ϻ��߻���һ��Ȧ���й����ش�����.�����ǽ���sd_probe֮��,��������                                                                        
// ֵ����������չ������Ĺ���.                                                                                                                             
// ���� sd_probe,�۳��ž�Ҫ����,���Ǻ���Ȼ,�������������ǻ�û���ᵽ,���Ǿ��� 1664 �е�                                                                     
// �� 16  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
// sd_revalidate_disk()�Լ�1672�е�add_disk(),��������������˵���Ҫ,�����������б�Ҫ��                                                                    
// ��һ��ר������������.                                                                                                                                   
//                                                                                                                                                         
// ���̴����㶯����!                                                                                                                                       
// �������ǿ� sd_revalidate_disk(),�����������Ҫ,һ���̶�����˵,�������������Ӳ������                                                                    
// ���������������������˽� scsi ���̵��Ը߳�.�������������һ��������ս��,����ȫ�Ǽ�                                                                      
// ����������������,����һ����������ǣ����N������.����N�������е�һЩ��������                                                                          
// ���кü�����,�������������ݽ�ȥ��.                                                                                                                      
//    1496 ///                                                                                                                                             
//    1497  *      sd_revalidate_disk - called the first time a new disk is seen,                                                                          
//    1498  *      performs disk spin up, read_capacity, etc.                                                                                              
//    1499  *      @disk: struct gendisk we care about                                                                                                     
//    1500  ///                                                                                                                                            
   1501 static int sd_revalidate_disk(struct gendisk *disk)                                                                                             
   1502 {                                                                                                                                               
   1503         struct scsi_disk *sdkp = scsi_disk(disk);                                                                                               
   1504         struct scsi_device *sdp = sdkp->device;                                                                                                 
   1505         unsigned char *buffer;                                                                                                                  
   1506         unsigned ordered;                                                                                                                       
   1507                                                                                                                                                 
   1508         SCSI_LOG_HLQUEUE(3, sd_printk(KERN_INFO, sdkp,                                                                                          
   1509                                       "sd_revalidate_disk\n"));                                                                                 
   1510                                                                                                                                                 
   1511         //                                                                                                                                      
   1512          * If the device is offline, don't try and read capacity or any                                                                         
   1513          * of the other niceties.                                                                                                               
   1514          //                                                                                                                                     
   1515         if (!scsi_device_online(sdp))                                                                                                           
   1516                 goto out;                                                                                                                       
   1517                                                                                                                                                 
   1518         buffer = kmalloc(SD_BUF_SIZE, GFP_KERNEL | __GFP_DMA);                                                                                  
   1519         if (!buffer) {                                                                                                                          
   1520                 sd_printk(KERN_WARNING, sdkp, "sd_revalidate_disk: Memory "                                                                     
   1521                           "allocation failure.\n");                                                                                             
   1522                 goto out;                                                                                                                       
   1523         }                                                                                                                                       
   1524                                                                                                                                                 
   1525         // defaults, until the device tells us otherwise //                                                                                     
   1526         sdp->sector_size = 512;                                                                                                                 
   1527         sdkp->capacity = 0;                                                                                                                     
   1528         sdkp->media_present = 1;                                                                                                                
�� 17  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
   1529         sdkp->write_prot = 0;                                                                                                                   
   1530         sdkp->WCE = 0;                                                                                                                          
   1531         sdkp->RCD = 0;                                                                                                                          
   1532                                                                                                                                                 
   1533         sd_spinup_disk(sdkp);                                                                                                                   
   1534                                                                                                                                                 
   1535         //                                                                                                                                      
   1536          * Without media there is no reason to ask; moreover, some devices                                                                      
   1537          * react badly if we do.                                                                                                                
   1538          //                                                                                                                                     
   1539         if (sdkp->media_present) {                                                                                                              
   1540                 sd_read_capacity(sdkp, buffer);                                                                                                 
   1541                 sd_read_write_protect_flag(sdkp, buffer);                                                                                       
   1542                 sd_read_cache_type(sdkp, buffer);                                                                                               
   1543         }                                                                                                                                       
   1544                                                                                                                                                 
   1545         //                                                                                                                                      
   1546          * We now have all cache related info, determine how we deal                                                                            
   1547          * with ordered requests.  Note that as the current SCSI                                                                                
   1548          * dispatch function can alter request order, we cannot use                                                                             
   1549          * QUEUE_ORDERED_TAG_* even when ordered tag is supported.                                                                              
   1550          //                                                                                                                                     
   1551         if (sdkp->WCE)                                                                                                                          
   1552                 ordered = sdkp->DPOFUA                                                                                                          
   1553                         ? QUEUE_ORDERED_DRAIN_FUA :                                                                                             
QUEUE_ORDERED_DRAIN_FLUSH;                                                                                                                              
   1554         else                                                                                                                                    
   1555                 ordered = QUEUE_ORDERED_DRAIN;                                                                                                  
   1556                                                                                                                                                 
   1557         blk_queue_ordered(sdkp->disk->queue, ordered, sd_prepare_flush);                                                                        
   1558                                                                                                                                                 
   1559         set_capacity(disk, sdkp->capacity);                                                                                                     
   1560         kfree(buffer);                                                                                                                          
   1561                                                                                                                                                 
   1562  out:                                                                                                                                           
   1563         return 0;                                                                                                                               
   1564 }                                                                                                                                               
�����Ǿ����ô��һ��������˵,�����׵����ĺ������� sd_spinup_disk().                                                                                   
   1005 //                                                                                                                                              
   1006  * spinup disk - called only in sd_revalidate_disk()                                                                                            
   1007  //                                                                                                                                             
   1008 static void                                                                                                                                     
   1009 sd_spinup_disk(struct scsi_disk *sdkp)                                                                                                          
   1010 {                                                                                                                                               
�� 18  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
   1011         unsigned char cmd[10];                                                                                                                  
   1012         unsigned long spintime_expire = 0;                                                                                                      
   1013         int retries, spintime;                                                                                                                  
   1014         unsigned int the_result;                                                                                                                
   1015         struct scsi_sense_hdr sshdr;                                                                                                            
   1016         int sense_valid = 0;                                                                                                                    
   1017                                                                                                                                                 
   1018         spintime = 0;                                                                                                                           
   1019                                                                                                                                                 
   1020         // Spin up drives, as required.  Only do this at boot time //                                                                           
   1021         // Spinup needs to be done for module loads too. //                                                                                     
   1022         do {                                                                                                                                    
   1023                 retries = 0;                                                                                                                    
   1024                                                                                                                                                 
   1025                 do {                                                                                                                            
   1026                         cmd[0] = TEST_UNIT_READY;                                                                                               
   1027                         memset((void *) &cmd[1], 0, 9);                                                                                         
   1028                                                                                                                                                 
   1029                         the_result = scsi_execute_req(sdkp->device, cmd,                                                                        
   1030                                                       DMA_NONE,                                                                                 
NULL, 0,                                                                                                                                                
   1031                                                       &sshdr,                                                                                   
SD_TIMEOUT,                                                                                                                                             
   1032                                                                                                                                                 
SD_MAX_RETRIES);                                                                                                                                        
   1033                                                                                                                                                 
   1034                         //                                                                                                                      
   1035                          * If the drive has indicated to us that it                                                                             
   1036                          * doesn't have any media in it, don't bother                                                                           
   1037                          * with any more polling.                                                                                               
   1038                          //                                                                                                                     
   1039                          if (media_not_present(sdkp, &sshdr))                                                                                   
   1040                                 return;                                                                                                         
   1041                                                                                                                                                 
   1042                         if (the_result)                                                                                                         
   1043                                 sense_valid = scsi_sense_valid(&sshdr);                                                                         
   1044                         retries++;                                                                                                              
   1045                 } while (retries < 3 &&                                                                                                         
   1046                          (!scsi_status_is_good(the_result) ||                                                                                   
   1047                           ((driver_byte(the_result) & DRIVER_SENSE) &&                                                                          
   1048                           sense_valid && sshdr.sense_key ==                                                                                     
UNIT_ATTENTION)));                                                                                                                                      
   1049                                                                                                                                                 
   1050                 if ((driver_byte(the_result) & DRIVER_SENSE) == 0) {                                                                            
�� 19  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
   1051                         // no sense, TUR either succeeded or failed                                                                             
   1052                          * with a status error //                                                                                               
   1053                         if(!spintime && !scsi_status_is_good(the_result)) {                                                                     
   1054                                 sd_printk(KERN_NOTICE, sdkp, "Unit Not                                                                          
Ready\n");                                                                                                                                              
   1055                                 sd_print_result(sdkp, the_result);                                                                              
   1056                         }                                                                                                                       
   1057                         break;                                                                                                                  
   1058                 }                                                                                                                               
   1059                                                                                                                                                 
   1060                 //                                                                                                                              
   1061                  * The device does not want the automatic start to be issued.                                                                   
   1062                  //                                                                                                                             
   1063                 if (sdkp->device->no_start_on_add) {                                                                                            
   1064                         break;                                                                                                                  
   1065                 }                                                                                                                               
   1066                                                                                                                                                 
   1067                 //                                                                                                                              
   1068                  * If manual intervention is required, or this is an                                                                            
   1069                  * absent USB storage device, a spinup is meaningless.                                                                          
   1070                  //                                                                                                                             
   1071                 if (sense_valid &&                                                                                                              
   1072                     sshdr.sense_key == NOT_READY &&                                                                                             
   1073                     sshdr.asc == 4 && sshdr.ascq == 3) {                                                                                        
   1074                         break;          // manual intervention required //                                                                      
   1075                                                                                                                                                 
   1076                 //                                                                                                                              
   1077                  * Issue command to spin up drive when not ready                                                                                
   1078                  //                                                                                                                             
   1079                 } else if (sense_valid && sshdr.sense_key == NOT_READY) {                                                                       
   1080                         if (!spintime) {                                                                                                        
   1081                                 sd_printk(KERN_NOTICE, sdkp, "Spinning up                                                                       
disk...");                                                                                                                                              
   1082                                 cmd[0] = START_STOP;                                                                                            
   1083                                 cmd[1] = 1;     // Return immediately //                                                                        
   1084                                 memset((void *) &cmd[2], 0, 8);                                                                                 
   1085                                 cmd[4] = 1;     // Start spin cycle //                                                                          
   1086                                 scsi_execute_req(sdkp->device, cmd,                                                                             
DMA_NONE,                                                                                                                                               
   1087                                                  NULL, 0, &sshdr,                                                                               
   1088                                                  SD_TIMEOUT,                                                                                    
SD_MAX_RETRIES);                                                                                                                                        
   1089                                 spintime_expire = jiffies + 100 * HZ;                                                                           
   1090                                 spintime = 1;                                                                                                   
�� 20  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
   1091                         }                                                                                                                       
   1092                         // Wait 1 second for next try //                                                                                        
   1093                         msleep(1000);                                                                                                           
   1094                         printk(".");                                                                                                            
   1095                                                                                                                                                 
   1096                 //                                                                                                                              
   1097                  * Wait for USB flash devices with slow firmware.                                                                               
   1098                  * Yes, this sense key/ASC combination shouldn't                                                                                
   1099                  * occur here.  It's characteristic of these devices.                                                                           
   1100                  //                                                                                                                             
   1101                 } else if (sense_valid &&                                                                                                       
   1102                                 sshdr.sense_key == UNIT_ATTENTION &&                                                                            
   1103                                 sshdr.asc == 0x28) {                                                                                            
   1104                         if (!spintime) {                                                                                                        
   1105                                 spintime_expire = jiffies + 5 * HZ;                                                                             
   1106                                 spintime = 1;                                                                                                   
   1107                         }                                                                                                                       
   1108                         // Wait 1 second for next try //                                                                                        
   1109                         msleep(1000);                                                                                                           
   1110                 } else {                                                                                                                        
   1111                         // we don't understand the sense code, so it's                                                                          
   1112                          * probably pointless to loop //                                                                                        
   1113                         if(!spintime) {                                                                                                         
   1114                                 sd_printk(KERN_NOTICE, sdkp, "Unit Not                                                                          
Ready\n");                                                                                                                                              
   1115                                 sd_print_sense_hdr(sdkp, &sshdr);                                                                               
   1116                         }                                                                                                                       
   1117                         break;                                                                                                                  
   1118                 }                                                                                                                               
   1119                                                                                                                                                 
   1120         } while (spintime && time_before_eq(jiffies, spintime_expire));                                                                         
   1121                                                                                                                                                 
   1122         if (spintime) {                                                                                                                         
   1123                 if (scsi_status_is_good(the_result))                                                                                            
   1124                         printk("ready\n");                                                                                                      
   1125                 else                                                                                                                            
   1126                         printk("not responding...\n");                                                                                          
   1127         }                                                                                                                                       
   1128 }                                                                                                                                               
// ����˼��,spinup_disk�����ô���ת����.Ȼ��,Ҫ�������������,��Ͳ��ò���SCSI spec��                                                                      
// һ���˽���.                                                                                                                                             
// ���������Ȼ����,�������Ǳ���������������˼��,�ص��ע������������м�ֵ�����д�                                                                        
// ��,û��,��ʹ������·����ó����ſڿ����г��Ĵ��趼֪��,������������м�ֵ������                                                                         
// ����һ����1029��,scsi_execute_req()�����ĵ���.�����������scsi���Ĳ��ṩ��,����ֻ��                                                                     
// �� 21  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
// ���ò��ù�ʵ��.������ include/scsi/scsi_device.h �����ҵ���������:                                                                                      
//     297 extern int scsi_execute_req(struct scsi_device *sdev, const unsigned char *cmd,                                                                 
//     298   int data_direction, void *buffer, unsigned bufflen,                                                                                           
//     299   struct scsi_sense_hdr *, int timeout, int retries);                                                                                           
// �� usb ���Ĳ�һ��,scsi ���Ĳ�Ҳ�ṩ�˴����ĺ��������ǵ���,��Щ��������ı���������                                                                      
// ��дscsi�豸��������.����ֻҪ׼���ò������ݸ��������,Ȼ������´���,�����жϺ�                                                                       
// ������ֵ������,������Ҫ���ݵ�����,���Ѿ�����������ǵĲ����е�buffer�����.��ͺ�                                                                       
// ����ÿ���ϰ��ʱ������г�ͣ����ֱ�ų���վ��,���������°������ʱ��,���г�������                                                                        
// Ȼ��Ȼ�ľͱ��������,ʲô����,���̺�,����ֽ,��ʣ��ƻ��,�����Ŀ�����,ż�������ù���                                                                      
// ������,�ܶ���֮,�׶����������һ�δε����Ҹж�����������,���Ҿ��ñ�Ư�����Ӳ���                                                                         
// �¶�.                                                                                                                                                   
// �������˵���˾���ִ��һ��scsi����,���һ���������ض�˵,�������ǵ�struct scsi_device                                                                    
// �Ľṹ��ָ��,����������������ôһ��.�ڶ����������Ǵ���������,cmd ��,����                                                                              
// command.��ʵÿһ����������˼��������.                                                                                                                   
// ���ǽ�����ǵĴ����������Ǿ��崫���������Ĳ���.��һ�� sdkp->device ��û��˵,�ڶ�                                                                        
// ��,cmd,������1011�������һ��unsigned char���͵�����,�ܹ�10��Ԫ��,1026�и�����ֵ                                                                        
// ΪTEST_UNIT_READY.Test Unit Ready����һ���ܻ�����SCSI����.DMA_NONE������                                                                              
// ����,buffer��bufflen�����ò���,��Ϊ���������ǲ����豸׼������û��,����Ҫ����ʲô                                                                      
// ����.                                                                                                                                                   
// ������������,������ôһ���� scsi_execute_req()��ִ����� Test Unit Ready����,���صĽ�                                                                   
// �������϶��Ǻõ�,�����豸�����ë��.                                                                                                                    
// ��Ȼ��Ҫ˵��û�г����ʱ��,�ǵ�ȻҲ���е�.���������������,                                                                                             
// [root@localhost dev]# ls sd*                                                                                                                            
// sda  sda1  sda10  sda11  sda12  sda13  sda14  sda2  sda3  sda5  sda6  sda7  sda8                                                                        
// sda9  sdb  sdc  sdd  sde  sdf                                                                                                                           
// [root@localhost ~]# sg_turs /dev/sda                                                                                                                    
// Completed 1 Test Unit Ready commands with 0 errors                                                                                                      
// [root@localhost ~]# sg_turs /dev/sdb                                                                                                                    
// Completed 1 Test Unit Ready commands with 0 errors                                                                                                      
// [root@localhost ~]# sg_turs /dev/sdc                                                                                                                    
// Completed 1 Test Unit Ready commands with 0 errors                                                                                                      
// [root@localhost ~]# sg_turs /dev/sde                                                                                                                    
// Completed 1 Test Unit Ready commands with 0 errors                                                                                                      
// [root@localhost ~]# sg_turs /dev/sdf                                                                                                                    
// test unit ready:  Fixed format, current;  Sense key: Not Ready                                                                                          
//  Additional sense: Medium not present                                                                                                                   
// Completed 1 Test Unit Ready commands with 1 errors                                                                                                      
// ����sg_turs���������������ֹ�����Test Unit Ready�õ�.����Ҫʹ���������,��ð�װ                                                                      
// sg3_utilsϵ�������.                                                                                                                                    
// [root@localhost dev]# rpm -qa | grep sg3_utils                                                                                                          
// sg3_utils-devel-1.20-2.1                                                                                                                                
// sg3_utils-1.20-2.1                                                                                                                                      
// sg3_utils-libs-1.20-2.1                                                                                                                                 
// ���ǿ������ҵ����Ӳ����,ǰ�Ŀ鶼û������,���ǵ�����ͱ�����.������ִ��������֮                                                                         
// �� 22  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
// ��,������ the_result ��¼�½��,������ 1046 �е��� scsi_status_is_good()���жϽ��.����                                                                 
// scsi_status_is_good()�Լ�������ص�һЩ�궨���� include/scsi/scsi.h �ļ���:                                                                             
//     125 //                                                                                                                                              
//     126  *  SCSI Architecture Model (SAM) Status codes. Taken from SAM-3 draft                                                                          
//     127  *  T10/1561-D Revision 4 Draft dated 7th November 2002.                                                                                        
//     128  //                                                                                                                                             
    129 #define SAM_STAT_GOOD            0x00                                                                                                           
    130 #define SAM_STAT_CHECK_CONDITION 0x02                                                                                                           
    131 #define SAM_STAT_CONDITION_MET   0x04                                                                                                           
    132 #define SAM_STAT_BUSY            0x08                                                                                                           
    133 #define SAM_STAT_INTERMEDIATE    0x10                                                                                                           
    134 #define SAM_STAT_INTERMEDIATE_CONDITION_MET 0x14                                                                                                
    135 #define SAM_STAT_RESERVATION_CONFLICT 0x18                                                                                                      
    136 #define SAM_STAT_COMMAND_TERMINATED 0x22        // obsolete in                                                                                  
SAM-3 //                                                                                                                                                
    137 #define SAM_STAT_TASK_SET_FULL   0x28                                                                                                           
    138 #define SAM_STAT_ACA_ACTIVE      0x30                                                                                                           
    139 #define SAM_STAT_TASK_ABORTED    0x40                                                                                                           
    140                                                                                                                                                 
    141 /// scsi_status_is_good - check the status return.                                                                                              
    142  *                                                                                                                                              
    143  * @status: the status passed up from the driver (including host and                                                                            
    144  *          driver components)                                                                                                                  
    145  *                                                                                                                                              
    146  * This returns true for known good conditions that may be treated as                                                                           
    147  * command completed normally                                                                                                                   
    148  //                                                                                                                                             
    149 static inline int scsi_status_is_good(int status)                                                                                               
    150 {                                                                                                                                               
    151         //                                                                                                                                      
    152          * FIXME: bit0 is listed as reserved in SCSI-2, but is                                                                                  
    153          * significant in SCSI-3.  For now, we follow the SCSI-2                                                                                
    154          * behaviour and ignore reserved bits.                                                                                                  
    155          //                                                                                                                                     
    156         status &= 0xfe;                                                                                                                         
    157         return ((status == SAM_STAT_GOOD) ||                                                                                                    
    158                 (status == SAM_STAT_INTERMEDIATE) ||                                                                                            
    159                 (status == SAM_STAT_INTERMEDIATE_CONDITION_MET) ||                                                                              
    160                 // FIXME: this is obsolete in SAM-3 //                                                                                          
    161                 (status == SAM_STAT_COMMAND_TERMINATED));                                                                                       
    162 }                                                                                                                                               
// �������Щ�걻��Ϊ״̬��, scsi_execute_req()�ķ���ֵ������Щ״̬���е�һ��.�����п�                                                                     
// �Ա���Ϊ�� good ��״̬���� scsi_status_is_good �������г�����������,��Ȼ��������˵��                                                                    
// ����ľ��� SAM_STAT_GOOD,�������⼸��Ҳ��ǿ���ǿ��Խ���,���ͽ��͵�������ȥ.                                                                             
// �� 23  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
// ������һ��������׵���,the_result ��״̬�뻹���������,�Ͼ�״̬��ֻ����ô��,�� 8 λ                                                                     
// ����ʾ����,�� the_result���ǿ����� unsigned int,��Ȼ����ֻ�� 8 λ,�������Ǿͳ��������                                                                  
// Դ,��˾�����������Щ��,                                                                                                                                
//     358 //                                                                                                                                              
//     359  *  Use these to separate status msg and our bytes                                                                                              
//     360  *                                                                                                                                              
//     361  *  These are set by:                                                                                                                           
//     362  *                                                                                                                                              
//     363  *      status byte = set from target device                                                                                                    
//     364  *      msg_byte    = return status from host adapter itself.                                                                                   
//     365  *      host_byte   = set by low-level driver to indicate status.                                                                               
//     366  *      driver_byte = set by mid-level.                                                                                                         
//     367  //                                                                                                                                             
    368 #define status_byte(result) (((result) >> 1) & 0x7f)                                                                                            
    369 #define msg_byte(result)    (((result) >> 8) & 0xff)                                                                                            
    370 #define host_byte(result)   (((result) >> 16) & 0xff)                                                                                           
    371 #define driver_byte(result) (((result) >> 24) & 0xff)                                                                                           
    372 #define suggestion(result)  (driver_byte(result) & SUGGEST_MASK)                                                                                
// Ҳ����˵������͵��Ǹ�byte����Ϊstatus byte��,ʣ�µ�byte����Ҳû�˷�,���Ƕ�������                                                                       
// ������Ϣ,���� driver_byte,�� bit23 �� bit31,�� 8 λ���������� mid-level ���õ���Ϣ.������                                                               
// ������DRIVER_SENSE����,���жϵ����Ƿ���sense data,���ǵ�����usb-storage�����о�                                                                         
// ˵��,scsi�������sense data���Ǵ�����Ϣ.����1025����1048�е����do-whileѭ������                                                                        
// ������ɹ�������ظ�����,ѭ��������֮��,1050���ٴ��ж���û��sense data,���û��,��                                                                      
// ˵��Ҳ��ɹ���.                                                                                                                                         
// Scsi��ϵͳ���޳ܵĵط������ڴ����жϵĴ����ر�Ķ�.�����sense data�Ĵ������Ǵ���                                                                       
// �жϵ�һ����.                                                                                                                                           
//       8 //                                                                                                                                              
//       9  * This is a slightly modified SCSI sense "descriptor" format header.                                                                           
//      10  * The addition is to allow the 0x70 and 0x71 response codes. The idea                                                                          
//      11  * is to place the salient data from either "fixed" or "descriptor" sense                                                                       
//      12  * format into one structure to ease application processing.                                                                                    
//      13  *                                                                                                                                              
//      14  * The original sense buffer should be kept around for those cases                                                                              
//      15  * in which more information is required (e.g. the LBA of a MEDIUM ERROR).                                                                      
     16  //                                                                                                                                             
     17 struct scsi_sense_hdr {         // See SPC-3 section 4.5 //                                                                                     
     18         u8 response_code;       // permit: 0x0, 0x70, 0x71, 0x72, 0x73 //                                                                       
     19         u8 sense_key;                                                                                                                           
     20         u8 asc;                                                                                                                                 
     21         u8 ascq;                                                                                                                                
     22         u8 byte4;                                                                                                                               
     23         u8 byte5;                                                                                                                               
     24         u8 byte6;                                                                                                                               
     25         u8 additional_length;   // always 0 for fixed sense format //                                                                           
�� 24  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
     26 };                                                                                                                                              
     27                                                                                                                                                 
     28 static inline int scsi_sense_valid(struct scsi_sense_hdr *sshdr)                                                                                
     29 {                                                                                                                                               
     30         if (!sshdr)                                                                                                                             
     31                 return 0;                                                                                                                       
     32                                                                                                                                                 
     33         return (sshdr->response_code & 0x70) == 0x70;                                                                                           
     34 }                                                                                                                                               
// ���ﶨ��� struct scsi_sense_hdr���Ǳ���������һ�� sense data.��hdr������header����˼,��                                                                
// Ϊsense data���ܳ��ȱȽϳ�,������ǰ8��bytes������Ҫ��,�����ⲿ�ֱ�����header,����                                                                       
// ˵ͷ��,����������ֻҪ���ͷ���͹���.                                                                                                                  
// ���ǿ�����scsi_execute_req()�е�����������struct scsi_sense_hdr *sshdr,����֮,�������ִ                                                                
// �г�����,��ôsense data�ͻ�ͨ�������������.�������Ƕ�����sshdr,Ȼ������ͨ���ж���                                                                      
// �����ĸ�����Ա,��������һ��.                                                                                                                            
// ��sense data��,�������һ��Ԫ�ؽ���response_code,���൱��Ϊһ��sense data������,����                                                                    
// ������һ�����,��Ϊsense data�Ͼ��кܶ���.response code�ܹ�����8��bits,Ŀǰʹ�õ�ֵ                                                                     
// ֻ�� 70h,71h,72h,73h,�������� 00h �� 6Fh �Լ� 74h �� 7Eh ��Щ���Ǳ�����,�Ա�����֮��.                                                                   
// ���������жϵľ��� response code ���� 0x70,0x71,0x72,0x73 ���� valid,������� invalid.��                                                                
// ���� scsi_sense_valid()��������.                                                                                                                        
// ���� sense data,��ʵ��,����һֱ������һ������ SCSI Primary Commands(SPC)���ؼ�,����                                                                     
// ���ؼ��ĵ�����,ȷ�е�˵�� 4.5 ��,���־ͽ��� Sense data,����һ����ר�Ž��� Sense Data                                                                    
// ��.Sense data����������Ķ�������sense key��sense code.���������������ȷ���������                                                                     
// ���󾿾���ʲô����.                                                                                                                                     
// 1048��,�����ж�sshdr��sense_key�ǲ��ǵ���UNIT_ATTENTION,�����Ϣ��ʾ����豸                                                                            
// ���ܱ������˻��߿��ƶ��Ľ��ʷ����˱仯,���߸�ͨ��һ��˵,ֻҪ�豸������һЩ�仯,                                                                         
// Ȼ����ϣ�����������������Ĺ�ע,����˵�豸ԭ���� on-line ��,ͻȻ����� off-line,���߷�                                                                   
// ����,�豸�� off-line �ص��� on-line.����ʽ��д�豸֮ǰ,����� UNIT_ATTENTION ����,��                                                                    
// ������������.����(��� UNIT ATTENTION)Ҳ���� Test Unit Ready�Ĺ���֮һ.                                                                               
// ����� sense key ���� NOT_READY,�������� logical unit ���ܱ�����.(NOT READY:                                                                          
// Indicates that the logical unit is not accessible.)����� sense key���� NOT READY,�� asc ����                                                           
// 04h,ascq ���� 03h,�������Logical Unit Not Ready,Manual Intervention required��.(��� SPC-4,                                                            
// ��¼ D����)��˵����Ҫ�˹���Ԥ.                                                                                                                          
// ��Ȼ����������,Ӧ��ִ�е��� 1079 ����� else if �������Ĵ���.������ȷʵӦ����                                                                         
// NOT_READY,����������Ҫ������һ������,�� START STOP,����һ�������书�ؼ���Ϊ                                                                             
// SCSI Block Commands-2(SBC-2)������,5.17 ��ר�Ž����� START STOP UNIT �������.��                                                                        
// ����������֮,���൱�ڵ�Դ����,SBC-2 ��Table 48 �������������ĸ�ʽ:                                                                                  
// �� 25  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
//                                                                                                                                                         
// ��ϴ��뿴,���ǰ� cmd[4]����Ϊ 1,ʵ���Ͼ͵����ǰ�����ͼ��� START λ����Ϊ 1.����                                                                       
// SBC-2 ��,��� START λ�ĺ�������:                                                                                                                       
// If the START bit is set to zero, then the logical unit shall transition to the stopped power condition,                                                 
// disable the idle condition timer if it is active (see SPC-3), and disable the standby condition timer                                                   
// if it is active (see SPC-3). If the START bit set to one, then the logical unit shall transition to the                                                 
// active power condition, enable the idle condition  timer if it is active, and enable the standby                                                        
// condition timer if it is active.                                                                                                                        
// ������,����������ĵ�Դ����.���,1086 ���ٴε��� scsi_execute_req ��ִ�� START STOP                                                                     
// UNIT ����,������������Ӳ��ת����.�����ù����ǵĻ�˵,������!                                                                                             
// �������Ǿͺ������ 1022 ��ֱ�� 1120 ����һ���д���� do-while ѭ������˼��.��������                                                                     
// �������̾���:                                                                                                                                           
// 1.       ���˵:���̴���������,��׼������û��?                                                                                                          
// 2.       ����˵:û��!                                                                                                                                   
// 3.       ���˵:���̴���������,������ת����!                                                                                                          
// 4.       ���:˯�� 1000 ����֮���ظ���һ��������.(��������ο����ߵڶ���,Ҳ�����ߵ���                                                                   
// ��.)                                                                                                                                                    
// 5.       ����˵:�ǵ�,��׼������,����ʱ��׼����.                                                                                                         
// 6.       ��ʱ,1057 �� break ���ᱻִ��,�Ӷ�ѭ������.sd_spinup_disk()����Ҳ�ͽ���������                                                                
// ʹ��.                                                                                                                                                   
// 7.       �ڵ�һ���ߵ����Ĳ���ʱ��,������spintime_expireΪ100��,�����ʱ��Ϊ������ͼ�                                                                   
// ��,������ֻҪ��100��֮�ڸ��Ҷ�����,�Ҿͼ�������,��������100���㻹���Ʋ��ԳԷ���,                                                                        
// �Ǿ�û�취��,while ѭ����Ȼ����,1126 ����� printk ���ִ��,�����ϼ�˵,not responding,                                                                  
// ����֮,����û����,����һ������İ���.                                                                                                                   
//                                                                                                                                                         
// ������ɽ(һ)                                                                                                                                            
// �ò����׽����� sd_spinup_disk(), �������Ǿ�������������ɽ . ������                                                                                      
// sd_read_capacity(),sd_read_write_protect_flag(),sd_read_cache_type(),Ҫ�������¿�,���ǲ���                                                              
// �����Ʒ���������ɽ.�ɵ�������ɽ�Ѿ���ë��ϯ��Ӣ���쵼�³ɹ��Ʒ���,���ǽ������ǵ�                                                                        
// ����ȴ����������ɽ��ѹ��֮��,��ǰ�������������ȳ��������ķ���ҽ�Ľ̸�.Ҫ֪����                                                                        
// �� sd.c����ļ�Ҳ������ 1900 ��,���ǹ�������������ռ�� 360 ��,�㲻�����а�!                                                                             
// ��һ����ɽ,sd_read_capacity.                                                                                                                            
//    1130 //                                                                                                                                              
// �� 26  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
//    1131 * read disk capacity                                                                                                                            
//    1132 //                                                                                                                                              
   1133 static void                                                                                                                                     
   1134 sd_read_capacity(struct scsi_disk *sdkp, unsigned char *buffer)                                                                                 
   1135 {                                                                                                                                               
   1136         unsigned char cmd[16];                                                                                                                  
   1137         int the_result, retries;                                                                                                                
   1138         int sector_size = 0;                                                                                                                    
   1139         int longrc = 0;                                                                                                                         
   1140         struct scsi_sense_hdr sshdr;                                                                                                            
   1141         int sense_valid = 0;                                                                                                                    
   1142         struct scsi_device *sdp = sdkp->device;                                                                                                 
   1143                                                                                                                                                 
   1144 repeat:                                                                                                                                         
   1145         retries = 3;                                                                                                                            
   1146         do {                                                                                                                                    
   1147                 if (longrc) {                                                                                                                   
   1148                         memset((void *) cmd, 0, 16);                                                                                            
   1149                         cmd[0] = SERVICE_ACTION_IN;                                                                                             
   1150                         cmd[1] = SAI_READ_CAPACITY_16;                                                                                          
   1151                         cmd[13] = 12;                                                                                                           
   1152                         memset((void *) buffer, 0, 12);                                                                                         
   1153                 } else {                                                                                                                        
   1154                         cmd[0] = READ_CAPACITY;                                                                                                 
   1155                         memset((void *) &cmd[1], 0, 9);                                                                                         
   1156                         memset((void *) buffer, 0, 8);                                                                                          
   1157                 }                                                                                                                               
   1158                                                                                                                                                 
   1159                 the_result = scsi_execute_req(sdp, cmd, DMA_FROM_DEVICE,                                                                        
   1160                                               buffer, longrc ? 12 : 8, &sshdr,                                                                  
   1161                                               SD_TIMEOUT, SD_MAX_RETRIES);                                                                      
   1162                                                                                                                                                 
   1163                 if (media_not_present(sdkp, &sshdr))                                                                                            
   1164                         return;                                                                                                                 
   1165                                                                                                                                                 
   1166                 if (the_result)                                                                                                                 
   1167                         sense_valid = scsi_sense_valid(&sshdr);                                                                                 
   1168                 retries--;                                                                                                                      
   1169                                                                                                                                                 
   1170         } while (the_result && retries);                                                                                                        
   1171                                                                                                                                                 
   1172         if (the_result && !longrc) {                                                                                                            
   1173                 sd_printk(KERN_NOTICE, sdkp, "READ CAPACITY failed\n");                                                                         
   1174                 sd_print_result(sdkp, the_result);                                                                                              
�� 27  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
   1175                 if (driver_byte(the_result) & DRIVER_SENSE)                                                                                     
   1176                         sd_print_sense_hdr(sdkp, &sshdr);                                                                                       
   1177                 else                                                                                                                            
   1178                         sd_printk(KERN_NOTICE, sdkp, "Sense not available.\n");                                                                 
   1179                                                                                                                                                 
   1180                 // Set dirty bit for removable devices if not ready -                                                                           
   1181                  * sometimes drives will not report this properly. //                                                                           
   1182                 if (sdp->removable &&                                                                                                           
   1183                     sense_valid && sshdr.sense_key == NOT_READY)                                                                                
   1184                         sdp->changed = 1;                                                                                                       
   1185                                                                                                                                                 
   1186                 // Either no media are present but the drive didn't tell us,                                                                    
   1187                    or they are present but the read capacity command fails //                                                                   
   1188                 // sdkp->media_present = 0; -- not always correct //                                                                            
   1189                 sdkp->capacity = 0; // unknown mapped to zero - as usual //                                                                     
   1190                                                                                                                                                 
   1191                 return;                                                                                                                         
   1192         } else if (the_result && longrc) {                                                                                                      
   1193                 // READ CAPACITY(16) has been failed //                                                                                         
   1194                 sd_printk(KERN_NOTICE, sdkp, "READ CAPACITY(16) failed\n");                                                                     
   1195                 sd_print_result(sdkp, the_result);                                                                                              
   1196                 sd_printk(KERN_NOTICE, sdkp, "Use 0xffffffff as device size\n");                                                                
   1197                                                                                                                                                 
   1198                 sdkp->capacity = 1 + (sector_t) 0xffffffff;                                                                                     
   1199                 goto got_data;                                                                                                                  
   1200         }                                                                                                                                       
   1201                                                                                                                                                 
   1202         if (!longrc) {                                                                                                                          
   1203                 sector_size = (buffer[4] << 24) |                                                                                               
   1204                         (buffer[5] << 16) | (buffer[6] << 8) | buffer[7];                                                                       
   1205                 if (buffer[0] == 0xff && buffer[1] == 0xff &&                                                                                   
   1206                     buffer[2] == 0xff && buffer[3] == 0xff) {                                                                                   
   1207                         if(sizeof(sdkp->capacity) > 4) {                                                                                        
   1208                                 sd_printk(KERN_NOTICE, sdkp, "Very big device. "                                                                
   1209                                           "Trying to use READ CAPACITY(16).\n");                                                                
   1210                                 longrc = 1;                                                                                                     
   1211                                 goto repeat;                                                                                                    
   1212                         }                                                                                                                       
   1213                          sd_printk(KERN_ERR, sdkp, "Too big for this kernel. Use "                                                              
   1214                                   "a kernel compiled with support for large "                                                                   
   1215                                   "block devices.\n");                                                                                          
   1216                         sdkp->capacity = 0;                                                                                                     
   1217                         goto got_data;                                                                                                          
   1218                 }                                                                                                                               
�� 28  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
   1219                 sdkp->capacity = 1 + (((sector_t)buffer[0] << 24) |                                                                             
   1220                         (buffer[1] << 16) |                                                                                                     
   1221                         (buffer[2] << 8) |                                                                                                      
   1222                         buffer[3]);                                                                                                             
   1223         } else {                                                                                                                                
   1224                 sdkp->capacity = 1 + (((u64)buffer[0] << 56) |                                                                                  
   1225                         ((u64)buffer[1] << 48) |                                                                                                
   1226                         ((u64)buffer[2] << 40) |                                                                                                
   1227                         ((u64)buffer[3] << 32) |                                                                                                
   1228                         ((sector_t)buffer[4] << 24) |                                                                                           
   1229                         ((sector_t)buffer[5] << 16) |                                                                                           
   1230                         ((sector_t)buffer[6] << 8) |                                                                                            
   1231                         (sector_t)buffer[7]);                                                                                                   
   1232                                                                                                                                                 
   1233                 sector_size = (buffer[8] << 24) |                                                                                               
   1234                         (buffer[9] << 16) | (buffer[10] << 8) | buffer[11];                                                                     
   1235         }                                                                                                                                       
   1236                                                                                                                                                 
   1237         // Some devices return the total number of sectors, not the                                                                             
   1238          * highest sector number. Make the necessary adjustment. //                                                                             
   1239         if (sdp->fix_capacity) {                                                                                                                
   1240                 --sdkp->capacity;                                                                                                               
   1241                                                                                                                                                 
   1242         // Some devices have version which report the correct sizes                                                                             
   1243          * and others which do not. We guess size according to a heuristic                                                                      
   1244          * and err on the side of lowering the capacity. //                                                                                     
   1245         } else {                                                                                                                                
   1246                 if (sdp->guess_capacity)                                                                                                        
   1247                         if (sdkp->capacity & 0x01) // odd sizes are odd //                                                                      
   1248                                 --sdkp->capacity;                                                                                               
   1249         }                                                                                                                                       
   1250                                                                                                                                                 
   1251 got_data:                                                                                                                                       
   1252         if (sector_size == 0) {                                                                                                                 
   1253                 sector_size = 512;                                                                                                              
   1254                 sd_printk(KERN_NOTICE, sdkp, "Sector size 0 reported, "                                                                         
   1255                           "assuming 512.\n");                                                                                                   
   1256         }                                                                                                                                       
   1257                                                                                                                                                 
   1258         if (sector_size != 512 &&                                                                                                               
   1259             sector_size != 1024 &&                                                                                                              
   1260             sector_size != 2048 &&                                                                                                              
   1261             sector_size != 4096 &&                                                                                                              
   1262             sector_size != 256) {                                                                                                               
�� 29  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
   1263                 sd_printk(KERN_NOTICE, sdkp, "Unsupported sector size %d.\n",                                                                   
   1264                           sector_size);                                                                                                         
   1265                 //                                                                                                                              
   1266                  * The user might want to re-format the drive with                                                                              
   1267                  * a supported sectorsize. Once this happens, it                                                                                
   1268                  * would be relatively trivial to set the thing up.                                                                             
   1269                  * For this reason, we leave the thing in the table.                                                                            
   1270                  //                                                                                                                             
   1271                 sdkp->capacity = 0;                                                                                                             
   1272                 //                                                                                                                              
   1273                  * set a bogus sector size so the normal read/write                                                                             
   1274                  * logic in the block layer will eventually refuse any                                                                          
   1275                  * request on this device without tripping over power                                                                           
   1276                  * of two sector size assumptions                                                                                               
   1277                  //                                                                                                                             
   1278                 sector_size = 512;                                                                                                              
   1279         }                                                                                                                                       
   1280         {                                                                                                                                       
   1281                //                                                                                                                               
   1282                  * The msdos fs needs to know the hardware sector size                                                                          
   1283                  * So I have created this table. See ll_rw_blk.c                                                                                
   1284                   * Jacques Gelinas (Jacques@solucorp.qc.ca)                                                                                    
   1285                  //                                                                                                                             
   1286                 int hard_sector = sector_size;                                                                                                  
   1287                 sector_t sz = (sdkp->capacity/2) * (hard_sector/256);                                                                           
   1288                 request_queue_t *queue = sdp->request_queue;                                                                                    
   1289                 sector_t mb = sz;                                                                                                               
  1290                                                                                                                                                  
   1291                 blk_queue_hardsect_size(queue, hard_sector);                                                                                    
   1292                 // avoid 64-bit division on 32-bit platforms //                                                                                 
   1293                 sector_div(sz, 625);                                                                                                            
   1294                 mb -= sz - 974;                                                                                                                 
   1295                 sector_div(mb, 1950);                                                                                                           
   1296                                                                                                                                                 
   1297                 sd_printk(KERN_NOTICE, sdkp,                                                                                                    
   1298                           "%llu %d-byte hardware sectors (%llu MB)\n",                                                                          
   1299                           (unsigned long long)sdkp->capacity,                                                                                   
   1300                           hard_sector, (unsigned long long)mb);                                                                                 
   1301         }                                                                                                                                       
   1302                                                                                                                                                 
   1303         // Rescale capacity to 512-byte units //                                                                                                
   1304         if (sector_size == 4096)                                                                                                                
   1305                 sdkp->capacity <<= 3;                                                                                                           
   1306         else if (sector_size == 2048)                                                                                                           
�� 30  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
   1307                 sdkp->capacity <<= 2;                                                                                                           
   1308         else if (sector_size == 1024)                                                                                                           
   1309                 sdkp->capacity <<= 1;                                                                                                           
   1310         else if (sector_size == 256)                                                                                                            
   1311                 sdkp->capacity >>= 1;                                                                                                           
   1312                                                                                                                                                 
   1313         sdkp->device->sector_size = sector_size;                                                                                                
   1314 }                                                                                                                                               
// ��������200����.�����֮,���������һ�仰��������֪��������̵�����,����רҵһ                                                                        
// ��˵,���� READ CAPACITY ����.����Ϥ SCSI ������ֵ���Ӧ��֪��,�ܶ� SCSI ���                                                                        
// ���������ְ汾,��ͬ�汾�������ʽ�᲻һ��,��Ȼ���ص���Ϣ��Ҳ������ͬ,���� READ                                                                          
// CAPACITY ������� 10 ���ֽڵĺ� 16 ���ֽڵ������汾.�� SBC-2 �� 5.10 �ں� 5.11 �ڷ�                                                                     
// ����ܵ��� READ CAPACITY(10) command �� READ CAPACITY(16) command.���߱�ǰ��                                                                            
// ��һ��������Ϣ.���������Ƕ�֮ǰ���ǲ���֪�������ĸ�����,��������Ļ���˼·������                                                                        
// �ö�����,���ʧ���˾���һ�³�����,����� 1211 ��goto repeat ��Ŀ��.�� goto repeat ֮ǰ                                                                  
// 1210��������longrcΪ1.���������ȸ�������SBC-2�ж�READ CAPACITY����ĸ�ʽ��                                                                              
// ��:                                                                                                                                                     
//                                                                                                                                                         
// ���ǿ�����һ��ʵ���������������,sg_readcap�����ֹ�����READ CAPACITY����.����                                                                           
// ������ҵ�һ���ų� 128M �� U�̷����������Ľ��.                                                                                                       
// [root@localhost ~]# sg_readcap /dev/sdc                                                                                                                 
// Read Capacity results:                                                                                                                                  
//    Last logical block address=257535 (0x3edff), Number of blocks=257536                                                                                 
//    Logical block length=512 bytes                                                                                                                       
// Hence:                                                                                                                                                  
//    Device size: 131858432 bytes, 125.8 MiB, 0.13 GB                                                                                                     
// ���ͬʱ,���ǽ�ϴ�������,�������ʵ���ϱȽ��鷳�ĵط����ڶ�buffer������ж�.ʵ��                                                                       
// �� buffer����װ���� READ CAPACITY ����ķ�����Ϣ.�����Ǵ� 1203 �п�ʼ�ж�,������                                                                        
// ��֪����� buffer �������� sd_revalidate_disk()�������.���СΪ SD_BUF_SIZE,�� 512 ��                                                                  
// �ֽ�.��ô��� buffer�����ݾ�����ʲôģ����?SBC-2 �� Table-35 �� READ CAPACITY(10)                                                                       
// �ķ������ݸ�������ͼ�ĸ�ʽ,                                                                                                                             
// �� 31  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
//                                                                                                                                                         
// ���� byte4,byte5,byte6,byte7 ��ͬ������ Block �Ĵ�С.����ν��������С,����˵�����е�                                                                    
// sector_size,�������������ǿ����Ķ��� 512bytes.�����ҵ���� U�̵�ȻҲ�����������.                                                                     
// RETURNED LOGICAL BLOCK ADDRESS ���Ǹ���������豸�ж��ٸ� Block,����ͨ�׵�                                                                              
// ˵,�ж��ٸ�����.��Ȼ,��׼ȷ��˵,�������������� N �� Block,��ô���ﷵ�ص������һ                                                                      
// �� Block �ı��,��Ϊ����Ǵ� 0 ��ʼ,�������һ�� Block �ı�ž��� N-1.�������ﷵ�ص�                                                                    
// �� N-1.�� SBC-2 �涨,���� byte0,byte1,byte2,byte3 ���ȫΪ FF,��ô˵�� READ                                                                             
// CAPACITY(10)�����Զ�ȡ�����̵�����.���е������ڴ�˵�еĻ��������.���������                                                                          
// ���ж�һ��,���sizeof(sdkp->capacity)ȷʵ����4,��ô�������������goto repeat,�Ķ�����                                                                   
// READ CAPACITY(16).ʵ����,��Ϊ capacity �� sector_t ���͵�,���� include/linux/types.h                                                                    
// ��,sector_t ����ô�����,                                                                                                                               
//     140 #ifdef CONFIG_LBD                                                                                                                               
//     141 typedef u64 sector_t;                                                                                                                           
//     142 #else                                                                                                                                           
//     143 typedef unsigned long sector_t;                                                                                                                 
//     144 #endif                                                                                                                                          
// ����,sector_t �� size �п������Ǵ��� 4 ��,Ҳ�п����ǵ��� 4 ��.������� 4 �Ǿ�û�취��.ֻ                                                                
// ������capacityΪ0.����û�а취��¼�¾����ж��ٸ�����,��ô���Ǵ��˾Ͳ���¼.(ͬʱ                                                                       
// ��������Ҳ���Կ����������������� capacity Ϊ 0,��Ŀ�Ķ���һ��,ֻ�������ܼ�������,��                                                                     
// ����ǿ������,�Ͼ�ǿŤ�Ĺϲ���.)                                                                                                                         
// ��Ȼ���û�����,��ô��ִ�� 1219 ��,���� sdkp �� capacity,�ղ�˵��,����                                                                                 
// byte0,byte1,byte2,byte3 �Ĺ�ͬ���õ�������� N �� N-1 �Ĺ�ϵ,�����������ǿ�����Ҫ����                                                                   
// 1.��� sdkp->capacity��¼�ľ��Ǵ����ж��ٸ�����.                                                                                                        
// �� 1223 ����� else ��һ��,������Գ������ buffer ���д����,��Ϊ SBC-2 �涨��,������                                                                  
// �ķ��ؽ�����������ͼ������:                                                                                                                           
//                                                                                                                                                         
// ���Կ���,��� byte0,byte1,��,byte7 �� 8 �� byte ��ͬ��������ʾ�� Block ��.��                                                                            
// byte8,byte9,byte10,byte11��ͬ���ñ�ʾ�� block �Ĵ�С,����˵������С.                                                                                    
// 1239 ��˵��Ҳ���� N �� N-1 ���Ǽ���,��Щ�豸�����������,���㱨��ʱ���Ѿ����Ǹ� 1                                                                       
// �� 32  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
// ������������,������������ֻ���ټ�һ,��������������������豸������ fix_capacity.                                                                        
// 1245 �������������һЩ����������Ƶ��豸��Ӧ�Դ�ʩ.����۾�Ʈ����.�Ͼ������̵�                                                                         
// ��С��Ҫ����ȥ���⳧��Ҳ̫�޳���.                                                                                                                       
// 1252 ��,������Щ������豸,����ֻ�ܼ���������������Ϸ�����,���Ǽ������ǵ�������                                                                        
// С�Ǵ��ڻ��� 512.                                                                                                                                       
// ��һ����,1258����һ��,������֪,������С����512,1024,2048,4096,��ε�Ҳ��256.����֮                                                                      
// ����豸�����ϾͿ���ȥ�μ��豸�а»���,û��Ҫ�ó�����������.                                                                                            
// 1280����1301�е�Ŀ����ע����˵�ú����,���ǿ���Ʈ������.ֻ����Ҫע��1291�е���                                                                          
// �� blk_queue_hardsect_size(),��������ǳ��Ķ�,����һ�仰,����һ�� struct request_queue_t                                                                
// ָ��ĳ�Ա hardsect_size ��ֵ����Ϊ����Ĳ��� hard_sector.�����Ǿ仰,������Ҳ��������                                                                   
// �� 512,�Ͼ����Ǿ�������.�������豸��Ҫ��ʾһ�� 80 ������ڲ�ͬ�ĸ���,����Ҳû��                                                                       
// ��.ֻ��ׯ������Ի��:��Īװ��,װ���⹷ҧ!��                                                                                                              
// 1304�п�ʼ����һ��if-else if,�������sector_size����һ��capacity,��ΪcapacityӦ������                                                                   
// ��¼�ж��ٸ�����,������ϣ���ڴ�����ͳһʹ��512�ֽڵ�����,(��Ҳ��Linux�е�һ���                                                                         
// ��)����������Ҫ����������һ��.��ԭ����������˵�� 100 ������,����ÿ������������                                                                          
// 4096���ֽ�,��ô�������Ҫ�Դ�����Ƕ���˵��512�ֽڽ��з���,��ô�ҾͿ��Լ�¼˵��                                                                         
// �������� 800 ������.                                                                                                                                    
// ���,1313 ��,�� sector_size Ҳ��¼�� sdkp �ĳ�Ա struct scsi_device ָ�� device�� sector_size                                                           
// ��.                                                                                                                                                     
//                                                                                                                                                         
// ������ɽ(��)                                                                                                                                            
// �ڶ�����ɽ,sd_read_write_protect_flag.                                                                                                                  
//    1327 //                                                                                                                                              
//    1328  * read write protect setting, if possible - called only in sd_revalidate_disk()                                                                
//    1329  * called with buffer of length SD_BUF_SIZE                                                                                                     
//    1330  //                                                                                                                                             
   1331 static void                                                                                                                                     
   1332 sd_read_write_protect_flag(struct scsi_disk *sdkp, unsigned char *buffer)                                                                       
   1333 {                                                                                                                                               
   1334         int res;                                                                                                                                
   1335         struct scsi_device *sdp = sdkp->device;                                                                                                 
   1336         struct scsi_mode_data data;                                                                                                             
   1337                                                                                                                                                 
   1338         set_disk_ro(sdkp->disk, 0);                                                                                                             
   1339         if (sdp->skip_ms_page_3f) {                                                                                                             
   1340                 sd_printk(KERN_NOTICE, sdkp, "Assuming Write Enabled\n");                                                                       
   1341                 return;                                                                                                                         
   1342         }                                                                                                                                       
   1343                                                                                                                                                 
   1344         if (sdp->use_192_bytes_for_3f) {                                                                                                        
   1345                 res = sd_do_mode_sense(sdp, 0, 0x3F, buffer, 192, &data, NULL);                                                                 
�� 33  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
   1346         } else {                                                                                                                                
   1347                 //                                                                                                                              
   1348                  * First attempt: ask for all pages (0x3F), but only 4 bytes.                                                                   
   1349                  * We have to start carefully: some devices hang if we ask                                                                      
   1350                  * for more than is available.                                                                                                  
   1351                  //                                                                                                                             
   1352                 res = sd_do_mode_sense(sdp, 0, 0x3F, buffer, 4, &data, NULL);                                                                   
   1353                                                                                                                                                 
   1354                 //                                                                                                                              
   1355                  * Second attempt: ask for page 0 When only page 0 is                                                                           
   1356                  * implemented, a request for page 3F may return Sense Key                                                                      
   1357                  * 5: Illegal Request, Sense Code 24: Invalid field in                                                                          
   1358                  * CDB.                                                                                                                         
   1359                  //                                                                                                                             
   1360                 if (!scsi_status_is_good(res))                                                                                                  
   1361                         res = sd_do_mode_sense(sdp, 0, 0, buffer, 4, &data,                                                                     
NULL);                                                                                                                                                  
   1362                                                                                                                                                 
   1363                 //                                                                                                                              
   1364                  * Third attempt: ask 255 bytes, as we did earlier.                                                                             
   1365                  //                                                                                                                             
   1366                 if (!scsi_status_is_good(res))                                                                                                  
   1367                         res = sd_do_mode_sense(sdp, 0, 0x3F, buffer, 255,                                                                       
   1368                                                &data, NULL);                                                                                    
   1369         }                                                                                                                                       
   1370                                                                                                                                                 
   1371         if (!scsi_status_is_good(res)) {                                                                                                        
   1372                 sd_printk(KERN_WARNING, sdkp,                                                                                                   
   1373                           "Test WP failed, assume Write Enabled\n");                                                                            
   1374         } else {                                                                                                                                
   1375                 sdkp->write_prot = ((data.device_specific & 0x80) != 0);                                                                        
   1376                 set_disk_ro(sdkp->disk, sdkp->write_prot);                                                                                      
   1377                 sd_printk(KERN_NOTICE, sdkp, "Write Protect is %s\n",                                                                           
   1378                           sdkp->write_prot ? "on" : "off");                                                                                     
   1379                 sd_printk(KERN_DEBUG, sdkp,                                                                                                     
   1380                           "Mode Sense: %02x %02x %02x %02x\n",                                                                                  
   1381                           buffer[0], buffer[1], buffer[2], buffer[3]);                                                                          
   1382         }                                                                                                                                       
   1383 }                                                                                                                                               
// ����������ƺܳ�,��ʵ������ľ���һ��,�Ǿ���1376��,����set_disk_ro()�Ӷ�ȷ��������                                                                      
// �Ƿ���д������.                                                                                                                                         
// 1338 ��,set_disk_ro �������ô���ֻ��,Ϊ 0 ���ǿɶ���д,Ϊ 1 ��������Ϊֻ��.����������                                                                   
// ֻ����������ϵ�������¼����,Ӳ���ϻ����������Լ���.��������ͨ������һ��δ�����                                                                        
// �յõ���һ��Ϣ,������1376 ���ٴ�����.                                                                                                                   
// �� 34  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
// ��ô��ε�֪д�����Ƿ���������?����������豸,���������� MODE SENSE.MODE                                                                              
// SENSE��������Ŀ�����ڻ���豸�ڲ��ܶ�Ǳ�ڵ���Ϣ,�����а����豸�Ƿ�������д��                                                                          
// ��,��Ȼ���и��� SCSI ���е���Ϣ.ֻ�������Ǵ�ʱ�˿�ֻ��עд��������û��.��Щ���Ծ�                                                                       
// ���豸������һ��,����������ʱ������ú���,��Ȼ��Щ����Ҳ�ǿ��Ըı��,�ͱ��緶��                                                                         
// ��,��������������ʱ����ƽƽ,���Ǿ�������,�������Ů.�ֱ��������,ԭ��������,����                                                                      
// ȴ�����Ů��.������SCSI�豸��˵,�ܶ����Կ��Ըı�,������Щ���ԾͲ����Ըı���,����                                                                        
// medium type,���������������͵��豸,����SCSI Block�豸,���ڲ�����MEDIUM TYPE��                                                                           
// ��� byte һ���� 00h.                                                                                                                                   
// �����ǵ�������Ϊ�˷����������,���������ΰ�װ,�ȵ���sd_do_mode_sense().                                                                                 
   1316 // called with buffer of length 512 //                                                                                                          
   1317 static inline int                                                                                                                               
   1318 sd_do_mode_sense(struct scsi_device *sdp, int dbd, int modepage,                                                                                
   1319                  unsigned char *buffer, int len, struct scsi_mode_data *data,                                                                   
   1320                  struct scsi_sense_hdr *sshdr)                                                                                                  
   1321 {                                                                                                                                               
   1322         return scsi_mode_sense(sdp, dbd, modepage, buffer, len,                                                                                 
   1323                                SD_TIMEOUT, SD_MAX_RETRIES, data,                                                                                
   1324                                sshdr);                                                                                                          
   1325 }                                                                                                                                               
// �� sd_do_mode_sense �������� scsi ���Ĳ�ͳһ�ṩ�� scsi_mode_sense(),���ں������ǾͲ�                                                                   
// ��ϸ������,��ִ֮��֮��,������Ǳ������� data ��,��data�� struct scsi_mode_data �ṹ��                                                                  
// ����.                                                                                                                                                   
     16 struct scsi_mode_data {                                                                                                                         
     17         __u32   length;                                                                                                                         
     18         __u16   block_descriptor_length;                                                                                                        
     19         __u8    medium_type;                                                                                                                    
     20         __u8    device_specific;                                                                                                                
     21         __u8    header_length;                                                                                                                  
     22         __u8    longlba:1;                                                                                                                      
     23 };                                                                                                                                              
// ����ÿһ����Ա���� scsi Э�����ܹ��ҵ���Ӧ��.�ͱ���ղ�˵�� medium_type,���� SCSI                                                                       
// ����,��һ���� 00h.����û��������.                                                                                                                       
// ������������ 1375 �������ж�,�� 1375 ��,Ϊɶ�ж� device_specific �� 0x80 ������?SBC-2                                                                   
// ����һ��ͼ��������� Device Specific �������.                                                                                                          
//                                                                                                                                                         
// ����bit7����WP,��Write Protect,д����λ.N��ǰ�����Ǹտ�ʼ�����̵�ʱ�����˵��д��                                                                       
// ��,���Զ�����������ǲ���İ��.�����һλΪ 1 ��˵��������д����,��֮����û������.                                                                       
// ���û������д����,��ô����־�ļ������Ǿ��ܿ��������������е�һ�仰:                                                                                    
// Dec  6 08:47:05 localhost kernel: sdb: Write Protect is off                                                                                             
// ���, sd_read_write_protect_flag ��һ�����������̾���:                                                                                                  
// �� 35  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
// 1.       �����:���̴�����������д������?                                                                                                               
// 2.       �������˵:�ǵ���������.                                                                                                                       
// 3.       �����ӡ: sdb: Write Protect is on                                                                                                             
// 4.       �������˵:��,��û������.                                                                                                                      
// 5.       �����ӡ: sdb: Write Protect is off                                                                                                            
// ���˵һ��,1344 ��,�ж���û������ use_192_bytes_for_3f,������Ϊʵ������,�ܶ����ֻ��                                                                    
// ���� MODE SENSE �� page=0x3f ʱ���䳤��Ϊ 192bytes,���������ڶ��� struct scsi_device                                                                    
// ��ʱ��Ϊ��Щ�豸׼������ôһ�� flag,�� scsi ����ɨ���豸��ʼ����ʱ��Ϳ���������ô                                                                      
// һ�� flag.��Ӧ�����Ƿ��������ʱ������ú� 192.                                                                                                         
// ��һ��1339��,skip_ms_page_3f,��Ҳ��һ�����Ƶ�flag,MODE SENSE������һ������page,                                                                         
// ͬ����ʵ������,ĳЩ�޴����豸�� page=0x3f ��ʱ������.����д����������ò�,��׼��                                                                      
// ��һ�� flag.                                                                                                                                            
// ����㻹���Ǻ�������� page ��ɶ��˼,��ô����������һ�� SPC-4 ��MODE SENSE ����                                                                         
// �ĸ�ʽ����ε�.                                                                                                                                         
// ������ 6 �ֽڵ�.                                                                                                                                        
//                                                                                                                                                         
// Ȼ���� 10 �ֽڵ�.                                                                                                                                       
//                                                                                                                                                         
// ������,PAGE CODE������������˵��page,������,��һ��ռ6��bits.�������ȡֵ��Χ��                                                                          
// �� 00h �� 3Fh(�� 11 1111).����������˵�� 3fh,����˵���㷢�� MODE SENSE �����ʱ��,                                                                      
// ���� PAGE CODE Ϊ 3fh��ʱ��,��Ϊ 3fh �����һ�� page,�ܶ��豸������һЩĪ�������                                                                       
// ����,������Ǻ�û����,����������Ҫ�������� flag ��������Щ���.                                                                                         
// ��Ȼ,����ܻ���֪��Ϊʲô��Ҫ PAGE ��ôһ������.Ok,��ʵ��������,������֪,��Դ����                                                                       
// �кܶ��į��,���Ǻ�����Ů��,�Ͼ�����ʿ�������˵��:��Ů��������,�Ȼ���Ů��,Ҳ����                                                                       
// ����.���� SCSI �������Ϊͬ���� IT ������,���ǶԿ�Դ�������ֵ���Ҳ��ͬ��,����������                                                                     
// �� 36  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
// ��� SCSI ��ʱ��һֱϣ���ѶԿ�Դ�����ֵ������õ�ףԸ�������豸��,������,��Դ����                                                                        
// ȱŮ��,�����Ǿ���˵,Ů�˾���һ����,(��Ȼ��,��Ů�˾���һ���Ǻ�.���˱�Ҫʱ,û��Ը��                                                                       
// ȥ����.),�����������豸�ڲ�������һ����,�Ȿ������豸��<<�ҵ��԰���>>,�����ø�                                                                         
// ��ʱ�еĻ�˵,�Ȿ������豸���Ը�д�漯,����Ҫ�Ķ��Ȿ��,��ͱ��뷢�� MODE                                                                              
// SENSE ����,���Ǿ�����������һ��,�����һҳһҳ�Ķ�,��������Ҫ����һ�� PAGE                                                                            
// CODE,����˵ҳ��,ͬʱ���ǿ��� Byte3 ���� SUBPAGE CODE,�������ҳ����,�����Ծ���                                                                          
// ��Ϊһҳ��ĳһ���������,���豸������һҳһҳ�Ķ�,Ҳ������һ��һ�εĶ�.����Ȼ,��                                                                        
// �� SUBPAGE CODE �� 8 �� bits,��������ֵ���� 255.��һ�� page ��������� 255 ��                                                                         
// subpage.                                                                                                                                                
//                                                                                                                                                         
// ������ɽ(��)                                                                                                                                            
// ������,��������ɽ�� sd_read_cache_type.                                                                                                                 
//    1385 //                                                                                                                                              
//    1386  * sd_read_cache_type - called only from sd_revalidate_disk()                                                                                   
//    1387  * called with buffer of length SD_BUF_SIZE                                                                                                     
//    1388  //                                                                                                                                             
   1389 static void                                                                                                                                     
   1390 sd_read_cache_type(struct scsi_disk *sdkp, unsigned char *buffer)                                                                               
   1391 {                                                                                                                                               
   1392         int len = 0, res;                                                                                                                       
   1393         struct scsi_device *sdp = sdkp->device;                                                                                                 
   1394                                                                                                                                                 
   1395         int dbd;                                                                                                                                
   1396         int modepage;                                                                                                                           
   1397         struct scsi_mode_data data;                                                                                                             
   1398         struct scsi_sense_hdr sshdr;                                                                                                            
   1399                                                                                                                                                 
   1400         if (sdp->skip_ms_page_8)                                                                                                                
   1401                 goto defaults;                                                                                                                  
   1402                                                                                                                                                 
   1403         if (sdp->type == TYPE_RBC) {                                                                                                            
   1404                 modepage = 6;                                                                                                                   
   1405                 dbd = 8;                                                                                                                        
   1406         } else {                                                                                                                                
   1407                 modepage = 8;                                                                                                                   
   1408                 dbd = 0;                                                                                                                        
   1409         }                                                                                                                                       
   1410                                                                                                                                                 
   1411         // cautiously ask //                                                                                                                    
   1412         res = sd_do_mode_sense(sdp, dbd, modepage, buffer, 4, &data, &sshdr);                                                                   
   1413                                                                                                                                                 
�� 37  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
   1414         if (!scsi_status_is_good(res))                                                                                                          
   1415                 goto bad_sense;                                                                                                                 
   1416                                                                                                                                                 
   1417         if (!data.header_length) {                                                                                                              
   1418                 modepage = 6;                                                                                                                   
   1419                 sd_printk(KERN_ERR, sdkp, "Missing header in MODE_SENSE                                                                         
response\n");                                                                                                                                           
   1420         }                                                                                                                                       
   1421                                                                                                                                                 
   1422         // that went OK, now ask for the proper length //                                                                                       
   1423         len = data.length;                                                                                                                      
   1424                                                                                                                                                 
   1425         //                                                                                                                                      
   1426          * We're only interested in the first three bytes, actually.                                                                            
   1427          * But the data cache page is defined for the first 20.                                                                                 
   1428          //                                                                                                                                     
   1429         if (len < 3)                                                                                                                            
   1430                 goto bad_sense;                                                                                                                 
   1431         if (len > 20)                                                                                                                           
   1432                 len = 20;                                                                                                                       
   1433                                                                                                                                                 
   1434         // Take headers and block descriptors into account //                                                                                   
   1435         len += data.header_length + data.block_descriptor_length;                                                                               
   1436         if (len > SD_BUF_SIZE)                                                                                                                  
   1437                 goto bad_sense;                                                                                                                 
   1438                                                                                                                                                 
   1439         // Get the data //                                                                                                                      
   1440         res = sd_do_mode_sense(sdp, dbd, modepage, buffer, len, &data, &sshdr);                                                                 
   1441                                                                                                                                                 
   1442         if (scsi_status_is_good(res)) {                                                                                                         
   1443                 int offset = data.header_length + data.block_descriptor_length;                                                                 
   1444                                                                                                                                                 
   1445                 if (offset >= SD_BUF_SIZE - 2) {                                                                                                
   1446                         sd_printk(KERN_ERR, sdkp, "Malformed MODE                                                                               
SENSE response\n");                                                                                                                                     
   1447                         goto defaults;                                                                                                          
   1448                 }                                                                                                                               
   1449                                                                                                                                                 
   1450                 if ((buffer[offset] & 0x3f) != modepage) {                                                                                      
   1451                         sd_printk(KERN_ERR, sdkp, "Got wrong page\n");                                                                          
   1452                         goto defaults;                                                                                                          
   1453                 }                                                                                                                               
   1454                                                                                                                                                 
   1455                 if (modepage == 8) {                                                                                                            
�� 38  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
   1456                         sdkp->WCE = ((buffer[offset + 2] & 0x04) != 0);                                                                         
   1457                         sdkp->RCD = ((buffer[offset + 2] & 0x01) != 0);                                                                         
   1458                 } else {                                                                                                                        
   1459                         sdkp->WCE = ((buffer[offset + 2] & 0x01) == 0);                                                                         
   1460                         sdkp->RCD = 0;                                                                                                          
   1461                 }                                                                                                                               
   1462                                                                                                                                                 
   1463                 sdkp->DPOFUA = (data.device_specific & 0x10) != 0;                                                                              
   1464                 if (sdkp->DPOFUA && !sdkp->device->use_10_for_rw) {                                                                             
   1465                         sd_printk(KERN_NOTICE, sdkp,                                                                                            
   1466                                   "Uses READ/WRITE(6), disabling FUA\n");                                                                       
   1467                         sdkp->DPOFUA = 0;                                                                                                       
   1468                 }                                                                                                                               
   1469                                                                                                                                                 
   1470                 sd_printk(KERN_NOTICE, sdkp,                                                                                                    
   1471                        "Write cache: %s, read cache: %s, %s\n",                                                                                 
   1472                        sdkp->WCE ? "enabled" : "disabled",                                                                                      
   1473                        sdkp->RCD ? "disabled" : "enabled",                                                                                      
   1474                        sdkp->DPOFUA ? "supports DPO and FUA"                                                                                    
   1475                        : "doesn't support DPO or FUA");                                                                                         
   1476                                                                                                                                                 
   1477                 return;                                                                                                                         
   1478         }                                                                                                                                       
   1479                                                                                                                                                 
   1480 bad_sense:                                                                                                                                      
   1481         if (scsi_sense_valid(&sshdr) &&                                                                                                         
   1482             sshdr.sense_key == ILLEGAL_REQUEST &&                                                                                               
   1483             sshdr.asc == 0x24 && sshdr.ascq == 0x0)                                                                                             
   1484                 // Invalid field in CDB //                                                                                                      
   1485                 sd_printk(KERN_NOTICE, sdkp, "Cache data unavailable\n");                                                                       
   1486         else                                                                                                                                    
   1487                 sd_printk(KERN_ERR, sdkp, "Asking for cache data failed\n");                                                                    
   1488                                                                                                                                                 
   1489 defaults:                                                                                                                                       
   1490         sd_printk(KERN_ERR, sdkp, "Assuming drive cache: write through\n");                                                                     
   1491         sdkp->WCE = 0;                                                                                                                          
   1492         sdkp->RCD = 0;                                                                                                                          
   1493         sdkp->DPOFUA = 0;                                                                                                                       
   1494 }                                                                                                                                               
// ����Ȼ,�����������Ҫ�Ĺ������ǵ��� sd_do_mode_sense,�����Ƿ��� MODE SENSE ����.                                                                        
// ����ǰ��˵��,SCSI �豸д�漯������ 64 ҳ(64=0x3f+1).���������Ǹ� modepage ��ֵΪ                                                                      
// 8,���߶��� RBC,��ֵΪ 6.����Ϊʲô��?�������Ǳ�����ȷ,�������µ�Ŀ���Ƕ�ȡ�豸д                                                                        
// �漯�й��� Cache ����Ϣ,��ʵ��ÿ�� SCSI ����,���߸���רҵ�����˵��,ÿһ��                                                                              
// Direct-access block device,������ʵ�� caches,ͨ��ʹ�� cache ��������豸������,�������                                                                 
// �� 39  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
// ���ٷ���ʱ��,���������������������.���� SBC-2 ��,Ϊ SCSI���̶�����һ�� Mode Page                                                                       
// ר������������ cache ��ص���Ϣ.���ǿ��Դ��������ű��п���,                                                                                             
//                                                                                                                                                         
// 08h ��� Page,������ caching mode page,��һ�� Page ����������Ҫ��.��Ҳ����Ϊʲô����                                                                    
// ��ֵ modepage Ϊ8.��������ѭ RBCЭ����豸���ֵ���� 6,������ǲ�ȥ���.                                                                                
// ����������Ҫ�����������.һ������� Caching Mode page ������ʲô��.��һ����������                                                                       
// �� 40  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
// �ǿ����� 1443 �ж����offset ���ױ�ʾʲô��˼?                                                                                                          
// �ȿ��ڶ�������.SPC-4 �е� Table238 ������ MODE SENSE ����ķ���ֵ�ĸ�ʽ:                                                                                
//                                                                                                                                                         
// ���Կ�����������ֵһ����������,�� Mode Parameter Header,Block Descriptor,Mode                                                                       
// Page(s).�� Mode Page �����ڵ�������.���������������Ҫ Mode Page 8,��ô���ͳ�������                                                                     
// ��ĵ�������.�����������еķ���ֵ�������� buffer[]������,�������Ҫ���� Mode Pages                                                                      
// ��һ����,���Ǿͱ���֪��ǰ���������ֵĳ���.����ǰ���������ֵĳ���Ϊ offset,��ô����                                                                      
// Ҫ���ʵ������־Ϳ���ʹ��buffer[offset],�������Ǿ�֪�����offset�ĺ�����.��ôǰ������                                                                    
// �����ж೤��?����֮��� offset �����Ƕ���?                                                                                                              
// �����ȿ���һ��������ζ����,���� 6 �ֽڵ�MODE SENSE,                                                                                                   
//                                                                                                                                                         
// ������ 10 �ֽڵ� MODE SENSE ����,�ⲿ����΢����Щ.                                                                                                      
//                                                                                                                                                         
// ��������� scsi_mode_sense()����,��ᷢ��,��ʵ data.header_length ǡǡ������� Mode                                                                     
// Parameter Header �ĳ���,�� data.block_descriptor_length ǡǡ���ǵڶ����ֵĳ���,�� Block                                                                 
// Descriptor�ĳ���.�����Ϊʲô���ǻ��� 1443 ���� offset ��������֮��.                                                                                    
// ���������� buffer[offset]�Ͷ�λ���� Mode Page��һ����,���� Mode Page ���峤ʲô����?                                                                    
// ���߸�ֱ��һ��,Caching Mode Page ��ʲô��?�� SBC-2 ��Table 101 ��������.                                                                                
// �� 41  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
//                                                                                                                                                         
// ���ǿ������Pageһ����19��bytes,������֪��buffer[offset]��Ӧ�ö�Ӧ����Byte0.������                                                                      
// ���ǿ��� Byte0 ��bit0��bit5 ����ľ��� PAGE CODE,������ caching mode page ��˵��Ӧ                                                                      
// ���� 08h,�����Ϊʲô������ 1450 ��Ҫȡ buffer[offset]�ĵ� 6 λ���ж����Ƿ��������ڴ�                                                                   
// ���Ǹ� 08h.�������,��˵������.��ʵ��,�κ�һ�� Mode Page ���� 6 λ��ʾ�Ķ��� Page                                                                       
// Code.���λ�þ��൱��������У�ڼ��ѧ��.�ֱ�һ�����ǲ�����Ҫ�ҵ���,�����ͨ��ѧ                                                                         
// ��ȥ�б�.                                                                                                                                               
// ��������,�ٴθ��� modepage �� 8 ���� 6 ������ͬ�ĸ�ֵ,���ǻ���ֻ�����������,������                                                                     
// modepage Ϊ 8 �����.buffer[offset+2]��������� Byte2.�����Զ�������ͼ����,����Ҫ����                                                                   
// �����WCE��RCD������bits,����������1����0.��ô����λ�ĺ�����ʲô��?SBC-2��                                                                              
// ������λ������������.                                                                                                                                   
// A writeback cache enable (WCE) bit set to zero specifies that the device server shall return GOOD                                                       
// status for a WRITE command only after successfully writing all of the data to the medium. A                                                             
// WCE bit set to one specifies that the device server may return GOOD status for a WRITE                                                                  
// command after successfully receiving the data and prior to having successfully written it to the                                                        
// medium.                                                                                                                                                 
//                                                                                                                                                         
// A read cache disable (RCD) bit set to zero specifies that the device server may return data                                                             
// requested by a READ command by accessing either the cache or medium. A RCD bit set to one                                                               
// specifies that the device server shall transfer all of the data requested by a READ command from                                                        
// the medium (i.e., data shall not be transferred from the cache).                                                                                        
// ����Ȼ������Щ�ʻ�����϶������Ǿ��������������ѧ����.Ψһһ������Ҳ�����                                                                             
// cache,���������� bit ��ֵ������֮��Ĺ�������,�������ǷѾ����۴��Ļ��ǲ����ֶη�ɽ                                                                      
// �� 42  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
// Խ���ɽ��ˮ����Ҫ�õ�������bit��ֵ.WCEΪ1˵��������д������ʱ���������cache,                                                                          
// ��ֻҪд�����ݵ���cache�о��ȷ��سɹ�,�����õȵ�����д���������Ժ��ٷ���.RCDΪ                                                                          
// 1 ��˵�����Ƕ����ݵ�ʱ�����ӽ����ж�,�����Ǵ� cache �ж�.                                                                                             
// ���,һ������ DPOFUA �� bit Ҳ����Ҫ�����μ����е�.���������������                                                                                     
// data.device_specific,�����������ǰ���Ƿ� Mode Parameter Header �е� DEVICE SPECIFIC                                                                    
// PARAMETER,������ѭ SBC-2 ���豸,��һ��ĸ�ʽҲ��ר���ж����:                                                                                           
//                                                                                                                                                         
// ��ʵ���ͼ����������ʶ.֮ǰ���Ǿ���ͨ����� WP λ���˽��豸�Ƿ�������д������.��                                                                        
// ����bit4����DPOFUA,��һ��Bit���Ϊ1.˵���豸֧��DPO��FUA bits,���Ϊ0,˵����                                                                            
// ������֧��DPO��FUA bits.DPO��disable page out����д,FUA��force unit access����д.                                                                       
// ��֪��,һζ�ĸ���ճ����һ�����޳ܵ�����,������Ҳ���ö���Ҫ��̫��,��Ϊ���ڱ�����                                                                         
// ��һ��������ɥ�����.����������,͵һ���˵�����������,͵�ܶ��˵���������о�,��                                                                        
// ����ֻ��ʱ������,ʱ���о�.                                                                                                                              
// When the cache becomes full of logical blocks, new logical blocks may replace those currently in                                                        
// the cache. The disable page out (DPO) bit in the CDB of commands performing write, read, or                                                             
// verify operations allows the application client to influence the replacement of logical blocks in the                                                   
// cache. For write operations, setting the DPO bit to one specifies that the device server should not                                                     
// replace existing logical blocks in the cache with the new logical blocks being written. For read and                                                    
// verify operations, setting the DPO bit to one specifies that the device server should not replace                                                       
// logical blocks in the cache with the logical blocks that are being read.                                                                                
//                                                                                                                                                         
// Application clients may use the force unit access (FUA) bit in the CDB of commands performing                                                           
// write or read operations to specify that the device server shall access the medium. For a write                                                         
// operation, setting the FUA bit to one causes the device server to complete the data write to the                                                        
// medium before completing the command. For a read operation, setting the FUA bit to one causes                                                           
// the device server to retrieve the logical blocks from the medium rather than from the cache.                                                            
//                                                                                                                                                         
// When the DPO and FUA bits are both set to one, write and read operations effectively bypass the                                                         
// cache.                                                                                                                                                  
// ������������SBC-2��4.10,ר�Ž���Cache��һ��.������Ӣ�ĺ���һ������,û����ô��                                                                         
// �׾�ͨ����������,��ô�ҽ����������Ķ�һ�����ϵ�����,��ѧϰӢ���кô�,���ٵ�����                                                                         
// ĳʦ��ѧԺѧ��Ͷ��<<Ϊ��������뵳���Ƚ���>>��ʱ��,������ĳ����һ����Ӣ�ı���ȡ                                                                         
// Ϊ��Behave the people��s advanced sex of the service and party��,������ĳʡ���ù���ɲ�ѧԺѧ                                                           
// ������<<���ؽ�ȡ��ץʵ�ɲ��Ͽ��������󿪷����¾���>>��ʱ��,������ĳ�˰���ץʵ��                                                                         
// ����� Really Grasp Solid Fuck.                                                                                                                         
// ������㲻�����濴,��ôһ�仰�ܽ�,������λ�˵�ľ��������� DPO �� FUA bits ����                                                                       
// �ó��� 1,��ô��Ķ�д����������ʹ�� cache.��Ϊ DPOFUA ������� bit4,�������ǿ���                                                                        
// 1463 ��,data.device_specific ���Ǻ� 0x10 ����,���ݷɳ������ֵ��Ƕ�֪��,�����õ��ľ���                                                                   
// bit4.                                                                                                                                                   
// ����,�� MODE SENSE ����һ��,READ/WRITE ����Ҳ�� 6 �ֽں� 10 �ֽڵ�,����                                                                                 
// READ/WRITE ����,Ĭ����������ǻ��ȳ���ʹ�� 10 �ֽڵ�.��������Ҳ������Υ����Ϸ��                                                                         
// �� 43  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
// ��.struct scsi_device �ṹ���� unsigned use_10_for_rw,������������õ�.Ĭ�������,���ǻ�                                                                
// ���豸��ʼ����ʱ��,ȷ�е�˵,�� scsi ����ɨ���ʱ��,scsi_add_lun �����л����� flag ��                                                                  
// ��Ϊ 1.�������ƫҪ��������,��Ҳ�����.����ʵ���� 6 �ֽڵ� READ/Write ������û�ж�                                                                      
// �� FUA,DPO,��������������Ҫ���� DPOFUA Ϊ 0.                                                                                                            
// ���,���� sdkp->WCE,sdkp->RCD,sdkp->DPOFUA,sd_read_cache_type()�������ض���.                                                                            
// ������������ɽ,���ǻص��� sd_revalidate_disk.                                                                                                           
//                                                                                                                                                         
// ��Ӧ�ò������� ioctl                                                                                                                                    
// 2007 ���ȥ��,��һ����������һ�����,�����Ǽ������������,��ϣ����λ��С��Ҳʹ��                                                                        
// �ֶ�.������������,�ó����ĳ���,�����ݵ�����.�������͵ľ�������,�д���ߵľ������.                                                                      
// ���Ҹ�����,�Ǽ���д�ҵ� blog,����˵ Linux ��Щ���¶�,����˵��Щ���ĵĺ���,��˵����                                                                      
// sd_probe֮��,����Ҫ�Ӵ�һЩ�µĺ�����,�����Ƴ�����ioctl,���嵽sdģ���о���sd_ioctl.                                                                     
// �������� scsi ���̷��������ʱ��,����������ᱻ����.������������ kdb ����ʾһ��:                                                                      
// ���� kdb �����öϵ�,sd_ioctl,                                                                                                                           
// Entering kdb (current=0xffff81022adcf140, pid 4074) on processor 6 due to KDB_ENTER()                                                                   
// [6]kdb> bp sd_ioctl                                                                                                                                     
// Instruction(i) BP #0 at 0xffffffff880b1de2 ([sd_mod]sd_ioctl)                                                                                           
//     is enabled globally adjust 1                                                                                                                        
// [6]kdb> go                                                                                                                                              
// Ȼ��ִ��һ�� scsi ����,���� INQUIRY ����.                                                                                                               
// [root@lfg2 tedkdb]# sg_inq /dev/sdg                                                                                                                     
// ����˵,����ʯ֮�� kdb ��ʾ���ʹ�ӡ�˳���,                                                                                                             
// Entering kdb (current=0xffff81022cdae760, pid 4095) on processor 5 due to Breakpoint @                                                                  
// 0xffffffff880b1de2                                                                                                                                      
// [5]kdb> bt                                                                                                                                              
// Stack traceback for pid 4095                                                                                                                            
// 0xffff81022cdae760     4095     4044  1    5   R  0xffff81022cdaea40 *sg_inq                                                                            
// rsp                rip                Function (args)                                                                                                   
//  ======================= <debug>                                                                                                                        
// 0xffff81022f619fd8 0xffffffff880b1de2 [sd_mod]sd_ioctl                                                                                                  
//  ======================= <normal>                                                                                                                       
// 0xffff81022d7f7d40 0xffffffff803101a0 blkdev_driver_ioctl+0x63                                                                                          
// 0xffff81022d7f7d80 0xffffffff80310810 blkdev_ioctl+0x65b                                                                                                
// 0xffff81022d7f7da0 0xffffffff80278825 __handle_mm_fault+0x6d3                                                                                           
// 0xffff81022d7f7db0 0xffffffff8029a1ea may_open+0x65                                                                                                     
// 0xffff81022d7f7e10 0xffffffff80322a48 __up_read+0x7a                                                                                                    
// 0xffff81022d7f7e40 0xffffffff80249b4f up_read+0x9                                                                                                       
// 0xffff81022d7f7e50 0xffffffff80482d6d do_page_fault+0x48a                                                                                               
// 0xffff81022d7f7e60 0xffffffff8027acff __vma_link+0x52                                                                                                   
// 0xffff81022d7f7ea0 0xffffffff802b58d5 block_ioctl+0x1b                                                                                                  
// 0xffff81022d7f7eb0 0xffffffff8029da98 do_ioctl+0x2c                                                                                                     
// �� 44  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
// 0xffff81022d7f7ee0 0xffffffff8029dd6d vfs_ioctl+0x247                                                                                                   
// 0xffff81022d7f7f30 0xffffffff8029dde9 sys_ioctl+0x5f                                                                                                    
// 0xffff81022d7f7f80 0xffffffff80209efc tracesys+0xdc                                                                                                     
// [5]kdb>                                                                                                                                                 
// ʵ�����ߵ�·����һ��ϵͳ���� ioctl,����˵�� sys_ioctl ������,�����ߵ��� sd_ioctl.                                                                       
// ���� sd_ioctl,���� drivers/scsi/sd.c:                                                                                                                   
//     641 ///                                                                                                                                             
//     642  *      sd_ioctl - process an ioctl                                                                                                             
//     643  *      @inode: only i_rdev/i_bdev members may be used                                                                                          
//     644  *      @filp: only f_mode and f_flags may be used                                                                                              
//     645  *      @cmd: ioctl command number                                                                                                              
//     646  *      @arg: this is third argument given to ioctl(2) system call.                                                                             
//     647  *      Often contains a pointer.                                                                                                               
//     648  *                                                                                                                                              
//     649  *      Returns 0 if successful (some ioctls return postive numbers on                                                                          
//     650  *      success as well). Returns a negated errno value in case of error.                                                                       
//     651  *                                                                                                                                              
//     652  *      Note: most ioctls are forward onto the block subsystem or further                                                                       
//     653  *      down in the scsi subsytem.                                                                                                              
//     654  ///                                                                                                                                            
    655 static int sd_ioctl(struct inode * inode, struct file * filp,                                                                                   
    656                     unsigned int cmd, unsigned long arg)                                                                                        
    657 {                                                                                                                                               
    658         struct block_device *bdev = inode->i_bdev;                                                                                              
    659         struct gendisk *disk = bdev->bd_disk;                                                                                                   
    660         struct scsi_device *sdp = scsi_disk(disk)->device;                                                                                      
    661         void __user *p = (void __user *)arg;                                                                                                    
    662         int error;                                                                                                                              
    663                                                                                                                                                 
    664         SCSI_LOG_IOCTL(1, printk("sd_ioctl: disk=%s, cmd=0x%x\n",                                                                               
    665                                                 disk->disk_name, cmd));                                                                         
    666                                                                                                                                                 
    667         //                                                                                                                                      
    668          * If we are in the middle of error recovery, don't let anyone                                                                          
    669          * else try and use this device.  Also, if error recovery fails, it                                                                     
    670          * may try and take the device offline, in which case all further                                                                       
    671          * access to the device is prohibited.                                                                                                  
    672          //                                                                                                                                     
    673         error = scsi_nonblockable_ioctl(sdp, cmd, p, filp);                                                                                     
    674         if (!scsi_block_when_processing_errors(sdp) || !error)                                                                                  
    675                 return error;                                                                                                                   
    676                                                                                                                                                 
    677         //                                                                                                                                      
    678          * Send SCSI addressing ioctls directly to mid level, send other                                                                        
�� 45  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
    679          * ioctls to block level and then onto mid level if they can't be                                                                       
680          * resolved.                                                                                                                                
    681          //                                                                                                                                     
    682         switch (cmd) {                                                                                                                          
    683                 case SCSI_IOCTL_GET_IDLUN:                                                                                                      
    684                 case SCSI_IOCTL_GET_BUS_NUMBER:                                                                                                 
    685                         return scsi_ioctl(sdp, cmd, p);                                                                                         
    686                 default:                                                                                                                        
    687                         error = scsi_cmd_ioctl(filp, disk, cmd, p);                                                                             
    688                         if (error != -ENOTTY)                                                                                                   
    689                                 return error;                                                                                                   
    690         }                                                                                                                                       
    691         return scsi_ioctl(sdp, cmd, p);                                                                                                         
    692 }                                                                                                                                               
// �������öϵ�,scsi_cmd_ioctl�� scsi_ioctl,�ᷢ��,���õ��� scsi_cmd_ioctl.                                                                                
// Instruction(i) breakpoint #2 at 0xffffffff802ee554 (adjusted)                                                                                           
// 0xffffffff802ee554 scsi_cmd_ioctl:         int3                                                                                                         
//                                                                                                                                                         
// Entering kdb (current=0xffff81022e1a01c0, pid 3583) due to Breakpoint @ 0xffffffff802ee554                                                              
// kdb> bt                                                                                                                                                 
// Stack traceback for pid 3583                                                                                                                            
// 0xffff81022e1a01c0     3583     3425  1    0   R  0xffff81022e1a0490 *sg_inq                                                                            
// rsp                rip                Function (args)                                                                                                   
//  ======================= <debug>                                                                                                                        
// 0xffffffff805dafa0 0xffffffff88080dcc [sd_mod]sd_ioctl                                                                                                  
// 0xffffffff805dafd8 0xffffffff802ee554 scsi_cmd_ioctl                                                                                                    
//  ======================= <normal>                                                                                                                       
// 0xffff8102112d7d70 0xffffffff88080e68 [sd_mod]sd_ioctl+0x9c                                                                                             
// 0xffff8102112d7db0 0xffffffff802ec9b2 blkdev_driver_ioctl+0x3a                                                                                          
// 0xffff8102112d7dc0 0xffffffff802ed00d blkdev_ioctl+0x627                                                                                                
// 0xffff8102112d7e40 0xffffffff80239e1b up_read+0x9                                                                                                       
// 0xffff8102112d7e50 0xffffffff80435872 do_page_fault+0x48a                                                                                               
// 0xffff8102112d7ea0 0xffffffff802641f6 vma_link+0x3a                                                                                                     
// 0xffff8102112d7ee0 0xffffffff80295155 block_ioctl+0x1b                                                                                                  
// 0xffff8102112d7ef0 0xffffffff8027ec3b do_ioctl+0x1b                                                                                                     
// 0xffff8102112d7f00 0xffffffff8027ee7e vfs_ioctl+0x20e                                                                                                   
// 0xffff8102112d7f30 0xffffffff8027eeef sys_ioctl+0x5f                                                                                                    
// 0xffff8102112d7f80 0xffffffff80209c8c tracesys+0xdc                                                                                                     
// ���е������� block/scsi_ioctl.c                                                                                                                         
    520 int scsi_cmd_ioctl(struct file *file, struct gendisk *bd_disk, unsigned int cmd, void                                                           
__user *arg)                                                                                                                                            
    521 {                                                                                                                                               
    522         request_queue_t *q;                                                                                                                     
    523         int err;                                                                                                                                
�� 46  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
    524                                                                                                                                                 
    525         q = bd_disk->queue;                                                                                                                     
    526         if (!q)                                                                                                                                 
    527                 return -ENXIO;                                                                                                                  
    528                                                                                                                                                 
    529         if (blk_get_queue(q))                                                                                                                   
    530                 return -ENXIO;                                                                                                                  
    531                                                                                                                                                 
    532         switch (cmd) {                                                                                                                          
    533                 //                                                                                                                              
    534                  * new sgv3 interface                                                                                                           
    535                  //                                                                                                                             
    536                 case SG_GET_VERSION_NUM:                                                                                                        
    537                         err = sg_get_version(arg);                                                                                              
    538                         break;                                                                                                                  
    539                 case SCSI_IOCTL_GET_IDLUN:                                                                                                      
    540                         err = scsi_get_idlun(q, arg);                                                                                           
    541                         break;                                                                                                                  
    542                 case SCSI_IOCTL_GET_BUS_NUMBER:                                                                                                 
    543                         err = scsi_get_bus(q, arg);                                                                                             
    544                         break;                                                                                                                  
    545                 case SG_SET_TIMEOUT:                                                                                                            
    546                         err = sg_set_timeout(q, arg);                                                                                           
    547                         break;                                                                                                                  
    548                 case SG_GET_TIMEOUT:                                                                                                            
    549                         err = sg_get_timeout(q);                                                                                                
    550                         break;                                                                                                                  
    551                 case SG_GET_RESERVED_SIZE:                                                                                                      
    552                         err = sg_get_reserved_size(q, arg);                                                                                     
    553                         break;                                                                                                                  
554                 case SG_SET_RESERVED_SIZE:                                                                                                          
    555                         err = sg_set_reserved_size(q, arg);                                                                                     
    556                         break;                                                                                                                  
    557                 case SG_EMULATED_HOST:                                                                                                          
    558                         err = sg_emulated_host(q, arg);                                                                                         
    559                         break;                                                                                                                  
    560                 case SG_IO: {                                                                                                                   
    561                         struct sg_io_hdr hdr;                                                                                                   
    562                                                                                                                                                 
    563                         err = -EFAULT;                                                                                                          
    564                         if (copy_from_user(&hdr, arg, sizeof(hdr)))                                                                             
    565                                 break;                                                                                                          
    566                         err = sg_io(file, q, bd_disk, &hdr);                                                                                    
    567                         if (err == -EFAULT)                                                                                                     
�� 47  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
    568                                 break;                                                                                                          
    569                                                                                                                                                 
    570                          if (copy_to_user(arg, &hdr, sizeof(hdr)))                                                                              
    571                                 err = -EFAULT;                                                                                                  
    572                         break;                                                                                                                  
    573                 }                                                                                                                               
    574                 case CDROM_SEND_PACKET: {                                                                                                       
    575                         struct cdrom_generic_command cgc;                                                                                       
    576                         struct sg_io_hdr hdr;                                                                                                   
    577                                                                                                                                                 
    578                         err = -EFAULT;                                                                                                          
    579                         if (copy_from_user(&cgc, arg, sizeof(cgc)))                                                                             
    580                                 break;                                                                                                          
    581                         cgc.timeout = clock_t_to_jiffies(cgc.timeout);                                                                          
    582                         memset(&hdr, 0, sizeof(hdr));                                                                                           
    583                         hdr.interface_id = 'S';                                                                                                 
    584                         hdr.cmd_len = sizeof(cgc.cmd);                                                                                          
    585                         hdr.dxfer_len = cgc.buflen;                                                                                             
    586                         err = 0;                                                                                                                
    587                         switch (cgc.data_direction) {                                                                                           
    588                                 case CGC_DATA_UNKNOWN:                                                                                          
    589                                         hdr.dxfer_direction =                                                                                   
SG_DXFER_UNKNOWN;                                                                                                                                       
    590                                         break;                                                                                                  
    591                                 case CGC_DATA_WRITE:                                                                                            
    592                                         hdr.dxfer_direction =                                                                                   
SG_DXFER_TO_DEV;                                                                                                                                        
    593                                         break;                                                                                                  
    594                                 case CGC_DATA_READ:                                                                                             
    595                                         hdr.dxfer_direction =                                                                                   
SG_DXFER_FROM_DEV;                                                                                                                                      
596                                         break;                                                                                                      
    597                                 case CGC_DATA_NONE:                                                                                             
    598                                         hdr.dxfer_direction =                                                                                   
SG_DXFER_NONE;                                                                                                                                          
    599                                         break;                                                                                                  
    600                                 default:                                                                                                        
    601                                         err = -EINVAL;                                                                                          
    602                         }                                                                                                                       
    603                         if (err)                                                                                                                
    604                                 break;                                                                                                          
    605                                                                                                                                                 
    606                         hdr.dxferp = cgc.buffer;                                                                                                
    607                         hdr.sbp = cgc.sense;                                                                                                    
�� 48  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
    608                         if (hdr.sbp)                                                                                                            
    609                                 hdr.mx_sb_len = sizeof(struct request_sense);                                                                   
    610                         hdr.timeout = cgc.timeout;                                                                                              
    611                         hdr.cmdp = ((struct cdrom_generic_command __user*)                                                                      
arg)->cmd;                                                                                                                                              
    612                         hdr.cmd_len = sizeof(cgc.cmd);                                                                                          
    613                                                                                                                                                 
    614                         err = sg_io(file, q, bd_disk, &hdr);                                                                                    
    615                         if (err == -EFAULT)                                                                                                     
    616                                 break;                                                                                                          
    617                                                                                                                                                 
    618                         if (hdr.status)                                                                                                         
    619                                 err = -EIO;                                                                                                     
    620                                                                                                                                                 
    621                         cgc.stat = err;                                                                                                         
    622                         cgc.buflen = hdr.resid;                                                                                                 
    623                         if (copy_to_user(arg, &cgc, sizeof(cgc)))                                                                               
    624                                 err = -EFAULT;                                                                                                  
    625                                                                                                                                                 
    626                         break;                                                                                                                  
    627                 }                                                                                                                               
    628                                                                                                                                                 
    629                 //                                                                                                                              
    630                  * old junk scsi send command ioctl                                                                                             
    631                  //                                                                                                                             
    632                 case SCSI_IOCTL_SEND_COMMAND:                                                                                                   
    633                         printk(KERN_WARNING "program %s is using a                                                                              
deprecated SCSI ioctl, please convert it to SG_IO\        n", current->comm);                                                                           
634                         err = -EINVAL;                                                                                                              
    635                         if (!arg)                                                                                                               
    636                                 break;                                                                                                          
    637                                                                                                                                                 
    638                         err = sg_scsi_ioctl(file, q, bd_disk, arg);                                                                             
    639                         break;                                                                                                                  
    640                 case CDROMCLOSETRAY:                                                                                                            
    641                         err = blk_send_start_stop(q, bd_disk, 0x03);                                                                            
    642                         break;                                                                                                                  
    643                 case CDROMEJECT:                                                                                                                
    644                         err = blk_send_start_stop(q, bd_disk, 0x02);                                                                            
    645                         break;                                                                                                                  
    646                 default:                                                                                                                        
    647                         err = -ENOTTY;                                                                                                          
    648         }                                                                                                                                       
    649                                                                                                                                                 
�� 49  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
    650         blk_put_queue(q);                                                                                                                       
    651         return err;                                                                                                                             
    652 }                                                                                                                                               
// ͨ��kdb�ĸ���,��ᷢ�ִ��ݽ�������cmd��SG_IO.����֮,switch-case��һ������ջᶨ                                                                         
// ����560�����SG_IO��.��ô�����漰��һ���ṹ��ͺ���Ҫ��,����include/scsi/sg.h�е�                                                                       
// sg_io_hdr.                                                                                                                                              
     83 typedef struct sg_io_hdr                                                                                                                        
     84 {                                                                                                                                               
     85     int interface_id;            // [i] 'S' for SCSI generic (required) //                                                                      
     86     int dxfer_direction;         // [i] data transfer direction  //                                                                             
     87     unsigned char cmd_len;      // [i] SCSI command length ( <= 16 bytes) //                                                                    
     88     unsigned char mx_sb_len;    // [i] max length to write to sbp //                                                                            
     89     unsigned short iovec_count; // [i] 0 implies no scatter gather //                                                                           
     90     unsigned int dxfer_len;     // [i] byte count of data transfer //                                                                           
     91     void __user *dxferp;        // [i], [*io] points to data transfer memory                                                                    
     92                                               or scatter gather list //                                                                         
     93     unsigned char __user *cmdp; // [i], [*i] points to command to perform //                                                                    
     94     void __user *sbp;           // [i], [*o] points to sense_buffer memory //                                                                   
     95     unsigned int timeout;       // [i] MAX_UINT->no timeout (unit: millisec) //                                                                 
     96     unsigned int flags;          // [i] 0 -> default, see SG_FLAG... //                                                                         
     97     int pack_id;                // [i->o] unused internally (normally) //                                                                       
     98     void __user * usr_ptr;      // [i->o] unused internally //                                                                                  
     99     unsigned char status;       // [o] scsi status //                                                                                           
    100     unsigned char masked_status;// [o] shifted, masked scsi status //                                                                           
    101     unsigned char msg_status;   // [o] messaging level data (optional) //                                                                       
    102     unsigned char sb_len_wr;    // [o] byte count actually written to sbp //                                                                    
    103     unsigned short host_status; // [o] errors from host adapter //                                                                              
    104     unsigned short driver_status;// [o] errors from software driver //                                                                          
    105     int resid;                  // [o] dxfer_len - actual_transferred //                                                                        
    106     unsigned int duration;      // [o] time taken by cmd (unit: millisec) //                                                                    
    107     unsigned int info;          // [o] auxiliary information //                                                                                 
    108 } sg_io_hdr_t;  // 64 bytes long (on i386) //                                                                                                   
// ������,cmdpָ��ָ��Ĳ��Ǳ���,���������Ҳ.                                                                                                           
// �й�Linux�±�̾������һ�������copy_from_user��copy_to_user�������ǻҼ��ĺ���                                                                         
// İ����,�ں˿ռ���û��ռ䴫�����ݵ��������亯��,��Զ�۾Ͳ�˵��,���� 2.4 �ں��ǻ��                                                                      
// ��������ʦ��дһ���򵥵��ַ�������ʱ�������������������.�����������˵,���ǰ�                                                                          
// arg��������copy��hdr��,Ȼ�����sg_io���ʵ���ԵĹ���,Ȼ���ٰ�hdr�������copy                                                                          
// �ص� arg ��.                                                                                                                                            
// ��һ������ sg_io,����block/scsi_ioctl.c:                                                                                                                
    225 static int sg_io(struct file *file, request_queue_t *q,                                                                                         
    226                 struct gendisk *bd_disk, struct sg_io_hdr *hdr)                                                                                 
    227 {                                                                                                                                               
    228         unsigned long start_time, timeout;                                                                                                      
    229         int writing = 0, ret = 0;                                                                                                               
�� 50  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
    230         struct request *rq;                                                                                                                     
    231         char sense[SCSI_SENSE_BUFFERSIZE];                                                                                                      
    232         unsigned char cmd[BLK_MAX_CDB];                                                                                                         
    233         struct bio *bio;                                                                                                                        
    234                                                                                                                                                 
    235         if (hdr->interface_id != 'S')                                                                                                           
    236                 return -EINVAL;                                                                                                                 
    237         if (hdr->cmd_len > BLK_MAX_CDB)                                                                                                         
    238                 return -EINVAL;                                                                                                                 
    239         if (copy_from_user(cmd, hdr->cmdp, hdr->cmd_len))                                                                                       
    240                 return -EFAULT;                                                                                                                 
    241         if (verify_command(file, cmd))                                                                                                          
    242                 return -EPERM;                                                                                                                  
    243                                                                                                                                                 
    244         if (hdr->dxfer_len > (q->max_hw_sectors << 9))                                                                                          
    245                 return -EIO;                                                                                                                    
    246                                                                                                                                                 
    247         if (hdr->dxfer_len)                                                                                                                     
    248                 switch (hdr->dxfer_direction) {                                                                                                 
    249                 default:                                                                                                                        
    250                         return -EINVAL;                                                                                                         
    251                 case SG_DXFER_TO_DEV:                                                                                                           
    252                         writing = 1;                                                                                                            
    253                         break;                                                                                                                  
    254                 case SG_DXFER_TO_FROM_DEV:                                                                                                      
    255                 case SG_DXFER_FROM_DEV:                                                                                                         
    256                         break;                                                                                                                  
    257                 }                                                                                                                               
    258                                                                                                                                                 
    259         rq = blk_get_request(q, writing ? WRITE : READ, GFP_KERNEL);                                                                            
    260         if (!rq)                                                                                                                                
    261                 return -ENOMEM;                                                                                                                 
    262                                                                                                                                                 
    263         //                                                                                                                                      
    264          * fill in request structure                                                                                                            
    265          //                                                                                                                                     
    266         rq->cmd_len = hdr->cmd_len;                                                                                                             
    267         memset(rq->cmd, 0, BLK_MAX_CDB); // ATAPI hates garbage after CDB //                                                                    
    268         memcpy(rq->cmd, cmd, hdr->cmd_len);                                                                                                     
    269                                                                                                                                                 
    270         memset(sense, 0, sizeof(sense));                                                                                                        
    271         rq->sense = sense;                                                                                                                      
    272         rq->sense_len = 0;                                                                                                                      
    273                                                                                                                                                 
�� 51  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
    274         rq->cmd_type = REQ_TYPE_BLOCK_PC;                                                                                                       
    275                                                                                                                                                 
    276         timeout = msecs_to_jiffies(hdr->timeout);                                                                                               
    277         rq->timeout = (timeout < INT_MAX) ? timeout : INT_MAX;                                                                                  
    278         if (!rq->timeout)                                                                                                                       
    279                 rq->timeout = q->sg_timeout;                                                                                                    
    280         if (!rq->timeout)                                                                                                                       
    281                 rq->timeout = BLK_DEFAULT_TIMEOUT;                                                                                              
    282                                                                                                                                                 
    283         if (hdr->iovec_count) {                                                                                                                 
    284                 const int size = sizeof(struct sg_iovec) * hdr->iovec_count;                                                                    
    285                 struct sg_iovec *iov;                                                                                                           
    286                                                                                                                                                 
    287                 iov = kmalloc(size, GFP_KERNEL);                                                                                                
    288                 if (!iov) {                                                                                                                     
    289                         ret = -ENOMEM;                                                                                                          
    290                         goto out;                                                                                                               
    291                 }                                                                                                                               
    292                                                                                                                                                 
    293                 if (copy_from_user(iov, hdr->dxferp, size)) {                                                                                   
    294                         kfree(iov);                                                                                                             
    295                         ret = -EFAULT;                                                                                                          
    296                         goto out;                                                                                                               
    297                 }                                                                                                                               
    298                                                                                                                                                 
    299                 ret = blk_rq_map_user_iov(q, rq, iov, hdr->iovec_count,                                                                         
    300                                           hdr->dxfer_len);                                                                                      
    301                 kfree(iov);                                                                                                                     
    302         } else if (hdr->dxfer_len)                                                                                                              
    303                 ret = blk_rq_map_user(q, rq, hdr->dxferp, hdr->dxfer_len);                                                                      
    304                                                                                                                                                 
    305         if (ret)                                                                                                                                
    306                 goto out;                                                                                                                       
    307                                                                                                                                                 
    308         bio = rq->bio;                                                                                                                          
    309         rq->retries = 0;                                                                                                                        
    310                                                                                                                                                 
    311         start_time = jiffies;                                                                                                                   
    312                                                                                                                                                 
    313         // ignore return value. All information is passed back to caller                                                                        
    314          * (if he doesn't check that is his problem).                                                                                           
    315          * N.B. a non-zero SCSI status is _not_ necessarily an error.                                                                           
    316          //                                                                                                                                     
    317         blk_execute_rq(q, bd_disk, rq, 0);                                                                                                      
�� 52  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
    318                                                                                                                                                 
    319         // write to all output members //                                                                                                       
    320         hdr->status = 0xff & rq->errors;                                                                                                        
    321         hdr->masked_status = status_byte(rq->errors);                                                                                           
    322         hdr->msg_status = msg_byte(rq->errors);                                                                                                 
    323         hdr->host_status = host_byte(rq->errors);                                                                                               
    324         hdr->driver_status = driver_byte(rq->errors);                                                                                           
    325         hdr->info = 0;                                                                                                                          
    326         if (hdr->masked_status || hdr->host_status || hdr->driver_status)                                                                       
    327                 hdr->info |= SG_INFO_CHECK;                                                                                                     
    328         hdr->resid = rq->data_len;                                                                                                              
    329         hdr->duration = ((jiffies - start_time) * 1000) / HZ;                                                                                   
    330         hdr->sb_len_wr = 0;                                                                                                                     
    331                                                                                                                                                 
    332         if (rq->sense_len && hdr->sbp) {                                                                                                        
    333                 int len = min((unsigned int) hdr->mx_sb_len, rq->sense_len);                                                                    
    334                                                                                                                                                 
    335                 if (!copy_to_user(hdr->sbp, rq->sense, len))                                                                                    
    336                         hdr->sb_len_wr = len;                                                                                                   
337         }                                                                                                                                           
    338                                                                                                                                                 
    339         if (blk_rq_unmap_user(bio))                                                                                                             
    340                 ret = -EFAULT;                                                                                                                  
    341                                                                                                                                                 
    342         // may not have succeeded, but output values written to control                                                                         
    343          * structure (struct sg_io_hdr).  //                                                                                                    
    344 out:                                                                                                                                            
    345         blk_put_request(rq);                                                                                                                    
    346         return ret;                                                                                                                             
    347 }                                                                                                                                               
// ���ѿ�������hdrʵ���ϰ�����������ɫ,һ��������,һ�������.������Ϊ�˵õ���Ϣ����                                                                        
// ȡ���ֶ���Ȼ�� blk_execute_rq,����Ȼ�����ύ request �ķ�ʽ,�� blk_execute_rq ֮��,ʵ��                                                                 
// ����Ϣ�Ѿ����浽�� rq �ĸ�����Ա���,����֮��Ĵ�����ǰ���Ϣ�� rq �ĳ�Ա��ת�Ƶ�                                                                       
// hdr�ĳ�Ա��.��������ͺñ�,��ȥ�乬������Ӿ,�һ�900��Ǯ����һ����Ӿ��,������Ч��                                                                        
// ������,�ܹ������� 30 ��,����ÿ����ȥ��Ӿ�͵�ƾ���ſ�����,���ҳ�����ʱ��,������Ա��                                                                      
// �ѿ�������,�������� 30 ������,ÿ��һ�ι�����Ա�Ữ��һ��.���� hdr ������������þ�                                                                      
// �൱�������ſ�,������ȥ��Ҫ�����򽻵�,���ҽ�����ȥʱ��״̬�ǲ�һ����.                                                                                   
// ��ô�����������������ʲô�����Ǻ�����˵�,����������עһЩϸ��.���Ƚ�� struct                                                                         
// sg_io_hdr���ΰ��Ľṹ����������.                                                                                                                      
// interface_id,������Ǵ�S��.��ʾ Scsi Generic.����ʷԨԴ��˵���������Ǹ����� sg ��ģ��.                                                                
// ����֮��Ӧ������һ������ pg ��ģ��(parallel port generic driver,���ж˿�ͨ������),Ҳ����                                                                
// interface_id��ôһ������,�����������������Ϊ��P��.                                                                                                   
// dxfer_direction,����ͱ�ʾ���ݴ��䷽��.�������д���������������ȡֵΪ                                                                                 
// SG_DXFER_TO_DEV,���ڶ����������������ȡֵΪ SG_DXFER_FROM_DEV.                                                                                         
// �� 53  ҳ  �� 54  ҳ Linux  ��Щ�¶�֮����SCSI Ӳ��                                                                                                     
// cmd_len �Ͳ���˵��,������ scsi ����ĳ���.������С�ڵ��� 16.��Ϊ scsi ���������� 16                                                                   
// ���ֽ�.�����Ϊʲô 237 ���ж��Ƿ���� 16.(BLK_MAX_CDB ������Ϊ 16.)                                                                                    
// dxfer_len�������ݴ���׶ε��׻ᴫ������ֽ�.max_hw_sectors��ʾ����request����ܴ�                                                                       
// ����ٸ� sectors,�����Ӳ������.һ�� sector �� 512 ���ֽ�,���� 244 ��Ҫ���� 9 λ,������                                                                 
// 512.                                                                                                                                                    
// 259 ��,blk_get_request �����Ͽ������Ϊ����һ�� struct request �ṹ��.                                                                                  
// Ȼ�� 268 ��,�� cmd ���Ƹ� rq->cmd.�� cmd ֻ�Ǹղ� 239 �д� hdr->cmdp �� copy������.                                                                     
// ��Ҫע�����274������������rq->cmd_type��REQ_TYPE_BLOCK_PC,block�Ǳ߻ᰴ��                                                                              
// ͬ���������ͽ��в�ͬ�Ĵ���.                                                                                                                             
// 283��,iovec_count,����dxferp�Ƿֲ�����.���iovec_countΪ0,dxferp��ʾ�û��ռ��ڴ��                                                                      
// ַ,���iovec_count����0,��ôdxferpʵ��ָ����һ��scatter-gather����,��������е�ÿһ                                                                     
// ����Ա��һ�� sg_iovec_t�ṹ�����.struct sg_iovec ������ include/scsi/sg.h:                                                                             
     76 typedef struct sg_iovec // same structure as used by readv() Linux system //                                                                    
     77 {                       // call. It defines one scatter-gather element. //                                                                      
     78     void __user *iov_base;      // Starting address  //                                                                                         
     79     size_t iov_len;             // Length in bytes  //                                                                                          
     80 } sg_iovec_t;                                                                                                                                   
// �� blk_rq_map_user �� blk_rq_map_user_iov ��������һ����,�����û����ݺ� request ֮���                                                                  
// ӳ��.��񼸺�ÿ���˶���˵�� Linux ����ν���㿽������,����˵��������㿽����һ����                                                                       
// ���Ǿ������֮��.����������������Ŀ�ľ���Ϊ��ʹ���㿽������.�㿽���������Բ���˵,                                                                       
// ��������,���Ч��,����ʮ�ߴ󳫵��Ŀ�ѧ��չ�����Ǻϵ�.Ȼ��,�������漰����̶ˮδ��                                                                        
// ̫����,���ǾͲ�ȥ������.                                                                                                                                
// ��ִ���� blk_execute_rq֮��ͼ���.                                                                                                                    
// resid ��ʾ��ʣ�¶����ֽ�û�д���.                                                                                                                       
// duration ��ʾ�� scsi ������͵����֮���ʱ��,��λ�Ǻ���.                                                                                             
// sbp ָ������д Scsi sense buffer��user memory.                                                                                                          
// sb_len_wr��ʾʵ��д�˶��ٸ�bytes��sbpָ���user memory��.��������ɹ��˻����Ͼ�                                                                         
// ����д sense buffer,�����Ļ� sb_len_wr���� 0.                                                                                                           
// mx_sb_len ��������� sbp ��д������ size.�����ѧ��������ѧ��֤�ĸ��Ƕ���֪                                                                         
// ��,sb_len_wr<=mx_sb_len.                                                                                                                                
// ��ô���,����ʵ���ϾͿ��Դ����˽��˴�Ӧ�ò���������θ� scsi �豸���������.sg_inq                                                                      
// ʵ���ϴ������� ioctl ��ϵͳ����,��������շת����,���� sd_ioctl �ᱻ����.�� sd_ioctl ���                                                                
// �� scsi ���Ĳ��ṩ�ĺ���,sg_io,�����ߵ�·����Ȼ�� blk_execute_rq,�������������������                                                                   
// ���� usb-storage ǣ���ֵ�,������ block ���Ǳ߶� scsi ������з���ʱ�Ѿ���ϸ�Ľ��ܹ���.                                                                  
//                                                                                                                                                         
//                                                                                                                                                         
// �� 54  ҳ  �� 54  ҳ                                                                                                                                    