// CHIKEN LITTLE - DYNER - AIDEN - CHERNIAK - CDR '24
#ifndef CNY_H
#define CNY_H

#include "Arduino.h"
#define CANT_CNY 2

#define CNY_IZQ A6
#define CNY_DER A7

extern uint8_t* pines_cny_der;
extern uint8_t* pines_cny_izq;

bool lecturaCny(uint8_t* pines);
uint8_t linea();

void setupCny();

#endif