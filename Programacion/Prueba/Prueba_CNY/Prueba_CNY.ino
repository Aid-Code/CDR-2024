#define CNY_IZQ A6
#define CNY_DER A7

int izquierdo;
int izqBlanco = 30;
int izqNegro = 1005;
int izqPromedio = (izqBlanco + izqNegro) /2;

int derecho;
int derBlanco = 24;
int derNegro = 990;
int derPromedio = (derBlanco + derNegro) /2;

void setup() 
{
  Serial.begin(9600);

  pinMode(CNY_IZQ, INPUT);
  pinMode(CNY_DER, INPUT);
}

void loop() 
{
  izquierdo = analogRead(CNY_IZQ);
  derecho = analogRead(CNY_DER);

  Serial.println(izqPromedio);
}