#include "cny.h"

uint16_t der_blanco = 285;
uint16_t der_negro = 805;

uint16_t der_promedio = (der_blanco + der_negro) / 2;

uint16_t izq_blanco = 28;
uint16_t izq_negro = 735;

uint16_t izq_promedio = (izq_blanco + izq_negro) / 2;


bool lecturaCny(uint8_t pines, uint32_t umbral) {
  int suma = 0;
  int lectura = 0;
  for (int i = 0; i < 10; i++) {
    lectura = analogRead(pines);
    suma = suma + lectura;
  }
  int resultado = suma / 10;

  if (resultado < umbral) {
    // Serial.println("Blanco");
    return true;
  } else {
    // Serial.println("Negro");
    return false;
  }
}

uint8_t linea() {
  int lecturaDer = lecturaCny(CNY_DER, der_promedio);
  int lecturaIzq = lecturaCny(CNY_IZQ, izq_promedio);
  return lecturaDer * 1 + lecturaIzq * 2;
}