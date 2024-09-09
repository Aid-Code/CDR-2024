#include "motors.h"
#include "ultrasonicos.h"
#include "cny.h"
#include "botones.h"


void setup() {
  setupMotores();
  setupUltrasonicos();
  setupCny();
  setupBotonesYLeds();
}


void loop() {

}
