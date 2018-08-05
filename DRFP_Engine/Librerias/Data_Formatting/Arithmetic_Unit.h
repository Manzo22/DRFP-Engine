#ifndef ARITHMETIC_UNIT
#define ARITHMETIC_UNIT

#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "math.h"

#define PI 3.14159265

int32_t convertir_a_negativo(uint32_t w1, uint32_t w2, uint32_t w3);
float arctan_2(int32_t wx, int32_t wy);
float arctan_3(int32_t wx, int32_t wy, int32_t wz);
float raiz_3(float wx, float wy, float wz);
float raiz_2(float wx, float wy);
int truncar(float valor);
int convertir_a_par(int valor);

#endif // ARITHMETIC_UNIT
