
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

long tiempo;
long distancia;

void Existencia(void);
void Distancia(void);

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
  Existencia();
}

void Existencia()
{
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_2);
  digitalWrite(LATCH, HIGH);
  delay(10);
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
  digitalWrite(LATCH, HIGH);
  
  tiempo = pulseIn(ECHO_2, HIGH, 10000);
  
  distancia = tiempo / 59;

  Serial.println(distancia);

  /*if(distancia < 10)
  {
    //Serial.println("Hay algo");
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, LED_2);
    digitalWrite(LATCH, HIGH);
    delay(10);
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
    digitalWrite(LATCH, HIGH);
  }
  else if (distancia > 0)
  {
    //Serial.println("No hay moros en la costa");
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, LED_1);
    digitalWrite(LATCH, HIGH);
    delay(10);
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
    digitalWrite(LATCH, HIGH);
  }*/
}

void Distancia()
{
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_2);
  digitalWrite(LATCH, HIGH);
  delay(10); 
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
  digitalWrite(LATCH, HIGH);
  
  tiempo = pulseIn(ECHO_2, HIGH, 10000);
  
  distancia = tiempo / 59;
  
  Serial.println(distancia);
  
  /*
  digitalWrite(TRIG_IZQ, HIGH);
  delay(10);
  digitalWrite(TRIG_IZQ, LOW);
  
  tiempo = pulseIn(ECHO_IZQ, HIGH);
  
  distancia = tiempo / 59;
  
  Serial.println(distancia);
  */
}