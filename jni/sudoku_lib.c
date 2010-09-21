/*
 *  sudoku_lib.c
 *
 */

/*------- Program Header Files --------------------------*/
#include "sudoku_lib.h"

/* Sudoku startup function prototipes */
static void sudoku_init(sudoku_private_type *Sudoku);
static void sudoku_deinit(sudoku_private_type *Sudoku);

/* Sudoku grid function prototipes */
static int sudoku_clean_grid(sudoku_private_type *Sudoku);
static int sudoku_init_grid(sudoku_private_type *Sudoku);
static int sudoku_set_value(sudoku_private_type *Sudoku);

/* Sudoku LED function prototipes */
static int sudoku_set_led_on(sudoku_private_type *Sudoku);
static int sudoku_set_led_off(sudoku_private_type *Sudoku);
static int sudoku_get_led_status(sudoku_private_type *Sudoku);


/* Fill handler for sudoku functions */
int sodoku_handle(sudoku_handler *Shandle)
{
	Shandle->sudoku_init = sudoku_init;
	Shandle->sudoku_deinit = sudoku_deinit;
	Shandle->sudoku_clean_grid = sudoku_clean_grid;
	Shandle->sudoku_init_grid = sudoku_init_grid;
	Shandle->sudoku_set_value = sudoku_set_value;
	Shandle->sudoku_set_led_on = sudoku_set_led_on;
	Shandle->sudoku_set_led_off = sudoku_set_led_off;
	Shandle->sudoku_get_led_status = sudoku_get_led_status;

	return 0;
}


/* sudoku grid api */
static void sudoku_init(sudoku_private_type *Sudoku)
{
	int fd;

	Sudoku->sDriverSupport = NO_DRV_SUPPORT;

	/* Open device driver for command grid changes */
	fd = open(SUDOKU_GRID_DEV, O_RDWR);
	if(fd == -1) {
		fprintf(stderr, "Unable to open %s.\n", SUDOKU_GRID_DEV);
		Sudoku->fd_sCommandsDriver = 0;
	} else {
		Sudoku->fd_sCommandsDriver = fd;
		Sudoku->sDriverSupport |= DRV_GRID_SUDOKU_SUPPORT;
	}

	/* Open device driver for command grid changes */
	fd = open(SUDOKU_LED_DEV, O_RDWR);
	if(fd == -1) {
		fprintf(stderr, "Unable to open %s.\n", SUDOKU_LED_DEV);
		Sudoku->fd_sLedDriver = 0;
	} else {
		Sudoku->fd_sLedDriver = fd;
		Sudoku->sDriverSupport |= DRV_LED_SUDOKU_SUPPORT;
	}
}

static void sudoku_deinit(sudoku_private_type *Sudoku)
{
	if(Sudoku->fd_sCommandsDriver) {
		Sudoku->fd_sCommandsDriver = close(Sudoku->fd_sCommandsDriver);
		if(Sudoku->fd_sCommandsDriver == -1) {
			fprintf(stderr, "Unable to close %s.\n", SUDOKU_GRID_DEV);
		}
	}

	if(Sudoku->fd_sLedDriver) {
		Sudoku->fd_sLedDriver = close(Sudoku->fd_sLedDriver);
		if(Sudoku->fd_sLedDriver == -1) {
			fprintf(stderr, "Unable to close %s.\n", SUDOKU_LED_DEV);
		}
	}
}

static int sudoku_clean_grid(sudoku_private_type *Sudoku)
{
	if(!(Sudoku->sDriverSupport & DRV_GRID_SUDOKU_SUPPORT)) {
		fprintf(stderr, "Error: No DRV_GRID_SUDOKU_SUPPORT\n");
		return -1;
	}

	if(ioctl(Sudoku->fd_sCommandsDriver, SUDOKU_CMDS_CLEAN_GRID) == -1) {
		fprintf(stderr, "Error: SUDOKU_CMDS_CLEAN_GRID\n");
		return -1;
	}

	return 0;
}

static int sudoku_init_grid(sudoku_private_type *Sudoku)
{
	if(!(Sudoku->sDriverSupport & DRV_GRID_SUDOKU_SUPPORT)) {
		fprintf(stderr, "Error: No DRV_GRID_SUDOKU_SUPPORT\n");
		return -1;
	}

	if(ioctl(Sudoku->fd_sCommandsDriver, SUDOKU_CMDS_INIT_GRID,
				(sudoku_init_vector *)Sudoku->data) == -1) {
		fprintf(stderr, "Error: SUDOKU_CMDS_CLEAN_GRID\n");
		return -1;
	}

	return 0;
}


static int sudoku_set_value(sudoku_private_type *Sudoku)
{
	if(!(Sudoku->sDriverSupport & DRV_GRID_SUDOKU_SUPPORT)) {
		fprintf(stderr, "Error: No DRV_GRID_SUDOKU_SUPPORT\n");
		return -1;
	}

	if(ioctl(Sudoku->fd_sCommandsDriver, SUDOKU_CMDS_SET_VALUE,
				(sudoku_element_value *)Sudoku->data) == -1) {
		fprintf(stderr, "Error: SUDOKU_CMDS_CLEAN_GRID\n");
		return -1;
	}

	return 0;
}


/* Sudoku led api */
static int sudoku_set_led(sudoku_private_type *Sudoku)
{
	if(!(Sudoku->sDriverSupport & DRV_LED_SUDOKU_SUPPORT)) {
		fprintf(stderr, "Error: No DRV_LED_SUDOKU_SUPPORT\n");
		return -1;
	}

	if(ioctl(Sudoku->fd_sLedDriver, IOCTL_SET_LED,
				(int)Sudoku->data) == -1) {
		fprintf(stderr, "Error: IOCTL_SET_LED\n");
		return -1;
	}

	return 0;
}

static int sudoku_set_led_on(sudoku_private_type *Sudoku)
{
	Sudoku->data = (void *)1;
	return sudoku_set_led(Sudoku);
}

static int sudoku_set_led_off(sudoku_private_type *Sudoku)
{
	Sudoku->data = (void *)0;
	return sudoku_set_led(Sudoku);
}

static int sudoku_get_led_status(sudoku_private_type *Sudoku)
{
	if(!(Sudoku->sDriverSupport & DRV_LED_SUDOKU_SUPPORT)) {
		fprintf(stderr, "Error: No DRV_LED_SUDOKU_SUPPORT\n");
		return -1;
	}

	Sudoku->data = (void *)ioctl(Sudoku->fd_sLedDriver, IOCTL_LED_STATE,0);
	if( Sudoku->data < 0 ) {
		fprintf(stderr, "Error: IOCTL_LED_STATE\n");
		return -1;
	}

	return 0;
}



