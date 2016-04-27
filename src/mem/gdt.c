#include "../system.h"
#include "gdt.h"

extern void gdt_flush(u32int_t);

void init_gdt();
static void set_gdt_gate(s32int_t,u32int_t,u32int_t,u8int_t,u8int_t);

gdt_entry_t gdt_table[5];
gdt_ptr_t   gdt_ptr;

void init_gdt() {
	gdt_ptr.limit = (sizeof(gdt_entry_t)*5)-1;
	gdt_ptr.base  = (u32int_t)&gdt_table;
	
	set_gdt_gate(0,0,0,0,0);
	set_gdt_gate(1,0,0xFFFFFFFF,0x9A,0xCF);
	set_gdt_gate(2,0,0xFFFFFFFF,0x92,0xCF);
	set_gdt_gate(3,0,0xFFFFFFFF,0xFA,0xCF);
	set_gdt_gate(4,0,0xFFFFFFFF,0xF2,0xCF);
	
	gdt_flush((u32int_t)&gdt_ptr);
}

static void set_gdt_gate(s32int_t num, u32int_t base, u32int_t limit, u8int_t access, u8int_t gran) {
	gdt_table[num].base_low  = (base&0xFFFF);
	gdt_table[num].base_mid  = (base>>16)&0xFF;
	gdt_table[num].base_high = (base>>24)&0xFF;
	gdt_table[num].limit_low = (limit&0xFFFF);
	gdt_table[num].gran      = (limit>>16)&0x0F;
	gdt_table[num].gran     |= (gran&0xF0);
	gdt_table[num].access    = access;
}

