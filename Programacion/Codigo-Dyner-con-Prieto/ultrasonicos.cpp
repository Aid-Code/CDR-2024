#include "ultrasonicos.h"

uint8_t* pines_ultrasonico_der = (ECHO_DER, TRIG_DER);
uint8_t* pines_ultrasonico_cen = (ECHO_MED, TRIG_MED);
uint8_t* pines_ultrasonico_izq = (ECHO_IZQ, TRIG_IZQ);

bool lecturaUltrasonico(uint8_t* pines) {
  digitalWrite(pines[1], HIGH);
  delayMicroseconds(10);
  digitalWrite(pines[1], LOW);

  uint32_t tiempo = pulseIn(pines[0], HIGH, 10000);

  uint32_t distancia = tiempo / 59;

  if (distancia < 10 && distancia != 0) {
    // Serial.println("Hay algo");
    return true;
  } else {
    // Serial.println("No hay moros en la costa");
    return false;
  }
}

uint8_t presencia() {
  bool lecturaDer = lecturaUltrasonico(pines_ultrasonico_der);
  bool lecturaCen = lecturaUltrasonico(pines_ultrasonico_cen);
  bool lecturaIzq = lecturaUltrasonico(pines_ultrasonico_izq);

  return lecturaDer * 1 + lecturaCen * 2 + lecturaIzq * 4;
}