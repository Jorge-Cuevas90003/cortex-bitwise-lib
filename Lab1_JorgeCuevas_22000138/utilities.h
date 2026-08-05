#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdint.h>
#include <stdio.h>

static inline void bitSet(uint32_t *ptr, uint8_t bit) {
    if (ptr != NULL) {
        if (bit < 32) {
            uint32_t mask = 1UL << bit;
            *ptr |= mask;
            printf("Bit %u set to 1\r\n", bit);
            printf("New value: %u\r\n", *ptr);
        } else {
            printf("Invalid bit number\r\n");
        }
    } else {
        printf("Invalid pointer\r\n");
    }
}

static inline void bitClear(uint32_t *ptr, uint8_t bit) {
    if (ptr != NULL) {
        if (bit < 32) {
            uint32_t mask = 1UL << bit;
            *ptr &= ~mask;
            printf("Bit %u set to 0\r\n", bit);
            printf("New value: %u\r\n", *ptr);
        } else {
            printf("Invalid bit number\r\n");
        }
    } else {
        printf("Invalid pointer\r\n");
    }
}

static inline void bitToggle(uint32_t *ptr, uint8_t bit) {
    if (ptr != NULL) {
        if (bit < 32) {
            uint32_t mask = 1UL << bit;
            *ptr ^= mask; // Alterna el bit usando XOR
            printf("Bit %u toggled\r\n", bit);
            printf("New value: %u\r\n", *ptr);
        } else {
            printf("Invalid bit number\r\n");
        }
    } else {
        printf("Invalid pointer\r\n");
    }
}

static inline uint8_t stringLength(uint8_t *str) {
    if (str == NULL) return 0;

    uint8_t contador = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        contador++;
    }
    printf("The length of the string is: %u\r\n", contador);
    return contador; // Retorno del resultado
}

#endif