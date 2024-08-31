#include "botones.h"

// Inicializar variables globales
int BTN_1;
int BTN_2;
int pinLeds[4];

int estado = 0;  // Inicialmente en la primera estrategia
bool sistemaEncendido = false;

int estrategias[16];  // Definición del arreglo de estrategias

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
    estado = (estado + 1) % 16;  // Cambiar estado (0-15 para las 16 estrategias)
    delay(200);                  // Debounce
  }

  if (digitalRead(BTN_2) == LOW) {
    iniciarContador();
    delay(200);  // Debounce
  }

  // Actualizar LEDs basado en el estado (código binario)
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
    if (tiempoActual - tiempoInicio >= 5000) {
      sistemaEncendido = true;   // Activar el sistema después de 5 segundos
      contadorEnMarcha = false;  // Detener el contador

      aplicarEstrategia(estado);  // Aplicar la estrategia seleccionada
    }
  }
}

// Aplicar la estrategia seleccionada
void aplicarEstrategia(int estrategia) {
  switch (estrategia) {
    case 0:  // Estrategia 0 (0000 en binario)
      break;

    case 1:  // Estrategia 1 (0001 en binario)
      break;

    case 2:  // Estrategia 2 (0010 en binario)
      break;

    case 3:  // Estrategia 3 (0011 en binario)
      break;

    case 4:  // Estrategia 4 (0100 en binario)
      break;

    case 5:  // Estrategia 5 (0101 en binario)
      break;

    case 6:  // Estrategia 6 (0110 en binario)
      break;

    case 7:  // Estrategia 7 (0111 en binario)
      break;

    case 8:  // Estrategia 8 (1000 en binario)
      break;

    case 9:  // Estrategia 9 (1001 en binario)
      break;

    case 10:  // Estrategia 10 (1010 en binario)
      break;

    case 11:  // Estrategia 11 (1011 en binario)
      break;

    case 12:  // Estrategia 12 (1100 en binario)
      break;

    case 13:  // Estrategia 13 (1101 en binario)
      break;

    case 14:  // Estrategia 14 (1110 en binario)
      break;

    case 15:  // Estrategia 15 (1111 en binario)
      break;

    default:
      // Código para cualquier otro valor (opcional)
      break;
  }

  // Actualizar LEDs basado en la estrategia (código binario)
  for (int i = 0; i < 4; i++) {
    digitalWrite(pinLeds[i], (estrategia & (1 << i)) ? HIGH : LOW);
  }
}