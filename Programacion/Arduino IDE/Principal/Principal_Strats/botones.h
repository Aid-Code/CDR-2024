#ifndef BOTONES_H
#define BOTONES_H

#include "Arduino.h"


#define BTN_1 A4
#define BTN_2 A5

#define BIT_LED_1 0b01000000 // basura // POR QUE!?
#define BIT_LED_2 0b00000001
#define BIT_LED_3 0b10000000
#define LED_4 A3

#define DATA 11
#define LATCH 12
#define CLOCK 13

#define CUENTAS_RESET 5

extern uint8_t* pinesLed;
extern uint8_t* pinesBtn;


bool prev_state;
uint8_t btn_counter;

auto prev_dbnc_millis = millis();


bool leerBtn(uint8_t pin);
void setLed(uint8_t pin, bool stateLed);
void indicateState(uint8_t* pinesLed, uint8_t contador);
uint8_t contadorBtn(bool stateBtn);
bool timerStart(bool stateBtn);


void setupBotonesYLeds();


#endif