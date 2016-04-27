#ifndef IDT_H
#define IDT_H

#include "../system.h"
#include "../mem/mem.h"

struct idt_entry_str {
	u16int_t base_low;
	u16int_t sel;
	u8int_t  zero;
	u8int_t  flags;
	u16int_t base_high;
} __attribute__((packed));

struct idt_ptr_str {
	u16int_t limit;
	u32int_t base;
} __attribute__((packed));

typedef struct idt_entry_str idt_entry_t;
typedef struct idt_ptr_str   idt_ptr_t;

#endif

