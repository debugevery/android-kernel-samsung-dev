/* arch/arm/plat-samsung/include/plat/ts.h
 *
 * Copyright (c) 2005 Arnaud Patard <arnaud.patard@rtp-net.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __MACH_TS_SMDKC110_H
#define __MACH_TS_SMDKC110_H

#ifdef CONFIG_HAS_WAKELOCK
//#include <linux/wakelock.h>
//#include <linux/earlysuspend.h>
#endif

enum s3c_adc_type {
	ADC_TYPE_0,
	ADC_TYPE_1,	/* S3C2416, S3C2450 */
	ADC_TYPE_2,	/* S3C64XX, S5PC1XX */
};

//�������ô�������Ϣ
struct s3c_ts_mach_info {

	int delay; //ADת����ʱ
	int presc; //��Ƶ
	int oversampling_shift; // ����������
	int resol_bit; //ת������
	enum s3c_adc_type s3c_adc_con;

};
//�ɼ���������Ϣ

struct s3c_ts_info {

	struct input_dev *dev;
	long xp; //x����λ��
	long yp; //y����λ��
	int count; //�ۼ�xp��yp���ݵĴ���
	int shift;
	char phys[32];
	int resol_bit; //ת������
	enum s3c_adc_type s3c_adc_con;
#ifdef CONFIG_HAS_WAKELOCK
        struct early_suspend early_suspend;
#endif
};

#endif /* __ASM_ARM_TS_H */
