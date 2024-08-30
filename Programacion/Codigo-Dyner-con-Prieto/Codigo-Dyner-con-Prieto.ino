#include "motors.h"
#include "ultrasonicos.h"
#include "cny.h"
#include "botones.h"


//BOTONES Y LEDS
int estado = 0;  // 0-15 (4 bits para los 4 LEDs)
bool sistemaEncendido = false;
unsigned long tiempoInicio = 0;
bool contadorEnMarcha = false;


void setup() {
  configurarBotonesYLeds(A4, A5, A3, 5, 6, 7);  //cambair los pines 5, 6 y 7 por los leds:   A4=Boton 1 / A5=Boton 2 / A3=Led1 / Los pines de los less 2,3,4 estan en el shift register y no los se anotar
}

void loop() {
  actualizarEstado(estado, sistemaEncendido, tiempoInicio, contadorEnMarcha);
  verificarContador(tiempoInicio, contadorEnMarcha, sistemaEncendido);
}
