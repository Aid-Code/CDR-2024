#ifndef ULTRASONICOS_H
#define ULTRASONICOS_H

#include "Arduino.h"

#define CANT_ULTRASONICOS 3

#define ECHO_DER 12  //3
#define TRIG_DER 13  //3
#define ECHO_IZQ 11  //1
#define TRIG_IZQ 10  //1
#define ECHO_MED 9   //2
#define TRIG_MED 8   //

#define SENSOR_CEN ((sensores << 2) >> 6)
#define SENSOR_DER ((sensores >> 6))
#define SENSOR_IZQ ((sensores << 4) >> 6) 

extern uint8_t* pines_ultrasonico_der;
extern uint8_t* pines_ultrasonico_cen;
extern uint8_t* pines_ultrasonico_izq;



uint8_t lecturaUltrasonico(uint8_t* pines);
uint8_t presencia();
void setupUltrasonicos();
#endif