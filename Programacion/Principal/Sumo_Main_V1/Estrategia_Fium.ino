// Estrategia Fium

int estado_fium;

enum estados
{
  INIT,
  BUSCO,
  ME_CAIGO,
  ENEMIGO
}

void MaquinaFium()
{
  switch(estado_fium)
  {
    case INIT:
      estado_fium = BUSCO;
    break;

    case BUSCO:
      if (flag_cny_izq || flag_cny_der)
      {
        estado_fium = ME_CAIGO;
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
        estado_fium = ENEMIGO_MED;
      }
      else if (flag_ult_der)
      {
        estado_fium = ENEMIGO_DER;
      }
      else if (flag_ult_izq)
      {
        estado_fium = ENEMIGO_IZQ;
      }
    break;

    case ME_CAIGO:
      Atras();

      if(flag_cny_izq)
      {
        Derecha();
        delay(200);
        
        estado_fium = BUSCO;
      }
      else if (flag_cny_der)
      {
        Izquierda();
        delay(200);

        estado_fium = BUSCO;
      }
    break;

    case ENEMIGO_MED:
      analogWrite(PWM_A, 225); //Motor Izquierdo
      analogWrite(PWM_B, 200); //Motor Derecho

      Adelante();
    break;
  }
}