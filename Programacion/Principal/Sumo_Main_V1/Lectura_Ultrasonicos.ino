// Lectura Ultrasonicos

long tiempo_ult_der = 0;
long tiempo_ult_med = 0;
long tiempo_ult_izq = 0;

long distancia_ult_der = 0;
long distancia_ult_med = 0;
long distancia_ult_izq = 0;

bool flag_ult_der = false;
bool flag_ult_med = false;
bool flag_ult_izq = false;

void LecturaUltrasonicos()
{
  digitalWrite(TRIG_MED, HIGH);
  delay(10);
  digitalWrite(TRIG_MED, LOW);
  
  tiempo_ult_med = pulseIn(ECHO_MED, HIGH, 10000);
  
  distancia_ult_med = tiempo_ult_med / 59;

  digitalWrite(TRIG_DER, HIGH);
  delay(10);
  digitalWrite(TRIG_DER, LOW);
  
  tiempo_ult_der = pulseIn(ECHO_DER, HIGH, 10000);
  
  distancia_ult_der = tiempo_ult_der / 59;

  digitalWrite(TRIG_IZQ, HIGH);
  delay(10);
  digitalWrite(TRIG_IZQ, LOW);
  
  tiempo_ult_izq = pulseIn(ECHO_IZQ, HIGH, 10000);
  
  distancia_ult_izq = tiempo_ult_izq / 59;
}