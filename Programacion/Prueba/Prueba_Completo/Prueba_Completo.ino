// Sensores
#define CNY_IZQ A1
#define CNY_DER A2
#define ECHO_DER 11
#define TRIG_DER 12
#define ECHO_IZQ 7
#define TRIG_IZQ 8
#define ECHO_MED 10
#define TRIG_MED 9

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

// CNY Izquierdo

uint32_t lectura_cny_izq = 0;
uint32_t cny_izquierdo = 0;
uint32_t suma_cny_izq = 0;

uint32_t izq_blanco = 25;
uint32_t izq_negro = 650;

uint32_t izq_promedio = (izq_blanco + izq_negro) /2;

//CNY Derecho

uint32_t lectura_cny_der = 0;
uint32_t cny_derecho = 0;
uint32_t suma_cny_der = 0;

uint32_t der_blanco = 120;
uint32_t der_negro = 820;

uint32_t der_promedio = (der_blanco + der_negro) /2;

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

  analogWrite(PWM_A, 75); //Motor Izquierdo
  analogWrite(PWM_B, 50); //Motor Derecho
}

void loop() 
{
  LecturaUltrasonicos();
  ExistenciaUlt();
  LecturaCNY();
  DetectarLinea();

  /*if (flag_cny_izq)
  {
    Serial.println("Atras");
    Atras();
    delay(1000);
    Derecha();
    Serial.println("Derecha");
    delay(500);
  } 
  else if (flag_cny_der)
  {
    Serial.println("Atras");
    Atras();
    delay(1000);
    Izquierda();
    Serial.println("Izquierda");
    delay(500);
  }
  else
  {
    Serial.println("Adelante");
    Adelante();
  }*/

  if (flag_ult_med)
  {
    Serial.println("Medio");
    Adelante();
  }
  else if (flag_ult_der)
  {
    Serial.println("Derecha");
    Derecha();
  }
  else if (flag_ult_izq)
  {
    Serial.println("Izquierda");
    Izquierda();
  }
}

void LecturaCNY()
{
  for (int i = 0; i <10; i++)
  {
    lectura_cny_izq = analogRead(CNY_IZQ);
    suma_cny_izq = suma_cny_izq + lectura_cny_izq;
  }

  for (int i = 0; i <10; i++)
  {
    lectura_cny_der = analogRead(CNY_DER);
    suma_cny_der = suma_cny_der + lectura_cny_der;
  }

  cny_izquierdo = suma_cny_izq /10;
  cny_derecho = suma_cny_der /10;

  suma_cny_izq = 0;
  suma_cny_der = 0;
}

void DetectarLinea()
{
  if (cny_izquierdo < izq_promedio)
  {
    //Serial.println("Blanco");
    flag_cny_izq = true;
  }
  else 
  {
    //Serial.println("Negro");
    flag_cny_izq = false;
  }

  if (cny_derecho < der_promedio)
  {
    flag_cny_der = true;
  }
  else 
  {
    flag_cny_der = false;
  }

  /*if (cny_izquierdo < izq_promedio && cny_derecho < der_promedio)
  {
    flag_cny_both = true;
  }
  else
  {
    flag_cny_both = false;
  }*/
}

void LecturaUltrasonicos()
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
}

void ExistenciaUlt()
{
  if(distancia_ult_med < 10)
  {
    //Serial.println("Hay algo");
    flag_ult_med = true;
  }
  else if(distancia_ult_med > 10)
  {
    //Serial.println("No hay moros en la costa");
    flag_ult_med = false;
  }

  if(distancia_ult_der < 30)
  {
    flag_ult_der = true;
  }
  else if(distancia_ult_der > 30)
  {
    flag_ult_der = false;
  }

  if(distancia_ult_izq < 30)
  {
    flag_ult_izq = true;
  }
  else if(distancia_ult_izq > 30)
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
  digitalWrite(M1_B, HIGH);
  digitalWrite(M1_A, LOW);
  digitalWrite(M2_B, LOW);
  digitalWrite(M2_A, HIGH);
}

void Izquierda()
{
  digitalWrite(M1_B, LOW);
  digitalWrite(M1_A, HIGH);
  digitalWrite(M2_B, HIGH);
  digitalWrite(M2_A, LOW);
}