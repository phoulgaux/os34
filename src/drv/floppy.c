#include "floppy.h"

void fdd_start_motor(u8int_t mot) {
	u32int_t i;
	u8int_t m;
	switch(m) {
		case 0: m=0x10; break;
		case 1: m=0x20; break;
		case 2: m=0x40; break;
		case 3: m=0x80; break;
	}
	outb(DIG_OUT_REG, m);
//	brk();
	wait(300);
}

void fdd_reinit() {
	fdd_cmd(VERSION,NULL);
}

u8int_t* fdd_cmd(u8int_t cmd, u8int_t* args) {
	u8int_t i=0;
	u8int_t ended=0;
	u8int_t* buf;
// Sending command
	if ((inb(MAIN_STATUS_REG) & 0xc0) == 0x80);
	outb(DATA_FIFO, cmd);
	while(!ended) {
		while(!(inb(MAIN_STATUS_REG)&0x80));
		if (inb(MAIN_STATUS_REG)&0x40)
			ended=1;
		else {
			outb(DATA_FIFO, args[i]);
			i++;
		}
	}
//	Execution
	if(!(inb(MAIN_STATUS_REG)&0x20))
		goto fdd_cmd_result;
	while (!(inb(MAIN_STATUS_REG)&0x80));
	
	
//	Result	
fdd_cmd_result:
	print();
}

