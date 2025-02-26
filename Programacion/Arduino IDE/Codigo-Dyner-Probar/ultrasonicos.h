// CHIKEN LITTLE - DYNER - AIDEN - CHERNIAK - CDR '24
#ifndef ULTRASONICOS_H
#define ULTRASONICOS_H

#include "Arduino.h"

#define CANT_ULTRASONICOS 5

#define ECHO_DER
#define TRIG_DER
#define ECHO_MED_DER
#define TRIG_MED_DER
#define ECHO_IZQ
#define TRIG_IZQ 
#define ECHO_MED_IZQ
#define TRIG_MED_IZQ 
#define ECHO_MED
#define TRIG_MED

extern uint8_t* pines_ultrasonico_der;
extern uint8_t* pines_ultrasonico_cen_der;
extern uint8_t* pines_ultrasonico_cen;
extern uint8_t* pines_ultrasonico_cen_izq;
extern uint8_t* pines_ultrasonico_izq;

extern uint32_t distanciaDer;
extern uint32_t distanciaCenDer;
extern uint32_t distanciaIzq;
extern uint32_t distanciaCenIzq;
extern uint32_t distanciaCen;

bool lecturaUltrasonico(uint8_t* pines);
uint8_t presencia();

void setupUltrasonicos();

#endif