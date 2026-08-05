#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdint.h> //uint32_t and uint8_t
#include "stdio.h"//para poder uitilzia rla funcion printf
static inline void bitSet(uint32_t *ptr, uint8_t bit){
if(&ptr!=NULL){

if(bit<32){

uint32_t mask=1<<bit;
*ptr|=mask;
printf("Bit %d set to 1\r\n",bit);
printf("New value: %d\r\n",*ptr);
}else{

printf("Invalid bit number\r\n");
}
}else{
printf("Invalid pointer\r\n");

}


}
static inline void bitClear(uint32_t *ptr, uint8_t bit) {
if(&ptr!=NULL){

if(bit<32){

uint32_t mask=1<<bit;
*ptr&=~mask;
printf("Bit %d set to 0\r\n",bit);
printf("New value: %d\r\n",*ptr);
}else{

printf("Invalid bit number\r\n");
}
}else{
printf("Invalid pointer\r\n");

}



}
static inline void bitToggle(uint32_t *ptr, uint8_t bit){

if(&ptr!=NULL){

if(bit<32){
uint32_t mask=1<<bit;
if(mask&*ptr==*ptr){
bitClear(&ptr, bit);

}else{
bitSet(&ptr, bit);

}



}else{

printf("Invalid bit number ");
}
}else{
printf("Invalid pointer");
}


}
static inline uint8_t stringLength(uint8_t *str){
int contador =0;
for(int i=0; str[i]!='\0';i++){
contador++;
}
printf("The length of the string is: %d\r\n",contador);
}


#endif