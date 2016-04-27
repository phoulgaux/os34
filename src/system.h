#ifndef SYSTEM_H
#define SYSTEM_H

#include "panic.h"
#include "mboot.h"

//#define VERBOSE

// standard constants
#define NULL ((void*)0)
#define VGA_ADDR   0xB8000
#define HTAB_WIDTH 8
#define SCR_HEIGHT 25
#define SCR_WIDTH  80
#define DEFAULT_FILL 0x0700

// standard integer types
typedef unsigned char           u8int_t;
typedef signed char             s8int_t;
typedef unsigned short         u16int_t;
typedef signed short           s16int_t;
typedef unsigned int           u32int_t;
typedef signed int             s32int_t;
typedef unsigned long long int u64int_t;
typedef signed long long int   s64int_t;

// own datatypes
typedef char* str_t;

// register list
typedef struct registers {
	u32int_t ds;
	u32int_t edi,esi,ebp,esp,ebx,edx,ecx,eax;
	u32int_t int_no, err_code;
	u32int_t eip,cs,eflags,useresp,ss;
} regs_t;

// function type needed by irq_handler()
typedef void (*isr_t)(regs_t);

// version info
#define SYSVER_NAME "os34"
#define SYSVER_MAJ  0
#define SYSVER_MIN  1
#define SYSVER_PLVL 4
#define SYSVER_ADD  "in-dev"
#define SYSVER_CPR	"(C) Piotr Balbier, 2010\n"
#define SYSVER_LIC	"Private build"

// init strings
#ifdef VERBOSE
#define INIT_VIDEO  "Ekran...              "
#define INIT_TIMER  "PIT...                "
#define INIT_KBD    "Klawiatura...         "
#define INIT_PAGING "Stronicowanie...      "
#define INIT_STI    "STI...                "
#define INIT_OK			"[ OK ]\n"
#else
#define INIT_VIDEO  ""
#define INIT_TIMER  ""
#define INIT_KBD    ""
#define INIT_PAGING ""
#define INIT_STI    ""
#define INIT_OK     ""
#endif

#endif

