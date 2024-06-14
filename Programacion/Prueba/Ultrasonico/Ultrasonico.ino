#define TRIG 12
#define ECHO 11

long tiempo;
long distancia;

void Existencia(void);
void Distancia(void);

void setup()
{
  Serial.begin(9600);
  
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop()
{
  Distancia();
}

void Existencia()
{
  digitalWrite(TRIG, HIGH);
  delay(10);
  digitalWrite(TRIG, LOW);
  
  tiempo = pulseIn(ECHO, HIGH);
  
  distancia = tiempo / 59;

  if(distancia < 20)
  {
    Serial.println("Hay algo");
  }
  else if(distancia > 20)
  {
    Serial.println("No hay moros en la costa");
  }
}

void Distancia()
{
  digitalWrite(TRIG, HIGH);
  delay(10);
  digitalWrite(TRIG, LOW);
  
  tiempo = pulseIn(ECHO, HIGH);
  
  distancia = tiempo / 59;
  
  Serial.println(distancia);
}
