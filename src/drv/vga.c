#include "../con/con.h"

s32int_t currpos;
extern prompt_pos;
int scroll_wait=0;

void init_video(void);
void putch(s8int_t);
void print(s8int_t*);
void clrscr(void);
void mov_csr(s32int_t, s32int_t);
void set_csr(s32int_t);
s32int_t  get_csr();
void newline();
void scroll();
void clear_ch();
s8int_t read_ch();
void set_wait(int);

void init_video() {
	clrscr();
	mov_csr(0,0);
	currpos=0;
}

void putch(s8int_t ch) {
	s32int_t i=0;
	if(ch==0) return;
	else if(ch=='\n')
		newline();
	else if(ch=='\t') {
		putch(' ');
		for(i=0;i<((currpos%SCR_WIDTH)%HTAB_WIDTH);i++)
			putch(' ');
	}
	else if(ch=='\r')
		mov_csr(0, (currpos/SCR_WIDTH));
	else if(ch=='\b') {
//		clear_ch(0);
		set_csr(get_csr()-1);
		clear_ch(0);
	}
	else {
		u8int_t *vga = (u8int_t *)VGA_ADDR;
		*(vga+2*currpos)=ch;
		currpos++;
		mov_csr((currpos%SCR_WIDTH),(currpos/SCR_WIDTH));
	}
	if(currpos>=(SCR_WIDTH*(SCR_HEIGHT+1)))
		scroll();
}

void print(s8int_t *str) {
	s8int_t *vga = (s8int_t *)VGA_ADDR;
	while(*str != 0) {
		putch(*str);
		str++;
	}
}

void clrscr() {
	u16int_t *vga = (u16int_t *)VGA_ADDR;
	u32int_t i = 0;
	for (i = 0; i < SCR_WIDTH*SCR_HEIGHT; i++)
		vga[i] = DEFAULT_FILL;
//	mov_csr(0,0);
}

void mov_csr(s32int_t x, s32int_t y) {
	s32int_t pos=(x+SCR_WIDTH*y);
	currpos=pos;
	outb(0x3D4+0,14);
	outb(0x3D4+1,pos>>8);
	outb(0x3D4+0,15);
	outb(0x3D4+1,pos);
}

void set_csr(s32int_t pos) {
	currpos=pos;
	outb(0x3D4+0,14);
	outb(0x3D4+1,pos>>8);
	outb(0x3D4+0,15);
	outb(0x3D4+1,pos);
}

s32int_t get_csr() {
	return currpos;
}

void newline() {
	u8int_t line=(u8int_t)(currpos/SCR_WIDTH);
	if(line>=SCR_HEIGHT-1)
		scroll();
	else
		mov_csr(0,line+1);
}

void scroll() {
	if(scroll_wait==1)
		getch();
	u16int_t *vga=(u16int_t *)VGA_ADDR;
	u32int_t temp;
	memcpy(vga, vga+SCR_WIDTH, 2*SCR_HEIGHT*SCR_WIDTH);
	memset(vga+SCR_HEIGHT*SCR_WIDTH,DEFAULT_FILL,SCR_WIDTH);
	mov_csr(0,SCR_HEIGHT-1);
	prompt_pos-=SCR_WIDTH;
}

void clear_ch() {
	u16int_t *vga = (u16int_t *)VGA_ADDR;
	vga[currpos] = DEFAULT_FILL;
}

s8int_t read_ch(s32int_t pos) {
	u16int_t *vga = (u16int_t *)VGA_ADDR;
	return vga[pos-1];
}

void set_wait(int x) {
	scroll_wait=x;
}

