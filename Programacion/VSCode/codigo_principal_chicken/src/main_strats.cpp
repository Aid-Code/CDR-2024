#include "Arduino.h"

// Sensores
#define CNY_IZQ A6
#define CNY_DER A7

#define ECHO_1 8 // Izquierda
#define ECHO_2 9 // Izquierda 45
#define ECHO_3 10 // Medio 
#define ECHO_4 A1 // Derecha 45
#define ECHO_5 A2 // Derecha

#define TRIG_1 0b00000100 // Izquierda
#define TRIG_2 0b01000000 // Izquierda 45
#define TRIG_3 0b00100000 // Medio
#define TRIG_4 0b00001000 // Derecha 45
#define TRIG_5 0b00010000 // Derecha

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
#define PWM_CHILL 100
#define PWM_FULL 255
#define RANGO_ULT 45
#define CUENTAS_RESET 5
#define GIRO_TICTAC 400
#define CANT_ESTRATEGIAS 6

#define GIRO_IZQ_45 90
#define GIRO_IZQ_90 140
#define GIRO_IZQ_180 280

#define GIRO_DER_45 90
#define GIRO_DER_90 135
#define GIRO_DER_180 220

uint8_t pines_trig_ultrasonicos[5] = [TRIG_1, TRIG_2, TRIG_3, TRIG_4, TRIG_5];
uint8_t pines_echo_ultrasonicos[5] = [ECHO_1, ECHO_2, ECHO_3, ECHO_4, ECHO_5];

// CNY Izquierdo
uint32_t lectura_cny_izq = 0;
uint32_t cny_izquierdo = 0;
uint32_t suma_cny_izq = 0;

uint32_t izq_blanco = 520;
uint32_t izq_negro = 800;

uint32_t izq_promedio = (izq_blanco + izq_negro) / 2;

//CNY Derecho
uint32_t lectura_cny_der = 0;
uint32_t cny_derecho = 0;
uint32_t suma_cny_der = 0;

uint32_t der_blanco = 380;
uint32_t der_negro = 780;

uint32_t der_promedio = (der_blanco + der_negro) / 2;

bool flag_cny_der = false;
bool flag_cny_izq = false;
bool flag_cny_both = false;

// Ultrasonicos
long tiempo_ult = 0;
long distancia_ult = 0;

uint8_t lecturas_ult[5] = [0,0,0,0,0];
uint16_t distancias_ult[5] = [0,0,0,0,0];

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
uint8_t auxiliar = 0;
uint16_t tiempo_direccion_arranque = 0;


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

long lectura(int trig, int echo);
bool existencia(long distancia);
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
    for (uint8_t i = 0, i < 5, i++)
    {
      lecturas_ult[i] = lectura(pines_trig_ultrasonicos[i], pines_echo_ultrasonicos[i]);
      distancias_ult[i] = distancia(pines_trig_ultrasonicos[i], pines_echo_ultrasonicos[i]);
    }
    LecturaCNY();
    DetectarLinea(); 
    no_caerse();

    if (!flag_arranque)
    {
      analogWrite(PWM_A, PWM_FULL);
      analogWrite(PWM_B, PWM_FULL);

      if (auxiliar == 0)
      {
        arranque_millis = millis();
        auxiliar = 1;
      }
      direcciones(counter_direccion);

      if (millis() - arranque_millis >= tiempo_direccion_arranque)
      {
        flag_arranque = true;
      }
    }
    
    if (flag_arranque)
    {
      //maquina_seteadora(counter_strat);
      Parado();
    }
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
    Parado();
    delay(10);
    Derecha();
    delay(100);
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
    delay(120);
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
      Serial.println("Izquierda 45");
      Izquierda();
      tiempo_direccion_arranque = GIRO_IZQ_45;
      break;

    case 2:
      Serial.println("Izquierda 90");
      Izquierda();
      tiempo_direccion_arranque = GIRO_IZQ_90;
      break;

    case 3:
      Serial.println("Izquierda 180");
      tiempo_direccion_arranque = GIRO_IZQ_180;
      Izquierda();
      break;

    case 4:
      Serial.println("Derecha 45");
      tiempo_direccion_arranque = GIRO_DER_45;
      Derecha();
      break;

    case 5:
      Serial.println("Derecha 90");
      tiempo_direccion_arranque = GIRO_DER_90;
      Derecha();
      break;

    case 6:
      Serial.println("Derecha 180");
      tiempo_direccion_arranque = GIRO_DER_180;
      Derecha();
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
      //Serial.println("pasitos");
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
  if (lecturas_ult[3])
  {
    analogWrite(PWM_A, PWM_FULL);
    analogWrite(PWM_B, PWM_FULL);
    Adelante();
  }
  else if (lecturas_ult[2])
  {
    analogWrite(PWM_A, PWM_CHILL);
    analogWrite(PWM_B, PWM_CHILL);
    Derecha();
  }
  else if (lecturas_ult[1])
  {
    analogWrite(PWM_A, PWM_FULL);
    analogWrite(PWM_B, PWM_FULL);
    Derecha();
  }
  else if (lecturas_ult[4])
  {
    analogWrite(PWM_A, PWM_CHILL);
    analogWrite(PWM_B, PWM_CHILL);
    Izquierda();
  }
  else if (lecturas_ult[5])
  {
    analogWrite(PWM_A, PWM_FULL);
    analogWrite(PWM_B, PWM_FULL);
    Izquierda();
  }
  else if (!lecturas_ult[3])
  {
    analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_CHILL);  //Motor Derecho
    Adelante();
  }
}

void torero()
{
  if (!lecturas_ult[3] && !ole)
  {
    if (distancias_ult[5] > 10 && distancias_ult[5] <= 50)
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
    else if (distancias_ult[1] > 10 && distancias_ult[1] <= 20)
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
  else if (distancias_ult[3] && ole)
  {
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
    Adelante();
  }
  else if (distancias_ult[5] && ole)
  {
    analogWrite(PWM_A, 250);  //Motor Izquierdo
    analogWrite(PWM_B, 100);  //Motor Derecho
    Derecha();
  }
  else if (distancias_ult[1] && ole)
  {
    analogWrite(PWM_A, 250);  //Motor Izquierdo
    analogWrite(PWM_B, 100);  //Motor Derecho
    Izquierda();
  }
}

void tic_tac()
{
  if (!distancias_ult[3] && !distancias_ult[1] && !distancias_ult[2] && !distancias_ult[4] && distancias_ult[5])
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
  else if (lecturas_ult[3])
  {
    analogWrite(PWM_A, PWM_FULL);
    analogWrite(PWM_B, PWM_FULL);
    Adelante();
  }
  else if (lecturas_ult[2])
  {
    analogWrite(PWM_A, PWM_CHILL);
    analogWrite(PWM_B, PWM_CHILL);
    Derecha();
  }
  else if (lecturas_ult[1])
  {
    analogWrite(PWM_A, PWM_FULL);
    analogWrite(PWM_B, PWM_FULL);
    Derecha();
  }
  else if (lecturas_ult[4])
  {
    analogWrite(PWM_A, PWM_CHILL);
    analogWrite(PWM_B, PWM_CHILL);
    Izquierda();
  }
  else if (lecturas_ult[5])
  {
    analogWrite(PWM_A, PWM_FULL);
    analogWrite(PWM_B, PWM_FULL);
    Izquierda();
  }
}

void radar()
{
  if (distancias_ult[3] > 20 || distancias_ult[3] == 0)
  {
    //Serial.println(distancias_ult[3]);
    if (lecturas_ult[5])
    {
      //Serial.println("Derecha");
      analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
      analogWrite(PWM_B, PWM_CHILL);  //Motor Derecho 
      Derecha();
    }
    else if (lecturas_ult[4])
    {
      analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
      analogWrite(PWM_B, PWM_CHILL);  //Motor Derecho 
      Derecha();
    }
    else if (lecturas_ult[2])
    {
      //Serial.println("Izquierda");
      analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
      analogWrite(PWM_B, PWM_CHILL);  //Motor Derecho 
      Izquierda();
    }
    else if (lecturas_ult[1])
    {
      analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
      analogWrite(PWM_B, PWM_CHILL);  //Motor Derecho 
      Izquierda();
    }
    else 
    {
      //Serial.println("Parado");
      Parado();
    }
  }
    else if (distancias_ult[3] <= 20 && distancias_ult[3] != 0)
  {
    //Serial.println("Adelante");
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho 
    Adelante();
  }
}

void bartolito()
{
  if (!distancias_ult[3])
  {
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
    Derecha();
  }
  else if (distancias_ult[3])
  {
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
    Adelante();
  }
}

void pasitos()
{
  if (!distancias_ult[3] && !distancias_ult[5] && !distancias_ult[1])
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
  else if (distancias_ult[3] <= 40)
  {
    Adelante();
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
  }
  
  
  if (distancias_ult[1])
  {
    //falta comprobar distancia
    Izquierda();
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
  }
  else if (distancias_ult[5])
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
              if (counter_direccion > 6)
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

bool lectura(int trig, int echo)
{
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, trig);
  digitalWrite(LATCH, HIGH);
  delay(10);
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
  digitalWrite(LATCH, HIGH);


  tiempo_ult = pulseIn(echo, HIGH, 10000);


  distancia_ult = tiempo_ult / 59;

  if (distancia_ult < RANGO_ULT && distancia_ult != 0) 
  {
    //Serial.println("Hay algo");
    return true;
  } 
  else 
  {
    //Serial.println("No hay moros en la costa");
    return false;
  }
}

uint16_t distancia (int trig, int echo)
{
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, trig);
  digitalWrite(LATCH, HIGH);
  delay(10);
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
  digitalWrite(LATCH, HIGH);


  tiempo_ult = pulseIn(echo, HIGH, 10000);


  distancia_ult = tiempo_ult / 59;
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
    flag_cny_both = true;
  } 
  else 
  {
    flag_cny_both = false;
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