#define CNY_IZQ A6
#define CNY_DER A7

// CNY Izquierdo

uint32_t lectura_cny_izq = 0;
uint32_t cny_izquierdo = 0;
uint32_t suma_cny_izq = 0;

uint32_t izq_blanco = 28;
uint32_t izq_negro = 735;

uint32_t izq_promedio = (izq_blanco + izq_negro) /2;

//CNY Derecho

uint32_t lectura_cny_der = 0;
uint32_t cny_derecho = 0;
uint32_t suma_cny_der = 0;

uint32_t der_blanco = 285;
uint32_t der_negro = 805;

uint32_t der_promedio = (der_blanco + der_negro) /2;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  lectura_cny_izq = analogRead(CNY_IZQ);
  lectura_cny_der = analogRead(CNY_DER);

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

  Serial.println(cny_derecho);

  /*if (cny_izquierdo > izq_promedio)
  {
    Serial.println("Negro");
  }
  else if (cny_izquierdo < izq_promedio)
  {
    Serial.println("Blanco");
  }

  if (cny_derecho > der_promedio)
  {
    Serial.println("Negro");
  }
  else if (cny_derecho < der_promedio)
  {
    Serial.println("Blanco");
  }*/
}