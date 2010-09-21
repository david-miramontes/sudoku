#ifndef SUDOKU_H
#define SUDOKU_H

#include <asm-generic/ioctl.h>

/* Specific to app; have to be moved to a header file */
typedef struct sudoku_element_value {
	int posx;
	int posy;
	int element_value;
} sudoku_element_value;

typedef struct sudoku_init_vector {
	sudoku_element_value *initvector;
	int nelements;
} sudoku_init_vector;

/* Grid size */
#define SUDOKU_GRID_SIZE 9

/* Read/write bitmask that determines input/output */
#define SUDOKU_CMDS_CLEAN_GRID	_IO('T', 0x00)
#define SUDOKU_CMDS_INIT_GRID	_IOW('T', 0x01, sudoku_init_vector)
#define SUDOKU_CMDS_SET_VALUE	_IOW('T', 0x02, sudoku_element_value)


#endif //SUDOKU_H