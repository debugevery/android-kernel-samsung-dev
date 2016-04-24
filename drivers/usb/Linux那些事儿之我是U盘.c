//   1
// Linux��Щ�¶�֮����U �� 
// ---------------------------------------------------------------------------------------------------------------------- 
// ժҪ 
//   2005��6��,������ѧ΢����ϵ���Ʊ�ҵ�����,��ʦ����:������һ�仰����һ��usb��
// ��.�һ���һ��:��ʦ,���в���,Ҫ����һ�仰�����һ�����ô��д��ô�������¸���? 
//  
// �ؼ��ʣ�Linux, Kernel, 2.6, bus, usb, device driver, mass storage, scsi, 
// urb, bulk, control, host, pipe, command,  ��־�� 
// ---------------------------------------------------------------------------------------------------------------------- 
// Ŀ¼ 
// ����  2 
// С�ǹ���  3 
// MAKEFILE���� MAKE LOVE 4 
// ��̬��ģ����� 6 
// �뵽���������ھ�Ҫ���� 9 
// δ����ʼȴ�ƽ��� 11 
// ����һȺ�˵Ĺµ� 12 
// ����,�豸,������(��) 13 
// ����,�豸,������(��) 15 
// ����˭����? 16 
// ��Э������,��Э����ȥ(��) 19 
// ��Э������,��Э����ȥ(��) 20 
// ��Э������,��Э����ȥ(��) 23 
// �ο�ʼ�ĵط� 24 
// �豸������ 27 
// �������߷�һ��֮�� 32 
// ��������,���컹��Զ��?(һ) 36 
// ��������,���컹��Զ��?(��) 41 
// ��������,���컹��Զ��?(��) 45 
// ��������,���컹��Զ��(��) 47 
// ��������,���컹��Զ��?(��) 52 
// ͨ������Ĺܵ� 57 
// ��˵�е� URB 63 
// ����  69 
// ��һ�����ܽӴ�(һ) 71 
// ��һ�����ܽӴ�(��) 76   2
// ��һ�����ܽӴ�(��) 80 
// ��һ�����ܽӴ�(��) 82 
// �����ƴ�����е��� 85 
// ��ճ����� SCSI 88 
// ˭�����̬�Ľṹ�� 92 
// SCSI���ݽṹ-������������� 102 
// �˰����Ĵ�˵(һ) 108 
// �˰����Ĵ�˵(��) 109 
// �˰����Ĵ�˵(��) 114 
// �˰����Ĵ�˵(��) 117 
// �˰����Ĵ�˵(��) 123 
// �˰����Ĵ�˵(��) 128 
// �˰����Ĵ�˵(��) 131 
// �˰����Ĵ�˵(��) 135 
// �˰����Ĵ�˵(THE END) 138 
// SCSI ����֮�������� 139 
// �������ص� BULK����(һ) 144 
// �������ص� BULK����(��) 150 
// �������ص� BULK����(��) 154 
// �������ص� BULK����(��) 158 
// �������ص� BULK����(��) 163 
// �������ص� BULK����(��) 166 
// ���Ÿо���(һ) 171 
// ���Ÿо���(��) 173 
// ��������ƻ��,����ŵ����,����Ħ������,�������ᰮ����! 179 
// �ж��ٰ����Ժ���?(һ) 182 
// �ж��ٰ����Ժ���?(��) 188 
// �������������� 193 
// ��ʵ���ϱ���·,�ߵ��˶���,Ҳ��û��· 198 
//  
// ���� 
// Ҳ�����ڸ������������ҹ���Ļ�ϰ��,����֮��Ҳ���Ǻ���Ҳ��Ը��˯.��������֮��,��
// ʼ���㲥������֮���ı�������ҹ.�����Ŀ�Ǵ� 23��ֱ���ڶ����賿һ��,�ҳ���������
// �˲Ż�˯��.�����Ǳ��������Ϻ�,������˵,����������ô����,�����ѹ��������ô��,ÿ
// ��ֻ���������Ŀ�в��ܹ�Ѱ�ҵ�һ˿��ů.�Ҳ�ϲ�����ڴ�����,����ϲ��һ����һ����
// ��������,������Ѫ�����ľ���,д�����ְ�,���ŵ粨����˷�������,����Ҳ����������
// ¼�Լ��������. 
//   
// �������뵽����дһЩ��Linux��ص�����.��ʵ���Ҳ���ϲ��Linux,ѧϰLinux��ȫ��һ
// ������,������Ҫ��,��������,���ò�ȥѧϰ,��ѧϰLinux�Ĺ�����Ψһ���Ҿ��û���Щ��
// Ȥ���ǵ����������ʱ�����ȥ������ȥ���ϲ�,�ܶ���д�˺ܶ��ĵ�������������Щ����
// �ǲο�ѧϰ,�������������ڹ��������˺ܶ���·.ͦ��л��Щ�����Լ�֪ʶ����.�������  3
// ��Ҳ���˵㶬��,������Щ���������ϵ�����Ҳ�Ƚ���,���������Ҳ���Ҳ���Լ���һҹ��
// �ջ�д����,�����Ժ�Ҳ�ܸ������ṩһЩ����,����Ҳ��,����Linux����������������,��
// ����Ѹ��������,����һ���˵���ůת�Ƶ���һ���˵����š�. 
//  
// ��Ҫд���� Linux �豸����������ص�,��Ҫ�������� Linux���� U ����ص��ǲ��ִ���.
// ��ȥҲû�п���,���ǽ���4�µ׵�ĳһ��,һ��żȻ��ԭ��,��һʱ�嶯�Ϳ���һ��.���Ǽ�
// ��ͬѧ���˴󸽽����齫,��ҹ����,��Ϊ���Ǽ�����ס��λ�ö����ͦԶ��,���Ի�ȥ��
// �ô�,���Ǿ�������ȥȨ��ǿ�������,���Ͼ�˯�ǵ���.��Ȩ���ϴԡ����,�ͼ���ͬѧϴ
// ԡ����,����ȥ��Ħ��,���Һ���һ�����������˷�����,������,��λ���Ǽ��Ҵ��˵���,˵
// ���в�AƬ,�ܲ���,���Ǻܴ�,����������U�����,����ͦ����˵����2008�걱�����˻�
// ָ�� A Ƭ,������û����Ȥ,�⻹����,��Ȼ����Ȥ��,��������򿪵���,���� u ��,Ȼ��һ
// ���Ҿ�ɵ��,��Ϊ�ҵĵ��Ը����Ͳ���ʶ��U��,�����ҵĵ��ԱȽϾ�,װ����˫ϵͳ,һ����
// Win 98,���û�취,û�� U ������,��һ���� Linux,2.6���ں�,����Ӧ����֧�� U �̵�,
// ������ʵ�����ȴ����û�п���U��,/dev/Ŀ¼�������û����ôһ���̷�,������û�취
// ��,һ����ɥ,��ͬѧ���Ա���Ȼ��ʾ���˶� Linux �ܱ��ӵ�����. 
//  
// ����һ��,��ȥ��������,������Ӣ��,��ȴû�����鿴����,����;������,��ô�᲻��ʹ
// �� U ����,�ⲻ���ܰ�,һ�������Լ��� Linux �����һЩ����û��Ū���,�����Ҿ����ú�
// �������⵽�׳�����,�ǵõ�ʱ����һ��/var/log/messages �����־�ļ���ߺ����¼
// ��һЩ��Ϣ,�о�����һЩ������Ϣ,���ǿ���������������˵ʲô.ͬѧ��ʼȰ��,��������,
// �����ٿ���,�⻰�ҿɲ�Ը����,����˵Linux�ں�Դ�����ǹ�������,���˿���Դ����,��
// �������ԭ���˻������ⲻ�ܽ��?�޷Ǿ���һЩ C �������,�ô�����Ҳ������ѧ��̷��
// ǿ����Ǳ� C ������Ƶ�.���ҵ����Ǳ���κ�ϰ����ʦ�����϶�����������,��˵�ǲο�
// ���Ǳ�ϰ�������,�ɾ���д���벻��,�����뻹��û�����,�﷨ʲô�Ļ����ϻ��Ǻ���
// ����,ʲô�жϽṹѭ���ṹ,���� goto���,���Ǽǵõ�. 
//  
// �����ҾͿ�ʼ����,����ν�����ж�Զ,�����߶�Զ.��ǰ��ֻ���� CS ���ɽ���ʱ���ܹ���
// ������˯,���Ǹ�����,Ϊ�˸�����ͬѧ,Linux��Ҳ�ܿ� AƬ,Linux ������������ʺ���
// �����,����Ǵ�һ�㿴��������,���ڰ� drivers/usb/storage/Ŀ¼����һ�����еĴ���
// ������һ��.��Ȼû�п���̫��ϸ,���Ǻ���Ȼ������ԭ��������,����Ҳ�ܿ���Խ��. 
//   
// ���Դ˿�,��������һ��˼·,�����������Ķ��������ּ�¼����.Ҳ��Ϊ�˼����Ǹ���Ѱ
// ����ҹ���.�����ҹ������ƪ�������,��Ϊ����һ�����еĴ����������͵�ռ������
// ҳ��,�����������Ҳ���ռ���Ҳ���ʱ��,Ȼ��,����,ÿ���б�������ҹ�����,����,Ҳ��
// ���Ұ���˼Ͷ�뵽д������µ�ʱ��,�ܹ�����Щѹ����Щ�������ֹ¶����������Լ�����
// ������ľ�������ʱ����Щ��.  
//  
// С�ǹ��� 
// ���������ʹ�õ���2.6.10���ں˴���.Linux�ں˴���Ŀ¼��, ����ȥ�豸���������йصĴ�
// �붼��drivers/Ŀ¼����,�����Ŀ¼�������� ls ������Կ����ܶ���Ŀ¼.   4
localhost:/usr/src/linux-2.6.10/drivers # ls 
Kconfig   atm        cdrom    eisa      ide       macintosh  message  net       parpo
rt  s390    tc         w1 
Makefile  base       char     fc4       ieee1394  mca        misc     nubus     pci      
sbus    telephony  zorro 
acorn     block      cpufreq  firmware  input     md         mmc      oprofile  pcmci
a   scsi    usb 
acpi      bluetooth  dio      i2c       isdn      media      mtd      parisc    pnp      se
rial  video 
//����usbĿ¼���������� usb �豸������,��usb Ŀ¼�����������Լ�����Ŀ¼,��ȥ��һ��, 
localhost:/usr/src/linux-2.6.10/drivers # cd usb/ 
locahost:/usr/src/linux-2.6.10/drivers/usb # ls 
Kconfig  Makefile  README  atm  class   core  gadget  host  image  input  media
//  misc  net  serial  storage  usb-skeleton.c 
//ע�⵽ÿһ��Ŀ¼���涼��һ��Kconfig �ļ���һ��Makefile,�����Ҫ.�Ժ���н���. 
//�����ǵĹ�����ʵ��Χ����drivers/usb/storage���Ŀ¼��չ����.ʵ��������ߵĴ�������
//������չʾ�������ճ�Ƶ���Ӵ���U ������ι�����,����α�����������.�������Ŀ¼���
//�Ķ���������������������Դ,�������Ǻ��������������ǧ˿���ƵĹϸ�.���Լ���������һ
//��, 
localhost:/usr/src/linux-2.6.10/drivers/usb # cd storage/ 
localhost:/usr/src/linux-2.6.10/drivers/usb/storage # ls 
Kconfig    debug.c  freecom.c       isd200.c    protocol.c  sddr09.c  shuttle_usbat
.c  unusual_devs.h 
Makefile   debug.h  freecom.h       isd200.h    protocol.h  sddr09.h  shuttle_usba
t.h  usb.c 
datafab.c  dpcm.c   initializers.c  jumpshot.c  scsiglue.c  sddr55.c  transport.c    
  usb.h 
datafab.h  dpcm.h   initializers.h  jumpshot.h  scsiglue.h  sddr55.h  transport.h 
//զһ��,��ʵ����һ��,��`wc -l *`�������ͳ��һ��,12076��,����... 
//����,Ҳ��,���������ǳ����˵�����. 
//���濴��һ�� Makefile �� Kconfig֮��,�������Ժ������. 
//Makefile ���� Make Love 
//������,����Ҫ����. 
//��ǰ�ڸ���,��������,û��ѧ���κζ���,ÿ������ӿ�,����,����Ϸ,˯��.��ҵ��ʱ��,��ߵ�
//�˶��еĶ���,�����ĳ���,�ҹ����İ�,ȥ�������ȥ�����,ȥ IBM ��ȥ IBM.���Լ�ȴһ����
//��,û���κμ���,ֱ����ʱ��ŷ���������Ƿ�˺ܶ�ծ,��֪����,�αص���.���˵���,�һ���һ  5
//�Ÿ�������ƾ,������������ƾ,����� Intel.Ȼ��,�����Ժ�,���Ƿ��ֵ�����У�ڼ�û�кúö�
//����ʵ������Ƿծ,����ûѧ,�����Ժ���Ҫѧ,��ȷ�ǳ���Ҫ����,�����Ӳ�����. 
//��ҵ��ʱ��,�˼Ҹ���˵Makefile����ȫ��֪,����һ˵Make Love�Ҿ�������.����������Ȼ
//���ö���. 
//������,Linux�ں���ÿһ��Ŀ¼�±߶���һ��Makefile,Makefile��Kconfig����һ�����е�
//��ͼ,��ͼ��������ȥ��ʶһ������,��Makefile��Kconfig������������˽����Ŀ¼�����
//�ṹ.drivers/usb/storage/Ŀ¼�±ߵ� Makefile ��������: 
# 
# Makefile for the USB Mass Storage device drivers. 
# 
# 15 Aug 2000, Christoph Hellwig <hch@infradead.org> 
# Rewritten to use lists instead of if-statements. 
# 
EXTRA_CFLAGS    := -Idrivers/scsi 
obj-$(CONFIG_USB_STORAGE)       += usb-storage.o 
usb-storage-obj-$(CONFIG_USB_STORAGE_DEBUG)     += debug.o 
usb-storage-obj-$(CONFIG_USB_STORAGE_HP8200e)   += shuttle_usbat.o 
usb-storage-obj-$(CONFIG_USB_STORAGE_SDDR09)    += sddr09.o 
usb-storage-obj-$(CONFIG_USB_STORAGE_SDDR55)    += sddr55.o 
usb-storage-obj-$(CONFIG_USB_STORAGE_FREECOM)   += freecom.o 
usb-storage-obj-$(CONFIG_USB_STORAGE_DPCM)      += dpcm.o 
usb-storage-obj-$(CONFIG_USB_STORAGE_ISD200)    += isd200.o 
usb-storage-obj-$(CONFIG_USB_STORAGE_DATAFAB)   += datafab.o 
usb-storage-obj-$(CONFIG_USB_STORAGE_JUMPSHOT)  += jumpshot.o 
usb-storage-objs :=     scsiglue.o protocol.o transport.o usb.o \ 
                        initializers.o $(usb-storage-obj-y) 
//����Kconfig �ļ�,�ڹ��µ��������,�˿����Ҳ���,Kconfig �ļ��Ƚϳ�,�Ͳ���������.��
//��ͨ����Kconfig�ļ�,���ǿ���֪��,����CONFIG_USB_STORAGE�������ѡ����������
//����Ҫ������,���ѡ�����Ƕ����Բ������.����,����
CONFIG_USB_STORAGE_DATAFAB,Kconfig�ļ�������ôһ��, 
config USB_STORAGE_DATAFAB 
        bool "Datafab Compact Flash Reader support (EXPERIMENTAL)" 
        depends on USB_STORAGE && EXPERIMENTAL 
        help 
          Support for certain Datafab CompactFlash readers. 
//          Datafab has a web page at <http://www.datafabusa.com/>. 
//��Ȼ,���ѡ�������û�й�ϵ,��������ר�����Datafab��˾�Ĳ�Ʒ��,���CompactFlash 
//reader��һ��flash�豸,������Ȼ����U��,��Ϊdrivers/usb/storage���Ŀ¼��ߵĴ���
//�����һ���豸��,����ĳһ���ض����豸,��һ���豸����usb mass storage�豸,��������
//�豸,��ר�ŵ��ĵ����н���,����Ӧ��spec,���������豸��ͨ�Ż��������ϵ������ϵȷ����  6
//�淶,U��ֻ�����е�һ��,�����豸ʹ�õ�ͨ��Э�鱻��ΪBulk-Only TransportЭ��.�ٱ���,
//����CONFIG_USB_STORAGE_SDDR55���ѡ��,Kconfig�ļ���Ҳ�ж�Ӧ��һ��, 
config USB_STORAGE_SDDR55 
        bool "SanDisk SDDR-55 SmartMedia support (EXPERIMENTAL)" 
        depends on USB_STORAGE && EXPERIMENTAL 
        help 
          Say Y here to include additional code to support the Sandisk SDDR-55 
          SmartMedia reader in the USB Mass Storage driver. 
//����Ȼ���� SanDisk�Ĳ�Ʒ,��������� SM ����,��Ҳ���� U��,��������Ҳ����ȥ�����.��
//ʵ��,������ȷ��,ֻ��CONFIG_USB_STORAGE���ѡ���������������ĵ�,��������Ӧ��
//ģ���usb-storage,Makefile �����һ��Ҳ˵��, 
usb-storage-objs :=     scsiglue.o protocol.o transport.o usb.o \ 
                        initializers.o $(usb-storage-obj-y) 
// �����ζ������ֻ��Ҫ��ע���ļ�����
// scsiglue.c,protocol.c,transport.c,usb.c,initializers.c �Լ�����ͬ����.hͷ�ļ�.�ٴ�ʹ��
// wc -l����ͳ��һ���⼸���ļ�,�����ܳ���ֻ�� 3701��,����������� 12000�����������,
// ��ʱ���ľͱ���. 
// ������Ҫ�ر�ע�����,CONFIG_USB_STORAGE_DEBUG �������ѡ��,���������Ǳ����,
// ����������Ҫ�Լ��޸Ļ��ߵ���usb-storage�Ĵ���,��ô�����ѡ���Ǻ��б�Ҫ��,��Ϊ
// ���Ḻ���ӡһЩ������Ϣ,�Ժ���Դ���������ǻῴ����������. 
// ��̬��ģ����� 
// ��һ�ָж�,����������,��һ�ֻ���,��ģ�����,ʮ�¸���һ������,�� Linux ������ģ�����.
// ��Ȼ,����ģ����Ƹ���Щ Linux �ķ������Ǵ����˷���,��Ϊģ�������ζ�����ǿ��԰��Ӵ�
// �� Linux �ں˻���Ϊ�������С��ģ��,���ڱ�д�豸����������ǰ�һ���˵,�Ӵ��Ժ���
// �ǿ��Ա�д�豸��������ȴ����Ҫ����������ں�,���� reboot ����,��ֻ��һ��ģ��,������
// Ҫ����ʱ��,����԰������뻳��(insmod),���㲻����Ҫ����ʱ��,����԰���һ���߿�,����,
// ����Զ�������:"����,����!"(rmmod).�����ܳ�Ϊ�������,ֻ��������·�. 
// Ҳ������ʵ�����ﲻ������,������ Linux ������������,ȷʵ���������,time and time 
// again,�����Լ�,ģ���Ƿ������ʵ�����еļ�Ůһ����?Linux �ں����ο�,������Ҫ���ģ��
// ��ʱ��,���Ͱ��˼����뻳��,��������Ҫ�˼ҵ�ʱ��,�Ͱѱ����߿�,����,ģ�������ܹ�����˳
// ��,���� Linux �ں˻�һ�δ�������,����ÿ��Linux �ں��ٴ���Ҫ����ʱ��,���ں��ٴ�ִ��
// insmod ��ʱ��,ģ����Ȼ�ᾡ�Լ�������ȥȡ���ں�,���Ƿ�̫�ɱ���Щ!�ǵÿ�������˵��,��
// ��Linux�ں˴��벻��,�ѵ��Ƕ���Linux�ں˴��뱳�����ѧ!�ѵ�����Ǵ�˵�еĲ���Linux
// ���뱳�����ѧ!����! 
// �׿���������ѧ��.�����Ǵ�һ��ΰ�������ȥ��ʶģ��.����Ǵ�˵�е�"Hello World!",��
// ���λð���������ǿ�����������,ÿһ������������ǰ,����ζ�����ǿ�ʼ�Ӵ�һ���µļ���
// ��������,����,��˿�,��ʼ����һ���µĹ���. 
//   �뿴������δ���,������ Linux �µ�һ����򵥵�ģ��.���㰲װ���ģ���ʱ��,��������
// ���е�����������,"Hello,world!",ǧ����ȷ,��û��˵"Honey,I love you!",��Ȼ,��������  7
// ô˵,�����Ҫ������ô˵.��������ж�������ģ��,��������������,��������,���ܾ���,����
// û�б�Թ,��ֻ�ǵ�����˵,"Goodbye,cruel world!"(�ټ�,�п������!) 
// ++++++++++++++++++hello.c++++++++++++++++++++ 
      1 //#include <linux/init.h>  // Needed for the macros // 
      2 //#include <linux/module.h> // Needed for all modules // 
      3 //MODULE_LICENSE("Dual BSD/GPL"); 
      4 //MODULE_AUTHOR("fudan_abc"); 
      5 
      6 static int __init hello_init(void) 
      7 { 
      8         printk(KERN_ALERT "Hello, world!\n"); 
      9         return 0; 
     10 } 
     11 
     12 static void __exit hello_exit(void) 
     13 { 
     14         printk(KERN_ALERT "Goodbye, cruel world\n"); 
     15 } 
     16 
     17 //module_init(hello_init); 
     18 //module_exit(hello_exit); 
//++++++++++++++++++++++++++++++++++++++++++++++++ 
//  ����Ҫʹ��module_init()�� module_exit(),����Գ�����Ϊ����,����ʵ����������һЩ
//��(macro),��������Բ���ȥ֪�����Ǳ���Ĺ���,ֻ��Ҫ֪��,��Linux Kernel 2.6��������,
//��д���κ�һ��ģ�鶼��Ҫʹ����������ʼ�����˳�,����˵ע���Լ�������ע��.������
//module_init()Ϊһ��ģ��ע����֮��,����ʹ�� insmod �������ȥ��װ��ʱ
//��,module_init()ע��ĺ������ᱻִ��,�������� rmmod �������ȥж��һ��ģ���ʱ
//��,module_exit()ע��ĺ������ᱻִ��.module_init()����Ϊ��������ĳ�ʼ�����
//(driver initialization entry point). 
//  ��ô����ʾ���ϴ����������?û��,����Ҫһ�� Makefile. 
//+++++++++++++++++++++Makefile++++++++++++++++++++++++
//+++ 
//      1 # To build modules outside of the kernel tree, we run "make" 
//      2 # in the kernel source tree; the Makefile these then includes this 
//      3 # Makefile once again. 
//      4 # This conditional selects whether we are being included from the 
//      5 # kernel Makefile or not. 
//      6 ifeq ($(KERNELRELEASE),) 
//      7 
//      8     # Assume the source tree is where the running kernel was built 
//      9     # You should set KERNELDIR in the environment if it's elsewhere 
//     10     KERNELDIR ?= /lib/modules/$(shell uname -r)/build 
//     11     # The current directory is passed to sub-makes as argument 
//     12     PWD := $(shell pwd)   8
//     13 
     14 modules: 
     15         $(MAKE) -C $(KERNELDIR) M=$(PWD) modules 
     16 
     17 modules_install: 
     18         $(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install 
     19 
     20 clean: 
     21         rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions 
     22 
     23 .PHONY: modules modules_install clean 
     24 
     25 else 
     26     # called from kernel build system: just declare what our modules are 
     27     obj-m := hello.o 
     28 endif 
// ++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++ 
//  ��lwn�Ͽ����ҵ��������,����԰����������ļ��������ĳ��Ŀ¼��,Ȼ��ִ��make,Ҳ��
// �㲻һ���ܳɹ�,��ΪLK 2.6Ҫ�������ģ��֮ǰ,���������ں�Դ����Ŀ¼��ִ��make,����
// ֮,����������ù��ں�,ִ�й� make,Ȼ����� make���Լ���ģ��.ԭ���ҾͲ�ϸ˵��,�㰴
// ����Ҫ�����ôȥ��������.���ں˶���Ŀ¼make��֮��,��Ϳ������㵱ǰ����Makefile��
// Ŀ¼��ִ��make��.Ok,make֮�����Ӧ�ÿ���һ������hello.ko���ļ�������,��ϲ��,��
// �����㽫Ҫ���Ե�ģ��. 
//   ִ������, 
//   #insmod hello.ko 
//   ͬʱ����һ������,������ tail -f /var/log/messages�쿴��־�ļ�,��ῴ�� 
//   Hello world����ӡ�˳���. 
//   ��ִ������, 
//   #rmmod hello.ko 
//   ��ʱ,����һ������ῴ�� Goodbye,cruel world!����ӡ�˳���. 
//   ������,�Ҹù�ϲ��,��Ϊ���Ѿ��ܹ���д Linux�ں�ģ����.���ָо�������,������?�����
// ��Ц�ػʺ��������Ĳ�����������ѷ��ɧ,�����Գ�Цһ���콾�ɼ�˼��ֻʶ�乭������. ��
// ��,Twins ���(s)��������,ֻҪ��ϲ��,����ʲô������. 
//   �պ����ǻῴ��,2.6�ں���,ÿ��ģ�鶼���� module_init ��ʼ,�� module_exit ����.���
// ����˵û�б�Ҫ֪������Ϊʲô,��ס�Ϳ�����,����ÿһ���� Linux��һ�㳣ʶ���˶���֪��
// ��һ���,�Դ��������˵,������� 1+1 Ϊʲô����2 һ��,����������֮����̵���ֱ��,��
// ��Ҫ֤��,���һ��Ҫ֤������֮��ֱ�����,������һ���ͷ��B��,��һ������A�����,���
// ���ֹ��ߵ���ֱ��,�ǵ�,����֪��,�㻹�ܲ�֪����?   9
// �뵽���������ھ�Ҫ���� 
// ��Ȼ֪������ô��дһ��ģ��,��ô��д�豸����������ȻҲ�Ͳ�����.������,ÿһ����дģ��
// ���˶��������д�豸����������.���Լ��в��в�ȷ���Ļ�,����ȥ��һ�¸���,��׼˵:"(����
// ��),�ҿ���." 
// ���,��û˵�ٻ�.д��������ʲô����,����ȫ���Ժ����ŵ�˵,���Ѿ�����дDevice Driver��.
// ��,û��,Ʈ��,����ô����. 
// ǰ��˵��ÿһ��ģ�鶼���� module_init ��ʼ,�� module_exit ����,��ô���Ǿ�����һ�� U
// �̵����������ģ��.��ãã�˺���,���Ǻ������ҵ�����ļ�:drivers/usb/storage/usb.c,
// ������ļ����ֲ��ѷ����������: 
// //***************************************************************
// ******* 
//    1056//Initialization and registration 
//    1057  **********************************************************
// ************// 
   1058 
   1059 static int __init usb_stor_init(void) 
   1060 { 
   1061         int retval; 
   1062         printk(KERN_INFO "Initializing USB Mass Storage driver...\n"); 
   1063 
   1064         // register the driver, return usb_register return code if error // 
   1065         retval = usb_register(&usb_storage_driver); 
   1066         if (retval == 0) 
   1067                 printk(KERN_INFO "USB Mass Storage support registered.\n"); 
   1068 
   1069         return retval; 
   1070 } 
   1071 
   1072 static void __exit usb_stor_exit(void) 
   1073 { 
   1074         US_DEBUGP("usb_stor_exit() called\n"); 
   1075 
   1076         // Deregister the driver 
   1077        //This will cause disconnect() to be called for each 
   1078        //attached unit 
   1079          // 
   1080         US_DEBUGP("-- calling usb_deregister()\n"); 
   1081         usb_deregister(&usb_storage_driver) ; 
   1082 } 
   1083   10
   1084 //module_init(usb_stor_init); 
   1085 //module_exit(usb_stor_exit); 
//  ��ʵ,module_init/module_exit ֻ��һ����,ͨ��дģ�����Ϊ�������Լ��ĸ���,�����
//���ĳ�ʼ��������ע�����������������,�������� module_init(usb_stor_init)�Լ�
//module_exit(usb_stor_exit)ʵ���Ͼ��Ǹ����������,�����ĺ�����usb_stor_init ��
//usb_stor_exit.���ּ����� Linux �ں˴������ż�����.������Ҳ�Ͳ��ش�С����,��Ҫ����
//��Ҫ����,����ȥ��.�������浱Ȼ�ʹ� usb_stor_init ��ʽ��ʼ���ǵ�̽��֮��. 
//���������ܾ��� 
//������֮ǰ,�����������˼������ôһ������,����Ҫ��ע�Ľ����� drivers/usb/storage/Ŀ
//¼��������ص�3000���д�����?�������������ļ�������һ������ͬ��U����Linux���湤
//��������? ��һ��ʼ���������Ŀ¼����һ��С�ǵĻ�,Ҳ��,������¹��Ư��,���ܹ����˵�
//������,�ܹ���ů�˵��ķ�.��������ľ����������������,һ��һ����? 
//�ܲ���,����Զ����������.���������ܾ���,��Ϊ U ��,����Ҫ��usb core�򽻵�,��Ҫ��
//scsi core�򽻵�,��Ҫ���ڴ����Ԫ�򽻵�,�����ں�������������ģ��򽻵�.���������
//�ܴ�,Զ����������Ĵ�. 
//ʲô��usb core?������ʵ��һЩ���ĵĹ���,Ϊ����豸���������ṩ����,���������ڴ�,��
//��ʵ��һЩ���е��豸������Ҫ�Ĺ����ĺ���,��ʵ��,�� usb ��������,һ����ͨ���豸Ҫ����
//�Ĺ���,����Ҫ���豸��������,����Ҫ��һ�������������Ķ���,����������� host controller,
//�������������������һ�������һ������,���� root hub,hub����Ӧ�ò���İ��,�ڴ�ѧ��,
//�е���������������,����������һ�����ϴ�ѧ��������ÿ��һ̨����,�������ڲ���,��������
//��ʹ��hub,�ö���˹���һ������,������̫���ϵ� hub,�� usb ��������ͬ����hub,��ʵԭ
//����һ����,�κ�֧�� usb �ĵ��Բ���˵ֻ������ֻ��һ��ʱ��ʹ��һ��usb�豸,���������
//��u��,��ͬ�������Բ���usb����,�������ٲ�һ��usb���,��Ϊ��ᷢ����ĵ����ﲢ��ֻ
//��һ��usb�ӿ�.��Щ��ʵ���Ͼ�����ν��hub ��.����ʵ�о�������һ�� usb ��������һ��
//hub����һ��,רҵһ��˵�м���,�����hubҲ������root hub,����֮,��usb��������
//��һ���hub����ϵͳ���������hub,������hub�������ӵ�������,Ȼ����������ȥ,���
//����豸,��ȻҲ���Բ��ñ��hub,��usb�豸ֱ�ӽӵ� root hub ��.hub �����õ�����֪��
//��,��ô usb host controller�����Ǹ�ʲô�õ���?controller,������,����˼��,���ڿ���,��
//��ʲô,�������е�usb�豸��ͨ��.ͨ���������cpu������ֱ�Ӻ�usb�豸�򽻵�,���ǺͿ�
//�����򽻵�,��Ҫ���豸��ʲô,������߿�����,������ֱ�Ӱ�ָ����豸,Ȼ���������ȥ��
//�����������,����ȥָ���豸ִ������,��cpu �Ͳ��ù�ʣ�µ�����,�����Ǹø������ȥ,
//����������ȥ���ʣ�µ�����,�����������֪ͨ cpu.������ cpuȥ����ÿһ���豸��ÿһ��
//����,���ǲ���ʵ��,�Ǿͺñ���һ��ѧԺ��Ժ��ȥ��������ÿһ���������Ͽ�,ȥ�������ǵĳ�
//��,ֻ��˵,����ʵ.�������Ǿͱ��ֳ��˼���ϵ,ͨ��Ժ����ʲôָʾֱ�Ӹ���ϵ�쵼˵�Ϳ�����,
//�����Ҫ������ϵ����˵����,����ʹ���������˶��ټ�����������,Ҳ���Ը������˸���һ��
//�绰,����绰����æ���Լ�������ȥ��,����ȥ��������Ů˶ʿ�绨ѩ��.������ϵ���ξͻ�ȥ
//�����������ȥִ�о��������,����֮�����Ǿͻ���Ժ���㱨. 
//����,Linux�ں˿�������,ר��д��һЩ����,��������Իusb core.ʱ�����ڷ�չ,���������
//����������������,������������͵�������־��������ħ�����.ͬ��,���ڵ�Linux�ں�,���
//�����������������в�θ�,Զ�����������������,��ʱ�� drivers/usb/���Ŀ¼�±߷�
//�˺ܶ�ܶ��ļ�,usb core�����������豸����������Ĵ��붼����������,����,����������ǧ
//�ı��,�ܰ���������˷�����.������drivers/usb/Ŀ¼���������һ�� coreĿ¼,��ר�ŷ�  11
//һЩ���ĵĴ���,�����ʼ������usbϵͳ,��ʼ�� root hub,��ʼ��host controller�Ĵ���,
//�ٺ��������� host controller��صĴ���Ҳ��������һ��Ŀ¼,�� host Ŀ¼,������Ϊ usb 
//host controller����ʱ���ķ�չ,Ҳ��ʼ���˺ü���,������տ�ʼ����ֻ��һ��,������,���
//���ǰ�һЩhost controller �����Ĵ�����Ȼ���� coreĿ¼��,��һЩ�� host controller ����
//�Ĵ������Ƶ� host Ŀ¼�����ø������ host controller����ȥά��,������host controller
//������,�ֱ����EHCI,UHCI,OHCI,��������,��������������,usb core,usb host,usb 
//device,��ԭ����һ����,ȴ���������ķֳ�����������...��ȷ,��ʵ���Ǻ�����,Ȼ��,����֪��
//��Ϭ�ķ���,���²��ܹ���Ϧ���?û��,usbͨ�ŵ�������usbЭ��. usb Э�齫������usb
//�豸��usb������������ѭ����Ϸ����.���ֹ���Ҳ����Ȼ���������˴�����.����,������Ҫ��
//��Ĳ������� drivers/usb/storage/Ŀ¼����Ķ���,����ȥ�˽������������,��Ȼ,ֻ��Ҫ
//�˽�һ���. 
//δ����ʼȴ�ƽ��� 
//���ǻص��Ǹ���ʼ��������,usb_stor_init,�������Ĵ���ÿһ���˵����ж���һ��Ī�����˷�,
//��Ϊ��̫����,����ô����,�������� printk �������,����һ�������ĵ���,usb_register. 
//printk ������˵,ÿһ����־���궼��֪��,����û���� printkҲ�ü��� printf ��,����Ļ�,��
//��������,��Ե���̷��ǿ�����?��̷��ǿ���Ĵ���������ѧ������
//#include<stdio.h>->main()->printf()����ӡhello,world!�Ӷ���ȫ����չʾ�����Ƕ�C
//����.�� stdio.h����һ��C ��,printf��һ������,���Ժ�����,�����ں���û�б�׼C��,����
//���������Լ�׼����һЩ����,ר�������ں˴�����,���Ծͳ�����һ�� printk,printk ��"k"��
//�� kernel,�ں�.��������ֻҪ�������� printf ���ֵܼ���,�������Ȥ,����ȥ�о�һ�� printk
//���ص�,����printf������Щ��ͬ,������˼����һ����.�������ǾͲ��ི��,��Ȼ������������
//�е�printk����U�̵Ĺ�����û��ʲô��,���޷��Ǵ���������ǿ���,����˵��ӡ���û���,
//������,��ӡ�������߿�,�ر��ǿ�����Ҫ���Գ����ʱ��,�ͻ������. 
//�������Ǹ�������,���ÿ�printk �Ļ�,�Ǿ�ֻ��һ������������,usb_register.��������Ǹ�
//���?�������������������usb core.����usb�豸����,��Ҫ���������������usb coreע
//��,�Ӷ���usb core֪������ôһ���豸.����������涨,һ�Է��޽��Ҫ����ز�������ȥ��
//����һ����,��������֪����������ι����,ֻ��Ҫ֪��ȥ��������ǼǼ���. 
//����,insmod ��ʱ��,usb_stor_init ��������ᱻ����,��ʼ�����������.�����豸�Ϳ�ʼ��
//����...��������rmmod��ʱ��,usb_stor_exit��������ᱻ����,���Ƿ���,�������Ҳ�ܶ�,
//�����ܿ�����,US_DEBUGҲ���Ǵ�ӡһЩ����,���,����ʵ����Ҳ���ǵ�����һ������
//usb_deregister(),����usb_register()��һ��,�����ע���Ĺ���,�Ӵ��豸�ʹ�usb core��
//��ʧ��.�������Ǿ��˵ķ���,��д�豸����������˵ļ�,����������ľ���ô������?... 
//��һ��,�������˲�����һ�ֻþ�,���˷ֲ�����´����￪ʼ,�ִ��������,һ�ж�̫������.
//�·�ʼ�ڽ�����ʱ��ʼ,������ȴ�ڿ�ʼ��ʱ������ѽ���. 
//�����? 
//���Ƿ񶨵�.�����Ѿ�����������,����Ҫ��������,��Ҫ�����뱳�����ѧ. 
//���������ڼ���֮ǰ,�����������ﵽ����ʲô��ѧ.����,����ΰ���Linux Kernel 2.6�е�ͳ
//һ���豸ģ��.   12
//���ǲ�����ȥ��ϸ���� 2.6�е��豸ģ��,���ǲ����豸ģ��������˵�Լ����豸������?����
//�����,д�������,��Ҫ֪��,ʲô���豸����?ʲô�����豸?�豸������֮�便����ʲô��ϵ?
//�豸���������������ϵ����?���������йش��������̵ĸ��Ƕ�Ҳ�ܻش��������.����
//��������,�豸�кܶ�����,����PCI�豸,���� ISA�豸,�ٱ���SCSI �豸,�ٱ������������
//USB�豸.Ϊ�豸������������,�������豸�����˼��������.��������˵�豸�Ǽ޸��˼����
//����,������˵�豸�Ǽ޸����豸��������.����Ȼ,�ڼ����������,���۷�������,������豸
//��������������. 
//Ψһ���ź���,������е��豸����������Ĺ�ϵȴ��������ֺ������Ĺ�ϵ����,һ��һ.Ȼ��
//�������ж���������������Ը��. 
//����һȺ�˵Ĺµ� 
//Linux�豸ģ������������Ҫ�ĸ����������,�豸,����.��bus,device,driver,��ʵ�����ں�
//��Ҳ��������ôһЩ���ݽṹ,������ struct bus_type,struct device,struct device_driver,
//��������Ҫ�����ݽṹ������һ���ط�,include/linux/device.h.����֪�������кܶ���,pci
//����,scsi����,usb ����,�������ǻῴ�� Linux �ں˴����г���
//pci_bus_type,scsi_bus_type,usb_bus_type,���Ƕ���struct bus_type���͵ı���.��
//struct bus_type�ṹ�������ǳ���Ҫ�ĳ�Ա���� struct kset drivers �� struct kset 
//devices.kset ����һ������ kobject���� Linux Kernel 2.6���豸ģ�͵Ļ���Ԫ��,���˴���
//��ȴ��Ը�ི,��Ϊ��ʱ����ȥ��ʶ����.���ǵ������л�������������˺���,��������˺�
//��������ֻ�ǲ������,ֻ�����������еĹ��Ͷ���.�����������ĵ�Ӱ��,����Ҳ��ֻ��һ����
//ͷ,������һ����ͷ����Ҳ����������.��������ֻ��Ҫ֪��,drivers �� devices �Ĵ���,��
//struct bus_type������������ϵ������,һ���� devices ������,һ����drivers ������,Ҳ��
//��˵,֪��һ����������Ӧ�����ݽṹ,�Ϳ����ҵ������������������豸����Щ,������Щ֧��
//�����豸����������. 
//��Ҫʵ����Щ,��Ҫ��ÿ�γ���һ���豸��Ҫ�����߻㱨,����˵ע��,ÿ�γ���һ������,ҲҪ��
//���߻㱨,����˵ע��.����ϵͳ��ʼ����ʱ��,��ɨ����������Щ�豸,��Ϊÿһ���豸������һ
//�� struct device�ı���,ÿһ����һ����������,��Ҫ׼��һ�� struct device_driver�ṹ��
//����.����Щ����ͳͳ������Ӧ������,device����devices����,driver����drivers����. ��
//��ͨ�����߾����ҵ�ÿһ���豸,ÿһ������. 
//Ȼ��,����������ֻ���豸ȴû�ж�Ӧ������,��ô�豸�޷�����.������,����ֻ������ȴû��
//�豸,����Ҳ�����κ�����.�����������˴�֮ǰ,˫������ͬ·����Ұ��,һ��Ʈ��Ʈ,һ��ҡ
//��ҡ,˭Ҳ��֪��δ��������,ֻ���������ķ���Ʈҡ.���������ϵ����ű���������ľ͹�����
//�����µ������.devices ��ʼ����,drivers ��ʼ����,��������������������,devices �Ǳ�
//��ȡů,drivers ��һ���,��������һ������ͬ��,��ֻ���ڵȴ������Լ����Ǹ���һ��. 
//���������,һֱ�������֪��,�����Ƿ��������ʵ��һ��,��Щ��ע���ǵȱ���,����Щ����ע
//�����˵ȵ�.   13
//����,�豸,������(��) 
//struct bus_type��Ϊ devices �� drivers ׼������������,������ device�Ľṹ��struct 
//device������������Ա,struct bus_type *bus ��struct device_driver *driver,ͬ��,����
//driver �Ľṹ�� struct device_driverͬ����������Ա,struct bus_type *bus�� struct 
//list_head devices,struct device�� struct device_driver�Ķ���� struct bus_typeһ��,
//�� include/linux/device.h ��.ƾһ�����˵�ֱ��,����֪��,struct device�е� bus��¼����
//����豸��������������,driver��¼��������豸�õ����ĸ�����,������,struct 
//device_driver�е�bus�����Ҳ���������������������,devices��¼�����������֧�ֵ�
//��Щ�豸,û��,��devices(����),������device(����),��Ϊһ�������������֧��һ������
//�豸,������һ���豸��ֻ��󶨸�һ����������. 
//����������֪��,���� bus,���� device,���� driver,��������ν�����ϵ����?����֮,������
//���ݽṹ�е�ָ������α���ֵ��?���Բ����ܷ�����������,һ��Ϊһ������������һ��
//struct bus_type�����ݽṹ֮��,����֪������devices�����drivers����������Щ����,
//��Щ����һ��������������е�,ֻ���Ǻ����������.�����嵽usb ϵͳ,�����������ľ���
//usb core.usb core�Ĵ����������� usb ϵͳ�ĳ�ʼ��,��������struct bus_type 
//usb_bus_type,Ȼ���ɨ�� usb ����,��������������Щusb�豸,����˵ root hub��������
//Щusb�豸,����˵����һ��usb����,��ô��Ϊ��׼��һ��struct device,��������ʵ�����,
//Ϊ���struct device��ֵ,������devices��������.�ֱ���root hub������һ����ͨ��hub,
//��ô����ҪΪ���hub ����׼��һ�� struct device����,���ü���ɨ�迴��� hub���Ƿ���
//���˱���豸,�еĻ������ظ�֮ǰ������,����һֱ������ȥ,ֱ���������ɨ��,���վͰ�
//usb_bus_type�е� devices���������������. 
//��ô drivers������?����Ͳ���bus����������,������ÿһ�� driver ����ȥ bus����Ǽ�,
//����˵����.���嵽usbϵͳ,ÿһ��usb�豸���������򶼻���һ�� struct usb_driver�ṹ
//��,���������,���� include/linux/usb.h 
//    485 // -------------------------------------------------------------------------- // 
//    486 
//    487 //* 
//    488//struct usb_driver - identifies USB driver to usbcore 
//    489//@owner: Pointer to the module owner of this driver; initialize 
//    490//     it using THIS_MODULE. 
//    491//@name: The driver name should be unique among USB drivers, 
//    492//     and should normally be the same as the module name. 
//    493//@probe: Called to see if the driver is willing to manage a particular 
//    494//     interface on a device.  If it is, probe returns zero and uses 
//    495//     dev_set_drvdata() to associate driver-specific data with the 
//    496//     interface.  It may also use usb_set_interface() to specify the 
//    497//     appropriate altsetting.  If unwilling to manage the interface, 
//    498//     return a negative errno value. 
//    499//@disconnect: Called when the interface is no longer accessible, usually 
//    500//     because its device has been (or is being) disconnected or the 
//    501//     driver module is being unloaded.   14
//    502//@ioctl: Used for drivers that want to talk to userspace through 
//    503//     the "usbfs" filesystem.  This lets devices provide ways to 
//    504//     expose information to user space regardless of where they 
//    505//     do (or don't) show up otherwise in the filesystem. 
//    506//@suspend: Called when the device is going to be suspended by the 
//system. 
//    507//@resume: Called when the device is being resumed by the system. 
//    508//@id_table: USB drivers use ID table to support hotplugging. 
//    509//     Export this with MODULE_DEVICE_TABLE(usb,...).  This must be set 
//    510//     or your driver's probe function will never get called. 
//    511//@driver: the driver model core driver structure. 
//    512//
//    513//USB drivers must provide a name, probe() and disconnect() methods, 
//    514//and an id_table.  Other driver fields are optional. 
//    515//
//    516//The id_table is used in hotplugging.  It holds a set of descriptors, 
//    517//and specialized data may be associated with each entry.  That table 
//    518//is used by both user and kernel mode hotplugging support. 
//    519//
//    520//The probe() and disconnect() methods are called in a context where 
//    521//they can sleep, but they should avoid abusing the privilege.  Most 
//    522//work to connect to a device should be done when the device is opened, 
//    523//and undone at the last close.  The disconnect code needs to address 
//    524//concurrency issues with respect to open() and close() methods, as 
//    525//well as forcing all pending I/O requests to complete (by unlinking 
//    526//them as necessary, and blocking until the unlinks complete). 
//    527  // 
    528 struct usb_driver { 
    529         struct module *owner; 
    530 
    531         const char *name; 
    532 
    533         int (*probe) (struct usb_interface *intf, 
    534                       const struct usb_device_id *id); 
    535 
    536         void (*disconnect) (struct usb_interface *intf); 
    537 
    538         int (*ioctl) (struct usb_interface *intf, unsigned int code, void *buf); 
    539 
    540         int (*suspend) (struct usb_interface *intf, u32 state); 
    541         int (*resume) (struct usb_interface *intf); 
    542 
    543         const struct usb_device_id *id_table; 
    544   15
    545         struct device_driver driver; 
    546 }; 
    547 #define to_usb_driver(d) container_of(d, struct usb_driver, driver) 
//   ���ƺܳ�һ��,ʵ����Ҳ����ע��Ϊ��.���˿�����ֻ��ע�⵽���е� struct device_driver 
// driver �����Ա,usb core Ϊÿһ���豸����׼����һ������,�������Լ������ struct 
// device_driver driver���뵽usb_bus_type�е�drivers ������ȥ.����������������Ǵ�
// ǰ������ usb_register.����֮��Ӧ��usb_deregister�����µ�������֮�෴�Ĺ���,�����
// �ṹ���drivers������ɾ��.����˵,usb core��ȷ����������,Ϊÿһ��usb�豸����������
// ����,����Ϊ���,��Ϊһ��ʵ�ʵ�usb�豸����,���ڳ�ʼ���׶���Ҫ��������ͺ���,�ܼ���,
// ֱ�ӵ���usb_register����.��ʵ��,û������������ȻӦ��Ϊ����ʲô��,��usb core��ô��
// ��.����ÿһ��дusb�豸��������Ӧ������,usb device driver������һ�����ڹ���,������
// ��,��usb core���ṩ��ĬĬ�����ֲ��ɻ�ȱ��֧��. 
// ����,�豸,������(��) 
// bus�ϵ����������¼��ÿһ��device��driver,��ôdevice��driver������֮�����������ϵ������
// ��?�˿�,�����׳�����һ������,����device���� driver? 
// �ܾúܾ���ǰ,���Ǽ���ȼ�յ�������,���е���device,ÿһ��Ҫ�õ�device�ڼ��������֮ǰ���Ѿ���
// ����,�������Ӧ���ڵ�λ����,Ȼ����������,Ȼ�����ϵͳ��ʼ��ʼ��,���߿�ʼɨ���豸,ÿ�ҵ�һ��
// �豸,��Ϊ������һ��struct device�ṹ,���ҹ��������е�devices��������,Ȼ��ÿһ����������ʼ
// ��ʼ��,��ʼע����struct device_driver�ṹ,Ȼ����ȥ���ߵ�devices������ȥѰ��(����),ȥѰ��ÿ
// һ����û�а�driver���豸,��struct device�е�struct device_driverָ����Ϊ�յ��豸,Ȼ������
// ȥ�۲������豸������,���Ƿ�������֧�ֵ��豸,�����,��ô����һ������device_bind_driver�ĺ���,
// Ȼ�����Ǿͽ�Ϊ���ؽ�֮��.���仰˵,��struct device�е�struct device_driver driverָ�����
// driver,��struct device_driver driver��struct device������������struct list_head devices����
// ����.������,bus,device,��driver,������֮�����˵�����е�����֮��,�͸���ϵ����.֪������֮һ,��
// ���ҵ���������.һ�پ���,һ�����. 
// �������������,����������ŵ�������,����ӣ�����ŵ�������,������һ���µ�����,���Ȳ��.device
// �����ڼ���������Ժ��ڲ�����߰γ��������.���,������˵������device��������driver��.��Ϊ��
// �п���.device�������κ�ʱ�̳���,��driverҲ�������κ�ʱ�̱�����,����,���ֵ��������,ÿ��һ��
// struct device����,���ͻ�ȥbus ��drivers������Ѱ���Լ�����һ��,��֮,ÿ��һ��һ��struct 
// device_driver����,����ȥbus��devices������Ѱ��������Щ�豸.����ҵ��˺��ʵ�,��ôok,��֮ǰ
// �������һ��,����device_bind_driver�󶨺�.����Ҳ���,û�й�ϵ,�ȴ���,�ȵ�꼻��ٿ�,�ȵ��羰��
// ͸,��������,������������һ�����������ȵ�,ֻ�ǻ�û����������. 
// ��,����,��ʵ��,����������ǹ�ϵ,����ÿһ���豸������ʼ���׶�����ɵ���Ҫʹ��֮һ.�����ǻ��ǻ�
// ����������,usb_register������������ǵ�����,���Ǵ��ݸ����Ĳ�����ʲô��? 
// ����ע�⵽,�Ǿ�����������ӵ�, 
   1064         // register the driver, return usb_register return code if error // 
   1065         retval = usb_register(&usb_storage_driver); 
�ǵ�,������һ������usb_storage_driver�ļһ�,����ʲô?ͬһ�ļ���,drivers/usb/storage/usb.c:   16
    232 struct usb_driver usb_storage_driver = { 
    233         .owner =        THIS_MODULE, 
    234         .name =         "usb-storage", 
    235         .probe =        storage_probe, 
    236         .disconnect =   storage_disconnect, 
    237         .id_table =     storage_usb_ids, 
    238 }; 
 
// ���Կ������ﶨ����һ��struct usb_driver�Ľṹ�����,usb_storage_driver,����usb_driver����
// �Ͻ��Ѿ�˵����,��ʱ��Ҫ˵�������еĳ�Աdriver,������Ҫ�����������⼸����Ա.����,.owner
// ��.name������ûɶ�ö�˵��,owner��������������ģ�������,ÿ��ģ�鶼��ô��,��ֵ����
// THIS_MODULE,��name�������ģ�������,usb core�ᴦ����,����������ģ�������������˵Ļ�,
// ʹ��lsmod�����ܿ���һ������usb-storage��ģ����.�ص�Ҫ��һ��,.probe��.disconnect�Լ����
// id_table. 
// ����˭����? 
// probe,disconnect,id_table,����������������Ҫ�ǳ�������� id_table,���Ǹ����õ���? 
// ����˵��,һ��deviceֻ�ܰ�һ��driver,��driver����ֻ��֧��һ���豸,����ܼ�,����
// ��������U��,��ô�ҿ���һ�𶼲���,������ֻ��Ҫ����һ��ģ��,usb-storage,û��˵������
// ���� U�̾͵ü����������������,���������� U�̱���͵�ʹ�ò�ͬ����������.Ҳ������Ϊ
// һ��ģ����Ա�����豸����,�Ż���ģ�������ôһ��˵��. 
// ok,��Ȼһ��driver����֧�ֶ��device,��ô������һ��device��ʱ��,���֪���ĸ�driver
// ��������Mr.Right��?�����id_table���ô�,��ÿһ��struct usb_driver׼��һ�ű�,���
// ע����driver֧����Щ�豸,���ܿ����˰�.���������豸�������ű����,��ôok,�󶨰�,��
// �����������ű����,��ô������˼,�����.����������ȥ. 
// ���� struct usb_driver�е� id_table, 
// const struct usb_device_id *id_table; 
// ʵ������һ��ָ��,һ�� struct usb_device_id �ṹ���ָ��,��Ȼ����ֵ�Ժ���Ǵ���һ����
// ������,���������ڶ��� struct usb_driver usb_storage_driver��������ֵ��
// ��,.id_table=storage_usb_ids,�Ǻ�,��������һ�� usb_device_id�⾿��������һ���ṹ
// ��. 
struct usb_device_id���� include/linux/mod_devicetable.h, 
     40 // 
     41//Device table entry for "new style" table-driven USB drivers. 
     42//User mode code can read these tables to choose which modules to load. 
     43//Declare the table as a MODULE_DEVICE_TABLE. 
     44//
     45//A probe() parameter will point to a matching entry from this table. 
     46//Use the driver_info field for each match to hold information tied   17
     47//to that match:  device quirks, etc. 
     48//
     49//Terminate the drivers table with an all-zeroes entry. 
     50//Use the flag values to control which fields are compared. 
     51  // 
     52 
     53 //
     54//struct usb_device_id - identifies USB devices for probing and hotplugging 
     55//@match_flags: Bit mask controlling of the other fields are used to match 
     56//     against new devices.  Any field except for driver_info may be used, 
     57//     although some only make sense in conjunction with other fields. 
     58//     This is usually set by a USB_DEVICE_*() macro, which sets all 
     59//     other fields in this structure except for driver_info. 
     60//@idVendor: USB vendor ID for a device; numbers are assigned 
     61//     by the USB forum to its members. 
     62//@idProduct: Vendor-assigned product ID. 
     63//@bcdDevice_lo: Low end of range of vendor-assigned product version 
numbers. 
     64//     This is also used to identify individual product versions, for 
     65//     a range consisting of a single device. 
     66//@bcdDevice_hi: High end of version number range.  The range of product 
     67//     versions is inclusive. 
     68//@bDeviceClass: Class of device; numbers are assigned 
     69//     by the USB forum.  Products may choose to implement classes, 
     70//     or be vendor-specific.  Device classes specify behavior of all 
     71//     the interfaces on a devices. 
     72//@bDeviceSubClass: Subclass of device; associated with bDeviceClass. 
     73//@bDeviceProtocol: Protocol of device; associated with bDeviceClass. 
     74//@bInterfaceClass: Class of interface; numbers are assigned 
     75//     by the USB forum.  Products may choose to implement classes, 
     76//     or be vendor-specific.  Interface classes specify behavior only 
     77//     of a given interface; other interfaces may support other classes. 
     78//@bInterfaceSubClass: Subclass of interface; associated with bInterfaceClass. 
     79//@bInterfaceProtocol: Protocol of interface; associated with bInterfaceClass. 
     80//@driver_info: Holds information used by the driver.  Usually it holds 
     81//     a pointer to a descriptor understood by the driver, or perhaps 
     82//     device flags. 
     83//
     84//In most cases, drivers will create a table of device IDs by using 
     85//USB_DEVICE(), or similar macros designed for that purpose. 
     86//They will then export it to userspace using MODULE_DEVICE_TABLE(), 
     87//and provide it to the USB core through their usb_driver structure. 
     88//
     89//See the usb_match_id() function for information about how matches are   18
     90//performed.  Briefly, you will normally use one of several macros to help 
     91//construct these entries.  Each entry you provide will either identify 
     92//one or more specific products, or will identify a class of products 
     93//which have agreed to behave the same.  You should put the more specific 
     94//matches towards the beginning of your table, so that driver_info can 
     95//record quirks of specific products. 
     96  // 
     97 struct usb_device_id { 
     98         // which fields to match against? // 
     99         __u16           match_flags; 
    100 
    101         // Used for product specific matches; range is inclusive // 
    102         __u16           idVendor; 
    103         __u16           idProduct; 
    104         __u16           bcdDevice_lo; 
    105         __u16           bcdDevice_hi; 
    106 
    107         // Used for device class matches // 
    108         __u8            bDeviceClass; 
    109         __u8            bDeviceSubClass; 
    110         __u8            bDeviceProtocol; 
    111 
    112         // Used for interface class matches // 
    113         __u8            bInterfaceClass; 
    114         __u8            bInterfaceSubClass; 
    115         __u8            bInterfaceProtocol; 
    116 
    117         // not matched against // 
    118         kernel_ulong_t  driver_info; 
    119 }; 
// ʵ��������ṹ���ÿһ��usb�豸��˵,���൱�����������֤,��¼������һЩ������Ϣ,ͨ�����ǵ���
// ��֤�ϻ��¼���ǵ�����,�Ա�,��������,���ڵ�ַ�ȵ�,��usb�豸��Ҳ������Ҫ��¼����Ϣ,����������
// ���usb�豸,����Vendor-����,Product-��Ʒ,�Լ�����һЩ�����Ʒ���,��Ʒ�����,��ѭ��Э��,��
// Щ������usb �Ĺ淶����ҵ���Ӧ�Ķ���.�����Ȳ�ϸ˵. 
// ��������֪��,һ��usb_driver�����������id��ȥ��ÿһ��usb�豸��ʵ��������бȽ�,������豸
// ��ʵ����������ű����ĳһ��id��ͬ,׼ȷ��˵,ֻ��������������Ǻ�,���ܹ���һ��usb device����
// ��usb driver ���а�,��Щ�������²�һ��Ҳ����.��������ÿ���˶���һ����,���ڲ�ͣѰ�����ñ˴�
// Ƕ��������Բ����һ����,��ʵȴ��,ÿ���˶ԡ�(PI)����ⲻ����ͬ,��Բ���ܷ��غ�,����ֻ��ʹ����֪
// ��.��֮����,ʧ֮����. 
// ��ôusb�豸��ʵ�������ʲôʱ����������?��,�ڽ���.probeָ��֮ǰ�б�Ҫ��̸һ̸��һ������
// �ṹ��,������struct usb_device.   19
// ��Э������,��Э����ȥ(��) 
// ��struct usb_driver��,.probe��.disconnect��ԭ������: 
// int (*probe) (struct usb_interface *intf,const struct usb_device_id *id); 
// void (*disconnect) (struct usb_interface *intf); 
// �����������еĲ���,struct usb_device_id�������˵��,�ղ��Ѿ����ܹ�,��ôstruct usb_interface
// �Ӻζ���?�����������ȴ�struct usb_device˵��. 
// ����֪��ÿһ��device��Ӧһ��struct device�ṹ�����,����device�����������ܵ�,�����Ƕ�����
// ��,�������ǿ�����"��"��ͳ��ȫ����,���Ƿֵ�ϸһ��,�������˺�Ů�˵�����,��ôdeviceҲһ��,����
// �и��ָ������豸,�����ֳ����˸���Ĵʻ�(���ݽṹ),�������usb �豸,�������������һ������
struct usb_device//�Ľṹ��.��������include/linux/usb.h, 
    294 // 
    295//struct usb_device - kernel s representation of a USB device 
    296//
    297//FIXME: Write the kerneldoc! 
    298//
    299//Usbcore drivers should not set usbdev->state directly.  Instead use 
    300//usb_set_device_state(). 
    301  // 
    302 struct usb_device { 
    303         int             devnum;         // Address on USB bus // 
    304         char            devpath [16];   // Use in messages: /port/port/... // 
    305         enum usb_device_state   state;  // configured, not attached, etc // 
    306         enum usb_device_speed   speed;  // high/full/low (or error) // 
    307 
    308         struct usb_tt   *tt;            // low/full speed dev, highspeed hub // 
    309         int             ttport;         // device port on that tt hub // 
    310 
    311         struct semaphore serialize; 
    312 
    313         unsigned int toggle[2];         // one bit for each endpoint ([0] = IN, [1] = 
OUT) // 
    314         int epmaxpacketin[16];          // INput endpoint specific maximums // 
    315         int epmaxpacketout[16];         // OUTput endpoint specific maximums 
// 
    316 
    317         struct usb_device *parent;      // our hub, unless we're the root // 
    318         struct usb_bus *bus;            // Bus we're part of // 
    319 
    320         struct device dev;              // Generic device interface // 
    321   20
    322         struct usb_device_descriptor descriptor;// Descriptor // 
    323         struct usb_host_config *config; // All of the configs // 
    324         struct usb_host_config *actconfig;// the active configuration // 
    325 
    326         char **rawdescriptors;          // Raw descriptors for each config // 
    327 
    328         int have_langid;                // whether string_langid is valid yet // 
    329         int string_langid;              // language ID for strings // 
    330 
    331         void *hcpriv;                   // Host Controller private data // 
    332 
    333         struct list_head filelist; 
    334         struct dentry *usbfs_dentry;    // usbfs dentry entry for the device // 
    335 
    336         // 
    337        //Child devices - these can be either new devices 
    338        //(if this is a hub device), or different instances 
    339        //of this same device. 
    340        //
    341        //Each instance needs its own set of data structures. 
    342          // 
    343 
    344         int maxchild;                   // Number of ports if hub // 
    345         struct usb_device *children[USB_MAXCHILDREN]; 
    346 }; 
    347 #define to_usb_device(d) container_of(d, struct usb_device, dev) 
// �������ܸ��ӵ�һ�����ݽṹ,��������Ŀǰ����Ҫȥ�������ÿһ����Ա,�������ǿ��Կ���,������һ��
// ��Աstruct device dev,û��,�����ǰ��˵���Ǹ�����ÿ���豸��struct device�ṹ�����. 
// ʵ����,U��������߲�����ֱ��ȥ��������ṹ��,��Ϊ����һ��U����˵,�����Ƕ�Ӧ��ôһ��struct 
// usb_device�ı���,���������usb core ��������͸�ֵ.����������Ҫ��ס����ṹ�����,��Ϊ�պ�
// ���ǵ���usb core�ṩ�ĺ�����ʱ��,������������Ϊ����������ȥ,��Ϊ�ܼ�,Ҫ��usb core����,
// �ܵ����˼�֪��������˭��,�������Ҫ���õ�һ������,usb_buffer_alloc,������Ҫ�������. 
// ����U���豸������˵,�����struct usb_device����Ҫ�����ݽṹ��,struct usb_interface.�ߵ���
// һ��,���ǲ��ò�ȥ�˽�һ��usb�豸�Ĺ淶��,����רҵһ��˵,usbЭ��.��Ϊ��������Ҫ֪��ʲô��
// usb interface. 
// ��Э������,��Э����ȥ(��) 
// ��ү˵,����������,����������.˵�ľ����κ����ﶼ����Ҫ���صĹ��.usb�豸Ҫ��ѭ�ľ���usb Э
// ��. �������������Ӳ��,����Ƶ���ʼ,����Ҫ�ο�usbЭ��.��ô���Ӳ��,��α�д���,����usbЭ��,
// ˭Ҳ������ƾ���������.�Ͼ�����дС˵,�м�������������,��ƾ�������д�����¾���,�����Ŀ,��
// ������Щ����İ���Ӱ������Ʒ����.   21
// usbЭ��涨��,ÿ��usb�豸������Щ������Ԫ��,��Ϊ������,���������������κ�һ��usb�豸����
// �е�.������,device descriptor,configuration descriptor,interface descriptor,endpoint 
// descriptor.��������Ķ�����һ���豸������ʱ��ͱ����Ҹ��̻����豸����.���ֶ�����������Ҳ�ı�
// ����,�������и�Intel ��U ��,����ߵĹ��е���Ϣ�϶�����Intel ������ʱ��ͱ����������,��������
// ������һ��,����Intelӡ.���Ե��Ҳ���U��,��cat /proc/scsi/scsi���һ�µĻ�,"Vendor"��һ����
// ʾ�Ŀ϶���Intel. �����⼸��������,usb core������ɨ���ǻ�ͻ�ȥ��ȡ,��ȥ�����ߵ���Ϣ,��
// ��,device������������������device,ע����,���device������һֱ����device��driver�����
// device�ǲ�һ����.��Ϊһ��usb deviceʵ����ָ����һ�ֺ���ϵĸ���,��������һ�ֶ๦�ܵ��豸,
// �ĸ￪��֮��,�๦�ܵĶ���Խ��Խ����,�������󳣼��Ķ๦��һ���,���Ǽ���ӡ��,��ӡ��,ɨ����,��
// �����һ����豸, ��Ȼ,�ⲻ����usb�豸,����usb�豸��ȻҲ���������,�����̨DJ���ܻ��õ���,
// һ������,�ϱߴ�һ��������,����������usb�ӿڽӵ�usb hub��ȥ,��device�����������ľ���������
// �豸���ص�.��ôconfiguration��������,��ʵ˵,�������˽�U����������û��ʲô����,������Ϊһ��
// �������ĵ�����,�˿�,�ұ���Ϊ����˵����,��Ȼֻ�Ǻܼ򵥵�˵����.һ���豸������һ�ֻ��߼�������,
// ��������?û���������usb�豸?��ô��,�ֻ�������,ÿ���ֻ������ж�������,����˵"�趨",����,��
// �����,Nokia6300,�ֻ�����,�����趨ΪEnglish,��������,��������,һ��ѡ��������һ��,��ô�ֻ���
// ������ʾ�����е���Ϣ���Ǹ�������/����.������򵥵�����,����ģʽҲ�кü���,��׼,����,����,etc.
// �������������Ϊ"����",��ô����ֻ�񶯲�����,Ҫ����Ϊ����,��ô��ɶ����Ҳ������,ֻ��ƾ�о���,��
// ǰȥ��˾���ԵĻ�ͨ��������Ϊ����,��Ϊ������Ҳ����,���˼����Թ������˻��ǲ�����.��ôusb�豸
// ������Ҳ�����,��ͬ��usb �豸��Ȼ�в�ͬ��������,����˵��Ҫ������Щ����Ҳ�᲻һ��.����,������
// ��,��˵��ô��,�����������ʱҲ����Ҫ�˽���. 
// ����usb�豸���������д����˵,��Ϊ�ؼ�������������,interface��endpoint.��˵,interface.��һ
// ��,һ��interface��Ӧһ��usb�豸��������.û��,��˵ǰ���Ǹ�����,һ��usb�豸,���ֹ���,һ������,
// �����һ��������,�����ӿ�,�������϶���Ҫ������������,һ���Ǽ�����������,һ������Ƶ����������.
// ���ϵ��ֵ�ϲ������������������һ��Ķ�������һ���豸,�Ǻ�,������ȥ�а�,������interface������
// ���������˰�.������������ǰ���ᵽ���Ǹ����ݽṹ,struct usb_interface.��������
include/linux/usb.h: 
//     71 //* 
//     72//struct usb_interface - what usb device drivers talk to 
//     73//@altsetting: array of interface structures, one for each alternate 
//     74//     setting that may be selected.  Each one includes a set of 
//     75//     endpoint configurations.  They will be in no particular order. 
//     76//@num_altsetting: number of altsettings defined. 
//     77//@cur_altsetting: the current altsetting. 
//     78//@driver: the USB driver that is bound to this interface. 
//     79//@minor: the minor number assigned to this interface, if this 
//     80//     interface is bound to a driver that uses the USB major number. 
//     81//     If this interface does not use the USB major, this field should 
//     82//     be unused.  The driver should set this value in the probe() 
//     83//     function of the driver, after it has been assigned a minor 
//     84//     number from the USB core by calling usb_register_dev(). 
//     85//@condition: binding state of the interface: not bound, binding 
//     86//     (in probe()), bound to a driver, or unbinding (in disconnect()) 
//     87//@dev: driver model s view of this device   22
//     88//@class_dev: driver model s class view of this device. 
//     89//
//     90//USB device drivers attach to interfaces on a physical device.  Each 
//     91//interface encapsulates a single high level function, such as feeding 
//     92//an audio stream to a speaker or reporting a change in a volume control. 
//     93//Many USB devices only have one interface.  The protocol used to talk to 
//    94//an interface's endpoints can be defined in a usb "class" specification, 
//     95//or by a product's vendor.  The (default) control endpoint is part of 
//     96//every interface, but is never listed among the interface's descriptors. 
//     97//
//     98//The driver that is bound to the interface can use standard driver model 
//     99//calls such as dev_get_drvdata() on the dev member of this structure. 
//    100//
//    101//Each interface may have alternate settings.  The initial configuration 
//    102//of a device sets altsetting 0, but the device driver can change 
//    103//that setting using usb_set_interface().  Alternate settings are often 
//    104//used to control the the use of periodic endpoints, such as by having 
//    105//different endpoints use different amounts of reserved USB bandwidth. 
//    106//All standards-conformant USB devices that use isochronous endpoints 
//    107//will use them in non-default settings. 
//    108//
//    109//The USB specification says that alternate setting numbers must run from 
//    110//0 to one less than the total number of alternate settings.  But some 
//    111//devices manage to mess this up, and the structures aren't necessarily 
//    112//stored in numerical order anyhow.  Use usb_altnum_to_altsetting() to 
//    113//look up an alternate setting in the altsetting array based on its number. 
//    114  // 
    115 struct usb_interface { 
    116         // array of alternate settings for this interface, 
    117        //stored in no particular order // 
    118         struct usb_host_interface *altsetting; 
    119 
    120         struct usb_host_interface *cur_altsetting;      // the currently 
    121                                        //active alternate setting // 
    122         unsigned num_altsetting;        // number of alternate settings // 
    123 
    124         int minor;                      // minor number this interface is bound to // 
    125         enum usb_interface_condition condition;         // state of binding // 
    126         struct device dev;              // interface specific device info // 
    127         struct class_device *class_dev; 
    128 }; 
    129 #define to_usb_interface(d) container_of(d, struct usb_interface, dev) 
    130 #define interface_to_usbdev(intf) \ 
    131         container_of(intf->dev.parent, struct usb_device, dev)   23
// ��,����ô��һ��,��ô����ע��Ϊ����?֪���,Linux������ע��ʵ����̫����,���������Ҫ���濴ĳһ
// ��ģ���ʱ����ͻ���ע������.����ṹ����һ���ᴩ����U�����������,������Ȼ���ǲ���ȥ������
// ��,������Ҫ��ס,����U�����������ں����κ�һ���ᵽ��struct usb_interface����ͬһ������,���
// ��������usb core����ɨ���ʱ���������˵�.����ֻ��᳹³Ѹ�������������弴��,ֱ���þ�����.
// ����ǰ��˵����storage_probe(struct usb_interface *intf,const struct usb_device_id 
// *id),storage_disconnect(struct usb_interface *intf)�����������е��Ǹ�����intf. 
// ������130�������-interface_to_usbdev,Ҳ���õ��ŵ�,����˼��,���Ǵ�һ��struct usb_interface
// ת����һ��struct usb_device,����˵����,��Щ������Ҫ�Ĳ�������struct usb_device,������
// usb_interface,��������ת���Ǿ������õ���,�������,usb core���������ҲΪ����׼������,���˸�
// ��,���ǻ���˵ʲô��? 
// ��Э������,��Э����ȥ(��) 
// ������Ǽ�����,����ʱ����һ�����뿪ʼ��storage_probe������,��Ϊ����U�̵Ĺ�������
// �����￪ʼ��.����,ɯʿ����˵��,ĥ�����󿳲�.������������ʱ��,���ٰ��Ĵ�ؼ�������
// ��һ����Ū������, 
// ǰ�������Ѿ��˽���device,configuration,interface,��ʣ���һ��endpoint.USBͨ�ŵ���
// ��������ʽ����ͨ�� endpoint,���ϵ��ֵܹ���������˵�,һ���ӿ���һ�������˵�,����
// Ϊ�� U�������Ĵ洢�豸��,��������һ�����ƶ˵�,����bulk �˵�.��Щ�˵㶼�Ǹ����?˵��
// ����,����һ���Ѿ���. 
// usbЭ����涨��,usb�豸������ͨ�ŷ�ʽ,�ֱ��ǿ��ƴ���,�жϴ���,��������,��ʱ����.��
// ��,��ʱ������Ȼ��������Ƶ����Ƶһ����豸,�����豸�����ܹ��и��Ƚ��ȶ���������,����
// �������� QQ��Ƶ����,�϶�ϣ��ÿ���Ӵ����ͼ��/���������ǱȽ��ȶ���,����˵��һ���Ӷ�
// ������������������������,������һ����ȴ��������ͣ��������,ֻ�ܿ�������ɵ��һ����
// ��,��˵�ⲻ�˷Ѹ�����.����,ÿһ������֪�����˶�Ӧ��֪��,usb-storage��߿϶�������
// ����ʱ����.��Ϊ����ֻ�� copy һ���ļ�,������һ��͵ڶ���Ĵ�����ʲô����,ֻҪ��ʮ��
// �ڴ����˾� ok. 
// ���֮��,��ʱ���������ִ��������鷳��,����,U������ò���,������͵����ȥ��.������Ҫ
// ˵,�жϴ���Ҳ�ò���,���� U ����˵,��ȷ�ò���,��Ȼ˵usb mass storage��Э�������һ
// ������CBI�Ĵ���Э��,CBI����Control/Bulk/Interrupt,������/����/�ж�,�����ִ��䶼��
// �õ�,�����ִ���Э�鲢��������U��,U��ʹ�õ���һ������Bulk-Only�Ĵ���Э��.ʹ������
// Э����豸ֻ�����ִ��䷽ʽ,һ������������,��һ���ǿ��ƴ���,���ƴ������κ�һ�� usb ��
// ��������֧�ֵ�,��ר�����ڴ���һЩ������Ϣ.���������ѯһ�¹������interface��һЩ��
// Ϣ,��ô���ÿ��ƴ���,��bulk ����,������ U�̵���Ҫ������,��д����,��������͵��� bulk
// ����.����Ĵ������Ǻ����ٽ�. 
// ����,֪���˴��䷽ʽ,�Ϳ�������ʶ endpoint��.�� endpoint��������һ�������ܵ�,������
// �Ļ����˹������ pipe.endpoint ����ͨ�ŵķ��ͻ��߽��յ�,��Ҫ��������,����ֻҪ������
// ���͵���ȷ�Ķ˵�����Ϳ�����.֮����U��������bulk�˵�,����Ϊ�˵�Ҳ���з����,һ����
// �� Bulk in,һ������ Bulk out,�� usb�������豸��Ϊ out,���豸��������Ϊ in.���ܵ�,ʵ��
// ��ֻ��Ϊ���������ܹ��ҵ��˵�,���൱�������ճ�˵���ʱ��ַ,����һ������,Ϊ��ͨ��,����
// ����������ط�ȡ��,���˸��������СС��·ȡ��,������Ҫ�ҷ���������Ĺ�Ա����,��Ҫȥ  24
// �Ϸ�,���ĳƫƧ��С�سǳ���,Ҫ���������Ϸ�,���������˵�(endpoint)���Ǳ���,�����
// ֪������������·��,������������سǵ�������·�߾���һ���ܵ�.���˺��������,�ܵ�Ӧ��
// �����˰�,һ���˵��Ǳ���,����һ���˵���?����,�����ܵ���Щ����,�ͱ����Ϸ�,����ֻ��Ҫ
// ֪��һ���Ǳ���,����һ������������ν,��Ϊ�������������㶼�õ��������Ϸ�.û��˵������
// ɽ��������Ϸ�,��Ҫ�����Ļ������Ϸ���,û���¶԰�. 
// �ϸ���˵,�ܵ�����һ��Ӧ����usb����,��ǰ��˵���Ǹ�host,usbЭ�����Ҳ����ô˵��,Э
// �����˵ pipes ������һ������,����һ��������,���������豸�ϵĶ˵�֮���ƶ�����,����ȥ
// ͦ����.��Ϊ��ʵ��,usb������е����ݴ��䶼�������������.һ�ж���������Ϊ����,������
// ������Χ����������Χ.������,usb core ��ߺܶຯ������,Ϊ���� usb host�ܹ���ȷ�����
// ���ݴ������˵�������,�͵ø��� host ��ôһ��pipe,����֮,����֪���Լ���ε��ȵ�����
// �Ǵ��͸�˭���ߴ�˭���ﴫ�����.����������Ҫ����,����˵��Ҫ�� U �����һ���ļ�,���Ҹ�
// ��usb hostĳ���˵���������?�Ǹ��ļ��ֲ��Ǵ����һ���˵����,�������Ǵ����U�����
// ��?�����ֻ���ں���Ĵ�����ȥ֪����.ʵ���϶˵��ⶫ����һ������Ķ���,�������ϳ����
// �����ҹ�����˼���е������������뷨,�����ݱ��������ڶ˵���,���ǿ���ȥȴ���÷·���
// �˵���.��һ�е�����,��������storage_probe()������ȥ�����⿪��. 
// �ο�ʼ�ĵط� 
// ��������usb-storageģ��,usb_stor_init()�����Ŀ�ʼ,Ȼ��,����U������������˵,������
// ��ʹ U�̹���ȴ��ʼ�� storage_probe(). 
// ����ƽ����ֻҪ�ཻ,��ע����ʼ����һ��,�����м��Ƿ���ݷ���. usbcoreΪ�豸�ҵ����ʺ�
// ������������,����Ϊ���������ҵ�������֧�ֵ��豸,����ֻ�Ǳ���˫���ĵ�һӡ�󻹿���,��
// �˴��Ƿ�����ʺ϶Է�����Ҫ��һ�����˽�.��ӹ����,�˽�Է��ĵ�һ����,֪��������Щ����,
// ��������,��������,ϲ����ʲô,��U��driver�����ú���storage_probe()ȥ��ʶ�Է�,��
// �Ǹ�ʲô�����豸,��������ϰ����?������ϵ��ʽ��?����������ĸ�����
// get_device_info,get_protocol,get_transport,get_pipes. ��Ȼ����һЩ���˲����˽��
// ������Ҳ��֪��,����������Χ,�����Ӧ�ľ��� usb_stor_Bulk_man_lun().  
// ���� U�������ⲿ��Ϸ,�� storage_probe��ʼ,�� storage_disconnect����.��
// ��,storage_probe�������ռ���൱���ƪ��.����һ��һ������.����������������
drivers/usb/storage/usb.c��: 
    926 // Probe to see if we can drive a newly-connected USB device // 
    927 static int storage_probe(struct usb_interface *intf, 
    928                          const struct usb_device_id *id) 
    929 { 
    930         struct us_data *us; 
    931         const int id_index = id - storage_usb_ids; 
    932         int result; 
    933 
    934         US_DEBUGP("USB Mass Storage device detected\n"); 
    935 
    936         // Allocate the us_data structure and initialize the mutexes // 
    937         us = (struct us_data *) kmalloc(sizeof(*us), GFP_KERNEL);   25
    938         if (!us) { 
    939                 printk(KERN_WARNING USB_STORAGE "Out of memory\n"); 
    940                 return -ENOMEM; 
    941         } 
//     942         memset(us, 0, sizeof(struct us_data)); 
// ������������ô����,�����������ö�˵��,struct usb_interface��struct usb_device_id��
// ������ָ�붼��ǰ����ܹ���,����usb core��һ��,���������������õ��ľ�����ôһ��,����
// ˵һ��ָ����,һ��ָ����,������ָ���ָ���Ƕ�������. 
// 930��,����Ҫ��һ�����ݽṹ������������֪�����ĵط�����������.����usb-storage
// ģ������Լ���������ݽṹ����,����us_data��һ��.������ݽṹ�Ǹ������ǵĴ���һֱ
// ����ȥ��,��Ӱ����,�������������Կ���������Ӱ.�Ȱ����Ĵ���������,����
drivers/usb/storage/usb.h: 
    105 // we allocate one of these for every device that we remember // 
    106 struct us_data { 
    107         // The device we're working with 
    108        //Its important to note: 
    109        //   (o) you must hold dev_semaphore to change pusb_dev 
    110          // 
    111         struct semaphore        dev_semaphore;   // protect pusb_dev // 
    112         struct usb_device       *pusb_dev;       // this usb_device // 
    113         struct usb_interface    *pusb_intf;      // this interface // 
    114         struct us_unusual_dev   *unusual_dev;    // device-filter entry     // 
    115         unsigned long           flags;           // from filter initially // 
    116         unsigned int            send_bulk_pipe;  // cached pipe values // 
    117         unsigned int            recv_bulk_pipe; 
    118         unsigned int            send_ctrl_pipe; 
    119         unsigned int            recv_ctrl_pipe; 
    120         unsigned int            recv_intr_pipe; 
    121 
    122         // information about the device // 
    123         char                    vendor[USB_STOR_STRING_LEN]; 
    124         char                    product[USB_STOR_STRING_LEN]; 
    125         char                    serial[USB_STOR_STRING_LEN]; 
    126         char                    *transport_name; 
    127         char                    *protocol_name; 
    128         u8                      subclass; 
    129         u8                      protocol; 
    130         u8                      max_lun; 
    131 
    132         u8                      ifnum;           // interface number   // 
    133         u8                      ep_bInterval;    // interrupt interval // 
    134 
    135         // function pointers for this device //   26
    136         trans_cmnd              transport;       // transport function     // 
    137         trans_reset             transport_reset; // transport device reset // 
    138         proto_cmnd              proto_handler;   // protocol handler       // 
    139 
    140         // SCSI interfaces // 
    141         struct Scsi_Host        *host;           // our dummy host data // 
    142         struct scsi_cmnd        *srb;            // current srb         // 
    143 
    144         // thread information // 
    145         int                     pid;             // control thread       // 
    146 
    147         // control and bulk communications data // 
    148         struct urb              *current_urb;    // USB requests         // 
    149         struct usb_ctrlrequest  *cr;             // control requests     // 
    150         struct usb_sg_request    current_sg;      // scatter-gather req.  // 
    151         unsigned char           *iobuf;          // I/O buffer           // 
    152         dma_addr_t              cr_dma;          // buffer DMA addresses // 
    153         dma_addr_t              iobuf_dma; 
    154 
    155         // mutual exclusion and synchronization structures // 
    156         struct semaphore        sema;            // to sleep thread on   // 
    157         struct completion       notify;          // thread begin/end     // 
    158         wait_queue_head_t       dev_reset_wait;  // wait during reset    // 
    159         wait_queue_head_t       scsi_scan_wait;  // wait before scanning // 
    160         struct completion       scsi_scan_done;  // scan thread end      // 
    161 
    162         // subdriver information // 
    163         void                    *extra;          // Any extra data          // 
    164         extra_data_destructor   extra_destructor;// extra data 
destructor   // 
//     165 }; 
// ���ѷ���,Linux�ں���ÿһ����Ҫ�����ݽṹ���ܸ���,���������ں˴����д���ǵ�һ����
// ��,�·��õ㸴�ӵ����ݽṹ���������������Ǹ����.��ɾͿ���������Щ���������,����
// ���й���ѧ��,�Ͼ�̷��ǿ������߷����ٱ�Ҳ��������ôһ��̬�����ݽṹ��.����,�˿�,ÿһ
// ����־���궼Ӧ�ñ��������ش�,ֻ�����ǹ���ǿ����,���ǲ��ܰ�̷��ǿ���鼮��ȫ�����ƹ�,
// �Ӷ�������Щд�ں˴���ļһ�,��Ҫд��ô���ӵĶ���,Ҫ����̷��ǿ������Ĺ���������
// �ݽṹ,����д����.������츣ȫ���������.������? 
// �Ȳ�˵��Щ��,��֮,�������ͷ�۵����ݽṹ��ÿһ�� device���е�,���仰˵,���ǻ�Ϊÿһ
// �� device����һ��us_data,��Ϊ����ṹ��ߵĶ�������֮��һֱ���õ��ŵ�.������ô��,
// ÿ����Աʲô��˼,�Ժ���������ϸ˵.930��,struct us_data *us,����,�պ����ǻ�ǳ�Ƶ��
// �Ŀ���us��.��,us ʲô��˼?���˵:us ��,usb storage ��Ҳ. 
// 937��,����Ϊus�����ڴ�ռ�,��938�о����ж��ڴ�ռ��Ƿ�����ɹ�,�ɹ��Ļ�us�Ͳ���
// Ϊ 0,����˵Ϊ NULL,���Ϊ NULL ��ô����ʧ����,��ô�����˷ѱ�����,����Ϸ����ô��ǰز  27
// ����.��������Ҫǿ������,�����ں˴�����,�������ж��ڴ������Ƿ�ɹ���������޴�����,ÿ
// �����ڴ���������,����һ�������һ���ж�����ɹ��������.д��������˶���֪��,
// �������Ǻ��б�Ҫ��,��Ϊ��û�����뵽�ڴ�,��ô������ȥ����û�������,���˿������˼�ʶ
// ���������α���֮��,û�б�ĺô�.���ڴ����벻�������˶��,���п���ʧ��,д���������
// �����޷�����������,���ǵļ������������������ǰ��ͦ,���ܴ���.���������ü����д
// �����ʱ����ͻᷢ�ּ������ô�Ĵ����������� 
// 942��,�� us ��ʼ��Ϊȫ0. 
// 934����� US_DEBUGP,��һ����,���� drivers/usb/storage/debug.h,�������ܶ������
// ����Ҳ�ῴ�������,���޷Ǿ��Ǵ�ӡһЩ������Ϣ.debug.h ������ôһ��, 
     54 #ifdef CONFIG_USB_STORAGE_DEBUG 
     55 void usb_stor_show_command(struct scsi_cmnd *srb); 
     56 void usb_stor_show_sense( unsigned char key, 
     57                 unsigned char asc, unsigned char ascq ); 
     58 #define US_DEBUGP(x...) printk( KERN_DEBUG USB_STORAGE x ) 
     59 #define US_DEBUGPX(x...) printk( x ) 
     60 #define US_DEBUG(x) x 
     61 #else 
     62 #define US_DEBUGP(x...) 
     63 #define US_DEBUGPX(x...) 
     64 #define US_DEBUG(x) 
     65 #endif 
     66 
     67 #endif 
// ����һ�������˼�����,US_DEBUGP,US_DEBUGPX,US_DEBUG,��𲻴�,ֻ����ʽ����
// �в�ͬ����. 
// ��Ҫע�����,��Щ������Ϣ�������Ǵ��˱���ѡ�� CONFIG_USB_STORAGE_DEBUG��
// �������,����Ҳ��������,������ѡ��Ϊ 0,��ô�⼸�����ʲôҲ����,��Ϊ���Ǳ���Ϊ����.
// ���� US_DEBUGϵ�е��⼸����,�ͽ���ô��,֮��������,��ֱ�ӹ��˵�,�����˵. 
// ���� prink�� kmalloc,����������Ҳû��̫����Ҫ˵��,�Դ����������,�Ͱ� printk ����
// printf,��kmalloc����malloc����,ֻ������������������ר�������ں˴����е�.һ���Ǵ�ӡ
// һЩ����,һ���������ڴ�ռ�. 
// 931����?id_index �����õ�?���������½ڲ�����ɢ��.Be there or be square!-�������
// ˵. 
// �豸������ 
// storage_probe�������ͦ����˼��,�ܳ��Ȳ���100��,���Ǹ����������,����������ϵĺ���,����
// �ж������������,�ڳ��ϲ�������,����ȴΪ�����Ŷ�������׿Խ�Ĺ���.Ҳ�кܶ����ۼ�˵����ս���ʼ�
// ������⼸���˥�����ǴӸ�����������۵����������ʼ��. 
// �ڽ�id_index ֮ǰ,���Ǽ�����storage_probe�Ĵ���:   28
    943         init_MUTEX(&(us->dev_semaphore)); 
    944         init_MUTEX_LOCKED(&(us->sema)); 
    945         init_completion(&(us->notify)); 
    946         init_waitqueue_head(&us->dev_reset_wait); 
    947         init_waitqueue_head(&us->scsi_scan_wait); 
    948         init_completion(&us->scsi_scan_done); 
    949 
    950         // Associate the us_data structure with the USB device // 
    951         result = associate_dev(us, intf); 
    952         if (result) 
    953                 goto BadDevice; 
    954 
    955         // 
    956        //Get the unusual_devs entries and the descriptors 
    957        //
    958        //id_index is calculated in the declaration to be the index number 
    959        //of the match from the usb_device_id table, so we can find the 
    960        //corresponding entry in the private table. 
    961          // 
    962         get_device_info(us, id_index); 
// storage_probe�������֮���Զ�С,����Ϊ�������˴����ĺ���.����,�������̶�һ�δ���,ʵ����ȴҪ
// �������Ƕ�������˺ü���Сʱ,�������Ǿ��ò�����,�ѹ������������������storage_probe������
// ʱ��,�����п�,����ȥ��,��������ʱ��,��������,�������ʱ��,�һ�л��,���ٿ���ʱ��,����,��������
// ������,���Ƕ���β���100 �еĺ���������ʱ��Ϊ��һȥ��������? 
// ��ʵ���ǲ�֪��id_indexҲ��Ӱ��Ժ�����������,����ĳ����������˵,��̫���īȥ�����
// id_index��һ�����������ĸо�,����,��ʱ��,��Щ����,����֪�������ε���,���ε�����,ȴ��Ҫ���ε�
// ���,���ε�ȥѡ��,��ʱ�����ε��ӱܶ�������,��Ϊ���Ƕ������ν�����.��������,ע�⵽962�г�����
// һ��get_device_info�ĺ���,����һ����������id_index,����,���Ǳ���ѡ��,ֻ�ܿ������id_index
// �����Ǹ����. 
// �Ͻ�����ע�⵽id_index=id-storage_usb_ids,id����֪��,storage_probe�����������β�֮һ,��
// storage_usb_ids,���Ǳ���,����������������usb_storage_driver�ĳ�Աid_table ��ֵ.������
// id_table�Ŀ��Ի�ȥ��.��ʵ���Ͼ���һ�ű��,����ȫ���������driver֧��������һЩ��
// ��.storage_usb_idsͬ������drivers/usb/storage/usb.c��, 
    111 // The entries in this table, except for final ones here 
    112//(USB_MASS_STORAGE_CLASS and the empty entry), correspond, 
    113//line for line with the entries of us_unsuaul_dev_list[]. 
    114  // 
    115 
    116 #define UNUSUAL_DEV(id_vendor, id_product, bcdDeviceMin, bcdDeviceMax, \ 
    117                     vendorName, productName,useProtocol, useTransport, \ 
    118                     initFunction, flags) \   29
    119 { USB_DEVICE_VER(id_vendor, id_product, bcdDeviceMin,bcdDeviceMax) } 
    120 
    121 static struct usb_device_id storage_usb_ids [] = { 
    122 
    123 #       include "unusual_devs.h" 
    124 #undef UNUSUAL_DEV 
    125         // Control/Bulk transport for all SubClass values // 
    126         { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_RBC, 
US_PR_CB) }, 
    127         { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_8020, 
US_PR_CB) }, 
    128         { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_QIC, 
US_PR_CB) }, 
    129         { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_UFI, 
US_PR_CB) }, 
    130         { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_8070, 
US_PR_CB) }, 
    131         { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_SCSI, 
US_PR_CB) }, 
    132 
    133         // Control/Bulk/Interrupt transport for all SubClass values // 
    134         { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_RBC, 
US_PR_CBI) }, 
    135         { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_8020, 
US_PR_CBI) }, 
    136         { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_QIC, 
US_PR_CBI) }, 
    137         { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_UFI, 
US_PR_CBI) }, 
    138         { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_8070, 
US_PR_CBI) }, 
    139         { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_SCSI, 
US_PR_CBI) }, 
    140 
    141         // Bulk-only transport for all SubClass values // 
    142         { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_RBC, 
US_PR_BULK) }, 
    143         { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_8020, 
US_PR_BULK) }, 
    144         { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_QIC, 
US_PR_BULK) }, 
    145         { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_UFI, 
US_PR_BULK) }, 
    146         { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_8070,   30
US_PR_BULK) }, 
    147 #if !defined(CONFIG_BLK_DEV_UB) && !defined(CONFIG_BLK_DEV_UB_MODULE) 
    148         { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_SCSI, 
US_PR_BULK) }, 
    149 #endif 
    150 
    151         // Terminating entry // 
    152         { } 
    153 }; 
//ע�⵽����һ��struct usb_device_id�ṹ�������,���Լ�ʹ�������°���˼��Ҳ��֪��,����ÿһ��
//��Ȼ��һ��struct usb_device_id�Ľṹ�����.����������USB_INTERFACE_INFO�������,����
//Ȼ����һ����,����include/linux/usb.h, 
    473 //* 
    474//USB_INTERFACE_INFO - macro used to describe a class of usb interfaces 
    475//@cl: bInterfaceClass value 
    476//@sc: bInterfaceSubClass value 
    477//@pr: bInterfaceProtocol value 
    478//
    479//This macro is used to create a struct usb_device_id that matches a 
    480//specific class of interfaces. 
    481  // 
    482 #define USB_INTERFACE_INFO(cl,sc,pr) \ 
    483         .match_flags = USB_DEVICE_ID_MATCH_INT_INFO, .bInterfaceClass = 
(cl), .bInterfaceSubClass = (sc), .bInterfaceProtocol = (pr) 
//ÿһ��USB_INTERFACE_INFO���ǹ���һ��struct usb_device_id�Ľṹ�����,�ع�һ������֮ǰ
//������struct usb_device_id�Ķ���,����ʵ���Ͼ���Ϊ���е��ĸ�Ԫ�ظ���ֵ,������
//match_flags,bInterfaceClass,bInterfaceSubClass,bInterfaceProtocol.���ﲻ�ò�˵����,�����
//�������������usb�豸,���Ǹ��и����ص�,Ϊ����������,usb�淶,����˵usbЭ��,��usb�豸��
//���˺ܶ���,Ȼ��ÿ�����ֳַ�����,��ܺ����,����һ����ѧҲ�����,���Ƿֳɺܶ��ѧԺ,�������Ǹ�
//����ѧ,��ϢѧԺ,����ѧԺ,����ѧԺ,����ѧԺ,�ȵ�.Ȼ��ÿ��ѧԺ�ֱ���Ϊ�ܶ��ϵ,������ϢѧԺ,����
//���˵��ӹ���ϵ,΢����ϵ,�����ϵ,ͨ�Ź���ϵ,Ȼ�����ÿ��ϵ�±��ַ��˸���רҵ,usbЭ��Ҳ������
//�ɵ�,����ÿ��Interface����һ��Class,(Ϊʲô�ǰ�Interface����,������Device����?ǰ�潲����,
//��usb�豸������,��������Device,��Ϊÿ���豸������Ӧ����һ��Interface,������һ��Device),Ȼ
//��Class�����ַ���SubClass,����SubClass�����ְ������豸����ѭ�Ĳ�ͬ��ͨ��Э�����ϸ��.usb
//Э�����Ϊÿһ��Class,ÿһ��SubClass,ÿһ��Protocol����һ����ֵ,����mass storage��Class
//����0x08,������USB_CLASS_MASS_STORAGE�������include/linux/usb_ch9.h�ж���,��ֵ��
//��8. 
//�����õ�126 ��������, 
//  { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_RBC, US_PR_CB) }, 
//  �������չ��,����˵��������ôһ��usb_device_id�ṹ�����,��
//match_flags=USB_DEVICE_ID_MATCH_INT_INFO,��  31
//bInterfaceClass=USB_CLASS_MASS_STORAGE,bInterfaceSubClass=US_SC_RBC,��
//bInterfaceProtocol=US_PR_CB. 
//USB_CLASS_MASS_STORAGE�Ͳ�����˵��,�����������������֧�ֵ�ÿһ���豸�������������,
//����˵���Class.�������Class��߰�����ͬ��SubClass,����subclass 02ΪCD-ROM�豸,04Ϊ
//����������,06Ϊͨ��SCSI���豸.��ͨ��Э������Ҫ��CBIЭ��� Bulk-OnlyЭ��. 
//��US_SC_RBC��Щ����sub class�ĺ�Ķ��������ļ�drivers/usb/storage/protocol.h��: 
     47 // Sub Classes // 
     48 
     49 #define US_SC_RBC       0x01            // Typically, flash devices // 
     50 #define US_SC_8020      0x02            // CD-ROM // 
     51 #define US_SC_QIC       0x03            // QIC-157 Tapes // 
     52 #define US_SC_UFI       0x04            // Floppy // 
     53 #define US_SC_8070      0x05            // Removable media // 
     54 #define US_SC_SCSI      0x06            // Transparent // 
     55 #define US_SC_ISD200    0x07            // ISD200 ATA // 
//����US_PR_CB��Щ���ڴ���Э��ĺ�������һ���ļ���,drivers/usb/storage/transport.h 
//  // Protocols // 
#define US_PR_CBI       0x00            // Control/Bulk/Interrupt // 
#define US_PR_CB        0x01            // Control/Bulk w/o interrupt // 
#define US_PR_BULK      0x50            // bulk only // 
// ����ļ��л������˸����Э��,����������ʱֻ��Ҫ֪��������,��Ϊ����Э�鶼��ר�����һЩ������
// ����,��storage_usb_ids������ʹ�ú�USB_INTERFACE_INFO�����usb_device_id��ֻ���õ�
// ������Э��.(US_PR_CBI��US_PR_CB������Э����usbЭ���ж�����CBI,����֮���е���.)����
// ��һЩ������豸,����unusual_devs.h�ļ�����ר�ŵ�һЩ��������,�������Ҳ�ȥ��ע����. 
// ˵�������,U���������е���һ����?usbЭ���й涨,U�̵�Subclass������US_SC_SCSI��.����ͨ
// ��Э��ʹ�õ���Bulk-Only��.��Ȼ��Щ�������Ǻ��������õ���. 
// ��ô���ﻹ��һ��match_flag,�����Ǳ�ʾʲô��˼?USB_INTERFACE_INFO�����ò�ư����е���
// ����match_flag��������� USB_DEVICE_ID_MATCH_INT_INFO,����Ϊɶ?���������
// include/linux/usb.h, 
//     435 #define USB_DEVICE_ID_MATCH_INT_INFO \ 
//     436         (USB_DEVICE_ID_MATCH_INT_CLASS | 
// USB_DEVICE_ID_MATCH_INT_SUBCLASS | USB_DEVICE_ID_MATCH_INT_PROTOCOL) 
// match_flag��������Ǹ�usb coreȥ�õ�,usb core������豸Ѱ���ʺ�����driver,�����driver
// Ѱ���ʺ�����device,�����Ƚϵľ���struct usb_device_id�ı���,�� struct usb_device_id�ṹ��
// ��������Ա,��ô�ǲ���һ��Ҫ��ÿһ����Ա�����Ƚ�һ����,��ʵû�б�Ҫ��ôϸ,��������,����
// ��������,���Ǹ���usb core,��ֻҪ�Ƚ�bInterfaceClass,bInterfaceSubClass,bInterfaceProtocol
// ����.include/linux/mod_devicetable.h�����struct usb_device_id�е�ÿһ��Ҫ�Ƚϵ������
// һ����:   32
    121 // Some useful macros to use to create struct usb_device_id // 
    122 #define USB_DEVICE_ID_MATCH_VENDOR              0x0001 
    123 #define USB_DEVICE_ID_MATCH_PRODUCT             0x0002 
    124 #define USB_DEVICE_ID_MATCH_DEV_LO              0x0004 
    125 #define USB_DEVICE_ID_MATCH_DEV_HI              0x0008 
    126 #define USB_DEVICE_ID_MATCH_DEV_CLASS           0x0010 
    127 #define USB_DEVICE_ID_MATCH_DEV_SUBCLASS        0x0020 
    128 #define USB_DEVICE_ID_MATCH_DEV_PROTOCOL        0x0040 
    129 #define USB_DEVICE_ID_MATCH_INT_CLASS           0x0080 
    130 #define USB_DEVICE_ID_MATCH_INT_SUBCLASS        0x0100 
    131 #define USB_DEVICE_ID_MATCH_INT_PROTOCOL        0x0200 
// ��ȥ�Ա�һ��struct usb_device_id��֪����Щ����ʲô��˼��. 
// Ȼ�������ٿ�storage_usb_ids���Ǹ�#include "unusual_devs.h",ʵ��������ļ�Ҳ�����������
// drivers/usb/storage/Ŀ¼����,����߶�����һЩ������豸,Ҳ����struct usb_device_id�ṹ���
// ������ʽ,��Щ�豸��������һЩ����豸���߱�������,������������ѭ��ͨ��Э����Щ���ڲ�ͬ,����,
// ���Ȳ���Bulk-OnlyҲ����CBI,����Щ����������Ƶ��豸,д�����ͬ־�ǰ����ǵ��������˳���.��
// ��������ļ���.��Ȼ,�Ӵ��������,������Ȼ������usb mass storage�������,����Ҳû��Ҫ����
// ���Ŀ¼������. 
// ����,���ǿ���֪��storage_usb_ids���������ô������.usb coreΪÿ���豸�����ű������,�����
// ����ĳһ�к�����豸��ƥ��,��ô���о�������ǰ���ᵽ���Ǹ�storage_probe()�Ĳ���id.����
// id_index=id-storage_usb_ids��������������������,�ڱ��еı��.������������ʲô��,��������
// ¿������.��֮,����ô�󾢸�����ôһ����,���������������. 
// ���,�ܽ�´�,�����ν�Ļ�����,�ͺñ����Ǵ�ѧ���������ѧУ,ÿ���˶��������Ѽ�һ����ѧУ����,
// Ȼ���ϸ�����,����ʦ������,�Ƿ�ţ�ĵ�ʦ����,���羭��ʵ��,�Ƿ��ܸ�����Ľ�ѧ��,������ڱ�����
// ��,�Ƿ��ù��ش���,ȡ�ù����ֳɼ�,����ѧУ����, �Ƿ�����У,�ۺ���Щ��������ȷ��һ������,��
// ���Լ��������ǵ�ѧУ������.��ô�Ǹ�match_flags��ʲô��˼��,���е�ͬѧ������̫�鷳,�ֻ�����
// �ǿ���ֻ����Ҫһ���ܷ�ѧ����,�������Ϲ���������ò�ʿѧλ���Ǹ����ֶٴ�ѧ����������ƾ��ѧУ
// Ҳ���������������,��ô���ǾͲ���ȥ������ô����,�����������е�match_flags�����ܹ���������Ϊ
// У�ѾͿ�����,�����Ƿ���Ϊ��ѧУ��ȡ���Ժ�����Ҳ������������ʹʧĸУ��. 
// �������߷�һ��֮�� 
// ������һ�콨�ɵ�.����U�̹���֮ǰ,��ʵ���ǵ��������˺ܶ�׼������. 
// ���Ǽ������Ÿо���,storage_probe(),943����948��,һϵ�е���init_*�����ĺ����ڴ˿̱�����,��
// ���漰��һЩ������,�ȴ�����,����ֻ�ǳ�ʼ��,���Ҳ����,�������õ���ʱ����ϸ˵,�������ס,�⼸
// ��ÿһ�ж������õ�.������Ȼ���õ���. 
// ��ʱ,������������,951��associate_dev()��962 ��get_device_info(),����������������Ŀǰ��Ҫ
// ����,һ��һ����.   33
// �ȿ�associate_dev(),������drivers/usb/storage/usb.c, 
429 // Associate our private data with the USB device // 
    430 static int associate_dev(struct us_data *us, struct usb_interface *intf) 
    431 { 
    432         US_DEBUGP("-- %s\n", __FUNCTION__); 
    433 
    434         // Fill in the device-related fields // 
    435         us->pusb_dev = interface_to_usbdev(intf); 
    436         us->pusb_intf = intf; 
    437         us->ifnum = intf->cur_altsetting->desc.bInterfaceNumber; 
    438         US_DEBUGP("Vendor: 0x%04x, Product: 0x%04x, Revision: 0x%04x\n", 
    439                         us->pusb_dev->descriptor.idVendor, 
    440                         us->pusb_dev->descriptor.idProduct, 
    441                         us->pusb_dev->descriptor.bcdDevice); 
    442         US_DEBUGP("Interface Subclass: 0x%02x, Protocol: 0x%02x\n", 
    443                         intf->cur_altsetting->desc.bInterfaceSubClass, 
    444                         intf->cur_altsetting->desc.bInterfaceProtocol); 
    445 
    446         // Store our private data in the interface // 
    447         usb_set_intfdata(intf, us); 
    448 
    449         // Allocate the device-related DMA-mapped buffers // 
    450         us->cr = usb_buffer_alloc(us->pusb_dev, sizeof(*us->cr), 
    451                         GFP_KERNEL, &us->cr_dma); 
    452         if (!us->cr) { 
    453                 US_DEBUGP("usb_ctrlrequest allocation failed\n"); 
    454                 return -ENOMEM; 
    455         } 
    456 
    457         us->iobuf = usb_buffer_alloc(us->pusb_dev, US_IOBUF_SIZE, 
    458                         GFP_KERNEL, &us->iobuf_dma); 
    459         if (!us->iobuf) { 
    460                 US_DEBUGP("I/O buffer allocation failed\n"); 
    461                 return -ENOMEM; 
    462         } 
    463         return 0; 
    464 } 
//   ������������ע����associate_dev�Ĳ���, struct us_data *us,���ݸ�������us,������ö�˵��
// ��,��ǰ�ո�Ϊ���������ڴ�,���ҳ�ʼ������ԱΪ0. ���us��һֱ�����������ȥ,ֱ�����ǵĹ��½���.
// ��������Ҫ�Բ��Զ���. struct usb_interface *intf,���Ҳ����˵,storage_probe()����������������
// ����֮һ.��֮,�˴�֣������һ��,struct us_data�Ľṹ��ָ��us,struct usb_interface�ṹ���ָ
// ��intf,�Լ�struct usb_device�ṹ���struct usb_device_id�ṹ��������U�������Ĺ�������Ψ
// һ��,ÿ���ᵽ�����Ǹ�. ���Ժ����ǻ����ϵļ�����Ҫ�����ݽṹ,struct urb urb,struct scsi_cmnd   34
// srb��Ҳ�ǳ���Ҫ,�������ǲ���Ψһ,Ҳ��ÿ�����϶���һ��,������Ϸһ��.ǰ���⼸�����ݽṹ�ı���
// ������Щ����,��֮��������urb��,srb��,��ȻƵ��¶��,����ֻ��Ⱥ����Ա,ֻ���������·�˼�,�´���
// ·����. ����,�Ժ����ǽ�ֻ˵us,����˵struct us_data *us,struct usb_interface * intfҲ��ֻ��
// intf������. 
// us֮������Ҫ,����Ϊ�������ܶຯ����Ҫ�õ����Լ����ĸ�����Ա.ʵ����Ŀǰ�����
// ��,associate_dev�������������Ϊus�ĸ���Ա��ֵ,�Ͼ��˿�us������֮ǰ�ᵽ����Щstruct 
// usb_device��,struct usb_interface��,��û��һ���ϵ.���,�������,�Լ���֮��ĺü�����������
// Ϊ�˸�us�ĸ���Ա�����ʵ���ֵ,֮���������ʦ����ȥΪ����ֵ,��Ҫ������Ϊ����Ҫ������.��ν����
// û����ѵ����. 
// 432��,��������ི,��Ϊֻ��һ��debug���,������һ��__FUNCTION__���"��",gcc 2.95��
// ��İ汾֧����ôһ������,���"��"�ڱ����ʱ��ᱻת��Ϊ������(�ַ���),������Ȼ����
// "associate_dev"��ôһ���ַ���,���Ǻ���ִ�е�����ͻ��ӡһ�仰������������ִ�е����������
// ��,����������Ȼ�����������ǵ��Գ���.�����������ʵ���ϲ��Ǻ�,��ΪԤ����������һ����֪.������
// ֻ�б������Ŷ�. 
// 435��,pusb_dev,����point of usb device����˼.struct us_data�е�һ����Ա,�������Ǹղ�
// Լ���Ĺ��,�˿��ҽ�˵us��һ����Ա,us->pusb_dev= interface_to_usbdev(intf), 
// interface_to_usbdev����ǰ���Ѿ�����,�京�����������ʾ������,��һ��struct interface�ṹ���
// ָ��ת����һ��struct usb_device�Ľṹ��ָ��.ǰ������˵��,struct usb_device������û��ʲô��,
// ����usb core ���һЩ����Ҫ��ʹ���������,�������ǲ����Ѷ�Ϊֹ,����ν���ڽ������ɼ�. 
// 436��,��intf����us ��pusb_intf. 
// 437��,us��ifnum, �ȿ�intf��cur_altsetting,������������л���.usb�豸��һ��
// configuration�ĸ���,�������ǰ�潲Э���ʱ��˵��,����������һ��setting,զһ����Щ���,������
// �ʲ���һ������.��ʱ��,�����ֳ�����ˮƽ��,�Ϲ��¶���û�Ϲ��¶���,��û�����������GRE�챦��,
// ����ʱ������ֳ������.��������������Ϥ���ֻ�����ȷ�,configuration��˵��,setting,һ���ֻ���
// �ܸ������ö�ȷ����,���񶯻��������Ѿ�ȷ����,���ֹ��ܶ�ȷ����,���������Ĵ�С�����Ա��,ͨ����
// ����������һ��һ��ı䶯,���Ҳ��5,6��,��ô���������һ��setting��.����cur_altsetting���Ǳ�
// ʾ�ĵ�ǰ�����setting,����˵����.cur_altsetting��һ��struct usb_host_interface��ָ��,�����
// ���嶨����include/linux/usb.h: 
51 // host-side wrapper for one interface setting's parsed descriptors // 
     52 struct usb_host_interface { 
     53         struct usb_interface_descriptor desc; 
     54 
     55         // array of desc.bNumEndpoint endpoints associated with this 
     56        //interface setting.  these will be in no particular order. 
     57          // 
     58         struct usb_host_endpoint *endpoint; 
     59 
     60         unsigned char *extra;   // Extra descriptors // 
     61         int extralen;   35
     62 }; 
// ���ĳ�Աdesc��һ��struct usb_interface_descriptor�ṹ�����,����ṹ��Ķ����Ǻ�usbЭ��ֱ
// �Ӷ�Ӧ��,������include/linux/usb_ch9.h.(����ȡ��Ϊ"ch9"����Ϊ����ļ��ܶණ����Ӧ��usb 
// spec 2.0�еĵھ���,chapter 9.): 
    242 // USB_DT_INTERFACE: Interface descriptor // 
    243 struct usb_interface_descriptor { 
    244         __u8  bLength; 
    245         __u8  bDescriptorType; 
    246 
    247         __u8  bInterfaceNumber; 
    248         __u8  bAlternateSetting; 
    249         __u8  bNumEndpoints; 
    250         __u8  bInterfaceClass; 
    251         __u8  bInterfaceSubClass; 
    252         __u8  bInterfaceProtocol; 
    253         __u8  iInterface; 
    254 } __attribute__ ((packed)); 
// ���������������ᵽ����bInterfaceNumber,һ���豸�����ж��Interface,����ÿһ��Interface��
// Ȼ�͵��ø������,Ҫ��Ȼզ���ְ�?������Щ��������Ķ������ǳ�����ʱ��͹̻����豸��ߵ�,����
// ������֮���Կ�����bInterfaceNumber����ֵ,����Ϊusbcore��Ϊ�豸��ʼ����ʱ����Ѿ���������
// Щ����.����Ļ�,�������Ǵ粽����. 
// ��֮,us->ifnum��������,���վ��ǵ��������������interface�ı��. 
// 438��444�о�������������,��ӡ����һЩ��������Ϣ,����device��������interface������. 
// 447��, usb_set_intfdata(),����ʵ��һ����������,����һ�д���,Ҳ�Ƕ�����
// include/linux/usb.h��: 
    138 static inline void usb_set_intfdata (struct usb_interface *intf, void *data) 
    139 { 
    140         dev_set_drvdata(&intf->dev, data); 
    141 } 
//   ��Ȥ����,dev_set_drvdata�������Ҳ����������,Ҳֻ��һ�д���,��������
// include/linux/device.h��: 
302 static inline void 
    303 dev_set_drvdata (struct device *dev, void *data) 
    304 { 
    305         dev->driver_data = data; 
    306 } 
//   ����,�������,�����������������&intf->dev->driver_data=data,��
// &intf->dev->driver_data=us.   36
// ��������,���������ڴ���,us->cr��us->iobuf����ָ��,����������ָ�������ڴ�ռ�,������õ�
// ��.��Ҫע�����usb_buffer_alloc(),���������usbcore�ṩ��,����ֻ�ܵ��ü���.�������Ͼ���֪��
// �������������ڴ��,��һ����������struct usb_device�ṹ���ָ��,��������Ҫ����һ��pusb_dev,
// ����������,GFP_KERNEL,��һ���ڴ������flag,ͨ���ڴ����붼�����flag,�������ж�������,����
// ˯��,�Ǿ͵���GPF_ATOMIC,����û��ô��Ҫ��.�ڶ������������buffer�Ĵ�С,����cr,���ݵ���
// sizeof(*us->cr),������iobuf,���ݵ���US_IOBUF_SIZE,����һ����,��С��64,�������Լ������,
// ����drivers/usb/storage/usb.h: 
     91 // 
     92//We provide a DMA-mapped I/O buffer for use with small USB transfers. 
     93//It turns out that CB[I] needs a 12-byte buffer and Bulk-only needs a 
      94//31-byte buffer.  But Freecom needs a 64-byte buffer, so thats the 
     95//size we ll allocate. 
     96  // 
     97 
     98 #define US_IOBUF_SIZE           64      // Size of the DMA-mapped I/O buffer 
// 
// ��usb_buffer_alloc()�ĵ��ĸ�������Щ��˼��,��һ�����Ǵ��ݵ���&us->cr_dma,�ڶ��δ��ݵ���
// &us->iobuf_dma,���漰��dma����.���������˴�ǰ���Ƕ�û�и���ֵ,�෴�������������������֮
// �󱻸���ֵ��.cr_dma��iobuf_dma����dma_addr_t���͵ı���,�������������Linux�ں���ר��
// Ϊdma�����׼����.Ϊ��֧��dma����,usb_buffer_alloc�������������˵�ַ,���ҽ�����dmaӳ
// ��,cr_dma�� iobuf_dma���Ǽ�¼��cr �� iobuf��dma ��ַ.����ʲô��cr,������Щ dma��ַ����
// ��ʲô��,�����Ժ�ͻ�����,��ʱ���ٽ�Ҳ����.������Ҫ֪���ľ���usb_buffer_alloc����Ŀռ�ֱ�
// ���ظ���cr �� iobuf.˳����һ��,��usb_buffer_alloc������ڴ�ռ���Ҫ�����Ĵ
// usb_buffer_free()���ͷ�. 
// 452�к�459 ��,ÿһ���������ڴ��Ҫ���ɹ����,���ǹ���.���������ܷ������豸,�ؼ����ǿ��ܷ�
// ���뵽�ڴ�ռ�,�κ�һ���ڴ�ռ�����ʧ��,�������������û����������.���������Ҷ���,̸����,��
// ��Ҫ����û�з���.û�з��ӵĻ�,��ô�����ϰ���Ҳ��ûϷ.Ȼ����ʵ��Ҫӵ�з��ӱȼ����������ڴ�ȴ
// Ҫ�������,���.������������һ����,�����ǲ�����Ǯ��ʱ��,�����Ƿ����,����������Ǯ��ʱ��,ȴ��
// �ַ����Ѿ�������.�ޡ� 
// ��������,���컹��Զ��?(һ) 
// ����usb-storageģ��Ĵ�����,�������Ĳ�����һ������usb_stor_control_thread()�ĺ�����,��
// ��Ҳ��Ȼ�������������µĸ߳�.��������ĵ�����Щ����,�����Ǵ�usb_stor_acquire_resources()��
// �������,���������Ǽ�������,��������Ϸ��ֻ���ֹ�һ��,��storage_probe��,�к�Ϊ998�ĵط�.Ȼ
// ���ڴ�֮ǰ,���ĸ���������������ǰ,���Ǿ���  37
// get_device_info,get_transport,get_protocol,get_pipes.����ǰ����˵,������Ҫ�ߵ�һ��,����Ҫ
// �˽�˴�,���ĸ�����������driverȥ��ʶ device��.��һ�����Ǵ�������Ҳ�ܿ�����.driver��Ҫ֪��
// device������˭,��������get_device_info,driver��Ҫ֪��deviceϲ����ʲô��ʽ��ͨ,����QQ ��
// ����msn����ֻ���ֻ�����,�����ĳһ��,��ô�˺��Ƕ���,�����ֻ����Ƕ���,д������˰���Щ������
// �����get_transport,get_protocol,get_pipes. 
// ʵ����,���ĸ�����,����֮ǰ��˵�����Ǹ�associate_dev(),��������������ƽ�������Ĳ���,��һ��
// ���ⲿ�ִ�������������,��ôû����һ��usb����ͨ�Ű�?��ȫû�п���usb host ��usb device����
// ���ڽ�����,����usb��?��һ��,��Ÿ������,���������,��ʧ��.����,����֪��,����,���Ƕ���绨ѩ
// ���й�,����,��������趷�����й�.�⼸������Ӧ��˵�Ǹ��������̵�,�컨��Ҫ����Ҷ��,û����δ���
// ���̵�,���˺���usb�豸����Ҳ�޷�����������.����,һ��������Ϣ��,�⼸����������ֻ��������һ��,
// ���������������о���ôһ��¶���Ļ���,������ÿ���˵��ഺ,ֻ��һ��,�޷���ͷ.������ÿ���˵��ഺ
// һ��,���Ǿ����.����,�������������ƽ������Ĵ����. 
// get_device_info, �������������drivers/usb/storage/usb.c��: 
466 // Get the unusual_devs entries and the string descriptors // 
    467 static void get_device_info(struct us_data *us, int id_index) 
    468 { 
    469         struct usb_device *dev = us->pusb_dev; 
    470         struct usb_interface_descriptor *idesc = 
    471                 &us->pusb_intf->cur_altsetting->desc; 
    472         struct us_unusual_dev *unusual_dev = &us_unusual_dev_list[id_index]; 
    473         struct usb_device_id *id = &storage_usb_ids[id_index]; 
    474 
    475         // Store the entries // 
    476         us->unusual_dev = unusual_dev; 
    477         us->subclass = (unusual_dev->useProtocol == US_SC_DEVICE) ? 
    478                         idesc->bInterfaceSubClass : 
    479                         unusual_dev->useProtocol; 
    480         us->protocol = (unusual_dev->useTransport == US_PR_DEVICE) ? 
    481                         idesc->bInterfaceProtocol : 
    482                         unusual_dev->useTransport; 
    483         us->flags = unusual_dev->flags; 
    484 
    485         // Log a message if a non-generic unusual_dev entry contains an 
    486        //unnecessary subclass or protocol override.  This may stimulate 
    487        //reports from users that will help us remove unneeded entries 
    488        //from the unusual_devs.h table. 
    489          // 
    490         if (id->idVendor || id->idProduct) { 
    491                 static char *msgs[3] = { 
    492                         "an unneeded SubClass entry", 
    493                         "an unneeded Protocol entry", 
    494                         "unneeded SubClass and Protocol entries"};   38
    495                 struct usb_device_descriptor *ddesc = &dev->descriptor; 
    496                 int msg = -1; 
    497 
    498                 if (unusual_dev->useProtocol != US_SC_DEVICE && 
    499                         us->subclass == idesc->bInterfaceSubClass) 
    500                         msg += 1; 
    501                 if (unusual_dev->useTransport != US_PR_DEVICE && 
    502                         us->protocol == idesc->bInterfaceProtocol) 
    503                         msg += 2; 
    504                 if (msg >= 0 && !(unusual_dev->flags & US_FL_NEED_OVERRIDE)) 
    505                         printk(KERN_NOTICE USB_STORAGE "This device " 
    506                                 "(%04x,%04x,%04x S %02x P %02x)" 
    507                                 " has %s in unusual_devs.h\n" 
    508                                 "   Please send a copy of this message to " 
    509                                 "<linux-usb-devel@lists.sourceforge.net>\n", 
    510                                 ddesc->idVendor, ddesc->idProduct, 
    511                                 ddesc->bcdDevice, 
    512                                 idesc->bInterfaceSubClass, 
    513                                 idesc->bInterfaceProtocol, 
    514                                 msgs[msg]); 
    515         } 
    516 
    517         // Read the device's string descriptors // 
    518         if (dev->descriptor.iManufacturer) 
    519                 usb_string(dev, dev->descriptor.iManufacturer, 
    520                            us->vendor, sizeof(us->vendor)); 
    521         if (dev->descriptor.iProduct) 
    522                 usb_string(dev, dev->descriptor.iProduct, 
    523                            us->product, sizeof(us->product)); 
    524         if (dev->descriptor.iSerialNumber) 
    525                 usb_string(dev, dev->descriptor.iSerialNumber, 
    526                            us->serial, sizeof(us->serial)); 
    527 
    528         // Use the unusual_dev strings if the device didn't provide them // 
    529         if (strlen(us->vendor) == 0) { 
    530                 if (unusual_dev->vendorName) 
    531                         strlcpy(us->vendor, unusual_dev->vendorName, 
    532                                 sizeof(us->vendor)); 
    533                 else 
    534                         strcpy(us->vendor, "Unknown"); 
    535         } 
    536         if (strlen(us->product) == 0) { 
    537                 if (unusual_dev->productName) 
    538                         strlcpy(us->product, unusual_dev->productName,   39
    539                                 sizeof(us->product)); 
    540                 else 
    541                         strcpy(us->product, "Unknown"); 
    542         } 
    543         if (strlen(us->serial) == 0) 
    544                 strcpy(us->serial, "None"); 
    545 
    546         US_DEBUGP("Vendor: %s,  Product: %s\n", us->vendor, us->product); 
    547 } 
// 469��,����˵,dev�����Ǹ� dev. 
// 470��,struct usb_interface_descriptor *idesc,���Ҳ������˵,֮ǰ�Ǹ�associate_dev������
// �Ѿ����ܹ�����ṹ��,�����������¾������һ��interface��,һ��interface�Ͷ�Ӧһ��interface��
// ����.���Բ��������￴��,���ܻ�����. 
// 472��, struct us_unusual_dev,����ṹ���ǵ�һ�γ���,��������drivers/usb/storage/usb.h��, 
 55 // 
     56//Unusual device list definitions 
     57  // 
     58 
     59 struct us_unusual_dev { 
     60         const char* vendorName; 
     61         const char* productName; 
     62         __u8  useProtocol; 
     63         __u8  useTransport; 
     64         int (*initFunction)(struct us_data *); 
     65         unsigned int flags; 
     66 }; 
// ���Ⱥ��ұߵ�us_unusal_dev_list��һ������,������drivers/usb/storage/usb.c: 
    157 // This is the list of devices we recognize, along with their flag data // 
    158 
    159 // The vendor name should be kept at eight characters or less, and 
    160//the product name should be kept at 16 characters or less. If a device 
    161//has the US_FL_FIX_INQUIRY flag, then the vendor and product names 
    162//normally generated by a device thorugh the INQUIRY response will be 
    163//taken from this list, and this is the reason for the above size 
    164//restriction. However, if the flag is not present, then you 
    165//are free to use as many characters as you like. 
    166  // 
    167 
    168 #undef UNUSUAL_DEV 
    169 #define UNUSUAL_DEV(idVendor, idProduct, bcdDeviceMin, bcdDeviceMax, \   40
    170                     vendor_name, product_name, use_protocol, use_transport, 
\ 
    171                     init_function, Flags) \ 
    172 { \ 
    173         .vendorName = vendor_name,      \ 
    174         .productName = product_name,    \ 
    175         .useProtocol = use_protocol,    \ 
    176         .useTransport = use_transport,  \ 
    177         .initFunction = init_function,  \ 
    178         .flags = Flags, \ 
    179 } 
    180 
    181 static struct us_unusual_dev us_unusual_dev_list[] = { 
    182 #       include "unusual_devs.h" 
    183 #       undef UNUSUAL_DEV 
    184         // Control/Bulk transport for all SubClass values // 
    185         { .useProtocol = US_SC_RBC, 
    186           .useTransport = US_PR_CB}, 
    187         { .useProtocol = US_SC_8020, 
    188           .useTransport = US_PR_CB}, 
    189         { .useProtocol = US_SC_QIC, 
    190           .useTransport = US_PR_CB}, 
    191         { .useProtocol = US_SC_UFI, 
    192           .useTransport = US_PR_CB}, 
    193         { .useProtocol = US_SC_8070, 
    194           .useTransport = US_PR_CB}, 
    195         { .useProtocol = US_SC_SCSI, 
    196           .useTransport = US_PR_CB}, 
    197 
    198         // Control/Bulk/Interrupt transport for all SubClass values // 
    199         { .useProtocol = US_SC_RBC, 
    200           .useTransport = US_PR_CBI}, 
    201         { .useProtocol = US_SC_8020, 
    202           .useTransport = US_PR_CBI}, 
    203         { .useProtocol = US_SC_QIC, 
    204           .useTransport = US_PR_CBI}, 
    205         { .useProtocol = US_SC_UFI, 
    206           .useTransport = US_PR_CBI}, 
    207         { .useProtocol = US_SC_8070, 
    208           .useTransport = US_PR_CBI}, 
    209         { .useProtocol = US_SC_SCSI, 
    210           .useTransport = US_PR_CBI}, 
    211 
    212         // Bulk-only transport for all SubClass values //   41
    213         { .useProtocol = US_SC_RBC, 
    214           .useTransport = US_PR_BULK}, 
    215         { .useProtocol = US_SC_8020, 
    216           .useTransport = US_PR_BULK}, 
    217         { .useProtocol = US_SC_QIC, 
    218           .useTransport = US_PR_BULK}, 
    219         { .useProtocol = US_SC_UFI, 
    220           .useTransport = US_PR_BULK}, 
    221         { .useProtocol = US_SC_8070, 
    222           .useTransport = US_PR_BULK}, 
    223 #if !defined(CONFIG_BLK_DEV_UB) 
&& !defined(CONFIG_BLK_DEV_UB_MODULE) 
    224         { .useProtocol = US_SC_SCSI, 
    225           .useTransport = US_PR_BULK}, 
    226 #endif 
    227 
    228         // Terminating entry // 
    229         { NULL } 
    230 }; 
// �޿��κλ���ȥ,������ʶ�����.������鿴��ȥ�ر�����Բ���?�����ǵõ������Ǽ������Ǹ�
// storage_usb_ids,��ϸ�Ա�һ�»ᷢ��,�����������Ԫ�ظ�����ȫһ��,ֻ����,һ������struct 
// usb_device_id�ṹ�幹�ɵ�,��һ������struct us_unusual_dev�ṹ�幹�ɵ�,��ʵ�����������һ
// һ��Ӧ��,����Ҳ��������ͬһ���ļ���. ϸ��һ���ע�⵽,UNUSUAL_DEV�����������ļ��ﱻ��
// ��������,���Ǹ����õ�?����ϸ��,�����������unusual_devs.h����ļ�,����ļ���������ʲô?��
// ��û������ļ�,��ôstorage_usb_ids���ű������USB_INTERFACE_INFO����궨���˼��ֳ���
// ��usb mass storage���豸,����, 
// { USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, US_SC_RBC, US_PR_CB) }, 
// ��һ�о��Ƕ���һ���豸��bInterfaceClass,bInterfaceSubClass,bInterfaceProtocol,Ҳ����˵
// һ��usb interfaceֻҪ�����������ص������ű��ﶨ����κ�һ��ƥ��,��ô�Ϳ��԰�����豸�������
// ����,���������������Ͼ�ֻ�ǹ涨��һЩ�����Ļ���˵������豸���ص�,���������usb mass 
// storage�豸�������,���Ӵ���,ʲô����.�������豸������������������������ȻҪ�����������
// ô��?����˵����豸��һ��,����ʽ����֮ǰ��Ҫ����һЩ��ʼ���Ĳ���,�����Լ��ṩһ����ʼ������,
// ����ô��?ΰ���Linux�ں˿�������Ϊ��׼����һ���ļ�,�����������usb mass storage�豸���һ�
// �������unusual_devs.h,������,�����ǲ�����Ϊ�Լ����豸����Linux�ں�֧�ֶ�������.��Ȼ���ǵ�
// U�̻����ϲ�������Щ�����豸,����Ϊһ���������ĵ��������������,�����б�ҪΪ����ļ�˵����. 
// ��������,���컹��Զ��?(��) 
// ���Ǵ�unusual_devs.h��,��㿴һ��,������߾��Ǻܶ�һ����UNUSUAL_DEV��,ÿһ�о�����ô
// һ����,������������Ӧһ���豸,���Ǵ�������һ������,������һ�����ǵİ�,��ȥ��Intel ��ʱ��,ǰ��
// �ǻ�˵,�����ǵ������Ƕ��Լ�̫������,�������������ô�����ǵ�����ռ�.˵����������ĩ,Intel ����
// ���flash��Ʒ�ļ۸�,��Nokia�����ͻ�������,�����ұ���,һ�������ǵ�С��˾���Ȱ�ĳ�����,û  42
// ������������һ��С��˾�ܹ�����Nokia,����,������,�����˵��;���������������������.����,����
// ����������,Nokia����������,��Intel,��flash��һ����ʧȥ��һ����Ҫ�Ŀͻ�,��CEOҲΪ�����̴�ְ
// ��.����������豸,�����������ǵ�һ��flash��Ʒ. 
//     711 // Submitted by Hartmut Wahl <hwahl@hwahl.de>// 
//     712 UNUSUAL_DEV( 0x0839, 0x000a, 0x0001, 0x0001, 
//     713                 "Samsung", 
//     714                 "Digimax 410", 
//     715                 US_SC_DEVICE, US_PR_DEVICE, NULL, 
// 716                 US_FL_FIX_INQUIRY),   
// Digimax 410,��Ϥ��������ĸ��Ƕ���Ŷ����ǵ����410������ 3 ����ѧ�佹�Ĳ�Ʒ����İ��,
// ��������������µúܿ�,���2002���Ƴ���������ȻҲ���Ǻ�һ����,�г������Ļ�Ҳ��1500��
// ��,������ʱ���Ƴ���ʱ��Ҳ��3000��4000Ԫ��.ok,����������һ����ʲô��˼. 
// UNUSUAL_DEV����걻���������,��Ȼ,#define��֮������һ��#define֮ǰ��һ��#undef,
// ������ظ�������.��storage_usb_ids֮ǰ,���Ķ����� 
    116 #define UNUSUAL_DEV(id_vendor, id_product, bcdDeviceMin, bcdDeviceMax, \ 
    117                     vendorName, productName,useProtocol, useTransport, \ 
    118                     initFunction, flags) \ 
    119 { USB_DEVICE_VER(id_vendor, id_product, bcdDeviceMin,bcdDeviceMax) } 
USB_DEVICE_VER�Ķ�����include/linux/usb.h��, 
    448 //* 
    449//USB_DEVICE_VER - macro used to describe a specific usb device with a 
version range 
    450//@vend: the 16 bit USB Vendor ID 
    451//@prod: the 16 bit USB Product ID 
    452//@lo: the bcdDevice_lo value 
    453//@hi: the bcdDevice_hi value 
    454//
    455//This macro is used to create a struct usb_device_id that matches a 
    456//specific device, with a version range. 
    457  // 
    458 #define USB_DEVICE_VER(vend,prod,lo,hi) \ 
    459         .match_flags = 
USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION, .idVendor = (vend), .idProduct = 
(prod), .bcdDevice_lo         = (lo), .bcdDevice_hi = (hi) 
//�����������ճ�����storage_usb_ids�е���˼������match_flags Ϊ 
USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION,idVendorΪ 0x0839,idProductΪ
0x000a,bcdDevice_loΪ0x0001,bcdDevice_hi Ϊ0x0001.   43
//����us_unusal_dev_list���ű�֮ǰ,UNUSUAL_DEV�ֱ�����Ϊ: 
    168 #undef UNUSUAL_DEV 
    169 #define UNUSUAL_DEV(idVendor, idProduct, bcdDeviceMin, bcdDeviceMax, \ 
    170                     vendor_name, product_name, use_protocol, use_transport, 
\ 
    171                     init_function, Flags) \ 
    172 { \ 
    173         .vendorName = vendor_name,      \ 
    174         .productName = product_name,    \ 
    175         .useProtocol = use_protocol,    \ 
    176         .useTransport = use_transport,  \ 
    177         .initFunction = init_function,  \ 
    178         .flags = Flags, \ 
    179 } 
// Ok.������������˼������vendorNameΪ"Samsung",��productNameΪ"Digimax 410",
// ��useProtocol ΪUS_SC_DEVICE, useTransportΪUS_PR_DEVICE,initFunctionΪNULL,flag
// ΪUS_FL_FIX_INQUIRY. 
// ����������?���Ȳ�ȥ�ܸ���ľ��庬��,�������ǿ�����,���ͬһ���ļ�,����ʹ�����ζ���
// UNUSUAL_DEV�����ķ���,�������������Ĳ�ͬԪ��,����֮,UNUSUAL_DEV����걾�������趨
// 10������,��storage_usb_ids����Ҫʹ�����е�ǰ4������,ͬʱus_unusual_dev_list����Ҫʹ��
// ���еĺ�6������,������unusual_devs.h�ж����һ��������������.����ע�⵽������
// storage_usb_ids���黹��us_unusual_dev_list,���ж�ͨ����ôһ�а�unusual_devs.h�ļ�����
// ���˽���.storage_usb_ids ��: 
    121 static struct usb_device_id storage_usb_ids [] = { 
    122 
    123 #       include "unusual_devs.h" 
    124 #undef UNUSUAL_DEV 
us_unusual_dev_list��: 
    181 static struct us_unusual_dev us_unusual_dev_list[] = { 
    182 #       include "unusual_devs.h" 
    183 #       undef UNUSUAL_DEV 
// ������֮����ʹ�����������ԭ����,storage_usb_ids���ṩ��usb core��,����Ҫ�Ƚ�driver��
// device�Ӷ�ȷ���豸�Ǳ����driver��֧�ֵ�,����ֻ��Ҫ�Ƚ�����Ϳ�����,��Ϊ�������Ѿ�����ȷ��
// һ���豸��,����,��Ʒ,���к�.�Ƚ���Щ�͹���,��us_unusual_dev_list��������е�Ԫ�������ǽ���
// ���Ĵ���Ҫ�õ�,��������ʲôЭ��,����ʲô��ʼ������,��������ʹ������������.��������Ҫע�����,
// ������������Ԫ�ص�˳����һ����,�������Ǵ�storage_usb_ids�еõ���id_index ����
// us_unusual_dev_listҲ�ǿ��Ե�,��ʾ�Ļ���ͬһ���豸.����Ҳ�������Ǹղ���get_device_info��
// ������.   44
472         struct us_unusual_dev *unusual_dev = &us_unusual_dev_list[id_index]; 
    473         struct usb_device_id *id = &storage_usb_ids[id_index]; 
// ����,unusual_dev ��id�͸�ȡ������.�������ǽ����õ�������ָ��.���Ҳ���. 
// �ܽ�´�,���������һ������Ϊ��������������д�����, 
// 1.               ���� match_flags,����ֵ��USB_DEVICE_ID_MATCH_DEVICE_AND_VERSION,��
// ��һ����,���͸���usb core,Ҫ�Ƚ�������������,idVendor,idProduct,bcdDevice_lo,bcdDevice_hi,
// ����idVendor�������vendorName�Ƕ�Ӧ��,��idProduct�������productName�Ƕ�Ӧ��,ҵ��
// Ϊÿ�ҹ�˾��һ����,�������ڹ���,�������ǵı�ž���0x0839,��ô���ǵĲ�Ʒ�оͻ������豸������
// ��idVendor ������0x0839.�������Լ���ÿ�ֲ�ƷҲ���и����,��Digimax 410��Ӧ�ı�ž���
// 0x000a,�� bcdDevice_lo��bcdDevice_hi ��ͬ���һ�������豸�ı��(device release 
// number),bcd����ζ���������Ƕ����Ƶĸ�ʽ. 
// 2.                vendorName��productName ������˵��, "Samsung"��"Digimax 410". 
// 3.                useProtocolΪUS_SC_DEVICE, useTransportΪUS_PR_DEVICE,���������˵����
// �������豸,������ʲôsubclass,��ʹ��ʲôͨ��Э��,�ô��豸���������ȥ��ȡ,����д���������.
// һ�����ǻῴ�����ǵĴ����л�����ж������. 
// 4.                initFunction����NULL,������������,������������豸�ĳ�ʼ������,һ����豸����
// ��Ҫ�������,������Щ�豸��ƫҪ��������,���͸�����,Ҫ���ҵ��豸���������һЩ��ʼ��,��������
// ����һ������,initFunction��Ȼ��һ������ָ��,���������ΪNULL�Ļ�,��ʱ��ͻᱻ����,�Ժ�����
// �ῴ�������ж����ָ��������ж�.���Ϊ�ղ����,����ͻ�ִ��.�������ǿ���������,���յ�������
// ��,�����ṩ��һ������init_8200e�ĳ�ʼ������, 
     63 UNUSUAL_DEV(  0x03f0, 0x0207, 0x0001, 0x0001, 
     64                 "HP", 
     65                 "CD-Writer+ 8200e", 
     66                 US_SC_8070, US_PR_SCM_ATAPI, init_8200e, 0), 
     67 
     68 UNUSUAL_DEV(  0x03f0, 0x0307, 0x0001, 0x0001, 
     69                 "HP", 
     70                 "CD-Writer+ CD-4e", 
     71                 US_SC_8070, US_PR_SCM_ATAPI, init_8200e, 0), 
// 5.                flag����US_FL_FIX_INQUIRY,���flag������Ϊ�ܶ�ֵ,���flag�Ĵ��ڱ���ͱ�ʾ��
// ���豸��Щ���ڲ�ͬ,��Ϊһ����豸�ǲ������flag��,�����flag�ͱ�������豸������ĳЩ�ط���Ҫ
// ��������Ĵ���,���Խ���ڴ��������ǻῴ��ͻȻ����һ��,�ж�us->flag����ĳ�����˲�,�������,��
// ִ��һЩ����,���������,�ǾͲ����κ�����.���flag�Ĵ���Ҳʹ�����ǿ��Է��㴦��һЩ�豸��bug,
// �����������豸������������?���ͻش����.���ǲ��������豸���ܾͻ�������ش�,���߻ش𱱾�����
// ���!���Ƕ��������豸,�������Ǿ���ҪһЩר�ŵĴ������Ը�.���嵽���US_FL_FIX_INQUIRY,��
// ��flag��ôһ����,�ͱ�������豸�ڽ��ܵ�INQUIRY �����ʱ�����һЩ�쳣������,�����Ժ����ǻ�  45
// �ڴ����￴����������δ�������.���������flag�ĵ�Ȼ��ֻ�����ǵ�������,����豸Ҳ�п�������
// ��. 
// 6.               ��Ȼ������unusual_devs.h������,��ô����Ȼ��һ������,���һ�������Ƴ���һ���µ�
// �豸,����һЩ�µ�����,��Ŀǰ���豸������������ȫ֧����,��ô����������Ҫ�������������
// unusual_devs.h�����һ��UNUSUAL_DEV�������Լ����豸,Ȼ���ٿ��Ƿ���Ҫ���ں˴򲹶��Լ�
// ��δ�.����⼸��unusual_devs.h����ļ��ĳ���Ҳ������������. 
// ��������,���컹��Զ��?(��) 
// �����ű�õ���������Ҫ�Ķ���,Ȼ������Ĵ������Χ����������ָ����չ����.(unusual_dev ��id) 
// 476��,��unusual_dev����¼��us���,����us���Ҳ����ôһ����Ա.������¼�����պ�Ҫ��������
// ������,��Ϊus�ǹᴩ�������µ�,���Է������ĳ�Ա�ܷ���,��ʱ������,����us_unusual_dev_list��
// ��storage_usb_ids�����ű����֮��Ͳ���������.��Ϊ�����Ѿ��õ���������Ҫ��,�������ǾͲ���
// ��ȥɧ��������������. 
// 477��483��,��us������������Ա��ֵ,subclass,protocol,flags.�������ǵ�U��,�����������豸,
// ��us_unusual_dev_list�б������ҵ���,��subclass ��US_SC_SCSI,��protocol ��Bulk-only,��
// �����ú�US_PR_BULK�������.(224 �к�225��.)����US_SC_DEVICE��US_PR_DEVICE ����
// ֮ǰ���Ǹ����ǵ����������ʱ���Ѿ�������,���ͱ�ʾsubclass��protocol�ô��豸����������߶���
// ��.�������������ܻ���,��Ϊ������ȫ���԰�subclass��protocol��UNUSUAL_DEV��д���,�α���
// ������ȥ���豸��������.Ȼ��,���ǿ�������,�������ĺô��Ƕ���һ��UNUSUAL_DEV���Դ�������
// ��,���������ü�����ͬsubclass���豸������ôһ����,���߼�����ͬprotocol���豸������ôһ����.
// ��ʡһ���ʡһ���,���������˿�Դ���������ڼ��Լ�ĸ���Ʒ��. ��Ҫ�ر�ָ������us->flags,����
// U����˵,����Ȼû��ʲôflags��Ҫ�趨,����unusual_devs.h�еĺܶ��豸�������˸���flags,�Ժ�
// �ڴ��������ǻῴ��,ʱ��ʱ���Ǿ͵��ж�һ���Ƿ�ĳ��flag������,ͨ�������������,��Ҫ��ִ��ĳ��
// ����,������ĳ��Ҫ��. 
// 490��515��,����һ�δ���ĵ��Դ���,���������usb û���κ������.��δ�����
// unusual_devs.h,���Ƿ�����ļ�������һ��û������ľ���.ʲô��û������?���Ǹղſ�����,�����
// ���豸����US_SC_DEVICE,��ô��subclass�����������ж�����,�����Ȼ,����
// subclass=unusual_dev->useProtocol,���������������ĺ����������������һ��,��ô����豸
// ��û�б�Ҫ���Լ���useProtocol������unusual_devs.h����,��Ϊ����Ҳ���Դ��������������.����
// ��ʹ���һ����ΪUS_SC_DEVICE����.�ͱ������������������д���һ��Sony��Memory Stick��
// Ʒ�Ĵ���: 
    371 UNUSUAL_DEV(  0x054c, 0x0069, 0x0000, 0x9999, 
    372                 "Sony", 
    373                 "Memorystick MSC-U03", 
    374                 US_SC_UFI, US_PR_CB, NULL, 
    375                 US_FL_SINGLE_LUN ),   46
// ���ǿ�����useProtocol ��һ����д��US_SC_UFI,��������Գ�������UFI���subclass��,������
// �����Ǵ�������������߶�����Ҳ�����,�Ǿ�û�б�Ҫע����������,����ֱ��д��US_SC_DEVICE��
// ��.��Ȼ,�ܵ���˵��δ�����Щɵ.д�������ϣ���ܹ����õĹ���unusual_devs.h,ϣ������Ҫ���ϵ�
// ����,����ϣ���ܹ�������ļ���ɾ��һЩ��,���Ҽ�ʹ����ɾ��һ��,Ҳϣ��ÿһ�ж�����ȥ����һ��,��
// ����ļ�����ȥ����С������,���Ӿ���.���������ݵ�����,��Ϣ������.��������Ҳֻ�ܶ����������Ķ�
// һ������. 
// 518��526��,���������һ������usb core�ĺ���,usb_string,��������������ǻ��һ���豸����
// ����������.��?��ô������һ�������ַ����������Ķ���?֮ǰ����ֻ����������������?û��,�豸����
// ��,����������,�ӿ�������,�˵�������,����ÿ���豸���е�,������Щ�������ǿ��п��޵�,�ַ�������
// ��������ôһ�����,�е��豸��,�е��豸û��.�ֱ���,hub,������һ��hub������,�⵱Ȼ��һ�����
// ��û�е�.��ô�ַ����������Ǹ������?��Щ����ģ��һЩҲδ������һ������,����̫͸���˲�֪����
// �п�.�����һ��Ҫ֪���Ļ�,�ٸ�����,�ҵĻ�����ܶ�usb�豸,��һ����lspci ���Ƶ�����,���Բ鿴һ
// ��,����������lsusb.��Ҳ������һ��,��װһ�������usbutils,Ȼ��Ϳ���ʹ���������.���ǿ�: 
localhost:~/test # lsusb 
Bus 004 Device 003: ID 0ea0:1001 Ours Technology, Inc. 
Bus 004 Device 002: ID 04b4:6560 Cypress Semiconductor Corp. CY7C65640 USB-2.0 
"TetraHub" 
Bus 004 Device 001: ID 0000:0000 
Bus 003 Device 001: ID 0000:0000 
Bus 002 Device 002: ID 0624:0294 Avocent Corp. 
Bus 002 Device 001: ID 0000:0000 
Bus 001 Device 001: ID 0000:0000 
// ������ڶ���, Cypress Semiconductor Corp., ��ôһ�����Ķ���,��˵������?�ǲ���Ӧ�ô��豸����?
// �豸���Ǽ�����׼������,�����������Ĵ�СҲ��һ���ŵ�����ôһ����,����,һЩ�豸ר��׼����һЩ��
// ����������(string descriptor).����������Щ�����Ķ���,���ǽ�ϸղŵ�518�п�ʼ��,����豸����
// �����iManufacturer��Ϊ0,��ô����usb_string,��仰��������ʲô?���Ǹ���iManufactuer ��ֵ
// �õ���˾����,��iManufactuer�ĵ�һ����ĸi,�ͱ�ʾindex,����¼���������Ĺ�˾���ֱ�������һ����
// ������������,��Ϊ�ַ��������������ж��,��ô��Ȼ���и�����������,����������,iProduct��¼�˲�
// Ʒ���ڵڼ����ַ�����������,iSerialNumber��¼�˲�Ʒ���к��ڵڼ����ַ���������,Ȼ�����
// usb_string�������,�Ͱ��������ַ�����������Ķ�������¼������.���ǿ���,�������ε��õ�ʱ���
// �𴫵���us->vendor,us->product,us->serial.�����������ý���֮��,����������ͼ�¼�˱�Ҫ����
// Ϣ,�����Ժ����ǾͿ�������. 
// �õ���us->vendor,us->product,us->serial,��ô����528ֱ��547 �оͲ���Ҫ�ི��,����˵���
// �õ��Ķ����ǿյ�,(�õ����ǿտ��������ֿ���,һ�����豸������û�ṩ��Щ�ַ���������,��һ�����
// ��usb_string����û�ܳɹ�,��������������ɹ�Ҳ����ν,ûӰ��.)��Ҳû��ϵ,�Ͼ���Щ��Ϣ���ǿ���
// ����,�޷��Ǵ�ӡ�������ͻ�����.���unusual_dev����еĻ�,�ǾͿ�������,���Ҳû��,��û�취,��
// ΪUnknown.�����к������������ΪNone����,��� US_DEBUGP����Щ��Ϣ����ӡ����,������
// ����debug����,��ô�������־�ļ��￴����ôһ�仰,��/var/log/messages���.   47
// ����,get_device_info��������ͽ���������ʹ��.��usb storage�ⲿϷ��,�������ٳ���.������˵,
// ����usb storage������ģ����˵,������ǲ���Ҫ,ÿ���������ǻ����ϵ�һĨɫ��.��������ÿһ����,
// ��Ҳ�Ǳ��������е����,�������Լ�������������? 
// ��������,���컹��Զ��(��) 
// ������get_device_info,���Ǽ�������storage_probe һ��һ������ȥ.Ϊ�˱���ԭ֭ԭζ,����������
// ��ԭ����һ��������ÿһ�ж�������.get_device_info��962��,�����Ѿ�����,���������963�п�ʼ
// ��. 
    963 
    964 #ifdef CONFIG_USB_STORAGE_SDDR09 
    965         if (us->protocol == US_PR_EUSB_SDDR09 || 
    966                         us->protocol == US_PR_DPCM_USB) { 
    967                 // set the configuration -- STALL is an acceptable response here // 
    968                 if (us->pusb_dev->actconfig->desc.bConfigurationValue != 1) { 
    969                         US_DEBUGP("active config #%d != 1 ??\n", us->pusb_dev 
    970                                 ->actconfig->desc.bConfigurationValue); 
    971                         goto BadDevice; 
    972                 } 
    973                 result = usb_reset_configuration(us->pusb_dev); 
    974 
    975                 US_DEBUGP("Result of usb_reset_configuration is %d\n", result); 
    976                 if (result == -EPIPE) { 
    977                         US_DEBUGP("-- stall on control interface\n"); 
    978                 } else if (result != 0) { 
    979                         // it's not a stall, but another error -- time to bail // 
    980                         US_DEBUGP("-- Unknown error.  Rejecting device\n"); 
    981                         goto BadDevice; 
    982                 } 
    983         } 
    984 #endif 
//������δ���,��Ц��.��Ϊ#ifdef CONFIG_USB_STORAGE_SDDR09˵����δ���������޹�.����
//��Щ����ѡ������ǰ����Ȼ���,�����и����������ѡ�������ĳ�������Ʒ��,������������Ĳ�Ʒ,��
//��ĳЩ���������Լ���Ҫ��,����������������Ĵ���.���嵽���ѡ��,���ǿ�һ��
//drivers/usb/storage/Kconfig�ļ�,����ļ���߽����˸�Ŀ¼��ÿһ������ѡ�������. 
     99 config USB_STORAGE_SDDR09 
    100         bool "SanDisk SDDR-09 (and other SmartMedia) support (EXPERIMENTAL)" 
    101         depends on USB_STORAGE && EXPERIMENTAL 
    102         help 
    103           Say Y here to include additional code to support the Sandisk SDDR-09 
    104           SmartMedia reader in the USB Mass Storage driver.   48
    105           Also works for the Microtech Zio! SmartMedia reader. 
// ���Կ���,���Ҫ֧��Sandisk SDDR-09 SmartMedia�Ķ�����,����ʹ��������ѡ���.Sandisk
// �ǹ�˾��,��������˶���ҹ�˾����İ��,���������ɵ�,����һ��ȫ�������������ݴ洢��Ʒ��Ӧ��.
// ��SmartMedia(���SM)��ͨ���������������,Ҳ��һ�ȱ�����MP3 ��,��Ҳ��һ��flash memory
// �洢��.������������Ϻ�����SM����,��Ϊ������Բ���.�����õñȽ϶��Ӧ����CF��(Compact 
// Flash)��.�����������������ѿ���ߵ����ݶ�����,ʹ��USB�ӿ�,��ԭ����������U ��Ҳ�ǲ��. (˳
// �����һ��,U�̺ʹ洢���������,����������U�̣����ǿ���ֱ�Ӷ�д�Ĵ洢��,���洢����Ҫ�ⲿ�豸
// ���ܽ��з���,���ֻ������濨,������������濨�Ⱦ�ֻ��һ�ſ�,���Բ���ֱ�Ӷ�����з���,�����Ҫ
// һ�ֽ�"������"���ⲿ�豸����ʶ��,�洢���ж���,��XD��CF��SD��SM�ȵ�,��Щ����������"���һ"
// �Ĺ���,���ԶԲ�ͬ�����濨���ж�д.��������δ������Լ��������Ĵ�����ÿһ���������뿪����Ȼ��
// Ӧ����һ�ֶ�����.�������ڲ�ͬ�ĳ��̵Ĳ�ͬ�Ĳ�Ʒ.) 
// ����,���������ǰ���ᵽ������������.get_transport,get_protocol,get_pipes.һ����������������
// ��,���Ǿͽ����뱾���µĸ߳�����.������֮ǰ,����ֻ��һ��һ������.�����⼸��������Ȼ����,������
// �����õ���Ϣֻ��һ���,���Կ��Ժܿ�Ŀ���. 
    985 
    986         // Get the transport, protocol, and pipe settings // 
    987         result = get_transport(us); 
    988         if (result) 
    989                 goto BadDevice; 
    990         result = get_protocol(us); 
    991         if (result) 
    992                 goto BadDevice; 
    993         result = get_pipes(us); 
    994         if (result) 
    995                 goto BadDevice; 
//��һ��,get_transport(us), 
    549 // Get the transport settings // 
    550 static int get_transport(struct us_data *us) 
    551 { 
    552         switch (us->protocol) { 
    553         case US_PR_CB: 
    554                 us->transport_name = "Control/Bulk"; 
    555                 us->transport = usb_stor_CB_transport; 
    556                 us->transport_reset = usb_stor_CB_reset; 
    557                 us->max_lun = 7; 
    558                 break; 
    559 
    560         case US_PR_CBI: 
    561                 us->transport_name = "Control/Bulk/Interrupt"; 
    562                 us->transport = usb_stor_CBI_transport;   49
    563                 us->transport_reset = usb_stor_CB_reset; 
    564                 us->max_lun = 7; 
    565                 break; 
    566 
    567         case US_PR_BULK: 
    568                 us->transport_name = "Bulk"; 
    569                 us->transport = usb_stor_Bulk_transport; 
    570                 us->transport_reset = usb_stor_Bulk_reset; 
    571                 break; 
    572 
    573 #ifdef CONFIG_USB_STORAGE_HP8200e 
    574         case US_PR_SCM_ATAPI: 
    575                 us->transport_name = "SCM/ATAPI"; 
    576                 us->transport = hp8200e_transport; 
    577                 us->transport_reset = usb_stor_CB_reset; 
    578                 us->max_lun = 1; 
    579                 break; 
    580 #endif 
    581 
    582 #ifdef CONFIG_USB_STORAGE_SDDR09 
    583         case US_PR_EUSB_SDDR09: 
    584                 us->transport_name = "EUSB/SDDR09"; 
    585                 us->transport = sddr09_transport; 
    586                 us->transport_reset = usb_stor_CB_reset; 
587                 us->max_lun = 0; 
    588                 break; 
    589 #endif 
    590 
    591 #ifdef CONFIG_USB_STORAGE_SDDR55 
    592         case US_PR_SDDR55: 
    593                 us->transport_name = "SDDR55"; 
    594                 us->transport = sddr55_transport; 
    595                 us->transport_reset = sddr55_reset; 
    596                 us->max_lun = 0; 
    597                 break; 
    598 #endif 
    599 
    600 #ifdef CONFIG_USB_STORAGE_DPCM 
    601         case US_PR_DPCM_USB: 
    602                 us->transport_name = "Control/Bulk-EUSB/SDDR09"; 
    603                 us->transport = dpcm_transport; 
    604                 us->transport_reset = usb_stor_CB_reset; 
    605                 us->max_lun = 1; 
    606                 break;   50
    607 #endif 
    608 
    609 #ifdef CONFIG_USB_STORAGE_FREECOM 
    610         case US_PR_FREECOM: 
    611                 us->transport_name = "Freecom"; 
    612                 us->transport = freecom_transport; 
    613                 us->transport_reset = usb_stor_freecom_reset; 
    614                 us->max_lun = 0; 
    615                 break; 
    616 #endif 
    617 
    618 #ifdef CONFIG_USB_STORAGE_DATAFAB 
    619         case US_PR_DATAFAB: 
    620                 us->transport_name  = "Datafab Bulk-Only"; 
    621                 us->transport = datafab_transport; 
    622                 us->transport_reset = usb_stor_Bulk_reset; 
    623                 us->max_lun = 1; 
    624                 break; 
    625 #endif 
    626 
627 #ifdef CONFIG_USB_STORAGE_JUMPSHOT 
    628         case US_PR_JUMPSHOT: 
    629                 us->transport_name  = "Lexar Jumpshot Control/Bulk"; 
    630                 us->transport = jumpshot_transport; 
    631                 us->transport_reset = usb_stor_Bulk_reset; 
    632                 us->max_lun = 1; 
    633                 break; 
    634 #endif 
    635 
    636         default: 
    637                 return -EIO; 
    638         } 
    639         US_DEBUGP("Transport: %s\n", us->transport_name); 
    640 
    641         // fix for single-lun devices // 
    642         if (us->flags & US_FL_SINGLE_LUN) 
    643                 us->max_lun = 0; 
    644         return 0; 
645 } 
// զһ��,��ô��һ��,�ó�ɳ����,��з�����ͷ�����ߡ���(��)����һ��.(��ɳ�����ڡ��͡��š�һ����)��
// ��������һ��,��֪����,��Ҫ����һ��switch,ѡ�����,�﷨����˵�ܼ�,̷��ǿ��������߽��ܵĺ�
// ���.�������ǿ�����δ��벻��,ֻ��,����˵����,��Ȼ��������һ��ѡ����,���ǲ�ͬѡ�����ζ�ź�
// ���������»���ǧ�����Ľ��,�����ѡ����������ϵ�ϻƽ�,����ζ��������չ��߷�;ѡ�����첫��,  51
// ����ζ�ŷ�������ĸ���.����,�˴�,������Ҫ��ϸ�Ŀ�������Ǿ���ѡ��������һ��·.����Ȼ,ǰ������
// �Ѿ�˵��,����U��,spec�涨��,��������Bulk-only�Ĵ��䷽ʽ,������us->protocol ����
// US_PR_BULK.�������Ǹո���get_device_info��ȷ��������.����,������switch������,������ִ��
// ��ֻ��US_PR_BULK��һ��,��, 
// us��transport_name����ֵΪ��Bulk��,transport����ֵΪ
// usb_stor_Bulk_transport,transport_reset����ֵΪusb_stor_Bulk_reset.������������Ҫ��ס��
// ��,us�ĳ�Աtransport ��transport_reset����������ָ��.����Ա�ǰ������������.��������ֵ����
// ��Ҫ�μ�,�պ����Ƕ����õ����ǵ�,��Ϊ�������������������ݴ����ʱ����õĶ���.����
// usb_stor_Bulk_*������������,���ǵ�ʱ�������������.����ֻ��֪��,�պ�����һ����ع��������
// ��ֵ��. 
// 573�е�634 ��,���ö�˵��,�����ȫ��������ض���Ʒ��ص�һЩ���뿪��,������Щ�Լ�����һ
// Щ���亯��,��Щ������Щͨ�õĺ���. 
// 641��,�ж�us->flags,���ǵ������ڽ�unusual_devs.h�ļ���ʱ��˵���Ǹ�flags��,�����һ��
// ������.��Щ�豸������US_FL_SINGLE_LUN��ôһ��flag,�ͱ�������ֻ��һ��LUN��.���������豸
// ͦ���,����unusual_devs.h��ץһ������: 
    338 UNUSUAL_DEV(  0x054c, 0x002d, 0x0100, 0x0100, 
    339                 "Sony", 
    340                 "Memorystick MSAC-US1", 
    341                 US_SC_DEVICE, US_PR_DEVICE, NULL, 
    342                 US_FL_SINGLE_LUN ), 
// �������Sony��Memorystick.�������м����,��С�͸����ƿ������Ƶ�,Ҳ��һ�ִ洢оƬ,��Sony
// ��˾�Ƴ���,�㷺����Sony�ĸ��������Ʒ��.�����������,������Ӱ��. 
// ��������,ɶ��LUN��?logical unit number.ͨ����̸��scsi �豸��ʱ�򲻿ɱ����Ҫ˵��LUN.����
// LUN,������ʱ,һλ����Novell(SUSE)�Ĳ��뿪��Linux�ں���usb��ϵͳ�Ĺ���ʦ��������˵,һ��
// lun����һ��device�е�һ��drive.����֮,usb������ lun��Ŀ������,������˵,��Щ�����������ж�
// �����,�����������,����һ��֧��CF��,��һ��֧��SD��,��ô�������Ҫ���������������Ķ���,
// �͵�����lun��ôһ����.����߼���Ԫ.����Ȼ,��U�������򵥵��豸��LUN��Ȼ��һ��.��ʱ��,���ǳ�
// ��U����һ����������һ��LUN,����˵���ܶ�Сѧ���꼶���µ������ǿ��Խ��ܵ�,������Ϊһ��������,
// ��Ӧ����ô���. 
// ֪����LUN�Ժ�,��Ȼ�Ϳ���֪��US_FL_SINGLE_LUN�Ǹ�����,���flag�����������,ֱ���˵���
// ������,������豸ֻ��һ��LUN,����֧�ֶ��LUN.�� max_lun����ʲô��˼?us�еĳ�Աmax_lun
// ����һ���豸��֧�ֵ�����lun��.�����һ���豸֧���ĸ�LUNs,��ô���ĸ�LUN�ı�ž���
// 0,1,2,3,��max_lun����3.���һ���豸����֧�ֶ��LUN,��ô����max_lun����0.��������
// max_lun������Ϊ��0. 
// ����һ����Ҫע��ĵط���,�Ƚ�һ�¸���case���,����, US_PR_BULK�ͱ��case��һ��,���case
// ���涼������us->max_lun,����Ӧ��Bulk-OnlyЭ������case,��û������us->max_lun,����Ϊ
// ��?��,�������ǻ�ר����һ������ȥ��ȡ���ֵ��,֮���Բ���,����Ϊ���ֵ���豸˵����,�������豸  52
// ��ѯ,����Bulk-OnlyЭ��涨��.��������֮�������usb_stor_Bulk_max_lun()����,���������ȡ
// ���max lun.������ȻҪ����һ��,�������������U����ûɶ�����,�������ֵ�϶���0. 
// ����,get_transport()Ҳ������,��get_device_infoһ��.����Ŀǰ����������Щ���������ò������ʵ,
// ��������˵,��л�����յĽ��,ʢ��ֻ��һ������...����������˵,Ҫ�����յ�,��ô����Щ������·���,
// �ղ�������.Ȼ��,�����ⲿ�ִ����ж�ô��Ҫ,Ҳ����������������;�ó���,��ȥ�Ҵҵ�ת��վ,����ͣ��
// ���,ʼ��Ҫ��ȥ����һ���. 
// ��������,���컹��Զ��?(��) 
// �������쳾�����߲����˼����ԹԹ. 
// ������get_transport()������get_protocol()��get_pipes().��Ȼ������
drivers/usb/storage/usb.c ��: 
    647 // Get the protocol settings // 
    648 static int get_protocol(struct us_data *us) 
    649 { 
    650         switch (us->subclass) { 
    651         case US_SC_RBC: 
    652                 us->protocol_name = "Reduced Block Commands (RBC)"; 
    653                 us->proto_handler = usb_stor_transparent_scsi_command; 
    654                 break; 
    655 
    656         case US_SC_8020: 
    657                 us->protocol_name = "8020i"; 
    658                 us->proto_handler = usb_stor_ATAPI_command; 
    659                 us->max_lun = 0; 
    660                 break; 
    661 
    662         case US_SC_QIC: 
    663                 us->protocol_name = "QIC-157"; 
    664                 us->proto_handler = usb_stor_qic157_command; 
    665                 us->max_lun = 0; 
    666                 break; 
    667 
    668         case US_SC_8070: 
    669                 us->protocol_name = "8070i"; 
    670                 us->proto_handler = usb_stor_ATAPI_command; 
    671                 us->max_lun = 0; 
    672                 break; 
    673 
    674         case US_SC_SCSI: 
    675                 us->protocol_name = "Transparent SCSI";   53
    676                 us->proto_handler = usb_stor_transparent_scsi_command; 
    677                 break; 
    678 
    679         case US_SC_UFI: 
    680                 us->protocol_name = "Uniform Floppy Interface (UFI)"; 
    681                 us->proto_handler = usb_stor_ufi_command; 
    682                 break; 
    683 
    684 #ifdef CONFIG_USB_STORAGE_ISD200 
    685         case US_SC_ISD200: 
    686                 us->protocol_name = "ISD200 ATA/ATAPI"; 
687                 us->proto_handler = isd200_ata_command; 
    688                 break; 
    689 #endif 
    690 
    691         default: 
    692                 return -EIO; 
    693         } 
    694         US_DEBUGP("Protocol: %s\n", us->protocol_name); 
    695         return 0; 
    696 } 
// ��δ���ǳ���ǳ���׶�.�����ż�ʹȥ���Ϻ���վ������Щ���ڳ��ĸ��Ƕ�,����Ҳ�ܸ�������δ���
// ����ʲô.��һ����,����us->subclass���ж�.����U����˵,spec��߹涨��,����subclass��
// US_SC_SCSI,��������������丳ֵ���.һ������us ��protocol_nameΪ"Transparent SCSI",��
// һ������us ��proto_handlerΪusb_stor_transparent_scsi_command.��������һ������ָ��,��
// ���պ�ؽ����ɱ���������������,���Ҳ���. 
// Ȼ����get_pipes().drivers/usb/storage/usb.c: 
    698 // Get the pipe settings // 
    699 static int get_pipes(struct us_data *us) 
    700 { 
    701         struct usb_host_interface *altsetting = 
    702                 us->pusb_intf->cur_altsetting; 
    703         int i; 
    704         struct usb_endpoint_descriptor *ep; 
    705         struct usb_endpoint_descriptor *ep_in = NULL; 
    706         struct usb_endpoint_descriptor *ep_out = NULL; 
    707         struct usb_endpoint_descriptor *ep_int = NULL; 
    708 
    709         // 
    710        //Find the endpoints we need. 
    711        //We are expecting a minimum of 2 endpoints - in and out (bulk). 
    712        //An optional interrupt is OK (necessary for CBI protocol). 
    713        //We will ignore any others.   54
    714          // 
    715         for (i = 0; i < altsetting->desc.bNumEndpoints; i++) { 
    716                 ep = &altsetting->endpoint[i].desc; 
    717 
    718                 // Is it a BULK endpoint? // 
    719                 if ((ep->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) 
    720                                 == USB_ENDPOINT_XFER_BULK) { 
    721                         // BULK in or out? // 
    722                         if (ep->bEndpointAddress & USB_DIR_IN) 
    723                                 ep_in = ep; 
    724                         else 
    725                                 ep_out = ep; 
    726                 } 
    727 
    728                 // Is it an interrupt endpoint? // 
    729                 else if ((ep->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) 
    730                                 == USB_ENDPOINT_XFER_INT) { 
    731                         ep_int = ep; 
    732                 } 
    733         } 
    734 
    735         if (!ep_in || !ep_out || (us->protocol == US_PR_CBI && !ep_int)) { 
    736                 US_DEBUGP("Endpoint sanity check failed! Rejecting dev.\n"); 
    737                 return -EIO; 
    738         } 
739 
    740         // Calculate and store the pipe values // 
    741         us->send_ctrl_pipe = usb_sndctrlpipe(us->pusb_dev, 0); 
    742         us->recv_ctrl_pipe = usb_rcvctrlpipe(us->pusb_dev, 0); 
    743         us->send_bulk_pipe = usb_sndbulkpipe(us->pusb_dev, 
    744                 ep_out->bEndpointAddress & USB_ENDPOINT_NUMBER_MASK); 
    745         us->recv_bulk_pipe = usb_rcvbulkpipe(us->pusb_dev, 
    746                 ep_in->bEndpointAddress & USB_ENDPOINT_NUMBER_MASK); 
    747         if (ep_int) { 
    748                 us->recv_intr_pipe = usb_rcvintpipe(us->pusb_dev, 
    749                         ep_int->bEndpointAddress & 
USB_ENDPOINT_NUMBER_MASK); 
    750                 us->ep_bInterval = ep_int->bInterval; 
    751         } 
    752         return 0; 
    753 } 
// �������Ӧ�ÿ���˵�������⼸�����ĵĺ��������һ����,����Ҳ�������˵��ӵ�һ��.������
// ������������.702��,us->pusb_intf,�ɻ��ǵ�,��associate_dev�и���ֵ,�粻�ǵ���ع�ȥ��һ��.  55
// û��,us->pusb_intf�������ǹ������ʼһ���ᵽ���Ǹ�interface(ָ��).�����ĳ�Ա
// cur_altsetting,���ǵ�ǰ��setting,����˵����.�ڽ�associate_dev��ʱ��Ҳ�Ѿ�������,��һ��
// struct usb_host_interface �Ľṹ��ָ��.������������һ��ָ����ʱ����һ��, altsetting.����������
// �����ĳ�Ա,desc�� endpoint.�ع�struct usb_host_interface,���Կ���,����������Ա,struct 
// usb_interface_descriptor desc,��struct usb_host_endpoint *endpoint.����,desc���ö�˵,����
// ���interface�Ľӿ�������,��endpoint���ָ���¼���Ǽ���endpoint,�������������ʽ���洢,
// ��endpointָ������ͷ.��Щ����������usb coreö�ٵ�ʱ������ú���,����������κ���,ֻ������
// �þ�����.�������struct usb_host_endpoint�Ķ���,����include/linux/usb.h: 
     43 // host-side wrapper for parsed endpoint descriptors // 
     44 struct usb_host_endpoint { 
     45         struct usb_endpoint_descriptor  desc; 
     46 
     47         unsigned char *extra;   // Extra descriptors // 
     48         int extralen; 
     49 }; 
//   ���Ŷ����˼���struct usb_endpoint_descriptor�Ľṹ��ָ��.����˼��,����Ƕ�Ӧendpoint��
// ��������.�䶨��������include/linux/usb_ch9.h: 
     260 // USB_DT_ENDPOINT: Endpoint descriptor // 
    261 struct usb_endpoint_descriptor { 
    262         __u8  bLength; 
    263         __u8  bDescriptorType; 
    264 
    265         __u8  bEndpointAddress; 
    266         __u8  bmAttributes; 
    267         __u16 wMaxPacketSize; 
    268         __u8  bInterval; 
    269 
    270         // NOTE:  these two are _only_ in audio endpoints. 
    271         // use USB_DT_ENDPOINT*_SIZE in bLength, not sizeof. 
    272         __u8  bRefresh; 
    273         __u8  bSynchAddress; 
274 } __attribute__ ((packed)); 
// ����,�Ĵ�������һһ����,�ڼ�����֮ǰ,��������С��һ��:����ʲô��������?ÿ��USB�豸����
// ���Ĵ�������,����������U����˵.��˵��Flash Memory��?Intel,����,��Щ������Flash Memory��,
// ��Ȼͨ�����Ǿͼ��Flash. Flash ��U���а���ʲô��ɫ?Flash���������û��洢���ݵ�,��U���е�
// Flash���൱��PC���е�Ӳ��,�洢������Ҫ�Ϳ���.��ô���˸��û��洢��������,�豸�Լ�����Ҫ�洢
// һЩ�豸������еĶ���,�����豸������˭?˭������?����һЩ��Ϣ,������豸�м�������,�м�����
// ��,�ȵ��������,��Щ������ô��?������ѧ97�繤�Ĵ����֮һ,����Intel����ʦ��ʦ��������������
// ˵:���������,����Flash memory��,����һ�����˽���EEPROM,Ҳ�������洢��,����EEPROM��
// ǰ��, ��Flash�ǻ���EEPROM������չ������һ�ֵͳɱ���ROM ��Ʒ. EEPROM�� Flash��ͬ,����
// ��Ҫ�����,��EEPROM���԰��ֽڲ���,������Flash����һ�β���һ��block,������ֻ��Ķ�������  56
// �ݵ������ʹ��EEPROM�ͺܷ�����.���EEPROM����һ����,���ĵ�·Ҫ����Щ,���ɶȲ���,һ��bit
// ��Ҫ��������,һ��������������Ϣ,һ���䵱����.����EEPROM�ĳɱ���,Flash����һЩ��·,�ɱ�
// �����˺ܶ�.���,ͨ��,USB�豸���,����һ��FlashоƬ,����һ��EEPROMоƬ,Flash���ͻ��洢��
// ��,��EEPROM�����洢�豸�������Ϣ.�����Ϊʲô�����ǰ�FlashоƬ����Motorola֮��,�ͻ���
// �����ֻ�������Ħ����������������Intel,��Ϊ������Ȼ����Flash��ʱ������ǵĳ���IDд����Flash
// ��,�������յĳ�Ʒ��������,�ṩ����Ϣ��������EEPROM,���Ե����USB�豸ͨ��USB�ӿ�������
// ����ȥ,��ô�������������ʾ����,��ôһ�������յİ�װ����,��������������ǿ�Flash�ĳ���.��
// EEPROM���дʲô?��ʲô��ʽд?������usb spec�涨��,���ָ�ʽ����һ�������������ĸ�ʽ.�豸
// ������,����������,�ӿ�������,�˵�������,�Լ�����һЩĳһЩ�����豸���е�������,����hub����
// ��.��Щ�������Ǻܹ淶��,������������ֱ�׼��������,ÿ��usb�豸���ǹ��ؾص�֧�ֵ�,����usb 
// core�������һ����ͬ�Ĵ�������Ƕ���������,���������������豸��������ȥ�Լ�����,�����Ȩ����
// �еĺô�,������Ҷ�Ҫ��������,�ɴ�����ͷһ�����˺���,�������쵼���Ǻð�! 
// 715��733��,ѭ��, bNumEndpoints���ǽӿ��������еĳ�Ա,��ʾ����ӿ��ж��ٸ��˵�,������
// ���в�����0�Ŷ˵�,0�Ŷ˵����κ�һ��usb�豸���������ṩ��,����˵�ר�����ڽ��п��ƴ���,����
// ��һ�����ƶ˵�.����Ϊ���,���Լ�ʹһ���豸û�н����κ�����,usb ����Ҳ���Կ�ʼ��������һЩͨ��,
// ��Ϊ��ʹ��֪�������Ķ˵�,������֪����һ����һ��0�Ŷ˵�,����˵һ�����ƶ˵�.����,ͨ��usb mass 
// storage��������bulk�˵�,����bulk����,����ν����������.�����ճ��Ķ�дU������ļ�,��������
// ��������,���Ժ�������,����mass storage�豸��˵,bulk������������Ҫ������ʽ,����ܼ�,����ʹ
// ��U�̾���������д�ļ���,˭û������ȥ����������������������������,�Դ�ҩ��?����Щ��������
// ���޷Ǿ���Ϊ�˰�����������ʵ�ֶ�д�ļ��Ĺ���,�����ÿһ��usb �洢�豸������ʹ��. 
// �������������ѭ�������ڸ���, altsetting->endpoint[i].desc,����struct usb_host_endpoint
// ����ṹ��Ķ���,��֪,desc����һ��struct usb_endpoint_descriptor�ı���.���Ǹոն������ĸ�
// ���ֽṹ���ָ��,ep,ep_in,ep_out,ep_int,�ܼ�,����������¼�˵���������,ep_in����
// bulk-in,ep_out����bulk-out,ep_int���ڼ�¼�ж϶˵�(����еĻ�).��ep,ֻ��һ����ʱָ��. 
// ���ǿ�struct usb_endpoint_descriptor,���ĳ�Ա��, bmAttributes��ʾ����,�ܹ�8λ,����bit1
// ��bit0��ͬ��ΪTransfer Type,����������,��00��ʾ����,01��ʾ��ʱ,10��ʾ����,11��ʾ�ж�.��
// 719�����ǿ���, USB_ENDPOINT_XFERTYPE_MASK����궨����include/linux/usb_ch9.h��: 
    286 #define USB_ENDPOINT_XFERTYPE_MASK      0x03    // in bmAttributes // 
    287 #define USB_ENDPOINT_XFER_CONTROL       0 
    288 #define USB_ENDPOINT_XFER_ISOC          1 
    289 #define USB_ENDPOINT_XFER_BULK          2 
    290 #define USB_ENDPOINT_XFER_INT           3 
// ��һ��C���Ե��˾Ͳ������,719�о����ж�����˵��������������ǲ���һ��Bulk�˵�,�����,
// �����Ƚ�,�����ȿ�bEndpointAddress,���struct usb_endpoint_descriptor�е���һ����Ա,Ҳ��8
// ��bit,����˵1�� byte,����bit7��ʾ��������˵�ķ���,0��ʾOUT,1��ʾIN,OUT��IN�Ƕ�����
// ����.OUT���Ǵ��������豸,IN���Ǵ��豸������.����USB_DIR_IN ��Ȼ����
include/linux/usb_ch9.h 
     25 // 
     26//USB directions   57
     27//
     28//This bit flag is used in endpoint descriptors bEndpointAddress field. 
     29//Its also one of three fields in control requests bRequestType. 
     30  // 
     31 #define USB_DIR_OUT                     0               // to device // 
     32 #define USB_DIR_IN                      0x80            // to host // 
// ����������˼������,����Ϊ����ep_in�� ep_outָ���ָ��endpoint descriptor. 
// 729�Ͳ�����˵��,����⻹�������Ļ�,���Կ���ȥ�����ľ�����ҵ��ǿ������ϵ���ɱ��,��ϧ���
// ѧУ�ﲻ�ϸ㽨��,����ȿ����Ѿ�����������.729��һ��else if�����þ����������˵����ж϶˵�,
// ��ô����ep_intָ����.����˵��,ÿһ��usb�������ж��ٶ˵��к��ֶ˵㶼�ǲ�ȷ����,�������ظ���
// �豸�Ĺ淶,��usb mass storage�Ĺ淶˵��,һ��usb mass storage �豸����Ӧ��������bulk�˵�,
// ����֮��,�Ǹ����ƶ˵���Ȼ�Ǳ����,��ӹ����,����,���ܻ���һ���ж϶˵�,�����豸֧��CBIЭ��,��
// Control/Bulk/InterruptЭ��.����Ҳ˵����,U�����ص��� Bulk-onlyЭ��,������Ҫ���ж϶˵�. 
// 735��738��δ���,ûɶ��˵��,�����ж��Ƿ�ep_in����ep_out������,����������CBIЭ�鵫
// ��û���ж϶˵�,��Щ���ǲ������,��Ȼ�ͻ���톪! 
// ʣ��һС�δ���,�����½��ٿ�.��Ҫ˵����,�����������֮�����ǽ���ʼ��ʵĲ���,������ΰ��
// ��usb_stor_acquire_resources().�ڰ�������ȥ,�����Ѿ���������·.�����ǹ�ͬ�ڴ���.ͬʱ,����С
// ��һ��,��ǰ���ǻ��˺ܴ��ƪ����Ϊusb_stor_acquire_resources()���̵�,���������ع�һ��,����
// ������Щ����? 
// �������Ǵ�storage_probe ����,һ���������������,������
// assocaite_dev,get_device_info,get_transport,get_protocol,get_pipes.������������Ŀ����ʲô?
// �ܼ�,����Ϊ�˽���һ�����ݽṹ,�����Ǵ�˵�е�struct us_data,�������ֽ���us.���ǰ�����������
// ��,Ϊ���������ڴ�,Ϊ���ĸ���Ԫ�ظ���ֵ,Ŀ�ľ���Ϊ�����Ժ����ǿ��Ժܺõ�������.�������������
// ��,��һ��Ҳ��д.�ѵ������ȥ����struct us_data,������������ݽṹ��д�����ͬ־��ר��Ϊ
// usb-storageģ�����Ƶ�.������Ի��,��ν���,�޷Ǿ������ݽṹ�����㷨.û��,���������
// drivers/usb/storage/usb.h�е����ݽṹ����60��,����������Ϸ������.�������ĳ�Ա,���ǻ��кܶ�
// û����,������,�����������.����,��Ȼget_pipes����һС��û��,�������ǿ�����ǰ����5������˵
// �ټ���,ϯĽ��˵��,�����ò�����,ҲҪ�úõ�˵���ټ�,ҲҪ���������һ�ݸ�л,лл������һ�ݼ���. 
// ͨ������Ĺܵ� 
// 1990��,����ս��,��̨�ﱨ���������,����Ա˵:��λ��������,���������˽ض��˿����ص��������ѹ�
// ��.(���͹ܵ�) 
// ��ʱ,������������������. 
// һ���,��Ԫ1991��,һ��������д��һ������Linux�Ĳ���ϵͳ,��Ҳ������λ����Ա����Ȥ,��������
// ���Ǵ����˻���.����Ϊ�˼����������Ŀ���,�����������Linux�������˹ܵ���ôһ������,��������
// �ܵ����ںܶ�ط�,�ļ�ϵͳ��,�豸������,���Ǻ������ǿ�����Linux�����˸��ָ����Ĺܵ�,����,û��  58
// ���͹ܵ�,��û�����ѹܵ�.������ͬ����,���еĹܵ������������䶫����,ֻ������Щ�ܵ��������ʵʵ
// ���ڵ�����,����Щ�ܵ������������. 
// ����������usb�����п����Ĺܵ�����������������,����ͨ��. ͨ����˫����,��������������԰�.����
// usb��ͨ����,һ���϶�������,��host,��һ����ʲô?���豸��?�����ٲ����µ�������,�����˵���豸,
// �����˵�������豸����ͨ��.����,����,�����Ѿ�����,�����Ѿ�����,������һ������ȼ�յ�������,��
// Ӧ��˵�ø�ȷ��һ��.��������������ͨ�ŵ����豸�ڵĶ˵�.���ڶ˵�,����Ҳ����רҵһ��˵,��Ӳ����
// ��������ʵʵ���ڴ��ڵ�,����ʵ��Ϊһ��FIFO,֧�ֶ��ٸ��˵��ǽӿ�оƬ��һ����Ҫָ��.���Ӹ�����
// ��˵,�˵���������usb�豸֮��ͨ�������յ�.�������豸���Խ��в�ͬ�����ͨ��,����˵���ݴ���,��
// ��,�豸������usb������,usb����Ϊ�˷ֱ�ÿһ���豸,��ÿһ���豸���Ϻ�,Ȼ��Ϊ��ʵ�ֶ���ͨ��,��
// ���������ṩ�˶˵�,�˵����,��ȻҲҪ���Ϻ�,�����������պͶ˵�ȥ��ϵ. 
// ³Ѹ����˵�ú�,���ϱ�û�йܵ�,�˵����,Ҳ�����˹ܵ�. 
// ��仰˵���൱��,�ǳ��е���,������,Ϭ��!û��,����֪��,usb��������,�����ֹܵ�,���Ƕ�Ӧusb����
// �е����ִ��䷽ʽ,���ƴ����Ӧ���ƹܵ�,�жϴ����Ӧ�жϹܵ�,���������Ӧ�����ܵ�,��ʱ�����Ӧ
// ��ʱ�ܵ�.ÿһ��usb�����е��豸Ҫ��usb����������,�͵���������Ĺܵ�.���ܵ��ĳ���,����Ϊ����
// ���Ƿֱ�˵�,����˵���Ӷ˵�.�ǵ������Ʋ�������������˵��,������˵�֮����������Ӿͳ�Ϊ�ܵ�. 
// ����˵,������ѧ,��һ����У��,Ҳ����˵�ǽ�ѧ��,(��ȻҲ����һЩʵ����),�Ͽ�ʲô�Ķ���ȥ��ѧ��,��
// ��ѧ����������,��ô������Ե���,�����кܶ�ѧ������¥,����¥����,�͸�ÿ��¥���Ϻ�,����1��¥,2
// ��¥,...,36��¥,..,ÿ��¥��һ���豸,����˵�����Ա���������һ�װ���������(��Ȼ,�϶��Ǽٵ�,Ҳ��
// һ���ٵ�����),�����˼Ҹ����ݹ���,�˼�������ס��?��˵��ס������ѧ,�������ֻ˵���ڸ�����ѧ,
// ��ô�Ϳ���Ǹ��ǿ����ȵøϵ�������ѧ����,����ѧ��������������,Ȼ���˼ҿ϶��͵���,�����Ĵ�¥��
// �䷿?������˵����36��¥201,��,��ô��201��ôһ��������,�Ͷ�Ӧ�˵��,������������Ҫ����ľ�
// �Ƕ˵�201,����������36��¥,�԰�,�����˼�Ҫ���͵�36 ��¥�¾Ͱ����׸��ӵ�������϶��ø�����.
// ��ô�����������,������У��������,ÿ������¥��һ���豸,��ס���Ǽ��������˵�.��ôpipe
// ��?pipe��������ʵ�е�ĳһʵ���Ӧ,����˵���Ǹ�������ͨ�������ĳ��·,��Ӧ�ð���ķ�ʽ���.��
// �����ܶණ��,����԰���������ݵĻ��������������ű�ǩ,����������д���ջ��˵ĵ�ַ,�������ٺ�¥
// ���ٺŷ�,��usb����,�����豸�źͶ˵��,֪������������,�������ȷ������Ŀ�ĵ�,��usb��������֪
// ������ͨ�ŵ����ĸ��˵�.��pipe���˰���������������,����������һЩ��Ϣ,������������ͨ�ŵķ���,
// Ҳ����˵,���ܴ����ű�ǩ�ϵ�֪36��¥201������ռ����ػ��Ǽļ���,��Ȼ��ʵ�в���Ҫд��,��Ϊ��
// ��Ա�϶�֪�������ռ���,��û�²Ų���ͼļ�����ϵ��.�ٱ���,pipe�ﻹ������pipe������,��������
// �Ǵ����ڵݹ���,��ô��ô�ݾ͵ÿ���,��ݹ�˾�϶��ṩ��ͬ���͵ķ���,�еĿ��е���,�еĿ��ܻ��б�
// ��ʲô��,���������Ǯ,����ѡ��ͬ�ķ�������,ͬ��pipeҲ���,��Ϊusb�豸�Ķ˵��в�ͬ������,
// ����pipe��Ͱ�����һ���ֶ�����¼��һ��,����ֶγ�Ϊpipe type.��,������������ʵ�ʵ�pipe ��. 
//   ������Щ��,ͷһ�������ǳ�����usb_sndctrlpipe,������include/linux/usb.h��,�����Ȱ���һ�Ѷ�
// ����صĴ�����г���. 
   1104 static inline unsigned int __create_pipe(struct usb_device *dev, unsigned int 
endpoint) 
   1105 { 
   1106         return (dev->devnum << 8) | (endpoint << 15); 
   1107 }   59
   1108 
   1109 // Create various pipes... // 
   1110 #define usb_sndctrlpipe(dev,endpoint)   ((PIPE_CONTROL << 30) | 
__create_pipe(dev,endpoint)) 
   1111 #define usb_rcvctrlpipe(dev,endpoint)   ((PIPE_CONTROL << 30) | 
__create_pipe(dev,endpoint) | USB_DIR_IN) 
   1112 #define usb_sndisocpipe(dev,endpoint)   ((PIPE_ISOCHRONOUS << 30) | 
__create_pipe(dev,endpoint)) 
   1113 #define usb_rcvisocpipe(dev,endpoint)   ((PIPE_ISOCHRONOUS << 30) | 
__create_pipe(dev,endpoint) | USB_DIR_IN) 
   1114 #define usb_sndbulkpipe(dev,endpoint)   ((PIPE_BULK << 30) | 
__create_pipe(dev,endpoint)) 
   1115 #define usb_rcvbulkpipe(dev,endpoint)   ((PIPE_BULK << 30) | 
__create_pipe(dev,endpoint) | USB_DIR_IN) 
   1116 #define usb_sndintpipe(dev,endpoint)    ((PIPE_INTERRUPT << 30) | 
__create_pipe(dev,endpoint)) 
   1117 #define usb_rcvintpipe(dev,endpoint)    ((PIPE_INTERRUPT << 30) | 
__create_pipe(dev,endpoint) | USB_DIR_IN) 
  �ȿ�1110��,�������չ��,PIPE_CONTROLҲ�Ǻ�,Ҳ�Ƕ�����ͬһ�ļ���,include/linux/usb.h, 
   1040 // -------------------------------------------------------------------------- // 
   1041 
   1042 // 
   1043//Calling this entity a "pipe" is glorifying it. A USB pipe 
   1044//is something embarrassingly simple: it basically consists 
   1045//of the following information: 
   1046// - device number (7 bits) 
   1047// - endpoint number (4 bits) 
   1048// - current Data0/1 state (1 bit) [Historical; now gone] 
   1049// - direction (1 bit) 
   1050// - speed (1 bit) [Historical and specific to USB 1.1; now gone.] 
   1051// - max packet size (2 bits: 8, 16, 32 or 64) [Historical; now gone.] 
   1052// - pipe type (2 bits: control, interrupt, bulk, isochronous) 
   1053//
   1054//Thats 18 bits. Really. Nothing more. And the USB people have 
   1055//documented these eighteen bits as some kind of glorious 
   1056//virtual data structure. 
   1057//
   1058//Let's not fall in that trap. We'll just encode it as a simple 
   1059//unsigned int. The encoding is: 
   1060//
   1061// - max size:         bits 0-1        [Historical; now gone.] 
   1062// - direction:        bit 7           (0 = Host-to-Device [Out], 
   1063//                                      1 = Device-to-Host [In] ... 
   1064//                                     like endpoint bEndpointAddress)   60
   1065// - device:           bits 8-14       ... bit positions known to uhci-hcd 
   1066// - endpoint:         bits 15-18      ... bit positions known to uhci-hcd 
   1067// - Data0/1:          bit 19          [Historical; now gone. ] 
   1068// - lowspeed:         bit 26          [Historical; now gone. ] 
   1069// - pipe type:        bits 30-31      (00 = isochronous, 01 = interrupt, 
   1070//                                      10 = control, 11 = bulk) 
   1071//
   1072//Why? Because its arbitrary, and whatever encoding we select is really 
   1073//up to us. This one happens to share a lot of bit positions with the UHCI 
   1074//specification, so that much of the uhci driver can just mask the bits 
   1075//appropriately. 
   1076  // 
   1077 
   1078 // NOTE:  these are not the standard USB_ENDPOINT_XFER_* values!! // 
   1079 #define PIPE_ISOCHRONOUS                0 
   1080 #define PIPE_INTERRUPT                  1 
   1081 #define PIPE_CONTROL                    2 
   1082 #define PIPE_BULK                       3 
//   ����֪��usb�����ִ��䷽ʽ,��ʱ����,�жϴ���,���ƴ���,��������.һ���豸��֧�������ִ����е�
// ��һ�ֻ����ļ������豸���������,��Ӳ����Ƶ�ʱ���ȷ����,����һ�������u ��,���϶���֧��
// Bulk�����Control �����.��ͬ�Ĵ���Ҫ���в�ͬ�Ķ˵�,���Զ���u����˵,��һ������Bulk�˵��
// Control �˵�,���Ǿ͵�ʹ����Ӧ��pipe������ͬ�Ķ˵���ϵ.���������ǿ������ĸ���,��
// ��,PIPE_ISOCHRONOUS���Ǳ�־��ʱͨ��,PIPE_INTERRUPT�����ж�ͨ��,PIPE_CONTROL����
// ����ͨ��,PIPE_BULK����BULKͨ��. 
//   ����__create_pipeҲ��һ����,���������Ķ�����Կ�����Ϊ����һ�����ṩ���豸�źͶ˵��.����
// ����ʹ��һ��unsigned int���͵ı���������һ��pipe,����8~14λ���豸��,��devnum,15~18λ
// �Ƕ˵��,��endpoint.�����ǻ���������ôһ����,USB_DIR_IN,����������pipe�����־���ݴ��䷽
// ���,һ���ܵ�Ҫô��ֻ������Ҫô��ֻ�����,������Ʋ��ɼ��Ҳ.��include/linux/usb_ch9.h����
// ��: 
     24 
     25 // 
     26//USB directions 
     27//
     28//This bit flag is used in endpoint descriptors bEndpointAddress field. 
     29//Its also one of three fields in control requests bRequestType. 
     30  // 
     31 #define USB_DIR_OUT                     0               // to device // 
//      32 #define USB_DIR_IN                      0x80            // to host // 
//   ��pipe����,��7λ(bit 7)�Ǳ��������.��������0x80Ҳ����˵�� bit 7Ϊ1,��ͱ�ʾ���䷽����
// ���豸��������,Ҳ������ν��in,�������һλ��0,�ͱ�ʾ���䷽�������������豸��,Ҳ������ν��out.
// ��������ΪUSB_DIR_OUT��0,��USB_DIR_IN ��1,�������ǿ�������ܵ���ʱ��ֻ���õ���
// USB_DIR_IN,��û���õ�USB_DIR_OUT,��Ϊ����0,�κ�����0���û������.   61
//   ����,���Ǿ�֪����,get_pipes������741,742�о���Ϊus�Ŀ�������Ϳ�������ܵ�����ֵ,�ܵ���
// �����,������һ������,�Ǿ��ǿ��ƶ˵�,���ƶ˵���˫���,������36��¥201����˵�ȿ����������
// ����,Ҳ�����Ǳ��˸���Ķ�������Ϊ�ռ��˵�ַ.��usb �淶�涨��,ÿһ��usb�豸���ٵ���һ������
// �˵�,��˵��Ϊ0.�����˵���û�еÿ������豸����,������˵��Ƿ�֮�ĺ�����׼��,��������ʲô��
// ��,ֻҪ����usb�������ϵ�,����͵�������ôһ�����,û������.�������ǿ���741,742���ﴫ�ݵ�
// endpoint����ֵΪ0.��Ȼ�乹��������ܵ����Ƕ�Ӧ���0�ſ��ƶ˵��.������������,���ǹ���bulk
// �ܵ����жϹܵ�(������ж϶˵�Ļ�). 
//   ����bulk�˵���ж϶˵�(����еĻ�),�����ǵĶ˵�������������ôһ���ֶ�,bEndpointAddress,
// ����ֶι���λ,������������ͦ����Ϣ��,��������˵�������˵㻹������˵�,��������˵�ĵ�
// ַ,(����ö�ٵ�ʱ����������),�Լ�����˵�Ķ˵��,����Ҫȡ�����Ķ˵�ŵ���һ������
// USB_ENDPOINT_NUMBER_MASK,��bEndpointAddress��USB_ENDPOINT_NUMBER_MASK��
// ����ܵõ����Ķ˵��.(�ͺñ�һ�ݲ�ͷʫ,��ð����ض��ķ������ܶ�����,�������ض��ķ������Ǻ�
// USB_ENDPOINT_NUMBER_MASK����������������.) 
//   750��,�����ж϶˵�,������ʹ�ö˵��������е�bInterval �ֶ�,��ʾ�˵���ж�������ʱ��. 
//   ����,get_pipes����������,��Ϣ�����浽��us����.����us�÷�������������.�ص�storage_probe()
// ����,998��,��us��Ϊ�������ݸ���usb_stor_acquire_resources()����.������������ǹ��µĸ߳�.
// ÿһ����ʶ֮ʿ�ڿ����������֮��ͻ��Ȼ����,����п�,һ���ӾͿ����˴���,�����˹���,ԭ��
// Linux�е��豸�������������ô�����İ�! 
996 
    997         // Acquire all the other resources and add the host // 
    998         result = usb_stor_acquire_resources(us); 
    999         if (result) 
   1000                 goto BadDevice; 
   1001         result = scsi_add_host(us->host, &intf->dev); 
   1002         if (result) { 
   1003                 printk(KERN_WARNING USB_STORAGE 
   1004                         "Unable to add the scsi host\n"); 
   1005                 goto BadDevice; 
   1006         } 
//��������usb_stor_acquire_resources����.����������drivers/usb/storage/usb.c ��: 
755 // Initialize all the dynamic resources we need // 
    756 static int usb_stor_acquire_resources(struct us_data *us) 
    757 { 
    758         int p; 
    759 
    760         us->current_urb = usb_alloc_urb(0, GFP_KERNEL); 
    761         if (!us->current_urb) { 
    762                 US_DEBUGP("URB allocation failed\n"); 
    763                 return -ENOMEM;   62
    764         } 
    765 
    766         // Lock the device while we carry out the next two operations // 
    767         down(&us->dev_semaphore); 
    768 
    769         // For bulk-only devices, determine the max LUN value // 
    770         if (us->protocol == US_PR_BULK) { 
    771                 p = usb_stor_Bulk_max_lun(us); 
    772                 if (p < 0) { 
    773                         up(&us->dev_semaphore); 
    774                         return p; 
    775                 } 
    776                 us->max_lun = p; 
    777         } 
    778 
    779         // Just before we start our control thread, initialize 
    780        //the device if it needs initialization // 
    781         if (us->unusual_dev->initFunction) 
    782                 us->unusual_dev->initFunction(us); 
    783 
    784         up(&us->dev_semaphore); 
    785 
    786         // 
    787        //Since this is a new device, we need to register a SCSI 
    788        //host definition with the higher SCSI layers. 
    789          // 
    790         us->host = scsi_host_alloc(&usb_stor_host_template, sizeof(us)); 
    791         if (!us->host) { 
    792                 printk(KERN_WARNING USB_STORAGE 
    793                         "Unable to allocate the scsi host\n"); 
    794                 return -EBUSY; 
    795         } 
    796 
    797         // Set the hostdata to prepare for scanning // 
    798         us->host->hostdata[0] = (unsigned long) us; 
    799 
    800         // Start up our control thread // 
    801         p = kernel_thread(usb_stor_control_thread, us, CLONE_VM); 
    802         if (p < 0) { 
    803                 printk(KERN_WARNING USB_STORAGE 
    804                        "Unable to start control thread\n"); 
    805                 return p; 
    806         } 
    807         us->pid = p;   63
    808 
    809         // Wait for the thread to start // 
    810         wait_for_completion(&(us->notify)); 
    811 
    812         return 0; 
    813 } 
// ����ɽ������ʱ,���ڴ���Ц.һ�����Ըߵ���Ӧ��һ�۾��ܴ�����������ҳ������ڴ���Ц�Ĵ�����,
// û��,������801��,kernel_thread,���������������ľ����Linux�ں�ģ��,������Ϊ���Ĵ�
// ��,Linux��ĳЩ�豸��������ı�д��÷ǳ���.����˵,��ĳЩ�豸����������˵,kernel_thread��
// ��������driver�����,����˵�Ǹ�Linux�ں�ģ������.���������صĶ�ô��,����������е�ө���,
// ����������,�����ĳ���.���������ŵ�˵,���ںܶ�ģ����˵,ֻҪ�ҵ�kernel_thread��һ��,���������
// ֪�����ģ������ô��������. 
// ��˵�е� URB 
// ������,��ôд������д��ô�ð�?����û�갡?��ˮ��ʱ��?�˺޺�ʱ��? 
// ��ȷ,һ·����,��Ҷ�������,����Ȼ�Ѿ��ߵ�����,����������Ҳֻ���Ǽ����ȥ.ʮ��֮ǰ,�Ҳ���ʶ
// ��,�㲻������,��ʮ��֮������Ȼ�ǵ���һ��(1997��),�ҵ�һ����ѧУ�ѵ���һ��:����ǰ���ǵ�����
// ��������Ԩ,��(��)����һ����ǰ,���޷���,�Ϲ�����,��������.����˽����F��,��ҵ�ڳ�ɳ��һ��. 
// usb_stor_acquire_resources,������������,��ȡ��Դ.ʲô��Դ?����Ϊ����ǽͷ�Ⱥ��ӵ����Ѳ���
// ��ʾ����һЩ����,֮ǰ����������һ����ڴ�����?д��usb�豸����������ô��ô�鷳��?����ר��Ϊ
// usb mass storage�豸׼����һ��struct us_data��ôһ���ṹ������?����˵�����Ѿ����߳�����? 
// ����˵�ú�,�һ�����·��.û��,�������Ϊ�����������Ѿ���usb�豸�������������㹻����ʶ,��
// Ϊ�������Ĵ����Ѿ�û�б�Ҫ�ٷ�����,��ô,��ֻ��˵,�ϵ۴�������ļƻ���,δ�ذ���ʹ���дusb��
// ����������. 
//   ��ȷ,��usb_stor_acquire_resources�Ĵ��벻��,ÿһ�ж���ÿһ�еĹ���.��������ֻ�����е�
// һ�д���,û��,����һ�д���,��Ϊ������Ҫ¡���Ƴ�һ������,һ���쵱��������,�����Ǵ�˵�е�urb,ȫ
// ��usb request block.usb�豸��Ҫͨ��,Ҫ��������,����Ҫʹ��urb,ȷ�е�˵,Ӧ����usb�豸������
// ��ʹ��urb.ʵ����,��Ϊusb�豸����,����������ֱ�Ӳ������ݵĴ���,��usb������԰��,����豸
// ��Զ�������,�����ĺ���ֻ��usb core,������������ȵ���usb host controller,�����ͨ����������
// usb����������оƬ,��ٲȻ��usb���԰�еĴ�ܼ�.�豸����Ҫ������Ϣ,����Ҫ�����ǽ���һ��urb��
// �ݽṹ,����������ݽṹ�������Ĳ�,�����Ĳ��Ϊ�����豸ͳһ��ɵ���,���豸���ύ��urb֮����Ҫ
// ����,ֻ�ǵȴ�,�ȴ�,����������ҹ�еȴ�.��,����������. 
// 760��,һ����ֵ���,�Ⱥ����,us->current_urb,�Ⱥ��ұ�,usb_alloc_urb����������.���˵
// struct us_data��usb mass storage�е�����,��ôstruct urb����������ĳ�Ϊ����usb��ϵͳ��
// ������. Linux�����е�usb�豸����,����ȻҲ����Ҫʹ��urb.��ôurb��������ʲô����?������ܽ��
// �����ô��ȶ�����,�����������־���ǰ��޹����Ը���?��include/linux/usb.h�����ҵ���������:   64
614 //* 
//    615//struct urb - USB Request Block 
//    616//@urb_list: For use by current owner of the URB. 
//    617//@pipe: Holds endpoint number, direction, type, and more. 
//    618//     Create these values with the eight macros available; 
//    619//     usb_{snd,rcv}TYPEpipe(dev,endpoint), where the TYPE is "ctrl" 
//    620//     (control), "bulk", "int" (interrupt), or "iso" (isochronous). 
//    621//     For example usb_sndbulkpipe() or usb_rcvintpipe().  Endpoint 
//    622//     numbers range from zero to fifteen.  Note that "in" endpoint two 
//    623//     is a different endpoint (and pipe) from "out" endpoint two. 
//    624//     The current configuration controls the existence, type, and 
//    625//     maximum packet size of any given endpoint. 
//    626//@dev: Identifies the USB device to perform the request. 
//    627//@status: This is read in non-iso completion functions to get the 
//    628//     status of the particular request.  ISO requests only use it 
//    629//     to tell whether the URB was unlinked; detailed status for 
//    630//     each frame is in the fields of the iso_frame-desc. 
//    631//@transfer_flags: A variety of flags may be used to affect how URB 
//    632//     submission, unlinking, or operation are handled.  Different 
//    633//     kinds of URB can use different flags. 
//    634//@transfer_buffer:  This identifies the buffer to (or from) which 
//    635//     the I/O request will be performed (unless URB_NO_TRANSFER_DMA_MAP 
//    636//     is set).  This buffer must be suitable for DMA; allocate it with 
//    637//     kmalloc() or equivalent.  For transfers to "in" endpoints, contents 
//    638//     of this buffer will be modified.  This buffer is used for the data 
//    639//     stage of control transfers. 
//    640//@transfer_dma: When transfer_flags includes URB_NO_TRANSFER_DMA_MAP, 
//    641//     the device driver is saying that it provided this DMA address, 
//    642//     which the host controller driver should use in preference to the 
//    643//     transfer_buffer. 
//    644//@transfer_buffer_length: How big is transfer_buffer.  The transfer may 
//    645//     be broken up into chunks according to the current maximum packet 
//    646//     size for the endpoint, which is a function of the configuration 
//    647//     and is encoded in the pipe.  When the length is zero, neither 
//    648//     transfer_buffer nor transfer_dma is used. 
//    649//@actual_length: This is read in non-iso completion functions, and 
//    650//     it tells how many bytes (out of transfer_buffer_length) were 
//    651//     transferred.  It will normally be the same as requested, unless 
//    652//     either an error was reported or a short read was performed. 
//    653//     The URB_SHORT_NOT_OK transfer flag may be used to make such 
//    654//     short reads be reported as errors. 
//    655//@setup_packet: Only used for control transfers, this points to eight bytes 
//    656//     of setup data.  Control transfers always start by sending this data 
//    657//     to the device.  Then transfer_buffer is read or written, if needed.   65
//    658//@setup_dma: For control transfers with URB_NO_SETUP_DMA_MAP set, the 
//    659//     device driver has provided this DMA address for the setup packet. 
//    660//     The host controller driver should use this in preference to 
//    661//     setup_packet. 
//    662//@start_frame: Returns the initial frame for isochronous transfers. 
//    663//@number_of_packets: Lists the number of ISO transfer buffers. 
//    664//@interval: Specifies the polling interval for interrupt or isochronous 
//    665//     transfers.  The units are frames (milliseconds) for for full and low 
//    666//     speed devices, and microframes (1/8 millisecond) for highspeed ones. 
//    667//@error_count: Returns the number of ISO transfers that reported errors. 
//    668//@context: For use in completion functions.  This normally points to 
//    669//     request-specific driver context. 
//    670//@complete: Completion handler. This URB is passed as the parameter to the 
//    671//     completion function.  The completion function may then do what 
//    672//     it likes with the URB, including resubmitting or freeing it. 
//    673//@iso_frame_desc: Used to provide arrays of ISO transfer buffers and to 
//    674//     collect the transfer status for each buffer. 
//    675//
//    676//This structure identifies USB transfer requests.  URBs must be allocated by 
//    677//calling usb_alloc_urb() and freed with a call to usb_free_urb(). 
//    678//Initialization may be done using various usb_fill_*_urb() functions.  URBs 
//    679//are submitted using usb_submit_urb(), and pending requests may be canceled 
//    680//using usb_unlink_urb() or usb_kill_urb(). 
//    681//
//    682//Data Transfer Buffers: 
//    683//
//    684//Normally drivers provide I/O buffers allocated with kmalloc() or otherwise 
//    685//taken from the general page pool.  That is provided by transfer_buffer 
//    686//(control requests also use setup_packet), and host controller drivers 
//    687//perform a dma mapping (and unmapping) for each buffer transferred.  Those 
//    688//mapping operations can be expensive on some platforms (perhaps using a dma 
//    689//bounce buffer or talking to an IOMMU), 
//    690//although theyre cheap on commodity x86 and ppc hardware. 
//    691//
//    692//Alternatively, drivers may pass the URB_NO_xxx_DMA_MAP transfer flags, 
//    693//which tell the host controller driver that no such mapping is needed since 
//    694//the device driver is DMA-aware.  For example, a device driver might 
//    695//allocate a DMA buffer with usb_buffer_alloc() or call usb_buffer_map(). 
//    696//When these transfer flags are provided, host controller drivers will 
//    697//attempt to use the dma addresses found in the transfer_dma and/or 
//    698//setup_dma fields rather than determining a dma address themselves.  (Note 
//    699//that transfer_buffer and setup_packet must still be set because not all 
//    700//host controllers use DMA, nor do virtual root hubs). 
//    701//  66
//    702//Initialization: 
//    703//
//    704//All URBs submitted must initialize the dev, pipe, transfer_flags (may be 
//    705//zero), and complete fields. 
//    706//The URB_ASYNC_UNLINK transfer flag affects later invocations of 
//    707//the usb_unlink_urb() routine.  Note: Failure to set URB_ASYNC_UNLINK 
//    708//with usb_unlink_urb() is deprecated.  For synchronous unlinks use 
//    709//usb_kill_urb() instead. 
//    710//
//    711//All URBs must also initialize 
//    712//transfer_buffer and transfer_buffer_length.  They may provide the 
//    713//URB_SHORT_NOT_OK transfer flag, indicating that short reads are 
//    714//to be treated as errors; that flag is invalid for write requests. 
//    715//
//    716//Bulk URBs may 
//    717//use the URB_ZERO_PACKET transfer flag, indicating that bulk OUT transfers 
//    718//should always terminate with a short packet, even if it means adding an 
//    719//extra zero length packet. 
//    720//
//    721//Control URBs must provide a setup_packet.  The setup_packet and 
//    722//transfer_buffer may each be mapped for DMA or not, independently of 
//    723//the other.  The transfer_flags bits URB_NO_TRANSFER_DMA_MAP and 
//    724//URB_NO_SETUP_DMA_MAP indicate which buffers have already been mapped. 
//    725//URB_NO_SETUP_DMA_MAP is ignored for non-control URBs. 
//    726//
//    727//Interrupt URBs must provide an interval, saying how often (in milliseconds 
//    728//or, for highspeed devices, 125 microsecond units) 
//    729//to poll for transfers.  After the URB has been submitted, the interval 
//    730//field reflects how the transfer was actually scheduled. 
//    731//The polling interval may be more frequent than requested. 
//    732//For example, some controllers have a maximum interval of 32 microseconds, 
//    733//while others support intervals of up to 1024 microseconds. 
//    734//Isochronous URBs also have transfer intervals.  (Note that for isochronous 
//    735//endpoints, as well as high speed interrupt endpoints, the encoding of 
//    736//the transfer interval in the endpoint descriptor is logarithmic. 
//    737//Device drivers must convert that value to linear units themselves.) 
//    738//
//    739//Isochronous URBs normally use the URB_ISO_ASAP transfer flag, telling 
//    740//the host controller to schedule the transfer as soon as bandwidth 
//    741//utilization allows, and then set start_frame to reflect the actual frame 
//    742//selected during submission.  Otherwise drivers must specify the start_frame 
//    743//and handle the case where the transfer cant begin then.  However, drivers 
//    744//wont know how bandwidth is currently allocated, and while they can 
//    745//find the current frame using usb_get_current_frame_number () they can't   67
//    746//know the range for that frame number.  (Ranges for frame counter values 
//    747//are HC-specific, and can go from 256 to 65536 frames from "now".) 
//    748//
//    749//Isochronous URBs have a different data transfer model, in part because 
//    750//the quality of service is only "best effort".  Callers provide specially 
//    751//allocated URBs, with number_of_packets worth of iso_frame_desc structures 
//    752//at the end.  Each such packet is an individual ISO transfer.  Isochronous 
//    753//URBs are normally queued, submitted by drivers to arrange that 
//    754//transfers are at least double buffered, and then explicitly resubmitted 
//    755//in completion handlers, so 
//    756//that data (such as audio or video) streams at as constant a rate as the 
//    757//host controller scheduler can support. 
//    758//
//    759//Completion Callbacks: 
//    760//
//    761//The completion callback is made in_interrupt(), and one of the first 
//    762//things that a completion handler should do is check the status field. 
//    763//The status field is provided for all URBs.  It is used to report 
//    764//unlinked URBs, and status for all non-ISO transfers.  It should not 
//    765//be examined before the URB is returned to the completion handler. 
//    766//
//    767//The context field is normally used to link URBs back to the relevant 
//    768//driver or request state. 
//    769//
//    770//When the completion callback is invoked for non-isochronous URBs, the 
//    771//actual_length field tells how many bytes were transferred.  This field 
//    772//is updated even when the URB terminated with an error or was unlinked. 
//    773//
//    774//ISO transfer status is reported in the status and actual_length fields 
//    775//of the iso_frame_desc array, and the number of errors is reported in 
//    776//error_count.  Completion callbacks for ISO transfers will normally 
//    777//(re)submit URBs to ensure a constant transfer rate. 
//    778  // 
    779 struct urb 
    780 { 
    781         // private, usb core and host controller only fields in the urb // 
    782         struct kref kref;               // reference count of the URB // 
    783         spinlock_t lock;                // lock for the URB // 
    784         void *hcpriv;                   // private data for host controller // 
    785         struct list_head urb_list;      // list pointer to all active urbs // 
    786         int bandwidth;                  // bandwidth for INT/ISO request // 
    787         atomic_t use_count;             // concurrent submissions counter // 
    788         u8 reject;                      // submissions will fail // 
    789   68
    790         // public, documented fields in the urb that can be used by drivers // 
    791         struct usb_device *dev;         // (in) pointer to associated device // 
    792         unsigned int pipe;              // (in) pipe information // 
    793         int status;                     // (return) non-ISO status // 
    794         unsigned int transfer_flags;    // (in) URB_SHORT_NOT_OK | ...// 
    795         void *transfer_buffer;          // (in) associated data buffer // 
    796         dma_addr_t transfer_dma;        // (in) dma addr for transfer_buffer // 
    797         int transfer_buffer_length;     // (in) data buffer length // 
    798         int actual_length;              // (return) actual transfer length // 
    799         unsigned char *setup_packet;    // (in) setup packet (control only) // 
    800         dma_addr_t setup_dma;           // (in) dma addr for setup_packet // 
    801         int start_frame;                // (modify) start frame (ISO) // 
    802         int number_of_packets;          // (in) number of ISO packets // 
    803         int interval;                   // (modify) transfer interval (INT/ISO) // 
    804         int error_count;                // (return) number of ISO errors // 
    805         void *context;                  // (in) context for completion // 
    806         usb_complete_t complete;        // (in) completion routine // 
    807         struct usb_iso_packet_descriptor iso_frame_desc[0];     // (in) ISO ONLY 
// 
    808 }; 
// ���ǳ�����Թ,Linux�ں�Դ������ע��̫����,���������ǳ�����������Щ���뾿����ʲô����.
// ��,urb�ÿ�����Ա����������,�ṹ��struct urb�Ķ��岻��30��,��˵������ȴ��������160����.��
// ��urb�Ľ�����λ.��ʱ������Ļ�����Щд��������ǲ�����Ϊ�Լ��Ĵ����ǰ��мƷѵ�,��ôһ�󴮵�
// ע����д�ò������ǿ��û�����.��Ȼ����������������Ҫ����Ϊ�˱���ԭ֭ԭζ,��һ�������ע��Ҳ˵
// �ú����,����ÿһ����Ա��������,�����ǽ���������ȻҪ�õ�urb��������Ա. 
// �˿�,������ʱ��ȥ�������ṹ��ÿһ��Ԫ�ص�����,ֻ��Ҫ֪��,һ��urb������ִ��usb��������
// Ҫ��������Ϣ.����Ϊ��������,Ҫͨ��,�ͱ��봴����ôһ�����ݽṹ,����Ϊ������ֵ,��Ȼ��ͬ���͵Ĵ�
// ��,��Ҫ��urb����ͬ��ֵ,Ȼ�����ύ���ײ�,���˵ײ��usb core���ҵ���Ӧ��usb host controller,
// �Ӷ�����ȥʵ�����ݵĴ���,��������֮��,usb host controller��֪ͨ�豸��������. 
// ��֮����֪��,760�о��ǵ���usb_alloc_urb()������һ��struct urb�ṹ��.����
// usb_alloc_urb()�������,���ǲ����㽲,����usb core ���ṩ��һ������,����
// drivers/usb/core/urb.c,usb������Ա��ȷ�Ǹ�����urb������,ר�ŰѺ�������ݽṹ��صĴ�������
// ����ôһ���ļ�����.���ǿ�����include/linux/usb.h���ҵ��������������, 
//     917 extern struct urb *usb_alloc_urb(int iso_packets, int mem_flags); 
// ������������ú�����,����Ϊһ��urb�ṹ�������ڴ�,������������,���е�һ��iso_packets����
// �ڵ�ʱ����ķ�ʽ��ָ������Ҫ������ٸ���,���ڷǵ�ʱģʽ��˵,�������ֱ��ʹ��0.��һ������
// mem_flags����һ��flag,���������ڴ�ķ�ʽ,���flag�����մ��ݸ�kmalloc����,�������ﴫ�ݵ�
// ��GFP_KERNEL,���flag���ڴ���������õ�,����֮ǰҲ�ù�,��Ϊus�����ڴ��ʱ
// ��.usb_alloc_urb���ս�����һ��urbָ��,��us�ĳ�Աcurrent_urbҲ��һ�� struct urb��ָ��,��
// �Ծ͸�������,������Ҫ��ס,usb_alloc_urb���������ڴ�����,���Խṹ�����˳�ʼ��,�ṹ��urb����  69
// ʼ��Ϊ0,��Ȼ��������û�а���������Ĵ���������,����Ҳǧ��Ҫ��Ϊд������˸������Ƶ�,�����
// ���������˳�ʼ��.ͬʱ,struct urb�л���һ�����ü���,�Լ�һ��������,��ЩҲͬ������ʼ����. 
// ����,���������Ǿͽ���us->current_urb�򽻵���.������urb������ô�û���Щ����Ļ�,����
// ����host controller�Ĵ���,����㲻�뿴,��ô�ҿ�����һ�������ܽ��ܵķ�ʽ������,usb��һ������,
// ����������Ҫͨ��,������ʵ����������Ҫʹ�õ����豸,���ǹ����豸��������ʵ��usbͨ��,����������
// ����usb host controller(usb����������),��������ͳһ����,��ͺñȱ����Ľ���,���������������
// ����Ҫ�ı����ǳ���������,�����г���������,û�н���,��ô���������ĳ��������˱ؽ�����,���ǵ�
// ���˽�����ôһ����ҵ,����վ��·��ͳһ����������ǻ��ҵĽ�ͨ.���糵�������˿�����ȫ�Ծ�����ĳ
// �ֹ�ض�����������������е�ÿһ������,ÿһ��·��,��ô������û�б�Ҫ������.ͬ��,�����豸�ܹ�
// ��ȫ�Ծ��Ĵ�����Ϣ,ÿһ�����ݰ����ܵ�����Ӧ��ȥ�ĵط�,��ô���Ǹ����Ͳ���Ҫ��������������ôһ
// ������.Ȼ��,��ʵ��,�ڱ���,���ؽ�ͨ������˲���,������ÿһ�������������˶��ᷢ��,�ڱ���,�����
// ��һ��ʱ��.�ҳ������Լ�˵,�����һ����û�д����,��ô�ɴ˿����Ƶ�����,��һ����һ��û�г���.ͬ
// ��,��usb��������,�豸Ҳ������ô�Ĳ��ع��,���Ǳ���Ҫ���һ�����������������������е�usb��
// ����ͨ��,����,�����������ͺ�ճ�����. 
// ��ô�豸�������������ķֹ����������?Ӳ��ʵ�������ǾͲ�˵��,˵������,Linux��,�豸����
// ����ֻҪΪÿһ������׼��һ��urb�ṹ�����,��������,(����˵���ϸø���ֵ)Ȼ��������usb core
// �ṩ�ĺ���,�����urb���ݸ�host controller,host controller�ͻ�Ѹ����豸�����������ύ��urb
// ͳһ�滮,ȥִ��ÿһ������.�����ڼ�,usb �豸��������ͨ�������˯��,��һ��host controller��urb
// Ҫ���������������,�������һ������ȥ����usb�豸��������,Ȼ��usb�豸��������Ϳ��Լ�������
// ����.���ֺñ�����ѧУ���ʦ����ϵ.���Ե�ʱ��,����ֻ�ܰ��Ծ����,Ȼ�����ǽ�����ʦ,Ȼ����ʦ��ȥ
// �����Ծ�,���ڼ����ǳ��˵ȴ�����ѡ��,�ȴ���ʦ�������Ծ�,���������Ƿ���,�����ּ������ǵ�����.��
// Ȼ��,����ɼ�����,Ҳ����Щ�˵�����Ͳ��������,�ڸ���,���ǿ���ѡ��ȥ�����ľ�����ϵ�,����ѡ��
// ȥ���Ľ�ѧ¥����������,�ڽ���,�����ȥ��˼Դ��.ͬ��,usb�豸��������Ҳ�����,���urb�ύ��
// usb host��,��������ȴû�гɹ�ִ��,��ôҲ���usb �豸�������������Ҳ����ǰ����.�����ⶼ�Ǻ�
// ��,����ֻҪ�и�������ʶ����,�Ժ󿴵��˾��ܸ���̵������,���ָ�λ�ֹ��ķ�ʽ�����Ǳ�д�豸����
// ��������˾޴�ķ���. 
// ���� 
// ������û����Ļ�,���Ǽ���usb_stor_acquire_resources����. 
// 761��764��,��ûɶ��˵�İ�.���Ǹղ�urb������֮���ж��Ƿ�����ɹ���,���ָ��ΪNULL��ô
// ����ʧ����.ֱ�ӷ���-ENOMEM.��������. 
// 767��,Ŷ,��һ���һ������ǳ���,dev_semaphore,����һ���ź���,��storage_probe�����ʼ��
// ��������������,��ʱ����ôһ�仰,����ǵ���һ����init_MUTEX����ʼ��һ���ź���, 
//    943         init_MUTEX(&(us->dev_semaphore)); 
// ���ǵ�ʱ˵��,�ȵ��õ�ʱ���ٽ�.�������ڵ�ȷ�ǵ��õ�ʱ����,����,�һ����뽲.�������������Ϊ,
// ֻҪѧ��̷��ǿ���Ǳ�C�������,���㲻��д����,ҲӦ���ܹ���������.Ȼ��,�����ҷ�����ʵ�������,
// ����û��,�Ҵ���.   70
// ����,ʲô���ź���?��ҵ��ʱ��,У԰��Ƹ�г����������Իῼ�ź���,�ῼ����,����ͨ�����Ļ�Ƚ�
// ��,���������ǿ���һЩ��������,ӡ����������Sun�й������о�Ժ�������б������,��ȻҲ�б�
// �ϸ���һ���,Ҫ���Ͼ���������ĳ���㷨���к����Է���,����Intel ĳ�����Ϻ�����ı�����,����
// �˾������ѧ�ҽ�������,�������˵������ֱ�̬�ı�������û����,�ҽ�Intel ��ʱ��ֻ���������ð��
// ����... 
// ���������������������ź���,���Ƕ���us�ĳ�Ա,һ�������dev_semaphore,��һ����sema,��
// ����struct us_data��ʱ�������Ѿ�������, 
//     111         struct semaphore        dev_semaphore;   // protect pusb_dev // 
//     156         struct semaphore        sema;            // to sleep thread on   // 
// semaҲͬ������storage_probe��һ��ʼ�����˳�ʼ��, 
// 944         init_MUTEX_LOCKED(&(us->sema)); 
// �豸���������ѵĲ���������������,һ�����漰���ڴ����Ĵ���,һ�����漰�����̹���Ĵ���,��һ
// �������ź����ͻ��������߱�����Ĵ���.��Щ����������������׵���ϵͳ����,���ź��������׵���
// �ľ�������. 
// ����Ϊ��Ѫ�����ĸ���˵����,��ô����ʲô���ź���?����ʲô�ǻ�����? 
// ��˵������.������������һ������.���������,��Щ����ֻ������ĳһ����,����˵��һ��ʱ����ֻ��
// ����һ����,������ϰ�,����һ��Ů������.����Ҫ׷��һ��Ů��ʱ,�����Ȼ�ȥ�˽������Ƿ���������,��
// �Ƿ�,��Ż�ȥ׷��,����Ȼ����,��ô��ֻ�ܷ���,����׼ȷ��˵,��ֻ�ܵȴ�.��Ȼ����Ժܼ�����˵,���
// �ȴ����Ի����漣�Ļ�,����Ը����ȥ,����һ��,�ֻ�һ��!Ȼ��,����������,�վ�������,�������˱�,����,
// ȴ�򲻿��������ǰ���.������Ӧ�þ��ܸо���ʲô�ǻ�������,һ��Ů�������������,��ô������˵,��
// �·�����������֮ǰ��������һ����,��Կ��,����������. 
// ��ô���ʴ�����ΪʲôҪ��?Ok,�Ҹ�����,��������ڲ���һ������,����һ������һ�ٸ�Ԫ��,�����
// ����ʮ��������,������ȥ�����������,�������û����,��ô�����������ʱ�����Ҳ���Բ����������,
// ���������Ͼ�Ҫ�ҵ�����ʮ����,����,����,ע����,����,���ʱ��,˵������λ���Ƕ�ȱ��,�ѵ���ʮ����
// ��ɾ����,���㲻�ǰ�æ����?����,��ô��?��һ����,ÿ����Ҫ�����������о͵��Ȼ�������,��һ��
// �����������,���ڲ���������ڼ�,���˾Ͳ��ܲ���,��Ϊ��Ҫ�������͵��Ȼ����,�����ʱ��������
// ����,������ֻ�ܵȴ�,���������,�ͷ�����,���ſ���ȥ����.��ô������ָ�ľ����������,һ����Դֻ
// ��ͬʱ��һ�����̲���,�����������˼Ҳ�������.�����ų�,����������˽��һ��. 
// ��ʲô���ź���?�ź����ͻ��������в�ͬ.������һ��ʱ�����м�������ͬʱ����һ����Դ.��������
// ���������趨,���Ϊ�趨�ź����ĳ�ֵ,���趨Ϊ1,�Ǿ�˵����ͬһʱ��ֻ��һ�����̿��Է���,��ô��
// ���ǻ�������,�����е�ʱ��һ����Դȷʵ�����ü������̷���,�ر��Ƕ�����,����һ���ļ����Ա�������
// ��ͬʱ��,�ⲻҪ����,��������,˭ҲӰ�첻��˭,ֻҪ��Ҷ���д������.�趨�ź����ĳ�ֵ,�����趨5,
// ��ô����˵,ͬһʱ����������5������ͬʱȥ������ļ�.ÿ�����̻�ȡ���ź����Ͱ��ź�����ֵ��һ,
// ��������������,��ȥ�ж�,����ֵ�Ѿ�����0��,���������ܷ�����,ֻ�ܵȴ�,�ȴ���Ľ����ͷ���.   71
// ����Ҳ��,һ��Կ��ֻ�ܿ�һ����,���ܴ������רһ.����ʵ����,Linux�ں˴��������õø���,����
// ֵ��Ϊ1���ź����õ������˵����.�������Ǹղſ������������ź���,�������ڵ�������������.��Ϊ��
// �ǵĳ�ֵһ�������ó���1(init_MUTEX),һ�������ó���0(init_MUTEX_LOCKED).���ó�һ�ܺ���
// ��,����һ�ѻ�����,ֻ������һ������ȥ�����,���ó�0 ��,�ͱ�ʾ������Ѿ�����ס��,���н����ͷ���
// �ſ���.��������767����� down(&us->dev_semaphore)��up(&us->dev_semaphore)��һ��,
// һ���ǻ����,һ�����ͷ���.���Ǿ���Ϊ�˱����м��Ƕδ���.�Ҹղ�˵�Ҳ��뽲��δ���,��ȷ,���ڽ�Ϊ
// ʲô����Ҫ������Ϊʱ����,����������us->dev_semaphore���ֵĴ������Ǻܶ�,�������Ǳ������
// �����붼��Ϥ�˲ſ������ΪʲôҪ�������,��Ϊ��Щ���붼�ǻ�����۵�,���ܹ�������.����,���ǽ�
// �ڹ��µ���β�׶���һ�������Ը��ݽ�겵ķ�ʽ��ÿһ��down(&us->dev_semaphore)��
// up(&us->dev_semaphore)��ʹ��ԭ��.���������ǿ������������ʱ��,Ҳ��һ����������.�������
// ����.��Ҫ˵��������down��up���������������÷ֱ����ȥ��������ͷ���.����down��˵,��ÿ��
// �ж�һ���ź�����ֵ�Ƿ����0,����,�ͽ�������Ĵ���,ͬʱ���ź�����ֵ��һ,����,�͵ȴ�,����˵רҵ
// һ��,����˯��.����down(),����Сʱ���ǲ�<<�ӽ�����>>�ĸ�ʺ����������������Ϊ, 
// ��:�ӽ�����,�����������,ҲԸ��������,������ѳ;   
// Ů:�ӽ�����,�����������,���»��ױ���һ������. 
// ����,�������￴����������,����us->dev_semaphore����,��һ����us->sema,���ڻ�û��ʹ��
// ��,�������ǿ�����˵һ��,us->sema�����������г��ֵĴ�������,�ܹ�ֻ������.���������ᵽ�����
// ��ʼ��Ϊ0�����,һ���������Ĵ�.������������������ʱ����Ҫ����,����ϸ�Ľ�.��Ϊ�����������
// Ϊʲô����������.�����ס,����ź�������˵������Ǳ���ʼ��Ϊ0��,����1,��һ��ʼ�ʹ�����ס��״
// ̬,��ʱ����ͻ�֪��Ϊʲô��.���Ǳ��߱߿�. 
// ����һ����Ҫ˵һ�µ���,��down ()���Ƶ���һ������down_interruptible ()�ĺ���,���ǵ�������
// �ں��߿ɱ��źŴ��,��ǰ�߲��ɱ��źŴ��,��һ����������,��ô���ǽ�����ȴ�,����רҵһ��˵,����
// ˯��,ֱ��ĳһ��... 
// ���ǽ������Ļ�ȡus->sema�ĺ������� down_interruptible.���ͷ����ĺ�����Ȼ������up. 
// ��һ�����ܽӴ�(һ) 
// ֱ���������ǲŽ���һ�������Ŀ�ʼ�Ӵ�usb���������ݴ���֮һ,���ƴ���.Ӧ��˵����һ�̿�ʼ,����
// ��ʼ��ø�����.������Ҫ��,������.������������ҹ,�����Ǽ�һ���¹�,��������˪. 
// 769��777��,����һ������,ȷ������豸��max lun.��Ҫ˵�㲻֪��ʲô��max lun.��֪���Ļ�ȥ
// �������,�Һܸ����ε������Ƽ�����Intel ���µ�3ϵ������оƬ������. 
// ��get_transport()������,������Ը��������us->max_lun����ֵ,�������ǵ�ʱ��ע�⵽��,Ψ��
// ����Bulk-Only���豸,��ʱ��û�и�ֵ,�����������ǿ���,����us->protocol ����US_PR_BULK��
// ���,��һ��ר�ŵĺ������������豸��max lun.����ŮΪ�ü���_��_�ݺ������,Ϊʲôд�����ͬ
// ־�������Bulk-Only���豸���ֳ�һ�֡�ƫƫϲ���㡱��̬����?ûʲô�ر��,������涨��.���е�
// usb�豸����һ���淶,����淶����usb spec,��usb �豸��Ϊ�ܶ�����,usb mass storage������һ
// ��,��mass storage�豸�ַ�Ϊ�ܶ�����,ÿ�������������Լ��Ĺ淶,����U���������صľ���usb   72
// mass storage class bulk-only transport spec.������淶˵�ú����,���������豸,����lun����ƾ
// �о������жϵ�,��÷���һ���������,����ȥ��ѯ,Ȼ������������Ӧ,���������֪���������Ǽ���lun.
// ����������ǡ�GET MAX LUN��,���spec 3.2. 
// �������Ǽ�ʹ�����濴�������Ҳ����֪������������ʲô.��������֮ǰ��˵��,��ͨ��U�̵�max 
// lun�϶���0.�������ֶ������ſ����ж��lun.�������ǻ��ǲ���������Ŀ�һ���������,�Ͼ������
// ������drivers/usb/storage/transport.c��,�������ǵ�Ͻ��.��Ȼ����Ҫ����,��ǰ����һֱû������
// ��ʶ������һ��usb��������ô����,��Ϊusb�豸�������򾿾���η���usb����,������������ø���
// ����һ�β���Ļ���.ͬʱ����Ҳ����֪��,�˽���һ�ο��ƴ���֮��,��Ĵ���Ҳ����������. 
// ��������֪����δ����Ŀ����Ϊ�˻��һ������,max lun,�����������ݵķ�ʽ�Ƿ�������,������
// �����̾���,�㷢��һ��������豸,�豸����һ��ֵ����,��ô�򵥵Ĵ����ʲô?���ƴ���.����Ȼ,����
// �˶�֪��,���ƴ�����usb���ִ��䷽ʽ����򵥵�����.�����������: 
 908 // Determine what the maximum LUN supported is // 
    909 int usb_stor_Bulk_max_lun(struct us_data *us) 
    910 { 
    911         int result; 
    912 
    913         // issue the command // 
    914         result = usb_stor_control_msg(us, us->recv_ctrl_pipe, 
    915                                  US_BULK_GET_MAX_LUN, 
    916                                  USB_DIR_IN | USB_TYPE_CLASS | 
    917                                  USB_RECIP_INTERFACE, 
    918                                  0, us->ifnum, us->iobuf, 1, HZ); 
    919 
    920         US_DEBUGP("GetMaxLUN command result is %d, data is %d\n", 
    921                   result, us->iobuf[0]); 
    922 
    923         // if we have a successful request, return the result // 
    924         if (result > 0) 
    925                 return us->iobuf[0]; 
    926 
    927         // 
    928        //Some devices (i.e. Iomega Zip100) need this -- apparently 
    929        //the bulk pipes get STALLed when the GetMaxLUN request is 
    930        //processed.   This is, in theory, harmless to all other devices 
    931        //(regardless of if they stall or not). 
    932          // 
    933         if (result == -EPIPE) { 
    934                 usb_stor_clear_halt(us, us->recv_bulk_pipe); 
    935                 usb_stor_clear_halt(us, us->send_bulk_pipe); 
    936         } 
    937 
    938         //   73
    939        //Some devices dont like GetMaxLUN.  They may STALL the control 
    940        //pipe, they may return a zero-length result, they may do nothing at 
    941        //all and timeout, or they may fail in even more bizarrely creative 
    942        //ways.  In these cases the best approach is to use the default 
    943        //value: only one LUN. 
    944          // 
    945         return 0; 
    946 } 
// ���벻��,������������.����914��, usb_stor_control_msg()����������,��Ҳ�������Լ�����ĺ�
// ��,����Ҳ�ý�,ͬ������drivers/usb/storage/transport.c: 
209 
    210 // 
    211//Transfer one control message, with timeouts, and allowing early 
    212//termination.  Return codes are usual -Exxx, *not* USB_STOR_XFER_xxx. 
    213  // 
    214 int usb_stor_control_msg(struct us_data *us, unsigned int pipe, 
    215                  u8 request, u8 requesttype, u16 value, u16 index, 
    216                  void *data, u16 size, int timeout) 
    217 { 
    218         int status; 
    219 
    220         US_DEBUGP("%s: rq=%02x rqtype=%02x value=%04x index=%02x 
len=%u\n", 
    221                         __FUNCTION__, request, requesttype, 
    222                         value, index, size); 
    223 
    224         // fill in the devrequest structure // 
    225         us->cr->bRequestType = requesttype; 
    226         us->cr->bRequest = request; 
    227         us->cr->wValue = cpu_to_le16(value); 
    228         us->cr->wIndex = cpu_to_le16(index); 
    229         us->cr->wLength = cpu_to_le16(size); 
    230 
    231         // fill and submit the URB // 
    232         usb_fill_control_urb(us->current_urb, us->pusb_dev, pipe, 
    233                          (unsigned char*) us->cr, data, size, 
    234                          usb_stor_blocking_completion, NULL); 
    235         status = usb_stor_msg_common(us, timeout); 
    236 
    237         // return the actual length of the data transferred if no error // 
    238         if (status == 0) 
    239                 status = us->current_urb->actual_length;   74
    240         return status; 
    241 } 
// ��������鷳һ��ĺ�����usb_stor_msg_common,��Ȼ�������Լ�����ĺ���,���������ֵü���
// ����һ�㿴,��ô��㺯�����õ�ȷͦ���˿���ͷ��,һ������Ҫ��İ����·,��İ���ķ羰,��İ���ĸ�,Ȼ
// ����ĳ���������˲��,��ᷢ��,ԭ���Ѿ��Ļ���ҪŪ����ĺ�������ô���Լ�Ū��Ϳ��.Ȼ��,��������
// ��ÿһ��·�������һ��,ÿһ��ģ�鶼�������۵ĺ�������,д����ĸ��Ƕ�Ϊ�˱����Լ�һ���ı��ˮ
// ƽ,��Զ����������һ·ƽ�ȵĿ�������ģ���.�������,���Ǳ���ѡ��,�Ͼ�����������ʱ,ҡ���͸�����
// ��,�����ǲ�ƽ����,Ҳ�Ƕ�����,����Ϊ�β�΢Ц�������Щ�鷳?��������Ծ�������
drivers/usb/storage/transport.c: 
132 // This is the common part of the URB message submission code 
    133//
    134//All URBs from the usb-storage driver involved in handling a queued scsi 
    135//command _must_ pass through this function (or something like it) for the 
    136//abort mechanisms to work properly. 
    137  // 
    138 static int usb_stor_msg_common(struct us_data *us, int timeout) 
    139 { 
    140         struct completion urb_done; 
    141         struct timer_list to_timer; 
    142         int status; 
    143 
    144         // don't submit URBs during abort/disconnect processing // 
    145         if (us->flags & ABORTING_OR_DISCONNECTING) 
    146                 return -EIO; 
    147 
    148         // set up data structures for the wakeup system // 
    149         init_completion(&urb_done); 
    150 
    151         // fill the common fields in the URB // 
    152         us->current_urb->context = &urb_done; 
    153         us->current_urb->actual_length = 0; 
    154         us->current_urb->error_count = 0; 
    155         us->current_urb->status = 0; 
    156 
    157         // we assume that if transfer_buffer isn't us->iobuf then it 
    158        //hasn't been mapped for DMA.  Yes, this is clunky, but it's 
    159        //easier than always having the caller tell us whether the 
    160        //transfer buffer has already been mapped. // 
    161         us->current_urb->transfer_flags = 
    162                         URB_ASYNC_UNLINK | URB_NO_SETUP_DMA_MAP; 
    163         if (us->current_urb->transfer_buffer == us->iobuf) 
    164                 us->current_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP; 
    165         us->current_urb->transfer_dma = us->iobuf_dma;   75
    166         us->current_urb->setup_dma = us->cr_dma; 
    167 
    168         // submit the URB // 
    169         status = usb_submit_urb(us->current_urb, GFP_NOIO); 
    170         if (status) { 
    171                 // something went wrong // 
    172                 return status; 
    173         } 
    174 
    175         // since the URB has been submitted successfully, it's now okay 
    176        //to cancel it // 
    177         set_bit(US_FLIDX_URB_ACTIVE, &us->flags); 
    178 
    179         // did an abort/disconnect occur during the submission? // 
    180         if (us->flags & ABORTING_OR_DISCONNECTING) { 
    181 
    182                 // cancel the URB, if it hasn't been cancelled already // 
    183                 if (test_and_clear_bit(US_FLIDX_URB_ACTIVE, &us->flags)) { 
    184                         US_DEBUGP("-- cancelling URB\n"); 
    185                         usb_unlink_urb(us->current_urb); 
    186                 } 
    187         } 
    188 
    189         // submit the timeout timer, if a timeout was requested // 
    190         if (timeout > 0) { 
    191                 init_timer(&to_timer); 
    192                 to_timer.expires = jiffies + timeout; 
    193                 to_timer.function = timeout_handler; 
    194                 to_timer.data = (unsigned long) us; 
    195                 add_timer(&to_timer); 
    196         } 
    197 
    198         // wait for the completion of the URB // 
    199         wait_for_completion(&urb_done); 
    200         clear_bit(US_FLIDX_URB_ACTIVE, &us->flags); 
    201 
    202         // clean up the timeout timer // 
    203         if (timeout > 0) 
    204                 del_timer_sync(&to_timer); 
    205 
    206         // return the URB status // 
    207         return us->current_urb->status; 
    208 }   76
// ����,����������,����������һ��һ��ȥ��ʶ��δ���.��ס�������վ���Ϊ�˿����
// usb_stor_Bulk_max_lun()���������������ô���max lun��. 
// ��һ�����ܽӴ�(��) 
// �����豸�����������,���ƴ���Ҫ��������ܼ�,��usb core�ύһ��urb,���urb�м������һ
// ������,����˵��������,��Ϊ������ʺ������Ǻ���Ҫ����ĳ����Ҫ�ĸ���.��������Ҫ���͵ľ���GET 
// MAX LUN.���ǵ�����һ������, usb_stor_control_msg,�����ô�������Ҳ���Կ���,���Ϳ�����Ϣ,��
// ��������.��һ������Ҫ����һ������Ĺ��,���Ϳ�����Ϣ���밴��һ���ĸ�ʽ,����ȥ���˼Ҳ��ܿ��ö�.
// ������Ҫ��Զ�������˼�һ����,��Ҫ���ŷ��ϰ�������ʽ��дһЩ����,����Ų��ܱ��ĳ�ȥ����. 
// ���ǽ��usb_stor_control_msg���������Լ����ǵ�������ʱ������������İ���ʵ�ʴ��ݸ�����
// ����������δ���,���������ʽ��������ε�.���ȵ�һ������us,������ö�˵�˰�.���ǻ����Ǹ�����,
// ����Ҳ�����Ǹ�����,ɽҲ��������ɽ,��Ҳ�����ǵ���,us��Ȼ�ܻ����Ǹ�us.��us����һ����Ա,����cr,
// ��struct us_data�Ķ���: 
149         struct usb_ctrlrequest  *cr;             // control requests     // 
// ����struct usb_ctrlrequest�ṹָ��, usb�淶�涨��һ����������ĸ�ʽΪһ��8���ֽڵ����ݰ�,
// ��struct usb_ctrlrequest����ר��Ϊ�˶�׼����8���ֽڵ�һ������,���Կ��ƴ������ܻ��õ���.����
// ������include/linux/usb_ch9.h��: 
     86 //* 
//     87//struct usb_ctrlrequest - SETUP data for a USB device control request 
//     88//@bRequestType: matches the USB bmRequestType field 
//     89//@bRequest: matches the USB bRequest field 
//     90//@wValue: matches the USB wValue field (le16 byte order) 
//     91//@wIndex: matches the USB wIndex field (le16 byte order) 
//     92//@wLength: matches the USB wLength field (le16 byte order) 
//     93//
//     94//This structure is used to send control requests to a USB device.  It matches 
//     95//the different fields of the USB 2.0 Spec section 9.3, table 9-2.  See the 
//     96//USB spec for a fuller description of the different fields, and what they are 
//     97//used for. 
//     98//
//     99//Note that the driver for any interface can issue control requests. 
//    100//For most devices, interfaces don't coordinate with each other, so 
//    101//such requests may be made at any time. 
//    102  // 
    103 struct usb_ctrlrequest { 
    104         __u8 bRequestType; 
    105         __u8 bRequest; 
    106         __le16 wValue; 
    107         __le16 wIndex;   77
    108         __le16 wLength; 
    109 } __attribute__ ((packed)); 
// ������Ҫ˵��һ��,��usb spec��,���� cr,����setup packet,��struct urb��߾�����ôһ������
//һ���ĳ�Ա, 
799         unsigned char *setup_packet;    // (in) setup packet (control only) // 
//��Ϊ��Linux��usb��������һ��ͨ�õ����ݽṹ��urb,�ܶຯ��������urbΪ������,�����Ժ�����
//ʵ���ϻ��ǻ���urb�е�setup_packet ָ��ָ�����usb_ctrlrequest�ṹ���.�Ͼ���������Ҫ�ύ
//�ľ���urb,������cr.����crֻ�ǳ����ڿ��ƴ���,��urbȴ���Ĵ��䶼Ҫ�õ���. 
//Ok,��usb mass storage bulk only transportЭ������,�涨�ĺ����,Ҫ����GET MAX LUN����,
//�����bmRequestType����Ϊdevice to host,class,interface,ͬʱ��bRequest����Ϊ254(FEh),
//�����������0xfe,��wValue����Ϊ 0,wIndex����Ϊ�ӿڵı��,���wLength����Ϊ1. 
//  ��Ҫ����һ��,ʲô��bmRequestType����device to host,class,interface?ʵ����,usb 2.0�淶
//����ָ��,���е�usb�豸������Ӧ������һЩ����,��Щ���������������,ͨ���豸��Ĭ�Ͽ��ƹܵ���
//��.(��0�Ŷ˵�����Ӧ���Ǹ��ܵ�)��Щ����,����˵��Щrequest,��ͨ�����ƴ�����ʵ�ֵ�,�����Լ���
//������Ĳ�������ͨ��setup packet�����͵�.���������������setup packet.(Ҳ�������Ǹղŵ�
//�Ǹ�cr,������ setup_packet.)ÿ��setup packet���� 8 ��bytes.���ǵĺ�������: 
//  byte0: bmRequestType,ע��,�ڸղ����Ǵ��������ݽṹstruct ctrlrequest�����д��
//bRequestType,�������Ƕ�Ӧ������ͬ�Ķ���.��֮����usbЭ����д��bmRequestType,����Ϊ��ʵ
//��������һ��λͼ(m��ʾ map),Ҳ����˵,������ֻ��1�� byte,��������Ȼ�ǵ���8λ����.���� 8λ
//�ĺ�����: 
//        D7: ���ƴ������ݴ���ķ���,0��ʾ����Ϊ�������豸,1��ʾ����Ϊ�豸������.(��ʱ���ƴ�
//����˷�����׶�����,���ܻ������ݴ���׶�,�˴���ʾ���������ݴ����Ǹ��׶εĴ��䷽��.) 
//        D6...5: ���������,0��Ϊ��׼����(Standard),1��ΪClass,2��ΪVendor,3���Ǳ�����,
//����ʹ��. 
//        D4...0: ������,0��ʾ�豸,1��ʾ�ӿ�,2��ʾ�˵�,3��ʾ����,4...31���Ǳ�����,����ʹ��. 
//        ����,bmRequestType����device to host,class,interface,��ʾ,���ݴ���׶δ��䷽������
//��������,�����������Class,��˼��,�������Ϳ����кü���,����usb spec�������˺ܶ��ֱ�׼����,
//���е�usb�豸������֧����Щ��׼����,���߻��׼request,��һ����,һ���豸���߳����Լ�Ҳ���Զ�
//���Լ��Ķ����һЩ����,��Ȼ����get max lun����usb mass storage�����,����˵���class ����
//�������,���,������������Ϊclass,��request�����߿������豸,Ҳ�����ǽӿ�,�������Ƕ˵�,��get 
//max lun���������˵,�������һ��u�̵�,�������Ľ�����Ӧ����interface. 
//  byte1: bRequest,1��byte,ָ�������ĸ�����.ÿһ��������һ�����,����������GET MAX 
//LUN,������ FEh. 
//  byte2...3: wValue,2��bytes,��ͬ�����в�ͬ��ֵ,��������ղ��Ѿ�˵��,����Ϊ0.   78
//  byte4...5: wIndex,2�� bytes,��ͬ�����в�ͬ��ֵ,��������Ҫ������Ϊ��interface number. 
//  byte6...7: wLength,2��bytes,��������������ݴ���׶�,�����ֵ���������ݴ���׶δ������
//��bytes,ûɶ��˵��,���ֵ��GET MAX LUN�����б��涨Ϊ1,Ҳ����˵����1 ��byte����. 
//  ��Ϻ������õ�ʵ�κͺ����Ķ���,�ɼ�,�������cr��˵,��bRequest����ֵΪ
//US_BULK_GET_MAX_LUN,bRequestType����ֵΪ
//USB_DIR_IN|USB_TYPE_CLASS|USB_RECIP_INTERFACE,��wValue����Ϊ0,wIndex������Ϊ
//us->ifnum, �ƿ��������,���Ƿ�����associate_dev()������,us->ifnum����ֵΪ
//intf->cur_altsetting->desc.bInterfaceNumber,����ȷʵ��Ӧ��interface number. wLength����
//ֵΪ1.���ú�cr֮��,�Ϳ��԰������ݸ�urb��setup_packet��.�Ա������usb_stor_control_msg()
//�����е�232 ��,�����溯��usb_fill_control_urb()�Ķ���,���ɿ���urb�� setup_packetָ��ָ��
//�����cr.��������usb_fill_control_urb()����,�������������include/linux/usb.h��: 
//    812 //* 
//    813//usb_fill_control_urb - initializes a control urb 
//    814//@urb: pointer to the urb to initialize. 
//    815//@dev: pointer to the struct usb_device for this urb. 
//    816//@pipe: the endpoint pipe 
//    817//@setup_packet: pointer to the setup_packet buffer 
//    818//@transfer_buffer: pointer to the transfer buffer 
//    819//@buffer_length: length of the transfer buffer 
//    820//@complete: pointer to the usb_complete_t function 
//    821//@context: what to set the urb context to. 
//    822//
//    823//Initializes a control urb with the proper information needed to submit 
//    824//it to a device. 
//    825  // 
    826 static inline void usb_fill_control_urb (struct urb *urb, 
    827                                          struct usb_device *dev, 
    828                                          unsigned int pipe, 
    829                                          unsigned char *setup_packet, 
    830                                          void *transfer_buffer, 
    831                                          int buffer_length, 
    832                                          usb_complete_t complete, 
    833                                          void *context) 
    834 { 
    835         spin_lock_init(&urb->lock); 
    836         urb->dev = dev; 
    837         urb->pipe = pipe; 
    838         urb->setup_packet = setup_packet; 
    839         urb->transfer_buffer = transfer_buffer; 
    840         urb->transfer_buffer_length = buffer_length; 
    841         urb->complete = complete; 
    842         urb->context = context; 
    843 }   79
//   ����Ȼ,������Ϊ�ض���pipe���һ��urb(���urb�����ʱ�򱻳�ʼ��Ϊ0���ﲻ��).�ԱȺ�������
// �ͺ�������,��֪, ���pipe����Ϊ��us->recv_ctrl_pipe,�����տ��ƹܵ�,Ҳ����˵ר��Ϊ�豸������
// �������ݶ����õĹܵ�.�����urb����us->current_urb,���ҳ���urb->setup_packet(unsigned 
// char���͵�ָ��)ָ����us->cr֮��,urb->transfer_buffer(voidָ��)ָ����
// us->iobuf,urb->transfer_buffer_length(int����)����ֵΪ1,urb->complete(usb_complete_t
// ����)����ֵΪ usb_stor_blocking_completion. 
//   �˴�������һ��usb_complete_t����,��include/linux/usb.h��,����ôһ��, 
    612 typedef void (*usb_complete_t)(struct urb *, struct pt_regs *); 
//   ��������typedef��������,����Ϥtypedef���ܵĿ���ȥ��һ��,typedef��ǿ��ʹ��������������
// ������ͬ: 
  һ����: 
  void (*func1)(struct urb *,struct pt_regs *); 
  void (*func2)(struct urb *,struct pt_regs *); 
  void (*func3)(struct urb *,struct pt_regs *);   
  ��һ����: 
  typedef void (*usb_complete_t)(struct urb *, struct pt_regs *); 
  usb_complete_t func1;  
  usb_complete_t func2; 
  usb_complete_t func3; 
//   �������˰�,���Ҫ�����ܶ������ָ��,���ǵĲ����ֶ��ܸ���,��ô��Ȼʹ��typedefһ��,�Ϳ���һ
// ��������,�Ժ������ͺܼ���.����,����Ҳ��֪��ʵ����,urb�е� complete��һ������ָ��,��������
// Ϊָ����usb_stor_blocking_completion().����usb_stor_blocking_completion()�������Ҳ���,
// �ȵ��õ�ʱ����˵. 
//   ������usb_fill_control_urb,�����ٻص�usb_stor_control_msg()����,����������һ����
// ��,usb_stor_msg_common(),ע����,usb_fill_control_urb�������ֻ�����urb�еļ���Ԫ
// ��,struct urb��������˺ܶණ��,������һЩ�����ǹ�ͬ��,����������usb_stor_msg_common()
// ����������,���Կ���������������ݵĲ���ֻ������,һ������us,��һ����timeout(��������ֵ��HZ),
// ���Ǽ������뵽�������������������������������װ���������.�������ÿһƬ�Ʋ�,����������,����
// ��տ����ޱ�;���ӵ��ÿһ������,������ƶ��,���Դ�ع�������;�������ÿһ������,�������С,��
// �Ժ�������ޱ�;���������֧�ָ��ִ���,��Ϊusb-storageģ��,��������ú��ִ��䷽ʽ,���۴�����
// �����Ķ���,���ն�һ��Ҫ�����������,�������Ǳ���������������ΰ��. 
// ���������������Ҫ��,�������ڸ�����Ϣ�Ĵ���,���������ǿ��ƴ���,�պ���bulk���������ǻ�����
// ����,���ǽ�����һ��ר��������.�����ڿ��������֮ǰ,��Щ�������Ҫ��������,�Ǿ�����Ϊ�豸����
// ����,ֻ��Ҫ�ύһ��urb�Ϳ�����,ʣ�µ�����usb core ��ȥ����,���˽������֪ͨ����.���ύ
// urb,usb coreΪ����׼����һ������,usb_submit_urb()��������ʹ��ʲô���䷽ʽ,���Ƕ�ֻҪ������
// ����������,�ڴ�֮ǰ,������Ҫ����ֻ��׼������ôһ��urb,��urb�и���صĳ�Ա����,Ȼ���ok��.
// ����usb_stor_msg_common������������.����Ȼ,��ͬ�Ĵ��䷽ʽ����дurb�ķ�ʽҲ��ͬ. 
// ���������Ҫָ��һ��,�������ǵ�cr��һ��ָ��,��ͬ־�������ָ��������ڴ�����?���ǿ϶���,
// �������������,������ʱ,�����ں���associate_dev()�оͼ�����us->cr,������usb_buffer_alloc
// Ϊ���������ڴ�,��ʱ���Ǿͽ�����.   80
// ��һ�����ܽӴ�(��) 
// �����ǵ���ֱ��,����usb_stor_msg_common()����. 
// ���ȿ�145��,��us->flags��ABORTING_OR_DISCONNECTING��
// ��,ABORTING_OR_DISCONNECTING�궨����drivers/usb/storage/usb.h��: 
   78 // Dynamic flag definitions: used in set_bit() etc. // 
     79 #define US_FLIDX_URB_ACTIVE     18  // 0x00040000  current_urb is in use  // 
     80 #define US_FLIDX_SG_ACTIVE      19  // 0x00080000  current_sg is in use   // 
     81 #define US_FLIDX_ABORTING       20  // 0x00100000  abort is in progress   // 
     82 #define US_FLIDX_DISCONNECTING  21  // 0x00200000  disconnect in progress 
// 
     83 #define ABORTING_OR_DISCONNECTING       ((1UL << US_FLIDX_ABORTING) | 
\ 
     84                                          (1UL << US_FLIDX_DISCONNECTING)) 
     85 #define US_FLIDX_RESETTING      22  // 0x00400000  device reset in progress 
// 
     86 #define US_FLIDX_TIMED_OUT      23  // 0x00800000  SCSI midlayer timed 
// out  // 
//   ��ֻ��һ��flag,����֪��,ÿһ��usb mass storage �豸,����һ��struct us_data�����ݽṹ,��
// us,����,������probe�Ĺ�������,���൱��һ��"ȫ��"�ı���,������ǿ���ʹ��һЩflags�����һЩ
// ����.����,�˴�,�����ύurb�ĺ�����˵,��Ȼ����ϣ���豸��ʱ�Ѿ����ڷ������߶Ͽ���״̬,��Ϊ����
// ��û�б�Ҫ�ύurb���ﲻ��. 
//   ����һ������init_completion(),ֻ��һ�����в�������,����������include/linux/completion.h
// ��: 
     13 struct completion { 
     14         unsigned int done; 
     15         wait_queue_head_t wait; 
     16 }; 
     24 static inline void init_completion(struct completion *x) 
     25 { 
     26         x->done = 0; 
     27         init_waitqueue_head(&x->wait); 
     28 } 
//   ��ֻ�ǵ�����init_waitqueue_headȥ��ʼ��һ���ȴ�����.��struct completion�Ķ���Ҳ��������
// ���г�.����init_waitqueue_head���ǽ�������Ĺ�����ר�Ž�������. 
//   ��������,����������us ��current_urb�ṹ,���ǿ� 161��,transfer_flags�����ó���
// URB_ASYNC_UNLINK | URB_NO_SETUP_DMA_MAP,����URB_ASYNC_UNLINK����
// usb_unlink_urb()���������첽����,�����첽����Ҳû�й�ϵ,��Ϊ�ں˵ķ�չ����˵�Ѹ��,��һ����
// ȫ���Ժ��Ϻ��ķ�չ�ٶ��е�һƴ,���µ��ں���,�����Ѿ��������������,��Ϊusb_unlink_urb�Ѿ���  81
// �첽���õĺ�����,�����ͬ������,�����ʹ����һ������usb_kill_urb().���������������þ���ȡ��
// һ��urb����.ͬ��������������һ�����,������ִ�й����п��Խ���˯��,����һ����������������ִ��,
// ���첽�����򲻻�˯��,��ô����֮����Ҫ����URB_ASYNC_UNLINK,��Ŀ�ľ�������
// usb_unlink_urb���첽��ִ��,ԭ����,�е�ʱ������ȡ��һ��urb request��ʱ���Ǵ���һ�ֲ���˯��
// ��������,����������ǻῴ���Ĵ���ʱ�ĺ���.�����ڻ�����������һ���ܴ��ļ���ʱ��,������������
// ʱ�����,Ȼ�����ǵ�����ͱ���ֹ��.����usbϵͳͬ�����������,���ǻ��һ��urb���ó�ʱ,�ύ��
// ȥ����һ��ʱ�仹û�ܴ���õĻ�����ζ�ſ��ܴ���������,�����������ͨ��Ҳ������urb��ȡ����.
// �����������������,��һ,�����ύ��urb֮��Ͳ�������,���ǵȴ�,��ô�ȴ�?˯��,���ǵĽ��̽���˯
// ��,���仰˵����������������龰��Ҳ����storage_probe����˯��.�������ʱ,��ô���´�,urbִ
// ������֮�����ǵĽ��̱�����,����������.��ô����ƽ��.���ǵڶ��������,���ǽ�����˯��,����ʱ�䵽
// ��,urb��û��ִ����,��ô��ʱ�����ᱻִ��,���ͻ�ȥȡ�����urb,���˵�����ʱ����Ҳ����˯��,��
// �Ͳ�������,���´�����,��˯��,˭�ɻ�?������������̱����!����,�������������Ҫ���õĺ����ǲ���
// ˯�ߵ�,Ҳ����˵�������첽��.��usb_unlink_urb�ڲ���ͨ���ж��Ƿ���URB_ASYNC_UNLINK��ô
// һ��flag����������urb->transfer_flags��,��ѡ�����첽ִ�л���ͬ��ִ��,ʵ��������ͬ��ִ�о���
// ����usb_kill_urb����.�����ղ�˵��,���°���ں�,����2.6.21,����߾Ͱ��������������׷ֿ���,��
// ������ôһ��flag,usb_unlink_urb�����첽,usb_kill_urb����ͬ��. 
// ��URB_NO_SETUP_DMA_MAP����,���ʹ��DMA����,��urb��setup_dmaָ����ָ��Ļ���
// ����DMA������,������setup_packet��ָ��Ļ�����.�������ٻ���
// URB_NO_TRANSFER_DMA_MAP�����,�����urb��һ��DMA��������Ҫ����,��û�������
// transfer_dmaָ����ָ����Ǹ�������,������transfer_bufferָ����ָ�����һ��������.���仰˵,
// ���û����������DMA��flag,��ôusb core�ͻ�ʹ��setup_packet��transfer_buffer��Ϊ���ݴ�
// ��Ļ�����,Ȼ���������о��ǰ�us ��iobuf_dma�� cr_dma������ urb��transfer_dma��
// setup_dma.(157��160��ע�ͱ���,ֻҪtransfer_buffer������ֵ,�Ǿͼ�����DMA��������Ҫ����,
// ���Ǿ�ȥ��URB_NO_TRANSFER_DMA_MAP.)����DMA��һ��,��Ϊ�Ƚ������,�������Ƕ�˵����. 
// ����,����������DMA��ص�flag,һ����URB_NO_SETUP_DMA_MAP,����һ����
// URB_NO_TRANSFER_DMA_MAP.�����������ǲ�һ����,ǰһ����ר��Ϊ���ƴ���׼����,��Ϊֻ�п�
// �ƴ�����Ҫ����ôһ��setup�׶���Ҫ׼��һ��setup packet.�����ǰ���setup_packetָ����
// us->cr���������ǵ���Ϊus->cr�����ڴ��ʱ���õ����������: 
  449         // Allocate the device-related DMA-mapped buffers // 
    450         us->cr = usb_buffer_alloc(us->pusb_dev, sizeof(*us->cr), 
    451                         GFP_KERNEL, &us->cr_dma); 
// �����������us->cr_dma,���������Ȼ����ֵ�Ǹ�����us->cr,�����ͬʱ,��us->cr_dma�м�
// ¼�Ŀ��Ըõ�ַ��ӳ���dma��ַ,��ô�ղ�����������URB_NO_SETUP_DMA_MAP��ôһ��flag,
// ��˵��,�����DMA��ʽ�Ĵ���,��ôusb core��Ӧ��ʹ��us->cr_dma��ߵĶ���ȥ����dma����,
// ����Ҫ��us->cr��ߵĶ�����.���仰˵,Ҳ����urb��ߵ�setup_dma������setup_buffer. 
// ͬ��transfer_buffer ��transfer_dma�Ĺ�ϵҲ�����,���ǵ���ͬ�������Ƶķ���������
// us->iobuf���ڴ�: 
  457         us->iobuf = usb_buffer_alloc(us->pusb_dev, US_IOBUF_SIZE, 
    458                         GFP_KERNEL, &us->iobuf_dma);   82
// �������us->iobuf��us->iobuf_dma����������,��������ע�⵽,163�� 164��,����������
// URB_NO_TRANSFER_DMA_MAP���flag��ʱ��,������һ���ж�,�ж�
// us->current_urb->transfer_buffer�Ƿ����us->iobuf,����ʲô��˼��?������ʲô�ط���
// transfer_buffer����ֵ? ����usb_fill_control_urb��,���ǰ�us->iobuf�����˹�ȥ,����������
// urb->transfer_buffer,����������ζ���������ｫʹ��DMA����,������������������flag,��������
// ��ϣ������DMA����,�Ǻܼ�,�����ڵ���usb_stor_msg_common֮ǰ,����
// urb->transfer_bufferָ�� us->iobuf������,�����ⶼ�������Լ����õ�,���˹ܲ���.��Ҫ֪����
// ��,transfer_buffer�Ǹ����ִ��䷽ʽ�������������ݴ����,��setup_packet�������ڿ��ƴ����з�
// ��setup�İ���,���ƴ������setup�׶�֮��,Ҳ�������ݴ���׶�,��һ�׶�Ҫ�������ݻ��ǵÿ�
// transfer_buffer,�����ʹ��dma��ʽ,��ô����ʹ��transfer_dma. 
// Ok,��һ��,169��,���ڵ����ύurb��һ����,usb_submit_urb�õ�����,��Ϊusb �豸��������,
// ���ǲ���Ҫ֪�����������������ʲô,ֻҪ֪����ôʹ�þͿ�����,�����ע���뱳�����ѧ.���Ķ�����
// drivers/usb/core/urb.c��,���ǵ�֪��������������,һ������Ҫ�ύ��urb,һ�����ڴ������flag,��
// ������ʹ�õ���GFP_NOIO,��˼���ǲ����������ڴ��ʱ�����IO����,����ܼ�,��������Ǵ洢��
// ��,����usb_submit_urb�ܿ�������Ϊ����Ҫ��Щ���̻���U��,�����������������ڴ�ĺ�������һ
// ��ȥ��д����,�Ǿ���������,ʲô����?Ƕ����.ʲô�������ڴ�ĺ���Ҳ���д����?���Linux���˲���
// ��֪��swap ��,��������,����Ҫ������,�ɲ�������Ϊ�ڴ治��ô.ʹ�ô�����Ϊ�����������ͷ�����,��
// �������ڴ��ʱ�����Ҫ���ڴ��ڴ�����,�Ǿ͵ý�������.�ⲻ�Ͷ�д������ô?��������Ϊ�˶�дӲ��
// ���ύurb,��ô��������оͲ����ٴ���IO������,��������Ŀ����Ϊ�˶ž�Ƕ����ѭ��. 
// �������ǵ�����169�оͿ�����������,ʣ�µ�����usb core ��usb host��ȥ����,�������������
// ��ķ���ֵ,���һ������,status���� 0.���������ж����status��Ϊ 0��ô���������. 
// 177��,һ��urb���ύ��֮��,ͨ�����ǻ��us->flags������һ��flag, US_FLIDX_URB_ACTIVE,
// �����Ǽ�¼�����urb��״̬�ǻ��ŵ�. 
// 180��,���������ٴ��ж�us->flags,���ǲ���˭����aborting����disconnected ��flag.�Ժ�����
// �ῴ��˭������Щflag,��Ȼ����Ѿ�������Щflag�Ļ�,���Ǿ�û��Ҫ������,���urb���� cancel ��. 
// 190��,һ���µĹ��½�������,�����ΰ���ʱ�����. 
// �ܳ�ˢһ�е�,��������,����ʱ��.����Linux��������ʱ�����. 
// ��һ�����ܽӴ�(��) 
//   �����˵:��֪����ʲôʱ��ʼ,��ʲô�������涼�и�����,�ﵶ������,���ͷ�����,������ֽ
// �������,�ҿ�ʼ����,�����������,����ʲô�����ǲ�����ڵ�? 
// ��ʱ����Ҳ���������������,�Ҳ�֪�����Ҳ����׻���������仯̫��.��Linux�ж������˹�����ô
// һ������.˵����һ����ǳ�ʱ.����һ��ʱ��,���ʱ�䵽�˸��������黹û������,��ôĳЩ����ͻᷢ
// ��.   83
// ����,������Ҫ������һЩ����,��������,����������Ҫ������,������8��30,������Ҫ��45����,����
// ����ϣ������9��һ����,Ȼ��ʱ�䵽��,���Ӿ��������ڴ���һ��,�����ͣ.�ڼ������,����Ҳ��Ҫ��
// ����������,��Щ����,������Ҫʱ�����,�ر�������,ͨ��,�ȵ�,�����漰���ݴ�����¶�,�͵ÿ��ǳ�ʱ,
// ���仰˵,��������,��Ҫ�������������ʱ���ﻹû���������������,��ôͣ����,������,�϶�������,
// ����,�������������45����,���ֵ���һ����ζ��û��,��ɫҲû��,�ǿ϶�������,����,�ȼ��һ�¿�
// ���ǲ��ǻ���,�ǲ���ͣ����,�ȵ�.�����嵽��������,��Ҫ��һ������,���߽�רҵһ��,��ʱ��,���ʱ��
// ����,��ִ��ĳ������,�������Linux�ں˵�ʱ������Ѿ�ʵ����,����ֻ��Ҫ��"˵����"������Ӧ�Ľӿ�
// ��������.������,190��,���timeout>0,Ҳ����˵��Ҫ��������,��ô������Ҫ����һ��struct 
// timer_list�ṹ��ı���,�������ﶨ��ı�������to_timer(��usb_stor_msg_commonһ��ʼ�Ͷ�
// ���˵�),Ȼ����init_timer()������add_timer()����������ʵ����������,init_timer()�ǳ�ʼ��,Ȼ��
// ���ú�֮�����add_timer ������������Ч.������ô���õ���?��add_timer()֮ǰ,Ϊ
// to_timer.expires��ֵΪjiffies+timeout,to_timer.function��ֵΪ
// timeout_handler,to_timer.data��ֵΪus.���ʾ,��ʱʱ���Ϊ��ǰʱ�����һ��
// timeout,(jiffies,Linux�ں��кպ�������ȫ�ֱ���,��ʾ��ǰʱ��),timeout����ǰ�����
// usb_stor_msg_common��ʱ������ó���HZ,Ҳ����1��.��ʱ�䵽��֮��,timeout_handler����
// �ᱻִ��,��us��Ϊ�������ݸ���.��������һ��timeout_handler������,��������
// drivers/usb/storage/transport.c��: 
//     119 // This is the timeout handler which will cancel an URB when its timeout 
//     120//expires. 
//     121  // 
    122 static void timeout_handler(unsigned long us_) 
    123 { 
    124         struct us_data *us = (struct us_data *) us_; 
    125 
    126         if (test_and_clear_bit(US_FLIDX_URB_ACTIVE, &us->flags)) { 
    127                 US_DEBUGP("Timeout -- cancelling URB\n"); 
    128                 usb_unlink_urb(us->current_urb); 
    129         } 
//     130 } 
//   ���ó�,��ʵҲû��ʲô,�������US_FLIDX_URB_ACTIVE flag,Ȼ�����usb_unlink_urb()����
// ������ǰ���urb.���ǵøղ�˵���Ǹ�ͬ���첽����?�����Ǹղ�˵���Ǹ��첽������,��Ȼ�˿��������
// ����˯��,��������driver�͹���... 
// ������,199��,�ǳ���Ҫ��һ��wait_for_completion(&urb_done),��仰��ʹ�����̽���˯��.��
// ���˸ղ������Ǿ�init_completion(&urb_done),urb_done��һ��struct completion�ṹ�����,
// ���������usb_stor_msg_common()�����ĵ�һ�оͳ�����.��Ȼcompletion��Linux��ͬ������
// ��һ������Ҫ�Ľṹ��.��wait_for_completion��Ӧ��һ��������complete().���÷���������������:
// ��������Ҫ��init_completion��ʼ��һ��struct completion�Ľṹ�����,Ȼ�����
// wait_for_completion()������ǰ���̾ͻ����˯��,����һ�ֵȴ�״̬,����һ�����̿��ܻ�ȥ��ĳ��,
// ����������ĳ������֮��,�������complete()����,һ�����������complete����,��ô�ղ�˯�ߵ���
// �����̾ͻᱻ����.������ʵ����һ��ͬ������,���߽еȴ�����.��ô��������complete���������ﱻ��
// �õ�,���仰˵,��������һ��˯ȥ,��ʱ��������.   84
//  ���ǵ��ڵ���usb_fill_control_urb()��� urb��ʱ������������һ��urb->completeָ����?û��,
// ��ʱ���ǾͿ�����,urb->complete=usb_stor_blocking_completion,���൱����usb host 
// controller driver������һ����Ϣ.����,��urb���������֮��,usb host controller�ỽ����,������ֱ
// �ӻ�����,����ͨ��ִ��֮ǰ�趨��urb�� complete����ָ����ָ��ĺ���,������
usb_stor_blocking_completion()����ȥ����������.usb_stor_blocking_completion()����������
drivers/usb/storage/transport.c��: 
109 // This is the completion handler which will wake us up when an URB 
    110//completes. 
    111  // 
    112 static void usb_stor_blocking_completion(struct urb *urb, struct pt_regs *regs) 
    113 { 
    114         struct completion *urb_done_ptr = (struct completion *)urb->context; 
    115 
    116         complete(urb_done_ptr); 
    117 } 
//   ������������仰,����������complete()����,urb_done_ptr�ͱ���Ϊurb->context,��
// urb->context��ʲô? usb_stor_msg_common()������,152��,�ɲ����ǰѸճ�ʼ���õ�
// urb_done��������ô?�����������Linux�ں˵ĺ��ĺ���,��Ҫ������������,����������������ں˵�
// ��,û��,���Ļ�����kernel/sched.c,����Ȼ,�����ǻ��Ѹղ�˯�ߵ��Ǹ�����.����֮,��
// ��,wait_for_completion()������,�Ӷ�����������. 
// ������㹻����,����������ʱ,��ôtimeout_handler�ᱻ����,����usb_unlink_urb�ᱻ����,
// Ȼ����?��ʵusb_stor_blocking_completion���ǻᱻ����,���һ�����urb->status�Ը��ߴ�����
// urb�� cancel ��. 
// ����ֻʣ�¼��д�����.������clear_bit()���US_FLIDX_URB_ACTIVE,�������urb������
// active��.��Ϊ�øɵ��¶�������,�ͺñ����İ����Ѿ��ĵ���,����Ȼ������Ǹ����Ӿ�û������.������
// ����Ӧ���б�־������ݵ��Ӷ�Ӧ�İ����Ѿ��͹���,��Ҫ������.����ǳ�ʱ��,��ôҲ��һ����,urb��
// ��cancel ��,��Ȼ�Ͳ�����Ϊactive��. 
// Ȼ����һ��,�����ʱtimeout������0,��ô˵���ղ�������Ǹ���ʱ���ӻ�û������,������������
// ��ȴ�Ѿ�������,����������ӾͲ���Ҫ����,�ͺñ��ʾֳ�ŵ������ĵ�,��������ס��,������Ҫû�ĵ�,
// ����ȥ����,�������Ը����Ͷ��˸�����,�����浽�������Ϳ���ȥ����,��������˼�����͸����ĵ���,
// ����������Ӿ�û�������ﲻ��,�����������͵�ȡ���������,ʡ���������Ͻ�����,������Ҳ��ɾ���ղ�
// �Ǹ�to_timer,���������Ե���Linux�ں�Ϊ���ṩ�ĺ���del_timer_sync(),���Ĳ������Ǹղ����
// to_timer�ĵ�ַ.���һ��,usb_stor_msg_common()�������ڸ÷�����,return 
// us->current_urb->status,���صľ���urb�� status.�������������ǿ����뿪���������. 
//   ����֮��,�ֻص�usb_stor_control_msg()����,���status��0,��ô˵���ɹ�������,���ڳɹ�����
// �����,urb�� actual_length������ֵΪʵ�ʴ��䳤��,Ȼ��usb_stor_control_msg()Ҳ������,Ҫô
// ��ʵ�ʳ���,Ҫô���ǲ��ɹ��ľ���status.�������Ҳ���ò��뿪�������.��Ȼ,����Ҫ�б�������,���
// Ӧ�þ�������.��������������,�������֮��������.�������Ǵ�����������֮������.   85
//   ����,�߹���ǧɽ��ˮ,������ǧ�����,������һ�λص��˾�Υ��usb_stor_Bulk_max_lun()����.
// ����һ�������Ŀ��ƴ������ô��ʼ����ô������. 
// ������,���Ǽ�����,���ƴ���Ľ�����ظ���result,����˵��,������U��һ����˵����������0,��
// ����Ȼֻ��һ��lun.�����жϵ���result����0,����ܼ�,result��һ��int�͵�����,�����صĸ�����
// ʵ������iobuf[0]��ôһ��char���͵ı���,�������ַ���0��,�����int�͵�Ȼ�ʹ���0��,���������ӡ
// ���������0,����resultʵ�����Ǵ���0��.��945������ͬ��ע�⵽,���result��һЩ��ֵ�ֵ,����
// ע����˵,�е��豸���Ͳ���GetMaxLUN �������,��������������Ǳ����һ����Ԩ,���¾�ʯҲ������
// ������,�������ɴ�ͷ���һ��0���ȵĽ����,��ô���������ô���Ǿ�ֻ�ܰ������豸����ֻ��һ��
// LUN��,����Ҳ�ͷ���0����. 
// ����933 ��935��������Ҫ˵һ��.��Ҳ��ר��ΪһЩ��̬���豸׼����.һ����豸�ò���.ֻ��
// usb_stor_clear_halt��������������Լ������,���ҽ������Ҳ���õ�,�������ǻ��ǽ�һ��.����,��
// ���������,���ǽ���һ�μ������ƴ���,���ǱϾ����������ǵĵ�һ�����ܽӴ���,����,��Ȼ������Ȼ��
// ����usb_stor_Bulk_max_lun��,��������������һ���ڽ���. 
// �����Ҫ����һ�µ���,��init_timer(),add_timer(),del_timer_sync()�⼸����������Linux�ں�
// �еĺ��ĺ���,�����ṹ��struct timer_list,���Ƕ�����include/linux/timer.h��kernel/timer.c��,
// ����ֻ��Ҫ֪�����þͿ�����,����֪��������ôʵ�ֵ�,ֻ��Ҫ֪�����������˳�ʱ�Ļ�,����ע��ĳ�ʱ
// �������ͻᱻִ��.���������������ȥ���õ�,��μ�ʱ���ȥ�жϳ�ʱ��Щ�ں��Իᴦ��,�������ǵ�
// ��,����Ϲ����Ҳû��.�����ں���˵,ʱ����������������Ƥ��,ֻ�����Լ������.������д�豸��������
// ��˵,��Щ���Ĵ������������е��ƶ�,�㿴������ĳһ������Ʈ,ȴʲôҲ������.�����������˵����
// ��:����Щ���鱾�������޷�����,ֻ�ÿ����Լ�.�� 
// �����ƴ�����е��� 
// ��ʵusb_stor_clear_halt������������úܼ�,����spec��߹涨��,usb�豸��,������˵�,��
// �����һ������Halt������,ɶ��Halt?���ɽ�ʰ�ȥ,�ж�,ֹͣ,��ͣ,��ô������,����ֻ�����,�Ͳ���
// ������Ů��������ͶƱ�˰�,��ѵ��Թ���,�Ͳ����ϻ�ɫ��վ�˰�,��ѵ��ӻ�����,�Ͳ��ܿ��й�֮����
// ���ޱ��ϵľ��ʱ����˰�.����usb�豸��˵,���ж˶˵��Bulk�˵������ôһ������,����Halt,��ʵ
// ���ǼĴ������ĳһλ,��Ϊ1,�ͱ�ʾ������Halt������,�Ǿ��Ǳ�ʾ����˵㲻������.Ҫ���ö˵�����
// ����,�ܼ�,����һλ����Ϊ0�Ϳ�����. 
// ����Halt,�������л�˵,�����һ��feature,��ʵ����һ������,�����ϲ��˵feature.��usb�豸ʵ
// �����кܶ�feature.ȷ�е�˵,�е�feature����device��feature,��Щ��interface��feature,��Щ
// ��endpoint��feature.��Halt��endpoint��feature. usb spec�涨��һЩ����,����SET_FEATURE,
// �Լ�CLEAR_FEATURE,����˼��,��������һ��feature�������һ��feature.��ô�������﷢������
// clear halt,ʵ���Ͼ���ִ��CLEAR_FEATURE,���halt���feature.�ղ�ͨ��
// usb_stor_Bulk_max_lun()���������Ѿ������˶���һ�ο��ƴ���,������Ϊ�豸������Ҫ����Щ����,
// ����͸ղŵ������������,�ղŷ��͵�������GET MAX LUN,������Ҫ���͵�������CLEAR FEATURE.
// ��һ������,GET MAX LUN��usb mass storage spec ר�Ÿ�������һС���豸�����,��CLEAR 
// FEATURE�������е�usb�豸��ͨ�õ�,��Ϊ����usb spec���涨��.   86
// ��ôʲôʱ��������Ҫ�������������?�Ȳ�˵���������������,ʵ����usb spec �涨��,�����豸��
// bulk�˵�,ÿ���豸��reset ֮��,��Ҫ���halt���featureȻ��˵������������.����֮�����ǻῴ
// ��,��reset��صĺ��������ǻ�����������,��ô���Ǵ˿�����������������Ǵ���ʲô�龰��?�����
// ��ע������ܿ���,��ô��ֻ��˵,�������̫�в���!��Դ������Ҫ������ΰ�����������սʿ!ע����˵
// �ú����,��Щ��̬���豸,�����ǲ����㰴�������,�˼���������ӦGetMaxLUN���request,��ƫҪ
// ˣ����,���ǲ���spec,�㷢��GetMaxLUN�������,������ظ�,������STALL���ص�,ʲô��STALL?
// ��ʵ����Halt,�˵����,����ͨ��һ�����,����������.����,��������,����Ҫ�����halt�����,������
// ��û�а취������. 
// Ok,��ʱ��ÿ��������ڲ���,����һ��������drivers/usb/storage/transport.c�еĺ�
// ��.usb_stor_clear_halt(): 
// 243 // This is a version of usb_clear_halt() that allows early termination and 
//     244//doesn't read the status from the device -- this is because some devices 
//     245//crash their internal firmware when the status is requested after a halt. 
//     246//
//     247//A definitive list of these 'bad' devices is too difficult to maintain or 
//     248//make complete enough to be useful.  This problem was first observed on the 
//     249//Hagiwara FlashGate DUAL unit.  However, bus traces reveal that neither 
//     250//MacOS nor Windows checks the status after clearing a halt. 
//     251//
//     252//Since many vendors in this space limit their testing to interoperability 
//     253//with these two OSes, specification violations like this one are common. 
//     254  // 
    255 int usb_stor_clear_halt(struct us_data *us, unsigned int pipe) 
    256 { 
    257         int result; 
    258         int endp = usb_pipeendpoint(pipe); 
    259 
    260         if (usb_pipein (pipe)) 
    261                 endp |= USB_DIR_IN; 
    262 
    263         result = usb_stor_control_msg(us, us->send_ctrl_pipe, 
    264                 USB_REQ_CLEAR_FEATURE, USB_RECIP_ENDPOINT, 
    265                 USB_ENDPOINT_HALT, endp, 
    266                 NULL, 0, 3*HZ); 
    267 
    268         // reset the endpoint toggle // 
    269         usb_settoggle(us->pusb_dev, usb_pipeendpoint(pipe), 
    270                 usb_pipeout(pipe), 0); 
    271 
    272         US_DEBUGP("%s: result = %d\n", __FUNCTION__, result); 
    273         return result; 
    274 }   87
258��,usb_pipeendpoint,������include/linux/usb.h��, 
   1091 #define usb_pipeendpoint(pipe)  (((pipe) >> 15) & 0xf) 
// �ܼ�,����15λ,Ȼ����0xf����,�õ�����Ȼ����ԭ��pipe��ߵ�15��18λ. ������������,һ��
// pipe�� 15λ��18λ�� endpoint��,(һ��16�� endpoint,)���Ժ���Ȼ,������ǵõ�endpoint��.
// Ȼ�����������endp.Ȼ�� usb_pipein()Ҳ������ͬһ�ļ���, 
//  1088 #define usb_pipein(pipe)        ((pipe) & USB_DIR_IN) 
//    1089 #define usb_pipeout(pipe)       (!usb_pipein(pipe)) 
// ��Ȼ,�����ж����ǲ���IN�Ĺܵ�.�����IN,��ô������1,��֮,����0.usb_pipeout���෴.261��,
// �����,�ͻ���. 
// 263��,��һ�ε���usb_stor_control_msg��������Ϣ��.USB_REQ_CLEAR_FEATURE��Ӧ��
// usb spec��һ����׼��������CLEAR_FEATURE(������usb�豸��Ӧ��֧�ֵ�����),��ʾ���һ����
// ����ĳ������,��USB_ENDPOINT_HALT���Ӧusb�Ķ˵�����,ÿ���˵㶼����ôһ����
// ��,ENDPOINT_HALT,��ָ���˵��Ƿ���ֹͣ״̬.CLEAR_FEATURE ������������ö˵��ֹͣ״
// ̬.˵����CLEAR_FEATURE������Ƕ˵������.���usb_stor_control_msg�β�ʵ������,usb 
// spec(Table 9-3)�涨�����������,wValueҪ������Ϊ��Feature Selector,��ֵΪ
// USB_ENDPOINT_HALT,��ѡ���Feature��ENDPOINT_HALT,��wIndex Ҫ������Ϊָ��һ��
// Endpoint,�ο�usb2.0�淶,��ָ��һ��EndpointʱwIndex�ĸ�ʽ,��֪,����λΪ�˵��
// (D3~D0),D7Ϊ����,(IN/OUT),�����λΪ����λ.ʵ���ϸ�ֵΪendp,���ǰ����˷���Ͷ˵������
// ����Ϣ.wLengthҪ������Ϊ0,data����ΪNULL,��Щ��û��.��ʱ����3s.����,�Ϳ���������
// Endpoint��ENDPOINT_HALT���flag.����usb_stor_control_msg���ǵ�Ȼ�Ͳ����ٽ���,������
// �Ļ�ͷȥ����,����һ������һ������,һ���ĺ�����������ǰ.Ψһ��ͬ��ֻ�Ǵ��ݵĲ�����ͬ����,Ҳ��
// ����������׺���Ϊˮ��,���ǵ�����Ҳ�����,ֻ����һ������·,����ȥ,�ͻز���ͷ,˭Ҳû�а취����
// һ��������·. 
// ��Ҫ�ر�ע��һ��,�ϴ�GETMaxLUN���� usb_stor_control_msg��ʱ��,���ǵ������ĸ���������
// ��0,���������Ǵ�����һ��endp,������Ϊ��ͬ������spec��߹涨���˵�,��Ȼ������������ƵĶ���
// ��һ��,������Ϊ���ƴ���,�������ǺͿ��ƶ˵��ڷ�����ϵ.������Ϊ���������bulk�˵��Halt 
// Feature��Ҫ���͸�bulk�˵�,���ƴ�����Զ��ֻ�Ƿ����������Ϳ��ƶ˵�֮��.������Ҫ����bulk�˵�,
// ����ͨ�������������endp��ôһ����,�豸��Ȼ��֪���ø�����. 
//   ������,269��,����һ��������include/linux/usb.h�еĺ�, 
//    1101 #define usb_settoggle(dev, ep, out, bit) ((dev)->toggle[out] = 
// ((dev)->toggle[out] & ~(1 << (ep))) | ((bit) << (ep))) 
//   dev ��struct usb_device�ṹ��ָ��,ֱ�����ڲ�֪��,struct usb_device�ṹ������unsigned 
// int toggle[2]��ôһ������,�������������Ԫ��,��Ӧendpoint��IN ��OUT.��OUT��˵,ÿһ��
// endpoint������ռһλ����λ,��usb���ƴ�������ݴ���ʱ,ÿһ������ͷ���ǽ����,�����ְ�
// ͷ,DATA0��DATA1,Ϊ�˱�֤�������ȷ��,һ����DATA0,һ����DATA1,һ���Ĵ�û�н���,host��
// ֪��������.������ν��usb_settoggle,���Ƕ�ָ����ep ����Ӧ���Ǹ�toggleλreset��0,Ȼ�����  88
// bit��Ϊ0,���bit���Ƶ�ep��Ӧ����λ�ٺ�toggle����,Ҳ����˵,�����toggleλreset��'bit',����
// bitΪ1,��ô����reset�� 1,���bitΪ 0,��ô����reset��0,����������reset ���Ǹ�λ��0,����
// ʱҲ�᲻��0,��Щ���ÿ����������.((dev)->toggle[out] & ~(1<<(ep)))���ǰ� 1���� epλ,����
// epΪ3,��ô���ǵõ���1000,Ȼ��ȡ��,�õ�0111,(��Ȼ��λ���и����1),Ȼ��(dev)->toggle[out]
// ��0111����,�����ʹ��toggle[out]�ĵ�3λ���������λ������.Ȼ����������bit���ݽ�������0,
// ���ԾͲ���ʲô����,����reset ��0.��֮,269������������ǰ�ָ����Endpoint �ĺ�ָ����pipe��
// Ӧ����λtoggleλ������.) 
// ��Ȼϸ�ĵ��˻ῴһ��spec,spec����˵��,����ʹ��data toggle�� endpoint,������halt feature
// �Ƿ�������,��ֻ֮Ҫ�����Clear Feature,��ô��data toggle���ǻᱻ��ʼ��ΪData0).��������
// �������,��Ȼ����Clear Feature���Ѿ���data toggleλ��ʼ��Ϊ 0��,������Ϊʲô��Ҫ�ٴ���һ��
// set toggle��? 
// ��ʵ����������,��ʵ���������������toggle bits,��������toggle bit,������toggle bit_s_,����
// ���𿴴���,��ʵ�豸�������һ��toggle bits,������������������,Ҳ������toggle bits,���
// toggle bits�Ǹ�host�õ�,�豸��ߵ��Ǹ�toggle bits��clear feature֮��,û��,�Ǳ���ʼ����Data0
// ��,����host�����Ҳ���¼����ôһ������,����д����ĸ��Ƕ��Ͷ��������һ������,���������set 
// toggle��Ŀ���޷Ǿ����������������豸�������ϵ��Ǹ�toggle bits����ͬ��. 
// �������������Ҳ�ͽ�����,���ص�����ο��ƴ���Ľ��,��������ע�⵽�������������������,��û
// ���˻�care�������ֵ,Ҳ���������жϷ���ֵ�����岻���˰�,���������ڴ������Ĵ�����. 
// ����, usb_stor_Bulk_max_lun�������Ҳ����Ҫ������.������������,������һ�λص���
// usb_stor_acquire_resources������,��������?��˵����,������ѧ���ڿ���Linux�ں˴�����˸���
// Ҳ���ò��п�˵,�������һ���ޱ��޼ʵ���,���׾ͽ�������������,��Խ��Խ��Խ���,·Խ��ԽԶԽ��
// ��,����Ҳ�����ס�������... 
// 776��,��us->max_lun���ڸղ�usb_stor_Bulk_max_lun()�ķ���ֵ.������,���ǽ�����һ�о�
// �л�ʱ������Ĵ���.�Ӵ����ǳ��Ŷ�����,�߽���ʱ��,�����ΰ���S-C-S-I. 
// ��ճ����� scsi 
// ��������ңԶ�ľ���, 
// ����������, 
// �����Ҿ�վ������ǰ,  
// ��ȴ��֪���Ұ���. 
// ��������ңԶ�ľ���, 
// �����Ҿ�վ������ǰ, 
// ��ȴ��֪���Ұ���, 
// ��������֪���˴��మ, 
// ȴ������һ��. 
// ��������ңԶ�ľ���, 
// ��������֪���˴��మ, 
// ȴ������һ��,   89
// ���������޷��ֵ��������, 
// ȴ���ù���װ��˿��û�а����������. 
// ��������ңԶ�ľ���, 
// ���������޷��ֵ��������, 
// ȴ���ù���װ��˿��û�а����������, 
// �������Լ���Ĭ����, 
// �԰�����˾���һ���޷���Խ�Ĺ���. 
// �����������Ϊ���뿴������,�ó����ĺ���Ҳ��������,�ó��������ݽṹҲ��������,������ʲô����
// �Ķ�����.�����������Ϊ���Ǽ���֪��������������ι�������.δ���뵽,���Ǿ�����ȫ�˽��������»�
// ��һ����. ����������ǰ��,��scsi. ��ȷ,��һ��U��������������Ҫ�˽�usbЭ��,��Ҫ��scsi Э��,Ҫ
// ֪��U������������usb�豸,�����ǡ��̡�,��Ҫ�洢����,���ԲŽ���usb mass storage,���ԲŽ�����
// ���洢,��U��,������ѭ�Ĵ���Э���bulk-only����,������ѭ��ָ�����SCSI transparent 
// command sets.���仰˵,U�̾�����ôͨ��?ʹ��scsi ����.�㲻��scsi Э������? 
// û�취,������scsiЭ����ȫ���˽�.��ô�Բ���,�ȳ�����Ϥһ��scsiЭ��,��Ϥһ��scsi�����.
// ��Ҫ˵��û��ʱ��,�׷�ͬ־˵�ĺ�,ʱ������鹵,ֻҪ�ϼ�,�����е�.ȥgoogleһ�Ѱ�,ȥ�ٶ�һ�Ѱ�.
// �������������. 
// �������Ĳ�ȥ��,�Ǻð�,�Ҽ������˽�һ���,ʲô��scsi?�޷�Ҳ��һ������.��������ͨ���������
// ͨ�˲�����Ӵ�scsi,��˾����õö�,����scsiӲ��,У԰��ߴ�ѧ��ͨ������scsiӲ��,��ideӲ��.ÿ��
// Ӳ�̶��������г�.����ÿ�����Ƕ�������fansһ��.��������֪�����������������,������,�кз�.��
// ô������Ӳ�̾���scsi Ӳ�̺�ideӲ��.scsi Ӳ������scsi �豸�е�һ��,���豸��������,�����߾���Э
// ��,��������֪���������������һ��Э�����scsi Э��,�ͺñ�����usb��������usbЭ��һ��.ʱ����
// �е���SCSI-2Э��.Linux�ں˴�������ȻҲ�����Э����Ϊscsi �豸׼���豸��������. 
// ����scsi,driversĿ¼���浱ȻҲ��һ����Ŀ¼����������,�Ǿ���drivers/scsi Ŀ¼.�������������
// ls���һ��,��ᷢ����������ļ������൱�Ķ�.�������ĺܸ���Ȥ,��ô���Kconfig�ļ���
// Makefile�ļ���ʼ����.ȥ�����˽�һ��Linux����scsi ��ϵͳ����ô������.�ҾͲ�������.����������
// ���������ܹ���2.6��ΰ����豸ģ��ʵ������ôһ������,��������pci ����usb ����scsi,�����㶨��
// һ������,Ȼ����������������,һ�����豸,һ��������,�����豸�����,pci ��pci ��ɨ�跽��,usb��
// usb��ɨ�跽��,scsi��scsi��ɨ�跽��,��֮������̱���Ϊ����ö��,ö������֮���豸������ͽ�����
// ��,ͬʱdrivers�����Ҳ��һ��һ������.ÿ���豸�����Լ��ıȽϷ���,Ҫ�Ǻ���,�Ͱ�һ���豸��һ��
// ����������,������,���������ṩ�ĺ�����Ȼ�ͻ�����Ҫ��ʱ�򱻵���,��ô,˭������? 
// Ok,������Ǵ��������,�����ô����?��������Ϊ����scsi ϵͳ�滮����?��֪��?��Ĳ�֪��?��
// ô�������Ľ����ô�������ʶ����.����,��ϧ,��Ҳ��֪��.�����ڸ�������Ĵ�ѧ����,���Ѿ���ѵ����
// ��һ���ϸ������.�⼸�������ǹ�ע��ֻ�������ı�͵���¼�,ֻ���������¼���¼�,ֻ����𶷵���
// ��¼�,ֻ�ǰ���İ������¼�,ȴ��δ����ע���Լ�Ӧ��ѧ��ʲô,��Ϊһ�����ں����³������й��Ĺ���
// ����Ӱ���,������! 
// ����,��֪���Ͳ�֪����,��������˼��һ��.����usb��ϵͳ�Ǳ�һ��,usb�Ǳ���һ���ֺ��Ĵ���,����
// Ϊusb core,��ôscsi �����ȻҲӦ������ôһ���ִ����,Ҳ��scsi core,����û�����.usb�Ǳ�Ū��
// һ��usb host Ŀ¼,Ȼ������豸Ҳ������,����storage�豸,����input�豸,����serial �豸,����
// image�豸,������Ϊusb����������������ɫ,һ����host,һ�����豸,��scsi ����ǲ���Ҳ��������  90
// ��?�Ȳ�˵�ɲ���������,��ʵ�����,û������,���еĶ�����һ���Զ�����drivers/scsi/Ŀ¼����,�г�
// һ����Ҫ�ǻ����˿���������,�㲻����������Ŀ¼����һ��,������������,���ٿ���ȥ����һ��,����
// ���㲻��.����Ҳ���������������Լ������ɰ�,����Ҳ��û��ʱ��,��ô����Ը��������׷�ͬ־����
// ��˵��.�������ǰ�scsi �豸�ֳ�������,��������д���ĸ�ģ����Ϊ��Щ�豸����������.���ĸ�ģ����
// sd_mod.ko,sr_mod.ko,st.ko,sg.ko.���������Linux��ʹ��U��,��ô��lsmod�鿴һ�µ�ǰ��װ
// ��ģ��,��һ���ῴ��һ������sd_mod��ģ��,һ���ῴ��һ������scsi_mod��ģ��,scsi_mod.ko��
// ��scsi �ĺ���ģ��,����ν��scsi core.��ôscsi host ��?hostͬ��Ҳ��һ��ģ��,��͵ÿ�������õ�
// ��ʲôhost��,�л��������HBA,��host bus adapter.����Ӧ����������ͽ�Host Bus Adapter 
// driver��.������usbϵͳ��,���е������ϵĻ������hostΪ����,��scsi Ҳ�����,���е��豸Ҳ��
// ��Χ��hostת.��ʹ������ת��,�豸��ȻҪΧ��hostת.�����������,��ʹ��Ļ�����û��һ����
// ��HBA�Ķ���,�������U�̻������ð�,������ô����?û��,����������,�����ر��,Linux�ں˴�����
// Ȼ��������,��������˵,ȴ�������ʲ���ʵ.�����������δ���usb-storage��scsi�Ľӿڵ���?������
// ����������һ��scsi host.����,�������cat /proc/scsi/scsi ����,�Ϳ��Կ���scsi �豸��U������ô
// ��������. 
// ������û�в�U�̵�һ������: 
// localhost:~ # cat /proc/scsi/scsi 
// Attached devices: 
// Host: scsi0 Channel: 00 Id: 08 Lun: 00 
//   Vendor: DP       Model: BACKPLANE        Rev: 1.00 
//   Type:   Enclosure                        ANSI SCSI revision: 05 
// Host: scsi0 Channel: 02 Id: 00 Lun: 00 
//   Vendor: DELL     Model: PERC 5/i         Rev: 1.00 
//   Type:   Direct-Access                    ANSI SCSI revision: 05 
// Host: scsi1 Channel: 00 Id: 00 Lun: 00 
//   Vendor: SUN      Model: StorEdge 3510    Rev: 415F 
//   Type:   Enclosure                        ANSI SCSI revision: 03 
// Host: scsi1 Channel: 00 Id: 01 Lun: 00 
//   Vendor: SUN      Model: StorEdge 3510    Rev: 415F 
//   Type:   Direct-Access                    ANSI SCSI revision: 03 
// Host: scsi1 Channel: 00 Id: 01 Lun: 01 
//   Vendor: SUN      Model: StorEdge 3510    Rev: 415F 
//   Type:   Direct-Access                    ANSI SCSI revision: 03 
// Host: scsi1 Channel: 00 Id: 01 Lun: 02 
//   Vendor: SUN      Model: StorEdge 3510    Rev: 415F 
//   Type:   Direct-Access                    ANSI SCSI revision: 03 
// Host: scsi1 Channel: 00 Id: 01 Lun: 03 
//   Vendor: SUN      Model: StorEdge 3510    Rev: 415F 
//   Type:   Direct-Access                    ANSI SCSI revision: 03 
// Host: scsi1 Channel: 00 Id: 01 Lun: 04 
//   Vendor: SUN      Model: StorEdge 3510    Rev: 415F 
//   Type:   Direct-Access                    ANSI SCSI revision: 03 
// Host: scsi1 Channel: 00 Id: 01 Lun: 05 
//   Vendor: SUN      Model: StorEdge 3510    Rev: 415F   91
//   Type:   Direct-Access                    ANSI SCSI revision: 03 
// Host: scsi1 Channel: 00 Id: 01 Lun: 06 
//   Vendor: SUN      Model: StorEdge 3510    Rev: 415F 
//   Type:   Direct-Access                    ANSI SCSI revision: 03 
// Host: scsi1 Channel: 00 Id: 01 Lun: 07 
//   Vendor: SUN      Model: StorEdge 3510    Rev: 415F 
//   Type:   Direct-Access                    ANSI SCSI revision: 03 
// ������ڶ����ǻ�������U �̵����: 
// localhost:~ # cat /proc/scsi/scsi 
// Attached devices: 
// Host: scsi0 Channel: 00 Id: 08 Lun: 00 
//   Vendor: DP       Model: BACKPLANE        Rev: 1.00 
//   Type:   Enclosure                        ANSI SCSI revision: 05 
// Host: scsi0 Channel: 02 Id: 00 Lun: 00 
//   Vendor: DELL     Model: PERC 5/i         Rev: 1.00 
//   Type:   Direct-Access                    ANSI SCSI revision: 05 
// Host: scsi1 Channel: 00 Id: 00 Lun: 00 
//   Vendor: SUN      Model: StorEdge 3510    Rev: 415F 
//   Type:   Enclosure                        ANSI SCSI revision: 03 
// Host: scsi1 Channel: 00 Id: 01 Lun: 00 
//   Vendor: SUN      Model: StorEdge 3510    Rev: 415F 
//   Type:   Direct-Access                    ANSI SCSI revision: 03 
// Host: scsi1 Channel: 00 Id: 01 Lun: 01 
//   Vendor: SUN      Model: StorEdge 3510    Rev: 415F 
//   Type:   Direct-Access                    ANSI SCSI revision: 03 
// Host: scsi1 Channel: 00 Id: 01 Lun: 02 
//   Vendor: SUN      Model: StorEdge 3510    Rev: 415F 
//   Type:   Direct-Access                    ANSI SCSI revision: 03 
// Host: scsi1 Channel: 00 Id: 01 Lun: 03 
//   Vendor: SUN      Model: StorEdge 3510    Rev: 415F 
//   Type:   Direct-Access                    ANSI SCSI revision: 03 
// Host: scsi1 Channel: 00 Id: 01 Lun: 04 
//   Vendor: SUN      Model: StorEdge 3510    Rev: 415F 
//   Type:   Direct-Access                    ANSI SCSI revision: 03 
// Host: scsi1 Channel: 00 Id: 01 Lun: 05 
//   Vendor: SUN      Model: StorEdge 3510    Rev: 415F 
//   Type:   Direct-Access                    ANSI SCSI revision: 03 
// Host: scsi1 Channel: 00 Id: 01 Lun: 06 
//   Vendor: SUN      Model: StorEdge 3510    Rev: 415F 
//   Type:   Direct-Access                    ANSI SCSI revision: 03 
// Host: scsi1 Channel: 00 Id: 01 Lun: 07 
//   Vendor: SUN      Model: StorEdge 3510    Rev: 415F 
//   Type:   Direct-Access                    ANSI SCSI revision: 03   92
// Host: scsi3 Channel: 00 Id: 00 Lun: 00 
//   Vendor: Leidisk  Model: USB Flash Drive  Rev: 
//   Type:   Direct-Access                    ANSI SCSI revision: 02 
// ������������?û��,���������һ��,����һ��Leidisk������U��.���ﱾû��һ����ʵ��host,����д
// ����ĸ�����ȴ�������Ҳ���ƺ������,������scsi core������ƭ��һ��.��ô��Щ�����������ʵ��
// ����?�������������Ŀ�,��������������������host��������γ��ֵ�,�������Ƿ������ķ���һ��,
// �Ƿ�����־�����һ��,���ż�ͦ,ʵ������ȫ����ĭ... 
// ˭�����̬�Ľṹ�� 
// scsi ��ϵͳ����豸ʹ��scsi ������ͨ��,scsi spec������һ��ѵ�����,spec������Ϊ���,��
// ��ν��command set.����һЩ������ÿһ��scsi �豸������֧�ֵ�,��һЩ�������ǿ�ѡ��.����ΪU
// ��,����֧�ֵ���scsi transparent command set,�����������Ͼ���֧�����е�scsi ������,��������
// ��ʵ���������κ�һ�����������,ֻ��Ҫ�˽�һЩ����������������.����������Ҫ֪��,���е�scsi
// �豸��������Ҫ֧���������ĸ�scsi ����:INQUIRY,REQUEST SENSE,SEND DIAGNOSTIC,TEST 
// UNIT READY.һ�������ڴ����л��������еļ���,���Ҳ���.������ڴ����豸,������Ҫ֧������һЩ
// ����,����������READ����,д�����WRITE����,�ֱ������Ǿ������ĸ�ʽ������,���Ͷ�Ӧ
// FORMAT UNIT����.���ڴ����������豸,SCSIЭ����߳���Ϊdirect-access devices.�����Ϊʲô
// ��ղ���cat /proc/scsi/scsi ��������ܿ���һ����Type:Direct-Access����ôһ��. 
// ֪����scsi ������ʹ��scsi ������ͨ��,��ô������һ����Ҫ֪��scsi host������,����Ҫ���Ǹ���
// ��������豸,Ȼ���豸��ȥִ������.����scsi hostҲ����Ϊinitiator(������),��scsi �豸����Ϊ
// target(Ŀ�ĵ�). 
// ��ô���Ǿ�֪��,�������û��scsi host,��������������scsiЭ�����scsi�����device,����ô��?
// ˭����������?û��Ӳ�����������,������˭���ݹ�����?Ӧ�ò�?����scsi core?������˭,ֻҪ������
// �����ϲ������ݸ��豸,�Ǿ�Ok�˶Բ���?scsi ���Ĳ��һ�ж�������,����ֻҪΪһ��scsi host��
// ����Ӧ�����ݽṹ,�����������ܹ����͸��豸,�ܹ����豸���յ�����,�Ǿ����´��˶Բ���?����˵��
// ��usb-storage�������Ĺ���Ҳ��ʵ���˶Բ���?���������ǾͿ��Կ�ʼ�����������ǵĴ�����.������
// ���ǻ���usb_stor_acquire_resources()������,ֻ�����ոս���usb_stor_Bulk_max_lun()������
// ��. 
// 781��,us->unusual_dev->initFunction��ʲô?��Ҫ˵��һ��ӡ��Ҳû��.�ڷ���
// unusual_devs.h�ļ���ʱ������ר�žٹ����ӵ�,˵��Щ�豸��ҪһЩ��ʼ������,���Ͷ�����
// unusual_devs.h�ļ���,������ͨ��UNUSUAL_DEV�Ķ����Ѿ�����Щ��ʼ��������������
// us->unusual_dev ��initFunctionָ����.������ʱ��,�ڴ��俪ʼ֮ǰ,�����ж�,�ǲ���������һ����
// ��,���������ָ���Ƿ�Ϊ��,�����Ϊ��,�ܺð�,ִ���������������.���統ʱ���Ǿ����ӵ�ʱ��˵����
// �������յ�CD��¼�����и���ʼ������init_8200e,��ô������ִ�к���.��Ȼ,һ����豸�϶�����Ҫ
// ��ôһ������.���ڴ��ݸ���������Ĳ���,��struct us_unusual_dev�ṹ�嶨���ʱ��,�Ͱ��������
// ��Ҫʲô���Ĳ����������,��Ҫ�ľ���һ��struct us_data *,��ô����Ȼ,���ݵľ���us. 
// Ȼ��790��,scsi_host_alloc����scsi ��ϵͳ�ṩ�ĺ���,�������þ�������һ��scsi host��Ӧ����
// �ݽṹ.��������Ҫע��������Ĳ���,�����ǵ�һ������, &usb_stor_host_template,��ʵ����һ��  93
// struct scsi_host_template�Ľṹ��ָ��,����һ�̿�ʼ,������Ҫ��ʼ�˽�
// drivers/usb/storage/scsiglue.c����ļ���,glue���ǽ�ˮ����˼,��scsi ������Ĵ������ǾͶ�׼��
// ������ļ�����. 
usb_stor_host_template�Ķ������drivers/usb/storage/scsiglue.c��, 
  416 // 
 //   417//this defines our host template, with which we'll allocate hosts 
    418  // 
    419 
    420 struct scsi_host_template usb_stor_host_template = { 
    421         // basic userland interface stuff // 
    422         .name =                         "usb-storage", 
    423         .proc_name =                    "usb-storage", 
    424         .proc_info =                    proc_info, 
    425         .info =                         host_info, 
    426 
    427         // command interface -- queued only // 
    428         .queuecommand =                 queuecommand, 
    429 
    430         // error and abort handlers // 
    431         .eh_abort_handler =             command_abort, 
    432         .eh_device_reset_handler =      device_reset, 
    433         .eh_bus_reset_handler =         bus_reset, 
    434 
    435         // queue commands only, only one command per LUN // 
    436         .can_queue =                    1, 
    437         .cmd_per_lun =                  1, 
    438 
    439         // unknown initiator id // 
    440         .this_id =                      -1, 
    441 
    442         .slave_alloc =                  slave_alloc, 
    443         .slave_configure =              slave_configure, 
    444 
    445         // lots of sg segments can be handled // 
    446         .sg_tablesize =                 SG_ALL, 
    447 
    448         // limit the total size of a transfer to 120 KB // 
    449         .max_sectors =                  240, 
    450 
    451         // merge commands... this seems to help performance, but 
    452        //periodically someone should test to see which setting is more 
    453        //optimal. 
    454          //   94
    455         .use_clustering =               1, 
    456 
    456 
    457         // emulated HBA // 
    458         .emulated =                     1, 
    459 
    460         // we do our own delay after a device or bus reset // 
    461         .skip_settle_delay =            1, 
    462 
    463         // sysfs device attributes // 
    464         .sdev_attrs =                   sysfs_device_attr_list, 
    465 
    466         // module management // 
    467         .module =                       THIS_MODULE 
    468 }; 
//   �����������ǰ����ṹ������Ķ������˵��ʼ���ܸ���,��ô������.��Ϊ������������һ������̬
// �����ݽṹ�Ķ���,�����Ǵ�˵�е�struct scsi_host_template,����scsi ��ϵͳ����Ľṹ��,����
include/scsi/scsi_host.h�ļ�: 
     40 struct scsi_host_template { 
     41         struct module *module; 
     42         const char *name; 
     43 
     44         // 
     45        //Used to initialize old-style drivers.  For new-style drivers 
     46        //just perform all work in your module initialization function. 
     47        //
     48        //Status:  OBSOLETE 
     49          // 
     50         int (* detect)(struct scsi_host_template *); 
     51 
     52         // 
     53        //Used as unload callback for hosts with old-style drivers. 
     54        //
     55        //Status: OBSOLETE 
     56          // 
     57         int (* release)(struct Scsi_Host *); 
     58 
     59         // 
     60        //The info function will return whatever useful information the 
     61        //developer sees fit.  If not provided, then the name field will 
     62        //be used instead. 
     63        //
     64        //Status: OPTIONAL   95
     65          // 
     66         const char *(* info)(struct Scsi_Host *); 
     67 
     68         // 
     69        //Ioctl interface 
     70        //
     71        //Status: OPTIONAL 
     72          // 
     73         int (* ioctl)(struct scsi_device *dev, int cmd, void __user *arg); 
     74 
     75         // 
//     76        //The queuecommand function is used to queue up a scsi 
//     77        //command block to the LLDD.  When the driver finished 
//     78        //processing the command the done callback is invoked. 
//     79        //
//     80        //If queuecommand returns 0, then the HBA has accepted the 
//     81        //command.  The done() function must be called on the command 
//     82        //when the driver has finished with it. (you may call done on the 
//     83        //command before queuecommand returns, but in this case you 
//     84        //*must* return 0 from queuecommand). 
//     85        //
//     86        //Queuecommand may also reject the command, in which case it may 
//     87        //not touch the command and must not call done() for it. 
//     88        //
//     89        //There are two possible rejection returns: 
//     90        //
//     91        //  SCSI_MLQUEUE_DEVICE_BUSY: Block this device temporarily, but 
//     92        //  allow commands to other devices serviced by this host. 
//     93        //
//     94        //  SCSI_MLQUEUE_HOST_BUSY: Block all devices served by this 
//     95        //  host temporarily. 
//     96        //
//     97        //For compatibility, any other non-zero return is treated the 
//     98        //same as SCSI_MLQUEUE_HOST_BUSY. 
//     99        //
//    100        //NOTE: "temporarily" means either until the next command for# 
//    101        //this device/host completes, or a period of time determined by 
//    102        //I/O pressure in the system if there are no other outstanding 
//    103        //commands. 
//    104        //
//    105        //STATUS: REQUIRED 
    106          // 
    107         int (* queuecommand)(struct scsi_cmnd *, 
    108                              void (*done)(struct scsi_cmnd *));   96
    109 
//    110         // 
//    111        //This is an error handling strategy routine.  You don't need to 
//    112        //define one of these if you don't want to - there is a default 
//    113        //routine that is present that should work in most cases.  For those 
//    114        //driver authors that have the inclination and ability to write their 
//    115        //own strategy routine, this is where it is specified.  Note - the 
//    116        //strategy routine is *ALWAYS* run in the context of the kernel eh 
//    117        //thread.  Thus you are guaranteed to *NOT* be in an interrupt 
//    118        //handler when you execute this, and you are also guaranteed to 
//    119        //*NOT* have any other commands being queued while you are in the 
//    120        //strategy routine. When you return from this function, operations 
//    121        //return to normal. 
//    122        //
//    123        //See scsi_error.c scsi_unjam_host for additional comments about 
//    124        //what this function should and should not be attempting to do. 
//    125        //
//    126        //Status: REQUIRED     (at least one of them) 
    127          // 
    128         int (* eh_strategy_handler)(struct Scsi_Host *); 
    129         int (* eh_abort_handler)(struct scsi_cmnd *); 
    130         int (* eh_device_reset_handler)(struct scsi_cmnd *); 
    131         int (* eh_bus_reset_handler)(struct scsi_cmnd *); 
    132         int (* eh_host_reset_handler)(struct scsi_cmnd *); 
    133 
    134         // 
    135        //This is an optional routine to notify the host that the scsi 
    136        //timer just fired.  The returns tell the timer routine what to 
    137        //do about this: 
    138        //
    139        //EH_HANDLED:          I fixed the error, please complete the command 
    140        //EH_RESET_TIMER:      I need more time, reset the timer and 
    141        //                     begin counting again 
    142        //EH_NOT_HANDLED       Begin normal error recovery 
    143        //
    144        //Status: OPTIONAL 
    145          // 
    146         enum scsi_eh_timer_return (* eh_timed_out)(struct scsi_cmnd *); 
    147 
//    148         // 
//    149        //Before the mid layer attempts to scan for a new device where none 
//    150        //currently exists, it will call this entry in your driver.  Should 
//    151        //your driver need to allocate any structs or perform any other init 
//    152        //items in order to send commands to a currently unused target/lun   97
//    153        //combo, then this is where you can perform those allocations.  This 
//    154        //is specifically so that drivers won't have to perform any kind of 
//    155        //"is this a new device" checks in their queuecommand routine, 
//    156        //thereby making the hot path a bit quicker. 
//    157        //
//    158        //Return values: 0 on success, non-0 on failure 
//    159        //
//    160        //Deallocation:  If we didn't find any devices at this ID, you will 
//    161        //get an immediate call to slave_destroy().  If we find something 
//    162        //here then you will get a call to slave_configure(), then the 
//    163        //device will be used for however long it is kept around, then when 
//    164        //the device is removed from the system (or * possibly at reboot 
//    165        //time), you will then get a call to slave_destroy().  This is 
//    166        //assuming you implement slave_configure and slave_destroy. 
//    167        //However, if you allocate memory and hang it off the device struct, 
//    168        //then you must implement the slave_destroy() routine at a minimum 
//    169        //in order to avoid leaking memory 
//    170        //each time a device is tore down. 
//    171        //
//    172        //Status: OPTIONAL 
    173          // 
    174         int (* slave_alloc)(struct scsi_device *); 
    175 
    176         // 
//    177        //Once the device has responded to an INQUIRY and we know the 
//    178        //device is online, we call into the low level driver with the 
//    179        //struct scsi_device *.  If the low level device driver implements 
//    180        //this function, it *must* perform the task of setting the queue 
//    181        //depth on the device.  All other tasks are optional and depend 
//    182        //on what the driver supports and various implementation details. 
//    183        //
//    184        //Things currently recommended to be handled at this time include: 
//    185        //
//    186        //1.  Setting the device queue depth.  Proper setting of this is 
//    187        //    described in the comments for scsi_adjust_queue_depth. 
//    188        //2.  Determining if the device supports the various synchronous 
//    189        //    negotiation protocols.  The device struct will already have 
//    190        //    responded to INQUIRY and the results of the standard items 
//    191        //    will have been shoved into the various device flag bits, eg. 
//    192        //    device->sdtr will be true if the device supports SDTR messages. 
//    193        //3.  Allocating command structs that the device will need. 
//    194        //4.  Setting the default timeout on this device (if needed). 
//    195        //5.  Anything else the low level driver might want to do on a device 
//    196        //    specific setup basis...   98
//    197        //6.  Return 0 on success, non-0 on error.  The device will be marked 
//    198        //    as offline on error so that no access will occur.  If you return 
//    199        //    non-0, your slave_destroy routine will never get called for this 
//    200        //    device, so don't leave any loose memory hanging around, clean 
//    201        //    up after yourself before returning non-0 
//    202        //
    203        //Status: OPTIONAL 
    204          // 
    205         int (* slave_configure)(struct scsi_device *); 
    206 
    207         // 
    208        //Immediately prior to deallocating the device and after all activity 
    209        //has ceased the mid layer calls this point so that the low level 
    210        //driver may completely detach itself from the scsi device and vice 
    211        //versa.  The low level driver is responsible for freeing any memory 
    212        //it allocated in the slave_alloc or slave_configure calls. 
    213        //
    214        //Status: OPTIONAL 
    215          // 
    216         void (* slave_destroy)(struct scsi_device *); 
    217 
    218         // 
    219        //This function determines the bios parameters for a given 
    220        //harddisk.  These tend to be numbers that are made up by 
    221        //the host adapter.  Parameters: 
    222        //size, device, list (heads, sectors, cylinders) 
    223        //
    224        //Status: OPTIONAL 
    225          // 
    226         int (* bios_param)(struct scsi_device *, struct block_device *, 
    227                         sector_t, int []); 
    228 
    229         // 
    230        //Can be used to export driver statistics and other infos to the 
    231        //world outside the kernel ie. userspace and it also provides an 
    232        //interface to feed the driver with information. 
    233        //
    234        //Status: OBSOLETE 
    235          // 
    236         int (*proc_info)(struct Scsi_Host *, char *, char **, off_t, int, int); 
    237 
    238         // 
    239        //Name of proc directory 
    240          //   99
    241         char *proc_name; 
    242 
    243         // 
    244        //Used to store the procfs directory if a driver implements the 
    245        //proc_info method. 
    246          // 
    247         struct proc_dir_entry *proc_dir; 
    248 
    249         // 
    250        //This determines if we will use a non-interrupt driven 
    251        //or an interrupt driven scheme,  It is set to the maximum number 
    252        //of simultaneous commands a given host adapter will accept. 
    253          // 
    254         int can_queue; 
    255 
    256         // 
    257        //In many instances, especially where disconnect / reconnect are 
    258        //supported, our host also has an ID on the SCSI bus.  If this is 
    259        //the case, then it must be reserved.  Please set this_id to -1 if 
    260        //your setup is in single initiator mode, and the host lacks an 
    261        //ID. 
    262          // 
    263         int this_id; 
    264 
    265         // 
    266        //This determines the degree to which the host adapter is capable 
    267        //of scatter-gather. 
    268          // 
    269         unsigned short sg_tablesize; 
    270 
    271         // 
    272        //If the host adapter has limitations beside segment count 
    273          // 
    274         unsigned short max_sectors; 
    275 
    276         // 
    277        //dma scatter gather segment boundary limit. a segment crossing this 
    278        //boundary will be split in two. 
    279          // 
    280         unsigned long dma_boundary; 
    281 
    282         // 
    283        //This specifies "machine infinity" for host templates which don't 
    284        //limit the transfer size.  Note this limit represents an absolute   100
    285        //maximum, and may be over the transfer limits allowed for 
    286        //individual devices (e.g. 256 for SCSI-1) 
    287          // 
    288 #define SCSI_DEFAULT_MAX_SECTORS        1024 
    289 
    290         // 
    291        //True if this host adapter can make good use of linked commands. 
    292        //This will allow more than one command to be queued to a given 
    293        //unit on a given host.  Set this to the maximum number of command 
    294        //blocks to be provided for each device.  Set this to 1 for one 
    295        //command block per lun, 2 for two, etc.  Do not set this to 0. 
    296        //You should make sure that the host adapter will do the right thing 
    297        //before you try setting this above 1. 
    298          // 
    299         short cmd_per_lun; 
    300 
    301         // 
    302        //present contains counter indicating how many boards of this 
    303        //type were found when we did the scan. 
    304          // 
    305         unsigned char present; 
    306 
    307         // 
    308        //true if this host adapter uses unchecked DMA onto an ISA bus. 
    309          // 
    310         unsigned unchecked_isa_dma:1; 
    311 
    312         // 
    313        //true if this host adapter can make good use of clustering. 
    314        //I originally thought that if the tablesize was large that it 
    315        //was a waste of CPU cycles to prepare a cluster list, but 
    316        //it works out that the Buslogic is faster if you use a smaller 
    317        //number of segments (i.e. use clustering).  I guess it is 
    318        //inefficient. 
    319          // 
    320         unsigned use_clustering:1; 
    321 
    322         // 
    323        //True for emulated SCSI host adapters (e.g. ATAPI) 
    324          // 
    325         unsigned emulated:1; 
    326 
    327         // 
    328        //True if the low-level driver performs its own reset-settle delays.   101
    329          // 
    330         unsigned skip_settle_delay:1; 
    331 
    332         // 
    333        //Countdown for host blocking with no commands outstanding 
    334          // 
    335         unsigned int max_host_blocked; 
    336 
    337         // 
    338        //Default value for the blocking.  If the queue is empty, 
    339        //host_blocked counts down in the request_fn until it restarts 
    340        //host operations as zero is reached. 
    341        //
    342        //FIXME: This should probably be a value in the template 
    343          // 
    344 #define SCSI_DEFAULT_HOST_BLOCKED       7 
    345 
    346         // 
    347        //Pointer to the sysfs class properties for this host, NULL terminated. 
    348          // 
    349         struct class_device_attribute **shost_attrs; 
    350 
    351         // 
    352        //Pointer to the SCSI device properties for this host, NULL terminated. 
    353          // 
    354         struct device_attribute **sdev_attrs; 
    355 
    356         // 
    357        //List of hosts per template. 
    358        //
    359        //This is only for use by scsi_module.c for legacy templates. 
    360        //For these access to it is synchronized implicitly by 
    361        //module_init/module_exit. 
    362          // 
    363         struct list_head legacy_hosts; 
    364 }; 
//   ��ֱ��������,һ���ṹ��Ķ������ע�ʹӵ�40�е���364��,д�����ͬ־������,�������ôһ��
// ��̬�����ݽṹ��,��������������д�������λ������Щ���кܶ��ǵ���,��Ϊ�Ǿ�"���ڼ�į������,��
// �ڼ�į�б�̬"�������������ֵ����쾡��.����û�취,���ǻ��ü�����,ʱ��ı�Ӱ�������,���յ�����
// ������ͷ,��ʱ����������ʱ��?�����ǻ�û����ʲô������,����úø���ѩ�����ŵ�����,��������Ъ��
// ��,��������������.����Ҳ����˵ʲô��,������ṹ�������,scsi_host_template����,Ҳ����֪��,��
// ��һ��ģ��,�ܶ�������ᱻ�õ�.���кܶ�Ԫ��,��������mass storage��߶���ı���
// usb_stor_host_template��û�г�ʼ�����е�Ԫ��,ֻ�ǳ�ʼ��������һ����.ʵ��
// ��,scsi_host_template����������һ��,�������scsi host,ͨ��һ��˵,һ��scsi ��,����רҵһ��˵  102
// scsi ������,���߸�רҵ��scsi ����������,����scsi ����������,scsi �������ж��,����Linux��,ÿһ
// ��scsi����Ӧһ�����ݽṹ,Scsi_Host(��Linux�н�ͨ��ʹ��һ��scsi_host_template�ṹָ��Ϊ��
// ���ĺ�����ΪScsi_Host��ʼ��),������ЩScsi_Host��Ӧ�Ĳ�������ʵ��scsi ��,Ӳ���ϲ�������,��
// ��Ȼ��Ҫһ��Scsi_Host,�������ǵ�u��,��Ϊ���ñ�ģ���scsi�豸,���Ե�Ϊ��׼��һ��scsi��,����
// ��scsi ��.����ղ�cat /proc/scsi/scsi �����,��U�̵����,��ʾ��scsi ��Ϣ���������ôһ��,����
// ����,Host��Ҳ����һ��,ԭ��Hostֻ�� scsi0,scsi1,�����ڶ����һ��scsi3.�����scsi3��ʵ����һ
// �������scsi ��.����,Ϊ�˴�����ôһ�������scsi �������ݽṹ,������
// drivers/usb/storage/scsiglue.c�ж����˽ṹ�����struct scsi_host_template 
// usb_stor_host_template. 
//   ʵ����Scsi_HostҲ��һ����̬�����ݽṹ,���ǽ����½ڽ�ϸղ��ᵽ�ĺ���scsi_host_alloc����
// ����Щ��̬�����ݽṹ.���˰�,û�취,����ô�ิ�ӵ����ݽṹ��ǰ,Ҳ��ֻ���������������<<�ּ�һ
// ������>>�е���Ƶ��Ƕξ��������13�����εĶ԰ײ��ܱ�����Ǵ˿̵������. 
// Scsi ���ݽṹ-������������� 
//   ����scsi,����˵����,��Linux�ں���,����scsi ��ϵͳ����Ϊ����.upper level,mid level,lower 
// level,Ҳ��������������ܷ�,LinuxΪʲô��ô�鷳��.����ĳλ������˵��:�治����,Ů����ܶ�ܶ�Ư
// ���·���,����Ϊ�������к���Ŀ��,���к��뿴��,ȴ�ǲ����·���Ů��.ʵ����,Linux�������ǰ�scsi ��
// ϵͳ��װ�ɺܶ��,��Ϊ�˸����ṩ����,�������������ʱ��ȴ��о��ܷ�,Ҫ��û����ô���ö��. 
//   ��˵˵�������,upper level,��ΰ��ĺ�������,�������ϲ�,���ǺͲ���ϵͳ�򽻵���,������Ҫ����
// һ��scsi Ӳ��,��ô������Ҫʹ��sd_mod.o��ôһ��ģ��,��ʵ��������Ӳ���޹ص�,�Ǵ��������ϵ�
// ������������ݽṹ�齨��ģ��.mid level,�в�,ʵ���������������ĺ��Ĳ�,�������˳�scsi-core,��
// scsi���Ĳ�,���ṩ��֧��scsi�ĺ������ݽṹ�ͺ���,��һ���Ӧ��ģ����scsi_mod.o,ϵͳ��Ҫ��ʹ��
// scsi �豸,���ȱ��������,������,ֻ�����е�scsi �豸��ģ�鶼��ж���˲��ܹ�ж����.½�ξ��������
// ��scsi ���Ĳ�,���������,һ��Ⱥ����. 
// Ȼ��,��lower level,�ײ�.�ܲ���,�����Ҫд����,�˳ɾ���д�ĵײ�,������ʵ�е�����һ��,��������
// �����ײ�.��Ϊupper level ��mid level���Ѿ�������ȷ����,���Ǻ�Ӳ��û��ϵ.����������������ֻ
// ���ǵײ�.��ʵ��������,�����80�����˵,�����ѹ����80�󲻿�������70������,������ֻ�����
// ��ʵ. 
//   ��Ȼ����Ҫ��ע���ǵײ�,��ô�ײ���в����˵scsi ���Ĳ�����δ򽻵�����?��������֪��,���Ĳ�
// �ṩ�˺ܶຯ�����ײ�ʹ��,������һ�ڼ�����scsi_host_alloc()�������Ǻ��Ĳ��ṩ��,���滹������
// ��һЩ����Ҳ�����в�,����scsi �в��ṩ�ĺ���,���ǲ���Ҫȥ�������������ʵ�ֵ�,ֻ������������
// ����.��include/scsi/scsi_host.h��,����ôһ��, 
// 527 extern struct Scsi_Host *scsi_host_alloc(struct scsi_host_template *, int); 
// ���Կ�����������Ĳ�����һ����struct scsi_host_template�ṹ���ָ��,����������һ��
// struct Scsi_Host�ṹ���ָ��,����һ��,ǰ�����ǵ�������������Ǿ�, 
// 790         us->host = scsi_host_alloc(&usb_stor_host_template, sizeof(us));   103
// ƾһ�����˵�ֱ��,���Բ³�,�������������һ��Scsi_Host�ṹ��,������ָ������ָ�븳��
// us->host.�Ӹ�һ��ĽǶ���˵,��ôһ�仰ʵ���Ͼ�����scsi���Ĳ�ע����һ��scsi��,��Ȼ�����scsi
// ���������.˳��������us->host.��ʵ���Ͼ���һ��struct Scsi_Host�ṹ���ָ��,��struct 
// Scsi_Host����һ����̬�����ݽṹ,���Ķ�����include/scsi/scsi_host.h��: 
376 struct Scsi_Host { 
    377         // 
    378        //__devices is protected by the host_lock, but you should 
    379        //usually use scsi_device_lookup / shost_for_each_device 
    380        //to access it and don't care about locking yourself. 
    381        //In the rare case of beeing in irq context you can use 
    382        //their __ prefixed variants with the lock held. NEVER 
    383        //access this list directly from a driver. 
    384          // 
    385         struct list_head        __devices; 
    386 
    387         struct scsi_host_cmd_pool *cmd_pool; 
    388         spinlock_t              free_list_lock; 
    389         struct list_head        free_list; // backup store of cmd structs // 
    390         struct list_head        starved_list; 
    391 
    392         spinlock_t              default_lock; 
    393         spinlock_t              *host_lock; 
    394 
    395         struct semaphore        scan_mutex;// serialize scanning activity // 
    396 
    397         struct list_head        eh_cmd_q; 
    398         struct task_struct  //ehandler;  // Error recovery thread. // 
    399         struct semaphore    //eh_wait;   // The error recovery thread waits 
    400                                               on this. // 
    401         struct completion   //eh_notify; // wait for eh to begin or end // 
    402         struct semaphore    //eh_action; // Wait for specific actions on the 
    403                                           host. // 
    404         unsigned int            eh_active:1; // Indicates the eh thread is awake 
and active if 
    405                                           this is true. // 
    406         unsigned int            eh_kill:1; // set when killing the eh thread // 
    407         wait_queue_head_t       host_wait; 
    408         struct scsi_host_template *hostt; 
    409         struct scsi_transport_template *transportt; 
    410         volatile unsigned short host_busy;   // commands actually active on 
low-level // 
    411         volatile unsigned short host_failed; // commands that failed. // 
    412   104
    413         unsigned short host_no;  // Used for IOCTL_GET_IDLUN, /proc/scsi et al. 
// 
    414         int resetting; // if set, it means that last_reset is a valid value // 
    415         unsigned long last_reset; 
    416 
    417         // 
    418        //These three parameters can be used to allow for wide scsi, 
    419        //and for host adapters that support multiple busses 
    420        //The first two should be set to 1 more than the actual max id 
    421        //or lun (i.e. 8 for normal systems). 
    422          // 
    423         unsigned int max_id; 
    424         unsigned int max_lun; 
    425         unsigned int max_channel; 
    426 
    427         // 
    428        //This is a unique identifier that must be assigned so that we 
    429        //have some way of identifying each detected host adapter properly 
    430        //and uniquely.  For hosts that do not support more than one card 
    431        //in the system at one time, this does not need to be set.  It is 
    432        //initialized to 0 in scsi_register. 
    433          // 
    434         unsigned int unique_id; 
    435 
    436         // 
    437        //The maximum length of SCSI commands that this host can accept. 
    438        //Probably 12 for most host adapters, but could be 16 for others. 
    439        //For drivers that don't set this field, a value of 12 is 
    440        //assumed.  I am leaving this as a number rather than a bit 
    441        //because you never know what subsequent SCSI standards might do 
    442        //(i.e. could there be a 20 byte or a 24-byte command a few years 
    443        //down the road?). 
    444          // 
    445         unsigned char max_cmd_len; 
    446 
    447         int this_id; 
    448         int can_queue; 
    449         short cmd_per_lun; 
    450         short unsigned int sg_tablesize; 
    451         short unsigned int max_sectors; 
    452         unsigned long dma_boundary; 
    453 
    454         unsigned unchecked_isa_dma:1; 
    455         unsigned use_clustering:1;   105
    456         unsigned use_blk_tcq:1; 
    457 
    458         // 
    459        //Host has requested that no further requests come through for the 
    460        //time being. 
    461          // 
    462         unsigned host_self_blocked:1; 
    463 
    464         // 
    465        //Host uses correct SCSI ordering not PC ordering. The bit is 
    466        //set for the minority of drivers whose authors actually read 
    467        //the spec ;) 
    468          // 
    469         unsigned reverse_ordering:1; 
    470 
    471         // 
    472        //Host has rejected a command because it was busy. 
    473          // 
    474         unsigned int host_blocked; 
    475 
    476         // 
    477        //Value host_blocked counts down from 
    478          // 
    479         unsigned int max_host_blocked; 
    480 
    481         // legacy crap // 
    482         unsigned long base; 
    483         unsigned long io_port; 
    484         unsigned char n_io_port; 
    485         unsigned char dma_channel; 
    486         unsigned int  irq; 
    487 
    488 
    489         unsigned long shost_state; 
    490 
    491         // ldm bits // 
    492         struct device           shost_gendev; 
    493         struct class_device     shost_classdev; 
    494 
    495         // 
    496        //List of hosts per template. 
    497        //
    498        //This is only for use by scsi_module.c for legacy templates. 
    499        //For these access to it is synchronized implicitly by   106
    500        //module_init/module_exit. 
    501          // 
    502         struct list_head sht_legacy_list; 
    503 
    504         // 
    505        //Points to the transport data (if any) which is allocated 
    506        //separately 
    507          // 
    508         void *shost_data; 
    509         struct class_device transport_classdev; 
    510 
    511         // 
    512        //We should ensure that this is aligned, both for better performance 
    513        //and also because some compilers (m68k) don't automatically force 
    514        //alignment to a long boundary. 
    515          // 
    516         unsigned long hostdata[0]  // Used for storage of host specific stuff // 
    517                 __attribute__ ((aligned (sizeof(unsigned long)))); 
    518 }; 
// ��Ҫ��һ��������Ԫ��,hostdata[0],����������Ȥ����__attribute__,����gcc�Ĺؼ���.����
// ������,��������,����,���͵�����,����Ȼ̷��ǿ����C ����������ǲ�����������ն���,��ʵ�ϴ��
// ����Ҳ�ò���֪����.������gcc����,�����ֵĺ�Ƶ��,��Ϊ�������ڴ����Ż��ʹ�����,�ر��ǵ�����
// ��д����һ��Ҫ�ڸ���Ӳ��ƽ̨�����еĲ���ϵͳ��ʱ��,��Щ�������൱���б�Ҫ��.ͨ��
// __attribute__(����attributeǰ������� underscore,���»���.)�����ڶ���һ������/����/���͵�ʱ
// ��,�������ڱ���/����/���Ͷ���ĺ���,�˴����ǿ�����__attribute__�ǽ�����unsigned long 
// hostdata[0]����һ������(��,�����Ȼֻ��һ��Ԫ��)����,�����ÿһ��Ԫ����һ��unsigned long��
// ���ͱ���,__attribute__����������������������,gccһ��֧��ʮ��������,����aligned��һ��,����
// ����һЩ���õ�,����packed,noreturn,��packed��ʵ����ǰ�����,ֻ��û������.���ڽ�һ��
// aligned���Ժ�packed����.���������Ǻ��ֽڶ����йص�����,ǰЩ����intel��microsoft��Щ�����
// ��������Ŀ�г������ֽڶ���Ķ���,�������źܶ��˶��ֽڶ��벢��İ��.�����֮,�ֽڶ�������ôһ��
// ��,����������ڴ��б���������ν��ô�ŵ�,��Ϊ��ô�Ŷ��ܷ��ʵ�,���ǲ�ͬ��Ӳ�������ڴ�ķ�ʽ��һ
// ��,ֻ�аѱ������ض��Ĺ��������ڴ���,��ȡЧ�ʲŻ��,���򲻰�����Ĵ�ű������п��ܽ��ͱ�����
// ȡЧ��.�ܶ������,���ǲ��������ֽڶ���,��Ϊͨ����Щ�����ɱ�����������,�������ܱ�ѩ,��֪�����
// ʲôƽ̨����ζ���.����ʱ��,������Ҫ��ʽ��ȥ�趨���뷽ʽ,��Ϊ��ʱ�����ǶԱ�������������Ϊ����
// ����,���������Լ������Լ�ָ���ķ�ʽ�����,����˴�,�ڶ���hostdata֮ǰ�ļ���ע��,�Ѿ��������
// ˵����Ϊɶ����Ҫ��ʽ��ȥָ�����뷽ʽ.������˵,unsigned long hostdata[0] __attribute__ 
// ((aligned (sizeof(unsigned long))))���Ǳ�ʾhostdata[0]����sizeof(unsigned long)�ֽڶ���,��
// Ȼ��ͬ��Ӳ��ƽ̨sizeof(unsinged long)�ǲ�һ����.��֮ǰ�������������Ǹ�������
// include/linux/usb_ch9.h�е�struct usb_device_descriptor�Լ�struct 
// usb_interface_descriptor�ṹ��,������������ôһ��:__attribute__ ((packed)),�����ʾʹ��
// ��С���ܵĶ���,��packed��������˼Ҳ�����,����һ��,��Ϲ���ռ�,ʵ������Ҳ���Ǹ���������һ��
// ����,���߱�����,��,һ���ʡһ��,���˷ѿռ䰡.   107
//   ��,������Scsi_Host���ݽṹ,���Ǽ����ص���������usb_stor_acquire_resources()������
// ��,us->host�õ�������Ҫ��,Ȼ������798��,ֻ��һ�丳ֵ,��us->host->hostdata[0]��ֵΪ
// (unsigned long)us,��������ʲô�����Ǻ�����������˵. 
//   ��֮,scsi_host_alloc()��ôһ����,���Ǹ����ǵ�struct Scsi_Host�ṹ�������˿ռ�,����Ҫ��
// ģ��һ��scsi ���龰,��Ҫ��������,scsi_host_alloc(),scsi_add_host(),scsi_scan_host().ֻ�е���
// �˵ڶ�������֮��,scsi ���Ĳ��֪������ôһ��host�Ĵ���,��ֻ�е�����������������֮��,��������
// ���ű�����.��Щ�����ĺ�������ǵ������Ǻϵĺܺ�.������? 
// �����Ҫָ������,scsi_host_alloc()��Ҫ��������,��һ��������struct scsi_host_template ��
// ָ��,���ǵ�Ȼ������&usb_stor_host_template,���ڶ�������ʵ�����Ǳ���Ϊdriver�Լ�������,��
// �Ǵ��ݵ���sizeof(us).������,scsi_host_alloc()�оͻ�����������ڴ�ռ�,��Ϊus�����ڴ�ռ�.��
// ����Ȥ����,us�������������˿ռ�,���������һ���Ƿ��б�Ҫ��?ע�⵽struct Scsi_Host��߲���
// ��һ��hostdataô,������������,struct us_data���������������usb-storageģ�����ר�Ŷ����,
// ��һ�����Ǻ�scsi ��򽻵�,����Ҫע��һЩ����,�ṩ��scsi ���Ĳ�,�ú��Ĳ�ȥ����,��Щ����ԭ�����
// ��scsi��˵�����,scsi��׼����һЩ����ָ��,����ֻ�ǰ���Щָ�븳��ֵ,scsi���֪����ʲôʱ��õ�
// ���ĸ�������.���Լ�Ȼԭ�����˼��ṩ��,��ô�˼ҿ϶���֪�����ǻ���һ��struct us_data��ôһ����
// ����,���������ڶ��庯����ʱ��Ͳ��ܰ�struct us_data����һ������,��������ר��Ϊ�Լ����ģ��׼
// ���Ľṹ���ֲ����ܲ���,����ô��?�ð�,scsi���Ĳ�����struct Scsi_Host����ṹ���,������ṹ��
// ����Ƶ�ʱ���ר��׼����һ��unsigned long hostdata[0]��������豸����ʹ��.�����ǻ�����ʲô,
// �����ָ��ָ�����ǵ�us�Ϳ�����.�Ժ�Ҫ��us��ͨ��hostdata[0]����þ�����.���Ըղ����ǿ�����
// us->host->hostdata[0]����ֵΪ(unsigned long)us.���host��������֮���һֱ�õ���struct 
// Scsi_Host�ṹ��,hostdata[0]��һ��unsigned long�ı���,us��һ��ָ��,�������ʹ�����������
// ֵ�������ָ��ָ��ĵ�ַ.��֮�����ǻᾭ������scsiglue.c�еĺ������ʹ�����µĸ�ֵ���: 
// struct us_data *us = (struct us_data *) host->hostdata[0]; 
// ������˼�ͺ���ȷ��.ָ�뱻����Ϊԭ��us ��ָ����Ǹ���ַ.���Կ����ֶ�����һ��struct 
// us_data *us,ʵ����ֻ������ԭ����һ��ȫ�ֱ���,������һ���ֲ���������.������scsi_host_alloc()
// ����������һ�δ�СΪsizeof(us)���ڴ�,��Ȼ�Ѿ����ڴ��˾�û�б�Ҫ������,ֻ�ǽ���hostdata ���
// ָ�����.��Ȼ,��������̫����,�˷��ڴ�,���ҵ�����������ֵļ�����ص���������Υ����,���ҵ����
// ǿ���Լ��ܶ�Ϊ��,�Խ�������Ϊ�ܵı�����,��δ�����Ȼ�⵽�˹������Ⱥ�ڵ�����,��˺�������,
// �����°汾��Linux�ں�����δ��뱻�޸���(�ý������еĻ�˵���Ǳ���г����).����Ȥ��ͬ־�ǿ���
// ��עһ��2.6.22����ں�. 
// �������,����һ��,Ϊʲôscsi_host_alloc���ݽ�������һ��struct scsi_host_templateָ��,
// �����ص�ȷ��һ��struct Scsi_Hostָ��?����,�������ṹ������ܶ���ͬ��Ԫ��,���ֲ���ȫ��ͬ,����
// Эͬ����,�������,���Ǹ���������ò�һ��,struct Scsi_Host�ṹ������һ����Ա,����һ��struct 
// scsi_host_templateָ��,����ָ�������������Ǹ�template,��struct scsi_host_template�к�
// �������ָ��,���ǵĲ�������struct Scsi_Host��ָ��.������֮��Ĺ�ϵǧ˿����,����������,ź��
// ˿����.һ�㲻���ڲ�خ������<<����>>���Ǹ��ӵ������ϵ,Ψһ�Ĳ��ֻ������û�����׹�ϵ����.
// ����,����Щ,���ָ��ӵĹ�ϵ���ǲ���Ҫȥ��ȫ�˽�,����Ҫ����ֻ��֪������������ҽ���һ��struct 
// Scsi_Host���ҽ���һ��struct scsi_host_template�Ϳ�����.   108
// ����,���������ߵ���usb_stor_acquire_resources()�е�801��,�����������ǧ����ʼ������
// �ں˾���. 
// �˰����Ĵ�˵(һ) 
// �˰���,�����Ǳ��˵Ļ���. 
// �ܾúܾ���ǰ,���еı�Ե�����˴�Ƭ��Ƭ������ɳ��,���Ļ�����һ��ħ��,�������������Լ�ǰ������
// ��.�ػ�����ɳ��������������,һ���ǻ���������,һ����Ҷ����ɳ��.�����غ��˼�ǧ��,���Ǵ���û�м�
// ����,��Ϊ������ʱ��,��û��Ҷ��,��Ҷ�ӵ�ʱ��û�л�.���Ƿ��������ű˴�,��������ʹ����ĥ��.��
// ����һ��,���Ǿ���Υ����Ĺ涨͵͵�ؼ�һ����.��һ�������ɳ�������޵Ļ������۵���ɫ������,����
// ������ұ����. 
// �����ɳ���ܵ��ͷ�,�������ֻ�,����������ԶҲ������һ��,�����������������ܵ�ĥ��.�����Ժ�,��
// ��ɳ���ֽб˰���,��˼�ǿ���������Ļ�,���Ļ�����״��һֻֻ����������������,������Ҳû������
// �����г��ֹ�.ÿ�����˰��ڼ�(����ǰ������д��˰�,���ǰ���������˰�)���Ὺ�ڻ�Ȫ·��,����
// ��ɳ����ÿһ��ת���ڻ�Ȫ·���ŵ��˰�������ζ��������ǰ���ĵ��Լ�,Ȼ���Ĳ��ֿ�,��ֻ������һ
// ��,��Ϊ���ǻ��ٴε���������ֻ�,��꼮�����⻨��ָ��,������ڤ���� 
// ��Ϊ�˼�����������������˵Ĵ�˵,Linux�ں����������ػ�����,Ҳ�����������˵��Ӧ,�ػ�����Ҳ
// ���ں˾���,��Ȼ,�����������Ƕ�̫����,�����ǹ�����Ա,����������,��ôok,����Խ���Ϊ�ں��߳�.
// ��ʵ����Ҳ����������,������ֻ���ڰ��������һ��.������������Ĵ���. 
// 801��,������kernel_thread()����,kernel_thread(usb_stor_control_thread, us, CLONE_VM),
// ��������ֵ��һ�����ͱ���p����ʾ,�����ǰ�����ں˱����Ǻ���Ϥ,����������ͻ������е�ͷ����.
// ����������ᴴ��һ���ں��߳�,������usb_stor_control_thread()����ִ��,us���Ǵ��ݸ����Ĳ�
// ��,CLONE_VMֻ���趨��һ��flag,��Linux�ں˲��Ǻ���Ϥ�Ļ�,���Խ�kernel_thread����������
// fork�Ķ���,ʲô?fork��Ҳ��֪��?�ð�.��֪���Ͳ�֪��,ֻ����ϡ�ǵ����Ǳ�ҵ��ְ��������,�ܶ�����
// �ı��������ж�������fork,��һЩ�������ķ���ֵ������,ӡ����,2004��ά�������У԰��Ƹ�����п�
// ��,������ȥSun�й������о�Ժ����Ҳ�������. ʵ����,��һ��˵,kernel_thread()��ôһִ����,
// �ͻ�����������,һ���Ǹ�����,һ�����ӽ���,�ӽ��̽���ִ��usb_stor_control_thread(),��us����
// Ϊusb_stor_control_thread�����Ĳ���(ʵ��),CLONE_VM��־�������ӽ���֮�乲���ַ�ռ�,ִ��
// ��usb_stor_control_thread()֮��,�ӽ��̾ͽ�����,�������exit()�����˳�.�������̼���˳��
// usb_stor_acquire_resources()����������,kernel_thread()�������ڸ����̶��Է��ص����ӽ��̵�
// ����id,����802�����ж�,���Ƿ���ֵp С��0,��˵��������,����,�ǾͰ�p����us ��Ԫ��pid. 
// ����,���ǽ����������ٴα�����·,�ֱ���ٸ����̺��ӽ���ǰ����.�ȿ�������,810��,ִ��
// wait_for_completion(&(us->notify)),�����˵wait_for_completion��˭?�����Ѿ���������,��ô
// ��������ĵ�.�ǵ����ǵ������ύurb��ʱ����ù�����?���ǳ�ʼ����һ���ȴ�����,urb->done,Ȼ��
// �����ύ��urb,Ȼ������ͨ������wait_for_completion(&urb->done)�����˵ȴ�,������˯��,��urb
// ��usb core��������,����˵��urb host controller��������,complete()�������ᱻ����,�Ӷ�������
// ���Ǹ�����˯�ߵĽ���.���Դ˴�Ҳһ��,us->notify���ں��������ǰstorage_probe()�����г�ʼ��
// ��,�ú�����945��,init_completion(&(us->notify)),��struct us_data��,����ôһ��Ԫ��notify,
// ��struct completion�ṹ�����,����������,�����̽�����˯��,˭��������?û��,���ܴ���,�����ӽ�  109
// ��,Ҳ������usb_stor_control_thread()������,����complete(&(us->notify))��ôһ
// ��,wait_for_completion()��complete()��һ����÷����ĺ���,��������һ����,һ�����ý��̽���
// ˯��,��һ��������������˯�ߵĽ��̻���,�����֪���ź����Ļ�,���Ǿ��������ź����е�
// down()/up()������,ֻ�������Ǹ��Ӱ�ȫ. 
// ��,�������ȸ�һ��,����������˯����,û�˻������Ļ�,���ǲ��������ߵ�.�����ӽ���,Ҳ����
// usb_stor_control_thread()����,�������������drivers/usb/storage/usb.c��.������һ��������
// �������,����,��Ϣ,��Ϣһ��... 
// �˰����Ĵ�˵(��) 
// ����ù��ڶ���ͶƱ�Ļ�,usb_stor_control_thread()��������еĴ�������������ģ������Ϊ����
// �Ĵ���.����ֻ��Ҫ���м�301���Ǹ�for(;;)��֪��,����һ����ѭ��,��ʹ��Ĵ��붼ִ������,��ʹ���
// �������˳���,���������Ȼ���������ŵĵ粨һ��,���䳣פ.��Ȼ,ֻ����ѭ�����ܴ�������.���ܴ�����
// ��.����ÿһ���ػ��ߵ�ְ��. 
usb_stor_control_thread(),���������: 
281 static int usb_stor_control_thread(void * __us) 
    282 { 
    283         struct us_data *us = (struct us_data *)__us; 
    284         struct Scsi_Host *host = us->host; 
    285 
    286         lock_kernel(); 
    287 
    288         // 
    289        //This thread doesn't need any user-level access, 
    290        //so get rid of all our resources. 
    291          // 
    292         daemonize("usb-storage"); 
    293 
    294         current->flags |= PF_NOFREEZE; 
    295 
    296         unlock_kernel(); 
    297 
    298         // signal that we've started the thread // 
    299         complete(&(us->notify)); 
    300 
    301         for(;;) { 
    302                 US_DEBUGP("*** thread sleeping.\n"); 
    303                 if(down_interruptible(&us->sema)) 
    304                         break; 
    305 
    306                 US_DEBUGP("*** thread awakened.\n");   110
    307 
    308                 // lock the device pointers // 
    309                 down(&(us->dev_semaphore)); 
    310 
    311                 // if us->srb is NULL, we are being asked to exit // 
    312                 if (us->srb == NULL) { 
    313                         US_DEBUGP("-- exit command received\n"); 
    314                         up(&(us->dev_semaphore)); 
    315                         break; 
    316                 } 
    317 
    318                 // lock access to the state // 
    319                 scsi_lock(host); 
    320 
    321                 // has the command timed out *already* ? // 
    322                 if (test_bit(US_FLIDX_TIMED_OUT, &us->flags)) { 
    323                         us->srb->result = DID_ABORT << 16; 
    324                         goto SkipForAbort; 
    325                 } 
    326 
    327                 // don't do anything if we are disconnecting // 
    328                 if (test_bit(US_FLIDX_DISCONNECTING, &us->flags)) { 
    329                         US_DEBUGP("No command during disconnect\n"); 
    330                         goto SkipForDisconnect; 
    331                 } 
    332 
    333                 scsi_unlock(host); 
    334 
    335                 // reject the command if the direction indicator 
    336                //is UNKNOWN 
    337                  // 
    338                 if (us->srb->sc_data_direction == DMA_BIDIRECTIONAL) { 
    339                         US_DEBUGP("UNKNOWN data direction\n"); 
    340                         us->srb->result = DID_ERROR << 16; 
    341                 } 
    342 
    343                 // reject if target != 0 or if LUN is higher than 
    344                //the maximum known LUN 
    345                  // 
    346                 else if (us->srb->device->id && 
    347                                 !(us->flags & US_FL_SCM_MULT_TARG)) { 
    348                         US_DEBUGP("Bad target number (%d:%d)\n", 
    349                                   us->srb->device->id, us->srb->device->lun); 
    350                         us->srb->result = DID_BAD_TARGET << 16;   111
    351                 } 
    352 
    353                 else if (us->srb->device->lun > us->max_lun) { 
    354                         US_DEBUGP("Bad LUN (%d:%d)\n", 
    355                                   us->srb->device->id, us->srb->device->lun); 
    356                         us->srb->result = DID_BAD_TARGET << 16; 
    357                 } 
    358 
    359                 // Handle those devices which need us to fake 
    360                //their inquiry data // 
    361                 else if ((us->srb->cmnd[0] == INQUIRY) && 
    362                             (us->flags & US_FL_FIX_INQUIRY)) { 
    363                         unsigned char data_ptr[36] = { 
    364                             0x00, 0x80, 0x02, 0x02, 
    365                             0x1F, 0x00, 0x00, 0x00}; 
    366 
    367                         US_DEBUGP("Faking INQUIRY command\n"); 
    368                         fill_inquiry_response(us, data_ptr, 36); 
    369                         us->srb->result = SAM_STAT_GOOD; 
    370                 } 
    371 
    372                 // we've got a command, let's do it! // 
    373                 else { 
    374                         US_DEBUG(usb_stor_show_command(us->srb)); 
    375                         us->proto_handler(us->srb, us); 
    376                 } 
    377 
    378                 // lock access to the state // 
    379                 scsi_lock(host); 
    380 
    381                 // indicate that the command is done // 
    382                 if (us->srb->result != DID_ABORT << 16) { 
    383                         US_DEBUGP("scsi cmd done, result=0x%x\n", 
    384                                    us->srb->result); 
    385                         us->srb->scsi_done(us->srb); 
    386                 } else { 
    387 SkipForAbort: 
    388                         US_DEBUGP("scsi command aborted\n"); 
    389                 } 
    390 
    391                 // If an abort request was received we need to signal that 
    392                //the abort has finished.  The proper test for this is 
    393                //the TIMED_OUT flag, not srb->result == DID_ABORT, because 
    394                //a timeout/abort request might be received after all the   112
    395                //USB processing was complete. // 
    396                 if (test_bit(US_FLIDX_TIMED_OUT, &us->flags)) 
    397                         complete(&(us->notify)); 
    398 
    399                 // finished working on this command // 
    400 SkipForDisconnect: 
    401                 us->srb = NULL; 
    402                 scsi_unlock(host); 
    403 
    404                 // unlock the device pointers // 
    405                 up(&(us->dev_semaphore)); 
    406         } // for (;;) // 
    407 
    408         // notify the exit routine that we're actually exiting now 
    409        //
    410        //complete()/wait_for_completion() is similar to up()/down(), 
    411        //except that complete() is safe in the case where the structure 
    412        //is getting deleted in a parallel mode of execution (i.e. just 
    413        //after the down() -- that's necessary for the thread-shutdown 
    414        //case. 
    415        //
    416        //complete_and_exit() goes even further than this -- it is safe in 
    417        //the case that the thread of the caller is going away (not just 
    418        //the structure) -- this is necessary for the module-remove case. 
    419        //This is important in preemption kernels, which transfer the flow 
    420        //of execution immediately upon a complete(). 
    421          // 
    422         complete_and_exit(&(us->notify), 0); 
    423 } 
// 284��,������һ��Scsi_Host��ָ��host,����ָ��us->host,Ҳ���Ǹո���scsi_host_alloc()
// ������Ǹ�Scsi_Host�ṹ�����. 
// 292��,daemonize("usb-storage"),��ʵ,��仰������������������̵�,daemonize()��������
// �ں˵ĺ���λ��,kernel/exit.c��,���������ôһ������,��һ����ͨ�Ľ���ת����Ϊ�˾������,������
// �����ǿ��Բ�ȥ�������̵�ԭ��,�������ǿ�����Ϊ��仰û�����κ�����,ֻ�ǴӴ�֮������ps����
// һ���ܹ�������һ������usb-storage�Ľ���.����������������: 
// localhost:~ # ps -el 
F S   UID   PID  PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD 
4 S     0     1     0  0  76   0 -   195 -      ?        00:00:02 init 
1 S     0     2     1  0 -40   - -     0 migrat ?        00:00:00 migration/0 
1 S     0     3     1  0  94  19 -     0 ksofti ?        00:00:00 ksoftirqd/0 
1 S     0    18     1  0  70  -5 -     0 worker ?        00:00:00 events/0 
1 S     0    26     1  0  71  -5 -     0 worker ?        00:00:00 khelper   113
1 S     0    27     1  0  70  -5 -     0 worker ?        00:00:00 kthread 
1 S     0    45    27  0  72  -5 -     0 worker ?        00:00:00 kacpid 
1 S     0   229    27  0  80   0 -     0 pdflus ?        00:00:00 pdflush 
1 S     0   230    27  0  75   0 -     0 pdflus ?        00:00:00 pdflush 
1 S     0   231     1  0  76   0 -     0 kswapd ?        00:00:00 kswapd0 
1 S     0   961    27  0  70  -5 -     0 scsi_e ?        00:00:00 scsi_eh_0 
1 S     0  1033    27  0  70  -5 -     0 scsi_e ?        00:00:00 scsi_eh_1 
1 S     0  1045    27  0  71  -5 -     0 scsi_e ?        00:00:00 scsi_eh_2 
1 S     0  1047    27  0  70  -5 -     0 worker ?        00:00:00 scsi_wq_2 
5 S     0  1262     1  0  72  -4 -  1774 -      ?        00:00:02 udevd 
1 S     0  1939    27  0  70  -5 -     0 hub_th ?        00:00:00 khubd 
1 S     0  7804    27  0  70  -5 -     0 scsi_e ?        00:00:00 scsi_eh_3 
1 S     0  7805    27  0  70  -5 -     0 -      ?        00:00:00 usb-storage 
4 S     0 13905 13902  0  75   0 -  2430 wait   pts/1    00:00:00 bash 
0 R     0 19098 13905  0  77   0 -   821 -      pts/1    00:00:00 ps 
// ��Ȼ,�����ն˰�ctrl-c�ǲ�������ֹ���usb-storage���̵�.���Ǿ��������������е�һ��,����
// ���ں�̨.��һ��kill -9�ӽ��̺�,������ɱ������?(ϵͳ�������ҿɲ�����Ŷ...) 
// 294��,����ΪĿǰ�Ľ�������һ��flag,PF_NOFREEZE,�������ں˴�����,���flagҲֻ���ֹ�����.
// ���flag�����Դ������ص�,2.6���ں�Ϊ��ʵ����Windows���Ƶ�һ������,Hibernate,Ҳ����"��
// ��",(��˵����֪��,Windows�ػ�ѡ��������"�ػ�","����","ע��","Stand by",�Լ�"Hibernate").��
// �ں˱���˵�����,Power managerment options��,��һ��ѡ��Software Suspend,Ҳ�����ں˱���
// ѡ���е�CONFIG_SOFTWARE_SUSPEND,ѡ������ʹ�û������Ա�suspended.��Ȼ���ǲ���care
// ��. ��������֮����Ҫ�������flag,����ΪsuspendҪ����ڴ���Ķ���д��������,��һ������������
// ���flag�ͱ�������suspend��ʱ�򲻻ᱻ��ס,���л���������,they��re not refrigerated during a 
// suspend.freeze�����䶳,��ס����˼,��ȥ�ִ�frozen�����ݴ�,�����,������,��ʵ�����ý���˯��.
// �����ܵ���˵,�������������˵,��ʹϵͳsuspend��,�������,����׼ȷ��˵,����ں��߳�,Ҳ��Ӧ��
// ����˯��. 
// Ҫִ��������������Ҫִ��lock_kernel()/unlock_kernel()��һ�Ժ���.Ȼ��299��,ִ��complete
// ����ǰ���ǽڵĸ�����.���ӽ��̲����˳�,����������,����Թ�޻ڵ�����,ֻ����������������Ϊ׷Ѱ��
// �������㼣�����е������ó�,���˴��ӽ���(ִ)�е������ں˵��ػ�.������ʹһ��,�ػ����İ�����. 
// ��������Ҳ��������������,299��, complete(&(us->notify)),�����Ǻ͸ղ��ڸ������￴�����Ǿ�
// ʹ���̽���˯�ߵ�wait_for_completion(&(us->notify))���Ӧ,������Ȼ�ǻ��Ѹ�����,�����ȼ�����
// һ���ӽ���,�Ժ�����ȥ��������. 
// 301��,һ��for�����ѭ��,�������������ܾ���,��������ȥ����for���������Ҳ����. 
// 303��,down_interruptible()����,��ʵ��302�е�ע���Ѿ���������,thread������˯����...,Ҳ��
// ������.down_interruptible�Ĳ�����&us->sema,��İ����,����֮ǰ���ź�������������ʱ����Ѿ�
// �����us->sema.��������ܼ�,�������������,���Ǳ�����,���ǵ����ͽ��ܹ�,�����һ��ʼ�ͱ�
// ��ʼ��Ϊ0��,Ҳ����˵����������ָ��Ϊ�������,һ������������͸��߱����Լ��Ѿ�������������.��  114
// ��,����ֻ�ܽ���˯��,�ȴ�һ��up()����ȥ�ͷ���.˭�����up()������?��ʱ�Ȳ�����,�����ȹ�עһ��
// ������,�Ͼ������Լ�������˯��,��֮ǰ���ǰѸ����̻�����. 
// �˰����Ĵ�˵(��) 
// ң�빫誵���,С�ǳ�����,����Ӣ��. 
//   �����ڽ�,̸Ц��,���ֻҷ�����. 
//   �ʹ�����,����ӦЦ��,��������, 
//   ��������,һ�׻�������. 
//   ��ȷ,��������,���Linux���������طǳ��Ͽ����ֹ۵�,��Ϊ������Ȼ������˼�����뵽�˴�����ȥ,
// �����ڴ��������ǳ�����˯��,����,˯��,����...����Ϊ����Ĵ�ѧ��,Linus���Ҳ����ͬ��ѧ�������
// ״,����ѧ�������˯��,ֻ���е���������˯,�е���һ����˯. 
// ǰ���Ѿ�˵��,�������ں���usb_stor_acquire_resources()���,810
// ��,wait_for_completion(&(us->notify)),����˯��,���ղ��������ӽ������Ѿ���
// ��,complete(&(us->notify))������,���Ǹ����̱�����,�ص�usb_stor_acquire_resources()������,
// ������,812��,����,Ψ���ض�.������0.�����������ڻص���storage_probe()��������. 
//   1001��,scsi_add_host()������ִ��,֮ǰ�����us->host����Ϊ�������ݸ���,ͬʱ,intf->devҲ
// �����ݸ���,��������Ǳ�����ע��sysfs ��.��scsi_host_alloc֮��,����ִ��scsi_add_host(),��
// ��,scsi ���Ĳ���ܹ�֪������ôһ��host ����.scsi_add_host()�ɹ��򷵻�0,���򷵻س������.���
// һ��˳��,���ǽ��ߵ�1009��,��,�ȰѴ���������,�����storage_probe()���������һС����: 
   1007 
   1008         // Start up the thread for delayed SCSI-device scanning // 
   1009         result = kernel_thread(usb_stor_scan_thread, us, CLONE_VM); 
   1010         if (result < 0) { 
   1011                 printk(KERN_WARNING USB_STORAGE 
   1012                        "Unable to start the device-scanning thread\n"); 
   1013                 scsi_remove_host(us->host); 
   1014                 goto BadDevice; 
   1015         } 
   1016 
   1017         return 0; 
   1018 
   1019         // We come here if there are any problems // 
   1020 BadDevice: 
   1021         US_DEBUGP("storage_probe() failed\n"); 
   1022         usb_stor_release_resources(us); 
   1023         dissociate_dev(us); 
   1024         return result; 
   1025 } 
   1026   115
//    ��һ�μ�����kernel_thread,����Ҫ�������,������Ȼ���Ǵ���һ���ں��ػ�����,ֻ���������
//  usb_stor_scan_thread,���ϴ���usb_stor_control_thread.usb_stor_scan_thread()����Ҳ�Ƕ�
//  ����drivers/usb/storage/usb.c��: 
//  886 // Thread to carry out delayed SCSI-device scanning // 
    887 static int usb_stor_scan_thread(void * __us) 
    888 { 
    889         struct us_data *us = (struct us_data *)__us; 
    890 
    891         // 
    892        //This thread doesn't need any user-level access, 
    893        //so get rid of all our resources. 
    894          // 
    895         lock_kernel(); 
    896         daemonize("usb-stor-scan"); 
    897         unlock_kernel(); 
    898 
    899         printk(KERN_DEBUG 
    900                 "usb-storage: device found at %d\n", us->pusb_dev->devnum); 
    901 
    902         // Wait for the timeout to expire or for a disconnect // 
    903         if (delay_use > 0) { 
    904                 printk(KERN_DEBUG "usb-storage: waiting for device " 
    905                                 "to settle before scanning\n"); 
    906 retry: 
    907                 wait_event_interruptible_timeout(us->scsi_scan_wait, 
    908                                 test_bit(US_FLIDX_DISCONNECTING, &us->flags), 
    909                                 delay_use * HZ); 
    910                 if (current->flags & PF_FREEZE) { 
    911                         refrigerator(PF_FREEZE); 
    912                         goto retry; 
    913                 } 
    914         } 
    915 
    916         // If the device is still connected, perform the scanning // 
    917         if (!test_bit(US_FLIDX_DISCONNECTING, &us->flags)) { 
    918                 scsi_scan_host(us->host); 
    919                 printk(KERN_DEBUG "usb-storage: device scan complete\n"); 
    920         } 
    921 
    922         complete_and_exit(&us->scsi_scan_done, 0); 
    923 } 
//   �Զ��׼�,�����daemonize()�ֻ���������ps -el����������п�����usb-stor-scan��ôһ����
// �����.   116
// 903��,delay_use������?ͬһ�ļ���,�ʼ�ĵط�,������һ����̬����, 
// 101 static unsigned int delay_use = 5; 
//     102 module_param(delay_use, uint, S_IRUGO | S_IWUSR); 
//     103 MODULE_PARM_DESC(delay_use, "seconds to delay before using a new device"); 
// ������delay_useΪ5,��module_param��LK 2.6�ṩ��һ����,ʹ��delay_use������ģ�鱻
// װ�ص�ʱ���趨.(�������,��ô����Ȼ���������ֵ5,��ʾʹ��һ���µ��豸֮ǰ�ȴ�5����ʱ.)ΪɶҪ
// delay��?��Ϊɶ,ֻ����Ϊ���ϵ����ǻ�����,���ϵ�õ����ή.�����ȥ��u��Ҳ���������ֱ����γ�
// ����,�����������Ժ�һ����֮���ְγ���,��ô��������Ҳ���õ��󹤷��ټ�����ﲻ��. 
//   903��,�ж� delay_use>0,Ȼ��907��,wait_event_interruptible_timeout(),���ĵ�һ��������
// us->scsi_scan_wait,��ش�,us->scsi_scan_wait�ǵ�һ��¶����? 
//   �켣������ô������, �ҿ��Ժܸ����εĺ��г������Ӣ�������ĳ��ĸ�����: The answer is no. ��
// storage_probe()���������,��us�ĳ�ʼ��ʱ,scsi_scan_wait����ʼ����.947
// ��,init_waitqueue_head(&us->scsi_scan_wait),���ڶ���struct us_dataʱ,��һ����Ա����
// scsi_scan_wait,��wait_queue_head_t scsi_scan_wait,��Щ����ʲô��˼��? 
//   ʵ����wait_event_interruptible_timeout()��һ����,��������Linux�е�һ�ֵȴ�����,�ȴ�ĳ��
// �¼��ķ���,����ԭ����,��һ��������һ���ȴ�����ͷ,��wait_queue_head_t����ı���,��LK 2.6
// ��ʹ��init_waitqueue_head()������ʼ������ȴ�����,Ȼ����������������ó�ʱ,��������������
// ��5s,���ʾ���5�뵽��,��ô�����᷵��0,���������������.�ڶ���������һ�ֵȴ�������,����˵��
// �����¼�,�������������,��ô����Ҳ�᷵��,����Ҫ�ǲ�����,��ô������̻����˯��,����
// interruptible�������źſ��԰����ж�.һ������˯��,��ô���������,һ����wake_up����
// wake_up_interruptible��������һ������ִ��,�Ӷ�������,�ڶ������ź��ж���,�����־��ǸղŽ���
// ��ʱ,ʱ�䵽��,��Ȼ�ͻ᷵��. 
//   ��ô���������˵,���ж�US_FLIDX_DISCONNECTING���flag��û����,���û����Ž���˯��,
// ����Ͳ���Ҫ�˷ѱ˴˵ĸ�����.�ڽ���˯��֮��,���5 ��֮����û�а�u�̰γ���,��ô5��һ��,����
// ����0,����������,�������5��֮ǰ�γ�����,��ô�������ǻὲ,storage_disconnect()������ִ��,
// ��������US_FLIDX_DISCONNECTING���flag,�����������wake_up(&us->scsi_scan_wait)
// ����������˯�ߵĽ���,������:"�����,���Ƕ�,��û������!"���������ͻ���ǰ����,���õȵ�5���ٷ���
// ��.��֮����������������,5��֮�ڿ϶��᷵��,�������Ǽ������¿�. 
// 910��,����PF_FREEZE������,�е�����,�����ϴ����ǿ�������PF_NOFREEZE,��Щ���ǵ�Դ��
// �������,�������.����usb �豸,�����Խ���suspend״̬,��ô������������flag,�������������
// ��,������������,���flag���Ǵ�û�����,���������flag��һ���ǵ�����������,Ҫ֪��������ܵȴ�
// ��һ��ʱ���,(delay_use),��Ȼ�ȴ���һ��ʱ��,���п��ܱ���Ϊ��Ҫ����˯��,�����ϾͲ����л,��
// ����ͷ��Ϊÿ��Ҫ������usb�豸��,���Ǿͻ�Ϊ�����ý���suspend��flag.�ر�����,��С�ӳԴ�
// ҩ��û����,��delay_use�����1����,ʲô?���겻��ʱ�䵥λ?�Ǻð�,�Ǽ������delay_use�����
// ��ϲ����ʮ����,����˵����豸�ǲ��Ǹý���suspend ״̬?����˵�ǲ��Ǹý�������״̬?�����,��
// ô�����ں��ṩ�ĺ���, refrigerator()ȥ����.   117
// 917��,�ٴ��ж��豸��û�б��Ͽ�,�������û��,��ôִ��scsi_scan_host()����ɨ��,ɨ��Ȼ���֪
// �����host����˵���scsi ���������ʲô�豸(��Ȼ�������ֻ��ģ���scsi ��),Ȼ��cat 
// /proc/scsi/scsi ���ܿ�������u���ﲻ��.(scsi_scan_host()�����淢���˺ܶ�ܶ�Ĺ���,���ⶼ��
// scsi �ǲ�Ĺ���,������ʱ�Ȳ�ȥ��ע�ò�?) 
//   Ȼ��922��,complete_and_exit����,����complete ��������һ��㲻һ��,���˻��ѱ���,���ý�
// ���Լ�(exit).���Ļ�����kernel/exit.c��: 
    842 NORET_TYPE void complete_and_exit(struct completion *comp, long code) 
    843 { 
    844         if (comp) 
    845                 complete(comp); 
    846 
    847         do_exit(code); 
    848 } 
//   ����������ȼ��&us->scsi_scan_done,��struct us_data��,������һ����Աstruct completion 
// scsi_scan_done,����storage_probe()����һ��ʼΪus ���г�ʼ����ʱ��,������
// init_completion(&us->scsi_scan_done)Ϊus->scsi_scan_done�����˳�ʼ��,�����ǰ
// storage_disconnect()������������,��ô�������wait_for_completion(&us->scsi_scan_done)
// ������˯�߲��ҵȴ����������������,���˺�,���Ҳ���.��������storage_disconnect��ʱ��������
// ��.�������������û���˵���wait_for_completion(&scsi_scan_done),��ôҲ����˵û����˯��,��
// ô���complete������ʲôҲ����.Ȼ��do_exit()�������ö�˵,�ں��ṩ�ĺ���,��������.Ҳ����˵,
// �����������scan�ľ������,���������ͻ�����˳���.���Կ�������һ���������ػ�����,��Ĳ�֪��
// ˵���Ӣ���ֻ��Ǹ�˵����������.��֮����������������˵,����ʹ��������������cat 
// /proc/scsi/scsi �п������U��,��Ȼ��,�Ӵ��Ժ�����/devĿ¼����Ҳ���ܿ�������豸��,����
// /dev/sda. 
//   ������������,Ҳ����storage_probe(),����kernel_thread()������usb_stor_scan_thread ֮
// ��,һ�������Ļ�,storage_probe()Ҳ�ߵ��˾�ͷ��.1017��,return 0��.����,������ϵĴ�˵Ҳ����
// �����ϵ���һ��,һ�ж�������,һ�ж�������ɢ��.�����������е����鶼�����и�����.--ϯĽ�� 
// �˰����Ĵ�˵(��) 
// ������:�����Ʒ���ô? ��:�������Ʒ���,��Ҷ����˺�����. 
// ��������:�Ͷ����񻹵�ţ����ô?��:���¸���,���Ͷ���.  
// ��ɫ���Ӿ��������绰��:�����Ƕ�����ý���˰�? ��:˼������,����С����.  
// ���������绰��:���˶������˰�?��:����������. 
// ��������绰��:�����Ƕ�����ô? ��:���뵳��. 
// ���˼���绰��:�ʱ��Ҷ�������ô? ��:����������.  
// �ϵ۴�绰��:��Linux��Щ�¶����˶���������? ��:û�صĶ���ȥ�����·��. 
//   ������������Щ�Ի�д�ɳ���,��¼��оƬ��,��ô�����ѯ���豸��ʱ��,�豸��֪������ô�ش�.��
// �����ʽ����Ƕ�����ý���˰�?�豸���ܻش���:˼������,����С����.�����scsi �豸�Ļ���������
// ʽ.scsi Э�鶨����һϵ�е�����.����ͨ������������豸��ʵ��ͨ��.   118
//   ���Ǹոո���storage_probe()��������������һ��,ò��һ�ж��ý�����,�����㲻�����㵽ĿǰΪֹ
// ������û�п������豸������ô��������?U��,��������usb�豸,���ǡ��̡�,����������usb mass 
// storageЭ��,��������transparent scsi�淶.����������ĽǶ�����,����һ���scsi���̲��.����
// ��Ϊ���,����U�̵Ĺ���������Ҫ�����ĸ�ģ��,usbcore,scsi_mod,sd_mod,�Լ����������
// usb-storage,����sd_modǡǡ����scsi disk����������.û����,���scsi Ӳ�̾ͱ�����Linux����
// ת����.�������Ĵ���,��Ϳ���ȥ���Ա�Ͷ��,��һƪ����תLinux�µ� scsi Ӳ�̡�����������. 
//   ��ô���Ǵ����￪ʼȥ�Ӵ���Щscsi ������?�������������ڵ�����,�ں��ػ�����,����������������
// һ�δ���ֻ����һ���û����.û��,�Ǿ���usb_stor_control_thread(),����������kernel_thread��
// ������ʱ���˵��,�Ӵ��Ժ�һ�����̱����������,�����Ǹղ�����storage_probe ������Ǹ�����,��
// �������շ�����,���ӽ�����û����ô��,�����Ѿ�˵��,usb_stor_control_thread()�е���ѭ��ע��
// ������ӽ�����һ������Ľ���,ֻҪ���ģ�黹û�б�ж��,����˵��û�б�Ҫ��ж��,����ӽ��̾ͱؽ�
// ���������ս����ȥ.�����������ƿ��������,�ع������������,�������ǽ�����303��,����
// us->semaһ��ʼ�������ŵ�,����down_interruptible����һ��ʼ�ͽ���˯����,ֻ���ڽӵ����ѵ���
// �Ż��������ͷ����ͷ����Ľ��������������Ż��ѹ���.��ô˭���ͷ��������? 
//   �������ط�,һ�������ģ��Ҫж����,��������Ժ�����.��һ��������scsi ���������.scsi �����
// ���﷢����?�ܼ�,scsi ���Ĳ�,Ӳ������˵,scsi ������� scsi ������scsi �豸,���Ӵ���ĽǶ���
// ˵,scsi���Ĳ�Ҫ��Ϊÿһ��scsi hostʵ��һ��queuecommand����,ÿһ��Ӧ�ò㷢������scsi����
// ��,������ȥ��д/dev/sda,����scsi ���Ĳ�ͻ�������host���Ӧqueuecommand,(ȷ�е�˵��
// struct Scsi_Host�ṹ���еĳ�Աstruct scsi_host_template�еĳ�Աָ��queuecommand,����һ
// ������ָ��.)��ô��������,�������Ƕ����struct scsi_host_template usb_stor_host_template,
// ���е�ȷ��һ��queuecommand,���Ǹ�������ֵҲ��queuecommand,��������queuecommand
// ָ��һ������queuecommand�ĺ���,��struct scsi_host_template�Ķ�����,����ָ���ԭ��Ϊ: 
// 107         int (* queuecommand)(struct scsi_cmnd *, 
//     108                              void (*done)(struct scsi_cmnd *)); 
// �������������queuecommand()��������������?��drivers/usb/storage/scsiglue.c��: 
165 // queue a command // 
    166 // This is always called with scsi_lock(srb->host) held // 
    167 static int queuecommand(struct scsi_cmnd *srb, 
    168                         void (*done)(struct scsi_cmnd *)) 
    169 { 
    170         struct us_data *us = (struct us_data *)srb->device->host->hostdata[0]; 
    171 
    172         US_DEBUGP("%s called\n", __FUNCTION__); 
    173         srb->host_scribble = (unsigned char *)us; 
    174 
    175         // check for state-transition errors // 
    176         if (us->srb != NULL) { 
    177                 printk(KERN_ERR USB_STORAGE "Error in %s: us->srb = %p\n", 
    178                         __FUNCTION__, us->srb); 
    179                 return SCSI_MLQUEUE_HOST_BUSY;   119
    180         } 
    181 
    182         // fail the command if we are disconnecting // 
    183         if (test_bit(US_FLIDX_DISCONNECTING, &us->flags)) { 
    184                 US_DEBUGP("Fail command during disconnect\n"); 
    185                 srb->result = DID_NO_CONNECT << 16; 
    186                 done(srb); 
    187                 return 0; 
    188         } 
    189 
    190         // enqueue the command and wake up the control thread // 
    191         srb->scsi_done = done; 
    192         us->srb = srb; 
    193         up(&(us->sema)); 
    194 
    195         return 0; 
    196 } 
// �����������,����ʹ��Ҳ�ܼ�,����Ϊ�˻������ǵ��Ǹ���˯�е��ػ�����,������,�������ٳ�˯. 
// ��������ϸ��һ��,170��,���ּ����Ѿ������˵,�������ǵ�һ�μ���hostdata[0]��ʱ����Ѿ�
// ˵�ú����,���ĳ��־���Ϊ�˸�����scsi ��صĴ���ʹ��,�������Ȼ��������. 
// 173��,host_scrible���ָ��ԭ������ָ��һ����ʱ����,���߽��м����ݴ���,���д����ֱ��
// ���þ�����һ��ָ��host_scrible��ָ��ָ��us,��ʵ�������д��������˴�������۾���,���ɺܼ�,
// ����Linux�ں˴����к�������������.��Ϊhost_scrible���ָ���������˵û���κ�����,����,����
// ���ں��Ѿ������д���ɾ����.��Ȼ,���д���д���Ҳ��ֻ����Ϊ���߿���̨�廹���ո�,�����δͳһ,
// ���������,��������ôһ�д����Ա���,һ���������ͳһ�˾Ͱ���ɾ��.������Դ����������ͬ־��Ų�
// ��ͬ��,���Ժ���Ȼ���д���û�ܱ�������.���һ������Ҳ��ӳ�˿�Դ������û���������й�,ʵ��һƬ��
// г,����Ǳ�ڵ����ǲ��ò���ÿһλ��ʶ֮ʿΪ��Դ������һ�Ѻ���!Ȼ��������Ҫ˵����,host_scrible
// ��Ȼ�����ǵ�����û����,������һЩ������scsi host adpater������������,�����жദʹ������,��Ϊ
// ���ָ�뱾�������ṩ���ײ�����ʹ�õ�. 
// 176��,�ж�us->srb,�µ����,��Щ����Ҳ����ס��,���ǲ��ò�ȥ���һ���µ����ݽṹ,������
// struct scsi_cmnd.queuecommand()�����ĵ�һ����������struct scsi_cmndָ��,��struct 
// us_data��Ҳ��һ��struct scsi_cmnd *srb,Ҳ��һ��ָ��.��ô��������struct scsi_cmnd,�������
// �ṹ�����������,���Ǵ���һ��scsi ����.��������include/scsi/scsi_cmnd.h��, 
 30 struct scsi_cmnd { 
     31         int     sc_magic; 
     32 
     33         struct scsi_device *device; 
     34         unsigned short state; 
     35         unsigned short owner; 
     36         struct scsi_request *sc_request;   120
     37 
     38         struct list_head list;  // scsi_cmnd participates in queue lists // 
     39 
     40         struct list_head eh_entry; // entry for the host eh_cmd_q // 
     41         int eh_state;           // Used for state tracking in error handlr // 
     42         int eh_eflags;          // Used by error handlr // 
     43         void (*done) (struct scsi_cmnd *);      // Mid-level done function // 
     44 
//     45         // 
//     46        //A SCSI Command is assigned a nonzero serial_number when 
//internal_cmnd 
//     47        //passes it to the driver's queue command function.  The serial_number 
//     48        //is cleared when scsi_done is entered indicating that the command has 
//     49        //been completed.  If a timeout occurs, the serial number at the moment 
//     50        //of timeout is copied into serial_number_at_timeout.  By subsequently 
//     51        //comparing the serial_number and serial_number_at_timeout fields 
//     52        //during abort or reset processing, we can detect whether the command 
//     53        //has already completed.  This also detects cases where the command has 
//     54        //completed and the SCSI Command structure has already being reused 
//     55        //for another command, so that we can avoid incorrectly aborting or 
//     56        //resetting the new command. 
//     57          // 
     58         unsigned long serial_number; 
     59         unsigned long serial_number_at_timeout; 
     60 
     61         int retries; 
     62         int allowed; 
     63         int timeout_per_command; 
     64         int timeout_total; 
     65         int timeout; 
     66 
     67         // 
     68        //We handle the timeout differently if it happens when a reset, 
     69        //abort, etc are in process. 
     70          // 
     71         unsigned volatile char internal_timeout; 
     72 
     73         unsigned char cmd_len; 
     74         unsigned char old_cmd_len; 
     75         enum dma_data_direction sc_data_direction; 
     76         enum dma_data_direction sc_old_data_direction; 
     77 
     78         // These elements define the operation we are about to perform // 
     79 #define MAX_COMMAND_SIZE        16   121
     80         unsigned char cmnd[MAX_COMMAND_SIZE]; 
     81         unsigned request_bufflen;       // Actual request size // 
     82 
     83         struct timer_list eh_timeout;   // Used to time out the command. // 
     84         void *request_buffer;           // Actual requested buffer // 
     85 
     86         // These elements define the operation we ultimately want to perform // 
     87         unsigned char data_cmnd[MAX_COMMAND_SIZE]; 
     88         unsigned short old_use_sg;      // We save  use_sg here when requesting 
     89                                        //sense info // 
     90         unsigned short use_sg;  // Number of pieces of scatter-gather // 
     91         unsigned short sglist_len;      // size of malloc'd scatter-gather list // 
     92         unsigned short abort_reason;    // If the mid-level code requests an 
     93                                        //abort, this is the reason. // 
     94         unsigned bufflen;       // Size of data buffer // 
     95         void *buffer;           // Data buffer // 
     96 
     97         unsigned underflow;     // Return error if less than 
     98                                    this amount is transferred // 
     99         unsigned old_underflow; // save underflow here when reusing the 
    100                                //command for error handling // 
    101 
    102         unsigned transfersize;  // How much we are guaranteed to 
    103                                    transfer with each SCSI transfer 
    104                                    (ie, between disconnect / 
    105                                    reconnects.   Probably == sector 
    106                                    size // 
    107 
    108         int resid;              // Number of bytes requested to be 
    109                                    transferred less actual number 
    110                                    transferred (0 if not supported) // 
    111 
    112         struct request *request;        // The command we are 
    113                                            working on // 
    114 
    115 #define SCSI_SENSE_BUFFERSIZE   96 
    116         unsigned char sense_buffer[SCSI_SENSE_BUFFERSIZE];              // 
obtained by REQUEST SENSE 
    117                                                //when CHECK CONDITION is 
    118                                                //received on original command 
    119                                                //(auto-sense) // 
    120 
    121         // Low-level done function - can be used by low-level driver to point 
    122        //       to completion function.  Not used by mid/upper level code. //   122
    123         void (*scsi_done) (struct scsi_cmnd *); 
    124 
    125         // 
    126        //The following fields can be written to by the host specific code. 
    127        //Everything else should be left alone. 
    128          // 
    129         struct scsi_pointer SCp;        // Scratchpad used by some host adapters 
// 
    130 
    131         unsigned char *host_scribble;   // The host adapter is allowed to 
    132                                          //call scsi_malloc and get some memory 
    133                                          //and hang it here.     The host adapter 
    134                                          //is also expected to call scsi_free 
    135                                          //to release this memory.  (The 
memory 
    136                                          //obtained by scsi_malloc is guaranteed 
    137                                          //to be at an address < 16Mb). // 
    138 
    139         int result;             // Status code from lower level driver // 
    140 
    141         unsigned char tag;      // SCSI-II queued command tag // 
    142         unsigned long pid;      // Process ID, starts at 0 // 
    143 }; 
// �����ǿ�������,�����漰scsi �Ǳߵ����ݽṹ��û��һ������̬,д������˳��ľ����Ż�����.��
// ��������Ϊ��������Ӱ���,���ܱ���Щ�ŵ���.��������,����ֻҪ֪������ôһ�����ݽṹ�Ϳ�����,ͬ
// ʱ��Ҫ֪����us����һ����Աsrb,������ָ��scsi ����.֪����Щ����.����˵176��,��һ��us->srb
// �ǲ���Ϊ��,���Ϊ�����ǲſ��Լ���������ȥ�����Ǹ��ػ�����,�����˵���˼��Ǳ�֮ǰ��һ�����
// û��ִ����.����Ϊʲô?��ʱ������󿴾�֪����,�˼��Ǳ�ִ����һ������ͻ������Ϊ��.����Ϊ��һ
// ����˵,��Ȼus->srbΪ��,��Ϊ��û���κ���Ϊ������ֵ,ֻ�ǳ�ʼ��us ��ʱ�������Ԫ�ض���ʼ��Ϊ0
// ��,�������һ�����������ʱ��϶��ǿ�.���������Ϊ�վͷ���SCSI_MLQUEUE_HOST_BUSY��
// scsi core,�������Ĳ��֪��,�˼����host æ����,�Ȳ�����ִ�����������. 
// 183��, US_FLIDX_DISCONNECTING���flag�����Ѿ����������,�Ѿ�����ི,����ֻ�ǲ�֪
// ���������������������flag,�պ����ǿ���storage_disconnect��֪����.���������һ��,������
// flag������,�ͱ��˷Ѵ�ҵĸ�����,�Ͻ�������.����srb->result��scsi core֪�������Ѿ��Ͽ�������.
// ��queuecommand�����ͷ���0.����������Ҫע�����186�����done����,��ϸ�����done
// ��queuecommand()�����ĵڶ�������,��һ������ָ��,ʵ����scsi core���� queuecommand��ʱ
// �򴫵ݵĲ������־ͽ���scsi_done,�����һ��������,scsi ���Ĳ㶨����һ������scsi_done�ĺ�
// ��,scsi ���Ĳ�Ҫ�󵱵Ͳ�������������һ�������Ҫ�����������ȥ֪ͨscsi ���Ĳ�,��ʵ���Ͼ��൱
// ��һ���жϻ���,scsi���Ĳ������queuecommand()֮�����Ͳ�������,����ȥ�ɱ����,����ײ�Ĵ�
// ������queuecommandִ������֮��,����׼ȷ��˵����ײ������ִ������֮��,��͵���
// scsi_done�Ӷ�scsi ���Ĳ��֪����������������,Ȼ�����ͻ������һЩ����������������������
// ����,���߱��һЩ��β�Ĺ���.�����������ǿ���,����豸�Ѿ������˶Ͽ���flag,��ô�����ִ��done,
// ���û�жϿ��Ǿ��������190������srb->scsi_done�������done,ʵ���Ͼ��ǵ���scsi_done,��  123
// ����scsi_done,һ����struct scsi_cmnd *srb�ĳ�Աָ��,һ����scsi���Ĳ�ĺ�����.��Ȼ����ͬ��,
// ������������ͬ�Ķ���,�ͺ��������綼�ǽ���ΰ,��ΰ,��ΰ,��ΰ��һ��,������ͬ�˲�ͬ,������. 
// ���,192��,��us->srb�������srb.�� 193��,���������ǿ��Ѱ�ҵĴ���,�������
// up(&us->sema),���������ǵ��ػ�����.֮��,195��,�����������ͽ�����,���̻�Ϩ��,��ҹ�ճ���.
// ��������Ȼ�͸�ȥ���Ǹ�usb_stor_control_thread()��.��Ϊ,������,����������. 
// �˰����Ĵ�˵(��) 
//   ����ȥ��,��������ʱ��;��������,�������ʱ��;�һ�л��,���ٿ���ʱ��;��������,�����ҵ�ʱ��,����
// ����,�л�����ʱ��;�����Ѽ�ӷ���,�зɻ�����ʱ��.һ������û�����������,���ٻ�����ʱ��.��ʵ,��
// Щ��,��Щ��,�վ�����Զ��. 
// ����,����һ�ν������ǵ���Ұ. 
//   ������usb_stor_control_thread().��������������queuecommand��up(&(us->sema)), 
// us->srb����ֵΪsrb,��srb������ scsi ���Ĳ��ڵ���queuecommandʱ�򴫵ݽ����Ĳ���.�۽�
// usb_stor_control_thread(),309��, ǰ��˵��,����dev_semaphore��������Ǳ����ڿ�������ģ
// ��֮�������ܽϸߵĽǶ�����,����������Ȼ������. 
// 312��,ûɶ��˵��,�������������NULL,��ô�����˳���.����ѡ��.(Ϊʲô�����ǿվ�˵��Ҫ������?
// ��Ϊ���srb �ǿ�,��ôscsi core�ǲ������queuecommand��,������˵�˰�,scsi coreҲ��ɵ,
// ��û�������������õײ�ĺ�������,�Դ�ҩ��?��ôqueuecommandû�е��õĻ���˭�����������
// ������?����ǰ��˵��,���������������ط�,һ����queuecommand,��һ������ģ��Ҫж����,׼ȷ��˵
// ��usb_stor_release_resources()����,�պ��������������������ٿ���,��֮����˵�����ģ�鶼Ҫ
// �ͷ���Դ��,��ʱ��srb�϶��ᱻ��ΪNULL,Ȼ����������»�������������ػ�����,���ǲ�����������
// ���ж����.) 
// 318��,host Ҳ��һ����,���������Ҳ�����������.���Ҳ���. 
// 321����331��,�����ж�����flag��û�б�����,�ڶ������ö�˵��,����������,�����ж��豸��û��
// ���γ�,Ҫ�����U�̲��ȥ����Զ���γ���,��ô����԰����flag��صĴ��붼ɾ��,��Ȼ��ʵ������
// �����ܲ��γ���,�Ȳ�α�������usb�豸��һ������.������������д����ĸ��Ƕ�Ϊʲô��ôɷ�ѿ�
// �ĵ�ȥ�ж��豸�ǲ����Ѿ�������.��ô��һ��flag��,US_FLDX_TIMED_OUT,���flag�ĺ���Ҳ����
// ��������һ��,��ʱ��,��ʱ�ĸ����ڼ������������ȱȽ���.�����������flag,�������ĺ�����
// command_abort,�������Ҳ�������ṩ��,��scsi ���Ĳ�ȥ����,�����Ǳ߸����ʱ,���˳�ʱ��ʱ����
// �͵���command_abort.�����Ժ�ῴ,�Ȳ���. 
// 338��,�ж�srb��һ����Աsc_data_direction, �ȿ�DMA_BIDIRECTIONAL�����.����궨����
include/linux/dma-mapping.h��, 
      7 // These definitions mirror those in pci.h, so they can be used 
      8//interchangeably with their PCI_ counterparts // 
      9 enum dma_data_direction {   124
     10         DMA_BIDIRECTIONAL = 0, 
     11         DMA_TO_DEVICE = 1, 
     12         DMA_FROM_DEVICE = 2, 
     13         DMA_NONE = 3, 
     14 }; 
  ��scsi_cmnd�ṹ�����,����ô������Ա, 
     75         enum dma_data_direction sc_data_direction; 
     76         enum dma_data_direction sc_old_data_direction; 
// ��Щ�������������ݽ׶����ݴ���ķ���.DMA_TO_DEVICE��ʾ�����浽��
// ��,DMA_FROM_DEVICE��ʾ���豸������.�����д���˵,DMA_NONE��ֻ�����ڵ���,һ�㲻��ʹ��
// �����п��ܵ����ں˱���.������׼ȷһ����,usb mass storageЭ����߹涨��˫�����ǷǷ���,��
// һ��������������ǺϷ���,����TEST_UNIT_READY ����Ͳ��ô�������.DMA_BIDIRECTIONAL
// ��ʾ���������п���,����֮Ҳ���ǲ�֪���������ĸ�����.�ͱ�������ĳλ��������,�������뿼����,
// ��������ʲôʱ������,��ȴ����˵,�������ϰ������ľ����°�������.����ֻ��˵����ʲô����֪��.ͬ
// ��,338�п���srb��sc_data_direction��DMA_BIDIRECTIONAL��ʱ��,��Ȼ�͵���������.��Ϊ��
// ȷ������Ļ�Ҳ��û�������������ﲻ��. 
// 346��, US_FL_SCM_MULT_TARG���flag,��ʾ�豸֧�ֶ��target,�������˼������,������Щ
// ��֧�ֶ��target���豸,�� us->srb->device->id����Ϊ0,�������������.struct us_data�ṹ��
// �еĳ�Աstruct scsi_cmnd * srb,struct scsi_cmnd�ṹ������һ��Աstruct scsi_device * device,
// ��struct scsi_device����˼��,����һ��scsi device,�����ȥ��struct usb_device��������usb 
// deviceһ��,��ЩдLinux����ĸ��Ƕ�Ҳû��ļ���,���⼸��.���ÿ�Ҳ֪��,struct scsi_device����
// һ����̬�����ݽṹ,�����Ǿ仰,�·�дһЩ��̬���ݽṹ������������Linus������������.������
// ��,������include/scsi/scsi_device.h��: 
     38 struct scsi_device { 
     39         struct Scsi_Host *host; 
     40         struct request_queue *request_queue; 
     41 
     42         // the next two are protected by the host->host_lock // 
     43         struct list_head    siblings;   // list of all devices on this host // 
     44         struct list_head    same_target_siblings; // just the devices sharing same 
target id // 
     45 
     46         volatile unsigned short device_busy;    // commands actually active on 
low-level // 
     47         spinlock_t sdev_lock;           // also the request queue_lock // 
     48         spinlock_t list_lock; 
     49         struct list_head cmd_list;      // queue of in use SCSI Command structures 
// 
     50         struct list_head starved_entry; 
     51         struct scsi_cmnd *current_cmnd; // currently active command // 
     52         unsigned short queue_depth;     // How deep of a queue we want //   125
     53         unsigned short last_queue_full_depth; // These two are used by // 
     54         unsigned short last_queue_full_count; // scsi_track_queue_full() // 
     55         unsigned long last_queue_full_time;// don't let QUEUE_FULLs on the same 
     56                                            jiffie count on our counter, they 
     57                                            could all be from the same event. // 
     58 
     59         unsigned int id, lun, channel; 
     60 
     61         unsigned int manufacturer;      // Manufacturer of device, for using 
     62                                        //vendor-specific cmd's // 
     63         unsigned sector_size;   // size in bytes // 
     64 
     65         void *hostdata;         // available to low-level driver // 
     66         char devfs_name[256];   // devfs junk // 
     67         char type; 
     68         char scsi_level; 
     69         char inq_periph_qual;   // PQ from INQUIRY data // 
     70         unsigned char inquiry_len;      // valid bytes in 'inquiry' // 
     71         unsigned char * inquiry;        // INQUIRY response data // 
     72         char * vendor;          // [back_compat] point into 'inquiry' ... // 
     73         char * model;           // ... after scan; point to static string // 
     74         char * rev;             // ... "nullnullnullnull" before scan // 
     75         unsigned char current_tag;      // current tag // 
     76         struct scsi_target      *sdev_target;   // used only for single_lun // 
     77 
     78         unsigned int    sdev_bflags; // black/white flags as also found in 
     79                                //scsi_devinfo.[hc]. For now used only to 
     80                                //pass settings from slave_alloc to scsi 
     81                                //core. // 
     82         unsigned writeable:1; 
     83         unsigned removable:1; 
     84         unsigned changed:1;     // Data invalid due to media change // 
     85         unsigned busy:1;        // Used to prevent races // 
     86         unsigned lockable:1;    // Able to prevent media removal // 
     87         unsigned locked:1;      // Media removal disabled // 
     88         unsigned borken:1;      // Tell the Seagate driver to be 
     89                                //painfully slow on this device // 
     90         unsigned disconnect:1;  // can disconnect // 
     91         unsigned soft_reset:1;  // Uses soft reset option // 
     92         unsigned sdtr:1;        // Device supports SDTR messages // 
     93         unsigned wdtr:1;        // Device supports WDTR messages // 
     94         unsigned ppr:1;         // Device supports PPR messages // 
     95         unsigned tagged_supported:1;    // Supports SCSI-II tagged queuing // 
     96         unsigned simple_tags:1; // simple queue tag messages are enabled //   126
     97         unsigned ordered_tags:1;// ordered queue tag messages are enabled // 
     98         unsigned single_lun:1;  // Indicates we should only allow I/O to 
     99                                //one of the luns for the device at a 
    100                                //time. // 
    101         unsigned was_reset:1;   // There was a bus reset on the bus for 
    102                                //this device // 
    103         unsigned expecting_cc_ua:1; // Expecting a 
CHECK_CONDITION/UNIT_ATTN 
    104                                    //because we did a bus reset. // 
    105         unsigned use_10_for_rw:1; // first try 10-byte read / write // 
    106         unsigned use_10_for_ms:1; // first try 10-byte mode sense/select // 
    107         unsigned skip_ms_page_8:1;      // do not use MODE SENSE page 0x08 
// 
    108         unsigned skip_ms_page_3f:1;     // do not use MODE SENSE page 0x3f // 
    109         unsigned use_192_bytes_for_3f:1; // ask for 192 bytes from page 0x3f // 
    110         unsigned no_start_on_add:1;     // do not issue start on add // 
    111         unsigned allow_restart:1; // issue START_UNIT in error handler // 
    112         unsigned no_uld_attach:1; // disable connecting to upper level drivers // 
    113         unsigned select_no_atn:1; 
    114         unsigned fix_capacity:1;        // READ_CAPACITY is too high by 1 // 
    115 
    116         unsigned int device_blocked;    // Device returned QUEUE_FULL. // 
    117 
    118         unsigned int max_device_blocked; // what device_blocked counts down 
from  // 
    119 #define SCSI_DEFAULT_DEVICE_BLOCKED     3 
    120 
    121         int timeout; 
    122 
    123         struct device           sdev_gendev; 
    124         struct class_device     sdev_classdev; 
    125 
    126         struct class_device     transport_classdev; 
    127 
    128         enum scsi_device_state sdev_state; 
    129         unsigned long           sdev_data[0]; 
    130 } __attribute__((aligned(sizeof(unsigned long)))); 
// ����ṹ�彫��δ���������ﱻ���Ƕ���ᵽ.��Ȼ,�˿�,����ֻ��Ҫע�⵽unsigned int id, lun, 
// channel ��������Ա,�����Ƕ�λһ��scsi �豸��Ҫ��������Ա,һ��scsi �������Ƶ��豸������Ϊ����,
// �������ɸ�channel,Ȼ��ÿ��channel �������ɸ�target,ÿ��target��һ��target id������,Ȼ��һ
// ��target���������ɸ�lun,�����������жϵ���target id.���ڲ�֧�ֶ��target���豸,������Ϊ0.
// ���ھ������usb mass storage�豸��˵,���ǵ�target id�϶�Ϊ0,������������������ô�����,��
// Щ�豸���Ҿ���Ҫ��������,������Ҫ������豸֧�ֶ��target,�������Ϳ�������  127
// US_FL_SCM_MULT_TARG��ôһ��flag,�������ǿ�����drivers/usb/storage/unusual_devs.h��
// �������µĶ���: 
UNUSUAL_DEV(  0x04e6, 0x0002, 0x0100, 0x0100, 
                "Shuttle", 
                "eUSCSI Bridge", 
                US_SC_DEVICE, US_PR_DEVICE, usb_stor_euscsi_init, 
                US_FL_SCM_MULT_TARG ), 
//   Ȼ��353��,us->srb->device->lun��Ӧ�ô���us->max_lun,������������ʲô��
// ��?us->max_lun�����������ʱ��ʹ��storage_probe ����usb_stor_Bulk_max_lun()��������
// usb mass storage�豸��õ����LUN,����MAX LUN����3,��ô��������豸֧�ֵľ���4��LUN,
// ��0,1,2,3.��us->srb->device->lun����������ĸ�ֵ�е���һ��,�����Ǵ��ݽ�����������Ҫ����˭
// ��.������Ȼ�����ܳ���MAX LUN. 
//   Ȼ�����359����.������ôһ��flag-US_FL_FIX_INQUIRY,������us->flags���ڶ�flag�е�һ
// ��,һЩ������drivers/usb/storage/unusal_devs.h�е��豸�����flag,��ʵ��,ͨ��������豸��
// vendor name�� product name��ͨ��INQUIRY��������õ�,�����flag����,��Щ�豸��vendor 
// name�� product name����Ҫ��ѯ,���߸����Ͳ�֧�ֲ�ѯ,���ǵ�vendor name��product name
// ֱ�ӾͶ������,��unusal_devs.h�о������.��ô359 ���������cmnd[0]��ʲô?struct 
// scsi_cmnd�������ôһ����Ա, 
//      79 #define MAX_COMMAND_SIZE        16 
//      80         unsigned char cmnd[MAX_COMMAND_SIZE]; 
// �������16��Ԫ��,�������ľ���scsi ����,Ҫ������������ж�,���ȿ��±��Ǿ�
// fill_inquiry_response()��������.�����Ҷ�û����Ļ�,�����������½��ٽ��Ž�. 
// �������������US_FL_FIX_INQUIRY���flag���豸,�⼸������Sony��PEG�����,���߽м�
// �俨,��������PDA���.drivers/usb/storage/unusual_devs.h��: 
    377 // Submitted by Nathan Babb <nathan@lexi.com> // 
    378 UNUSUAL_DEV(  0x054c, 0x006d, 0x0000, 0x9999, 
    379                 "Sony", 
    380                 "PEG Mass Storage", 
    381                 US_SC_DEVICE, US_PR_DEVICE, NULL, 
    382                 US_FL_FIX_INQUIRY ), 
    383 
    384 // Submitted by Mike Alborn <malborn@deandra.homeip.net> // 
    385 UNUSUAL_DEV(  0x054c, 0x016a, 0x0000, 0x9999, 
    386                 "Sony", 
    387                 "PEG Mass Storage", 
    388                 US_SC_DEVICE, US_PR_DEVICE, NULL, 
    389                 US_FL_FIX_INQUIRY ), 
    390   128
    391 // Submitted by Frank Engel <frankie@cse.unsw.edu.au> // 
    392 UNUSUAL_DEV(  0x054c, 0x0099, 0x0000, 0x9999, 
    393                 "Sony", 
    394                 "PEG Mass Storage", 
    395                 US_SC_DEVICE, US_PR_DEVICE, NULL, 
    396                 US_FL_FIX_INQUIRY ), 
// �������ϵ��Ե�ͬ־�ǲ����Sony����ЩPEG��Ʒİ����. 
// �˰����Ĵ�˵(��) 
// ����ǰ,���Ǹ�ǧ������,ƾ��<<�ҵĸ���ĸ��>>��ý𼦽����Ů���ǵ����������˵:"�ҳ���ͦƯ
// ��,���ǵ���,���˲����ܶ���û��Ȥ!"�ǵ�,������,���˷�����,һ���Ǻ�ɫ,һ����ʮ�ֺ�ɫ.����������
// �⻰һ��û��.����,���ڴ����80����˵,�������Ѳ�����ʮ��ǰ��ô����,��ô����,��Ϊ��������ѹ��
// ����,���Ǻ���ʵ,����ʵ,һ���Զ��׼�����ʵ,yy��������������ʵʵ��ѧLinux.��Ȼ�ܶ��˶����߶���
// ��Ȥ.������ѧ���˺���,���Ի�ڷ���,˭�����Ƕ���֪ʶ������. 
// ��ʱ,��ͷһת,���Ǽ���������һ�����¿�.fill_inquiry_response(),�����������
drivers/usb/storage/usb.c ��, 
240 // 
    241//fill_inquiry_response takes an unsigned char array (which must 
    242//be at least 36 characters) and populates the vendor name, 
    243//product name, and revision fields. Then the array is copied 
    244//into the SCSI command's response buffer (oddly enough 
    245//called request_buffer). data_len contains the length of the 
    246//data array, which again must be at least 36. 
    247  // 
    248 
    249 void fill_inquiry_response(struct us_data *us, unsigned char *data, 
    250                 unsigned int data_len) 
    251 { 
    252         if (data_len<36) // You lose. 
    253                 return; 
    254 
    255         if(data[0]&0x20) { // USB device currently not connected. Return 
    256                               peripheral qualifier 001b ("...however, the 
    257                               physical device is not currently connected 
    258                               to this logical unit") and leave vendor and 
    259                               product identification empty. ("If the target 
    260                               does store some of the INQUIRY data on the 
    261                               device, it may return zeros or ASCII spaces 
    262                               (20h) in those fields until the data is 
    263                               available from the device."). //   129
    264                 memset(data+8,0,28); 
    265         } else { 
    266                 memcpy(data+8, us->unusual_dev->vendorName, 
    267                         strlen(us->unusual_dev->vendorName) > 8 ? 8 : 
    268                         strlen(us->unusual_dev->vendorName)); 
    269                 memcpy(data+16, us->unusual_dev->productName, 
    270                         strlen(us->unusual_dev->productName) > 16 ? 16 : 
    271                         strlen(us->unusual_dev->productName)); 
    272                 data[32] = 0x30 + ((us->pusb_dev->descriptor.bcdDevice>>12) 
& 0x0F); 
    273                 data[33] = 0x30 + ((us->pusb_dev->descriptor.bcdDevice>>8) & 
0x0F); 
    274                 data[34] = 0x30 + ((us->pusb_dev->descriptor.bcdDevice>>4) & 
0x0F); 
    275                 data[35] = 0x30 + ((us->pusb_dev->descriptor.bcdDevice) & 
0x0F); 
    276         } 
    277 
    278         usb_stor_set_xfer_buf(data, data_len, us->srb); 
    279 } 
// ���·�����̫ͻȻ,�����˲����þ�. �������������˾��������� scsi ����ĺ����Ǻ��潫Ҫ����
// proto_handler(),���벻�����������￪ʼ�Ӵ�scsi������.����������Ϊ��Sony�⼸��PEG��Ʒ����
// ����,��������� scsi ���� INQUIRY ����֧��,���������� Linux ��ʹ��,��û�취��,Sony �Ͼ��Ǵ�
// ˾,��ŷ�޹ھ����������ǼҺ�ϲ����������,��Դ����û�б�Ҫ��������,���Ծ�׼��һ�������� fix ���
// �����,��������,������Ӳ���ϵ�һ��bug. 
// ��ôʲô�� INQUIRY ����?����Ҳ���,INQUIRY ���������������һ�� SCSI ����,����������һ
// ��̽���豸��ʱ���Ҫ��INQUIRY�������˽�����һ��ʲô�豸,����scsi��������һ����۲���һ����
// ��,��ôscsi����������,����scsi������,����scsi�Ŵ�,�ֻ���scsi��CD ROM��?��Ϊ�豸,���ڲ�һ
// ����һ�ι̼�����,����ν�� firmware.�����ڽ��յ������� INQUIRY ����֮�������ش�.����Ӧ����ô
// �ش�?��Ȼ������ scsi Э����涨�ĸ�ʽ��.������ INQUIRY ����,����ÿһ�����Ӧ�����.ֻҪ�Է�
// ��:�����ǵػ�.����Ϊ�豸�͸ûش�,���������.����ʵ�ͺñ����ǶԶ���,�˼�����ֺ�,�ػֺ�,��ػ�
// ��,�͵ö������,�����,�������.�ⶼ�ǲ����ĵĹ��,������ scsi ���˰���Щд���˹淶,���ͱ����
// ���ĵĹ����.������˵, �豸���ܵ�INQUIRY�����ѯʱ,������Ӧ���scsiЭ������涨�ı�׼��ʽ,
// ��׼��ʽ�涨��,��Ӧ���ݱ������ٰ���36���ֽ�,����252��,���data_lenС��36,�Ǿͱ���������,
// ���ذ�.��Υ����. 
// ������scsiЭ���İ��,����û������INQUIRY���������ʲô,��ô�Ƽ�һ�����߸���,�����
// ��һ��,�Ա��и�ֱ�۵�ӡ��,��ʵ INQUIRY �����������������˼һ��,��ѯ,��ѯ�豸��һЩ������Ϣ,
// ������ĽǶ���˵,������ɨ���ʱ��,����˵ö�ٵ�ʱ��,��ÿһ���豸�����������,���һ�ûش�,����
// ����Ӵ˾ͻᱣ����Щ��Ϣ,��Ϊ��Щ��Ϣ֮����ܶ����õ�����˵���е�һ���ֻᱻ�õ�.�����Ƽ��Ĺ�
// ���� sg_utils3,����һ�������,Linux �п���ʹ�õ������,����������,����֮��װ��,Ȼ��������һ
// ��Ӧ�ó���sg_inq,����ʵ���Ǹ��豸����INQUIRY�����õ�,�÷�������ʾ:   130
[root@localhost ~]# sg_inq -36 /dev/sda 
standard INQUIRY: 
  PQual=0  Device_type=0  RMB=1  version=0x02  [SCSI-2] 
  [AERC=0]  [TrmTsk=0]  NormACA=0  HiSUP=0  Resp_data_format=2 
  SCCS=0  ACC=0  TGPS=0  3PC=0  Protect=0  BQue=0 
  EncServ=0  MultiP=0  [MChngr=0]  [ACKREQQ=0]  Addr16=0 
  [RelAdr=0]  WBus16=0  Sync=0  Linked=0  [TranDis=0]  CmdQue=0 
    length=36 (0x24)   Peripheral device type: disk 
 Vendor identification: Intel 
 Product identification: Flash Disk 
 Product revision level: 2.00 
// ������ʹ�õ�������Intel�Լ�������һ��U��,ȥ������ʱ�����Ǵ��ϰ巢��,ʹ��sg_inq�������
// ��ѯ�������ҵ���� U �̵Ļ�����Ϣ,ʵ���� sg_inq ���Բ�ѯ���е� scsi �豸����Ϣ,��Ϊ INQUIRY ��
// ������һ����׼��SCSI������.��Ȼ������Щ��Ϣ��,����֮���õõ��Ĵ��Ҳ����Vendor ID,Product 
// ID,Product revision,�Լ��Ǹ�length,device type--disk,�����Ǹ����������SCSI-2,��������ص�
// SCSI�İ汾,scsi Э��Ҳ��չ����ô����,��ȻҲ�в�ͬ�İ汾��.  
// Ok,����ֱ�۵�ӡ�������Ǿͼ���������,255 ��,�ж� data[0]�Ƿ��� 20h,20h ��ʲô�ر����?��
// Ȼ.scsi Э����涨��,��׼�� INQUIRY data �� data[0],�ܹ� 8 �� bit �ﲻ��,���� bit7~bi5 ����Ϊ
// peripheral qualifier(��λ),��bit4~bit0 ����Ϊperpheral device type(��λ),�����һ�����˲�ͬ��
// ����,���� 20h �ͱ�ʾ peripheral qualifier �����Χ�豸�޶���Ϊ 001b,�� peripheral device type
// �����Χ�豸������Ϊ 00h,���� scsi Э���֪,���ߴ�������豸����Ϊ����,����˵ֱ�ӷ����豸,ǰ��
// �������Ŀ���豸�ĵ�ǰ lun ֧����������,Ȼ��,ʵ�ʵ������豸��û�������ڵ�ǰ lun ��.�� data[36]
// ��,�� data[8]һֱ�� data[35]�� 28 ���ֽڶ��Ǳ���� vendor �� product ����Ϣ.scsi Э�����д��,
// ����豸���б�����Щ��Ϣ,��ô��������ʱ�ȷ���0x20h,��Ϊ������ϵͳpower onʱ�ڻ�����reset
// �ڼ�,Ҫ����������ʱ,����fill_inquiry_response()�ͻ��data[8]��data[35]�������ó�0.�ȵ�����
// ���豸�ϵ���Щ��Ϣ���Զ�����ȥ��. 
// �������20h,�����������ﴫ�ݽ�����data[0]����0,��ô��266��,data[8]��ʼ��8���ֽڿ��Ա�
// �� vendor ��ص���Ϣ,����,us->unusual_dev,�������Ѳ�İ��,struct us_data �ṹ���еĳ�Ա
// struct us_unusual_dev *unusual_dev, �뵱�� , ������ storage_probe() ʱ������
// us_unusual_dev_list[] �����еĶ�ӦԪ�ظ������� ,  �� us_unusua_dev_list[] ������
// unusual_devs.h,����Ԥ�ȶ�����˵�.����������ǰ����е�vendorName���Ƶ�data��������,����
// ���vendorName����8���ַ����ǿɲ���,ֻȡǰ8����ok��,��Ȼ���Ҽ�Intel�Ͳ��������������,
// ֻ�� 5 ���ַ�,�������˾Ҳ���ǰ˸��ַ�����,���糤һ��������� Motorola,Sansung Ҳ��û����.ͬ
// ��productNameҲ��һ���ķ���,���Ƶ�data��������,Э����涨��,��16��ʼ���productName,
// ���ܳ��� 16 ���ַ�,��ô��Flash Disk��Ҳû������.(ע:��ʽ��˴�������ͼƬ,Standard INQUIRY 
// data format) 
// Ȼ����Կ� 272 ��,us->pusb_dev->descriptor.bcdDevice,struct us_data ����һ����Ա struct 
// usb_device *pusb_dev,�� struct usb_device ����һ����Ա struct usb_device_descriptor 
// descriptor,��struct usb_device_descriptor�еĳ�Ա__u16 bcdDevice,��ʾ����������ָ���Ĳ�Ʒ
// �İ汾��,���ϵĹ�����ð汾��,������ id �Ͳ�Ʒ id ����־һ���豸.bcdDevice һ�� 16 λ,���� bcd  131
// ��ķ�ʽ�������Ϣ,Ҳ����˵,ÿ4λ����һ��ʮ���Ƶ���,����0011 0110 1001 0111�ʹ����3697.
// ����scsi ��׼��INQUIRY data��,data[32]��data[35]������Ϊ�������ĸ���,����Ҫ����ASCII��
// �ķ�ʽ����,ASCII ���� 48 ��Ӧ�����ճ��� 0,49 ��Ӧ 1,50 ��Ӧ 2,Ҳ����˵�����������ֵĻ����ϼ���
// 48,����˵����0x30.�����272 ��275 ����������˼. 
// һ��׼������֮��,���ǾͿ��԰� data ����,������� 36 ���ַ�����Ϣ���͵� scsi ����ָ����λ����,
// ��srbָ����λ��.������278����, usb_stor_set_xfer_buf��������Ϊ. 
// �ڽ��Ž�278���������usb_stor_set_xfer_buf֮ǰ,�Ƚ���һ��֮ǰ����data_ptr[36]ʱ��ʼ��
// ��ǰ 8 ��Ԫ��.���ǵĺ��嶼�� scsi Э��涨�Ķ�Ӧ.data_ptr[0]����˵��,data_ptr[1]����Ϊ 0x80,
// ���������豸�ǿ��Ƴ���,data_ptr[2]����Ϊ0x02��˵���豸��ѭSCSI-2Э��,data_ptr[3]����Ϊ
// 0x02,˵�����ݸ�ʽ��ѭ���ʱ�׼����֯���涨�ĸ�ʽ,��data_ptr[4]����Ϊadditional length,���Ӳ�
// ���ĳ���,����������ôһ����׼��ʽ��������Ӧ֮��,���ܻ��᷵�ظ����һЩ��Ϣ.�������õ���0x1F. 
// �˰����Ĵ�˵(��) 
// ����Ȼ,�����ǰ�ΪINQUIRY����׼�������ݱ��浽�������Լ������һ���ṹ����,��struct 
// data_ptr[36],����������Ϊ�˻�Ӧһ��SCSI����,������Ҫ֪���𰸵���scsi ���Ĳ�.�������Ǵ�����
// һ��scsi_cmnd�ṹ������,��srb.struct scsi_cmnd����������Ա, unsigned request_bufflen��
// void *request_buffer,С�����������,Ӧ�ð�data�����е����ݴ��͵�request_buffer��ȥ,��
// ��,scsi ���Ĳ��֪��ȥ�����ȡ���.û��,��ʱ��������! 
usb_stor_set_xfer_buf()�����������,drivers/usb/storage/protocol.c��. 
281 // Store the contents of buffer into srb's transfer buffer and set the 
    282//SCSI residue. // 
    283 void usb_stor_set_xfer_buf(unsigned char *buffer, 
    284         unsigned int buflen, struct scsi_cmnd *srb) 
    285 { 
    286         unsigned int index = 0, offset = 0; 
    287 
    288         usb_stor_access_xfer_buf(buffer, buflen, srb, &index, &offset, 
    289                         TO_XFER_BUF); 
    290         if (buflen < srb->request_bufflen) 
    291                 srb->resid = srb->request_bufflen - buflen; 
    292 } 
// ��Ҫ���õ�����usb_stor_access_xfer_buf()����,�������Ҳ����ͬһ����
// ��,drivers/usb/storage/protocol.c,  
   185 
//********************************************************************** 
   186//Scatter-gather transfer buffer access routines 
   187  *****************************************************************  132
*****// 
    188 
    189 // Copy a buffer of length buflen to/from the srb's transfer buffer. 
    190//(Note: for scatter-gather transfers (srb->use_sg > 0), srb->request_buffer 
    191//points to a list of s-g entries and we ignore srb->request_bufflen. 
    192//For non-scatter-gather transfers, srb->request_buffer points to the 
    193//transfer buffer itself and srb->request_bufflen is the buffer's length.) 
    194//Update the *index and *offset variables so that the next copy will 
    195//pick up from where this one left off. // 
    196 
    197 unsigned int usb_stor_access_xfer_buf(unsigned char *buffer, 
    198         unsigned int buflen, struct scsi_cmnd *srb, unsigned int *index, 
    199         unsigned int *offset, enum xfer_buf_dir dir) 
    200 { 
    201         unsigned int cnt; 
    202 
    203         // If not using scatter-gather, just transfer the data directly. 
    204        //Make certain it will fit in the available buffer space. // 
    205         if (srb->use_sg == 0) { 
    206                 if (*offset >= srb->request_bufflen) 
    207                         return 0; 
    208                 cnt = min(buflen, srb->request_bufflen - *offset); 
    209                 if (dir == TO_XFER_BUF) 
    210                         memcpy((unsigned char *) srb->request_buffer + *offset, 
    211                                         buffer, cnt); 
    212                 else 
    213                         memcpy(buffer, (unsigned char *) srb->request_buffer + 
    214                                         *offset, cnt); 
    215                 *offset += cnt; 
    216 
    217         // Using scatter-gather.  We have to go through the list one entry 
    218        //at a time.  Each s-g entry contains some number of pages, and 
    219        //each page has to be kmap()'ed separately.  If the page is already 
    220        //in kernel-addressable memory then kmap() will return its address. 
    221        //If the page is not directly accessible -- such as a user buffer 
    222        //located in high memory -- then kmap() will map it to a temporary 
    223        //position in the kernel's virtual address space. // 
    224         } else { 
    225                 struct scatterlist *sg = 
    226                                 (struct scatterlist *) srb->request_buffer 
    227                                 + *index; 
    228 
    229                 // This loop handles a single s-g list entry, which may 
    230                //include multiple pages.  Find the initial page structure   133
    231                //and the starting offset within the page, and update 
    232                //the *offset and *index values for the next loop. // 
    233                 cnt = 0; 
    234                 while (cnt < buflen && *index < srb->use_sg) { 
    235                         struct page *page = sg->page + 
    236                                         ((sg->offset + *offset) >> PAGE_SHIFT); 
    237                         unsigned int poff = 
    238                                         (sg->offset + *offset) & (PAGE_SIZE-1); 
    239                         unsigned int sglen = sg->length - *offset; 
    240 
    241                         if (sglen > buflen - cnt) { 
    242 
    243                                 // Transfer ends within this s-g entry // 
    244                                 sglen = buflen - cnt; 
    245                                 *offset += sglen; 
    246                         } else { 
    247 
    248                                 // Transfer continues to next s-g entry // 
    249                                 *offset = 0; 
    250                                 ++*index; 
    251                                 ++sg; 
    252                         } 
    253 
    254                         // Transfer the data for all the pages in this 
    255                        //s-g entry.  For each page: call kmap(), do the 
    256                        //transfer, and call kunmap() immediately after. // 
    257                         while (sglen > 0) { 
    258                                 unsigned int plen = min(sglen, (unsigned int) 
    259                                                 PAGE_SIZE - poff); 
    260                                 unsigned char *ptr = kmap(page); 
    261 
    262                                 if (dir == TO_XFER_BUF) 
    263                                         memcpy(ptr + poff, buffer + cnt, plen); 
    264                                 else 
    265                                         memcpy(buffer + cnt, ptr + poff, plen); 
    266                                 kunmap(page); 
    267 
    268                                 // Start at the beginning of the next page // 
    269                                 poff = 0; 
    270                                 ++page; 
    271                                 cnt += plen; 
    272                                 sglen -= plen; 
    273                         } 
    274                 }   134
    275         } 
    276 
    277         // Return the amount actually transferred // 
    278         return cnt; 
    279 } 
// ��,�������������ʱ������; 
//   ��,����������ϸ��ʱ��Ʈ��; 
// ��,�����ڽ������ʱ��������ϧ; 
//   ҹ,�������������ʱ������ϣ��; 
//   �ڱ�дLinux�豸����ʱ,���������ľ�����,���������޷��ӱ�,��������Ҫ�漰�ڴ����.�ڴ�����
// ��������Linux�ں�����ӵ�һ����,�ܲ��漰���Ƕ�ϣ����ȥ�漰.�����������ǳ���������,�����Ļ�
// �ǻ���.�����ǵ��Ǹ�����,�Ͼ�������ÿ������һ��.(����˵����ˮ��ú���ѵĵ���,�������.)�����ǰ�
// �㵵��������,ÿ��׼ʱ��׬�������. 
// ����,usb_stor_access_xfer_buf()����ӳ�������ǵ�����. 
//   �����ж�srb->use_sg�Ƿ�Ϊ0. 
//   ���ĵ�it����Ǵ�������һ����,����scatter/gather,����һ�����ڸ�����IO�ı�׼����.��ͨ����ζ
// ��һ��DMA���䷽ʽ,����һ�����������ݿ�,�����˼ҿ������ڴ��д�����һЩ��ɢ�Ļ�����,����֮,��
// ��˵һЩ���������ڴ滺����һ�𱣴�һ�����ݿ�,���û��scatter/gather��,��ô������Ҫ����һ��
// ���ڴ浽���̵Ĵ���,��ô����ϵͳͨ����Ϊÿһ��buffer��һ�δ���,���߸ɴ���ǰ���Щ��������
// buffer��ߵĶ���ȫ���ƶ�����һ���ܴ��buffer���,Ȼ���ٿ�ʼ����.��ô�����ַ�����Ȼ����Ч�ʲ�
// �ߵ�.��������,��� ����ϵͳ/��������/Ӳ�� �ܹ�����Щ�����ڴ�����ɢλ�õ������ռ�����(gather 
// up)��ת�����ǵ��ʵ�λ���������������һ����һ�Ĳ����Ļ�,Ч�ʿ϶��ͻ����.��֮,���Ҫ�Ӵ�����
// �ڴ��д���,����һ����һ�Ĳ����ܹ������ݿ�ֱ�ӷ�ɢ����(scatter)�����ڴ�����Ҫ��λ��,��������Ҫ
// �м���Ǹ����ƶ�,���߱�ķ���,��ô��Ȼ,Ч���ܻ����. 
//   ��struct scsi_cmnd��,��һ����Աunsigned short use_sg,��ͷ��������scsi_cmnd,��use_sg
// ������˵�,�����ж�һ��,�����Ϊ0,��ô˵��û��ʹ��scatter/gather.struct scsi_cmnd�л�������
// ��Ա,unsigned request_bufflen��void *request_buffer,���Ǻ�use_sg��ʲô��ϵ��? 
//   ��ʵ��,Ҫ��scatter/gather,����Ҫһ��scatterlist����,���˹�����ɢ�б�����.���ڲ�ͬ��Ӳ��ƽ̨,
// �����˲�ͬ��struct scatterlist�ṹ��,��������include/asm/scatterlist.h��,(�����Ӳ��ƽ̨i386
// ��,��ô����include/asm-i386/scatterlist.h,�����x86_64��ƽ̨,��ô����
// include/asm-x86_64/scatterlist.h ��),Ȼ����ν��scatter/gather����һ�ΰ�����scatterlist����
// �����͵�.��use_sgΪ 0�ͱ�ʾû��scatter gather list,����˵scatterlist,�����������,���ݽ�ֱ��
// ���͸�request_buffer����ֱ�Ӵ�request_buffer��ȡ������.�����use_sg���� 0,��ô��ʾ
// scatter gather list��ôһ���������request_buffer��,������Ԫ�ظ�������use_sg��.Ҳ����
// ˵,srb->request_buffer��ߵĶ��������ֿ���,һ���ǰ��������ݱ���,��һ���ǰ�����scatter 
// gather list.�������������ͨ���ж�use_sg������.������������Ҫ������srb->request_bufflen ��  135
// ��˼��,����buffer�ĳ���,������use_sg���� 0�����,����֮,����ʹ��scatter gather list����
// ��,request_bufflenû������,��������. 
// ����Щԭ�����˻������˽�֮��,���ǿ��Դ��½ڿ�ʼ��������.����������һ��,Ҫע���������������
// Ȼ�����Ǵ�������,����ʵ���ϲ�û�к�usb����������ϵ,����ֻ�Ǵ��������fixһ��Ӳ����bug,���
// bug���������Ѿ�˵���˵�,������Ӧ������SCSI����INQUIRY,������,����ȫ�������.����Ϊʲô��
// ����Ӧ�ҾͲ���˵�˰�?�˵���Į,������Ϊ���������,ֻ�ǰ������ľ����ѽ�����ͨ������Ĵ����ر�
// ��.���豸����Į,��Ȼ������������ɵ����.(��û�з��Sony����˼,��ʵ�������������ֻ��Sony��
// �ǼҲų�����,��ĳ���Ҳ�������Ĳ�Ʒ.ֻ��,Device�� bug,�����ó���ȥ��,����80���������,��ʲ
// ôȥ��?) 
// ���Զ�����Щ������ӦINQUIRY������豸,���ϲ����������ȥINQUIRY��ʱ��,ʵ�����ǵ�������
// ��queuecommand,��ô���Ǹ����Ͳ��ú������Ӳ��ȥ�򽻵�,��ֱ�ӻظ��ϲ�,�����Ǵ��������׼
// �����һ��INQUIRY���ݸ��ϲ�,������������������Ŀ��.�����ĺ�Ӳ���򽻵��Ĵ����ں���,���ǻ�
// û�ߵ���һ��.������һ����˵. 
// �˰����Ĵ�˵(��) 
//   ����use_sgΪ 0�����,���ǽ������ٿ�206��,offset�Ǻ������ô��ݽ����Ĳ���,ע����˵�ĺ���
// ��,����������־ƫ������,ÿ��copy�����ֽ��������Ӽ�,�����Ҳ���ܳ���request_bufflen,������Ȼ
// ��.usb_stor_access_xfer_buf()�������������������Ǵ�srb->request_buffer��buffer���
// copy����,���߷�������buffer��srb->request_buffer,Ȼ�󷵻�copy�˶��ٸ��ֽ�.����offset ��
// �ڵ���request_bufflen�����,��Ȼ��ֱ�ӷ���0��,��Ϊ request_buffer�Ѿ�����. 
//   ����enum xfer_buf_dir dir��־�����Ǵ��䷽��,���������������ĳ������Ľ����ﱻ����
// ��,drivers/usb/storage/protocol.h��: 
//      68 // struct scsi_cmnd transfer buffer access utilities // 
//      69 enum xfer_buf_dir       {TO_XFER_BUF, FROM_XFER_BUF}; 
// ��ʵ�Ǻܼ򵥵�һ��ö����������,����Ҳ�ܼ�,һ����ʾ��srb->request_buffer���
// copy,TO_XFER_BUF,��һ����ʾ��srb->request_buffer�������copy,FROM_XFER_BUF.(����
// ��:XFER���� TRANSFER����˼,����ϲ��������д.�ս�Intel ��ʱ���ϰ�ר�Ÿ�����һ��excel �ļ�,
// ���ȫ��Intel �ڲ��㷺ʹ�õ�Ӣ����д,����Intel ��һ��ʱ�����û�����.)���ﶨ���ö����������
// Ҳ�Ǻ��б�Ҫ��,��Ϊ���ݴ���϶������ҽ���һ������,����˼��,ֻ��һ������,��Ϊ��˼�����δ��˼
// ����. ������˾�,���Ǵ���������ǰ��,����209���ж�֮���ִ��210��,��buffer ���copy cnt��
// �ֽڵ�(unsigned char *) srb->request_buffer + *offsetȥ.cnt ��208��ȷ��,min��������˵Ҳ
// ֪��,ȡ��Сֵ,����ѧ��̷��ǿ��ʦ�Ǳ����ͬ־��Ӧ�ò��᲻��Ϥ�����ĺ���,����linux�ں����ȷʵ
// �ж����������,include/linux/kernel.h��,����Ҳ�г���,��������,�Ͼ����ǵĹ���̫������һ��,����
// �Բ���ǿ: 
203 // 
    204//min()/max() macros that also do 
    205//strict type-checking.. See the   136
    206//"unnecessary" pointer comparison. 
    207  // 
    208 #define min(x,y) ({ \ 
    209         typeof(x) _x = (x);     \ 
    210         typeof(y) _y = (y);     \ 
    211         (void) (&_x == &_y);            \ 
    212         _x < _y ? _x : _y; }) 
    213 
    214 #define max(x,y) ({ \ 
    215         typeof(x) _x = (x);     \ 
    216         typeof(y) _y = (y);     \ 
    217         (void) (&_x == &_y);            \ 
//     218         _x > _y ? _x : _y; }) 
// ��208�бȽϵ���һ��buflen,һ��srb->request_bufflen-*offset,�������Ҫ���͵����ݳ�����
// buflen,������ȻҲ���ܹ���������,���Ծ�ȡ����С���Ǹ�,����memcpy copy,Ȼ��215��*offset��
// ��copy���ֽ�cnt,�������ֲ�����scatter gather��ʽ�Ĵ���,��ô������Ϳ��Է�����,ֱ�Ӿ͵�278
// ��,����cnt����. 
//   ���Ƕ���ʹ��scatter gather��ʽ�Ĵ���,�����Ȼ��һ����.��224 �п�ʼ���¿�,��Ȼ��������˵,
// �ö���һ��struct scatterlist�ṹ���ָ��,����struct scatterlist�Ǻ���ϵ�ṹ�йص�,��Ϊ������
// Intel ��,��û���κ���ԥ��Ӧ����i386��Ϊ��,include/i386/scatterlist.h: 
      4 struct scatterlist { 
      5     struct page         *page; 
      6     unsigned int        offset; 
      7     dma_addr_t          dma_address; 
      8     unsigned int        length; 
      9 }; 
// ����ṹ��������,����pageָ��ͨ��ָ��Ҫ����scatter gather������buffer.��length��ʾ
// buffer�ĳ���,offset��ʾbuffer��page�ڵ�ƫ����.225��,����һ��struct scatterlistָ��sg,Ȼ��
// ����ָ��(struct scatterlist*)srb->request_buffer+*index,����һ���ں˴���Ϳ���֪��,ÿ��
// *index���Ǳ���ʼ��Ϊ0Ȼ��ŵ���usb_stor_access_xfer_buf()��,233��,cnt��Ϊ0,234�п�ʼ
// ����ѭ��,ѭ����������cnt С��buflen,ͬʱ*indexС��srb->use_sg, srb->use_sg���Ǹղ�˵��
// ��,ֻҪ������0,��ô����ߵĶ����ʹ�����scatter gather����ʱ����Ԫ�صĸ���. 
//   ������������ע��,225��������sg����srb->request_buffer,(��Ȼ��Ҫ����*index,���index��
// Ϊ0�Ļ�),��ôrequest_buffer������ʲô?����ʹ��scatter/gather��������,request_buffer��
// ��ʵ������һ������,ÿһ��Ԫ�ض���һ��struct scatterlist��ָ��,��ÿһ��scatterlistָ��� page
// ��߰�����һЩpage(������һ��page),��offset��߰�������ÿһ��DMA buffer���ܵ�ƫ����,����
// ���������,��λ���ֱ�־��page��,��λ���ֱ�־�ž���ĳ��page �е�ƫ����,��λ��λ��
// PAGE_SHIFT��������,��ͬ��Ӳ��ƽ̨PAGE_SHIFTֵ��һ��,��Ϊ��ͬ��Ӳ��ƽ̨page�Ĵ�СҲ��
// һ��,�������PAGE_SIZE ��һ��,Ŀǰ�Ƚ�ǰ����Ӳ��ƽ̨��page size��4k���� 8k��,��
// PAGE_SHIFT Ҳ����12����13,����֮,sg->offsetȥ����12λ���ߵ�13λ���� page��,���� 12  137
// λ���ߵ�13λǡǡ���ڸ�page�ڵ�ƫ����.֮���Կ��԰�һ��sg->offset����������,������Ϊpage 
// sizeֻ��Ҫ12λ���� 13λ���㹻��,����˵ƫ��������ֻ��12λ����13λ,��һ��int�ͱ�����Ȼ��
// �԰�����12λ��13λ�������Ϣ.����������Ҫ��buffer(��ǰ��˵���Ǹ�36�� bytes�ı�׼��
// INQUIRY data buffer)��ߵĶ���copy ��DMA buffer��,buffer�����Ѿ�֪��,������
// usb_stor_access_xfer_buf()�������ݽ����Ĳ���,��DMA buffer������?ֻҪ����֪�������ĸ�
// page��,֪������offset,��ô��һ���������԰������ǻ������Ӧ���ں������ַ,�������ַ��������
// ��Ҫ��,������,���Ǿ��ܵ���memcpy������copy������.����235�е�238��,���Ǽ������������
// ��page,�����Ƕ���offset,�����ñ�������unsigned int����poff,*offset��
// usb_stor_access_xfer_buf()�������ݽ����Ĳ���,��Ҳ���Կ�������Ҫ�������ݵ�DMA buffer��Ӧ
// ��offset,�����������Ǵ��ݽ�������0.���Բ�ȥcare. 
//   239�ж�unsigned int sglen��ֵ,sg->lengthʵ���Ͼ���DMA buffer�ĳ���.������Ȼ����copy
// �������ܳ����������,������ǻ�ָ����*offset,�ͱ���DMA buffer�д�*offset��ʼװ,��ô�Ͳ��ܳ�
// ��sg->length-*offset. 
//   241��,�����������ڻ���whileѭ����,�����ȿ���һ��ִ�е�241��,��ʱcnt����0,buflen������
// ��data buffer�ĳ���,����������36.sglen������DMA buffer��߿���װ����,���sglen ��buflen
// Ҫ��,��ô�ܺ�,һ�ξͿ���װ��,��Ϊ��ͺñ�buflen��һ��ɳ��,��sglen���ʾװɳ���������ֻ��߸�
// ��,��������.����244��245��,�����þ����������,����sglen��������¼ʵ��װ���˶���������ɳ��,
// ��*offset�������װɳ�����˶�����,�����ûж���´���Ҫ��������װ�Ǿ�װ��,����û���Ϳ���װ.��
// ô���sglen��buflenҪС���߸պù���,��ô*offset�϶��ͱ���Ϊ0,��Ϊ��һ����Ȼ�ᱻװ��,Ҫ��װ
// ɳ��ֻ�ܵ�����һ����,����ͬʱsg��*indexҲ�Լ�. 
//   Ȼ������257����,sglenһ��ʼ�϶�Ӧ�ô���0��,����������ʵ��װ�˶���,�����ڴ���������һ��
// ����,memcpy���䲻�ܹ���ҳ,Ҳ����˵���ܿ�page,һ�������ǰѱ�page�Ķ�����copy��,�����
// �����ݳ�����һ��page,���㻹����copyһ�λ��߶��,��Ϊ������������ѭ��.ÿһ������copy�ĳ���
// ��plen������,����271�к�272��,cnt �Ǽ�����,������Ҫ����һ��plen,��sglenҲ��һ��������,
// �������Ƿ��ż�,������ÿ��Ҫ����һ��plen.��poff��pageһ����Ϊ0,һ���Լ�,�������ܼ�,����
// һҳ��ͷ���м���copy.�� 258���ٴε���ǿ���min()����Ҳ����Ϊ�˱�֤ÿ��copy���ܿ�ҳ.260
// ��266�����ԩ�ҵĳ���,kmap()��kunmap(),����Ҳ�ܼ�.���ԩ�����ں��е��ڴ�������ṩ��
// ���ǵ���Ҫ����,����kmap()���������þ��Ǵ��ݸ���һ��struct pageָ��,���ܷ������pageָ��
// ��ָ���Ǹ�page���ں������ַ,���������page��Ӧ�������ַ,��������ǰ���Ѿ�֪����ƫ����,��
// �ǾͿ��Ե���memcpy������copy������.����kunmap,��������:����kmap()�������������ù�ϵ
// ������kunmap()���ݻ�. 
//   Ȼ��,262�� 265�е����� memcpy�����ٽ���. 
//   278��,����ʵ�ʴ�����ֽ���. 
//   ����,usb_stor_access_xfer_buf()���������ÿһ��ÿһ�ζ�������.�����ǻ�����!��һ��,���ǲ�
// ��һ������ս��.(ע:Ӧ��˵������Ǻ������ԵĻ�,��δ���Ҫ��������ͦ�ѵ�,��˵����������޵û�֦
// �Ҳ�,��Ҳ�������㿴���ۻ�����.��ʽ���й����������Ӧ����һ���ȽϺõ�ͼ��,���������˫��ѭ��,
// ��֪��ѭ���ǰ�sg entry��ѭ��,��һ��sg entryѭ��һ��,����ѭ���ǰ�page��ѭ��,����˵��,һ��
// sg entry�����ж��page,����Ϊ����û�а취��pageӳ��,����ֻ��ÿ��page ӳ��һ��,���Բ���Ҫ
// ѭ��.)   138
//   �ص�usb_stor_set_xfer_buf()����,Ҳֻʣ��һ�仰��,�������Ҫ���ݵ�36���ֽڻ�������������
// ��װɳ���Ļ�,�Ǿ������Ǽ�¼������������װ����ɳ�Ӱ�,srb->resid���ǰ����������¼�ߵĽ�ɫ. 
//   Ȼ�����ǻص�fill_inquiry_response()����,һ��,��,�������Ҳ������.������һ�λص����Ǹ�������
// �������,usb_stor_control_thread()����,�������ٲȻ������ʥ��ʿ��ʸ�еĲ�����һ��,��Ҳ��
// ����,��һ���ֻ����.����INQUIRY����,������fill_inquiry_response()֮��,��srb->result��Ϊ��
// SAM_STAT_GOOD,����scsi ϵͳ��߶����һ����,include/scsi/scsi.h��: 
    117 // 
    118// SCSI Architecture Model (SAM) Status codes. Taken from SAM-3 draft 
    119// T10/1561-D Revision 4 Draft dated 7th November 2002. 
    120  // 
    121 #define SAM_STAT_GOOD            0x00 
//   ��ʵ����0,��������˹���֮���srb->result��Ϊ0,�Ժ�����scsi�Ǳߵĺ�����ȥ���.�������ǹ�
// ��. 
//   Ȼ�����ǽ��뵽381��,��ȷ�е���,385��,srb->scsi_done()�����ᱻ����,srb->scsi_done()ʵ��
// ����һ������ָ��,������queuecommand����������scsi_done,���Ǳ�Ҫ��������˸���������֮��
// �����������,ʣ�µ�����scsi ���Ĳ��ȥ����. 
// ����,���queuecommand���ݽ���INQUIRY��������,�����ľͶ�����. 
// ��󵥶�����һ��,����Щϲ������ɳ���ʵ��׵�������ʿ: 
// First of all, �ö˶˵Ĵ�������ΪʲôҪ��ɢ�ɺö��scatter gather list,�ⲻ�������鷳��?������
// ������,�����ҵ�������Ϊ,Ҳ��ֻ��֧�����������.��������ʶ��,SCSI�����usb-storage֮����Ҫ
// ʹ��scatter gather����Ϊ��һ��������ϵͳ��һ��SCSI�����д����������ϲ�������buffers. 
// ����kmap()��kunmap().�����������Ǹ����?ΪʲôҪӳ��?Сʱ������û�и��߹�����?�����㳤
// ����,������Ϥ��Linux�ں��е��ڴ��������ͻ�֪��,�����������һ����ַ,���������ַ,����һ
// ����ַ�����ں˵�ַ,struct page������������ַ,�ں�������ṹ��������ÿһ������page,����˵
// ����ҳ,��Ȼ���Ǵ����в���ֱ�Ӳ��������ַ,memcpy������������Ͳ���ʶ�����ַ,��ֻ��ʹ����
// �˵�ַ.����������Ҫ�������ַӳ�䵽�ں˵�ַ�ռ�����.kmap()���µ���������ΰ��Ĺ���.����д��
// ��������˽�kmap()����ĺ�high memory�򽻵���ʱ����ʶ��,�������⻰,����. 
// �˰����Ĵ�˵(The End) 
//   ��������INQUIRY������,���ǾͿ��Լ�����������,373��,�����������Bulk����ĵ�
// ��,proto_handler()���������˾��Ĵ���SCSI����ĺ���ָ��.��usb_stor_control_thread֮ǰ����
// �д������Ϊ���ж��ǲ����б�Ҫ����proto_handler(),���糬ʱ��,����ģ���ж����,���������˶�
// ��flag��,����Ҫ����ľ�������������INQUIRY,�ȵ���Щ�������Ҫ���ų��˲��б�Ҫ����������
// ִ������������.ʵ����������ȴӺ����������,��֤�����ߵ���һ����ȷ�ĵ�·,�������������Ŵ����
// ��·�߰���,�Ͼ�,�ڴ����·��,���㱼��Ҳû����!��˵������,�㱼Ҳû����!   139
// ���ǵ����Ȳ����ŵ�proto_handler���ȥ��,�Ȱ���ߵĴ��뿴��.Сʱ��,���ǲ����������Ϊ,����
// ������ܾ���ô?����������proto_handler(),��usb_stor_control_thread()��ʣ�µĴ��뿴��,�Ӷ�
// �������˽�����ػ����̾��������ѭ����. 
// 382��,ֻҪ�ղŵ�����Ľ����srb->result��ΪDID_ABORT,��ô���ǳɹ�ִ����.�������Ǿ͵�
// ��scsi_done����. 
// 387��,SkipForAbort,����һ���б�־,��Ӧǰ����Ǹ�goto SkipForAbort���. �ǵô�ѧ�ڼ�,ѧ��
// ̷��ǿ����Ǳ�����goto��ʱ��,��ʦ���ǻ�����,��Ҫ����goto���,���ǲ��õı��ϰ��,������
// Linux�ں�Դ������,goto���ȴ�ǱȱȽ���,������Ϊ��ЩдLinuxԴ�����ͬ־�ǵ�C����ˮƽ���İ�,
// �϶���У�ڼ�û�кú�����,�����˼ҳ����е�������.����,��˵������,��Щ�һ����겻ʶ����ζ.���� 
// ����˵Linux,396��,ǰ���ע��Ҳ˵�ú������,�����������US_FLIDX_TIMED_OUT��ô�ͻ�����
// ���flag�Ľ���,��ʵ���ǻ���command_abort,�������ǻὲcommand_abort().����֮�����ж���
// ��flag�������ж�srb->result==DID_ABORTע����˵��Ҳ�����,��Ϊ�п�������usb�������֮
// ����յ���abort����,����֮,�������srb->result��ΪDID_ABORTҲ���������ֽӵ���abort��
// ����,����������ж�abort �����ȻҪ���õ�һ��flag���ж�. 
// 400��,SkipForDisconnect,��Ҳûɶ˵��,��ǰ���goto SkipForDisconnect����Ӧ,���Ҫ�Ͽ�
// ��,������һ������ִ������,������abort ��,��ô���վ��ǰ�us->srb ���ÿ�.ʣ�����е�������������
// ��˵��,�ᵽ���ͳһ����. 
// 406��,����,����ػ����̾���������һ����,forѭ������,����˰���,��һǧ��,��һǧ��,��Ҷ������
// ��.�鲻Ϊ���,Եע������.�������������ɳ��һ�δεĵ���������ֻ�,��ʵ�����������ﶼ���ֻص�,
// ����ʹ��. 
// �������,ֻʣ��422��һ����,����ִ�е���һ����ζ��forѭ��������,����forѭ���Ĵ������ǲ�
// �ѿ���,����forѭ����ֻ��һ�仰,�����Ǿ�break,����ǰ��˵��,����ζ��ģ��Ҫ��ж����.��������
// complete_and_exit()���ǻ��ѱ���ͬʱ�����Լ�,������һ��,usb_stor_control_thread()Ҳ����ʽ
// ������,Ҳ�������˵,�������ǽ��Ѱ�.����ɴ���׷��,ֻ�ǵ�ʱ���Ȼ. 
// ��Ҫ����һ�µ���,complete_and_exit()���﻽�ѵ���˭?��usb_stor_release_resources(),Ϊʲ
// ôҪ����,�����Ժ򽲵����������ʱ��������.����������ػ�����,����Ҳ���ڽ�����,���е�
// proto_handler()������,��Ϊ����Ҫ��,���ǵ�����������. 
// scsi ����֮�������� 
//   usb_stor_control_thread()����������,�������������⼸��,���Ǹ߳��еĸ߳�.��ν�� Bulk ����,
// ��ν��Bulk-Only Э��.�������������ֳ�����. 
372                 // we've got a command, let's do it! // 
    373                 else { 
    374                         US_DEBUG(usb_stor_show_command(us->srb)); 
    375                         us->proto_handler(us->srb, us); 
    376                 }   140
// ��ν�� US_DEBUG,����ǰ���Ѿ�����,�޷Ǿ��Ǵ�ӡ������Ϣ��.��������仰����ִ��
// usb_stor_show_command(us->srb)�������,������������������Լ�д��,�����е�����,����Ҳ��
// �г���.�������������drivers/usb/storage/debug.c��, 
     55 void usb_stor_show_command(struct scsi_cmnd *srb) 
     56 { 
     57         char *what = NULL; 
     58         int i; 
     59 
     60         switch (srb->cmnd[0]) { 
     61         case TEST_UNIT_READY: what = "TEST_UNIT_READY"; break; 
     62         case REZERO_UNIT: what = "REZERO_UNIT"; break; 
     63         case REQUEST_SENSE: what = "REQUEST_SENSE"; break; 
     64         case FORMAT_UNIT: what = "FORMAT_UNIT"; break; 
     65         case READ_BLOCK_LIMITS: what = "READ_BLOCK_LIMITS"; break; 
     66         case REASSIGN_BLOCKS: what = "REASSIGN_BLOCKS"; break; 
     67         case READ_6: what = "READ_6"; break; 
     68         case WRITE_6: what = "WRITE_6"; break; 
     69         case SEEK_6: what = "SEEK_6"; break; 
     70         case READ_REVERSE: what = "READ_REVERSE"; break; 
     71         case WRITE_FILEMARKS: what = "WRITE_FILEMARKS"; break; 
     72         case SPACE: what = "SPACE"; break; 
     73         case INQUIRY: what = "INQUIRY"; break; 
     74         case RECOVER_BUFFERED_DATA: what = "RECOVER_BUFFERED_DATA"; 
break; 
     75         case MODE_SELECT: what = "MODE_SELECT"; break; 
     76         case RESERVE: what = "RESERVE"; break; 
     77         case RELEASE: what = "RELEASE"; break; 
     78         case COPY: what = "COPY"; break; 
     79         case ERASE: what = "ERASE"; break; 
     80         case MODE_SENSE: what = "MODE_SENSE"; break; 
     81         case START_STOP: what = "START_STOP"; break; 
     82         case RECEIVE_DIAGNOSTIC: what = "RECEIVE_DIAGNOSTIC"; break; 
     83         case SEND_DIAGNOSTIC: what = "SEND_DIAGNOSTIC"; break; 
     84         case ALLOW_MEDIUM_REMOVAL: what = "ALLOW_MEDIUM_REMOVAL"; 
break; 
     85         case SET_WINDOW: what = "SET_WINDOW"; break; 
     86         case READ_CAPACITY: what = "READ_CAPACITY"; break; 
     87         case READ_10: what = "READ_10"; break; 
     88         case WRITE_10: what = "WRITE_10"; break; 
     89         case SEEK_10: what = "SEEK_10"; break; 
     90         case WRITE_VERIFY: what = "WRITE_VERIFY"; break; 
     91         case VERIFY: what = "VERIFY"; break; 
     92         case SEARCH_HIGH: what = "SEARCH_HIGH"; break;   141
     93         case SEARCH_EQUAL: what = "SEARCH_EQUAL"; break; 
     94         case SEARCH_LOW: what = "SEARCH_LOW"; break; 
     95         case SET_LIMITS: what = "SET_LIMITS"; break; 
     96         case READ_POSITION: what = "READ_POSITION"; break; 
     97         case SYNCHRONIZE_CACHE: what = "SYNCHRONIZE_CACHE"; break; 
     98         case LOCK_UNLOCK_CACHE: what = "LOCK_UNLOCK_CACHE"; break; 
     99         case READ_DEFECT_DATA: what = "READ_DEFECT_DATA"; break; 
    100         case MEDIUM_SCAN: what = "MEDIUM_SCAN"; break; 
    101         case COMPARE: what = "COMPARE"; break; 
    102         case COPY_VERIFY: what = "COPY_VERIFY"; break; 
    103         case WRITE_BUFFER: what = "WRITE_BUFFER"; break; 
    104         case READ_BUFFER: what = "READ_BUFFER"; break; 
    105         case UPDATE_BLOCK: what = "UPDATE_BLOCK"; break; 
    106         case READ_LONG: what = "READ_LONG"; break; 
    107         case WRITE_LONG: what = "WRITE_LONG"; break; 
    108         case CHANGE_DEFINITION: what = "CHANGE_DEFINITION"; break; 
    109         case WRITE_SAME: what = "WRITE_SAME"; break; 
    110         case GPCMD_READ_SUBCHANNEL: what = "READ SUBCHANNEL"; break; 
    111         case READ_TOC: what = "READ_TOC"; break; 
    112         case GPCMD_READ_HEADER: what = "READ HEADER"; break; 
    113         case GPCMD_PLAY_AUDIO_10: what = "PLAY AUDIO (10)"; break; 
    114         case GPCMD_PLAY_AUDIO_MSF: what = "PLAY AUDIO MSF"; break; 
    115         case GPCMD_GET_EVENT_STATUS_NOTIFICATION: 
    116                 what = "GET EVENT/STATUS NOTIFICATION"; break; 
    117         case GPCMD_PAUSE_RESUME: what = "PAUSE/RESUME"; break; 
    118         case LOG_SELECT: what = "LOG_SELECT"; break; 
    119         case LOG_SENSE: what = "LOG_SENSE"; break; 
    120         case GPCMD_STOP_PLAY_SCAN: what = "STOP PLAY/SCAN"; break; 
    121         case GPCMD_READ_DISC_INFO: what = "READ DISC INFORMATION"; 
break; 
    122         case GPCMD_READ_TRACK_RZONE_INFO: 
    123                 what = "READ TRACK INFORMATION"; break; 
    124         case GPCMD_RESERVE_RZONE_TRACK: what = "RESERVE TRACK"; break; 
    125         case GPCMD_SEND_OPC: what = "SEND OPC"; break; 
    126         case MODE_SELECT_10: what = "MODE_SELECT_10"; break; 
    127         case GPCMD_REPAIR_RZONE_TRACK: what = "REPAIR TRACK"; break; 
    128         case 0x59: what = "READ MASTER CUE"; break; 
    129         case MODE_SENSE_10: what = "MODE_SENSE_10"; break; 
    130         case GPCMD_CLOSE_TRACK: what = "CLOSE TRACK/SESSION"; break; 
    131         case 0x5C: what = "READ BUFFER CAPACITY"; break; 
    132         case 0x5D: what = "SEND CUE SHEET"; break; 
    133         case GPCMD_BLANK: what = "BLANK"; break; 
    134         case MOVE_MEDIUM: what = "MOVE_MEDIUM or PLAY AUDIO (12)"; break; 
    135         case READ_12: what = "READ_12"; break;   142
    136         case WRITE_12: what = "WRITE_12"; break; 
    137         case WRITE_VERIFY_12: what = "WRITE_VERIFY_12"; break; 
    138         case SEARCH_HIGH_12: what = "SEARCH_HIGH_12"; break; 
    139         case SEARCH_EQUAL_12: what = "SEARCH_EQUAL_12"; break; 
    140         case SEARCH_LOW_12: what = "SEARCH_LOW_12"; break; 
    141         case SEND_VOLUME_TAG: what = "SEND_VOLUME_TAG"; break; 
    142         case READ_ELEMENT_STATUS: what = "READ_ELEMENT_STATUS"; break; 
    143         case GPCMD_READ_CD_MSF: what = "READ CD MSF"; break; 
    144         case GPCMD_SCAN: what = "SCAN"; break; 
    145         case GPCMD_SET_SPEED: what = "SET CD SPEED"; break; 
    146         case GPCMD_MECHANISM_STATUS: what = "MECHANISM STATUS"; break; 
    147         case GPCMD_READ_CD: what = "READ CD"; break; 
    148         case 0xE1: what = "WRITE CONTINUE"; break; 
    149         case WRITE_LONG_2: what = "WRITE_LONG_2"; break; 
    150         default: what = "(unknown command)"; break; 
    151         } 
    152         US_DEBUGP("Command %s (%d bytes)\n", what, srb->cmd_len); 
    153         US_DEBUGP(""); 
    154         for (i = 0; i < srb->cmd_len && i < 16; i++) 
    155                 US_DEBUGPX(" %02x", srb->cmnd[i]); 
    156         US_DEBUGPX("\n"); 
    157 } 
//   ���ż�ʹ������������ߵ�ɵ��Ҳ�ܿ����������,�ܼ�,���ǰ�Ҫִ�е�scsi �����ӡ����.�г���
// ������û�����˼,�ò���Ϥscsi��ͬ־��֪�������ϻ�����Щɶ����.��Ȼ,�ղ�˵���Ǹ�INQUIRYҲ��
// �������е�. 
// ��������������� easy,��Ҫ�ǲ���Ϥ scsi Э��Ļ�,�㻹��Ľ��Ͳ����������.������˵
// srb->cmnd[]������鵽����ʲô����?��ʲô��ʽ?Ϊɶ����һ��ʼֻ�ж� cmnd[0]?ʵ������,�����
// ������ѧ��.����,��scsi �Ĺ淶��߶�����һЩ����,ÿ�������һ���ĸ�ʽ,������ֽ���Ҳ�кü���,
// �е������������ֽڵ�,�е������� 10 ���ֽڵ�,�е������� 12 ���ֽڵ�.�㿴,�㿴,�������ժ�� scsi
// �淶��ߵļ���ͼ,scsi ����͸����������. 
//  
// ����6�ֽڵ�,   143
//  
// ����10���ֽڵ�, 
//  
// ����12���ֽڵ�. 
// ֮��������ü�������������,ûʲô�ر��,Ҳ��ֻ������������Ķ����Զ���,�ֻ���,ӡ֤���Ű�
// ����Ǿ仰,Ҳ��ÿһ������ȫ���й�����������Ů��,��������.Ȣ�˺�õ��,�ö���֮,��ı����ǽ�ϵ�
// һĨ����Ѫ,�׵Ļ��ǡ���ǰ���¹⡱;Ȣ�˰�õ��,�׵ı����·��ϵ�һ����ճ��,���ȴ���Ŀ��ϵ�һ����
// ɰ��. 
// ���������ǰ����������ֽڵ������֮Ϊ CDB, command descriptor block, ������������.����
// ��ΪCDB׼����һ���ַ�����,�ṹ��struct scsi_cmnd �е�unsigned char cmnd[16],��˵����
// 12 ���ֽ�,���ﲻ����һ�� 12 ���ֽڵ�����?����һ������:�Ҽǵø�����û��һ�ſγ̽����ɳ����Է�  144
// չ,�����Ҽǵ����Ϻ������ͬѧ���޹�����һ�ſγ�,�л���Ļ�,ȥ������һ�°�. 
// Ok,��Ȼ��� CDB �� 16 ���ֽ�,��ôΪʲô����ÿ�ζ��ж� cmnd[0]�͹���?��ϸ��������ͼ,ע��
// ���Ǹ� Operation code ����?û��,����ͼ�еĵ�һ���ֽڶ�����Ϊ Operation code,����֮,��������
// ʲô���ӵ�����,  �㶼�����ڵ�һ���ֽ���ǩ���Լ�������,������˵������˭.������
// include/scsi/scsi.h ��,�����˺ö�ö��,����#define INQUIRY 0x12,�ֱ���#define READ_6 
// 0x08,�ٱ���#define FORMAT_UNIT 0x04,����,ʵ���ϲ�������൱�� scsi ��������к�,scsi ����
// �ܹ�Ҳ����ô��,8 λ�Ĳ������Ѿ��㹻��ʾ��,���,����ֻҪ��һ���ֽھͿ����жϳ������ĸ�������. 
// ��Ϊ��ĵ�һ���ֽھ��൱������۾�,��������صĶ���,��ᷢ��������������۾������������,��һ
// ��֣�л���Ÿ��������. 
// ����,����˵����,��ʼ����������������Ĳ�����. 
// �������ص� bulk����(һ) 
//   2006 ������һ������,�����˱���,��ʼ�˱�Ư������.���Ϻ���ͬ����,���������������֮��,����
// ��Ȼû���¹�һ����,�ѹ��ձ�С��˵:�����Ǳ���С�����Ҹ�,������Ǵ�ɳĮ,���˳ǾͿ��������տ�����
// ��.������,����������,���˴���,�ô�ô�,һ���������,�ؼҵ�ʱ���°���ʪ�ˡ�(����,��ôд��д��
// �����Ǹ�������ȥ�ˡ�����,�ҳ�����ֻ��һ�����°���˼����������.) 
//   ����,�������ű�������ҹ,�ֲ�����˯,�������������,����е��ر���ů,��Щ����,�ӳ�ɳ,���Ϻ�,��
// ������,ÿÿֻ����ҹ���˾���ʱ��,���Ź㲥,������ȴһЩ����.���Ǽ���д��,��Ȼ������Ļ���Ѿ�����,
// ��һ��Ҫ�������ݳ�;��Ȼ�Ų��Ѿ����,���꿲��Ҳ�����˲�;��Ȼ���Ѱ�ϣ����������,��һ��Ҫ��ֵ�
// ʤ����лĻ. 
//   375��,us->proto_handler()��ʵ��һ������ָ��,֪����ָ��ʲô��?��Ҫ˵�㲻֪��,����������
// storage_probe()��,ȷ�е�˵,��get_protocol()�͸���ֵ,��ʱֻ֪����get protocol,ȴ��֪��������
// ʲô��,���ڸ�������,����Ϊд����Ķ���ɵ��,һ��ָ��Ҫ��ûʲô���˼ҲŲ���Ϊ����ֵ��.��������
// �ͽ���,����U��,proto_handler����ֵΪ usb_stor_transparent_scsi_command,��������������
// �߰�. ���߶�����drivers/usb/storage/protocol.c: 
172 void usb_stor_transparent_scsi_command(struct scsi_cmnd *srb, 
    173                                        struct us_data *us) 
    174 { 
    175         // send the command to the transport layer // 
    176         usb_stor_invoke_transport(srb, us); 
    177 
    178         if (srb->result == SAM_STAT_GOOD) { 
    179                 // Fix the READ CAPACITY result if necessary // 
    180                 if (us->flags & US_FL_FIX_CAPACITY) 
    181                         fix_read_capacity(srb); 
    182         } 
    183 }   145
// ����ע�⵽����usb_stor_invoke_transport()������������ɲ���.����������˼��׼��, ����
// ����ȥ��ʶһ������®ɽ����Ŀ. ������drivers/usb/storage/transport.c: 
519 
//********************************************************************** 
    520//Transport routines 
    521  ****************************************************************
******// 
    522 
    523 // Invoke the transport and basic error-handling/recovery methods 
    524//
    525//This is used by the protocol layers to actually send the message to 
    526//the device and receive the response. 
    527  // 
    528 void usb_stor_invoke_transport(struct scsi_cmnd *srb, struct us_data *us) 
    529 { 
    530         int need_auto_sense; 
    531         int result; 
    532 
    533         // send the command to the transport layer // 
    534         srb->resid = 0; 
    535         result = us->transport(srb, us); 
    536 
    537         // if the command gets aborted by the higher layers, we need to 
    538        //short-circuit all other processing 
    539          // 
    540         if (test_bit(US_FLIDX_TIMED_OUT, &us->flags)) { 
    541                 US_DEBUGP("-- command was aborted\n"); 
    542                 goto Handle_Abort; 
    543         } 
    544 
    545         // if there is a transport error, reset and don't auto-sense // 
    546         if (result == USB_STOR_TRANSPORT_ERROR) { 
    547                 US_DEBUGP("-- transport indicates error, resetting\n"); 
    548                 us->transport_reset(us); 
    549                 srb->result = DID_ERROR << 16; 
    550                 return; 
    551         } 
    552 
    553         // if the transport provided its own sense data, don't auto-sense // 
    554         if (result == USB_STOR_TRANSPORT_NO_SENSE) { 
    555                 srb->result = SAM_STAT_CHECK_CONDITION; 
    556                 return; 
    557         }   146
    558 
    559         srb->result = SAM_STAT_GOOD; 
    560 
    561         // Determine if we need to auto-sense 
    562        //
    563        //I normally don't use a flag like this, but it's almost impossible 
    564        //to understand what's going on here if I don't. 
    565          // 
    566         need_auto_sense = 0; 
    567 
    568         // 
    569        //If we're running the CB transport, which is incapable 
    570        //of determining status on its own, we will auto-sense 
    571        //unless the operation involved a data-in transfer.  Devices 
    572        //can signal most data-in errors by stalling the bulk-in pipe. 
    573          // 
    574         if ((us->protocol == US_PR_CB || us->protocol == US_PR_DPCM_USB) && 
    575                         srb->sc_data_direction != DMA_FROM_DEVICE) { 
    576                 US_DEBUGP("-- CB transport device requiring auto-sense\n"); 
    577                 need_auto_sense = 1; 
    578         } 
    579 
    580         // 
    581        //If we have a failure, we're going to do a REQUEST_SENSE 
    582        //automatically.  Note that we differentiate between a command 
    583        //"failure" and an "error" in the transport mechanism. 
    584          // 
    585         if (result == USB_STOR_TRANSPORT_FAILED) { 
    586                 US_DEBUGP("-- transport indicates command failure\n"); 
    587                 need_auto_sense = 1; 
    588         } 
    589 
    590         // 
    591        //A short transfer on a command where we don't expect it 
    592        //is unusual, but it doesn't mean we need to auto-sense. 
    593          // 
    594         if ((srb->resid > 0) && 
    595             !((srb->cmnd[0] == REQUEST_SENSE) || 
    596               (srb->cmnd[0] == INQUIRY) || 
    597               (srb->cmnd[0] == MODE_SENSE) || 
    598               (srb->cmnd[0] == LOG_SENSE) || 
    599               (srb->cmnd[0] == MODE_SENSE_10))) { 
    600                 US_DEBUGP("-- unexpectedly short transfer\n"); 
    601         }   147
    602 
    603         // Now, if we need to do the auto-sense, let's do it // 
    604         if (need_auto_sense) { 
    605                 int temp_result; 
    606                 void* old_request_buffer; 
    607                 unsigned short old_sg; 
    608                 unsigned old_request_bufflen; 
    609                 unsigned char old_sc_data_direction; 
    610                 unsigned char old_cmd_len; 
    611                 unsigned char old_cmnd[MAX_COMMAND_SIZE]; 
    612                 unsigned long old_serial_number; 
    613                 int old_resid; 
    614 
    615                 US_DEBUGP("Issuing auto-REQUEST_SENSE\n"); 
    616 
    617                 // save the old command // 
    618                 memcpy(old_cmnd, srb->cmnd, MAX_COMMAND_SIZE); 
    619                 old_cmd_len = srb->cmd_len; 
    620 
    621                 // set the command and the LUN // 
    622                 memset(srb->cmnd, 0, MAX_COMMAND_SIZE); 
    623                 srb->cmnd[0] = REQUEST_SENSE; 
    624                 srb->cmnd[1] = old_cmnd[1] & 0xE0; 
    625                 srb->cmnd[4] = 18; 
    626 
    627                 // FIXME: we must do the protocol translation here // 
    628                 if (us->subclass == US_SC_RBC || us->subclass == US_SC_SCSI) 
    629                         srb->cmd_len = 6; 
    630                 else 
    631                         srb->cmd_len = 12; 
    632 
    633                 // set the transfer direction // 
    634                 old_sc_data_direction = srb->sc_data_direction; 
    635                 srb->sc_data_direction = DMA_FROM_DEVICE; 
    636 
    637                 // use the new buffer we have // 
    638                 old_request_buffer = srb->request_buffer; 
    639                 srb->request_buffer = srb->sense_buffer; 
    640 
    641                 // set the buffer length for transfer // 
    642                 old_request_bufflen = srb->request_bufflen; 
    643                 srb->request_bufflen = 18; 
    644 
    645                 // set up for no scatter-gather use //   148
    646                 old_sg = srb->use_sg; 
    647                 srb->use_sg = 0; 
    648 
    649                 // change the serial number -- toggle the high bit// 
    650                 old_serial_number = srb->serial_number; 
    651                 srb->serial_number ^= 0x80000000; 
    652 
    653                 // issue the auto-sense command // 
    654                 old_resid = srb->resid; 
    655                 srb->resid = 0; 
    656                 temp_result = us->transport(us->srb, us); 
    657 
    658                 // let's clean up right away // 
    659                 srb->resid = old_resid; 
    660                 srb->request_buffer = old_request_buffer; 
    661                 srb->request_bufflen = old_request_bufflen; 
    662                 srb->use_sg = old_sg; 
    663                 srb->serial_number = old_serial_number; 
    664                 srb->sc_data_direction = old_sc_data_direction; 
    665                 srb->cmd_len = old_cmd_len; 
    666                 memcpy(srb->cmnd, old_cmnd, MAX_COMMAND_SIZE); 
    667 
    668                 if (test_bit(US_FLIDX_TIMED_OUT, &us->flags)) { 
    669                         US_DEBUGP("-- auto-sense aborted\n"); 
    670                         goto Handle_Abort; 
    671                 } 
    672                 if (temp_result != USB_STOR_TRANSPORT_GOOD) { 
    673                         US_DEBUGP("-- auto-sense failure\n"); 
    674 
    675                         // we skip the reset if this happens to be a 
    676                        //multi-target device, since failure of an 
    677                        //auto-sense is perfectly valid 
    678                          // 
    679                         if (!(us->flags & US_FL_SCM_MULT_TARG)) 
    680                                 us->transport_reset(us); 
    681                         srb->result = DID_ERROR << 16; 
    682                         return; 
    683                 } 
    684 
    685                 US_DEBUGP("-- Result from auto-sense is %d\n", temp_result); 
    686                 US_DEBUGP("-- code: 0x%x, key: 0x%x, ASC: 0x%x, ASCQ: 
0x%x\n", 
    687                           srb->sense_buffer[0], 
    688                           srb->sense_buffer[2] & 0xf,   149
    689                           srb->sense_buffer[12], 
    690                           srb->sense_buffer[13]); 
    691 #ifdef CONFIG_USB_STORAGE_DEBUG 
    692                 usb_stor_show_sense( 
    693                           srb->sense_buffer[2] & 0xf, 
    694                           srb->sense_buffer[12], 
    695                           srb->sense_buffer[13]); 
    696 #endif 
    697 
    698                 // set the result so the higher layers expect this data // 
    699                 srb->result = SAM_STAT_CHECK_CONDITION; 
    700 
    701                 // If things are really okay, then let's show that.  Zero 
    702                //out the sense buffer so the higher layers won't realize 
    703                //we did an unsolicited auto-sense. // 
    704                 if (result == USB_STOR_TRANSPORT_GOOD && 
    705                         // Filemark 0, ignore EOM, ILI 0, no sense // 
    706                                 (srb->sense_buffer[2] & 0xaf) == 0 && 
    707                         // No ASC or ASCQ // 
    708                                 srb->sense_buffer[12] == 0 && 
    709                                 srb->sense_buffer[13] == 0) { 
    710                         srb->result = SAM_STAT_GOOD; 
    711                         srb->sense_buffer[0] = 0x0; 
    712                 } 
    713         } 
    714 
    715         // Did we transfer less than the minimum amount required? // 
    716         if (srb->result == SAM_STAT_GOOD && 
    717                         srb->request_bufflen - srb->resid < srb->underflow) 
    718                 srb->result = (DID_ERROR << 16) | (SUGGEST_RETRY << 24); 
    719 
    720         return; 
    721 
    722         // abort processing: the bulk-only transport requires a reset 
    723        //following an abort // 
    724   Handle_Abort: 
    725         srb->result = DID_ABORT << 16; 
    726         if (us->protocol == US_PR_BULK) 
    727                 us->transport_reset(us); 
    728 } 
// �üһ�,���������������е�һ������,��һ��׳�۶����˵�! ŷ���޴��������һ�׵�������������ӵ�
// ������ν�������쾡��. 
//   ͥԺ�������?��������,��Ļ������.   150
//   ���յ���ұ��,¥�߲�����̨·. 
//   
//   ���������ĺ,���ڻƻ�,�޼�����ס. 
//   �����ʻ�������,�Һ�ɹ���ǧȥ. 
//   
//  ��Ƭ���,������,������̨·����д����δ���ĸ���,���ù�ϵһ����һ��,�úܶ����ֿ��˸о��޿�
// �κ�,���û�и��˵�ָ��,äĿ��ȥ�Ķ��������ȥ����Щ����������,��ô�����ڶ������������޺�.��
// Ƭ��籩�����Ǳ�������äĿ��ѧϰ�ĺ���,�����Ի����ݲ������������Լ��ഺ����.�ػ�����,��������.
// �α���? 
// �������ص� Bulk����(��) 
//    ��ʵ�����Ѿ����˺ܾ���,���������õ��������Ѿ��ѹ��¶���������,��ô�����.�������Ǵ���,��
// �����뷨�����ھ���,��������һ�ѵ�,����Ϊ�Լ��ǵ���,�������һ����ͷ,����Ϊ�Լ�������������.��
// ��,���Ǿͼ�����,�ȿ�535��,us->transport(),�������ָ��ͬ������storage_probe��ʱ�򱻸�ֵ,
// �������ǵ�u ��,�����ص���Bulk-OnlyЭ��,���us->transport()����ֵΪ
usb_stor_Bulk_transport().����usb_stor_Bulk_transport(),��ͬ������
drivers/usb/storage/transport.c: 
948 int usb_stor_Bulk_transport(struct scsi_cmnd *srb, struct us_data *us) 
    949 { 
    950         struct bulk_cb_wrap *bcb = (struct bulk_cb_wrap *) us->iobuf; 
    951         struct bulk_cs_wrap *bcs = (struct bulk_cs_wrap *) us->iobuf; 
    952         unsigned int transfer_length = srb->request_bufflen; 
    953         unsigned int residue; 
    954         int result; 
    955         int fake_sense = 0; 
    956         unsigned int cswlen; 
    957 
    958         // set up the command wrapper // 
    959         bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN); 
    960         bcb->DataTransferLength = cpu_to_le32(transfer_length); 
    961         bcb->Flags = srb->sc_data_direction == DMA_FROM_DEVICE ? 1 << 7 : 0; 
    962         bcb->Tag = srb->serial_number; 
    963         bcb->Lun = srb->device->lun; 
    964         if (us->flags & US_FL_SCM_MULT_TARG) 
    965                 bcb->Lun |= srb->device->id << 4; 
    966         bcb->Length = srb->cmd_len; 
    967   151
    968         // copy the command payload // 
    969         memset(bcb->CDB, 0, sizeof(bcb->CDB)); 
    970         memcpy(bcb->CDB, srb->cmnd, bcb->Length); 
    971 
    972         // send it to out endpoint // 
    973         US_DEBUGP("Bulk Command S 0x%x T 0x%x L %d F %d Trg %d LUN %d 
CL %d\n", 
    974                         le32_to_cpu(bcb->Signature), bcb->Tag, 
    975                         le32_to_cpu(bcb->DataTransferLength), bcb->Flags, 
    976                         (bcb->Lun >> 4), (bcb->Lun & 0x0F), 
    977                         bcb->Length); 
    978         result = usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe, 
    979                                 bcb, US_BULK_CB_WRAP_LEN, NULL); 
    980         US_DEBUGP("Bulk command transfer result=%d\n", result); 
    981         if (result != USB_STOR_XFER_GOOD) 
    982                 return USB_STOR_TRANSPORT_ERROR; 
    983 
    984         // DATA STAGE // 
    985         // send/receive data payload, if there is any // 
    986 
    987         // Genesys Logic interface chips need a 100us delay between the 
    988        //command phase and the data phase // 
    989         if (us->pusb_dev->descriptor.idVendor == USB_VENDOR_ID_GENESYS) 
    990                 udelay(100); 
    991 
    992         if (transfer_length) { 
    993                 unsigned int pipe = srb->sc_data_direction == 
DMA_FROM_DEVICE ? 
    994                                 us->recv_bulk_pipe : us->send_bulk_pipe; 
    995                 result = usb_stor_bulk_transfer_sg(us, pipe, 
    996                                         srb->request_buffer, transfer_length, 
    997                                         srb->use_sg, &srb->resid); 
    998                 US_DEBUGP("Bulk data transfer result 0x%x\n", result); 
    999                 if (result == USB_STOR_XFER_ERROR) 
   1000                         return USB_STOR_TRANSPORT_ERROR; 
   1001 
   1002                 // If the device tried to send back more data than the 
   1003                //amount requested, the spec requires us to transfer 
   1004                //the CSW anyway.  Since there's no point retrying the 
   1005                //the command, we'll return fake sense data indicating 
   1006                //Illegal Request, Invalid Field in CDB. 
   1007                  // 
   1008                 if (result == USB_STOR_XFER_LONG) 
   1009                         fake_sense = 1;   152
   1010         } 
   1011 
   1012         // See flow chart on pg 15 of the Bulk Only Transport spec for 
   1013        //an explanation of how this code works. 
   1014          // 
   1015 
   1016         // get CSW for device status // 
   1017         US_DEBUGP("Attempting to get CSW...\n"); 
   1018         result = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe, 
   1019                                 bcs, US_BULK_CS_WRAP_LEN, &cswlen); 
   1020 
   1021         // Some broken devices add unnecessary zero-length packets to the 
   1022        //end of their data transfers.  Such packets show up as 0-length 
   1023        //CSWs.  If we encounter such a thing, try to read the CSW again. 
   1024          // 
   1025         if (result == USB_STOR_XFER_SHORT && cswlen == 0) { 
   1026                 US_DEBUGP("Received 0-length CSW; retrying...\n"); 
   1027                 result = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe, 
   1028                                 bcs, US_BULK_CS_WRAP_LEN, &cswlen); 
   1029         } 
   1030 
   1031         // did the attempt to read the CSW fail? // 
   1032         if (result == USB_STOR_XFER_STALLED) { 
   1033 
   1034                 // get the status again // 
   1035                 US_DEBUGP("Attempting to get CSW (2nd try)...\n"); 
   1036                 result = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe, 
   1037                                 bcs, US_BULK_CS_WRAP_LEN, NULL); 
   1038         } 
   1039 
   1040         // if we still have a failure at this point, we're in trouble // 
   1041         US_DEBUGP("Bulk status result = %d\n", result); 
   1042         if (result != USB_STOR_XFER_GOOD) 
   1043                 return USB_STOR_TRANSPORT_ERROR; 
   1044 
   1045         // check bulk status // 
   1046         residue = le32_to_cpu(bcs->Residue); 
   1047         US_DEBUGP("Bulk Status S 0x%x T 0x%x R %u Stat 0x%x\n", 
   1048                         le32_to_cpu(bcs->Signature), bcs->Tag, 
   1049                         residue, bcs->Status); 
   1050         if ((bcs->Signature != cpu_to_le32(US_BULK_CS_SIGN) && 
   1051                     bcs->Signature != 
cpu_to_le32(US_BULK_CS_OLYMPUS_SIGN)) || 
   1052                         bcs->Tag != srb->serial_number ||   153
   1053                         bcs->Status > US_BULK_STAT_PHASE) { 
   1054                 US_DEBUGP("Bulk logical error\n"); 
   1055                 return USB_STOR_TRANSPORT_ERROR; 
   1056         } 
   1057 
   1058         // try to compute the actual residue, based on how much data 
   1059        //was really transferred and what the device tells us // 
   1060         if (residue) { 
   1061                 if (!(us->flags & US_FL_IGNORE_RESIDUE) || 
   1062                                 srb->sc_data_direction == DMA_TO_DEVICE) { 
   1063                         residue = min(residue, transfer_length); 
   1064                         srb->resid = max(srb->resid, (int) residue); 
   1065                 } 
   1066         } 
   1067 
   1068         // based on the status code, we report good or bad // 
   1069         switch (bcs->Status) { 
   1070                 case US_BULK_STAT_OK: 
   1071                         // device babbled -- return fake sense data // 
   1072                         if (fake_sense) { 
   1073                                 memcpy(srb->sense_buffer, 
   1074                                        usb_stor_sense_invalidCDB, 
   1075                                        sizeof(usb_stor_sense_invalidCDB)); 
   1076                                 return USB_STOR_TRANSPORT_NO_SENSE; 
   1077                         } 
   1078 
   1079                         // command good -- note that data could be short // 
   1080                         return USB_STOR_TRANSPORT_GOOD; 
   1081 
   1082                 case US_BULK_STAT_FAIL: 
   1083                         // command failed // 
   1084                         return USB_STOR_TRANSPORT_FAILED; 
   1085 
   1086                 case US_BULK_STAT_PHASE: 
   1087                         // phase error -- note that a transport reset will be 
   1088                        //invoked by the invoke_transport() function 
   1089                          // 
   1090                         return USB_STOR_TRANSPORT_ERROR; 
   1091         } 
   1092 
   1093         // we should never get here, but if we do, we're in trouble // 
   1094         return USB_STOR_TRANSPORT_ERROR; 
   1095 }   154
// ��ɵ�˰�,�������Ҳ���Ǻ��ǵ�.��������������ƿ�������bulk�������ƪ��. 
// �������ص� Bulk����(��) 
//    ��usb_stor_Bulk_transport()��, ����һ���Ѫ��Ϊ����ָ������������е��õĵ�һ������Ҫ��
// ����,�Ǿ���usb_stor_bulk_transfer_buf().��Ȼ������drivers/usb/stroage/transport.c. 
//      409 // 
//     410//Transfer one buffer via bulk pipe, without timeouts, but allowing early 
//     411//termination.  Return codes are USB_STOR_XFER_xxx.  If the bulk pipe 
//     412//stalls during the transfer, the halt is automatically cleared. 
    413  // 
    414 int usb_stor_bulk_transfer_buf(struct us_data *us, unsigned int pipe, 
    415         void *buf, unsigned int length, unsigned int *act_len) 
    416 { 
    417         int result; 
    418 
    419         US_DEBUGP("%s: xfer %u bytes\n", __FUNCTION__, length); 
    420 
    421         // fill and submit the URB // 
    422         usb_fill_bulk_urb(us->current_urb, us->pusb_dev, pipe, buf, length, 
    423                       usb_stor_blocking_completion, NULL); 
    424         result = usb_stor_msg_common(us, 0); 
    425 
    426         // store the actual length of the data transferred // 
    427         if (act_len) 
    428                 *act_len = us->current_urb->actual_length; 
    429         return interpret_urb_result(us, pipe, length, result, 
    430                         us->current_urb->actual_length); 
    431 } 
  һ·������ͬ־�ǲ�����������usb_fill_bulk_urb()��ȫİ��.���ǵ�ȷ�ǵ�һ�μ��������,����
��ǰ�����м���usb_fill_control_urb(),����֮�⻹��һ������usb_fill_int_urb()�ĺ���,����˵,�⼸
�������ǲ���,ֻ�������Ƿֱ��Ӧusb����ģʽ�е�bulk,control,interrupt.Ψһһ����
usb_fill_control_urb��ͬ�ı���bulk���䲻��Ҫ��һ��setup_packet.������
��,usb_fill_bulk_urb()������include/linux/usb.h: 
845 //* 
    846//usb_fill_bulk_urb - macro to help initialize a bulk urb 
    847//@urb: pointer to the urb to initialize. 
    848//@dev: pointer to the struct usb_device for this urb. 
    849//@pipe: the endpoint pipe 
    850//@transfer_buffer: pointer to the transfer buffer 
    851//@buffer_length: length of the transfer buffer 
    852//@complete: pointer to the usb_complete_t function   155
    853//@context: what to set the urb context to. 
    854//
    855//Initializes a bulk urb with the proper information needed to submit it 
    856//to a device. 
    857  // 
    858 static inline void usb_fill_bulk_urb (struct urb *urb, 
    859                                       struct usb_device *dev, 
    860                                       unsigned int pipe, 
    861                                       void *transfer_buffer, 
    862                                       int buffer_length, 
    863                                       usb_complete_t complete, 
    864                                       void *context) 
    865 { 
    866         spin_lock_init(&urb->lock); 
    867         urb->dev = dev; 
    868         urb->pipe = pipe; 
    869         urb->transfer_buffer = transfer_buffer; 
    870         urb->transfer_buffer_length = buffer_length; 
    871         urb->complete = complete; 
    872         urb->context = context; 
    873 } 
//   �������Ǹ�usb_fill_control_urb֮���������Ӧ���Ǻܼ򵥵���.������������������Ĵ���,��
// ֪,urb->complete����ֵΪusb_stor_blocking_completion,����˵,�������֮��϶��ᱻ����.��
// ���ϴο��ƴ���������������. 
// 424��,usb_stor_msg_common()���������һ�α�����,�������껨����,���������˲�ͬ,urb��
// ���ϴ����������ύ,Ȼ����Ĳ�ȥ����,ȥִ����.���������ύ�ɹ���,��ô����ֵresult����0.��
// act_len ����¼ʵ�ʴ���ĳ���.�����⿴������������ʵ������ʲô,���Ǳ���������������.���仰˵,
// ������Ҫ���usb_stor_Bulk_transport()��usb_stor_bulk_transfer_buf�����õ�������,�Ա��β�
// ��ʵ������,�����������,���ܲ�����ŨŨ������. 
// usb_stor_Bulk_transport()������,978��,usb_stor_bulk_transfer_buf()�����õ�����.��һ
// ������,us,�����˵,�ڶ�������,us->send_bulk_pipe,��Ϊu����˵,��������һ�����ƹܵ�����,����
// ������bulk�ܵ�,һ����In,һ����Out,��������ǰ�ķ������,�����Ѿ���usb����Щ���ʲ���������
// ��,��ν�ܵ��޷Ǿ���һ��unsigned int���͵���.us->send_bulk_pipe�ͽ������������̻����˵�
// us->recv_bulk_pipe�����������Ǹ����˻�ζ��storage_probe()�е���get_pipes()������õ�.Ȼ
// �����������bcb,����ʲô����?�ٺ�,����ϸ��. 
// 950��,��������ôһ��ָ��bcb,��struct bulk_cb_wrap�ṹ���ָ��,����һ��ר��Ϊbulk only
// Э���ر�׼�������ݽṹ,����drivers/usb/storage/transport.h:  
     80 // 
     81//Bulk only data structures 
     82  //   156
     83 
     84 // command block wrapper // 
     85 struct bulk_cb_wrap { 
     86         __le32  Signature;              // contains 'USBC' // 
     87         __u32   Tag;                    // unique per command id // 
     88         __le32  DataTransferLength;     // size of data // 
     89         __u8    Flags;                  // direction in bit 0 // 
     90         __u8    Lun;                    // LUN normally 0 // 
     91         __u8    Length;                 // of of the CDB // 
     92         __u8    CDB[16];                // max command // 
     93 }; 
//   �ۼ��ֿ��ͬ־��һ���Ѿ�����,ͬһ�ļ��л���������һ�����ݽṹ,struct bulk_cs_wrap,  
// 100 // command status wrapper // 
    101 struct bulk_cs_wrap { 
    102         __le32  Signature;              // should = 'USBS' // 
    103         __u32   Tag;                    // same as original command // 
    104         __le32  Residue;                // amount not transferred // 
    105         __u8    Status;                 // see below // 
    106         __u8    Filler[18]; 
    107 }; 
// ���������ݽṹ��Ӧ�ڽ����д�˵��CBW��CSW,�� command block wrapper��command 
// status wrapper.�µ����,������Ҫ��עһ��usb mass storage bulk only transportЭ����,��Ϊ u
// ���ǰ������Э��涨�ķ�ʽȥ�������ݵ�,Bulk only���䷽ʽ���������е�,������host���豸����һ
// ��CBW,Ȼ��device���յ���CBW,������н���,Ȼ����CBW�ﶨ�������ȥִ��������������,Ȼ
// �������host����һ��CSW.CBWʵ����������ķ�װ��,��CSWʵ������״̬�ķ�װ��.(����ִ�к�
// ��״̬,�ɹ�,ʧ��,���￴������δ��...������Ҫʹ����ôһ��״̬��). ������˵ΪɶҪ�������Լ���ӳ
// ����ִ�гɹ�����״̬��װ����,�Ǻܼ�, ��װ�Ƿ��Ӹ����ûʵ����,��װ�ǳ�����Ѥ����̫��ɡ,
// ��װ��ģ������̨���߳���һ��è��.����֮���˽���֮,���spec����Ҳ������. 
//   ��ʱ�����ǾͿ��Կ���usb_stor_Bulk_transport()������,����usb_stor_bulk_transfer_buf()֮
// ǰ���Ǽ��о����ڸ�����.������,��Щ�ж�����Ϊusb_stor_bulk_transfer_buf()�������������׼��,
// ��Ӧ����Щ����Ƭ�е�ǰϷ,�������ʵĲ��ֻ�����usb_stor_bulk_transfer_buf()��,��ǰϷ�Ĵ��ڱ�
// Ȼ�Ǻ����,�Ͼ�,������Ի��:û�м����ӵ��,�������ϵķ���.�������������忴���ⲿ��ǰϷ.(��,��Ϊ
// ��������һ������Ĵ�ѧ��,���ָܹ���,��Ҫ���Լ�û�м�ǿ����־Ʒ�ʰ�!) 
//   950��,struct bulk_cb_wrap *bcb,��ֵΪ(struct bulk_cb_wrap *) us->iobuf,951��,struct 
// bulk_cs_wrap *bcs,Ҳ��ֵΪ(struct bulk_cb_wrap *) us->iobuf,Ȼ����һ��unsigned int�ı�
// ��transfer_length,��ֵΪsrb->request_bufflen.Ȼ��������Ϳ�ʼΪbcb�ĸ���Ա��ֵ��.���ǲ���
// ��һ��usb mass storage spec�е�����ͼƬ,һ����CBW�ĸ�ʽ,һ����CSW�ĸ�ʽ,   157
//  
// ����CBW, 
//  
// ����,����CSW. 
// 959��, bcb->Signature=cpu_to_le32(US_BULK_CB_SIGN),Signature��Ӧusb mass storage 
// spec��CBW ��ǰ�ĸ�bytes,��dCBWSignature,US_BULK_CB_SIGN����궨����
// drivers/usb/storage/transport.h��,  
//      96 #define US_BULK_CB_SIGN         0x43425355      //spells out USBC // 
// Ҳ��֪�����ĸ�ɵX�涨��,ֻ�а�dCBWSignature���д��43425355h���ܱ�־�Ÿ����ݰ���һ��
// CBW.����,CBW�Ĵ���ȫ������little endian��,����cpu_to_le32()�������Ҫʹ��,��ת�����ݸ�ʽ.  
//   Ȼ��bcb->DataTransferLength��ӦCBW�е� dCBWDataTransferLength.������Ǳ�־host
// ϣ�����endpoint������ٸ�bytes������.�����cpu_to_le32(transfer_length)��������.��
// transfer_length�ղ��Ѿ�˵��,����srb->request_bufflen. ��ʵ�⼸��������������ȥ����Ҫ��¼��
// ����ͬһ������.   158
//   bcb->Flags,��Ӧ��CBW�е�bmCBWFlags,bcb->Flags = srb->sc_data_direction == 
// DMA_FROM_DEVICE ? 1 << 7 : 0;��������������ݴ���ķ���,DMA_FROM_DEVICE����ǰ�潲
// ��,��ʾ�����Ǵ��豸��������.��bmCBWFlags��8λ��,����bit7��ʾ����,0��ʾData-Out,��from 
// host to the device,1��ʾ Data-in,��from the device to the host.�������������1�Ļ�Ҫ����7
// λ.  
//   bcb->Tag = srb->serial_number,���Tag��ӦCBW�е� dCBWTag,��� dCBWTag��������
// ��,host��send��ȥ,��device�������� Tag�����ݸ���ӡ����,ȷ�е�˵,device�����һ��CSW
// ����,����CSW�л���һ��dCSWTag,�������ݺ����dCBWTag��һ����,����ʵ������͸���ͷ����
// �Ƶ�.ÿһ��scsi ����ᱻ����һ��serial_number,�������������Tag��. 
//   bcb->Lun = srb->device->lun,�ܼ�,��ӦCBW�е�bCBWLUN,���Ǳ�����������Ƿ����ĸ�
// LUN��,����֪��һ���豸���֧�ֶ��LUN,��ô��Ȼÿ��LUN����һ�����.��������Ҫ��дu���ϵ�
// ĳ������,��ô��Ȼ��ָ�����ĸ�������.����豸��֧�ֶ��lun,��ô����ᱻ����Ϊ0.������Ҫע��,
// ����bcb->Lun��CBW�е�bCBWLUN ������ȫ��Ӧ,bCBWLUNֻ��4 ��bit,���������ﶨ���ʱ
// ��,Lun���� 8 λ��,����λ������ӦbCBWLUN,������λʵ��������������target id��.���Խ�������
// ��us->flags�������US_FL_SCM_MULT_TARG�����־û��,�����,˵����֧�ֶ��target��,��
// �Ǿ�Ҫ��¼�����ĸ�target. 
//   bcb->Length = srb->cmd_len,�����Ӧ��CBW �е�bCBWCBLength,���������Ч����,��λ��
// bytes. scsi�������Ч����ֻ����1 ��16֮��.�������и�CDB����,���鹲16��Ԫ��,�������Ǹղ�
// ��struct scsi_cmnd�е�cmnd���Ѿ�˵����.��969��,970�����ǰ�����srb->cmnd���������
// copy�� bcb->CDB��. 
//   ��ʱ��,ǰϷ������,usb_stor_bulk_transfer_buf��ʽ��������.���ݸ����ĵ�������������bcb,��
// ���ĸ�������US_BULK_CB_WRAP_LEN,��Ҳ�Ƕ�����drivers/usb/storage/transport.h��,  
//      95 #define US_BULK_CB_WRAP_LEN     31 
//  31����CBW�ĳ���,CBW����31��bytes.��usb_stor_bulk_transfer_buf��������Ϊ�����Ƿǳ�
// �����,�޷Ǿ����ύ��ôһ��urb,Ȼ��Ͳ��ù�����,�͵Ƚ����.�����յ�result����
// interpret_urb_result()���ص�,������ȷ��ô�᷵��USB_STOR_XFER_GOOD,���������ȷ,��ô
// usb_stor_Bulk_transport()�о�ֱ�ӷ�����,����ֵ��USB_STOR_TRANSPORT_ERROR.�����ȷ,
// ��ô����������,��ŵ����������ݴ���׶�. ��������ʼ�����ݴ���׶�֮ǰ,������������
// interpret_urb_result()����. 
// �������ص� Bulk����(��) 
//    �ڽ����ݴ���׶�֮ǰ,�Ƚ���ղŵ���ʷ��������. usb_stor_bulk_transfer_buf()��,429��,��һ
// ������Ȥ�ĺ���interpret_urb_result()������.�������ͬ������drivers/usb/storage/transport.c: 
// 277 // 
    278//Interpret the results of a URB transfer 
    279//
    280//This function prints appropriate debugging messages, clears halts on   159
    281//non-control endpoints, and translates the status to the corresponding 
    282//USB_STOR_XFER_xxx return code. 
    283  // 
    284 static int interpret_urb_result(struct us_data *us, unsigned int pipe, 
    285                 unsigned int length, int result, unsigned int partial) 
    286 { 
    287         US_DEBUGP("Status code %d; transferred %u/%u\n", 
    288                         result, partial, length); 
    289         switch (result) { 
    290 
    291         // no error code; did we send all the data? // 
    292         case 0: 
    293                 if (partial != length) { 
    294                         US_DEBUGP("-- short transfer\n"); 
    295                         return USB_STOR_XFER_SHORT; 
    296                 } 
    297 
    298                 US_DEBUGP("-- transfer complete\n"); 
    299                 return USB_STOR_XFER_GOOD; 
    300 
    301         // stalled // 
    302         case -EPIPE: 
    303                 // for control endpoints, (used by CB[I]) a stall indicates 
    304                //a failed command // 
    305                 if (usb_pipecontrol(pipe)) { 
    306                         US_DEBUGP("-- stall on control pipe\n"); 
    307                         return USB_STOR_XFER_STALLED; 
    308                 } 
    309 
    310                 // for other sorts of endpoint, clear the stall // 
    311                 US_DEBUGP("clearing endpoint halt for pipe 0x%x\n", pipe); 
    312                 if (usb_stor_clear_halt(us, pipe) < 0) 
    313                         return USB_STOR_XFER_ERROR; 
    314                 return USB_STOR_XFER_STALLED; 
    315 
    316         // timeout or excessively long NAK // 
    317         case -ETIMEDOUT: 
    318                 US_DEBUGP("-- timeout or NAK\n"); 
    319                 return USB_STOR_XFER_ERROR; 
    320 
    321         // babble - the device tried to send more than we wanted to read // 
    322         case -EOVERFLOW: 
    323                 US_DEBUGP("-- babble\n"); 
    324                 return USB_STOR_XFER_LONG;   160
    325 
    326         // the transfer was cancelled by abort, disconnect, or timeout // 
    327         case -ECONNRESET: 
    328                 US_DEBUGP("-- transfer cancelled\n"); 
    329                 return USB_STOR_XFER_ERROR; 
    330 
    331         // short scatter-gather read transfer // 
    332         case -EREMOTEIO: 
    333                 US_DEBUGP("-- short read transfer\n"); 
    334                 return USB_STOR_XFER_SHORT; 
    335 
    336         // abort or disconnect in progress // 
    337         case -EIO: 
    338                 US_DEBUGP("-- abort or disconnect in progress\n"); 
    339                 return USB_STOR_XFER_ERROR; 
    340 
    341         // the catch-all error case // 
    342         default: 
    343                 US_DEBUGP("-- unknown error\n"); 
    344                 return USB_STOR_XFER_ERROR; 
    345         } 
    346 } 
// Ӧ��˵���������������һĿ��Ȼ��.���Ǹ��ݴ������Ĳ���result�����ж�,�Ӷ���ȡ��Ӧ����
// ��.partial ��ʵ�ʴ���ĳ���,��length����������ĳ���,��������˵�ȻҪ�Ƚ�������,��Ϊ�����ڴ�,
// �Ż�ʧ��.result��usb_stor_msg_common()�����ķ���ֵ,��ʵ����״̬����,���Ϊ0˵��һ�ж���
// ˳��,���Ҳ�ǳɹ���,287����,��ӡ��result��,ͬʱ��ӡ��partial��length�ı�,ע������%u�м���
// ����/��,���ǳ���,����˵�ָ���Ӻͷ�ĸ�ķ���.Ȼ��ͨ��һ��switch����ж�result,Ϊ0,˵����������
// �д���,Ȼ�����������,���Ƿ��ز�ͬ��ֵ,һ����USB_STOR_XFER_SHORT,��һ����
// USB_STOR_XFER_GOOD.���ڷ�����Щֵ֮���õ�ʲô��Ӧ,�����Ǳ��߱߿�.Ŀǰֻ��Ҫ֪������,
// ��������������ȫ������������,����ֵֻ����USB_STOR_XFER_GOOD.��������ֵ��˵��������.
// ��������Ϊ���ݸ�switch��result,ʵ������usb core ��һ�㴫������ֵ.������ע��
// ��,interpret_urb_result������������Ǳ���Ϊһ������ֵ������usb_stor_bulk_transfer_buf()��
// ��,����֮,ǰ�߷���֮��,����Ҳ���Ͼͷ�����,���ٴη��ص���usb_stor_Bulk_transport()������.��
// ��,���ǰ���������usb_stor_Bulk_transport(),981��,���result��ΪUSB_STOR_XFER_GOOD,
// ��˵��������Щ����,��������usb_stor_Bulk_transport()Ҳ����,û��Ҫ�ٽ�����һ�׶εĴ�����.��
// ��,�ſ��Խ�����һ�׶�. 
// ʲô��һ�׶�?��ν��Bulk Only����,�ܹ����������׶�,�����׶�,���ݴ���׶�,״̬����׶�.
// ����Ȼ,������������Ľ׶ξ������ݴ���׶�,���ڴ�֮ǰ,�����Ѿ����˵�һ�׶�,�������׶�.����
// ���ǿ����������ݽ׶�. 
// 989��,990��,ʵ��û����˵,USB_VENDOR_ID_GENESYS����ĳ��˾,�⹫˾�Ĳ�Ʒ������׶�
// �����ݽ׶ξ�Ȼ������ʱ100΢��.û�취,˭Ҫ����������һ��������Ե�ʱ����.�������ǰ�,û����һ  161
// ����֬��ͿĨʱ��,û����һ����װ���������,û����һ�׹ż���װ�����,û����һ�ҹ�˾��˵�Լ��Ĳ�
// Ʒ��������,��û��ȱ�ݵ�. 
//   992��,transfer_length����Ϊ0,��Ϊ�е�������������Ҫ����������,������û�����ݽ׶�.��������
// Щ�����ݽ׶ε����,���ǽ���if��һ��. 
//   993��,ûʲô��˵��,���Ǹ������ݴ��䷽��ȷ���ý���pipe���Ƿ���pipe.  
//   Ȼ��,995��,usb_stor_bulk_transfer_sg()���������������ִ��bulk���ݴ�����.�����������
// drivers/usb/storage/transport.c��:  
// 484 // 
//     485//Transfer an entire SCSI command's worth of data payload over the bulk 
//     486//pipe. 
//     487//
//     488//Note that this uses usb_stor_bulk_transfer_buf() and 
//     489//usb_stor_bulk_transfer_sglist() to achieve its goals -- 
//     490//this function simply determines whether we're going to use 
//     491//scatter-gather or not, and acts appropriately. 
    492  // 
    493 int usb_stor_bulk_transfer_sg(struct us_data* us, unsigned int pipe, 
    494                 void *buf, unsigned int length_left, int use_sg, int *residual) 
    495 { 
    496         int result; 
    497         unsigned int partial; 
    498 
    499         // are we scatter-gathering? // 
    500         if (use_sg) { 
    501                 // use the usb core scatter-gather primitives // 
    502                 result = usb_stor_bulk_transfer_sglist(us, pipe, 
    503                                 (struct scatterlist *) buf, use_sg, 
    504                                 length_left, &partial); 
    505                 length_left -= partial; 
    506         } else { 
    507                 // no scatter-gather, just make the request // 
    508                 result = usb_stor_bulk_transfer_buf(us, pipe, buf, 
    509                                 length_left, &partial); 
    510                 length_left -= partial; 
    511         } 
    512 
    513         // store the residual and return the error code // 
    514         if (residual) 
    515                 *residual = length_left; 
    516         return result; 
    517 }   162
// ע��˵�ú����,���������һ����,�����ɻ�����������û���˵���õ���������
// ��.usb_stor_bulk_transfer_sglist()��usb_stor_bulk_transfer_buf().�������Ǹղ��Ѿ���������,
// ��ǰ����ר��Ϊscatter-gather����׼���ĺ���,��Ҳ����drivers/usb/storage/transport.c��: 
    433 // 
    434//Transfer a scatter-gather list via bulk transfer 
    435//
    436//This function does basically the same thing as usb_stor_bulk_transfer_buf() 
    437//above, but it uses the usbcore scatter-gather library. 
    438  // 
    439 int usb_stor_bulk_transfer_sglist(struct us_data *us, unsigned int pipe, 
    440                 struct scatterlist *sg, int num_sg, unsigned int length, 
    441                 unsigned int *act_len) 
    442 { 
    443         int result; 
    444 
    445         // don't submit s-g requests during abort/disconnect processing // 
    446         if (us->flags & ABORTING_OR_DISCONNECTING) 
    447                 return USB_STOR_XFER_ERROR; 
    448 
    449         // initialize the scatter-gather request block // 
    450         US_DEBUGP("%s: xfer %u bytes, %d entries\n", __FUNCTION__, 
    451                         length, num_sg); 
    452         result = usb_sg_init(&us->current_sg, us->pusb_dev, pipe, 0, 
    453                         sg, num_sg, length, SLAB_NOIO); 
    454         if (result) { 
    455                 US_DEBUGP("usb_sg_init returned %d\n", result); 
    456                 return USB_STOR_XFER_ERROR; 
    457         } 
    458 
    459         // since the block has been initialized successfully, it's now 
    460        //okay to cancel it // 
    461         set_bit(US_FLIDX_SG_ACTIVE, &us->flags); 
    462 
    463         // did an abort/disconnect occur during the submission? // 
    464         if (us->flags & ABORTING_OR_DISCONNECTING) { 
    465 
    466                 // cancel the request, if it hasn't been cancelled already // 
    467                 if (test_and_clear_bit(US_FLIDX_SG_ACTIVE, &us->flags)) { 
    468                         US_DEBUGP("-- cancelling sg request\n"); 
    469                         usb_sg_cancel(&us->current_sg); 
    470                 } 
    471         } 
    472   163
    473         // wait for the completion of the transfer // 
    474         usb_sg_wait(&us->current_sg); 
    475         clear_bit(US_FLIDX_SG_ACTIVE, &us->flags); 
    476 
    477         result = us->current_sg.status; 
    478         if (act_len) 
    479                 *act_len = us->current_sg.bytes; 
    480         return interpret_urb_result(us, pipe, length, result, 
    481                         us->current_sg.bytes); 
    482 } 
//   usb_stor_bulk_transfer_sg()������,�ж�use_sg�Ƿ�Ϊ0,�Ӷ�ȷ���Ƿ���scatter-gather.����
// use_sg���� 0�����,��ʾ����scatter-gather,��ô����usb_stor_bulk_transfer_buf()����scsi
// ����.ʵ�ʴ��ݵ����ݳ�����partial ��¼,Ȼ��length_left�ͼ�¼��ʣ�¶���û����,��ֵ��Ȼ��������
// ���ݵ��Ǹ�����.ÿ�μ�ȥʵ�ʴ��ݵĳ��ȼ���.����use_sg������ 0 ����
// ��,usb_stor_bulk_transfer_sglist()����������.���������������. 
// �������ص� Bulk����(��) 
//   usb_stor_bulk_transfer_sglist()���������һ���Ĺƻ���,����ǰ��˵��,֮���Բ��� sglist,����Ϊ
// ����ߴ���Ч��.���Ǹ�֪��,sg��Ŀ�ľ�����һ�Ѳ�������buffersһ��DMA�����Ͷ������ȥ.��ʵ��
// usb �Ĺ�����,���鲢�����.���������� usb core ��ߵ���Ϊ�����ĵĻ�,�Ǿ�����ν��.��Щ����,��
// ��֪��Ҳ��. 
//   446��,447��,aborting�˻���disconnecting��,�Ͳ�Ҫ����������. 
//   Ȼ��452��,usb_sg_init()����������,�����������drivers/usb/core/message.c,Ҳ����˵,����
// usb���Ĳ��ṩ�ĺ���,�����õ�?��ʼ��sg����.���һ��������struct usb_sg_request�ṹ���ָ
// ��.�������Ǵ�����us->current_sg�ĵ�ַ����,����us->current_sg ��һ�������ó�,����������Ҫ
// ¡�صĽ���һ��.��struct us_data��,��������ôһ����Ա,struct usb_sg_request   current_sg.
// ������ʱ���Ǽ�����current_urb,����������һ��current_sg.Ҳ����о�������,�������,ɫ��������
// ����Ŀ,�������������Ի�,ֻ���Ű������ʵ����ʶ�����ѵ�.��ʵ�����������,֮ǰ����֪��struct 
// urb��������һ��usb request,������struct usb_sg_requestʵ���ϱ�ʾ����һ��scatter gather 
// request,�����Ƿ�usb���Ĳ��������,�������ṹ����÷���һ����.����ÿ��urb����,����������ֻ
// ������һ���ṹ���������˵����ָ��Ȼ�������ڴ�,�ڶ��������ύurb,������usb_submit_urb(),
// ʣ�µ�����usb core�ͻ�ȥ�����Ǵ�����,Linux�е�ģ����ƿ�Ϳ�������,ÿ��ģ�鶼�����˷���,Ҳ
// ͬʱ�����ű����ṩ�ķ���.�������ǳ�˵��,��վ�����Ͽ��羰,���羰������¥�Ͽ���.����װ�������
// ����,��װ���˱��˵���.��Ҫ�������Эͬ����,��ֻҪ�����˼��ṩ�ĺ���ȥ����,�����ָ����ı���
// ���ݸ�����,��������������ù�,�³�֮�����˼���Ȼ��֪ͨ��.ͬ������sg request,usb coreҲʵ����
// ��Щ,����ֻ��Ҫ���벢��ʼ��һ��struct usb_sg_request�Ľṹ��,Ȼ���ύ,Ȼ��usb core�Ǳ���Ȼ
// ��֪������ô������.�л���˵,������struct usb_sg_request�ṹ��.������include/linux/usb.h: 
// 988 //* 
//     989//struct usb_sg_request - support for scatter/gather I/O 
//     990//@status: zero indicates success, else negative errno   164
//     991//@bytes: counts bytes transferred. 
//     992//
//     993//These requests are initialized using usb_sg_init(), and then are used 
//     994//as request handles passed to usb_sg_wait() or usb_sg_cancel().  Most 
//     995//members of the request object aren't for driver access. 
//     996//
//     997//The status and bytecount values are valid only after usb_sg_wait() 
//     998//returns.  If the status is zero, then the bytecount matches the total 
//     999//from the request. 
//    1000//
//    1001//After an error completion, drivers may need to clear a halt condition 
//    1002//on the endpoint. 
//    1003  // 
   1004 struct usb_sg_request { 
   1005         int                     status; 
   1006         size_t                  bytes; 
   1007 
   1008         // 
   1009        //members below are private to usbcore, 
   1010        //and are not provided for driver access! 
   1011          // 
   1012         spinlock_t              lock; 
   1013 
   1014         struct usb_device       *dev; 
   1015         int                     pipe; 
   1016         struct scatterlist      *sg; 
   1017         int                     nents; 
   1018 
   1019         int                     entries; 
   1020         struct urb              **urbs; 
   1021 
   1022         int                     count; 
   1023         struct completion       complete; 
   1024 }; 
// ����usbϵͳ����ʹ��������ݽṹ,�������ϣ��ʹ��scatter gather��ʽ�Ļ�.usb core�Ѿ�Ϊ
// ����׼���������ݽṹ����Ӧ�ĺ���,����ֻ��Ҫ���ü���.һ������������,������
// usb_sg_init,usb_sg_wait,usb_sg_cancel.����Ҫ�ύһ��sg����,��Ҫ������,����usb_sg_init��
// ��ʼ������,Ȼ��usb_sg_wait()��ʽ�ύ,Ȼ�����Ǹ����ľͶ�����.����볷��һ��sg����,��ô����
// usb_sg_cancel ����. 
//   ������˵������ϸȥ�������������ڲ������ʵ�ֵ�,�����ٵ�֪���ô���ʲô������.��������ϸ��һ
// ��usb_sg_init()������ʱ���ݸ����Ĳ���.ͷһ���ղ��Ѿ�˵��,����sg request,�ڶ���,��Ҫ��������
// �ĸ�usb�豸Ҫ���ͻ��������,���Ǹ������ݵ���us->pusb_dev,������,���ĸ�pipe,���ûʲô��˵
// ��,pipe������һ·��������.���ĸ�����,����ר���������жϴ����,�������ж϶˵����ѯ��,����  165
// bulk����,ֱ�Ӻ���,�������Ǵ�����0.������͵����������ͷֱ���sg �����sg������Ԫ�صĸ���.Ȼ
// ����߸�����,length,���ݵľ�������ϣ����������ݳ���,���һ����SLAB flag,�ڴ�������ص�һ��
// flag.�������������block I/O·����Ӧ��ʹ��GFP_NOIO,��������SLAB_NOIOʵ������һ����,
// ʵ���Ͼ���GFP_NOIO.��Ҫ����Ϊʲô��SLAB_NOIO����˵GFP_NOIO,�޿ɷ��.(����������֪
// ��Ϊʲô�Ļ�,��ȥ��������������ε���usb_submit_urb()��,���ɵ�ʱ���Ѿ�������.)��������ɹ�
// ����ֵΪ0,���򷵻ظ��Ĵ�����.��ʼ������֮��Ϳ���Ϊus->flags����US_FLIDX_SG_ACTIVE��,
// �����flagİ����?���ǻ�ȥ��usb_submit_urb(),��ʱ����ҲΪurb��������ôһ��
// flag,US_FLDX_URB_ACTIVE,��ʵ��ʷ���Ǿ��˵�����.�������ǶԴ�urb�ķ�ʽ�����Դ�sg 
// request�ķ�ʽ����һ��.������ʵ�Ǻܺ�����. 
//   �Ա�һ�µ�������usb_submit_urb()�Ĵ���,�ͻᷢ��464��471��һ�����ǲ���İ��,����������
// ��urb֮ǰ������ôһ��,usb_stor_msg_common()������,ֻ������ʱ����urb������sg,�����δ�
// ��֮����������!ֻ���������껨����,���������˲�ͬ��!Ȼ��474��,usb_sg_wait()�����õ�����.
// ������Ҫ�Ĳ�������sg request�ĵ�ַ,���Ǵ�����us->current_sg�ĵ�ַ����.���������
// ��,US_FLIDX_SG_ACTIVE���flag�Ϳ���clear����.����ֵ��������us->current_sg.status��,
// Ȼ�����������result.��us->current_sg.bytes������ʵ�ʴ���ĳ���,��������*act_len,Ȼ�󷵻�
// ֮ǰ,once more,����interpret_urb_result()ת��һ�½��. 
// ���,usb_stor_bulk_transfer_sg()��������֮ǰ������һ����,��ʣ�µĳ��ȸ�ֵ����
// *residual.*residual���β�,ʵ����&srb->resid.������usb_stor_bulk_transfer_sg()���ص�ֵ����
// interpret_urb_result()���������ֵ.������Ҫ���׵�һ����,��������ķ��ؾ���ζ��Bulk�����е�
// �ؼ��׶�,�����ݽ׶εĽ���.ʣ��һ���׶ξ���״̬�׶���,Ҫ���ݵ���CSW,���񵱳�����CBWһ��. 
//    �ص� usb_stor_Bulk_transport()��������,�жϽ���Ƿ�Ϊ USB_STOR_XFER_ERROR ����
// USB_STOR_XFER_LONG,ǰ�߱�ʾ����,��ûɶ��˵��.�����߱�ʾ�豸��ͼ���͵����ݱ�������Ҫ��
// ����Ҫ��,�����������ʹ��һ��fake sense data�����ϲ�㱨,������,���Ǻ�һ��ĳ���һ������,
// �����ϲ�,�����������ط���.fake_sense �տ�ʼ��ʼ��Ϊ 0,��������Ϊ 1,���潫���õ�.��ʱ���ٿ�.
// Ŀǰֻ��Ҫ֪������,������������ǲ�����,ʵ����usb mass storage bulk-only spec��߾Ͷ�����
// �������,spec ˵�˶��������,��һ���׶λ���Ҫ��������.�����豸����Ҫ������,�Ǿ�ֻ����֪����,
// ����˵������ֻ�Ƕ���˵,������ʮ��Ǯ��,��ȴӲ������һ�ٿ�Ǯ.(��ֻ�Ǵ���ȷ�,��������.)����һ��˵,
// ���,ԭ���ߢһö��Ҷ,��ȴ�����������ķ���. 
//   ��� , ����һ�� ,USB_STOR_XFER_LONG ֻ�������Լ������һ���� , ʵ��������
// interpret_urb_result()���������,�����Ĵ� usb core ��һ�㴫�ݹ����Ľ���ǽ���-EOVERFLOW,
// ��һ���� interpret_urb_result ���������ҵ���Ӧ��ϵ.-EOVERFLOW ���Ǿͳ�����,����˼��,������
// ��. 
//   �������,�ٽ���һ��,ʵ���� usb core ��һ�����������Ի���һ����Ƕ� urb �Ͷ� sg �Ĵ�����.д
// �������ϲ�������ݴ�����廯Ϊrequest,urb��sg��������request,������.��usb core�����;���
// ����д�豸���������ܹ�ֻҪ����һ������,����usb core�ṩ�ĺ������г�ʼ��,Ȼ�����usb core��
// ���ĺ��������ύ,��Щ���趼�ǹ̶���,��ȫ����ʹ��ɵ�������һ��,Ȼ����̿���˯��,���߿��Ըɱ�
// ������,����֮��usb core��֪ͨ��.Ȼ����Ϳ��Խ������ɱ��������.����һ���ȷ�,�ͺñ��㿼������,
// ����һ��ǹ��,����ȥ���㿼,��ֻҪ��������Ļ�����Ϣ,�����׼��֤����,Ȼ����Ͳ��ùܱ��ʲô��,
// ʣ�µ���������ȥ����,Ȼ����Ҳ���õ�������֮��������֪ͨ��,���ֱ�ǲ������ɵ�,��Ϊ�㻹û��Ǯ��.
// �����˲�,С����?   166
// �������ص� Bulk����(��) 
// ���������Ǹÿ�����δ���CSW��.1018��,usb_stor_bulk_transfer_buf()������һ�α�����,��
// ���ǻ��CSW,����������US_BULK_CS_WRAP_LEN,���������
// drivers/usb/storage/transport.h��: 
// 109 #define US_BULK_CS_WRAP_LEN     13 
// 13 ��Ӧ CSW �ĳ���,13 �� bytes.�� cswlen ��¼��ʵ�ʴ���ĳ���.1025 ��,�������ֵ��
// USB_STOR_XFER_SHORT,�������ݴ�����,û�дﵽ������������ô��,������ cswlen �ֵ��� 0,��ô
// ˵��û�л�������� CSW,����ע����˵,��Щ��̬���豸�������ݽ׶�ĩβ���һЩ 0 ���ȵİ�����,��
// ����ζ�����ǲ�û�л�� CSW,��������ִ��һ�� usb_stor_bulk_transfer_buf(),�ٻ��һ��.(�԰�:
// ���ݴ���ʧ���˿�������һ��,����ʧȥ���ഺ������һ��ô?��,����û�в���,���춼���ֳ�ֱ��.) 
// 1032 ��,��� result ���� USB_STOR_XFER_STALLED,�� interpret_urb_result �в���һ
// ��,USB_STOR_XFER_STALLED��Ӧ��usb core����������-EPIPE,�������˵���ܵ���ͨ,���൱��
// ���������ˮ�ܵ�����,��Ȼ��Ҳ˵�� get CSW �ٴ�ʧ����...,��������ܼ�,ֱ�� retry,ΪʲôҪ
// retry?���ǿ�һ��interpret_urb_result()����,����Ҫ�ľ���310��314��,�����ж���,��Ϊ��������
// ����,bulk�˵���ܻ�������halt����,���������������Ķ˵��Ȼ������ܵ�,��������Ͳ������,��һ
// �Կ�,��������flag�Ƿ���к�ת.���Զ����������,���ǿ�������һ��.���Ǳ�����һ�Ե���̬ȥretry,
// Ӧ��˵������̬����ȷ��,��������һ��,����ʵ���Ϸ�ӳ�ľ���Linux���뱳�����ѧ,��ӳ����һ���¸�
// ��Դ��۵�����̬��,һö����Ҫ��һ����ʱ����ܽ�������ɳ��ת����һ���������������,���Ĳʺ�
// ����ɲ�ǵ�����ȴҪ����������ˮ��.�������Щ��������һ����һ�δ���,��ô�Ǵ��۳ɾ��˹�ʶ�Ŀ��
// ����������Ĳʺ�.����Ҫ����,ʧ�ܲ�������,ʧ����ͨ���ɹ��ĵ�·. 
// ��������������һ�����ӵĻ�,(��ǰ���¹ⶼ�ܿ��ɵ���˪����,�����ǽ�����?)��Ӧ�ûῴ�����
// ���ݸ�usb_stor_bulk_transfer_buf()���������һ������������֮ǰ����,�����NULL,������Ϊʵ
// ����cswlen��Ϊһ����ʱ����,��������״̬�׶ε�ʵ�ʴ��䳤��,����������������������Ѿ�����Ҫ
// ʹ�������ʱ������. 
//   1042��,�üһ�,�������ô���»�ȡ�˻����ɹ��Ļ�,������Ϲ���󹤷���,ֱ�ӷ��ذ�,���쵼�㱨��
// �豸��ҩ�ɾ���.û�취,����USB_STOR_TRANSPORT_ERROR,�����ﻹ���ɹ�����ľ������˾���
// ��.ʲô?��˵ʧ���ǳɹ�֮ĸ?������仰��û������,������ʧ����������֮ǰ�Ѿ�������... 
// ����1046�п�ʼ,��ʽ����CSW��.������Ǵ�usb mass storage bulk onlyЭ����ץ�������Ƿ�
// ͼ,�Ƿ�����CSW�ĸ�ʽ��ͼ,bcs->Residue��Ӧ��CSW��dCSWDataResidue,����ʾ����ʵ�ʴ���
// �����ݺ�������������ݵĲ�ֵ.bcs->Signature��Ӧ��CSW�е� dCSWSignature,bcs->Tag ��Ӧ
// ��CSW�е�dCSWTag,��bcs->Status��Ӧ��bCSWStatus.������Щ����û�����,���˺�����,����
// û�ʸ�,·�����ߵ�.��bcs�г�Ա�Ĵ洢��ʽ��Ȼ��������,�е���little endian��,��Щȴ����.������Щ
// little endian��,������Ҫ������cpu_to_le32�����ĺ���ת��,��������ȴ����Ҫת��,����bcs��˵,
// ���ԱResidue��Signature����Ҫ����ת��.��Щ��ط·���û�е����.    167
//   1050��,��֮ǰbcb��ʹ��US_BULK_CB_SIGNһ��,US_BULK_CS_SIGN�����������־�����
// �ݰ���һ��CSW��.��US_BULK_CS_OLYMPUS_SIGNҲ��һ����,��������רΪĳ�ֱ�̬�豸ר��׼
// ����.��������ͽ��������ᵽ��һЩ����Ȼ����drivers/usb/storage/transport.h ��, 
110 #define US_BULK_CS_SIGN         0x53425355      // spells out 'USBS' // 
    111 // This is for Olympus Camedia digital cameras // 
    112 #define US_BULK_CS_OLYMPUS_SIGN         0x55425355      // spells out 
'USBU' // 
    113 #define US_BULK_STAT_OK         0 
    114 #define US_BULK_STAT_FAIL       1 
    115 #define US_BULK_STAT_PHASE      2 
// �Դ������ͨ���豸��˵,���Ҫ��־һ��CSW��,��Signature���� 53425355h.����Olympus 
// Camedia�����������ƫƫҪ��������,����Ǹ�����������,����Ҳû�취.�����˼�������Ǵ�����˹
// ���������,���ǲ���Ѱ��·. 
//   Tag���Ǻ� CBW���Ӧ��,����TagӦ����ͬ.Ҫ��ȻҲ�Ͳ��н�ͷ������.ǰ��ΪTag��ֵΪ
// srb->serial_number,�����ȻҲӦ�õ������ֵ. 
//   ��bcs->Status,��־����ִ���ǳɹ�����ʧ��,������0���������ǳɹ���,�����Ƿ�0,�ٺ�,�϶�����
// ��.Ŀǰ��spec�涨,��ֻ����00h,01h,02h,��03h �� FFh���Ǳ�����,������,����������ж����Ƿ�
// �Ǵ���US_BULK_STAT_PHASE,Ҳ����˵�Ƿ�����02h,�����˵�Ȼ�Ͳ���.��,������,����˵��Щ��
// �����������Ļ�,��ôһ�����������.���ش���ֵ��. 
//   1060����1066��,���residue��Ϊ0,��ô˵������û����,����˵��Ԥ�ڵĲ�һ��,��ô��ϸ��һ��,
// ���ȸ��豸Ӧ��û������US_FL_IGNORE_RESIDUE���flag,�Ϲ��,�����ǿ�һ��ʲô�����豸����
// �����flag, 
    269 // Yakumo Mega Image 37 
    270//Submitted by Stephan Fuhrmann <atomenergie@t-online.de> // 
    271 UNUSUAL_DEV(  0x052b, 0x1801, 0x0100, 0x0100, 
    272                 "Tekom Technologies, Inc", 
    273                 "300_CAMERA", 
    274                 US_SC_DEVICE, US_PR_DEVICE, NULL, 
    275                 US_FL_IGNORE_RESIDUE ), 
    276 
    277 // Another Yakumo camera. 
    278//Reported by Michele Alzetta <michele.alzetta@aliceposta.it> // 
    279 UNUSUAL_DEV(  0x052b, 0x1804, 0x0100, 0x0100, 
    280                 "Tekom Technologies, Inc", 
    281                 "300_CAMERA", 
    282                 US_SC_DEVICE, US_PR_DEVICE, NULL, 
    283                 US_FL_IGNORE_RESIDUE ), 
    284 
    285 // Reported by Iacopo Spalletti <avvisi@spalletti.it> //   168
    286 UNUSUAL_DEV(  0x052b, 0x1807, 0x0100, 0x0100, 
    287                 "Tekom Technologies, Inc", 
    288                 "300_CAMERA", 
    289                 US_SC_DEVICE, US_PR_DEVICE, NULL, 
    290                 US_FL_IGNORE_RESIDUE ), 
    291 
    292 // Yakumo Mega Image 47 
    293//Reported by Bjoern Paetzel <kolrabi@kolrabi.de> // 
    294 UNUSUAL_DEV(  0x052b, 0x1905, 0x0100, 0x0100, 
    295                 "Tekom Technologies, Inc", 
    296                 "400_CAMERA", 
    297                 US_SC_DEVICE, US_PR_DEVICE, NULL, 
    298                 US_FL_IGNORE_RESIDUE ), 
    299 
    300 // Reported by Paul Ortyl <ortylp@3miasto.net> 
    301//Note that it's similar to the device above, only different prodID // 
    302 UNUSUAL_DEV(  0x052b, 0x1911, 0x0100, 0x0100, 
    303                 "Tekom Technologies, Inc", 
    304                 "400_CAMERA", 
    305                 US_SC_DEVICE, US_PR_DEVICE, NULL, 
    306                 US_FL_IGNORE_RESIDUE ), 
// һ����豸�ǲ����������flag��,����ȷʵ����ôһЩ�豸���������flag��,��һ��
// drivers/usb/storage/unusual_devs.h,����Tekom��˾���������ȫ������ôһ������.���flag��
// ��˼����ȷ,���������豸����Ҫ���ں�CSW�е��Ǹ� dCSWDataResidue,��Ϊʮ�а˾�����ֽڻ㱨
// �Ķ����Ǵ��,�ǲ�׼��,��Ȼ��Ҳ������һ��Ӳ��bug��������.���������жϵľ������flagû����,��
// ��srb->sc_data_direction����DMA_TO_DEVICE,���������,���͸��豸�����ݳ��Ȳ�Ӧ�ó���
// transfer_length.��1064��srb->resid���������Ǵ��ݸ�usb_stor_bulk_transfer_sg�Ĳ���,��¼
// �ľ���ʣ�µ����ݳ���,(�����ڴ�ֵ��10,������8,��ôʣ�����2.�׳ն�֪��.),��residue�ոձ��ٴ�
// ��ֵ��,����ԭ����residue ����transfer_length,Ҫ֪��ԭ����residue���� dCSWDataResidue,��
// ���豸���ݹ�����,����֮,��Ӳ������������,��δ�ؾͺ����������������ͬ.����srb->resid��ʱ���
// ����residue ��,��Ӳ����Ϊ׼��.��������˵����,�⼸�д���ʵ�����漰��һ����Ϊ��֪�Ļ���,�����
// ������ÿ�춼���˱���,ÿ�춼�����ں����,���������ǳ�˵�����������µ���,����Զ����֪����һ��
// ��ù�Ļ���˭.����������ֻ���ϲ��ں�.�����㿴��δ����ʱ��,һ��������ΪʲôҪ�жϴ��䷽���ǲ�
// ��DMA_TO_DEVICE�԰�,��ʵ��������һ��Ӳ����bug,�����豸�����ⶫ��,����ľ���ʵս,����
// ����usb-storage��ôһ��ͨ�õ�ģ��,��Ҫ֧�ָ��ָ������豸,�����������ǼҵĻ�������ҵ�,ֻҪ
// ����������usb mass storage�豸,�������ֲ�׼���Լ�ר��дһ���豸����,��ô�������
// usb-storage��Ӧ��֧��������豸.��,��ʵս��,���Ƿ���,��Щ�豸,������ִ�ж�������ʱ��,������
// ��״̬�׶λ㱨һ�������dCSWDataResidue,����˵���籾��û�д�����ȫ˳��,�ô������ֽھʹ�
// �˼����ֽ�,����˵�������,dCSWDataResidueӦ���Ǽ�¼��0,����ʵ������Щ�豸ȴ�����ֵ���
// ��ĳ������,��˵�ⲻ�Ǻ�����?��������Ƿ������ֵ������,��ô��������scsi ���Ĳ㷴ӳ����������
// ������Ľ����ʱ��ͻ�˵�������ִ��ʧ����.����ʵ����Щ�豸ִ�ж�������û������,�����������
// �ѱ�����,�����ն.������������ͼ�����ôһ����־,���ڶ�����,������ΪDMA_FROM_DEVICE����
// ��,���Ǿͺ������dCSWDataResidue,����֮,Ҳ���Ǻ���residue,����ֱ�ӷ��ظ�scsi �Ǳ�  169
// srb->resid�Ϳ�����.��֮,����д����,������ΪDMA_TO_DEVICE�Ĳ���,���ǵ�Ȼ��Ը����Ե�޹ʵ�
// ������Ч��dCSWDataResidue��.���Զ���DMA_TO_DEVICE�����,�������շ��ظ�scsi ���Ĳ��
// srb->resid����srb->resid ��residue���Ǹ���һ���Ϊ׼.�����Ϊʲô��������Ҫ�жϻ���������
// ����US_FL_IGNORE_RESIDUE��ôһ��flag,��������ִ�е��Ƕ�����,�����������������Ҫ���Ե�
// residue,��֮���ǾͲ�����.������Ȥ����,����ǰ,ĳ������ȥ��Դ������Թ,˵������һ���й���������
// ��MP3,���豸��д������ʱ������Ī������ı���,������Windows ��ȴ�õúúõ�.�����һ����,
// �����������������,������豸��д��ʱ�����dCSWDataResidue,������������Щ��ƵĻ�˵��
// ��,�����豸��ִ��д�����ʱ��,����dCSWDataResidue��д������Ϣ.����д��������ȷ��ִ����,��
// ��ƫƫҪ��scsi�Ǳ���Ϊ����û��ִ�гɹ�.����,ĳλ˧����ύ��һ��patch,������жϷ���Ĵ���ȥ
// ����,��Ϊ������д���п��ܳ�����,��ô�ɴ���ж���,�������Ե�����,Ҳ���,����������������豸,
// �ͱ�������US_FL_IGNORE_RESIDUE���flag��.��ʱ�Ǹ�patch��������: 
// ===== drivers/usb/storage/transport.c 1.151 vs edited ===== 
// --- 1.151/drivers/usb/storage/transport.c 2004-10-20 12:38:15 -04:00 
// +++ edited/drivers/usb/storage/transport.c 2004-10-28 10:50:42 -04:00 
// @@ -1058,8 +1058,7 @@ 
//   // try to compute the actual residue, based on how much data 
//  //was really transferred and what the device tells us // 
//   if (residue) { 
// -  if (!(us->flags & US_FL_IGNORE_RESIDUE) || 
// -    srb->sc_data_direction == DMA_TO_DEVICE) { 
// +  if (!(us->flags & US_FL_IGNORE_RESIDUE)) { 
//     residue = min(residue, transfer_length); 
//     srb->resid = max(srb->resid, (int) residue); 
//    } 
// ͬʱ����Ҳ�ѵ�ʱȥ��Դ������Թ����λ���ǵĵ�����Ϣ������: 
//   usb-storage: Command WRITE_10 (10 bytes) 
//   usb-storage:  2a 00 00 00 01 37 00 00 08 00 
//   usb-storage: Bulk Command S 0x43425355 T 0x82 L 4096 F 0 Trg 0 LUN 0 CL 10 
//   usb-storage: usb_stor_bulk_transfer_buf: xfer 31 bytes 
//   usb-storage: Status code 0; transferred 31/31 
//   usb-storage: -- transfer complete 
//   usb-storage: Bulk command transfer result=0 
//   usb-storage: usb_stor_bulk_transfer_sglist: xfer 4096 bytes, 2 entries 
//   usb-storage: Status code 0; transferred 4096/4096 
//   usb-storage: -- transfer complete 
//   usb-storage: Bulk data transfer result 0x0 
//   usb-storage: Attempting to get CSW... 
//   usb-storage: usb_stor_bulk_transfer_buf: xfer 13 bytes 
//   usb-storage: Status code 0; transferred 13/13 
//   usb-storage: -- transfer complete 
//   usb-storage: Bulk status result = 0 
//   usb-storage: Bulk Status S 0x53425355 T 0x82 R 3072 Stat 0x0   170
//   usb-storage: -- unexpectedly short transfer 
//   usb-storage: scsi cmd done, result=0x10070000 
//   SCSI error : <0 0 0 0> return code = 0x10070000 
//   end_request: I/O error, dev sda, sector 311 
//   Ӧ��˵�����Ϣ�����Ĵ�ӡ��������Bulk��������ô���е�.һ�������׶�,Command/Data/Status,
// ����ִ�е��������WRITE_10,��������һ�γɹ��Ĵ���,������󷵻�ֵresultȴ��Ϊ0,����
// 0x10070000,�������0x10070000��γ�����,�����Ժ��֪��.���������scsi core�ǱߵĴ����
// ӡ������,���ǲ��ù�,ֻ����Ҫ֪���������շ��ظ�scsi���Ĳ��һ��������Ϣ����srb->result.������
// �ǿ���scsi �Ǳߴ�ӡ��һ��reture code,�����������result��һ����.��ʵ��ӡ�Ķ���srb->result.
// ����Ȼ,srb��������൱��usb-storage��scsi �Ǳߵ�����,����������ģ��. 
// Ok,����������.1068�п�ʼ����CSW���ص�״̬,���жϽ����.�жϵ�ֵ����bcs->Status.�����
// 0,��ô��������ִ�гɹ���.����bcs->Status��ȡֵ,usb mass storage bulk only spec����涨��
// �����,�ο��������ͼ 
//  
// ����ǰ�濴��,���Ƕ�����������US_BULK_STAT_OK / US_BULK_STAT_FAIL / 
// US_BULK_STAT_PHASE ,�ֱ��Ӧ00h,01h,02h.�����������Ǿ������������������ж�.����������
// ��,�����US_BULK_STAT_FAIL,��ô����USB_STOR_TRANSPORT_FAILED,�����
// US_BULK_STAT_PHASE,��ô����USB_STOR_TRANSPORT_ERROR.����ûɶ��˵��,������
// drivers/usb/storage/transport.h��һ���������ĸ������ĺ�: 
//     131 // 
//     132//Transport return codes 
//     133  // 
//     134 
//     135 #define USB_STOR_TRANSPORT_GOOD    0   // Transport good, command 
good     // 
    136 #define USB_STOR_TRANSPORT_FAILED  1   // Transport good, command 
failed   // 
    137 #define USB_STOR_TRANSPORT_NO_SENSE 2  // Command failed, no 
auto-sense    // 
    138 #define USB_STOR_TRANSPORT_ERROR   3   // Transport bad (i.e. device dead) 
//   171
// ����˼��������,�������Ͼ��ܿ�����.�����ܹ�����������������㲻�ῴ������.�������ﷵ����Щֵ
// �Ժ�������δ����������Ժ��������������˾�֪����.��һ������,FAILED��ERROR������Ҳ����
// ��,һ����˵����û����,��������ִ�е�ʱ���д���,��һ���Ǵ��䱾����д�. 
// ��������������US_BULK_STAT_OK�������,�������˵��,����ɹ���.����������Ҫ�ж�
// fake_sense.ʲô��fake_sense?������һ������ר�������������,��Ҫ֪������,����������return
// ����ζ��usb_stor_Bulk_transport()������������(��Ȼ,����һ��return,1094��,����˵���������
// ����������,�ǵ�Ȼ�����ǳ�����,����ֱ�ӷ���USB_STOR_TRANSPORT_ERROR).���ǽ�����
// usb_stor_invoke_transport(),���������ζ��һ��Bulk����Ľ���.�������Ǿ����ǰ������������
// ��Bulk�������ͷ��β����һ��.���ص�usb_stor_invoke_transport()֮������Ҫ���ľ���һЩ����
// ������,����˵�������. 
// ���Ÿо���(һ) 
// ��������ʱ�������ǻ�Ӵ���������,fake_sense��need_auto_sense,sense����˼��,�о�.����
// �������Ǹ��Ÿо���.����ǰ���ᵽ��,����豸�뷢�ͱ�����ֵ���������,��ô����ǰ�������
// fake_senseΪ1.�������������Ϊ1֮����ô��.�������ǿ��������һ����
// ��,usb_stor_sense_invalidCDB,����˭?  
//   �����ǰѾ�ͷ��׼drivers/usb/storage/scsiglue.c,  
// 479 // To Report "Illegal Request: Invalid Field in CDB // 
    480 unsigned char usb_stor_sense_invalidCDB[18] = { 
    481         [0]     = 0x70,                     // current error // 
    482         [2]     = ILLEGAL_REQUEST,          // Illegal Request = 0x05 // 
    483         [7]     = 0x0a,                     // additional length // 
    484         [12]    = 0x24                      // Invalid Field in CDB // 
    485 }; 
    486 
// ����һ���ַ�����,��18��Ԫ��,��ʼ����ʱ������4��Ԫ�ر�����ֵ,Ϊ��˵���������,���治�ò�
// �岥һ��scsi ���,���������̻���. 
// ����֪��SCSIͨ������ͨ��,��һ��������Request Sense.����������ȡ������Ϣ��,��֪��Ϊʲ
// ô,��Щ���Ļ����˰Ѵ�����Ϣ����sense data.��������ȡ���ֶ�ϲ��ȡ�ú����Ű�,���֮��,���ǹ���
// �ܶණ��ȡ���־���Щ��,����ĳ����У,��������������,��Ӣ������Ȼ����Shenyang Ligong 
// University.����û�Ļ�������ʵ������Ц����.���һ���豸���յ���һ��Request Sense����,��ô��
// ������Ϸ���򷵻�һ��sense data,���ǿ��Բο�scsi Э��,�ҵ�sense data�ĸ�ʽ�涨,����ͼ��ʾ:   172
//  
// ��׼��sense data�� 18�� bytes��.��������׼����һ��18��Ԫ�ص�����,��0��byte�ĵ���λ
// ��Ϊerror code,0x70�����ǳ�������ǵ�ǰ�������,�ڶ���byte�ĵ���λ��Ϊsense key,0x5h��
// ΪIllegal Request,���������������,��������Ĳ������Ϸ�.�����߸�byte��Ϊadditional sense 
// length���������18��Ԫ��֮�󻹻���additional sense bytes,�����ĳ��Ⱦ������ﱻ��ע��,��Щ
// additional sense bytesͨ��ָ����һЩ�������е�����,������һЩ��Χ�豸���е�����,����Ϊ����ֵ
// Ϊ0x0a.����ʮ����byte,��Ϊadditional sense code,�ⲿ�����sense key�ṩһЩ��Ϣ,Ҳ����˵
// ����sense key�����Illegal Request,��ô����֪����������������,��ô������ʲô����
// ��?additional sense code�ṩ����ϸ��һЩ��Ϣ,scsi �淶�ж�24h��������Invalid Field in CDB,
// ������������ע����˵. 
//   ����,��������������,1073��,���ǽ�usb_stor_sense_invalidCDB������ߵĶ���copy��
// srb->sense_buffer���,Ȼ�󷵻�USB_STOR_TRANSPORT_NO_SENSE.struct scsi_cmnd�ṹ
// ����������������sense_buffer��,  
115 #define SCSI_SENSE_BUFFERSIZE   96 
    116         unsigned char sense_buffer[SCSI_SENSE_BUFFERSIZE];              // 
obtained by REQUEST SENSE 
    117                                                //when CHECK CONDITION is 
    118                                                //received on original command 
    119                                                //(auto-sense) // 
// ����sense_buffer�͵ô�scsiЭ���Լ�Linux�е�scsi���Ĳ�������.scsiЭ���������ôһ����
// ��,��һ��scsi ����ִ�г��˴�,����Է���һ��REQUEST_SENSE�����Ŀ���豸,Ȼ�����᷵�ظ���
// һЩ��Ϣ,��sense data.������,scsi ���Ĳ�͵��,����һ��޵������׸��˵ײ�����,��������Ϊ�ײ���
// �����ò��Լ�����REQUEST SENSE�����Ŀ���豸.��Ȼ��,��ν��scsi core͵��������û�����ĵ���,
// ��Ϊ��Щscsi host�����Զ������������,����˵���豸�㱨˵����ִ������,����ʱscsi host�����Զ�  173
// ����REQUEST SENSE����ȥ�˽�����.����scsi core�͸ɴ��Ȩ���·�,�õײ������Լ�ȥ�����.��
// ���Ժ����ǻῴ��һ���������ֽ���need_auto_sense.����˵,REQUEST SENSE�������Ҫô����
// Ӳ�����Զ�����ȥ,Ҫô��������Զ�����ȥ,��֮scsi core��һ���ǲ�������.ֻҪ�����շ���scsi����
// ���ʱ�����ص�sense data������srb->sense_buffer��,scsi ���Ĳ���Ȼ��֪������δ�����. 
// �ٻص����Ǿ������������,����˵��,��Щ�豸���Ǽ�,������ֻ����������n���ֽ�,��ƫƫҪ����
// ����,���뷵��n+m���ֽ�,�����������������ô����?��ʵ˵,����෵�صļ����ֽ�������ȫ������
// ��,��Ϊ����ֻ���������ṩ��buffer�Ƿ�װ����,�Ƿ�ﵽ������Ҫ���length���ֽ�,����ﵽ��,��ô
// ʣ�µĲ���Ҳ��,����д�����ͬ־������������Ͽ��ǵñ�����Ҫ�ܵ�,���Ƕ����ϸ��Ҳ��������΢��.
// ����˵���Ƕ�����ɵX���豸Ҳ�Ǻܹ��ĵ�.�����������,д�����ͬ־�ǿ���,����Ӧ�����ϲ�㱨һ��,
// ˵��������������豸��˵,ִ����������Щ����.��Ϊ���������ȫ���ܾ���,����˵,һ��������Դ�
// ��һЩ����,������ĳ���豸����֧�����е�ĳ������,����ִ�������ʱ��ȥ�����������,��ô�豸�ķ�
// ��ֵ���ܾͲ�����,��ν�ı�Ԥ�ڵ�ֵҪ�����һ�ֲ������ı���,������,�����������,���Ǹɴ�͸���
// �ϲ��������������,��Linux��,���ǾͿ���ͨ��sense data�����ϲ�㱨.��֮�����������fake 
// sense,˵�������sense  data����Ķ����������Լ����úõ�,��Ϊ�����Ѿ����������Ӧ�����豸��
// ����ʲô,����Ҫ���豸����һ��REQUEST SENSE������,����ȷ�е�˵,�����������ķ��ؽ����
// US_BULK_STAT_OK,Ҳ����˵,���豸�Ƿ����ص�״̬����,�豸��Ϊ����û������,������˵�豸�Ļ�
// ����������?��ʵ˵,����־�հ�����ʼ,�Ҳ����ž���!����ӿ������ʼ,�Ҳ����ŷ���!�������İ�����ʼ,
// �Ҳ���������!�Ӵ��ܻ������ӿ�ʼ,�Ҳ������й�ƽ!��CCTV ÿ�챨ϲ�����ǿ�ʼ,�Ҳ��������滰!��
// ���ҽ��븴��΢����ϵ��ʼѧϰ�����Ӳ��,������ľ�û���Ź�Ӳ���豸.��������ë����������ë��,Ӳ
// ��bug��������.����,��������,����˵,��Ϊ�豸��Ϊ�����ǳɹ���,�����㷢��REQUEST SENSE����
// ��û��,��Ϊ�豸�����Ͳ���Ϊ��׼��sense data,��Ϊsense data��������Ϊ���ṩ������Ϣ��.���
// ������Ҫ�Լ���һ��sense data,�Ž�sense_buffer��ȥ.�Ӷ���scsi core��һ��֪������ôһ����,
// ���豸���������������. 
// ��������,usb_stor_Bulk_transport()����������������.����ֵһ������������
// ��,USB_STOR_TRANSPORT_GOOD,USB_STOR_TRANSPORT_FAILED,USB_STOR_TRANSPO
// RT_ERROR,�Լ�USB_STOR_TRANSPORT_NO_SENSE.Ȼ���ϲ��ȥ������Щ����ֵ.�����ǽ�����
// ������,�ص��������ĺ�������,��usb_stor_invoke_transport().�ڻ�ȥ֮ǰ,������Ҫ��ס�ľ���,��
// �ڸղ�˵���������,��fake_senseΪ 1 �����,���Ƿ��صľ���
// USB_STOR_TRANSPORT_NO_SENSE.һ�����ǻῴ��usb_stor_invoke_transport()�������Ӧ
// �����������. 
// ���Ÿо���(��) 
// �ص�usb_stor_invoke_transport()����,540��,��������·,�����ǲ������������,�����˵�Ȼ��
// ��ľͱ�ִ����.goto Handle_Abortȥ. 
// 546��,����д���,ע������ǰ����˵,USB_STOR_TRANSPORT_ERROR��ʾ���䱾�����������
// ��,����ܵ�����.��USB_STOR_TRANSPORT_FAILED��ֻ��˵���������û�������,�ͱ�������
// Ϊ������ڸ��ǳ�����һ��������,Ȼ����ӽ����鵽��,�����绰,�绰ͨ��,�����ҽ�,�ҳ��˽���
// ���ܻ���Լ���Ҫ�Ľ�Ʒ,������������û������,�������ʧȥ�˻���,������FAILED,������һ�ָ���
// �������,ӽ������绰��������С�Ӱ��ֻ�����,�����ֻ���ϵ�ù��,�������ERROR.������������
// �ܵ�����������,���ǻ�����Լ�д��һ������us->transport_reset(us),us->transport_reset()��  174
// ʵҲ��һ��ָ��,����Ҳ�Ǻ�����ǰ��us->transport()һ�𸳵�ֵ,����U��,���Ǹ���ֵ��
// usb_stor_Bulk_reset().��νreset,���൱��������������,ÿ������Щʲô���߰��������,���Ƕ�
// ����˵,�������ͨ���ͻᷢ��һ�ж�����.�����豸reset�Ķ���,���ǽ��������ִ����һ��֮������ר
// �Ž�.���Ҳ���.�����������,��Ȼ���ǻ�����srb->resultΪDID_ERROR.Ȼ�󷵻�. 
// 554��,�����˰�,������ж��ǲ���USB_STOR_TRANSPORT_NO_SENSE��.����ǵ�,��ô����
// ��scsi �Ľ����SAM_STAT_CHECK_CONDITION.�������ֵ,scsi ���Ĳ��Ǳ߾�֪����ȥ��
// srb->sense_buffer��ߵĶ���.SAM_STAT_CHECK_CONDITION��scsi �Ǳ߶���ĺ�,scsi Э���
// ��,scsi �����������ɸ��׶�,��������׶�,�������ݽ׶�,����״̬�׶�,�������׶���ʵ����Bulk-Only 
// spec���Ҳ��.����scsiЭ���ﻹ�涨�˸����һЩ�׶�,��scsiЭ����߳�һ���׶�Ϊһ��phase.����
// ������phase����,��������bus free phase,��selection phase,��message phase�ȵ�.��״̬��
// �ξ���Ҫ��Ŀ���豸���ظ�����һ��״̬��(status code).������Щ״̬��,��scsi �Ĺ淶��߶���ú�
// ���.��include/scsi/scsi.h��Ҳ����صĺ궨��. 
//     117 // 
    118// SCSI Architecture Model (SAM) Status codes. Taken from SAM-3 draft 
    119// T10/1561-D Revision 4 Draft dated 7th November 2002. 
    120  // 
    121 #define SAM_STAT_GOOD            0x00 
    122 #define SAM_STAT_CHECK_CONDITION 0x02 
    123 #define SAM_STAT_CONDITION_MET   0x04 
    124 #define SAM_STAT_BUSY            0x08 
    125 #define SAM_STAT_INTERMEDIATE    0x10 
    126 #define SAM_STAT_INTERMEDIATE_CONDITION_MET 0x14 
    127 #define SAM_STAT_RESERVATION_CONFLICT 0x18 
    128 #define SAM_STAT_COMMAND_TERMINATED 0x22        // obsolete in SAM-3 
// 
    129 #define SAM_STAT_TASK_SET_FULL   0x28 
    130 #define SAM_STAT_ACA_ACTIVE      0x30 
    131 #define SAM_STAT_TASK_ABORTED    0x40 
// ����,SAM_STAT_CHECK_CONDITION���Ƕ�ӦscsiЭ���е�CHECK CONDITION,��һ״̬����
// ��sense data����������Ӧ��buffer��,����scsi core�Ǳ߾ͻ�ȥ��sense buffer.����������������
// �����,��Ȼ�Ϳ��Է�����. 
// 559��,Ҫ��û���ɶ����Ļ�,�����������ǾͿ�������srb->resultΪ SAM_STAT_GOOD��,˵��
// һ�ж���ok��.��Ȼ,����֮�����ֵ�REQUEST SENSE��ִ��ʧ��,���ǻ��ٴ��޸�srb->result��. 
// ����566��,������һ������need_auto_sense�ı���,�������Ƕ������ʱ����,���︳��ֵΪ
// 0.574��588��,����if���,Ϊneed_auot_sense����ֵ,��ֵΪ1.�������Ⱥ��������ڶ���if,����
// ����ǰ����ܵ�����,REQUEST SENSE�����޵������·Ÿ������ǵײ�����,��ô���Ǿ��¸ҵ�ȥ
// �е���,��USB_STOR_TRANSPORT_FAILED�������,���Ǿ�ȥ����һ��REQUEST SENSE����.��
// �����flag�Ժ����Ǿͻῴ�����ǻ���˶�ִ��REQUEST SENSE.��ô��һ��if��?������Щע���Ѿ�
// ˵�ú�����˰�,�������Լ������̻���һ��������ĵĻ�,Ӧ�þͲ���Ҫ�ҽ�����.��ֻ˵һ��,������
// Щ����CB����DPCMЭ����豸����û���Լ�û�а취����״̬,����scsi ���Ĳ㵱Ȼ�Ͳ�֪��ȥ����  175
// �ǵ�sense buffer��,���ǲ���sense buffer�������������ִ�гɹ���񶼲�֪��,����ô��?���豸
// ���ڴ�����������Ĵ���Ҳ����Ҫʹ��sense buffer,��Ϊ���Ƕ��ڶ������Ĵ���ͨ����ֹͣ��bulk-in 
// pipe,���Ѿ���һ�������Ե��ź���,����Ҫ�ټ��sense buffer,��Ϊ���sense buffer����˵���
// sense data��Ŀ���޷Ǿ��ǳ������Ժ���֪�������ԭ��,�����������ԭ���Ѿ�������ﲻ��.������
// ��Ϊʲô���������������ص�,����ֻ��˵������,����.д�豸�������ľ��Ǿ���. 
// 594��,srb->resid����0,˵��������,ϣ������n���ֽ�,����㱨����˵ֻ������n-m���ֽ�.����
// �����г������������,�ٴ������ֽڵ�������ν,����INQUIRY,�Ҿ���֪���豸�Ļ�����Ϣ,����˵����
// ����˭,��������,ѧ�����,���,�ȵ���Щ��Ϣ,���˵����Ͷ�˵����,��˵�������˵����,����ν,ûʲ
// ôӰ��,������Щ����Ͳ����ٴ�����,������Ҫ��һ��pdf�ĵ�,�㴫��һ��Ͳ�����,�ǿ϶�����,ֱ�ӵ�
// ���ҿ��ܴ򲻿����pdf�ĵ�.��������Ҫ��д������,���˼Ҳ����㼱�͹���.�������Ǿ��ǵ���
// US_DEBUGP��ӡһ��������,Ҳ�Ͳ��˳���,��������. 
// ��������һЩ��,604�п�ʼ,һֱ��713��,���Ǿ���Ϊneed_auto_sense���������REQUEST 
// SENSE������.��ʵ��֮ǰһ��,���ǻ��ǵ����ٽ���һ��Bulk����,���������׶�,������������֮ǰ��
// ����,�����ٿ�Bulk����ͼ򵥶���,�޷Ǿ���׼��һ��struct scsi_cmnd,����
// us->transport(us->srb,us),Ȼ�������֮������.��������һ�ٶ�������������.��������͵�˵�
// ��,û����������һ��struct scsi_cmnd,����ֱ������֮ǰ���Ǹ�srb,ֻ�ǵ���us->transport֮ǰ��
// ��һЩ�ؼ��Ķ�����������,Ȼ��ִ����us->transport ֮���ٻָ�����.���Խ��������ǿ��������¼�: 
// ��old_cmnd������srb->cmnd; 
// ��old_cmd_len������srb->cmd_len; 
// �Ȱ�srb->cmnd����,Ȼ��������¸�ֵ,��REQUEST SENSE����˼����ֵ. 
// ��ͬ��������REQUEST SENSE�ĳ���Ҳ��ͬ,����RBC�������ǵ�SCSI,����Ϊ6,�����ڱ��
// ���,�䳤��Ϊ12. 
// Ȼ����old_sc_data_direction������srb->sc_data_direction,����srb->sc_data_direction��
// ��ΪREQUEST SENSE��Ҫ��,DMA_FROM_DEVICE,����Ȼ,REQUEST SENSE�����豸Ҫsense 
// data,��ô��Ȼ���ݴ��䷽���Ǵ��豸������. 
// Ȼ����old_request_buffer������srb->request_buffer,����srb->request_buffer����Ϊ
// srb->sense_buffer,ͬʱ��old_request_bufflen������srb->request_bufflen,ͬʱ��
// srb->request_bufflen����Ϊ18. 
// ��old_sg������srb->use_sg,����srb->use_sg����Ϊ0,����ô������Ҳ�ͱ������鷳��
// scatter-gather������. 
// Ȼ����old_serial_number������srb->serial_number,����srb->serial_number�����λȡ��. 
// �����old_resid������srb->resid,����srb->resid�ٴγ�ʼ��Ϊ0. 
// ��ʱ��Ϳ��Ե���us->transport(us->srb,us)��.������һ����ʱ����temp_result�����������
// ��.   176
// �����������֮��,����659 ��666��,�ͰѸղű��ݵ���Щ�������ָ�ԭ����ֵ. 
// 668��,��һ���ж��ǲ��Ǳ�������,�������goto Handle_Abort. 
// 672��,Ȼ���ж�temp_result,������result˵����δ��仹������,�Ǿ�˵����REQUEST SENSE
// ��fail��.�������ǻ�����srb->result=DID_ERROR<<16.����֮ǰ���ǻ������
// us->transport_reset(us)���豸reset,��ΪREQUEST SENSE���������˵���ܲ�����,�������
// �����ǲ��ò�����ݵ���,������,����Ҫ���Լ���һ��!��Ȼ������һ������,�����жϵ���
// US_FL_SCM_MULT_TARG���flagû������,��Ϊ�������flag���豸�ж��target,�����������
// �ǾͲ��ú��Ҹ���ȫreset ��,��ΪREQUEST SENSE���������Ȼ��һ������������,���ǱϾ�ִ�г�
// ���������ν,����ֻ�ǳ��ں������֪��һ������ִ�г����ԭ��.��ʹ��֪��Ҳû��̫��Ĺ�ϵ.û��Ҫ
// �ǵô�����ĵİ�һ�����target���豸���˼�reset ��,���ùܵ����鲻Ҫ��. 
// Ȼ��685 ��696���޷Ǿ��ǰ�temp_result��ֵ��ӡ����,��sense_buffer���ֵ��ӡ����.��Щ��
// �ǵ�����Ϣ.�Ե����豸�����ǳ�����. 
// ������֮ǰ,�����ȿ�һ��,692��,usb_stor_show_sense().�������,�ǵ�һ�γ���,�������Ǽ���
// һ�����Ƶĺ���,����usb_stor_show_command().����������,������
drivers/usb/storage/debug.c: 
    159 void usb_stor_show_sense( 
    160                 unsigned char key, 
    161                 unsigned char asc, 
    162                 unsigned char ascq) { 
    163 
    164         const char *what, *keystr; 
    165 
    166         keystr = scsi_sense_key_string(key); 
    167         what = scsi_extd_sense_format(asc, ascq); 
    168 
    169         if (keystr == NULL) 
    170                 keystr = "(Unknown Key)"; 
    171         if (what == NULL) 
    172                 what = "(unknown ASC/ASCQ)"; 
    173 
    174         US_DEBUGP("%s: ", keystr); 
    175         US_DEBUGPX(what, ascq); 
    176         US_DEBUGPX("\n"); 
    177 } 
// �������ֵ�������������,scsi_sense_key_string��scsi_extd_sense_format,��������������
// driver/scsi/constants.c,���Ҳ���.��������usb_stor_show_sense��������ĵ���.���ݸ�����ʵ��
// ��srb->sense_buffer�еļ���Ԫ��,�Ա�����ǰ�����������Ǹ�sense data�ĸ�ʽ,��֪
// sense_buffer[2]�ĵ���λ����ΪSense Key,��sense_buffer[12]�� Additional sense code,Ҳ��
// ASC,sense_buffer[13]��Additional sense code qulifier,Ҳ��ASCQ.��������������Ϊmid level  177
// �ṩ����Ҫ����Ϣ,��ҪҲ���Ǵ�����Ϣ�����쳣��Ϣ.ΪʲôҪ����������?ʵ���Ͼ���һ���ֲ������
// ����,����Ҫ����ĳ�������Ҫ˵ĳ����ĳ�ֵ�ĳ���ƺ�.����������Ҳ��������ôһ������,Sense Key
// �ǵ�һ��,ASC���Ƕ����Ĳ���,��ASCQ�����Ƕ�ASC�Ĳ���,����˵����.����������������
// usb_stor_show_sense�ͺ������,���Ǵ��ݽ�����������char����,��ʵ�ʵ���Ϣ����ĳ�ֱ���һ��
// ������������Щchar������,�����õ���������scsi ���Ĳ�ĺ���scsi_sense_key_string��
// scsi_extd_sense_format�������ŷ��������,Ҳ�н���.�����˾Ϳ��Դ�ӡ������.Yeah! 
//   699��,srb->result����ΪSAM_STAT_CHECK_CONDITION.Ϊʲô?��Ϊʲô,Request Sense
// ִ����֮��,scsi �淶��������Ӧ�ð�srb->result��ΪSAM_STAT_CHECK_CONDITION,����mid 
// level ��֪��ȥ���sense data.��Ҳ��Ϊʲô��554��,555�л���srb->resultҲΪ���ֵ,ֻ������
// ��sense data�������Լ��ֹ�׼����,����ͨ�������õ�. 
//   704���if��һС��,����������Ҫ����,need_auot_sense���flag����Ϊ1ʵ�����������ֿ��ܵ�,
// ����������usb_stor_invoke_transport()�е�һ���������һ���ֲ�����,����������������������
// ��ʼ��Ϊ0. ��һ������Ϊ1 ��λ����574 �е�ʱcheck us->protocol ΪUS_PR_CB����
// US_PR_DPCM_USB,���������豸,(�����ֻ����u��,��ô�ͱ��������豸��.)�ڶ����������flag��
// ��������ȷʵ������failure,585��,result�������USB_STOR_TRANSPORT_FAILED,���������Ȼ
// Ҫ����need_auto_sense��.��704�������ж�result �Ƿ����USB_STOR_TRANSPORT_GOOD,
// ��ô����Ȼ,���result���� USB_STOR_TRANSPORT_FAILED,��ô���Ͳ����ܵ���
// USB_STOR_TRANSPORT_GOOD,���,��������ж�һ������Ե�һ��need_auto_sense�����,
// ������������˵����,����US_PR_CB/US_PR_DPCM_USBЭ����豸�ǲ����Լ���������ִ��֮���
// Status,�������ǲ�����ִ�е��׳ɹ����,���Ƕ��������һ��REQUEST SENSE,����Ϊ�˾����ܶ��
// ��ȡһЩ��Ϣ,����һ����������,���������ܶ�һЩ������Ϣ���������ж����������.��ô����
// USB_STOR_TRANSPORT_GOOD�����,������˵������ִ����û���������,������ϸ��һ�����if
// ���,��������������⻹�ж���������������,(srb->sense_buffer[2]&0xaf)���Ϊ0,��ô˵��
// srb->sense_buffer[2]��bit0~bit3��Ϊ0,bit5Ϊ0,bit7ҲΪ0,��bit4��bit6��ʲô��������ν.(��
// ������㻹Ҫ��Ϊʲô��ô��ֻ��˵��û����.û�취,���������ֻ��10����,һ���Ƕ������Ƶ�,һ����
// ���������Ƶ�.)��Ȼ����û����Ȥ��Ϥÿһ��SCSI�����ϸ��,�����ǱϾ��ǹ�������Ӱ���,Ӧ�ö���
// �����彨��ķ������涼�����˽�,��������������ϸ�������sense_buffer[2].����sense data�ĸ�
// ʽ����ͼ,sense data�ĵڶ����ֽ�,bit0~bit3��sense key,bit4��Reserved,��������,��ʹ��
// ��.bit5��ILI,ȫ��incorrect length indicator,bit6��EOM,ȫ��End of Medium,bit7�� Filemark,
// ΰ��Ĳ���Ľ�ɽ�ʰԸ�����������ʽ������.����sense key,ScsiЭ������ô�涨��,���sense 
// keyΪ0h,��ô���������ʾNO SENSE.�������ͨ����Ӧ������ĳɹ�ִ�л��߾���
// Filemark/EOM/ILI bits�е���һ��������Ϊ��1.��Ҫע�����,scsi Э����߶�����������
// ��,Filemark/EOM/ILI/Sense Key,���Ƕ���Ϊ���ṩ������Ϣ��,ֻ��ǰ����ֻҪһ��bit���ܱ����ȷ
// ����˼��,�����һ�������ܶ���Ϣ,������Ҫ��4 ��bits,���һ��ں��渽�кܶ������Ϣ,��
// sense_buffer[12]�� sense_buffer[13],����ҲҪ������Ϊ0,����ν��ASC��ASCQ��Ϊ0,��scsi
// Э������,���������֮ΪNO ADDITIONAL SENSE INFORMATION.������һ��scsi Э������ô˵
// ��:��The REQUEST SENSE command requests that the target transfer sense data to the 
// initiator. If the target has no other sense data available to return, it shall return a sense key 
// of NO SENSE and an additional sense code of NO ADDITIONAL SENSE INFORMATION.������
// ������������Ĵ�����������˼.(ʲô?��Ҫ�ҷ�����λ�?��û�и��,�ѵ���û�Ϲ��¶���,û����
// ���޵Ŀ�?��ô�Ҵ���������������ϴǵĸ�����,ͬ־,�����������Ү!) 
// (filemark��eom������ԴŴ��豸��,�������豸�޹�.Ҳ����˵�������޹�.)   178
// ���,���������ĸ�����������ͱ�ʾ�ղ����scsi ����Ĵ���ȷʵ��Բ�������.Ӧ��˵��μ�⻹��
// ���ϸ��,�Ͼ���Դ������ͬ־�Ǿ���д���벻�����ǿ���,ÿ�ο�����,���ַ��ǻ����Ȼ��Բ���ɹ���.
// �����˼Ҽ������ô������������Ȼ�������srb->resultΪSAM_STAT_GOOD,���Ұ�
// srb->sense_buffer[0]Ҳ��Ϊ0.sense data�� byte 0�����������,Valid��Error code,�����Ϊ
// 0,���Ⱦ�˵��������sense data����Ч��, ��scsi ��׼��˵����invalid, ����scsi core��Ȼû��ʶ��
// ��ôһ��sense data,�����Ǽ�Ȼ�϶���������ǳɹ�ִ�е�,��Ȼ��û�б�Ȼ��scsi core ��ȥ�����ô
// һ��sense data��. 
// ���ϻ��˴�����ī�ͽ���704��712���if����.��Ҫ����ǿ��һ��,���������Ѿ�˵����,����U��,
// ��δ�������Ͳ�����ִ��,���������Ѿ�˵����.���Ǽ�Ȼ��������������ǰ��,��������ʲô����ȥ�ӱ�
// ��?д����,������д����ͨ�õ��豸��������,��ȻҪ���Ǹ������,������ȫ���Ÿо���,Ҳ���Ǵ����׷
// �������㷨�����ݽṹ,��Ӧ�ýӽ�ʵ��,�����Ĵ�������Ķ���ȱ�����ʸ�. 
//   ����,����need_auto_sense�����˵���һ�ξͽ�����.������ظ�һ��,˵����,REQUEST SENSE
// ��������Ӧ����mid level����,��Ӧ���ɵײ���������,����ͨ��mid-level����Ը�ⷢ�������,��Ϊʵ
// ���Ϻܶ�SCSI�������俨(SCSI host adapter)���Զ�request the sense.����Ϊ���������ü�,
// �����Ҫ��ײ�����ȥ�Ը��������.����ҪôSCSi host adapters�Զ����sense data,Ҫô��������
// LLD(�ײ���������)ȥ�����������,�����������ģ���scsiϵͳ,��Ȼֻ���������ȥʵ��,�����Ǳ���
// ��LLD���ô���������request sense. 
//   ��Ȼ��,716��,�����������ôһ������,srb->result��Ȼ����SAM_STAT_GOOD,(������559��,
// ������autosense֮ǰ��srb->result���ó���SAM_STAT_GOOD.)��ô˵������»���,��������
// �����һ������,������Ҫ��������ݳ�����srb->request_bufflen,��ʵ���ϻ�ʣ��srb->resid����
// ��û�б�����,�����������ûʲô,����struct scsi_cmnd����һ����Ա����underflow,����˼�����
// ��������������ֵ��û�дﵽ�Ļ�,���������������,�������ϲ㷴ӳ,������.���仰˵,��Щscsi����
// ��һ������,�����ٵôﵽ���������,�����Ҹ��㼱!������������ж���ôһ�������Ƿ�����,�������
// �ĳ���С��srb->underflow,��ô���÷ϻ�,���������������ж�������������������ǳɹ���,�һ���Ҫ
// �㱨˵���������ִ������.�������������,���Ƿ�����scsi core��result��DID_ERROR<<16����
// SUGGEST_RETRY<<24.DID_ERROR������Ϊ0x07,SUGGEST_RETRY Ϊ0x10.�䶨�嶼��
// include/scsi/scsi.h��.��������srb->result�����ձ�����Ϊ0x10070000��.���ǲ��ǵõ���������
// �������Ǹ�����US_FL_IGNORE_RESIDUE����MP3�ĵ�����Ϣ��?�ع�ȥ��һ��,û��,��ʱ��result
// ����0x10070000,Ҳ�������︳��ֵ.����ʱ֮���Ե���ִ������δ���,ԭ�������豸���龯,������д
// ����,��ƫҪϹдһ��residue��״̬�ֽ���ȥ.�������ǵĴ����������жϳ���д���˴�.����ɰ�ֻ�е�
// ���������ǲ�����������,����! 
//   ����,���ǵ��������Ҳ��ӽ�β����.�������н�����ʱ��,��Linux����ӳ���������Ƕ����ɵ�׷��ȴ
// ������ֹ����.�쳤�ؾ���ʱ��,�˺������޾���!--��Դ����׷�����ɵ�սʿ�׾���. 
// 720��, usb_stor_invoke_transport()�������ڷ�����.���֮ǰ��ִ��goto Handle_Abort,��ô
// 724�лᱻִ��,ʵ���Ͼ�������srb->resultΪDID_ABORT<<16,����ִ��reset.����reset,����
// �������Ͼͻὲ. 
// usb_stor_invoke_transport()���ؾͻص���usb_stor_transparent_scsi_command(),�������
// ʵ���ϲ���ʲô������,���ǵ���usb_stor_invoke_transport().Ȼ�������ж���һ��flag, 
// US_FL_FIX_CAPACITY,���Ƕ��˶Ը�ĳЩӲ��bug.���ǿ��Կ���,������flagû������,��ô  179
// usb_stor_transparent_scsi_command()�����ͻ�ʹ˷�����,���ص�usb_stor_control_thread()
// ��,���������������Ǵ�375 ��us->proto_handler(us->srb,us)����
// usb_stor_transparent_scsi_command()��,������375 ��֮����ô������֮ǰ���Ѿ�������
// ��,usb_stor_control_thread()����ػ�����,���������������ѭ����ȥ,�������˯�ߵȴ�����һ��
// ����ĵ���,����㲻ǿ��kill ��,����ж��ģ��,��ô�����ػ����쳤�ؾ�,������ʯ��,��ɽ�����⵽��ˮ
// ������... 
// Ȼ�����ǾͿ���ȥ��US_FL_FIX_CAPACITY,��������һ��Ӳ��bug,ǰ��������Ӳ��bug���ֵû���
// �Ǻܶ�,��2.6.10���ں���ֻ�����µȼ��ҹ�˾�Ĳ�Ʒ����ôһ������,�������Ÿĸ￪�ŵķ�չ,�ܶ���
// �鶼����,�����Ǽ���,�������Ǽ���,Apple��˾��iPod,ŵ���� 3250,E70,E60,N91,N80,E61,NIKON
// ��DSC D70,DSC D70s,DSC D80,���ᰮ���ŵ�P990i,M600i,Ħ��������RAZR V3x,RAZR V3i,��
// һ������Ʒ���������������.��Ȼż�Լ���Nokia 6108û����������,���ǿ��ǵ�Apple��iPod ���
// ����Ϊ��ΰ���20��IT��Ʒ֮һ,��Nokia��Ϊ����Intel����������Ҫ��customer֮һ,�Ҿ�������
// ���ǻ����б�Ҫ���������bug��.��˵��,�˽������,����ȥNokia����,ȥApple����,���ߴ�һ��,ȥ
// Ħ�������������ᰮ��������,���˼�̸һ��,ι,���,����˵��ҵĲ�Ʒ����ô��ôһ�� bug,��ô���°�?
// �ֵ����ǲ��Ǵ�������ѹ��̫��?�˼�һ������ôק,��������Ļ��֪��,�ܲ�Ҫ��ô? 
// ��������ƻ��,����ŵ����,����Ħ������,�������ᰮ����! 
// ��һ������������һ���ںܶ���ҵ�Ĳ�Ʒ�ж����ڵ� bug.д�豸������һ����ʵ�ڵ�����,��ø���ʵ
// ʵ���ڵ�Ӳ������д��Ĵ���,������Ӳ������ĳ�� bug,��ô���Ҫȥ fix ��.�����ϣ����Ϊͨ�õ���
// ������,��ô���Ҫ��˸�����ҵ,��˸��ֿ��ܴ��ڵ�bug.Ҳ��һ�ټ���ҵ�Ĳ�Ʒ�����Ժܺõı���ĳ�
// ����֧��,���������һ����һ�ҵĲ�Ʒ������,��͵þ������.usb-storage ��������һ��ģ��.������
// �Ĵ�������漰���ܶ಻ͬ����ҵ.��Ȼ������,��һ������Ҫ��ԭ��,�Ǿ���,û����ҵ��֧��,Linux ����
// �������������.���� Linux �ں˴�����֧�������ҵ���豸Ҳ�Ǳ�Ȼ��,���������ڸ���ƱͶ����ɶ���
// �Ǹ����Ǹ���������漵�ʱ��˵���Ǿ�:���������ڹ���˽,��Ӧ������. 
// �ܶ���ǰ,����ҵ�ܿ�������:���������ҵ�Ŀ����ߴ󲿷�ˮƽ����,����������߶˵���ҵ����Ʒ��. ����
// ��ʵ, ����΢�� Linux �����г���ͷ�صĻ���, ��ȷ���ڸ���������ģ����֮��. ���κ�һ����ҵ֧
// �� Linux ��Ŀ�Ķ�ֻ��Ϊ��׬Ǯ.IBM ����֧�� Linux?�ϰ�˼�뾳���?��Ϊȫ�������?�Ҹ�����,IBM
// �Դ� 2000 �꿪ʼչ�� Linux ս��,2002 �����ǼҾʹ� Linux �г���׬ȡ�� 10 ����Ԫ.���еĹ�˾֧��
// Linux��Ŀ���޷Ǿ�����Ϸ���Щ��������΢��ĲƸ�. ����鲨��˵������,����ҵֻ�����ǻ�ǮΪ���
// �����ð�һ�����˵�����,����������ͬ����һ���۵�,�Ǿ���,�ž��������������˳���,������,��Ǯ����
// �� Linux �Ϸ�΢��,������. (ע:�ž�,�ҵ�����,Ҳ���ҵ����ż��)����������,ʱ�䳤��,ÿһ��ѧϰ
// Linux ���˶�������һ�ָо�,�����Լ�������һ��ΰ��������,׷�����ɵĴ���.(֣������һ��,������
// ��,��δ����Linux��ΰ����ʲô��ϵ,ѧϰLinuxֻ�ǻ�ڷ�����.) 
// Ok,��������������ϸ�����������ƻ��,����ŵ����,����Ħ������,�������ᰮ���ŵĴ���
// ��.US_FL_FIX_CAPACITY ��� flag ������,��ζ�������豸������ôһ�� bug.�� scsi �ڶ�������,��
// һ��������� READ CAPACITY.�������úܼ�,���Ƕ�ȡ���̵�������.������ֱ�۵�ӡ���,���ǵõ�
// �����Ǹ����Ƽ����Ǹ����� sg_utils3 ô,��������ִ���� INQUIRY ����.������������ִ�� READ 
// CAPACITY,�����������ֽ��� sg_readcap.��Ҫ��װ�� SUSE Linux �Ļ�,��ߵ� rpm �����ܲ���
// sg_utils,���ǽ� scsi-xx-xx,����ż�ľ��� scsi-1.7_2.36_1.19_0.17_0.97-12.4.����������ܶ�ִ
// ��scsi ����Ĺ���.���Ҷ���man�ĵ�,�����ÿ���man��֪����.   180
// ������Ӳ�̵�,����ż��scsi Ӳ��: 
// myhost: # sg_readcap -b /dev/sda 
// 0x11040000 0x200 
// myhost: # fdisk -l /dev/sda 
//  
// Disk /dev/sda: 146.1 GB, 146163105792 bytes 
// 255 heads, 63 sectors/track, 17769 cylinders 
// Units = cylinders of 16065 * 512 = 8225280 bytes 
//  
//    Device Boot      Start         End      Blocks   Id  System 
// /dev/sda1               1         266     2136613+  83  Linux 
// /dev/sda2            2879       17769   119611957+  83  Linux 
// /dev/sda3 //        267        1572    10490445   83  Linux 
// /dev/sda4            1573        2878    10490445   82  Linux swap / Solaris 
//  
// myhost: # 
// ����sg_readcap����������Ϣ����?���ǿ��Դ��ݲ�ͬ�Ĳ���,�������������-b����,��ô�����
// block���Լ�ÿ��block���ֽ���.����������һ��,�������ﷵ�ص�����ֵ�ֱ���0x11040000��
// 0x200,0x11040000��Ӧ��ʮ����285474816,0x200����ʮ���Ƶ�512,N���豸��block��С����
// 512.��������˾������ǵ�����,��˵Ľ����146163105792,��������?��fdisk������ʾ������һģ
// һ��,�Ǻ�,��ʵfdisk������ô�ɵ�.��һ���ͼ�����.Ok,����ֱ�۵�ӡ����Լ������¿���.�ղ�����֪
// ������������US_FL_FIX_CAPACITY���flag���豸,�ͻ�ִ��fix_read_capacity(),�����������
// ��drivers/usb/storage/protocol.c��,��ν�����bug�����ע����˵�ú����.����������N,ƫƫҪ
// �㱨˵�Լ���N+1,��˵�ⲻ���ҳ�ô?��Ȼ��Ҳ�ܼ�,���Ǵ�����������. 
//      60 // 
//      61//Fix-up the return data from a READ CAPACITY command. My Feiya reader 
//      62//returns a value that is 1 too large. 
     63  // 
     64 static void fix_read_capacity(struct scsi_cmnd *srb)   181
     65 { 
     66         unsigned int index, offset; 
     67         __be32 c; 
     68         unsigned long capacity; 
     69 
     70         // verify that it's a READ CAPACITY command // 
     71         if (srb->cmnd[0] != READ_CAPACITY) 
     72                 return; 
     73 
     74         index = offset = 0; 
     75         if (usb_stor_access_xfer_buf((unsigned char *) &c, 4, srb, 
     76                         &index, &offset, FROM_XFER_BUF) != 4) 
     77                 return; 
     78 
     79         capacity = be32_to_cpu(c); 
     80         US_DEBUGP("US: Fixing capacity: from %ld to %ld\n", 
     81                capacity+1, capacity); 
     82         c = cpu_to_be32(capacity - 1); 
     83 
     84         index = offset = 0; 
     85         usb_stor_access_xfer_buf((unsigned char *) &c, 4, srb, 
     86                         &index, &offset, TO_XFER_BUF); 
     87 } 
// Ӧ��˵����ǰ�������������INQRUIY�����Ǹ�bug�Ĵ����ͬ־��Ӧ���ܹ������׿�����ǰ��δ�
// ��.���е��õ���ؼ��ĺ�������usb_stor_access_xfer_buf(),��usb_stor_access_xfer_buf()����
// İ����ͬ־�ǿ��Իع�ȥ������ʱ��������η�����.����75�е����þ��Ǵ�request_buffer��߰���
// ��copy �� c ���ȥ,��85 �е����þ��Ƿ�������c��ߵ�����copy��request_buffer���ȥ.������
// ֮��,����Ҫ��һ����Ȼ��79�к�82��,capacity����Ϊc,��c�ٱ���Ϊcapacity-1.������򵥵��ļ�
// �д����fix����ôһ��bug. 
// ��Ȼ,��Ȼ�Ҳ�ϲ��Linux,�����һ����б�ҪΪ�����һЩ����. 
// ���ǲ��ǿ�����Щ������һϵ�к�����: 
// be32_to_cpu/cpu_to_be32(),cpu_to_le16(),cpu_to_le32(),��ǰ����һֱû�н�,��������������
// һ��������.�����������µĴ����������Ѿ��������,�����ڿ�ʼ�Ĺ��»����Ͼ�����һЩС��С��С��
// С��ʽ��ϸ֦ĩ����.le����Little Endian,be����Big Endian,���������ֽ���.le�ͱ�ʾ��ַ��λ�洢
// ֵ�ĵ�λ,��ַ��λ�洢ֵ�ĸ�λ.be�ͱ�ʾ��ַ��λ�洢ֵ�ĸ�λ,��ַ��λ�洢ֵ�ĵ�λ.���Ǿ�������
// �����ʱ����cΪ��.����c ���������洢���ڴ��ַ0x0000��ʼ�ĵط�: 
// 0x0000     0x12 
//  0x0001     0x34 
//  0x0002     0xab 
//  0x0003     0xcd   182
// ������ǲ���le���ֽ���,��ô��������ֵ����0xcdab3412,��֮,�������õ���be ���ֽ���,��ô
// ��������ֵ����0x1234abcd.ͬ����,������0x1234abcdд��0x0000��ʼ���ڴ���,��ô�����
// ��: 
//              big-endian     little-endian 
// 0x0000     0x12              0xcd 
// 0x0001     0x23              0xab 
// 0x0002     0xab              0x34 
// 0x0003     0xcd              0x12 
// Ϊʲô�⼸�������������涼һ����cpu��?̸���ֽ���̸cpu�Ǿͺñ���ɷ����̸�𳬼�Ů��ȴ��
// ����ӱ�Ǻ�����ҲãȻ��֪.��ͬ��cpu���ò�ͬ���ֽ���.���������Լ�ϲ����.����,big endian��
// Motolora��PowerPCϵ��cpuΪ����,��little endian�����Ҽ�Intel��x86ϵ��cpuΪ����.������
// ��������������߶�����cpu������,��ô�������ʶ��ڲ�ͬ��cpu,�⼸������ִ�еĴ����ǲ�һ����.
// ����,����xx_to_cpu��˵�������Ľ���Ǹ�cpuʹ�õ�,��֮�����cpu_to_xx��˵���Ǵ�cpu����
// ����ת����Ŀ���ֽ���. 
// ��ôĿ���ֽ���Ӧ����ʲô����?����������usb�����.usb spec 2.0�ڰ���,��ֽ���ֵĹ涨����ôһ
// ��,usb������ʹ�õ���little-endian���ֽ���.����,���������ڴ���bcs/bcb��ʱ��һֱ�ڵ���
// lexx_to_cpu/cpu_to_lexx()�����ĺ���,����׼ȷ��˵,�����ĺ�.(usb spec 2.0, Chapter 8, 8.1 
// Byte/Bit Ordering: 
// Bits are sent out onto the bus least-significant bit (LSb) first, followed by the next LSb, 
// through to the most significant bit (MSb) last. In the following diagrams, packets are 
// displayed such that both individual bits and fields are represented (in a left to right reading 
// order) as they would move across the bus. Multiple byte fields in standard descriptors, 
// requests, and responses are interpreted as and moved over the bus in little-endian order, i.e., 
// LSB to MSB.) 
// �����ͬʱ,�ڵƻ���ɺ��,����Ҳ��ϡ�ǵ�,���Ƿ���ΪSCSI Primary Commands-4�Ĺ淶,���Ƿ�
// �ڽ���������SCSI��������֮������SPC-4��,������,3.5, Bit and byte ordering��һ��,�������
// ����: If a field consists of more than one byte and contains a single value, the byte containing 
// the MSB is stored at the lowest address and the byte containing the LSB is stored at the 
// highest address (i.e., big-endian byte ordering).����request_buffer�����������ǲ���be����
// ����,������������cҪͨ��be32_to_cpu()ת�����ܱ��cpuʹ�õĽ��.������,�������ٴ�copy
// ��request_buffer�е�ʱ��,Ҫ��ʹ��cpu_to_be32()��ת��ȥ. 
// �������㻹Ҫ��,ΪʲôҪ���������ֽ���?���鷳��?����ûʲô��˵��,�����ϵ�������������Ĳ��
// ȥ��,Ҳ�������ܸ�����,���ܰ����������,ֻҪ����è��ס�ľ��Ǻ�����. 
// �ж��ٰ����Ժ���?(һ) 
// �ϵ۸���ÿ����һ֧��д������Ǧ��,ȴδ����������Ƥ��.�������������ȴ�������,�����������ž�
// �ò�������,��һ��reset����һ��ok��. (��Ȼ��Ҫ��������è���㰡���˳����ɶ�Ĳ����Ǿ�������  183
// ��,ι,�����в���,���ǽ�������.)�������Ҳ��������,��ô��ү���Ƕξ���ĸ����֪�ġ��������
// ���ġ������硭�����Ķ԰׿��¾�û��������. 
// ������������,һ���ǳ��ǳ���Ҫ�ĸ�����Ǵ�����.�����������,������Ϊ���˶���������,д����
// ����дС˵,������Ϊ���ߵĹ�˼�����������޷�.���������������� usb-storage ��,���������������
// �������. 
// һ�ж��ô��Ǹ��ṹ�����struct scsi_host_template usb_stor_host_template��ʼ˵��.��ʵ��
// ���ṹ���������Ǻ� scsi ���Ĳ�����ؼ��Ľӿ�.����֪������ṹ���кܶ�����,����Ϊ
// usb_stor_host_template ������Ա����ֵ,������Ȼ�ܶ����Ƕ�û�н�.��ô������ʱ��ȥ����.����
// ��,���ǲ��������������ص�������Ա��������.��Щ�������������Լ������,�ṩ�� scsi core �Ǳ�
// ȥ����,�ͺ���queuecommand()һ��. 
//    430         // error and abort handlers // 
//     431         .eh_abort_handler =             command_abort, 
//     432         .eh_device_reset_handler =      device_reset, 
//     433         .eh_bus_reset_handler =         bus_reset, 
// ��,������һ��һ������.�ȿ������� reset ��صĺ���,���ѡ�Ҫ����Ů������Ϊʲô������ reset ����,��
// ��,����ĵ����е�Сë����֮��,�����������ѡ��,һ����ע���Ϳ�����,һ��������ſ�
// ��.device_reset �������Ӧ�ľ���ע��,bus_reset ��Ӧ�ľ�������.��Ȼ����˵�����Ͻ�,ֻ��˵,һ��
// ��˵��΢һ��,device_reset �͹���,�������һ��,�ۿ����豸���������,��ô���ܾ�Ҫ bus_reset()
// ��. 
// Ok,�����ô�����������. 
// ���ȿ�������device_reset().����drivers/usb/storage/scsiglue.c, 
// 239 // This invokes the transport reset mechanism to reset the state of the 
    240//device // 
    241 // This is always called with scsi_lock(srb->host) held // 
    242 static int device_reset(struct scsi_cmnd *srb) 
    243 { 
    244         struct us_data *us = (struct us_data *)srb->device->host->hostdata[0]; 
    245         int result; 
    246 
    247         US_DEBUGP("%s called\n", __FUNCTION__); 
    248 
    249         scsi_unlock(srb->device->host); 
    250 
    251         // lock the device pointers and do the reset // 
    252         down(&(us->dev_semaphore)); 
    253         if (test_bit(US_FLIDX_DISCONNECTING, &us->flags)) { 
    254                 result = FAILED; 
    255                 US_DEBUGP("No reset during disconnect\n");   184
    256         } else 
    257                 result = us->transport_reset(us); 
    258         up(&(us->dev_semaphore)); 
    259 
    260         // lock the host for the return // 
    261         scsi_lock(srb->device->host); 
    262         return result; 
    263 } 
// 244��,ûɶ��˵��,���ǻ����ǿ�����Ӵ,���������Ǹ�����,ɽҲ��������ɽӴ,��Ҳ�����ǵ���,����
// ������,���Ǹ�Ӵ,���ǵ���������,���͵ư�,��֨֨����,��Ļ���ô������,�Ŷ...�Ŷ...ֻ�������ǽ
// Ӱ��զ��ô��,ֻ�������ǽӰ��զ��ô��,�����ǿ��ҵĹ��еĽеĽеĽе�զ����ô��...80�󲻿���
// û������ë�����ĸ�,������û����������ë�������ĳ�����.20�����ȥ,���ǲ������ǿ�����,����Ҳ
// �����Ǹ�����,��Ҳ����������Ӵ,��Ҳ����������.Ȼ��,us�����Ǹ�us.���������ǽ,Ӱ�ӻ���ô��. 
// 253��,���ȿ� US_FLIDX_DISCONNECTING flag����û��.��Ȼ,disconnecting�˾�û�б�Ҫ��
// reset��.���� disconnect,���,����reset���־͸ý�����. 
//   ����,�����us->transport_reset,����ǰ���Ѿ�˵����,�ܾúܾ���ǰ,��������Ϊ
// us->transport_reset��ֵΪusb_stor_Bulk_reset,��������Ҳ���Ǻ���usb_stor_Bulk_reset()��
// ������,usb_stor_Bulk_reset������ drivers/usb/storage/transport.c��, 
// 1184 // This issues a Bulk-only Reset to the device in question, including 
   1185//clearing the subsequent endpoint halts that may occur. 
   1186  // 
   1187 int usb_stor_Bulk_reset(struct us_data *us) 
   1188 { 
   1189         US_DEBUGP("%s called\n", __FUNCTION__); 
   1190 
   1191         return usb_stor_reset_common(us, US_BULK_RESET_REQUEST, 
   1192                                  USB_TYPE_CLASS | USB_RECIP_INTERFACE, 
   1193                                  0, us->ifnum, NULL, 0); 
   1194 } 
// �����������һ��,�ܼ�,Ҳ���ɱ��,���ǵ���usb_stor_reset_common().����,���ǽ���������
// �������driver/usb/storage/transport.c�е�usb_stor_reset_common()����. 
   1101 // This is the common part of the device reset code. 
   1102//
   1103//It's handy that every transport mechanism uses the control endpoint for 
   1104//resets. 
   1105//
   1106//Basically, we send a reset with a 20-second timeout, so we don't get 
   1107//jammed attempting to do the reset. 
   1108  //   185
   1109 static int usb_stor_reset_common(struct us_data *us, 
   1110                 u8 request, u8 requesttype, 
   1111                 u16 value, u16 index, void *data, u16 size) 
   1112 { 
   1113         int result; 
   1114         int result2; 
   1115         int rc = FAILED; 
   1116 
   1117         // Let the SCSI layer know we are doing a reset, set the 
   1118        //RESETTING bit, and clear the ABORTING bit so that the reset 
   1119        //may proceed. 
   1120          // 
   1121         scsi_lock(us->host); 
   1122         usb_stor_report_device_reset(us); 
   1123         set_bit(US_FLIDX_RESETTING, &us->flags); 
   1124         clear_bit(US_FLIDX_ABORTING, &us->flags); 
   1125         scsi_unlock(us->host); 
   1126 
   1127         // A 20-second timeout may seem rather long, but a LaCie 
   1128        //StudioDrive USB2 device takes 16+ seconds to get going 
   1129        //following a powerup or USB attach event. 
   1130          // 
   1131         result = usb_stor_control_msg(us, us->send_ctrl_pipe, 
   1132                         request, requesttype, value, index, data, size, 
   1133                         20*HZ); 
   1134         if (result < 0) { 
   1135                 US_DEBUGP("Soft reset failed: %d\n", result); 
   1136                 goto Done; 
   1137         } 
   1138 
   1139         // Give the device some time to recover from the reset, 
   1140        //but don't delay disconnect processing. // 
   1141         wait_event_interruptible_timeout(us->dev_reset_wait, 
   1142                         test_bit(US_FLIDX_DISCONNECTING, &us->flags), 
   1143                         HZ*6); 
   1144         if (test_bit(US_FLIDX_DISCONNECTING, &us->flags)) { 
   1145                 US_DEBUGP("Reset interrupted by disconnect\n"); 
   1146                 goto Done; 
   1147         } 
   1148 
   1149         US_DEBUGP("Soft reset: clearing bulk-in endpoint halt\n"); 
   1150         result = usb_stor_clear_halt(us, us->recv_bulk_pipe); 
   1151 
   1152         US_DEBUGP("Soft reset: clearing bulk-out endpoint halt\n");   186
   1153         result2 = usb_stor_clear_halt(us, us->send_bulk_pipe); 
   1154 
   1155         // return a result code based on the result of the control message // 
   1156         if (result < 0 || result2 < 0) { 
   1157                 US_DEBUGP("Soft reset failed\n"); 
   1158                 goto Done; 
   1159         } 
   1160         US_DEBUGP("Soft reset done\n"); 
   1161         rc = SUCCESS; 
   1162 
   1163   Done: 
   1164         clear_bit(US_FLIDX_RESETTING, &us->flags); 
   1165         return rc; 
   1166 } 
// ǰ�漸���Ǹ�ֵ,Ȼ��usb_stor_report_device_reset()������. usb_stor_report_device_reset()
// ������drivers/usb/storage/scsiglue.c��, 
    308 // Report a driver-initiated device reset to the SCSI layer. 
    309//Calling this for a SCSI-initiated reset is unnecessary but harmless. 
    310//The caller must own the SCSI host lock. // 
    311 void usb_stor_report_device_reset(struct us_data *us) 
    312 { 
    313         int i; 
    314 
    315         scsi_report_device_reset(us->host, 0, 0); 
    316         if (us->flags & US_FL_SCM_MULT_TARG) { 
    317                 for (i = 1; i < us->host->max_id; ++i) 
    318                         scsi_report_device_reset(us->host, 0, i); 
    319         } 
    320 } 
//   315��,scsi_report_device_reset(),drivers/scsi/scsi_error.c�ж����.�������scsi core�Ǳ�
// Ҫ�����ǵ��õ�,�������ɼ�.Ȼ���������������ϸ��,ֻ��˵,����̫��,����ֻ�ں�������Ҫ�ں��Ķ�
// ��,������������Ͼ�˼�.����ֻ����960��ƽ��ǧ�׵�һ��������,������Ϊ�Լ��������ƴ,Ϊ�Լ�Ѱ��
// һ����ҫ.usb������care��,��scsi �ĺ���,�����ǲ���ȥ���,ֻ��дscsi ���ĵ�ͬ־�ǻ��ں�.����
// ��������ôһ�仰:Ů���ں������°������Ҹ�,�к���ע�����°�����Ҹ�.ͬ��,Linux������,ÿһ����
// �ں��Ķ����ǲ�һ���ġ����Թ�����,�����ǲ���Ҫ��ϵ���������ô�����,����������Ҫ֪��ʲôʱ��
// �������,����������?��Ҫ����ʲô����?����,Ҫ������������,��һ��,Scsi_Hostָ��,һ��u�̾���һ
// ��Scsi_Host,Ȼ��ڶ�������,channel,Ȼ�����������target,����scsi �豸λ�õ��ĸ���������ȱһ
// ��,ȱ�ľ���LUN,��Ϊһ��device��reset��ô�Ͳ�����������м���LUN��,�м�����һ�����reset.
// ��ô�������������Ŀ����ʲô?����scsi����,���۲쵽ĳ���豸reset��.����scsi���Ļ���δ�����,
// ���۹ܲ���,Ҳ����ȥ��.�ܶ���֮,�Զ���֮,ͳ����֮,�Զ�ͳ֮,���ǵ�ְ�����ڷ�����һ���豸reset֮
// ���������ϼ��㱨.   187
//  US_FL_SCM_MULT_TARG���flag,����Ҳ����ü���,���������֧�ֶ��target,�����豸�����
// ����,�������ǵĴ���㶸��豸���.���������豸,scsi_report_device_reset()�ͻᱻ����ü���,���
// ÿһ��targetҪreportһ��. 
//   ������scsi_report_device_reset(),��Ȼ�ֻص���usb_stor_reset_common(),1123��,1124��
// ����һ�� flag,���һ�� flag,���õ��� US_FLIDX_RESETTING,������� US_FLIDX_ABORTING,��
// ��������flag,һ�����ǽ��command_abort()����. 
// 1131 ��,usb_stor_control_msg()������,��һ�ο������������ش���Ѿ�����İ���˰�.�����Ƿ�
// ��һ����������,��ʵ�����Ѿ��ܾ�û�н����ƴ�����.�����ϲ������������͵�ʲô����.����,us ����
// �Ǹ�us,���ٶ�˵.Ȼ��,pipe��us->send_ctrl_pipe,���Ƿ��Ϳ��ƹܵ�.Ȼ��request,requesttype��
// Щ�����ڵ��� usb_stor_reset_common()��ʱ�򴫵ݽ����Ĳ���,�� usb_stor_Bulk_reset()�п���
// ���� ,request �� US_BULK_RESET_REQUEST,requesttype �� USB_TYPE_CLASS | 
// USB_RECIP_INTERFACE. 
//   US_BULK_RESET_REQUEST��drivers/usb/storage/transport.h�б�����Ϊ0xff,���Ǻ�usb 
// mass storage class-Bulk Only transportЭ�����Ӧ��.��Э��ר��ΪBulk-Only Mass Storage��
// ��������һ������,��Reset.Э����˵,this request is used to reset the mass storage device and 
// its associated interface.Э���й涨��,��usb hostҪ��������reset usb�豸��ʱ��,��Ҫͨ�����Ϳ�
// �ƹܵ�����һ������,��ǰ�������ctrlrequest,���ʽ����ͼ��ʾ: 
//  
// ����bReques ��һλ������Ϊ255(FFh),wValue����Ϊ0,wIndex ����Ϊinterface 
// number,wLength����Ϊ 0.(����������Ҳȷʵ��������,wIndex����ֵΪus->ifnum,���ϴ����ǵ�
// ��usb_stor_control_msg ��ʱ�򴫵ݵ�һ��,��Ȼinterface�����Ǹ�interface.��ɽ���,�ļ����,
// �������е�interfaceʼ�ղ���.) 
//   ����requesttype,��������usb_stor_Bulk_max_lun()�н��Ĳ��,Ψһ�������ǿ������ݴ��䷽
// ��,��ʱ��device to host,������host to device,���Ե�ʱ����һ��USB_DIR_IN,������û��д
// USB_DIR_OUT,ԭ��ܼ�,USB_DIR_OUT������Ϊ 0,���Ի򲻻�������ν. 
//   ��,����,����������豸����reset���������.����ֵС��0���ǳ�����. 
//   û������ô��1141��,wait_event_interruptible_timeout()������.us->dev_reset_wait����ǰ
// �潲��,����һ���ȴ�����ͷ,��storage_probe()�б���ʼ��,���Ժ��ڽ�storage_disconnect()ʱ��
// ����,����ôһ��,wake_up(&us->dev_reset_wait),�����ѵ������������˯�ߵĽ���,����1141��,
// �����˯��,����˯��֮ǰ���ж�US_FLIDX_DISCONNECTING���flag��û������,Ҫ�����˾�û��
// ��Ҫ˯����,ֱ���˳���.1144��,���ж�һ��,������������flag��ôֱ��goto Done,����rc,rc ����
// ��ֵFAILED.����֮ǰ�����US_FLIDX_RESETTING flag. ����
// wait_event_interruptible_timeout()�������,���ǵ����ڷ���usb_stor_scan_thread()��ʱ����
// ����ϸ�Ľ�����,�������ﲻ��Ҫ���˷����ҵ��ഺȥ�ི��.   188
//   ��Ȼ,��� US_FLIDX_DISCONNECTING ��û������,��ô 6s ��ʱ�䵽��,˯����Ȼ��,1150 ��
// 1153��,usb_stor_clear_halt(),����һ�������еĺ���,�����˵�ǰ�����ڽ�GET MAX LUN��ʱ���
// ר�Ž������������,������ʱ�����Ǿ��Ѿ�˵��,��һ�����������Ҫ�����������,˵���������������
// ���,�����豸reset֮��,��Ҫ���halt���feature,Ȼ��˵������������.�������ǵ�����bulk�˵�,
// ֻҪ��һ���� halt feature ʧ����,��ô����������� reset �ĺ��� usb_stor_reset_common ����ʧ
// ����,������˻᷵��FAILED,�����ڷ���֮ǰ�Ȱ�US_FLIDX_RESETTING���flag��ȥ��. 
// Ȼ��������,usb_stor_reset_commond �÷�����,Ȼ�����Ǿ��ȵķ���, usb_stor_Bulk_reset()
// Ҳ�÷�����,��Ȼ�������־��ȵķ���,device_reset()Ҳ�÷�����.������,����������device_reset()��
// ôһ������.֮���Լ�����Ϊ����ʹ������ͺܼ�,��ʵ���Ǹ��豸����һ�� reset �� request,Ȼ��
// clear��halt feature,��֤�豸�Ķ˵�û��ֹͣ.����Щ,��͹���. 
// �ж��ٰ����Ժ���?(��) 
// device_reset()����֮����������bus_reset().ͬ������drivers/usb/storage/scsiglue.c��. 
265 // This resets the device's USB port. // 
    266 // It refuses to work if there's more than one interface in 
    267//the device, so that other users are not affected. // 
    268 // This is always called with scsi_lock(srb->host) held // 
    269 static int bus_reset(struct scsi_cmnd *srb) 
    270 { 
    271         struct us_data *us = (struct us_data *)srb->device->host->hostdata[0]; 
    272         int result, rc; 
    273 
    274         US_DEBUGP("%s called\n", __FUNCTION__); 
    275 
    276         scsi_unlock(srb->device->host); 
    277 
    278         // The USB subsystem doesn't handle synchronisation between 
    279        //a device's several drivers. Therefore we reset only devices 
    280        //with just one interface, which we of course own. // 
    281 
    282         down(&(us->dev_semaphore)); 
    283         if (test_bit(US_FLIDX_DISCONNECTING, &us->flags)) { 
    284                 result = -EIO; 
    285                 US_DEBUGP("No reset during disconnect\n"); 
    286         } else if (us->pusb_dev->actconfig->desc.bNumInterfaces != 1) { 
    287                 result = -EBUSY; 
    288                 US_DEBUGP("Refusing to reset a multi-interface device\n"); 
    289         } else { 
    290                 rc = usb_lock_device_for_reset(us->pusb_dev, us->pusb_intf); 
    291                 if (rc < 0) { 
    292                         US_DEBUGP("unable to lock device for reset: %d\n", rc);   189
    293                         result = rc; 
    294                 } else { 
    295                         result = usb_reset_device(us->pusb_dev); 
    296                         if (rc) 
    297                                 usb_unlock_device(us->pusb_dev); 
    298                         US_DEBUGP("usb_reset_device returns %d\n", result); 
    299                 } 
    300         } 
    301         up(&(us->dev_semaphore)); 
    302 
    303         // lock the host for the return // 
    304         scsi_lock(srb->device->host); 
    305         return result < 0 ? FAILED : SUCCESS; 
    306 } 
// ������device_reset������bus_resetӦ�þͲ�����.�����������д��Ҳ�ر����,ע�ͺ���ϸ����
// ����һЩ������Ϣ,������,�йش���Щ����С����ëƬ�ĸ�Ůͬ־��Ӧ�ö��ܿ������������.�����ټ�
// ����һ��,��device_reset��ͬ�ĵط�����,device_resetʵ����ֻ���豸����ĸ�λ,��bus_reset��
// ����͸��ӹ㷺��,���漰����usb core��һ��������ʼ������豸,ǧ��Ҫ������,bus reset����˵
// usb bus��reset,����scsi bus,��scsi ����.������scsi ����?����ģ���,�ٵ�.�ѵ�������������ģ��
// ��һ��scsi host,һ��scsi deviceô,ʵ����Ҳ����ģ����һ��scsi ����.�����������reset����ζ��
// ����driver�������³�ʼ��,����usb core �Ǳ߿�ʼ,ȷ�е�˵��usb hub�Ǳ�,�ȸ�������usb������
// �����·���һ����ַ,���½�����֮ǰ������,����ѡ��altsetting,Ҳ����˵������������豸,�൱����
// �¾�����һ��usb������ö��.��֮��,���ǵ�storage_probe()�����±�����,����ģ���scsi ���߽���
// ͷ����,����˵bus_reset��һ���ܴ��ģ���˶�,������device reset��������С��С��ʽ��. 
//   283��,��������·,����ǲ���disconnecting��,Ҫ�ǵĻ��ͱ�reset��,ʡʡ�°�,��Ϲ������. 
//   286��,���ǵ�����˵��һ��interface��Ӧһ��driver��,һ��device�����ж�� interface,Ҳ���
// ���ܶ�Ӧ���driver,��ô���������һ��device reset��ֻ���������һ��deviceֻ��һ��interface
// �����,��ΪҪ��Ȼ����Ӱ�������,�ͺñ�,�������Ǽ�����һ��ɭ�����,ǰ��������ŵ�ķ���, ��
// ��˵���Ǽҵ��ܱߵ��κ��Ǹ�ʷ����ţ�����춤�ӻ����,�����������Լ����õķ��Ӹ�����,�ǿ���
// û�˹�,��������ס����¥��,�������Ҹ��ھӼҵ�����һǽ֮��,����ԡ�Ҹ��ھӼҵ�ԡ��һǽ֮��,����
// Ҫ�ǸҰ����Ƕ�ǽ����,��ӹ����,�ھӷǸ���������. 
//   Ȼ��289�е�300��,�ܹ���������usb core�ǱߵĹؼ���
// ��,usb_lock_device_for_reset/usb_reset_device/usb_unlock_device.usb core��Ϊ��׼������,
// ��Ҫ����������reset�豸,���ȵ��õ���usb_lock_device_for_reset,����usb���Ĳ�ĺ���,����
// drivers/usb/core/usb.c��,�ɹ�ִ�оͷ���1����0,ʧ���˾ͷ���һ�����Ĵ������.295�е�
// usb_reset_device(),ͬ������usb���Ĳ�,drivers/usb/core/hub.c��,��usb���Ĳ��ṩ�����ǵ���
// �����³�ʼ��һ���豸�ĺ���.�ɹ�����0,����ͷ��ظ��Ĵ������.�����˾͵õ���
// usb_unlock_device���ͷ���. 
//   ���305��,resultΪ 0���Ƿ��سɹ�,���򷵻�FAILED.   190
// �ܿ��� 296 ��,297 ����?����˵��,usb_lock_device_for_reset ���Է��ظ���,���Է��� 1,���Է���
// 0.���ظ������������ 291 �� 293 ������������,������ usb_lock_device_for_reset ��˵,������ 1
// ��ʾ������ִ���� usb_reset_device ֮��Ҫ���� usb_unlock_device ���ͷ���,������ 0 ��ʾ������
// ִ���� usb_reset_device ֮����Ҫ���� usb_unlock_device ���ͷ���.��������Щ�ܺ���,��ô��
// ���Կ�һ�� usb core �Ĵ���.�ر��ǿ�һ�¹���������Ĵ���,USB_INTERFACE_BINDING ��
// USB_INTERFACE_BOUND. 
// ����,���Ǿ����������bus_reset()�������������. 
// ����������� command_abort().����Ȼ����һ����������, ����ְ�����ȷ, ��ͼȥ��ֹ��ǰ��
// ����.ͬ������drivers/usb/storage/scsiglue.c: 
// 202 // Command timeout and abort // 
    203 // This is always called with scsi_lock(srb->host) held // 
    204 static int command_abort(struct scsi_cmnd *srb ) 
    205 { 
    206         struct Scsi_Host *host = srb->device->host; 
    207         struct us_data *us = (struct us_data *) host->hostdata[0]; 
    208 
    209         US_DEBUGP("%s called\n", __FUNCTION__); 
    210 
    211         // Is this command still active? // 
    212         if (us->srb != srb) { 
    213                 US_DEBUGP ("-- nothing to abort\n"); 
    214                 return FAILED; 
    215         } 
    216 
    217         // Set the TIMED_OUT bit.  Also set the ABORTING bit, but only if 
    218        //a device reset isn't already in progress (to avoid interfering 
    219        //with the reset).  To prevent races with auto-reset, we must 
    220        //stop any ongoing USB transfers while still holding the host 
    221        //lock. // 
    222         set_bit(US_FLIDX_TIMED_OUT, &us->flags); 
    223         if (!test_bit(US_FLIDX_RESETTING, &us->flags)) { 
    224                 set_bit(US_FLIDX_ABORTING, &us->flags); 
    225                 usb_stor_stop_transport(us); 
    226         } 
    227         scsi_unlock(host); 
    228 
    229         // Wait for the aborted command to finish // 
    230         wait_for_completion(&us->notify); 
    231 
    232         // Reacquire the lock and allow USB transfers to resume // 
    233         scsi_lock(host); 
    234         clear_bit(US_FLIDX_ABORTING, &us->flags);   191
    235         clear_bit(US_FLIDX_TIMED_OUT, &us->flags); 
    236         return SUCCESS; 
    237 } 
// ��Ȼ����ֹĳ������,��ô���ݽ����Ĳ�����Ȼ��struct scsi_cmnd��ָ����.ǰ���еĸ�ֵ�����˵. 
//   212��,us->srb��ʾ���ǵ�ǰ��srb,��srb����������������Ĳ���,command_abort()ϣ��������
// ֹ��ǰ������,�����紫�����Ĳ��������Ͳ��ǵ�ǰ������,��ô�϶�������.ɶҲ��˵��,ֱ�ӷ���
// FAILED. 
//   Ȼ��,��abort��ʱ��,���� US_FLIDX_TIMED_OUT�� flag,Ȼ������豸û��reset,��ô��������
// ����һ��flag,US_FLIDX_ABORTING,Ȼ�����usb_stor_stop_transport(),���������Ŀ�ĺܼ�,
// ��ֹ�κν����еĴ���,�������������drivers/usb/storage/transport.c��: 
    730 // Stop the current URB transfer // 
    731 void usb_stor_stop_transport(struct us_data *us) 
    732 { 
    733         US_DEBUGP("%s called\n", __FUNCTION__); 
    734 
    735         // If the state machine is blocked waiting for an URB, 
    736        //let's wake it up.  The test_and_clear_bit() call 
    737        //guarantees that if a URB has just been submitted, 
    738        //it won't be cancelled more than once. // 
    739         if (test_and_clear_bit(US_FLIDX_URB_ACTIVE, &us->flags)) { 
    740                 US_DEBUGP("-- cancelling URB\n"); 
    741                 usb_unlink_urb(us->current_urb); 
    742         } 
    743 
    744         // If we are waiting for a scatter-gather operation, cancel it. // 
    745         if (test_and_clear_bit(US_FLIDX_SG_ACTIVE, &us->flags)) { 
    746                 US_DEBUGP("-- cancelling sg request\n"); 
    747                 usb_sg_cancel(&us->current_sg); 
    748         } 
    749 } 
//   ����������flag,US_FLIDX_URB_ACTIVE��US_FLIDX_SG_ACTIVE,ǰһ��flag���Ǵ�ǰ�ڽ�
// storage_probe()��ʱ��������,��ʱ����Ϊ�˻��max lun,�����ύ��urb,����
// usb_stor_msg_common()������,��urb���ɹ��ύ��֮��,����set_bit()��Ϊus->flags��������
// һλ,��������Ϳ������ж�,���ȷʵ������,��ô��ʱ�Ϳ��Ե���usb_unlink_urb����urb������ȡ��
// ��,��Ϊû�б�Ҫ��������������. 
//   ��US_FLIDX_SG_ACTIVE���flag����Ҳ��İ��,��bulk��������õ�.�������flag����bulk��
// ���еĺ���usb_stor_bulk_transfer_sglist(),�������set_bit�������������flag. ��������Ҳ�ж�,
// ���ȷʵ������,��ô��ʱ�Ϳ��Ե���usb_sg_cancel ����sgȡ��.   192
//   ���ó�,usb_stor_stop_transport()�ľ��ĺܼᶨ,Ŀ��ܼ�,����Ҫ����Ĵ�����в���ȥ,��urb
// ��ȡ��urb,�� sg��ȡ��sg,�����˵�ɱ�˷�ɱ�������������. 
//   ��ʱ,��230 ��,���ǿ����˵ȴ�����,wait_for_completion(&us->notify),command_abort()����
// ����ȴ�.˭����������?usb_stor_control_thread()�е�complete(&(us->notify))������. 
//   һ�����,������˯����,usb�豸�Ͽ���,����usb_stor_control_threadҪ�˳���,�����������
// complete_and_exit()������command_abort()�����˳�usb_stor_control_thread(),����һ����
// ����ô����Ӵ˾��徲��. 
//   �ڶ������,һ��scsi ���û�п�ʼִ��,����˵����Ҫ��ʼִ�е�ʱ��,���ǵ�����
// command_abort(),��ô��Ӧ��usb_stor_control_thread()�е� 322 ��325�Ǽ��е�if���,����
// US_FLIDX_TIMED_OUT flag��������,����,����Ҳ��ִ����,ֱ��goto SkipForAbort,Ȼ�����
// complete(&(us->notify))���������������˯�ߵĽ���.ͬʱ,����usb_stor_control_thread()���
// ��˵,��us->srb����Ϊ NULL��һ�� ok��,���Կ�ʼ��һ��ѭ����. 
//   ���������, һ��scsi ����ִ������֮��,���ǲ�ִ�е�command_abort,��ô���������,��������
// ������US_FLIDX_TIMED_OUT��־,��Ӧ��usb_stor_control_thread()�Ǳߵ� 396,397�е�if��
// ��,Ҳûʲô�ر��,ͬ����,ִ��complete(&(us->notify))���������������˯�ߵĽ��̰�.���ҽ�
// us->srb��Ϊ NULL. 
//   ���,234,235��,���������US_FLIDX_ABORTING ��US_FLIDX_TIMED_OUT������flag,��
// �����Ĵ��仹�����������-�վ�.��command_abort()��������Ȼ����SUCCESS.��ֹ�˱���,����
// �ɹ���.����������SUCCESS. 
//   �������Ǿ��㽲�������������������ĺ�����.��ô����������flag�Ĺ�����.������������.ʵ��
// ��������һ�������ں�Ŀ¼,ֻ��command_abort()������set��������flag,�����
// command_abort()ִ�гɹ���,���ڷ���֮ǰ,������flag�������.����Ҫ����
// US_FLIDX_TIMED_OUT���flag�ĵط�,����ֻ��usb_stor_control_thread()�к�
// usb_stor_invoke_transport()��.����ǰ���������Ǹղ�����������,���˻���command_abort()��
// ��,��������us->srbΪ NULL,���ܵ���˵,�����϶�scsi �Ǳ�û��ʲôӰ��.����
// usb_stor_invoke_transport()��,�������������US_FLIDX_TIMED_OUT������,��ô���������
// ��ͬ,��Ϊ��ʱ������������scsi ��򽻵�,��������ΪҪִ��һ��scsi ����Ž��뵽
// usb_stor_invoke_transport()��,������������������������abort,��ô�������ٵø�scsiһ������,
// ����������usb_stor_invoke_transport()�е�724����һС�ο���������,���ǻظ���scsi �����
// srb->result,���ǰ��������DID_ABORT<<16.ͬʱ,����Bulk-only���豸,���ǻ���Ҫ�����ǵ���
// ������reset.����bulk-only�Ĵ���Э����߹涨��,��,��һ��abort ֮��,����Ҫ����һ��reset,Ҫ��
// �豸�´�û������.(�μ�Bulk-only transport 5.3.3.1 Phase Error/5.3.4 Reset Recovery) 
//   ��������һ��flag,US_FLIDX_ABORTING.ʵ����û����ר��ȥ�������flag��û������,��������
// �Ե�����һ��flag,ABORTING_OR_DISCONNECTING,�������flag�Ķ����������������г�����,
// ʵ������˼������,������������Aborting��flag,���߾���������Disconnecting��flag.�ܶ��������
// ��ʵ����Ҫ�жϵľ���������֮���κ�һ���Ƿ�������,��Ϊ����Ȼ,�ܶ������,����������е��κ�һ
// ����������,��ô���ǵ�ĳЩ�����û�б�Ҫ������,��Ϊ��������֪������֮��û��δ��,���кα��˷�˫
// ���ĸ�����?(��Ȼ,һҹ�鲻���������۵ķ���֮��.)����ABORTING_OR_DISCONNECTING,һ����  193
// ������������Ҫ�ж���,һ���� usb_stor_msg_common(),һ���� usb_stor_bulk_transfer_sglist().
// ��ʵ,��ϸ�ع�һ������������,��Ͳ��ѷ���,��usb_stor_msg_common()��,��ʵ���Ǿ������ύһ
// ��urb֮ǰ�ȼ�����flag��û������,�ύ��֮���ٴμ��һ��,ʵ���Ͼ��൱���Ǹ������λ���,��Ϊ��
// ����֮����൱�ڱ����֮��,����˫�����ܻ�û�з���ʲôʵ���ԵĹ���,����һ���������ʶ������һ
// ��û�н��������,�㻹����ѡ�����.���ǹ�����ڶ����ж�,��ô����ͽ�����������췹��.����
// usb_stor_bulk_transfer_sglist()��,��ʵ������һ����,���ǰ�urb�ĸ����sg,���˶���. 
//   Ok,���������ǿ����������һ����������flag��.�Ǿ���US_FLIDX_DISCONNECTING.����������
// ���������������µ����һ������������, storage_disconnect().���������Ҳ�����������������µ�
// ����,�Ͼ������޲�ɢ����ϯ,���ҿ�ʼд������µ�ʱ��,�Ҿ�֪��һ�ж���ע��,ע���˿�ʼ,ע���˽�
// ��. 
// �������������� 
//   �����Թ������,���ǿ�,���������! 
//   �������Ѻδ�? 
//   ������,�������. 
//   ��ȥ����,Ӧ�������þ�����. 
//   ������,ǧ�ַ���,�������˵? 
//   
//   ��������Լ�ɲ���,��̳�����������������˸γ���ϵ�<<������>>,�������������һ����Ҫ�ĺ�
// ��,storage_disconnect. 
//   usb�豸���Ȳ������ע��������Ӧ�����豸�����ʱ����һЩ����,���豸�γ���ʱ����һЩ����.��
// ����usb�豸��������ϵ������,��Ҫ����ʱ��,Ҫ������ж����,�罺����,�����ˮ.����,�а�����ʹ,
// ��һ��usb�豸�ض�Ҫ�뿪����.����������˵,����û��usb�豸�����᲻ͬ.����,��ʵ��,usb�ļ��弴
// ������Ҳ������֪��,usb�豸�����������ȥ,���ǻ��������.ǰ������ʱ�������storage_probe
// ���ñ˴˽��ܶԷ�,���ھ͸õ���storage_disconnect����������.����Ҳ����Ҫ�ֲƲ�,��usb�豸�뿪
// ����Ҳ��Ҫ����һЩ����. 
//   ���probe,disconnect�����ͼ򵥶���,������Ҫ����30����,����ֻҪ3����,������ǧ�õ��ǲ�<<
// ����>>֮���֪������������һ���鷳��,�ѹֱ����Ľֱߵ��߸���ǽ���ϵ���д����ʹ�������ɸ㶨��
// ����. storage_disconnect()���������� drivers/usb/storage/usb.c ��,�����������, 
   1027 // Handle a disconnect event from the USB core // 
   1028 static void storage_disconnect(struct usb_interface *intf) 
   1029 { 
   1030         struct us_data *us = usb_get_intfdata(intf); 
   1031 
   1032         US_DEBUGP("storage_disconnect() called\n"); 
   1033 
   1034         // Prevent new USB transfers, stop the current command, and 
   1035        //interrupt a device-reset delay //   194
   1036         set_bit(US_FLIDX_DISCONNECTING, &us->flags); 
   1037         usb_stor_stop_transport(us); 
   1038         wake_up(&us->dev_reset_wait); 
   1039 
   1040         // Interrupt the SCSI-device-scanning thread's time delay, and 
   1041        //wait for the thread to finish // 
   1042         wake_up(&us->scsi_scan_wait); 
   1043         wait_for_completion(&us->scsi_scan_done); 
   1044 
   1045         // Wait for the current command to finish, then remove the host // 
   1046         down(&us->dev_semaphore); 
   1047         up(&us->dev_semaphore); 
   1048         scsi_remove_host(us->host); 
   1049 
   1050         // Wait for everything to become idle and release all our resources // 
   1051         usb_stor_release_resources(us); 
   1052         dissociate_dev(us); 
   1053 } 
//   ���ֱ�������㻹��֪��1030���ڸ���,��������һ����������ǲ�����ˣ��?��Ȼ
// usb_get_intfdata()���������ȷ�ǵ�һ��¶��,��������ĺ�����Ȼ��˾����֮��·�˽�
// ֪.usb_get_infdata()������û�н���,�������ǽ��� usb_set_intfdata().�뵱��,associate_dev()��,
// ���ǵ���usb_set_intfdata(intf,us),��ʱ���Ƿ�����,�������Ľ������ʹ��
// %intf->dev->driver_data=us,���������ǵ���usb_get_intfdata(intf)�����þ��ǰ�us����ȡ����,
// ���������������ʱָ��us. 
//   1036��,ȫ����Ψһһ������US_FLIDX_DISCONNECTING���flag�ĵط���������. 
//   1037��, usb_stor_stop_transport(us),����������ǿ��ǸողŽ���,���˵���������,����
// command_abort()����õ�.Ŀ�ľ���ͣ����ǰ��urb�� sg,����еĻ�. 
//   1038��, wake_up(&us->dev_reset_wait),����Ҳ�Ѿ�������,�����ڽ�device_reset()������,
// ��ʱ��usb_stor_reset_common()��,��ʹ��wait_event_interruptible_timeout()������˯��,˯��
// ��Ŀ���Ǹ�6 ���������豸��reset״̬�ָ�����,������������ڼ�����Ҫ�Ͽ��豸��,��ô��Ȼ��û��
// ��Ҫ�����Ǳ߼���˯����,�豸��Ҫ�Ͽ���,����ʲô�ָ���������?���Զ����������,���ǻع�ͷ����
// usb_stor_reset_common(),�ᷢ��֮��ú��������˯��������,Ȼ�������Ϊreset�����õ�
// flag,US_FLIDX_RESETTING,Ȼ��ͷ�����,����ֵ��FAILED. 
//   1042��, wake_up(&us->scsi_scan_wait),�������������������ͬ,��ͬ������λ��ѵ���
// usb_stor_scan_thread,����������Ҳ����Ϊdelay_use�����ö�����
// wait_event_interrruptible_timeoutȥ�ȴ�ȥ˯��,�������������һ����.�����ͬʱ,1043��, 
// wait_for_completion(&us->scsi_scan_done),ǡǡ���ǵȴ��Է��Ľ���,����ע�⵽,��
// usb_stor_scan_thread()�����һ�仰, complete_and_exit(&us->scsi_scan_done, 0),��������
// ���������storage_disconnect()ͬʱ�������Լ�.Ӧ��˵������ʵ����һ��ͬ������.����˵��Ϊ����  195
// ֮������Ҫ���ľ��������Ż���,��һЩ��Ҫ����Դ���ͷŵ�,�����������ȱ��뱣֤���ǵĽ��̶��˳���,
// ��Դ�����ٱ���ʹ��,�������ǲſ��Է��ĵ�ȥ�����ǵ�������. 
//   1048��,scsi_remove_host()������,���Ǻ������scsi_add_host���Ӧ��.���ǵ���scsi core��
// ���ĺ���. 
//   1051��,usb_stor_release_resources(us),������Ǻ����ǵ����Ǹ�
// usb_stor_acquire_resources(us)���Ӧ.��1052�е� dissociate_dev(us)���Ǻ͵����Ǹ�
// associate_dev()���Ӧ.��������һ�¾������,����drivers/usb/storage/usb.c,�������������Ĵ�
// �붼һ��������: 
// 815 // Release all our dynamic resources // 
    816 void usb_stor_release_resources(struct us_data *us) 
    817 { 
    818         US_DEBUGP("-- %s\n", __FUNCTION__); 
    819 
    820         // Kill the control thread.  The SCSI host must already have been 
    821        //removed so it won't try to queue any more commands. 
    822          // 
    823         if (us->pid) { 
    824 
    825                 // Wait for the thread to be idle // 
    826                 down(&us->dev_semaphore); 
    827                 US_DEBUGP("-- sending exit command to thread\n"); 
    828 
    829                 // If the SCSI midlayer queued a final command just before 
    830                //scsi_remove_host() was called, us->srb might not be 
    831                //NULL.  We can overwrite it safely, because the midlayer 
    832                //will not wait for the command to finish.  Also the 
    833                //control thread will already have been awakened. 
    834                //That's okay, an extra up() on us->sema won't hurt. 
    835                //
    836                //Enqueue the command, wake up the thread, and wait for 
    837                //notification that it has exited. 
    838                  // 
    839                 scsi_lock(us->host); 
    840                 us->srb = NULL; 
    841                 scsi_unlock(us->host); 
    842                 up(&us->dev_semaphore); 
    843 
    844                 up(&us->sema); 
    845                 wait_for_completion(&us->notify); 
    846         } 
    847 
    848         // Call the destructor routine, if it exists //   196
    849         if (us->extra_destructor) { 
    850                 US_DEBUGP("-- calling extra_destructor()\n"); 
    851                 us->extra_destructor(us->extra); 
    852         } 
    853 
    854         // Finish the host removal sequence // 
    855         if (us->host) 
    856                 scsi_host_put(us->host); 
    857 
    858         // Free the extra data and the URB // 
    859         if (us->extra) 
    860                 kfree(us->extra); 
    861         if (us->current_urb) 
    862                 usb_free_urb(us->current_urb); 
    863 
    864 } 
    865 
    866 // Dissociate from the USB device // 
    867 static void dissociate_dev(struct us_data *us) 
    868 { 
    869         US_DEBUGP("-- %s\n", __FUNCTION__); 
    870 
    871         // Free the device-related DMA-mapped buffers // 
    872         if (us->cr) 
    873                 usb_buffer_free(us->pusb_dev, sizeof(*us->cr), us->cr, 
    874                                 us->cr_dma); 
    875         if (us->iobuf) 
    876                 usb_buffer_free(us->pusb_dev, US_IOBUF_SIZE, us->iobuf, 
    877                                 us->iobuf_dma); 
    878 
    879         // Remove our private data from the interface // 
    880         usb_set_intfdata(us->pusb_intf, NULL); 
    881 
    882         // Free the structure itself // 
    883         kfree(us); 
    884 } 
// 823��,�ж�us�� pid,���pid��������?����Ȼ,usb_stor_release_resources������ǰ��˵����
// usb_stor_acquire_resources������һ��,us->pidҲ��������usb_stor_acquire_resources()����,
// ��ʱ�ڵ���kernel_thread����usb_stor_control_thread��ʱ��,������kernel_thread()�ķ���ֵ,
// ������������us->pid,ʵ����kernel_thread()���ڸ�������˵,����ֵ�����ӽ��̵�pid,Ҳ����˵����
// �����ľ�����̵�pid�Ǳ���¼�����˵�.д������������ı�̹��׿ɼ�һ��. 
//   840��,���� us->srb ΪNULL.   197
//   844�к�845��,up(&us->sema),�Լ�wait_for_completion(&us->notify),֪��������������?
// ���ǵ�usb_stor_control_thread(),��������down_interruptible(&us->sema),���Ǿ�˵���ػ���
// �̽�����˯��,��ô˭�ܰ�������,����ǰ�潲��queuecommand֮��,����ͬ��Ҳ�ǻ������Ĵ���,����
// ��������ڻ��ѱ���֮��,�Լ�ִ��wait_for_completion����������ȴ�.��,�ٴλص��Ǹ�����
// ��,usb_stor_control_thread(),303��,��up()���ѵ�down_interruptible����0.Ȼ��312�е�316
// �е����ifС�ε�Ȼ�ͻ�ִ����,��Ϊus->srb��ʱ���������,����NULL,����break�ᱻִ��,�Ӷ���
// ��for��ѭ��,�Ӷ�usb_stor_control_thread�����������һ��,���յ���
// complete_and_exit(&(us->notify),0)��������������Լ����һ�����������Ľ���ȴ���
// usb_stor_release_resources.����Ȼ,������������ͨ���ĸ�����,����˵�������,��ʵ���˽��̵�ͬ
// ��,������Linux���ں�ͬ�����Ƶĵ���Ӧ��.(�������ָ����:up�� down,wait_for_completion��
// complete.) 
//   ��������,849��,struct us_data����һ��Ԫ��,extra_data_destructor extra_destructor,����һ
// ������ָ��,ʵ���϶�ĳЩ�豸��˵,�����Լ�������һЩ����ĺ���,���˳�֮ǰ��Ҫִ��,����Datafab 
// USB ���ն�����,�����������ı�̬���豸����,���ڴ�����豸��˵,�������ָ�붼Ϊ��.���������,
// ��ô��ȥִ����. 
//   Ȼ��856��,scsi_host_put,ֻ�Ƕ����host�����ü�����1,�����host�����ü����ﵽ0��,��ô
// ���ͷ����Ӧ��Scsi_Host���ݽṹ��ռ�Ŀռ�.һ��scsi ���������scsi_host_alloc��ʱ��ᱻ����
// ���ü���Ϊ1,���ü������Ǳ����ж��ٽ���ʹ���������Դ,�Ҽǵ��������Ե�ʱ��Ҳ�������ʵ���
// ��,2005���,�����µ�ʱ��,ȥ�Ž�����Ƽ�԰,�μ�SAP������,��ʱ̸��һ�����̹���վ�Ļ���,���Թ�
// ������,��Ȼ�ͻ��˶�û��Ӳ��,��ô��������ͬʱ��д�������ϵ�ͬһ���ļ�,������������,��ʱ��
// ������һ���Ҿ�ɵ��.��������,Ҳ����������ü����õ��ϵ��,�������Ǹ���ν��д����
// (copy-on-write)����.�����һ���ͦϲ��SAP,��ϧ,�˼ҿ�������. 
//   ������859��,�ж�us->extra,us->extra����Ϊǰ���Ǹ�extra_data_destructor����׼���Ĳ���,
// һ�㲻������,��������,�Ǿ��ͷ���. 
//   �ٽ�����,current_urbҲû����,�ͷŰ�.�ͷ�urb��Ҫ����ר�ŵĺ���usb_free_urb,������
// drivers/usb/core/urb.c��. 
//   ����������ǰ��ռ�е���Դ�����Ͼ��ͷŵ���. 
//   �ٿ���һ������,dissociate_dev(),����Ȼ,�������������ǰ�潲��associate_dev()������һ��.��
// associate_dev������,���ǵ�����usb_buffer_alloc()����,�Ⱥ�Ϊus->cr��us->iobuf�����˿ռ�,
// �����������ȵ������Ӧ�ĺ���usb_buffer_free()���ͷ������οռ�,Ȼ��,Ȼ��������������
// usb_set_intfdata����us->pusb_intf������Ӧ���豸��driver_dataָ����us,��������
// usb_set_intfdata()�ٴε��ôӶ���us->pusb_intf�� driver_dataָ���.���,����kfree�ͷ� us.
// ����,����,�����徲��. 
//   �������,���ǻ���һ�������Ҫ��,�Ǿ��Ƿ���һ�����ǹ����е�������,��������������ŵ��,Ҫ��
// �����ܽ�������,���ɺܼ�,ֻ�����ǰ��������¶�Ū������,���ǲſ���Ū���Ϊʲô��ĳ���ط�Ҫ��
// ��,��Ϊ��������Զ����ǣ���Ŷദ�Ĵ����,������һ������ս��!   198
// ��ʵ���ϱ���·,�ߵ��˶���,Ҳ��û��· 
//   ��ʵ�ź����ⶫ��,���񱱾�����,��ռ��һ������,�ҾͿ���û��������.������Щ����,û�б���������
// �ְ첻��.����������׳־���ߵ�ҽԺ��ҽ�����˵��ϣ�������Ժ���Ծ�������,�ɵõ���ֻ��ҽ������
// �Ļظ�,�Բ���,��û���ʸ�,��Ϊ��û�л���. 
//   ����ǰ��˵��,Linux��,���ź���,��������,�л�����,���������߻�������ĳ����������˵��ֻ��һ��
// ������ź���,���ź�����ζ����Դ��������,���������Ҳ����ܱ�����ÿ��ı������ڵ�����,�����ɸ�,
// ������ӳ�ľ��Ǹ�������,���Ƶ�������Ϊһ,����������ν��һ��һ����.��ֻ������һ����,һ����ռ��
// ����,������˻�Ҫ��õ���,�������ͷ�.����˵��������������. 
//   ���嵽usb storage,���ǲ����ź���������Linux������ôʵ�ֵ�,����֮���Ƿ��������������˵Ҳ
// ����ν,��ʵ��,usb-storage ��ʹ�õĶ�����,�������ź���,Ҳ�ǰ�����������ʹ��,�����ǵ����ǵ�����
// �ź����ĳ�ʼ��Ϊ1��?���ź�����ʼ��Ϊ1,��ô��������˵,�����൱���˻�Ϊһ������.����,ֻ������
// ״̬,�����ͽ���. 
//   ��ǰ���Ǽ����ܶ�����麯��,������һֱ���ڲ���. 
//   ���Ǿ���scsi_lock()��scsi_unlock(),�Լ�down(&us->dev_semaphore)��
// up(&us->dev_semaphore). 
//   ��������һ��.�����������Լ�����ĺ�.����drivers/usb/storage/usb.h. 
// 174 // The scsi_lock() and scsi_unlock() macros protect the sm_state and the 
//     175//single queue element srb for write access // 
//     176 #define scsi_unlock(host)       spin_unlock_irq(host->host_lock) 
//     177 #define scsi_lock(host)         spin_lock_irq(host->host_lock) 
// ��Ȼ,��������������ţ��֯Ůһ��,��һ��.�����ǵ�����,����������������������Դ,���������
// struct Scsi_Host��һ����Աspinlock_t *host_lock.��ô��ʲô�������Ҫʹ��������������������
// ������Դ��? 
//   ����Ҫдus->srb��ʱ��,(����дus->srb��Ԫ��,����дus->srb,������us->srb=NULL),����ʱ
// ��,����Ҫʹ�����������.��һ�������,�������scsi mid layer(scsi �в�)�ĺ���ʱ,��ʱ����Щ����
// Ҫ�������ӵ�������,��host_lock. 
//   ����һ��,����һ����7��ʹ����scsi_lock. 
//   �����о�һЩ��. 
   ��һ��,drivers/usb/storage/usb.c:usb_stor_release_resources()������, 
839                 scsi_lock(us->host); 
    840                 us->srb = NULL; 
    841                 scsi_unlock(us->host);   199
������ý����˰�,�������дus->srb,��ȻҪ��scsi_lock/scsi_unlock. 
  �ڶ���,drivers/usb/storage/transport.c:usb_stor_reset_common()������, 
   1121         scsi_lock(us->host); 
   1122         usb_stor_report_device_reset(us); 
   1123         set_bit(US_FLIDX_RESETTING, &us->flags); 
   1124         clear_bit(US_FLIDX_ABORTING, &us->flags); 
   1125         scsi_unlock(us->host); 
  ����ǵڶ������,��Ϊ���������usb_stor_report_device_reset(),�����������
drivers/usb/storage/scsiglue.c,Ҳ�����Ƕ����, 
308 // Report a driver-initiated device reset to the SCSI layer. 
    309//Calling this for a SCSI-initiated reset is unnecessary but harmless. 
    310//The caller must own the SCSI host lock. // 
    311 void usb_stor_report_device_reset(struct us_data *us) 
    312 { 
    313         int i; 
    314 
    315         scsi_report_device_reset(us->host, 0, 0); 
    316         if (us->flags & US_FL_SCM_MULT_TARG) { 
    317                 for (i = 1; i < us->host->max_id; ++i) 
    318                         scsi_report_device_reset(us->host, 0, i); 
    319         } 
    320 } 
ע�⵽,����ߵ�����scsi_report_device_reset(),��������drivers/scsi/scsi_error.c,������scsi 
mid layer����ĺ���,���������ע��˵�ú����,������ʱ����Ҫӵ��host lock. 
  ����˵���е��������,drivers/usb/storage/usb.c,usb_stor_control_thread()������, 
318                 // lock access to the state // 
    319                 scsi_lock(host); 
    320 
    321                 // has the command timed out *already* ? // 
    322                 if (test_bit(US_FLIDX_TIMED_OUT, &us->flags)) { 
    323                         us->srb->result = DID_ABORT << 16; 
    324                         goto SkipForAbort; 
    325                 } 
    326 
    327                 // don't do anything if we are disconnecting // 
    328                 if (test_bit(US_FLIDX_DISCONNECTING, &us->flags)) { 
    329                         US_DEBUGP("No command during disconnect\n"); 
    330                         goto SkipForDisconnect; 
    331                 }   200
    332 
    333                 scsi_unlock(host); 
������̫�в���,��δ��붼����ע�⵽��.��ȷ������,�����޷��ǵ�����test_bit,����ȴʹ����
scsi_lock/scsi_unlock���ԩ��,����ʲôԭ��?��ʵ��������,����ע�⵽����������goto���, 
387 SkipForAbort: 
    388                         US_DEBUGP("scsi command aborted\n"); 
    389                 } 
    390 
    391                 // If an abort request was received we need to signal that 
    392                //the abort has finished.  The proper test for this is 
    393                //the TIMED_OUT flag, not srb->result == DID_ABORT, because 
    394                //a timeout/abort request might be received after all the 
    395                //USB processing was complete. // 
    396                 if (test_bit(US_FLIDX_TIMED_OUT, &us->flags)) 
    397                         complete(&(us->notify)); 
    398 
    399                 // finished working on this command // 
    400 SkipForDisconnect: 
    401                 us->srb = NULL; 
    402                 scsi_unlock(host); 
��401��,us->srb=NULL,������һ��.�����Ϊʲô֮ǰҪ��scsi_lock������ԭ��.��Ϊ��Ҫ��ת,
������ȥ�Ժ���Ҫдus->srb,����Ҫ���host lock,��Ȼ���ǿ��԰�scsi_lockд��test_bit()֮��,��
�� 
    321                 // has the command timed out *already* ? // 
    322                 if (test_bit(US_FLIDX_TIMED_OUT, &us->flags)) { 
    323                         us->srb->result = DID_ABORT << 16; 
�������һ��==>         scsi_lock(host); 
    324                         goto SkipForAbort; 
// �����Ķ�����Ҳ����,�Եø����Ͻ�,�����Ĳ������岢����. 
//   ��Ȼ,��һ�β��Գ�ʱ�Ĵ��뱾��ʹ���ϵĿ�����Ҳ����,��Ϊ�������û�п�ʼִ����,����,һ��
// ���û�п�ʼ�ͳ�ʱ,��������ۼ���,���й���������ɱ�����籭����. 
//   �������ڶ���,����us->dev_semaphore,����������ֳ�����һ�ֽ��̼��ͬ������.2.6.10���ں�
// ������һ����6��ʹ��������ź���.�ֱ�����device_reset()��,bus_reset()
// ��,usb_stor_control_thread()��,usb_stor_acquire_resources()
// ��,usb_stor_release_resources()��,storage_disconnect()��.�⼸������֮���Ǵ���һ���໥��Լ
// �Ĺ�ϵ.   201
//   ����,һ���龰��,��device_reset()����bus_reset()��������,����usb_stor_control_thread()��
// �߾Ͳ����������ʱ��ִ������,usb_stor_acquire_resources()�е� GET_MAX_LUNҲ����ִ��,��
// Ϊ����Ȼ,����reset��,�ͺñ���ĵ������������㵱Ȼ������ִ��һ����������Ĳ���. 
//   ����һ���龰,��usb_stor_control_thread()����ִ������,��ô��Ȼ
// usb_stor_release_resources()�����Ͳ����ͷ���Դ��,����storage_disconnect()Ҳ�õȴ�,�õ���
// ��ǰ�������ִ������,���Ż�ȥִ�жϿ��Ĵ���.�ͺñ������ڿ�����սս�����Ĵ���,��ʦȴǿ�а����
// �Ծ�����ȥ,��˵��᲻��ܷ�ŭ?(��Ȼ,�������Ϊ�����ױ�����,�Ǿ���������.) 
//   ��֮,���ֹ�ϵ�����໥��,�໥��Լ,ͬʱҲ��֤������ϵͳ������ת,���˭Υ����,��ô�˺����Ǵ��
// ������.�����Linux�ں˵�ͬ������. 
//   ����.�ҵĹ��½�����.��Ȼ����, ����, ��ʵ, ��һֱ��Ѱ��, Ѱ��������µĽ��, Ѱ���Լ����ĳ�
// ·, ����, ׷Ѱ����ǰ��, ȴһֱû���ҵ�����. 