#include "main.h"

int clz(uint32_t x) {
    return __builtin_clz(x);
}
