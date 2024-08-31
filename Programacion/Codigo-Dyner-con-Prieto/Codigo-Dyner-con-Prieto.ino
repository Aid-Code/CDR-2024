#include "motors.h"
#include "ultrasonicos.h"
#include "cny.h"
#include "botones.h"


void setup() {
  // ULTRASONICOS
  pinMode(ECHO_DER, INPUT);
  pinMode(TRIG_DER, OUTPUT);
  pinMode(ECHO_IZQ, INPUT);
  pinMode(TRIG_IZQ, OUTPUT);
  pinMode(ECHO_MED, INPUT);
  pinMode(TRIG_MED, OUTPUT);

  //MOTORES
  pinMode(MotorIzq_A, OUTPUT);
  pinMode(MotorIzq_B, OUTPUT);
  pinMode(PWM_Izq, OUTPUT);
  pinMode(MotorDer_A, OUTPUT);
  pinMode(MotorDer_B, OUTPUT);
  pinMode(PWM_Der, OUTPUT);

  //CNY
  pinMode(CNY_IZQ, INPUT);
  pinMode(CNY_DER, INPUT);

  Serial.begin(9600);
}

void loop() {
  presencia();
}
