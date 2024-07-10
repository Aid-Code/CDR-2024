// Código Lectura

long tiempo_ult_der = 0;
long tiempo_ult_med = 0;
long tiempo_ult_izq = 0;

long distancia_ult_der = 0;
long distancia_ult_med = 0;
long distancia_ult_izq = 0;

bool flagUltDer = false;
bool flagUltMed = false;
bool flagUltIzq = false;

int estado_ults;

enum estados_ultrasonicos
{
  ADELANTE,
  DERECHA,
  IZQUIERDA
}

/*void MaquinaUltrasonicos()
{
  switch(estado)
  {
    case 
  }
}*/



void ExistenciaUltMed()
{
  digitalWrite(TRIG_MED, HIGH);
  delay(10);
  digitalWrite(TRIG_MED, LOW);
  
  tiempo_ult_med = pulseIn(ECHO_MED, HIGH);
  
  distancia_ult_med = tiempo_ult_med / 59;

  if(distancia_ult_med < 20)
  {
    //Serial.println("Hay algo");
    flagUltMed = true;
  }
  else if(distancia_ult_med > 20)
  {
    //Serial.println("No hay moros en la costa");
    flagUltMed = false;
  }
}

void ExistenciaUltDer()
{
  digitalWrite(TRIG_DER, HIGH);
  delay(10);
  digitalWrite(TRIG_DER, LOW);
  
  tiempo_ult_der = pulseIn(ECHO_DER, HIGH);
  
  distancia_ult_der = tiempo_ult_der / 59;

  if(distancia_ult_der < 20)
  {
    flagUltDer = true;
  }
  else if(distancia_ult_der > 20)
  {
    flagUltDer = false;
  }
}

void ExistenciaUltIzq()
{
  digitalWrite(TRIG_IZQ, HIGH);
  delay(10);
  digitalWrite(TRIG_IZQ, LOW);
  
  tiempo_ult_izq = pulseIn(ECHO_IZQ, HIGH);
  
  distancia_ult_izq = tiempo_ult_izq / 59;

  if(distancia_ult_izq < 20)
  {
    flagUltIzq = true;
  }
  else if(distancia_ult_izq > 20)
  {
    flagUltIzq = false;
  }
}