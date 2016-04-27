#include "../system.h"
#include "../mboot.h"

mboot_mem_low

void mboot_mem(multiboot_info_t* mbd, u32int_t magic) {
	if(!(mbd->flags))
		return;
	
}
