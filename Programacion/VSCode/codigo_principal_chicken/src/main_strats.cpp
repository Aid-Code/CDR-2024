#include "Arduino.h"

// Sensores
#define CNY_IZQ A6
#define CNY_DER A7

#define ECHO_1 8
#define ECHO_2 9 // Izquierda
#define ECHO_3 10 // Medio<
#define ECHO_4 A1 // Derecha
#define ECHO_5 A2

#define TRIG_1 0b00000100
#define TRIG_2 0b01000000 // Izquierda
#define TRIG_3 0b00100000 // Medio
#define TRIG_4 0b00001000 // Derecha
#define TRIG_5 0b00010000

#define TRIG_L 0b00000000

// Botones y Leds
#define BTN_1 A4
#define BTN_2 A5

#define LED_1 0b00000001
#define LED_2 0b10000000
#define LED_3 0b00000010
#define LED_4 A3

//Shift Register
#define DATA 11    
#define LATCH 12    
#define CLOCK 13

// Motor Izquierdo
#define AIN_2 3
#define AIN_1 4
#define PWM_A 6

// Motor Derecho
#define BIN_2 2
#define BIN_1 7
#define PWM_B 5

// Valores
#define PWM_CHILL 50
#define PWM_FULL 70
#define RANGO_ULT 30
#define CUENTAS_RESET 5
#define GIRO_TICTAC 400
#define CANT_ESTRATEGIAS 6

// CNY Izquierdo
uint32_t lectura_cny_izq = 0;
uint32_t cny_izquierdo = 0;
uint32_t suma_cny_izq = 0;

uint32_t izq_blanco = 250;
uint32_t izq_negro = 825;

uint32_t izq_promedio = (izq_blanco + izq_negro) / 2;

//CNY Derecho
uint32_t lectura_cny_der = 0;
uint32_t cny_derecho = 0;
uint32_t suma_cny_der = 0;

uint32_t der_blanco = 315;
uint32_t der_negro = 790;

uint32_t der_promedio = (der_blanco + der_negro) / 2;

bool flag_cny_der = false;
bool flag_cny_izq = false;
bool flag_cny_both = false;

// Ultrasonicos
long tiempo_ult_der = 0;
long tiempo_ult_med = 0;
long tiempo_ult_izq = 0;

long distancia_ult_der = 0;
long distancia_ult_med = 0;
long distancia_ult_izq = 0;

bool flag_ult_der = false;
bool flag_ult_med = false;
bool flag_ult_izq = false;

// Millis
uint16_t actual_millis = 0;
uint16_t prev_millis = 0;

uint16_t stop_millis = 0;
uint16_t step_millis = 0;
uint16_t tictac_millis = 0;
uint16_t radar_millis = 0;
uint16_t arranque_millis = 0;

// Auxiliares

bool is_moving = false;
bool ole = false;
bool flag_arranque = false;

uint8_t flag_tictac = 0;


// Debounce

bool estado_previo[2];
uint8_t contador[2] = {0,0};
uint8_t pines_dbnc[2] = {BTN_1, BTN_2};

bool flag_evento[2] = {false,false};
bool flag_tipo[2] = {false,false};
bool estado_actual;
bool iniciar = false;

auto prev_dbnc_millis = millis();

// Counters

uint8_t counter_direccion = 0;
uint8_t counter_strat = 0;
uint8_t counter_setear = 0;

void funcion_debounce();
void no_caerse();
void maquina_seteadora(int strat);
void direcciones(int direccion);
void mostrarBinario(int valor);

void LecturaUltrasonicos();
void ExistenciaUlt();
void LecturaCNY();
void DetectarLinea();

void Adelante();
void Atras();
void Izquierda();
void Derecha();
void Parado();

void crespin();
void pasitos();
void tic_tac();
void bartolito();
void torero();
void radar();


void setup()
{
  Serial.begin(9600);

  //Motores
  pinMode(PWM_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);

  pinMode(AIN_1, OUTPUT);
  pinMode(BIN_1, OUTPUT);
  pinMode(AIN_2, OUTPUT);
  pinMode(BIN_2, OUTPUT);

  //Sensores
  pinMode(ECHO_4, INPUT);
  pinMode(ECHO_3, INPUT);
  pinMode(ECHO_2, INPUT);

  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);

  //Placa botones
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(LED_4, OUTPUT);

  analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
  analogWrite(PWM_B, PWM_CHILL);  //Motor Derecho

  Serial.println("Setear direccion");

  actual_millis = millis();
  prev_millis = millis();
  step_millis = millis();
  stop_millis = millis();
  radar_millis = millis();
  tictac_millis = millis();
  arranque_millis = millis();
}

void loop() 
{
  if(millis() - prev_dbnc_millis >= 1)
  {
    prev_dbnc_millis = millis();

    funcion_debounce();
  }
  
  if (iniciar && millis() - prev_millis >= 5000)
  {
    LecturaUltrasonicos();
    ExistenciaUlt();
    LecturaCNY();
    DetectarLinea(); 
    //no_caerse();

    if (!flag_arranque)
    {
      direcciones(counter_direccion);
      flag_arranque = true;
    }
    
    maquina_seteadora(counter_strat);

    LecturaCNY();
    DetectarLinea(); 
    //no_caerse();
  }
}

void no_caerse()
{
  if (flag_cny_izq) 
  {
    // Serial.println("Atras");
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);
    Atras();
    delay(400);
    Derecha();
    delay(80);
    analogWrite(PWM_A, PWM_CHILL);
    analogWrite(PWM_B, PWM_CHILL);
    // Serial.println("Derecha");
  } 
  else if (flag_cny_der) 
  {
    // Serial.println("Atras");
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);
    Atras();
    delay(400);
    Izquierda();
    delay(80);
    analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_CHILL);
    // Serial.println("Izquierda");
  }
  else if (flag_cny_both)
  {
    // Serial.println("Atras");
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);
    Atras();
    delay(600);
    Izquierda();
    delay(100);
    analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_CHILL);
    // Serial.println("Izquierda");
  }
}

void direcciones (int direccion)
{
  switch (direccion)
  {
    case 1:
      Serial.println("Izquierda");
      Izquierda();
      break;

    case 2:
      Serial.println("Derecha");
      Derecha();
      break;

    case 3:
      Serial.println("Adelante");
      Adelante();
      break;

    case 4:
      Serial.println("Atras");
      Atras();
      break;

    default:
      Derecha();
      break;
  }
}

void maquina_seteadora (int strat)
{
  switch (strat)
  {
    case 1:
      Serial.println("crespin");
      crespin();
      break;

    case 2:
      Serial.println("pasitos");
      pasitos();
      break;

    case 3:
      Serial.println("tic-tac");
      tic_tac();
      break;

    case 4:
      Serial.println("bartolito");
      bartolito();
      break;

    case 5:
      Serial.println("torero");
      torero();
      break;

    case 6:
      Serial.println("radar");
      radar();
      break;

    default:
      crespin();
      break;
  }
}

void crespin()
{
  if (flag_ult_med)
  {
    analogWrite(PWM_A, PWM_FULL);
    analogWrite(PWM_B, PWM_FULL);
    Adelante();
  }
  else if (flag_ult_der)
  {
    analogWrite(PWM_A, PWM_FULL);
    analogWrite(PWM_B, PWM_FULL);
    Derecha();
  }
  else if (flag_ult_izq)
  {
    analogWrite(PWM_A, PWM_FULL);
    analogWrite(PWM_B, PWM_FULL);
    Izquierda();
  }
  else if (!flag_ult_med)
  {
    analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_CHILL);  //Motor Derecho
    Adelante();
  }
}

void torero()
{
  if (!flag_ult_med && !ole)
  {
    if (distancia_ult_der > 10 && distancia_ult_der <= 50)
    {
      analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
      analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
      Adelante();
      delay(500);

      analogWrite(PWM_A, 250);  //Motor Izquierdo
      analogWrite(PWM_B, 20);  //Motor Derecho
      Adelante();
      delay(600);

      ole = true;
    }
    else if (distancia_ult_izq > 10 && distancia_ult_izq <= 20)
    {
      analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
      analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
      Adelante();
      delay(200);

      analogWrite(PWM_A, 20);  //Motor Izquierdo
      analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
      Adelante();
      delay(600);

      ole = true;
    }
  }
  else if (flag_ult_med && ole)
  {
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
    Adelante();
  }
  else if (flag_ult_der && ole)
  {
    analogWrite(PWM_A, 250);  //Motor Izquierdo
    analogWrite(PWM_B, 100);  //Motor Derecho
    Derecha();
  }
  else if (flag_ult_izq && ole)
  {
    analogWrite(PWM_A, 250);  //Motor Izquierdo
    analogWrite(PWM_B, 100);  //Motor Derecho
    Izquierda();
  }
}

void tic_tac()
{
  if (!flag_ult_med && !flag_ult_der && !flag_ult_izq)
  {
    analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_CHILL);  //Motor Derecho

    if (flag_tictac == 0)
    {
      Derecha();

      if ((millis() - tictac_millis) >= GIRO_TICTAC)
      {
        flag_tictac = 1;
        tictac_millis = millis();
      }
    }
    else if (flag_tictac == 1)
    {
      Izquierda();

      if ((millis() - tictac_millis) >= GIRO_TICTAC)
      {
        flag_tictac = 2;
        tictac_millis = millis();
      }
    }
    else if (flag_tictac == 2)
    {
      Parado();

      if ((millis() - tictac_millis) >= GIRO_TICTAC)
      {
        flag_tictac = 3;
        tictac_millis = millis();
      }
    }
    else if (flag_tictac == 3)
    {
      Izquierda();

      if ((millis() - tictac_millis) >= GIRO_TICTAC)
      {
        flag_tictac = 4;
        tictac_millis = millis();
      }
    }
    else if (flag_tictac == 4)
    {
      Derecha();

      if ((millis() - tictac_millis) >= GIRO_TICTAC)
      {
        flag_tictac = 5;
        tictac_millis = millis();
      }
    }
    else if (flag_tictac == 5)
    {
      Parado();

      if ((millis() - tictac_millis) >= GIRO_TICTAC)
      {
        flag_tictac = 0;
        tictac_millis = millis();
      }
    }
  }
  else if (flag_ult_med)
  {
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
    Adelante();
  }
  else if (flag_ult_der)
  {
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
    Derecha();
  }
  else if (flag_ult_izq)
  {
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
    Izquierda();
  }
}

void radar()
{
  if (distancia_ult_med > 20 || distancia_ult_med == 0)
  {
    Serial.println(distancia_ult_med);
    if (flag_ult_der)
    {
      Serial.println("Derecha");
      analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
      analogWrite(PWM_B, PWM_CHILL);  //Motor Derecho 
      Derecha();
    }
    else if (flag_ult_izq)
    {
      Serial.println("Izquierda");
      analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
      analogWrite(PWM_B, PWM_CHILL);  //Motor Derecho 
      Izquierda();
    }
    else 
    {
      Serial.println("Parado");
      Parado();
    }
  }
    else if (distancia_ult_med <= 20 && distancia_ult_med != 0)
  {
    Serial.println("Adelante");
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho 
    Adelante();
  }
}

void bartolito()
{
  if (!flag_ult_med)
  {
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
    Derecha();
  }
  else if (flag_ult_med)
  {
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
    Adelante();
  }
}

void pasitos()
{
  if (!flag_ult_med && !flag_ult_der && !flag_ult_izq)
  {
    if (is_moving && millis() - step_millis >= 100)
    {
      Parado();
      stop_millis = millis();
      is_moving = false;
    }
    else if (!is_moving && millis() - stop_millis >= 1000)
    {
      Adelante();
      analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
      analogWrite(PWM_B, PWM_CHILL);  //Motor Derecho
      step_millis = millis();
      is_moving = true;
    }
  }
  else if (distancia_ult_med <= 40)
  {
    Adelante();
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
  }
  
  
  if (flag_ult_izq)
  {
    //falta comprobar distancia
    Izquierda();
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
  }
  else if (flag_ult_der)
  {
    //falta comprobar distancia
    Derecha();
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
  }
}

void funcion_debounce(void)
{
  for(uint8_t i = 0; i < 2; i++)
  {
    estado_actual = digitalRead(pines_dbnc[i]);

    if(estado_actual != estado_previo[i])
    {
      contador[i] = CUENTAS_RESET;
      flag_evento[i] = false;
    }
    else
    {
      if(contador[i] > 0)
      {
        contador[i]--;

        if(contador[i] == 0)
        {
          //Serial.println(contador[1]);

          flag_evento[i] = true;
          flag_tipo[i] = estado_actual;
          
          if(contador[0] == 0)
          {
            if (counter_setear == 0)
            {
              counter_direccion++;
              Serial.println(counter_direccion);
              mostrarBinario(counter_direccion);
              if (counter_direccion > 4)
              {
                counter_direccion = 0;
              }
            }
            else if (counter_setear == 1)
            {
              counter_strat++;
              Serial.println(counter_strat);
              mostrarBinario(counter_strat);
              if (counter_strat > CANT_ESTRATEGIAS)
              {
                counter_strat = 0;
              }
            }
          }

          if (contador[1] == 0)
          {
            counter_setear++;

            if (counter_setear == 1)
            {
              mostrarBinario(0);
              Serial.println("Setear Estrategia");
            }
            else if (counter_setear == 2)
            {
              Serial.println("Iniciar");
              iniciar = true;
              prev_millis = millis();
            }
          }
        }
      }
    }
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
  
  
 
  Serial.println();  // Nueva línea*/
}

void LecturaUltrasonicos()
{
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_3);
  digitalWrite(LATCH, HIGH);
  delay(10);
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
  digitalWrite(LATCH, HIGH);


  tiempo_ult_med = pulseIn(ECHO_3, HIGH, 10000);


  distancia_ult_med = tiempo_ult_med / 59;


  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_4);
  digitalWrite(LATCH, HIGH);
  delay(10);
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
  digitalWrite(LATCH, HIGH);


  tiempo_ult_der = pulseIn(ECHO_4, HIGH, 10000);


  distancia_ult_der = tiempo_ult_der / 59;


  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_2);
  digitalWrite(LATCH, HIGH);
  delay(10);
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
  digitalWrite(LATCH, HIGH);


  tiempo_ult_izq = pulseIn(ECHO_2, HIGH, 10000);


  distancia_ult_izq = tiempo_ult_izq / 59;
}


void ExistenciaUlt()
{
  /*Serial.print(distancia_ult_izq);
  Serial.print('\t');
  Serial.print(distancia_ult_med);
  Serial.print('\t');
  Serial.print(distancia_ult_der);
  Serial.println();*/
 
  if (distancia_ult_med < RANGO_ULT && distancia_ult_med != 0) 
  {
    //Serial.println("Hay algo");
    flag_ult_med = true;
  } 
  else 
  {
    //Serial.println("No hay moros en la costa");
    flag_ult_med = false;
  }


  if (distancia_ult_der < RANGO_ULT && distancia_ult_der != 0) 
  {
    flag_ult_der = true;
  } 
  else 
  {
    flag_ult_der = false;
  }


  if (distancia_ult_izq < RANGO_ULT && distancia_ult_izq != 0) 
  {
    flag_ult_izq = true;
  } 
  else
  {
    flag_ult_izq = false;
  }
}

void LecturaCNY() 
{
  for (int i = 0; i < 5; i++)
  {
    lectura_cny_izq = analogRead(CNY_IZQ);
    suma_cny_izq = suma_cny_izq + lectura_cny_izq;
  }


  for (int i = 0; i < 5; i++) 
  {
    lectura_cny_der = analogRead(CNY_DER);
    suma_cny_der = suma_cny_der + lectura_cny_der;
  }


  cny_izquierdo = suma_cny_izq / 5;
  cny_derecho = suma_cny_der / 5;

  /*Serial.println(cny_derecho);
  Serial.print('\t');
  Serial.println(cny_izquierdo);
  Serial.println();*/


  suma_cny_izq = 0;
  suma_cny_der = 0;
}


void DetectarLinea()
{
  if (lectura_cny_izq < izq_promedio) 
  {
    // Serial.println("Blanco");
    flag_cny_izq = true;
  } 
  else 
  {
    // Serial.println("Negro");
    flag_cny_izq = false;
  }


  if (lectura_cny_der < der_promedio) 
  {
    flag_cny_der = true;
  } 
  else 
  {
    flag_cny_der = false;
  }


  if (flag_cny_der && flag_cny_izq) 
  {
    flag_cny_both = false;
  } 
  else 
  {
    flag_cny_both = true;
  }
}


void Parado()
{
  digitalWrite(AIN_1, LOW);
  digitalWrite(AIN_2, LOW);
 
  digitalWrite(BIN_1, LOW);
  digitalWrite(BIN_2, LOW);
}


void Adelante()
{
  digitalWrite(AIN_1, LOW);
  digitalWrite(AIN_2, HIGH);
 
  digitalWrite(BIN_1, HIGH);
  digitalWrite(BIN_2, LOW);
}


void Atras()
{
  digitalWrite(AIN_1, HIGH);
  digitalWrite(AIN_2, LOW);


  digitalWrite(BIN_1, LOW);
  digitalWrite(BIN_2, HIGH);
}


void Derecha()
{
  digitalWrite(AIN_1, LOW);
  digitalWrite(AIN_2, HIGH);


  digitalWrite(BIN_1, LOW);
  digitalWrite(BIN_2, HIGH);
}


void Izquierda()
{
  digitalWrite(AIN_1, HIGH);// Izquierda atras
  digitalWrite(AIN_2, LOW); // Izquierda adelante


  digitalWrite(BIN_1, HIGH); // Derecha adelante
  digitalWrite(BIN_2, LOW); // Derecha atras
}