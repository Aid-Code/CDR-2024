#ifndef BOTONES_H
#define BOTONES_H

#include <Arduino.h>

// Pines de los botones y LEDs
extern int BTN_1;
extern int BTN_2;
extern int pinLeds[4];

// Variables globales
extern int estado;
extern bool sistemaEncendido;

// Definición del arreglo de estrategias
extern int estrategias[16];

// Funciones de la librería
void configurarBotonesYLeds(int boton1, int boton2, int led1, int led2, int led3, int led4);
void actualizarEstado();
void iniciarContador();
void verificarContador();
void aplicarEstrategia(int estrategia);

#endif  