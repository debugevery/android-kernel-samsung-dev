///*MTDԭʼ�豸��FLASHӲ�������ĶԻ� 
//����<<Linux MTDԴ�������>>�����MTD�ķֲ�ṹ�Լ�����ķֹ�������˴��µ��˽⣬Ȼ������֮������ν��жԻ����أ�����������⣬<<Linux MTDԴ�������>>��û����ϸ��ȥ˵����
//С�ܳ���о���һ�£�������µ��ϣ��ڴ��ϵ��£��������������о�һ��MTDԭʼ�豸��FLASHӲ�������ĶԻ�(MTDԭʼ�豸����ϲ�ĶԻ������Ժ����о�)��
//�����ǵ�һ���֣����µ��ϵĽ���FLASHӲ��������MTDԭʼ�豸����ν�����ϵ�ġ�
//��1�����ȴ���ں�����ʼ

//=======================��ע�͹ۿ�   /*=================================

static int s3c24xx_nand_probe(struct device *dev, int is_s3c2440)
{
    struct platform_device *pdev = to_platform_device(dev);
    struct s3c2410_platform_nand *plat = to_nand_plat(dev);
    //��ȡnand flash�����ýṹ������(dev.c�ж��壬��ϸ����¼����)
    struct s3c2410_nand_info *info;
    struct s3c2410_nand_mtd *nmtd;
    struct s3c2410_nand_set *sets;
    struct resource *res;
    int err = 0;
    int size;
    int nr_sets;
    int setno;

    pr_debug("s3c2410_nand_probe(%p)\n", dev);

    info = kmalloc(sizeof(*info), GFP_KERNEL);
    if (info == NULL) {
        printk(KERN_ERR PFX "no memory for flash info\n");
        err = -ENOMEM;
        goto exit_error;
    }

    memzero(info, sizeof(*info));
    dev_set_drvdata(dev, info);                  //�Ժ�����

    spin_lock_init(&info->controller.lock);      //��ʼ��������
    init_waitqueue_head(&info->controller.wq);   //��ʼ���ȴ�����

    // get the clock source and enable it 

    info->clk = clk_get(dev, "nand");
    if (IS_ERR(info->clk)) {
        printk(KERN_ERR PFX "failed to get clock");
        err = -ENOENT;
        goto exit_error;
    }

    clk_use(info->clk);
    clk_enable(info->clk);

    // allocate and map the resource 

    // currently we assume we have the one resource 
    res  = pdev->resource;                        //��ȡdev.c�ж�������豸��ص���Դ
    size = res->end - res->start + 1;

    info->area = request_mem_region(res->start, size, pdev->name);

    if (info->area == NULL) {
        printk(KERN_ERR PFX "cannot reserve register region\n");
        err = -ENOENT;
        goto exit_error;
    }

    info->device     = dev;
    info->platform   = plat;                     //�����struct s3c2410_platform_nand�ṹ����
    info->regs       = ioremap(res->start, size);//ӳ��nand flash�õ��ļĴ���
    info->is_s3c2440 = is_s3c2440;               

    if (info->regs == NULL) {
        printk(KERN_ERR PFX "cannot reserve register region\n");
        err = -EIO;
        goto exit_error;
    }        

    printk(KERN_INFO PFX "mapped registers at %p\n", info->regs);

    // initialise the hardware 

    err = s3c2410_nand_inithw(info, dev);
    //��ʼ��s3c2410 nand flash���ƣ���Ҫ������S3C2410_NFCONF�Ĵ���
    if (err != 0)
        goto exit_error;

    sets = (plat != NULL) ? plat->sets : NULL;   
    nr_sets = (plat != NULL) ? plat->nr_sets : 1;
   
    info->mtd_count = nr_sets;
    //�ҵİ���ֻ��һ��nand flash��������Ϣ��plat-sets����ĿΪ1��

    // allocate our information 

    size = nr_sets * sizeof(*info->mtds);
    info->mtds = kmalloc(size, GFP_KERNEL);
    if (info->mtds == NULL) {
        printk(KERN_ERR PFX "failed to allocate mtd storage\n");
        err = -ENOMEM;
        goto exit_error;
    }

    memzero(info->mtds, size);

    // initialise all possible chips 

    nmtd = info->mtds;

    for (setno = 0; setno < nr_sets; setno++, nmtd++) {
        pr_debug("initialising set %d (%p, info %p)\n",
             setno, nmtd, info);
        
        s3c2410_nand_init_chip(info, nmtd, sets);

        nmtd->scan_res = nand_scan(&nmtd->mtd,
                       (sets) ? sets->nr_chips : 1);//Ϊʲôʹ��set->nr_chips(��û���õĶ���)��

        if (nmtd->scan_res == 0) {
            s3c2410_nand_add_partition(info, nmtd, sets);
        }

        if (sets != NULL)
            sets++;
    }
    
    pr_debug("initialised ok\n");
    return 0;

 exit_error:
    s3c2410_nand_remove(dev);

    if (err == 0)
        err = -EINVAL;
    return err;
}

//��ʼ������һƬflash��struct nand_chip�ṹ

static void s3c2410_nand_init_chip(struct s3c2410_nand_info *info,
                   struct s3c2410_nand_mtd *nmtd,
                   struct s3c2410_nand_set *set)
{
    struct nand_chip *chip = &nmtd->chip;

    chip->IO_ADDR_R       = info->regs + S3C2410_NFDATA;   //����ַ
    chip->IO_ADDR_W    = info->regs + S3C2410_NFDATA;      //д��ַ
    chip->hwcontrol    = s3c2410_nand_hwcontrol;   
    chip->dev_ready    = s3c2410_nand_devready;            //ready״̬��ѯ
    chip->write_buf    = s3c2410_nand_write_buf;           //д����
    chip->read_buf     = s3c2410_nand_read_buf;            //������
    chip->select_chip  = s3c2410_nand_select_chip;         //Ƭѡ����
    chip->chip_delay   = 50;
    chip->priv       = nmtd;
    chip->options       = 0;
    chip->controller   = &info->controller;

    if (info->is_s3c2440) {
        chip->IO_ADDR_R     = info->regs + S3C2440_NFDATA;
        chip->IO_ADDR_W  = info->regs + S3C2440_NFDATA;
        chip->hwcontrol  = s3c2440_nand_hwcontrol;
    }

    nmtd->info       = info;
    nmtd->mtd.priv       = chip;            
    //nand_scan�����л����struct nand_chip *this = mtd->privȡ����struct nand_chip�ṹ
    nmtd->set       = set;

    if (hardware_ecc) {
        chip->correct_data  = s3c2410_nand_correct_data;
        chip->enable_hwecc  = s3c2410_nand_enable_hwecc;
        chip->calculate_ecc = s3c2410_nand_calculate_ecc;
        chip->eccmode        = NAND_ECC_HW3_512;
        chip->autooob       = &nand_hw_eccoob;

        if (info->is_s3c2440) {
            chip->enable_hwecc  = s3c2440_nand_enable_hwecc;
            chip->calculate_ecc = s3c2440_nand_calculate_ecc;
        }
    } else {                                 
        chip->eccmode        = NAND_ECC_SOFT;         //ECC������
        }
}

// command and control functions 
// *
// * Note, these all use tglx's method of changing the IO_ADDR_W field
// * to make the code simpler, and use the nand layer's code to issue the
// * command and address sequences via the proper IO ports.
// *


static void s3c2410_nand_hwcontrol(struct mtd_info *mtd, int cmd)
{
    struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
    struct nand_chip *chip = mtd->priv;

    switch (cmd) {
    case NAND_CTL_SETNCE:
    case NAND_CTL_CLRNCE:
        printk(KERN_ERR "%s: called for NCE\n", __FUNCTION__);
        break;

    case NAND_CTL_SETCLE:
        chip->IO_ADDR_W = info->regs + S3C2410_NFCMD;//д����
        break;

    case NAND_CTL_SETALE:
        chip->IO_ADDR_W = info->regs + S3C2410_NFADDR;//д��ַ
        break;

        // NAND_CTL_CLRCLE: 
        // NAND_CTL_CLRALE: 
    default:
        chip->IO_ADDR_W = info->regs + S3C2410_NFDATA;//д����
        break;
    }
}

// s3c2410_nand_devready()
 *
 * returns 0 if the nand is busy, 1 if it is ready


static int s3c2410_nand_devready(struct mtd_info *mtd)
{
    struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
    
    if (info->is_s3c2440)
        return readb(info->regs + S3C2440_NFSTAT) & S3C2440_NFSTAT_READY;
    return readb(info->regs + S3C2410_NFSTAT) & S3C2410_NFSTAT_BUSY;//����nand flash��æ��־
}

static void s3c2410_nand_write_buf(struct mtd_info *mtd,
                   const u_char *buf, int len)
{
    struct nand_chip *this = mtd->priv;
    writesb(this->IO_ADDR_W, buf, len);//д����
}

static void s3c2410_nand_read_buf(struct mtd_info *mtd, u_char *buf, int len)
{
    struct nand_chip *this = mtd->priv;
    readsb(this->IO_ADDR_R, buf, len);//������
}

// select chip 
// 
// * ����chip��ֵ����nand flash��Ƭѡ�ź�:
// * chip = -1 -- ����nand flash
// * chip !=-1 -- ѡ���Ӧ��nand flash
 
static void s3c2410_nand_select_chip(struct mtd_info *mtd, int chip)
{
    struct s3c2410_nand_info *info;
    struct s3c2410_nand_mtd *nmtd; 
    struct nand_chip *this = mtd->priv;
    void __iomem *reg;
    unsigned long cur;
    unsigned long bit;

    nmtd = this->priv;
    info = nmtd->info;

    bit = (info->is_s3c2440) ? S3C2440_NFCONT_nFCE : S3C2410_NFCONF_nFCE;
    reg = info->regs+((info->is_s3c2440) ? S3C2440_NFCONT:S3C2410_NFCONF);

    cur = readl(reg);

    if (chip == -1) {
        cur |= bit;
    } else {
        if (nmtd->set != NULL && chip > nmtd->set->nr_chips) {
            printk(KERN_ERR PFX "chip %d out of range\n", chip);
            return;
        }

        if (info->platform != NULL) {
            if (info->platform->select_chip != NULL)
                (info->platform->select_chip)(nmtd->set, chip);
        }

        cur &= ~bit;
    }

    writel(cur, reg);
}


ע��
    s3c2410_nand_init_chip���struct nand_chip��һ���ֳ�Ա��nand_scan��ͨ��nand flash�ı�׼���м�⣬�����struct nand_chip��������Ա����Ҫʱ���ݼ��������ȡ�ᡣ

int nand_scan (struct mtd_info *mtd, int maxchips)
{
    int i, nand_maf_id, nand_dev_id, busw, maf_id;
    struct nand_chip *this = mtd->priv;          //ȡ��struct nand_chip�ṹ

    // Get buswidth to select the correct functions
    busw = this->options & NAND_BUSWIDTH_16;     //nand flash��λ��

    // check for proper chip_delay setup, set 20us if not 
    if (!this->chip_delay)                     
        this->chip_delay = 20;

    // check, if a user supplied command function given 
    if (this->cmdfunc == NULL)                  //��������
        this->cmdfunc = nand_command;

    // check, if a user supplied wait function given 
    if (this->waitfunc == NULL)                  //���ȴ�����
        this->waitfunc = nand_wait;

    if (!this->select_chip)                      //s3c2410_nand_init_chip���Ѷ���
        this->select_chip = nand_select_chip;
    if (!this->write_byte)                       //ʹ��Ĭ�ϵ�
        this->write_byte = busw ? nand_write_byte16 : nand_write_byte;
    if (!this->read_byte)                        //ʹ��Ĭ�ϵ�
        this->read_byte = busw ? nand_read_byte16 : nand_read_byte;
    if (!this->write_word)                       //ʹ��Ĭ�ϵ�
        this->write_word = nand_write_word;
    if (!this->read_word)                        //ʹ��Ĭ�ϵ�
        this->read_word = nand_read_word;
    if (!this->block_bad)                        //ʹ��Ĭ�ϵ�
        this->block_bad = nand_block_bad;
    if (!this->block_markbad)                    //ʹ��Ĭ�ϵ�
        this->block_markbad = nand_default_block_markbad;
    if (!this->write_buf)                        //s3c2410_nand_init_chip���Ѷ���
        this->write_buf = busw ? nand_write_buf16 : nand_write_buf;
    if (!this->read_buf)                         //s3c2410_nand_init_chip���Ѷ���
        this->read_buf = busw ? nand_read_buf16 : nand_read_buf;
    if (!this->verify_buf)                       //ʹ��Ĭ�ϵ�
        this->verify_buf = busw ? nand_verify_buf16 : nand_verify_buf;
    if (!this->scan_bbt)                         //ʹ��Ĭ�ϵ�
        this->scan_bbt = nand_default_bbt;

    // Select the device 
    this->select_chip(mtd, 0);       //Ƭѡ����ϧ��s3c2410 nand flash�������д˲���Ϊ��

    // Send the command for reading device ID 
    this->cmdfunc (mtd, NAND_CMD_READID, 0x00, -1);//���Ͷ�ID����

    // Read manufacturer and device IDs 
    nand_maf_id = this->read_byte(mtd);            //��ȡ������ID
    nand_dev_id = this->read_byte(mtd);            //��ȡ�豸ID

    // Print and store flash device information 
    for (i = 0; nand_flash_ids[i].name != NULL; i++) {   
//������nand flash���ϵ�nand_flash_ids����include/linux/mtd/nand_ids.c�ļ��У���ϸ����¼
                
        if (nand_dev_id != nand_flash_ids[i].id)    //�Ƚ��豸ID 
            continue;

        if (!mtd->name) mtd->name = nand_flash_ids[i].name;   //����豸��
        this->chipsize = nand_flash_ids[i].chipsize << 20;    //����豸��С
        
        // New devices have all the information in additional id bytes 
        if (!nand_flash_ids[i].pagesize) {
            int extid;
            // The 3rd id byte contains non relevant data ATM 
            extid = this->read_byte(mtd);
            // The 4th id byte is the important one 
            extid = this->read_byte(mtd);
            // Calc pagesize 
            mtd->oobblock = 1024 << (extid & 0x3);
            extid >>= 2;
            // Calc oobsize 
            mtd->oobsize = (8 << (extid & 0x03)) * (mtd->oobblock / 512);
            extid >>= 2;
            // Calc blocksize. Blocksize is multiples of 64KiB 
            mtd->erasesize = (64 * 1024)  << (extid & 0x03);
            extid >>= 2;
            // Get buswidth information 
            busw = (extid & 0x01) ? NAND_BUSWIDTH_16 : 0;
        
        } else {
            // Old devices have this data hardcoded in the
             * device id table 
            mtd->erasesize = nand_flash_ids[i].erasesize;   //����߳���Ԫ��С(16k)
            mtd->oobblock = nand_flash_ids[i].pagesize;     //���ҳ��С(512)
            mtd->oobsize = mtd->oobblock / 32;              //oob��С(512/32=16)
            busw = nand_flash_ids[i].options & NAND_BUSWIDTH_16;//��ȡnand flash���ж����λ��
        }

        // Try to identify manufacturer             //�Ƚ�������ID
        for (maf_id = 0; nand_manuf_ids[maf_id].id != 0x0; maf_id++) {
            if (nand_manuf_ids[maf_id].id == nand_maf_id)
                break;
        }

        // Check, if buswidth is correct. Hardware drivers should set
         * this correct ! 
        /�û������λ����оƬʵ�ʵ�λ��һ�£�ȡ��nand flash��Ƭѡ
        if (busw != (this->options & NAND_BUSWIDTH_16)) {    
            printk (KERN_INFO "NAND device: Manufacturer ID:"
                " 0x%02x, Chip ID: 0x%02x (%s %s)\n", nand_maf_id, nand_dev_id, 
                nand_manuf_ids[maf_id].name , mtd->name);
            printk (KERN_WARNING 
                "NAND bus width %d instead %d bit\n", 
                    (this->options & NAND_BUSWIDTH_16) ? 16 : 8,
                    busw ? 16 : 8);
            this->select_chip(mtd, -1);//��s3c2410 nand flash�����������У��˲���Ϊ�ղ���
            return 1;    
        }
        
        // Calculate the address shift from the page size  
        //����ҳ�����߳���Ԫ��nand flash��С��ƫ��ֵ  
        this->page_shift = ffs(mtd->oobblock) - 1;
        this->bbt_erase_shift = this->phys_erase_shift = ffs(mtd->erasesize) - 1;
        this->chip_shift = ffs(this->chipsize) - 1;

        // Set the bad block position 
        //��ע��nand flashΪ��ҳ����Сҳ��
        this->badblockpos = mtd->oobblock > 512 ? 
            NAND_LARGE_BADBLOCK_POS : NAND_SMALL_BADBLOCK_POS;

        // Get chip options, preserve non chip based options 
        //�û�ûָ����ѡ���nand flash���л�ȡ����
        this->options &= ~NAND_CHIPOPTIONS_MSK;
        this->options |= nand_flash_ids[i].options & NAND_CHIPOPTIONS_MSK;
        // Set this as a default. Board drivers can override it, if neccecary 
        this->options |= NAND_NO_AUTOINCR;
        // Check if this is a not a samsung device. Do not clear the options
         * for chips which are not having an extended id.
             
        if (nand_maf_id != NAND_MFR_SAMSUNG && !nand_flash_ids[i].pagesize)
            this->options &= ~NAND_SAMSUNG_LP_OPTIONS;
        
        // Check for AND chips with 4 page planes 
        if (this->options & NAND_4PAGE_ARRAY)
            this->erase_cmd = multi_erase_cmd;
        else
            this->erase_cmd = single_erase_cmd;      

        // Do not replace user supplied command function ! 
        if (mtd->oobblock > 512 && this->cmdfunc == nand_command)
            this->cmdfunc = nand_command_lp;
                
        printk (KERN_INFO "NAND device: Manufacturer ID:"
            " 0x%02x, Chip ID: 0x%02x (%s %s)\n", nand_maf_id, nand_dev_id, 
            nand_manuf_ids[maf_id].name , nand_flash_ids[i].name);
        break;
    }//�õģ�������^_^

    if (!nand_flash_ids[i].name) {      
        printk (KERN_WARNING "No NAND device found!!!\n");
        this->select_chip(mtd, -1);
        return 1;
    }

    //ͳ��һ��ͬ�����͵�nand flash�ж��ٿ�(�Ұ���ֻ��һ��)
    for (i=1; i < maxchips; i++) {
        this->select_chip(mtd, i);

        // Send the command for reading device ID 
        this->cmdfunc (mtd, NAND_CMD_READID, 0x00, -1);

        // Read manufacturer and device IDs 
        if (nand_maf_id != this->read_byte(mtd) ||
            nand_dev_id != this->read_byte(mtd))
            break;
    }
    if (i > 1)
        printk(KERN_INFO "%d NAND chips detected\n", i);
    
    // Allocate buffers, if neccecary 
    if (!this->oob_buf) {
        size_t len;
        //���һ���߳���Ԫ64K��oob��ռ�õ��ܿռ�
        len = mtd->oobsize << (this->phys_erase_shift - this->page_shift);
        this->oob_buf = kmalloc (len, GFP_KERNEL);
        if (!this->oob_buf) {
            printk (KERN_ERR "nand_scan(): Cannot allocate oob_buf\n");
            return -ENOMEM;
        }
        this->options |= NAND_OOBBUF_ALLOC;//oob�ռ��ѷ��䣬����Ӧ�ı�־λ
    }
    
    if (!this->data_buf) {
        size_t len;
        len = mtd->oobblock + mtd->oobsize;//512+16=128
        this->data_buf = kmalloc (len, GFP_KERNEL);
        if (!this->data_buf) {
            if (this->options & NAND_OOBBUF_ALLOC)
                kfree (this->oob_buf);
            printk (KERN_ERR "nand_scan(): Cannot allocate data_buf\n");
            return -ENOMEM;
        }
        this->options |= NAND_DATABUF_ALLOC;//���ݿռ��ѷ��䣬����Ӧ�ı�־λ
    }

    // Store the number of chips and calc total size for mtd 
    this->numchips = i;//��¼nand flashƬ��
    mtd->size = i * this->chipsize;//�����nand flash�ܴ�С
    // Convert chipsize to number of pages per chip -1. 
    this->pagemask = (this->chipsize >> this->page_shift) - 1;//(64M>>9)-1=128k-1=0x1ffff

    // Preset the internal oob buffer 
    //oob_bufȫ����Ϊ0xff
    memset(this->oob_buf, 0xff, mtd->oobsize << (this->phys_erase_shift - this->page_shift));

    // If no default placement scheme is given, select an * appropriate one 
    if (!this->autooob) {   //����ѡ�õ���NAND_ECC_SOFT��autooobδ����
        // Select the appropriate default oob placement scheme for placement agnostic filesystems 
        switch (mtd->oobsize) { 
        case 8:
            this->autooob = &nand_oob_8;
            break;
        case 16:
            this->autooob = &nand_oob_16;//���ǵ�nand flash������һ��
            break;
        case 64:
            this->autooob = &nand_oob_64;
            break;
        default:
            printk (KERN_WARNING "No oob scheme defined for oobsize %d\n",
                mtd->oobsize);
            BUG();
        }
    }
//ע��
//    ECC�Ķ������Ǻܶ���������^_^   


    // The number of bytes available for the filesystem to place fs dependend
    // * oob data 
    mtd->oobavail = 0;
    for (i = 0; this->autooob->oobfree[i][1]; i++)
        mtd->oobavail += this->autooob->oobfree[i][1];

    // 
    // * check ECC mode, default to software
    // * if 3byte/512byte hardware ECC is selected and we have 256 byte pagesize
    // * fallback to software ECC 
    
    this->eccsize = 256;    // set default eccsize     
    this->eccbytes = 3;

    switch (this->eccmode) {
    case NAND_ECC_HW12_2048:
        if (mtd->oobblock < 2048) {
            printk(KERN_WARNING "2048 byte HW ECC not possible on %d byte page size, fallback to SW ECC\n",
                   mtd->oobblock);
            this->eccmode = NAND_ECC_SOFT;
            this->calculate_ecc = nand_calculate_ecc;
            this->correct_data = nand_correct_data;
        } else
            this->eccsize = 2048;
        break;

    case NAND_ECC_HW3_512: 
    case NAND_ECC_HW6_512: 
    case NAND_ECC_HW8_512: 
        if (mtd->oobblock == 256) {
            printk (KERN_WARNING "512 byte HW ECC not possible on 256 Byte pagesize, fallback to SW ECC \n");
            this->eccmode = NAND_ECC_SOFT;
            this->calculate_ecc = nand_calculate_ecc;
            this->correct_data = nand_correct_data;
        } else 
            this->eccsize = 512; // set eccsize to 512 
        break;
            
    case NAND_ECC_HW3_256:
        break;
        
    case NAND_ECC_NONE: 
        printk (KERN_WARNING "NAND_ECC_NONE selected by board driver. This is not recommended !!\n");
        this->eccmode = NAND_ECC_NONE;
        break;

    case NAND_ECC_SOFT:    
        this->calculate_ecc = nand_calculate_ecc;
        this->correct_data = nand_correct_data;
        break;

    default:
        printk (KERN_WARNING "Invalid NAND_ECC_MODE %d\n", this->eccmode);
        BUG();    
    }    

    // Check hardware ecc function availability and adjust number of ecc bytes per 
    // * calculation step
    
    switch (this->eccmode) {
    case NAND_ECC_HW12_2048:
        this->eccbytes += 4;
    case NAND_ECC_HW8_512: 
        this->eccbytes += 2;
    case NAND_ECC_HW6_512: 
        this->eccbytes += 3;
    case NAND_ECC_HW3_512: 
    case NAND_ECC_HW3_256:
        if (this->calculate_ecc && this->correct_data && this->enable_hwecc)
            break;
        printk (KERN_WARNING "No ECC functions supplied, Hardware ECC not possible\n");
        BUG();    
    }
        
    mtd->eccsize = this->eccsize;
    
    // Set the number of read / write steps for one page to ensure ECC generation 
    switch (this->eccmode) {
    case NAND_ECC_HW12_2048:
        this->eccsteps = mtd->oobblock / 2048;
        break;
    case NAND_ECC_HW3_512:
    case NAND_ECC_HW6_512:
    case NAND_ECC_HW8_512:
        this->eccsteps = mtd->oobblock / 512;
        break;
    case NAND_ECC_HW3_256:
    case NAND_ECC_SOFT:    
        this->eccsteps = mtd->oobblock / 256;
        break;
        
    case NAND_ECC_NONE: 
        this->eccsteps = 1;
        break;
    }
    
    // Initialize state, waitqueue and spinlock 
    this->state = FL_READY;
    init_waitqueue_head (&this->wq);
    spin_lock_init (&this->chip_lock);

    // De-select the device 
    this->select_chip(mtd, -1);

    // Invalidate the pagebuffer reference 
    this->pagebuf = -1;

    // Fill in remaining MTD driver data 
    //���mtd�ṹ����������
    mtd->type = MTD_NANDFLASH;
    mtd->flags = MTD_CAP_NANDFLASH | MTD_ECC;
    mtd->ecctype = MTD_ECC_SW;
    mtd->erase = nand_erase;
    mtd->point = NULL;
    mtd->unpoint = NULL;
    mtd->read = nand_read;
    // nand_read->nand_do_read_ecc->read_buf->s3c2410_nand_read_buf 
    mtd->write = nand_write;
    // nand_write->nand_write_ecc->nand_write_page->write_buf->s3c2410_nand_write_buf 
    mtd->read_ecc = nand_read_ecc;
    mtd->write_ecc = nand_write_ecc;
    mtd->read_oob = nand_read_oob;
    mtd->write_oob = nand_write_oob;
    mtd->readv = NULL;
    mtd->writev = nand_writev;
    mtd->writev_ecc = nand_writev_ecc;
    mtd->sync = nand_sync;
    mtd->lock = NULL;
    mtd->unlock = NULL;
    mtd->suspend = NULL;
    mtd->resume = NULL;
    mtd->block_isbad = nand_block_isbad;
    mtd->block_markbad = nand_block_markbad;

    // and make the autooob the default one 
    memcpy(&mtd->oobinfo, this->autooob, sizeof(mtd->oobinfo));

    mtd->owner = THIS_MODULE;
    
    // Check, if we should skip the bad block table scan 
    if (this->options & NAND_SKIP_BBTSCAN)
        return 0;

    // Build bad block table 
    return this->scan_bbt (mtd);
}

//*
// * nand_command - [DEFAULT] Send command to NAND device
// * @mtd:    MTD device structure
// * @command:    the command to be sent
// * @column:    the column address for this command, -1 if none
// * @page_addr:    the page address for this command, -1 if none
// *
// * Send command to NAND device. This function is used for small page
// * devices (256/512 Bytes per page)
 
static void nand_command (struct mtd_info *mtd, unsigned command, int column, int page_addr)
{
    register struct nand_chip *this = mtd->priv;

    // Begin command latch cycle 
    this->hwcontrol(mtd, NAND_CTL_SETCLE);    //ѡ��д��S3C2410_NFCMD�Ĵ���
    //
     * Write out the command to the device.
     
    if (command == NAND_CMD_SEQIN) {
        int readcmd;

        if (column >= mtd->oobblock) {        //��/дλ�ó���512����oob_data
            // OOB area 
            column -= mtd->oobblock;
            readcmd = NAND_CMD_READOOB;
        } else if (column < 256) {            //��/дλ����ǰ512��ʹ��read0����
            // First 256 bytes --> READ0 
            readcmd = NAND_CMD_READ0;
        } else {                              //��/дλ���ں�512��ʹ��read1����
            column -= 256;
            readcmd = NAND_CMD_READ1;
        }
        this->write_byte(mtd, readcmd);        //д���������
    }
    this->write_byte(mtd, command);

    // Set ALE and clear CLE to start address cycle 
    // ���CLE�����������λALE����ʼ�����ַ 
    this->hwcontrol(mtd, NAND_CTL_CLRCLE);      //��������

    if (column != -1 || page_addr != -1) {
        this->hwcontrol(mtd, NAND_CTL_SETALE);  //ѡ��д��S3C2410_NFADDR�Ĵ���

        // Serially input address 
        if (column != -1) {
            // Adjust columns for 16 bit buswidth 
            if (this->options & NAND_BUSWIDTH_16)
                column >>= 1;
            this->write_byte(mtd, column);      //д���е�ַ
        }
        if (page_addr != -1) {                  //д��ҳ��ַ(�������ֽ�д��)
            this->write_byte(mtd, (unsigned char) (page_addr & 0xff));
            this->write_byte(mtd, (unsigned char) ((page_addr >> 8) & 0xff));
            // One more address cycle for devices > 32MiB 
            if (this->chipsize > (32 << 20))
                this->write_byte(mtd, (unsigned char) ((page_addr >> 16) & 0x0f));
        }
        // Latch in address 
        // �����ַ 
        this->hwcontrol(mtd, NAND_CTL_CLRALE);
    }

    // 
    // * program and erase have their own busy handlers 
    // * status and sequential in needs no delay
    
    switch (command) {
            
    case NAND_CMD_PAGEPROG:
    case NAND_CMD_ERASE1:
    case NAND_CMD_ERASE2:
    case NAND_CMD_SEQIN:
    case NAND_CMD_STATUS:
        return;

    case NAND_CMD_RESET:      //��λ����
                              // �ȴ�nand flash become ready
        if (this->dev_ready)  //�ж�nand flash �Ƿ�busy(1:ready 0:busy)
            break;
        udelay(this->chip_delay);
        this->hwcontrol(mtd, NAND_CTL_SETCLE);
        this->write_byte(mtd, NAND_CMD_STATUS);
        this->hwcontrol(mtd, NAND_CTL_CLRCLE);
        while ( !(this->read_byte(mtd) & NAND_STATUS_READY));
        return;

    // This applies to read commands     
    default:
        // 
        // * If we don't have access to the busy pin, we apply the given
         * command delay
        
        if (!this->dev_ready) {
            udelay (this->chip_delay);//�����ӳ�
            return;
        }    
    }
    // Apply this short delay always to ensure that we do wait tWB in
    // * any case on any machine. 
    ndelay (100);

    nand_wait_ready(mtd);
}


// 
// * Wait for the ready pin, after a command
// * The timeout is catched later.
 
static void nand_wait_ready(struct mtd_info *mtd)
{
    struct nand_chip *this = mtd->priv;
    unsigned long    timeo = jiffies + 2;

    // wait until command is processed or timeout occures 
    do {
        if (this->dev_ready(mtd))          //�򵥵���this->dev_ready(s3c2410_nand_devready)����                                             �ȴ�nand flash become ready
            return;
        touch_softlockup_watchdog();
    } while (time_before(jiffies, timeo));    
}

//*
// * nand_wait - [DEFAULT]  wait until the command is done
// * @mtd:    MTD device structure
// * @this:    NAND chip structure
// * @state:    state to select the max. timeout value
// *
// * Wait for command done. This applies to erase and program only
// * Erase can take up to 400ms and program up to 20ms according to 
// * general NAND and SmartMedia specs
// *

// �ȴ�֪���������ɣ��������߳���д������ 
static int nand_wait(struct mtd_info *mtd, struct nand_chip *this, int state)
{

    unsigned long    timeo = jiffies;
    int    status;
    
    if (state == FL_ERASING)
         timeo += (HZ * 400) / 1000;//�߳������Ļ���ʱ�����Ҫ��һЩ
    else
         timeo += (HZ * 20) / 1000;

    // Apply this short delay always to ensure that we do wait tWB in
     * any case on any machine. 
    ndelay (100);

    if ((state == FL_ERASING) && (this->options & NAND_IS_AND))
        this->cmdfunc (mtd, NAND_CMD_STATUS_MULTI, -1, -1);
    else    
        this->cmdfunc (mtd, NAND_CMD_STATUS, -1, -1);

    while (time_before(jiffies, timeo)) {        
        // Check, if we were interrupted 
        if (this->state != state)
            return 0;
        // �ȴ�nand flash become ready 
        if (this->dev_ready) {
            if (this->dev_ready(mtd))
                break;    
        } else {
            if (this->read_byte(mtd) & NAND_STATUS_READY)
                break;
        }
        cond_resched();
    }
    status = (int) this->read_byte(mtd);
    return status;
}

//*
// * nand_block_bad - [DEFAULT] Read bad block marker from the chip
// * ���nand flash��ĳһҳ�Ƿ�Ϊ����
// * @mtd:    MTD device structure
// * @ofs:    offset from device start
// * @getchip:    0, if the chip is already selected
// *
// * Check, if the block is bad. 
 
static int nand_block_bad(struct mtd_info *mtd, loff_t ofs, int getchip)
{
    int page, chipnr, res = 0;
    struct nand_chip *this = mtd->priv;
    u16 bad;

    if (getchip) {
        page = (int)(ofs >> this->page_shift);
        chipnr = (int)(ofs >> this->chip_shift);

        // Grab the lock and see if the device is available 
        nand_get_device (this, mtd, FL_READING);

        // Select the NAND device 
        this->select_chip(mtd, chipnr);
    } else 
        page = (int) ofs;    

    if (this->options & NAND_BUSWIDTH_16) {
        this->cmdfunc (mtd, NAND_CMD_READOOB, this->badblockpos & 0xFE, page & this->pagemask);
        bad = cpu_to_le16(this->read_word(mtd));
        if (this->badblockpos & 0x1)
            bad >>= 1;
        if ((bad & 0xFF) != 0xff)
            res = 1;
    } else {
        this->cmdfunc (mtd, NAND_CMD_READOOB, this->badblockpos, page & this->pagemask);
        // ���Ͷ�oob_data����(oob_data��badblockpos (��6)λ��¼�Ż����־) 
        if (this->read_byte(mtd) != 0xff)//����
            res = 1;
    }
        
    if (getchip) {
        // Deselect and wake up anyone waiting on the device 
        nand_release_device(mtd);
    }    
    
    return res;
}

//*
// * nand_default_block_markbad - [DEFAULT] mark a block bad
// * ��־����
// * @mtd:    MTD device structure
// * @ofs:    offset from device start
// *
// * This is the default implementation, which can be overridden by
// * a hardware specific driver.

static int nand_default_block_markbad(struct mtd_info *mtd, loff_t ofs)
{
    struct nand_chip *this = mtd->priv;
    u_char buf[2] = {0, 0};
    size_t    retlen;
    int block;
    
    // Get block number 
    block = ((int) ofs) >> this->bbt_erase_shift;
    if (this->bbt)
        this->bbt[block >> 2] |= 0x01 << ((block & 0x03) << 1);
    // 
    // �����ʱ���Ǻܺ�˵���ں�ά��һ����־bad block��ʹ��2bit����ʾ1block��
    // ������ڿ�����ʱ��ͨ��ɨ��nand flashÿ��block��ͷ��ҳ��oob���������ɣ�
    // ���ֻ��������Ӧ��block��־λΪ����(��ʱ����3������ʱ����1����û��������ʲô��ͬ)
     

    // Do we have a flash based bad block table ? 
    if (this->options & NAND_USE_FLASH_BBT)//samsun nand flash���������֣���ʱ��ȥ�о����Ժ�ͬ
        return nand_update_bbt (mtd, ofs);
        
    // We write two bytes, so we dont have to mess with 16 bit access 
    ofs += mtd->oobsize + (this->badblockpos & ~0x01);//???????????????
    return nand_write_oob (mtd, ofs , 2, &retlen, buf);
}

//*
// * nand_verify_buf - [DEFAULT] Verify chip data against buffer
// * ����nand flash��buffer�������Ƿ�һ�� 
// * @mtd:    MTD device structure
// * @buf:    buffer containing the data to compare
// * @len:    number of bytes to compare
// *
// * Default verify function for 8bit buswith
 
static int nand_verify_buf(struct mtd_info *mtd, const u_char *buf, int len)
{
    int i;
    struct nand_chip *this = mtd->priv;

    for (i=0; i<len; i++)
        if (buf[i] != readb(this->IO_ADDR_R))
            return -EFAULT;

    return 0;
}

//*
// * nand_default_bbt - [NAND Interface] Select a default bad block table for the device 
// * @mtd:    MTD device structure
// *
// * This function selects the default bad block table
// * support for the device and calls the nand_scan_bbt function
// *

int nand_default_bbt (struct mtd_info *mtd)
{
    struct nand_chip *this = mtd->priv;
    
    // Default for AG-AND. We must use a flash based 
     * bad block table as the devices have factory marked
     * _good_ blocks. Erasing those blocks leads to loss
     * of the good / bad information, so we _must_ store
     * this information in a good / bad table during 
     * startup
    
    if (this->options & NAND_IS_AND) {
        // Use the default pattern descriptors 
        if (!this->bbt_td) {    
            this->bbt_td = &bbt_main_descr;
            this->bbt_md = &bbt_mirror_descr;
        }    
        this->options |= NAND_USE_FLASH_BBT;
        return nand_scan_bbt (mtd, &agand_flashbased);
    }
    
    
    // Is a flash based bad block table requested ? 
    if (this->options & NAND_USE_FLASH_BBT) {
        // Use the default pattern descriptors     
        if (!this->bbt_td) {    
            this->bbt_td = &bbt_main_descr;
            this->bbt_md = &bbt_mirror_descr;
        }
        if (!this->badblock_pattern) {
            this->badblock_pattern = (mtd->oobblock > 512) ?
                &largepage_flashbased : &smallpage_flashbased;
        }
    } else {      //samsun nand flash�Ļ����������nand flash���棬��Ҫɨ�������ɡ�
        this->bbt_td = NULL;
        this->bbt_md = NULL;
        if (!this->badblock_pattern) {
            this->badblock_pattern = (mtd->oobblock > 512) ?
                &largepage_memorybased : &smallpage_memorybased;
        }
    }
    return nand_scan_bbt (mtd, this->badblock_pattern);
}

//*
// * nand_scan_bbt - [NAND Interface] scan, find, read and maybe create bad block table(s)
// * @mtd:    MTD device structure
// * @bd:        descriptor for the good/bad block search pattern
// *
// * The function checks, if a bad block table(s) is/are already 
// * available. If not it scans the device for manufacturer
// * marked good / bad blocks and writes the bad block table(s) to
// * the selected place.
// *
// * The bad block table memory is allocated here. It must be freed
// * by calling the nand_free_bbt function.
// *

int nand_scan_bbt (struct mtd_info *mtd, struct nand_bbt_descr *bd)
{
    struct nand_chip *this = mtd->priv;
    int len, res = 0;
    uint8_t *buf;
    struct nand_bbt_descr *td = this->bbt_td;
    struct nand_bbt_descr *md = this->bbt_md;

    len = mtd->size >> (this->bbt_erase_shift + 2);
    // Allocate memory (2bit per block) 
    // 2bit per block=(2/8)byte per block����������Ҫ������2λ 
    this->bbt = kmalloc (len, GFP_KERNEL);
    if (!this->bbt) {
        printk (KERN_ERR "nand_scan_bbt: Out of memory\n");
        return -ENOMEM;
    }
    // Clear the memory bad block table 
    memset (this->bbt, 0x00, len);

    // If no primary table decriptor is given, scan the device
    // * to build a memory based bad block table
     
    if (!td) {
        if ((res = nand_memory_bbt(mtd, bd))) {
            printk (KERN_ERR "nand_bbt: Can't scan flash and build the RAM-based BBT\n");
            kfree (this->bbt);
            this->bbt = NULL;
        }
        return res;
    }

    // Allocate a temporary buffer for one eraseblock incl. oob 
    // ����1 block����Ҫ��oob data�ռ� 
    len = (1 << this->bbt_erase_shift);
    len += (len >> this->page_shift) * mtd->oobsize;
    buf = kmalloc (len, GFP_KERNEL);
    if (!buf) {
        printk (KERN_ERR "nand_bbt: Out of memory\n");
        kfree (this->bbt);
        this->bbt = NULL;
        return -ENOMEM;
    }
    
    //����td��md��ΪNULL��һ�º��������������ã��Ȳ�ȥ�о���
    // Is the bbt at a given page ? 
    if (td->options & NAND_BBT_ABSPAGE) {
        res = read_abs_bbts (mtd, buf, td, md);
    } else {    
        // Search the bad block table using a pattern in oob 
        res = search_read_bbts (mtd, buf, td, md);
    }    

    if (res) 
        res = check_create (mtd, buf, bd);
    
    // Prevent the bbt regions from erasing / writing 
    mark_bbt_region (mtd, td);
    if (md)
        mark_bbt_region (mtd, md);
    
    kfree (buf);
    return res;
}

//*
// * nand_memory_bbt - [GENERIC] create a memory based bad block table
// * @mtd:    MTD device structure
// * @bd:        descriptor for the good/bad block search pattern
// *
// * The function creates a memory based bbt by scanning the device 
// * for manufacturer / software marked good / bad blocks

static inline int nand_memory_bbt (struct mtd_info *mtd, struct nand_bbt_descr *bd)
{
    struct nand_chip *this = mtd->priv;

    bd->options &= ~NAND_BBT_SCANEMPTY;
    //����ֻ��Ҫɨ��oob data������Ҫɨ��ȫ��(512+16bytes������)
    return create_bbt (mtd, this->data_buf, bd, -1);
}

//*
// * create_bbt - [GENERIC] Create a bad block table by scanning the device
// * @mtd:    MTD device structure
// * @buf:    temporary buffer
// * @bd:        descriptor for the good/bad block search pattern
// * @chip:    create the table for a specific chip, -1 read all chips.
// *        Applies only if NAND_BBT_PERCHIP option is set
// *
// * Create a bad block table by scanning the device
// * for the given good/bad block identify pattern
 
static int create_bbt (struct mtd_info *mtd, uint8_t *buf, struct nand_bbt_descr *bd, int chip)
{
    struct nand_chip *this = mtd->priv;
    int i, j, numblocks, len, scanlen;
    int startblock;
    loff_t from;
    size_t readlen, ooblen;

    printk (KERN_INFO "Scanning device for bad blocks\n");

    if (bd->options & NAND_BBT_SCANALLPAGES)//ɨ�����ж�ҳ
        len = 1 << (this->bbt_erase_shift - this->page_shift);//���ÿblock������page��
    else {
        if (bd->options & NAND_BBT_SCAN2NDPAGE)//ֻ���2 page
            len = 2;
        else    
            len = 1;//ֻ���1 page
    }

    if (!(bd->options & NAND_BBT_SCANEMPTY)) {
        // We need only read few bytes from the OOB area 
        // ����ֻ��Ҫ���OOB��ĳЩ���� 
        scanlen = ooblen = 0;
        readlen = bd->len;
    } else {
        // Full page content should be read 
        // ��ȡ��ҳ���� 
        scanlen    = mtd->oobblock + mtd->oobsize;
        readlen = len * mtd->oobblock;
        ooblen = len * mtd->oobsize;
    }

    if (chip == -1) {
        // Note that numblocks is 2 * (real numblocks) here, see i+=2 below as it
        // * makes shifting and masking less painful 
        // �����nand flash��������block��Ŀ(ע����������Ŀ�����ֳ�2����)
        numblocks = mtd->size >> (this->bbt_erase_shift - 1);
        startblock = 0;
        from = 0;
    } else {
        if (chip >= this->numchips) {
            printk (KERN_WARNING "create_bbt(): chipnr (%d) > available chips (%d)\n",
                chip + 1, this->numchips);
            return -EINVAL;
        }
        numblocks = this->chipsize >> (this->bbt_erase_shift - 1);
        startblock = chip * numblocks;
        numblocks += startblock;
        from = startblock << (this->bbt_erase_shift - 1);
    }
    
    for (i = startblock; i < numblocks;) {
        int ret;
        
        if (bd->options & NAND_BBT_SCANEMPTY)        //��ҳ���ݶ�ȡ
            if ((ret = nand_read_raw (mtd, buf, from, readlen, ooblen)))
                return ret;

        for (j = 0; j < len; j++) {
            if (!(bd->options & NAND_BBT_SCANEMPTY)) {
                size_t retlen;
                
                // Read the full oob until read_oob is fixed to 
                // * handle single byte reads for 16 bit buswidth 
                // ��ȡ��ǰҳ��oob������������ 
                ret = mtd->read_oob(mtd, from + j * mtd->oobblock,
                            mtd->oobsize, &retlen, buf);
                if (ret)
                    return ret;
                // ���oob data��bad block��־λ���ж��Ƿ��ǻ��� 
                if (check_short_pattern (buf, bd)) {
                    this->bbt[i >> 3] |= 0x03 << (i & 0x6);
                // ע�⣺����i=ʵ��ֵ*2������һ��block��״̬��2bit����ʾ����ôһ���ֽڿ��Դ��4��block��״̬��
                   ����i>>3�պ���ʵ��block/4��4��block��״̬�պô����this->bbt��ָ���һ���ֽ����� 
                 
                    printk (KERN_WARNING "Bad eraseblock %d at 0x%08x\n", 
                        i >> 1, (unsigned int) from);
                    break;
                }
            } else {
                if (check_pattern (&buf[j * scanlen], scanlen, mtd->oobblock, bd)) {
                    this->bbt[i >> 3] |= 0x03 << (i & 0x6);
                    printk (KERN_WARNING "Bad eraseblock %d at 0x%08x\n", 
                        i >> 1, (unsigned int) from);
                    break;
                }
            }
        }
        i += 2;//����block�����
        from += (1 << this->bbt_erase_shift);//����nand flash�ĵ�ַ
    }
    return 0;
}

//*
// * nand_release - [NAND Interface] Free resources held by the NAND device 
// * @mtd:    MTD device structure

void nand_release (struct mtd_info *mtd)
{
    struct nand_chip *this = mtd->priv;

#ifdef CONFIG_MTD_PARTITIONS
    // Deregister partitions 
    del_mtd_partitions (mtd);
#endif
    // Deregister the device 
    del_mtd_device (mtd);

    // Free bad block table memory, if allocated 
    if (this->bbt)
        kfree (this->bbt);
    // Buffer allocated by nand_scan ? 
    if (this->options & NAND_OOBBUF_ALLOC)
        kfree (this->oob_buf);
    // Buffer allocated by nand_scan ? 
    if (this->options & NAND_DATABUF_ALLOC)
        kfree (this->data_buf);
}

//��¼��
///arch/arm/mach-s3c2410/dev.c�ļ���

static struct mtd_partition partition_info[]={
  [0]={
     name    :"vivi",
     size    :0x20000,
     offset  :0,
  },[1]={
     name    :"param",
     size    :0x10000,
     offset  :0x20000,
  },[2]={
     name    :"kernel",
     size    :0x1d0000,
     offset  :0x30000,
  },[3]={
     name    :"root",
     size    :0x3c00000,
     offset  :0x200000,
  }
};

struct s3c2410_nand_set nandset={
    nr_partitions    :4,
    partitions       :partition_info,
};

struct s3c2410_platform_nand superlpplatform={
    tacls     :0,
    twrph0    :30,
    twrph1    :0,
    sets      :&nandset,
    nr_sets   :1,
};

struct platform_device s3c_device_nand = {
    .name          = "s3c2410-nand",
    .id          = -1,
    .num_resources      = ARRAY_SIZE(s3c_nand_resource),
    .resource      = s3c_nand_resource,
    .dev={
        .platform_data=&superlpplatform
    }
};

//nand_flash_ids��
///driver/mtd/nand/nand_ids.c�ļ���
struct nand_flash_dev nand_flash_ids[] = {
................................................................................
    {"NAND 64MiB 3,3V 8-bit",     0x76, 512, 64, 0x4000, 0},
................................................................................
};
//ע��
//����ֻ�г����õ�samsun 64M Nand Flash�����ϣ���Ӧ����Ϣ�뿴�ýṹ��Ķ��壺
struct nand_flash_dev {
    char *name;
    int id;
    unsigned long pagesize;
    unsigned long chipsize;
    unsigned long erasesize;
    unsigned long options;
};
//��֪��nand flash �豸ID��Ϊ0x76��ҳ��СΪ512����СΪ64(M)���߳���Ԫ��СΪ16(K)��






//MTDԭʼ�豸��FLASHӲ�������ĶԻ�-�� 
//��һ�������µ��ϵĽ�����FLASHӲ�������������MTDԭʼ�豸������ϵ�ģ����������ϵ��µ��о�һ�������ͨ��MTDԭʼ�豸������FLASHӲ�������ġ�
//
//���ȷ���һ�����ͨ��MTDԭʼ�豸����ͨ��FLASHӲ����������ȡFLASH�洢�������ݡ�
//
//������<<Linuxϵͳ��ֲ>>һ�ģ�
//
//"��Nand Flash��
//����nand flash���豸�ļ�(nand flash��/dev�¶�Ӧ���ļ�)ִ��ϵͳ����read(),����ĳ���ļ�ϵͳ�жԸ�
//�豸���ж�����ʱ. �����struct mtd_info�е�read����,����ȱʡ���ú���Ϊnand_read(),��
//drivers/mtd/nand/nand_base.c�ж���.nand_read()����nand_do_read_ecc(),ִ�ж�����. ��
//nand_do_read_ecc()������,��Ҫ������¼������
// 1.�������nand flash�����ж�struct nand_chip���ص�select_chip����,��
//s3c2410_nand_select_chip()ѡ��Ҫ������MTDоƬ.
// 2. �������struct nand_chip��ϵͳȱʡ�ķ���cmdfunc���Ͷ����nand flash.
// 3. �������nand flash�����ж�struct nand_chip���ص�read_buf(),��s3c2410_nand_read_buf()
//��Nand Flash�Ŀ����������ݼĴ����ж�������.
// 4. ����б�Ҫ�Ļ�,�������nand flash�����ж�struct nand_chip���ص�
//enable_hwecc,correct_data�Լ�calculate_ecc����,��������ECCУ�顣"
//
//�����о�һ�����е�ϸ�ڣ�
//*
// * nand_read - [MTD Interface] MTD compability function for nand_do_read_ecc
// * @mtd:    MTD device structure
// * @from:    offset to read from
// * @len:    number of bytes to read
// * @retlen:    pointer to variable to store the number of read bytes
// * @buf:    the databuffer to put data
// *
// * This function simply calls nand_do_read_ecc with oob buffer and oobsel = NULL
// * and flags = 0xff
 
static int nand_read (struct mtd_info *mtd, loff_t from, size_t len, size_t * retlen, u_char * buf)
{
    return nand_do_read_ecc (mtd, from, len, retlen, buf, NULL, &mtd->oobinfo, 0xff);
}
//ע��
//    �Բ���oob_bufΪNULL��flagsΪ0xff����nand_do_read_ecc������

//*
// * nand_do_read_ecc - [MTD Interface] Read data with ECC
// * @mtd:    MTD device structure
// * @from:    offset to read from
// * @len:    number of bytes to read
// * @retlen:    pointer to variable to store the number of read bytes
// * @buf:    the databuffer to put data
// * @oob_buf:    filesystem supplied oob data buffer (can be NULL)
// * @oobsel:    oob selection structure
// * @flags:    flag to indicate if nand_get_device/nand_release_device should be preformed
// *        and how many corrected error bits are acceptable:
// *          bits 0..7 - number of tolerable errors
// *          bit  8    - 0 == do not get/release chip, 1 == get/release chip
// *
// * NAND read with ECC
 
int nand_do_read_ecc (struct mtd_info *mtd, loff_t from, size_t len,
                 size_t * retlen, u_char * buf, u_char * oob_buf, 
                 struct nand_oobinfo *oobsel, int flags)
{

    int i, j, col, realpage, page, end, ecc, chipnr, sndcmd = 1;
    int read = 0, oob = 0, ecc_status = 0, ecc_failed = 0;
    struct nand_chip *this = mtd->priv;
    u_char *data_poi, *oob_data = oob_buf;//Ŀǰoob_dataָ��Ϊ�գ��Ժ��ȥ�޸�����
    u_char ecc_calc[32];//���������ڴ�ż��������ecc���
    u_char ecc_code[32];//���������ڴ��oob��ecc���ֵ�����
    int eccmode, eccsteps;//eccmode���ecc������(ECC_SOFT)��
                            eccsteps���ڼ�¼һ��page�����eccУ�����(2)��
    int    *oob_config, datidx;
    int    blockcheck = (1 << (this->phys_erase_shift - this->page_shift)) - 1;
    int    eccbytes;
    int    compareecc = 1;//�Ƿ���Ҫecc��־(������ó�ECC_NONE�������־������0)
    int    oobreadlen;


    DEBUG (MTD_DEBUG_LEVEL3, "nand_read_ecc: from = 0x%08x, len = %i\n", (unsigned int) from, (int) len);

    // Do not allow reads past end of device 
    // ������Խ�豸�����Ķ����� 
    if ((from + len) > mtd->size) {
        DEBUG (MTD_DEBUG_LEVEL0, "nand_read_ecc: Attempt read beyond end of device\n");
        *retlen = 0;
        return -EINVAL;
    }

    // Grab the lock and see if the device is available 
    // ��ȡ���������ȴ��豸���ò���ȡ�����Ȩ 
    if (flags & NAND_GET_DEVICE)
        nand_get_device (this, mtd, FL_READING);

    // Autoplace of oob data ? Use the default placement scheme 
    if (oobsel->useecc == MTD_NANDECC_AUTOPLACE)
        oobsel = this->autooob;
    // 
    // * �о���һ���е���࣬��Ϊnand_scan���Ѿ����������´��룺 
    // * memcpy(&mtd->oobinfo, this->autooob, sizeof(mtd->oobinfo));
    // * ��this->autooob�����ݿ�����mtd->oobinfo����
     
        
    eccmode = oobsel->useecc ? this->eccmode : NAND_ECC_NONE;
    oob_config = oobsel->eccpos;//��¼ecc��oob�����е�λ��

    // Select the NAND device 
    chipnr = (int)(from >> this->chip_shift);
    this->select_chip(mtd, chipnr);//ѡ��nand flashоƬ(��s3c2410 nand flash��������Ϊ�ղ���)

    // First we calculate the starting page 
    // ���ȣ����Ǽ������ʼҳ�� 
    realpage = (int) (from >> this->page_shift);
    page = realpage & this->pagemask;

    // Get raw starting column 
    // ��Σ����Ǽ���ҳ��ƫַ 
    col = from & (mtd->oobblock - 1);

    end = mtd->oobblock;//ҳ��С(512)
    ecc = this->eccsize;//ecc�����µ����ݴ�С(256)
    eccbytes = this->eccbytes;//ecc��ռ���ֽ���(3)
    
    if ((eccmode == NAND_ECC_NONE) || (this->options & NAND_HWECC_SYNDROME))
        compareecc = 0;//�������Ϊ�ر�ECC��д��������ҪECC���ǰ�ecc������(���ڿ��Ƕ�����^_^)

    oobreadlen = mtd->oobsize;//16
    if (this->options & NAND_HWECC_SYNDROME) 
        oobreadlen -= oobsel->eccbytes;

    // Loop until all data read 
    while (read < len) {
        
        int aligned = (!col && (len - read) >= end);
        // 
        // * If the read is not page aligned, we have to read into data buffer
        // * due to ecc, else we read into return buffer direct
        // * ���Ҫ����λ�ò���ҳ���붼������ôֻҪ�Ȱ���ҳ��������
        // * ȡ������Ҫ��ȡ�����ݣ�Ȼ���޸Ķ�λ�ã���ô�Ժ�Ķ���������ҳ������ˡ�
         
        if (aligned)
            data_poi = &buf[read];
        else 
            data_poi = this->data_buf;
        
        // Check, if we have this page in the buffer 
        // *
        // * FIXME: Make it work when we must provide oob data too,
        // * check the usage of data_buf oob field
        // * �����������Ҫ�����ݻ������ڻ����ж�����
        // * 1 �����λ��ҳ���룬����ֻҪ�ѻ����е�����ֱ�ӿ�����data_poi(buf[read])�м���(��Ϊ���ݴ����뻺���У�����Ҳ����Ҫ����ecc����)
        // * 2 �����λ�ò���ҳ���룬ʲô����Ҫ��������������ڻ���(data_buf)�У��Ժ���data_poi(ָ�򻺴�data_buf)����ȡ����Ҫ�����ݡ�
         
        if (realpage == this->pagebuf && !oob_buf) {
            // aligned read ? 
            if (aligned)
                memcpy (data_poi, this->data_buf, end);
            goto readdata;
        }

        // Check, if we must send the read command 
        // ���Ͷ����ҳ��ַΪpage���е�ַΪ0x00 
        if (sndcmd) {
            this->cmdfunc (mtd, NAND_CMD_READ0, 0x00, page);
            sndcmd = 0;
        }    

        // get oob area, if we have no oob buffer from fs-driver 
        if (!oob_buf || oobsel->useecc == MTD_NANDECC_AUTOPLACE ||
            oobsel->useecc == MTD_NANDECC_AUTOPL_USR)
            oob_data = &this->data_buf[end];//���������oob_data�ݴ���data_buf������

        eccsteps = this->eccsteps;//2
        
        switch (eccmode) {
        case NAND_ECC_NONE: {    // No ECC, Read in a page 
            static unsigned long lastwhinge = 0;
            if ((lastwhinge / HZ) != (jiffies / HZ)) {
                printk (KERN_WARNING "Reading data from NAND FLASH without ECC is not recommended\n");
                lastwhinge = jiffies;
            }
            this->read_buf(mtd, data_poi, end);
            break;
        }
            
        case NAND_ECC_SOFT:    // Software ECC 3/256: Read in a page + oob data 
            this->read_buf(mtd, data_poi, end);//��ȡ���ݵ�data_poi
            for (i = 0, datidx = 0; eccsteps; eccsteps--, i+=3, datidx += ecc) 
                this->calculate_ecc(mtd, &data_poi[datidx], &ecc_calc[i]);
            // �������ȡ��data_poi�����ݵ�eccֵ������ŵ�ecc_calc�����С�
            // * ��Ϊ����������һҳ��С(512)����Ҫ�ֱ�����ϰ벿���°벿�ּ���һ��eccֵ�����ֿ���ŵ�ecc_calc������Ӧ��λ���С�
             
            break;    

        default:
            for (i = 0, datidx = 0; eccsteps; eccsteps--, i+=eccbytes, datidx += ecc) {
                this->enable_hwecc(mtd, NAND_ECC_READ);
                this->read_buf(mtd, &data_poi[datidx], ecc);

                // HW ecc with syndrome calculation must read the
                // * syndrome from flash immidiately after the data 
                if (!compareecc) {
                    // Some hw ecc generators need to know when the
                     * syndrome is read from flash 
                    this->enable_hwecc(mtd, NAND_ECC_READSYN);
                    this->read_buf(mtd, &oob_data[i], eccbytes);
                    // We calc error correction directly, it checks the hw
                    // * generator for an error, reads back the syndrome and
                    // * does the error correction on the fly 
                    ecc_status = this->correct_data(mtd, &data_poi[datidx], &oob_data[i], &ecc_code[i]);
                    if ((ecc_status == -1) || (ecc_status > (flags && 0xff))) {
                        DEBUG (MTD_DEBUG_LEVEL0, "nand_read_ecc: " 
                            "Failed ECC read, page 0x%08x on chip %d\n", page, chipnr);
                        ecc_failed++;
                    }
                } else {
                    this->calculate_ecc(mtd, &data_poi[datidx], &ecc_calc[i]);
                }    
            }
            break;                        
        }

        // read oobdata 
        this->read_buf(mtd, &oob_data[mtd->oobsize - oobreadlen], oobreadlen);
        //��ȡoob_data��ŵ�oob_data[mtd->oobsize - oobreadlen]����������data_buf[end]��

        // Skip ECC check, if not requested (ECC_NONE or HW_ECC with syndromes) 
        // ����ecc��� 
        if (!compareecc)
            goto readoob;    
        
        // Pick the ECC bytes out of the oob data 
        // �Ӹն�������oob_data��ȡ��ecc����(��������ǰ�����ֽ�) 
        for (j = 0; j < oobsel->eccbytes; j++)
            ecc_code[j] = oob_data[oob_config[j]];

        // correct data, if neccecary 
        for (i = 0, j = 0, datidx = 0; i < this->eccsteps; i++, datidx += ecc) {
            ecc_status = this->correct_data(mtd, &data_poi[datidx], &ecc_code[j], &ecc_calc[j]);
            // ��ǰ����������ecc_cal���鶼�������������ecc�������Ƚϣ���������������(������֤���޸������忴����ֵ) 
            
            // Get next chunk of ecc bytes 
            j += eccbytes;
            
            // Check, if we have a fs supplied oob-buffer, 
            // * This is the legacy mode. Used by YAFFS1
            // * Should go away some day
             
            if (oob_buf && oobsel->useecc == MTD_NANDECC_PLACE) { 
                int *p = (int *)(&oob_data[mtd->oobsize]);
                p[i] = ecc_status;
            }
            // �ܲ��ң�ecc��ⷢ�ִ�����δ���޸����������     
            if ((ecc_status == -1) || (ecc_status > (flags && 0xff))) {    
                DEBUG (MTD_DEBUG_LEVEL0, "nand_read_ecc: " "Failed ECC read, page 0x%08x\n", page);
                ecc_failed++;
            }
        }        

    readoob:
        // check, if we have a fs supplied oob-buffer 
        if (oob_buf) {
            // without autoplace. Legacy mode used by YAFFS1 
            switch(oobsel->useecc) {
            case MTD_NANDECC_AUTOPLACE:
            case MTD_NANDECC_AUTOPL_USR:
                // Walk through the autoplace chunks 
                for (i = 0; oobsel->oobfree[i][1]; i++) {
                    int from = oobsel->oobfree[i][0];
                    int num = oobsel->oobfree[i][1];
                    memcpy(&oob_buf[oob], &oob_data[from], num);
                    oob += num;
                }
                break;
            case MTD_NANDECC_PLACE:
                // YAFFS1 legacy mode 
                oob_data += this->eccsteps * sizeof (int);
            default:
                oob_data += mtd->oobsize;
            }
        }
    readdata:
        // Partial page read, transfer data into fs buffer 
        // * ��λ�ò���ҳ���룬��data_poi(data_buf��)��ȡ����Ҫ������
         
        if (!aligned) { 
            for (j = col; j < end && read < len; j++)
                buf[read++] = data_poi[j];//read����
            this->pagebuf = realpage;    
        } else        
            read += mtd->oobblock;//��ҳ��ȡ������ֵ������ҳ����Ŀ(512)

        // Apply delay or wait for ready/busy pin 
        // * Do this before the AUTOINCR check, so no problems
        // * arise if a chip which does auto increment
        // * is marked as NOAUTOINCR by the board driver.
        
        if (!this->dev_ready) 
            udelay (this->chip_delay);
        else
            nand_wait_ready(mtd);
            
        if (read == len)//�������ݶ��궼������˳���ѭ����
            break;    

        // For subsequent reads align to page boundary. 
        col = 0;//���ڶ�λ�ò���ҳ���붼�����ǰ���Ѷ����������Ӧ���������ڶ�λ�ñ��ҳ�����ˡ�
        // Increment page address 
        realpage++;//ҳ��ַ��1,��ȡ��һҳ��

        page = realpage & this->pagemask;
        // Check, if we cross a chip boundary 
        if (!page) {
            chipnr++;
            this->select_chip(mtd, -1);
            this->select_chip(mtd, chipnr);
        }
        // Check, if the chip supports auto page increment 
        // * or if we have hit a block boundary. 
        // * ���оƬ֧��ҳ��������,��δ��block boundary(15)�Ļ��������ٷ��Ͷ�����
         
        if (!NAND_CANAUTOINCR(this) || !(page & blockcheck))
            sndcmd = 1;                
    }

    // Deselect and wake up anyone waiting on the device 
    if (flags & NAND_GET_DEVICE)
        nand_release_device(mtd);//�������豸������Ȩ�������������̻�ȡ��ռ����

    //
    // * Return success, if no ECC failures, else -EBADMSG
    // * fs driver will take care of that, because
    // * retlen == desired len and result == -EBADMSG
     
    *retlen = read;
    return ecc_failed ? -EBADMSG : 0;
}

//�õģ������о�һ�����ͨ��MTDԭʼ�豸����ͨ��FLASHӲ��������FLASH�洢��д���ݡ�
//
//������<<Linuxϵͳ��ֲ>>һ�ģ�
//
//дNand Flash
//����nand flash���豸�ļ�(nand flash��/dev�¶�Ӧ���ļ�)ִ��ϵͳ����write(),����ĳ���ļ�ϵͳ�жԸ��豸
//���ж�����ʱ, �����struct mtd_info��write����,����ȱʡ���ú���Ϊnand_write(),������������
//drivers/mtd/nand/nand_base.c�ж���. nand_write()����nand_write_ecc(),ִ��д����.��
//nand_do_write_ecc()������,��Ҫ������¼������
// 1. �������nand flash�����ж�struct nand_chip���ص�select_chip����,��
//s3c2410_nand_select_chip()ѡ��Ҫ������MTDоƬ.
// 2. ����nand_write_page()дһ��ҳ.
// 3. ��nand_write_page()��,�������struct nand_chip��ϵͳȱʡ�ķ���cmdfunc����д����
//��nand flash.
// 4. ��nand_write_page()��,�������nand flash�����ж�struct nand_chip���ص�
//write_buf(),��s3c2410_nand_write_buf()��Nand Flash�Ŀ����������ݼĴ�����д������.
//5. ��nand_write_page()��,�������nand flash�����ж�struct nand_chip����waitfunc����,
//�÷�������ϵͳȱʡ����nand_wait(),�÷�����ȡ����״̬,���ȴ�nand flash�������.��
//���������,�ǵ���nand flash�����ж�struct nand_chip�����ص�dev_ready����,��
//s3c2410_nand_devready()����.
//
//�����о�һ�����е�ϸ�ڣ�
//*
// * nand_write - [MTD Interface] compability function for nand_write_ecc
// * @mtd:    MTD device structure
// * @to:        offset to write to
// * @len:    number of bytes to write
// * @retlen:    pointer to variable to store the number of written bytes
// * @buf:    the data to write
// *
// * This function simply calls nand_write_ecc with oob buffer and oobsel = NULL
// *

static int nand_write (struct mtd_info *mtd, loff_t to, size_t len, size_t * retlen, const u_char * buf)
{
    return (nand_write_ecc (mtd, to, len, retlen, buf, NULL, NULL));
}
ע��
    �Բ���eccbuf��oobselΪNULL������nand_write_ecc������

//*
// * nand_write_ecc - [MTD Interface] NAND write with ECC
// * @mtd:    MTD device structure
// * @to:        offset to write to
// * @len:    number of bytes to write
// * @retlen:    pointer to variable to store the number of written bytes
// * @buf:    the data to write
// * @eccbuf:    filesystem supplied oob data buffer
// * @oobsel:    oob selection structure
// *
// * NAND write with ECC
 
static int nand_write_ecc (struct mtd_info *mtd, loff_t to, size_t len,
             size_t * retlen, const u_char * buf, u_char * eccbuf, struct nand_oobinfo *oobsel)
{
    int startpage, page, ret = -EIO, oob = 0, written = 0, chipnr;
    int autoplace = 0, numpages, totalpages;
    struct nand_chip *this = mtd->priv;
    u_char *oobbuf, *bufstart;
    int    ppblock = (1 << (this->phys_erase_shift - this->page_shift));//page/block

    DEBUG (MTD_DEBUG_LEVEL3, "nand_write_ecc: to = 0x%08x, len = %i\n", (unsigned int) to, (int) len);

    // Initialize retlen, in case of early exit 
    *retlen = 0;

    // Do not allow write past end of device 
    // ��Խnand flash������д�����ǲ������ 
    if ((to + len) > mtd->size) {
        DEBUG (MTD_DEBUG_LEVEL0, "nand_write_ecc: Attempt to write past end of page\n");
        return -EINVAL;
    }

    // reject writes, which are not page aligned 
    // ����ҳ�����д����ͬ���ǲ������    
    if (NOTALIGNED (to) || NOTALIGNED(len)) {
        printk (KERN_NOTICE "nand_write_ecc: Attempt to write not page aligned data\n");
        return -EINVAL;
    }

    // Grab the lock and see if the device is available 
    // ��ȡ�豸�Ŀ���Ȩ 
    nand_get_device (this, mtd, FL_WRITING);

    // Calculate chipnr 
    // 
    // * ���ڶ�Ƭflash������£��������Ҫд������Ƭflash��
    // * (��Ȼ�����ҵİ壬ֻ��һƬnand flash��������������ǲ���Ҫ��)
     
    chipnr = (int)(to >> this->chip_shift);
    // Select the NAND device 
    // Ƭѡ���� 
    this->select_chip(mtd, chipnr);

    // Check, if it is write protected 
    // ���nand flashд��������Ȼ������д�� 
    if (nand_check_wp(mtd))
        goto out;

    // if oobsel is NULL, use chip defaults 
    if (oobsel == NULL) 
        oobsel = &mtd->oobinfo;        
        
    // Autoplace of oob data ? Use the default placement scheme 
    if (oobsel->useecc == MTD_NANDECC_AUTOPLACE) {
        oobsel = this->autooob;
        autoplace = 1;
    }    
    if (oobsel->useecc == MTD_NANDECC_AUTOPL_USR)
        autoplace = 1;

    // Setup variables and oob buffer 
    totalpages = len >> this->page_shift;//������Ҫ��ȡ�����ݳ��ȹ��ж���ҳ
    page = (int) (to >> this->page_shift);//����������Ҫд���Ŀ�ʼҳ��
    // Invalidate the page cache, if we write to the cached page 
    // ������汣�������������Ҫд���ݵķ�Χ�ڣ��ѻ��������������Ϊ������???? 
    if (page <= this->pagebuf && this->pagebuf < (page + totalpages))  
        this->pagebuf = -1;
    
    // Set it relative to chip 
    page &= this->pagemask;
    startpage = page;
    // Calc number of pages we can write in one go 
    numpages = min (ppblock - (startpage  & (ppblock - 1)), totalpages);//�������block������д��ҳ��
    oobbuf = nand_prepare_oobbuf (mtd, eccbuf, oobsel, autoplace, numpages);//�Ȳ������о�~_~
    bufstart = (u_char *)buf;//��ȡ��Ҫд���ݵĵ�ַ

    // Loop until all data is written 
    // ѭ������д���� 
    while (written < len) {

        this->data_poi = (u_char*) &buf[written];//�Ȱ���Ҫд�����ݻ��嵽data_poi��
        // Write one page. If this is the last page to write
        // * or the last page in this block, then use the
        // * real pageprogram command, else select cached programming
        // * if supported by the chip.
        // * ���������д���ݵ����һ��ҳ����������дblock�����һ��ҳ������nand flash��          
        // * pageprogramָ�����������д��nand flash��(nand flash����С������ԪΪblock)
         
        ret = nand_write_page (mtd, this, page, &oobbuf[oob], oobsel, (--numpages > 0));
        if (ret) {
            DEBUG (MTD_DEBUG_LEVEL0, "nand_write_ecc: write_page failed %d\n", ret);
            goto out;
        }    
        // Next oob page 
        oob += mtd->oobsize;
        // Update written bytes count 
        // ����д�����ֵ 
        written += mtd->oobblock;
        if (written == len)//д����ϣ��˳� 
            goto cmp;
        
        // Increment page address 
        page++;//��һҳ

        // Have we hit a block boundary ? Then we have to verify and
        // * if verify is ok, we have to setup the oob buffer for
        // * the next pages.
        // * ��ʱ���Ǻ����ף���Ҫ�ȸ�����nand_prepare_oobbuf����������
        
        if (!(page & (ppblock - 1))){
            int ofs;
            this->data_poi = bufstart;//����nand_verify_pages�õ�
            ret = nand_verify_pages (mtd, this, startpage, 
                page - startpage,
                oobbuf, oobsel, chipnr, (eccbuf != NULL));//һҳд�꣬�������
            if (ret) {
                DEBUG (MTD_DEBUG_LEVEL0, "nand_write_ecc: verify_pages failed %d\n", ret);
                goto out;
            }    
            *retlen = written;

            ofs = autoplace ? mtd->oobavail : mtd->oobsize;
            if (eccbuf)
                eccbuf += (page - startpage) * ofs;
            totalpages -= page - startpage;//������Ҫд��ҳ��
            numpages = min (totalpages, ppblock);//���¿���д��ҳ��
            page &= this->pagemask;//����ҳ��
            startpage = page;//���¿�ʼҳ��
            oobbuf = nand_prepare_oobbuf (mtd, eccbuf, oobsel, 
                    autoplace, numpages);
            // Check, if we cross a chip boundary 
            if (!page) {
                chipnr++;
                this->select_chip(mtd, -1);
                this->select_chip(mtd, chipnr);
            }
        }
    }
    // Verify the remaining pages 
cmp:
    this->data_poi = bufstart;//����nand_verify_pages�õ�
     ret = nand_verify_pages (mtd, this, startpage, totalpages,
        oobbuf, oobsel, chipnr, (eccbuf != NULL));
    if (!ret)
        *retlen = written;
    else    
        DEBUG (MTD_DEBUG_LEVEL0, "nand_write_ecc: verify_pages failed %d\n", ret);

out:
    // Deselect and wake up anyone waiting on the device 
    nand_release_device(mtd);//�������豸�Ŀ���Ȩ

    return ret;
}

//*
// * nand_write_page - [GENERIC] write one page
// * @mtd:    MTD device structure
// * @this:    NAND chip structure
// * @page:     startpage inside the chip, must be called with (page & this->pagemask)
// * @oob_buf:    out of band data buffer
// * @oobsel:    out of band selecttion structre
// * @cached:    1 = enable cached programming if supported by chip
// *
// * Nand_page_program function is used for write and writev !
// * This function will always program a full page of data
// * If you call it with a non page aligned buffer, you're lost :)
// *
// * Cached programming is not supported yet.
 
static int nand_write_page (struct mtd_info *mtd, struct nand_chip *this, int page, 
    u_char *oob_buf,  struct nand_oobinfo *oobsel, int cached)
{
    int     i, status;
    u_char    ecc_code[32];
    int    eccmode = oobsel->useecc ? this->eccmode : NAND_ECC_NONE;
    int      *oob_config = oobsel->eccpos;
    int    datidx = 0, eccidx = 0, eccsteps = this->eccsteps;
    int    eccbytes = 0;
    
    // FIXME: Enable cached programming 
    cached = 0;//�ڸ߰汾���ں����ҵ������Ľ��ͣ�
    //
    // * Cached progamming disabled for now, Not sure if its worth the
    // * trouble. The speed gain is not very impressive. (2.3->2.6Mib/s)
     
    
    // Send command to begin auto page programming 
    // ����ҳ���ָ�� 
    this->cmdfunc (mtd, NAND_CMD_SEQIN, 0x00, page);

    // Write out complete page of data, take care of eccmode 
    switch (eccmode) {
    // No ecc, write all 
    case NAND_ECC_NONE:
        printk (KERN_WARNING "Writing data without ECC to NAND-FLASH is not recommended\n");
        this->write_buf(mtd, this->data_poi, mtd->oobblock);
        break;
        
    // Software ecc 3/256, write all 
    case NAND_ECC_SOFT:
        for (; eccsteps; eccsteps--) {
            this->calculate_ecc(mtd, &this->data_poi[datidx], ecc_code);//�����һҳ��ecc����
            for (i = 0; i < 3; i++, eccidx++)
                oob_buf[oob_config[eccidx]] = ecc_code[i];//��ŵ�ecc_code������
            datidx += this->eccsize;
        }
        this->write_buf(mtd, this->data_poi, mtd->oobblock);//����FLASHӲ�����������д����
        break;
    default:
        eccbytes = this->eccbytes;
        for (; eccsteps; eccsteps--) {
            // enable hardware ecc logic for write 
            this->enable_hwecc(mtd, NAND_ECC_WRITE);
            this->write_buf(mtd, &this->data_poi[datidx], this->eccsize);
            this->calculate_ecc(mtd, &this->data_poi[datidx], ecc_code);
            for (i = 0; i < eccbytes; i++, eccidx++)
                oob_buf[oob_config[eccidx]] = ecc_code[i];
            // If the hardware ecc provides syndromes then
             * the ecc code must be written immidiately after
             * the data bytes (words) 
            if (this->options & NAND_HWECC_SYNDROME)
                this->write_buf(mtd, ecc_code, eccbytes);
            datidx += this->eccsize;
        }
        break;
    }
                                        
    // Write out OOB data 
    if (this->options & NAND_HWECC_SYNDROME)
        this->write_buf(mtd, &oob_buf[oobsel->eccbytes], mtd->oobsize - oobsel->eccbytes);
    else 
        this->write_buf(mtd, oob_buf, mtd->oobsize);//дoob data����Ҫ����������eccֵд��ȥ

    // Send command to actually program the data 
    this->cmdfunc (mtd, cached ? NAND_CMD_CACHEDPROG : NAND_CMD_PAGEPROG, -1, -1);

    if (!cached) {
        // call wait ready function 
        status = this->waitfunc (mtd, this, FL_WRITING);//�ȴ�д�����

        // See if operation failed and additional status checks are available 
        if ((status & NAND_STATUS_FAIL) && (this->errstat)) {
            status = this->errstat(mtd, this, FL_WRITING, status, page);
        }

        // See if device thinks it succeeded 
        if (status & NAND_STATUS_FAIL) {
            DEBUG (MTD_DEBUG_LEVEL0, "%s: " "Failed write, page 0x%08x, ", __FUNCTION__, page);
            return -EIO;
        }
    } else {
        // FIXME: Implement cached programming ! 
        // wait until cache is ready
        // status = this->waitfunc (mtd, this, FL_CACHEDRPG);//cached��д������ʱû��
    }
    return 0;    
}

