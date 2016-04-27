#include "isr.h"

isr_t int_handlers[256];

void isr_handler(regs_t regs) {
	isr_t handler = int_handlers[regs.int_no];
	handler(regs);
/*	print("interrupt/exception caught: ");
	print_hex(regs.int_no);
	print(" (");
	print_int(regs.err_code);
	print(")\n");*/
}

void irq_handler(regs_t regs) {
/*	print("IRQ caught: ");
	print_hex(regs.int_no);
	print(" (");
	print_int(regs.err_code);
	print(")\n");*/
	
	if(regs.int_no>=0x40)
		outb(0xA0, 0x20);
	outb(0x20,0x20);
	if (int_handlers[regs.int_no]!=0) {
		isr_t handler = int_handlers[regs.int_no];
		handler(regs);
	}
}

void reg_int_handler(u8int_t n, isr_t handler) {
	int_handlers[n]=handler;
}

