#ifndef ULTRASONICOS_H
#define ULTRASONICOS_H

#include "Arduino.h"

#define CANT_ULTRASONICOS 3

#define ECHO_DER 12
#define TRIG_DER 13
#define ECHO_IZQ 11
#define TRIG_IZQ 10
#define ECHO_MED 9
#define TRIG_MED 8

extern uint8_t pines_ultrasonico_der[2];
extern uint8_t pines_ultrasonico_cen[2];
extern uint8_t pines_ultrasonico_izq[2];

uint32_t lecturaUltrasonico(uint8_t* pines);
void gestionarMotores(uint32_t distanciaDer, uint32_t distanciaCen, uint32_t distanciaIzq);
uint8_t presencia();

#endif