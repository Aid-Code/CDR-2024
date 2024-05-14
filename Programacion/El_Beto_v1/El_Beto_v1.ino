//El Beto V1

//Sensores
#define CNY_IZQ A0
#define CNY_MED A1
#define CNY_DER A2
#define ECHO_DER 6
#define TRIG_DER 7
#define ECHO_IZQ 8
#define TRIG_IZQ 9
#define ECHO_MED 10
#define TRIG_MED 11

//Motores
#define M1_PWM 3
#define M2_PWM 5
#define M1_AD 12
#define M2_AD 13
#define M1_AT 2
#define M2_AT 4

int tiempoUltDer = 0;
int tiempoUltMed = 0;
int tiempoUltIzq = 0;

int distanciaUltDer = 0;
int distanciaUltMed = 0;
int distanciaUltIzq = 0;

int lecturaCnyDer = 0;
int lecturaCnyMed = 0;
int lecturaCnyIzq = 0;

int medio;
int medBlanco = 0;
int medNegro = 0;
int medPromedio = (medBlanco + medNegro) /2;

int izquierdo;
int izqBlanco = 30;
int izqNegro = 1005;
int izqPromedio = (izqBlanco + izqNegro) /2;

int derecho;
int derBlanco = 24;
int derNegro = 990;
int derPromedio = (derBlanco + derNegro) /2;

bool flagUltDer = false;
bool flagUltMed = false;
bool flagUltIzq = false;

void setup() 
{
  Serial.begin(9600);

  //Motores
  pinMode(M1_PWM, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
  pinMode(M1_AD, OUTPUT);
  pinMode(M2_AD, OUTPUT);
  pinMode(M1_AT, OUTPUT);
  pinMode(M2_AT, OUTPUT);

  //Sensores
  pinMode(TRIG_DER, OUTPUT);
  pinMode(ECHO_DER, INPUT);
  pinMode(TRIG_MED, OUTPUT);
  pinMode(ECHO_MED, INPUT);
  pinMode(TRIG_IZQ, OUTPUT);
  pinMode(ECHO_IZQ, INPUT);

  pinMode(CNY_IZQ, INPUT);
  pinMode(CNY_MED, INPUT);
  pinMode(CNY_DER, INPUT);
}

void loop() 
{
  Lectura_Ultrasonicos();

  lecturaCnyMed = analogRead(CNY_MED);
  lecturaCnyDer = analogRead(CNY_DER);
  lecturaCnyIzq = analogRead(CNY_IZQ);
}

void Lectura_Piso()
{
  if (lecturaCnyMed > medPromedio && lecturaCnyDer > derPromedio && lecturaCnyIzq > izqPromedio)
  {
    Atras();
    delay(500);

    Izquierda();
    delay(500);
  }

  if (lecturaCnyDer > derPromedio)
  {
    Atras();
    delay(500);

    Derecha();
    delay(300);

    Izquierda();
    delay(500);
  }
}

void Lectura_Ultrasonicos()
{
  //Ultrasonico del Medio

  digitalWrite(TRIG_MED, HIGH);
  delay(10);
  digitalWrite(TRIG_MED, LOW);

  tiempoUltMed = pulseIn(ECHO_MED, HIGH);

  distanciaUltMed = tiempoUltMed / 59;

  if (distanciaUltMed < 50)
  {
    flagUltMed = true;
  }
  else if (distanciaUltMed > 50)
  {
    flagUltMed = false;
  }

  //Ultrasonico Derecho

  digitalWrite(TRIG_DER, HIGH);
  delay(10);
  digitalWrite(TRIG_DER, LOW);

  tiempoUltDer = pulseIn(ECHO_DER, HIGH);

  distanciaUltDer = tiempoUltDer / 59;

  if (distanciaUltDer < 50)
  {
    flagUltDer = true;
  }
  else if (distanciaUltDer > 50)
  {
    flagUltDer = false;
  }

  //Ultrasonico Izquierdo

  digitalWrite(TRIG_IZQ, HIGH);
  delay(10);
  digitalWrite(TRIG_IZQ, LOW);

  tiempoUltIzq = pulseIn(ECHO_IZQ, HIGH);

  distanciaUltIzq = tiempoUltIzq / 59;

  if (distanciaUltIzq > 50)
  {
    flagUltIzq = true;
  }
  else if (distanciaUltIzq < 50)
  {
    flagUltIzq = false;
  }
}

void Adelante()
{
  digitalWrite(M1_PWM, HIGH);
  digitalWrite(M2_PWM, HIGH);

  digitalWrite(M1_AD, HIGH);
  digitalWrite(M1_AT, LOW);
  digitalWrite(M2_AD, HIGH);
  digitalWrite(M2_AT, LOW);
}

void Atras()
{
  digitalWrite(M1_PWM, HIGH);
  digitalWrite(M2_PWM, HIGH);

  digitalWrite(M1_AD, LOW);
  digitalWrite(M1_AT, HIGH);
  digitalWrite(M2_AD, LOW);
  digitalWrite(M2_AT, HIGH);
}

void Derecha()
{
  digitalWrite(M1_PWM, HIGH);
  digitalWrite(M2_PWM, HIGH);

  digitalWrite(M1_AD, LOW);
  digitalWrite(M1_AT, HIGH);
  digitalWrite(M2_AD, HIGH);
  digitalWrite(M2_AT, LOW);
}

void Izquierda()
{
  digitalWrite(M1_PWM, HIGH);
  digitalWrite(M2_PWM, HIGH);

  digitalWrite(M1_AD, HIGH);
  digitalWrite(M1_AT, LOW);
  digitalWrite(M2_AD, LOW);
  digitalWrite(M2_AT, HIGH);
}
