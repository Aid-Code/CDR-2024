#ifndef BOTONES_H
#define BOTONES_H

#include "Arduino.h"


#define BTN_1 A4
#define BTN_2 A5

#define LED_1 A3
#define LED_2
#define LED_3
#define LED_4

#define DATA 11
#define LATCH 12
#define CLOCK 13


extern uint8_t* pinesLed;
extern uint8_t* pinesBtn;

bool leerBtn(uint8_t pin);
void setLed(uint8_t pin, bool state);
void indicateState(uint8_t* pinesLed, );


void setupBotonesYLeds();


#endif