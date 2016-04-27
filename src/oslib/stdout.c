const char dig[] = {
	'0','1','2','3','4','5','6','7',
	'8','9','A','B','C','D','E','F'};

static void print_ui32(unsigned a) {
	if(a>=1000000) {
		putch(dig[a/1000000]);
		a%=1000000;
		putch(dig[a/100000]);
		a%=100000;
		putch(dig[a/10000]);
		a%=10000;
		putch(dig[a/1000]);
		a%=1000;
		putch(dig[a/100]);
		a%=100;
		putch(dig[a/10]);
		a%=10;
		putch(dig[a]);
	} else if(a>=100000) {
		putch(dig[a/100000]);
		a%=100000;
		putch(dig[a/10000]);
		a%=10000;
		putch(dig[a/1000]);
		a%=1000;
		putch(dig[a/100]);
		a%=100;
		putch(dig[a/10]);
		a%=10;
		putch(dig[a]);
	} else if(a>=10000) {
		putch(dig[a/10000]);
		a%=10000;
		putch(dig[a/1000]);
		a%=1000;
		putch(dig[a/100]);
		a%=100;
		putch(dig[a/10]);
		a%=10;
		putch(dig[a]);
	} else if(a>=1000) {
		putch(dig[a/1000]);
		a%=1000;
		putch(dig[a/100]);
		a%=100;
		putch(dig[a/10]);
		a%=10;
		putch(dig[a]);
	} else if(a>=100) {
		putch(dig[a/100]);
		a%=100;
		putch(dig[a/10]);
		a%=10;
		putch(dig[a]);
	} else if (a>=10) {
		putch(dig[a/10]);
		a%=10;
		putch(dig[a]);
	} else
		putch(dig[a]);
}

void print_int(signed a) {
	if(a<0) {
		putch('-');
		print_ui32(-a);
	} else print_ui32(a);
}

static void print_ui32_hex(unsigned a) {
  print("0x");
  	if(a>=0x10000000) {
		putch(dig[a/0x10000000]);
		a%=0x10000000;
		putch(dig[a/0x1000000]);
		a%=0x1000000;
		putch(dig[a/0x100000]);
		a%=0x100000;
		putch(dig[a/0x10000]);
		a%=0x10000;
		putch(dig[a/0x1000]);
		a%=0x1000;
		putch(dig[a/0x100]);
		a%=0x100;
		putch(dig[a/0x10]);
		a%=0x10;
		putch(dig[a]);
	} else if(a>=0x1000000) {
		putch(dig[a/0x1000000]);
		a%=0x1000000;
		putch(dig[a/0x100000]);
		a%=0x100000;
		putch(dig[a/0x10000]);
		a%=0x10000;
		putch(dig[a/0x1000]);
		a%=0x1000;
		putch(dig[a/0x100]);
		a%=0x100;
		putch(dig[a/0x10]);
		a%=0x10;
		putch(dig[a]);
	} else if(a>=0x100000) {
		putch(dig[a/0x100000]);
		a%=0x100000;
		putch(dig[a/0x10000]);
		a%=0x10000;
		putch(dig[a/0x1000]);
		a%=0x1000;
		putch(dig[a/0x100]);
		a%=0x100;
		putch(dig[a/0x10]);
		a%=0x10;
		putch(dig[a]);
	} else if(a>=0x10000) {
		putch(dig[a/0x10000]);
		a%=0x10000;
		putch(dig[a/0x1000]);
		a%=0x1000;
		putch(dig[a/100]);
		a%=0x100;
		putch(dig[a/0x10]);
		a%=0x10;
		putch(dig[a]);
	} else if(a>=0x1000) {
		putch(dig[a/0x1000]);
		a%=0x1000;
		putch(dig[a/0x100]);
		a%=0x100;
		putch(dig[a/0x10]);
		a%=0x10;
		putch(dig[a]);
	} else if(a>=0x100) {
		putch(dig[a/0x100]);
		a%=0x100;
		putch(dig[a/0x10]);
		a%=0x10;
		putch(dig[a]);
	} else if(a>=0x10) {
		putch(dig[a/0x10]);
		a%=0x10;
		putch(dig[a]);
	} else
		putch(dig[a]);
}

void print_hex(signed a) {
	if(a<0) {
		putch('-');
		print_ui32_hex(-a);
	} else print_ui32_hex(a);
}

