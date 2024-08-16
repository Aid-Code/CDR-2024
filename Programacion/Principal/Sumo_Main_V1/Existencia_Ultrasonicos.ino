// Existencia Ultrasonicos

void ExistenciaUltrasonicos()
{
  if(distancia_ult_med < 10)
  {
    //Serial.println("Hay algo");
    flag_ult_med = true;
  }
  else if(distancia_ult_med > 10)
  {
    //Serial.println("No hay moros en la costa");
    flag_ult_med = false;
  }

  if(distancia_ult_der < 15)
  {
    flag_ult_der = true;
  }
  else if(distancia_ult_der > 15)
  {
    flag_ult_der = false;
  }

  if(distancia_ult_izq < 15)
  {
    flag_ult_izq = true;
  }
  else if(distancia_ult_izq > 15)
  {
    flag_ult_izq = false;
  }
}