#define CNY_IZQ A1
#define CNY_DER A2

int izquierdo;
int izqBlanco = 30;
int izqNegro = 810;
int izqPromedio = (izqBlanco + izqNegro) /2;

int derecho;
int derBlanco = 350;
int derNegro = 1000;
int derPromedio = (derBlanco + derNegro) /2;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  izquierdo = analogRead(CNY_IZQ);
  derecho = analogRead(CNY_DER);

  //Serial.println(izquierdo);

  if (izquierdo > izqPromedio)
  {
    Serial.println("Negro");
  }
  else if (izquierdo < izqPromedio)
  {
    Serial.println("Blanco");
  }

  /*if (derecho > derPromedio)
  {
    Serial.println("Negro");
  }
  else if (derecho < derPromedio)
  {
    Serial.println("Blanco");
  }*/
}