// CHIKEN LITTLE - DYNER - AIDEN - CHERNIAK - CDR '24
#include "botones.h"

uint8_t estrategia = 0;

void setupBotonesYLeds() {
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
}

void seleccionarEstrategia() {
  if (digitalRead(BTN_1) == LOW) {
    delay(10);
    estrategia = (estrategia + 1) % 16;
    mostrarEstrategia(estrategia);
  }
}

void mostrarEstrategia(uint8_t estrategia) {
  digitalWrite(LED_1, estrategia & 0x01);  // Primer bit
  digitalWrite(LED_4, estrategia & 0x02);  // Segundo bit
  digitalWrite(LED_3, estrategia & 0x04);  // Tercer bit
  digitalWrite(LED_2, estrategia & 0x08);  // Cuarto bit
}

void iniciarRobot() {
  if (digitalRead(BTN_2) == LOW) {
    delay(200);  // para que no lea 87 mil vecs ;)
    uint32_t contador = millis();

    // Esperar 5 segundos
    while (millis() - contador < 5100) {
      if (digitalRead(BTN_2) == HIGH) {
        return;
      }
    }
    ejecutarEstrategia();
  }
}

void ejecutarEstrategia() {
  switch (estrategia) {
    case 0:
      // Implementar estrategia 0
      break;
    case 1:
      // Implementar estrategia 1
      break;
    case 2:
      // Implementar estrategia 2
      break;
    case 3:
      // Implementar estrategia 3
      break;
    case 4:
      // Implementar estrategia 4
      break;
    case 5:
      // Implementar estrategia 5
      break;
    case 6:
      // Implementar estrategia 6
      break;
    case 7:
      // Implementar estrategia 7
      break;
    case 8:
      // Implementar estrategia 8
      break;
    case 9:
      // Implementar estrategia 9
      break;
    case 10:
      // Implementar estrategia 10
      break;
    case 11:
      // Implementar estrategia 11
      break;
    case 12:
      // Implementar estrategia 12
      break;
    case 13:
      // Implementar estrategia 13
      break;
    case 14:
      // Implementar estrategia 14
      break;
    case 15:
      // Implementar estrategia 15
      break;
  }
}