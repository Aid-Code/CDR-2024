#define BTN_2 A5

#define LED_1 0b00000001
#define LED_2 0b10000000
#define LED_3 0b00000010
#define LED_4 A3    // LED conectado directamente al Arduino (pin 4)

#define DATA 11     
#define LATCH 12    
#define CLOCK 13   

enum estados_strat
{
  INIT,
  STRAT_1,
  STRAT_2,
  STRAT_3,
  STRAT_4
}

enum estados_antirrebote
{
  ESPERA,
  CONFIRMACION,
  LIBERACION
}

int strat = INIT;
//int stratAnt;
int contador = 0;
int antirrebote;

int lectura_BTN2;

uint16_t milis;
uint16_t millisAnt;

bool flag_BTN2 = false;

void setup() 
{
  Serial.begin(9600);

  // Configuración de los pines
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(LED_4, OUTPUT);        // LED conectado directamente al pin 4 del Arduino
  
  // Pines del shift register
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
}

void loop() 
{
  milis = millis();
  Antirrebote();

  switch(strat)
  {
    case INIT:
      if (flag_BTN2)
      {
        stratAnt = STRAT_4;
        mostrarBinario(STRAT_1);
        strat = STRAT_1;
      }
    break;

    case STRAT_1:
      if(stratAnt == INIT && flag_BTN2)
      {
        stratAnt = strat - 1;
        mostrarBinario(STRAT_2);
        strat = STRAT_2;
      }
    break;

    case STRAT_2:
      if(stratAnt == STRAT_1 && flag_BTN2)
      {
        stratAnt = strat - 1;
        mostrarBinario(STRAT_3);
        strat = STRAT_3;
      }
    break;

    case STRAT_3:
      if(stratAnt == STRAT_2 && flag_BTN2)
      {
        stratAnt = strat - 1;
        mostrarBinario(STRAT_4);
        strat = STRAT_4;
      }
    break;

    case STRAT_4:
      if(stratAnt == STRAT_3 && flag_BTN2)
      {
        stratAnt = strat - 1;
        mostrarBinario(STRAT_1);
        strat = INIT;
      }
    break;
  }
}

void mostrarBinario(int valor) 
{

  // LEDs conectados al shift register (Q0, Q6, y Q7)
  uint8_t datosShiftRegister = 0b00000000;

  // LED en Q7 (valor binario 0001)
  if (valor & 0b0001) {
    datosShiftRegister |= LED_1; //LED 1
  }

  // LED en Q0 (valor binario 0010)
  if (valor & 0b0010) {
    datosShiftRegister |= LED_2;   //LED 2
  }

  // LED en Q6 (valor binario 0100)
  if (valor & 0b0100) {
    datosShiftRegister |= LED_3; // LED 3
  }

  // LED conectado directamente al pin 4 (LED_4)
  uint8_t estadoLED4 = (valor & 0b1000) ? HIGH : LOW;
  digitalWrite(LED_4, estadoLED4);

  // Enviar los datos al shift register
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, datosShiftRegister);
  digitalWrite(LATCH, HIGH);

  // Mostrar el estado de los LEDs en binario en el monitor serial
  /*Serial.print("Estado de los LEDs: ");
  Serial.print(estadoLED4 ? "1" : "0");       // LED 4 (pin 4)
  Serial.print((valor & 0b0100) ? "1" : "0");  // Q6 (LED 3)
  Serial.print((valor & 0b0010) ? "1" : "0");  // Q0 (LED 2)
  Serial.print((valor & 0b0001) ? "1" : "0");  // Q7 (LED 1)
  
  
 
  Serial.println();*/
}

void Antirrebote()
{
  switch(antirrebote)
  {
    case ESPERA:
      if (lectura_BTN2 == LOW)
      {
        flag_BTN2 = false;
        millisAnt = millis;
        antirrebote = CONFIRMACION;
      }
    break;

    case CONFIRMACION:
      if (lectura_BTN2 == HIGH && millis - millisAnt >= 15)
      {
        antirrebote = ESPERA;
      }
      else if (lectura_BTN2 == LOW && millis - millisAnt >= 15)
      {
        antirrebote = LIBERACION;
      }
    break;

    case LIBERACION:
      if (lectura_BTN2 == HIGH)
      {
        flag_BTN2 = true;
        antirrebote = ESPERA;
      }
    break;
  }
}
