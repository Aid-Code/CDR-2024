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


#define PWM_CHILL 50
#define PWM_FULL 250


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


// CNY Izquierdo


uint32_t lectura_cny_izq = 0;
uint32_t cny_izquierdo = 0;
uint32_t suma_cny_izq = 0;


uint32_t izq_blanco = 185;
uint32_t izq_negro = 825;


uint32_t izq_promedio = (izq_blanco + izq_negro) / 2;


//CNY Derecho


uint32_t lectura_cny_der = 0;
uint32_t cny_derecho = 0;
uint32_t suma_cny_der = 0;


uint32_t der_blanco = 60;
uint32_t der_negro = 715;


uint32_t der_promedio = (der_blanco + der_negro) / 2;


bool flag_cny_der = false;
bool flag_cny_izq = false;
bool flag_cny_both = false;


int auxiliar = 0;
int milis = 0;
int milisAnt = 0;


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


  analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
  analogWrite(PWM_B, PWM_CHILL);  //Motor Derecho
}


void loop()
{
  milis = millis();


  if (digitalRead(BTN_1) == LOW)
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
      analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
      analogWrite(PWM_B, PWM_FULL);
      Atras();
      delay(500);
      Izquierda();
      delay(200);
      analogWrite(PWM_A, PWM_CHILL);
      analogWrite(PWM_B, PWM_CHILL);
      // Serial.println("Derecha");


    } else if (flag_cny_der) {
      // Serial.println("Atras");
      analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
      analogWrite(PWM_B, PWM_FULL);
      Atras();
      delay(500);
      Derecha();
      delay(150);
      analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
      analogWrite(PWM_B, PWM_CHILL);
      // Serial.println("Izquierda");
    } else {
      // Serial.println("Adelante");
      analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
      analogWrite(PWM_B, PWM_CHILL);
      Adelante();
    }


    if (flag_ult_med)
    {
      analogWrite(PWM_A, PWM_FULL);
      analogWrite(PWM_B, PWM_FULL);


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
      analogWrite(PWM_A, PWM_FULL);
      analogWrite(PWM_B, PWM_FULL);


      //Serial.println("Derecha");
      Derecha();
      /*digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLOCK, LSBFIRST, LED_1);
      digitalWrite(LATCH, HIGH);
      delay(10);
      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
      digitalWrite(LATCH, HIGH);
      digitalWrite(LED_4, LOW);*/


    } else if (flag_ult_izq)
    {
      analogWrite(PWM_A, PWM_FULL);
      analogWrite(PWM_B, PWM_FULL);


      //Serial.println("Izquierda");
      Izquierda();
      /*digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLOCK, LSBFIRST, LED_3);
      digitalWrite(LATCH, HIGH);
      delay(10);
      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
      digitalWrite(LATCH, HIGH);
      digitalWrite(LED_4, LOW);*/
    }
    else
    {
      analogWrite(PWM_A, PWM_CHILL);
      analogWrite(PWM_B, PWM_CHILL);
    }
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
 
  if (distancia_ult_med < 80 && distancia_ult_med != 0) {
    // Serial.println("Hay algo");
    flag_ult_med = true;
  } else {
    // Serial.println("No hay moros en la costa");
    flag_ult_med = false;
  }


  if (distancia_ult_der < 80 && distancia_ult_der != 0) {
    flag_ult_der = true;
  } else {
    flag_ult_der = false;
  }


  if (distancia_ult_izq < 80 && distancia_ult_izq != 0) {
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
