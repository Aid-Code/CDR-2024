// Sumo Main V1

// Sensores
#define CNY_IZQ A1
#define CNY_DER A2
#define ECHO_DER 11
#define TRIG_DER 12
#define ECHO_IZQ 7
#define TRIG_IZQ 8
#define ECHO_MED 10
#define TRIG_MED 9

// Botones y Leds
#define BTN A4
/*#define BTN_1 A6
#define BTN_2 A7
#define LED_1 A4
#define LED_2 A3
#define LED_3 13
#define LED_4 A0*/

// Motor Izquierdo
#define M1_B A5
#define M1_A 2
#define PWM_A 5

// Motor Derecho
#define M2_B 4
#define M2_A 6
#define PWM_B 3

int estado_main = 0;

enum estados
{
  INIT,

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

  //Boton
  pinMode(BTN, INPUT_PULLUP);

  analogWrite(PWM_A, 105); //Motor Izquierdo
  analogWrite(PWM_B, 80); //Motor Derecho

  while(digitalRead(BTN) == HIGH){}
  delay(5100);
  Serial.println("Prendido");
}

void loop() 
{
  LecturaUltrasonicos();
  ExistenciaUlt();
  LecturaCNY();
  DetectarLinea();
}

void MaquinaMain()
{
  switch(estado_main)
  {
    
  }
}