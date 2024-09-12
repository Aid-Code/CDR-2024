
#define TRIG_1 0b00000100
#define TRIG_2 0b01000000
#define TRIG_3 0b00100000
#define TRIG_4 0b00001000
#define TRIG_5 0b00010000
#define TRIG_L 0b00000000

#define ECHO_1 2 // 8
#define ECHO_2 3 // 9
#define ECHO_5 A2

#define DATA 11     
#define LATCH 12    
#define CLOCK 13

long tiempo;
long distancia;

void Existencia(void);
void Distancia(void);

void setup()
{
  Serial.begin(9600);
  

  //pinMode(TRIG, OUTPUT);
  pinMode(ECHO_5, INPUT);
  pinMode(ECHO_1, INPUT);
  pinMode(ECHO_2, INPUT);

  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
}

void loop()
{
  Distancia();
}

void Existencia()
{
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_4);
  digitalWrite(LATCH, HIGH);
  delay(10);
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
  digitalWrite(LATCH, HIGH);
  
  tiempo = pulseIn(ECHO_2, HIGH);
  
  distancia = tiempo / 59;

  if(distancia < 10)
  {
    Serial.println("Hay algo");
  }
  else if (distancia > 10)
  {
    Serial.println("No hay moros en la costa");
  }


  /*
  digitalWrite(TRIG_IZQ, HIGH);
  delay(10);
  digitalWrite(TRIG_IZQ, LOW);
  
  tiempo = pulseIn(ECHO_IZQ, HIGH);
  
  distancia = tiempo / 59;

  if(distancia < 10)
  {
    Serial.println("Hay algo");
  }
  else if (distancia > 10)
  {
    Serial.println("No hay moros en la costa");
  }
  */
}

void Distancia()
{
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_5);
  digitalWrite(LATCH, HIGH);
  delay(10);
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
  digitalWrite(LATCH, HIGH);
  
  tiempo = pulseIn(ECHO_2, HIGH);
  
  distancia = tiempo / 59;
  
  Serial.println(distancia, DEC);
  
  /*
  digitalWrite(TRIG_IZQ, HIGH);
  delay(10);
  digitalWrite(TRIG_IZQ, LOW);
  
  tiempo = pulseIn(ECHO_IZQ, HIGH);
  
  distancia = tiempo / 59;
  
  Serial.println(distancia);
  */
}