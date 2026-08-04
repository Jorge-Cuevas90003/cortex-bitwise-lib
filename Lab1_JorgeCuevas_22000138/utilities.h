#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdint.h> //uint32_t and uint8_t
#include "stdio.h"//para poder uitilzia rla funcion printf
static inline void bitSet(uint32_t *ptr, uint8_t bit){
if(&ptr!=NULL){

if(bit<32){

uint32_t mask=1<<bit;
*ptr|=mask;
printf("Bit %d set to 1\n",bit);
printf("New value: %d\n",*ptr);
}else{

printf("Invalid bit number ");
}
}else{
printf("Invalid pointer");

}


}
static inline void bitClear(uint32_t *ptr, uint8_t bit) {
if(&ptr!=NULL){

if(bit<32){

uint32_t mask=1<<bit;
*ptr&=~mask;
printf("Bit %d set to 0\n",bit);
printf("New value: %d\n",*ptr);
}else{

printf("Invalid bit number ");
}
}else{
printf("Invalid pointer");

}



}
static inline void bitToggle(uint32_t *ptr, uint8_t bit){



}
static inline uint8_t stringLength(uint8_t *str){


}


#endif