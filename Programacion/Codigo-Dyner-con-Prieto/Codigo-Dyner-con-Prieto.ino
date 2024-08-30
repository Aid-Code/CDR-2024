// Sensores
//CNY70
#define CNY_IZQ A1
#define CNY_DER A0
//Ultrasonicos
#define ECHO_DER 12  //3
#define TRIG_DER 13  //3
#define ECHO_IZQ 11  //1
#define TRIG_IZQ 10  //1
#define ECHO_MED 9   //2
#define TRIG_MED 8   //

// Placa de Botones
#define BTN A4
/*#define BTN_1 A6
#define BTN_2 A7
#define LED_1 A4
#define LED_2 A3
#define LED_3 13
#define LED_4 A0*/

// Motor Izquierdo
#define MotorIzq_B 7
#define MotorIzq_A 4
#define PWM_Izq 6

// Motor Derecho
#define MotorDer_B 2
#define MotorDer_A 3
#define PWM_Der 5

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

uint8_t* pines_motorDer = (MotorDer_A ,MotorDer_B);
uint8_t* pines_motorIzq = (MotorIzq_A ,MotorIzq_B);

void setDir(uint8_t Dir,uint8_t* Pines);
void setPWM(uint8_t Pin, uint8_t Valor);
void adelante(int pwmD,int pwmI);
void atras(int pwmD,int pwmI);
void parado(int pwmD,int pwmI);
void derecha(int pwmD,int pwmI, int tipo);
void izquierda(int pwmD,int pwmI, int tipo);



void setup(){

}

void loop(){

}

void setDir(uint8_t Dir,uint8_t* Pines)
{
switch (Dir){ 
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

void setPwm(uint8_t Pin, uint8_t Valor){
  analogWrite(Pin, Valor);
}

void adelante(int pwmD,int pwmI){
  setDir(ADELANTE,pines_motorDer);
  setDir(ADELANTE,pines_motorIzq);
  setPwm(PWM_Der, pwmD);
  setPwm(PWM_Izq, pwmI);
}

void atras (int pwmD,int pwmI){
  setDir(ATRAS,pines_motorDer);
  setDir(ATRAS,pines_motorIzq);
  setPwm(PWM_Der, pwmD);
  setPwm(PWM_Izq, pwmI);

}

void parado (int pwmD,int pwmI){
  setDir(PARADO,pines_motorDer);
  setDir(PARADO,pines_motorIzq);
  setPwm(PWM_Der, pwmD);
  setPwm(PWM_Izq, pwmI);

}

void izquierda (int pwmD,int pwmI, int tipo){
  switch (tipo){
    case: SOBRE_PROPIO_EJE
  setDir(ATRAS,pines_motorDer);
  setDir(ADELANTE,pines_motorIzq);
  break;  

    case: GIRO_ABIERTO


  break;

    case: CON_UNA_RUEDA
  setDir(PARADO,pines_motorDer);
  setDir(ADELANTE,pines_motorIzq);
  break;
  }
}


void derecha (int pwmD,int pwmI, int tipo) {
  switch(tipo){
      case: SOBRE_PROPIO_EJE
  setDir(ADELANTE,pines_motorDer);
  setDir(ATRAS,pines_motorIzq);
  break;  

    case: GIRO_ABIERTO


  break;

    case: CON_UNA_RUEDA
  setDir(ADELANTE,pines_motorDer);
  setDir(PARADO,pines_motorIzq);
  break;
  }
}