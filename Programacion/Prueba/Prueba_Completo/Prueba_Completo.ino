// Sensores
#define CNY_IZQ A1
#define CNY_DER A2
#define ECHO_DER 7
#define TRIG_DER 8
#define ECHO_IZQ 10
#define TRIG_IZQ 9
#define ECHO_MED 11
#define TRIG_MED 12

// Botones y Leds
#define BTN_1 A6
#define BTN_2 A7
#define LED_1 A4
#define LED_2 A3
#define LED_3 13
#define LED_4 A0

// Motor Izquierdo
#define M1_B A5
#define M1_A 2
#define PWM_A 5

// Motor Derecho
#define M2_B 4
#define M2_A 6
#define PWM_B 3

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

// CNY

uint8_t lectura_cny_der = 0;
uint8_t lectura_cny_izq = 0;

uint8_t izquierdo;
uint8_t izq_blanco = 30;
uint8_t izq_negro = 1005;
uint8_t izq_promedio = (izq_blanco + izq_negro) /2;

uint8_t derecho;
uint8_t der_blanco = 24;
uint8_t der_negro = 990;
uint8_t der_promedio = (der_blanco + der_negro) /2;

bool flag_cny_der = false;
bool flag_cny_izq = false;
bool flag_cny_both = false;

void setup() 
{
  Serial.begin(9600);

  //Motores
  pinMode(PWM_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);
  pinMode(M1_A, OUTPUT);
  pinMode(M2_A, OUTPUT);
  pinMode(M1_B, OUTPUT);
  pinMode(M2_B, OUTPUT);

  //Sensores
  pinMode(TRIG_DER, OUTPUT);
  pinMode(ECHO_DER, INPUT);
  pinMode(TRIG_MED, OUTPUT);
  pinMode(ECHO_MED, INPUT);
  pinMode(TRIG_IZQ, OUTPUT);
  pinMode(ECHO_IZQ, INPUT);

  pinMode(CNY_IZQ, INPUT);
  pinMode(CNY_DER, INPUT);

  analogWrite(PWM_A, 240);
  analogWrite(PWM_B, 240);
}

void loop() 
{
  ExistenciaUltrasonicos();
  LecturaCNY();

  Adelante();

  if (flag_cny_both)
  {
    Atras();
    delay(500);

    Izquierda();
    delay(700);
  }
  else if (flag_cny_izq && !flag_cny_der)
  {
    Atras();
    delay(300);

    Derecha();
    delay(500);
  }
  else if (flag_cny_der && !flag_cny_izq)
  {
    Atras();
    delay(300);

    Izquierda();
    delay(500);
  }

  if (flag_ult_med)
  {
    Adelante();
  }
  else if (flag_ult_der)
  {
    Derecha();
  }
  else if (flag_ult_izq)
  {
    Izquierda();
  }
}

void LecturaCNY()
{
  lectura_cny_der = analogRead(CNY_DER);
  lectura_cny_izq = analogRead(CNY_IZQ);

  if (lectura_cny_der < der_promedio && lectura_cny_izq > izq_promedio)
  {
    flag_cny_der = true;
    flag_cny_izq = false;
    flag_cny_both = false;
  }
  else if (lectura_cny_izq < izq_promedio && lectura_cny_der > der_promedio)
  {
    flag_cny_izq = true;
    flag_cny_der = false;
    flag_cny_both = false;
  }
  else if (lectura_cny_der < der_promedio && lectura_cny_izq < izq_promedio)
  {
    flag_cny_both = true;
  }
}

void ExistenciaUltrasonicos()
{
  digitalWrite(TRIG_MED, HIGH);
  delay(10);
  digitalWrite(TRIG_MED, LOW);
  
  tiempo_ult_med = pulseIn(ECHO_MED, HIGH);
  
  distancia_ult_med = tiempo_ult_med / 59;

  digitalWrite(TRIG_DER, HIGH);
  delay(10);
  digitalWrite(TRIG_DER, LOW);
  
  tiempo_ult_der = pulseIn(ECHO_DER, HIGH);
  
  distancia_ult_der = tiempo_ult_der / 59;

  digitalWrite(TRIG_IZQ, HIGH);
  delay(10);
  digitalWrite(TRIG_IZQ, LOW);
  
  tiempo_ult_izq = pulseIn(ECHO_IZQ, HIGH);
  
  distancia_ult_izq = tiempo_ult_izq / 59;

  if(distancia_ult_med < 20)
  {
    //Serial.println("Hay algo");
    flag_ult_med = true;
  }
  else if(distancia_ult_med > 20)
  {
    //Serial.println("No hay moros en la costa");
    flag_ult_med = false;
  }

  if(distancia_ult_der < 20)
  {
    flag_ult_der = true;
  }
  else if(distancia_ult_der > 20)
  {
    flag_ult_der = false;
  }

  if(distancia_ult_izq < 20)
  {
    flag_ult_izq = true;
  }
  else if(distancia_ult_izq > 20)
  {
    flag_ult_izq = false;
  }
}

void Adelante()
{
  digitalWrite(M1_B, HIGH);
  digitalWrite(M1_A, LOW);
  digitalWrite(M2_B, HIGH);
  digitalWrite(M2_A, LOW);
}

void Atras()
{
  digitalWrite(M1_B, LOW);
  digitalWrite(M1_A, HIGH);
  digitalWrite(M2_B, LOW);
  digitalWrite(M2_A, HIGH);
}

void Derecha()
{
  digitalWrite(M1_B, LOW);
  digitalWrite(M1_A, HIGH);
  digitalWrite(M2_B, HIGH);
  digitalWrite(M2_A, LOW);
}

void Izquierda()
{
  digitalWrite(M1_B, HIGH);
  digitalWrite(M1_A, LOW);
  digitalWrite(M2_B, LOW);
  digitalWrite(M2_A, HIGH);
}