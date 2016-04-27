#include "ver.h"

void print_stamp() {
	print(SYSVER_NAME);
	print(" ver. ");
	print_int(SYSVER_MAJ);
	putch('.');
	print_int(SYSVER_MIN);
	putch('.');
	print_int(SYSVER_PLVL);
	print(" (");
	print(SYSVER_ADD);
	print(")\n");
	print("Compiled with GNU gcc ");
	print(__VERSION__);
	print(", ");
	print(__TIMESTAMP__);
	print("\n\n");
	print(SYSVER_CPR);
	print(SYSVER_LIC);
	newline();
};

void cmd_ver() {
	print_stamp();
}

