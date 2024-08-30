#include "botones.h"

// Inicializar variables globales
int BTN_1;
int BTN_2;
int pinLeds[4];

int estado = 0;  // 0-15
bool sistemaEncendido = false;

unsigned long tiempoInicio = 0;
bool contadorEnMarcha = false;

// Configurar pines de los botones y LEDs
void configurarBotonesYLeds(int boton1, int boton2, int led1, int led2, int led3, int led4) {
  BTN_1 = boton1;
  BTN_2 = boton2;
  pinLeds[0] = led1;
  pinLeds[1] = led2;
  pinLeds[2] = led3;
  pinLeds[3] = led4;

  pinMode(BTN_1, INPUT);
  pinMode(BTN_2, INPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(pinLeds[i], OUTPUT);
  }
}

// Actualizar el estado basado en los botones
void actualizarEstado() {
  if (digitalRead(BTN_1) == LOW) {
    estado = (estado + 1) % 16;  // Cambiar estado (0-15)
    delay(200);
  }

  if (digitalRead(BTN_2) == LOW) {
    iniciarContador();
    delay(200);  // Debounce
  }

  // Actualizar LEDs basado en el estado
  for (int i = 0; i < 4; i++) {
    digitalWrite(pinLeds[i], (estado & (1 << i)) ? HIGH : LOW);
  }
}

// Iniciar el contador de 5 segundos
void iniciarContador() {
  tiempoInicio = millis();
  contadorEnMarcha = true;
}

// Verificar y actualizar el estado del contador
void verificarContador() {
  if (contadorEnMarcha) {
    unsigned long tiempoActual = millis();
    if (tiempoActual - tiempoInicio = 5100) {
      sistemaEncendido = true;   // Activar el sistema después de 5 segundos
      contadorEnMarcha = false;  // Detener el contador
    }
  }
}
