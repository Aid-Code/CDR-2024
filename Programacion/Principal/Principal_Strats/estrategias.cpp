#include "estrategias.h"
#include "motors.h"
#include "ultrasonicos.h"
#include "botones.h"

void runStrat(uint8_t strat) 
{
  strat = contadorBtn(BTN_1);

  switch (strat) {
    case 0:
      break;
    case 1:
      crespin();
      break;
    case 2:
      pasitos();
      break;
    case 3:
      radar();
      break;
    case 4:
      bartolito();
      break;
    case 5:
      torero();
      break;
    default:
      crespin();
      break;
  }
}

void crespin() 
{
  uint8_t sensores = presencia();
  if (SENSOR_CEN >= 1) 
  {
    adelante(255, 255);
  } 
  else if (SENSOR_DER >= 1)
  {
    if ((sensores >> 1) == 1) 
    { //comprueba la distancia??
      derecha(200,200,SOBRE_PROPIO_EJE); //falta pwm y tipo
    }
  } 
  else if (SENSOR_IZQ >= 1) 
  {
  }
}

void pasitos()
{
  millis();
  uint16_t prev_millis = 0;
  uint8_t sensores = presencia();

  if (SENSOR_CEN < 1)
  {
    adelante(200,200);
    prev_millis = millis();

    if (millis() - prev_millis >= 10)
    {
      parado(0,0);
      prev_millis = millis();
    }
  }
  else if (SENSOR_CEN >= 1)
  {
    adelante(255,255);
  }
  else if (SENSOR_IZQ >= 1)
  {
    //falta comprobar distancia
    izquierda(200,200,SOBRE_PROPIO_EJE); //falta pwm y tipo de giro
  }
  else if (SENSOR_DER >= 1)
  {
    //falta comprobar distancia
    derecha(200,200,SOBRE_PROPIO_EJE); //falta pwm y tipo de giro
  }
}

void radar()
{
  uint8_t sensores = presencia();

  if (SENSOR_DER >= 1)
  {
    if ((sensores >> 1) == 3)
    {
      derecha(100,100,SOBRE_PROPIO_EJE);
    }
    else if ((sensores >> 1) == 2)
    {
      derecha(150,150,SOBRE_PROPIO_EJE);
    }
    else if ((sensores >> 1) == 1)
    {
      derecha(200,200,SOBRE_PROPIO_EJE);
    }
  }
  else if (SENSOR_IZQ >= 1)
  {
    if ((sensores >> 1) == 3)
    {
      izquierda(100,100,SOBRE_PROPIO_EJE);
    }
    else if ((sensores >> 1) == 2)
    {
      izquierda(150,150,SOBRE_PROPIO_EJE);
    }
    else if ((sensores >> 1) == 1)
    {
      izquierda(200,200,SOBRE_PROPIO_EJE);
    }
  }
  else if (SENSOR_CEN >= 1)
  {
    if ((sensores >> 1) == 1)
    {
      adelante(255,255);
    }
  }
}

void bartolito()
{
  uint8_t sensores = presencia();

  if (SENSOR_CEN < 1)
  {
    derecha(200,200,SOBRE_PROPIO_EJE);
  }
  else if (SENSOR_CEN >= 1)
  {
    adelante(255,255);
  }
}

void torero()
{
  uint8_t sensores = presencia();

  if (SENSOR_DER >= 1)
  {
    if ((sensores >> 1) == 3)
    {
      derecha(150,80,GIRO_ABIERTO);
    }
    else if ((sensores >> 1) == 2)
    {
      derecha(200,130,GIRO_ABIERTO);
    }
    else if ((sensores >> 1) == 1)
    {
      derecha(255,255,SOBRE_PROPIO_EJE);
    }
  }
  else if (SENSOR_IZQ >= 1)
  {
    if ((sensores >> 1) == 3)
    {
      izquierda(150,80,GIRO_ABIERTO);
    }
    else if ((sensores >> 1) == 2)
    {
      izquierda(200,130,GIRO_ABIERTO);
    }
    else if ((sensores >> 1) == 1)
    {
      izquierda(255,255,SOBRE_PROPIO_EJE);
    }
  }
  else if (SENSOR_CEN >= 1)
  {
    adelante(255,255);
  }
}