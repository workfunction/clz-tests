#include <stdio.h>
#include "main.h"

int main(){
	uint32_t test = 0x6732;
	int c = 0;
	c = clz(test);
	printf("%d\n", c);
}
