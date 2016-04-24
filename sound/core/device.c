/*
 *  Device management routines==============设备管理相关函数
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *
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

//#include <linux/slab.h>
//#include <linux/time.h>
//#include <linux/errno.h>
//#include <sound/core.h>

/**
 * snd_device_new - create an ALSA device component
 * @card: the card instance
 * @type: the device type, SNDRV_DEV_XXX
 * @device_data: the data pointer of this device
 * @ops: the operator table
 *
 * Creates a new device component for the given data pointer.
 * The device will be assigned to the card and managed together
 * by the card.
 *
 * The data pointer plays a role as the identifier, too, so the
 * pointer address must be unique and unchanged.
 *
 * Returns zero if successful, or a negative error code on failure.
 当 card  被创建后，设备（组件）能够被创建并关联于该 card。第 1  个参数是
snd_card_new()创建的 card 指针，第 2 个参数 type 指的是 device-level 即设备类型， 
形式为 SNDRV_DEV_XXX，包括 SNDRV_DEV_CODEC、SNDRV_DEV_CONTROL、 SNDRV_DEV_PCM、SNDRV_DEV_  RAWMIDI 等，用户自定义设备的 device-level 是 SNDRV_DEV_LOWLEVEL，ops 参数是 1 个函数集（定义为 snd_device_ops 结构 体）的指针，device_data 是设备数据指针，注意函数 snd_device_ new()本身不会分配 设备数据的内存，因此应事先分配。
*/
int snd_device_new(struct snd_card *card, snd_device_type_t type,
		   void *device_data, struct snd_device_ops *ops)
{//创建组件:当 card  被创建后，设备（组件）能够被创建并关联于该 card
	struct snd_device *dev;

	if (snd_BUG_ON(!card || !device_data || !ops))
		return -ENXIO;
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (dev == NULL) {
		snd_printk(KERN_ERR "Cannot allocate device\n");
		return -ENOMEM;
	}
	dev->card = card;
	dev->type = type;
	dev->state = SNDRV_DEV_BUILD;
	dev->device_data = device_data;
	dev->ops = ops;
	list_add(&dev->list, &card->devices);	/* add to the head of list */
	return 0;
}

//EXPORT_SYMBOL(snd_device_new);

/**
 * snd_device_free - release the device from the card
 * @card: the card instance
 * @device_data: the data pointer to release
 *
 * Removes the device from the list on the card and invokes the
 * callbacks, dev_disconnect and dev_free, corresponding to the state.
 * Then release the device.
 *
 * Returns zero if successful, or a negative error code on failure or if the
 * device not found.
 每个 ALSA 预定义的组件在构造时需调用 snd_device_new()，而每个组件的析构方法则 在函数集中被包含。
 对于 PCM、AC97 此类预定义组件，我们不需关心它们的析构，而对 于自定义的组件，则需要填充 snd_device_ops 
 中的析构函数指针 dev_free，这样，当 snd_card_free()被调用时，组件将自动被释放。*/
int snd_device_free(struct snd_card *card, void *device_data)
{//组件释放
	struct snd_device *dev;
	
	if (snd_BUG_ON(!card || !device_data))
		return -ENXIO;
	list_for_each_entry(dev, &card->devices, list) {
		if (dev->device_data != device_data)
			continue;
		/* unlink */
		list_del(&dev->list);
		if (dev->state == SNDRV_DEV_REGISTERED &&
		    dev->ops->dev_disconnect)
			if (dev->ops->dev_disconnect(dev))
				snd_printk(KERN_ERR
					   "device disconnect failure\n");
		if (dev->ops->dev_free) {
			if (dev->ops->dev_free(dev))
				snd_printk(KERN_ERR "device free failure\n");
		}
		kfree(dev);
		return 0;
	}
	snd_printd("device free %p (from %pF), not found\n", device_data,
		   __builtin_return_address(0));
	return -ENXIO;
}

//EXPORT_SYMBOL(snd_device_free);

/**
 * snd_device_disconnect - disconnect the device
 * @card: the card instance
 * @device_data: the data pointer to disconnect
 *
 * Turns the device into the disconnection state, invoking
 * dev_disconnect callback, if the device was already registered.
 *
 * Usually called from snd_card_disconnect().
 *
 * Returns zero if successful, or a negative error code on failure or if the
 * device not found.
 */
int snd_device_disconnect(struct snd_card *card, void *device_data)
{
	struct snd_device *dev;

	if (snd_BUG_ON(!card || !device_data))
		return -ENXIO;
	list_for_each_entry(dev, &card->devices, list) {
		if (dev->device_data != device_data)
			continue;
		if (dev->state == SNDRV_DEV_REGISTERED &&
		    dev->ops->dev_disconnect) {
			if (dev->ops->dev_disconnect(dev))
				snd_printk(KERN_ERR "device disconnect failure\n");
			dev->state = SNDRV_DEV_DISCONNECTED;
		}
		return 0;
	}
	snd_printd("device disconnect %p (from %pF), not found\n", device_data,
		   __builtin_return_address(0));
	return -ENXIO;
}

/**
 * snd_device_register - register the device
 * @card: the card instance
 * @device_data: the data pointer to register
 *
 * Registers the device which was already created via
 * snd_device_new().  Usually this is called from snd_card_register(),
 * but it can be called later if any new devices are created after
 * invocation of snd_card_register().
 *
 * Returns zero if successful, or a negative error code on failure or if the
 * device not found.
 */
int snd_device_register(struct snd_card *card, void *device_data)
{
	struct snd_device *dev;
	int err;

	if (snd_BUG_ON(!card || !device_data))
		return -ENXIO;
	list_for_each_entry(dev, &card->devices, list) {
		if (dev->device_data != device_data)
			continue;
		if (dev->state == SNDRV_DEV_BUILD && dev->ops->dev_register) {
			if ((err = dev->ops->dev_register(dev)) < 0)
				return err;
			dev->state = SNDRV_DEV_REGISTERED;
			return 0;
		}
		snd_printd("snd_device_register busy\n");
		return -EBUSY;
	}
	snd_BUG();
	return -ENXIO;
}

//EXPORT_SYMBOL(snd_device_register);

/*
 * register all the devices on the card.
 * called from init.c
 */
int snd_device_register_all(struct snd_card *card)
{
	struct snd_device *dev;
	int err;
	
	if (snd_BUG_ON(!card))
		return -ENXIO;
	list_for_each_entry(dev, &card->devices, list) {
		if (dev->state == SNDRV_DEV_BUILD && dev->ops->dev_register) {
			if ((err = dev->ops->dev_register(dev)) < 0)
				return err;
			dev->state = SNDRV_DEV_REGISTERED;
		}
	}
	return 0;
}

/*
 * disconnect all the devices on the card.
 * called from init.c
 */
int snd_device_disconnect_all(struct snd_card *card)
{
	struct snd_device *dev;
	int err = 0;

	if (snd_BUG_ON(!card))
		return -ENXIO;
	list_for_each_entry(dev, &card->devices, list) {
		if (snd_device_disconnect(card, dev->device_data) < 0)
			err = -ENXIO;
	}
	return err;
}

/*
 * release all the devices on the card.
 * called from init.c
 */
int snd_device_free_all(struct snd_card *card, snd_device_cmd_t cmd)
{
	struct snd_device *dev;
	int err;
	unsigned int range_low, range_high;

	if (snd_BUG_ON(!card))
		return -ENXIO;
	range_low = cmd * SNDRV_DEV_TYPE_RANGE_SIZE;
	range_high = range_low + SNDRV_DEV_TYPE_RANGE_SIZE - 1;
      __again:
	list_for_each_entry(dev, &card->devices, list) {
		if (dev->type >= range_low && dev->type <= range_high) {
			if ((err = snd_device_free(card, dev->device_data)) < 0)
				return err;
			goto __again;
		}
	}
	return 0;
}
