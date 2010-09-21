#ifndef SUDOKU_LIB_H
#define SUDOKU_LIB_H
/*
 *  sudoku_lib.h
 *
 */

/* ----- System and Platform Files ----------------------*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/*------- Program Header Files --------------------------*/
#include "sudoku.h"
#include "led.h"

#define SUDOKU_GRID_DEV "/dev/sudoku"
#define SUDOKU_LED_DEV "/dev/led_dev"

typedef enum SUDOKU_DRIVER_SUPPORT_TYPE {
	NO_DRV_SUPPORT		= 0x0,
	DRV_GRID_SUDOKU_SUPPORT	= 0x01,
	DRV_LED_SUDOKU_SUPPORT	= 0x02
} SUDOKU_DRIVER_SUPPORT_TYPE;

typedef struct sudoku_private_type {
	int fd_sCommandsDriver;
	int fd_sLedDriver;
	int sDriverSupport;
	void *data;
} sudoku_private_type;

typedef struct sudoku_handler {
	/* Sudoku startup function prototipes */
	void (*sudoku_init) (sudoku_private_type *, char*);
	void (*sudoku_deinit) (sudoku_private_type *);

	/* Sudoku grid function prototipes */
	int (*sudoku_clean_grid) (sudoku_private_type *);
	int (*sudoku_init_grid) (sudoku_private_type *);
	int (*sudoku_set_value) (sudoku_private_type *);

	/* Sudoku LED function prototipes */
	int (*sudoku_set_led_on) (sudoku_private_type *);
	int (*sudoku_set_led_off) (sudoku_private_type *);
	int (*sudoku_get_led_status) (sudoku_private_type *);
} sudoku_handler;

int sodoku_handle(sudoku_handler *Shandle);

#endif //SUDOKU_LIB_H
