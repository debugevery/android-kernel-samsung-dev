// Linux MMC/SD/SDIO��ϵ�ṹ                                                                                                                                                                                                                                                                     
// [���ڣ�2011-03-12] ��Դ��Linux����  ���ߣ�yuanyou                                                                                                                                                                                                                                             
// �й�MMC/SD/SDIO��ص�֪ʶ����Ͳ��ི�ˣ���ο�������ϡ�������Ҫ�漰Linux��MMC������ݡ�                                                                                                                                                                                                     
// �ں˰汾(2.6.36)                                                                                                                                                                                                                                                                              
// ����˵һ��Linux���MMC�Ĵ���ֲ�����Ҫ������Ŀ¼��һ��ͷ�ļ�Ŀ¼��һ��Դ����Ŀ¼��                                                                                                                                                                                                            
// �ֱ�λ�����£�                                                                                                                                                                                                                                                                                
// include/linux/mmc                                                                                                                                                                                                                                                                             
// drivers/mmc                                                                                                                                                                                                                                                                                   
// Ҫ�Ķ�MMC��ش���ͱ���Ҫ��������Ŀ¼����drivers/mmcĿ¼�·ֱ���������Ŀ¼���佫��Ӧ������Ҫ����MMC����ϵ�ṹ����������Ŀ¼�ֱ�Ϊ��                                                                                                                                                           
//                                                                                                                                                                                                                                                                                               
//  card                                                                                                                                                                                                                                                                                         
//  core                                                                                                                                                                                                                                                                                         
//  host                                                                                                                                                                                                                                                                                         
//                                                                                                                                                                                                                                                                                               
// ���ǵ����ݺ��潲����ϵ�ṹʱ��Ȼ�������ˡ�                                                                                                                                                                                                                                                    
//  ������˵˵MMC����ϵ�ṹ�����Ϊ����                                                                                                                                                                                                                                                          
//                                                                                                                                                                                                                                                                                               
//         /dev���豸�ļ�����MMC/SD/SDIO                                                                                                                                                                                                                                                         
// �û��ռ�             |                                                                                                                                                                                                                                                                        
// ---------------------|-----------------------------------------------------                                                                                                                                                                                                                   
// �ں˿ռ�            \ /                                                                                                                                                                                                                                                                       
//          MMC Card��(��Ӧ������豸��������MMC/SD�����豸������SDIO UART)                                                                                                                                                                                                                      
//                      |                                                                                                                                                                                                                                                                        
//                     \ /                                                                                                                                                                                                                                                                       
//           MMC core��(Ϊ�ϴ��豸����ʵ���ṩ�����ӿڣ����²�hostע���ṩ����)                                                                                                                                                                                                                  
//                      |                                                                                                                                                                                                                                                                        
//                     \ /                                                                                                                                                                                                                                                                       
//            Host��(����MMC/SD/SDIO�����������㡣��S3C2440 MMC/SD����������)                                                                                                                                                                                                                    
//                      |                                                                                                                                                                                                                                                                        
//                     \ /                                                                                                                                                                                                                                                                       
// -----------------------------------------------------------------------------                                                                                                                                                                                                                 
//                     Ӳ����                                                                                                                                                                                                                                                                    
//                                                                                                                                                                                                                                                                                               
// ����������˵����дMMC/SD�����������Ҫ�漰�ľ���Host�㣬����㲻�ÿ��ǡ�
// ����SDIO�豸����Host�����⣬���п���Ҫ��дMMC Card����豸������ 

// ��дHost����������Ҫ�����mmc_host�ṹ��������ݺ�ʵ��mmc_host_ops�ṹ���еĺ�����
// ������mmc_add_host��MMC coreע��host���������Բο�S3C24XX��HOST������
// ��(drivers/mmc/host/s3cmci.c,s3cmci.h),�ϲ�MMC Core��Ҫ����mmc_host_ops�е�
// ������ʵ����Ӳ��������������mmc_host_ops�ṹ������ĺ�����
  struct mmc_host_ops {                                                                                                                                                                                                                                                                       
    //ʹ�ܺͽ�ֹHOST������                                                                                                                                                                                                                                                                  
    int (*enable)(struct mmc_host *host);                                                                                                                                                                                                                                                     
    int (*disable)(struct mmc_host *host, int lazy);                                                                                                                                                                                                                                          
        //����ǹؼ��ĺ��������ж�MMC/SD�Ĳ���������������Ͷ����ݣ���ͨ���ýӿ���ʵ�֣�
        //����ʵ�ָýӿ�ʱҪ��������������ݲ���������Ҫ�����Ƿ�ʹ��DMA���������ݴ��䡣                                                                                                                     
    void    (*request)(struct mmc_host *host, struct mmc_request *req);                                                                                                                                                                                                                       
        //��������MMC/SD��ʱ�ӣ���ѹ�Ȳ���                                                                                                                                                                                                                                                  
    void    (*set_ios)(struct mmc_host *host, struct mmc_ios *ios);                                                                                                                                                                                                                           
        //���MMC/SD�Ƿ�д������                                                                                                                                                                                                                                                            
    int    (*get_ro)(struct mmc_host *host);                                                                                                                                                                                                                                                  
        //���mmc/sd�Ĳ���Ͱγ�                                                                                                                                                                                                                                                            
    int    (*get_cd)(struct mmc_host *host);                                                                                                                                                                                                                                                  
    void    (*enable_sdio_irq)(struct mmc_host *host, int enable);                                                                                                                                                                                                                            
    // optional callback for HC quirks                                                                                                                                                                                                                                                      
    void    (*init_card)(struct mmc_host *host, struct mmc_card *card);                                                                                                                                                                                                                       
};                                                                                                                                                                                                                                                                                            
//===============================================================================
// ������˵˵MMC Core�㡣
// �ò���Ҫʵ���˼����ṹ�庯��ָ�룬������������MMC�豸����ģ�͡������ǣ�
struct bus_type mmc_bus_type  //mmc���ߣ���������sd/mmc���豸������ 
struct mmc_bus_ops mmc_ops    //MMC�����߲�����������Ҫ���ڵ�Դ������

struct mmc_bus_ops mmc_sd_ops  //SD�����߲�����������Ҫ���ڵ�Դ������

struct mmc_bus_ops mmc_sdio_ops  //SDIO���߲�����������Ҫ���ڵ�Դ������
struct bus_type sdio_bus_type  //SDIO���ⶨ����һ������

// core.c�ļ���ʵ���˼����ؼ��ĺ����������ṩ���ϲ�MMC Card���úͶ�SD/MMC������⺯���Լ���ʼ����
// �����ϲ�MMC Card������Ҫ�У�
void mmc_wait_for_req(struct mmc_host *host, struct mmc_request *mrq);
 int mmc_wait_for_cmd(struct mmc_host *host, struct mmc_command *cmd, int retries);
// mmc card�����ͨ����Щ����������mmc/sd��������Щ�������յ��õ���mmc_host_ops �ṹ���е�request������
//���о���Ĳ�����
// 
// ��SD/MMC������⺯���Լ���ʼ������Ҫʵ����
void mmc_rescan(struct work_struct *work);// �����С�
// host���ڵ���mmc_add_hostʱ�������ú����ĵ��ã����/��ʼ��˳��Ϊ��

// ��SDIO�ӿ�
  //
     * First we search for SDIO...
     
    err = mmc_send_io_op_cond(host, 0, &ocr);
    if (!err) {
        if (mmc_attach_sdio(host, ocr)) {
   ...

//��SD:
//  //
     * ...then normal SD...
     
    err = mmc_send_app_op_cond(host, 0, &ocr);
    if (!err) {
        if (mmc_attach_sd(host, ocr))

//�����MMC��
 //
     * ...and finally MMC.
     
    err = mmc_send_op_cond(host, 0, &ocr);
    if (!err) {
        if (mmc_attach_mmc(host, ocr))
//
//����mmc_attach_xxx������������������ͳ�ʼ���ģ�ѡ����Ӧ�����߲���������������struct mmc_card�ṹ�壬
//����������ݣ����ע��һ��mmc_card(������һ���豸)������ע������mmc_bus_type�ṹ���match��probe����
//�����ҵ��ʺϸ��豸������(�����ǣ�浽�豸����ģ�ͣ����Բ鿴�豸����ģ��������ݣ��˽��豸������ƥ���
//����)�����ｫƥ�䵽mmc card���MMC_Block(MMC���豸���������� struct mmc_driver����)��������豸���
//�ͳ�ʼ���Ժ��Ժ�Ĳ�������mmc card������ص��豸�������򷢳����ˡ�
//===============================================================================
//��˵˵MMC card�㣬�ò���Ҫʵ�־�����豸����������MMC���豸��������ͨ��mmc_register_driverע�ᡣ
//�����SDIO���п����������ַ��豸���������ˣ���ͨ������sdio_register_driver��ע���豸������
//
//���������˵��
//host���ṩ�������MMC/SD/SDIO�������Ĺ��ܡ�
//Core���ṩ�˾���MMC/SD/SDIO�豸���ͳ�ʼ�����ܣ��Լ���Դ����������ݺ�ͨ�õĲ������ܡ�
//CardΪʵ�־�����豸�����㡣
//�����ķֲ�ṹ��Linux�豸�����зǳ���������I2C,SPI�ȶ��ṩ������������ģ�͡�
//
//===============================================================================
//����˵˵SDIO��ز��֡���core��ע�����µ�sdio_bus_type���ߣ����Ҷ������µ�sdio_driver������sdio�豸
//��������������struct sdio_func�������豸��������SDIO�豸����struct mmc_card�������豸���⣬
//����struct sdio_func��������幦���豸��������mmc_attach_sdio�����г���ע��mmc_card���⣬��ע��
//��sdio_func������������£�
int mmc_attach_sdio(struct mmc_host *host, u32 ocr);
{
   ....
  //
     * First add the card to the driver model...
     
    err = mmc_add_card(host->card);
    if (err)
        goto remove_added;

    //
     * ...then the SDIO functions.
     
    for (i = 0;i < funcs;i++) {
        err = sdio_add_func(host->card->sdio_func[i]);
        if (err)
            goto remove_added;
    }
    ....
}
//���������˵���mmc_bus_type�ṹ���match��probe���������ҵ��ʺϸ��豸�������⣬Ҳ����sdio_bus_type�ṹ��
//��match��probe���������ҵ��ʺϸ��豸��������


// =================================================================================================
// SD/MMC/SDIO �������ָ�Ҫ (2010-01-13 13:58)                                                                                                                                                                                                   
// ���ࣺ Linux����                                                                                                                                                                                                                              
// SD��Secure Digital���� MMC��Multimedia Card��                                                                                                                                                                                                 
//                                                                                                                                                                                                                                               
// SD ��һ�� flash memory card �ı�׼��Ҳ����һ�㳣���� SD ���俨���� MMC ���ǽ����һ�ּ��俨��׼��Ŀǰ�Ѿ��� SD ��׼��ȡ������ά���ٿ������൱��ϸ�� SD/MMC ���˵����[http://zh.wikipedia.org/wiki/Secure_Digital]��                          
//                                                                                                                                                                                                                                               
// SDIO��Secure Digital I/O��                                                                                                                                                                                                                    
//                                                                                                                                                                                                                                               
// SDIO ��Ŀǰ���ǱȽϹ��ĵļ�����SDIO ����˼�壬���� SD �� I/O �ӿڣ�interface������˼�������������Ϳ��ܻ��е���񡣸������˵����SD �����Ǽ��俨�ı�׼����������Ҳ���԰� SD ��������һЩ��Χ�ӿ�ʹ�ã������ļ������� SDIO��                    
//                                                                                                                                                                                                                                               
// ���� SDIO ������һ���൱�����ļ�����͸�� SD �� I/O �ӽ��������ⲿ��Χ������͸�� SD �ϵ� I/O ���ݽ�λ����Щ��Χ�������ݣ����� SD Э���ԱҲ�Ƴ��������� SDIO stack ��������ʹ�� SDIO ��Χ�����ǳ�Ϊ SDIO �����Ŀ�����Ӧ�ñ���൱���š�      
//                                                                                                                                                                                                                                               
// �����Ѿ��зǳ�����ֻ������ֳ�װ�ö�֧�� SDIO �Ĺ��ܣ�SD ��׼ԭ��������� mobile device ���ƶ������������ SDIO ��ΧҲ�����������������ֻ������Χ�������ף����ҿ����ϸ��е��ԣ�����Ҫ�ڽ���Χ����Ŀǰ������ SDIO ��Χ��SDIO �����У�         
//                                                                                                                                                                                                                                               
// Wi-Fi card���������翨��                                                                                                                                                                                                                      
// CMOS sensor card������ģ�飩                                                                                                                                                                                                                  
// GPS card                                                                                                                                                                                                                                      
// GSM/GPRS modem card                                                                                                                                                                                                                           
// Bluetooth card                                                                                                                                                                                                                                
// Radio/TV card���ܺ��棩                                                                                                                                                                                                                       
// SDIO ��Ӧ�ý���δ��Ƕ��ʽϵͳ����Ҫ�Ľӿڼ���֮һ������Ҳ��ȡ��Ŀǰ GPIO ʽ�� SPI �ӿڡ�                                                                                                                                                      
//                                                                                                                                                                                                                                               
// SD/SDIO �Ĵ���ģʽ                                                                                                                                                                                                                            
//                                                                                                                                                                                                                                               
// SD ����ģʽ������ 3 �֣�                                                                                                                                                                                                                      
//                                                                                                                                                                                                                                               
// SPI mode��required��                                                                                                                                                                                                                          
// 1-bit mode                                                                                                                                                                                                                                    
// 4-bit mode                                                                                                                                                                                                                                    
// SDIO ͬ��Ҳ֧������ 3 �ִ���ģʽ������ SD ��׼�����е� SD�����俨���� SDIO����Χ��������֧�� SPI mode����� SPI mode �ǡ�required�������⣬���ڵ� MMC ����ʹ�� SPI ���䣩Ҳ�ܽӵ� SD ���㣨SD slot��������ʹ�� SPI mode �� 1-bit mode ����ȡ��
//                                                                                                                                                                                                                                               
// SD �� MMC Mode                                                                                                                                                                                                                                
//                                                                                                                                                                                                                                               
// SD Ҳ�ܶ�ȡ MMC �ڴ棬��Ȼ MMC ��׼���ᵽ��MMC �ڴ治����Ҫ֧�� SPI mode������һ��Ҫ֧�� 1-bit mode���������������ܿ����� MMC ����ʵ����֧�� SPI mode����ˣ����ǿ��԰� SD �趨�� SPI mode �Ĵ��䷽ʽ����ȡ MMC ���俨��                      
//                                                                                                                                                                                                                                               
// SD �� MMC Mode ����������ȡ MMC ����һ�ִ���ģʽ��������SD �� MMC Mode ��ȻҲ��ʹ�� SPI mode�������������������в���ģ�                                                                                                                      
//                                                                                                                                                                                                                                               
// MMC �� SPI mode ���������Ϊ 20 Mbit/s��                                                                                                                                                                                                    
// SD �� SPI mode ���������Ϊ 25 Mbit/s��                                                                                                                                                                                                     
// Ϊ�����������ʱҲ�� SPI/MMC mode �� SPI/SD mode ��д�������������                                                                                                                                                                         
//                                                                                                                                                                                                                                               
