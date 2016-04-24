///*MTD原始设备与FLASH硬件驱动的对话 
//看了<<Linux MTD源代码分析>>后对以MTD的分层结构以及各层的分工情况有了大致的了解，然而各层之间是如何进行对话的呢，对于这个问题，<<Linux MTD源代码分析>>上没有详细的去说明。
//小弟抽空研究了一下，打算从下到上，在从上到下，分两条主线来研究一下MTD原始设备与FLASH硬件驱动的对话(MTD原始设备与更上层的对话留待以后再研究)。
//以下是第一部分，从下到上的介绍FLASH硬件驱动与MTD原始设备是如何建立联系的。
//：1、首先从入口函数开始

//=======================打开注释观看   /*=================================

static int s3c24xx_nand_probe(struct device *dev, int is_s3c2440)
{
    struct platform_device *pdev = to_platform_device(dev);
    struct s3c2410_platform_nand *plat = to_nand_plat(dev);
    //获取nand flash配置用结构体数据(dev.c中定义，详细见附录部分)
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
    dev_set_drvdata(dev, info);                  //以后有用

    spin_lock_init(&info->controller.lock);      //初始化自旋锁
    init_waitqueue_head(&info->controller.wq);   //初始化等待队列

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
    res  = pdev->resource;                        //提取dev.c中定义的与设备相关的资源
    size = res->end - res->start + 1;

    info->area = request_mem_region(res->start, size, pdev->name);

    if (info->area == NULL) {
        printk(KERN_ERR PFX "cannot reserve register region\n");
        err = -ENOENT;
        goto exit_error;
    }

    info->device     = dev;
    info->platform   = plat;                     //保存好struct s3c2410_platform_nand结构数据
    info->regs       = ioremap(res->start, size);//映射nand flash用到的寄存器
    info->is_s3c2440 = is_s3c2440;               

    if (info->regs == NULL) {
        printk(KERN_ERR PFX "cannot reserve register region\n");
        err = -EIO;
        goto exit_error;
    }        

    printk(KERN_INFO PFX "mapped registers at %p\n", info->regs);

    // initialise the hardware 

    err = s3c2410_nand_inithw(info, dev);
    //初始化s3c2410 nand flash控制，主要是配置S3C2410_NFCONF寄存器
    if (err != 0)
        goto exit_error;

    sets = (plat != NULL) ? plat->sets : NULL;   
    nr_sets = (plat != NULL) ? plat->nr_sets : 1;
   
    info->mtd_count = nr_sets;
    //我的板上只有一块nand flash，配置信息见plat-sets，数目为1。

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
                       (sets) ? sets->nr_chips : 1);//为什么使用set->nr_chips(还没配置的东西)？

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

//初始化代表一片flash的struct nand_chip结构

static void s3c2410_nand_init_chip(struct s3c2410_nand_info *info,
                   struct s3c2410_nand_mtd *nmtd,
                   struct s3c2410_nand_set *set)
{
    struct nand_chip *chip = &nmtd->chip;

    chip->IO_ADDR_R       = info->regs + S3C2410_NFDATA;   //读地址
    chip->IO_ADDR_W    = info->regs + S3C2410_NFDATA;      //写地址
    chip->hwcontrol    = s3c2410_nand_hwcontrol;   
    chip->dev_ready    = s3c2410_nand_devready;            //ready状态查询
    chip->write_buf    = s3c2410_nand_write_buf;           //写函数
    chip->read_buf     = s3c2410_nand_read_buf;            //读函数
    chip->select_chip  = s3c2410_nand_select_chip;         //片选函数
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
    //nand_scan函数中会调用struct nand_chip *this = mtd->priv取出该struct nand_chip结构
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
        chip->eccmode        = NAND_ECC_SOFT;         //ECC的类型
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
        chip->IO_ADDR_W = info->regs + S3C2410_NFCMD;//写命令
        break;

    case NAND_CTL_SETALE:
        chip->IO_ADDR_W = info->regs + S3C2410_NFADDR;//写地址
        break;

        // NAND_CTL_CLRCLE: 
        // NAND_CTL_CLRALE: 
    default:
        chip->IO_ADDR_W = info->regs + S3C2410_NFDATA;//写数据
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
    return readb(info->regs + S3C2410_NFSTAT) & S3C2410_NFSTAT_BUSY;//返回nand flash都忙标志
}

static void s3c2410_nand_write_buf(struct mtd_info *mtd,
                   const u_char *buf, int len)
{
    struct nand_chip *this = mtd->priv;
    writesb(this->IO_ADDR_W, buf, len);//写操作
}

static void s3c2410_nand_read_buf(struct mtd_info *mtd, u_char *buf, int len)
{
    struct nand_chip *this = mtd->priv;
    readsb(this->IO_ADDR_R, buf, len);//读操作
}

// select chip 
// 
// * 根据chip都值设置nand flash都片选信号:
// * chip = -1 -- 禁用nand flash
// * chip !=-1 -- 选择对应的nand flash
 
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


注：
    s3c2410_nand_init_chip填充struct nand_chip的一部分成员，nand_scan以通用nand flash的标准进行检测，并填充struct nand_chip的其它成员，必要时根据检测结果进行取舍。

int nand_scan (struct mtd_info *mtd, int maxchips)
{
    int i, nand_maf_id, nand_dev_id, busw, maf_id;
    struct nand_chip *this = mtd->priv;          //取出struct nand_chip结构

    // Get buswidth to select the correct functions
    busw = this->options & NAND_BUSWIDTH_16;     //nand flash的位宽

    // check for proper chip_delay setup, set 20us if not 
    if (!this->chip_delay)                     
        this->chip_delay = 20;

    // check, if a user supplied command function given 
    if (this->cmdfunc == NULL)                  //填充命令函数
        this->cmdfunc = nand_command;

    // check, if a user supplied wait function given 
    if (this->waitfunc == NULL)                  //填充等待函数
        this->waitfunc = nand_wait;

    if (!this->select_chip)                      //s3c2410_nand_init_chip中已定义
        this->select_chip = nand_select_chip;
    if (!this->write_byte)                       //使用默认的
        this->write_byte = busw ? nand_write_byte16 : nand_write_byte;
    if (!this->read_byte)                        //使用默认的
        this->read_byte = busw ? nand_read_byte16 : nand_read_byte;
    if (!this->write_word)                       //使用默认的
        this->write_word = nand_write_word;
    if (!this->read_word)                        //使用默认的
        this->read_word = nand_read_word;
    if (!this->block_bad)                        //使用默认的
        this->block_bad = nand_block_bad;
    if (!this->block_markbad)                    //使用默认的
        this->block_markbad = nand_default_block_markbad;
    if (!this->write_buf)                        //s3c2410_nand_init_chip中已定义
        this->write_buf = busw ? nand_write_buf16 : nand_write_buf;
    if (!this->read_buf)                         //s3c2410_nand_init_chip中已定义
        this->read_buf = busw ? nand_read_buf16 : nand_read_buf;
    if (!this->verify_buf)                       //使用默认的
        this->verify_buf = busw ? nand_verify_buf16 : nand_verify_buf;
    if (!this->scan_bbt)                         //使用默认的
        this->scan_bbt = nand_default_bbt;

    // Select the device 
    this->select_chip(mtd, 0);       //片选，可惜在s3c2410 nand flash控制器中此操作为空

    // Send the command for reading device ID 
    this->cmdfunc (mtd, NAND_CMD_READID, 0x00, -1);//发送读ID命令

    // Read manufacturer and device IDs 
    nand_maf_id = this->read_byte(mtd);            //读取生产商ID
    nand_dev_id = this->read_byte(mtd);            //读取设备ID

    // Print and store flash device information 
    for (i = 0; nand_flash_ids[i].name != NULL; i++) {   
//保存着nand flash资料的nand_flash_ids表在include/linux/mtd/nand_ids.c文件中，详细见附录
                
        if (nand_dev_id != nand_flash_ids[i].id)    //比较设备ID 
            continue;

        if (!mtd->name) mtd->name = nand_flash_ids[i].name;   //填充设备名
        this->chipsize = nand_flash_ids[i].chipsize << 20;    //填充设备大小
        
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
            mtd->erasesize = nand_flash_ids[i].erasesize;   //填充檫除单元大小(16k)
            mtd->oobblock = nand_flash_ids[i].pagesize;     //填充页大小(512)
            mtd->oobsize = mtd->oobblock / 32;              //oob大小(512/32=16)
            busw = nand_flash_ids[i].options & NAND_BUSWIDTH_16;//获取nand flash表中定义的位宽
        }

        // Try to identify manufacturer             //比较生产商ID
        for (maf_id = 0; nand_manuf_ids[maf_id].id != 0x0; maf_id++) {
            if (nand_manuf_ids[maf_id].id == nand_maf_id)
                break;
        }

        // Check, if buswidth is correct. Hardware drivers should set
         * this correct ! 
        /用户定义的位宽与芯片实际的位宽不一致，取消nand flash的片选
        if (busw != (this->options & NAND_BUSWIDTH_16)) {    
            printk (KERN_INFO "NAND device: Manufacturer ID:"
                " 0x%02x, Chip ID: 0x%02x (%s %s)\n", nand_maf_id, nand_dev_id, 
                nand_manuf_ids[maf_id].name , mtd->name);
            printk (KERN_WARNING 
                "NAND bus width %d instead %d bit\n", 
                    (this->options & NAND_BUSWIDTH_16) ? 16 : 8,
                    busw ? 16 : 8);
            this->select_chip(mtd, -1);//在s3c2410 nand flash控制器驱动中，此操作为空操作
            return 1;    
        }
        
        // Calculate the address shift from the page size  
        //计算页、可檫除单元、nand flash大小的偏移值  
        this->page_shift = ffs(mtd->oobblock) - 1;
        this->bbt_erase_shift = this->phys_erase_shift = ffs(mtd->erasesize) - 1;
        this->chip_shift = ffs(this->chipsize) - 1;

        // Set the bad block position 
        //标注此nand flash为大页还是小页？
        this->badblockpos = mtd->oobblock > 512 ? 
            NAND_LARGE_BADBLOCK_POS : NAND_SMALL_BADBLOCK_POS;

        // Get chip options, preserve non chip based options 
        //用户没指定的选项从nand flash表中获取补上
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
    }//好的，检测结束^_^

    if (!nand_flash_ids[i].name) {      
        printk (KERN_WARNING "No NAND device found!!!\n");
        this->select_chip(mtd, -1);
        return 1;
    }

    //统计一下同种类型的nand flash有多少块(我板上只有一块)
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
        //求出一个檫除单元64K中oob所占用的总空间
        len = mtd->oobsize << (this->phys_erase_shift - this->page_shift);
        this->oob_buf = kmalloc (len, GFP_KERNEL);
        if (!this->oob_buf) {
            printk (KERN_ERR "nand_scan(): Cannot allocate oob_buf\n");
            return -ENOMEM;
        }
        this->options |= NAND_OOBBUF_ALLOC;//oob空间已分配，置相应的标志位
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
        this->options |= NAND_DATABUF_ALLOC;//数据空间已分配，置相应的标志位
    }

    // Store the number of chips and calc total size for mtd 
    this->numchips = i;//记录nand flash片数
    mtd->size = i * this->chipsize;//计算出nand flash总大小
    // Convert chipsize to number of pages per chip -1. 
    this->pagemask = (this->chipsize >> this->page_shift) - 1;//(64M>>9)-1=128k-1=0x1ffff

    // Preset the internal oob buffer 
    //oob_buf全部置为0xff
    memset(this->oob_buf, 0xff, mtd->oobsize << (this->phys_erase_shift - this->page_shift));

    // If no default placement scheme is given, select an * appropriate one 
    if (!this->autooob) {   //我们选用的是NAND_ECC_SOFT，autooob未设置
        // Select the appropriate default oob placement scheme for placement agnostic filesystems 
        switch (mtd->oobsize) { 
        case 8:
            this->autooob = &nand_oob_8;
            break;
        case 16:
            this->autooob = &nand_oob_16;//我们的nand flash属于这一类
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
//注：
//    ECC的东西不是很懂，先跳过^_^   


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
    //填充mtd结构的其它部分
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
    this->hwcontrol(mtd, NAND_CTL_SETCLE);    //选择写入S3C2410_NFCMD寄存器
    //
     * Write out the command to the device.
     
    if (command == NAND_CMD_SEQIN) {
        int readcmd;

        if (column >= mtd->oobblock) {        //读/写位置超出512，读oob_data
            // OOB area 
            column -= mtd->oobblock;
            readcmd = NAND_CMD_READOOB;
        } else if (column < 256) {            //读/写位置在前512，使用read0命令
            // First 256 bytes --> READ0 
            readcmd = NAND_CMD_READ0;
        } else {                              //读/写位置在后512，使用read1命令
            column -= 256;
            readcmd = NAND_CMD_READ1;
        }
        this->write_byte(mtd, readcmd);        //写入具体命令
    }
    this->write_byte(mtd, command);

    // Set ALE and clear CLE to start address cycle 
    // 清楚CLE，锁存命令；置位ALE，开始传输地址 
    this->hwcontrol(mtd, NAND_CTL_CLRCLE);      //锁存命令

    if (column != -1 || page_addr != -1) {
        this->hwcontrol(mtd, NAND_CTL_SETALE);  //选择写入S3C2410_NFADDR寄存器

        // Serially input address 
        if (column != -1) {
            // Adjust columns for 16 bit buswidth 
            if (this->options & NAND_BUSWIDTH_16)
                column >>= 1;
            this->write_byte(mtd, column);      //写入列地址
        }
        if (page_addr != -1) {                  //写入页地址(分三个字节写入)
            this->write_byte(mtd, (unsigned char) (page_addr & 0xff));
            this->write_byte(mtd, (unsigned char) ((page_addr >> 8) & 0xff));
            // One more address cycle for devices > 32MiB 
            if (this->chipsize > (32 << 20))
                this->write_byte(mtd, (unsigned char) ((page_addr >> 16) & 0x0f));
        }
        // Latch in address 
        // 锁存地址 
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

    case NAND_CMD_RESET:      //复位操作
                              // 等待nand flash become ready
        if (this->dev_ready)  //判断nand flash 是否busy(1:ready 0:busy)
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
            udelay (this->chip_delay);//稍作延迟
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
        if (this->dev_ready(mtd))          //简单调用this->dev_ready(s3c2410_nand_devready)函数                                             等待nand flash become ready
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

// 等待知道命令传输完成，适用于檫除和写入命令 
static int nand_wait(struct mtd_info *mtd, struct nand_chip *this, int state)
{

    unsigned long    timeo = jiffies;
    int    status;
    
    if (state == FL_ERASING)
         timeo += (HZ * 400) / 1000;//檫除操作的话，时间相对要长一些
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
        // 等待nand flash become ready 
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
// * 检查nand flash中某一页是否为坏块
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
        // 发送读oob_data命令(oob_data的badblockpos (第6)位记录着坏块标志) 
        if (this->read_byte(mtd) != 0xff)//坏块
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
// * 标志坏块
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
    // 这个暂时不是很好说：内核维护一个标志bad block表，使用2bit来表示1block。
    // 这个表在开机的时候通过扫描nand flash每个block的头两页的oob数据来生成，
    // 发现坏块后至相应的block标志位为非零(有时候至3，但有时候至1，还没搞明白有什么不同)
     

    // Do we have a flash based bad block table ? 
    if (this->options & NAND_USE_FLASH_BBT)//samsun nand flash不属于这种，暂时不去研究，以后同
        return nand_update_bbt (mtd, ofs);
        
    // We write two bytes, so we dont have to mess with 16 bit access 
    ofs += mtd->oobsize + (this->badblockpos & ~0x01);//???????????????
    return nand_write_oob (mtd, ofs , 2, &retlen, buf);
}

//*
// * nand_verify_buf - [DEFAULT] Verify chip data against buffer
// * 检验nand flash与buffer的数据是否一致 
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
    } else {      //samsun nand flash的坏块表不存在与nand flash里面，需要扫描来生成。
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
    // 2bit per block=(2/8)byte per block，所以上面要多右移2位 
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
    // 分配1 block所需要的oob data空间 
    len = (1 << this->bbt_erase_shift);
    len += (len >> this->page_shift) * mtd->oobsize;
    buf = kmalloc (len, GFP_KERNEL);
    if (!buf) {
        printk (KERN_ERR "nand_bbt: Out of memory\n");
        kfree (this->bbt);
        this->bbt = NULL;
        return -ENOMEM;
    }
    
    //由于td、md均为NULL，一下函数基本不起作用，先不去研究它
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
    //我们只需要扫描oob data，不需要扫描全部(512+16bytes的数据)
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

    if (bd->options & NAND_BBT_SCANALLPAGES)//扫描所有都页
        len = 1 << (this->bbt_erase_shift - this->page_shift);//求出每block所含的page数
    else {
        if (bd->options & NAND_BBT_SCAN2NDPAGE)//只检查2 page
            len = 2;
        else    
            len = 1;//只检查1 page
    }

    if (!(bd->options & NAND_BBT_SCANEMPTY)) {
        // We need only read few bytes from the OOB area 
        // 我们只需要检查OOB的某些数据 
        scanlen = ooblen = 0;
        readlen = bd->len;
    } else {
        // Full page content should be read 
        // 读取整页内容 
        scanlen    = mtd->oobblock + mtd->oobsize;
        readlen = len * mtd->oobblock;
        ooblen = len * mtd->oobsize;
    }

    if (chip == -1) {
        // Note that numblocks is 2 * (real numblocks) here, see i+=2 below as it
        // * makes shifting and masking less painful 
        // 计算出nand flash所包含都block数目(注意这里总数目经过林乘2操作)
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
        
        if (bd->options & NAND_BBT_SCANEMPTY)        //整页数据读取
            if ((ret = nand_read_raw (mtd, buf, from, readlen, ooblen)))
                return ret;

        for (j = 0; j < len; j++) {
            if (!(bd->options & NAND_BBT_SCANEMPTY)) {
                size_t retlen;
                
                // Read the full oob until read_oob is fixed to 
                // * handle single byte reads for 16 bit buswidth 
                // 读取当前页的oob区的所有数据 
                ret = mtd->read_oob(mtd, from + j * mtd->oobblock,
                            mtd->oobsize, &retlen, buf);
                if (ret)
                    return ret;
                // 检查oob data的bad block标志位，判断是否是坏块 
                if (check_short_pattern (buf, bd)) {
                    this->bbt[i >> 3] |= 0x03 << (i & 0x6);
                // 注意：这里i=实际值*2。由于一个block的状态用2bit来表示，那么一个字节可以存放4个block的状态。
                   这里i>>3刚好是实际block/4，4个block的状态刚好存放在this->bbt所指向的一个字节里面 
                 
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
        i += 2;//更新block的序号
        from += (1 << this->bbt_erase_shift);//更新nand flash的地址
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

//附录：
///arch/arm/mach-s3c2410/dev.c文件：

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

//nand_flash_ids表
///driver/mtd/nand/nand_ids.c文件：
struct nand_flash_dev nand_flash_ids[] = {
................................................................................
    {"NAND 64MiB 3,3V 8-bit",     0x76, 512, 64, 0x4000, 0},
................................................................................
};
//注：
//这里只列出常用的samsun 64M Nand Flash的资料，对应的信息请看该结构体的定义：
struct nand_flash_dev {
    char *name;
    int id;
    unsigned long pagesize;
    unsigned long chipsize;
    unsigned long erasesize;
    unsigned long options;
};
//可知该nand flash 设备ID号为0x76，页大小为512，大小为64(M)，檫除单元大小为16(K)。






//MTD原始设备与FLASH硬件驱动的对话-续 
//上一个贴由下到上的介绍了FLASH硬件驱动是如何与MTD原始设备建立联系的，现在再由上到下的研究一下是如何通过MTD原始设备来访问FLASH硬件驱动的。
//
//首先分析一下如何通过MTD原始设备进而通过FLASH硬件驱动来读取FLASH存储器的数据。
//
//引用自<<Linux系统移植>>一文：
//
//"读Nand Flash：
//当对nand flash的设备文件(nand flash在/dev下对应的文件)执行系统调用read(),或在某个文件系统中对该
//设备进行读操作时. 会调用struct mtd_info中的read方法,他们缺省调用函数为nand_read(),在
//drivers/mtd/nand/nand_base.c中定义.nand_read()调用nand_do_read_ecc(),执行读操作. 在
//nand_do_read_ecc()函数中,主要完成如下几项工作：
// 1.会调用在nand flash驱动中对struct nand_chip重载的select_chip方法,即
//s3c2410_nand_select_chip()选择要操作的MTD芯片.
// 2. 会调用在struct nand_chip中系统缺省的方法cmdfunc发送读命令到nand flash.
// 3. 会调用在nand flash驱动中对struct nand_chip重载的read_buf(),即s3c2410_nand_read_buf()
//从Nand Flash的控制器的数据寄存器中读出数据.
// 4. 如果有必要的话,会调用在nand flash驱动中对struct nand_chip重载的
//enable_hwecc,correct_data以及calculate_ecc方法,进行数据ECC校验。"
//
//下面研究一下其中的细节：
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
//注：
//    以参数oob_buf为NULL，flags为0xff调用nand_do_read_ecc函数。

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
    u_char *data_poi, *oob_data = oob_buf;//目前oob_data指针为空，以后会去修改它。
    u_char ecc_calc[32];//该数组用于存放计算出来的ecc结果
    u_char ecc_code[32];//该数组用于存放oob中ecc部分的数据
    int eccmode, eccsteps;//eccmode存放ecc的类型(ECC_SOFT)；
                            eccsteps用于记录一个page所需的ecc校验次数(2)。
    int    *oob_config, datidx;
    int    blockcheck = (1 << (this->phys_erase_shift - this->page_shift)) - 1;
    int    eccbytes;
    int    compareecc = 1;//是否需要ecc标志(如果设置成ECC_NONE，这个标志将被清0)
    int    oobreadlen;


    DEBUG (MTD_DEBUG_LEVEL3, "nand_read_ecc: from = 0x%08x, len = %i\n", (unsigned int) from, (int) len);

    // Do not allow reads past end of device 
    // 不允许超越设备容量的读操作 
    if ((from + len) > mtd->size) {
        DEBUG (MTD_DEBUG_LEVEL0, "nand_read_ecc: Attempt read beyond end of device\n");
        *retlen = 0;
        return -EINVAL;
    }

    // Grab the lock and see if the device is available 
    // 获取自旋锁，等待设备可用并获取其控制权 
    if (flags & NAND_GET_DEVICE)
        nand_get_device (this, mtd, FL_READING);

    // Autoplace of oob data ? Use the default placement scheme 
    if (oobsel->useecc == MTD_NANDECC_AUTOPLACE)
        oobsel = this->autooob;
    // 
    // * 感觉这一步有点多余，因为nand_scan中已经调用了以下代码： 
    // * memcpy(&mtd->oobinfo, this->autooob, sizeof(mtd->oobinfo));
    // * 把this->autooob的内容拷贝到mtd->oobinfo中了
     
        
    eccmode = oobsel->useecc ? this->eccmode : NAND_ECC_NONE;
    oob_config = oobsel->eccpos;//记录ecc在oob数据中的位置

    // Select the NAND device 
    chipnr = (int)(from >> this->chip_shift);
    this->select_chip(mtd, chipnr);//选择nand flash芯片(在s3c2410 nand flash控制器中为空操作)

    // First we calculate the starting page 
    // 首先，我们计算出开始页码 
    realpage = (int) (from >> this->page_shift);
    page = realpage & this->pagemask;

    // Get raw starting column 
    // 其次，我们计算页内偏址 
    col = from & (mtd->oobblock - 1);

    end = mtd->oobblock;//页大小(512)
    ecc = this->eccsize;//ecc保护下的数据大小(256)
    eccbytes = this->eccbytes;//ecc所占的字节数(3)
    
    if ((eccmode == NAND_ECC_NONE) || (this->options & NAND_HWECC_SYNDROME))
        compareecc = 0;//如果设置为关闭ECC或写操作才需要ECC，那把ecc给禁用(现在可是读操作^_^)

    oobreadlen = mtd->oobsize;//16
    if (this->options & NAND_HWECC_SYNDROME) 
        oobreadlen -= oobsel->eccbytes;

    // Loop until all data read 
    while (read < len) {
        
        int aligned = (!col && (len - read) >= end);
        // 
        // * If the read is not page aligned, we have to read into data buffer
        // * due to ecc, else we read into return buffer direct
        // * 如果要读的位置不是页对齐都话，那么只要先把整页读出来，
        // * 取出所需要读取的数据，然后修改读位置，那么以后的读操作都是页对齐的了。
         
        if (aligned)
            data_poi = &buf[read];
        else 
            data_poi = this->data_buf;
        
        // Check, if we have this page in the buffer 
        // *
        // * FIXME: Make it work when we must provide oob data too,
        // * check the usage of data_buf oob field
        // * 如果我们所需要的数据还存在于缓冲中都话：
        // * 1 如果读位置页对齐，我们只要把缓冲中的数据直接拷贝到data_poi(buf[read])中即可(因为数据存在与缓存中，所以也无需要考虑ecc问题)
        // * 2 如果读位置不是页对齐，什么读不要作，让其继续留在缓存(data_buf)中，以后会从data_poi(指向缓存data_buf)中提取所需要的数据。
         
        if (realpage == this->pagebuf && !oob_buf) {
            // aligned read ? 
            if (aligned)
                memcpy (data_poi, this->data_buf, end);
            goto readdata;
        }

        // Check, if we must send the read command 
        // 发送读命令，页地址为page，列地址为0x00 
        if (sndcmd) {
            this->cmdfunc (mtd, NAND_CMD_READ0, 0x00, page);
            sndcmd = 0;
        }    

        // get oob area, if we have no oob buffer from fs-driver 
        if (!oob_buf || oobsel->useecc == MTD_NANDECC_AUTOPLACE ||
            oobsel->useecc == MTD_NANDECC_AUTOPL_USR)
            oob_data = &this->data_buf[end];//以上情况，oob_data暂存在data_buf缓存中

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
            this->read_buf(mtd, data_poi, end);//读取数据到data_poi
            for (i = 0, datidx = 0; eccsteps; eccsteps--, i+=3, datidx += ecc) 
                this->calculate_ecc(mtd, &data_poi[datidx], &ecc_calc[i]);
            // 计算出读取到data_poi的数据的ecc值，并存放到ecc_calc数组中。
            // * 因为读都数据有一页大小(512)，需要分别对其上半部和下半部分计算一次ecc值，并分开存放到ecc_calc数组相应都位置中。
             
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
        //读取oob_data存放到oob_data[mtd->oobsize - oobreadlen]，在这里是data_buf[end]中

        // Skip ECC check, if not requested (ECC_NONE or HW_ECC with syndromes) 
        // 跳过ecc检测 
        if (!compareecc)
            goto readoob;    
        
        // Pick the ECC bytes out of the oob data 
        // 从刚读出来都oob_data中取出ecc数据(在这里是前三个字节) 
        for (j = 0; j < oobsel->eccbytes; j++)
            ecc_code[j] = oob_data[oob_config[j]];

        // correct data, if neccecary 
        for (i = 0, j = 0, datidx = 0; i < this->eccsteps; i++, datidx += ecc) {
            ecc_status = this->correct_data(mtd, &data_poi[datidx], &ecc_code[j], &ecc_calc[j]);
            // 拿前面计算出来都ecc_cal数组都数据与读出来的ecc数据作比较，并尝试修正错误(但不保证能修复，具体看返回值) 
            
            // Get next chunk of ecc bytes 
            j += eccbytes;
            
            // Check, if we have a fs supplied oob-buffer, 
            // * This is the legacy mode. Used by YAFFS1
            // * Should go away some day
             
            if (oob_buf && oobsel->useecc == MTD_NANDECC_PLACE) { 
                int *p = (int *)(&oob_data[mtd->oobsize]);
                p[i] = ecc_status;
            }
            // 很不幸，ecc检测发现错误且未能修复，报告错误     
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
        // * 读位置不是页对齐，从data_poi(data_buf中)提取所需要都数据
         
        if (!aligned) { 
            for (j = col; j < end && read < len; j++)
                buf[read++] = data_poi[j];//read自增
            this->pagebuf = realpage;    
        } else        
            read += mtd->oobblock;//整页读取，计数值加上整页的数目(512)

        // Apply delay or wait for ready/busy pin 
        // * Do this before the AUTOINCR check, so no problems
        // * arise if a chip which does auto increment
        // * is marked as NOAUTOINCR by the board driver.
        
        if (!this->dev_ready) 
            udelay (this->chip_delay);
        else
            nand_wait_ready(mtd);
            
        if (read == len)//所需数据读完都情况，退出读循环。
            break;    

        // For subsequent reads align to page boundary. 
        col = 0;//对于读位置不是页对齐都情况，前面已对其进行林相应都处理，现在读位置变得页对齐了。
        // Increment page address 
        realpage++;//页地址加1,读取下一页。

        page = realpage & this->pagemask;
        // Check, if we cross a chip boundary 
        if (!page) {
            chipnr++;
            this->select_chip(mtd, -1);
            this->select_chip(mtd, chipnr);
        }
        // Check, if the chip supports auto page increment 
        // * or if we have hit a block boundary. 
        // * 如果芯片支持页自增操作,且未到block boundary(15)的话，不用再发送读命令
         
        if (!NAND_CANAUTOINCR(this) || !(page & blockcheck))
            sndcmd = 1;                
    }

    // Deselect and wake up anyone waiting on the device 
    if (flags & NAND_GET_DEVICE)
        nand_release_device(mtd);//放弃对设备都控制权，好让其它进程获取并占有它

    //
    // * Return success, if no ECC failures, else -EBADMSG
    // * fs driver will take care of that, because
    // * retlen == desired len and result == -EBADMSG
     
    *retlen = read;
    return ecc_failed ? -EBADMSG : 0;
}

//好的，接着研究一下如何通过MTD原始设备进而通过FLASH硬件驱动向FLASH存储器写数据。
//
//引用自<<Linux系统移植>>一文：
//
//写Nand Flash
//当对nand flash的设备文件(nand flash在/dev下对应的文件)执行系统调用write(),或在某个文件系统中对该设备
//进行读操作时, 会调用struct mtd_info中write方法,他们缺省调用函数为nand_write(),这两个函数在
//drivers/mtd/nand/nand_base.c中定义. nand_write()调用nand_write_ecc(),执行写操作.在
//nand_do_write_ecc()函数中,主要完成如下几项工作：
// 1. 会调用在nand flash驱动中对struct nand_chip重载的select_chip方法,即
//s3c2410_nand_select_chip()选择要操作的MTD芯片.
// 2. 调用nand_write_page()写一个页.
// 3. 在nand_write_page()中,会调用在struct nand_chip中系统缺省的方法cmdfunc发送写命令
//到nand flash.
// 4. 在nand_write_page()中,会调用在nand flash驱动中对struct nand_chip重载的
//write_buf(),即s3c2410_nand_write_buf()从Nand Flash的控制器的数据寄存器中写入数据.
//5. 在nand_write_page()中,会调用在nand flash驱动中对struct nand_chip重载waitfunc方法,
//该方法调用系统缺省函数nand_wait(),该方法获取操作状态,并等待nand flash操作完成.等
//待操作完成,是调用nand flash驱动中对struct nand_chip中重载的dev_ready方法,即
//s3c2410_nand_devready()函数.
//
//下面研究一下其中的细节：
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
注：
    以参数eccbuf、oobsel为NULL，调用nand_write_ecc函数。

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
    // 超越nand flash容量的写操作是不允许的 
    if ((to + len) > mtd->size) {
        DEBUG (MTD_DEBUG_LEVEL0, "nand_write_ecc: Attempt to write past end of page\n");
        return -EINVAL;
    }

    // reject writes, which are not page aligned 
    // 不按页对齐的写操作同样是不允许的    
    if (NOTALIGNED (to) || NOTALIGNED(len)) {
        printk (KERN_NOTICE "nand_write_ecc: Attempt to write not page aligned data\n");
        return -EINVAL;
    }

    // Grab the lock and see if the device is available 
    // 获取设备的控制权 
    nand_get_device (this, mtd, FL_WRITING);

    // Calculate chipnr 
    // 
    // * 存在多片flash的情况下，计算出所要写的是哪片flash？
    // * (当然，像我的板，只用一片nand flash，所以这个操作是不必要的)
     
    chipnr = (int)(to >> this->chip_shift);
    // Select the NAND device 
    // 片选操作 
    this->select_chip(mtd, chipnr);

    // Check, if it is write protected 
    // 如果nand flash写保护，当然不能再写了 
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
    totalpages = len >> this->page_shift;//计算所要读取的数据长度共有多少页
    page = (int) (to >> this->page_shift);//计算数据所要写到的开始页码
    // Invalidate the page cache, if we write to the cached page 
    // 如果缓存保存的数据在我们要写数据的范围内，把缓存里的数据设置为不可用???? 
    if (page <= this->pagebuf && this->pagebuf < (page + totalpages))  
        this->pagebuf = -1;
    
    // Set it relative to chip 
    page &= this->pagemask;
    startpage = page;
    // Calc number of pages we can write in one go 
    numpages = min (ppblock - (startpage  & (ppblock - 1)), totalpages);//计算出本block中允许被写的页数
    oobbuf = nand_prepare_oobbuf (mtd, eccbuf, oobsel, autoplace, numpages);//先不深入研究~_~
    bufstart = (u_char *)buf;//获取所要写数据的地址

    // Loop until all data is written 
    // 循环进行写操作 
    while (written < len) {

        this->data_poi = (u_char*) &buf[written];//先把所要写的数据缓冲到data_poi下
        // Write one page. If this is the last page to write
        // * or the last page in this block, then use the
        // * real pageprogram command, else select cached programming
        // * if supported by the chip.
        // * 如果这是所写数据的最后一个页或许这是所写block的最后一个页，调用nand flash的          
        // * pageprogram指令，真正把数据写入nand flash中(nand flash的最小擦除单元为block)
         
        ret = nand_write_page (mtd, this, page, &oobbuf[oob], oobsel, (--numpages > 0));
        if (ret) {
            DEBUG (MTD_DEBUG_LEVEL0, "nand_write_ecc: write_page failed %d\n", ret);
            goto out;
        }    
        // Next oob page 
        oob += mtd->oobsize;
        // Update written bytes count 
        // 更新写入计数值 
        written += mtd->oobblock;
        if (written == len)//写入完毕，退出 
            goto cmp;
        
        // Increment page address 
        page++;//下一页

        // Have we hit a block boundary ? Then we have to verify and
        // * if verify is ok, we have to setup the oob buffer for
        // * the next pages.
        // * 暂时不是很明白，需要先搞明白nand_prepare_oobbuf函数的作用
        
        if (!(page & (ppblock - 1))){
            int ofs;
            this->data_poi = bufstart;//怀疑nand_verify_pages用到
            ret = nand_verify_pages (mtd, this, startpage, 
                page - startpage,
                oobbuf, oobsel, chipnr, (eccbuf != NULL));//一页写完，检查数据
            if (ret) {
                DEBUG (MTD_DEBUG_LEVEL0, "nand_write_ecc: verify_pages failed %d\n", ret);
                goto out;
            }    
            *retlen = written;

            ofs = autoplace ? mtd->oobavail : mtd->oobsize;
            if (eccbuf)
                eccbuf += (page - startpage) * ofs;
            totalpages -= page - startpage;//更新需要写的页数
            numpages = min (totalpages, ppblock);//更新可以写的页数
            page &= this->pagemask;//更新页码
            startpage = page;//更新开始页码
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
    this->data_poi = bufstart;//怀疑nand_verify_pages用到
     ret = nand_verify_pages (mtd, this, startpage, totalpages,
        oobbuf, oobsel, chipnr, (eccbuf != NULL));
    if (!ret)
        *retlen = written;
    else    
        DEBUG (MTD_DEBUG_LEVEL0, "nand_write_ecc: verify_pages failed %d\n", ret);

out:
    // Deselect and wake up anyone waiting on the device 
    nand_release_device(mtd);//放弃对设备的控制权

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
    cached = 0;//在高版本的内核下找到这样的解释：
    //
    // * Cached progamming disabled for now, Not sure if its worth the
    // * trouble. The speed gain is not very impressive. (2.3->2.6Mib/s)
     
    
    // Send command to begin auto page programming 
    // 发送页编程指令 
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
            this->calculate_ecc(mtd, &this->data_poi[datidx], ecc_code);//计算出一页的ecc数据
            for (i = 0; i < 3; i++, eccidx++)
                oob_buf[oob_config[eccidx]] = ecc_code[i];//存放到ecc_code数组中
            datidx += this->eccsize;
        }
        this->write_buf(mtd, this->data_poi, mtd->oobblock);//调用FLASH硬件驱动层进行写操作
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
        this->write_buf(mtd, oob_buf, mtd->oobsize);//写oob data，主要把上面计算的ecc值写进去

    // Send command to actually program the data 
    this->cmdfunc (mtd, cached ? NAND_CMD_CACHEDPROG : NAND_CMD_PAGEPROG, -1, -1);

    if (!cached) {
        // call wait ready function 
        status = this->waitfunc (mtd, this, FL_WRITING);//等待写入完成

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
        // status = this->waitfunc (mtd, this, FL_CACHEDRPG);//cached的写操作暂时没用
    }
    return 0;    
}

