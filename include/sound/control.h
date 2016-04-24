#ifndef __SOUND_CONTROL_H
#define __SOUND_CONTROL_H

/*
 *  Header file for control interface
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *Control接口主要让用户空间的应用程序（alsa-lib）可以访问和控制音频codec芯片中的多路开关，滑动控件等。对于Mixer（混音）来说，
 Control接口显得尤为重要，从ALSA 0.9.x版本开始，所有的mixer工作都是通过control接口的API来实现的。

ALSA已经为AC97定义了完整的控制接口模型，如果你的Codec芯片只支持AC97接口，你可以不用关心本节的内容。
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

//#include <sound/asound.h>

#define snd_kcontrol_chip(kcontrol) ((kcontrol)->private_data)

struct snd_kcontrol;
typedef int (snd_kcontrol_info_t) (struct snd_kcontrol * kcontrol, struct snd_ctl_elem_info * uinfo);
typedef int (snd_kcontrol_get_t) (struct snd_kcontrol * kcontrol, struct snd_ctl_elem_value * ucontrol);
typedef int (snd_kcontrol_put_t) (struct snd_kcontrol * kcontrol, struct snd_ctl_elem_value * ucontrol);
typedef int (snd_kcontrol_tlv_rw_t)(struct snd_kcontrol *kcontrol,
				    int op_flag, /* 0=read,1=write,-1=command */
				    unsigned int size,
				    unsigned int __user *tlv);

/*iface字段指出了control的类型，alsa定义了几种类型（SNDDRV_CTL_ELEM_IFACE_XXX），常用的类型是MIXER，当然也可以定义属于全局的CARD类型，也可以定义属于某类设备的类型，例如HWDEP，PCMRAWMIDI，TIMER等，这时需要在device和subdevice字段中指出卡的设备逻辑编号。
name字段是该control的名字，从ALSA 0.9.x开始，control的名字是变得比较重要，因为control的作用是按名字来归类的。ALSA已经预定义了一些control的名字，我们再Control Name一节详细讨论。
index字段用于保存该control的在该卡中的编号。如果声卡中有不止一个codec，每个codec中有相同名字的control，这时我们可以通过index来区分这些controls。当index为0时，则可以忽略这种区分策略。
access字段包含了该control的访问类型。每一个bit代表一种访问类型，这些访问类型可以多个“或”运算组合在一起。
private_value字段包含了一个任意的长整数类型值。该值可以通过info，get，put这几个回调函数访问。你可以自己决定如何使用该字段，例如可以把它拆分成多个位域，又或者是一个指针，指向某一个数据结构。
tlv字段为该control提供元数据。
*/
struct snd_kcontrol_new {//控制接口
	snd_ctl_elem_iface_t iface;	/* interface identifier */
	unsigned int device;		/* 设备号device/client number */
	unsigned int subdevice;		/*子流（子设备）号 subdevice (substream) number */
	unsigned char *name;		/* 名称(ASCII 格式)ASCII name of item */
	unsigned int index;		/* 索引 index of item */
	unsigned int access;		/*访问权限  access rights */
	unsigned int count;		/* 享用元素的数量count of same elements */
	snd_kcontrol_info_t *info;// control 的详细信息,它的主要工作就是填充通过参数传入的snd_ctl_elem_info对象
	snd_kcontrol_get_t *get;//读取control的当前值，并返回给用户空间的应用程序
	snd_kcontrol_put_t *put;//把应用程序的控制值设置到control中
	union {
		snd_kcontrol_tlv_rw_t *c;
		const unsigned int *p;
	} tlv;
	unsigned long private_value;
};

struct snd_kcontrol_volatile {
	struct snd_ctl_file *owner;	/* locked */
	unsigned int access;	/* access rights */
};

struct snd_kcontrol {
	struct list_head list;		/* list of controls */
	struct snd_ctl_elem_id id;
	unsigned int count;		/* count of same elements */
	snd_kcontrol_info_t *info;
	snd_kcontrol_get_t *get;
	snd_kcontrol_put_t *put;
	union {
		snd_kcontrol_tlv_rw_t *c;
		const unsigned int *p;
	} tlv;
	unsigned long private_value;
	void *private_data;
	void (*private_free)(struct snd_kcontrol *kcontrol);
	struct snd_kcontrol_volatile vd[0];	/* volatile data */
};

#define snd_kcontrol(n) list_entry(n, struct snd_kcontrol, list)

struct snd_kctl_event {
	struct list_head list;	/* list of events */
	struct snd_ctl_elem_id id;
	unsigned int mask;
};

#define snd_kctl_event(n) list_entry(n, struct snd_kctl_event, list)

struct pid;

struct snd_ctl_file {
	struct list_head list;		/* list of all control files */
	struct snd_card *card;
	struct pid *pid;
	int prefer_pcm_subdevice;
	int prefer_rawmidi_subdevice;
	wait_queue_head_t change_sleep;
	spinlock_t read_lock;
	struct fasync_struct *fasync;
	int subscribed;			/* read interface is activated */
	struct list_head events;	/* waiting events for read */
};

#define snd_ctl_file(n) list_entry(n, struct snd_ctl_file, list)

typedef int (*snd_kctl_ioctl_func_t) (struct snd_card * card,
				      struct snd_ctl_file * control,
				      unsigned int cmd, unsigned long arg);

void snd_ctl_notify(struct snd_card * card, unsigned int mask, struct snd_ctl_elem_id * id);

struct snd_kcontrol *snd_ctl_new1(const struct snd_kcontrol_new * kcontrolnew, void * private_data);
void snd_ctl_free_one(struct snd_kcontrol * kcontrol);
int snd_ctl_add(struct snd_card * card, struct snd_kcontrol * kcontrol);
int snd_ctl_remove(struct snd_card * card, struct snd_kcontrol * kcontrol);
int snd_ctl_remove_id(struct snd_card * card, struct snd_ctl_elem_id *id);
int snd_ctl_rename_id(struct snd_card * card, struct snd_ctl_elem_id *src_id, struct snd_ctl_elem_id *dst_id);
struct snd_kcontrol *snd_ctl_find_numid(struct snd_card * card, unsigned int numid);
struct snd_kcontrol *snd_ctl_find_id(struct snd_card * card, struct snd_ctl_elem_id *id);

int snd_ctl_create(struct snd_card *card);

int snd_ctl_register_ioctl(snd_kctl_ioctl_func_t fcn);
int snd_ctl_unregister_ioctl(snd_kctl_ioctl_func_t fcn);
#ifdef CONFIG_COMPAT
int snd_ctl_register_ioctl_compat(snd_kctl_ioctl_func_t fcn);
int snd_ctl_unregister_ioctl_compat(snd_kctl_ioctl_func_t fcn);
#else
#define snd_ctl_register_ioctl_compat(fcn)
#define snd_ctl_unregister_ioctl_compat(fcn)
#endif

static inline unsigned int snd_ctl_get_ioffnum(struct snd_kcontrol *kctl, struct snd_ctl_elem_id *id)
{
	return id->numid - kctl->id.numid;
}

static inline unsigned int snd_ctl_get_ioffidx(struct snd_kcontrol *kctl, struct snd_ctl_elem_id *id)
{
	return id->index - kctl->id.index;
}

static inline unsigned int snd_ctl_get_ioff(struct snd_kcontrol *kctl, struct snd_ctl_elem_id *id)
{
	if (id->numid) {
		return snd_ctl_get_ioffnum(kctl, id);
	} else {
		return snd_ctl_get_ioffidx(kctl, id);
	}
}

static inline struct snd_ctl_elem_id *snd_ctl_build_ioff(struct snd_ctl_elem_id *dst_id,
						    struct snd_kcontrol *src_kctl,
						    unsigned int offset)
{
	*dst_id = src_kctl->id;
	dst_id->index += offset;
	dst_id->numid += offset;
	return dst_id;
}

/*
 * Frequently used control callbacks
 */
int snd_ctl_boolean_mono_info(struct snd_kcontrol *kcontrol,
			      struct snd_ctl_elem_info *uinfo);
int snd_ctl_boolean_stereo_info(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_info *uinfo);

/*
 * virtual master control
 */
struct snd_kcontrol *snd_ctl_make_virtual_master(char *name,
						 const unsigned int *tlv);
int _snd_ctl_add_slave(struct snd_kcontrol *master, struct snd_kcontrol *slave,
		       unsigned int flags);
/* optional flags for slave */
#define SND_CTL_SLAVE_NEED_UPDATE	(1 << 0)

/**
 * snd_ctl_add_slave - Add a virtual slave control
 * @master: vmaster element
 * @slave: slave element to add
 *
 * Add a virtual slave control to the given master element created via
 * snd_ctl_create_virtual_master() beforehand.
 * Returns zero if successful or a negative error code.
 *
 * All slaves must be the same type (returning the same information
 * via info callback).  The fucntion doesn't check it, so it's your
 * responsibility.
 *
 * Also, some additional limitations:
 * at most two channels,
 * logarithmic volume control (dB level) thus no linear volume,
 * master can only attenuate the volume without gain
 */
static inline int
snd_ctl_add_slave(struct snd_kcontrol *master, struct snd_kcontrol *slave)
{
	return _snd_ctl_add_slave(master, slave, 0);
}

/**
 * snd_ctl_add_slave_uncached - Add a virtual slave control
 * @master: vmaster element
 * @slave: slave element to add
 *
 * Add a virtual slave control to the given master.
 * Unlike snd_ctl_add_slave(), the element added via this function
 * is supposed to have volatile values, and get callback is called
 * at each time quried from the master.
 *
 * When the control peeks the hardware values directly and the value
 * can be changed by other means than the put callback of the element,
 * this function should be used to keep the value always up-to-date.
 */
static inline int
snd_ctl_add_slave_uncached(struct snd_kcontrol *master,
			   struct snd_kcontrol *slave)
{
	return _snd_ctl_add_slave(master, slave, SND_CTL_SLAVE_NEED_UPDATE);
}

#endif	/* __SOUND_CONTROL_H */
