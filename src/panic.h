#ifndef PANIC_H
#define PANIC_H

/*
#define PANIC      "\nKernel ci spanikowal i wykrzyczal: "
#define PANIC_FILE "\nBylo to gdzies w pliku "
#define PANIC_LINE ", wydaje mi sie, ze w linii "
#define PANIC_BYE  ")\n\nJa sie tymczasem zmywam,\n \tz pozdrowieniami Procesor,\n \t \tNa razie"
*/

#define PANIC      "\nPanic: "
#define PANIC_FILE "\nPlik: "
#define PANIC_LINE ", linia "
#define PANIC_BYE  ")\n\nZegnam\n"

#define panic(err_str) {         \
	send_serial_str(err_str);      \
	print(PANIC);                  \
	print(err_str);                \
	print(PANIC_FILE);             \
	print(__FILE__);               \
	print(PANIC_LINE);             \
	print_int(__LINE__);           \
	print(" (");                   \
	print_hex(__LINE__);           \
	print(PANIC_BYE);              \
	__asm__ __volatile__ ("movl $0xdeadbeef, %eax"); \
	__asm__ __volatile__ ("hlt"); \
	for(;;);  \
}

#endif

