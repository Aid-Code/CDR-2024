#include "botones.h"

void setupBotonesYLeds() 
{
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(BIT_LED_1, OUTPUT);
  pinMode(BIT_LED_2, OUTPUT);
  pinMode(BIT_LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
}

bool leerBtn(uint8_t pin)  //Hacer antirebote, si es que falta
{
  bool act_state = digitalRead(pin);

  if(act_state != prev_state)
  {
    btn_counter = CUENTAS_RESET;
  }
  else
  {
    if(btn_counter > 0)
    {
      btn_counter--;

      if(btn_counter == 0)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
  }
}

void setLed(uint8_t pin, bool stateLed) 
{
}

void indicateState(uint8_t* pinesLed, uint8_t contador) 
{
  contador = contadorBtn(leerBtn(BTN_1));
  // LEDs conectados al shift register (Q0, Q6, y Q7)
  uint8_t datosShiftRegister = 0b00000000;

  // LED en Q7 (valor binario 0001)
  if (contador & 0b0001) {
    datosShiftRegister |= BIT_LED_1; //LED 1
  }

  // LED en Q0 (valor binario 0010)
  if (contador & 0b0010) {
    datosShiftRegister |= BIT_LED_2;   //LED 2
  }

  // LED en Q6 (valor binario 0100)
  if (contador & 0b0100) {
    datosShiftRegister |= BIT_LED_3; // LED 3
  }

  // LED conectado directamente al pin 4 (LED_4)
  uint8_t estadoLED4 = (contador & 0b1000) ? HIGH : LOW;
  digitalWrite(LED_4, estadoLED4);

  // Enviar los datos al shift register
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, datosShiftRegister);
  digitalWrite(LATCH, HIGH);
}

uint8_t contadorBtn(bool stateBtn) 
{
  uint8_t contador = 0;

  stateBtn = leerBtn(BTN_1);
  if (stateBtn == true)
  {
    contador++;

    if (contador > 5)
    {
      contador = 0;
    }

    return contador;
  }
}

bool timerStart(bool stateBtn) 
{
  millis();
  uint16_t prev_millis = 0;
  stateBtn = leerBtn(BTN_2);

  if (stateBtn == true)
  {
    prev_millis = millis();
    if (millis() - prev_millis == 5000)
    {
      return true;
    }
    else 
    {
      return false;
    }
  }
}