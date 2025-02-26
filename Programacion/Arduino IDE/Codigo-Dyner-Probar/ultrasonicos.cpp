// CHIKEN LITTLE - DYNER - AIDEN - CHERNIAK - CDR '24 
#include "ultrasonicos.h"
#include "motors.h"

uint8_t* pines_ultrasonico_der = (ECHO_DER, TRIG_DER);
uint8_t* pines_ultrasonico_cen = (ECHO_MED, TRIG_MED);
uint8_t* pines_ultrasonico_izq = (ECHO_IZQ, TRIG_IZQ);
uint8_t* pines_ultrasonico_cen_izq = (ECHO_MED_IZQ, TRIG_MED_IZQ);
uint8_t* pines_ultrasonico_cen_der = (ECHO_MED_DER, TRIG_MED_DER);

uint32_t distanciaDer;
uint32_t distanciaIzq;
uint32_t distanciaCen;
unit32_t distanciaCenDer;
unit32_t distanciaCenIzq;


void setupUltrasonicos() { 
  pinMode(ECHO_DER, INPUT);
  pinMode(TRIG_DER, OUTPUT);

  pinMode(ECHO_IZQ, INPUT);
  pinMode(TRIG_IZQ, OUTPUT);

  pinMode(ECHO_MED, INPUT);
  pinMode(TRIG_MED, OUTPUT);

  pinMode(ECHO_MED_DER, INPUT);
  pinMode(TRIG_MED_DER, OUTPUT);

  pinMode(ECHO_MED_IZQ, INPUT);
  pinMode(TRIG_MED_IZQ, OUTPUT);
 
}

uint8_t lecturaUltrasonico(uint8_t* pines) {
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
  uint8_t lecturaDer = lecturaUltrasonico(pines_ultrasonico_der);
  uint8_t lecturaCen = lecturaUltrasonico(pines_ultrasonico_cen);
  uint8_t lecturaIzq = lecturaUltrasonico(pines_ultrasonico_izq);
  
  return (lecturaDer) * 1 + (lecturaCen) * 4 + (lecturaIzq) * 8;
}
