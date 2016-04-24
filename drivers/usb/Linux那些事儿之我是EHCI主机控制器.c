// Linux  ��Щ�¶�֮���� EHCI����������                                                                                                                    
//                                                                                                                                                         
//                                                                                                                                                         
//                                                                                                                                                         
//                                                                                                                                                         
// Linux��Щ�¶�                                                                                                                                           
// ϵ�д���                                                                                                                                                
// ֮                                                                                                                                                      
// ����EHCI                                                                                                                                                
// ��ԭ��Ϊblog.csdn.net/fudan_abc �ϵġ�linux ��Щ�¶�֮����EHCI�������������µĻ�������������Ŀ���                                                      
// ���������ͣ�Ҳ����email ��ilttv.cn@gmail.com                                                                                                            
// �� 1  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                                
// Ŀ¼                                                                                                                                                    
// Ŀ¼..................................................................................................................................................2 
// ����..................................................................................................................................................3 
// �ӿ���ϵ...........................................................................................................................................3    
// ��·................................................................................................................................................10  
// pci match  �� probe........................................................................................................................12           
// data structure of ehci driver and device ..........................................................................................14                   
// 2008 �����һ��ѩ........................................................................................................................18             
// �� 2  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                                
// ����                                                                                                                                                    
// ת��֮�䣬���� 2008 �꣬��ף���������֣�ϣ���µ�һ��������������������ǡ��þ�                                                                        
// û��д�ˣ�һ��ԭ�����ڣ���Ϊһ�� PHD ѧ��������Ҫ��һЩ�� paperд paper�����£���                                                                       
// һ��ԭ������Լ�̫���ˡ�����һ���������ֵ�д������ʵ�������塣��ʱ�˿̣�����                                                                        
// ���Խ�����ʫһ�ף���Ʈ�����ӣ����ϴ��ɷ򡣺��ϳ��������£������ʹ�һ֦����������                                                                        
// �С�                                                                                                                                                    
// ������Ҫ�� linux ehci host controller�ⲿ�ֵĴ��룬̸̸���Լ���⡣����֮�������ָ����                                                                 
// �ο����ϣ�ehci spec �� linux-2.6.22.1 �ںˡ��Ҿ����������룬���������������                                                                            
// ���ڿ�˵��Ҫ���� usb ���䣬����һ�� usb host controller, usb �����������������ϵͳ��                                                                   
// USB  �豸�����໥�������������� USB  �豸��ϵͳ��������ͨ������������еͲ��                                                                         
// ϸ�ڡ�                                                                                                                                                  
// һ�� usb2.0��������ͼ��ʾ                                                                                                                               
//                                                                                                                                                         
// usb 2.0 �����˵���(ls)��ȫ��(fs)������(hs)���䡣EHCI����֧�ָ��ٴ��䣬���������뻹Ҫ                                                                    
// ��һ�� companion HC����(UHCI)��֧�ֵ��ٺ�ȫ���豸�����ʱ�����ģ�                                                                                       
// 1), fs/ls  �豸���뵽 root hub port,���� companion HC(uhci/ohci)���ֲ������豸;                                                                         
// 2),fs/ls  �豸���뵽 usb 2.0 hub(not root hub),��ô��ehci  ͨ�� split transaction�� transanction                                                        
// translation(tt)֧�� fs/ls  �豸��                                                                                                                       
// ���磬��һ�� usb �豸���� root hub port ʱ����Ҫ��һ�� routing �����顣���е� root hub port                                                             
// Ĭ���Ǳ� EHCIռ�еģ����ԣ�EHCI�Ͳ���� usb �豸ͨ�ţ����ǲ��� hs�豸������Ǻ�                                                                         
// ˵��������ǣ�EHCI�ͷ������ port ��ռ��Ȩ���ø� companion HC(uhci/ohci)ȥ����                                                                        
// �ӿ���ϵ                                                                                                                                                
// EHCI������һ��PCI�豸�����ǿ��� lspciһ�¿�����                                                                                                         
// 00:1a:7 USB Controller: Intel Corporation USB2 EHCI Controller #1 (rev 03)                                                                              
// �� 3  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                                
// ��������ΧӲ���򽻵������԰������� in(out)ָ��ݸ���ΧӲ���������԰����ݴ��䵽 cpu                                                                    
// ����ΧӲ��������ڴ�����ȥ����Щ���Ǽ������Ӳ���Ľӿڡ����μ� ldd3 �� 9�£�                                                                            
// ��ô���ǵĳ�������� EHCI ��ϵ�������أ�EHCI�����������ӿڿռ䡣��ͼ                                                                                    
//                                                                                                                                                         
// ��Ϊһ������Ա�����ǹ��ĵ�������ڴ����ж�/д��Щ�ط������ݡ������ԵĶ����϶��� LDD3                                                                    
// д����ã��ҾͲ�׸���ˡ�                                                                                                                                
// 1��pci configuration space.  (ldd3 �� 12��)                                                                                                             
// ����EHCI��һ��PCI�豸����������ϵͳ���ö�ٺ� PCI�ĵ�Դ����                                                                                           
// �� x86 Ϊ������ȡ PCI ������·�������ġ�����Ҫ��ȡ PCI �����ϵ�ַΪ add������Ϊ 4 ��                                                                    
// �ֽڵ����ݡ�                                                                                                                                            
//                 outl(add, 0xcf8); \\ �Ȱ�add��out����ַΪ 0xcf8�ĵط�                                                                                   
//                 value = inl(0xcfc); \\ Ȼ���ٶ�ȡ 0xcfc������                                                                                           
// �����ҵ���һ�γ��򣬴�ҿ�������һ�¡�                                                                                                                  
// name: pci.c  //                                                                                                                                      
//#include <stdio.h>                                                                                                                                      
//#include <assert.h>                                                                                                                                     
//#include <sys/io.h>                                                                                                                                     
                                                                                                                                                        
#define IO_PORTS1         1       // ioport <= 0x3ff //                                                                                                 
#define IO_PORTS2         2       // ioport >0x3ff && ioport < 0xffff //                                                                                
#define IO_PERMOFF        0                                                                                                                             
#define IO_PERMON         1                                                                                                                             
#define IO_PERMON2        3                                                                                                                             
#define RW_DELAY    10000 //delay 100000 microseconds for reading and writin                                                                            
g I/O ports. //                                                                                                                                         
#ifndef BOOL                                                                                                                                            
�� 4  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                                
typedef unsigned char BOOL;                                                                                                                             
#endif                                                                                                                                                  
                                                                                                                                                        
#ifndef BYTE                                                                                                                                            
typedef unsigned char   BYTE;                                                                                                                           
#endif                                                                                                                                                  
                                                                                                                                                        
#ifndef DWORD                                                                                                                                           
typedef unsigned long   DWORD;                                                                                                                          
#endif                                                                                                                                                  
                                                                                                                                                        
#ifndef INT                                                                                                                                             
typedef unsigned int INT;                                                                                                                               
#endif                                                                                                                                                  
                                                                                                                                                        
#ifndef ULONG                                                                                                                                           
typedef unsigned long   ULONG;                                                                                                                          
#endif                                                                                                                                                  
                                                                                                                                                        
#ifndef WORD                                                                                                                                            
typedef unsigned short  WORD;                                                                                                                           
#endif                                                                                                                                                  
//                                                                                                                                                      
// ** Function : Write the value of the specified I/O port by giving the length and th                                                                     
// e                                                                                                                                                       
// **            starting address.                                                                                                                         
// ** Parameter: PortAddr: the port address                                                                                                                
// **            PortVal : the value to set                                                                                                                
// **            size    : size = 1 for reading 1 byte, 2 for word, 4 for double words                                                                     
// ** Return   : 1 returned if success, or  0  returned                                                                                                    
//                                                                                                                                                      
BOOL SetPortVal(WORD PortAddr, DWORD PortVal, BYTE size)                                                                                                
{                                                                                                                                                       
    BOOL  Ret     = 0;                                                                                                                                  
    INT   tmpRet  = 0;                                                                                                                                  
    ULONG numperm = 1;                                                                                                                                  
    INT privilege = 0;                                                                                                                                  
    assert(PortAddr>0);                                                                                                                                 
    if(PortAddr <=0x3ff)                                                                                                                                
    {                                                                                                                                                   
        tmpRet = ioperm((ULONG)PortAddr, numperm, IO_PERMON);                                                                                           
        privilege = IO_PORTS1;                                                                                                                          
    }                                                                                                                                                   
// �� 5  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                                
    else if( PortAddr > 0x3ff)                                                                                                                          
    {                                                                                                                                                   
        tmpRet = iopl(IO_PERMON2);                                                                                                                      
        privilege = IO_PORTS2;                                                                                                                          
    }                                                                                                                                                   
    else                                                                                                                                                
        return Ret;                                                                                                                                     
    if(tmpRet<0)                                                                                                                                        
    {                                                                                                                                                   
        fprintf(stderr, "can't set the io port permission for setting ! ");                                                                             
        return Ret;                                                                                                                                     
    }                                                                                                                                                   
    else                                                                                                                                                
    {                                                                                                                                                   
        switch(size)                                                                                                                                    
        {                                                                                                                                               
            case 1: //write one byte to the port //                                                                                                     
                outb(PortVal, PortAddr);                                                                                                                
                break;                                                                                                                                  
           case 2: //write one word to the port //                                                                                                      
                outw(PortVal, PortAddr);                                                                                                                
                break;                                                                                                                                  
            case 4: //write double words to the port //                                                                                                 
                outl(PortVal, PortAddr);                                                                                                                
                break;                                                                                                                                  
            default:                                                                                                                                    
                Ret = 0;                                                                                                                                
                break;                                                                                                                                  
        }                                                                                                                                               
        usleep(RW_DELAY);                                                                                                                               
        Ret = 1;                                                                                                                                        
    }                                                                                                                                                   
    if( privilege == IO_PORTS1 )                                                                                                                        
        ioperm((ULONG)PortAddr, numperm, IO_PERMOFF);                                                                                                   
    else if(privilege == IO_PORTS2 )                                                                                                                    
        iopl(IO_PERMOFF);                                                                                                                               
    return Ret;                                                                                                                                         
}                                                                                                                                                       
                                                                                                                                                        
//                                                                                                                                                      
// ** Function : Read the value of the specified I/O port by giving the lenght and th                                                                      
// e                                                                                                                                                       
// **            starting address.                                                                                                                         
// �� 6  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                                
// ** Parameter: PortAddr : the port address                                                                                                               
// **            PortVal  : value from port                                                                                                                
// **            size     : size = 1 for reading 1 byte, 2 for word, 4 for double words                                                                    
// ** Return   : 1 returned if success, or 0 returned.                                                                                                     
// //                                                                                                                                                      
BOOL GetPortVal(WORD PortAddr, DWORD * PortVal, BYTE size)                                                                                              
{                                                                                                                                                       
    BOOL  Ret     = 0;                                                                                                                                  
    int   tmpRet  = 0;                                                                                                                                  
    unsigned long numperm = 1;                                                                                                                          
    int privilege = 0;                                                                                                                                  
    assert(PortAddr>0);                                                                                                                                 
    assert(PortVal!=NULL);                                                                                                                              
    if(PortAddr <=0x3ff)                                                                                                                                
    {                                                                                                                                                   
        tmpRet = ioperm((unsigned long)PortAddr, numperm, IO_PERMON);                                                                                   
        privilege = IO_PORTS1;                                                                                                                          
    }                                                                                                                                                   
    else if( PortAddr > 0x3ff)                                                                                                                          
    {                                                                                                                                                   
        tmpRet = iopl(IO_PERMON2);                                                                                                                      
        privilege = IO_PORTS2;                                                                                                                          
    }                                                                                                                                                   
    else                                                                                                                                                
        return Ret;                                                                                                                                     
    if(tmpRet<0)                                                                                                                                        
    {                                                                                                                                                   
        fprintf(stderr, "can't set the io port permission for reading ! ");                                                                             
        return Ret;                                                                                                                                     
    }                                                                                                                                                   
    else                                                                                                                                                
    {                                                                                                                                                   
        switch(size)                                                                                                                                    
        {                                                                                                                                               
            case 1: //read one byte from the port //                                                                                                    
                *PortVal = inb(PortAddr);                                                                                                               
                break;                                                                                                                                  
            case 2: //read one word from the port //                                                                                                    
                *PortVal = inw(PortAddr);                                                                                                               
                break;                                                                                                                                  
            case 4: //read double words from the port //                                                                                                
                *PortVal = inl(PortAddr);                                                                                                               
                break;                                                                                                                                  
            default:                                                                                                                                    
// �� 7  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                                
                Ret = 0;                                                                                                                                
                break;                                                                                                                                  
        }                                                                                                                                               
        usleep(RW_DELAY);                                                                                                                               
        Ret = 1;                                                                                                                                        
    }                                                                                                                                                   
                                                                                                                                                        
    if( privilege == IO_PORTS1 )                                                                                                                        
        ioperm( (unsigned long)PortAddr, numperm, IO_PERMOFF );                                                                                         
    else if( privilege == IO_PORTS2 )                                                                                                                   
        iopl(IO_PERMOFF);                                                                                                                               
        return Ret;                                                                                                                                     
}                                                                                                                                                       
                                                                                                                                                        
int main (int argc, char * argv[])                                                                                                                      
{                                                                                                                                                       
    WORD add_port = 0xcf8;                                                                                                                              
    WORD data_port = 0xcfc;                                                                                                                             
    DWORD addr = 0x80000000;                                                                                                                            
    DWORD port_value;                                                                                                                                   
    BYTE size = 4;                                                                                                                                      
    int input;                                                                                                                                          
    printf("Please select the option number as follow: ");                                                                                              
    printf("1--bus 0:dev:0 fun:0 as address 0x80000000 ");                                                                                              
    printf("2--bus 0:dev:1 fun:0 as address 0x80000800 ");                                                                                              
    printf("3--input your own defined address value: ");                                                                                                
    scanf("%d",&input);                                                                                                                                 
    switch(input)                                                                                                                                       
    {                                                                                                                                                   
           case 1:                                                                                                                                      
                  addr=0x80000000;                                                                                                                      
                  break;                                                                                                                                
           case 2:                                                                                                                                      
                  addr=0x80000800;                                                                                                                      
                  break;                                                                                                                                
           case 3:                                                                                                                                      
                  printf("please input the 32 bits address in Hex format(such as 8000                                                                   
7800): ");                                                                                                                                              
                  scanf ("%x", &addr);                                                                                                                  
    break;                                                                                                                                              
           default:                                                                                                                                     
                  printf("input invalid option num, exit program. ");                                                                                   
                  return -1;                                                                                                                            
    }                                                                                                                                                   
//�� 8  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                                
    printf ("The addr is :%X ", addr);                                                                                                                  
    printf ("The add_port is : %X ", add_port);                                                                                                         
    printf ("The data_port is : %X ", data_port);                                                                                                       
    if (SetPortVal(add_port, addr, size))                                                                                                               
    {                                                                                                                                                   
           if (GetPortVal(data_port, &port_value, size))                                                                                                
           {                                                                                                                                            
                  printf("port value is :%08X ", port_value);                                                                                           
                  return 0;                                                                                                                             
           }                                                                                                                                            
    }                                                                                                                                                   
    return -1;                                                                                                                                          
}                                                                                                                                                       
                                                                                                                                                        
// ��ӡ������������(1)�� lspci -xxx ���������(2)EHCI spec 2.1�µ����ݶ���һ�¡�                                                                           
// ���ˣ�����������������ô֪��PCI������EHCI�ĵ�ַ add��lspci���Կ�������PCI�豸��                                                                         
// ��ַ�����ȣ�EHCI ������û������������� PCI �豸�� PCI ����ö��ʱ�ͱ�̽�⵽�ˣ���ʱ                                                                     
// �����ͱ������˵�ַ��ÿ�� PCI ������һ�����ߺ�, һ���豸��, һ�����ܺű�ʶ�š�����                                                                       
// 00:1a:7��00���ߺţ�1a�豸�ţ�7���ܺš���Щ��������˶�һ�޶��� ID��ID �͵�ַ��ת                                                                        
// ����ϵ�������ģ�                                                                                                                                        
//                                                                                                                                                         
// ����ֻҪ ID����֪��������ĵ�ַ��Ȼ��Ϳ��Զ�д PCI�Ĵ��������ݡ�������Կ���                                                                           
// pci_read()��pci_write()   \\arch\i386\pci\common.c                                                                                                      
// �����ݣ��������и������⡣                                                                                                                            
// 2��regster space.                                                                                                                                       
// ���ǻ����ڵ� i/o �Ĵ��������� i/o �ڴ档��������� Capability Registers �� Operational                                                                  
// Registers�����ǿ��Զ�ȡ/proc/iomem ���� io �ڴ�ķ�����������ǿ��Կ��� ehci�ĵ�ַ                                                                      
// �� fe226400-fe2267ff ������ڴ治����ֱ�Ӷ�д����Ҫ���� ioremap ������                                                                                  
// ioremap_nocache��Ӱ��������ַ����ʹ�á�                                                                                                               
// ��д��һ�γ��򡣴�ҿ�������һ�¡�                                                                                                                      
    //#include <asm/io.h>                                                                                                                                 
static int hello_init(void)                                                                                                                             
{                                                                                                                                                       
        unsigned long  port_value, mem_value;                                                                                                           
        void __iomem *add;                                                                                                                              
        int i;                                                                                                                                          
        printk(KERN_ALERT "Hello, world ");                                                                                                             
        add = ioremap(0xfe226400, 0x400);                                                                                                               
        for(i = 0; i < 100; i++){                                                                                                                       
//�� 9  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                                
                mem_value = ioread32(add+i*4);                                                                                                          
                printk("%08X mem value is :%08X ", add+i*4, mem_value);                                                                                 
        }                                                                                                                                               
        iounmap(add);                                                                                                                                   
        return 0;                                                                                                                                       
}                                                                                                                                                       
                                                                                                                                                        
// �����ǻ��� ldd3 ���Ǹ���򵥵�ģ�� hello.ko �ĵġ���Ҫ��Ϊ�˿������ں˿ռ����С����                                                                    
// ���԰Ѵ�ӡ������������ ehci spec 2.2����һ�¡�                                                                                                          
// 3��Schedule Interface Space.                                                                                                                            
// ���������ͨ���ڴ档����ֱ�ӾͿ��Է�������                                                                                                              
// ��·                                                                                                                                                    
// ��Ի������·���ơ���ȷ��ʲô����������·���������椵���·����ǰ���²��绨Ǯ���¡�                                                                      
// ���齫�д��齫����·���ٳ������ٷ��ڣ�������ܶ෢�ơ��Ǽ����Ǽʵ���·��linux Ҳ                                                                        
// �� linux ����·�����ν��Ĺ�����һ�θ������ǣ����䲻�����⣬��߲��Ǿ��룬�� cai                                                                       
// ���С�                                                                                                                                                  
// ���ǲ������� modprobe ehci-hcd  ֮������ʲô���顣ehci-hcd ��һ���������򣬲�֪��                                                                     
// �ǲ��ǵ����� sysfs ��̸�۹��豸ģ�͡���������Ҫ��������� bus �ϣ�һ�����豸 device                                                                     
// ����һ�������� driver����                                                                                                                           
// ÿ��������һ�� bus ע��һ������ driverʱ����·�������ģ�                                                                                                
// driver_register(struct device_driver * drv)  -> bus_add_driver() -> driver_attach() ->                                                                  
// bus_for_each_dev(drv->bus, NULL, drv, __driver_attach);                                                                                                 
// bus_for_each_dev ���������������е� device��ִ��һ��__driver_attach()�����ܲ��ܽ�����                                                                   
// ����(attach)��ĳ���豸��ȥ��                                                                                                                            
__driver_attach()                                                                                                                                       
          ->driver_probe_device()                                                                                                                       
                  ->drv->bus->match(dev, drv), // ���� bus�� match ������ �� device�� driverƥ��ƥ                                                      
//�䡣���ƥ���ϣ�                                                                                                                                        
                                                                           //����ִ��really_probe()��                                                     
                  ->really_probe()                                                                                                                      
                                ->driver->probe()��(��� bus->probe �ǿգ������ bus->probe)                                                            
                                                                                                                                                        
//��ÿ��������һ�� bus���һ��Ӳ��ʱʱ����·�������ģ�                                                                                                    
device_add()                                                                                                                                            
             \\ device_add  ���кܶ����kobject��ע��sysfs���γ�Ӳ��hiberarchy�ṹ�Ĵ��롣                                                              
             ����������ˣ��Ȼ�ͷȥ�ο��ο�"���� sysfs"                                                                                                 
            ->bus_attach_device() -> device_attach() ->bus_for_each_drv()                                                                               
 bus_for_each_drv �� bus_for_each_dev ���ƣ����������������е� driver��ִ��һ��                                                                         
__device_attach()�����ܲ��ܽ��豸����(attach)��ĳ���ѵǼǵ�������ȥ��                                                                                   
 __device_attach()                                                                                                                                      
               ->driver_probe_device() //����������һ��                                                                                                 
// �� 10  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                               
// �ܽ�һЩ��һ�仰��ע��һ��ĳ�� bus �����������Ȱ������Լ����뵽 bus ����������ȥ��                                                                      
// �ڴ� bus ���豸������һһѰ�ң�����û���Լ����Թ����ϵ��豸���ҵ��� probe���ٰѶ�                                                                       
// �� bind ��������֮������豸����Ҳ��һ���ġ�                                                                                                            
// �ðɣ����ǻ��ǿ��� modprobe ehci-hcd ������顣һ�дӴ˿�ʼ��                                                                                           
// module_init(ehci_hcd_init);                                                                                                                             
// ���ǰѲ���Ҫ��Ԥ�������ȥ����ehci_hcd_init ���£�                                                                                                    
static int __init ehci_hcd_init(void)                                                                                                                   
{                                                                                                                                                       
 int retval = 0;                                                                                                                                        
                                                                                                                                                        
   pr_debug("%s: block sizes: qh %Zd qtd %Zd itd %Zd sitd %Zd ",                                                                                        
   hcd_name,                                                                                                                                            
   sizeof(struct ehci_qh), sizeof(struct ehci_qtd),                                                                                                     
   sizeof(struct ehci_itd), sizeof(struct ehci_sitd));                                                                                                  
                                                                                                                                                        
   retval = pci_register_driver(&PCI_DRIVER);                                                                                                           
   if (retval < 0) {                                                                                                                                    
         return retval;                                                                                                                                 
   }                                                                                                                                                    
   if (retval < 0) {                                                                                                                                    
       platform_driver_unregister(&PLATFORM_DRIVER);                                                                                                    
       pci_unregister_driver(&PCI_DRIVER);                                                                                                              
       return retval;                                                                                                                                   
   }                                                                                                                                                    
 }                                                                                                                                                      
                                                                                                                                                        
PCI_DRIVER ��һ���꣬#define PCI_DRIVER  ehci_pci_driver��                                                                                              
static struct pci_driver ehci_pci_driver = {                                                                                                            
    .name =        (char *) hcd_name,                                                                                                                   
    .id_table =    pci_ids,                                                                                                                             
                                                                                                                                                        
    .probe =    usb_hcd_pci_probe,                                                                                                                      
    .remove =    usb_hcd_pci_remove,                                                                                                                    
                                                                                                                                                        
#ifdef    CONFIG_PM                                                                                                                                     
    .suspend =    usb_hcd_pci_suspend,                                                                                                                  
    .resume =    usb_hcd_pci_resume,                                                                                                                    
#endif                                                                                                                                                  
    .shutdown =     usb_hcd_pci_shutdown,                                                                                                               
};                                                                                                                                                      
                                                                                                                                                        
ehci_hcd_init �ܼ򵥾��ǵ����� pci_register_driver()������__pci_register_driver()��                                                                     
int __pci_register_driver(struct pci_driver *drv, struct module *owner,                                                                                 
              const char *mod_name)                                                                                                                     
//�� 11  ҳ �� 22 ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                                 
{                                                                                                                                                       
    int error;                                                                                                                                          
                                                                                                                                                        
    // initialize common driver fields //                                                                                                               
    drv->driver.name = drv->name;                                                                                                                       
    drv->driver.bus = &pci_bus_type;                                                                                                                    
    drv->driver.owner = owner;                                                                                                                          
    drv->driver.mod_name = mod_name;                                                                                                                    
    drv->driver.kobj.ktype = &pci_driver_kobj_type;                                                                                                     
                                                                                                                                                        
    spin_lock_init(&drv->dynids.lock);                                                                                                                  
    INIT_LIST_HEAD(&drv->dynids.list);                                                                                                                  
                                                                                                                                                        
    // register with core //                                                                                                                            
    error = driver_register(&drv->driver);                                                                                                              
    if (error)                                                                                                                                          
        return error;                                                                                                                                   
                                                                                                                                                        
    error = pci_create_newid_file(drv);                                                                                                                 
    if (error)                                                                                                                                          
        driver_unregister(&drv->driver);                                                                                                                
                                                                                                                                                        
    return error;                                                                                                                                       
}                                                                                                                                                       
// driver_register(struct device_driver * drv)����ǰ�潲���ˣ����� linux ����·�������ǿ��� pci                                                            
// ���ߵ� match, probe ������ʲô���İɡ�                                                                                                                  
// pci match �� probe                                                                                                                                      
// pci_bus_type �������£�                                                                                                                                 
struct bus_type pci_bus_type = {                                                                                                                        
    .name        = "pci",                                                                                                                               
    .match        = pci_bus_match,                                                                                                                      
    .uevent        = pci_uevent,                                                                                                                        
    .probe        = pci_device_probe,                                                                                                                   
    .remove        = pci_device_remove,                                                                                                                 
    .suspend    = pci_device_suspend,                                                                                                                   
    .suspend_late    = pci_device_suspend_late,                                                                                                         
    .resume_early    = pci_device_resume_early,                                                                                                         
    .resume        = pci_device_resume,                                                                                                                 
    .shutdown    = pci_device_shutdown,                                                                                                                 
    .dev_attrs    = pci_dev_attrs,                                                                                                                      
};                                                                                                                                                      
//�� 12  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                               
static int pci_bus_match(struct device *dev, struct device_driver *drv)                                                                                 
{                                                                                                                                                       
    struct pci_dev *pci_dev = to_pci_dev(dev);                                                                                                          
    struct pci_driver *pci_drv = to_pci_driver(drv);                                                                                                    
    const struct pci_device_id *found_id;                                                                                                               
                                                                                                                                                        
    found_id = pci_match_device(pci_drv, pci_dev);                                                                                                      
    if (found_id)                                                                                                                                       
        return 1;                                                                                                                                       
                                                                                                                                                        
    return 0;                                                                                                                                           
}                                                                                                                                                       
//�ܵ���˵���ж�һ���豸�������Ƿ�ƥ�䣬�ǿ��豸���������Ƿ��������֧�ֵ�һ����                                                                          
pci_match_device()�ֱ��� driver->dynid ��driver->id_table �������б� ( ��һϵ�е�                                                                       
pci_device_id ����)������ҡ��ҵ��򷵻�����豸�� pci_device_id��(�����Ƚ�һ��                                                                          
pci_bus_type->match  �� usb_bus_type->match)                                                                                                            
struct pci_device_id {                                                                                                                                  
    __u32 vendor, device;        // Vendor and device ID or PCI_ANY_ID//                                                                                
    __u32 subvendor, subdevice;    // Subsystem ID's or PCI_ANY_ID //                                                                                   
    __u32 class, class_mask;    // (class,subclass,prog-if) triplet //                                                                                  
    kernel_ulong_t driver_data;    // Data private to the driver //                                                                                     
};                                                                                                                                                      
ע�⣬pci_device_id->driver_data ָ����ÿ�� pci �豸���������е����ݽṹ������ ehci ��                                                                  
˵��.driver_data = (unsigned long) &ehci_pci_hc_driver��                                                                                                
������ǣ�                                                                                                                                              
static int pci_device_probe(struct device * dev)                                                                                                        
{                                                                                                                                                       
    int error = 0;                                                                                                                                      
    struct pci_driver *drv;                                                                                                                             
    struct pci_dev *pci_dev;                                                                                                                            
                                                                                                                                                        
    drv = to_pci_driver(dev->driver);                                                                                                                   
    pci_dev = to_pci_dev(dev);                                                                                                                          
    pci_dev_get(pci_dev);                                                                                                                               
    error = __pci_device_probe(drv, pci_dev);                                                                                                           
    if (error)                                                                                                                                          
        pci_dev_put(pci_dev);                                                                                                                           
                                                                                                                                                        
    return error;                                                                                                                                       
}                                                                                                                                                       
                                                                                                                                                        
pci_device_probe() ---> __pci_device_probe() ---> pci_call_probe() ---> ( pci_driver->probe() )                                                         
�� ehci_pci_driver->probe = usb_hcd_pci_probe()����pci_device_probe ���������������һ��                                                                
// ����������ơ�����������������ǧ����࣬�������Ƶ� usb �ˡ�                                                                                           
// �� 13  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                               
//                                                                                                                                                         
// data structure of ehci driver and device                                                                                                                
// ����"��ְ"�ˣ�kde4 �����ˣ������Ҽ������ǣ�Ӣ��־���������и����ˣ��ⲿ���س���8                                                                        
// ���С˵������Ҫ���뾫�ʵĴ��֡�¬�Ƶ����˾�����Σ��ۺ���Զ���ĸ��Ը�������ȫ                                                                        
// ��ͬ���ˣ�˭�Ǻã�˭�ǻ���˭�Ƕԣ�˭�Ǵ���ν������                                                                                                    
// �����ϻ�˵��usb_hcd_pci_probe ���������"���� UHCI"��Ҳ�����ۣ��������밴���ҵ�˼                                                                       
// ·д��ȥ��                                                                                                                                              
//      46 //*                                                                                                                                             
//      47  * usb_hcd_pci_probe - initialize PCI-based HCDs                                                                                                
//      48  * @dev: USB Host Controller being probed                                                                                                       
//      49  * @id: pci hotplug id connecting controller to HCD framework                                                                                   
//      50  * Context: !in_interrupt()                                                                                                                     
//      51  *                                                                                                                                              
//      52  * Allocates basic PCI resources for this USB host controller, and                                                                              
//      53  * then invokes the start() method for the HCD associated with it                                                                               
//      54  * through the hotplug entry's driver_data.                                                                                                     
//      55  *                                                                                                                                              
//      56  * Store this function in the HCD's struct pci_driver as probe().                                                                               
     57  //                                                                                                                                             
     58 int usb_hcd_pci_probe (struct pci_dev *dev, const struct pci_device_id *id)                                                                     
     59 {                                                                                                                                               
     60         struct hc_driver        *driver;                                                                                                        
     61         struct usb_hcd          *hcd;                                                                                                           
     62         int                     retval;                                                                                                         
     63                                                                                                                                                 
     64         if (usb_disabled())                                                                                                                     
     65                 return -ENODEV;                                                                                                                 
     66                                                                                                                                                 
     67         if (!id || !(driver = (struct hc_driver *) id->driver_data))                                                                            
     68                 return -EINVAL;                                                                                                                 
     69                                                                                                                                                 
     70         if (pci_enable_device (dev) < 0)                                                                                                        
     71                 return -ENODEV;                                                                                                                 
     72         dev->current_state = PCI_D0;                                                                                                            
     73         dev->dev.power.power_state = PMSG_ON;                                                                                                   
     74                                                                                                                                                 
     75         if (!dev->irq) {                                                                                                                        
     76                 dev_err (&dev->dev,                                                                                                             
     77                         "Found HC with no IRQ.  Check BIOS/PCI %s setup! ",                                                                     
     78                         pci_name(dev));                                                                                                         
     79                 retval = -ENODEV;                                                                                                               
//�� 14  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                               
     80                 goto err1;                                                                                                                      
     81         }                                                                                                                                       
     82                                                                                                                                                 
     83         hcd = usb_create_hcd (driver, &dev->dev, pci_name(dev));                                                                                
     84         if (!hcd) {                                                                                                                             
     85                 retval = -ENOMEM;                                                                                                               
     86                 goto err1;                                                                                                                      
     87         }                                                                                                                                       
     88                                                                                                                                                 
     89         if (driver->flags & HCD_MEMORY) {       // EHCI, OHCI                                                                                   
     90                 hcd->rsrc_start = pci_resource_start (dev, 0);                                                                                  
     91                 hcd->rsrc_len = pci_resource_len (dev, 0);                                                                                      
     92                 if (!request_mem_region (hcd->rsrc_start, hcd->rsrc_len,                                                                        
     93                                 driver->description)) {                                                                                         
     94                         dev_dbg (&dev->dev, "controller already in use ");                                                                      
     95                         retval = -EBUSY;                                                                                                        
     96                         goto err2;                                                                                                              
     97                 }                                                                                                                               
     98                 hcd->regs = ioremap_nocache (hcd->rsrc_start, hcd->rsrc_len);                                                                   
     99                 if (hcd->regs == NULL) {                                                                                                        
    100                         dev_dbg (&dev->dev, "error mapping memory ");                                                                           
    101                         retval = -EFAULT;                                                                                                       
    102                         goto err3;                                                                                                              
    103                 }                                                                                                                               
    104                                                                                                                                                 
    105         } else {                                // UHCI                                                                                         
    106                 int     region;                                                                                                                 
    107                                                                                                                                                 
    108                 for (region = 0; region < PCI_ROM_RESOURCE; region++) {                                                                         
    109                         if (!(pci_resource_flags (dev, region) &                                                                                
    110                                         IORESOURCE_IO))                                                                                         
    111                                 continue;                                                                                                       
    112                                                                                                                                                 
    113                         hcd->rsrc_start = pci_resource_start (dev, region);                                                                     
    114                         hcd->rsrc_len = pci_resource_len (dev, region);                                                                         
    115                         if (request_region (hcd->rsrc_start, hcd->rsrc_len,                                                                     
    116                                         driver->description))                                                                                   
    117                                 break;                                                                                                          
    118                 }                                                                                                                               
    119                 if (region == PCI_ROM_RESOURCE) {                                                                                               
    120                         dev_dbg (&dev->dev, "no i/o regions available ");                                                                       
    121                         retval = -EBUSY;                                                                                                        
    122                         goto err1;                                                                                                              
    123                 }                                                                                                                               
//�� 15  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                               
    124         }                                                                                                                                       
    125                                                                                                                                                 
    126         pci_set_master (dev);                                                                                                                   
    127                                                                                                                                                 
    128         retval = usb_add_hcd (hcd, dev->irq, IRQF_SHARED);                                                                                      
    129         if (retval != 0)                                                                                                                        
    130                 goto err4;                                                                                                                      
    131         return retval;                                                                                                                          
    132                                                                                                                                                 
    133  err4:                                                                                                                                          
    134         if (driver->flags & HCD_MEMORY) {                                                                                                       
    135                 iounmap (hcd->regs);                                                                                                            
    136  err3:                                                                                                                                          
    137                 release_mem_region (hcd->rsrc_start, hcd->rsrc_len);                                                                            
    138         } else                                                                                                                                  
    139                 release_region (hcd->rsrc_start, hcd->rsrc_len);                                                                                
    140  err2:                                                                                                                                          
    141         usb_put_hcd (hcd);                                                                                                                      
    142  err1:                                                                                                                                          
    143         pci_disable_device (dev);                                                                                                               
    144         dev_err (&dev->dev, "init %s fail, %d ", pci_name(dev), retval);                                                                        
    145         return retval;                                                                                                                          
    146 }                                                                                                                                               
                                                                                                                                                        
// 64 �У�usb_disabled()�ж��ں���û�п���֧�� usb��Ҫ���ⶼ��֧�֣�һ�ж���̸��                                                                           
// 70 �У�pci_enable_device()���Ƕ� ehci����ӿ��е� pci configuration space���в���������                                                                 
// ����ĳ���Ĵ�����ֵ��ʹ�豸���ڹ���״̬������ pci_read_config_word() ��                                                                                  
// pci_write_config_word ����д pci ���ÿռ�ļĴ����� pci_enable_device ->                                                                                
// pci_enable_device_bars -> do_pci_enable_device ...   ԭ���ѣ�ֻҪ���� spec���Կ�����                                                                  
// 72��73 �ǵ�Դ��������ݡ�75 �ж��豸���жϺ��Ƿ�Ϊ�ա�                                                                                                  
// 83��usb_create_hcd()  ����һ�� usb_hcd�����塣                                                                                                          
                                                                                                                                                        
//   1480 //*                                                                                                                                             
//   1481  * usb_create_hcd - create and initialize an HCD structure                                                                                      
//   1482  * @driver: HC driver that will use this hcd                                                                                                    
//   1483  * @dev: device for this HC, stored in hcd->self.controller                                                                                     
//   1484  * @bus_name: value to store in hcd->self.bus_name                                                                                              
//   1485  * Context: !in_interrupt()                                                                                                                     
//   1486  *                                                                                                                                              
//   1487  * Allocate a struct usb_hcd, with extra space at the end for the                                                                               
//   1488  * HC driver's private data.  Initialize the generic members of the                                                                             
//   1489  * hcd structure.                                                                                                                               
//   1490  *                                                                                                                                              
//   1491  * If memory is unavailable, returns NULL.                                                                                                      
//�� 16  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                               
   1492  //                                                                                                                                             
   1493 struct usb_hcd *usb_create_hcd (const struct hc_driver *driver,                                                                                 
   1494                 struct device *dev, char *bus_name)                                                                                             
   1495 {                                                                                                                                               
   1496         struct usb_hcd *hcd;                                                                                                                    
   1497                                                                                                                                                 
   1498         hcd = kzalloc(sizeof(*hcd) + driver->hcd_priv_size, GFP_KERNEL);                                                                        
   1499         if (!hcd) {                                                                                                                             
   1500                 dev_dbg (dev, "hcd alloc failed ");                                                                                             
   1501                 return NULL;                                                                                                                    
   1502         }                                                                                                                                       
   1503         dev_set_drvdata(dev, hcd);                                                                                                              
   1504         kref_init(&hcd->kref);                                                                                                                  
   1505                                                                                                                                                 
   1506         usb_bus_init(&hcd->self);                                                                                                               
   1507         hcd->self.controller = dev;                                                                                                             
   1508         hcd->self.bus_name = bus_name;                                                                                                          
   1509         hcd->self.uses_dma = (dev->dma_mask != NULL);                                                                                           
   1510                                                                                                                                                 
   1511         init_timer(&hcd->rh_timer);                                                                                                             
   1512         hcd->rh_timer.function = rh_timer_func;                                                                                                 
   1513         hcd->rh_timer.data = (unsigned long) hcd;                                                                                               
   1514 #ifdef CONFIG_PM                                                                                                                                
   1515         INIT_WORK(&hcd->wakeup_work, hcd_resume_work);                                                                                          
   1516 #endif                                                                                                                                          
   1517                                                                                                                                                 
   1518         hcd->driver = driver;                                                                                                                   
   1519         hcd->product_desc = (driver->product_desc) ? driver->product_desc :                                                                     
   1520                         "USB Host Controller";                                                                                                  
   1521                                                                                                                                                 
   1522         return hcd;                                                                                                                             
   1523 }                                                                                                                                               
                                                                                                                                                        
//                                                                                                                                                         
// һ���ӳ����˺ܶ����ݽṹ�������б�Ҫ��һ������֮��Ĺ�ϵ��                                                                                              
// (1)�������������ݽṹ                                                                                                                                   
//                                                                                                                                                         
// ehci ������������������Ҫ����Щʲô������վ�� pci ���ߵĽǶ���˵��ehci ��һ�� pci ��                                                                    
// �豸������������������ṩ���� ehci �豸�����翪��(start)���ر�(stop)������(reset)����                                                                  
// �ϵĺ��������⣬վ�� usb �������ĽǶ���˵�������������滹Ҫ��ײ� usb ϵͳ�����ĺ�                                                                      
// ���������\ɾ�� urb(rb_enqueue, urb_dequeue)��                                                                                                          
//                                                                                                                                                         
pci_driver ehci_pci_driver{                                                                                                                             
//           .........                                                                                                                                    
//�� 17  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                               
           .id_table = pci_ids,        ------------>driver_data = (unsigned long) &ehci_pci_hc_driver,                                                  
          .probe = usb_hcd_pci_probe                                                                                                                    
                                                                                                                                                        
}                                                                                                                                                       
hc_driver ehci_pci_hc_driver{                                                                                                                           
        ........                                                                                                                                        
       .hcd_priv_size = sizeof(struct ehci_hcd),                                                                                                        
                                                                                                                                                        
       .irq =   ehci_irq,                                                                                                                               
       .reset =  ehci_pci_setup,                                                                                                                        
       .start =  ehci_run,                                                                                                                              
       .stop =   ehci_stop,                                                                                                                             
       .shutdown =  ehci_shutdown,                                                                                                                      
                                                                                                                                                        
       .urb_enqueue =  ehci_urb_enqueue,                                                                                                                
       .urb_dequeue =  ehci_urb_dequeue,                                                                                                                
}                                                                                                                                                       
//(2)�����豸�����ݽṹ                                                                                                                                   
//                                                                                                                                                        
usb_hcd{                                                                                                                                                
        ........                                                                                                                                        
        usb_bus .self                                                                                                                                   
       .hcd_priv = ehci_hcd                                                                                                                             
}                                                                                                                                                       
                                                                                                                                                        
// usb_hcd �����˼��й�������                                                                                                                              
// linux ��Щ�¶�  ֮  Ϸ˵USB(28)�豸�������� (��)                                                                                                        
//  http://blog.csdn.net/fudan_abc/archive/2007/10/18/1831459.aspx                                                                                         
//                                                                                                                                                         
// usb_hcd ע����˵ USB Host Controller Driver�����Ҹ�Ը����Ϊ����һ������һ�� usb������                                                                   
// ���豸�����ݽṹ��usb_hcd ������ usb �����������е����ԣ�usb_hcd.hcd_priv ָ�����ض�                                                                    
// �������������ݽṹ���������������е����ԡ��� ehci���� ehci_hcd���� uhci���� uhci_hcd��                                                                  
// usb_hcd �ĳ�Ա usb_bus self  �� HCD bus-glue layer��usb ������������֮��ճ�ϼ���                                                                        
// ������1498�ͺ�����ˡ�1506 ��usb_bus_init ��ʼ�� usb_hcd.self�� 1511-1513 ��ʼ�� root                                                                   
// harbor  ��ʱ����Ȼ����з��ص� usb_hcd_pci_probe()                                                                                                      
//                                                                                                                                                         
// 2008 �����һ��ѩ                                                                                                                                       
// 2008 �����һ��ѩ��������ʱ������Ҫ��һЩ����ǰ���򲻵�Ʊ�������ƱҲ�߲����ˡ�                                                                         
// ��ʱ�˿̣������ֵܽ��ñ�����·�ϣ��������ȣ����ٳ���ͣ��ͣˮ����۷��ǡ���������                                                                        
// ��ס�ƿڴ����һ����гʢ������˵�����֣��������˻���ֱ��ԭ�����Ǹ����Ķ��ꡣ��                                                                        
// ����Ϊ���������Ͽ���̣��Լ���ν��ˮ������                                                                                                              
// �� 18  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                               
// ףԸ��Щ������·����·�ϵ��������ջؼ���Բ����ҹ������ꡣ                                                                                              
// �����ȿ������У�����Ϣ�ƣ�"���´��̱�����ԭ������Ϊ������Ľ�ѩ,  ���´����Ĺ���                                                                        
// ������վ,����.�޷�������г���,  ���ڼ�����Ա����������ͣ����޷���������,  ����                                                                      
// �˽���Ĵ��ʽ��޷�����,  ���Ҳ�Ҫ�ֻš��ݲ���ȫͳ���� 60%�Ļ�������ֱ����ڻ���                                                                       
// �Է����档"                                                                                                                                             
// �л��ٽ����Ȳ���һ��ͼ��                                                                                                                                
// ���ǽ��� usb_hcd_pci_probe()�����ߣ�89 - 108 �У���Ϊ EHCI ���� io �ڴ棬92 ��                                                                          
// request_mem_region()���룬98 ����һ�� mapping���� EHCI(1)�������ᵽ����EHCI �Ľӿ�                                                                      
// �� 3 �֣���һ���� PCI ���üĴ������ڶ����� io �ڴ棬�����־�����ͨ���ڴ档�����Ȱ�                                                                      
// �� 19  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                               
// EHCI�� io�ڴ�Ǽǣ�����һ�� ioremap ӳ��������ַ��                                                                                                    
// ������ 126 pci_set_master()  �� UHCI 4                                                                                                                  
// http://blog.csdn.net/fudan_abc/archive/2007/10/04/1811451.aspx                                                                                          
//128 �н����� usb_add_hcd()                                                                                                                              
//   1548 //*                                                                                                                                             
//   1549 * usb_add_hcd - finish generic HCD structure initialization and register                                                                        
//   1550 * @hcd: the usb_hcd structure to initialize                                                                                                     
//   1551 * @irqnum: Interrupt line to allocate                                                                                                           
//   1552 * @irqflags: Interrupt type flags                                                                                                               
//   1553 *                                                                                                                                               
//   1554 * Finish the remaining parts of generic HCD initialization: allocate the                                                                        
//   1555 * buffers of consistent memory, register the bus, request the IRQ line,                                                                         
//   1556 * and call the driver's reset() and start() routines.                                                                                           
//   1557 //                                                                                                                                              
   1558 int usb_add_hcd(struct usb_hcd *hcd,                                                                                                            
   1559                 unsigned int irqnum, unsigned long irqflags)                                                                                    
   1560 {                                                                                                                                               
   1561         int retval;                                                                                                                             
   1562         struct usb_device *rhdev;                                                                                                               
   1563                                                                                                                                                 
   1564         dev_info(hcd->self.controller, "%s\n", hcd->product_desc);                                                                              
   1565                                                                                                                                                 
   1566         set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);                                                                                           
   1567                                                                                                                                                 
   1568         // HC is in reset state, but accessible. Now do the one-time init,                                                                      
   1569          * bottom up so that hcds can customize the root hubs before khubd                                                                      
   1570          * starts talking to them. (Note, bus id is assigned early too.)                                                                        
   1571          //                                                                                                                                     
   1572         if ((retval = hcd_buffer_create(hcd)) != 0) {                                                                                           
   1573                 dev_dbg(hcd->self.controller, "pool alloc failed\n");                                                                           
   1574                 return retval;                                                                                                                  
   1575         }                                                                                                                                       
   1576                                                                                                                                                 
   1577         if ((retval = usb_register_bus(&hcd->self)) < 0)                                                                                        
   1578                 goto err_register_bus;                                                                                                          
   1579                                                                                                                                                 
   1580         if ((rhdev = usb_alloc_dev(NULL, &hcd->self, 0)) == NULL) {                                                                             
   1581                 dev_err(hcd->self.controller, "unable to allocate root hub\n");                                                                 
   1582                 retval = -ENOMEM;                                                                                                               
   1583                 goto err_allocate_root_hub;                                                                                                     
   1584         }                                                                                                                                       
   1585         rhdev->speed = (hcd->driver->flags & HCD_USB2) ? USB_SPEED_HIGH :                                                                       
   1586                         USB_SPEED_FULL;                                                                                                         
   1587         hcd->self.root_hub = rhdev;                                                                                                             
//�� 20  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                               
//   1588                                                                                                                                                 
   1589         // wakeup flag init defaults to "everything works" for root hubs,                                                                       
   1590          * but drivers can override it in reset() if needed, along with                                                                         
   1591          * recording the overall controller's system wakeup capability.                                                                         
   1592          //                                                                                                                                     
   1593         device_init_wakeup(&rhdev->dev, 1);                                                                                                     
   1594                                                                                                                                                 
   1595         // "reset" is misnamed; its role is now one-time init. the controller                                                                   
   1596          * should already have been reset (and boot firmware kicked off etc).                                                                   
   1597          //                                                                                                                                     
   1598         if (hcd->driver->reset && (retval = hcd->driver->reset(hcd)) < 0) {                                                                     
   1599                 dev_err(hcd->self.controller, "can't setup\n");                                                                                 
   1600                 goto err_hcd_driver_setup;                                                                                                      
   1601         }                                                                                                                                       
   1602                                                                                                                                                 
   1603         // NOTE: root hub and controller capabilities may not be the same //                                                                    
   1604         if (device_can_wakeup(hcd->self.controller)                                                                                             
   1605                         && device_can_wakeup(&hcd->self.root_hub->dev))                                                                         
   1606                 dev_dbg(hcd->self.controller, "supports USB remote wakeup\n");                                                                  
   1607                                                                                                                                                 
   1608         // enable irqs just before we start the controller //                                                                                   
   1609         if (hcd->driver->irq) {                                                                                                                 
   1610                 snprintf(hcd->irq_descr, sizeof(hcd->irq_descr), "%s:usb%d",                                                                    
   1611                                 hcd->driver->description, hcd->self.busnum);                                                                    
   1612                 if ((retval = request_irq(irqnum, &usb_hcd_irq, irqflags,                                                                       
   1613                                 hcd->irq_descr, hcd)) != 0) {                                                                                   
   1614                         dev_err(hcd->self.controller,                                                                                           
   1615                                         "request interrupt %d failed\n", irqnum);                                                               
   1616                         goto err_request_irq;                                                                                                   
   1617                 }                                                                                                                               
  1618                 hcd->irq = irqnum;                                                                                                               
   1619                 dev_info(hcd->self.controller, "irq %d, %s 0x%08llx\n", irqnum,                                                                 
   1620                                 (hcd->driver->flags & HCD_MEMORY) ?                                                                             
   1621                                         "io mem" : "io base",                                                                                   
   1622                                         (unsigned long long)hcd->rsrc_start);                                                                   
   1623         } else {                                                                                                                                
   1624                 hcd->irq = -1;                                                                                                                  
   1625                 if (hcd->rsrc_start)                                                                                                            
    1626                          dev_info(hcd->self.controller,  "%s                                                                                   
0x%08llx\n", 1627                                         (hcd->driver->flags & HCD_MEMORY) ?                                                           
                                                                                                                                                        
   1628                                         "io mem" : "io base",                                                                                   
   1629                                         (unsigned long long)hcd->rsrc_start);                                                                   
   1630         }                                                                                                                                       
//�� 21  ҳ  �� 22  ҳ Linux  ��Щ�¶�֮���� EHCI����������                                                                                               
   1631                                                                                                                                                 
   1632         if ((retval = hcd->driver->start(hcd)) < 0) {                                                                                           
   1633                 dev_err(hcd->self.controller, "startup error %d\n", retval);                                                                    
   1634                 goto err_hcd_driver_start;                                                                                                      
   1635         }                                                                                                                                       
   1636                                                                                                                                                 
   1637         // starting here, usbcore will pay attention to this root hub //                                                                        
   1638         rhdev->bus_mA = min(500u, hcd->power_budget);                                                                                           
   1639         if ((retval = register_root_hub(hcd)) != 0)                                                                                             
   1640                 goto err_register_root_hub;                                                                                                     
   1641                                                                                                                                                 
   1642         if (hcd->uses_new_polling && hcd->poll_rh)                                                                                              
   1643                 usb_hcd_poll_rh_status(hcd);                                                                                                    
   1644         return retval;                                                                                                                          
   1645                                                                                                                                                 
   1646 err_register_root_hub:                                                                                                                          
   1647         hcd->driver->stop(hcd);                                                                                                                 
   1648 err_hcd_driver_start:                                                                                                                           
   1649         if (hcd->irq >= 0)                                                                                                                      
   1650                 free_irq(irqnum, hcd);                                                                                                          
   1651 err_request_irq:                                                                                                                                
   1652 err_hcd_driver_setup:                                                                                                                           
   1653         hcd->self.root_hub = NULL;                                                                                                              
   1654         usb_put_dev(rhdev);                                                                                                                     
   1655 err_allocate_root_hub:                                                                                                                          
   1656         usb_deregister_bus(&hcd->self);                                                                                                         
   1657 err_register_bus:                                                                                                                               
   1658         hcd_buffer_destroy(hcd);                                                                                                                
   1659         return retval;                                                                                                                          
   1660 }                                                                                                                                               
// 1572�� hcd_buffer_create()�� UHCI 5                                                                                                                     
// http://blog.csdn.net/fudan_abc/archive/2007/10/10/1818462.aspx��                                                                                        
// ���ܽ�һ�£�����,  �ݻ� buffur: hcd_buffer_create() / hcd_buffer_destroy()������֮�󣬴�                                                              
// ��������ȡ���߰���ȡ���ͷŻ�ȥ��usb_buffer_alloc()/usb_buffer_free()��                                                                                  
// 1577�� usb_register_bus�� UHCI 6                                                                                                                        
// http://blog.csdn.net/fudan_abc/archive/2007/10/13/1823287.aspx��                                                                                        
// ����˵�����Լ����뵽ȫ�ֱ��� usb_bus_list �У������� class_device_create �� sysfs �¼�                                                                
// ��һ�� class��                                                                                                                                          
// 1580�� usb_alloc_dev()��UHCI 7                                                                                                                          
// http://blog.csdn.net/fudan_abc/archive/2007/10/16/1827449.aspx��                                                                                        
// 1598 ��֮ǰ������ UHCI û��ʲô�ֱ� hcd->driver->reset ָ����ǣ�                                                                                     
// ehci_pci_hc_driver.ehci_pci_setup()                                                                                                                     
//                                                                                                                                                         
// �� 22  ҳ  �� 22  ҳ                                                                                                                                    