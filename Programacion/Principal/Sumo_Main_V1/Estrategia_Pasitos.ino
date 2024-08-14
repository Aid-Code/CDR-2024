// Estrategia Pasitos

int estado_pasitos;

enum estados
{
  INIT,
  BUSCO,
  ME_CAIGO,
  ENEMIGO
}

void MaquinaPasitos()
{
  switch(estado_pasitos)
  {
    case INIT:
      estado_pasitos = BUSCO;
    break;

    case BUSCO:
      if (flag_cny_izq || flag_cny_der)
      {
        estado_pasitos = ME_CAIGO;
      }
      else if (!flag_ult_med && !flag_ult_der && !flag_ult_izq)
      {
        Adelante();
        delay(500);

        Izquierda();
        delay(250);
      }
      else if (flag_ult_med)
      {
        estado_pasitos = ENEMIGO_MED;
      }
      else if (flag_ult_der)
      {
        estado_pasitos = ENEMIGO_DER;
      }
      else if (flag_ult_izq)
      {
        estado_pasitos = ENEMIGO_IZQ;
      }
    break;

    case ME_CAIGO:
      Atras();

      if(flag_cny_izq)
      {
        Derecha();
        delay(200);
        
        estado_pasitos = BUSCO;
      }
      else if (flag_cny_der)
      {
        Izquierda();
        delay(200);

        estado_pasitos = BUSCO;
      }
    break;

    case ENEMIGO_MED:
      analogWrite(PWM_A, 225); //Motor Izquierdo
      analogWrite(PWM_B, 200); //Motor Derecho

      Adelante();
    break;
  }
}