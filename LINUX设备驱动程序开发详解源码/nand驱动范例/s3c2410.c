/* linux/drivers/mtd/nand/s3c2410.c
 *
 * Copyright (c) 2004,2005 Simtec Electronics
 *	http://www.simtec.co.uk/products/SWLINUX/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Samsung S3C2410/S3C240 NAND driver
 *
 * Changelog:
 *	21-Sep-2004  BJD  Initial version
 *	23-Sep-2004  BJD  Mulitple device support
 *	28-Sep-2004  BJD  Fixed ECC placement for Hardware mode
 *	12-Oct-2004  BJD  Fixed errors in use of platform data
 *	18-Feb-2005  BJD  Fix sparse errors
 *	14-Mar-2005  BJD  Applied tglx's code reduction patch
 *	02-May-2005  BJD  Fixed s3c2440 support
 *	02-May-2005  BJD  Reduced hwcontrol decode
 *	20-Jun-2005  BJD  Updated s3c2440 support, fixed timing bug
 *	08-Jul-2005  BJD  Fix OOPS when no platform data supplied
 *	20-Oct-2005  BJD  Fix timing calculation bug
 *
 * $Id: s3c2410.c,v 1.20 2005/11/07 11:14:31 gleixner Exp $
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
和NOR Flash非常类似，如图19.5所示，Linux内核在MTD
的 下层实现了通用的NAND 驱动 （ 主要 通过
drivers/mtd/nand/nand_base.c 文件实现） ，因此芯片级的 NAND 驱
动不再需要实现mtd_info中的read()、 write()、 read_oob()、 write_oob()
等成员函数，而主体转移到了nand_chip数据结构。 
MTD使用nand_chip数据结构表示一个NAND Flash芯片，
这个结构体中包含了关于NAND Flash的地址信息、 读写方法、
ECC 模式、硬件控制等一系列底层机制，其定义如代码清单
19.10所示。 

与 NOR Flash类似， 由于有了 MTD 层， 完成一个 NAND 
Flash 驱动在 Linux 中的工作量也很小，如图 19.6 所示，主
要的工作如下。 
（1）如果Flash要分区，则定义mtd_partition数组，将实际
电路板中Flash分区信息记录于其中。 
（2）在模块加载时分配和 nand_chip的内存， 根据目标板
NAND 控制器的特殊情况初始化 nand_chip 中的 hwcontrol()、
dev_ready()、 calculate_ecc()、 correct_data()、 read_byte()、 write_byte()
等成员函数（如果不赋值会使用nand_base.c中的默认函数） ，注意将mtd_info的priv置为nand_chip。 
如果使用软件 ECC，则不需要赋值 calculate_ecc()和 correct_data()成员，因为
NAND 核心层包含了相应的软件算法。如果使用 NAND 控制器的 ECC，应该自定义
calculate_ecc()函数，并在其中将硬件上产生的ECC字节返回到 ecc_code参数。 
（3） 以mtd_info为参数调用nand_scan()函数探测 NAND Flash的存在。 nand_scan()
函数的原型为： 
int nand_scan (struct mtd_info *mtd, int maxchips); 
nand_scan()函数会读取NAND芯片ID， 并根据mtd->priv即nand_chip中的成员初始
化mtd_info。 
（4）如果要分区，则以mtd_info和 mtd_partition为参数调用 add_mtd_partitions()，
添加分区信息。 
*/

//===============打开注释:回车  /*=====================================



//#include <config/mtd/nand/s3c2410/hwecc.h>
//#include <config/mtd/nand/s3c2410/debug.h>

#ifdef CONFIG_MTD_NAND_S3C2410_DEBUG
#define DEBUG
#endif

//#include <linux/module.h>
//#include <linux/types.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
//#include <linux/string.h>
//#include <linux/ioport.h>
//#include <linux/platform_device.h>
//#include <linux/delay.h>
//#include <linux/err.h>
//#include <linux/slab.h>
//#include <linux/clk.h>

//#include <linux/mtd/mtd.h>
//#include <linux/mtd/nand.h>
//#include <linux/mtd/nand_ecc.h>
//#include <linux/mtd/partitions.h>

//#include <asm/io.h>

//#include <asm/arch/regs-nand.h>
//#include <asm/arch/nand.h>

#define PFX "s3c2410-nand: "

#ifdef CONFIG_MTD_NAND_S3C2410_HWECC
static int hardware_ecc = 1;
#else
static int hardware_ecc = 0;
#endif

//// new oob placement block for use with hardware ecc generation
// 

static struct nand_oobinfo nand_hw_eccoob = {
	.useecc		= MTD_NANDECC_AUTOPLACE,
	.eccbytes	= 3,//ECC字节数为3 
	.eccpos		= {0, 1, 2 },//ECC放置位置在0、1、2 
	.oobfree	= { {8, 8} } //可自由使用的OOB区域 
};

// controller and mtd information 

struct s3c2410_nand_info;

struct s3c2410_nand_mtd {
	struct mtd_info			mtd;
	struct nand_chip		chip;
	struct s3c2410_nand_set		*set;
	struct s3c2410_nand_info	*info;
	int				scan_res;
};

// overview of the s3c2410 nand state 

struct s3c2410_nand_info {
	// mtd info 
	struct nand_hw_control		controller;
	struct s3c2410_nand_mtd		*mtds;
	struct s3c2410_platform_nand	*platform;

	// device info 
	struct device			*device;
	struct resource			*area;
	struct clk			*clk;
	void __iomem			*regs;
	int				mtd_count;

	unsigned char			is_s3c2440;
};

// conversion functions 

static struct s3c2410_nand_mtd *s3c2410_nand_mtd_toours(struct mtd_info *mtd)
{
	return container_of(mtd, struct s3c2410_nand_mtd, mtd);
}

static struct s3c2410_nand_info *s3c2410_nand_mtd_toinfo(struct mtd_info *mtd)
{
	return s3c2410_nand_mtd_toours(mtd)->info;
}

static struct s3c2410_nand_info *to_nand_info(struct platform_device *dev)
{
	return platform_get_drvdata(dev);
}

static struct s3c2410_platform_nand *to_nand_plat(struct platform_device *dev)
{
	return dev->dev.platform_data;
}

// timing calculations 

#define NS_IN_KHZ 1000000

static int s3c2410_nand_calc_rate(int wanted, unsigned long clk, int max)
{
	int result;

	result = (wanted * clk) / NS_IN_KHZ;
	result++;

	pr_debug("result %d from %ld, %d\n", result, clk, wanted);

	if (result > max) {
		printk("%d ns is too big for current clock rate %ld\n",
		       wanted, clk);
		return -1;
	}

	if (result < 1)
		result = 1;

	return result;
}

#define to_ns(ticks,clk) (((ticks) * NS_IN_KHZ) / (unsigned int)(clk))

// controller setup 

static int s3c2410_nand_inithw(struct s3c2410_nand_info *info,
			       struct platform_device *pdev)
{
	struct s3c2410_platform_nand *plat = to_nand_plat(pdev);
	unsigned long clkrate = clk_get_rate(info->clk);
	int tacls, twrph0, twrph1;
	unsigned long cfg;

	// calculate the timing information for the controller 

	clkrate /= 1000;	// turn clock into kHz for ease of use 

	if (plat != NULL) {
		tacls  = s3c2410_nand_calc_rate(plat->tacls, clkrate, 4);
		twrph0 = s3c2410_nand_calc_rate(plat->twrph0, clkrate, 8);
		twrph1 = s3c2410_nand_calc_rate(plat->twrph1, clkrate, 8);
	} else {
		// default timings 
		tacls = 4;
		twrph0 = 8;
		twrph1 = 8;
	}

	if (tacls < 0 || twrph0 < 0 || twrph1 < 0) {
		printk(KERN_ERR PFX "cannot get timings suitable for board\n");
		return -EINVAL;
	}

	printk(KERN_INFO PFX "Tacls=%d, %dns Twrph0=%d %dns, Twrph1=%d %dns\n",
	       tacls, to_ns(tacls, clkrate),
	       twrph0, to_ns(twrph0, clkrate),
	       twrph1, to_ns(twrph1, clkrate));

	if (!info->is_s3c2440) {
		cfg  = S3C2410_NFCONF_EN;
		cfg |= S3C2410_NFCONF_TACLS(tacls-1);
		cfg |= S3C2410_NFCONF_TWRPH0(twrph0-1);
		cfg |= S3C2410_NFCONF_TWRPH1(twrph1-1);
	} else {
		cfg   = S3C2440_NFCONF_TACLS(tacls-1);
		cfg  |= S3C2440_NFCONF_TWRPH0(twrph0-1);
		cfg  |= S3C2440_NFCONF_TWRPH1(twrph1-1);
	}

	pr_debug(PFX "NF_CONF is 0x%lx\n", cfg);

	writel(cfg, info->regs + S3C2410_NFCONF);
	return 0;
}

// select chip 
 // 选中芯片  
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

	if (chip == -1) { //不选中NAND芯片 
		cur |= bit; //nFCE位置1 
	} else { //选中1个NAND 
		 //NAND序号越界 
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

	writel(cur, reg); //写NFCONF寄存器 
}

// command and control functions
// *
// * Note, these all use tglx's method of changing the IO_ADDR_W field
// * to make the code simpler, and use the nand layer's code to issue the
// * command and address sequences via the proper IO ports.
// *

 // GPIO方式的硬件控制  
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
		chip->IO_ADDR_W = info->regs + S3C2410_NFCMD;
		break;

	case NAND_CTL_SETALE:
		chip->IO_ADDR_W = info->regs + S3C2410_NFADDR;
		break;

		// NAND_CTL_CLRCLE: 
		// NAND_CTL_CLRALE: 
	default:
		chip->IO_ADDR_W = info->regs + S3C2410_NFDATA;
		break;
	}
}

// command and control functions 

static void s3c2440_nand_hwcontrol(struct mtd_info *mtd, int cmd)
{
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	struct nand_chip *chip = mtd->priv;

	switch (cmd) {
	case NAND_CTL_SETNCE:
	case NAND_CTL_CLRNCE:
		printk(KERN_ERR "%s: called for NCE\n", __FUNCTION__);
		break;

	case NAND_CTL_SETCLE:
		chip->IO_ADDR_W = info->regs + S3C2440_NFCMD;
		break;

	case NAND_CTL_SETALE:
		chip->IO_ADDR_W = info->regs + S3C2440_NFADDR;
		break;

		// NAND_CTL_CLRCLE: 
		// NAND_CTL_CLRALE: 
	default:
		chip->IO_ADDR_W = info->regs + S3C2440_NFDATA;
		break;
	}
}

// s3c2410_nand_devready()
// *
// * returns 0 if the nand is busy, 1 if it is ready

 // 返回设备ready状态   // NAND Flash准备好 
static int s3c2410_nand_devready(struct mtd_info *mtd)
{
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	if (info->is_s3c2440)
		return readb(info->regs + S3C2440_NFSTAT) & S3C2440_NFSTAT_READY;
	return readb(info->regs + S3C2410_NFSTAT) & S3C2410_NFSTAT_BUSY;
}


// ECC handling functions 
 // 数据纠正 
static int s3c2410_nand_correct_data(struct mtd_info *mtd, u_char *dat,
				     u_char *read_ecc, u_char *calc_ecc)
{
	pr_debug("s3c2410_nand_correct_data(%p,%p,%p,%p)\n",
		 mtd, dat, read_ecc, calc_ecc);

	pr_debug("eccs: read %02x,%02x,%02x vs calc %02x,%02x,%02x\n",
		 read_ecc[0], read_ecc[1], read_ecc[2],
		 calc_ecc[0], calc_ecc[1], calc_ecc[2]);

	if (read_ecc[0] == calc_ecc[0] &&
	    read_ecc[1] == calc_ecc[1] &&
	    read_ecc[2] == calc_ecc[2])
		return 0;

	// we curently have no method for correcting the error 

	return -1;
}

// ECC functions
// *
// * These allow the s3c2410 and s3c2440 to use the controller's ECC
// * generator block to ECC the data as it passes through]

// 使能硬件ECC产生器 
static void s3c2410_nand_enable_hwecc(struct mtd_info *mtd, int mode)
{
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	unsigned long ctrl;

	ctrl = readl(info->regs + S3C2410_NFCONF);
	ctrl |= S3C2410_NFCONF_INITECC;
	writel(ctrl, info->regs + S3C2410_NFCONF);
}

static void s3c2440_nand_enable_hwecc(struct mtd_info *mtd, int mode)
{
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	unsigned long ctrl;

	ctrl = readl(info->regs + S3C2440_NFCONT);
	writel(ctrl | S3C2440_NFCONT_INITECC, info->regs + S3C2440_NFCONT);
}
 // 读取ECC  
static int s3c2410_nand_calculate_ecc(struct mtd_info *mtd,
				      const u_char *dat, u_char *ecc_code)
{
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	ecc_code[0] = readb(info->regs + S3C2410_NFECC + 0);
	ecc_code[1] = readb(info->regs + S3C2410_NFECC + 1);
	ecc_code[2] = readb(info->regs + S3C2410_NFECC + 2);

	pr_debug("calculate_ecc: returning ecc %02x,%02x,%02x\n",
		 ecc_code[0], ecc_code[1], ecc_code[2]);

	return 0;
}


static int s3c2440_nand_calculate_ecc(struct mtd_info *mtd,
				      const u_char *dat, u_char *ecc_code)
{
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	unsigned long ecc = readl(info->regs + S3C2440_NFMECC0);

	ecc_code[0] = ecc;
	ecc_code[1] = ecc >> 8;
	ecc_code[2] = ecc >> 16;

	pr_debug("calculate_ecc: returning ecc %02x,%02x,%02x\n",
		 ecc_code[0], ecc_code[1], ecc_code[2]);

	return 0;
}


// over-ride the standard functions for a little more speed. We can
// * use read/write block to move the data buffers to/from the controller

 // 读NAND中的数据到缓冲区  
static void s3c2410_nand_read_buf(struct mtd_info *mtd, u_char *buf, int len)
{
	struct nand_chip *this = mtd->priv;
	readsb(this->IO_ADDR_R, buf, len);
}

 // 写缓冲区的数据到NAND Flash中  
static void s3c2410_nand_write_buf(struct mtd_info *mtd,
				   const u_char *buf, int len)
{
	struct nand_chip *this = mtd->priv;
	writesb(this->IO_ADDR_W, buf, len);
}

// device management functions 

static int s3c2410_nand_remove(struct platform_device *pdev)
{
	struct s3c2410_nand_info *info = to_nand_info(pdev);

	platform_set_drvdata(pdev, NULL);

	if (info == NULL)
		return 0;

	// first thing we need to do is release all our mtds
	 * and their partitions, then go through freeing the
	 * resources used
	 
	 // 释放所有的MTD设备和分区   
	if (info->mtds != NULL) {
		struct s3c2410_nand_mtd *ptr = info->mtds;
		int mtdno;

		for (mtdno = 0; mtdno < info->mtd_count; mtdno++, ptr++) {
			pr_debug("releasing mtd %d (%p)\n", mtdno, ptr);
			nand_release(&ptr->mtd);
		}

		kfree(info->mtds);
	}

	// free the common resources 
	 // 释放公用资源 
	if (info->clk != NULL && !IS_ERR(info->clk)) {
		clk_disable(info->clk);
		clk_put(info->clk);
	}

	if (info->regs != NULL) {
		iounmap(info->regs);
		info->regs = NULL;
	}

	if (info->area != NULL) {
		release_resource(info->area);
		kfree(info->area);
		info->area = NULL;
	}

	kfree(info);

	return 0;
}

#ifdef CONFIG_MTD_PARTITIONS //如果配置了MTD分区支持 
static int s3c2410_nand_add_partition(struct s3c2410_nand_info *info,
				      struct s3c2410_nand_mtd *mtd,
				      struct s3c2410_nand_set *set)
{
	if (set == NULL)
		return add_mtd_device(&mtd->mtd);

	if (set->nr_partitions > 0 && set->partitions != NULL) {
		return add_mtd_partitions(&mtd->mtd, //添加MTD设备 
					  set->partitions,
					  set->nr_partitions);  //添加分区 
	}

	return add_mtd_device(&mtd->mtd);
}
#else//内核没有配置MTD分区支持 
static int s3c2410_nand_add_partition(struct s3c2410_nand_info *info,
				      struct s3c2410_nand_mtd *mtd,
				      struct s3c2410_nand_set *set)
{
	return add_mtd_device(&mtd->mtd);//添加MTD设备 
}
#endif

// s3c2410_nand_init_chip
// *
// * init a single instance of an chip


static void s3c2410_nand_init_chip(struct s3c2410_nand_info *info,
				   struct s3c2410_nand_mtd *nmtd,
				   struct s3c2410_nand_set *set)
{
	struct nand_chip *chip = &nmtd->chip;
	 // 初始化nand_chip  
	chip->IO_ADDR_R	   = info->regs + S3C2410_NFDATA; // 设置NAND Flash的I/O基地址 
	chip->IO_ADDR_W    = info->regs + S3C2410_NFDATA; // 设置NAND Flash的I/O基地址 
	chip->hwcontrol    = s3c2410_nand_hwcontrol;  // 硬件控制函数  
	chip->dev_ready    = s3c2410_nand_devready; // 初始化设备ready函数  
	chip->write_buf    = s3c2410_nand_write_buf; // 写缓冲区的数据到NAND Flash中  
	chip->read_buf     = s3c2410_nand_read_buf;  // 读NAND中的数据到缓冲区  
	chip->select_chip  = s3c2410_nand_select_chip; // 获得私有数据（nand_chip）指针  
	chip->chip_delay   = 50;  // 从数据手册获知命令延迟时间  
	chip->priv	   = nmtd;
	chip->options	   = 0;
	chip->controller   = &info->controller;

	if (info->is_s3c2440) {
		chip->IO_ADDR_R	 = info->regs + S3C2440_NFDATA;
		chip->IO_ADDR_W  = info->regs + S3C2440_NFDATA;
		chip->hwcontrol  = s3c2440_nand_hwcontrol;
	}

	nmtd->info	   = info;
	nmtd->mtd.priv	   = chip;
	nmtd->set	   = set;

	if (hardware_ecc) { //如果采用硬件ECC 
		chip->correct_data  = s3c2410_nand_correct_data;
		chip->enable_hwecc  = s3c2410_nand_enable_hwecc;
		chip->calculate_ecc = s3c2410_nand_calculate_ecc;
		chip->eccmode	    = NAND_ECC_HW3_512; //512字节产生3字节的ECC码
		chip->autooob       = &nand_hw_eccoob;

		if (info->is_s3c2440) {
			chip->enable_hwecc  = s3c2440_nand_enable_hwecc;
			chip->calculate_ecc = s3c2440_nand_calculate_ecc;
		}
	} else {  //使用软件ECC
		chip->eccmode	    = NAND_ECC_SOFT;
	}
}

// s3c2410_nand_probe
// *
// * called by device layer when it finds a device matching
// * one our driver can handled. This code checks to see if
// * it can allocate all necessary resources then calls the
// * nand layer to look for devices


static int s3c24xx_nand_probe(struct platform_device *pdev, int is_s3c2440)
{
	struct s3c2410_platform_nand *plat = to_nand_plat(pdev);
	struct s3c2410_nand_info *info;
	struct s3c2410_nand_mtd *nmtd;
	struct s3c2410_nand_set *sets;
	struct resource *res;
	int err = 0;
	int size;
	int nr_sets;
	int setno;

	pr_debug("s3c2410_nand_probe(%p)\n", pdev);

	info = kmalloc(sizeof(*info), GFP_KERNEL);
	if (info == NULL) {
		dev_err(&pdev->dev, "no memory for flash info\n");
		err = -ENOMEM;
		goto exit_error;
	}

	memzero(info, sizeof(*info));
	platform_set_drvdata(pdev, info);

	spin_lock_init(&info->controller.lock);
	init_waitqueue_head(&info->controller.wq);

	// get the clock source and enable it 
 	// 获得时钟源并使能   
	info->clk = clk_get(&pdev->dev, "nand");
	if (IS_ERR(info->clk)) {
		dev_err(&pdev->dev, "failed to get clock");
		err = -ENOENT;
		goto exit_error;
	}

	clk_enable(info->clk);

	// allocate and map the resource 
	 // 分配并映射资源  
	// currently we assume we have the one resource 
	res  = pdev->resource;
	size = res->end - res->start + 1; //I/O内存大小 

	info->area = request_mem_region(res->start, size, pdev->name);//申请I/O内存 

	if (info->area == NULL) {
		dev_err(&pdev->dev, "cannot reserve register region\n");
		err = -ENOENT;
		goto exit_error;
	}

	info->device     = &pdev->dev;
	info->platform   = plat;
	info->regs       = ioremap(res->start, size); //寄存器地址ioremap 
	info->is_s3c2440 = is_s3c2440;

	if (info->regs == NULL) {
		dev_err(&pdev->dev, "cannot reserve register region\n");
		err = -EIO;
		goto exit_error;
	}

	dev_dbg(&pdev->dev, "mapped registers at %p\n", info->regs);

	// initialise the hardware 
	  // 初始化硬件  
	err = s3c2410_nand_inithw(info, pdev);
	if (err != 0)
		goto exit_error;

	sets = (plat != NULL) ? plat->sets : NULL;
	nr_sets = (plat != NULL) ? plat->nr_sets : 1;

	info->mtd_count = nr_sets;

	// allocate our information 
	 // 分配s3c2410 nand_info中s3c2410_nand_mtd的内存 
	size = nr_sets * sizeof(*info->mtds);
	info->mtds = kmalloc(size, GFP_KERNEL);
	if (info->mtds == NULL) {
		dev_err(&pdev->dev, "failed to allocate mtd storage\n");
		err = -ENOMEM;
		goto exit_error;
	}

	memzero(info->mtds, size);

	// initialise all possible chips 
	  // 初始化所有可能存在的芯片  
	nmtd = info->mtds;

	for (setno = 0; setno < nr_sets; setno++, nmtd++) {
		pr_debug("initialising set %d (%p, info %p)\n",
			 setno, nmtd, info);

		s3c2410_nand_init_chip(info, nmtd, sets);

		nmtd->scan_res = nand_scan(&nmtd->mtd, // 扫描Flash,初始化mtd_info ,扫描以确定设备的存在  
					   (sets) ? sets->nr_chips : 1);

		if (nmtd->scan_res == 0) { //添加分区 
			s3c2410_nand_add_partition(info, nmtd, sets);
		}

		if (sets != NULL)
			sets++;
	}

	pr_debug("initialised ok\n");
	return 0;

 exit_error:
	s3c2410_nand_remove(pdev);

	if (err == 0)
		err = -EINVAL;
	return err;
}

// driver device registration 

static int s3c2410_nand_probe(struct platform_device *dev)
{
	return s3c24xx_nand_probe(dev, 0);
}

static int s3c2440_nand_probe(struct platform_device *dev)
{
	return s3c24xx_nand_probe(dev, 1);
}

static struct platform_driver s3c2410_nand_driver = {
	.probe		= s3c2410_nand_probe,
	.remove		= s3c2410_nand_remove,
	.driver		= {
		.name	= "s3c2410-nand",
		.owner	= THIS_MODULE,
	},
};

static struct platform_driver s3c2440_nand_driver = {
	.probe		= s3c2440_nand_probe,
	.remove		= s3c2410_nand_remove,
	.driver		= {
		.name	= "s3c2440-nand",
		.owner	= THIS_MODULE,
	},
};

static int __init s3c2410_nand_init(void)
{
	printk("S3C24XX NAND Driver, (c) 2004 Simtec Electronics\n");

	platform_driver_register(&s3c2440_nand_driver);
	return platform_driver_register(&s3c2410_nand_driver);
}

static void __exit s3c2410_nand_exit(void)
{
	platform_driver_unregister(&s3c2440_nand_driver);
	platform_driver_unregister(&s3c2410_nand_driver);
}

//module_init(s3c2410_nand_init);
//module_exit(s3c2410_nand_exit);

//MODULE_LICENSE("GPL");
//MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
//MODULE_DESCRIPTION("S3C24XX MTD NAND driver");

