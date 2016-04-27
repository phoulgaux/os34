#include "pit.h"
#include "../system.h"
#include "../int/isr.h"

u32int_t tick=0;

static void timer_cb(regs_t regs) {
	tick++;
/*	print("\nTick: ");*/
/*	print_int(tick);*/
}

void init_timer(u32int_t freq) {
	reg_int_handler(IRQ0, &timer_cb);
	u32int_t div=1193180/freq;
	outb(0x43, 0x36);
	u8int_t div_low  = (u8int_t)( div    &0xFF);
	u8int_t div_high = (u8int_t)((div>>8)&0xFF);
	outb(0x40,div_low);
	outb(0x40,div_high);	
}

u32int_t get_time() { return tick; }

void reset_timer() { tick=0; }

void wait(u32int_t t) { // w setnych sekundy
	reset_timer();
	while(tick<t) if(tick>t) return;
}

