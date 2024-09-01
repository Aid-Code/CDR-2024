// CHIKEN LITTLE - DYNER - AIDEN - CHERNIAK - CDR '24 
#include "motors.h"
#include "ultrasonicos.h"
#include "cny.h"
#include "botones.h"

/*cambiar los pines de:
-Botones
-Leds
-cny
-ultrasonicos
PREGUNTAR A AGUS CUALES SON LOS PINES QUE PONEMOS EN EL CODIGO 

*/
void setup() {
  setupMotores();
  setupUltrasonicos();
  setupCny();
  setupBotonesYLeds();
}

void loop() {
  seleccionarEstrategia();
  iniciarRobot();
  uint8_t lecturaCny = linea();
  uint8_t lecturaUltrasonico = presencia();
}
