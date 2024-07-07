// Librerías necesarias
#include <TimerOne.h>

// Pines de conexión
const int pinIncremento = 2;
const int pinDecremento = 3;
const int pinInicio = 4;
const int pinLed = 13;

// Variables globales
int tiempoConfigurado = 60; // Tiempo inicial de 60 segundos
int tiempoActual = 0;
bool conteoActivo = false;

// Estados del sistema
enum Estados {
  CONFIGURACION,
  ESPERA_INICIO,
  CONTEO_REGRESIVO
};

Estados estadoActual = CONFIGURACION;

void setup() {
  // Inicializar pines como entradas o salidas
  pinMode(pinIncremento, INPUT);
  pinMode(pinDecremento, INPUT);
  pinMode(pinInicio, INPUT);
  pinMode(pinLed, OUTPUT);

  // Inicializar TimerOne para generar una interrupción cada segundo
  Timer1.initialize(1000000); // 1 segundo
  Timer1.attachInterrupt(contarSegundo);
}

void loop() {
  // Leer estados de los pulsadores
  int estadoIncremento = digitalRead(pinIncremento);
  int estadoDecremento = digitalRead(pinDecremento);
  int estadoInicio = digitalRead(pinInicio);

  // Procesar estados del sistema
  switch (estadoActual) {
    case CONFIGURACION:
      if (estadoIncremento == HIGH) {
        tiempoConfigurado++;
        Serial.print("Tiempo configurado: ");
        Serial.println(tiempoConfigurado);
      } else if (estadoDecremento == HIGH) {
        tiempoConfigurado--;
        if (tiempoConfigurado < 1) {
          tiempoConfigurado = 1;
        }
        Serial.print("Tiempo configurado: ");
        Serial.println(tiempoConfigurado);
      } else if (estadoInicio == HIGH) {
        estadoActual = ESPERA_INICIO;
        tiempoActual = tiempoConfigurado;
      }
      break;
    case ESPERA_INICIO:
      if (estadoInicio == HIGH) {
        estadoActual = CONTEO_REGRESIVO;
        conteoActivo = true;
      }
      break;
    case CONTEO_REGRESIVO:
      if (conteoActivo) {
        if (tiempoActual > 0) {
          tiempoActual--;
          Serial.print("Tiempo restante: ");
          Serial.println(tiempoActual);
          digitalWrite(pinLed, HIGH);
          delay(500);
          digitalWrite(pinLed, LOW);
          delay(500);
        } else {
          conteoActivo = false;
          estadoActual = CONFIGURACION;
          Serial.println("Tiempo finalizado!");
        }
      }
      break;
  }
}

void contarSegundo() {
  if (conteoActivo) {
    tiempoActual--;
    Serial.print("Tiempo restante: ");
    Serial.println(tiempoActual);
  }
}

void serialEvent() {
  if (Serial.available() > 0) {
    String trama = Serial.readStringUntil('*');
    if (trama.startsWith("#1-60")) {
      tiempoConfigurado = 60;
      Serial.println("Tiempo configurado a 60 segundos");
    } else if (trama.startsWith("#1-30")) {
      tiempoConfigurado = 30;
      Serial.println("Tiempo configurado a 30 segundos");
    } else if (trama.startsWith("#l-ok")) {
      tiempoConfigurado = tiempoActual;
      Serial.println("Tiempo configurado al valor actual");
    }
  }
}