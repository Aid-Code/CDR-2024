// Sumo Main V1

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

long tiempo_ult_der = 0;
long tiempo_ult_med = 0;
long tiempo_ult_izq = 0;

long distancia_ult_der = 0;
long distancia_ult_med = 0;
long distancia_ult_izq = 0;

uint8_t lectura_cny_der = 0;
uint8_t lectura_cny_med = 0;
uint8_t lectura_cny_izq = 0;

uint8_t medio;
uint8_t medBlanco = 0;
uint8_t medNegro = 0;
uint8_t medPromedio = (medBlanco + medNegro) /2;

uint8_t izquierdo;
uint8_t izqBlanco = 30;
uint8_t izqNegro = 1005;
uint8_t izqPromedio = (izqBlanco + izqNegro) /2;

uint8_t derecho;
uint8_t derBlanco = 24;
uint8_t derNegro = 990;
uint8_t derPromedio = (derBlanco + derNegro) /2;

bool flagUltDer = false;
bool flagUltMed = false;
bool flagUltIzq = false;

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
}

void loop() 
{
  Existencia();
  if (flagUltMed == true)
  {
    Adelante();
  }
}

void Existencia()
{
  digitalWrite(TRIG_MED, HIGH);
  delay(10);
  digitalWrite(TRIG_MED, LOW);
  
  tiempo_ult_med = pulseIn(ECHO_MED, HIGH);
  
  distancia_ult_med = tiempo_ult_med / 59;

  if(distancia_ult_med < 20)
  {
    Serial.println("Hay algo");
    flagUltMed = true;
  }
  else if(distancia_ult_med > 20)
  {
    Serial.println("No hay moros en la costa");
    flagUltMed = false;
  }
}

void Distancia()
{
  digitalWrite(TRIG_MED, HIGH);
  delay(10);
  digitalWrite(TRIG_MED, LOW);
  
  tiempo_ult_med = pulseIn(ECHO_MED, HIGH);
  
  distancia_ult_med = tiempo_ult_med / 59;
  
  Serial.println(distancia_ult_med);
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