#ifndef SUDOKU_COMMANDS_H
#define SUDOKU_COMMANDS_H

//#include <linux/config.h>
#include <config/modversions.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/fcntl.h>
#include <asm/system.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/pci.h>
#include <linux/cdev.h>

#include "sudoku.h"

/********/
/* specific to driver implemtation tastk */
#define SUDOKU_ISCLOSE	0
#define SUDOKU_ISOPEN	1

typedef struct sudoku_data_grid {
	int grid_data[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE];
} sudoku_data_grid;

typedef struct sudoku_file_operations {
	//struct module *owner;
	int (*clean) (void);
	int (*init) (sudoku_init_vector *);
	int (*set_value) (sudoku_element_value *);
} sudoku_file_operations;

typedef struct Sudoku {
	sudoku_data_grid *grid;
	sudoku_file_operations *sfops;

	int sudoku_mod_major;
	int sudoku_mod_minor;
	int sudoku_mod_number_devs;
	struct cdev sudoku_dev;

	int sudoku_status;
} Sudoku;
/**/

#define VERSION                 "1.0"

/* by default, we use dynamic allocation of major numbers */
#define SUDOKU_MOD_MAJOR 0
#define SUDOKU_MOD_MINOR 0
/* Number of device modules supported at a time */
#define SUDOKU_MOD_NUMBER_DEVS 1

#define OUR_NAME "sudoku"

// Pretend we're PPDEV for IOCTL
//#include <linux/ppdev.h>

#endif //SUDOKU_COMMANDS_H

