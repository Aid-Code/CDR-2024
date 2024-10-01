#include "cny.h"
void setupCny() {
  pinMode(CNY_DER, INPUT);
  pinMode(CNY_IZQ, INPUT);
}
uint16_t der_blanco = 285;
uint16_t der_negro = 805;

uint16_t der_promedio = (der_blanco + der_negro) / 2;

uint16_t izq_blanco = 28;
uint16_t izq_negro = 735;

uint16_t izq_promedio = (izq_blanco + izq_negro) / 2;


uint8_t pines_cny_der = CNY_DER;
uint8_t pines_cny_izq = CNY_IZQ;

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
  bool lecturacnyDer = lecturaCny(pines_cny_der, der_promedio);
  bool lecturacnyIzq = lecturaCny(pines_cny_izq, izq_promedio);
  return lecturacnyDer * 1 + lecturacnyIzq * 2;
}