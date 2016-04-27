#ifndef FLOPPY_H
#define FLOPPY_H

#include "../system.h"

enum FloppyRegs {
	STATUS_REG_A        = 0x3F0,
	STATUS_REG_B        = 0x3F1,
	DIG_OUT_REG         = 0x3F2,
	TAPE_DRV_REG        = 0x3F3,
	MAIN_STATUS_REG     = 0x3F4,
	DATARATE_SELECT_REG = 0x3F4,
	DATA_FIFO           = 0x3F5,
	DIG_IN_REG          = 0x3F7,
	CONF_CTRL_REG       = 0x3F7
};

enum FloppyCommands
{
	READ_TRACK =                 2,	// generates IRQ6
	SPECIFY =                    3,      // * set drive parameters
	SENSE_DRIVE_STATUS =         4,
	WRITE_DATA =                 5,      // * write to the disk
	READ_DATA =                  6,      // * read from the disk
	RECALIBRATE =                7,      // * seek to cylinder 0
	SENSE_INTERRUPT =            8,      // * ack IRQ6, get status of last command
	WRITE_DELETED_DATA =         9,
	READ_ID =                    10,	// generates IRQ6
	READ_DELETED_DATA =          12,
	FORMAT_TRACK =               13,     // *
	SEEK =                       15,     // * seek both heads to cylinder X
	VERSION =                    16,	// * used during initialization, once
	SCAN_EQUAL =                 17,
	PERPENDICULAR_MODE =         18,	// * used during initialization, once, maybe
	CONFIGURE =                  19,     // * set controller parameters
	LOCK =                       20,     // * protect controller params from a reset
	VERIFY =                     22,
	SCAN_LOW_OR_EQUAL =          25,
	SCAN_HIGH_OR_EQUAL =         29
};

void fdd_start_motor(u8int_t);
void fdd_reinit();
u8int_t* fdd_cmd(u8int_t, u8int_t*);

#endif

