#ifndef MEM_H
#define MEM_H

#define memcpy(dst,src,count) \
{ \
	int d0,d1,d2; \
	__asm__ __volatile__("cld;rep;movsw":"=&S"(d0),"=&D"(d1),"=&c" (d2):"0"(src),"1"(dst),"2"(count):"memory"); \
}

#define memset(dst,val,count) \
{ \
	int d0,d1; \
	__asm__ __volatile__("cld;rep;stosw":"=&D"(d0),"=&c"(d1):"0" (dst),"a"(val),"1"(count):"memory"); \
}

#endif

