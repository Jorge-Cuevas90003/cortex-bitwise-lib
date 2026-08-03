#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdint.h> //uint32_t and uint8_t

void bitSet(uint32_t *ptr, uint8_t bit);
void bitClear(uint32_t *ptr, uint8_t bit) ;
void bitToggle(uint32_t *ptr, uint8_t bit);
uint8_t stringLength(uint8_t *str);

#endif