// CHIKEN LITTLE - DYNER - AIDEN - CHERNIAK - CDR '24 
#include "motors.h"
#include "ultrasonicos.h"
#include "cny.h"
#include "botones.h"

/*cambiar los pines de:
-Botones
-Leds  orden de los leds en la placa es: LED 1, LED 4, LED 3, LED 2
-ultrasonicos
PREGUNTAR A AGUS CUALES SON LOS PINES QUE PONEMOS EN EL CODIGO (del shift register)

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
  uint8_t lecturaUltrasonico = presencia(); //Entiendo de alguna forma que esto llama a leer los ultrasonicos, pero no entiendo como
                                            // Mentira ya entendí
}
