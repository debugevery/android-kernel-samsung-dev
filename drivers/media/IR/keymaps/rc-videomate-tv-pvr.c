/* videomate-tv-pvr.h - Keytable for videomate_tv_pvr Remote Controller
 *
 * keymap imported from ir-keymaps.c
 *
 * Copyright (c) 2010 by Mauro Carvalho Chehab <mchehab@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

//#include <media/rc-map.h>

static struct ir_scancode videomate_tv_pvr[] = {
	{ 0x14, KEY_MUTE },
	{ 0x24, KEY_ZOOM },

	{ 0x01, KEY_DVD },
	{ 0x23, KEY_RADIO },
	{ 0x00, KEY_TV },

	{ 0x0a, KEY_REWIND },
	{ 0x08, KEY_PLAYPAUSE },
	{ 0x0f, KEY_FORWARD },

	{ 0x02, KEY_PREVIOUS },
	{ 0x07, KEY_STOP },
	{ 0x06, KEY_NEXT },

	{ 0x0c, KEY_UP },
	{ 0x0e, KEY_DOWN },
	{ 0x0b, KEY_LEFT },
	{ 0x0d, KEY_RIGHT },
	{ 0x11, KEY_OK },

	{ 0x03, KEY_MENU },
	{ 0x09, KEY_SETUP },
	{ 0x05, KEY_VIDEO },
	{ 0x22, KEY_CHANNEL },

	{ 0x12, KEY_VOLUMEUP },
	{ 0x15, KEY_VOLUMEDOWN },
	{ 0x10, KEY_CHANNELUP },
	{ 0x13, KEY_CHANNELDOWN },

	{ 0x04, KEY_RECORD },

	{ 0x16, KEY_1 },
	{ 0x17, KEY_2 },
	{ 0x18, KEY_3 },
	{ 0x19, KEY_4 },
	{ 0x1a, KEY_5 },
	{ 0x1b, KEY_6 },
	{ 0x1c, KEY_7 },
	{ 0x1d, KEY_8 },
	{ 0x1e, KEY_9 },
	{ 0x1f, KEY_0 },

	{ 0x20, KEY_LANGUAGE },
	{ 0x21, KEY_SLEEP },
};

static struct rc_keymap videomate_tv_pvr_map = {
	.map = {
		.scan    = videomate_tv_pvr,
		.size    = ARRAY_SIZE(videomate_tv_pvr),
		.ir_type = IR_TYPE_UNKNOWN,	/* Legacy IR type */
		.name    = RC_MAP_VIDEOMATE_TV_PVR,
	}
};

static int __init init_rc_map_videomate_tv_pvr(void)
{
	return ir_register_map(&videomate_tv_pvr_map);
}

static void __exit exit_rc_map_videomate_tv_pvr(void)
{
	ir_unregister_map(&videomate_tv_pvr_map);
}

//module_init(init_rc_map_videomate_tv_pvr)
//module_exit(exit_rc_map_videomate_tv_pvr)

//MODULE_LICENSE("GPL");
//MODULE_AUTHOR("Mauro Carvalho Chehab <mchehab@redhat.com>");
