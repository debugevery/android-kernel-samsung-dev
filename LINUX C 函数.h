//�ַ�����ƪ=====================================================================
//
//isalnum�������ַ��Ƿ�ΪӢ�Ļ����֣�  
//��غ���  isalpha��isdigit��islower��isupper
// 
//��ͷ�ļ�  #include<ctype.h>
// 
  int isalnum (int c)
// 
//����˵��  ������c�Ƿ�ΪӢ����ĸ���������֣��ڱ�׼c���൱��ʹ�á�isalpha(c) || isdigit(c)�������ԡ�
// 
//����ֵ  ������cΪ��ĸ�����֣��򷵻�TRUE�����򷵻�NULL(0)��
// 
//����˵��  ��Ϊ�궨�壬������������
// 
//����  /* �ҳ�str �ַ�����ΪӢ����ĸ�����ֵ��ַ�*/
//#include < ctype.h>
//main()
//{
//char str[]=��123c@#FDsP[e?��;
//int i;
//for (i=0;str[i]!=0;i++ )
//if ( isalnum(str[i])) printf(��%c is an alphanumeric character\n��,str[i]);
//}
// 
//ִ��  1 is an apphabetic character
// 2 is an apphabetic character
// 3 is an apphabetic character
//c is an apphabetic character
//F is an apphabetic character
//D is an apphabetic character
//s is an apphabetic character
//P is an apphabetic character
//e is an apphabetic character
// 
//�� 
//
// 
//
// 
//isalpha �������ַ��Ƿ�ΪӢ����ĸ��  
//��غ���  isalnum��islower��isupper
// 
//��ͷ�ļ�  #include<ctype.h>
// 
  int isalpha (int c)
// 
//����˵��  ������c�Ƿ�ΪӢ����ĸ���ڱ�׼c���൱��ʹ�á�isupper(c)||islower(c)�������ԡ�
// 
//����ֵ  ������cΪӢ����ĸ���򷵻�TRUE�����򷵻�NULL(0)��
// 
//����˵��  ��Ϊ�궨�壬������������
// 
//����  /* �ҳ�str �ַ�����ΪӢ����ĸ���ַ�*/
//#include <ctype.h>
//main()
//{
//char str[]=��123c@#FDsP[e?��;
//int i;
//for (i=0;str[i]!=0;i++)
//if(isalpha(str[i])) printf(��%c is an alphanumeric character\n��,str[i]);
//}
// 
//ִ��  c is an apphabetic character
//F is an apphabetic character
//D is an apphabetic character
//s is an apphabetic character
//P is an apphabetic character
//e is an apphabetic character
// 
//�� 
//
// 
//
// 
//isascii�������ַ��Ƿ�ΪASCII ���ַ���  
//��غ���  iscntrl
// 
//��ͷ�ļ�  #include <ctype.h>
// 
  int isascii(int c);
// 
//����˵��  ������c�Ƿ�ΪASCII���ַ���Ҳ�����ж�c�ķ�Χ�Ƿ���0��127֮�䡣
// 
//����ֵ  ������cΪASCII���ַ����򷵻�TRUE�����򷵻�NULL(0)��
// 
//����˵��  ��Ϊ�궨�壬������������
// 
//����  /* �ж�int i�Ƿ���ж�ӳ��ASCII���ַ�*/
//#include<ctype.h>
//main()
//{
//int i;
//for(i=125;i<130;i++)
//if(isascii(i))
//printf("%d is an ascii character:%c\n",i,i);
//else
//printf("%d is not an ascii character\n",i);
//}
// 
//ִ��  125 is an ascii character:}
//126 is an ascii character:~
//127 is an ascii character:
//128 is not an ascii character
//129 is not an ascii character
// 
//�� 
//
// 
//
// 
//iscntrl�������ַ��Ƿ�ΪASCII ��Ŀ����ַ���  
//��غ���  isascii
// 
//��ͷ�ļ�  #include <ctype.h>
// 
  int iscntrl(int c)��
// 
//����˵��  ������c�Ƿ�ΪASCII�����룬Ҳ�����ж�c�ķ�Χ�Ƿ���0��30֮�䡣
// 
//����ֵ  ������cΪASCII�����룬�򷵻�TRUE�����򷵻�NULL(0)��
// 
//����˵��  ��Ϊ�궨�壬������������
// 
//�� 
//
// 
//
// 
//isdigit�������ַ��Ƿ�Ϊ���������֣�  
//��غ���  isxdigit
// 
//��ͷ�ļ�  #include<ctype.h>
// 
  int isdigit(int c)
// 
//����˵��  ������c�Ƿ�Ϊ����������0��9��
// 
//����ֵ  ������cΪ���������֣��򷵻�TRUE�����򷵻�NULL(0)��
// 
//����˵��  ��Ϊ�궨�壬������������
// 
//����  /* �ҳ�str�ַ�����Ϊ���������ֵ��ַ�*/
//#include<ctype.h>
//main()
//{
//char str[]="123@#FDsP[e?";
//int i;
//for(i=0;str[i]!=0;i++)
//if(isdigit(str[i])) printf("%c is an digit character\n",str[i]);
//}
// 
//ִ��  1 is an digit character
//2 is an digit character
//3 is an digit character
// 
//�� 
//
// 
//
// 
//isgraphis�������ַ��Ƿ�Ϊ�ɴ�ӡ�ַ���  
//��غ���  isprint
// 
//��ͷ�ļ�  #include <ctype.h>
// 
  int isgraph (int c)
// 
//����˵��  ������c�Ƿ�Ϊ�ɴ�ӡ�ַ�����c����ӳ��ASCII��ɴ�ӡ���ҷǿո��ַ��򷵻�TRUE��
// 
//����ֵ  ������cΪ�ɴ�ӡ�ַ����򷵻�TRUE�����򷵻�NULL(0)��
// 
//����˵��  ��Ϊ�궨�壬������������
// 
//����  /* �ж�str�ַ�������ЩΪ�ɴ�ӡ�ַ�*/
//#include<ctype.h>
//main()
//{
//char str[]="a5 @;";
//int i;
//for(i=0;str[i]!=0;i++)
//if(isgraph(str[i])) printf("str[%d] is printable character:%d\n",i,str[i]);
//}
// 
//ִ��  str[0] is printable character:a
//str[1] is printable character:5
//str[3] is printable character:@
//str[4] is printable character:;
// 
//�� 
//
// 
//
// 
//islower�������ַ��Ƿ�ΪСд��ĸ��  
//��غ���  isalpha��isupper
// 
//��ͷ�ļ�  #include<ctype.h>
// 
  int islower(int c)
// 
//����˵��  ������c�Ƿ�ΪСдӢ����ĸ��
// 
//����ֵ  ������cΪСдӢ����ĸ���򷵻�TRUE�����򷵻�NULL(0)��
// 
//����˵��  ��Ϊ�궨�壬������������
// 
//����  #include<ctype.h>
//main()
//{
//char str[]="123@#FDsP[e?";
//int i;
//for(i=0;str[i]!=0;i++)
//if(islower(str[i])) printf("%c is a lower-case character\n",str[i]);
//}
// 
//ִ��  c is a lower-case character
//s is a lower-case character
//e is a lower-case character
// 
//�� 
//
// 
//
// 
//isprint�������ַ��ǣ���Ϊ�ɴ�ӡ�ַ���  
//��غ���  isgraph
// 
//��ͷ�ļ�  #include<ctype.h>
// 
  int isprint(int c);
// 
//����˵��  ������c�Ƿ�Ϊ�ɴ�ӡ�ַ�����c����ӳ��ASCII��ɴ�ӡ�����а����ո��ַ����򷵻�TRUE��
// 
//����ֵ  ������cΪ�ɴ�ӡ�ַ����򷵻�TRUE�����򷵻�NULL(0)��
// 
//����˵��  ��Ϊ�궨�壬������������
// 
//����  /* �ж�str�ַ�������ЩΪ�ɴ�ӡ�ַ������ո��ַ�*/
//#include<ctype.h>
//main()
//{
//char str[]="a5 @;";
//int i;
//for(i=0;str[i]!=0;i++)
//if(isprint(str[i])) printf("str[%d] is printable character:%d\n",i,str[i]);
//}
// 
//ִ��  str[0] is printable character:a
//str[1] is printable character:5
//str[2] is printable character:
//str[3] is printable character:@
//str[4] is printable character:;
// 
//�� 
//
// 
//
// 
//isspace�������ַ��Ƿ�Ϊ�ո��ַ���  
//��غ���  isgraph
// 
//��ͷ�ļ�  #include<ctype.h>
// 
  int isspace(int c)
// 
//����˵��  ������c�Ƿ�Ϊ�ո��ַ���Ҳ�����ж��Ƿ�Ϊ�ո�('')����λ�ַ�('\t')��CR('\r')������('\n')����ֱ��λ�ַ�('\v')��ҳ('\f')�������
// 
//����ֵ  ������cΪ�ո��ַ����򷵻�TRUE�����򷵻�NULL(0)��
// 
//����˵��  ��Ϊ�궨�壬������������
// 
//����  /*���ַ���str[]���ں��Ŀո��ַ��ҳ�������ʾ�ո��ַ���ASCII��*/
//#include <ctype.h>
//main()
//{
//char str="123c @# FD\tsP[e?\n";
//int i;
//for(i=0;str[i]!=0;i++)
//if(isspace(str[i]))
//printf("str[%d] is a white-space character:%d\n",i,str[i]);
//}
// 
//ִ��  str[4] is a white-space character:32
//str[7] is a white-space character:32
//str[10] is a white-space character:9 /* \t */
//str[16] is a white-space character:10 /* \t */
// 
//�� 
//
// 
//
// 
//ispunct�������ַ��Ƿ�Ϊ�����Ż�������ţ�  
//��غ���  isspace��isdigit��isalpha
// 
//��ͷ�ļ�  #inlude<ctype.h>
// 
  int ispunct(int c)
// 
//����˵��  ������c�Ƿ�Ϊ�����Ż�������š�����TRUEҲ���Ǵ������cΪ�ǿո񡢷����ֺͷ�Ӣ����ĸ��
// 
//����ֵ  v������cΪ�����Ż�������ţ��򷵻�TRUE�����򷵻�NULL(0)��
// 
//����˵��  ��Ϊ�궨�壬������������
// 
//����  /*�г��ַ���str�еı����Ż��������*/
//#include <ctype.h>
//main()
//{
//char str[]="123c@ #FDsP[e?";
//int i;
//for(i=0;str[i]!=0;i++)
//if(ispunct(str[i])) printf("%c\n",str[i]);
//}
// 
//ִ��  v
//@#[?
// 
//�� 
//
// 
//
// 
//isupper�������ַ��Ƿ�Ϊ��дӢ����ĸ��  
//��غ���  isalpha��islower
// 
//��ͷ�ļ�  #include<ctype.h>
// 
  int isupper(int c)
// 
//����˵��  ������c�Ƿ�Ϊ��дӢ����ĸ��
// 
//����ֵ  ������cΪ��дӢ����ĸ���򷵻�TRUE�����򷵻�NULL(0)��
// 
//����˵��  ��Ϊ�궨�壬������������
// 
//����  /*�ҳ��ַ���str��Ϊ��дӢ����ĸ���ַ�*/
//#include <ctype.h>
//main()
//{
//char str[]="123c@#FDsP[e?";
//int i;
//for(i=0;str[i]!=0;i++)
//if(isupper(str[i])) printf("%c is an uppercase character\n",str[i]);
//}
// 
//ִ��  F is an uppercase character
//D is an uppercase character
//P is an uppercase character
// 
//�� 
//
// 
//
// 
//isxdigit�������ַ��Ƿ�Ϊ16�������֣�  
//��غ���  isalnum��isdigit
// 
//��ͷ�ļ�  #include<ctype.h>
// 
  int isxdigit (int c)
// 
//����˵��  ������c�Ƿ�Ϊ16�������֣�ֻҪcΪ��������һ������򷵻�TRUE��16��������:0123456789ABCDEF��
// 
//����ֵ  ������cΪ16�������֣��򷵻�TRUE�����򷵻�NULL(0)��
// 
//����˵��  ��Ϊ�궨�壬������������
// 
//����  /*�ҳ��ַ���str��Ϊʮ���������ֵ��ַ�*/
//#include <ctype.h>
//main()
//{
//char str[]="123c@#FDsP[e?";
//int i;
//for(i=0;str[i]!=0;i++)
//if(isxdigit(str[i])) printf("%c is a hexadecimal digits\n",str[i]);
//}
// 
//ִ��  1 is a hexadecimal digits
//2 is a hexadecimal digits
//3 is a hexadecimal digits
//c is a hexadecimal digits
//F is a hexadecimal digits
//D is a hexadecimal digits
//e is a hexadecimal digits
// 
//�� 
//
//�ַ���ת��ƪ====================================================================================
//
//�� 
//
// 
//
// 
//atof�����ַ���ת���ɸ���������  
//��غ���  atoi��atol��strtod��strtol��strtoul
// 
//��ͷ�ļ�  #include <stdlib.h>
// 
  double atof(const char *nptr);
// 
//����˵��  atof()��ɨ�����nptr�ַ���������ǰ��Ŀո��ַ���ֱ���������ֻ��������Ųſ�ʼ��ת�����������������ֻ��ַ�������ʱ('\0')�Ž���ת��������������ء�����nptr�ַ����ɰ��������š�С�����E(e)����ʾָ�����֣���123.456��123e-2��
// 
//����ֵ  ����ת����ĸ���������
// 
//����˵��  atof()��ʹ��strtod(nptr,(char**)NULL)�����ͬ��
// 
//����  /* ���ַ���a ���ַ���bת�������ֺ����*/
//#include<stdlib.h>
//main()
//{
//char *a=��-100.23��;
//char *b=��200e-2��;
//float c;
//c=atof(a)+atof(b);
//printf(��c=%.2f\n��,c);
//}
// 
//ִ��  c=-98.23
// 
//�� 
//
// 
//
// 
//atoi�����ַ���ת������������  
//��غ���  atof��atol��atrtod��strtol��strtoul
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  int atoi(const char *nptr);
// 
//����˵��  atoi()��ɨ�����nptr�ַ���������ǰ��Ŀո��ַ���ֱ���������ֻ��������Ųſ�ʼ��ת�����������������ֻ��ַ�������ʱ('\0')�Ž���ת��������������ء�
// 
//����ֵ  ����ת�������������
// 
//����˵��  atoi()��ʹ��strtol(nptr��(char**)NULL��10)�������ͬ��
// 
//����  /* ���ַ���a ���ַ���bת�������ֺ����*/
//#include<stdlib.h>
//mian()
//{
//char a[]=��-100��;
//char b[]=��456��;
//int c;
//c=atoi(a)+atoi(b);
//printf(c=%d\n��,c);
//}
// 
//ִ��  c=356
// 
//�� 
//
// 
//
// 
//atol�����ַ���ת���ɳ���������  
//��غ���  atof��atoi��strtod��strtol��strtoul
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  long atol(const char *nptr);
// 
//����˵��  atol()��ɨ�����nptr�ַ���������ǰ��Ŀո��ַ���ֱ���������ֻ��������Ųſ�ʼ��ת�����������������ֻ��ַ�������ʱ('\0')�Ž���ת��������������ء�
// 
//����ֵ  ����ת����ĳ���������
// 
//����˵��  atol()��ʹ��strtol(nptr,(char**)NULL,10)�������ͬ��
// 
//����  /*���ַ���a���ַ���bת�������ֺ����*/
//#include<stdlib.h>
//main()
//{
//char a[]=��1000000000��;
//char b[]=�� 234567890��;
//long c;
//c=atol(a)+atol(b);
//printf(��c=%d\n��,c);
//}
// 
//ִ��  c=1234567890
// 
//�� 
//
// 
//
// 
//gcvt������������ת��Ϊ�ַ�����ȡ�������룩  
//��غ���  ecvt��fcvt��sprintf
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  char *gcvt(double number��size_t ndigits��char *buf);
// 
//����˵��  gcvt()����������numberת����ASCII���ַ���������ndigits��ʾ��ʾ��λ����gcvt()��ecvt()��fcvt()��ͬ�ĵط����ڣ�gcvt()��ת������ַ�������С������������š���ת���ɹ���ת������ַ�������ڲ���bufָ����ָ�Ŀռ䡣
// 
//����ֵ  ����һ�ַ���ָ�룬�˵�ַ��Ϊbufָ�롣
// 
//����˵��  
// 
//����  #include<stdlib.h>
//main()
//{
//double a=123.45;
//double b=-1234.56;
//char *ptr;
//int decpt,sign;
//gcvt(a,5,ptr);
//printf(��a value=%s\n��,ptr);
//ptr=gcvt(b,6,ptr);
//printf(��b value=%s\n��,ptr);
//}
// 
//ִ��  a value=123.45
//b value=-1234.56
// 
//�� 
//
// 
//
// 
//strtod�����ַ���ת���ɸ�������  
//��غ���  atoi��atol��strtod��strtol��strtoul
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  double strtod(const char *nptr,char **endptr);
// 
//����˵��  strtod()��ɨ�����nptr�ַ���������ǰ��Ŀո��ַ���ֱ���������ֻ��������Ųſ�ʼ��ת���������ַ����ֻ��ַ�������ʱ('\0')�Ž���ת��������������ء���endptr��ΪNULL����Ὣ����������������ֹ��nptr�е��ַ�ָ����endptr���ء�����nptr�ַ����ɰ��������š�С�����E(e)����ʾָ�����֡���123.456��123e-2��
// 
//����ֵ  ����ת����ĸ���������
// 
//����˵��  �ο�atof()��
// 
//����  /*���ַ���a��b��c �ֱ����10��2��16 ����ת��������*/
//#include<stdlib.h>
//mian()
//{
//char a[]=��1000000000��;
//char b[]=��1000000000��;
//char c[]=��ffff��;
//printf(��a=%d\n��,strtod(a,NULL,10));
//printf(��b=%d\n��,strtod(b,NULL,2));
//printf(��c=%d\n��,strtod(c,NULL,16));
//}
// 
//ִ��  a=1000000000
//b=512
//c=65535
// 
//�� 
//
// 
//
// 
//strtol�����ַ���ת���ɳ���������  
//��غ���  atof��atoi��atol��strtod��strtoul
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  long int strtol(const char *nptr,char **endptr,int base);
// 
//����˵��  strtol()�Ὣ����nptr�ַ������ݲ���base��ת���ɳ�������������base��Χ��2��36����0������base������õĽ��Ʒ�ʽ����baseֵΪ10�����10���ƣ���baseֵΪ16�����16���Ƶȡ���baseֵΪ0ʱ���ǲ���10������ת������������'0x'ǰ���ַ����ʹ��16������ת����һ��ʼstrtol()��ɨ�����nptr�ַ���������ǰ��Ŀո��ַ���ֱ���������ֻ��������Ųſ�ʼ��ת���������������ֻ��ַ�������ʱ('\0')����ת��������������ء�������endptr��ΪNULL����Ὣ����������������ֹ��nptr�е��ַ�ָ����endptr���ء�
// 
//����ֵ  ����ת����ĳ������������򷵻�ERANGE��������������errno�С�
// 
//����˵��  ERANGEָ����ת���ַ��������Ϸ���Χ��
// 
//����  /* ���ַ���a��b��c �ֱ����10��2��16����ת��������*/
//#include<stdlib.h>
//main()
//{
//char a[]=��1000000000��;
//char b[]=��1000000000��;
//char c[]=��ffff��;
//printf(��a=%d\n��,strtol(a,NULL,10));
//printf(��b=%d\n��,strtol(b,NULL,2));
//printf(��c=%d\n��,strtol(c,NULL,16));
//}
// 
//ִ��  a=1000000000
//b=512
//c=65535
// 
//�� 
//
// 
//
// 
//strtoul�����ַ���ת�����޷��ų���������  
//��غ���  atof��atoi��atol��strtod��strtol
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  unsigned long int strtoul(const char *nptr,char **endptr,int base);
// 
//����˵��  strtoul()�Ὣ����nptr�ַ������ݲ���base��ת�����޷��ŵĳ�������������base��Χ��2��36����0������base������õĽ��Ʒ�ʽ����baseֵΪ10�����10���ƣ���baseֵΪ16�����16�������ȡ���baseֵΪ0ʱ���ǲ���10������ת������������'0x'ǰ���ַ����ʹ��16������ת����һ��ʼstrtoul()��ɨ�����nptr�ַ���������ǰ��Ŀո��ַ�����ֱ���������ֻ��������Ųſ�ʼ��ת���������������ֻ��ַ�������ʱ('\0')����ת��������������ء�������endptr��ΪNULL����Ὣ����������������ֹ��nptr�е��ַ�ָ����endptr���ء�
// 
//����ֵ  ����ת����ĳ������������򷵻�ERANGE��������������errno�С�
// 
//����˵��  ERANGEָ����ת���ַ��������Ϸ���Χ��
// 
//����  �ο�strtol()
// 
//�� 
//
// 
//
// 
//toascii����������ת���ɺϷ���ASCII ���ַ���  
//��غ���  isascii��toupper��tolower
// 
//��ͷ�ļ�  #include<ctype.h>
// 
  int toascii(int c)
// 
//����˵��  toascii()�Ὣ����cת����7λ��unsigned charֵ���ڰ�λ��ᱻ��������ַ����ᱻת��ASCII���ַ���
// 
//����ֵ  ��ת���ɹ���ASCII���ַ�ֵ���ء�
// 
//����  #include<stdlib.h>
//main()
//{
//int a=217;
//char b;
//printf(��before toascii () : a value =%d(%c)\n��,a,a);
//b=toascii(a);
//printf(��after toascii() : a value =%d(%c)\n��,b,b);
//}
// 
//ִ��  before toascii() : a value =217()
//after toascii() : a value =89(Y)
// 
//�� 
//
// 
//
// 
//tolower������д��ĸת����Сд��ĸ��  
//��غ���  isalpha��toupper
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  int tolower(int c);
// 
//����˵��  ������cΪ��д��ĸ�򽫸ö�Ӧ��Сд��ĸ���ء�
// 
//����ֵ  ����ת�����Сд��ĸ��������ת���򽫲���cֵ���ء�
// 
//����˵��  
// 
//����  /* ��s�ַ����ڵĴ�д��ĸת����Сд��ĸ*/
//#include<ctype.h>
//main()
//{
//char s[]=��aBcDeFgH12345;!#$��;
//int i;
//printf(��before tolower() : %s\n��,s);
//for(i=0;I<sizeof(s);i++)
//s[i]=tolower(s[i]);
//printf(��after tolower() : %s\n��,s);
//}
// 
//ִ��  before tolower() : aBcDeFgH12345;!#$
//after tolower() : abcdefgh12345;!#$
// 
//�� 
//
// 
//
// 
//toupper����Сд��ĸת���ɴ�д��ĸ��  
//��غ���  isalpha��tolower
// 
//��ͷ�ļ�  #include<ctype.h>
// 
  int toupper(int c);
// 
//����˵��  ������cΪСд��ĸ�򽫸ö�ӳ�Ĵ�д��ĸ���ء�
// 
//����ֵ  ����ת����Ĵ�д��ĸ��������ת���򽫲���cֵ���ء�
// 
//����˵��  
// 
//����  /* ��s�ַ����ڵ�Сд��ĸת���ɴ�д��ĸ*/
//#include<ctype.h>
//main()
//{
//char s[]=��aBcDeFgH12345;!#$��;
//int i;
//printf(��before toupper() : %s\n��,s);
//for(i=0;I<sizeof(s);i++)
//s[i]=toupper(s[i]);
//printf(��after toupper() : %s\n��,s);
//}
// 
//ִ��  before toupper() : aBcDeFgH12345;!#$
//after toupper() : ABCDEFGH12345;!#$
// 
//�� 
//
// 
//�ڴ����ƪ====================================================================================
//�� 
//
// 
//
// 
//calloc�������ڴ�ռ䣩  
//��غ���  malloc��free��realloc��brk
// 
//��ͷ�ļ�  #include <stdlib.h>
// 
  void *calloc(size_t nmemb��size_t size);
// 
//����˵��  calloc()��������nmemb�����ڵ��ڴ浥λ��ÿһ��λ�Ĵ�СΪsize��������ָ���һ��Ԫ�ص�ָ�롣���ʹ�����еķ�ʽЧ����ͬ:malloc(nmemb*size);������������calloc()�����ڴ�ʱ�Ὣ�ڴ����ݳ�ʼ��Ϊ0��
// 
//����ֵ  �����óɹ��򷵻�һָ�룬ʧ���򷵻�NULL��
// 
//����  /* ��̬����10��struct test �ռ�*/
//#include<stdlib.h>
//struct test
//{
//int a[10];
//char b[20];
//}
//main()
//{
//struct test *ptr=calloc(sizeof(struct test),10);
//}
// 
//�� 
//
// 
//
// 
//free���ͷ�ԭ�����õ��ڴ棩  
//��غ���  malloc��calloc��realloc��brk
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  void free(void *ptr);
// 
//����˵��  ����ptrΪָ����ǰ��malloc()��calloc()��realloc()�����ص��ڴ�ָ�롣����free()��ptr��ָ���ڴ�ռ��ᱻ�ջء���������ptr��ָ���ڴ�ռ��ѱ��ջػ���δ֪���ڴ��ַ�������free()���ܻ����޷�Ԥ�ڵ����������������ptrΪNULL����free()�������κ����á�
// 
//�� 
//
// 
//
// 
//getpagesize��ȡ���ڴ��ҳ��С��  
//��غ���  sbrk
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  size_t getpagesize(void);
// 
//����˵��  ����һ��ҳ�Ĵ�С����λΪ�ֽڣ�byte������Ϊϵͳ�ķ�ҳ��С����һ�����Ӳ����ҳ��С��ͬ��
// 
//����ֵ  �ڴ��ҳ��С������˵����Intel x86 ���䷵��ֵӦΪ4096bytes��
// 
//����  #include <unistd.h>
//main()
//{
//printf(��page size = %d\n��,getpagesize( ) );
//}
// 
//�� 
//
// 
//
// 
//malloc�������ڴ�ռ䣩  
//��غ���  calloc��free��realloc��brk
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  void * malloc(size_t size);
// 
//����˵��  malloc()���������ڴ�ռ䣬���С��ָ����size������
// 
//����ֵ  �����óɹ��򷵻�һָ�룬ʧ���򷵻�NULL��
// 
//����  void p = malloc(1024); /*����1k���ڴ�*/
// 
//�� 
//
// 
//
// 
//mmap�������ڴ�ӳ�䣩  
//��غ���  munmap��open
// 
//��ͷ�ļ�  #include <unistd.h>
//#include <sys/mman.h>
// 
  void *mmap(void *start,size_t length,int prot,int flags,int fd,off_t offsize);
// 
//����˵��  mmap()������ĳ���ļ�����ӳ�䵽�ڴ��У��Ը��ڴ�����Ĵ�ȡ����ֱ�ӶԸ��ļ����ݵĶ�д������startָ������Ӧ���ڴ���ʼ��ַ��ͨ����ΪNULL��������ϵͳ�Զ�ѡ����ַ����Ӧ�ɹ���õ�ַ�᷵�ء�����length�����ļ��ж��Ĳ��ֶ�Ӧ���ڴ档
// 
//����  prot����ӳ������ı�����ʽ���������
//PROT_EXEC ӳ������ɱ�ִ��
//PROT_READ ӳ������ɱ���ȡ
//PROT_WRITE ӳ������ɱ�д��
//PROT_NONE ӳ�������ܴ�ȡ
// 
//����  flags��Ӱ��ӳ������ĸ�������
//MAP_FIXED �������start��ָ�ĵ�ַ�޷��ɹ�����ӳ��ʱ�������ӳ�䣬���Ե�ַ��������ͨ���������ô���ꡣ
//MAP_SHARED��ӳ�������д�����ݻḴ�ƻ��ļ��ڣ�������������ӳ����ļ��Ľ��̹���
//MAP_PRIVATE ��ӳ�������д����������һ��ӳ���ļ��ĸ��ƣ���˽�˵ġ�д��ʱ���ơ���copy on write���Դ����������κ��޸Ķ�����д��ԭ�����ļ����ݡ�
//MAP_ANONYMOUS��������ӳ�䡣��ʱ����Բ���fd�����漰�ļ�������ӳ�������޷����������̹���
//MAP_DENYWRITEֻ�����ӳ�������д��������������ļ�ֱ��д��Ĳ������ᱻ�ܾ���
//MAP_LOCKED ��ӳ����������ס�����ʾ�����򲻻ᱻ�û���swap����
//�ڵ���mmap()ʱ����Ҫָ��MAP_SHARED ��MAP_PRIVATE������fdΪopen()���ص��ļ������ʣ�������ӳ�䵽�ڴ���ļ�������offsetΪ�ļ�ӳ���ƫ������ͨ������Ϊ0��������ļ���ǰ����ʼ��Ӧ��offset�����Ƿ�ҳ��С����������
// 
//����ֵ  ��ӳ��ɹ��򷵻�ӳ�������ڴ���ʼ��ַ�����򷵻�MAP_FAILED(��1)������ԭ�����errno �С�
// 
//�������  EBADF ����fd ������Ч���ļ�������
//EACCES ��ȡȨ�����������MAP_PRIVATE ������ļ�����ɶ���ʹ��MAP_SHARED��Ҫ��PROT_WRITE�Լ����ļ�Ҫ��д�롣
//EINVAL ����start��length ��offset��һ�����Ϸ���
//EAGAIN �ļ�����ס��������̫���ڴ汻��ס��
//ENOMEM �ڴ治�㡣
// 
//����  /* ����mmap()����ȡ/etc/passwd �ļ�����*/
//#include<sys/types.h>
//#include<sys/stat.h>
//#include<fcntl.h>
//#include<unistd.h>
//#include<sys/mman.h>
//main()
//{
//int fd;
//void *start;
//struct stat sb;
//fd=open(��/etc/passwd��,O_RDONLY); /*��/etc/passwd*/
//fstat(fd,&sb); /*ȡ���ļ���С*/
//start=mmap(NULL,sb.st_size,PROT_READ,MAP_PRIVATE,fd,0);
//if(start= = MAP_FAILED) /*�ж��Ƿ�ӳ��ɹ�*/
//return;
//printf(��%s��,start);
//munma(start,sb.st_size); /*���ӳ��*/
//closed(fd);
//}
// 
//ִ��  root : x : 0 : root : /root : /bin/bash
//bin : x : 1 : 1 : bin : /bin :
//daemon : x : 2 : 2 :daemon : /sbin
//adm : x : 3 : 4 : adm : /var/adm :
//lp : x :4 :7 : lp : /var/spool/lpd :
//sync : x : 5 : 0 : sync : /sbin : bin/sync :
//shutdown : x : 6 : 0 : shutdown : /sbin : /sbin/shutdown
//halt : x : 7 : 0 : halt : /sbin : /sbin/halt
//mail : x : 8 : 12 : mail : /var/spool/mail :
//news : x :9 :13 : news : /var/spool/news :
//uucp : x :10 :14 : uucp : /var/spool/uucp :
//operator : x : 11 : 0 :operator : /root:
//games : x : 12 :100 : games :/usr/games:
//gopher : x : 13 : 30 : gopher : /usr/lib/gopher-data:
//ftp : x : 14 : 50 : FTP User : /home/ftp:
//nobody : x :99: 99: Nobody : /:
//xfs :x :100 :101 : X Font Server : /etc/xll/fs : /bin/false
//gdm : x : 42 :42 : : /home/gdm: /bin/bash
//kids : x : 500 :500 :/home/kids : /bin/bash
// 
//�� 
//
// 
//
// 
//munmap������ڴ�ӳ�䣩  
//��غ���  mmap
// 
//��ͷ�ļ�  #include<unistd.h>
//#include<sys/mman.h>
// 
  int munmap(void *start,size_t length);
// 
//����˵��  munmap()����ȡ������start��ָ��ӳ���ڴ���ʼ��ַ������length������ȡ�����ڴ��С�������̽���������exec��غ�����ִ����������ʱ��ӳ���ڴ���Զ���������رն�Ӧ���ļ�������ʱ������ӳ�䡣
// 
//����ֵ  ������ӳ��ɹ��򷵻�0�����򷵻أ�1������ԭ�����errno�д������EINVAL
// 
//����  start��length ���Ϸ���
// 
//����  �ο�mmap����
// 
//�� 
//
// 
//����ʱ��ƪ====================================================================================
//
//�� 
//
// 
//
// 
//asctime����ʱ����������ַ�����ʽ��ʾ��  
//��غ���  time��ctime��gmtime��localtime
// 
//��ͷ�ļ�  #include<time.h>
// 
  char * asctime(const struct tm * timeptr);
// 
//����˵��  asctime()������timeptr��ָ��tm�ṹ�е���Ϣת������ʵ������ʹ�õ�ʱ�����ڱ�ʾ������Ȼ�󽫽�����ַ�����̬���ء��˺����Ѿ���ʱ��ת���ɵ���ʱ�䣬�ַ�����ʽΪ:��Wed Jun 30 21:49:08 1993\n��
// 
//����ֵ  ���ٵ�����ص�ʱ�����ں��������ַ������ܻᱻ�ƻ����˺�����ctime��ͬ�����ڴ���Ĳ����ǲ�ͬ�Ľṹ��
// 
//����˵��  ����һ�ַ�����ʾĿǰ���ص�ʱ�����ڡ�
// 
//����  #include <time.h>
//main()
//{
//time_t timep;
//time (&timep);
//printf(��%s��,asctime(gmtime(&timep)));
//}
// 
//ִ��  Sat Oct 28 02:10:06 2000
// 
//�� 
//
// 
//
// 
//ctime����ʱ����������ַ�����ʽ��ʾ��  
//��غ���  time��asctime��gmtime��localtime
// 
//��ͷ�ļ�  #include<time.h>
// 
  char *ctime(const time_t *timep);
// 
//����˵��  ctime()������timep��ָ��time_t�ṹ�е���Ϣת������ʵ������ʹ�õ�ʱ�����ڱ�ʾ������Ȼ�󽫽�����ַ�����̬���ء��˺����Ѿ���ʱ��ת���ɵ���ʱ�䣬�ַ�����ʽΪ��Wed Jun 30 21 :49 :08 1993\n�������ٵ�����ص�ʱ�����ں��������ַ������ܻᱻ�ƻ���
// 
//����ֵ  ����һ�ַ�����ʾĿǰ���ص�ʱ�����ڡ�
// 
//����  #include<time.h>
//main()
//{
//time_t timep;
//time (&timep);
//printf(��%s��,ctime(&timep));
//}
// 
//ִ��  Sat Oct 28 10 : 12 : 05 2000
// 
//�� 
//
// 
//
// 
//gettimeofday��ȡ��Ŀǰ��ʱ�䣩  
//��غ���  time��ctime��ftime��settimeofday
// 
//��ͷ�ļ�  #include <sys/time.h>
//#include <unistd.h>
// 
  int gettimeofday ( struct timeval * tv , struct timezone * tz )
// 
//����˵��  gettimeofday()���Ŀǰ��ʱ����tv��ָ�Ľṹ���أ�����ʱ������Ϣ��ŵ�tz��ָ�Ľṹ�С�
//timeval�ṹ����Ϊ:
//struct timeval{
//long tv_sec; /*��*/
//long tv_usec; /*΢��*/
//};
//timezone �ṹ����Ϊ:
//struct timezone{
//int tz_minuteswest; /*��Greenwich ʱ����˶��ٷ���*/
//int tz_dsttime; /*�չ��Լʱ���״̬*/
//};
//���������ṹ��������/usr/include/sys/time.h��tz_dsttime �������״̬����
//DST_NONE /*��ʹ��*/
//DST_USA /*����*/
//DST_AUST /*����*/
//DST_WET /*��ŷ*/
//DST_MET /*��ŷ*/
//DST_EET /*��ŷ*/
//DST_CAN /*���ô�*/
//DST_GB /*���е�*/
//DST_RUM /*��������*/
//DST_TUR /*������*/
//DST_AUSTALT /*���ޣ�1986���Ժ�*/
// 
//����ֵ  �ɹ��򷵻�0��ʧ�ܷ��أ�1������������errno������˵��EFAULTָ��tv��tz��ָ���ڴ�ռ䳬����ȡȨ�ޡ�
// 
//����  #include<sys/time.h>
//#include<unistd.h>
//main(){
//struct timeval tv;
//struct timezone tz;
//gettimeofday (&tv , &tz);
//printf(��tv_sec; %d\n��, tv,.tv_sec) ;
//printf(��tv_usec; %d\n��,tv.tv_usec);
//printf(��tz_minuteswest; %d\n��, tz.tz_minuteswest);
//printf(��tz_dsttime, %d\n��,tz.tz_dsttime);
//}
// 
//ִ��  tv_sec: 974857339
//tv_usec:136996
//tz_minuteswest:-540
//tz_dsttime:0
// 
//�� 
//
// 
//
// 
//gmtime��ȡ��Ŀǰʱ������ڣ�  
//��غ���  time,asctime,ctime,localtime
// 
//��ͷ�ļ�  #include<time.h>
// 
  struct tm*gmtime(const time_t*timep);
// 
//����˵��  gmtime()������timep ��ָ��time_t �ṹ�е���Ϣת������ʵ������ʹ�õ�ʱ�����ڱ�ʾ������Ȼ�󽫽���ɽṹtm���ء�
//�ṹtm�Ķ���Ϊ
//struct tm
//{
//int tm_sec;
//int tm_min;
//int tm_hour;
//int tm_mday;
//int tm_mon;
//int tm_year;
//int tm_wday;
//int tm_yday;
//int tm_isdst;
//};
//int tm_sec ����Ŀǰ������������ΧΪ0-59����������61��
//int tm_min ����Ŀǰ��������Χ0-59
//int tm_hour ����ҹ�����ʱ������ΧΪ0-23
//int tm_mday Ŀǰ�·ݵ���������Χ01-31
//int tm_mon ����Ŀǰ�·ݣ���һ�����𣬷�Χ��0-11
//int tm_year ��1900 ���������������
//int tm_wday һ���ڵ�������������һ���𣬷�ΧΪ0-6
//int tm_yday �ӽ���1��1�������������������ΧΪ0-365
//int tm_isdst �չ��Լʱ������
//�˺������ص�ʱ������δ��ʱ��ת��������UTCʱ�䡣
// 
//����ֵ  ���ؽṹtm����ĿǰUTC ʱ��
// 
//����  #include <time.h>
//main(){
//char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
//time_t timep;
//struct tm *p;
//time(&timep);
//p=gmtime(&timep);
//printf(��%d%d%d��,(1900+p->tm_year), (1+p->tm_mon),p->tm_mday);
//printf(��%s%d;%d;%d\n��, wday[p->tm_wday], p->tm_hour, p->tm_min, p->tm_sec);
//}
// 
//ִ��  2000/10/28 Sat 8:15:38
// 
//�� 
//
// 
//
// 
//localtime��ȡ�õ���Ŀǰʱ������ڣ�  
//��غ���  time, asctime, ctime, gmtime
// 
//��ͷ�ļ�  #include<time.h>
// 
  struct tm *localtime(const time_t * timep);
// 
//����˵��  localtime()������timep��ָ��time_t�ṹ�е���Ϣת������ʵ������ʹ�õ�ʱ�����ڱ�ʾ������Ȼ�󽫽���ɽṹtm���ء��ṹtm�Ķ�����ο�gmtime()���˺������ص�ʱ�������Ѿ�ת���ɵ���ʱ����
// 
//����ֵ  ���ؽṹtm����Ŀǰ�ĵ���ʱ�䡣
// 
//����  #include<time.h>
//main(){
//char *wday[]={��Sun��,��Mon��,��Tue��,��Wed��,��Thu��,��Fri��,��Sat��};
//time_t timep;
//struct tm *p;
//time(&timep);
//p=localtime(&timep); /*ȡ�õ���ʱ��*/
//printf (��%d%d%d ��, (1900+p->tm_year),( l+p->tm_mon), p->tm_mday);
//printf(��%s%d:%d:%d\n��, wday[p->tm_wday],p->tm_hour, p->tm_min, p->tm_sec);
//}
// 
//ִ��  2000/10/28 Sat 11:12:22
// 
//�� 
//
// 
//
// 
//mktime����ʱ��ṹ����ת���ɾ�����������  
//��غ���  time��asctime��gmtime��localtime
// 
//��ͷ�ļ�  #include<time.h>
// 
  time_t mktime(strcut tm * timeptr);
// 
//����˵��  mktime()����������timeptr��ָ��tm�ṹ����ת���ɴӹ�Ԫ1970��1��1��0ʱ0��0 �����������UTCʱ����������������
// 
//����ֵ  ���ؾ�����������
// 
//����  /* ��time()ȡ��ʱ�䣨������������localtime()
//ת����struct tm ������mktine������struct tmת����ԭ��������*/
//#include<time.h>
//main()
//{
//time_t timep;
//strcut tm *p;
//time(&timep);
//printf(��time() : %d \n��,timep);
//p=localtime(&timep);
//timep = mktime(p);
//printf(��time()->localtime()->mktime():%d\n��,timep);
//}
// 
//ִ��  time():974943297
//time()->localtime()->mktime():974943297
// 
//�� 
//
// 
//
// 
//settimeofday������Ŀǰʱ�䣩  
//��غ���  time��ctime��ftime��gettimeofday
// 
//��ͷ�ļ�  #include<sys/time.h>
//#include<unistd.h>
// 
  int settimeofday ( const struct timeval *tv,const struct timezone *tz);
// 
//����˵��  settimeofday()���Ŀǰʱ�������tv��ָ�Ľṹ��Ϣ������ʱ����Ϣ�����tz��ָ�Ľṹ����ϸ��˵����ο�gettimeofday()��ע�⣬ֻ��rootȨ�޲���ʹ�ô˺����޸�ʱ�䡣
// 
//����ֵ  �ɹ��򷵻�0��ʧ�ܷ��أ�1������������errno��
// 
//�������  EPERM ������rootȨ�޵���settimeofday������Ȩ�޲�����
//EINVAL ʱ����ĳ�������ǲ���ȷ�ģ��޷���ȷ����ʱ�䡣
// 
//�� 
//
// 
//
// 
//time��ȡ��Ŀǰ��ʱ�䣩  
//��غ���  ctime��ftime��gettimeofday
// 
//��ͷ�ļ�  #include<time.h>
// 
  time_t time(time_t *t);
// 
//����˵��  �˺����᷵�شӹ�Ԫ1970��1��1�յ�UTCʱ���0ʱ0��0���������������������������t ���ǿ�ָ��Ļ����˺���Ҳ�Ὣ����ֵ�浽tָ����ָ���ڴ档
// 
//����ֵ  �ɹ��򷵻�������ʧ���򷵻�((time_t)-1)ֵ������ԭ�����errno�С�
// 
//����  #include<time.h>
//mian()
//{
//int seconds= time((time_t*)NULL);
//printf(��%d\n��,seconds);
//}
// 
//ִ��  9.73E+08
// 
//�� 
//
// 
//�ڴ漰�ַ�������ƪ ====================================================================================
//�� 
//
// 
//
// 
//bcmp���Ƚ��ڴ����ݣ�  
//��غ���  bcmp��strcasecmp��strcmp��strcoll��strncmp��strncasecmp
// 
//��ͷ�ļ�  #include<string.h>
// 
  int bcmp ( const void *s1,const void * s2,int n);
// 
//����˵��  bcmp()�����Ƚ�s1��s2��ָ���ڴ�����ǰn���ֽڣ�������nΪ0���򷵻�0��
// 
//����ֵ  ������s1 ��s2 ��ָ���ڴ����ݶ���ȫ��ͬ�򷵻�0 ֵ�����򷵻ط���ֵ��
// 
//����˵��  ����ʹ��memcmp()ȡ����
// 
//����  �ο�memcmp()��
// 
//�� 
//
// 
//
// 
//bcopy�������ڴ����ݣ�  
//��غ���  memccpy��memcpy��memmove��strcpy��ctrncpy
// 
//��ͷ�ļ�  #include <string.h>
// 
  void bcopy ( const void *src,void *dest ,int n);
// 
//����˵��  bcopy()��memcpy()һ��������������src��ָ���ڴ�����ǰn���ֽڵ�dest��ָ�ĵ�ַ����������src��dest�ڴ�������ʱ���෴��λ�á�
// 
//����ֵ  
// 
//����˵��  ����ʹ��memcpy()ȡ��
// 
//����  #include<string.h>
//main()
//{
//char dest[30]=��string(a)��;
//char src[30]=��string\0string��;
//int i;
//bcopy(src,dest,30);/* srcָ�����ǰ*/
//printf(bcopy(): ��)
//for(i=0;i<30;i++)
//printf(��%c��,dest[i]);
//memcpy(dest src,30); /*destָ�����Ǯ*/
//printf(��\nmemcpy() : ��);
//for(i=0;i<30;i++)
//printf(��%c��,dest[i]);
// 
//ִ��  bcopy() : string string
//memcpy() :string sring
// 
//�� 
//
// 
//
// 
//bzero����һ���ڴ�����ȫ��Ϊ�㣩  
//��غ���  memset��swab
// 
//��ͷ�ļ�  #include<string.h>
// 
  void bzero(void *s,int n)��
// 
//����˵��  bzero()�Ὣ����s��ָ���ڴ�����ǰn���ֽڣ�ȫ����Ϊ��ֵ���൱�ڵ���memset((void*)s,0,size_tn);
// 
//����ֵ  
// 
//����˵��  ����ʹ��memsetȡ��
// 
//����  �ο�memset()��
// 
//�� 
//
// 
//
// 
//index�������ַ����е�һ�����ֵ�ָ���ַ���  
//��غ���  rindex��srechr��strrchr
// 
//��ͷ�ļ�  #include<string.h>
// 
  char * index( const char *s, int c);
// 
//����˵��  index()�����ҳ�����s�ַ����е�һ�����ֵĲ���c��ַ��Ȼ�󽫸��ַ����ֵĵ�ַ���ء��ַ��������ַ�(NULL)Ҳ��Ϊ�ַ���һ���֡�
// 
//����ֵ  ����ҵ�ָ�����ַ��򷵻ظ��ַ����ڵ�ַ�����򷵻�0��
// 
//����  #include<string.h>
//main()
//{
//char *s =��0123456789012345678901234567890��;
//char *p;
//p =index(s,��5��);
//printf(%s\n��,p);
//}
// 
//ִ��  5.68E+25
// 
//�� 
//
// 
//
// 
//memccpy�������ڴ����ݣ�  
//��غ���  bcopy��memcpy��memmove��strcpy��strncpy
// 
//��ͷ�ļ�  #include<string.h>
// 
  void * memccpy(void *dest, const void * src, int c,size_t n);
// 
//����˵��  memccpy()��������src��ָ���ڴ�����ǰn���ֽڵ�dest��ָ�ĵ�ַ�ϡ���memcpy()��ͬ���ǣ�memccpy()���ڸ���ʱ������c�Ƿ���֣������򷵻�dest��ֵΪc����һ���ֽڵ�ַ��
// 
//����ֵ  ����ָ��dest��ֵΪc����һ���ֽ�ָ�롣����ֵΪ0��ʾ��src��ָ�ڴ�ǰn���ֽ���û��ֵΪc���ֽڡ�
// 
//����  #include<string.h>
//main()
//{
//char a[]="string[a]";
//char b[]="string(b)";
//memccpy(a,b,'B',sizeof(b));
//printf("memccpy():%s\n",a);
//}
// 
//ִ��  memccpy():string(b)
// 
//�� 
//
// 
//
// 
//memchr����ĳһ�ڴ淶Χ�в���һ�ض��ַ���  
//��غ���  index��rindex��strchr��strpbrk��strrchr��strsep��strspn��strstr
// 
//��ͷ�ļ�  #include<string.h>
// 
  void * memchr(const void *s,int c,size_t n);
// 
//����˵��  memchr()��ͷ��ʼ��Ѱs��ָ���ڴ�����ǰn���ֽڣ�ֱ�����ֵ�һ��ֵΪc���ֽڣ��򷵻�ָ����ֽڵ�ָ�롣
// 
//����ֵ  ����ҵ�ָ�����ֽ��򷵻ظ��ֽڵ�ָ�룬���򷵻�0��
// 
//����  #include <string.h>
//main()
//{
//char *s="0123456789012345678901234567890";
//char *p;
//p=memchr(s,'5',10);
//printf("%s\n",p);
//}
// 
//ִ��  5.68E+25
// 
//�� 
//
// 
//
// 
//memcmp���Ƚ��ڴ����ݣ�  
//��غ���  bcmp��strcasecmp��strcmp��strcoll��strncmp��strncasecmp
// 
//��ͷ�ļ�  #include<string.h>
// 
  int memcmp (const void *s1,const void *s2,size_t n);
// 
//����˵��  memcmp()�����Ƚ�s1��s2��ָ���ڴ�����ǰn���ַ����ַ�����С�ıȽ�����ASCII����ϵ�˳������������˳����Ϊ�ַ���ֵ��memcmp()���Ƚ�s1��һ���ַ�ֵ��ȥs2��һ���ַ���ֵ������Ϊ0���ټ����Ƚ��¸��ַ�������ֵ��Ϊ0�򽫲�ֵ���ء����磬�ַ���"Ac"��"ba"�Ƚ���᷵���ַ�'A'(65)��'b'(98)�Ĳ�ֵ(��33)��
// 
//����ֵ  ������s1��s2��ָ���ڴ����ݶ���ȫ��ͬ�򷵻�0ֵ��s1������s2�򷵻ش���0��ֵ��s1��С��s2�򷵻�С��0��ֵ��
// 
//����  #include<string.h>
//main()
//{
//char *a ="aBcDeF";
//char *b="AbCdEf";
//char *c="aacdef";
//char *d="aBcDeF";
//printf("memcmp(a,b):%d\n",memcmp((void*)a,(void*) b,6));
//printf("memcmp(a,c):%d\n",memcmp((void*)a,(void*) c,6));
//printf("memcmp(a,d):%d\n",memcmp((void*)a,(void*) d,6));
// 
//ִ��  memcmp(a,b):1 /*�ַ���a>�ַ���b������1*/
//memcmp(a,c):-1 /* �ַ���a<�ַ���c,���أ�1*/
//memcmp(a,d):0 /*�ַ���a���ַ���d������0*/
// 
//�� 
//
// 
//
// 
//memcpy�������ڴ����ݣ�  
//��غ���  bcopy��memccpy��memcpy��memmove��strcpy��strncpy
// 
//��ͷ�ļ�  #include<string.h>
// 
  void * memcpy (void * dest ,const void *src, size_t n);
// 
//����˵��  memcpy()��������src��ָ���ڴ�����ǰn���ֽڵ�dest��ָ���ڴ��ַ�ϡ���strcpy()��ͬ���ǣ�memcpy()�������ĸ���n���ֽڣ�������Ϊ�����ַ�������'\0'��������
// 
//����ֵ  ����ָ��dest��ָ�롣
// 
//����˵��  ָ��src��dest��ָ���ڴ����򲻿��ص���
// 
//����  #include<string.h>
//main()
//{
//char a[30]="string (a)";
//char b[30]="string\0string";
//int i;
//strcpy(a,b);
//printf("strcpy():");
//for(i=0;i<30;i++)
//printf("%c",a[i]);
//memcpy(a,b,30);
//printf("\nmemcpy() :");
//for(i=0;i<30;i++)
//printf("%c",a[i]);
//}
// 
//ִ��  strcpy() : string a )
//memcpy() : string string
// 
//�� 
//
// 
//
// 
//memmove�������ڴ����ݣ�  
//��غ���  bcopy��memccpy��memcpy��strcpy��strncpy
// 
//��ͷ�ļ�  #include<string.h>
// 
  void * memmove(void *dest,const void *src,size_t n);
// 
//����˵��  memmove()��memcpy()һ��������������src��ָ���ڴ�����ǰn���ֽڵ�dest��ָ�ĵ�ַ�ϡ���ͬ���ǣ���src��dest��ָ���ڴ������ص�ʱ��memmove()��Ȼ������ȷ�Ĵ�������ִ��Ч���ϻ��ʹ��memcpy()����Щ��
// 
//����ֵ  ����ָ��dest��ָ�롣
// 
//����˵��  ָ��src��dest��ָ���ڴ���������ص���
// 
//����  �ο�memcpy()��
// 
//�� 
//
// 
//
// 
//memset����һ���ڴ�ռ�����ĳֵ��  
//��غ���  bzero��swab
// 
//��ͷ�ļ�  #include<string.h>
// 
  void * memset (void *s ,int c, size_t n);
// 
//����˵��  memset()�Ὣ����s��ָ���ڴ�����ǰn���ֽ��Բ���c���룬Ȼ�󷵻�ָ��s��ָ�롣�ڱ�д����ʱ������Ҫ��ĳһ��������ʼ����memset()���൱���㡣
// 
//����ֵ  ����ָ��s��ָ�롣
// 
//����˵��  ����c������Ϊint�� ��������unsigned char �����Է�Χ��0��255֮�䡣
// 
//����  #include <string.h>
//main()
//{
//char s[30];
//memset (s,'A',sizeof(s));
//s[30]='\0';
//printf("%s\n",s);
//}
// 
//ִ��  AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
// 
//�� 
//
// 
//
// 
//rindex�������ַ��������һ�����ֵ�ָ���ַ���  
//��غ���  index��memchr��strchr��strrchr
// 
//��ͷ�ļ�  #include<string.h>
// 
  char * rindex( const char *s,int c);
// 
//����˵��  rindex()�����ҳ�����s�ַ��������һ�����ֵĲ���c��ַ��Ȼ�󽫸��ַ����ֵĵ�ַ���ء��ַ��������ַ�(NULL)Ҳ��Ϊ�ַ���һ���֡�
// 
//����ֵ  ����ҵ�ָ�����ַ��򷵻ظ��ַ����ڵĵ�ַ�����򷵻�0��
// 
//����  #include <string.h>
//mian()
//{
//char *s ="0123456789012345678901234567890";
//char *p;
//p=rindex(s,'5');
//printf("%s\n",p);
//}
// 
//ִ��  567890
// 
//�� 
//
// 
//
// 
//strcasecmp�����Դ�Сд�Ƚ��ַ�����  
//��غ���  bcmp��memcmp��strcmp��strcoll��strncmp
// 
//��ͷ�ļ�  #include<string.h>
// 
  int strcasecmp (const char *s1, const char *s2);
// 
//����˵��  strcasecmp()�����Ƚϲ���s1��s2�ַ������Ƚ�ʱ���Զ����Դ�Сд�Ĳ��졣
// 
//����ֵ  ������s1��s2�ַ�����ͬ�򷵻�0��s1���ȴ���s2�����򷵻ش���0 ��ֵ��s1 ������С��s2 �����򷵻�С��0��ֵ��
// 
//����  #include <string.h>
//main()
//{
//char *a="aBcDeF";
//char *b="AbCdEf";
//if(!strcasecmp(a,b))
//printf("%s=%s\n",a,b);
//}
// 
//ִ��  aBcDeF=AbCdEf
// 
//�� 
//
// 
//
// 
//strcat���������ַ�����  
//��غ���  bcopy��memccpy��memcpy��strcpy��strncpy
// 
//��ͷ�ļ�  #include <string.h>
// 
  char *strcat (char *dest,const char *src);
// 
//����˵��  strcat()�Ὣ����src�ַ�������������dest��ָ���ַ���β����һ������destҪ���㹻�Ŀռ�������Ҫ�������ַ�����
// 
//����ֵ  ���ز���dest���ַ�����ʼ��ַ
// 
//����  #include <string.h.>
//main()
//{
//char a[30]="string(1)";
//char b[]="string(2)";
//printf("before strcat() : %s\n",a);
//printf("after strcat() : %s\n",strcat(a,b));
//}
// 
//ִ��  before strcat () : string(1)
//after strcat () : string(1)string(2)
// 
//�� 
//
// 
//
// 
//strchr�������ַ����е�һ�����ֵ�ָ���ַ���  
//��غ���  index��memchr��rinex��strbrk��strsep��strspn��strstr��strtok
// 
//��ͷ�ļ�  #include<string.h>
// 
  char * strchr (const char *s,int c);
// 
//����˵��  strchr()�����ҳ�����s�ַ����е�һ�����ֵĲ���c��ַ��Ȼ�󽫸��ַ����ֵĵ�ַ���ء�
// 
//����ֵ  ����ҵ�ָ�����ַ��򷵻ظ��ַ����ڵ�ַ�����򷵻�0��
// 
//����  #include<string.h>
//main()
//{
//char *s=0123456789012345678901234567890��;
//char *p;
//p=strchr(s,'5');
//printf("%s\n",p);
//}
// 
//ִ��  5.68E+25
// 
//�� 
//
// 
//
// 
//strcmp���Ƚ��ַ�����  
//��غ���  bcmp��memcmp��strcasecmp��strncasecmp��strcoll
// 
//��ͷ�ļ�  #include<string.h>
// 
  int strcmp(const char *s1,const char *s2);
// 
//����˵��  strcmp()�����Ƚϲ���s1��s2�ַ������ַ�����С�ıȽ�����ASCII ����ϵ�˳������������˳����Ϊ�ַ���ֵ��strcmp()���Ƚ�s1��һ���ַ�ֵ��ȥs2��һ���ַ�ֵ������ֵΪ0���ټ����Ƚ��¸��ַ�������ֵ��Ϊ0�򽫲�ֵ���ء������ַ���"Ac"��"ba"�Ƚ���᷵���ַ�"A"(65)��'b'(98)�Ĳ�ֵ(��33)��
// 
//����ֵ  ������s1��s2�ַ�����ͬ�򷵻�0��s1������s2�򷵻ش���0��ֵ��s1��С��s2�򷵻�С��0 ��ֵ��
// 
//����  #include<string.h>
//main()
//{
//char *a="aBcDeF";
//char *b="AbCdEf";
//char *c="aacdef";
//char *d="aBcDeF";
//printf("strcmp(a,b) : %d\n",strcmp(a,b));
//printf("strcmp(a,c) : %d\n",strcmp(a,c));
//printf("strcmp(a,d) : %d\n",strcmp(a,d));
//}
// 
//ִ��  strcmp(a,b) : 32
//strcmp(a,c) :-31
//strcmp(a,d) : 0
// 
//�� 
//
// 
//
// 
//strcoll������Ŀǰ������ַ����д������Ƚ��ַ�����  
//��غ���  strcmp��bcmp��memcmp��strcasecmp��strncasecmp
// 
//��ͷ�ļ�  #include<string.h>
// 
  int strcoll( const char *s1, const char *s2);
// 
//����˵��  strcoll()������������LC_COLLATE��ָ�����������д������Ƚ�s1��s2 �ַ�����
// 
//����ֵ  ������s1��s2�ַ�����ͬ�򷵻�0��s1������s2�򷵻ش���0��ֵ��s1��С��s2�򷵻�С��0 ��ֵ��
// 
//����˵��  ��LC_COLLATEΪ"POSIX"��"C"����strcoll()��strcmp()������ȫ��ͬ��
// 
//����  �ο�strcmp()��
// 
//�� 
//
// 
//
// 
//strcpy�������ַ�����  
//��غ���  bcopy��memcpy��memccpy��memmove
// 
//��ͷ�ļ�  #include<string.h>
// 
  char *strcpy(char *dest,const char *src);
// 
//����˵��  strcpy()�Ὣ����src�ַ�������������dest��ָ�ĵ�ַ��
// 
//����ֵ  ���ز���dest���ַ�����ʼ��ַ��
// 
//����˵��  �������dest��ָ���ڴ�ռ䲻���󣬿��ܻ���ɻ������(buffer Overflow)�Ĵ���������ڱ�д����ʱ���ر����⣬������strncpy()��ȡ����
// 
//����  #include<string.h>
//main()
//{
//char a[30]="string(1)";
//char b[]="string(2)";
//printf("before strcpy() :%s\n",a);
//printf("after strcpy() :%s\n",strcpy(a,b));
//}
// 
//ִ��  before strcpy() :string(1)
//after strcpy() :string(2)
// 
//�� 
//
// 
//
// 
//strcspn�������ַ�������������ָ���ַ������ݵ��ַ�����  
//��غ���  strspn
// 
//��ͷ�ļ�  #inclued<string.h>
// 
  size_t strcspn ( const char *s,const char * reject);
// 
//����˵��  strcspn()�Ӳ���s�ַ����Ŀ�ͷ�����������ַ�������Щ�ַ�����ȫ���ڲ���reject ��ָ���ַ����С��򵥵�˵����strcspn()���ص���ֵΪn��������ַ���s��ͷ������n���ַ��������ַ���reject�ڵ��ַ���
// 
//����ֵ  �����ַ���s��ͷ���������ַ���reject�ڵ��ַ���Ŀ��
// 
//����  #include <string.h>
//main()
//{
//char *str="Linux was first developed for 386/486-based pcs.";
//printf("%d\n",strcspn(str," "));
//printf("%d\n",strcspn(str,"/-"));
//printf("%d\n",strcspn(str,"1234567890"));
//}
// 
//ִ��  5 /*ֻ���㵽�� ���ĳ��֣����Է��ء�Linux���ĳ���*/
//33 /*���㵽���֡�/���򡰣��������Է��ص���6���ĳ���*/
//30 /* ���㵽���������ַ�Ϊֹ�����Է��ء�3������ǰ�ĳ���*/
// 
//�� 
//
// 
//
// 
//strdup�������ַ�����  
//��غ���  calloc��malloc��realloc��free
// 
//��ͷ�ļ�  #include<string.h>
// 
  char * strdup( const char *s);
// 
//����˵��  strdup()������maolloc()���������s�ַ�����ͬ�Ŀռ��С��Ȼ�󽫲���s�ַ��������ݸ��Ƶ����ڴ��ַ��Ȼ��Ѹõ�ַ���ء��õ�ַ����������free()���ͷš�
// 
//����ֵ  ����һ�ַ���ָ�룬��ָ��ָ���ƺ�����ַ�����ַ��������NULL��ʾ�ڴ治�㡣
// 
//����  #include<string.h>
//main()
//{
//char a[]="strdup";
//char *b;
//b=strdup(a);
//printf("b[ ]=\"%s\"\n",b);
//}
// 
//ִ��  b[ ]="strdup"
// 
//�� 
//
// 
//
// 
//strlen�������ַ������ȣ�  
//��غ���  
// 
//��ͷ�ļ�  #include<string.h>
// 
  size_t strlen (const char *s);
// 
//����˵��  strlen()��������ָ�����ַ���s�ĳ��ȣ������������ַ�"\0"��
// 
//����ֵ  �����ַ���s���ַ�����
// 
//����  /*ȡ���ַ���str�ĳ���*/
//#include<string.h>
//main()
//{
//char *str = "12345678";
//printf("str length = %d\n", strlen(str));
//}
// 
//ִ��  str length = 8
// 
//�� 
//
// 
//
// 
//strncasecmp�����Դ�Сд�Ƚ��ַ�����  
//��غ���  bcmp��memcmp��strcmp��strcoll��strncmp
// 
//��ͷ�ļ�  #include<string.h>
// 
  int strncasecmp(const char *s1,const char *s2,size_t n);
// 
//����˵��  strncasecmp()�����Ƚϲ���s1��s2�ַ���ǰn���ַ����Ƚ�ʱ���Զ����Դ�Сд�Ĳ��졣
// 
//����ֵ  ������s1��s2 �ַ�����ͬ�򷵻�0��s1 ������s2�򷵻ش���0��ֵ��s1��С��s2�򷵻�С��0 ��ֵ��
// 
//����  #include<string.h>
//main()
//{
//char *a="aBcDeF";
//char *b="AbCdEf";
//if(!strncasecmp(a,b))
//printf("%s =%s\n",a,b);
//}
// 
//ִ��  aBcDef=AbCdEf
// 
//�� 
//
// 
//
// 
//strncat���������ַ�����  
//��غ���  bcopy��memccpy��memecpy��strcpy��strncpy
// 
//��ͷ�ļ�  #inclue <string.h>
// 
  char * strncat(char *dest,const char *src,size_t n);
// 
//����˵��  strncat()�Ὣ����src�ַ�������n���ַ�������dest��ָ���ַ���β����һ������destҪ���㹻�Ŀռ�������Ҫ�������ַ�����
// 
//����ֵ  ���ز���dest���ַ�����ʼ��ַ��
// 
//����  #include <string.h>
//main()
//{
//char a[30]="string(1)";
//char b[]="string(2)";
//printf("before strnact() :%s\n", a);
//printf("after strncat() :%s\n", strncat(a,b,6));
//}
// 
//ִ��  before strnact() : string(1)
//after strncat() : string(1) string
// 
//�� 
//
// 
//
// 
//strncpy�������ַ�����  
//��غ���  bcopy��memccpy��memcpy��memmove
// 
//��ͷ�ļ�  #include<string.h>
// 
  char * strncpy(char *dest,const char *src,size_t n);
// 
//����˵��  strncpy()�Ὣ����src�ַ�������ǰn���ַ�������dest��ָ�ĵ�ַ��
// 
//����ֵ  ���ز���dest���ַ�����ʼ��ַ��
// 
//����  #inclue <string.h>
//main()
//{
//char a[30]="string(1)";
//char b[]="string(2)";
//printf("before strncpy() : %s\n",a);
//printf("after strncpy() : %s\n",strncpy(a,b,6));
//}
// 
//ִ��  before strncpy() : string(1)
//after strncpy() : string(1)
// 
//�� 
//
// 
//
// 
//strpbrk�������ַ����е�һ�����ֵ�ָ���ַ���  
//��غ���  index��memchr��rindex��strpbrk��strsep��strspn��strstr��strtok
// 
//��ͷ�ļ�  #include <include.h>
// 
  char *strpbrk(const char *s,const char *accept);
// 
//����˵��  strpbrk()�����ҳ�����s �ַ��������ȳ��ִ��ڲ���accept �ַ����е������ַ���
// 
//����ֵ  ����ҵ�ָ�����ַ��򷵻ظ��ַ����ڵ�ַ�����򷵻�0��
// 
//����  #include <string.h>
//main()
//{
//char *s="0123456789012345678901234567890";
//char *p;
//p=strpbrk(s,"a1 839"); /*1��������s�ַ������ҵ�*/
//printf("%s\n",p);
//p=strprk(s,"4398");/*3 ��������s �ַ������ҵ�*/
//printf("%s\n",p);
// 
//ִ��  1.23E+29
// 
//�� 
//
// 
//
// 
//strrchr�������ַ����������ֵ�ָ���ַ���  
//��غ���  index��memchr��rindex��strpbrk��strsep��strspn��strstr��strtok
// 
//��ͷ�ļ�  #include<string.h>
// 
  char * strrchr(const char *s, int c);
// 
//����˵��  strrchr()�����ҳ�����s�ַ��������һ�����ֵĲ���c��ַ��Ȼ�󽫸��ַ����ֵĵ�ַ���ء�
// 
//����ֵ  ����ҵ�ָ�����ַ��򷵻ظ��ַ����ڵ�ַ�����򷵻�0��
// 
//����  #include<string.h>
//main()
//{
//char *s="0123456789012345678901234567890";
//char *p;
//p=strrchr(s,'5');
//printf("%s\n",p);
//}
// 
//ִ��  567890
// 
//�� 
//
// 
//
// 
//strspn�������ַ�������������ָ���ַ������ݵ��ַ�����  
//��غ���  strcspn��strchr��strpbrk��strsep��strstr
// 
//��ͷ�ļ�  #include<string.h>
// 
  size_t strspn (const char *s,const char * accept);
// 
//����˵��  strspn()�Ӳ���s �ַ����Ŀ�ͷ�����������ַ�������Щ�ַ�����ȫ��accept ��ָ�ַ����е��ַ����򵥵�˵����strspn()���ص���ֵΪn��������ַ���s ��ͷ������n ���ַ����������ַ���accept�ڵ��ַ���
// 
//����ֵ  �����ַ���s��ͷ���������ַ���accept�ڵ��ַ���Ŀ��
// 
//����  #include<string.h>
//main()
//{
//char *str="Linux was first developed for 386/486-based PCs.";
//char *t1="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
//printf("%d\n",strspn(str,t1));
//}
// 
//ִ��  5 /*�����Сд��ĸ���������� �������Է���Linux�ĳ��ȡ�*/
// 
//�� 
//
// 
//
// 
//strstr����һ�ַ����в���ָ�����ַ�����  
//��غ���  index��memchr��rindex��strchr��strpbrk��strsep��strspn��strtok
// 
//��ͷ�ļ�  #include<string.h>
// 
  char *strstr(const char *haystack,const char *needle);
// 
//����˵��  strstr()����ַ���haystack ����Ѱ�ַ���needle��������һ�γ��ֵĵ�ַ���ء�
// 
//����ֵ  ����ָ���ַ�����һ�γ��ֵĵ�ַ�����򷵻�0��
// 
//����  #include<string.h>
//main()
//{
//char * s="012345678901234567890123456789";
//char *p;
//p= strstr(s,"901");
//printf("%s\n",p);
//}
// 
//ִ��  9.01E+21
// 
//�� 
//
// 
//
// 
//strtok���ָ��ַ�����  
//��غ���  index��memchr��rindex��strpbrk��strsep��strspn��strstr
// 
//��ͷ�ļ�  #include<string.h>
// 
  char * strtok(char *s,const char *delim);
// 
//����˵��  strtok()�������ַ����ָ��һ����Ƭ�Ρ�����sָ�����ָ���ַ���������delim��Ϊ�ָ��ַ�������strtok()�ڲ���s���ַ����з��ֵ�����delim�ķָ��ַ�ʱ��Ὣ���ַ���Ϊ\0 �ַ����ڵ�һ�ε���ʱ��strtok()����������s�ַ���������ĵ����򽫲���s���ó�NULL��ÿ�ε��óɹ��򷵻���һ���ָ����ַ���ָ�롣
// 
//����ֵ  ������һ���ָ����ַ���ָ�룬������޴ӷָ��򷵻�NULL��
// 
//����  #include<string.h>
//main()
//{
//char s[]="ab-cd : ef;gh :i-jkl;mnop;qrs-tu: vwx-y;z";
//char *delim="-: ";
//char *p;
//printf("%s ";strtok(s,delim));
//while((p=strtok(NULL,delim)))printf("%s ",p);
//printf("\n");
//}
// 
//ִ��  ab cd ef;gh i jkl;mnop;qrs tu vwx y;z /*����:�ַ��Ѿ���\0 �ַ�ȡ��*/
// 
//�� 
//
// 
//������ѧ����ƪ====================================================================================
//�� 
//
// 
//
// 
//abs�������������ľ���ֵ��  
//��غ���  labs, fabs
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  int abs (int j)
// 
//����˵��  abs()�����������j�ľ���ֵ��Ȼ�󽫽�����ء�
// 
//����ֵ  ���ز���j�ľ���ֵ�����
// 
//����  #ingclude <stdlib.h>
//main(){
//int ansert;
//answer = abs(-12);
//printf("|-12| = %d\n", answer);
//}
// 
//ִ��  |-12| = 12
// 
//�� 
//
// 
//
// 
//acos��ȡ�����Һ�����ֵ��  
//��غ���  asin , atan , atan2 , cos , sin , tan
// 
//��ͷ�ļ�  #include <math.h>
// 
  double acos (double x);
// 
//����˵��  acos()�����������x�ķ�����ֵ��Ȼ�󽫽�����ء�����x��ΧΪ��1��1֮�䣬�����˷�Χ���ʧ�ܡ�
// 
//����ֵ  ����0��PI֮��ļ���������λΪ���ȣ��ں������нǶȾ��Ի�������ʾ��
// 
//�������  EDOM����x������Χ��
// 
//����˵��  ʹ��GCC����ʱ����룭lm��
// 
//����  #include <math.h>
//main (){
//double angle;
//angle = acos(0.5);
//printf("angle = %f\n", angle);
//}
// 
//ִ��  angle = 1.047198
// 
//�� 
//
// 
//
// 
//asin��ȡ�����Һ���ֵ��  
//��غ���  acos , atan , atan2 , cos , sin , tan
// 
//��ͷ�ļ�  #include <math.h>
// 
  double asin (double x)
// 
//����˵��  asin()�����������x�ķ�����ֵ��Ȼ�󽫽�����ء�����x��ΧΪ��1��1֮�䣬�����˷�Χ���ʧ�ܡ�
// 
//����ֵ  ���أ�PI/2֮PI/2֮��ļ�������
// 
//�������  EDOM����x������Χ
// 
//����˵��  ʹ��GCC����ʱ����룭lm
// 
//����  #include<math.h>
//main()
//{
//double angle;
//angle = asin (0.5);
//printf("angle = %f\n",angle);
//}
// 
//ִ��  angle = 0.523599
// 
//�� 
//
// 
//
// 
//atan��ȡ�����к���ֵ��  
//��غ���  acos��asin��atan2��cos��sin��tan
// 
//��ͷ�ļ�  #include<math.h>
// 
  double atan(double x);
// 
//����˵��  atan()�����������x�ķ�����ֵ��Ȼ�󽫽�����ء�
// 
//����ֵ  ����-PI/2��PI/2֮��ļ�������
// 
//����˵��  ʹ��GCC����ʱ�����-lm
// 
//����  #include<math.h>
//main()
//{
//double angle;
//angle =atan(1);
//printf("angle = %f\n",angle);
//}
// 
//ִ��  angle = 1.570796
// 
//�� 
//
// 
//
// 
//atan2��ȡ�÷����к���ֵ��  
//��غ���  acos��asin��atan��cos��sin��tan
// 
//��ͷ�ļ�  #include<math.h>
// 
  double atan2(double y,double x);
// 
//����˵��  atan2()�����������y/x�ķ�����ֵ��Ȼ�󽫽�����ء�
// 
//����ֵ  ����-PI/2 ��PI/2 ֮��ļ�������
// 
//����˵��  ʹ��GCC����ʱ�����-lm��
// 
//����  #include<math.h>
//main()
//{
//double angle;
//angle = atan2(1,2);
//printf("angle = %f\n", angle);
//}
// 
//ִ��  angle = 0.463648
// 
//�� 
//
// 
//
// 
//ceil��ȡ��С�ڲ�������С��������  
//��غ���  fabs
// 
//��ͷ�ļ�  #include <math.h>
// 
  double ceil (double x);
// 
//����˵��  ceil()�᷵�ز�С�ڲ���x����С����ֵ�������double��̬���ء�
// 
//����ֵ  ���ز�С�ڲ���x����С����ֵ��
// 
//����˵��  ʹ��GCC����ʱ�����-lm��
// 
//����  #include<math.h>
//main()
//{
//double value[ ]={4.8,1.12,-2.2,0};
//int i;
//for (i=0;value[i]!=0;i++)
//printf("%f=>%f\n",value[i],ceil(value[i]));
//}
// 
//ִ��  4.800000=>5.000000
//1.120000=>2.000000
//-2.200000=>-2.000000
// 
//�� 
//
// 
//
// 
//cos��ȡ��������ֵ��  
//��غ���  acos��asin��atan��atan2��sin��tan
// 
//��ͷ�ļ�  #include<math.h>
// 
  double cos(double x);
// 
//����˵��  cos()�����������x ������ֵ��Ȼ�󽫽�����ء�
// 
//����ֵ  ����-1��1֮��ļ�������
// 
//����˵��  ʹ��GCC����ʱ�����-lm��
// 
//����  #include<math.h>
//main()
//{
//double answer = cos(0.5);
//printf("cos (0.5) = %f\n",answer);
//}
// 
//ִ��  cos(0.5) = 0.877583
// 
//�� 
//
// 
//
// 
//cosh��ȡ˫������������ֵ��  
//��غ���  sinh��tanh
// 
//��ͷ�ļ�  #include<math.h>
// 
  double cosh(double x);
// 
//����˵��  cosh()�����������x��˫��������ֵ��Ȼ�󽫽�����ء���ѧ����ʽΪ:(exp(x)+exp(-x))/2��
// 
//����ֵ  ���ز���x��˫��������ֵ��
// 
//����˵��  ʹ��GCC����ʱ�����-lm��
// 
//����  #include<math.h>
//main()
//{
//double answer = cosh(0.5);
//printf("cosh(0.5) = %f\n",answer);
//}
// 
//ִ��  cosh(0.5) = 1.127626
// 
//�� 
//
// 
//
// 
//exp������ָ����  
//��غ���  log��log10��pow
// 
//��ͷ�ļ�  #include<math.h>
// 
  double exp(double x);
// 
//����˵��  exp()����������eΪ�׵�x�η�ֵ����exֵ��Ȼ�󽫽�����ء�
// 
//����ֵ  ����e��x�η���������
// 
//����˵��  ʹ��GCC����ʱ�����-lm��
// 
//����  #include<math.h>
//main()
//{
//double answer;
//answer = exp (10);
//printf("e^10 =%f\n", answer);
//}
// 
//ִ��  e^10 = 22026.465795
// 
//�� 
//
// 
//
// 
//frexp��������������Ϊ������ָ����  
//��غ���  ldexp��modf
// 
//��ͷ�ļ�  #include<math.h>
// 
  double frexp( double x, int *exp);
// 
//����˵��  frexp()����������x �ĸ��������и�ɵ�����ָ������������ֱ�ӷ��أ�ָ������������exp ָ�뷵�أ�������ֵ����2 ��exp�η���Ϊx��ֵ��
// 
//����ֵ  ���ز���x�ĵ������֣�ָ�����������expָ����ָ�ĵ�ַ��
// 
//����˵��  ʹ��GCC����ʱ�����-lm��
// 
//����  #include <math.h>
//main()
//{
//int exp;
//double fraction;
//fraction = frexp (1024,&exp);
//printf("exp = %d\n",exp);
//printf("fraction = %f\n", fraction);
//}
// 
//ִ��  exp = 11
//fraction = 0.500000 /* 0.5*(2^11)=1024*/
// 
//�� 
//
// 
//
// 
//ldexp������2�Ĵη�ֵ��  
//��غ���  frexp
// 
//��ͷ�ļ�  #include<math.h>
// 
  double ldexp(double x,int exp);
// 
//����˵��  ldexp()����������x����2��exp�η�ֵ����x*2exp��
// 
//����ֵ  ���ؼ�������
// 
//����˵��  ʹ��GCC����ʱ�����-lm��
// 
//����:  /* ����3*(2^2)��12 */
//#include<math.h>
//main()
//{
//int exp;
//double x,answer;
//answer = ldexp(3,2);
//printf("3*2^(2) = %f\n",answer);
//}
// 
//ִ��  3*2^(2) = 12.000000
// 
//�� 
//
// 
//
// 
//log��������e Ϊ�׵Ķ���ֵ��  
//��غ���  exp��log10��pow
// 
//��ͷ�ļ�  #include <math.h>
// 
  double log (double x);
// 
//����˵��  log��������������eΪ�׵�x ����ֵ��Ȼ�󽫽�����ء�
// 
//����ֵ  ���ز���x����Ȼ����ֵ��
// 
//�������  EDOM ����xΪ������ERANGE ����xΪ��ֵ����Ķ���ֵ�޶��塣
// 
//����˵��  ʹ��GCC����ʱ�����-lm��
// 
//����  #include<math.h>
//main()
//{
//double answer;
//answer = log (100);
//printf("log(100) = %f\n",answer);
//}
// 
//ִ��  log(100) = 4.605170
// 
//�� 
//
// 
//
// 
//log10��������10 Ϊ�׵Ķ���ֵ��  
//��غ���  exp��log��pow
// 
//��ͷ�ļ�  #include<math.h>
// 
  double log10(double x);
// 
//����˵��  log10()����������10Ϊ�׵�x����ֵ��Ȼ�󽫽�����ء�
// 
//����ֵ  ���ز���x��10Ϊ�׵Ķ���ֵ��
// 
//�������  EDOM����xΪ������RANGE����xΪ��ֵ����Ķ���ֵ�޶��塣
// 
//����˵��  ʹ��GCC����ʱ�����-lm��
// 
//����  #include<math.h>
//main()
//{
//double answer;
//answer = log10(100);
//printf("log10(100) = %f\n",answer);
//}
// 
//ִ��  log10(100) = 2.000000
// 
//�� 
//
// 
//
// 
//pow������η�ֵ��  
//��غ���  exp��log��log10
// 
//��ͷ�ļ�  #include<math.h>
// 
  double pow(double x,double y);
// 
//����˵��  pow()����������xΪ�׵�y�η�ֵ����xyֵ��Ȼ�󽫽�����ء�
// 
//����ֵ  ����x��y�η���������
// 
//�������  EDOM ����xΪ�����Ҳ���y����������
// 
//����˵��  ʹ��GCC����ʱ�����-lm��
// 
//����  #include <math.h>
//main()
//{
//double answer;
//answer =pow(2,10);
//printf("2^10 = %f\n", answer);
//}
// 
//ִ��  2^10 = 1024.000000
// 
//�� 
//
// 
//
// 
//sin��ȡ��������ֵ��  
//��غ���  acos��asin��atan��atan2��cos��tan
// 
//��ͷ�ļ�  #include<math.h>
// 
  double sin(double x);
// 
//����˵��  sin���������������x������ֵ��Ȼ�󽫽�����ء�
// 
//����ֵ  ����-1 ��1֮��ļ�������
// 
//����˵��  ʹ��GCC����ʱ�����-lm��
// 
//����  #include<math.h>
//main()
//{
//double answer = sin (0.5);
//printf("sin(0.5) = %f\n",answer);
//}
// 
//ִ��  sin(0.5) = 0.479426
// 
//�� 
//
// 
//
// 
//sinh��ȡ˫������������ֵ��  
//��غ���  cosh��tanh
// 
//��ͷ�ļ�  #include<math.h>
// 
  double sinh( double x);
// 
//����˵��  sinh()�����������x��˫��������ֵ��Ȼ�󽫽�����ء���ѧ����ʽΪ:(exp(x)-exp(-x))/2��
// 
//����ֵ  ���ز���x��˫��������ֵ��
// 
//����˵��  ʹ��GCC����ʱ�����-lm��
// 
//����  #include<math.h>
//main()
//{
//double answer = sinh (0.5);
//printf("sinh(0.5) = %f\n",answer);
//}
// 
//ִ��  sinh(0.5) = 0.521095
// 
//�� 
//
// 
//
// 
//sqrt������ƽ����ֵ��  
//��غ���  hypotq
// 
//��ͷ�ļ�  #include<math.h>
// 
  double sqrt(double x);
// 
//����˵��  sqrt()�����������x��ƽ������Ȼ�󽫽�����ء�����x����Ϊ������
// 
//����ֵ  ���ز���x��ƽ����ֵ��
// 
//�������  EDOM ����xΪ������
// 
//����˵��  ʹ��GCC����ʱ�����-lm��
// 
//����  /* ����200��ƽ����ֵ*/
//#include<math.h>
//main()
//{
//double root;
//root = sqrt (200);
//printf("answer is %f\n",root);
//}
// 
//ִ��  answer is 14.142136
// 
//�� 
//
// 
//
// 
//tan��ȡ���к���ֵ��  
//��غ���  atan��atan2��cos��sin
// 
//��ͷ�ļ�  #include <math.h>
// 
  double tan(double x);
// 
//����˵��  tan()�����������x������ֵ��Ȼ�󽫽�����ء�
// 
//����ֵ  ���ز���x������ֵ��
// 
//����˵��  ʹ��GCC����ʱ�����-lm��
// 
//����  #include<math.h>
//main()
//{
//double answer = tan(0.5);
//printf("tan (0.5) = %f\n",answer);
//}
// 
//ִ��  tan(0.5) = 0.546302
// 
//�� 
//
// 
//
// 
//tanh��ȡ˫�������к���ֵ��  
//��غ���  cosh��sinh
// 
//��ͷ�ļ�  #include<math.h>
// 
  double tanh(double x);
// 
//����˵��  tanh()�����������x��˫��������ֵ��Ȼ�󽫽�����ء���ѧ����ʽΪ:sinh(x)/cosh(x)��
// 
//����ֵ  ���ز���x��˫��������ֵ��
// 
//����˵��  ʹ��GCC����ʱ�����-lm��
// 
//����  #include<math.h>
//main()
//{
//double answer = tanh(0.5);
//printf("tanh(0.5) = %f\n",answer);
//}
// 
//ִ��  tanh(0.5) = 0.462117
// 
//�� 
//
// 
//
//
////�û���ƪ====================================================================================
//
//endgrent���ر����ļ���  
//��غ���  getgrent��setgrent
// 
//��ͷ�ļ�  #include<grp.h>
//#include<sys/types.h>
// 
  void endgrent(void);
// 
//����˵��  endgrent()�����ر���getgrent()���򿪵������ļ���
// 
//����ֵ  
// 
//����˵��  
// 
//����  ��ο�getgrent()��setgrent()��
// 
//�� 
//
// 
//
// 
//endpwent���ر������ļ���  
//��غ���  getpwent��setpwent
// 
//��ͷ�ļ�  #include<pwd.h>
//#include<sys/types.h>
// 
  void endpwent(void);
// 
//����˵��  endpwent()�����ر���getpwent()���򿪵������ļ���
// 
//����ֵ  
// 
//����˵��  
// 
//����  ��ο�getpwent()��setpwent()��
// 
//�� 
//
// 
//
// 
//endutent���ر�utmp �ļ���  
//��غ���  getutent��setutent
// 
//��ͷ�ļ�  #include<utmp.h>
// 
  void endutent(void);
// 
//����˵��  endutent()�����ر���getutent���򿪵�utmp�ļ���
// 
//����ֵ  
// 
//����˵��  
// 
//����  ��ο�getutent()��
// 
//�� 
//
// 
//
// 
//fgetgrent����ָ�����ļ�����ȡ���ʽ��  
//��غ���  fgetpwent
// 
//��ͷ�ļ�  #include<grp.h>
//#include<stdio.h>
//#include<sys/types.h>
// 
  struct group * getgrent(FILE * stream);
// 
//����˵��  fgetgrent()��Ӳ���streamָ�����ļ���ȡһ�����ݣ�Ȼ����group�ṹ�������ݷ��ء�����stream��ָ�����ļ�����͡�etc/group��ͬ�ĸ�ʽ��group�ṹ������ο�getgrent()��
// 
//����ֵ  ����group�ṹ���ݣ��������NULL���ʾ�������ݣ����д�������
// 
//����  #include <grp.h>
//#include<sys/types.h>
//#include<stdio.h>
//main()
//{
//struct group *data;
//FILE *stream;
//int i;
//stream = fopen("/etc/group", "r");
//while((data = fgetgrent(stream))!=0){
//i=0;
//printf("%s :%s:%d :", data->gr_name,data->gr_passwd,data->gr_gid);
//while (data->gr_mem[i])printf("%s,",data->gr_mem[i++]);
//printf("\n");
//}
//fclose(stream);
//}
// 
//ִ��  root:x:0:root,
//bin:x:1:root,bin,daemon
//daemon:x:2:root,bin,daemon
//sys:x:3:root,bin,adm
//adm:x:4:root,adm,daemon
//tty:x:5
//disk:x:6:root
//lp:x:7:daemon,lp
//mem:x:8
//kmem:x:9
//wheel:x:10:root
//mail:x:12:mail
//news:x:13:news
//uucp:x:14:uucp
//man:x:15
//games:x:20
//gopher:x:30
//dip:x:40:
//ftp:x:50
//nobody:x:99:
// 
//�� 
//
// 
//
// 
//fgetpwent����ָ�����ļ�����ȡ�����ʽ��  
//��غ���  fgetgrent
// 
//��ͷ�ļ�  #include<pwd.h>
//#include<stdio.h>
//#include<sys/types.h>
// 
  struct passwd * fgetpwent(FILE *stream);
// 
//����˵��  fgetpwent()��Ӳ���streamָ�����ļ���ȡһ�����ݣ�Ȼ����passwd�ṹ�������ݷ��ء�����stream��ָ�����ļ������/etc/passwd��ͬ�ĸ�ʽ��passwd�ṹ������ο�getpwent()��
// 
//����ֵ  ����passwd�ṹ���ݣ��������NULL���ʾ�������ݣ����д�������
// 
//����  #include<pwd.h>
//#include<sys/types.h>
//main()
//{
//struct passwd *user;
//FILE *stream;
//stream = fopen("/etc/passwd", "r");
//while((user = fgetpwent(stream))!=0){
//printf("%s:%d:%d:%s:%s:%s\n",user->pw_name,user->pw_uid,user->pw_gid,user->pw_gecos,user->pw_dir,user->pw_shell);
//}
//}
// 
//ִ��  root:0:0:root:/root:/bin/bash
//bin:1:1:bin:/bin:
//daemon:2:2:daemon:/sbin:
//adm:3:4:adm:/var/adm:
//lp:4:7:lp:/var/spool/lpd:
//sync:5:0:sync:/sbin:/bin/sync
//shutdown:6:0:shutdown:/sbin:/sbin/shutdown
//halt:7:0:halt:/sbin:/sbin/halt
//mail:8:12:mail:/var/spool/mail:
//news:9:13:news:var/spool/news
//uucp:10:14:uucp:/var/spool/uucp:
//operator:11:0:operator :/root:
//games:12:100:games:/usr/games:
//gopher:13:30:gopher:/usr/lib/gopher-data:
//ftp:14:50:FTP User:/home/ftp:
//nobody:99:99:Nobody:/:
//xfs:100:101:X Font Server: /etc/Xll/fs:/bin/false
//gdm:42:42:/home/gdm:/bin/bash
//kids:500:500: : /home/kids:/bin/bash
// 
//�� 
//
// 
//
// 
//getegid��ȡ����Ч����ʶ���룩  
//��غ���  getgid��setgid��setregid
// 
//��ͷ�ļ�  #include<unistd.h>
//#include<sys/types.h>
// 
  gid_t getegid(void);
// 
//����˵��  getegid()����ȡ��ִ��Ŀǰ������Ч��ʶ���롣��Ч����ʶ����������������ִ��ʱ���Ȩ�ޡ�����ֵ������Ч����ʶ���롣
// 
//����  main()
//{ 
//printf("egid is %d\n",getegid());
//}
// 
//ִ��  egid is 0 /*��ʹ��root���ִ�з�������ʱ*/
// 
//�� 
//
// 
//
// 
//geteuid��ȡ����Ч���û�ʶ���룩  
//��غ���  getuid��setreuid��setuid
// 
//��ͷ�ļ�  #include<unistd.h>
//#include<sys/types.h>
// 
  uid_t geteuid(void)
// 
//����˵��  geteuid()����ȡ��ִ��Ŀǰ������Ч���û�ʶ���롣��Ч���û�ʶ����������������ִ�е�Ȩ�ޣ����ɴ˸ı��ֵ�����̿��Ի�ö����Ȩ�ޡ�����ִ���ļ���setIDλ�ѱ����ã����ļ�ִ��ʱ������̵�euidֵ�����ɸ��ļ������ߵ�uid�����磬ִ���ļ�/usr/bin/passwd��Ȩ��Ϊ-r-s--x--x����s λ��ΪsetID(SUID)λ�������κ��û���ִ��passwd ʱ����Ч���û�ʶ����ᱻ���passwd �����ߵ�uid ֵ����root��uid ֵ(0)��
// 
//����ֵ  ������Ч���û�ʶ���롣
// 
//����  main()
//{ 
//printf ("euid is %d \n",geteuid());
//}
// 
//ִ��  euid is 0 /*��ʹ��root���ִ�з�������ʱ*/
// 
//�� 
//
// 
//
// 
//getgid��ȡ����ʵ����ʶ���룩  
//��غ���  getegid��setregid��setgid
// 
//��ͷ�ļ�  #include<unistd.h>
//#include<sys/types.h>
// 
  gid_t getgid(void);
// 
//����˵��  getgid()����ȡ��ִ��Ŀǰ���̵���ʶ���롣
// 
//����ֵ  ������ʶ����
// 
//����  main()
//{
//printf(��gid is %d\n��,getgid());
//}
// 
//ִ��  gid is 0 /*��ʹ��root���ִ�з�������ʱ*/
// 
//�� 
//
// 
//
// 
//getgrent�������ļ���ȡ���˺ŵ����ݣ�  
//��غ���  setgrent��endgrent
// 
//��ͷ�ļ�  #include<grp.h>
//#include <sys/types.h>
// 
  struct group *getgrent(void);
// 
//����˵��  getgrent()���������ļ�(/etc/group)�ж�ȡһ�������ݣ���������group �ṹ���ء���һ�ε���ʱ��ȡ�õ�һ�������ݣ�֮��ÿ����һ�ξͻ᷵����һ�����ݣ�ֱ�������κ�����ʱ����NULL��
//struct group{
//char *gr_name; /*������*/
//char *gr_passwd; /* ������*/
//gid_t gr_gid; /*��ʶ����*/
//char **gr_mem; /*���Ա�˺�*/
//}
// 
//����ֵ  ����group�ṹ���ݣ��������NULL���ʾ�������ݣ����д�������
// 
//����˵��  getgrent()�ڵ�һ�ε���ʱ������ļ�����ȡ������Ϻ��ʹ��endgrent()���رո����ļ���
// 
//�������  ENOMEM �ڴ治�㣬�޷�����group�ṹ��
// 
//����  #include<grp.h>
//#include<sys/types.h>
//main()
//{
//struct group *data;
//int i;
//while((data= getgrent())!=0){
//i=0;
//printf(��%s:%s:%d:��,data->gr_name,data->gr_passwd,data->gr_gid);
//while(data->gr_mem[i])printf(��%s,��,data->gr_mem[i++]);
//printf(��\n��);
//}
//endgrent();
//}
// 
//ִ��  root:x:0:root,
//bin:x:1:root,bin,daemon,
//daemon:x:2:root,bin,daemon,
//sys:x:3:root,bin,adm,
//adm:x:4:root,adm,daemon
//tty:x:5
//disk:x:6:root
//lp:x:7:daemon,lp
//mem:x:8
//kmem:x:9:
//wheel:x:10:root
//mail:x:12:mail
//news:x:13:news
//uucp:x:14:uucp
//man:x:15:
//games:x:20
//gopher:x:30
//dip:x:40
//ftp:x:50
//nobody:x:99
// 
//�� 
//
// 
//
// 
//getgrgid�������ļ���ȡ��ָ��gid �����ݣ�  
//��غ���  fgetgrent��getgrent��getgrnam
// 
//��ͷ�ļ�  #include<grp.h>
//#include<sys/types.h>
// 
  strcut group * getgrgid(gid_t gid);
// 
//����˵��  getgrgid��������������gidָ������ʶ������һ�������ļ����ҵ�ʱ�㽫�����������group�ṹ���ء�group�ṹ��ο�getgrent������
// 
//����ֵ  ����group�ṹ���ݣ��������NULL���ʾ�������ݣ����д�������
// 
//����  /* ȡ��gid��3��������*/
//#include<grp.h>
//#include<sys/types.h>
//main()
//{
//strcut group *data;
//int i=0;
//data = getgrgid(3);
//printf(��%s:%s:%d:��,data->gr_name,data->gr_passwd,data->gr_gid);
//while(data->gr_mem[i])printf(��%s ,��,data->mem[i++]);
//printf(��\n��);
//}
// 
//ִ��  sys:x:3:root,bin,adm
// 
//�� 
//
// 
//
// 
//getgrnam�������ļ���ȡ��ָ��������ݣ�  
//��غ���  fgetgrent��getrent��getgruid
// 
//��ͷ�ļ�  #include<grp.h>
//#include<sys/types.h>
// 
  strcut group * getgrnam(const char * name);
// 
//����˵��  getgrnam����������һ����������ôָ���������ƣ��ҵ�ʱ�㽫�����������group�ṹ���ء�group �ṹ��ο�getgrent������
// 
//����ֵ  ����group�ṹ���ݣ��������NULL���ʾ�������ݣ����д�������
// 
//����  /* ȡ��adm��������*/
//#include<grp.h>
//#include<sys/types.h>
//main()
//{
//strcut group * data;
//int i=0;
//data = getgrnam(��adm��);
//printf(��%s:%s:%d:��,data->gr_name,data->gr_passwd,data->gr_gid);
//while(data->gr_mem[i])printf(��%s,��,data->gr_mem[i++]);
//printf(��\n��);
//}
// 
//ִ��  adm:x:4:root,adm,daemon
// 
//�� 
//
// 
//
// 
//getgroups��ȡ������룩  
//��غ���  initgroups��setgroup��getgid��setgid
// 
//��ͷ�ļ�  #include<unistd.h>
//#include<sys/types.h>
// 
  int getgroups(int size,gid_t list[]);
// 
//����˵��  getgroup��������ȡ��Ŀǰ�û�����������롣����sizeΪlist�����������ɵ�gid_t ��Ŀ���������size ֵΪ�㣬�˺������᷵���û�������������
// 
//����ֵ  ������ʶ���룬���д����򷵻�-1��
// 
//�������  EFAULT ����list�����ַ���Ϸ���EINVAL ����sizeֵ�������������е��顣
// 
//����  #include<unistd.h>
//#include<sys/types.h>
//main()
//{
//gid_t list[500];
//int x,i;
//x = getgroups(0.list);
//getgroups(x,list);
//for(i=0;i<x;i++)
//printf(��%d:%d\n��,i,list[i]);
//}
// 
//ִ��  0:00
//1:01
//2:02
//3:03
//4:04
//5:06
//6:10
// 
//�� 
//
// 
//
// 
//getpw��ȡ��ָ���û��������ļ����ݣ�  
//��غ���  getpwent
// 
//��ͷ�ļ�  #include<pwd.h>
//#include<sys/types.h>
// 
  int getpw(uid_t uid,char *buf);
// 
//����˵��  getpw()���/etc/passwd�в��ҷ��ϲ���uid��ָ�����û��˺����ݣ��Ҳ���������ݾͷ���-1�������ص�buf�ַ�����ʽ����:�˺�:����:�û�ʶ����(uid):��ʶ����(gid):ȫ��:��Ŀ¼:shell
// 
//����ֵ  ����0��ʾ�ɹ����д�����ʱ����-1��
// 
//����˵��  1. getpw()����Ǳ�ڵİ�ȫ�����⣬�뾡��ʹ�ñ�ĺ���ȡ����
//2. ʹ��shadow��ϵͳ�Ѱ��û�������/etc/passwd�����ʹ��getpw()ȡ�õ����뽫Ϊ��x����
// 
//����  #include<pwd.h>
//#include<sys/types.h>
//main()
//{
//char buffer[80];
//getpw(0,buffer);
//printf(��%s\n��,buffer);
//}
// 
//ִ��  root:x:0:0:root:/root:/bin/bash
// 
//�� 
//
// 
//
// 
//getpwent���������ļ���ȡ���˺ŵ����ݣ�  
//��غ���  getpw��fgetpwent��getpwnam��getpwuid��setpwent��endpwent
// 
//��ͷ�ļ�  #include<pwd.h>
//#include<sys/types.h>
// 
  strcut passwd * getpwent(void);
// 
//����˵��  getpwent���������������ļ���/etc/passwd���ж�ȡһ���û����ݣ����û���������passwd �ṹ���ء���һ�ε���ʱ��ȡ�õ�һλ�û����ݣ�֮��ÿ����һ�ξͻ᷵����һ�����ݣ�ֱ�������κ�����ʱ����NULL��
//passwd �ṹ��������
//struct passwd{
//char * pw_name; /*�û��˺�*/
//char * pw_passwd; /*�û�����*/
//uid_t pw_uid; /*�û�ʶ����*/
//gid_t pw_gid; /*��ʶ����*/
//char * pw_gecos; /*�û�ȫ��*/
//char * pw_dir; /*��Ŀ¼*/
//char * pw_shell; /* ��ʹ�õ�shell·��*/
//};
// 
//����ֵ  ����passwd �ṹ���ݣ��������NULL ���ʾ�������ݣ����д�������
// 
//����˵��  getpwent()�ڵ�һ�ε���ʱ��������ļ�����ȡ������Ϻ��ʹ��endpwent()���رո������ļ����������ENOMEM �ڴ治�㣬�޷�����passwd�ṹ��
// 
//����  #include<pwd.h>
//#include<sys/types.h>
//main()
//{
//struct passwd *user;
//while((user = getpwent())!=0){
//printf(��%s:%d:%d:%s:%s:%s\n��,user->pw_name,user->pw_uid,user->pw_gid,
//user->pw_gecos,user->pw_dir,user->pw_shell);
//}
//endpwent();
//}
// 
//ִ��  root:0:0:root:/root:/bin/bash
//bin:1:1:bin:/bin:
//daemon:2:2:daemon:/sbin:
//adm:3:4:adm:/var/adm:
//lp:4:7:lp:/var/spool/lpd:
//sync:5:0:sync:/sbin:/bin/sync
//shutdown:6:0:shutdown:/sbin:/sbin/shutdown
//halt:7:0:halt:/sbin:/sbin/halt
//mail:8:12:mail:/var/spool/mail:
//news:9:13:news:var/spool/news
//uucp:10:14:uucp:/var/spool/uucp:
//operator:11:0:operator :/root:
//games:12:100:games:/usr/games:
//gopher:13:30:gopher:/usr/lib/gopher-data:
//ftp:14:50:FTP User:/home/ftp:
//nobody:99:99:Nobody:/:
//xfs:100:101:X Font Server: /etc/Xll/fs:/bin/false
//gdm:42:42:/home/gdm:/bin/bash
//kids:500:500: : /home/kids:/bin/bash
// 
//�� 
//
// 
//
// 
//getpwnam���������ļ���ȡ��ָ���˺ŵ����ݣ�  
//��غ���  getpw��fgetpwent��getpwent��getpwuid
// 
//��ͷ�ļ�  #include<pwd.h>
//#include<sys/types.h>
// 
  struct passwd * getpwnam(const char * name);
// 
//����˵��  getpwnam()������һ��������name ָ�����˺����ƣ��ҵ�ʱ�㽫���û���������passwd�ṹ���ء�passwd�ṹ��ο�getpwent()��
// 
//����ֵ  ����passwd �ṹ���ݣ��������NULL ���ʾ�������ݣ����д�������
// 
//����  /*ȡ��root�˺ŵ�ʶ����͸�Ŀ¼*/
//#include<pwd.h>
//#include<sys/types.h>
//main()
//{
//struct passwd *user;
//user = getpwnam(��root��);
//printf(��name:%s\n��,user->pw_name);
//printf(��uid:%d\n��,user->pw_uid);
//printf(��home:%s\n��,user->pw_dir);
//}
// 
//ִ��  name:root
//uid:0
//home:/root
// 
//�� 
//
// 
//
// 
//getpwuid���������ļ���ȡ��ָ��uid �����ݣ�  
//��غ���  getpw��fgetpwent��getpwent��getpwnam
// 
//��ͷ�ļ�  #include<pwd.h>
//#include<sys/types.h>
// 
  struct passwd * getpwuid(uid_t uid);
// 
//����˵��  getpwuid()������һ��������uid ָ�����û�ʶ���룬�ҵ�ʱ�㽫���û��������Խṹ���ؽṹ��ο������û���������passwd �ṹ���ء�passwd �ṹ��ο�getpwent()��
// 
//����ֵ  ����passwd �ṹ���ݣ��������NULL ���ʾ�������ݣ������д�������
// 
//����  #include<pwd.h>
//#include<sys/types.h>
//main()
//{
//struct passwd *user;
//user= getpwuid(6);
//printf(��name:%s\n��,user->pw_name);
//printf(��uid:%d\n��,user->pw_uid);
//printf(��home:%s\n��,user->pw_dir);
//}
// 
//ִ��  name:shutdown
//uid:6
//home:/sbin
// 
//�� 
//
// 
//
// 
//getuid��ȡ����ʵ���û�ʶ���룩  
//��غ���  geteuid��setreuid��setuid
// 
//��ͷ�ļ�  #include<unistd.h>
//#include<sys/types.h>
// 
  uid_t getuid(void);
// 
//����˵��  getuid()����ȡ��ִ��Ŀǰ���̵��û�ʶ���롣
// 
//����ֵ  �û�ʶ����
// 
//����  main()
//{ 
//printf(��uid is %d\n��,getuid());
//}
// 
//ִ��  uid is 0 /*��ʹ��root���ִ�з�������ʱ*/
// 
//�� 
//
// 
//
// 
//getutent����utmp �ļ���ȡ���˺ŵ�¼���ݣ�  
//��غ���  getutent��getutid��getutline��setutent��endutent��pututline��utmpname
// 
//��ͷ�ļ�  #include<utmp.h>
// 
  struct utmp *getutent(void);
// 
//����˵��  getutent()������utmp �ļ�(/var/run/utmp)�ж�ȡһ���¼���ݣ���������utmp �ṹ���ء���һ�ε���ʱ��ȡ�õ�һλ�û����ݣ�֮��ÿ����һ�ξͻ᷵����һ�����ݣ�ֱ�������κ�����ʱ����NULL��
//utmp�ṹ��������
//struct utmp
//{
//short int ut_type; /*��¼����*/
//pid_t ut_pid; /*login���̵�pid*/
//char ut_line[UT_LINESIZE];/*��¼װ������ʡ���ˡ�/dev/��*/
//char ut_id[4]; /* Inittab ID*/
//char ut_user[UT_NAMESIZE];/*��¼�˺�*/
//char ut_host[UT_HOSTSIZE];/*��¼�˺ŵ�Զ����������*/
//struxt exit_status ut_exit;/* ������ΪDEAD_PROCESSʱ���̵Ľ�
//��״̬*/
//long int ut_session; /*Sessioc ID*/
//struct timeval ut_tv; /*ʱ���¼*/
//int32_t ut_addr_v6[4]; /*Զ�������������ַ*/
//char __unused[20]; /* ����δʹ��*/
//};
//ut_type�����¼�������:
//EMPTY ��Ϊ�յļ�¼��
//RUN_LVL ��¼ϵͳrun��level�ĸı�
//BOOT_TIME ��¼ϵͳ����ʱ��
//NEW_TIME ��¼ϵͳʱ��ı���ʱ��
//OLD_TINE ��¼���ı�ϵͳʱ��ʱ��ʱ�䡣
//INIT_PROCESS ��¼һ����init���������Ľ��̡�
//LOGIN_PROCESS ��¼login���̡�
//USER_PROCESS ��¼һ����̡�
//DEAD_PROCESS ��¼һ�����Ľ��̡�
//ACCOUNTING Ŀǰ��δʹ�á�
//exit_status�ṹ����
//struct exit_status
//{
//short int e_termination; /*���̽���״̬*/
//short int e_exit; /*�����˳�״̬*/
//};
//timeval�Ľṹ������ο�gettimeofday������
//��س�����������:
//UT_LINESIZE 32
//UT_NAMESIZE 32
//UT_HOSTSIZE 256
// 
//����ֵ  ����utmp �ṹ���ݣ��������NULL ���ʾ�������ݣ����д�������
// 
//����˵��  getutent()�ڵ�һ�ε���ʱ���utmp �ļ�����ȡ������Ϻ��ʹ��endutent()���رո�utmp�ļ���
// 
//����  #include<utmp.h>
//main()
//{
//struct utmp *u;
//while((u=getutent())){
//if(u->ut_type = = USER_PROCESS)
//printf(��%d %s %s %s \n��,u->ut_type,u->ut_user,u->ut_line,u->ut_host);
//}
//endutent();
//}
// 
//ִ��  /* ��ʾ������root�˺ŷֱ��¼/dev/pts/0��/dev/pts/1��/dev/pts/2 */
//7 root pts/0
//7 root pts/1
//7 root pts/2
// 
//�� 
//
// 
//
// 
//getutid����utmp �ļ��в����ض��ļ�¼��  
//��غ���  getutent��getutline
// 
//��ͷ�ļ�  #include<utmp.h>
// 
  strcut utmp *getutid(strcut utmp *ut);
// 
//����˵��  getutid()������Ŀǰutmp �ļ��Ķ�дλ����һ������������utָ���ļ�¼�����ut->ut_type ΪRUN_LVL��BOOT_TIME��NEW_TIME��OLD_TIME ����֮һ�������ut->ut_type ����ļ�¼����ut->ut_type ΪINIT_PROCESS��LOGIN_PROCESS��USER_PROCESS��DEAD_PROCESS����֮һ���������ut->ut_id����ļ�¼���ҵ�����ļ�¼�㽫��������utmp �ṹ���ء�utmp�ṹ��ο�getutent()��
// 
//����ֵ  ����utmp �ṹ���ݣ��������NULL ���ʾ�������ݣ����д�������
// 
//����  #include<utmp.h>
//main()
//{
//struct utmp ut,*u;
//ut.ut_type=RUN_LVL;
//while((u= getutid(&ut))){
//printf(��%d %s %s %s\n��,u->ut_type,u->ut_user,u->ut_line,u->ut_host);
//}
//}
// 
//ִ��  1 runlevel -
// 
//�� 
//
// 
//
// 
//getutline����utmp �ļ��в����ض��ļ�¼��  
//��غ���  getutent��getutid��pututline
// 
//��ͷ�ļ�  #include<utmp.h>
// 
  struct utmp * getutline (struct utmp *ut);
// 
//����˵��  getutline()������Ŀǰutmp�ļ��Ķ�дλ����һ��������ut_typeΪUSER_PROCESS ��LOGIN_PROCESS �ļ�¼������ut_line ��ut->ut_line ������ҵ�����ļ�¼�㽫��������utmp �ṹ���أ�utmp�ṹ��ο�getutent()��
// 
//����ֵ  ����utmp �ṹ���ݣ��������NULL ���ʾ�������ݣ����д�������
// 
//����  #include<utmp.h>
//main()
//{
//struct utmp ut,*u;
//strcpy (ut.ut_line,��pts/1��);
//while ((u=getutline(&ut))){
//printf(��%d %s %s %s \n��,u->ut_type,u->ut_user,u->ut_line,u->ut_host);
//}
//}
// 
//ִ��  7 root pts/1
// 
//�� 
//
// 
//
// 
//initgroups����ʼ�����嵥��  
//��غ���  setgrent��endgrent
// 
//��ͷ�ļ�  #include<grp.h>
//#include<sys/types.h>
// 
  int initgroups(const char *user,gid_t group);
// 
//����˵��  initgroups�������������ļ���/etc/group���ж�ȡһ�������ݣ����������ݵĳ�Ա���в���userʱ���㽫����group��ʶ������뵽�������С�
// 
//����ֵ  ִ�гɹ��򷵻�0��ʧ���򷵻�-1�����������errno��
// 
//�� 
//
// 
//
// 
//pututline����utmp ��¼д���ļ���  
//��غ���  getutent��getutid��getutline
// 
//��ͷ�ļ�  #include<utmp.h>
// 
  void pututline(struct utmp *ut);
// 
//����˵��  pututline()����������ut��utmp�ṹ��¼��utmp�ļ��С��˺���������getutid()��ȡ����ȷ��д��λ�ã����û���ҵ�����ļ�¼�����뵽utmp�ļ�β��utmp�ṹ��ο�getutent()��
// 
//����ֵ  
// 
//����˵��  ��Ҫ��д��/var/run/utmp ��Ȩ��
// 
//����  #include<utmp.h>
//main()
//{
//struct utmp ut;
//ut.ut_type =USER_PROCESS;
//ut.ut_pid=getpid();
//strcpy(ut.ut_user,��kids��);
//strcpy(ut.ut_line,��pts/1��);
//strcpy(ut.ut_host,��www.gnu.org��);
//pututline(&ut);
//}
// 
//ִ��  /*ִ�з�������ָ��who -l �۲�*/
//root pts/0 dec9 19:20
//kids pts/1 dec12 10:31(www.gnu.org)
//root pts/2 dec12 13:33
// 
//�� 
//
// 
//
// 
//seteuid��������Ч���û�ʶ���룩  
//��غ���  setuid��setreuid��setfsuid
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int seteuid(uid_t euid);
// 
//����˵��  seteuid()������������ִ��Ŀǰ���̵���Ч�û�ʶ���롣��Linux�£�seteuid(euid)�൱��setreuid(-1,euid)��
// 
//����ֵ  ִ�гɹ��򷵻�0��ʧ���򷵻�-1������������errno
// 
//����˵��  ��ο�setuid
// 
//�� 
//
// 
//
// 
//setfsgid�������ļ�ϵͳ����ʶ���룩  
//��غ���  setuid��setreuid��seteuid��setfsuid
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int setfsgid(uid_t fsgid);
// 
//����˵��  setfsgid()������������Ŀǰ���̵��ļ�ϵͳ����ʶ���롣һ������£��ļ�ϵͳ����ʶ����(fsgid)����Ч����ʶ����(egid)����ͬ�ġ�����ǳ����û����ô˺���������fsgid ����Ϊ�κ�ֵ���������fsgid����Ϊreal/effective/saved����ʶ����֮һ��
// 
//����ֵ  ִ�гɹ��򷵻�0��ʧ���򷵻�-1������������errno��
// 
//����˵��  �˺���ΪLinux���С�
// 
//�������  EPERM Ȩ�޲������޷�������á�
// 
//�� 
//
// 
//
// 
//setfsuid�������ļ�ϵͳ���û�ʶ���룩  
//��غ���  setuid��setreuid��seteuid��setfsgid
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int setfsuid(uid_t fsuid);
// 
//����˵��  setfsuid()������������Ŀǰ���̵��ļ�ϵͳ���û�ʶ���롣һ������£��ļ�ϵͳ���û�ʶ����(fsuid)����Ч���û�ʶ����(euid)����ͬ�ġ�����ǳ����û����ô˺���������fsuid����Ϊ�κ�ֵ���������fsuid����Ϊreal/effective/saved���û�ʶ����֮һ��
// 
//����ֵ  ִ�гɹ��򷵻�0��ʧ���򷵻�-1������������errno
// 
//����˵��  �˺���ΪLinux����
// 
//�������  EPERM Ȩ�޲������޷�������á�
// 
//�� 
//
// 
//
// 
//setgid��������ʵ����ʶ���룩  
//��غ���  getgid��setregid��getegid��setegid
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int setgid(gid_t gid);
// 
//����˵��  setgid()������Ŀǰ���̵���ʵ��ʶ����(real gid)��ɲ���gidֵ��������Գ����û����ִ�д˵��ã���real��effective��savedgid������ɲ���gid��
// 
//����ֵ  ���óɹ��򷵻�0��ʧ���򷵻�-1������������errno�С�
// 
//�������  EPERM �����Գ����û���ݵ��ã����Ҳ���gid ���ǽ��̵�effective gid��saved gidֵ֮һ��
// 
//�� 
//
// 
//
// 
//setgrent����ͷ��ȡ���ļ��е������ݣ�  
//��غ���  getgrent��endgrent
// 
//��ͷ�ļ�  #include<grp.h>
//#include<sys/types.h>
// 
  void setgrent(void);
// 
//����˵��  setgrent()������getgrent()�Ķ�д��ַָ�����ļ���ͷ��
// 
//����ֵ  
// 
//����˵��  ��ο�setpwent()��
// 
//�� 
//
// 
//
// 
//setgroups����������룩  
//��غ���  initgroups��getgroup��getgid��setgid
// 
//��ͷ�ļ�  #include<grp.h>
// 
  int setgroups(size_t size,const gid_t * list);
// 
//����˵��  setgroups()������list ������������������뵽Ŀǰ���̵��������С�����sizeΪlist()��gid_t��Ŀ�����ֵΪNGROUP(32)��
// 
//����ֵ  ���óɹ��򷵻�0�����д����򷵻�-1��
// 
//�������  EFAULT ����list�����ַ���Ϸ���
//EPERM Ȩ�޲��㣬������rootȨ��
//EINVAL ����sizeֵ����NGROUP(32)��
// 
//�� 
//
// 
//
// 
//setpwent����ͷ��ȡ�����ļ��е��˺����ݣ�  
//��غ���  getpwent��endpwent
// 
//��ͷ�ļ�  #include<pwd.h>
//#include<sys/types.h>
// 
  void setpwent(void);
// 
//����˵��  setpwent()������getpwent()�Ķ�д��ַָ�������ļ���ͷ��
// 
//����ֵ  
// 
//����  #include<pwd.h>
//#include<sys/types.h>
//main()
//{
//struct passwd *user;
//int i;
//for(i=0;i<4;i++){
//user=getpwent();
//printf(��%s :%d :%d :%s:%s:%s\n��,user->pw_name,user->pw_uid,user->pw_gid,
//user->pw_gecos,user->pw_dir,user->pw_shell);
//}
//setpwent();
//user=getpwent();
//printf(��%s :%d :%d :%s:%s:%s\n��,user->pw_name,user->pw_uid,user->pw_gid,
//user->pw_gecos,user->pw_dir,user->pw_shell);
//endpwent();
//}
// 
//ִ��  root:0:0:root:/root:/bin/bash
//bin:1:1:bin:/bin
//daemon:2:2:daemon:/sbin
//adm:3:4:adm:/var/adm
//root:0:0:root:/root:/bin/bash
// 
//�� 
//
// 
//
// 
//setregid��������ʵ����Ч����ʶ���룩  
//��غ���  setgid��setegid��setfsgid
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int setregid(gid_t rgid,gid_t egid);
// 
//����˵��  setregid()����������rgid��ΪĿǰ���̵���ʵ��ʶ���룬������egid����ΪĿǰ���̵���Ч��ʶ���롣�������rgid��egidֵΪ-1�����Ӧ��ʶ���벻��ı䡣
// 
//����ֵ  ִ�гɹ��򷵻�0��ʧ���򷵻�-1������������errno��
// 
//�� 
//
// 
//
// 
//setreuid��������ʵ����Ч���û�ʶ���룩  
//��غ���  setuid��seteuid��setfsuid
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int setreuid(uid_t ruid,uid_t euid);
// 
//����˵��  setreuid()����������ruid ��ΪĿǰ���̵���ʵ�û�ʶ���룬������euid ����ΪĿǰ���̵���Ч�û�ʶ���롣�������ruid ��euidֵΪ-1�����Ӧ��ʶ���벻��ı䡣
// 
//����ֵ  ִ�гɹ��򷵻�0��ʧ���򷵻�-1������������errno��
// 
//����˵��  ��ο�setuid������
// 
//�� 
//
// 
//
// 
//setuid��������ʵ���û�ʶ���룩  
//��غ���  getuid��setreuid��seteuid��setfsuid
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int setuid(uid_t uid)
// 
//����˵��  setuid()������������ִ��Ŀǰ���̵��û�ʶ���롣������Ҫ�ô˺��������ã�����Ч���û�ʶ�������Ϊ0(root)����Linux�£���rootʹ��setuid()���任�������û�ʶ����ʱ��rootȨ�޻ᱻ��������ȫת���ɸ��û���ݣ�Ҳ����˵���ý������󽫲��پ��п�setuid()��Ȩ�������ֻ������ʱ����root Ȩ�ޣ��Ժ�������ȡ��Ȩ�ޣ������ʹ��seteuid()��
// 
//����ֵ  ִ�гɹ��򷵻�0��ʧ���򷵻�-1������������errno��
// 
//����˵��  һ���ڱ�д��setuid root�ĳ���ʱ��Ϊ���ٴ�����������ϵͳ��ȫ���գ���ʹ����rootȨ�޺�������ִ��setuid(getuid());������rootȨ�ޡ����⣬����uid��euid��һ��ʱLinuxϵͳ���������core dump��
// 
//�� 
//
// 
//
// 
//setutent����ͷ��ȡutmp �ļ��еĵ�¼���ݣ�  
//��غ���  getutent��endutent
// 
//��ͷ�ļ�  #include<utmp.h>
// 
  void setutent(void);
// 
//����˵��  setutent()������getutent()�Ķ�д��ַָ��utmp�ļ���ͷ��
// 
//����˵��  ��ο�setpwent()��setgrent()��
// 
//�� 
//
// 
//
// 
//utmpname������utmp �ļ�·����  
//��غ���  getutent��getutid��getutline��setutent��endutent��pututline
// 
//��ͷ�ļ�  #include<utmp.h>
// 
  void utmpname(const char * file);
// 
//����˵��  utmpname()��������utmp�ļ���·�������ṩutmp��غ����Ĵ�ȡ·�������û��ʹ��utmpname()��Ĭ��utmp�ļ�·��Ϊ/var/run/utmp��
// 
//����ֵ  
// 
//�� 
//
// 
//���ݽṹ���㷨ƪ===============================================================
//�� 
//
// 
//
// 
//crypt������������ݱ��룩  
//��غ���  getpass
// 
//��ͷ�ļ�  #define _XOPEN_SOURCE
//#include<unistd.h>
// 
  char * crypt (const char *key,const char * salt);
// 
//����˵��  crypt()��ʹ��Data Encryption Standard(DES)���㷨������key��ָ���ַ������Ա��룬key�ַ������Ƚ�ȡǰ8���ַ��������˳��ȵ��ַ�û�����塣����saltΪ�����ַ���ɵ��ַ�������a-z��A-Z��0-9����.���͡�/������ɣ���������ʹ��4096 �ֲ�ͬ�ڽ�������һ��������ִ�гɹ���᷵��ָ���������ַ���ָ�룬����key ��ָ���ַ�������������������������ַ�������Ϊ13 ���ַ���ǰ�����ַ�Ϊ����salt������ַ�����
// 
//����ֵ  ����һ��ָ����NULL��β�������ַ�����
// 
//����˵��  ʹ��GCC����ʱ���-lcrypt��
// 
//����  #include<unistd.h>
//main()
//{
//char passwd[13];
//char *key;
//char slat[2];
//key= getpass(��Input First Password:��);
//slat[0]=key[0];
//slat[1]=key[1];
//strcpy(passwd,crypt(key slat));
//key=getpass(��Input Second Password:��);
//slat[0]=passwd[0];
//slat[1]=passwd[1];
//printf(��After crypt(),1st passwd :%s\n��,passwd);
//printf(��After crypt(),2nd passwd:%s \n��,crypt(key slat));
//}
// 
//ִ��  Input First Password: /* ����test����������passwd[ ] */
//Input Second Password /*����test��������ͬ�����Ҳ����ͬ*/
//After crypt () 1st Passwd : teH0wLIpW0gyQ
//After crypt () 2nd Passwd : teH0wLIpW0gyQ
// 
//�� 
//
// 
//
// 
//bsearch����Ԫ������  
//��غ���  qsort
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  void *bsearch(const void *key,const void *base,size_t nmemb,size_tsize,int (*compar) (const void*,const void*));
// 
//����˵��  bsearch()���ö�Ԫ����������õ������в������ݡ�����keyָ�������ҵĹؼ����ݣ�����baseָ��Ҫ�����������鿪ͷ��ַ������nmemb ���������е�Ԫ��������ÿһԪ�صĴ�С���ɲ���size���������һ�����compar Ϊһ����ָ�룬������������ж�����Ԫ��֮��Ĵ�С��ϵ��������compar �ĵ�һ��������ָ��Ԫ�����ݴ��ڵڶ���������ָ��Ԫ�����������ش�����0 ��ֵ������Ԫ�����������ش�0��
// 
//����˵��  �ҵ��ؼ������򷵻��ҵ��ĵ�ַ��������������Ҳ����ؼ������򷵻�NULL��
// 
//����  #include<stdio.h>
//#include<stdlib.h>
//#define NMEMB 5
//#define SIZE 10
//int compar(const void *a,const void *b)
//{
//return (strcmp((char *)a,(char *)b));
//}
//main()
//{
//char data[50][size]={��linux��,��freebsd��,��solaris��,��sunos��,��windows��};
//char key[80],*base ,*offset;
//int i, nmemb=NMEMB,size=SIZE;
//while(1){
//printf(��>��);
//fgets(key,sizeof(key),stdin);
//key[strlen(key)-1]=��\0��;
//if(!strcmp(key,��exit��))break;
//if(!strcmp(key,��list��)){
//for(i=0;i<nmemb;i++)
//printf(��%s\n��,data[i]);
//continue;
//}
//base = data[0];
//qsort(base,nmemb,size,compar);
//offset = (char *) bsearch(key,base,nmemb,size,compar);
//if( offset = =NULL){
//printf(��%s not found!\n��,key);
//strcpy(data[nmemb++],key);
//printf(��Add %s to data array\n��,key);
//}else{
//printf(��found: %s \n��,offset);
//}
//}
//}
// 
//ִ��  >hello /*����hello�ַ���*/
//hello not found! /*�Ҳ���hello �ַ���*/
//add hello to data array /*��hello�ַ�������*/
//>.list /*�г���������*/
//freebsd
//linux
//solaris
//sunos
//windows
//hello
//>hello
//found: hello
// 
//�� 
//
// 
//
// 
//lfind������������  
//��غ���  lsearch
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  void *lfind (const void *key,const void *base,size_t *nmemb,size_t
//size,int(* compar) (const void * ,const void *));
// 
//����˵��  lfind()�������������������д�ͷ��βһ����������ݡ�����keyָ�������ҵĹؼ����ݣ�����baseָ��Ҫ�����������鿪ͷ��ַ������nmemb���������е�Ԫ��������ÿһԪ�صĴ�С���ɲ���size���������һ�����comparΪһ����ָ�룬������������ж�����Ԫ���Ƿ���ͬ��������compar ����ظ�������ָ��Ԫ�����ݺ͵ڶ���������ָ��Ԫ��������ͬʱ�򷵻�0������Ԫ�����ݲ���ͬ�򷵻ط�0ֵ��Lfind()��lsearch()��ͬ�����ڣ����Ҳ����ؼ�����ʱlfind()���᷵��NULL�������������Ѹñ����ݼ�������β�ˡ�
// 
//����ֵ  �ҵ��ؼ������򷵻��ҵ��ĸñ�Ԫ�صĵ�ַ��������������Ҳ����ؼ������򷵻ؿ�ָ��(NULL)��
// 
//����  �ο�lsearch()��
// 
//�� 
//
// 
//
// 
//lsearch������������  
//��غ���  lfind
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  void *lsearch(const void * key ,const void * base ,size_t * nmemb,size_t size, int ( * compar) (const void * ,const void *));
// 
//����˵��  lsearch()�������������������д�ͷ��βһ����������ݡ�����keyָ�������ҵĹؼ����ݣ�����baseָ��Ҫ�����������鿪ͷ��ַ������nmemb ���������е�Ԫ��������ÿһԪ�صĴ�С���ɲ���size ���������һ�����compar Ϊһ����ָ�룬������������ж�����Ԫ���Ƿ���ͬ��������compar �ĵ�һ��������ָ��Ԫ�����ݺ͵ڶ���������ָ��Ԫ��������ͬʱ�򷵻�0������Ԫ�����ݲ���ͬ�򷵻ط�0 ֵ�����lsearch�����Ҳ����ؼ�����ʱ�������Ѹ������ݼ��������
// 
//����ֵ  �ҵ��ؼ������򷵻��ҵ��ĸñ�Ԫ�ص���֫��������������Ҳ����ؼ������򽫴˹ؼ����ݼ������飬�ٰѼ��������ĵ�ַ���ء�
// 
//����  #include<stdio.h>
//#include<stdlib.h>
//#define NMEMB 50
//#define SIZE 10
//int compar (comst void *a,const void *b)
//{
//return (strcmp((char *) a, (char *) b));
//}
//main()
//{
//char data[NMEMB][SIZE]={��Linux��,��freebsd��,��solzris��,��sunos��,��windows��};
//char key[80],*base,*offset;
//int i, nmemb=NMEMB,size=SIZE;
//for(i=1;i<5;i++){
//fgets(key,sizeof9key),stdin);
//key[strlen(key)-1]=��\0��;
//base = data[0];
//offset = (char *)lfind(key,base,&nmemb,size,compar);
//if(offset ==NULL){
//printf(��%s not found!\n��,key);
//offset=(char *) lsearch(key,base,&nmemb,size,compar);
//printf(��Add %s to data array\n��,offset);
//}else{
//printf(��found : %s \n��,offset);
//}
//}
//}
// 
//ִ��  linux
//found:linux
//os/2
//os/2 not found!
//add os/2 to data array
//os/2
//found:os/2
// 
//�� 
//
// 
//
// 
//qsort�����ÿ��������������飩  
//��غ���  bsearch
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  void qsort(void * base,size_t nmemb,size_t size,int ( * compar)(const void *, const void *));
// 
//����˵��  ����baseָ������������鿪ͷ��ַ������nmemb���������е�Ԫ��������ÿһԪ�صĴ�С���ɲ���size���������һ�����comparΪһ����ָ�룬������������ж�����Ԫ�ؼ�Ĵ�С��ϵ��������compar�ĵ�һ��������ָ��Ԫ�����ݴ��ڵڶ���������ָ��Ԫ�����������ش��������ֵ������Ԫ�����������ش�0��
// 
//����ֵ  
// 
//����˵��  
// 
//����  #define nmemb 7
//#include <stdlib.h>
//int compar (const void *a ,const void *b)
//{
//int *aa=(int * ) a,*bb = (int * )b;
//if( * aa >* bb)return 1;
//if( * aa == * bb) return 0;
//if( * aa < *bb) return -1;
//}
//main( )
//{
//int base[nmemb]={ 3,102,5,-2,98,52,18};
//int i;
//for ( i=0; i<nmemb;i++)
//printf(��%d ��,base[i]);
//printf(��\n��);
//qsort(base,nmemb,sizeof(int),compar);
//for(i=0;i<nmemb;i++)
//printf(��%d��base[i]);
//printf(��\n��);
//}
// 
//ִ��  3 102 5 -2 98 52 18
//-2 3 5 18 52 98 102
// 
//�� 
//
// 
//
// 
//rand�������������  
//��غ���  srand��random��srandom
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  int rand(void)
// 
//����˵��  rand()�᷵��һ�����ֵ����Χ��0��RAND_MAX �䡣�ڵ��ô˺������������ǰ������������srand()�����������ӣ����δ����������ӣ�rand()�ڵ���ʱ���Զ������������Ϊ1�����������������ο�srand()��
// 
//����ֵ  ����0��RAND_MAX֮��������ֵ��RAND_MAX������stdlib.h����ֵΪ2147483647��
// 
//����  /* ��������1 ��10 ��������ֵ���˷���δ����������ӣ������������������ο�
//srand����*/
//#include<stdlib.h>
//main()
//{
//int i,j;
//for(i=0;i<10;i++)
//{
//j=1+(int)(10.0*rand()/(RAND_MAX+1.0));
//printf(��%d ��,j);
//}
//}
// 
//ִ��  9 4 8 8 10 2 4 8 3 6
//9 4 8 8 10 2 4 8 3 6
// 
//�� 
//
// 
//
// 
//srand��������������ӣ�  
//��غ���  rand��random srandom
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  void srand (unsigned int seed);
// 
//����˵��  srand()��������rand()���������ʱ����������ӡ�����seed�����Ǹ�������ͨ����������geypid()��time(0)�ķ���ֵ������seed�����ÿ��seed������ֵͬ��rand()�������������ֵÿ�ξͻ�һ����
// 
//����ֵ  
// 
//����  /* ��������1 ��10 ��������ֵ���˷�����ִ�н������rand��������*/
//#include<time.h>
//#include<stdlib.h>
//main()
//{
//int i,j;
//srand((int)time(0));
//for(i=0;i<10;i++)
//{
//j=1+(int)(10.0*rand()/(RAND_MAX+1.0));
//printf(�� %d ��,j);
//}
//}
// 
//ִ��  5 8 8 8 10 2 10 8 9 9
//2 9 7 4 10 3 2 10 8 7
// 
//�� 
//
// 
//�ļ�����ƪ==================================================================
//�� 
//
// 
//
// 
//close���ر��ļ���  
//��غ���  open��fcntl��shutdown��unlink��fclose
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int close(int fd);
// 
//����˵��  ��ʹ�����ļ������Ѳ�����Ҫ���ʹ��close()�رո��ļ�����close()��������д�ش��̣����ͷŸ��ļ���ռ�õ���Դ������fdΪ��ǰ��open()��creat()�����ص��ļ������ʡ�
// 
//����ֵ  ���ļ�˳���ر��򷵻�0����������ʱ����-1��
// 
//�������  EBADF ����fd ����Ч���ļ������ʻ���ļ��ѹرա�
// 
//����˵��  ��Ȼ�ڽ��̽���ʱ��ϵͳ���Զ��ر��Ѵ򿪵��ļ������Խ������йر��ļ�����ȷʵ��鷵��ֵ��
// 
//����  �ο�open()
// 
//�� 
//
// 
//
// 
//creat�������ļ���  
//��غ���  read��write��fcntl��close��link��stat��umask��unlink��fopen
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<sys/stat.h>
//#include<fcntl.h>
// 
  int creat(const char * pathname, mode_tmode);
// 
//����˵��  ����pathnameָ�����������ļ�·���ַ�����Creat()�൱��ʹ�����еĵ��÷�ʽ����open()
//open(const char * pathname ,(O_CREAT|O_WRONLY|O_TRUNC));
// 
//�������  ���ڲ���mode��ο�open����������
// 
//����ֵ  creat()�᷵���µ��ļ������ʣ����д�������᷵��-1�����Ѵ���������errno��
//EEXIST ����pathname��ָ���ļ��Ѵ��ڡ�
//EACCESS ����pathname ��ָ�����ļ���������Ҫ����Ե�Ȩ��
//EROFS ����д��Ȩ�޵��ļ�������ֻ���ļ�ϵͳ��
//EFAULT ����pathname ָ�볬���ɴ�ȡ���ڴ�ռ�
//EINVAL ����mode ����ȷ��
//ENAMETOOLONG ����pathname̫����
//ENOTDIR ����pathnameΪһĿ¼
//ENOMEM �����ڴ治��
//ELOOP ����pathname�й�������������⡣
//EMFILE �Ѵﵽ���̿�ͬʱ�򿪵��ļ�������
//ENFILE �Ѵﵽϵͳ��ͬʱ�򿪵��ļ�������
// 
//����˵��  creat()�޷������ر��װ���ļ��������Ҫ��ʹ��mknod()��
// 
//����  ��ο�open()��
// 
//�� 
//
// 
//
// 
//dup�������ļ������ʣ�  
//��غ���  open��close��fcntl��dup2
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int dup (int oldfd);
// 
//����˵��  dup()�������Ʋ���oldfd��ָ���ļ������ʣ����������ء����µ��ļ������ʺͲ���oldfdָ����ͬһ���ļ����������е���������дλ�ú͸���Ȩ�޻���ꡣ���磬������lseek()��ĳ���ļ�����������ʱ����һ���ļ������ʵĶ�дλ��Ҳ�����Ÿı䡣�������ļ�������֮�䲢������close-on-exec��ꡣ
// 
//����ֵ  �����Ƴɹ�ʱ���򷵻���С����δʹ�õ��ļ������ʡ����д����򷵻�-1��errno���Ŵ�����롣�������EBADF����fd����Ч���ļ������ʣ�����ļ��ѹرա�
// 
//�� 
//
// 
//
// 
//dup2�������ļ������ʣ�  
//��غ���  open��close��fcntl��dup
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int dup2(int odlfd,int newfd);
// 
//����˵��  dup2()�������Ʋ���oldfd��ָ���ļ������ʣ�����������������newfd��һ�鷵�ء�������newfdΪһ�Ѵ򿪵��ļ������ʣ���newfd��ָ���ļ����ȱ��رա�dup2()�����Ƶ��ļ������ʣ���ԭ�����ļ������ʹ�������ļ�״̬������ɲο�dup()��
// 
//����ֵ  �����Ƴɹ�ʱ���򷵻���С����δʹ�õ��ļ������ʡ����д����򷵻�-1��errno���Ŵ�����롣
// 
//����˵��  dup2()�൱�ڵ���fcntl(oldfd��F_DUPFD��newfd)����ο�fcntl()��
// 
//�������  EBADF ����fd ����Ч���ļ������ʣ�����ļ��ѹر�
// 
//�� 
//
// 
//
// 
//fcntl���ļ������ʲ�����  
//��غ���  open��flock
// 
//��ͷ�ļ�  #include<unistd.h>
//#include<fcntl.h>
// 
  int fcntl(int fd , int cmd);
//int fcntl(int fd,int cmd,long arg);
//int fcntl(int fd,int cmd,struct flock * lock);
// 
//����˵��  fcntl()���������ļ������ʵ�һЩ���ԡ�����fd���������õ��ļ������ʣ�����cmd������������ָ�
//�����¼������:
//F_DUPFD�������Ҵ��ڻ���ڲ���arg����С����δʹ�õ��ļ������ʣ����Ҹ��Ʋ���fd���ļ������ʡ�ִ�гɹ��򷵻��¸��Ƶ��ļ������ʡ���ο�dup2()��F_GETFDȡ��close-on-exec��ꡣ��������FD_CLOEXECλΪ0�������ڵ���exec()��غ���ʱ�ļ�������رա�
//F_SETFD ����close-on-exec ��ꡣ������Բ���arg ��FD_CLOEXECλ������
//F_GETFL ȡ���ļ�������״̬��꣬�����Ϊopen�����Ĳ���flags��
//F_SETFL �����ļ�������״̬��꣬����argΪ����꣬��ֻ����O_APPEND��O_NONBLOCK��O_ASYNCλ�ĸı䣬����λ�ĸı佫����Ӱ�졣
//F_GETLK ȡ���ļ�������״̬��
//F_SETLK �����ļ�������״̬����ʱflcok �ṹ��l_type ֵ������F_RDLCK��F_WRLCK��F_UNLCK������޷������������򷵻�-1���������ΪEACCES ��EAGAIN��
//F_SETLKW F_SETLK ������ͬ�������޷���������ʱ���˵��û�һֱ�ȵ����������ɹ�Ϊֹ�����ڵȴ������Ĺ����б��ź��ж�ʱ������������-1���������ΪEINTR������lockָ��Ϊflock �ṹָ�룬��������
//struct flcok
//{
//short int l_type; /* ������״̬*/
//short int l_whence;/*����l_startλ��*/
//off_t l_start; /*��������Ŀ�ͷλ��*/
//off_t l_len; /*��������Ĵ�С*/
//pid_t l_pid; /*���������Ľ���*/
//};
//l_type ������״̬:
//F_RDLCK ����һ������ȡ�õ�����
//F_WRLCK ����һ����д���õ�����
//F_UNLCK ɾ��֮ǰ����������
//l_whence Ҳ�����ַ�ʽ:
//SEEK_SET ���ļ���ͷΪ��������ʼλ�á�
//SEEK_CUR ��Ŀǰ�ļ���дλ��Ϊ��������ʼλ��
//SEEK_END ���ļ���βΪ��������ʼλ�á�
// 
//����ֵ  �ɹ��򷵻�0�����д����򷵻�-1������ԭ�����errno.
// 
//�� 
//
// 
//
// 
//flock�������ļ�����������  
//��غ���  open,fcntl
// 
//��ͷ�ļ�  #include<sys/file.h>
// 
  int flock(int fd,int operation);
// 
//����˵��  flock()��������operation��ָ���ķ�ʽ�Բ���fd��ָ���ļ��������������������Ķ������˺���ֻ�����������ļ����޷������ļ���ĳһ����
// 
//����  operation�������������:
//LOCK_SH ��������������������̿�ͬʱ��ͬһ���ļ�������������
//LOCK_EX ��������������һ���ļ�ͬʱֻ��һ������������
//LOCK_UN ����ļ�����״̬��
//LOCK_NB �޷���������ʱ���˲����ɲ�����ϣ����Ϸ��ؽ��̡�ͨ����LOCK_SH��LOCK_EX ��OR(|)��ϡ�
//��һ�ļ��޷�ͬʱ�������������ͻ�������������ʹ��dup()��fork()ʱ�ļ������ʲ���̳д���������
// 
//����ֵ  ����0��ʾ�ɹ������д����򷵻�-1������������errno��
// 
//�� 
//
// 
//
// 
//fsync��������������д�ش��̣�  
//��غ���  sync
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int fsync(int fd);
// 
//����˵��  fsync()���𽫲���fd��ָ���ļ����ݣ���ϵͳ������д�ش��̣���ȷ������ͬ����
// 
//����ֵ  �ɹ��򷵻�0��ʧ�ܷ���-1��errnoΪ������롣
// 
//�� 
//
// 
//
// 
//lseek���ƶ��ļ��Ķ�дλ�ã�  
//��غ���  dup��open��fseek
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<unistd.h>
// 
  off_t lseek(int fildes,off_t offset ,int whence);
// 
//����˵��  ÿһ���Ѵ򿪵��ļ�����һ����дλ�ã������ļ�ʱͨ�����дλ����ָ���ļ���ͷ�������Ը��ӵķ�ʽ���ļ�(��O_APPEND)�����дλ�û�ָ���ļ�β����read()��write()ʱ����дλ�û���֮���ӣ�lseek()�����������Ƹ��ļ��Ķ�дλ�á�����fildes Ϊ�Ѵ򿪵��ļ������ʣ�����offset Ϊ���ݲ���whence���ƶ���дλ�õ�λ������
// 
//����  whenceΪ��������һ��:
//SEEK_SET ����offset��Ϊ�µĶ�дλ�á�
//SEEK_CUR ��Ŀǰ�Ķ�дλ����������offset��λ������
//SEEK_END ����дλ��ָ���ļ�β��������offset��λ������
//��whence ֵΪSEEK_CUR ��SEEK_ENDʱ������offet����ֵ�ĳ��֡�
//�����ǽ��ر��ʹ�÷�ʽ:
//1) ������дλ���Ƶ��ļ���ͷʱ:lseek��int fildes,0,SEEK_SET����
//2) ������дλ���Ƶ��ļ�βʱ:lseek��int fildes��0,SEEK_END����
//3) ��Ҫȡ��Ŀǰ�ļ�λ��ʱ:lseek��int fildes��0,SEEK_CUR����
// 
//����ֵ  �����óɹ�ʱ�򷵻�Ŀǰ�Ķ�дλ�ã�Ҳ���Ǿ����ļ���ͷ���ٸ��ֽڡ����д����򷵻�-1��errno ���Ŵ�����롣
// 
//����˵��  Linuxϵͳ������lseek������ttyװ�����ã����������lseek��������ESPIPE��
// 
//����  �ο�������˵��
// 
//�� 
//
// 
//
// 
//mkstemp������Ψһ����ʱ�ļ���  
//��غ���  mktemp
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  int mkstemp(char * template);
// 
//����˵��  mkstemp()��������Ψһ����ʱ�ļ�������template ��ָ���ļ������ַ�������������ַ�������XXXXXX��Mkstemp()���Կɶ�дģʽ��0600 Ȩ�����򿪸��ļ���������ļ���������Ὠ�����ļ����򿪸��ļ������ļ������ʻ᷵�ء��ļ�˳���򿪺󷵻ؿɶ�д���ļ������ʡ������ļ���ʧ���򷵻�NULL�����Ѵ���������errno �С�
// 
//�������  EINVAL ����template �ַ�����������ַ���XXXXXX��EEXIST �޷�������ʱ�ļ���
// 
//����˵��  ����template��ָ���ļ������ַ�����������Ϊ���飬��:
//char template[ ] =��template-XXXXXX��;
//ǧ�򲻿���ʹ�����еı�﷽ʽ
//char *template = ��template-XXXXXX��;
// 
//����  #include<stdlib.h>
//main( )
//{
//int fd;
//char template[ ]=��template-XXXXXX��;
//fd=mkstemp(template);
//printf(��template = %s\n��,template);
//close(fd);
//}
// 
//ִ��  template = template-lgZcbo
// 
//�� 
//
// 
//
// 
//open�����ļ���  
//��غ���  read��write��fcntl��close��link��stat��umask��unlink��fopen
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<sys/stat.h>
//#include<fcntl.h>
// 
  int open( const char * pathname, int flags);
//int open( const char * pathname,int flags, mode_t mode);
// 
//����˵��  ����pathname ָ�����򿪵��ļ�·���ַ����������ǲ���flags ����ʹ�õ����:
//O_RDONLY ��ֻ����ʽ���ļ�
//O_WRONLY ��ֻд��ʽ���ļ�
//O_RDWR �Կɶ�д��ʽ���ļ���������������ǻ���ģ�Ҳ���ǲ���ͬʱʹ�ã����������е��������OR(|)�������ϡ�
//O_CREAT �����򿪵��ļ����������Զ��������ļ���
//O_EXCL ���O_CREAT Ҳ�����ã���ָ���ȥ����ļ��Ƿ���ڡ��ļ����������������ļ������򽫵��´��ļ����󡣴��⣬��O_CREAT��O_EXCLͬʱ���ã��������򿪵��ļ�Ϊ�������ӣ������ļ�ʧ�ܡ�
//O_NOCTTY ������򿪵��ļ�Ϊ�ն˻��豸ʱ���򲻻Ὣ���ն˻����ɽ��̿����ն˻���
//O_TRUNC ���ļ����ڲ����Կ�д�ķ�ʽ��ʱ�����������ļ�������Ϊ0����ԭ�����ڸ��ļ�������Ҳ����ʧ��
//O_APPEND ����д�ļ�ʱ����ļ�β��ʼ�ƶ���Ҳ������д������ݻ��Ը��ӵķ�ʽ���뵽�ļ����档
//O_NONBLOCK �Բ�����ϵķ�ʽ���ļ���Ҳ���������������ݶ�ȡ��ȴ��������������ؽ���֮�С�
//O_NDELAY ͬO_NONBLOCK��
//O_SYNC ��ͬ���ķ�ʽ���ļ���
//O_NOFOLLOW �������pathname ��ָ���ļ�Ϊһ�������ӣ��������ļ�ʧ�ܡ�
//O_DIRECTORY �������pathname ��ָ���ļ�����ΪһĿ¼���������ļ�ʧ�ܡ�
//��ΪLinux2.2�Ժ����е���꣬�Ա���һЩϵͳ��ȫ���⡣����mode ��������������ϣ�ֻ���ڽ������ļ�ʱ�Ż���Ч�������������ļ�ʱ��Ȩ�޻��ܵ�umaskֵ��Ӱ�죬��˸��ļ�Ȩ��Ӧ��Ϊ��mode-umaks����
//S_IRWXU00700 Ȩ�ޣ�������ļ������߾��пɶ�����д����ִ�е�Ȩ�ޡ�
//S_IRUSR ��S_IREAD��00400Ȩ�ޣ�������ļ������߾��пɶ�ȡ��Ȩ�ޡ�
//S_IWUSR ��S_IWRITE��00200 Ȩ�ޣ�������ļ������߾��п�д���Ȩ�ޡ�
//S_IXUSR ��S_IEXEC��00100 Ȩ�ޣ�������ļ������߾��п�ִ�е�Ȩ�ޡ�
//S_IRWXG 00070Ȩ�ޣ�������ļ��û�����пɶ�����д����ִ�е�Ȩ�ޡ�
//S_IRGRP 00040 Ȩ�ޣ�������ļ��û�����пɶ���Ȩ�ޡ�
//S_IWGRP 00020Ȩ�ޣ�������ļ��û�����п�д���Ȩ�ޡ�
//S_IXGRP 00010 Ȩ�ޣ�������ļ��û�����п�ִ�е�Ȩ�ޡ�
//S_IRWXO 00007Ȩ�ޣ����������û����пɶ�����д����ִ�е�Ȩ�ޡ�
//S_IROTH 00004 Ȩ�ޣ����������û����пɶ���Ȩ��
//S_IWOTH 00002Ȩ�ޣ����������û����п�д���Ȩ�ޡ�
//S_IXOTH 00001 Ȩ�ޣ����������û����п�ִ�е�Ȩ�ޡ�
// 
//����ֵ  ���������˲��Ȩ�޶�ͨ���˼���򷵻�0 ֵ����ʾ�ɹ���ֻҪ��һ��Ȩ�ޱ���ֹ�򷵻�-1��
// 
//�������  EEXIST ����pathname ��ָ���ļ��Ѵ��ڣ�ȴʹ����O_CREAT��O_EXCL��ꡣ
//EACCESS ����pathname��ָ���ļ���������Ҫ����Ե�Ȩ�ޡ�
//EROFS ������д��Ȩ�޵��ļ�������ֻ���ļ�ϵͳ�ڡ�
//EFAULT ����pathnameָ�볬���ɴ�ȡ�ڴ�ռ䡣
//EINVAL ����mode ����ȷ��
//ENAMETOOLONG ����pathname̫����
//ENOTDIR ����pathname����Ŀ¼��
//ENOMEM �����ڴ治�㡣
//ELOOP ����pathname�й�������������⡣
//EIO I/O ��ȡ����
// 
//����˵��  ʹ��access()���û���֤������ж�Ҫ�ر�С�ģ�������access()������open()���ļ����ܻ����ϵͳ��ȫ�ϵ����⡣
// 
//����  #include<unistd.h>
//#include<sys/types.h>
//#include<sys/stat.h>
//#include<fcntl.h>
//main()
//{
//int fd,size;
//char s [ ]=��Linux Programmer!\n��,buffer[80];
//fd=open(��/tmp/temp��,O_WRONLY|O_CREAT);
//write(fd,s,sizeof(s));
//close(fd);
//fd=open(��/tmp/temp��,O_RDONLY);
//size=read(fd,buffer,sizeof(buffer));
//close(fd);
//printf(��%s��,buffer);
//}
// 
//ִ��  Linux Programmer!
// 
//�� 
//
// 
//
// 
//read�����Ѵ򿪵��ļ���ȡ���ݣ�  
//��غ���  readdir��write��fcntl��close��lseek��readlink��fread
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  ssize_t read(int fd,void * buf ,size_t count);
// 
//����˵��  read()��Ѳ���fd ��ָ���ļ�����count���ֽڵ�bufָ����ָ���ڴ��С�������countΪ0����read()���������ò�����0������ֵΪʵ�ʶ�ȡ�����ֽ������������0����ʾ�ѵ����ļ�β�����޿ɶ�ȡ�����ݣ������ļ���дλ�û����ȡ�����ֽ��ƶ���
// 
//����˵��  ���˳��read()�᷵��ʵ�ʶ������ֽ���������ܽ�����ֵ�����count ���Ƚϣ������ص��ֽ�����Ҫ���ȡ���ֽ����٣����п��ܶ������ļ�β���ӹܵ�(pipe)���ն˻���ȡ��������read()���ź��ж��˶�ȡ���������д�����ʱ�򷵻�-1������������errno�У����ļ���дλ�����޷�Ԥ�ڡ�
// 
//�������  EINTR �˵��ñ��ź����жϡ�
//EAGAIN ��ʹ�ò������I/O ʱ��O_NONBLOCK�����������ݿɶ�ȡ�򷵻ش�ֵ��
//EBADF ����fd ����Ч���ļ������ʣ�����ļ��ѹرա�
// 
//����  �ο�open������
// 
//�� 
//
// 
//
// 
//sync��������������д�ش��̣�  
//��غ���  fsync
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int sync(void)
// 
//����˵��  sync()����ϵͳ����������д�ش��̣���ȷ������ͬ����
// 
//����ֵ  ����0��
// 
//�� 
//
// 
//
#define	 ssize_t  int
//write��������д���Ѵ򿪵��ļ��ڣ�  
//��غ���  open��read��fcntl��close��lseek��sync��fsync��fwrite
// 
//��ͷ�ļ�  #include<unistd.h> 

	//ssize_t write (int fd,const void *buf,size_t count);
 	 ssize_t write(int fd,void * buf ,size_t count);
//����˵��  write()��Ѳ���buf��ָ���ڴ�д��count���ֽڵ�����fd��ָ���ļ��ڡ���Ȼ���ļ���дλ��Ҳ����֮�ƶ���
// 
//����ֵ  ���˳��write()�᷵��ʵ��д����ֽ��������д�����ʱ�򷵻�-1������������errno�С�
// 
//�������  EINTR �˵��ñ��ź����жϡ�
//EAGAIN ��ʹ�ò������I/O ʱ��O_NONBLOCK�����������ݿɶ�ȡ�򷵻ش�ֵ��
//EADF ����fd����Ч���ļ������ʣ�����ļ��ѹرա�
// 
//����  ��ο�open������
// 
//�� 
//
// 
//
//�ļ����ݲ���ƪ===================================================================
//�� 
//
// 
//
// 
//clearerr������ļ����Ĵ�����꣩  
//��غ���  feof
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  void clearerr(FILE * stream);
// 
//����˵��  clearerr�����������streamָ�����ļ�����ʹ�õĴ�����ꡣ
// 
//����ֵ  
// 
//�� 
//
// 
//
// 
//fclose���ر��ļ���  
//��غ���  close��fflush��fopen��setbuf
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int fclose(FILE * stream);
// 
//����˵��  fclose()�����ر���ǰfopen()�򿪵��ļ����˶������û������ڵ�����д���ļ��У����ͷ�ϵͳ���ṩ���ļ���Դ��
// 
//����ֵ  �����ļ������ɹ��򷵻�0���д�����ʱ�򷵻�EOF���Ѵ������浽errno��
// 
//�������  EBADF��ʾ����stream���Ѵ򿪵��ļ���
// 
//����  ��ο�fopen������
// 
//�� 
//
// 
//
// 
//fdopen�����ļ�������תΪ�ļ�ָ�룩  
//��غ���  fopen��open��fclose
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  FILE * fdopen(int fildes,const char * mode);
// 
//����˵��  fdopen()�Ὣ����fildes ���ļ������ʣ�ת��Ϊ��Ӧ���ļ�ָ��󷵻ء�����mode �ַ�����������ļ�ָ�������̬������̬�����ԭ���ļ������ʶ�дģʽ��ͬ������mode �ַ�����ʽ��ο�fopen()��
// 
//����ֵ  ת���ɹ�ʱ����ָ��������ļ�ָ�롣ʧ���򷵻�NULL�����Ѵ���������errno�С�
// 
//����  #include<stdio.h>
//main()
//{
//FILE * fp =fdopen(0,��w+��);
//fprintf(fp,��%s\n��,��hello!��);
//fclose(fp);
//}
// 
//ִ��  hello!
// 
//�� 
//
// 
//
// 
//feof������ļ����Ƿ�������ļ�β��  
//��غ���  fopen��fgetc��fgets��fread
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int feof(FILE * stream);
// 
//����˵��  feof()��������Ƿ��ȡ�����ļ�β��β��streamΪfopen����������֮�ļ�ָ�롣����ѵ��ļ�β�򷵻ط���ֵ�������������0��
// 
//����ֵ  ���ط���ֵ�����ѵ����ļ�β��
// 
//�� 
//
// 
//
// 
//fflush�����»�������  
//��غ���  write��fopen��fclose��setbuf
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int fflush(FILE* stream);
// 
//����˵��  fflush()��ǿ�Ƚ��������ڵ�����д�ز���streamָ�����ļ��С��������streamΪNULL��fflush()�Ὣ���д򿪵��ļ����ݸ��¡�
// 
//����ֵ  �ɹ�����0��ʧ�ܷ���EOF������������errno�С�
// 
//�������  EBADF ����stream ָ�����ļ�δ���򿪣����״̬Ϊֻ���������������ο�write������
// 
//�� 
//
// 
//
// 
//fgetc�����ļ��ж�ȡһ���ַ���  
//��غ���  open��fread��fscanf��getc
// 
//��ͷ�ļ�  include<stdio.h>
// 
  nt fgetc(FILE * stream);
// 
//����˵��  fgetc()�Ӳ���stream��ָ���ļ��ж�ȡһ���ַ����������ļ�β��������ʱ�㷵��EOF��
// 
//����ֵ  getc()�᷵�ض�ȡ�����ַ���������EOF���ʾ�����ļ�β��
// 
//����  #include<stdio.h>
//main()
//{
//FILE *fp;
//int c;
//fp=fopen(��exist��,��r��);
//while((c=fgetc(fp))!=EOF)
//printf(��%c��,c);
//fclose(fp);
//}
// 
//�� 
//
// 
//
// 
//fgets�����ļ��ж�ȡһ�ַ�����  
//��غ���  open��fread��fscanf��getc
// 
//��ͷ�ļ�  include<stdio.h>
// 
  har * fgets(char * s,int size,FILE * stream);
// 
//����˵��  fgets()�����Ӳ���stream��ָ���ļ��ڶ����ַ����浽����s��ָ���ڴ�ռ䣬ֱ�����ֻ����ַ��������ļ�β�����Ѷ���size-1���ַ�Ϊֹ���������NULL��Ϊ�ַ���������
// 
//����ֵ  gets()���ɹ��򷵻�sָ�룬����NULL���ʾ�д�������
// 
//����  #include<stdio.h>
//main()
//{
//char s[80];
//fputs(fgets(s,80,stdin),stdout);
//}
// 
//ִ��  this is a test /*����*/
//this is a test /*���*/
// 
//�� 
//
// 
//
// 
//fileno�������ļ�����ʹ�õ��ļ������ʣ�  
//��غ���  open��fopen
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int fileno(FILE * stream);
// 
//����˵��  fileno()����ȡ�ò���streamָ�����ļ�����ʹ�õ��ļ������ʡ�
// 
//����ֵ  �����ļ������ʡ�
// 
//����  #include<stdio.h>
//main()
//{
//FILE * fp;
//int fd;
//fp=fopen(��/etc/passwd��,��r��);
//fd=fileno(fp);
//printf(��fd=%d\n��,fd);
//fclose(fp);
//}
// 
//ִ��  fd=3
// 
//�� 
//
// 
//
// 
//fopen�����ļ���  
//��غ���  open��fclose
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  FILE * fopen(const char * path,const char * mode);
// 
//����˵��  ����path�ַ����������򿪵��ļ�·�����ļ���������mode�ַ��������������̬��
//mode�����м�����̬�ַ���:
//r ��ֻ���ļ������ļ�������ڡ�
//r+ �򿪿ɶ�д���ļ������ļ�������ڡ�
//w ��ֻд�ļ������ļ��������ļ�������Ϊ0�������ļ����ݻ���ʧ�����ļ��������������ļ���
//w+ �򿪿ɶ�д�ļ������ļ��������ļ�������Ϊ�㣬�����ļ����ݻ���ʧ�����ļ��������������ļ���
//a �Ը��ӵķ�ʽ��ֻд�ļ������ļ������ڣ���Ὠ�����ļ�������ļ����ڣ�д������ݻᱻ�ӵ��ļ�β�����ļ�ԭ�ȵ����ݻᱻ������
//a+ �Ը��ӷ�ʽ�򿪿ɶ�д���ļ������ļ������ڣ���Ὠ�����ļ�������ļ����ڣ�д������ݻᱻ�ӵ��ļ�β�󣬼��ļ�ԭ�ȵ����ݻᱻ������
//��������̬�ַ����������ټ�һ��b�ַ�����rb��w+b��ab������ϣ�����b �ַ��������ߺ�����򿪵��ļ�Ϊ�������ļ������Ǵ������ļ���������POSIXϵͳ������Linux������Ը��ַ�����fopen()�����������ļ������S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH(0666)Ȩ�ޣ����ļ�Ȩ��Ҳ��ο�umaskֵ��
// 
//����ֵ  �ļ�˳���򿪺�ָ��������ļ�ָ��ͻᱻ���ء������ļ���ʧ���򷵻�NULL�����Ѵ���������errno �С�
// 
//����˵��  һ����ԣ����ļ������һЩ�ļ���ȡ��д��Ķ����������ļ�ʧ�ܣ��������Ķ�д����Ҳ�޷�˳�����У�������fopen()�����������жϼ�����
// 
//����  #include<stdio.h>
//main()
//{
//FILE * fp;
//fp=fopen(��noexist��,��a+��);
//if(fp= =NULL) return;
//fclose(fp);
//}
// 
//�� 
//
// 
//
// 
//fputc����һָ���ַ�д���ļ����У�  
//��غ���  fopen��fwrite��fscanf��putc
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int fputc(int c,FILE * stream);
// 
//����˵��  fputc �Ὣ����c תΪunsigned char ��д�����stream ָ�����ļ��С�
// 
//����ֵ  fputc()�᷵��д��ɹ����ַ���������c��������EOF�����д��ʧ�ܡ�
// 
//����  #include<stdio.h>
//main()
//{
//FILE * fp;
//char a[26]=��abcdefghijklmnopqrstuvwxyz��;
//int i;
//fp= fopen(��noexist��,��w��);
//for(i=0;i<26;i++)
//fputc(a[i],fp);
//fclose(fp);
//}
// 
//�� 
//
// 
//
// 
//fputs����һָ�����ַ���д���ļ��ڣ�  
//��غ���  fopen��fwrite��fscanf��fputc��putc
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int fputs(const char * s,FILE * stream);
// 
//����˵��  fputs()����������s��ָ���ַ���д�뵽����stream��ָ���ļ��ڡ�
// 
//����ֵ  ���ɹ��򷵻�д�����ַ�����������EOF���ʾ�д�������
// 
//����  ��ο�fgets������
// 
//�� 
//
// 
//
// 
//fread�����ļ�����ȡ���ݣ�  
//��غ���  fopen��fwrite��fseek��fscanf
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  size_t fread(void * ptr,size_t size,size_t nmemb,FILE * stream);
// 
//����˵��  fread()�������ļ����ж�ȡ���ݡ�����streamΪ�Ѵ򿪵��ļ�ָ�룬����ptr ָ������Ŷ�ȡ���������ݿռ䣬��ȡ���ַ����Բ���size*nmemb��������Fread()�᷵��ʵ�ʶ�ȡ����nmemb��Ŀ�������ֵ�Ȳ���nmemb ����С���������ܶ������ļ�β���д���������ʱ������feof()��ferror()����������ʲô�����
// 
//����ֵ  ����ʵ�ʶ�ȡ����nmemb��Ŀ��
// 
//����˵��  
// 
//����  #include<stdio.h>
//#define nmemb 3
//struct test
//{
//char name[20];
//int size;
//}s[nmemb];
//main()
//{
//FILE * stream;
//int i;
//stream = fopen(��/tmp/fwrite��,��r��);
//fread(s,sizeof(struct test),nmemb,stream);
//fclose(stream);
//for(i=0;i<nmemb;i++)
//printf(��name[%d]=%-20s:size[%d]=%d\n��,i,s[i].name,i,s[i].size);
//}
// 
//ִ��  name[0]=Linux! size[0]=6
//name[1]=FreeBSD! size[1]=8
//name[2]=Windows2000 size[2]=11
// 
//�� 
//
// 
//
// 
//freopen�����ļ���  
//��غ���  fopen��fclose
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  FILE * freopen(const char * path,const char * mode,FILE * stream);
// 
//����˵��  ����path�ַ����������򿪵��ļ�·�����ļ���������mode��ο�fopen()˵��������streamΪ�Ѵ򿪵��ļ�ָ�롣Freopen()�Ὣԭstream���򿪵��ļ����رգ�Ȼ��򿪲���path���ļ���
// 
//����ֵ  �ļ�˳���򿪺�ָ��������ļ�ָ��ͻᱻ���ء�����ļ���ʧ���򷵻�NULL�����Ѵ���������errno �С�
// 
//����  #include<stdio.h>
//main()
//{
//FILE * fp;
//fp=fopen(��/etc/passwd��,��r��);
//fp=freopen(��/etc/group��,��r��,fp);
//fclose(fp);
//}
// 
//�� 
//
// 
//
// 
//fseek���ƶ��ļ����Ķ�дλ�ã�  
//��غ���  rewind��ftell��fgetpos��fsetpos��lseek
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int fseek(FILE * stream,long offset,int whence);
// 
//����˵��  fseek()�����ƶ��ļ����Ķ�дλ�á�����streamΪ�Ѵ򿪵��ļ�ָ�룬����offsetΪ���ݲ���whence���ƶ���дλ�õ�λ������
// 
//����  whenceΪ��������һ��:
//SEEK_SET�Ӿ��ļ���ͷoffsetλ����Ϊ�µĶ�дλ�á�SEEK_CUR ��Ŀǰ�Ķ�дλ����������offset��λ������
//SEEK_END����дλ��ָ���ļ�β��������offset��λ������
//��whenceֵΪSEEK_CUR ��SEEK_ENDʱ������offset����ֵ�ĳ��֡�
//�����ǽ��ر��ʹ�÷�ʽ:
//1) ������дλ���ƶ����ļ���ͷʱ:fseek(FILE *stream,0,SEEK_SET);
//2) ������дλ���ƶ����ļ�βʱ:fseek(FILE *stream,0,0SEEK_END);
// 
//����ֵ  �����óɹ�ʱ�򷵻�0�����д����򷵻�-1��errno���Ŵ�����롣
// 
//����˵��  fseek()����lseek()�᷵�ض�дλ�ã���˱���ʹ��ftell()��ȡ��Ŀǰ��д��λ�á�
// 
//����  #include<stdio.h>
//main()
//{
//FILE * stream;
//long offset;
//fpos_t pos;
//stream=fopen(��/etc/passwd��,��r��);
//fseek(stream,5,SEEK_SET);
//printf(��offset=%d\n��,ftell(stream));
//rewind(stream);
//fgetpos(stream,&pos);
//printf(��offset=%d\n��,pos);
//pos=10;
//fsetpos(stream,&pos);
//printf(��offset = %d\n��,ftell(stream));
//fclose(stream);
//}
// 
//ִ��  offset = 5
//offset =0
//offset=10
// 
//�� 
//
// 
//
// 
//ftell��ȡ���ļ����Ķ�ȡλ�ã�  
//��غ���  fseek��rewind��fgetpos��fsetpos
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  long ftell(FILE * stream);
// 
//����˵��  ftell()����ȡ���ļ���Ŀǰ�Ķ�дλ�á�����streamΪ�Ѵ򿪵��ļ�ָ�롣
// 
//����ֵ  �����óɹ�ʱ�򷵻�Ŀǰ�Ķ�дλ�ã����д����򷵻�-1��errno���Ŵ�����롣
// 
//�������  EBADF ����stream��Ч����ƶ���дλ�õ��ļ�����
// 
//����  �ο�fseek()��
// 
//�� 
//
// 
//
// 
//fwrite��������д���ļ�����  
//��غ���  fopen��fread��fseek��fscanf
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  size_t fwrite(const void * ptr,size_t size,size_t nmemb,FILE * stream);
// 
//����˵��  fwrite()����������д���ļ����С�����streamΪ�Ѵ򿪵��ļ�ָ�룬����ptr ָ����д������ݵ�ַ���ܹ�д����ַ����Բ���size*nmemb��������Fwrite()�᷵��ʵ��д���nmemb��Ŀ��
// 
//����ֵ  ����ʵ��д���nmemb��Ŀ��
// 
//����  #include<stdio.h>
//#define set_s (x,y) {strcoy(s[x].name,y);s[x].size=strlen(y);}
//#define nmemb 3
//struct test
//{
//char name[20];
//int size;
//}s[nmemb];
//main()
//{
//FILE * stream;
//set_s(0,��Linux!��);
//set_s(1,��FreeBSD!��);
//set_s(2,��Windows2000.��);
//stream=fopen(��/tmp/fwrite��,��w��);
//fwrite(s,sizeof(struct test),nmemb,stream);
//fclose(stream);
//}
// 
//ִ��  �ο�fread������
// 
//�� 
//
// 
//
// 
//getc�����ļ��ж�ȡһ���ַ���  
//��غ���  read��fopen��fread��fgetc
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int getc(FILE * stream);
// 
//����˵��  getc()�����Ӳ���stream��ָ���ļ��ж�ȡһ���ַ����������ļ�β��������ʱ�㷵��EOF����Ȼgetc()��fgetc()������ͬ����getc()Ϊ�궨�壬�������ĺ������á�
// 
//����ֵ  getc()�᷵�ض�ȡ�����ַ���������EOF���ʾ�����ļ�β��
// 
//����  �ο�fgetc()��
// 
//�� 
//
// 
//
// 
//getchar���ɱ�׼�����豸�ڶ���һ�ַ���  
//��غ���  fopen��fread��fscanf��getc
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int getchar(void);
// 
//����˵��  getchar()�����ӱ�׼�����豸�ж�ȡһ���ַ���Ȼ�󽫸��ַ���unsigned charת����int�󷵻ء�
// 
//����ֵ  getchar()�᷵�ض�ȡ�����ַ���������EOF���ʾ�д�������
// 
//����˵��  getchar()����������������getc(stdin)�궨�塣
// 
//����  #include<stdio.h>
//main()
//{
//FILE * fp;
//int c,i;
//for(i=0li<5;i++)
//{
//c=getchar();
//putchar(c);
//}
//}
// 
//ִ��  1234 /*����*/
//1234 /*���*/
// 
//�� 
//
// 
//
// 
//gets���ɱ�׼�����豸�ڶ���һ�ַ�����  
//��غ���  fopen��fread��fscanf��fgets
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  char * gets(char *s);
// 
//����˵��  gets()�����ӱ�׼�豸�����ַ����浽����s��ָ���ڴ�ռ䣬ֱ�����ֻ����ַ�������ļ�βΪֹ��������NULL��Ϊ�ַ���������
// 
//����ֵ  gets()���ɹ��򷵻�sָ�룬����NULL���ʾ�д�������
// 
//����˵��  ����gets()�޷�֪���ַ���s�Ĵ�С���������������ַ����ļ�β�Ż�������룬���������ɻ�������İ�ȫ�����⡣����ʹ��fgets()ȡ����
// 
//����  �ο�fgets()
// 
//�� 
//
// 
//
// 
//mktemp������Ψһ����ʱ�ļ�����  
//��غ���  tmpfile
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  char * mktemp(char * template);
// 
//����˵��  mktemp()��������Ψһ����ʱ�ļ���������template��ָ���ļ������ַ�������������ַ�������XXXXXX����������ļ�������ַ���ָ�뷵�ء�
// 
//����ֵ  �ļ�˳���򿪺�ָ��������ļ�ָ��ͻᱻ���ء�����ļ���ʧ���򷵻�NULL�����Ѵ���������errno�С�
// 
//����˵��  ����template��ָ���ļ������ַ�����������Ϊ���飬��:
//char template[ ]=��template-XXXXXX����
//������char * template=��template-XXXXXX����
// 
//����  #include<stdlib.h>
//main()
//{
//char template[ ]=��template-XXXXXX��;
//mktemp(template);
//printf(��template=%s\n��,template);
//}
// 
//�� 
//
// 
//
// 
//putc����һָ���ַ�д���ļ��У�  
//��غ���  fopen��fwrite��fscanf��fputc
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int putc(int c,FILE * stream);
// 
//����˵��  putc()�Ὣ����cתΪunsigned char��д�����streamָ�����ļ��С���Ȼputc()��fputc()������ͬ����putc()Ϊ�궨�壬�������ĺ������á�
// 
//����ֵ  putc()�᷵��д��ɹ����ַ���������c��������EOF�����д��ʧ�ܡ�
// 
//����  �ο�fputc������
// 
//�� 
//
// 
//
// 
//putchar����ָ�����ַ�д����׼����豸��  
//��غ���  fopen��fwrite��fscanf��fputc
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int putchar (int c);
// 
//����˵��  putchar()����������c�ַ�д����׼����豸��
// 
//����ֵ  putchar()�᷵������ɹ����ַ���������c��������EOF��������ʧ�ܡ�
// 
//����˵��  putchar()����������������putc(c��stdout)�궨�塣
// 
//����  �ο�getchar()��
// 
//�� 
//
// 
//
// 
//rewind�������ļ����Ķ�дλ��Ϊ�ļ���ͷ��  
//��غ���  fseek��ftell��fgetpos��fsetpos
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  void rewind(FILE * stream);
// 
//����˵��  rewind()�������ļ����Ķ�дλ�������ļ���ͷ������streamΪ�Ѵ򿪵��ļ�ָ�롣�˺����൱�ڵ���fseek(stream,0,SEEK_SET)��
// 
//����ֵ  
// 
//����  �ο�fseek()
// 
//�� 
//
// 
//
// 
//setbuf�������ļ����Ļ�������  
//��غ���  setbuffer��setlinebuf��setvbuf
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  void setbuf(FILE * stream,char * buf);
// 
//����˵��  �ڴ��ļ����󣬶�ȡ����֮ǰ������setbuf()�������������ļ����Ļ�����������streamΪָ�����ļ���������bufָ���Զ��Ļ�������ʼ��ַ���������bufΪNULLָ�룬��Ϊ�޻���IO��Setbuf()�൱�ڵ���:setvbuf(stream,buf,buf?_IOFBF:_IONBF,BUFSIZ) 
// 
//����ֵ  
// 
//�� 
//
// 
//
// 
//setbuffer�������ļ����Ļ�������  
//��غ���  setlinebuf��setbuf��setvbuf
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  void setbuffer(FILE * stream,char * buf,size_t size);
// 
//����˵��  �ڴ��ļ����󣬶�ȡ����֮ǰ������setbuffer()�����������ļ����Ļ�����������streamΪָ�����ļ���������bufָ���Զ��Ļ�������ʼ��ַ������sizeΪ��������С��
// 
//����ֵ  
// 
//�� 
//
// 
//
// 
//setlinebuf�������ļ���Ϊ���Ի�������  
//��غ���  setbuffer��setbuf��setvbuf
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  void setlinebuf(FILE * stream);
// 
//����˵��  setlinebuf()���������ļ����Ի���Ϊ���ݵ��޻���IO���൱�ڵ���:setvbuf(stream,(char * )NULL,_IOLBF,0);��ο�setvbuf()��
// 
//����ֵ  
// 
//�� 
//
// 
//
// 
//setvbuf�������ļ����Ļ�������  
//��غ���  setbuffer��setlinebuf��setbuf
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int setvbuf(FILE * stream,char * buf,int mode,size_t size);
// 
//����˵��  �ڴ��ļ����󣬶�ȡ����֮ǰ������setvbuf()�������������ļ����Ļ�����������streamΪָ�����ļ���������bufָ���Զ��Ļ�������ʼ��ַ������sizeΪ��������С������mode�����м���
//_IONBF �޻���IO
//_IOLBF �Ի���Ϊ���ݵ��޻���IO
//_IOFBF ��ȫ�޻���IO���������bufΪNULLָ�룬��Ϊ�޻���IO��
// 
//����ֵ  
// 
//�� 
//
// 
//
// 
//ungetc����ָ���ַ�д���ļ����У�  
//��غ���  fputc��getchar��getc
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int ungetc(int c,FILE * stream);
// 
//����˵��  ungetc()������c�ַ�д�ز���stream��ָ�����ļ��������д�ص��ַ�������һ����ȡ�ļ����ĺ���ȡ�á�
// 
//����ֵ  �ɹ��򷵻�c �ַ������д����򷵻�EOF��
// 
//�� 
//
//���̲���ƪ=============================================================================
//�� 
//
// 
//
// 
//atexit�����ó�����������ǰ���õĺ�����  
//��غ���  _exit,exit,on_exit
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  int atexit (void (*function)(void));
// 
//����˵��  atexit()��������һ��������������ǰ���õĺ�����������ͨ������exit()���main�з���ʱ������function��ָ���ĺ������ȱ����ã�Ȼ���������exit()��������
// 
//����ֵ  ���ִ�гɹ��򷵻�0�����򷵻�-1��ʧ��ԭ�����errno�С�
// 
//����  #include<stdlib.h>
//void my_exit(void)
//{
//printf(��before exit () !\n��);
//}
//main()
//{
//atexit (my_exit);
//exit(0);
//}
// 
//ִ��  before exit()!
// 
//�� 
//
// 
//
// 
//execl��ִ���ļ���  
//��غ���  fork��execle��execlp��execv��execve��execvp
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int execl(const char * path,const char * arg,....);
// 
//����˵��  execl()����ִ�в���path�ַ�����������ļ�·�����������Ĳ�������ִ�и��ļ�ʱ���ݹ�ȥ��argv(0)��argv[1]���������һ�����������ÿ�ָ��(NULL)��������
// 
//����ֵ  ���ִ�гɹ��������᷵�أ�ִ��ʧ����ֱ�ӷ���-1��ʧ��ԭ�����errno�С�
// 
//����  #include<unistd.h>
//main()
//{
//execl(��/bin/ls��,��ls��,��-al��,��/etc/passwd��,(char * )0);
//}
// 
//ִ��  /*ִ��/bin/ls -al /etc/passwd */
//-rw-r--r-- 1 root root 705 Sep 3 13 :52 /etc/passwd
// 
//�� 
//
// 
//
// 
//execlp����PATH ���������в����ļ���ִ�У�  
//��غ���  fork��execl��execle��execv��execve��execvp
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int execlp(const char * file,const char * arg,����);
// 
//����˵��  execlp()���PATH ����������ָ��Ŀ¼�в��ҷ��ϲ���file���ļ������ҵ����ִ�и��ļ���Ȼ�󽫵ڶ����Ժ�Ĳ����������ļ���argv[0]��argv[1]���������һ�����������ÿ�ָ��(NULL)��������
// 
//����ֵ  ���ִ�гɹ��������᷵�أ�ִ��ʧ����ֱ�ӷ���-1��ʧ��ԭ�����errno �С�
// 
//�������  �ο�execve()��
// 
//����  /* ִ��ls -al /etc/passwd execlp()����PATH �����е�/bin�ҵ�/bin/ls */
//#include<unistd.h>
//main()
//{
//execlp(��ls��,��ls��,��-al��,��/etc/passwd��,(char *)0);
//}
// 
//ִ��  -rw-r--r-- 1 root root 705 Sep 3 13 :52 /etc/passwd
// 
//�� 
//
// 
//
// 
//execv��ִ���ļ���  
//��غ���  fork��execl��execle��execlp��execve��execvp
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int execv (const char * path, char * const argv[ ]);
// 
//����˵��  execv()����ִ�в���path�ַ�����������ļ�·������execl()��ͬ�ĵط�����execve()ֻ�������������ڶ���������������ָ�������ݸ�ִ���ļ���
// 
//����ֵ  ���ִ�гɹ��������᷵�أ�ִ��ʧ����ֱ�ӷ���-1��ʧ��ԭ�����errno �С�
// 
//�������  ��ο�execve������
// 
//����  /* ִ��/bin/ls -al /etc/passwd */
//#include<unistd.h>
//main()
//{
//char * argv[ ]={��ls��,��-al��,��/etc/passwd��,(char*) }};
//execv(��/bin/ls��,argv);
//}
// 
//ִ��  -rw-r--r-- 1 root root 705 Sep 3 13 :52 /etc/passwd
// 
//�� 
//
// 
//
// 
//execve��ִ���ļ���  
//��غ���  fork��execl��execle��execlp��execv��execvp
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int execve(const char * filename,char * const argv[ ],char * const envp[ ]);
// 
//����˵��  execve()����ִ�в���filename�ַ�����������ļ�·�����ڶ�������ϵ��������ָ�������ݸ�ִ���ļ������һ��������Ϊ���ݸ�ִ���ļ����»����������顣
// 
//����ֵ  ���ִ�гɹ��������᷵�أ�ִ��ʧ����ֱ�ӷ���-1��ʧ��ԭ�����errno �С�
// 
//�������  EACCES
//1. ��ִ�е��ļ��������û���ִ�е�Ȩ�ޡ�
//2. ��ִ�е��ļ��������ļ�ϵͳ����noexec ��ʽ���ϡ�
//3.��ִ�е��ļ���script��������һ���ļ���
//EPERM
//1.���̴��ڱ�׷��ģʽ��ִ���߲�������rootȨ�ޣ���ִ�е��ļ�����SUID ��SGID λ��
//2.��ִ�е��ļ��������ļ�ϵͳ����nosuid��ʽ���ϣ���ִ�е��ļ�����SUID ��SGID λԪ����ִ���߲�������rootȨ�ޡ�
//E2BIG �����������
//ENOEXEC �޷��ж���ִ���ļ���ִ���ļ���ʽ���п����Ǹ�ʽ������޷��ڴ�ƽִ̨�С�
//EFAULT ����filename��ָ���ַ�����ַ�����ɴ�ȡ�ռ䷶Χ��
//ENAMETOOLONG ����filename��ָ���ַ���̫����
//ENOENT ����filename�ַ�����ָ�����ļ������ڡ�
//ENOMEM �����ڴ治��
//ENOTDIR ����filename�ַ�����������Ŀ¼·��������ЧĿ¼
//EACCES ����filename�ַ�����������Ŀ¼·���޷���ȡ��Ȩ�޲���
//ELOOP ����ķ�������
//ETXTBUSY ��ִ�е��ļ��ѱ��������̴򿪶�����������д����ļ���
//EIO I/O ��ȡ����
//ENFILE �Ѵﵽϵͳ������Ĵ��ļ�������
//EMFILE �Ѵﵽϵͳ������һ�������ܴ򿪵��ļ�������
//EINVAL ��ִ���ļ���ELFִ�и�ʽ��ֻһ��PT_INTERP����
//EISDIR ELF������ΪһĿ¼
//ELIBBAD ELF�����������⡣
// 
//����  #include<unistd.h>
//main()
//{
//char * argv[ ]={��ls��,��-al��,��/etc/passwd��,(char *)0};
//char * envp[ ]={��PATH=/bin��,0}
//execve(��/bin/ls��,argv,envp);
//}
// 
//ִ��  -rw-r--r-- 1 root root 705 Sep 3 13 :52 /etc/passwd
// 
//�� 
//
// 
//
// 
//execvp��ִ���ļ���  
//��غ���  fork��execl��execle��execlp��execv��execve
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int execvp(const char *file ,char * const argv []);
// 
//����˵��  execvp()���PATH ����������ָ��Ŀ¼�в��ҷ��ϲ���file ���ļ������ҵ����ִ�и��ļ���Ȼ�󽫵ڶ�������argv��������ִ�е��ļ���
// 
//����ֵ  ���ִ�гɹ��������᷵�أ�ִ��ʧ����ֱ�ӷ���-1��ʧ��ԭ�����errno�С�
// 
//�������  ��ο�execve������
// 
//����  /*����execlp������������*/
//#include<unistd.h>
//main()
//{
//char * argv[ ] ={ ��ls��,��-al��,��/etc/passwd��,0};
//execvp(��ls��,argv);
//}
// 
//ִ��  -rw-r--r-- 1 root root 705 Sep 3 13 :52 /etc/passwd
// 
//�� 
//
// 
//
// 
//exit�������������̣�  
//��غ���  _exit��atexit��on_exit
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  void exit(int status);
// 
//����˵��  exit()���������ս�Ŀǰ���̵�ִ�У����Ѳ���status���ظ������̣����������еĻ��������ݻ��Զ�д�ز��ر�δ�رյ��ļ���
// 
//����ֵ  
// 
//����  �ο�wait����
// 
//�� 
//
// 
//
//_  
//exit����������ִ�У�  
//��غ���  exit��wait��abort
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  void _exit(int status);
// 
//����˵��  _exit()�������̽���Ŀǰ���̵�ִ�У����Ѳ���status���ظ������̣����ر�δ�رյ��ļ����˺������ú󲻻᷵�أ����һᴫ��SIGCHLD�źŸ������̣������̿�����wait����ȡ���ӽ��̽���״̬��
// 
//����ֵ  
// 
//����˵��  _exit�������ᴦ���׼I/O ����������Ҫ���»�������ʹ��exit������
// 
//�� 
//
// 
//
// 
//vfork������һ���µĽ��̣�  
//��غ���  wait��execve
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  pid_t vfork(void);
  pid_t  fork(void);
// 
//����˵��  vfork()�����һ���µ��ӽ��̣����ӽ��̻Ḵ�Ƹ����̵��������ջ�ռ䣬���̳и����̵��û����룬����룬�����������Ѵ򿪵��ļ����롢����Ŀ¼����Դ���Ƶȡ�Linux ʹ��copy-on-write(COW)������ֻ�е�����һ������ͼ�޸������ƵĿռ�ʱ�Ż��������ĸ��ƶ�����������Щ�̳е���Ϣ�Ǹ��ƶ���������ָ��ͬ���ڴ�ռ䣬����ӽ��̶���Щ�������޸ĺ͸����̲�����ͬ�������⣬�ӽ��̲���̳и����̵��ļ�������δ������źš�ע�⣬Linux����֤�ӽ��̻�ȸ�������ִ�л���ִ�У���˱�д����ʱҪ����
// 
//�������������ķ�����  
// 
//����ֵ  ���vfork()�ɹ����ڸ����̻᷵���½������ӽ��̴���(PID)�������½������ӽ������򷵻�0�����vfork ʧ����ֱ�ӷ���-1��ʧ��ԭ�����errno�С�
// 
//�������  EAGAIN �ڴ治�㡣ENOMEM �ڴ治�㣬�޷����ú�����������ݽṹ�ռ䡣
// 
//����  #include<unistd.h>
//main()
//{
//if(vfork() = =0)
//{
//printf(��This is the child process\n��);
//}else{
//printf(��This is the parent process\n��);
//}
//}
// 
//ִ��  this is the parent process
//this is the child process
// 
//�� 
//
	 setsid(); 
//��ʹ������ȫ�����������Ӷ����������������̵Ŀ��ơ� 
//˵�����������ǻỰ�鳤ʱsetsid()����ʧ�ܡ�����һ���Ѿ���֤���̲��ǻ�
//���鳤��setsid()���óɹ��󣬽��̳�Ϊ�µĻỰ�鳤���µĽ����鳤��
//����ԭ���ĵ�¼�Ự�ͽ��������롣���ڻỰ���̶Կ����ն˵Ķ�ռ�ԣ�
//����ͬʱ������ն����롣 
//
// 
//getpgid��ȡ�ý�����ʶ���룩  
//��غ���  setpgid��setpgrp��getpgrp
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  pid_t getpgid( pid_t pid);
// 
//����˵��  getpgid()����ȡ�ò���pid ָ��������������ʶ���롣�������pidΪ0�����ȡ��Ŀǰ���̵���ʶ���롣
// 
//����ֵ  ִ�гɹ��򷵻���ʶ���룬����д����򷵻�-1������ԭ�����errno�С�
// 
//�������  ESRCH �Ҳ������ϲ���pid ָ���Ľ��̡�
// 
//����  /*ȡ��init ���̣�pid��1������ʶ����*/
//#include<unistd.h>
//mian()
//{
//printf(��init gid = %d\n��,getpgid(1));
//}
// 
//ִ��  init gid = 0
// 
//�� 
//
// 
//
// 
//getpgrp��ȡ�ý�����ʶ���룩  
//��غ���  setpgid��getpgid��getpgrp
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  pid_t getpgrp(void);
// 
//����˵��  getpgrp()����ȡ��Ŀǰ������������ʶ���롣�˺����൱�ڵ���getpgid(0)��
// 
//����ֵ  ����Ŀǰ������������ʶ���롣
// 
//����  #include<unistd.h>
//main()
//{
//printf(��my gid =%d\n��,getpgrp());
//}
// 
//ִ��  my gid =29546
// 
//�� 
//
// 
//
// 
//getpid��ȡ�ý���ʶ���룩  
//��غ���  fork��kill��getpid
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  pid_t getpid(void);
// 
//����˵��  getpid��������ȡ��Ŀǰ���̵Ľ���ʶ���룬����������ȡ���Ĵ�ֵ��������ʱ�ļ����Ա�����ʱ�ļ���ͬ���������⡣
// 
//����ֵ  Ŀǰ���̵Ľ���ʶ����
// 
//����  #include<unistd.h>
//main()
//{
//printf(��pid=%d\n��,getpid());
//}
// 
//ִ��  pid=1494 /*ÿ��ִ�н������һ����ͬ*/
// 
//�� 
//
// 
//
// 
//getppid��ȡ�ø����̵Ľ���ʶ���룩  
//��غ���  fork��kill��getpid
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  pid_t getppid(void);
// 
//����˵��  getppid()����ȡ��Ŀǰ���̵ĸ�����ʶ���롣
// 
//����ֵ  Ŀǰ���̵ĸ�����ʶ���롣
// 
//����  #include<unistd.h>
//main()
//{
//printf(��My parent ��pid =%d\n��,getppid());
//}
// 
//ִ��  My parent pid =463
// 
//�� 
//
// 
//
// 
//getpriority��ȡ�ó������ִ������Ȩ��  
//��غ���  setpriority��nice
// 
//��ͷ�ļ�  #include<sys/time.h>
//#include<sys/resource.h>
// 
  int getpriority(int which,int who);
// 
//����˵��  getpriority()������ȡ�ý��̡���������û��Ľ���ִ������Ȩ��
// 
//����  which��������ֵ������who ����whichֵ�в�ͬ����
//which who ���������
//PRIO_PROCESS who Ϊ����ʶ����
//PRIO_PGRP who Ϊ���̵���ʶ����
//PRIO_USER who Ϊ�û�ʶ����
//�˺������ص���ֵ����-20 ��20֮�䣬�������ִ������Ȩ����ֵԽ�ʹ����нϸߵ����ȴ���ִ�л��Ƶ����
// 
//����ֵ  ���ؽ���ִ������Ȩ�����д���������ֵ��Ϊ-1 �Ҵ���ԭ�����errno��
// 
//����˵��  ���ڷ���ֵ�п�����-1�����Ҫͬʱ���errno�Ƿ���д���ԭ������ڵ��ôκ���ǰ�����errno������
// 
//�������  ESRCH ����which��who �����д����Ҳ������ϵĽ��̡�EINVAL ����which ֵ����
// 
//�� 
//
// 
//
// 
//nice���ı��������˳��  
//��غ���  setpriority��getpriority
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int nice(int inc);
// 
//����˵��  nice()�����ı���̵Ľ���ִ������˳�򡣲���inc��ֵԽ��������˳������Խ���棬����ʾ����ִ�л�Խ����ֻ�г����û�����ʹ�ø���inc ֵ����������˳������ǰ�棬����ִ�л�Ͽ졣
// 
//����ֵ  ���ִ�гɹ��򷵻�0�����򷵻�-1��ʧ��ԭ�����errno�С�
// 
//�������  EPERM һ���û���ͼת�ø��Ĳ���incֵ�ı��������˳��
// 
//�� 
//
// 
//
// 
//on_exit�����ó�����������ǰ���õĺ�����  
//��غ���  _exit��atexit��exit
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  int on_exit(void (* function)(int, void*),void *arg);
// 
//����˵��  on_exit()��������һ��������������ǰ���õĺ�����������ͨ������exit()���main�з���ʱ������function��ָ���ĺ������ȱ����ã�Ȼ���������exit()�������򡣲���argָ��ᴫ������function��������ϸ������������
// 
//����ֵ  ���ִ�гɹ��򷵻�0�����򷵻�-1��ʧ��ԭ�����errno�С�
// 
//����˵��  
// 
//����  #include<stdlib.h>
//void my_exit(int status,void *arg)
//{
//printf(��before exit()!\n��);
//printf(��exit (%d)\n��,status);
//printf(��arg = %s\n��,(char*)arg);
//}
//main()
//{
//char * str=��test��;
//on_exit(my_exit,(void *)str);
//exit(1234);
//}
// 
//ִ��  before exit()!
//exit (1234)
//arg = test
// 
//�� 
//
// 
//
// 
//setpgid�����ý�����ʶ���룩  
//��غ���  getpgid��setpgrp��getpgrp
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int setpgid(pid_t pid,pid_t pgid);
// 
//����˵��  setpgid()������pid ָ��������������ʶ������Ϊ����pgid ָ������ʶ���롣�������pid Ϊ0�������������Ŀǰ���̵���ʶ���룬�������pgidΪ0�������Ŀǰ���̵Ľ���ʶ������ȡ����
// 
//����ֵ  ִ�гɹ��򷵻���ʶ���룬����д����򷵻�-1������ԭ�����errno�С�
// 
//�������  EINVAL ����pgidС��0��
//EPERM ����Ȩ�޲��㣬�޷���ɵ��á�
//ESRCH �Ҳ������ϲ���pidָ���Ľ��̡�
// 
//�� 
//
// 
//
// 
//setpgrp�����ý�����ʶ���룩  
//��غ���  getpgid��setpgid��getpgrp
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int setpgrp(void);
// 
//����˵��  setpgrp()��Ŀǰ������������ʶ������ΪĿǰ���̵Ľ���ʶ���롣�˺����൱�ڵ���setpgid(0,0)��
// 
//����ֵ  ִ�гɹ��򷵻���ʶ���룬����д����򷵻�-1������ԭ�����errno�С�
// 
//�� 
//
// 
//
// 
//setpriority�����ó������ִ������Ȩ��  
//��غ���  getpriority��nice
// 
//��ͷ�ļ�  #include<sys/time.h>
//#include<sys/resource.h>
// 
  int setpriority(int which,int who, int prio);
// 
//����˵��  setpriority()���������ý��̡���������û��Ľ���ִ������Ȩ������which��������ֵ������who ����whichֵ�в�ͬ����
//which who ���������
//PRIO_PROCESS whoΪ����ʶ����
//PRIO_PGRP who Ϊ���̵���ʶ����
//PRIO_USER whoΪ�û�ʶ����
//����prio����-20 ��20 ֮�䡣�������ִ������Ȩ����ֵԽ�ʹ����нϸߵ����ȴ���ִ�л��Ƶ����������ȨĬ����0����ֻ�г����û���root�������ʹ�ֵ��
// 
//����ֵ  ִ�гɹ��򷵻�0������д���������ֵ��Ϊ-1������ԭ�����errno��
//ESRCH ����which��who �����д����Ҳ������ϵĽ���
//EINVAL ����whichֵ����
//EPERM Ȩ�޲������޷��������
//EACCES һ���û��޷���������Ȩ
// 
//�� 
//
// 
//
// 
//system��ִ��shell ���  
//��غ���  fork��execve��waitpid��popen
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  int system(const char * string);
// 
//����˵��  system()�����fork()�����ӽ��̣����ӽ���������/bin/sh-c string��ִ�в���string�ַ�������������������ִ������漴����ԭ���õĽ��̡��ڵ���system()�ڼ�SIGCHLD �źŻᱻ��ʱ���ã�SIGINT��SIGQUIT �ź���ᱻ���ԡ�
// 
//����ֵ  ���system()�ڵ���/bin/shʱʧ���򷵻�127������ʧ��ԭ�򷵻�-1��������stringΪ��ָ��(NULL)���򷵻ط���ֵ�����system()���óɹ������᷵��ִ��shell�����ķ���ֵ�����Ǵ˷���ֵҲ�п���Ϊsystem()����/bin/shʧ�������ص�127�����������ټ��errno ��ȷ��ִ�гɹ���
// 
//����˵��  �ڱ�д����SUID/SGIDȨ�޵ĳ���ʱ����ʹ��system()��system()��̳л���������ͨ�������������ܻ����ϵͳ��ȫ�����⡣
// 
//����  #include<stdlib.h>
//main()
//{
//system(��ls -al /etc/passwd /etc/shadow��);
//}
// 
//ִ��  -rw-r--r-- 1 root root 705 Sep 3 13 :52 /etc/passwd
//-r--------- 1 root root 572 Sep 2 15 :34 /etc/shadow
// 
//�� 
//
// 
//
// 
//wait���ȴ��ӽ����жϻ������  
//��غ���  waitpid��fork
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<sys/wait.h>
// 
  pid_t wait (int * status);
// 
//����˵��  wait()����ʱֹͣĿǰ���̵�ִ�У�ֱ�����ź��������ӽ��̽���������ڵ���wait()ʱ�ӽ����Ѿ���������wait()�����������ӽ��̽���״ֵ̬���ӽ��̵Ľ���״ֵ̬���ɲ���status ���أ����ӽ��̵Ľ���ʶ����Ҳ��һ�췵�ء�������������״ֵ̬����
// 
//����  status�������NULL���ӽ��̵Ľ���״ֵ̬��ο�waitpid()��
// 
//����ֵ  ���ִ�гɹ��򷵻��ӽ���ʶ����(PID)������д������򷵻�-1��ʧ��ԭ�����errno�С�
// 
//����˵��  
// 
//����  #include<stdlib.h>
//#include<unistd.h>
//#include<sys/types.h>
//#include<sys/wait.h>
//main()
//{
//pid_t pid;
//int status,i;
//if(fork()= =0){
//printf(��This is the child process .pid =%d\n��,getpid());
//exit(5);
//}else{
//sleep(1);
//printf(��This is the parent process ,wait for child...\n��;
//pid=wait(&status);
//i=WEXITSTATUS(status);
//printf(��child��s pid =%d .exit status=^d\n��,pid,i);
//}
//}
// 
//ִ��  This is the child process.pid=1501
//This is the parent process .wait for child...
//child��s pid =1501,exit status =5
// 
//�� 
//
// 
//
// 
//waitpid���ȴ��ӽ����жϻ������  
//��غ���  wait��fork
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<sys/wait.h>
// 
  pid_t waitpid(pid_t pid,int * status,int options);
// 
//����˵��  waitpid()����ʱֹͣĿǰ���̵�ִ�У�ֱ�����ź��������ӽ��̽���������ڵ���wait()ʱ�ӽ����Ѿ���������wait()�����������ӽ��̽���״ֵ̬���ӽ��̵Ľ���״ֵ̬���ɲ���status���أ����ӽ��̵Ľ���ʶ����Ҳ��һ�췵�ء�������������״ֵ̬�������status�������NULL������pidΪ���ȴ����ӽ���ʶ���룬������ֵ��������:
//pid<-1 �ȴ�������ʶ����Ϊpid����ֵ���κ��ӽ��̡�
//pid=-1 �ȴ��κ��ӽ��̣��൱��wait()��
//pid=0 �ȴ�������ʶ������Ŀǰ������ͬ���κ��ӽ��̡�
//pid>0 �ȴ��κ��ӽ���ʶ����Ϊpid���ӽ��̡�
//����option����Ϊ0 �������OR ���
//WNOHANG ���û���κ��Ѿ��������ӽ��������Ϸ��أ������Եȴ���
//WUNTRACED ����ӽ��̽�����ִͣ����������Ϸ��أ�������״̬��������ᡣ
//�ӽ��̵Ľ���״̬���غ����status�������м�������б�������
//WIFEXITED(status)����ӽ�������������Ϊ��0ֵ��
//WEXITSTATUS(status)ȡ���ӽ���exit()���صĽ������룬һ�������WIFEXITED ���ж��Ƿ�������������ʹ�ô˺ꡣ
//WIFSIGNALED(status)����ӽ�������Ϊ�źŶ�������˺�ֵΪ��
//WTERMSIG(status)ȡ���ӽ������źŶ���ֹ���źŴ��룬һ�������WIFSIGNALED ���жϺ��ʹ�ô˺ꡣ
//WIFSTOPPED(status)����ӽ��̴�����ִͣ�������˺�ֵΪ�档һ��ֻ��ʹ��WUNTRACED ʱ�Ż��д������
//WSTOPSIG(status)ȡ�������ӽ�����ͣ���źŴ��룬һ�������WIFSTOPPED ���жϺ��ʹ�ô˺ꡣ
// 
//����ֵ  ���ִ�гɹ��򷵻��ӽ���ʶ����(PID)������д������򷵻�-1��ʧ��ԭ�����errno�С�
// 
//����  �ο�wait()��
// 
//�� 
//
// 
//
// 
//fprintf����ʽ������������ļ���  
//��غ���  printf��fscanf��vfprintf
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int fprintf(FILE * stream, const char * format,.......);
// 
//����˵��  fprintf()����ݲ���format�ַ�����ת������ʽ�����ݣ�Ȼ�󽫽�����������streamָ�����ļ��У�ֱ�������ַ�������('\0')Ϊֹ��
// 
//����ֵ  ���ڲ���format�ַ����ĸ�ʽ��ο�printf()���ɹ��򷵻�ʵ��������ַ�����ʧ���򷵻�-1������ԭ�����errno�С�
// 
//����  #include<stdio.h>
//main()
//{
//int i = 150;
//int j = -100;
//double k = 3.14159;
//fprintf(stdout,��%d %f %x \n��,j,k,i);
//fprintf(stdout,��%2d %*d\n��,i,2,i);
//}
// 
//ִ��  -100 3.141590 96
//150 150
// 
//�� 
//
// 
//
// 
//fscanf����ʽ���ַ������룩  
//��غ���  scanf��sscanf
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int fscanf(FILE * stream ,const char *format,....);
// 
//����˵��  fscanf()���Բ���stream���ļ����ж�ȡ�ַ������ٸ��ݲ���format�ַ�����ת������ʽ�����ݡ���ʽת����ʽ��ο�scanf()��ת����Ľṹ���ڶ�Ӧ�Ĳ����ڡ�
// 
//����ֵ  �ɹ��򷵻ز�����Ŀ��ʧ���򷵻�-1������ԭ�����errno�С�
// 
//����˵��  
// 
//����  #include<stdio.h>
//main()
//{
//int i;
//unsigned int j;
//char s[5];
//fscanf(stdin,��%d %x %5[a-z] %*s %f��,&i,&j,s,s);
//printf(��%d %d %s \n��,i,j,s);
//}
// 
//ִ��  10 0x1b aaaaaaaaa bbbbbbbbbb /*�Ӽ�������*/
//10 27 aaaaa
// 
//�� 
//
// 
//
// 
//printf����ʽ��������ݣ�  
//��غ���  scanf��snprintf
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int printf(const char * format,.............);
// 
//����˵��  printf()����ݲ���format�ַ�����ת������ʽ�����ݣ�Ȼ�󽫽��д������׼����豸��ֱ�������ַ�������('\0')Ϊֹ������format�ַ����ɰ������������ַ�����
//1.һ���ı�������ֱ�������
//2.ASCII�����ַ�����\t��\n�ȡ�
//3.��ʽת���ַ���
//��ʽת��Ϊһ���ٷֱȷ���(��)�����ĸ�ʽ�ַ�����ɡ�һ����ԣ�ÿ������������󶼱�����һprintf()�Ĳ�����֮���Ӧ��ֻ�е�����ת���ַ�����ʱ��ֱ��������ַ���������������������ͱ����������Ӧ��ת���ַ�������ͬ��
//Printf()��ʽת����һ����ʽ����
//��(flags)(width)(.prec)type
//���������������Ĳ���Ϊѡ���Բ�����������type���Ǳ�Ҫ�ġ������Ƚ���type�ļ�����ʽ
//����
//��d �����Ĳ����ᱻת��һ�з��ŵ�ʮ��������
//��u �����Ĳ����ᱻת��һ�޷��ŵ�ʮ��������
//��o �����Ĳ����ᱻת��һ�޷��ŵİ˽�������
//��x �����Ĳ����ᱻת��һ�޷��ŵ�ʮ���������֣�����Сдabcdef��ʾ
//��X �����Ĳ����ᱻת��һ�޷��ŵ�ʮ���������֣����Դ�дABCDEF��ʾ��������
//��f double �͵Ĳ����ᱻת��ʮ�������֣���ȡ��С����������λ���������롣
//��e double�͵Ĳ�����ָ����ʽ��ӡ����һ�����ֻ���С����ǰ����λ������С����󣬶���ָ�����ֻ���Сд��e����ʾ��
//��E �룥e������ͬ��Ψһ������ָ�����ֽ��Դ�д��E ����ʾ��
//��g double �͵Ĳ������Զ�ѡ���ԣ�f ��e �ĸ�ʽ����ӡ�����׼�Ǹ�������ӡ����ֵ�������õ���Чλ����������
//��G �룥g ������ͬ��Ψһ��������ָ����̬��ӡʱ��ѡ��E ��ʽ��
//�ַ����ַ���
//��c �������Ĳ����ᱻת��unsigned char�ʹ�ӡ����
//��s ָ���ַ����Ĳ����ᱻ���������ֱ������NULL�ַ�Ϊֹ
//��p ����ǲ����ǡ�void *����ָ����ʹ��ʮ�����Ƹ�ʽ��ʾ��
//prec �м������
//1. ����������Сλ����
//2.�ڸ��������д���С��λ��
//3.�ڣ�g ��ʽ������Чλ�������ֵ��
//4.�ڣ�s��ʽ�����ַ�������󳤶ȡ�
//5.��Ϊ������������¸�����ֵΪ��󳤶ȡ�
//widthΪ��������С���ȣ�������������ֵ������*���ţ����ʾ����һ�����������������ȡ�
//flags �����м������
//#NAME?
//+ һ���ڴ�ӡ����ʱ��printf�������ӡһ�����ţ������򲻼��κθ��š�������ʹ���ڴ�ӡ����ǰ��һ�����ţ�+����
//# ������������ת���ַ��Ĳ�ͬ���в�ͬ���塣��������Ϊo ֮ǰ���磥#o��������ڴ�ӡ�˽�����ֵǰ��ӡһ��o��
//��������Ϊx ֮ǰ����#x������ڴ�ӡʮ��������ǰ��ӡ��0x��������̬Ϊe��E��f��g��G ֮ǰ���ǿ����ֵ��ӡС���㡣������Ϊg ��G֮ǰʱ��ͬʱ����С���㼰С��λ��ĩβ���㡣
//0 ����ָ������ʱ�������ֵĲ���������0��Ĭ���ǹرմ���꣬����һ����ӡ���հ��ַ���
// 
//����ֵ  �ɹ��򷵻�ʵ��������ַ�����ʧ���򷵻�-1������ԭ�����errno�С�
// 
//����  #include<stdio.h>
//main()
//{
//int i = 150;
//int j = -100;
//double k = 3.14159;
//printf(��%d %f %x\n��,j,k,i);
//printf(��%2d %*d\n��,i,2,i); /*����2 ������ʽ*�У�����%2dͬ����*/
//}
// 
//ִ��  -100 3.14159 96
//150 150
// 
//�� 
//
// 
//
// 
//sacnf����ʽ���ַ������룩  
//��غ���  fscanf��snprintf
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int scanf(const char * format,.......);
// 
//����˵��  scanf()�Ὣ��������ݸ��ݲ���format�ַ�����ת������ʽ�����ݡ�Scanf()��ʽת����һ����ʽ����
//��[*][size][l][h]type
//���������������Ĳ���Ϊѡ���Բ�����������type���Ǳ�Ҫ�ġ�
//* ����ö�Ӧ�Ĳ������ݺ��Բ����档
//size Ϊ���������������ݳ��ȡ�
//l �����������ֵ��long int ��double�ͱ��档
//h �����������ֵ��short int �ͱ��档
//���½���type�ļ�����ʽ
//��d ��������ݻᱻת��һ�з��ŵ�ʮ�������֣�int����
//��i ��������ݻᱻת��һ�з��ŵ�ʮ�������֣������������ԡ�0x����0X����ͷ����ת��ʮ���������֣����ԡ�0����ͷ��ת���˽������֣������������ʮ���ơ�
//��0 ��������ݻᱻת����һ�޷��ŵİ˽������֡�
//��u ��������ݻᱻת����һ�޷��ŵ���������
//��x ���������Ϊ�޷��ŵ�ʮ���������֣�ת�������unsigned int�ͱ�����
//��X ͬ��x
//��f ���������Ϊ�з��ŵĸ���������ת�������float�ͱ�����
//��e ͬ��f
//��E ͬ��f
//��g ͬ��f
//��s ��������Ϊ�Կո��ַ�Ϊ��ֹ���ַ�����
//��c ��������Ϊ��һ�ַ���
//[] ��ȡ���ݵ�ֻ���������ڵ��ַ�����[a-z]��
//[^] ��ȡ���ݵ������������ŵ�^���ź���ַ����֣���[^0-9].
// 
//����ֵ  �ɹ��򷵻ز�����Ŀ��ʧ���򷵻�-1������ԭ�����errno�С�
// 
//����  #include <stdio.h>
//main()
//{
//int i;
//unsigned int j;
//char s[5];
//scanf(��%d %x %5[a-z] %*s %f��,&i,&j,s,s);
//printf(��%d %d %s\n��,i,j,s);
//}
// 
//ִ��  10 0x1b aaaaaaaaaa bbbbbbbbbb
//10 27 aaaaa
// 
//�� 
//
// 
//
// 
//sprintf����ʽ���ַ������ƣ�  
//��غ���  printf��sprintf
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int sprintf( char *str,const char * format,.........);
// 
//����˵��  sprintf()����ݲ���format�ַ�����ת������ʽ�����ݣ�Ȼ�󽫽�����Ƶ�����str��ָ���ַ������飬ֱ�������ַ�������(��\0��)Ϊֹ�����ڲ���format�ַ����ĸ�ʽ��ο�printf()��
// 
//����ֵ  �ɹ��򷵻ز���str�ַ������ȣ�ʧ���򷵻�-1������ԭ�����errno�С�
// 
//����˵��  ʹ�ô˺����������ջ����������snprintf������
// 
//����  #include<stdio.h>
//main()
//{
//char * a=��This is string A!��;
//char buf[80];
//sprintf(buf,��>>> %s<<<\n��,a);
//printf(��%s��.buf);
//}
// 
//ִ��  >>>This is string A!<<<
// 
//�� 
//
// 
//
// 
//sscanf����ʽ���ַ������룩  
//��غ���  scanf��fscanf
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int sscanf (const char *str,const char * format,........);
// 
//����˵��  sscanf()�Ὣ����str���ַ������ݲ���format�ַ�����ת������ʽ�����ݡ���ʽת����ʽ��ο�scanf()��ת����Ľ�����ڶ�Ӧ�Ĳ����ڡ�
// 
//����ֵ  �ɹ��򷵻ز�����Ŀ��ʧ���򷵻�-1������ԭ�����errno�С�
// 
//����  #include<stdio.h>
//main()
//{
//int i;
//unsigned int j;
//char input[ ]=��10 0x1b aaaaaaaa bbbbbbbb��;
//char s[5];
//sscanf(input,��%d %x %5[a-z] %*s %f��,&i,&j,s,s);
//printf(��%d %d %s\n��,i,j,s);
//}
// 
//ִ��  10 27 aaaaa
// 
//�� 
//
// 
//
// 
//vfprintf����ʽ������������ļ���  
//��غ���  printf��fscanf��fprintf
// 
//��ͷ�ļ�  #include<stdio.h>
//#include<stdarg.h>
// 
  int vfprintf(FILE *stream,const char * format,va_list ap);
// 
//����˵��  vfprintf()����ݲ���format�ַ�����ת������ʽ�����ݣ�Ȼ�󽫽�����������streamָ�����ļ��У�ֱ�������ַ�������(��\0��)Ϊֹ�����ڲ���format�ַ����ĸ�ʽ��ο�printf()��va_list�÷���ο���¼C��vprintf()������
// 
//����ֵ  �ɹ��򷵻�ʵ��������ַ�����ʧ���򷵻�-1������ԭ�����errno�С�
// 
//����  �ο�fprintf()��vprintf()��
// 
//�� 
//
// 
//
// 
//vfscanf����ʽ���ַ������룩  
//��غ���  scanf��sscanf��fscanf
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int vfscanf(FILE * stream,const char * format ,va_list ap);
// 
//����˵��  vfscanf()���Բ���stream ���ļ����ж�ȡ�ַ������ٸ��ݲ���format�ַ�����ת������ʽ�����ݡ���ʽת����ʽ��ο�scanf()��ת����Ľ�����ڶ�Ӧ�Ĳ����ڡ�va_list�÷���ο���¼C ��vprintf()��
// 
//����ֵ  �ɹ��򷵻ز�����Ŀ��ʧ���򷵻�-1������ԭ�����errno�С�
// 
//����  �ο�fscanf()��vprintf()��
// 
//�� 
//
// 
//
// 
//vprintf����ʽ��������ݣ�  
//��غ���  printf��vfprintf��vsprintf
// 
//��ͷ�ļ�  #include<stdio.h>
//#include<stdarg.h>
// 
  int vprintf(const char * format,va_list ap);
// 
//����˵��  vprintf()���ú�printf()��ͬ������format��ʽҲ��ͬ��va_listΪ���������Ĳ����У��÷���������ο���¼C��
// 
//����ֵ  �ɹ��򷵻�ʵ��������ַ�����ʧ���򷵻�-1������ԭ�����errno�С�
// 
//����  #include<stdio.h>
//#include<stdarg.h>
//int my_printf( const char *format,����)
//{
//va_list ap;
//int retval;
//va_start(ap,format);
//printf(��my_printf( ):��);
//retval = vprintf(format,ap);
//va_end(ap);
//return retval;
//}
//main()
//{
//int i = 150,j = -100;
//double k = 3.14159;
//my_printf(��%d %f %x\n��,j,k,i);
//my_printf(��%2d %*d\n��,i,2,i);
//}
// 
//ִ��  my_printf() : -100 3.14159 96
//my_printf() : 150 150
// 
//�� 
//
// 
//
// 
//vscanf����ʽ���ַ������룩  
//��غ���  vsscanf��vfscanf
// 
//��ͷ�ļ�  #include<stdio.h>
//#include<stdarg.h>
// 
  int vscanf( const char * format,va_list ap);
// 
//����˵��  vscanf()�Ὣ��������ݸ��ݲ���format�ַ�����ת������ʽ�����ݡ���ʽת����ʽ��ο�scanf()��ת����Ľ�����ڶ�Ӧ�Ĳ����ڡ�va_list�÷���ο���¼C��vprintf()������
// 
//����ֵ  �ɹ��򷵻ز�����Ŀ��ʧ���򷵻�-1������ԭ�����errno�С�
// 
//����  ��ο�scanf()��vprintf()��
// 
//�� 
//
// 
//
// 
//vsprintf����ʽ���ַ������ƣ�  
//��غ���  vnsprintf��vprintf��snprintf
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int vsprintf( char * str,const char * format,va_list ap);
// 
//����˵��  vsprintf()����ݲ���format�ַ�����ת������ʽ�����ݣ�Ȼ�󽫽�����Ƶ�����str��ָ���ַ������飬ֱ�������ַ�������(��\0��)Ϊֹ�����ڲ���format�ַ����ĸ�ʽ��ο�printf()��va_list�÷���ο���¼C��vprintf()������
// 
//����ֵ  �ɹ��򷵻ز���str�ַ������ȣ�ʧ���򷵻�-1������ԭ�����errno�С�
// 
//����  ��ο�vprintf()��vsprintf()��
// 
//�� 
//
// 
//
// 
//vsscanf����ʽ���ַ������룩  
//��غ���  vscanf��vfscanf
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int vsscanf(const char * str,const char * format,va_list ap);
// 
//����˵��  vsscanf()�Ὣ����str���ַ������ݲ���format�ַ�����ת������ʽ�����ݡ���ʽת����ʽ��ο���¼C ��vprintf()������
// 
//����ֵ  �ɹ��򷵻ز�����Ŀ��ʧ���򷵻�-1������ԭ�����errno�С�
// 
//����  ��ο�sscanf()��vprintf()��
// 
//�� 
//
// 
// �ļ�Ȩ�޿���ƪ===========================================================
//�� 
//
// 
//
// 
//access���ж��Ƿ���д�ȡ�ļ���Ȩ�ޣ�  
//��غ���  stat��open��chmod��chown��setuid��setgid
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int access(const char * pathname,int mode);
// 
//����˵��  access()�����Ƿ���Զ�/дĳһ�Ѵ��ڵ��ļ�������mode�м��������ϣ�R_OK��W_OK��X_OK ��F_OK��R_OK��W_OK��X_OK��������ļ��Ƿ���ж�ȡ��д���ִ�е�Ȩ�ޡ�F_OK���������жϸ��ļ��Ƿ���ڡ�����access()ֻ��Ȩ�޵ĺ˲飬��������ļ���̬���ļ����ݣ���ˣ����һĿ¼��ʾΪ����д�롱����ʾ�����ڸ�Ŀ¼�н������ļ��Ȳ�����������ζ��Ŀ¼���Ա������ļ��������磬��ᷢ��DOS���ļ������С���ִ�С�Ȩ�ޣ�����execve()ִ��ʱ���ʧ�ܡ�
// 
//����ֵ  ����������˵�Ȩ�޶�ͨ���˼���򷵻�0ֵ����ʾ�ɹ���ֻҪ��һȨ�ޱ���ֹ�򷵻�-1��
// 
//�������  EACCESS ����pathname ��ָ�����ļ���������Ҫ����Ե�Ȩ�ޡ�
//EROFS ������д��Ȩ�޵��ļ�������ֻ���ļ�ϵͳ�ڡ�
//EFAULT ����pathnameָ�볬���ɴ�ȡ�ڴ�ռ䡣
//EINVAL ����mode ����ȷ��
//ENAMETOOLONG ����pathname̫����
//ENOTDIR ����pathnameΪһĿ¼��
//ENOMEM �����ڴ治��
//ELOOP ����pathname�й�������������⡣
//EIO I/O ��ȡ����
// 
//����˵��  ʹ��access()���û���֤������ж�Ҫ�ر�С�ģ�������access()������open()�Ŀ��ļ����ܻ����ϵͳ��ȫ�ϵ����⡣
// 
//����  /* �ж��Ƿ������ȡ/etc/passwd */
//#include<unistd.h>
//int main()
//{
//if (access(��/etc/passwd��,R_OK) = =0)
//printf(��/etc/passwd can be read\n��);
//}
// 
//ִ��  /etc/passwd can be read
// 
//�� 
//
// 
//
// 
//alphasort������ĸ˳������Ŀ¼�ṹ��  
//��غ���  scandir��qsort
// 
//��ͷ�ļ�  #include<dirent.h>
// 
  int alphasort(const struct dirent **a,const struct dirent **b);
// 
//����˵��  alphasort()Ϊscandir()������qsort()����ʱ����qsort()��Ϊ�жϵĺ�������ϸ˵����ο�scandir()��qsort()��
// 
//����ֵ  �ο�qsort()��
// 
//����  /* ��ȡ/Ŀ¼�����е�Ŀ¼�ṹ��������ĸ˳������*/
//main()
//{
//struct dirent **namelist;
//int i,total;
//total = scandir(��/��,&namelist ,0,alphasort);
//if(total <0)
//perror(��scandir��);
//else{
//for(i=0;i<total;i++)
//printf(��%s\n��,namelist[i]->d_name);
//printf(��total = %d\n��,total);
//}
//}
// 
//ִ��  ..
//.gnome
//.gnome_private
//ErrorLog
//Weblog
//bin
//boot
//dev
//dosc
//dosd
//etc
//home
//lib
//lost+found
//misc
//mnt
//opt
//proc
//root
//sbin
//tmp
//usr
//var
//total = 24
// 
//�� 
//
// 
//
// 
//chdir���ı䵱ǰ�Ĺ�����Ŀ¼��  
//��غ���  getcwd��chroot
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int chdir(const char * path);
// 
//����˵��  chdir()��������ǰ�Ĺ���Ŀ¼�ı���Բ���path��ָ��Ŀ¼��
// 
//����ֵ  ִ�гɹ��򷵻�0��ʧ�ܷ���-1��errnoΪ������롣
// 
//����  #include<unistd.h>
//main()
//{
//chdir(��/tmp��);
//printf(��current working directory: %s\n��,getcwd(NULL,NULL));
//}
// 
//ִ��  current working directory :/tmp
// 
//�� 
//
// 
//
// 
//chmod���ı��ļ���Ȩ�ޣ�  
//��غ���  fchmod��stat��open��chown
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<sys/stat.h>
// 
  int chmod(const char * path,mode_t mode);
// 
//����˵��  chmod()��������mode Ȩ�������Ĳ���path ָ���ļ���Ȩ�ޡ�
// 
//����  mode �������������
//S_ISUID 04000 �ļ��ģ�set user-id on execution��λ
//S_ISGID 02000 �ļ��ģ�set group-id on execution��λ
//S_ISVTX 01000 �ļ���stickyλ
//S_IRUSR��S_IREAD�� 00400 �ļ������߾߿ɶ�ȡȨ��
//S_IWUSR��S_IWRITE��00200 �ļ������߾߿�д��Ȩ��
//S_IXUSR��S_IEXEC�� 00100 �ļ������߾߿�ִ��Ȩ��
//S_IRGRP 00040 �û���߿ɶ�ȡȨ��
//S_IWGRP 00020 �û���߿�д��Ȩ��
//S_IXGRP 00010 �û���߿�ִ��Ȩ��
//S_IROTH 00004 �����û��߿ɶ�ȡȨ��
//S_IWOTH 00002 �����û��߿�д��Ȩ��
//S_IXOTH 00001 �����û��߿�ִ��Ȩ��
//ֻ�и��ļ��������߻���Ч�û�ʶ����Ϊ0���ſ����޸ĸ��ļ�Ȩ�ޡ�����ϵͳ��ȫ�������������д��һִ���ļ�������ִ���ļ�����S_ISUID ��S_ISGID Ȩ�ޣ���������λ�ᱻ��������һĿ¼����S_ISUID λȨ�ޣ���ʾ�ڴ�Ŀ¼��ֻ�и��ļ��������߻�root����ɾ�����ļ���
// 
//����ֵ  Ȩ�޸ı�ɹ�����0��ʧ�ܷ���-1������ԭ�����errno��
// 
//�������  EPERM ���̵���Ч�û�ʶ���������޸�Ȩ�޵��ļ�ӵ���߲�ͬ������Ҳ����rootȨ�ޡ�
//EACCESS ����path��ָ�����ļ��޷���ȡ��
//EROFS ��д��Ȩ�޵��ļ�������ֻ���ļ�ϵͳ�ڡ�
//EFAULT ����pathָ�볬���ɴ�ȡ�ڴ�ռ䡣
//EINVAL ����mode����ȷ
//ENAMETOOLONG ����path̫��
//ENOENT ָ�����ļ�������
//ENOTDIR ����path·������һĿ¼
//ENOMEM �����ڴ治��
//ELOOP ����path�й�������������⡣
//EIO I/O ��ȡ����
// 
//����  /* ��/etc/passwd �ļ�Ȩ�����S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH */
//#include<sys/types.h>
//#include<sys/stat.h>
//main()
//{
//chmod(��/etc/passwd��,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
//}
// 
//�� 
//
// 
//
// 
//chown���ı��ļ��������ߣ�  
//��غ���  fchown��lchown��chmod
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<unistd.h>
// 
  int chown(const char * path, uid_t owner,gid_t group);
// 
//����˵��  chown()�Ὣ����pathָ���ļ��������߱��Ϊ����owner������û����������ļ�������Ϊ����group�顣�������owner��groupΪ-1����Ӧ�������߻��鲻�������ı䡣root���ļ������߽Կɸı��ļ��飬�������߱����ǲ���group��ĳ�Ա����root��chown()�ı��ļ������߻���ʱ�����ļ�������S_ISUID��S_ISGIDȨ�ޣ���������Ȩ��λ�������������S_ISGIDȨ�޵�����S_IXGRPλ������ļ��ᱻǿ���������ļ�ģʽ�ᱣ����
// 
//����ֵ  �ɹ��򷵻�0��ʧ�ܷ���-1������ԭ�����errno��
// 
//�������  �ο�chmod������
// 
//����  /* ��/etc/passwd �������ߺ��鶼��Ϊroot */
//#include<sys/types.h>
//#include<unistd.h>
//main()
//{
//chown(��/etc/passwd��,0,0);
//}
// 
//�� 
//
// 
//
// 
//chroot���ı��Ŀ¼��  
//��غ���  chdir
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int chroot(const char * path);
// 
//����˵��  chroot()�����ı��Ŀ¼Ϊ����path ��ָ����Ŀ¼��ֻ�г����û�������ı��Ŀ¼���ӽ��̽��̳��µĸ�Ŀ¼��
// 
//����ֵ  ���óɹ��򷵻�0��ʧ����-1������������errno��
// 
//�������  EPERM Ȩ�޲��㣬�޷��ı��Ŀ¼��
//EFAULT ����pathָ�볬���ɴ�ȡ�ڴ�ռ䡣
//ENAMETOOLONG ����path̫����
//ENOTDIR ·���е�Ŀ¼���ڵ�ȴ��������Ŀ¼��
//EACCESS ��ȡĿ¼ʱ���ܾ�
//ENOMEM �����ڴ治�㡣
//ELOOP ����path�й�������������⡣
//EIO I/O ��ȡ����
// 
//����  /* ����Ŀ¼��Ϊ/tmp ,��������Ŀ¼�л���/tmp */
//#include<unistd.h>
//main()
//{
//chroot(��/tmp��);
//chdir(��/��);
//}
// 
//�� 
//
// 
//
// 
//closedir���ر�Ŀ¼��  
//��غ���  opendir
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<dirent.h>
// 
  int closedir(DIR *dir);
// 
//����˵��  closedir()�رղ���dir��ָ��Ŀ¼����
// 
//����ֵ  �رճɹ��򷵻�0��ʧ�ܷ���-1������ԭ�����errno �С�
// 
//�������  EBADF ����dirΪ��Ч��Ŀ¼��
// 
//����  �ο�readir()��
// 
//�� 
//
// 
//
// 
//fchdir���ı䵱ǰ�Ĺ���Ŀ¼��  
//��غ���  getcwd��chroot
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int fchdir(int fd);
// 
//����˵��  fchdir()��������ǰ�Ĺ���Ŀ¼�ı���Բ���fd ��ָ���ļ������ʡ�
// 
//����ִֵ  �гɹ��򷵻�0��ʧ�ܷ���-1��errnoΪ������롣
// 
//����˵��  
// 
//����  #include<sys/types.h>
//#include<sys/stat.h>
//#include<fcntl.h>
//#include<unistd.h>
//main()
//{
//int fd;
//fd = open(��/tmp��,O_RDONLY);
//fchdir(fd);
//printf(��current working directory : %s \n��,getcwd(NULL,NULL));
//close(fd);
//}
// 
//ִ��  current working directory : /tmp
// 
//�� 
//
// 
//
// 
//fchmod���ı��ļ���Ȩ�ޣ�  
//��غ���  chmod��stat��open��chown
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<sys/stat.h>
// 
  int fchmod(int fildes,mode_t mode);
// 
//����˵��  fchmod()��������modeȨ�������Ĳ���fildes��ָ�ļ���Ȩ�ޡ�����fildesΪ�Ѵ��ļ����ļ������ʡ�����mode��ο�chmod������
// 
//����ֵ  Ȩ�޸ı�ɹ��򷵻�0��ʧ�ܷ���-1������ԭ�����errno��
// 
//����ԭ��  EBADF ����fildesΪ��Ч���ļ������ʡ�
//EPERM ���̵���Ч�û�ʶ���������޸�Ȩ�޵��ļ������߲�ͬ������Ҳ����rootȨ�ޡ�
//EROFS ��д��Ȩ�޵��ļ�������ֻ���ļ�ϵͳ�ڡ�
//EIO I/O ��ȡ����
// 
//����  #include<sys/stat.h>
//#include<fcntl.h>
//main()
//{
//int fd;
//fd = open (��/etc/passwd��,O_RDONLY);
//fchmod(fd,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
//close(fd);
//}
// 
//�� 
//
// 
//
// 
//fchown���ı��ļ��������ߣ�  
//��غ���  chown��lchown��chmod
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<unistd.h>
// 
  int fchown(int fd,uid_t owner,gid_t group);
// 
//����˵��  fchown()�Ὣ����fdָ���ļ��������߱��Ϊ����owner������û����������ļ�������Ϊ����group�顣�������owner��groupΪ-1����ӳ�������߻��������ı䡣����fd Ϊ�Ѵ򿪵��ļ������ʡ���root��fchown()�ı��ļ������߻���ʱ�����ļ�����S_ISUID��S_ISGIDȨ�ޣ���������Ȩ��λ��
// 
//����ֵ  �ɹ��򷵻�0��ʧ���򷵻�-1������ԭ�����errno��
// 
//�������  EBADF ����fd�ļ�������Ϊ��Ч�Ļ���ļ��ѹرա�
//EPERM ���̵���Ч�û�ʶ���������޸�Ȩ�޵��ļ������߲�ͬ������Ҳ����rootȨ�ޣ����ǲ���owner��group����ȷ��
//EROFS ��д����ļ�������ֻ���ļ�ϵͳ�ڡ�
//ENOENT ָ�����ļ�������
//EIO I/O��ȡ����
// 
//����  #include<sys/types.h>
//#include<unistd.h>
//#include<fcntl.h>
//main()
//{
//int fd;
//fd = open (��/etc/passwd��,O_RDONLY);
//chown(fd,0,0);
//close(fd);
//}
// 
//�� 
//
// 
//
// 
//fstat�����ļ�������ȡ���ļ�״̬��  
//��غ���  stat��lstat��chmod��chown��readlink��utime
// 
//��ͷ�ļ�  #include<sys/stat.h>
//#include<unistd.h>
// 
  int fstat(int fildes,struct stat *buf);
// 
//����˵��  fstat()����������fildes��ָ���ļ�״̬�����Ƶ�����buf��ָ�Ľṹ��(struct stat)��Fstat()��stat()������ȫ��ͬ����ͬ�����ڴ���Ĳ���Ϊ�Ѵ򿪵��ļ������ʡ���ϸ������ο�stat()��
// 
//����ֵ  ִ�гɹ��򷵻�0��ʧ�ܷ���-1������������errno��
// 
//����  #include<sys/stat.h>
//#include<unistd.h>
//#include<fcntk.h>
//main()
//{
//struct stat buf;
//int fd;
//fd = open (��/etc/passwd��,O_RDONLY);
//fstat(fd,&buf);
//printf(��/etc/passwd file size +%d\n ��,buf.st_size);
//}
// 
//ִ��  /etc/passwd file size = 705
// 
//�� 
//
// 
//
// 
//ftruncate���ı��ļ���С��  
//��غ���  open��truncate
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int ftruncate(int fd,off_t length);
// 
//����˵��  ftruncate()�Ὣ����fdָ�����ļ���С��Ϊ����lengthָ���Ĵ�С������fdΪ�Ѵ򿪵��ļ������ʣ����ұ�������д��ģʽ�򿪵��ļ������ԭ�����ļ���С�Ȳ���length���򳬹��Ĳ��ֻᱻɾȥ��
// 
//����ֵ  ִ�гɹ��򷵻�0��ʧ�ܷ���-1������ԭ�����errno��
// 
//�������  EBADF ����fd�ļ�������Ϊ��Ч�Ļ���ļ��ѹرա�
//EINVAL ����fd Ϊһsocket �����ļ������Ǹ��ļ�������д��ģʽ�򿪡�
// 
//�� 
//
// 
//
// 
//getcwd��ȡ�õ�ǰ�Ĺ���Ŀ¼��  
//��غ���  get_current_dir_name��getwd��chdir
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  char * getcwd(char * buf,size_t size);
// 
//����˵��  getcwd()�Ὣ��ǰ�Ĺ���Ŀ¼����·�����Ƶ�����buf��ָ���ڴ�ռ䣬����sizeΪbuf�Ŀռ��С���ڵ��ô˺���ʱ��buf��ָ���ڴ�ռ�Ҫ�㹻��������Ŀ¼����·�����ַ������ȳ�������size��С�����ֵNULL��errno��ֵ��ΪERANGE����������bufΪNULL��getcwd()��������size�Ĵ�С�Զ������ڴ�(ʹ��malloc())���������sizeҲΪ0����getcwd()��������Ŀ¼����·�����ַ����̶������������õ��ڴ��С�����̿�����ʹ������ַ���������free()���ͷŴ˿ռ䡣
// 
//����ֵ  ִ�гɹ��򽫽�����Ƶ�����buf��ָ���ڴ�ռ䣬���Ƿ����Զ����õ��ַ���ָ�롣ʧ�ܷ���NULL������������errno��
// 
//����  #include<unistd.h>
//main()
//{
//char buf[80];
//getcwd(buf,sizeof(buf));
//printf(��current working directory : %s\n��,buf);
//}
// 
//ִ��  current working directory :/tmp
// 
//�� 
//
// 
//
// 
//link�������ļ����ӣ�  
//��غ���  symlink��unlink
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int link (const char * oldpath,const char * newpath);
// 
//����˵��  link()�Բ���newpathָ��������������һ���µ�����(Ӳ����)������oldpath��ָ�����Ѵ����ļ����������newpathָ��������Ϊһ�Ѵ��ڵ��ļ��򲻻Ὠ�����ӡ�
// 
//����ֵ  �ɹ��򷵻�0��ʧ�ܷ���-1������ԭ�����errno��
// 
//����˵��  link()��������Ӳ�����޷���Խ��ͬ�ļ�ϵͳ�������Ҫ�����symlink()��
// 
//�������  EXDEV ����oldpath��newpath���ǽ�����ͬһ�ļ�ϵͳ��
//EPERM ����oldpath��newpath��ָ���ļ�ϵͳ��֧��Ӳ����
//EROFS �ļ�������ֻ���ļ�ϵͳ��
//EFAULT ����oldpath��newpath ָ�볬���ɴ�ȡ�ڴ�ռ䡣
//ENAMETOLLONG ����oldpath��newpath̫��
//ENOMEM �����ڴ治��
//EEXIST ����newpath��ָ���ļ����Ѵ��ڡ�
//EMLINK ����oldpath��ָ���ļ��Ѵ����������Ŀ��
//ELOOP ����pathname�й��������������
//ENOSPC �ļ�ϵͳ��ʣ��ռ䲻�㡣
//EIO I/O ��ȡ����
// 
//����  /* ����/etc/passwd ��Ӳ����Ϊpass */
//#include<unistd.h>
//main()
//{
//link(��/etc/passwd��,��pass��);
//}
// 
//�� 
//
// 
//
// 
//lstat�����ļ�������ȡ���ļ�״̬��  
//��غ���  stat��fstat��chmod��chown��readlink��utime
// 
//��ͷ�ļ�  #include<sys/stat.h>
//#include<unistd.h>
// 
  int lstat (const char * file_name.struct stat * buf);
// 
//����˵��  lstat()��stat()������ȫ��ͬ������ȡ�ò���file_name��ָ���ļ�״̬���������ڣ����ļ�Ϊ��������ʱ��lstat()�᷵�ظ�link�����״̬����ϸ������ο�stat()��
// 
//����ֵ  ִ�гɹ��򷵻�0��ʧ�ܷ���-1������������errno��
// 
//����  �ο�stat()��
// 
//�� 
//
// 
//
// 
//opendir����Ŀ¼��  
//��غ���  open��readdir��closedir��rewinddir��seekdir��telldir��scandir
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<dirent.h>
// 
  DIR * opendir(const char * name);
// 
//����˵��  opendir()�����򿪲���nameָ����Ŀ¼��������DIR*��̬��Ŀ¼������open()���ƣ���������Ŀ¼�Ķ�ȡ��������Ҫʹ�ô˷���ֵ��
// 
//����ֵ  �ɹ��򷵻�DIR* ��̬��Ŀ¼������ʧ���򷵻�NULL��
// 
//�������  EACCESS Ȩ�޲���
//EMFILE �Ѵﵽ���̿�ͬʱ�򿪵��ļ������ޡ�
//ENFILE �Ѵﵽϵͳ��ͬʱ�򿪵��ļ������ޡ�
//ENOTDIR ����name��������Ŀ¼
//ENOENT ����name ָ����Ŀ¼�����ڣ����ǲ���name Ϊһ���ַ�����
//ENOMEM �����ڴ治�㡣
// 
//�� 
//
// 
//
// 
//readdir����ȡĿ¼��  
//��غ���  open��opendir��closedir��rewinddir��seekdir��telldir��scandir
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<dirent.h>
// 
  struct dirent * readdir(DIR * dir);
// 
//����˵��  readdir()���ز���dirĿ¼�����¸�Ŀ¼����㡣
//�ṹdirent��������
//struct dirent
//{
//ino_t d_ino;
//ff_t d_off;
//signed short int d_reclen;
//unsigned char d_type;
//har d_name[256;
//};
//d_ino ��Ŀ¼������inode
//d_off Ŀ¼�ļ���ͷ����Ŀ¼������λ��
//d_reclen _name�ĳ��ȣ�������NULL�ַ�
//d_type d_name ��ָ���ļ�����
//d_name �ļ���
// 
//����ֵ  �ɹ��򷵻��¸�Ŀ¼����㡣�д��������ȡ��Ŀ¼�ļ�β�򷵻�NULL��
// 
//����˵��  EBADF����dirΪ��Ч��Ŀ¼����
// 
//����  #include<sys/types.h>
//#include<dirent.h>
//#include<unistd.h>
//main()
//{
//DIR * dir;
//struct dirent * ptr;
//int i;
//dir =opendir(��/etc/rc.d��);
//while((ptr = readdir(dir))!=NULL)
//{
//printf(��d_name: %s\n��,ptr->d_name);
//}
//closedir(dir);
//}
// 
//ִ��  d_name:.
//d_name:..
//d_name:init.d
//d_name:rc0.d
//d_name:rc1.d
//d_name:rc2.d
//d_name:rc3.d
//d_name:rc4.d
//d_name:rc5.d
//d_name:rc6.d
//d_name:rc
//d_name:rc.local
//d_name:rc.sysinit
// 
//�� 
//
// 
//
// 
//readlink��ȡ�÷���������ָ���ļ���  
//��غ���  stat��lstat��symlink
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int readlink(const char * path ,char * buf,size_t bufsiz);
// 
//����˵��  readlink()�Ὣ����path�ķ����������ݴ浽����buf��ָ���ڴ�ռ䣬���ص����ݲ�����NULL���ַ�����β�����Ὣ�ַ������ַ������ء�������bufsizС�ڷ������ӵ����ݳ��ȣ����������ݻᱻ�ضϡ�
// 
//����ֵ  ִ�гɹ��򴫷���������ָ���ļ�·���ַ�����ʧ���򷵻�-1������������errno��
// 
//�������  EACCESS ȡ�ļ�ʱ���ܾ���Ȩ�޲���
//EINVAL ����bufsiz Ϊ����
//EIO I/O ��ȡ����
//ELOOP ���򿪵��ļ��й�������������⡣
//ENAMETOOLONG ����path��·������̫��
//ENOENT ����path��ָ�����ļ�������
//ENOMEM �����ڴ治��
//ENOTDIR ����path·���е�Ŀ¼���ڵ�ȴ��������Ŀ¼��
// 
//�� 
//
// 
//
// 
//remove��ɾ���ļ���  
//��غ���  link��rename��unlink
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int remove(const char * pathname);
// 
//����˵��  remove()��ɾ������pathnameָ�����ļ����������pathnameΪһ�ļ��������unlink()����������pathnameΪһĿ¼�������rmdir()��������ο�unlink()��rmdir()��
// 
//����ֵ  �ɹ��򷵻�0��ʧ���򷵻�-1������ԭ�����errno��
// 
//�������  EROFS ��д����ļ�������ֻ���ļ�ϵͳ��
//EFAULT ����pathnameָ�볬���ɴ�ȡ�ڴ�ռ�
//ENAMETOOLONG ����pathname̫��
//ENOMEM �����ڴ治��
//ELOOP ����pathname�й��������������
//EIO I/O ��ȡ����
// 
//�� 
//
// 
//
// 
//rename�������ļ����ƻ�λ�ã�  
//��غ���  link��unlink��symlink
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int rename(const char * oldpath,const char * newpath);
// 
//����˵��  rename()�Ὣ����oldpath ��ָ�����ļ����Ƹ�Ϊ����newpath��ָ���ļ����ơ���newpath��ָ�����ļ��Ѵ��ڣ���ᱻɾ����
// 
//����ֵ  ִ�гɹ��򷵻�0��ʧ�ܷ���-1������ԭ�����errno
// 
//����  /* ���һ��DOS�µ�renameָ��rename ���ļ������ļ���*/
//#include <stdio.h>
//void main(int argc,char **argv)
//{
//if(argc<3){
//printf(��Usage: %s old_name new_name\n��,argv[0]);
//return;
//}
//printf(��%s=>%s��,argc[1],argv[2]);
//if(rename(argv[1],argv[2]<0)
//printf(��error!\n��);
//else
//printf(��ok!\n��);
//}
// 
//�� 
//
// 
//
// 
//rewinddir�������ȡĿ¼��λ��Ϊ��ͷλ�ã�  
//��غ���  open��opendir��closedir��telldir��seekdir��readdir��scandir
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<dirent.h>
// 
  void rewinddir(DIR *dir);
// 
//����˵��  rewinddir()�������ò���dir Ŀ¼��Ŀǰ�Ķ�ȡλ��Ϊԭ����ͷ�Ķ�ȡλ�á�
// 
//����ֵ  
// 
//�������  EBADF dirΪ��Ч��Ŀ¼��
// 
//����  #include<sys/types.h>
//#include<dirent.h>
//#include<unistd.h>
//main()
//{
//DIR * dir;
//struct dirent *ptr;
//dir = opendir(��/etc/rc.d��);
//while((ptr = readdir(dir))!=NULL)
//{
//printf(��d_name :%s\n��,ptr->d_name);
//}
//rewinddir(dir);
//printf(��readdir again!\n��);
//while((ptr = readdir(dir))!=NULL)
//{
//printf(��d_name: %s\n��,ptr->d_name);
//}
//closedir(dir);
//}
// 
//ִ��  d_name:.
//d_name:..
//d_name:init.d
//d_name:rc0.d
//d_name:rc1.d
//d_name:rc2.d
//d_name:rc3.d
//d_name:rc4.d
//d_name:rc5.d
//d_name:rc6.d
//d_name:rc
//d_name:rc.local
//d_name:rc.sysinit
//readdir again!
//d_name:.
//d_name:..
//d_name:init.d
//d_name:rc0.d
//d_name:rc1.d
//d_name:rc2.d
//d_name:rc3.d
//d_name:rc4.d
//d_name:rc5.d
//d_name:rc6.d
//d_name:rc
//d_name:rc.local
//d_name:rc.sysinit
// 
//�� 
//
// 
//
// 
//seekdir�������»ض�ȡĿ¼��λ�ã�  
//��غ���  open��opendir��closedir��rewinddir��telldir��readdir��scandir
// 
//��ͷ�ļ�  #include<dirent.h>
// 
  void seekdir(DIR * dir,off_t offset);
// 
//����˵��  seekdir()�������ò���dirĿ¼��Ŀǰ�Ķ�ȡλ�ã��ڵ���readdir()ʱ��Ӵ���λ�ÿ�ʼ��ȡ������offset �������Ŀ¼�ļ���ͷ��ƫ������
// 
//����ֵ  
// 
//�������  EBADF ����dirΪ��Ч��Ŀ¼��
// 
//����  #include<sys/types.h>
//#include<dirent.h>
//#include<unistd.h>
//main()
//{
//DIR * dir;
//struct dirent * ptr;
//int offset,offset_5,i=0;
//dir=opendir(��/etc/rc.d��);
//while((ptr = readdir(dir))!=NULL)
//{
//offset = telldir(dir);
//if(++i = =5) offset_5 =offset;
//printf(��d_name :%s offset :%d \n��,ptr->d_name,offset);
//}
//seekdir(dir offset_5);
//printf(��Readdir again!\n��);
//while((ptr = readdir(dir))!=NULL)
//{
//offset = telldir(dir);
//printf(��d_name :%s offset :%d\n��,ptr->d_name.offset);
//}
//closedir(dir);
//}
// 
//ִ��  d_name : . offset :12
//d_name : .. offset:24
//d_name : init.d offset 40
//d_name : rc0.d offset :56
//d_name :rc1.d offset :72
//d_name:rc2.d offset :88
//d_name:rc3.d offset 104
//d_name:rc4.d offset:120
//d_name:rc5.d offset:136
//d_name:rc6.d offset:152
//d_name:rc offset 164
//d_name:rc.local offset :180
//d_name:rc.sysinit offset :4096
//readdir again!
//d_name:rc2.d offset :88
//d_name:rc3.d offset 104
//d_name:rc4.d offset:120
//d_name:rc5.d offset:136
//d_name:rc6.d offset:152
//d_name:rc offset 164
//d_name:rc.local offset :180
//d_name:rc.sysinit offset :4096
// 
//�� 
//
// 
//
// 
//stat��ȡ���ļ�״̬��  
//��غ���  fstat��lstat��chmod��chown��readlink��utime
// 
//��ͷ�ļ�  #include<sys/stat.h>
//#include<unistd.h>
// 
  int stat(const char * file_name,struct stat *buf);
// 
//����˵��  stat()����������file_name��ָ���ļ�״̬�����Ƶ�����buf��ָ�Ľṹ�С�
//������struct stat�ڸ�������˵��
//struct stat
//{
//dev_t st_dev; /*device*/
//ino_t st_ino; /*inode*/
//mode_t st_mode; /*protection*/
//nlink_t st_nlink; /*number of hard links */
//uid_t st_uid; /*user ID of owner*/
//gid_t st_gid; /*group ID of owner*/
//dev_t st_rdev; /*device type */
//off_t st_size; /*total size, in bytes*/
//unsigned long st_blksize; /*blocksize for filesystem I/O */
//unsigned long st_blocks; /*number of blocks allocated*/
//time_t st_atime; /* time of lastaccess*/
//time_t st_mtime; /* time of last modification */
//time_t st_ctime; /* time of last change */
//};
//st_dev �ļ����豸���
//st_ino �ļ���i-node
//st_mode �ļ������ͺʹ�ȡ��Ȩ��
//st_nlink �������ļ���Ӳ������Ŀ���ս������ļ�ֵΪ1��
//st_uid �ļ������ߵ��û�ʶ����
//st_gid �ļ������ߵ���ʶ����
//st_rdev �����ļ�Ϊװ���豸�ļ�����Ϊ���豸���
//st_size �ļ���С�����ֽڼ���
//st_blksize �ļ�ϵͳ��I/O ��������С��
//st_blcoks ռ���ļ�����ĸ�����ÿһ�����СΪ512 ���ֽڡ�
//st_atime �ļ����һ�α���ȡ��ִ�е�ʱ�䣬һ��ֻ������mknod��utime��read��write��tructateʱ�ı䡣
//st_mtime �ļ����һ�α��޸ĵ�ʱ�䣬һ��ֻ������mknod��utime��writeʱ�Ż�ı�
//st_ctime i-node���һ�α����ĵ�ʱ�䣬�˲��������ļ������ߡ��顢Ȩ�ޱ�����ʱ������ǰ��������st_mode �����������������
//S_IFMT 0170000 �ļ����͵�λ����
//S_IFSOCK 0140000 scoket
//S_IFLNK 0120000 ��������
//S_IFREG 0100000 һ���ļ�
//S_IFBLK 0060000 ����װ��
//S_IFDIR 0040000 Ŀ¼
//S_IFCHR 0020000 �ַ�װ��
//S_IFIFO 0010000 �Ƚ��ȳ�
//S_ISUID 04000 �ļ��ģ�set user-id on execution��λ
//S_ISGID 02000 �ļ��ģ�set group-id on execution��λ
//S_ISVTX 01000 �ļ���stickyλ
//S_IRUSR��S_IREAD�� 00400 �ļ������߾߿ɶ�ȡȨ��
//S_IWUSR��S_IWRITE��00200 �ļ������߾߿�д��Ȩ��
//S_IXUSR��S_IEXEC�� 00100 �ļ������߾߿�ִ��Ȩ��
//S_IRGRP 00040 �û���߿ɶ�ȡȨ��
//S_IWGRP 00020 �û���߿�д��Ȩ��
//S_IXGRP 00010 �û���߿�ִ��Ȩ��
//S_IROTH 00004 �����û��߿ɶ�ȡȨ��
//S_IWOTH 00002 �����û��߿�д��Ȩ��
//S_IXOTH 00001 �����û��߿�ִ��Ȩ��
//�������ļ�������POSIX �ж����˼����Щ���͵ĺ궨��
//S_ISLNK ��st_mode�� �ж��Ƿ�Ϊ��������
//S_ISREG ��st_mode�� �Ƿ�Ϊһ���ļ�
//S_ISDIR ��st_mode���Ƿ�ΪĿ¼
//S_ISCHR ��st_mode���Ƿ�Ϊ�ַ�װ���ļ�
//S_ISBLK ��s3e�� �Ƿ�Ϊ�Ƚ��ȳ�
//S_ISSOCK ��st_mode�� �Ƿ�Ϊsocket
//��һĿ¼����sticky λ��S_ISVTX�������ʾ�ڴ�Ŀ¼�µ��ļ�ֻ�ܱ����ļ������ߡ���Ŀ¼�����߻�root��ɾ���������
// 
//����ֵ  ִ�гɹ��򷵻�0��ʧ�ܷ���-1������������errno
// 
//�������  ENOENT ����file_nameָ�����ļ�������
//ENOTDIR ·���е�Ŀ¼���ڵ�ȴ��������Ŀ¼
//ELOOP ���򿪵��ļ��й�������������⣬����Ϊ16��������
//EFAULT ����bufΪ��Чָ�룬ָ���޷����ڵ��ڴ�ռ�
//EACCESS ��ȡ�ļ�ʱ���ܾ�
//ENOMEM �����ڴ治��
//ENAMETOOLONG ����file_name��·������̫��
// 
//����  #include<sys/stat.h>
//#include<unistd.h>
//mian()
//{
//struct stat buf;
//stat (��/etc/passwd��,&buf);
//printf(��/etc/passwd file size = %d \n��,buf.st_size);
//}
// 
//ִ��  /etc/passwd file size = 705
// 
//�� 
//
// 
//
// 
//symlink�������ļ��������ӣ�  
//��غ���  link��unlink
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int symlink( const char * oldpath,const char * newpath);
// 
//����˵��  symlink()�Բ���newpathָ��������������һ���µ�����(��������)������oldpath��ָ�����Ѵ����ļ�������oldpathָ�����ļ���һ��Ҫ���ڣ��������newpathָ��������Ϊһ�Ѵ��ڵ��ļ��򲻻Ὠ�����ӡ�
// 
//����ֵ  �ɹ��򷵻�0��ʧ�ܷ���-1������ԭ�����errno��
// 
//�������  EPERM ����oldpath��newpath��ָ���ļ�ϵͳ��֧�ַ�������
//EROFS ������д��Ȩ�޵��ļ�������ֻ���ļ�ϵͳ��
//EFAULT ����oldpath��newpathָ�볬���ɴ�ȡ�ڴ�ռ䡣
//ENAMETOOLONG ����oldpath��newpath̫��
//ENOMEM �����ڴ治��
//EEXIST ����newpath��ָ���ļ����Ѵ��ڡ�
//EMLINK ����oldpath��ָ���ļ��Ѵﵽ���������Ŀ
//ELOOP ����pathname�й��������������
//ENOSPC �ļ�ϵͳ��ʣ��ռ䲻��
//EIO I/O ��ȡ����
// 
//����  #include<unistd.h>
//main()
//{
//symlink(��/etc/passwd��,��pass��);
//}
// 
//�� 
//
// 
//
// 
//telldir��ȡ��Ŀ¼���Ķ�ȡλ�ã�  
//��غ���  open��opendir��closedir��rewinddir��seekdir��readdir��scandir
// 
//��ͷ�ļ�  #include<dirent.h>
// 
  off_t telldir(DIR *dir);
// 
//����˵��  telldir()���ز���dirĿ¼��Ŀǰ�Ķ�ȡλ�á��˷���ֵ�������Ŀ¼�ļ���ͷ��ƫ��������ֵ�����¸���ȡλ�ã��д�����ʱ����-1��
// 
//�������  EBADF����dirΪ��Ч��Ŀ¼����
// 
//����  #include<sys/types.h>
//#include<dirent.h>
//#include<unistd.h>
//main()
//{
//DIR *dir;
//struct dirent *ptr;
//int offset;
//dir = opendir(��/etc/rc.d��);
//while((ptr = readdir(dir))!=NULL)
//{
//offset = telldir (dir);
//printf(��d_name : %s offset :%d\n��, ptr->d_name,offset);
//}
//closedir(dir);
//}
// 
//ִ��  d_name : . offset :12
//d_name : .. offset:24
//d_name : init.d offset 40
//d_name : rc0.d offset :56
//d_name :rc1.d offset :72
//d_name:rc2.d offset :88
//d_name:rc3.d offset 104
//d_name:rc4.d offset:120
//d_name:rc5.d offset:136
//d_name:rc6.d offset:152
//d_name:rc offset 164
//d_name:rc.local offset :180
//d_name:rc.sysinit offset :4096
// 
//�� 
//
// 
//
// 
//truncate���ı��ļ���С��  
//��غ���  open��ftruncate
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int truncate(const char * path,off_t length);
// 
//����˵��  truncate()�Ὣ����path ָ�����ļ���С��Ϊ����length ָ���Ĵ�С�����ԭ�����ļ���С�Ȳ���length���򳬹��Ĳ��ֻᱻɾȥ��
// 
//����ֵ  ִ�гɹ��򷵻�0��ʧ�ܷ���-1������ԭ�����errno��
// 
//�������  EACCESS ����path��ָ�����ļ��޷���ȡ��
//EROFS ��д����ļ�������ֻ���ļ�ϵͳ��
//EFAULT ����pathָ�볬���ɴ�ȡ�ڴ�ռ�
//EINVAL ����path�������Ϸ��ַ�
//ENAMETOOLONG ����path̫��
//ENOTDIR ����path·������һĿ¼
//EISDIR ����path ָ��һĿ¼
//ETXTBUSY ����path��ָ���ļ�Ϊ������򣬶�������ִ����
//ELOOP ����path���й��������������
//EIO I/O ��ȡ����
// 
//�� 
//
// 
//
// 
//umask�����ý������ļ�ʱ��Ȩ�����֣�  
//��غ���  creat��open
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<sys/stat.h>
// 
  mode_t umask(mode_t mask);
// 
//����˵��  umask()�Ὣϵͳumaskֵ��ɲ���mask&0777���ֵ��Ȼ����ǰ��umaskֵ���ء���ʹ��open()�������ļ�ʱ���ò���mode�������������ļ���Ȩ�ޣ�����(mode&~umask)��Ȩ��ֵ�����磬�ڽ����ļ�ʱָ���ļ�Ȩ��Ϊ0666��ͨ��umaskֵĬ��Ϊ022������ļ�������Ȩ����Ϊ0666&��022��0644��Ҳ����rw-r--r--����ֵ�˵��ò����д���ֵ���ء�����ֵΪԭ��ϵͳ��umaskֵ��
// 
//�� 
//
// 
//
// 
//unlink��ɾ���ļ���  
//��غ���  link��rename��remove
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int unlink(const char * pathname);
// 
//����˵��  unlink()��ɾ������pathnameָ�����ļ���������ļ���Ϊ������ӵ㣬�����������̴��˴��ļ����������й��ڴ��ļ����ļ������ʽԹرպ�Ż�ɾ�����������pathnameΪһ�������ӣ�������ӻᱻɾ����
// 
//����ֵ  �ɹ��򷵻�0��ʧ�ܷ���-1������ԭ�����errno
// 
//�������  EROFS �ļ�������ֻ���ļ�ϵͳ��
//EFAULT ����pathnameָ�볬���ɴ�ȡ�ڴ�ռ�
//ENAMETOOLONG ����pathname̫��
//ENOMEM �����ڴ治��
//ELOOP ����pathname �й��������������
//EIO I/O ��ȡ����
// 
//�� 
//
// 
//
// 
//utime���޸��ļ��Ĵ�ȡʱ��͸���ʱ�䣩  
//��غ���  utimes��stat
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<utime.h>
// 
  int utime(const char * filename,struct utimbuf * buf);
// 
//����˵��  utime()�����޸Ĳ���filename�ļ�������inode��ȡʱ�䡣
//�ṹutimbuf��������
//struct utimbuf{
//time_t actime;
//time_t modtime;
//};
// 
//����ֵ  �������bufΪ��ָ��(NULL)������ļ��Ĵ�ȡʱ��͸���ʱ��ȫ������ΪĿǰʱ�䡣
//ִ�гɹ��򷵻�0��ʧ�ܷ���-1������������errno��
// 
//�������  EACCESS ��ȡ�ļ�ʱ���ܾ���Ȩ�޲���
//ENOENT ָ�����ļ������ڡ�
// 
//�� 
//
// 
//
// 
//utimes���޸��ļ��Ĵ�ȡʱ��͸���ʱ�䣩  
//��غ���  utime��stat
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<utime.h>
// 
  int utimes(char * filename.struct timeval *tvp);
// 
//����˵��  utimes()�����޸Ĳ���filename�ļ�������inode��ȡʱ����޸�ʱ�䡣
//�ṹtimeval��������
//struct timeval {
//long tv_sec;
//long tv_usec; /* ΢��*/
//};
// 
//����ֵ  ����tvp ָ������timeval �ṹ�ռ䣬��utime����ʹ�õ�utimebuf�ṹ�Ƚϣ�tvp[0].tc_sec ��Ϊutimbuf.actime��tvp]1].tv_sec Ϊutimbuf.modtime��
//ִ�гɹ��򷵻�0��ʧ�ܷ���-1������������errno��
// 
//�������  EACCESS ��ȡ�ļ�ʱ���ܾ���Ȩ�޲���
//ENOENT ָ�����ļ�������
// 
//�� 
//
//�źŴ���ƪ====================================================================
//�� 
//
// 
//
// 
//alarm�������źŴ������ӣ�  
//��غ���  signal��sleep
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  unsigned int alarm(unsigned int seconds);
// 
//����˵��  alarm()���������ź�SIGALRM�ھ�������secondsָ�����������͸�Ŀǰ�Ľ��̡��������seconds Ϊ0����֮ǰ���õ����ӻᱻȡ��������ʣ�µ�ʱ�䷵�ء�
// 
//����ֵ  ����֮ǰ���ӵ�ʣ�����������֮ǰδ�������򷵻�0��
// 
//����  #include<unistd.h>
//#include<signal.h>
//void handler() {
//printf(��hello\n��);
//}
//main()
//{
//int i;
//signal(SIGALRM,handler);
//alarm(5);
//for(i=1;i<7;i++){
//printf(��sleep %d ...\n��,i);
//sleep(1);
//}
//}
// 
//ִ��  sleep 1 ...
//sleep 2 ...
//sleep 3 ...
//sleep 4 ...
//sleep 5 ...
//hello
//sleep 6 ...
// 
//�� 
//
// 
//
// 
//kill�������źŸ�ָ���Ľ��̣�  
//��غ���  raise��signal
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<signal.h>
// 
  int kill(pid_t pid,int sig);
// 
//����˵��  kill()���������Ͳ���sigָ�����źŸ�����pidָ���Ľ��̡�����pid�м������:
//pid>0 ���źŴ�������ʶ����Ϊpid �Ľ��̡�
//pid=0 ���źŴ�����Ŀǰ������ͬ����������н���
//pid=-1 ���źŹ㲥���͸�ϵͳ�����еĽ���
//pid<0 ���źŴ���������ʶ����Ϊpid����ֵ�����н���
//����sig������źű�ſɲο���¼D
// 
//����ֵ  ִ�гɹ��򷵻�0������д����򷵻�-1��
// 
//�������  EINVAL ����sig ���Ϸ�
//ESRCH ����pid ��ָ���Ľ��̻�����鲻����
//EPERM Ȩ�޲����޷������źŸ�ָ������
// 
//����  #include<unistd.h>
//#include<signal.h>
//#include<sys/types.h>
//#include<sys/wait.h>
//main()
//{
//pid_t pid;
//int status;
//if(!(pid= fork())){
//printf(��Hi I am child process!\n��);
//sleep(10);
//return;
//}
//else{
//printf(��send signal to child process (%d) \n��,pid);
//sleep(1);
//kill(pid ,SIGABRT);
//wait(&status);
//if(WIFSIGNALED(status))
//printf(��chile process receive signal %d\n��,WTERMSIG(status));
//}
//}
// 
//ִ��  sen signal to child process(3170)
//Hi I am child process!
//child process receive signal 6
// 
//�� 
//
// 
//
// 
//pause���ý�����ֱͣ���źų��֣�  
//��غ���  kill��signal��sleep
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int pause(void);
// 
//����˵��  pause()����Ŀǰ�Ľ�����ͣ������˯��״̬����ֱ�����ź�(signal)���жϡ�
// 
//����ֵ  ֻ����-1��
// 
//�������  EINTR ���źŵ����ж��˴˺�����
// 
//�� 
//
// 
//
// 
//sigaction����ѯ�������źŴ���ʽ��  
//��غ���  signal��sigprocmask��sigpending��sigsuspend
// 
//��ͷ�ļ�  #include<signal.h>
// 
  int sigaction(int signum,const struct sigaction *act ,struct sigaction *oldact);
// 
//����˵��  sigaction()��������signumָ�����źű�������ø��źŵĴ�����������signum����ָ��SIGKILL��SIGSTOP����������źš�
//������ṹsigaction��������
//struct sigaction
//{
//void (*sa_handler) (int);
//sigset_t sa_mask;
//int sa_flags;
//void (*sa_restorer) (void);
//}
//sa_handler�˲�����signal()�Ĳ���handler��ͬ�������µ��źŴ�����������������ο�signal()��
//sa_mask ���������ڴ�����ź�ʱ��ʱ��sa_mask ָ�����źŸ��á�
//sa_restorer �˲���û��ʹ�á�
//sa_flags ���������źŴ����������ز��������е���ֵ���á�
//OR ���㣨|�����
//A_NOCLDSTOP : �������signumΪSIGCHLD�����ӽ�����ͣʱ������֪ͨ������
//SA_ONESHOT/SA_RESETHAND:�������µ��źŴ�����ǰ�������źŴ���ʽ��ΪϵͳԤ��ķ�ʽ��
//SA_RESTART:���ź��жϵ�ϵͳ���û���������
//SA_NOMASK/SA_NODEFER:�ڴ�����ź�δ����ǰ�������źŵ��ٴε�����
//�������oldact����NULLָ�룬��ԭ�����źŴ���ʽ���ɴ˽ṹsigaction ���ء�
// 
//����ֵ  ִ�гɹ��򷵻�0������д����򷵻�-1��
// 
//�������  EINVAL ����signum ���Ϸ��� ������ͼ����SIGKILL/SIGSTOPSIGKILL�ź�
//EFAULT ����act��oldactָ���ַ�޷���ȡ��
//EINTR �˵��ñ��ж�
// 
//����  #include<unistd.h>
//#include<signal.h>
//void show_handler(struct sigaction * act)
//{
//switch (act->sa_flags)
//{
//case SIG_DFL:printf(��Default action\n��);break;
//case SIG_IGN:printf(��Ignore the signal\n��);break;
//default: printf(��0x%x\n��,act->sa_handler);
//}
//}
//main()
//{
//int i;
//struct sigaction act,oldact;
//act.sa_handler = show_handler;
//act.sa_flags = SA_ONESHOT|SA_NOMASK;
//sigaction(SIGUSR1,&act,&oldact);
//for(i=5;i<15;i++)
//{
//printf(��sa_handler of signal %2d =��.i);
//sigaction(i,NULL,&oldact);
//}
//}
// 
//ִ��  sa_handler of signal 5 = Default action
//sa_handler of signal 6= Default action
//sa_handler of signal 7 = Default action
//sa_handler of signal 8 = Default action
//sa_handler of signal 9 = Default action
//sa_handler of signal 10 = 0x8048400
//sa_handler of signal 11 = Default action
//sa_handler of signal 12 = Default action
//sa_handler of signal 13 = Default action
//sa_handler of signal 14 = Default action
// 
//�� 
//
// 
//
// 
//sigaddset������һ���ź����źż���  
//��غ���  sigemptyset��sigfillset��sigdelset��sigismember
// 
//��ͷ�ļ�  #include<signal.h>
// 
  int sigaddset(sigset_t *set,int signum);
// 
//����˵��  sigaddset()����������signum ������źż���������set �źż��
// 
//����ֵ  ִ�гɹ��򷵻�0������д����򷵻�-1��
// 
//�������  EFAULT ����setָ���ַ�޷���ȡ
//EINVAL ����signum�ǺϷ����źű��
// 
//�� 
//
// 
//
// 
//sigdelset�����źż���ɾ��һ���źţ�  
//��غ���  sigemptyset��sigfillset��sigaddset��sigismember
// 
//��ͷ�ļ�  #include<signal.h>
// 
  int sigdelset(sigset_t * set,int signum);
// 
//����˵��  sigdelset()����������signum������źŴӲ���set�źż���ɾ����
// 
//����ֵ  ִ�гɹ��򷵻�0������д����򷵻�-1��
// 
//�������  EFAULT ����setָ���ַ�޷���ȡ
//EINVAL ����signum�ǺϷ����źű��
// 
//�� 
//
// 
//
// 
//sigemptyset����ʼ���źż���  
//��غ���  sigaddset��sigfillset��sigdelset��sigismember
// 
//��ͷ�ļ�  #include<signal.h>
// 
  int sigemptyset(sigset_t *set);
// 
//����˵��  sigemptyset()����������set�źż���ʼ������ա�
// 
//����ֵ  ִ�гɹ��򷵻�0������д����򷵻�-1��
// 
//�������  EFAULT ����setָ���ַ�޷���ȡ
// 
//�� 
//
// 
//
// 
//sigfillset���������źż������źż���  
//��غ���  sigempty��sigaddset��sigdelset��sigismember
// 
//��ͷ�ļ�  #include<signal.h>
// 
  int sigfillset(sigset_t * set);
// 
//����˵��  sigfillset()����������set�źż���ʼ����Ȼ������е��źż��뵽���źż��
// 
//����ֵ  ִ�гɹ��򷵻�0������д����򷵻�-1��
// 
//����˵��  EFAULT ����setָ���ַ�޷���ȡ
// 
//�� 
//
// 
//
// 
//sigismember������ĳ���ź��Ƿ��Ѽ������źż��  
//��غ���  sigemptyset��sigfillset��sigaddset��sigdelset
// 
//��ͷ�ļ�  #include<signal.h>
// 
  int sigismember(const sigset_t *set,int signum);
// 
//����˵��  sigismember()�������Բ���signum ������ź��Ƿ��Ѽ���������set�źż������źż������и��ź��򷵻�1�����򷵻�0��
// 
//����ֵ  �źż����и��ź��򷵻�1��û���򷵻�0������д����򷵻�-1��
// 
//�������  EFAULT ����setָ���ַ�޷���ȡ
//EINVAL ����signum �ǺϷ����źű��
// 
//�� 
//
// 
//
// 
//signal�������źŴ���ʽ��  
//��غ���  sigaction��kill��raise
// 
//��ͷ�ļ�  #include<signal.h>
// 
  void (*signal(int signum,void(* handler)(int)))(int);
   void  signal();

//����˵��  signal()��������signum ָ�����źű�������ø��źŵĴ���������ָ�����źŵ���ʱ�ͻ���ת������handlerָ���ĺ���ִ�С��������handler���Ǻ���ָ�룬�������������������֮һ:
//SIG_IGN ���Բ���signumָ�����źš�
//SIG_DFL ������signum ָ�����ź�����Ϊ����Ԥ����źŴ���ʽ��
//�����źŵı�ź�˵������ο���¼D
// 
//����ֵ  ������ǰ���źŴ�����ָ�룬����д����򷵻�SIG_ERR(-1)��
// 
//����˵��  ���źŷ�����ת���Զ���handler������ִ�к�ϵͳ���Զ����˴���������ԭ��ϵͳԤ��Ĵ���ʽ�����Ҫ�ı�˲��������sigaction()��
// 
//����  �ο�alarm()��raise()��
// 
//�� 
//
// 
//
// 
//sigpending����ѯ�����õ��źţ�  
//��غ���  signal��sigaction��sigprocmask��sigsuspend
// 
//��ͷ�ļ�  #include<signal.h>
// 
  int sigpending(sigset_t *set);
// 
//����˵��  sigpending()�Ὣ�����õ��źż����ɲ���setָ�뷵�ء�
// 
//����ִֵ  �гɹ��򷵻�0������д����򷵻�-1��
// 
//�������  EFAULT ����setָ���ַ�޷���ȡ
//EINTR �˵��ñ��жϡ�
// 
//�� 
//
// 
//
// 
//sigprocmask����ѯ�������ź����֣�  
//��غ���  signal��sigaction��sigpending��sigsuspend
// 
//��ͷ�ļ�  #include<signal.h>
// 
  int sigprocmask(int how,const sigset_t *set,sigset_t * oldset);
// 
//����˵��  sigprocmask()���������ı�Ŀǰ���ź����֣������������how������
//SIG_BLOCK �µ��ź�������Ŀǰ���ź����ֺͲ���set ָ�����ź�����������
//SIG_UNBLOCK ��Ŀǰ���ź�����ɾ��������setָ�����ź�����
//SIG_SETMASK ��Ŀǰ���ź�������ɲ���setָ�����ź����֡�
//�������oldset����NULLָ�룬��ôĿǰ���ź����ֻ��ɴ�ָ�뷵�ء�
// 
//����ֵ  ִ�гɹ��򷵻�0������д����򷵻�-1��
// 
//�������  EFAULT ����set��oldsetָ���ַ�޷���ȡ��
//EINTR �˵��ñ��ж�
// 
//�� 
//
// 
//
// 
//sleep���ý�����ִͣ��һ��ʱ�䣩  
//��غ���  signal��alarm
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  unsigned int sleep(unsigned int seconds);
// 
//����˵��  sleep()����Ŀǰ�Ľ�����ͣ��ֱ���ﵽ����seconds ��ָ����ʱ�䣬���Ǳ��ź����жϡ�
// 
//����ֵ  ��������ͣ������seconds ��ָ����ʱ���򷵻�0�������ź��ж��򷵻�ʣ��������
// 
//�� 
//
// 
//
// 
//ferror������ļ����Ƿ��д�������  
//��غ���  clearerr��perror
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int ferror(FILE *stream);
// 
//����˵��  ferror()����������stream��ָ�����ļ����Ƿ����˴�����������д������򷵻ط�0ֵ��
// 
//����ֵ  ����ļ����д������򷵻ط�0ֵ��
// 
//�� 
//
// 
//
// 
//perror����ӡ������ԭ����Ϣ�ַ�����  
//��غ���  strerror
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  void perror(const char *s);
// 
//����˵��  perror()��������һ���������������ԭ���������׼����(stderr)������s��ָ���ַ������ȴ�ӡ���������ټ��ϴ���ԭ���ַ������˴���ԭ������ȫ�ֱ���errno��ֵ������Ҫ������ַ�����
// 
//����ֵ  
// 
//����  #include<stdio.h>
//main()
//{
//FILE *fp;
//fp = fopen(��/tmp/noexist��,��r+��);
//if(fp = =NULL) perror(��fopen��);
//}
// 
//ִ��  $ ./perror
//fopen : No such file or diretory
// 
//�� 
//
// 
//
// 
//strerror�����ش���ԭ��������ַ�����  
//��غ���  perror
// 
//��ͷ�ļ�  #include<string.h>
// 
  char * strerror(int errnum);
// 
//����˵��  strerror()����������errnum�Ĵ����������ѯ�����ԭ��������ַ�����Ȼ�󽫸��ַ���ָ�뷵�ء�
// 
//����ֵ  ������������ԭ����ַ���ָ�롣
// 
//����  /* ��ʾ�������0 ��9 �Ĵ���ԭ������*/
//#include<string.h>
//main()
//{
//int i;
//for(i=0;i<10;i++)
//printf(��%d : %s\n��,i,strerror(i));
//}
// 
//ִ��  0 : Success
//1 : Operation not permitted
//2 : No such file or directory
//3 : No such process
//4 : Interrupted system call
//5 : Input/output error
//6 : Device not configured
//7 : Argument list too long
//8 : Exec format error
//9 : Bad file descriptor
// 
//�� 
//
// 
//
// 
//mkfifo�����������ܵ���  
//��غ���  pipe��popen��open��umask
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<sys/stat.h>
// 
  int mkfifo(const char * pathname,mode_t mode);
// 
//����˵��  mkfifo()��������pathname���������FIFO�ļ������ļ����벻���ڣ�������modeΪ���ļ���Ȩ�ޣ�mode%~umask�������umaskֵҲ��Ӱ�쵽FIFO�ļ���Ȩ�ޡ�Mkfifo()������FIFO�ļ��������̶������ö�дһ���ļ��ķ�ʽ��ȡ����ʹ��open()����FIFO�ļ�ʱ��O_NONBLOCK������Ӱ��
//1����ʹ��O_NONBLOCK ���ʱ����FIFO �ļ�����ȡ�Ĳ��������̷��أ���������û���������̴�FIFO �ļ�����ȡ����д��Ĳ����᷵��ENXIO ������롣
//2��û��ʹ��O_NONBLOCK ���ʱ����FIFO ����ȡ�Ĳ�����ȵ��������̴�FIFO�ļ���д����������ء�ͬ���أ���FIFO�ļ���д��Ĳ�����ȵ��������̴�FIFO �ļ�����ȡ����������ء�
// 
//����ֵ  ���ɹ��򷵻�0�����򷵻�-1������ԭ�����errno�С�
// 
//�������  EACCESS ����pathname��ָ����Ŀ¼·���޿�ִ�е�Ȩ��
//EEXIST ����pathname��ָ�����ļ��Ѵ��ڡ�
//ENAMETOOLONG ����pathname��·������̫����
//ENOENT ����pathname������Ŀ¼������
//ENOSPC �ļ�ϵͳ��ʣ��ռ䲻��
//ENOTDIR ����pathname·���е�Ŀ¼���ڵ�ȴ��������Ŀ¼��
//EROFS ����pathnameָ�����ļ�������ֻ���ļ�ϵͳ�ڡ�
// 
//����  #include<sys/types.h>
//#include<sys/stat.h>
//#include<fcntl.h>
//main()
//{
//char buffer[80];
//int fd;
//unlink(FIFO);
//mkfifo(FIFO,0666);
//if(fork()>0){
//char s[ ] = ��hello!\n��;
//fd = open (FIFO,O_WRONLY);
//write(fd,s,sizeof(s));
//close(fd);
//}
//else{
//fd= open(FIFO,O_RDONLY);
//read(fd,buffer,80);
//printf(��%s��,buffer);
//close(fd);
//}
//}
// 
//ִ��  hello!
// 
//�� 
//
// 
//
// 
//pclose���رչܵ�I/O��  
//��غ���  popen
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  int pclose(FILE * stream);
// 
//����˵��  pclose()�����ر���popen�������Ĺܵ����ļ�ָ�롣����streamΪ��ǰ��popen()�����ص��ļ�ָ�롣
// 
//����ֵ  �����ӽ��̵Ľ���״̬������д����򷵻�-1������ԭ�����errno�С�
// 
//�������  ECHILD pclose()�޷�ȡ���ӽ��̵Ľ���״̬��
// 
//����  �ο�popen()��
// 
//�� 
//
// 
//
// 
//pipe�������ܵ���  
//��غ���  mkfifo��popen��read��write��fork
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int pipe(int filedes[2]);
// 
//����˵��  pipe()�Ὠ���ܵ��������ļ��������ɲ���filedes���鷵�ء�filedes[0]Ϊ�ܵ���Ķ�ȡ�ˣ�filedes[1]��Ϊ�ܵ���д��ˡ�
// 
//����ֵ  ���ɹ��򷵻��㣬���򷵻�-1������ԭ�����errno�С�
// 
//�������  EMFILE �����������ļ��������������
//ENFILE ϵͳ�����ļ������ʿ��á�
//EFAULT ����filedes�����ַ���Ϸ���
// 
//����  /* �����̽�ܵ����ַ�����hello!\n�������ӽ��̲���ʾ*/
//#include <unistd.h>
//main()
//{
//int filedes[2];
//char buffer[80];
//pipe(filedes);
//if(fork()>0){
///* ������*/
//char s[ ] = ��hello!\n��;
//write(filedes[1],s,sizeof(s));
//}
//else{
///*�ӽ���*/
//read(filedes[0],buffer,80);
//printf(��%s��,buffer);
//}
//}
// 
//ִ��  hello!
// 
//�� 
//
// 
//
// 
//popen�������ܵ�I/O��  
//��غ���  pipe��mkfifo��pclose��fork��system��fopen
// 
//��ͷ�ļ�  #include<stdio.h>
// 
  FILE * popen( const char * command,const char * type);
// 
//����˵��  popen()�����fork()�����ӽ��̣�Ȼ����ӽ����е���/bin/sh -c��ִ�в���command��ָ�����type��ʹ�á�r�������ȡ����w������д�롣���մ�typeֵ��popen()�Ὠ���ܵ������ӽ��̵ı�׼����豸���׼�����豸��Ȼ�󷵻�һ���ļ�ָ�롣�����̱�����ô��ļ�ָ������ȡ�ӽ��̵�����豸����д�뵽�ӽ��̵ı�׼�����豸�С����⣬����ʹ���ļ�ָ��(FILE*)�����ĺ���Ҳ������ʹ�ã�����fclose()���⡣
// 
//����ֵ  ���ɹ��򷵻��ļ�ָ�룬���򷵻�NULL������ԭ�����errno�С�
// 
//�������  EINVAL����type���Ϸ���
// 
//ע������  �ڱ�д��SUID/SGIDȨ�޵ĳ���ʱ�뾡������ʹ��popen()��popen()��̳л���������ͨ�������������ܻ����ϵͳ��ȫ�����⡣
// 
//����  #include<stdio.h>
//main()
//{
//FILE * fp;
//char buffer[80];
//fp=popen(��cat /etc/passwd��,��r��);
//fgets(buffer,sizeof(buffer),fp);
//printf(��%s��,buffer);
//pclose(fp);
//}
// 
//ִ��  root :x:0 0: root: /root: /bin/bash
// 
//�� 
//
// 
//�ӿڴ���ƪ====================================================================
//�� 
//
// 
//
// 
//accept������socket���ߣ�  
//��غ���  socket��bind��listen��connect
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<sys/socket.h>
// 
  int accept(int s,struct sockaddr * addr,int * addrlen);
// 
//����˵��  accept()�������ܲ���s��socket���ߡ�����s��socket�����Ⱦ�bind()��listen()������������������߽���ʱaccept()�᷵��һ���µ�socket������룬��������ݴ������ȡ���Ǿ����µ�socket������ԭ������s��socket�ܼ���ʹ��accept()�������µ�����Ҫ�����߳ɹ�ʱ������addr��ָ�Ľṹ�ᱻϵͳ����Զ�������ĵ�ַ���ݣ�����addrlenΪscokaddr�Ľṹ���ȡ����ڽṹsockaddr�Ķ�����ο�bind()��
// 
//����ֵ  �ɹ��򷵻��µ�socket������룬ʧ�ܷ���-1������ԭ�����errno�С�
// 
//�������  EBADF ����s �ǺϷ�socket������롣
//EFAULT ����addrָ��ָ���޷���ȡ���ڴ�ռ䡣
//ENOTSOCK ����sΪһ�ļ������ʣ���socket��
//EOPNOTSUPP ָ����socket����SOCK_STREAM��
//EPERM ����ǽ�ܾ������ߡ�
//ENOBUFS ϵͳ�Ļ����ڴ治�㡣
//ENOMEM �����ڴ治�㡣
// 
//����  �ο�listen()��
// 
//�� 
//
// 
//
// 
//bind����socket��λ��  
//��غ���  socket��accept��connect��listen
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<sys/socket.h>
// 
  int bind(int sockfd,struct sockaddr * my_addr,int addrlen);
// 
//����˵��  bind()�������ø�����sockfd��socketһ�����ơ��������ɲ���my_addrָ��һsockaddr�ṹ�����ڲ�ͬ��socket domain������һ��ͨ�õ����ݽṹ
//struct sockaddr
//{
//unsigned short int sa_family;
//char sa_data[14];
//};
//sa_family Ϊ����socket����ʱ��domain��������AF_xxxxֵ��
//sa_data ���ʹ��14���ַ����ȡ�
//��sockaddr�ṹ����ʹ�ò�ͬ��socket domain���в�ͬ�ṹ���壬����ʹ��AF_INET domain����socketaddr�ṹ�����Ϊ
//struct socketaddr_in
//{
//unsigned short int sin_family;
//uint16_t sin_port;
//struct in_addr sin_addr;
//unsigned char sin_zero[8];
//};
//struct in_addr
//{
//uint32_t s_addr;
//};
//sin_family ��Ϊsa_family
//sin_port Ϊʹ�õ�port���
//sin_addr.s_addr ΪIP ��ַ
//sin_zero δʹ�á�
// 
//����  addrlenΪsockaddr�Ľṹ���ȡ�
// 
//����ֵ  �ɹ��򷵻�0��ʧ�ܷ���-1������ԭ�����errno�С�
// 
//�������  EBADF ����sockfd �ǺϷ�socket������롣
//EACCESS Ȩ�޲���
//ENOTSOCK ����sockfdΪһ�ļ������ʣ���socket��
// 
//����  �ο�listen()
// 
//�� 
//
// 
//
// 
//connect������socket���ߣ�  
//��غ���  socket��bind��listen
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<sys/socket.h>
// 
  int connect (int sockfd,struct sockaddr * serv_addr,int addrlen);
// 
//����˵��  connect()����������sockfd ��socket ��������serv_addr ָ���������ַ���ṹsockaddr��ο�bind()������addrlenΪsockaddr�Ľṹ���ȡ�
// 
//����ֵ  �ɹ��򷵻�0��ʧ�ܷ���-1������ԭ�����errno�С�
// 
//�������  EBADF ����sockfd �ǺϷ�socket�������
//EFAULT ����serv_addrָ��ָ���޷���ȡ���ڴ�ռ�
//ENOTSOCK ����sockfdΪһ�ļ������ʣ���socket��
//EISCONN ����sockfd��socket��������״̬
//ECONNREFUSED ����Ҫ��server�˾ܾ���
//ETIMEDOUT ��ͼ���ߵĲ��������޶�ʱ����δ����Ӧ��
//ENETUNREACH �޷��������ݰ���ָ����������
//EAFNOSUPPORT sockaddr�ṹ��sa_family����ȷ��
//EALREADY socketΪ�����������ǰ�����߲�����δ��ɡ�
// 
//����  /* ����socket��TCP client
//�˳��������TCP server����������������ַ������͸�server��
//TCP server������ο�listen������
//*/
//#include<sys/stat.h>
//#include<fcntl.h>
//#include<unistd.h>
//#include<sys/types.h>
//#include<sys/socket.h>
//#include<netinet/in.h>
//#include<arpa/inet.h>
//#define PORT 1234
//#define SERVER_IP ��127.0.0.1��
//main()
//{
//int s;
//struct sockaddr_in addr;
//char buffer[256];
//if((s = socket(AF_INET,SOCK_STREAM,0))<0){
//perror(��socket��);
//exit(1);
//}
///* ��дsockaddr_in�ṹ*/
//bzero(&addr,sizeof(addr));
//addr.sin_family = AF_INET;
//addr.sin_port=htons(PORT);
//addr.sin_addr.s_addr = inet_addr(SERVER_IP);
///* ��������*/
//if(connect(s,&addr,sizeof(addr))<0){
//perror(��connect��);
//exit(1);
//}
///* ������server�˴�������Ϣ*/
//recv(s,buffer,sizeof(buffer),0);
//printf(��%s\n��,buffer);
//while(1){
//bzero(buffer,sizeof(buffer));
///* �ӱ�׼�����豸ȡ���ַ���*/
//read(STDIN_FILENO,buffer,sizeof(buffer));
///* ���ַ�������server��*/
//if(send(s,buffer,sizeof(buffer),0)<0){
//perror(��send��);
//exit(1);
//}
//}
//}
// 
//ִ��  $ ./connect
//Welcome to server!
//hi I am client! /*��������*/
///*<Ctrl+C>�жϳ���*/
// 
//�� 
//
// 
//
// 
//endprotoent����������Э�����ݵĶ�ȡ��  
//��غ���  getprotoent��getprotobyname��getprotobynumber��setprotoent
// 
//��ͷ�ļ�  #include<netdb.h>
// 
  void endprotoent(void);
// 
//����˵��  endprotoent()�����ر���getprotoent()�򿪵��ļ���
// 
//����ֵ  
// 
//����  �ο�getprotoent()
// 
//�� 
//
// 
//
// 
//endservent����������������ݵĶ�ȡ��  
//��غ���  getservent��getservbyname��getservbyport��setservent
// 
//��ͷ�ļ�  #include<netdb.h>
// 
  void endservent(void);
// 
//����˵��  endservent()�����ر���getservent()���򿪵��ļ���
// 
//����ֵ  
// 
//����  �ο�getservent()��
// 
//�� 
//
// 
//
// 
//getsockopt��ȡ��socket״̬��  
//��غ���  setsockopt
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<sys/socket.h>
// 
  int getsockopt(int s,int level,int optname,void* optval,socklen_t* optlen);
// 
//����˵��  getsockopt()�Ὣ����s��ָ����socket״̬���ء�����optname������ȡ�ú���ѡ��״̬��������optval��ָ�������������ڴ��ַ������optlen��Ϊ�ÿռ�Ĵ�С������level��optname��ο�setsockopt()��
// 
//����ֵ  �ɹ��򷵻�0�����д����򷵻�-1������ԭ�����errno
// 
//�������  EBADF ����s ���ǺϷ���socket�������
//ENOTSOCK ����sΪһ�ļ������ʣ���socket
//ENOPROTOOPT ����optnameָ����ѡ���ȷ
//EFAULT ����optvalָ��ָ���޷���ȡ���ڴ�ռ�
// 
//����  #include<sys/types.h>
//#include<sys/socket.h>
//main()
//{
//int s,optval,optlen = sizeof(int);
//if((s = socket(AF_INET,SOCK_STREAM,0))<0) perror(��socket��);
//getsockopt(s,SOL_SOCKET,SO_TYPE,&optval,&optlen);
//printf(��optval = %d\n��,optval);
//close(s);}
// 
//ִ��  optval = 1 /*SOCK_STREAM�Ķ������Ǵ�ֵ*/
// 
//�� 
//
// 
//
// 
//htonl����32λ�����ַ�˳��ת���������ַ�˳��  
//��غ���  htons��ntohl��ntohs
// 
//��ͷ�ļ�  #include<netinet/in.h>
// 
  unsigned long int htonl(unsigned long int hostlong);
// 
//����˵��  htonl��������������ָ����32λhostlong ת���������ַ�˳��
// 
//����ֵ  ���ض�Ӧ�������ַ�˳��
// 
//����  �ο�getservbyport()��connect()��
// 
//�� 
//
// 
//
// 
//htons����16λ�����ַ�˳��ת���������ַ�˳��  
//��غ���  htonl��ntohl��ntohs
// 
//��ͷ�ļ�  #include<netinet/in.h>
// 
  unsigned short int htons(unsigned short int hostshort);
// 
//����˵��  htons()����������ָ����16λhostshortת���������ַ�˳��
// 
//����ֵ  ���ض�Ӧ�������ַ�˳��
// 
//����  �ο�connect()��
// 
//�� 
//
// 
//
// 
//inet_addr���������ַת�ɶ����Ƶ����֣�  
//��غ���  inet_aton��inet_ntoa
// 
//��ͷ�ļ�  #include<sys/socket.h>
//#include<netinet/in.h>
//#include<arpa/inet.h>
// 
  unsigned long int inet_addr(const char *cp);
// 
//����˵��  inet_addr()����������cp��ָ�������ַ�ַ���ת����������ʹ�õĶ��������֡������ַ�ַ����������ֺ͵���ɵ��ַ���������:��163.13.132.68����
// 
//����ֵ  �ɹ��򷵻ض�Ӧ����������Ƶ����֣�ʧ�ܷ���-1��
// 
//�� 
//
// 
//
// 
//inet_aton���������ַת����������Ƶ����֣�  
//��غ���  inet_addr��inet_ntoa
// 
//��ͷ�ļ�  #include<sys/scoket.h>
//#include<netinet/in.h>
//#include<arpa/inet.h>
// 
  int inet_aton(const char * cp,struct in_addr *inp);
// 
//����˵��  inet_aton()����������cp��ָ�������ַ�ַ���ת��������ʹ�õĶ����Ƶ����֣�Ȼ����ڲ���inp��ָ��in_addr�ṹ�С�
//�ṹin_addr��������
//struct in_addr
//{
//unsigned long int s_addr;
//};
// 
//����ֵ  �ɹ��򷵻ط�0ֵ��ʧ���򷵻�0��
// 
//�� 
//
// 
//
// 
//inet_ntoa������������Ƶ�����ת���������ַ��  
//��غ���  inet_addr��inet_aton
// 
//��ͷ�ļ�  #include<sys/socket.h>
//#include<netinet/in.h>
//#include<arpa/inet.h>
// 
  char * inet_ntoa(struct in_addr in);
// 
//����˵��  inet_ntoa()����������in��ָ����������Ƶ�����ת���������ַ��Ȼ��ָ��������ַ�ַ�����ָ�뷵�ء�
// 
//����ֵ  �ɹ��򷵻��ַ���ָ�룬ʧ���򷵻�NULL��
// 
//�� 
//
// 
//
// 
//listen���ȴ����ӣ�  
//��غ���  socket��bind��accept��connect
// 
//��ͷ�ļ�  #include<sys/socket.h>
// 
  int listen(int s,int backlog);
// 
//����˵��  listen()�����ȴ�����s ��socket���ߡ�����backlogָ��ͬʱ�ܴ�����������Ҫ�����������Ŀ���������client�˽��յ�ECONNREFUSED�Ĵ���Listen()��δ��ʼ�������ߣ�ֻ������socketΪlistenģʽ����������client�����ߵ���accept()��ͨ��listen()����socket()��bind()֮����ã����Ųŵ���accept()��
// 
//����ֵ  �ɹ��򷵻�0��ʧ�ܷ���-1������ԭ�����errno
// 
//����˵��  listen()ֻ����SOCK_STREAM��SOCK_SEQPACKET��socket���͡����socketΪAF_INET�����backlog ���ֵ������128��
// 
//�������  EBADF ����sockfd�ǺϷ�socket�������
//EACCESS Ȩ�޲���
//EOPNOTSUPP ָ����socket��δ֧Ԯlistenģʽ��
// 
//����  #include<sys/types.h>
//#include<sys/socket.h>
//#include<netinet/in.h>
//#include<arpa/inet.h>
//#include<unistd.h>
//#define PORT 1234
//#define MAXSOCKFD 10
//main()
//{
//int sockfd,newsockfd,is_connected[MAXSOCKFD],fd;
//struct sockaddr_in addr;
//int addr_len = sizeof(struct sockaddr_in);
//fd_set readfds;
//char buffer[256];
//char msg[ ] =��Welcome to server!��;
//if ((sockfd = socket(AF_INET,SOCK_STREAM,0))<0){
//perror(��socket��);
//exit(1);
//}
//bzero(&addr,sizeof(addr));
//addr.sin_family =AF_INET;
//addr.sin_port = htons(PORT);
//addr.sin_addr.s_addr = htonl(INADDR_ANY);
//if(bind(sockfd,&addr,sizeof(addr))<0){
//perror(��connect��);
//exit(1);
//}
//if(listen(sockfd,3)<0){
//perror(��listen��);
//exit(1);
//}
//for(fd=0;fd<MAXSOCKFD;fd++)
//is_connected[fd]=0;
//while(1){
//FD_ZERO(&readfds);
//FD_SET(sockfd,&readfds);
//for(fd=0;fd<MAXSOCKFD;fd++)
//if(is_connected[fd]) FD_SET(fd,&readfds);
//if(!select(MAXSOCKFD,&readfds,NULL,NULL,NULL))continue;
//for(fd=0;fd<MAXSOCKFD;fd++)
//if(FD_ISSET(fd,&readfds)){
//if(sockfd = =fd){
//if((newsockfd = accept (sockfd,&addr,&addr_len))<0)
//perror(��accept��);
//write(newsockfd,msg,sizeof(msg));
//is_connected[newsockfd] =1;
//printf(��cnnect from %s\n��,inet_ntoa(addr.sin_addr));
//}else{
//bzero(buffer,sizeof(buffer));
//if(read(fd,buffer,sizeof(buffer))<=0){
//printf(��connect closed.\n��);
//is_connected[fd]=0;
//close(fd);
//}else
//printf(��%s��,buffer);
//}
//}
//}
//}
// 
//ִ��  $ ./listen
//connect from 127.0.0.1
//hi I am client
//connected closed.
// 
//�� 
//
// 
//
// 
//ntohl����32λ�����ַ�˳��ת���������ַ�˳��  
//��غ���  htonl��htons��ntohs
// 
//��ͷ�ļ�  #include<netinet/in.h>
// 
  unsigned long int ntohl(unsigned long int netlong);
// 
//����˵��  ntohl()����������ָ����32λnetlongת���������ַ�˳��
// 
//����ֵ  ���ض�Ӧ�������ַ�˳��
// 
//����  �ο�getservent()��
// 
//�� 
//
// 
//
// 
//ntohs����16λ�����ַ�˳��ת���������ַ�˳��  
//��غ���  htonl��htons��ntohl
// 
//��ͷ�ļ�  #include<netinet/in.h>
// 
  unsigned short int ntohs(unsigned short int netshort);
// 
//����˵��  ntohs()����������ָ����16λnetshortת���������ַ�˳��
// 
//����ֵ  ���ض�Ӧ������˳��
// 
//����  �ο�getservent()��
// 
//�� 
//
// 
//
// 
//recv����socket�������ݣ�  
//��غ���  recvfrom��recvmsg��send��sendto��socket
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<sys/socket.h>
// 
  int recv(int s,void *buf,int len,unsigned int flags);
// 
//����˵��  recv()��������Զ��������ָ����socket���������ݣ��������ݴ浽�ɲ���buf ָ����ڴ�ռ䣬����lenΪ�ɽ������ݵ���󳤶ȡ�
// 
//����  flagsһ����0��������ֵ��������:
//MSG_OOB ������out-of-band �ͳ������ݡ�
//MSG_PEEK �����������ݲ�������ϵͳ��ɾ��������ٵ���recv()�᷵����ͬ���������ݡ�
//MSG_WAITALLǿ�Ƚ��յ�len��С�����ݺ���ܷ��أ������д�����źŲ�����
//MSG_NOSIGNAL�˲�����Ը��SIGPIPE�ź��жϷ���ֵ�ɹ��򷵻ؽ��յ����ַ�����ʧ�ܷ���-1������ԭ�����errno�С�
// 
//�������  EBADF ����s�ǺϷ���socket�������
//EFAULT ��������һָ��ָ���޷���ȡ���ڴ�ռ�
//ENOTSOCK ����sΪһ�ļ������ʣ���socket��
//EINTR ���ź����ж�
//EAGAIN �˶������������ϣ�������s��socketΪ�������
//ENOBUFS ϵͳ�Ļ����ڴ治�㡣
//ENOMEM �����ڴ治��
//EINVAL ����ϵͳ���õĲ�������ȷ��
// 
//����  �ο�listen()��
// 
//�� 
//
// 
//
// 
//recvfrom����socket�������ݣ�  
//��غ���  recv��recvmsg��send��sendto��socket
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<sys/socket.h>
// 
  int recvfrom(int s,void *buf,int len,unsigned int flags ,struct sockaddr *from ,int *fromlen);
// 
//����˵��  recv()��������Զ��������ָ����socket ���������ݣ��������ݴ浽�ɲ���buf ָ����ڴ�ռ䣬����len Ϊ�ɽ������ݵ���󳤶ȡ�����flags һ����0��������ֵ������ο�recv()������from����ָ�������͵������ַ���ṹsockaddr ��ο�bind()������fromlenΪsockaddr�Ľṹ���ȡ�
// 
//����ֵ  �ɹ��򷵻ؽ��յ����ַ�����ʧ���򷵻�-1������ԭ�����errno�С�
// 
//�������  EBADF ����s�ǺϷ���socket�������
//EFAULT ��������һָ��ָ���޷���ȡ���ڴ�ռ䡣
//ENOTSOCK ����sΪһ�ļ������ʣ���socket��
//EINTR ���ź����жϡ�
//EAGAIN �˶������������ϣ�������s��socketΪ������ϡ�
//ENOBUFS ϵͳ�Ļ����ڴ治��
//ENOMEM �����ڴ治��
//EINVAL ����ϵͳ���õĲ�������ȷ��
// 
//����  /*����socket��UDP client
//�˳��������UDP server����������������ַ�������server��
//UDP server ������ο�sendto������
//*/
//#include<sys/stat.h>
//#include<fcntl.h>
//#include<unistd.h>
//#include<sys/typs.h>
//#include<sys/socket.h>
//#include<netinet/in.h>
//#include<arpa/inet.h>
//#define PORT 2345
//#define SERVER_IP ��127.0.0.1��
//main()
//{
//int s,len;
//struct sockaddr_in addr;
//int addr_len =sizeof(struct sockaddr_in);
//char buffer[256];
///* ����socket*/
//if((s = socket(AF_INET,SOCK_DGRAM,0))<0){
//perror(��socket��);
//exit(1);
//}
///* ��дsockaddr_in*/
//bzero(&addr,sizeof(addr));
//addr.sin_family = AF_INET;
//addr.sin_port = htons(PORT);
//addr.sin_addr.s_addr = inet_addr(SERVER_IP);
//while(1){
//bzero(buffer,sizeof(buffer));
///* �ӱ�׼�����豸ȡ���ַ���*/
//len =read(STDIN_FILENO,buffer,sizeof(buffer));
///* ���ַ������͸�server��*/
//sendto(s,buffer,len,0,&addr,addr_len);
///* ����server�˷��ص��ַ���*/
//len = recvfrom(s,buffer,sizeof(buffer),0,&addr,&addr_len);
//printf(��receive: %s��,buffer);
//}
//}
// 
//ִ��  (��ִ��udp server ��ִ��udp client)
//hello /*�Ӽ��������ַ���*/
//receive: hello /*server�˷��������ַ���*/
// 
//�� 
//
// 
//
// 
//recvmsg����socket�������ݣ�  
//��غ���  recv��recvfrom��send��sendto��sendmsg��socket
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<sys/socktet.h>
// 
  int recvmsg(int s,struct msghdr *msg,unsigned int flags);
// 
//����˵��  recvmsg()��������Զ��������ָ����socket���������ݡ�����sΪ�ѽ��������ߵ�socket���������UDPЭ�����辭�����߲���������msgָ�������ߵ����ݽṹ���ݣ�����flagsһ����0����ϸ������ο�send()�����ڽṹmsghdr�Ķ�����ο�sendmsg()��
// 
//����ֵ  �ɹ��򷵻ؽ��յ����ַ�����ʧ���򷵻�-1������ԭ�����errno�С�
// 
//�������  EBADF ����s�ǺϷ���socket������롣
//EFAULT ��������һָ��ָ���޷���ȡ���ڴ�ռ�
//ENOTSOCK ����sΪһ�ļ������ʣ���socket��
//EINTR ���ź����жϡ�
//EAGAIN �˲������������ϣ�������s��socketΪ������ϡ�
//ENOBUFS ϵͳ�Ļ����ڴ治��
//ENOMEM �����ڴ治��
//EINVAL ����ϵͳ���õĲ�������ȷ��
// 
//����  �ο�recvfrom()��
// 
//�� 
//
// 
//
// 
//send����socket�������ݣ�  
//��غ���  sendto��sendmsg��recv��recvfrom��socket
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<sys/socket.h>
// 
  int send(int s,const void * msg,int len,unsigned int falgs);
// 
//����˵��  send()������������ָ����socket �����Է�����������sΪ�ѽ��������ӵ�socket������msgָ�������ߵ��������ݣ�����len��Ϊ���ݳ��ȡ�����flagsһ����0��������ֵ��������
//MSG_OOB ���͵�������out-of-band �ͳ���
//MSG_DONTROUTE ȡ��·�ɱ��ѯ
//MSG_DONTWAIT ����Ϊ�����������
//MSG_NOSIGNAL �˶�����Ը��SIGPIPE �ź��жϡ�
// 
//����ֵ  �ɹ��򷵻�ʵ�ʴ��ͳ�ȥ���ַ�����ʧ�ܷ���-1������ԭ�����errno
// 
//�������  EBADF ����s �ǺϷ���socket������롣
//EFAULT ��������һָ��ָ���޷���ȡ���ڴ�ռ�
//ENOTSOCK ����sΪһ�ļ������ʣ���socket��
//EINTR ���ź����жϡ�
//EAGAIN �˲������������ϣ�������s��socketΪ������ϡ�
//ENOBUFS ϵͳ�Ļ����ڴ治��
//ENOMEM �����ڴ治��
//EINVAL ����ϵͳ���õĲ�������ȷ��
// 
//����  �ο�connect()
// 
//�� 
//
// 
//
// 
//sendmsg����socket�������ݣ�  
//��غ���  send��sendto��recv��recvfrom��recvmsg��socket
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<sys/socket.h>
// 
  int sendmsg(int s,const strcut msghdr *msg,unsigned int flags);
// 
//����˵��  sendmsg()������������ָ����socket�����Է�����������sΪ�ѽ��������ߵ�socket���������UDPЭ�����辭�����߲���������msg ָ�������ߵ����ݽṹ���ݣ�����flagsһ��Ĭ��Ϊ0����ϸ������ο�send()��
//�ṹmsghdr��������
//struct msghdr
//{
//void *msg_name; /*Address to send to /receive from . */
//socklen_t msg_namelen; /* Length of addres data */
//strcut iovec * msg_iov; /* Vector of data to send/receive into */
//size_t msg_iovlen; /* Number of elements in the vector */
//void * msg_control; /* Ancillary dat */
//size_t msg_controllen; /* Ancillary data buffer length */
//int msg_flags; /* Flags on received message */
//};
// 
//����ֵ  �ɹ��򷵻�ʵ�ʴ��ͳ�ȥ���ַ�����ʧ�ܷ���-1������ԭ�����errno
// 
//�������  EBADF ����s �ǺϷ���socket������롣
//EFAULT ��������һָ��ָ���޷���ȡ���ڴ�ռ�
//ENOTSOCK ����sΪһ�ļ������ʣ���socket��
//EINTR ���ź����жϡ�
//EAGAIN �˲������������ϣ�������s��socketΪ������ϡ�
//ENOBUFS ϵͳ�Ļ����ڴ治��
//ENOMEM �����ڴ治��
//EINVAL ����ϵͳ���õĲ�������ȷ��
// 
//����  �ο�sendto()��
// 
//�� 
//
// 
//
// 
//sendto����socket�������ݣ�  
//��غ���  send , sendmsg,recv , recvfrom , socket
// 
//��ͷ�ļ�  #include < sys/types.h >
//#include < sys/socket.h >
// 
  int sendto ( int s , const void * msg, int len, unsigned int flags, const 
//struct sockaddr * to , int tolen ) ;
// 
//����˵��  sendto() ������������ָ����socket�����Է�����������sΪ�ѽ������ߵ�socket,�������UDPЭ�����辭�����߲���������msgָ�������ߵ��������ݣ�����flags һ����0����ϸ������ο�send()������to����ָ�������͵������ַ���ṹsockaddr��ο�bind()������tolenΪsockaddr�Ľ�����ȡ�
// 
//����ֵ  �ɹ��򷵻�ʵ�ʴ��ͳ�ȥ���ַ�����ʧ�ܷ��أ�1������ԭ�����errno �С�
// 
//�������  EBADF ����s�Ƿ���socket������롣
//EFAULT ��������һָ��ָ���޷���ȡ���ڴ�ռ䡣
//WNOTSOCK canshu sΪһ�ļ������ʣ���socket��
//EINTR ���ź����жϡ�
//EAGAIN �˶������������ϣ�������s��soketΪ������ϵġ�
//ENOBUFS ϵͳ�Ļ����ڴ治�㡣
//EINVAL ����ϵͳ���õĲ�������ȷ��
// 
//����  #include < sys/types.h >
//#include < sys/socket.h >
//# include <netinet.in.h>
//#include <arpa.inet.h>
//#define PORT 2345 /*ʹ�õ�port*/
//main(){
//int sockfd,len;
//struct sockaddr_in addr;
//char buffer[256];
///*����socket*/
//if(sockfd=socket (AF_INET,SOCK_DGRAM,0))<0){
//perror (��socket��);
//exit(1);
//}
///*��дsockaddr_in �ṹ*/
//bzero ( &addr, sizeof(addr) );
//addr.sin_family=AF_INET;
//addr.sin_port=htons(PORT);
//addr.sin_addr=hton1(INADDR_ANY) ;
//if (bind(sockfd, &addr, sizeof(addr))<0){
//perror(��connect��);
//exit(1);
//}
//while(1){
//bezro(buffer,sizeof(buffer));
//len = recvfrom(socket,buffer,sizeof(buffer), 0 , &addr &addr_len);
///*��ʾclient�˵������ַ*/
//printf(��receive from %s\n �� , inet_ntoa( addr.sin_addr));
///*���ִ����ظ�client��*/
//sendto(sockfd,buffer,len,0,&addr,addr_len);��
//}
//}
// 
//ִ��  ��ο�recvfrom()
// 
//�� 
//
// 
//
// 
//setprotoent��������Э��������ļ���  
//��غ���  getprotobyname, getprotobynumber, endprotoent
// 
//��ͷ�ļ�  #include <netdb.h>
// 
  void setprotoent (int stayopen);
// 
//����˵��  setprotoent()������/etc/protocols�� �������stayopenֵΪ1�����������getprotobyname()��getprotobynumber()�������Զ��رմ��ļ���
// 
//�� 
//
// 
//
// 
//setservent���������������������ļ���  
//��غ���  getservent, getservbyname, getservbyport, endservent
// 
//��ͷ�ļ�  #include < netdb.h >
// 
  void setservent (int stayopen);
// 
//����˵��  setservent()������/etc/services���������stayopenֵΪ1�����������getservbyname()��getservbyport()�������Զ��ر��ļ���
// 
//�� 
//
// 
//
// 
//setsockopt������socket״̬��  
//��غ���  getsockopt
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<sys/socket.h>
// 
  int setsockopt(int s,int level,int optname,const void * optval,,socklen_toptlen);
// 
//����˵��  setsockopt()�������ò���s��ָ����socket״̬������level���������õ�����㣬һ�����SOL_SOCKET�Դ�ȡsocket�㡣����optname���������õ�ѡ������м�����ֵ:
//SO_DEBUG �򿪻�ر��Ŵ�ģʽ
//SO_REUSEADDR ������bind���������б��ص�ַ���ظ�ʹ��
//SO_TYPE ����socket��̬��
//SO_ERROR ����socket�ѷ����Ĵ���ԭ��
//SO_DONTROUTE �ͳ������ݰ���Ҫ����·���豸�����䡣
//SO_BROADCAST ʹ�ù㲥��ʽ����
//SO_SNDBUF �����ͳ����ݴ�����С
//SO_RCVBUF ���ý��յ��ݴ�����С
//SO_KEEPALIVE ����ȷ�������Ƿ�����ֹ��
//SO_OOBINLINE �����յ�OOB ����ʱ������������׼�����豸
//SO_LINGER ȷ�����ݰ�ȫ�ҿɿ��Ĵ��ͳ�ȥ��
// 
//����  optval���������õ�ֵ������optlen��Ϊoptval�ĳ��ȡ�
// 
//����ֵ  �ɹ��򷵻�0�����д����򷵻�-1������ԭ�����errno��
// 
//����˵��  EBADF ����s���ǺϷ���socket�������
//ENOTSOCK ����sΪһ�ļ������ʣ���socket
//ENOPROTOOPT ����optnameָ����ѡ���ȷ��
//EFAULT ����optvalָ��ָ���޷���ȡ���ڴ�ռ䡣
// 
//����  �ο�getsockopt()��
// 
//�� 
//
// 
//
// 
//shutdown����ֹsocketͨ�ţ�  
//��غ���  socket��connect
// 
//��ͷ�ļ�  #include<sys/socket.h>
// 
  int shutdown(int s,int how);
// 
//����˵��  shutdown()������ֹ����s��ָ����socket���ߡ�����s�������е�socket������룬����how�����м������:
//how=0 ��ֹ��ȡ������
//how=1 ��ֹ���Ͳ���
//how=2 ��ֹ��ȡ�����Ͳ���
// 
//����ֵ  �ɹ��򷵻�0��ʧ�ܷ���-1������ԭ�����errno��
// 
//�������  EBADF ����s������Ч��socket�������
//ENOTSOCK ����sΪһ�ļ������ʣ���socket
//ENOTCONN ����sָ����socket��δ����
// 
//�� 
//
// 
//
// 
//socket������һ��socketͨ�ţ�  
//��غ���  accept��bind��connect��listen
// 
//��ͷ�ļ�  #include<sys/types.h>
//#include<sys/socket.h>
// 
  int socket(int domain,int type,int protocol);
// 
//����˵��  socket()��������һ���µ�socket��Ҳ������ϵͳע�ᣬ֪ͨϵͳ����һͨ�Ŷ˿ڡ�����domain ָ��ʹ�ú��ֵĵ�ַ���ͣ������Ķ�����/usr/include/bits/socket.h �ڣ������ǳ�����Э��:
//PF_UNIX/PF_LOCAL/AF_UNIX/AF_LOCAL UNIX ����ͨ��Э��
//PF_INET?AF_INET Ipv4����Э��
//PF_INET6/AF_INET6 Ipv6 ����Э��
//PF_IPX/AF_IPX IPX-NovellЭ��
//PF_NETLINK/AF_NETLINK �����û��ӿ�װ��
//PF_X25/AF_X25 ITU-T X.25/ISO-8208 Э��
//PF_AX25/AF_AX25 ҵ������AX.25Э��
//PF_ATMPVC/AF_ATMPVC ��ȡԭʼATM PVCs
//PF_APPLETALK/AF_APPLETALK appletalk��DDP��Э��
//PF_PACKET/AF_PACKET ��������ӿ�
// 
//����  type�����м�����ֵ:
//SOCK_STREAM �ṩ˫�������ҿ�����������������TCP��֧��
//OOB ���ƣ����������ݴ���ǰ����ʹ��connect()����������״̬��
//SOCK_DGRAM ʹ�ò������������������ݰ�����
//SOCK_SEQPACKET �ṩ���������������ݰ�����
//SOCK_RAW �ṩԭʼ����Э���ȡ
//SOCK_RDM �ṩ�����������ݰ�����
//SOCK_PACKET �ṩ��������������ֱ��ͨ�š�
//protocol����ָ��socket��ʹ�õĴ���Э���ţ�ͨ���˲ο����ù�������Ϊ0���ɡ�
// 
//����ֵ  �ɹ��򷵻�socket������룬ʧ�ܷ���-1��
// 
//�������  EPROTONOSUPPORT ����domainָ�������Ͳ�֧�ֲ���type��protocolָ����Э��
//ENFILE �����ڴ治�㣬�޷������µ�socket�ṹ
//EMFILE �����ļ���������޷��ٽ����µ�socket
//EACCESS Ȩ�޲��㣬�޷�����type��protocolָ����Э��
//ENOBUFS/ENOMEM �ڴ治��
//EINVAL ����domain/type/protocol���Ϸ�
// 
//����  �ο�connect()��
// 
//�� 
//
// 
//��������ƪ========================================================================
//�� 
//
// 
//
// 
//getenv��ȡ�û����������ݣ�  
//��غ���  putenv��setenv��unsetenv
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  char * getenv(const char *name);
// 
//����˵��  getenv()����ȡ�ò���name�������������ݡ�����nameΪ�������������ƣ�����ñ���������᷵��ָ������ݵ�ָ�롣���������ĸ�ʽΪname��value��
// 
//����ֵ  ִ�гɹ��򷵻�ָ������ݵ�ָ�룬�Ҳ������ϵĻ������������򷵻�NULL��
// 
//����  #include<stdlib.h>
//mian()
//{
//char *p;
//if((p = getenv(��USER��)))
//printf(��USER=%s\n��,p);
//}
// 
//ִ��  USER = root
// 
//�� 
//
// 
//
// 
//putenv���ı�����ӻ���������  
//��غ���  getenv��setenv��unsetenv
// 
//��ͷ�ļ�  #include4<stdlib.h>
// 
  int putenv(const char * string);
// 
//����˵��  putenv()�����ı�����ӻ������������ݡ�����string�ĸ�ʽΪname��value������û�������ԭ�ȴ��ڣ���������ݻ�������string�ı䣬����˲������ݻ��Ϊ�µĻ���������
// 
//����ֵ  ִ�гɹ��򷵻�0���д������򷵻�-1��
// 
//�������  ENOMEM �ڴ治�㣬�޷������µĻ��������ռ䡣
// 
//����  #include<stdlib.h>
//main()
//{
//char *p;
//if((p = getenv(��USER��)))
//printf(��USER =%s\n��,p);
//putenv(��USER=test��);
//printf(��USER+5s\n��,getenv(��USER��));
//}
// 
//ִ��  USER=root
//USER=root
// 
//�� 
//
// 
//
// 
//setenv���ı�����ӻ���������  
//��غ���  getenv��putenv��unsetenv
// 
//��ͷ�ļ�  #include<stdlib.h>
// 
  int setenv(const char *name,const char * value,int overwrite);
// 
//����˵��  setenv()�����ı�����ӻ������������ݡ�����nameΪ�������������ַ�����
// 
//����  value��Ϊ�������ݣ�����overwrite���������Ƿ�Ҫ�ı��Ѵ��ڵĻ������������overwrite��Ϊ0�����û�������ԭ�������ݣ���ԭ���ݻᱻ��Ϊ����value��ָ�ı������ݡ����overwriteΪ0���Ҹû��������������ݣ������value�ᱻ���ԡ�
// 
//����ֵ  ִ�гɹ��򷵻�0���д�����ʱ����-1��
// 
//�������  ENOMEM �ڴ治�㣬�޷������µĻ��������ռ�
// 
//����  #include<stdlib.h>
//main()
//{
//char * p;
//if((p=getenv(��USER��)))
//printf(��USER =%s\n��,p);
//setenv(��USER��,��test��,1);
//printf(��USER=%s\n��,getenv(��USEr��));
//unsetenv(��USER��);
//printf(��USER=%s\n��,getenv(��USER��));
//}
// 
//ִ��  USER = root
//USER = test
//USER = (null)
// 
//�� 
//
// 
//�ն˿���ƪ===============================================================
//�� 
//
// 
//
// 
//getopt�����������в�����  
//��غ���  
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int getopt(int argc,char * const argv[ ],const char * optstring);
// 
//����˵��  getopt()�������������в���������argc��argv����main()���ݵĲ������������ݡ�����optstring ������������ѡ���ַ������˺����᷵����argv ����һ����ѡ����ĸ������ĸ���Ӧ����optstring �е���ĸ�����ѡ���ַ��������ĸ�����ð�š�:�������ʾ������صĲ�����ȫ�����optarg ����ָ��˶�����������getopt()�Ҳ������ϵĲ������ӡ������Ϣ������ȫ�����optopt��Ϊ��?���ַ��������ϣ��getopt()ӡ������Ϣ����ֻҪ��ȫ�����opterr��Ϊ0���ɡ�
// 
//����ֵ  ����ҵ����ϵĲ����򷵻ش˲�����ĸ����������������ڲ���optstring ��ѡ����ĸ�򷵻ء�?���ַ������������򷵻�-1��
// 
//����  #include<stdio.h>
//#include<unistd.h>
//int main(int argc,char **argv)
//{
//int ch;
//opterr = 0;
//while((ch = getopt(argc,argv,��a:bcde��))!= -1)
//switch(ch)
//{
//case ��a��:
//printf(��option a:��%s��\n��,optarg);
//break;
//case ��b��:
//printf(��option b :b\n��);
//break;
//default:
//printf(��other option :%c\n��,ch);
//}
//printf(��optopt +%c\n��,optopt);
//}
// 
//ִ��  $./getopt �Cb
//option b:b
//$./getopt �Cc
//other option:c
//$./getopt �Ca
//other option :?
//$./getopt �Ca12345
//option a:��12345��
// 
//�� 
//
// 
//
// 
//isatty���ж��ļ��������Ƿ���Ϊ�ն˻���  
//��غ���  ttyname
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  int isatty(int desc);
// 
//����˵��  �������desc��������ļ�������Ϊһ�ն˻��򷵻�1�����򷵻�0��
// 
//����ֵ  ����ļ�Ϊ�ն˻��򷵻�1�����򷵻�0��
// 
//����  �ο�ttyname()��
// 
//�� 
//
// 
//
// 
//select��I/O�๤���ƣ�  
//��ͷ�ļ�  #include<sys/time.h>
//#include<sys/types.h>
//#include<unistd.h>
// 
  int select(int n,fd_set * readfds,fd_set * writefds,fd_set * exceptfds,struct timeval * timeout);
// 
//����˵��  select()�����ȴ��ļ�������״̬�ĸı䡣����n���������ļ������ʼ�1������readfds��writefds ��exceptfds ��Ϊ�������飬�������ش��������ʵĶ���д�������״�������µĺ��ṩ�˴�����������������ķ�ʽ:
//FD_CLR(inr fd,fd_set* set)�����������������set�����fd ��λ
//FD_ISSET(int fd,fd_set *set)������������������set�����fd ��λ�Ƿ�Ϊ��
//FD_SET��int fd,fd_set*set��������������������set�����fd��λ
//FD_ZERO��fd_set *set���� ���������������set��ȫ��λ
// 
//����  timeoutΪ�ṹtimeval����������select()�ĵȴ�ʱ�䣬��ṹ��������
//struct timeval
//{
//time_t tv_sec;
//time_t tv_usec;
//};
// 
//����ֵ  �������timeout��ΪNULL���ʾselect����û��timeout��
// 
//�������  ִ�гɹ��򷵻��ļ�������״̬�Ѹı�ĸ������������0������������״̬�ı�ǰ�ѳ���timeoutʱ�䣬���д�����ʱ�򷵻�-1������ԭ�����errno����ʱ����readfds��writefds��exceptfds��timeout��ֵ��ɲ���Ԥ�⡣
//EBADF �ļ�������Ϊ��Ч�Ļ���ļ��ѹر�
//EINTR �˵��ñ��ź����ж�
//EINVAL ����n Ϊ��ֵ��
//ENOMEM �����ڴ治��
// 
//����  �����ĳ���Ƭ��:fs_set readset��
//FD_ZERO(&readset);
//FD_SET(fd,&readset);
//select(fd+1,&readset,NULL,NULL,NULL);
//if(FD_ISSET(fd,readset){����}
// 
//�� 
//
// 
//
// 
//ttyname������һ�ն˻����ƣ�  
//��غ���  Isatty
// 
//��ͷ�ļ�  #include<unistd.h>
// 
  char * ttyname(int desc);
// 
//����˵��  �������desc��������ļ�������Ϊһ�ն˻�����Ὣ���ն˻�������һ�ַ���ָ�뷵�أ����򷵻�NULL��
// 
//����ֵ  ����ɹ��򷵻�ָ���ն˻����Ƶ��ַ���ָ�룬�д����������ʱ�򷵻�NULL��
// 
//����  #include<unistd.h>
//#include<sys/types.h>
//#include <sys/stat.h>
//#include<fcntl.h>
//main()
//{
//int fd;
//char * file = ��/dev/tty��;
//fd = open (fiel,O_RDONLY);
//printf(��%s��,file);
//if(isatty(fd)){
//printf(��is a tty.\n��);
//printf(��ttyname = %s \n��,ttyname(fd));
//}
//else printf(�� is not a tty\n��);
//close(fd);
//}
// 
//ִ��  /dev/tty is a tty
//ttyname = /dev/tty
// 
//�� 
//
// 
//
