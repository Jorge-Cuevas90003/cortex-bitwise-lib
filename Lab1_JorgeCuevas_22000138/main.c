#include "utilities.h"

#include "RTE_Components.h"
#include CMSIS_device_header
#include "stdio.h"//Para poder utilizart la funcion printf

int main() {
uint8_t bit=1; 
uint32_t value=0x00000000; //La direccion de memoria
uint8_t texto[]="Universidad Galileo";
//printf("Hello World\n");
//printf("Ingresa el numero de bit que deseas modificar: \n\r");
//scanf("%u",&bit);

//llamar las funciones 
printf("Jorge Cuevas     22000138       04/08/2026 \n\r");

bitSet(&value,bit);

bitToggle(&value, bit);


bitClear(&value,bit);

stringLength(texto);
    
// Bucle infinito para mantener el procesador en ejecucion
    for (;;) {
    }

}
