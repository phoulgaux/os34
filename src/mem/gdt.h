#ifndef GDT_H
#define GDT_H

struct gdt_entry_str {
	u16int_t limit_low;
	u16int_t base_low;
	u8int_t  base_mid;
	u8int_t  access;
	u8int_t  gran;
	u8int_t  base_high;
} __attribute__((packed));

struct gdt_ptr_str {
	u16int_t limit;
	u32int_t base;
} __attribute__((packed));

// in-kernel use types
typedef struct gdt_entry_str     gdt_entry_t;
typedef struct gdt_ptr_str       gdt_ptr_t;

void init_gdt();

#endif

