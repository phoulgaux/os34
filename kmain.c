#include "src/system.h"

void init_kernel();
//void mboot_mem(multiboot_info_t*, u32int_t);
void hello();
inline void sti();
inline void brk();

s32int_t kmain(multiboot_info_t* mbd, u32int_t magic) {
	init_kernel();
	hello();
//	brk();
//	UIInit(SCR_WIDTH, SCR_HEIGHT);
//	okienka();
//	mboot_mem(mbd, magic);
	print("nfs\n");
	con_start();
	for(;;);
	return 0xCAFEBABE;
}

void init_kernel() {
//	init_serial(1);
	init_gdt();
	init_idt();
	init_timer(10);
	init_video();
	print("Uruchamianie...   ");
//	init_paging();
//	fdd_reinit();
//	fdd_start_motor(1);
	init_kbd();
	init_irq3();
	sti();
	print(INIT_OK);
	send_serial_str("Uruchomiono");
	newline();
}

void hello() {
	print("Witaj w os34\n");
}

inline void sti() {
	__asm__ __volatile__ ("sti");
}

inline void brk() {
// breakpoint interrupt
	print("brk() caught\n");
	__asm__ __volatile__ ("int $3");
}

