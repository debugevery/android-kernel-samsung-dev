/*======================================================================
    A simple kernel module to introduce export symbol
         
    The initial developer of the original code is Baohua Song
    <author@linuxdriver.cn>. All Rights Reserved.
======================================================================*/
//#include <linux/init.h>                                
//#include <linux/module.h>                                
//MODULE_LICENSE("Dual BSD/GPL");                                
                                
int add_integar(int a,int b)                                
{                                
	return a+b;                             
} 
                               
int sub_integar(int a,int b)                                
{                                
	return a-b;                             
}                            
//�궨�����һ��ʹ�ø����ķ�����ģ�������. _GPL �汾�ĺ궨��ֻ��ʹ
//���Ŷ� GPL ��ɵ�ģ�����. ���ű�����ģ���ļ���ȫ�ֲ������, ���κκ�
//��֮��, ��Ϊ�궨����չ��һ��������;�Ĳ���������ȫ�ִ�ȡ�ı���������.
//EXPORT_SYMBOL(add_integar);
//EXPORT_SYMBOL(sub_integar);