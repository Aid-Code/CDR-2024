#include "estrategias.h"
#include "motors.h"
#include "ultrasonicos.h"

void runStrat(uint8_t strat) {
  switch (strat) {
    case 0:
      crespin();
      break;
    case 1:
      pasitos();
      break;
    case 2:
      radar();
      break;
    case 3:
      bartolito();
      break;
    default:
      crespin();
      break;
  }
}

void crespin() {
  uint8_t sensores = presencia();
  if (SENSOR_CEN >= 1) {
    adelante(255, 255);
  } else if (SENSOR_DER >= 1) {
    if ((sensores >> 1) == 1) {
      derecha();
    }
    
  } else if (((sensores << 4) >> 6) >= 1) {

  }
}
