
#define TRIG_1 0b00000100
#define TRIG_2 0b01000000
#define TRIG_3 0b00100000
#define TRIG_4 0b00001000
#define TRIG_5 0b00010000

#define TRIG_L 0b00000000

#define ECHO_1 8
#define ECHO_2 9 // Izquierda
#define ECHO_3 10 // Medio
#define ECHO_4 A1 // Derecha
#define ECHO_5 A2

#define DATA 11     
#define LATCH 12    
#define CLOCK 13

#define LED_1 0b00000001
#define LED_2 0b10000000
#define LED_3 0b00000010

enum ESTADOS
{
  INIT,
  SETEAR,
  CONFIRM_DER,
  CONFIRM_IZQ
}

enum DIRECCIONES
{
  ADELANTE,
  DERECHA,
  IZQUIERDA
}

uint8_t state = INIT;
uint8_t direccion = ADELANTE;

long actual_millis = 0;
long ant_millis = 0; 

long tiempo_ult_der = 0;
long tiempo_ult_izq = 0;

long distancia_ult_der = 0;
long distancia_ult_izq = 0;

bool flag_ult_der = false;
bool flag_ult_izq = false;

void LecturaUltrasonicos(void);
void SetearDireccion(void);

void setup()
{
  Serial.begin(9600);
  
  pinMode(ECHO_1, INPUT);
  pinMode(ECHO_2, INPUT);
  pinMode(ECHO_3, INPUT);
  pinMode(ECHO_4, INPUT);
  pinMode(ECHO_5, INPUT);

  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
}

void loop()
{
  actual_millis = millis();

  LecturaUltrasonicos();
  ExistenciaUltrasonicos();
  SetearDireccion();
}

void SetearDireccion()
{
  switch (state)
  {
    case INIT:
      state = SETEAR;
    break;

    case SETEAR:
      
      if (flag_ult_der)
      {
        ant_millis = actual_millis;
        state = CONFIRM_DER;
      }
      else if (flag_ult_izq)
      {
        ant_millis = actual_millis;
        state = CONFIRM_IZQ;
      }
    break;

    case CONFIRM_DER:

      if (flag_ult_der && (actual_millis - ant_millis) >= 3000)
      {
        direccion = DERECHA;
      }
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

void ExistenciaUltrasonicos()
{
  if (distancia_ult_der < 10 && distancia_ult_der != 0) {
    flag_ult_der = true;
  } else {
    flag_ult_der = false;
  }

  if (distancia_ult_izq < 10 && distancia_ult_izq != 0) {
    flag_ult_izq = true;
  } else 
  {
    flag_ult_izq = false;
  }
}