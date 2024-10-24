
#define TRIG_DER 7
#define ECHO_DER 8

long tiempo;
long distancia;

void Existencia(void);
void Distancia(void);

void setup()
{
  Serial.begin(9600);

  pinMode(TRIG_DER, OUTPUT);
  pinMode(ECHO_DER, INPUT);
}

void loop()
{
 Distancia();
}

void Existencia()
{
  
  digitalWrite(TRIG_DER, HIGH);
  delay(10);
  digitalWrite(TRIG_DER, LOW);
  
  tiempo = pulseIn(ECHO_DER, HIGH);
  
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
  digitalWrite(TRIG_DER, HIGH);
  delay(10);
  digitalWrite(TRIG_DER, LOW);
  
  tiempo = pulseIn(ECHO_DER, HIGH, 10000);
  
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