#include "utilities.h"

#include "RTE_Components.h"
#include CMSIS_device_header
#include "stdio.h"//Para poder utilizart la funcion printf

int main() {
uint8_t bit=1; 
uint32_t value=0x00000000; //La direccion de memoria

//printf("Hello World\n");
//printf("Ingresa el numero de bit que deseas modificar: \n\r");
//scanf("%u",&bit);

//llamar las funciones 


bitSet(&value,bit);


bitClear(&value,bit);

    


}
