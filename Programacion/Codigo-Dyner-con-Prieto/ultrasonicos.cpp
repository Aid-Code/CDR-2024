#include "ultrasonicos.h"
#include "motors.h"
#include "cny.h"

uint8_t pines_ultrasonico_der[2] = {ECHO_DER, TRIG_DER};
uint8_t pines_ultrasonico_cen[2] = {ECHO_MED, TRIG_MED};
uint8_t pines_ultrasonico_izq[2] = {ECHO_IZQ, TRIG_IZQ};

uint32_t lecturaUltrasonico(uint8_t* pines) {
  digitalWrite(pines[1], HIGH);
  delayMicroseconds(10);
  digitalWrite(pines[1], LOW);

  uint32_t tiempo = pulseIn(pines[0], HIGH, 10000);
  uint32_t distancia = tiempo / 59;

  return distancia;
}

void gestionarMotores(uint32_t distanciaDer, uint32_t distanciaCen, uint32_t distanciaIzq) {
  uint8_t deteccionCny = linea();  // Lee la detección del sensor CNY

  if (deteccionCny > 0) {  // Si se detecta una línea blanca
    atras(255, 255);       // Retrocede
    delay(300);
    if (deteccionCny & 1) {                       // CNY_DER detecta blanco
      izquierda(PWM_Der, PWM_Izq, GIRO_ABIERTO);  // Gira hacia la izquierda
    } else if (deteccionCny & 2) {                // CNY_IZQ detecta blanco
      derecha(PWM_Der, PWM_Izq, GIRO_ABIERTO);    // Gira hacia la derecha
    }
    delay(450);                  // Tiempo de giro
    adelante(PWM_Der, PWM_Izq);  // Avanza después del giro
    return;                      // Termina la función para evitar acciones adicionales
  }

  bool debeGirar = false;

  // Lógica para el sensor derecho
  if (distanciaDer < 10 && distanciaDer != 0) {
    while (lecturaUltrasonico(pines_ultrasonico_cen) > 10) {
      derecha(PWM_Der, PWM_Izq, SOBRE_PROPIO_EJE);
      delay(100);
    }
    debeGirar = true;
  } else if (distanciaDer >= 11 && distanciaDer <= 20) {
    derecha(PWM_Der, PWM_Izq, CON_UNA_RUEDA);
    debeGirar = true;
  } else if (distanciaDer >= 21 && distanciaDer <= 30) {
    adelante(PWM_Der, PWM_Izq);
    debeGirar = true;
  }

  // Lógica para el sensor izquierdo
  if (distanciaIzq < 10 && distanciaIzq != 0) {
    while (lecturaUltrasonico(pines_ultrasonico_cen) > 10) {
      izquierda(PWM_Der, PWM_Izq, SOBRE_PROPIO_EJE);
      delay(100);
    }
    debeGirar = true;
  } else if (distanciaIzq >= 11 && distanciaIzq <= 20) {
    izquierda(PWM_Der, PWM_Izq, CON_UNA_RUEDA);
    debeGirar = true;
  } else if (distanciaIzq >= 21 && distanciaIzq <= 30) {
    adelante(PWM_Der, PWM_Izq);
    debeGirar = true;
  }

  if (!debeGirar) {
    adelante(PWM_Der, PWM_Izq);
  }
}

uint8_t presencia() {
  uint32_t distanciaDer = lecturaUltrasonico(pines_ultrasonico_der);
  uint32_t distanciaCen = lecturaUltrasonico(pines_ultrasonico_cen);
  uint32_t distanciaIzq = lecturaUltrasonico(pines_ultrasonico_izq);

  gestionarMotores(distanciaDer, distanciaCen, distanciaIzq);

  return 0;
}