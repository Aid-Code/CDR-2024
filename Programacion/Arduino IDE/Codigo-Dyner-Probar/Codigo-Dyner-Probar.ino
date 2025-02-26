// CHIKEN LITTLE - DYNER - AIDEN - CHERNIAK - CDR '24
#include "motors.h"
#include "ultrasonicos.h"
#include "cny.h"
#include "botones.h"


void setup() {
  setupMotores();
  setupUltrasonicos();
  setupCny();
  setupBotones();
}

void loop() {
  seleccionarEstrategia();
  iniciarRobot();
  uint8_t lecturaCny = linea();
  uint8_t lecturaUltrasonico = presencia();
}
