#include "idt.h"

extern void idt_flush(u32int_t);
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void init_idt();
static void set_idt_gate(u8int_t,u32int_t,u16int_t,u8int_t);

idt_entry_t idt_table[256];
idt_ptr_t   idt_ptr;

void init_idt() {
	idt_ptr.limit = sizeof(idt_entry_t)*256-1;
	idt_ptr.base  = (u32int_t)&idt_table;
	memset(&idt_table,0,sizeof(idt_entry_t)*256);
	
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);
	
	set_idt_gate(0,(u32int_t)isr0,0x08,0x8E);
	set_idt_gate(1,(u32int_t)isr1,0x08,0x8E);
	set_idt_gate(2,(u32int_t)isr2,0x08,0x8E);
	set_idt_gate(3,(u32int_t)isr3,0x08,0x8E);
	set_idt_gate(4,(u32int_t)isr4,0x08,0x8E);
	set_idt_gate(5,(u32int_t)isr5,0x08,0x8E);
	set_idt_gate(6,(u32int_t)isr6,0x08,0x8E);
	set_idt_gate(7,(u32int_t)isr7,0x08,0x8E);
	set_idt_gate(8,(u32int_t)isr8,0x08,0x8E);
	set_idt_gate(9,(u32int_t)isr9,0x08,0x8E);
	set_idt_gate(10,(u32int_t)isr10,0x08,0x8E);
	set_idt_gate(11,(u32int_t)isr11,0x08,0x8E);
	set_idt_gate(12,(u32int_t)isr12,0x08,0x8E);
	set_idt_gate(13,(u32int_t)isr13,0x08,0x8E);
	set_idt_gate(14,(u32int_t)isr14,0x08,0x8E);
	set_idt_gate(15,(u32int_t)isr15,0x08,0x8E);
	set_idt_gate(16,(u32int_t)isr16,0x08,0x8E);
	set_idt_gate(17,(u32int_t)isr17,0x08,0x8E);
	set_idt_gate(18,(u32int_t)isr18,0x08,0x8E);
	set_idt_gate(19,(u32int_t)isr19,0x08,0x8E);
	set_idt_gate(20,(u32int_t)isr20,0x08,0x8E);
	set_idt_gate(21,(u32int_t)isr21,0x08,0x8E);
	set_idt_gate(22,(u32int_t)isr22,0x08,0x8E);
	set_idt_gate(23,(u32int_t)isr23,0x08,0x8E);
	set_idt_gate(24,(u32int_t)isr24,0x08,0x8E);
	set_idt_gate(25,(u32int_t)isr25,0x08,0x8E);
	set_idt_gate(26,(u32int_t)isr26,0x08,0x8E);
	set_idt_gate(27,(u32int_t)isr27,0x08,0x8E);
	set_idt_gate(28,(u32int_t)isr28,0x08,0x8E);
	set_idt_gate(29,(u32int_t)isr29,0x08,0x8E);
	set_idt_gate(30,(u32int_t)isr30,0x08,0x8E);
	set_idt_gate(31,(u32int_t)isr31,0x08,0x8E);
	
  set_idt_gate(32, (u32int_t)irq0, 0x08, 0x8E);
  set_idt_gate(33, (u32int_t)irq1, 0x08, 0x8E);
  set_idt_gate(34, (u32int_t)irq2, 0x08, 0x8E);
  set_idt_gate(35, (u32int_t)irq3, 0x08, 0x8E);
  set_idt_gate(36, (u32int_t)irq4, 0x08, 0x8E);
  set_idt_gate(37, (u32int_t)irq5, 0x08, 0x8E);
  set_idt_gate(38, (u32int_t)irq6, 0x08, 0x8E);
  set_idt_gate(39, (u32int_t)irq7, 0x08, 0x8E);
  set_idt_gate(40, (u32int_t)irq8, 0x08, 0x8E);
  set_idt_gate(41, (u32int_t)irq9, 0x08, 0x8E);
  set_idt_gate(42, (u32int_t)irq10, 0x08, 0x8E);
  set_idt_gate(43, (u32int_t)irq11, 0x08, 0x8E);
  set_idt_gate(44, (u32int_t)irq12, 0x08, 0x8E);
  set_idt_gate(45, (u32int_t)irq13, 0x08, 0x8E);
  set_idt_gate(46, (u32int_t)irq14, 0x08, 0x8E);
  set_idt_gate(47, (u32int_t)irq15, 0x08, 0x8E);
  	
	idt_flush((u32int_t)&idt_ptr);
}

static void set_idt_gate(u8int_t num, u32int_t base, u16int_t sel, u8int_t flags) {
	idt_table[num].base_low  = base&0xFFFF;
	idt_table[num].base_high = (base>>16)&0xFFFF;
	idt_table[num].sel       = sel;
	idt_table[num].zero      = 0;
	idt_table[num].flags     = flags;
}

