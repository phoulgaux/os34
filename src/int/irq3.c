#include "../system.h"
#include "../int/isr.h"

void irq3_cb() {
	print("/nZatrzymano");
	__asm__ __volatile__ ("hlt");
}

void init_irq3() {
	reg_int_handler(IRQ3, &irq3_cb);
}

