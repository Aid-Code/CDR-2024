#ifndef CNY_H
#define CNY_H

#include "Arduino.h"
#define CANT_CNY 3

#define CNY_IZQ A1
#define CNY_DER A0

extern uint8_t pines_cny_der[];
extern uint8_t pines_cny_izq[];

bool lecturaCny(uint8_t pines, uint32_t umbral);
uint8_t linea();

#endif