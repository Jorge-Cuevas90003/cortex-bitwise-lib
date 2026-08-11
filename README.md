# cortex-bitwise-lib ⚡

[![Language](https://img.shields.io/badge/Language-C99-00599C.svg?logo=c&logoColor=white)](https://en.cppreference.com/w/c)
[![Architecture](https://img.shields.io/badge/Architecture-ARM%20Cortex--M4-0091BD.svg?logo=arm&logoColor=white)](https://developer.arm.com/Processors/Cortex-M4)
[![Standard](https://img.shields.io/badge/CMSIS-Core%20v5-green.svg?logo=arm)](https://arm-software.github.io/CMSIS_5/)
[![Toolchain](https://img.shields.io/badge/Toolchain-CMSIS--Toolbox%20%7C%20AC6-blue.svg)](https://www.keil.arm.com/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

Librería de utilidades en lenguaje C para la manipulación precisa de bits en registros de 32 bits y cálculo de longitud de cadenas a bajo nivel en arquitecturas **ARM Cortex-M** (enfocado en plataformas STM32 / ARMCM4).

Diseñada especialmente para sistemas embebidos, firmware de bajo nivel y control de registros mapeados en memoria (MMIO).

---

## 📋 Tabla de Contenidos

- [Descripción General](#-descripción-general)
- [Estructura del Proyecto](#-estructura-del-proyecto)
- [Fundamentos Teóricos](#-fundamentos-teóricos)
  - [Manipulación de Bits (Bitwise Operations)](#manipulación-de-bits-bitwise-operations)
  - [Paso por Referencia](#paso-por-referencia)
  - [Manejo de Cadenas en Memoria](#manejo-de-cadenas-en-memoria)
- [Documentación de la API (`utilities.h`)](#-documentación-de-la-api-utilitiesh)
- [Demostración y Ejemplo (`main.c`)](#-demostración-y-ejemplo-mainc)
- [Resultados y Evidencias de Ejecución](#-resultados-y-evidencias-de-ejecución)
- [Entorno de Desarrollo y Simulación](#-entorno-de-desarrollo-y-simulación)
- [Autor](#-autor)

---

## 🎯 Descripción General

En el desarrollo de firmware y sistemas embebidos de bajo nivel para microcontroladores ARM Cortex, los periféricos y registros de control (GPIO, Timers, UART, etc.) se configuran a través de registros mapeados en memoria (MMIO) de 32 bits. Cada bit o campo de bits en un registro representa una bandera de estado, habilitación de reloj o configuración de un pin.

Este repositorio implementa una colección de funciones auxiliares optimizadas (`static inline`) que permiten:
1. **Encender bits (`bitSet`)**: Establecer un bit específico en `1` mediante una máscara lógica OR sin alterar el resto de los bits.
2. **Limpiar bits (`bitClear`)**: Forzar un bit específico a `0` mediante una máscara AND invertida (NOT).
3. **Alternar bits (`bitToggle`)**: Conmutar el estado lógico de un bit específico mediante la operación XOR.
4. **Medir longitud de cadenas (`stringLength`)**: Determinar la cantidad exacta de caracteres procesando la memoria contigua hasta encontrar el delimitador nulo (`\0`).

---

## 📁 Estructura del Proyecto

```plaintext
cortex-bitwise-lib/
│
├── Lab1_JorgeCuevas_22000138.csolution.yml  # Configuración global CMSIS Solution
├── Lab1_JorgeCuevas_22000138.cbuild-idx.yml # Metadatos de compilación
├── vcpkg-configuration.json                 # Configuración del gestor de paquetes
├── README.md                                # Documentación principal del repositorio
│
└── Lab1_JorgeCuevas_22000138/
    ├── Lab1_JorgeCuevas_22000138.cproject.yml # Definición de componentes y toolchain
    ├── utilities.h                            # Cabecera con las funciones de manipulación de bits
    ├── main.c                                 # Programa principal y casos de prueba
    └── RTE/                                   # Archivos del CMSIS Run-Time Environment
```

---

## 🔬 Fundamentos Teóricos

### Manipulación de Bits (Bitwise Operations)

Para manipular un bit en la posición $n$ ($0 \le n < 32$) de un registro de 32 bits, se construye una máscara binaria mediante el operador de desplazamiento a la izquierda:

$$\text{Máscara} = 1\text{UL} \ll n$$

| Operación | Función | Expresión Bitwise | Comportamiento |
| :--- | :--- | :--- | :--- |
| **Set (Encendido)** | `bitSet` | `*ptr |= (1UL << bit);` | Aplica OR lógico. Si el bit era 0 pasa a 1; si era 1 permanece en 1. |
| **Clear (Limpieza)** | `bitClear` | `*ptr &= ~(1UL << bit);` | Aplica AND con la máscara invertida. Fuerza el bit a 0 manteniendo el resto idéntico. |
| **Toggle (Inversión)** | `bitToggle` | `*ptr ^= (1UL << bit);` | Aplica XOR lógico. Invierte el estado actual del bit ($0 \to 1$ ó $1 \to 0$). |

### Paso por Referencia

Las funciones reciben punteros (`uint32_t *ptr`) en lugar de variables por valor. Esto permite acceder y desreferenciar la dirección física real en memoria del procesador donde reside la variable o registro, garantizando que los cambios surtan efecto en el contexto del llamante (`main()`) y en registros de periféricos en hardware.

### Manejo de Cadenas en Memoria

En C, las cadenas de caracteres son arreglos contiguos de bytes terminados por el carácter nulo `0x00` (`\0`). La función `stringLength` recorre secuencialmente cada posición de memoria incrementando un contador hasta detectar el terminador nulo, garantizando un conteo exacto sin requerir dependencias pesadas de la librería estándar `<string.h>`.

---

## 🛠 Documentación de la API (`utilities.h`)

Todas las funciones están definidas como `static inline` para máxima eficiencia de ejecución y evitar sobrecostos de llamada en sistemas embebidos. Cuentan con validación defensiva contra punteros nulos (`NULL`) y desbordamiento de índice de bit ($\ge 32$).

```c
#include "utilities.h"
```

### 1. `bitSet`
```c
static inline void bitSet(uint32_t *ptr, uint8_t bit);
```
- **Parámetros:**
  - `ptr`: Puntero a la variable o registro de 32 bits (`uint32_t *`).
  - `bit`: Índice del bit a encender ($0$ a $31$).
- **Validaciones:** Comprueba `ptr != NULL` y `bit < 32`.

### 2. `bitClear`
```c
static inline void bitClear(uint32_t *ptr, uint8_t bit);
```
- **Parámetros:**
  - `ptr`: Puntero a la variable o registro de 32 bits (`uint32_t *`).
  - `bit`: Índice del bit a limpiar ($0$ a $31$).
- **Validaciones:** Comprueba `ptr != NULL` y `bit < 32`.

### 3. `bitToggle`
```c
static inline void bitToggle(uint32_t *ptr, uint8_t bit);
```
- **Parámetros:**
  - `ptr`: Puntero a la variable o registro de 32 bits (`uint32_t *`).
  - `bit`: Índice del bit a conmutar ($0$ a $31$).
- **Validaciones:** Comprueba `ptr != NULL` y `bit < 32`.

### 4. `stringLength`
```c
static inline uint8_t stringLength(uint8_t *str);
```
- **Parámetros:**
  - `str`: Puntero a la cadena de caracteres (`uint8_t *`).
- **Retorno:** Cantidad de caracteres contados antes del terminador `\0`. Retorna `0` si el puntero es `NULL`.

---

## 💻 Demostración y Ejemplo (`main.c`)

```c
#include "utilities.h"
#include "RTE_Components.h"
#include CMSIS_device_header
#include <stdio.h>

int main(void) {
    uint8_t bit = 1; 
    uint32_t value = 0x00000000;
    uint8_t texto[] = "Cortex-M Bitwise Library";

    // 1. Encender el bit 1: 0x00000000 -> 0x00000002 (Valor decimal: 2)
    bitSet(&value, bit);

    // 2. Conmutar el bit 1: 0x00000002 -> 0x00000000 (Valor decimal: 0)
    bitToggle(&value, bit);

    // 3. Limpiar el bit 1: 0x00000000 -> 0x00000000 (Valor decimal: 0)
    bitClear(&value, bit);

    // 4. Medir longitud de la cadena
    stringLength(texto);
    
    // Bucle infinito para mantener el procesador en ejecución
    for (;;) {
    }
}
```

---

## 📊 Resultados y Evidencias de Ejecución

### Cálculos Teóricos

1. **Estado Inicial:** `value = 0x00000000` ($0_{10}$), `bit = 1`.
2. **Máscara:** `1 << 1` = $2_{10}$ (`0b00000010`).
3. **`bitSet(&value, 1)`:** $0 \text{ OR } 2 = 2_{10}$ $\to$ `New value: 2`.
4. **`bitToggle(&value, 1)`:** $2 \text{ XOR } 2 = 0_{10}$ $\to$ `New value: 0`.
5. **`bitClear(&value, 1)`:** $0 \text{ AND } (\text{NOT } 2) = 0_{10}$ $\to$ `New value: 0`.

### Salida en Consola de Depuración (Semihosting / FVP Cortex-M4)

```text
[model] Bit 1 set to 1
[model] New value: 2
[model] Bit 1 toggled
[model] New value: 0
[model] Bit 1 set to 0
[model] New value: 0
[model] The length of the string is: 19
```

---

## ⚙️ Entorno de Desarrollo y Simulación

- **IDE / Editor:** Keil Studio for VS Code / Arm Keil MDK
- **Compilador:** Arm Compiler 6 (AC6) con estándar DWARF 5
- **Framework:** CMSIS (Cortex Microcontroller Software Interface Standard)
- **Target Hardware / Simulación:** Arm Virtual Hardware (AVH) / Fixed Virtual Platform (`FVP_MPS2_Cortex_M4`) & Placas STM32 Nucleo.

---

## 👤 Autor

- **Jorge Daniel Cuevas Mejía**
- **GitHub:** [@Jorge-Cuevas90003](https://github.com/Jorge-Cuevas90003)
- **Repositorio:** [cortex-bitwise-lib](https://github.com/Jorge-Cuevas90003/cortex-bitwise-lib)
