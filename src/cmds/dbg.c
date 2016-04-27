#include "../system.h"

static void print_rev(int x) {
	char b[4];
	b[0]=(char)(x&0xFF);
	b[1]=(char)((x>>8)&0xFF);
	b[2]=(char)((x>>16)&0xFF);
	b[3]=(char)((x>>24)&0xFF);
	
//	if(b[0]!=0x20)
	putch(b[0]);
//	if(b[1]!=0x20)
	putch(b[1]);
//	if(b[2]!=0x20)
	putch(b[2]);
//	if(b[3]!=0x20)
	putch(b[3]);
}


void cmd_cpuid() {
	set_wait(1);
	int reax,rebx,recx,redx;
	__asm__ __volatile__ ("movl $0x00, %%eax;cpuid":"=&a"(reax),"=&b"(rebx),"=&c"(recx),"=&d"(redx));
	int maxleaf=reax;
	
	print(" CPUID");
	
	print("\nBasic Max of leaf: ");
	print_hex((char)reax);
	
	print("\nVendor name:       ");
	print_rev(rebx);
	print_rev(redx);
	print_rev(recx);
	
	__asm__ __volatile__ ("movl $0x80000000, %%eax;cpuid":"=&a"(reax),"=&b"(rebx),"=&c"(recx),"=&d"(redx));
	if(reax&0x80000000)
		if(reax>=0x80000004) {
			print("\nCPU brand string:  ");
			__asm__ __volatile__ ("movl $0x80000002, %%eax;cpuid":"=&a"(reax),"=&b"(rebx),"=&c"(recx),"=&d"(redx));
			print_rev(reax);
			print_rev(rebx);
			print_rev(recx);
			print_rev(redx);
			__asm__ __volatile__ ("movl $0x80000003, %%eax;cpuid":"=&a"(reax),"=&b"(rebx),"=&c"(recx),"=&d"(redx));
			print_rev(reax);
			print_rev(rebx);
			print_rev(recx);
			print_rev(redx);
			__asm__ __volatile__ ("movl $0x80000004, %%eax;cpuid":"=&a"(reax),"=&b"(rebx),"=&c"(recx),"=&d"(redx));
			print_rev(reax);
			print_rev(rebx);
			print_rev(recx);
			print_rev(redx);
		}
	
	__asm__ __volatile__ ("movl $0x01, %%eax;cpuid":"=&a"(reax),"=&b"(rebx),"=&c"(recx),"=&d"(redx));
	
	print("\n\nCPU type:          ");
	switch((reax>>12)&0x3) {
		case 0: print("Original OEM Processor"); break;
		case 1: print("Intel OverDrive (R) Processor"); break;
		case 2: print("Dual processor"); break;
		case 3: print("Intel reserved"); break;
	}
	
	print("\nFamily ID:         ");
	print_int((reax>>8)&0x0F);
	print(" (");
	print_int((reax>>20)&0xFF);
	print(")");
	
	print("\nModel:             ");
	print_int((reax>>4)&0x0F);
	print(" (");
	print_int((reax>>16)&0x0F);
	print(")");
	
	print("\nStepping ID:       ");
	print_int(reax&0x07);
	
	print("\n\nCLFLUSH cache:     ");
	print_int((rebx>>8)&0xFF);
	print(" (");
	print_int(((rebx>>8)&0xFF)*8);
	print("B)");
	
	print("\nLocal APIC ID:     ");
	print_int((rebx>>24)&0xFF);
	
	print("\nEDX flags:         ");
	if((redx>>0)&1) print("FPU ");
	if((redx>>1)&1) print("VME ");
	if((redx>>2)&1) print("DE ");
	if((redx>>3)&1) print("PSE ");
	if((redx>>4)&1) print("TSC ");
	if((redx>>5)&1) print("MSR ");
	if((redx>>6)&1) print("PAE ");
	if((redx>>7)&1) print("MCE ");
	if((redx>>8)&1) print("CX8 ");
	if((redx>>9)&1) print("APIC ");
	if((redx>>11)&1) print("SEP ");
	if((redx>>12)&1) print("MTRR ");
	if((redx>>13)&1) print("PGE ");
	if((redx>>14)&1) print("MCA ");
	if((redx>>15)&1) print("CMOV ");
	if((redx>>16)&1) print("PAT ");
	if((redx>>17)&1) print("PSE-36 ");
	if((redx>>18)&1) print("PSN ");
	if((redx>>19)&1) print("CLFSH ");
	if((redx>>21)&1) print("DS ");
	if((redx>>22)&1) print("ACPI ");
	if((redx>>23)&1) print("MMX ");
	if((redx>>24)&1) print("FXSR ");
	if((redx>>25)&1) print("SSE ");
	if((redx>>26)&1) print("SSE2 ");
	if((redx>>27)&1) print("SS ");
	if((redx>>28)&1) print("HTT ");
	if((redx>>29)&1) print("TM ");
	if((redx>>31)&1) print("PB");
	
	print("\nECX flags:         ");
	if((redx>>0)&1) print("SSE3 ");
	if((redx>>1)&1) print("PCLMULQDQ ");
	if((redx>>2)&1) print("DTES64 ");
	if((redx>>3)&1) print("MONITOR ");
	if((redx>>4)&1) print("DS-CPL ");
	if((redx>>5)&1) print("VMX ");
	if((redx>>6)&1) print("SMX ");
	if((redx>>7)&1) print("EST ");
	if((redx>>8)&1) print("TM2 ");
	if((redx>>9)&1) print("SSSE3 ");
	if((redx>>10)&1) print("CNXT-ID ");
	if((redx>>13)&1) print("CMPXCHG16B ");
	if((redx>>14)&1) print("xTPR-UC ");
	if((redx>>15)&1) print("PDCM ");
	if((redx>>18)&1) print("DCA ");
	if((redx>>19)&1) print("SSE4.1 ");
	if((redx>>20)&1) print("SSE4.2 ");
	if((redx>>21)&1) print("x2APIC ");
	if((redx>>22)&1) print("MOVBE ");
	if((redx>>23)&1) print("POPCNT ");
	if((redx>>25)&1) print("AES ");
	if((redx>>26)&1) print("XSAVE ");
	if((redx>>27)&1) print("OSXSAVE ");
	
	newline();
	set_wait(0);
}

