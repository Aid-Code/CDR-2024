// Sensores
#define CNY_IZQ A1
#define CNY_DER A0
#define ECHO_DER 12  //3
#define TRIG_DER 13  //3
#define ECHO_IZQ 11  //1
#define TRIG_IZQ 10  //1
#define ECHO_MED 9   //2
#define TRIG_MED 8   //

// Botones y Leds
#define BTN A4
/*#define BTN_1 A6
#define BTN_2 A7
#define LED_1 A4
#define LED_2 A3
#define LED_3 13
#define LED_4 A0*/

// Motor Izquierdo
#define M1_B 7
#define M1_A 4
#define PWM_A 6

// Motor Derecho
#define M2_B 2
#define M2_A 3
#define PWM_B 5

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

uint32_t izq_blanco = 28;
uint32_t izq_negro = 735;

uint32_t izq_promedio = (izq_blanco + izq_negro) / 2;

//CNY Derecho

uint32_t lectura_cny_der = 0;
uint32_t cny_derecho = 0;
uint32_t suma_cny_der = 0;

uint32_t der_blanco = 285;
uint32_t der_negro = 805;

uint32_t der_promedio = (der_blanco + der_negro) / 2;

bool flag_cny_der = false;
bool flag_cny_izq = false;
bool flag_cny_both = false;

void setup() {
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
  pinMode(ECHO_DER, INPUT_PULLUP);
  pinMode(TRIG_MED, OUTPUT);
  pinMode(ECHO_MED, INPUT_PULLUP);
  pinMode(TRIG_IZQ, OUTPUT);
  pinMode(ECHO_IZQ, INPUT_PULLUP);

  //Boton
  pinMode(BTN, INPUT_PULLUP);

  analogWrite(PWM_A, 200);  //Motor Izquierdo
  analogWrite(PWM_B, 185);  //Motor Derecho
}

void loop() {
  LecturaUltrasonicos();
  ExistenciaUlt();
  LecturaCNY();
  DetectarLinea();
  
  if (flag_cny_izq)
  {
    // Serial.println("Atras");
    Atras();
    delay (500);
    Izquierda();
     delay (450);
    // Serial.println("Derecha");
    
  } 
  else if (flag_cny_der)
  {
    // Serial.println("Atras");
    Atras();
     delay (500);
     Derecha();
     delay (450);
    // Serial.println("Izquierda");
  }
  else
  {
    // Serial.println("Adelante");
    Adelante();
  }

  if (flag_ult_med) {
    // Serial.println("Medio");
    Adelante();
    
  } else if (flag_ult_der) {
    // Serial.println("Derecha");
    Derecha();
    
  } else if (flag_ult_izq) {
    // Serial.println("Izquierda");
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
    // Serial.println("Blanco");
    flag_cny_izq = true;
  }
  else 
  {
    // Serial.println("Negro");
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

  if (cny_izquierdo < izq_promedio && cny_derecho < der_promedio)
  {
    flag_cny_both = true;
  }
  else
  {
    flag_cny_both = false;
  }
}

void LecturaUltrasonicos() {


  digitalWrite(TRIG_MED, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_MED, LOW);

  tiempo_ult_med = pulseIn(ECHO_MED, HIGH, 5000);

  distancia_ult_med = tiempo_ult_med / 59;

  digitalWrite(TRIG_DER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_DER, LOW);

  tiempo_ult_der = pulseIn(ECHO_DER, HIGH, 10000);

  distancia_ult_der = tiempo_ult_der / 59;

  digitalWrite(TRIG_IZQ, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_IZQ, LOW);

  tiempo_ult_izq = pulseIn(ECHO_IZQ, HIGH);

  distancia_ult_izq = tiempo_ult_izq / 59;
}

void ExistenciaUlt() {
  Serial.print(distancia_ult_der);
  Serial.print('\t');
  Serial.print(distancia_ult_med);
  Serial.print('\t');
  Serial.print(distancia_ult_izq);
  Serial.println();
  if (distancia_ult_med < 10 && distancia_ult_med != 0) {
    // Serial.println("Hay algo");
    flag_ult_med = true;
  } else {
    // Serial.println("No hay moros en la costa");
    flag_ult_med = false;
  }

  if (distancia_ult_der < 15 && distancia_ult_der != 0) {
    flag_ult_der = true;
  } else {
    flag_ult_der = false;
  }

  if (distancia_ult_izq < 15 && distancia_ult_izq != 0) {
    flag_ult_izq = true;
  } else {
    flag_ult_izq = false;
  }
}

void Adelante() {

  digitalWrite(M1_B, HIGH);
  digitalWrite(M2_B, LOW);
  digitalWrite(M1_A, LOW);
  digitalWrite(M2_A, HIGH);
}

void Atras() {
  digitalWrite(M1_B, LOW);
  digitalWrite(M2_B, HIGH);
  digitalWrite(M1_A, HIGH);
  digitalWrite(M2_A, LOW);
}

void Derecha() {
  digitalWrite(M1_B, LOW);
  digitalWrite(M2_B, HIGH);
  digitalWrite(M1_A, LOW);
  digitalWrite(M2_A, HIGH);
}

void Izquierda() {
  digitalWrite(M1_B, HIGH);
  digitalWrite(M2_B, LOW);
  digitalWrite(M1_A, HIGH);
  digitalWrite(M2_A, LOW);
}
