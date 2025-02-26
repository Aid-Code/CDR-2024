// CHIKEN LITTLE - DYNER - AIDEN - CHERNIAK - CDR '24 
#ifndef BOTONES_H
#define BOTONES_H

#include "Arduino.h"


#define BTN_1 
#define BTN_2
#define BTN_3
#define BTN_4
#define BTN_5
#define BTN_6


extern uint8_t estrategia;  

void setupBotones();
void seleccionarEstrategia();
void iniciarRobot();
void ejecutarEstrategia();

#endif