inline void outb(unsigned short port, unsigned char val) {
	__asm__("outb %%al, %%dx"::"a"(val),"d"(port));
}

inline unsigned char inb(unsigned short port) {
	unsigned char ret;
	__asm__("inb %%dx, %%al":"=a"(ret):"d"(port));
	return ret;
}

inline void iowait(void) {
	asm volatile ("jmp 1f;1:jmp 1f;1:");
}
