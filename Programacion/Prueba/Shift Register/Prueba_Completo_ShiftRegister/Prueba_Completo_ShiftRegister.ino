//Sensores
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

//Botones y Leds
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

//Motor Izquierdo
#define AIN_2 3
#define AIN_1 4
#define PWM_A 6

// Motor Derecho
#define BIN_2 2
#define BIN_1 7
#define PWM_B 5

//Ultrasonicos

long tiempo_ult_der = 0;
long tiempo_ult_med = 0;
long tiempo_ult_izq = 0;

long distancia_ult_der = 0;
long distancia_ult_med = 0;
long distancia_ult_izq = 0;

bool flag_ult_der = false;
bool flag_ult_med = false;
bool flag_ult_izq = false;

//CNY Izquierdo

uint32_t lectura_cny_izq = 0;
uint32_t cny_izquierdo = 0;
uint32_t suma_cny_izq = 0;

uint32_t izq_blanco = 195;
uint32_t izq_negro = 800;

uint32_t izq_promedio = (izq_blanco + izq_negro) / 2;

//CNY Derecho

uint32_t lectura_cny_der = 0;
uint32_t cny_derecho = 0;
uint32_t suma_cny_der = 0;

uint32_t der_blanco = 45;
uint32_t der_negro = 725;

uint32_t der_promedio = (der_blanco + der_negro) / 2;

bool flag_cny_der = false;
bool flag_cny_izq = false;
bool flag_cny_both = false;

int auxiliar = 0;
int milis = 0;
int milisAnt = 0;

//Botones

int lectura_BTN1 = 0;
int lectura_BTN2 = 0;

bool flag_BTN1 = false;
bool flag_BTN2 = false;

//Maquina seteadora

enum strats
{
  INIT,
  STRAT_1,
  STRAT_2,
  STRAT_3,
  STRAT_4
}

int strat = INIT;
int strat_Ant;
int contador = 0;

//Antirrebotes 

enum estados_antirrebote
{
  ESPERA,
  CONFIRMACION,
  LIBERACION
}

int antirrebote_1;
int antirrebote_2;

void LecturaUltrasonicos();
void ExistenciaUlt();
void LecturaCNY();
void DetectarLinea();

void Adelante();
void Atras();
void Izquierda();
void Derecha();
void Parado();

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

  //Boton y led
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(LED_4, OUTPUT);

  analogWrite(PWM_A, 100);  //Motor Izquierdo
  analogWrite(PWM_B, 100);  //Motor Derecho
}

void loop() 
{
  milis = millis();
  
  lectura_BTN1 = digitalRead(BTN_1);
  lectura_BTN2 = digitalRead(BTN_2);

  if (flag_BTN1)
  {
    auxiliar = 1;
    milisAnt = milis;
    Serial.println("Apretado");
    
  }

  if (auxiliar == 1 && milis - milisAnt >= 5000)
  {
    digitalWrite(LED_4, HIGH);
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, 0b10000011);
    digitalWrite(LATCH, HIGH);
    Serial.println("Encendido");

    LecturaUltrasonicos();
    ExistenciaUlt();
    LecturaCNY();
    DetectarLinea();

    if (flag_cny_izq) {
      // Serial.println("Atras");
      analogWrite(PWM_A, 250);  //Motor Izquierdo
      analogWrite(PWM_B, 250);
      Atras();
      delay(600);
      Izquierda();
      delay(100);
      analogWrite(PWM_A, 100);
      analogWrite(PWM_B, 100);
      // Serial.println("Derecha");

    } else if (flag_cny_der) {
      // Serial.println("Atras");
      analogWrite(PWM_A, 250);  //Motor Izquierdo
      analogWrite(PWM_B, 250);
      Atras();
      delay(600);
      Derecha();
      delay(100);
      analogWrite(PWM_A, 100);  //Motor Izquierdo
      analogWrite(PWM_B, 100);
      // Serial.println("Izquierda");
    } else {
      // Serial.println("Adelante");
      Adelante();
    }

    if (flag_ult_med) 
    {
      analogWrite(PWM_A, 255);
      analogWrite(PWM_B, 255);

      //Serial.println("Medio");
      Adelante();
      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLOCK, LSBFIRST, LED_2);
      digitalWrite(LATCH, HIGH);
      delay(10);
      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
      digitalWrite(LATCH, HIGH);
      digitalWrite(LED_4, LOW);
    } 
    else if (flag_ult_der) 
    {
      analogWrite(PWM_A, 255);
      analogWrite(PWM_B, 255);

      //Serial.println("Derecha");
      Derecha();
      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLOCK, LSBFIRST, LED_1);
      digitalWrite(LATCH, HIGH);
      delay(10);
      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
      digitalWrite(LATCH, HIGH);
      digitalWrite(LED_4, LOW);

    } else if (flag_ult_izq) 
    {
      analogWrite(PWM_A, 255);
      analogWrite(PWM_B, 255);

      //Serial.println("Izquierda");
      Izquierda();
      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLOCK, LSBFIRST, LED_3);
      digitalWrite(LATCH, HIGH);
      delay(10);
      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
      digitalWrite(LATCH, HIGH);
      digitalWrite(LED_4, LOW);
    } 
    else
    {
      analogWrite(PWM_A, 100);
      analogWrite(PWM_B, 100);
    }
  } 
}

void MaquinaSeteadora()
{
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

void mostrarBinario(int valor) {

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
  Serial.print("Estado de los LEDs: ");
  Serial.print(estadoLED4 ? "1" : "0");       // LED 4 (pin 4)
  Serial.print((valor & 0b0100) ? "1" : "0");  // Q6 (LED 3)
  Serial.print((valor & 0b0010) ? "1" : "0");  // Q0 (LED 2)
  Serial.print((valor & 0b0001) ? "1" : "0");  // Q7 (LED 1)
  
  
 
  Serial.println();  // Nueva línea
}

void AntirreboteBTN1()
{
  switch(antirrebote_1)
  {
    case ESPERA:
      if (lectura_BTN1 == LOW)
      {
        flag_BTN1 = false;
        millisAnt = millis;
        antirrebote_1 = CONFIRMACION;
      }
    break;

    case CONFIRMACION:
      if (lectura_BTN1 == HIGH && millis - millisAnt >= 15)
      {
        antirrebote_1 = ESPERA;
      }
      else if (lectura_BTN1 == LOW && millis - millisAnt >= 15)
      {
        antirrebote_1 = LIBERACION;
      }
    break;

    case LIBERACION:
      if (lectura_BTN1 == HIGH)
      {
        flag_BTN1 = true;
        antirrebote_1 = ESPERA;
      }
    break;
  }
}

void AntirreboteBTN2()
{
  switch(antirrebote_2)
  {
    case ESPERA:
      if (lectura_BTN2 == LOW)
      {
        flag_BTN2 = false;
        millisAnt = millis;
        antirrebote_2 = CONFIRMACION;
      }
    break;

    case CONFIRMACION:
      if (lectura_BTN2 == HIGH && millis - millisAnt >= 15)
      {
        antirrebote_2 = ESPERA;
      }
      else if (lectura_BTN2 == LOW && millis - millisAnt >= 15)
      {
        antirrebote_2 = LIBERACION;
      }
    break;

    case LIBERACION:
      if (lectura_BTN2 == HIGH)
      {
        flag_BTN2 = true;
        antirrebote_2 = ESPERA;
      }
    break;
  }
}

void LecturaCNY() {
  for (int i = 0; i < 10; i++) 
  {
    lectura_cny_izq = analogRead(CNY_IZQ);
    suma_cny_izq = suma_cny_izq + lectura_cny_izq;
  }

  for (int i = 0; i < 10; i++) {
    lectura_cny_der = analogRead(CNY_DER);
    suma_cny_der = suma_cny_der + lectura_cny_der;
  }

  cny_izquierdo = suma_cny_izq / 10;
  cny_derecho = suma_cny_der / 10;

  suma_cny_izq = 0;
  suma_cny_der = 0;
}

void DetectarLinea() 
{
  if (cny_izquierdo < izq_promedio) {
    // Serial.println("Blanco");
    flag_cny_izq = true;
  } else {
    // Serial.println("Negro");
    flag_cny_izq = false;
  }

  if (cny_derecho < der_promedio) {
    flag_cny_der = true;
  } else {
    flag_cny_der = false;
  }

  if (cny_izquierdo < izq_promedio && cny_derecho < der_promedio) {
    flag_cny_both = true;
  } else {
    flag_cny_both = false;
  }
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
  Serial.print(distancia_ult_izq);
  Serial.print('\t');
  Serial.print(distancia_ult_med);
  Serial.print('\t');
  Serial.print(distancia_ult_der);
  Serial.println();
  
  if (distancia_ult_med < 60 && distancia_ult_med != 0) {
    // Serial.println("Hay algo");
    flag_ult_med = true;
  } else {
    // Serial.println("No hay moros en la costa");
    flag_ult_med = false;
  }

  if (distancia_ult_der < 60 && distancia_ult_der != 0) {
    flag_ult_der = true;
  } else {
    flag_ult_der = false;
  }

  if (distancia_ult_izq < 60 && distancia_ult_izq != 0) {
    flag_ult_izq = true;
  } else 
  {
    flag_ult_izq = false;
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