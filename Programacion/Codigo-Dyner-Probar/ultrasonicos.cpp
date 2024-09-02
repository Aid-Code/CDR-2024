// CHIKEN LITTLE - DYNER - AIDEN - CHERNIAK - CDR '24 
#include "ultrasonicos.h"
#include "motors.h"

uint8_t* pines_ultrasonico_der = (ECHO_DER, TRIG_DER);
uint8_t* pines_ultrasonico_cen = (ECHO_MED, TRIG_MED);
uint8_t* pines_ultrasonico_izq = (ECHO_IZQ, TRIG_IZQ);

uint32_t distanciaDer;
uint32_t distanciaIzq;
uint32_t distanciaCen;

void setupUltrasonicos() { //Falta setear los otros dos ultrasonicos si es que los vamos a usar, sino los agregamos despues
  pinMode(ECHO_DER, INPUT);
  pinMode(TRIG_DER, OUTPUT);

  pinMode(ECHO_IZQ, INPUT);
  pinMode(TRIG_IZQ, OUTPUT);

  pinMode(ECHO_MED, INPUT);
  pinMode(TRIG_MED, OUTPUT);
}

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
  
  // Acción para el sensor derecho
  if (distanciaDer > 0 && distanciaDer <= 10) {
    derecha(PWM_ADELANTE, PWM_ADELANTE, SOBRE_PROPIO_EJE); //Me hace mal la redaccion pero parece estar bien jajsdjajs
  } else if (distanciaDer > 11 && distanciaDer <= 20) {
    derecha(PWM_ADELANTE, PWM_ADELANTE, CON_UNA_RUEDA);
  } else if (distanciaDer > 21 && distanciaDer <= 30) {
    derecha(PWM_ADELANTE, PWM_ADELANTE, GIRO_ABIERTO);
  }

  // Acción para el sensor izquierdo
  if (distanciaIzq > 0 && distanciaIzq <= 10) {
    izquierda(PWM_ADELANTE, PWM_ADELANTE, SOBRE_PROPIO_EJE);
  } else if (distanciaIzq > 11 && distanciaIzq <= 20) {
    izquierda(PWM_ADELANTE, PWM_ADELANTE, CON_UNA_RUEDA);
  } else if (distanciaIzq > 21 && distanciaIzq <= 30) {
    izquierda(PWM_ADELANTE, PWM_ADELANTE, GIRO_ABIERTO);
  }

  return (distanciaDer > 0) * 1 + (distanciaCen > 0) * 2 + (distanciaIzq > 0) * 4;
}
