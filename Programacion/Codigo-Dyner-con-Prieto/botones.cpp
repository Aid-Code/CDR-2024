#include "botones.h"

void setupBotonesYLeds() {
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
}

bool leerBtn(uint8_t pin)
{
  uint8_t lecturaBtn = digitalRead(pin);

  if (lecturaBtn == LOW)
  {
    return true;
  }
  else 
  {
    return false;
  }
}

void setLed(uint8_t pin, bool stateLed)
{
  
}

void indicateState(uint8_t* pinesLed, uint8_t contador)
{

}

uint8_t contadorBtn(bool stateBtn)
{

}

bool timerStart(bool stateBtn)
{
  
}