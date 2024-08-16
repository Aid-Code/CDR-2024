// Sumo Main V1

// Sensores
#define CNY_IZQ A0
#define CNY_DER A1
#define ECHO_DER 12
#define TRIG_DER 13
#define ECHO_IZQ 11
#define TRIG_IZQ 10
#define ECHO_MED 9
#define TRIG_MED 8

// Botones y Leds
#define BTN_1 A6
#define BTN_2 A7
#define LED_1 A5
#define LED_2 A2
#define LED_3 A3
#define LED_4 A4

// Motor Izquierdo
#define M1_B 7
#define M1_A 4
#define PWM_A 6

// Motor Derecho
#define M2_B 2
#define M2_A 3
#define PWM_B 5

int estado_strat = 0;

int boton_1 = 0;
int boton_2 = 0;

enum estrategias
{
  NORMIE,
  PASITOS,
  FIUM
}

void setup() 
{
  Serial.begin(9600);

  //Motores
  pinMode(PWM_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);
  pinMode(M1_A, OUTPUT);
  pinMode(M2_A, OUTPUT);
  pinMode(M1_B, OUTPUT);
  pinMode(M2_B, OUTPUT);

  //Sensores
  pinMode(TRIG_DER, OUTPUT);
  pinMode(ECHO_DER, INPUT);
  pinMode(TRIG_MED, OUTPUT);
  pinMode(ECHO_MED, INPUT);
  pinMode(TRIG_IZQ, OUTPUT);
  pinMode(ECHO_IZQ, INPUT);

  //Botones
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);

  //Leds
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);

  analogWrite(PWM_A, 105); //Motor Izquierdo
  analogWrite(PWM_B, 80); //Motor Derecho
}

void loop() 
{
  LecturaUltrasonicos();
  ExistenciaUltrasonicos();
  LecturaCNY();
  DetectarLinea();

  while(boton_1 == HIGH && boton_2 == HIGH)
  {
    boton_1 = digitalRead(BTN_1);
    boton_2 = digitalRead(BTN_2);

    if(boton_1 == HIGH)
    {
      estado_strat = NORMIE;
    }
    else if (boton_2 == HIGH)
    {
      estado_strat = FIUM;
    }
  }
}

void MaquinaEstrategias()
{
  switch(estado_strat)
  {
    case NORMIE:
      if ()
  }
}