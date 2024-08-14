// Detectar Linea

void DetectarLinea()
{
  if (cny_izquierdo < izq_promedio)
  {
    //Serial.println("Blanco");
    flag_cny_izq = true;
  }
  else 
  {
    //Serial.println("Negro");
    flag_cny_izq = false;
  }

  if (cny_derecho < der_promedio)
  {
    flag_cny_der = true;
  }
  else 
  {
    flag_cny_der = false;
  }

  /*if (cny_izquierdo < izq_promedio && cny_derecho < der_promedio)
  {
    flag_cny_both = true;
  }
  else
  {
    flag_cny_both = false;
  }*/
}