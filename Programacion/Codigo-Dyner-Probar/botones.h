// CHIKEN LITTLE - DYNER - AIDEN - CHERNIAK - CDR '24 
#ifndef BOTONES_H
#define BOTONES_H

#include "Arduino.h"


#define BTN_1 A4
#define BTN_2 A5

#define LED_1 A3
#define LED_2
#define LED_3
#define LED_4

extern uint8_t estrategia;  

void setupBotonesYLeds();
void seleccionarEstrategia();
void mostrarEstrategia(uint8_t estrategia);
void iniciarRobot();
void ejecutarEstrategia();

#endif