// CHIKEN LITTLE - DYNER - AIDEN - CHERNIAK - CDR '24
#include "motors.h"

void setupMotores() {
  pinMode(MotorIzq_A, OUTPUT);
  pinMode(MotorIzq_B, OUTPUT);
  pinMode(PWM_Izq, OUTPUT);

  pinMode(MotorDer_A, OUTPUT);
  pinMode(MotorDer_B, OUTPUT);
  pinMode(PWM_Der, OUTPUT);
}


uint8_t* pines_motorDer = (MotorDer_A, MotorDer_B);
uint8_t* pines_motorIzq = (MotorIzq_A, MotorIzq_B);

void setDir(uint8_t Dir, uint8_t* Pines) {
  switch (Dir) {
    case ADELANTE:
      digitalWrite(Pines[0], HIGH);
      digitalWrite(Pines[1], LOW);
      break;

    case ATRAS:
      digitalWrite(Pines[0], LOW);
      digitalWrite(Pines[1], HIGH);
      break;

    case PARADO:
      digitalWrite(Pines[0], LOW);
      digitalWrite(Pines[1], LOW);
      break;
  }
}

void setPwm(uint8_t Pin, uint8_t Valor) {
  analogWrite(Pin, Valor);
}

void adelante(int pwmD, int pwmI) {
  setDir(ADELANTE, pines_motorDer);
  setDir(ADELANTE, pines_motorIzq);
  setPwm(PWM_Der, pwmD);
  setPwm(PWM_Izq, pwmI);
}

void atras(int pwmD, int pwmI) {
  setDir(ATRAS, pines_motorDer);
  setDir(ATRAS, pines_motorIzq);
  setPwm(PWM_Der, pwmD);
  setPwm(PWM_Izq, pwmI);
}

void parado(int pwmD, int pwmI) {
  setDir(PARADO, pines_motorDer);
  setDir(PARADO, pines_motorIzq);
  setPwm(PWM_Der, pwmD);
  setPwm(PWM_Izq, pwmI);
}

void izquierda(int pwmD, int pwmI, int tipo) {
  switch (tipo) {
    case SOBRE_PROPIO_EJE:

      setDir(ADELANTE, pines_motorDer);
      setDir(ATRAS, pines_motorIzq);
      setPwm(PWM_Der, pwmD);
      setPwm(PWM_Izq, pwmI);
      break;

    case GIRO_ABIERTO:
      setDir(ADELANTE, pines_motorDer);
      setDir(ADELANTE, pines_motorIzq);
      setPwm(PWM_Der, pwmD);
      setPwm(PWM_Izq, pwmI);
      break;

    case CON_UNA_RUEDA:

      setDir(ADELANTE, pines_motorDer);
      setDir(PARADO, pines_motorIzq);
      setPwm(PWM_Der, pwmD);
      setPwm(PWM_Izq, pwmI);
      break;
  }
}


void derecha(int pwmD, int pwmI, int tipo) {
  switch (tipo) {
    case SOBRE_PROPIO_EJE:
      setDir(ATRAS, pines_motorDer);
      setDir(ADELANTE, pines_motorIzq);
      setPwm(PWM_Der, pwmD);
      setPwm(PWM_Izq, pwmI);
      break;

    case GIRO_ABIERTO:
      setDir(ADELANTE, pines_motorDer);
      setDir(ADELANTE, pines_motorIzq);
      setPwm(PWM_Der, pwmD);
      setPwm(PWM_Izq, pwmI);
      break;

    case CON_UNA_RUEDA:
      setDir(PARADO, pines_motorDer);
      setDir(ADELANTE, pines_motorIzq);
      setPwm(PWM_Der, pwmD);
      setPwm(PWM_Izq, pwmI);
      break;
  }
}
