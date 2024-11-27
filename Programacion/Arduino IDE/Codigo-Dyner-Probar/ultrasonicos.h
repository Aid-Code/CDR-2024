// CHIKEN LITTLE - DYNER - AIDEN - CHERNIAK - CDR '24
#ifndef ULTRASONICOS_H
#define ULTRASONICOS_H

#include "Arduino.h"

#define CANT_ULTRASONICOS 5

#define ECHO_DER A2  //5
#define TRIG_DER     //5
#define ECHO_IZQ 8   //1
#define TRIG_IZQ     //1
#define ECHO_MED 10  //3
#define TRIG_MED     //3

extern uint8_t* pines_ultrasonico_der;
extern uint8_t* pines_ultrasonico_cen;
extern uint8_t* pines_ultrasonico_izq;

extern uint32_t distanciaDer;
extern uint32_t distanciaIzq;
extern uint32_t distanciaCen;

bool lecturaUltrasonico(uint8_t* pines);
uint8_t presencia();

void setupUltrasonicos();

#endif