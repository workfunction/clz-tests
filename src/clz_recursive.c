#include "main.h"

uint32_t count = 16;
uint32_t mask  = 0xFFFFFFFF;

int clz(uint32_t x)
{	
	int result;
	/* shift upper half down, rest is filled up with 0s */
	uint16_t upper = (x >> count); 
	// mask upper half away
	mask >>= count;
	uint16_t lower = (x & mask);

	if(count == 1) {
		return 0;
	}
	
	count >>= 1;
	result = upper ? clz(upper) : (count << 1) + clz(lower);
	count <<= 1;

	return result;
}
