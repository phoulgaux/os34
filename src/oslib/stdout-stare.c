void print_ui8(unsigned char a) {
	if(a>100) {
		putch(a/100+0x30);
		a%=100;
		putch(a/10+0x30);
		a%=10;
		putch(a+0x30);
	} else if (a>10) {
		putch(a/10+0x30);
		a%=10;
		putch(a+0x30);
	} else
		putch(a+0x30);
}

void print_si8(signed char a) {
	if(a<0) {
		putch('-');
		print_ui8(-a);
	} else print_ui8(a);
}

void print_ui16(unsigned short a) {
	if(a>10000) {
		putch(a/10000+0x30);
		a%=10000;
		putch(a/1000+0x30);
		a%=1000;
		putch(a/100+0x30);
		a%=100;
		putch(a/10+0x30);
		a%=10;
		putch(a+0x30);
	} else if(a>1000) {
		putch(a/1000+0x30);
		a%=1000;
		putch(a/100+0x30);
		a%=100;
		putch(a/10+0x30);
		a%=10;
		putch(a+0x30);
	} else if(a>100) {
		putch(a/100+0x30);
		a%=100;
		putch(a/10+0x30);
		a%=10;
		putch(a+0x30);
	} else if (a>10) {
		putch(a/10+0x30);
		a%=10;
		putch(a+0x30);
	} else
		putch(a+0x30);
}

void print_si16(signed short a) {
	if(a<0) {
		putch('-');
		print_ui16(-a);
	} else print_ui16(a);
}


