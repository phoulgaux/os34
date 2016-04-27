#include "../system.h"

s32int_t strlen(str_t);
s32int_t strcmp(str_t, str_t);

s32int_t strlen(str_t str) {
	int i=0;
	int len=0;
	while (str[i]) {
		len++;
		i++;
	}
	return len;
}

s32int_t strcmp(str_t x, str_t y) {
	int i=0;
	while(x[i]||y[i]) {
		if(x[i]!=y[i])
			return 1;
		i++;
	}
	return 0;
}

