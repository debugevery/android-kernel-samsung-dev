ʷ������Linux�ں�ѧϰ������
2010��05��12��00:00 IT168ԭ�� ���ߣ���Դʱ�� �༭������ ���ۣ�0�� 
����Tag�� linux���� Linux linux�ں˿��� ������IT168 ����������

����Makefile����Make Love

������ǰ��ѧУ���������꣬û��ѧ���κζ�����ÿ������ӿΣ�����������Ϸ��˯������ҵ��ʱ���˼Ҹ���˵Makefile����ȫ��֪������һ˵Make Love�Ҿ������ˣ�����������Ȼ���ö��ˡ�

�����������ŵ�˵��Kconfig��Makefile����������ں˴���ʱ��Ϊ���̵������ļ��������ϣ�Linux�ں���ÿһ��Ŀ¼�±߶�����һ��Kconfig�ļ���һ��Makefile�ļ�������һ��ϣ���ܹ���Linux�ں˵���������￴��һ˿��������˵�������Ƿ�����ô��Ҫ�ĵ�λ�������֡�

��������ȥ��ۣ�ͨ�����ص�ʱ���ܻ�����ѵĵ�ͼ�͸���ָ���ã������������������ǲŲ�������ͷ��Ӭ����㯵�������İ���Ľֵ��ϡ���ʹ���ڵس�ȥ���ε�ʱ��һ����˵Ҳ���ǻ������ҷݵ�ͼ����Ȼ�ˣ���ʱ����Ҫȥ���ˣ������ò����ģ���ͬ�ĵط��в�ͬ����ɫ�� ֻ�����е���ɫ�Ƿ����е���ɫ����ȡ��

����Kconfig��Makefile����Linux Kernel�Թ���ĵ�ͼ����ͼ��������ȥ��ʶһ�����У���Kconfig��Makefile������������˽�һ��KernelĿ¼����Ľṹ������ÿ�����kernelѰ�������Լ�����һ�δ���ʱ����Ӧ�����ȿ���Ŀ¼�µ��������ļ���

��������Kconfig��MakefileѰ��Ŀ�����

�����������õ�ͼѰ��Ŀ�ĵ�һ����������Ҫ����Kconfig��Makefile��Ѱ����Ҫ�о���Ŀ����롣�������Ǵ����о�U��������ʵ�֣���ΪU����һ��storage�豸����������Ӧ���Ƚ��뵽drivers/usb/storage/Ŀ¼�����Ǹ�Ŀ¼�µ��ļ��ܶ࣬��ô������Щ�ļ�����������Ҫ��ע��?��ʱ���б�Ҫ��ȥ�Ķ�Kconfig��Makefile�ļ���

��������Kconfig�ļ������ǿ��Կ��������ѡ�

config USB_STORAGE_DATAFAB
bool "Datafab Compact Flash Reader support (EXPERIMENTAL)"
depends on USB_STORAGE && EXPERIMENTAL
help
Support for certain Datafab CompactFlash readers.
Datafab has a web page at <http://www.datafabusa.com/>.
������Ȼ�����ѡ������ǵ�Ŀ��û�й�ϵ��������ר�����Datafab��˾�Ĳ�Ʒ�������ȻCompactFlash reader��һ��flash�豸������Ȼ����U�̡���Ϊdrivers/usb/storageĿ¼�µĴ��������usb mass storage��һ���豸�����������ĳһ���ض����豸��U��ֻ��usb mass storage�豸�е�һ�֡��ٱ��磺

config USB_STORAGE_SDDR55
bool "SanDisk SDDR-55 SmartMedia support (EXPERIMENTAL)"
depends on USB_STORAGE && EXPERIMENTAL
help
Say Y here to include additional code to support the Sandisk SDDR-55
SmartMedia reader in the USB Mass Storage driver.


��������Ȼ���ѡ�����й�SanDisk��Ʒ�ģ�������Ե���SM����ͬ������U�̣���������Ҳ����Ҫȥ��ע��

������ʵ�ϣ�������ȷ����ֻ��ѡ��CONFIG_USB_STORAGE��������������Ҫ��ע�ġ�

9 config USB_STORAGE

10 tristate "USB Mass Storage support"

11 depends on USB && SCSI

12 ---help---

13 Say Y here if you want to connect USB mass storage devices to your

14 computer's USB port. This is the driver you need for USB

15 floppy drives, USB hard disks, USB tape drives, USB CD-ROMs,

16 USB flash devices, and memory sticks, along with

17 similar devices. This driver may also be used for some cameras

18 and card readers.

19

20 This option depends on 'SCSI' support being enabled, but you

21 probably also need 'SCSI device support: SCSI disk support'

22 (BLK_DEV_SD) for most USB storage devices.

23

24 To compile this driver as a module, choose M here: the

25 module will be called usb-storage.


�����������Ķ�Makefile�ļ���

0 #

1 # Makefile for the USB Mass Storage device drivers.

2 #

3 # 15 Aug 2000, Christoph Hellwig

4 # Rewritten to use lists instead of if-statements.

5 #

6

7 EXTRA_CFLAGS := -Idrivers/scsi

8

9 obj-$(CONFIG_USB_STORAGE) += usb-storage.o

10

11 usb-storage-obj-$(CONFIG_USB_STORAGE_DEBUG) += debug.o

12 usb-storage-obj-$(CONFIG_USB_STORAGE_USBAT) += shuttle_usbat.o

13 usb-storage-obj-$(CONFIG_USB_STORAGE_SDDR09) += sddr09.o

14 usb-storage-obj-$(CONFIG_USB_STORAGE_SDDR55) += sddr55.o

15 usb-storage-obj-$(CONFIG_USB_STORAGE_FREECOM) += freecom.o

16 usb-storage-obj-$(CONFIG_USB_STORAGE_DPCM) += dpcm.o

17 usb-storage-obj-$(CONFIG_USB_STORAGE_ISD200) += isd200.o

18 usb-storage-obj-$(CONFIG_USB_STORAGE_DATAFAB) += datafab.o

19 usb-storage-obj-$(CONFIG_USB_STORAGE_JUMPSHOT) += jumpshot.o

20 usb-storage-obj-$(CONFIG_USB_STORAGE_ALAUDA) += alauda.o

21 usb-storage-obj-$(CONFIG_USB_STORAGE_ONETOUCH) += onetouch.o

22 usb-storage-obj-$(CONFIG_USB_STORAGE_KARMA) += karma.o

23

24 usb-storage-objs := scsiglue.o protocol.o transport.o usb.o \

25 initializers.o $(usb-storage-obj-y)

26

27 ifneq ($(CONFIG_USB_LIBUSUAL),)

28 obj-$(CONFIG_USB) += libusual.o

29 endif

����ǰ��ͨ��Kconfig�ļ��ķ���������ȷ����ֻ��Ҫȥ��עCONFIG_USB_STORAGEѡ���Makefile�ļ������CONFIG_USB_STORAGE���ӵ�9�е�֪����ѡ���Ӧ��ģ��Ϊusbstorage����ΪKconfig�ļ��������ѡ�����Ƕ�����Ҫ��ע������Makefile��11~22�п��Ժ��ԡ���24����ζ������ֻ��Ҫ��ע scsiglue.c��protocol.c��transport.c��usb.c��initializers.c�Լ�����ͬ����.hͷ�ļ���

����Kconfig��Makefile�ܺõİ������Ƕ�λ������Ҫ��ע��Ŀ�꣬�������ǵ�һ��İ���ĵط�Ҫ����Я����ͼ��������ѧϰLinux�ں�ʱ��ҲҪ����Ѱ��Kconfig��Makefile�İ�����

����͸�����󿴱��ʣ��������޷Ǿ���һЩ��������չʾ��ͬ���������￴��ȥ��ѧϰ�ںˣ�����ѧϰ�ں˵�Դ���룬�κ��ں��йص��鼮���ǻ����ںˣ����ֲ������ں˵ġ�

������ȻҪѧϰ�ں�Դ�룬��Ҫ�������ں˴�����з��������ں˴���ǧǧ�򣬻�ǰ�ͺ�̵Ĳ�������ӣ�����ô󲿷��˶��������￴���������������С����� ��Ҫ�£����Ϸ����������������Ӧ��֮�ߣ������¶������ԣ����е������ɣ���ν��ѧҲ�ѡ������˵������Ҫ̤ʵ���Ǻ�ѧ����ͬ־��Ҫ��ѭ�Ͻ���̬�ȣ�ȥ�� ��ÿһ�δ����ʵ�֣����ʶ����ǡ������������ۻ����ù��ҹ���̬�ȣ�������п��ܾ���һ�߿�һ�߶���û�ж����ջ�

��������ȫ����������1.5%������80��ֳ���ũ���ӵ�??����Ȼ���ǵ����������˼��裬��ô����������������ھ��Ȳ�������ϣ���о��ں���USB��ϵͳ��ʵ�֣�Ӧ��û�������?�Ǻã��������USB��ϵͳ��ʵ�ַ���Ϊ�걾���������ں�Դ��Ӧ��������֡�

��������README

�����ں���USB��ϵͳ�Ĵ���λ��Ŀ¼drivers/usb��������۲�����Ҫ���衣�������ǽ��뵽��Ŀ¼��ִ������ls�������ʾ���£�

����atm class core gadget host image misc mon serial storage Kconfig

����Makefile README usb-skeleton.c

����Ŀ¼drivers/usb��������10����Ŀ¼��4���ļ���usb-skeleton.c��һ���򵥵�USB driver�Ŀ�ܣ�����Ȥ�Ŀ���ȥ������Ŀǰ��˵�����������������ǵ�������ô����Ӧ�ù�עʲô?���ӭ������һ��ppmm��������ȿ������Ż����� ��?��Ȼ������ÿ���˵��û�������ͬ���������������Ӧ��ֻ��һ���𰸣��Ǿ���Kconfig��Makefile��README��

����README���й������Ŀ¼�����ݵ�һ���������������ǹؼ���ֻ�ǰ������˽⡣��˵�ˣ���ԡ�read�Ұ�read�Ұɡ���ô���鱼�ŵĺ����������������ǲ������޶����Եģ����������������涼��Щʲô���ݡ�

23 Here is a list of what each subdirectory here is, and what is contained in

24 them.

25

26 core/ - This is for the core USB host code, including the

27 usbfs files and the hub class driver ("khubd").

28

29 host/ - This is for USB host controller drivers. This

30 includes UHCI, OHCI, EHCI, and others that might

31 be used with more specialized "embedded" systems.

32

33 gadget/ - This is for USB peripheral controller drivers and

34 the various gadget drivers which talk to them.

35

36

37 Individual USB driver directories. A new driver should be added to the

38 first subdirectory in the list below that it fits into.

39

40 image/ - This is for still image drivers, like scanners or

41 digital cameras.

42 input/ - This is for any driver that uses the input subsystem,

43 like keyboard, mice, touchscreens, tablets, etc.

44 media/ - This is for multimedia drivers, like video cameras,

45 radios, and any other drivers that talk to the v4l

46 subsystem.

47 net/ - This is for network drivers.

48 serial/ - This is for USB to serial drivers.

49 storage/ - This is for USB mass-storage drivers.

50 class/ - This is for all USB device drivers that do not fit

51 into any of the above categories, and work for a range

52 of USB Class specified devices.

53 misc/ - This is for all USB device drivers that do not fit

54 into any of the above categories.
�������README�ļ�������ǰ��ʹ��ls�����г�����10���ļ��е���;����ôʲô��USB Core?

����Linux�ں˿������ǣ�ר��д��һЩ���룬����ʵ��һЩ���ĵĹ��ܣ�Ϊ����豸���������ṩ���񣬱��������ڴ棬����ʵ��һЩ���е��豸���� ��Ҫ�Ĺ����ĺ�������������ԻUSB Core��

����ʱ�����ڷ�չ��������������������������ʣ�������������͵�������־��������ħ����ġ�ͬ�������ڵ�Linux�ںˣ���ṹ���������������в� �θУ�Զ����������������£���ʱ��drivers/usb/���Ŀ¼�±߷��˺ܶ�ܶ��ļ���USB Core�����������豸����������Ĵ��붼����

�������������������������ǧ�ı�ã��ܰ���������˷����ˡ�������drivers/usb/Ŀ¼��������� һ��coreĿ¼����ר�ŷ�һЩ���ĵĴ��룬�����ʼ������USBϵͳ����ʼ��Root Hub����ʼ�������������Ĵ��룬�ٺ���������������������صĴ���Ҳ��������һ��Ŀ¼����hostĿ¼��������ΪUSB��������������ʱ���ķ�չ��Ҳ�� ʼ���˺ü��֣�������տ�ʼ����ֻ��һ�֣������أ�������ǰ�һЩ���������������Ĵ�����Ȼ����coreĿ¼�£���һЩ�����������������Ĵ������Ƶ� hostĿ¼�����ø��������������������ȥά����

������ôUSB gadget��?gadget����˵�����������˼����Ҫ����һЩ�ڲ�����Linux��Ƕ��ʽ�豸������PDA���豸������USB�豸������(USB Device Controller)�����Խ�PC��Ҳ�������ǵ�������Ϊmaster�ˣ����������豸��Ϊslave�˺�����ͨ��USB����ͨ�š��������Ĺ۵������� ����ϵͳ��USB����������Ʋ������е�USB�豸����USB gadget���������������Χ�豸�����Ϊһ��USB�豸������ͨ__________�š����磬���ǵ�Ƕ��ʽ������֧��SD�����������ϣ���ڽ�����ͨ��USB���ӵ�PC ֮�����SD����ģ���U�̣���ô��Ҫͨ��USB gadget�ܹ���������

����ʣ�µļ���Ŀ¼���ű���ķ��˸���USB�豸������������U�̵�������storageĿ¼�£���������USB��������������inputĿ¼�£��ȵȡ�



����������Ӧ��README��������������������������Ҫ�ģ�ͨ���������˽���USBĿ¼�����Щ�ļ��ж�����ʲô���Ľ�ɫ��������Ϊֹ����ֻʣ���ں˵ĵ�ͼ����Kconfig��Makefile�����ļ��ˡ�

�����е�ͼ���֣��������ں����ε���������˵���Ǽ������õ����飬��������Ϊ���ǵ�Ŀ�����о��ں˶�USB��ϵͳ��ʵ�֣��������ض��豸��host controller����������������Ķ�λ�����ԣ�USB Core����������Ҫ��ע�Ķ�����ô����������Ҫ��coreĿ¼�е����ݽ��ж�λ�ˡ�

��������Kconfig��Makefile

�������뵽drivers/usb/coreĿ¼��ִ������ls�������ʾ���£�

����Kconfig Makefile buffer.c config.c devices.c devio.c driver.c
����endpoint.c file.c generic.c hcd-pci.c hcd.c hcd.h hub.c hub.h
����inode.c message.c notify.c otg_whitelist.h quirks.c sysfs.c urb.c
����usb.c usb.h
����Ȼ��ִ��wc���������ʾ��

# wc �Cl ./*

148 buffer.c

607 config.c

706 devices.c

1677 devio.c

1569 driver.c

357 endpoint.c

248 file.c

238 generic.c

1759 hcd.c

458 hcd.h

433 hcd-pci.c

3046 hub.c

195 hub.h

758 inode.c

144 Kconfig

21 Makefile

1732 message.c

68 notify.c

112 otg_whitelist.h

161 quirks.c

710 sysfs.c

589 urb.c

984 usb.c

160 usb.h

16880 total
����drivers/usb/coreĿ¼������24���ļ���16880�д��롣core������core��Ϊ���ĬĬ������ô���¡�������ô���ļ��ﲻһ��������������Ҫ��ע�ģ��������ǵĵ�ͼ����������������ô�ߡ�



�����ȿ���Kconfig�ļ������Կ��������ѡ�

15 config USB_DEVICEFS

16 bool "USB device filesystem"

17 depends on USB

18 ---help---

19 If you say Y here (and to "/proc file system support" in the "File

20 systems" section, above), you will get a file /proc/bus/usb/devices

21 which lists the devices currently connected to your USB bus or

22 busses, and for every connected device a file named

23 "/proc/bus/usb/xxx/yyy", where xxx is the bus number and yyy the

24 device number; the latter files can be used by user space programs

25 to talk directly to the device. These files are "virtual", meaning

26 they are generated on the fly and not stored on the hard drive.

27

28 You may need to mount the usbfs file system to see the files, use

29 mount -t usbfs none /proc/bus/usb

30

31 For the format of the various /proc/bus/usb/ files, please read

32 <file:Documentation/usb/proc_usb_info.txt>.

33

34 Usbfs files can't handle Access Control Lists (ACL), which are the

35 default way to grant access to USB devices for untrusted users of a

36 desktop system. The usbfs functionality is replaced by real

37 device-nodes managed by udev. These nodes live in /dev/bus/usb and

38 are used by libusb.
����ѡ��USB_DEVICEFS��usbfs�ļ�ϵͳ�йء�usbfs�ļ�ϵͳ������/proc/bus/usbĿ¼����ʾ�˵�ǰ���ӵ�����USB �� �������ߵĸ�����Ϣ��ÿ�����ӵ�USB�豸�����ж�����һ����Ӧ���ļ����������������ļ�/proc/bus/usb/xxx/yyy��xxx��ʾ��__________�ߵ� ��ţ�yyy��ʾ�豸�������ߵĵ�ַ���������ܹ������������ȶ��ط����豸����Ϊͬһ�豸�������Ӷ�Ӧ�������ļ����ܻ᲻ͬ�����磬��һ������һ���豸 ʱ����������002/027��һ��ʱ����ٴ����ӣ������ܾ��Ѿ��ı�Ϊ002/048��

�����ͺñȺò������㰵����mm��������ʱ��������˸����ۣ����Ļ�ŭ�ţ��Ͽ�ȥ����100���Ʊ��ף�����ڶ����ټ�������ʱ��������˵����˭�����㱯ʹ�����Ĺο���100���Ʊ��������һɫ��лл�㡣

������Ϊusbfs�ļ�ϵͳ��������USB��ϵͳʵ�ֵĺ��Ĳ��֣���֮��صĴ������ǿ��Բ��ع�ע��

74 config USB_SUSPEND

75 bool "USB selective suspend/resume and wakeup (EXPERIMENTAL)"

76 depends on USB && PM && EXPERIMENTAL

77 help

78 If you say Y here, you can use driver calls or the sysfs

79 "power/state" file to suspend or resume individual USB

80 peripherals.

81

82 Also, USB "remote wakeup" signaling is supported, whereby some

83 USB devices (like keyboards and network adapters) can wake up

84 their parent hub. That wakeup cascades up the USB tree, and

85 could wake the system from states like suspend-to-RAM.

86

87 If you are unsure about this, say N here.
������һ�����й�USB�豸�Ĺ���ͻָ�������USB���˶��ǽڵ���ܵĺú��ӣ�����Э����͹涨�ˣ����е��豸������֧�ֹ���״̬������˵Ϊ�˴ﵽ�� ���Ŀ�ģ����豸��ָ����ʱ���ڣ����û�з������ߴ��䣬��Ҫ�������״̬�������յ�һ��non-idle���ź�ʱ���ͻᱻ���ѡ���Լ�õ��USB���� �������������Ҳû̫���ϵ����ش���Ҳ���Բ��ù�ע�ˡ�

����ʣ�µĻ��м�������ƺ������ǹ�ϵҲ���󣬻���ȥ����Makefile��

5 usbcore-objs := usb.o hub.o hcd.o urb.o message.o driver.o \

6 config.o file.o buffer.o sysfs.o endpoint.o \

7 devio.o notify.o generic.o quirks.o

8

9 ifeq ($(CONFIG_PCI),y)

10 usbcore-objs += hcd-pci.o

11 endif

12

13 ifeq ($(CONFIG_USB_DEVICEFS),y)

14 usbcore-objs += inode.o devices.o

15 endif

16

17 obj-$(CONFIG_USB) += usbcore.o

18

19 ifeq ($(CONFIG_USB_DEBUG),y)

20 EXTRA_CFLAGS += -DDEBUG

21 endif
����Makefile�ɱ�Kconfig���Զ��ˣ����Կ�����Ҳ�����е㣬���������õ�moneyԽ��Խ�ã����Ĵ���Խ��Խ�á�����֮���Ի���� CONFIG_PCI������Ϊͨ��USB��Root Hub������һ��PCI�豸�С�hcd-pci��hcd������˼���֪����˵�����������ģ�����ʵ���������������������֣���

����Э�����˵�����Ǿ��� HCDI(HCD�Ĺ����ӿ�)��hostĿ¼����ʵ���˸��ֲ�ͬ��������������CONFIG_USB_DEVICEFSǰ���Kconfig�ļ���Ҳ�����ˣ�����usbfs�ģ������ǵ������޹أ�inode.c��devices.c�����ļ�Ҳ���Բ��ù��ˡ�

������ô���ǿ��Եó����ۣ�Ϊ������ں˶�USB��ϵͳ��ʵ�֣�������Ҫ�о�

����buffer.c��config.c��driver.c�� endpoint.c��file.c��generic.c��hcd.c

����hcd.h��hub.c��message.c��notify.c��otg_whitelist.h��quirks.c��sysfs.c��urb.c ��usb.c�ļ���

������ô�������������Ҫ��ע�����ӣ�û�м������ѹ�����������ﱾ�����USB Core���֣���Ҫ���ܶ����Ϊ���Ƿ��ǵģ����Զ��Ҳ�ǿ������ġ�



��������ķ�������¬����˵�ˣ����ݲ���Ҫ����Ҫ����̬�ȡ����񺫾ֳ��Դ��ռǵ�̬���������Ͻ���ϸ�¡�

����ֻҪ��ʹ��������̬�ȿ�ʼ�����ںˣ���ô������ѡ���ں˵��ĸ�������Ϊ����㣬����USB��������̹����ڻ�����Բ���ܶ��ʱ��֮����ͻᷢ ������ں˵���������������һ���߶ȣ�һ�������龰����������0.1�ں���ȫע�ͣ����Ÿ��ָ������ں��鼮������ȥ�Ŀ��ܶ�������ܶ�鶼�޷��ﵽ�ĸ� �ȡ���������!��������Linux�����﷢�����٣�ѧϰ�ں�Դ�룬��ѧϰ���ֳ���ʼ!

����̬�Ⱦ���һ�У��ӳ�ʼ��������ʼ

������Сǿ��˵���۸��Ǵ����ڿ�ʼ����������˵ţ�д�5000�㿪ʼ�����ǵĿ�ʼ��Ҫ���ǵ�Ǯ�������ǵĿ�ʼֻ��Ҫһ̨���ԣ��������һ���裬���ż�֧С������������Ǯ���ǻ�Ƚ����ġ������ף������ף�������ף���Ϊ��Ҫ����Ǯ��

�������˵�ͼKconfig��Makefile�����ǿ������Ӵ��ӵ��ں˴����ж�λ�Լ���С��Ŀ�����ķ�Χ����ô���ڣ�Ϊ���о��ں˶�USB��ϵͳ��ʵ�֣����ǻ���Ҫ��Ŀ��������ҵ�һ��ͻ�ƿڣ����ͻ�ƿھ���USB��ϵͳ�ĳ�ʼ�����롣

�������ĳ����ϵͳ��ĳ���������ں�ʹ��subsys_initcall��//module_init��ָ����ʼ����������drivers/usb/core/usb.c�ļ��У����ǿ��Է�������Ĵ��롣

����940 subsys_initcall(usb_init);

����941 //module_exit(usb_exit);

�������ǿ���һ��subsys_initcall����Ҳ��һ���꣬���ǿ��԰������Ϊ//module_init��ֻ������Ϊ�ⲿ�ִ���ȽϺ��ģ��������� ��������һ����ϵͳ������������һ��ģ�顣��Ҳ�ܺ���⣬usbcore���ģ��������Ĳ���ĳһ���豸����������USB�豸���������ģ�飬Linux �У�������һ�������豸���������Ϊһ����ϵͳ������PCI��ϵͳ������SCSI��ϵͳ�������ϣ�drivers/Ŀ¼�����һ���ÿ��Ŀ¼����һ���� ϵͳ����Ϊ���Ǵ�����һ���豸��

����subsys_initcall(usb_init)����˼���Ǹ�������usb_init��USB��ϵͳ�����ĳ�ʼ����������usb_exit() ��������USB��ϵͳ�Ľ���ʱ��������������Ϊ���о�USB��ϵͳ���ں��е�ʵ�֣�

����������Ҫ��usb_init������ʼ����

865 static int __init usb_init(void)

866 {

867 int retval;

868 if (nousb) {

869 pr_info("%s: USB support disabled\n", usbcore_name);

870 return 0;

871 }

872

873 retval = ksuspend_usb_init();

874 if (retval)

875 goto out;

876 retval = bus_register(&usb_bus_type);

877 if (retval)

878 goto bus_register_failed;

879 retval = usb_host_init();

880 if (retval)

881 goto host_init_failed;

882 retval = usb_major_init();

883 if (retval)

884 goto major_init_failed;

885 retval = usb_register(&usbfs_driver);

886 if (retval)

887 goto driver_register_failed;

888 retval = usb_devio_init();

889 if (retval)

890 goto usb_devio_init_failed;

891 retval = usbfs_init();

892 if (retval)

893 goto fs_init_failed;

894 retval = usb_hub_init();

895 if (retval)

896 goto hub_init_failed;

897 retval = usb_register_device_driver(&usb_generic_driver, THIS_MODULE);

898 if (!retval)

899 goto out;

900

901 usb_hub_cleanup();

902 hub_init_failed:

903 usbfs_cleanup();

904 fs_init_failed:

905 usb_devio_cleanup();

906 usb_devio_init_failed:

907 usb_deregister(&usbfs_driver);

908 driver_register_failed:

909 usb_major_cleanup();

910 major_init_failed:

911 usb_host_cleanup();

912 host_init_failed:

913 bus_unregister(&usb_bus_type);

914 bus_register_failed:

915 ksuspend_usb_cleanup();

916 out:

917 return retval;

918 }

����(1)__init��ǡ�

��������usb_init����һ�������ǣ���865�е�__init��Ǿ���ʲô����?

����д��������Ӧ�ò���İ���������ں���˵����һ�ְ�ʾ����������������ڳ�ʼ���ڼ�ʹ�ã���ģ�鱻װ��֮����ռ�õ���Դ�ͻ��ͷŵ��������������İ� ʾ�㶮������İ�ʾ����ȴ�������߶�װ��������ô���˸��ˡ������Լ����ݵ�һ����һֱ���·��صĹ������Ե��ǲ��³�����ţ�̣����µ�������USB��ϵͳ�� ���١�

���������־�������Ⱦ���Ҿ���__________�б�ҪΪ��˵�ĸ���Щ��__init�Ķ�����include/linux/init.h�ļ���43 #define __init __attribute__ ((__section__ (".init.text")))

�����������������˸�������ʣ�__attribute__��ʲô?Linux�ں˴���ʹ���˴�����GNU C��չ��������GNU C��Ϊ�ܹ������ں˵�Ψһ��������GNU C����Щ��չ�Դ����Ż���Ŀ����벼�֡���ȫ���ȷ���Ҳ�ṩ�˺�ǿ��֧�֡���__attribute__������Щ��չ�е�һ��������Ҫ����������һЩ��������ԣ���Щ������Ҫ������ָʾ�����������ض�������Ż��͸���ϸ�Ĵ����顣GNU C֧��ʮ�������ԣ�section�����е�һ�������ǲ鿴GCC���ֲ���Կ������������

������section ("section-name")'

����Normally, the compiler places the code it generates in the `text' section.��Sometimes, however, you need additional sections, or you need certain particular functions to appear in special sections.The `section' attribute specifies that a function lives in a particular section.��For example, the declaration:extern void foobar (void) __attribute__ ((section ("bar")));puts the function ��foobar' in the ��bar' section.Some file formats do not support arbitrary sections so the ��section' attribute is not available on all platforms.��If you need to map the entire contents of a module to a particular section, consider using the facilities of the linker instead.

����ͨ������������������.text�ڣ���������.data��.bss�ڣ�ʹ��section���ԣ������ñ��������������������ָ���Ľ��С���ôǰ�� ��__init�Ķ�����ʾ�������εĴ������.init.text�ڡ����������԰���ͬ�ڵĴ�������ݰ�����һ�𣬱���__init���ε����д��붼�� ������.init.text�����ʼ��������Ϳ����ͷ��ⲿ���ڴ档

����������Ե���Ϊֹ��Ҳ���Ը����룬���ں�������ε��õ���Щ__init���εĳ�ʼ������?Ҫ�ش�������⣬����Ҫ�ع�һ��subsys_initcall�꣬��Ҳ��include/linux/init.h�ﶨ��

����125 #define subsys_initcall(fn) __define_initcall("4",fn,4)

���������ֳ�����һ����__define_initcall�������ڽ�ָ���ĺ���ָ��fn�ŵ�initcall.init���� �����ھ����subsys_initcall�꣬���ǰ�fn�ŵ�.initcall.init���ӽ�.initcall4.init�ҪŪ���.initcall.init��.init.text��.initcall4.init�����Ķ��������ǻ���Ҫ�˽�һ���ں˿�ִ���ļ���صĸ��

�����ں˿�ִ���ļ������������һ��Ķ����ļ���ɡ������ļ������ڣ����ı������ݡ�init���ݡ�bass�ȵȡ���Щ�����ļ�����__________��һ����Ϊ������ �ű����ļ����Ӳ�װ��ġ�����������ű��Ĺ����ǽ���������ļ��ĸ���ӳ�䵽����ļ���;���仰˵������������������ļ������ӵ���һ�Ŀ�ִ���ļ��У��� �ÿ�ִ���ļ��ĸ���װ�뵽ָ����ַ���� vmlinux.lds�Ǵ�����arch// Ŀ¼�е��ں��������ű��������������ں˵ĸ����ڲ�������װ���ڴ����ض�ƫ��������

�����ҿ��Ը����εĸ����㣬Ҫ����vmlinux.lds����ļ�����Ҫһ������ģ�������Ҷ��Ǵ����ˣ��������������£���������Ҫ����ֻ������initcall.init��Ȼ���ῴ��������ʶ������

__inicall_start = .;

.initcall.init : AT(ADDR(.initcall.init) �C 0xC0000000) {

*(.initcall1.init)

*(.initcall2.init)

*(.initcall3.init)

*(.initcall4.init)

*(.initcall5.init)

*(.initcall6.init)

*(.initcall7.init)

}

__initcall_end = .;
���������__initcall_startָ��.initcall.init�ڵĿ�ʼ��__initcall_endָ�����Ľ�β����.initcall.init���ֱ���Ϊ��7���ӽڣ��ֱ���

.initcall1.init

.initcall2.init

.initcall3.init

.initcall4.init

.initcall5.init

.initcall6.init

.initcall7.init
�������ǵ�subsys_initcall����ǽ�ָ���ĺ���ָ�������.initcall4.init�ӽڡ������ı���core_initcall������ָ�����.initcall1.init�ӽڣ�device_initcall������ָ�������.initcall6.init�ӽڵȵȣ������Դ� include/linux/init.h�ļ��ҵ����ǵĶ��塣�����ֽڵ�˳����ȷ���ģ����ȵ���.initcall1.init�еĺ���ָ���ٵ� ��.initcall2.init�еĺ���ָ�룬�ȵȡ�__init���εĳ�ʼ���������ں˳�ʼ�������е��õ�˳���.initcall.init���ﺯ ��ָ���˳���йأ���ͬ�ĳ�ʼ�����������ڲ�ͬ���ӽ��У����Ҳ�;��������ǵĵ���˳��

��������ʵ��ִ�к������õĵط�������/init/main.c�ļ���ں˵ĳ�ʼ��ô���������ﻹ������������do_initcalls������ֱ���õ������__initcall_start��__initcall_end�������жϡ�



����(2)ģ�������

��������usb_init�������ڶ��������ǣ���868�е�nousb��ʾʲô?

����֪��C���Ե��˶���֪��nousb��һ����־��ֻ�ǲ�ͬ�ı�־�в�һ���ľ��ʣ������nousb�������������������ں˵�ʱ��ͨ���ں˲���ȥ�� USB��ϵͳ�ģ�Linux�����һ�������Ի������磬������ȥ�������ǽ���USB��һ�ж�ֻ�غ������Լ�����Ҫ��������������һ����˵�ǲ���ȥָ��nousb�İɡ���������ָ����nousb��������ֻ����Թ��˵һ�䡰USB support disabled����Ȼ���˳�usb_init��

����nousb��drivers/usb/core/usb.c�ļ��ж���Ϊ��

����static int nousb; /* Disable USB when built into kernel image */

����module_param_named(autosuspend, usb_autosuspend_delay, int, 0644);

����MODULE_PARM_DESC(autosuspend, "default autosuspend delay");

�������п�֪nousb�Ǹ�ģ�����������ģ����������Ƕ�֪�������ڼ���ģ���ʱ�����ָ��������������ں�������ʱ��ָ��?

������ϵͳ��grub�ļ���Ȼ���ҵ�kernel�У����磺

����kernel /boot/vmlinuz-2.6.18-kdb root=/dev/sda1 ro splash=silent vga=0x314

�������е�root��splash��vga�ȶ���ʾ�ں˲�������ĳһģ�鱻������ں˵�ʱ������ģ���������Ҫ��kernel����ָ������ʽΪ��ģ����.����=ֵ�������磺

����modprobe usbcore autosuspend=2

������Ӧ��kernel�У���Ϊ ��

����usbcore.autosuspend=2

����ͨ�����modinfo -p ${modulename}�����Ե�֪һ��ģ������Щ��������ʹ�á�ͬʱ�������Ѿ����ص��ں����ģ�飬���ǵ�ģ��������о���/sys/module /${modulename}/parameters/Ŀ¼���棬����ʹ�á�echo -n ${value} > /sys/module/${modulename}/parameters/$

����{parm}������������ȥ�޸ġ�

����(3)�ɱ�����ꡣ

��������usb_init�����������������ǣ�pr_info���ʵ����ʹ��?pr_infoֻ��һ����ӡ��Ϣ�Ŀɱ�����꣬printk�ı��壬��include/linux/kernel.h�ﶨ�壺

����242 #define pr_info(fmt,arg...) \

����243 printk(KERN_INFO fmt,##arg)

����99���ISO C��׼��涨�˿ɱ�����꣬�ͺ����﷨���ƣ�����

����#define debug(format, ...) fprintf (stderr, format, __VA_ARGS__)����ġ������ͱ�ʾ�ɱ����������ʱ�����Ǿͻ�����������__VA_ARGS__��GCC���ǻ��Ե���������һЩ����֧�ָ����ӵ���ʽ�����Ը��ɱ����ȡ�����֣�����#define debug(format, args...) fprintf (stderr, format, args)

���������������ǻ����׽���һЩ���ǲ�����pr_info�ȽϽӽ���?���ˡ�##��������Ҫ����Կղ������������Ȼ˵�ǿɱ�������Ǵ��ݿղ���Ҳ���ǿ��Եģ��ռ��Ƕ࣬�༴�ǿգ����������������ͬ��Ҳ���ʺϵġ����û�С�##�������ݿղ�����ʱ�򣬱���debug ("A message");չ����������ַ��������������Ķ��š����������Ӧ�ò���ϲ��������##�����ʹԤ������ȥ���������Ķ��š�



��������usb_init�������������������֮�⣬���µĴ���ֱ����usb�����ֵĳ�ʼ��������������ҪΧ�����Ƿֱ���������������Ϊ����ֻ����ʾ������ַ�����չʾ��ֻ��һ��̬�ȣ����Ծ����������������˰ɡ�

��������ѧϰ��˵����������ѧУ�Ŀ���ѧϰ����������˵���ں�ѧϰ��Ч���û��߻�������Ҫȡ�����������桪�������ۺ�����ע�⣬�����������̵Ĳ��죬���������֮����������˵���������ŵķ��롣

����ǰ������Kernel��ͼ������������֣�˵�Ķ��Ƿ����۵����⣬��ô����Ҫ��Եľ���Ҫ�������ϵ����⡣

�����������ϵ�������Ҫ��������һ����äĿ���������ܹ���������Linux֮ǰ����LinuxΪ���ﻹ˵�����������������Ȳ�������äĿ��ȥ�о��ں˵� Դ���롣��һ�����˻���ü�Ȼ��ѧϰ�ںˣ���ô�ķ�ʱ������ϤLinux�Ļ��������ϴ������˷ѱ����ʱ��͸��顣����������Ȼ���к���ͬ־������͸ɾ� ����������������һ����������������Linus���Ǿ仰��Ҫ�Ȼ�ʹ������

�����ڶ������ǿ־塣���������ô���꣬��Ը��ӵ���������黹���ܻ��������ľ��¸У��������ں�ѧϰ������ǣ���ô�Ӵ��ӵ��ں˴��룬�����������������Կ���!

�����������ֿ־������д��ڣ������Ͼͻ�ȥ�ų���ԽӴ��ں�Դ�룬��Ըȥ�����龰�������Ѽ����ָ����廨���ŵ��ں��鼮�����������ţ����������������ֿ���Ҳ������Ըȥ����ϸ�µ����Դ�롣

�������ʱ���������������Ǵ����ã�����������ܽ�ؽ�㣬����Ů֮���Ժ����������������ж�ã�������Ϊ���ǵ������㹻��ǿ���ǵģ������򺫾ֳ�ѧϰ̬�ȣ����ǻ�Ҫ��ӿ�ֳ�����������ܽ�ؽ��͹���Ůѧϰ��ǿ������

�����б�Ҫ��ǿ��һ�Σ�ѧϰ�ںˣ�����ѧϰ�ں˵�Դ���룬�κ��ں��йص��鼮���ǻ����ںˣ����ֲ������ں˵ġ��ں�Դ�뱾�������õĲο����ϣ������κξ����Ǿ���������ֻ���𵽸��������ã�����Ҳ��Ӧ��ȡ���ں˴���������ѧϰ�����е�������λ��

��������������ȱ�Ĳ��ǽ�Ǯ��������Դ����������һ�ݱ�ֽ�Ͽ�����������ʱ���ҵĵ�һ��Ӧ�ǡ�������һ���Ǹ���Ȼ���������ߣ�Ȼ�����������÷�ʡ�����ͬʱ��Ȼ����һ�ɶ��������޲������������ޱȳ羴�������������ǣ��Ҽ������¿����������XXX��δ��ʽ����֮ʱ��ǰ����ѯ�Ŀͻ��Ѿ����٣���Щ���۹�Ĺ��������ף�˭����Ŀǰ��õĹ�����������󻯵�ռ�о����� Դ��˭���ƿ���δ���Ƹ����򡣡�(Ϊ�˱������������ɣ���������ʹ��XXX�����¥�̵����֡�)��ʱ���������!

������ʵ������ͬ־�Ѿ����ռ��������������Դ����Ҫ�ԣ����������ѧϰ����ͬ־�Ͻ�ϸ�µ�̬��ͬʱ����Ҫ����������Դ��������á�ֻ�������ں�Դ��Ϊ���ģ���ָ���ѧϰ��Դ�ĳ��ڽ��費��ҡ�����ܴﵽ���ֳ������ĸ߶ȣ�����Linux�ں��������������̬��

����ע�⣬����۵���ǰ����˵��ѧϰЧ����Ҫȡ���ڷ����ۺ������������沢��ì�ܣ��������ڲ�ͬ����ϵ����⡣



�����ں��ĵ�

�����ں˴����а����д������ĵ�����Щ�ĵ�����ѧϰ����ں����Ų��ɹ����ļ�ֵ����ס�����κ�ʱ��������������Ŀ�еĵ�λ��Ӧ�ø�����Щ��ʽ���ں˲ο��顣������һЩ�ں�������Ӧ���Ķ����ĵ���

����README

��������ļ����ȼ򵥽�����Linux�ں˵ı�����Ȼ��������������úͱ����ںˣ���󻹸������ǳ�������ʱӦ����ô�졣

����Documentation/Changes����ļ����������������ʹ���ں�����Ҫ����С������б�

����Documentation/CodingStyle����ļ��������ں���ѡ�ı��������д��붼Ӧ���������涨��Ĺ淶��

����Documentation/SubmittingPatches

����Documentation/SubmittingDrivers

����Documentation/SubmitChecklist

�����������ļ�������������ύ����ģ�����SubmittingPatches�����������ύ�����Ĺ��̣�

����SubmittingDrivers��������ν� �豸�����ύ��2.4��2.6�Ȳ�ͬ�汾���ں�����SubmitChecklist���������ύ����֮ǰ��Ҫcheck�Լ��Ĵ���Ӧ�����ص�ĳЩ���

����Documentation/stable_api_nonsense.txt����ļ�������Ϊʲô�ں�û��һ���ȶ����ڲ�API(���û��ռ�Ľӿڡ���ϵͳ���á������ȶ���)�����������Linux�Ŀ�����ѧ������Ҫ�����ڽ�����ƽ̨����������ϵͳת�Ƶ�Linux�Ŀ�������˵Ҳ����Ҫ��

����Documentation/stable_kernel_rules.txt�������ȶ����ں�(stable releases)�����Ĺ����Լ���ν������ύ����Щ�汾��

����Documentation/SecurityBugs

�����ں˿����߶԰�ȫ������ǳ���ע���������Ϊ�Լ����������������⣬���Ը�������ļ��и�������ϵ��ʽ�ύbug���Ա��ܹ������ܿ�Ľ��������⡣

����Documentation/kernel-docs.txt����ļ��о��˺ܶ��ں���ص��ĵ����鼮�����治������֮����

����Documentation/applying-patches.txt����ļ��ش������Ϊ�ں˴򲹶���

����Documentation/bug-hunting����ļ����й�Ѱ�ҡ��ύ������bug�ġ�

����Documentation/HOWTO����ļ���ָ������γ�Ϊһ���ں˿����ߣ�����ѧ�����ͬ�ں˿��������������������ܲ������κι����ں˱�̵ļ���ϸ�ڣ��������ָ��һ�������Щ֪ʶ����ȷ;����



���������鼮

��������ɽ������ʱ��������Щ������΢Ц��

�����й��ں˵��鼮�����ú�ţ�䶰�����ݣ�����ֻ��һЩ�����������ס�˿��顣������5���þ����������(���˸���Ϊ��2+1+2������һ��2��ָ2��ȫ�潲 ���ں˵��飬�м��1ָ1�����������������飬�����2��ָ2���й��ں˾�����ϵͳ���飬���Ƿ��뵽��ĳĳ�����������ͻȻվ�𵥱���ٸߺ���1��1 �� 1���ĳ���?)��

������Linux�ں������ʵ�֡�

�������LKD�������ſ�ʼ��������������̹���ϵͳ���á��жϺ��жϴ�������ں�ͬ����ʱ

����������ڴ������ַ�ռ䡢���Լ����ȷ��棬���ݱȽ�ǳ���׶���������Ϊ���ں��������ȱ�

���������鼮�����˵��д��飬����!

�������������Linux�ںˡ�

�������ULK�������LKD�����ݲ������롢�����治�㣬ULKҪ����ȫ��öࡣ

����ǰ����������һ��������죬һ��ȫ�����롣

������Linux�豸��������

�������LDD�����������߶�Ҫ����һ���ˡ�

�������������Linux�����ڴ����

�������LVMM����һ������Linux�����ڴ������Ƶ��顣�����ϣ��������о�Linux���ڴ����

������ϵͳ����ϸ���ж��Ȿ����������õ�ѡ��

�������������LINUX������Ļ��

����һ������������ϵͳʵ�ֵ��飬ͨ���Ȿ�飬���ǿ����˽⵽Linux�ں������ʵ�ָ��ӵ����繦�ܵġ�(���������£������г��������������ĵģ����ǲ��������ҽ�����ȥ�����ǵ����İ棬�����еķ����ʵ��̫??�ˣ��Ǻ�)

������5������в��أ����������ͼ��չʾ��������ǡ�ô����˸���һֱ���ŵ��ں�ѧϰ����������ͨ��LKD��ULK�˽��ں˵����ʵ���ص㣬���ں��и�����ȫ�ֵ���ʶ����⣬Ȼ��ɷ�Ϊ������·�������������������������LDD�����ϣ�����ں˲��Ƿ�����̸�����и��������⣬�����ѡ��һ���Լ�����Ȥ����ϵͳ����ϸ�������Ĵ��룬�����ĵط���ͨ���������ʼ��б����ֱ�ӷ�Email��maintainer��̵�;��Ū��������ù��ҹ�������������������ͬ�����жϵȵ��ں˵ĺܶ����Ҳͬ����ǳ��˽⣬�׻�˵��һͨ���ͨ�������������Ȼ�������ѡ���о������ڴ����������磬���������������������ѧϰ�������������ϵͳ���ܾ�û����ô�õ������ˡ�

�����ں�����

����������꣬������վ�ǳ����Ȼ𣬲����������Ǳ�������

����Linux����һ�����ƾ�������һ�������Ž����ڶ�ʹ���ߺͿ����ߵ�����������Ŀ������ṩ���ƾ������ںˡ��ں��������������ں��ʼ��б�(Linux Kernel Mailing List��LKML)�����ǿ�����http://vger.kernel.org/vger-lists.html#linux-kernel���濴����������ʼ��б��ϸ�ڡ�

�����ں��ʼ��б�������ܴ�ÿ�춼�м�������Ϣ�������Ǵ�ţ�ǵ�ս����Сţ�ǵ����ã��κ�һ���ں˿����߶����Դ��������ǳ������LKML���������ϵͳҲ���Լ��������ʼ��б���Э�����ԵĿ�������������USB��ϵͳ���ʼ��б������http://www.linux-usb.org/mailing.html ���涩�ġ�

��������������Դ

���������ں��ʼ��б����кܶ���������̳����վֵ�����Ǿ�����ע������Ҫ֪���������ϲ��������޺ͷ�㣬Ҳ������Ϭ����ͺ��ֳ���http://www.kernel.org/ ����ͨ�������վ�������ں˵�Դ����Ͳ����������ں�bug�ȡ�http://kerneltrap.org Linux��BSD�ں˵ļ������š����ûʱ�����LKML����ô�������kerneltrap�Ǹ������⡣http://lwn.net/ Linux weekly news��������1997��׵�һ��Linux����վ�㡣http://zh-kernel.org/mailman/listinfo/linux-kernel �����ں˿����������ʼ��б������Ծ�źܶ��ں˿�������Ļ��ˣ�����Herbert  Xu,��Mingming Cao��Bryan Wu�ȡ�
