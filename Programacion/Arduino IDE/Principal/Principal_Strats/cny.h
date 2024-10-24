#ifndef CNY_H
#define CNY_H

#include "Arduino.h"
#define CANT_CNY 3

#define CNY_IZQ A7
#define CNY_DER A6

extern uint8_t pines_cny_der;
extern uint8_t pines_cny_izq;

bool lecturaCny(uint8_t* pines);
uint8_t linea();
void setupCny();

#endif