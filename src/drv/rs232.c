#include "../system.h"

#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

static int is_received() {
	return inb(COM1+5)&1;
}

static int is_ready() {
	return inb(COM1+5)&0x20;
}

char read_serial() {
	while (is_received()==0);
	return inb(COM1);
}

void send_serial(char ch) {
	while (is_ready()==0);
	outb(COM1, ch);
}

int send_serial_str(char* str) {
	int n=0;
	while(*str != 0) {
		send_serial(*str);
		str++;
		n++;
	}
	send_serial('\n');
	send_serial('\r');
	return n;
}

void init_serial(int n) {
	if(n==1) n=COM1;
	else if(n==2) n=COM2;
	else if(n==3) n=COM3;
	else if(n==4) n=COM4;
	else panic("Nie wybrano portu przy inicjalizacji");

	outb(n+1, 0x00);
	outb(n+3, 0x80);
	outb(n+0, 0x03);
	outb(n+1, 0x00);
	outb(n+3, 0x03);
	outb(n+2, 0xC7);
	outb(n+4, 0x0B);
	
	send_serial_str("Zainicjalizowano COM");
}

