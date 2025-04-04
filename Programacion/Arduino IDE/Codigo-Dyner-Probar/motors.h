// CHIKEN LITTLE - DYNER - AIDEN - CHERNIAK - CDR '24 
#ifndef MOTORS_H
#define MOTORS_H

#include "Arduino.h"

// Motor Izquierdo
#define MotorIzq_B 
#define MotorIzq_A 
#define PWM_Izq 

// Motor Derecho
#define MotorDer_B 
#define MotorDer_A 
#define PWM_Der 

//Direcciones
#define ADELANTE 0
#define ATRAS 1
#define PARADO 2

//Velocidades
#define PWM_ADELANTE 225
#define PWM_DIFERENCIA 20

//Tipo de Giro
#define SOBRE_PROPIO_EJE 0
#define GIRO_ABIERTO 1
#define CON_UNA_RUEDA 2

extern uint8_t* pines_motorDer;
extern uint8_t* pines_motorIzq;

void setDir(uint8_t Dir, uint8_t* Pines);
void setPWM(uint8_t Pin, uint8_t Valor);
void adelante(int pwmD, int pwmI);
void atras(int pwmD, int pwmI);
void parado(int pwmD, int pwmI);
void derecha(int pwmD, int pwmI, int tipo);
void izquierda(int pwmD, int pwmI, int tipo);

void setupMotores();
#endif
