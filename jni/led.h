/*
 * led.h - the header file with the ioctl definitions.
 *
 * The declarations have to be on a header file, because
 * they need to be known both to the kernel module
 * (led.c) and the process using the ioctl (led_app.c)
 */
#ifndef LEDDEV_H
#define LEDDEV_H

#include <linux/ioctl.h>

#define MAJOR_NUM		100
#define DEVICE_FILE_NAME	"led_dev"

#define IOCTL_SET_LED		_IOR(MAJOR_NUM, 11, int)
#define IOCTL_LED_STATE		_IOW(MAJOR_NUM, 21, int)

#endif
