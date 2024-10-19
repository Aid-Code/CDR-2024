// Sensores
#define CNY_IZQ A6
#define CNY_DER A7


#define ECHO_1 8
#define ECHO_2 9 // Izquierda
#define ECHO_3 10 // Medio<
#define ECHO_4 A1 // Derecha
#define ECHO_5 A2


#define TRIG_1 0b00000100
#define TRIG_2 0b01000000 // Izquierda
#define TRIG_3 0b00100000 // Medio
#define TRIG_4 0b00001000 // Derecha
#define TRIG_5 0b00010000


#define TRIG_L 0b00000000


// Botones y Leds
#define BTN_1 A4
#define BTN_2 A5


#define LED_1 0b00000001
#define LED_2 0b10000000
#define LED_3 0b00000010
#define LED_4 A3


//Shift Register
#define DATA 11    
#define LATCH 12    
#define CLOCK 13


// Motor Izquierdo
#define AIN_2 3
#define AIN_1 4
#define PWM_A 6


// Motor Derecho
#define BIN_2 2
#define BIN_1 7
#define PWM_B 5

// Valores

#define PWM_CHILL 50
#define PWM_FULL 80

#define RANGO_ULT 20

#define CUENTAS_RESET 5

// CNY Izquierdo

uint32_t lectura_cny_izq = 0;
uint32_t cny_izquierdo = 0;
uint32_t suma_cny_izq = 0;

uint32_t izq_blanco = 635;
uint32_t izq_negro = 840;

uint32_t izq_promedio = (izq_blanco + izq_negro) / 2;


//CNY Derecho

uint32_t lectura_cny_der = 0;
uint32_t cny_derecho = 0;
uint32_t suma_cny_der = 0;

uint32_t der_blanco = 385;
uint32_t der_negro = 780;

uint32_t der_promedio = (der_blanco + der_negro) / 2;

bool flag_cny_der = false;
bool flag_cny_izq = false;
bool flag_cny_both = false;


// Ultrasonicos

long tiempo_ult_der = 0;
long tiempo_ult_med = 0;
long tiempo_ult_izq = 0;

long distancia_ult_der = 0;
long distancia_ult_med = 0;
long distancia_ult_izq = 0;

bool flag_ult_der = false;
bool flag_ult_med = false;
bool flag_ult_izq = false;


// Millis

uint16_t actual_millis = 0;
uint16_t prev_millis = 0;
uint16_t stop_millis = 0;
uint16_t step_millis = 0;


bool is_moving;


// Debounce

bool estado_previo[2];
uint8_t contador[2] = {0,0};
uint8_t pines_dbnc[2] = {BTN_1, BTN_2};

bool flag_evento[2] = {false,false};
bool flag_tipo[2] = {false,false};
bool estado_actual;
bool iniciar = false;

auto prev_dbnc_millis = millis();

int counter = 0;


void setup()
{
  Serial.begin(9600);


  //Motores
  pinMode(PWM_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);


  pinMode(AIN_1, OUTPUT);
  pinMode(BIN_1, OUTPUT);
  pinMode(AIN_2, OUTPUT);
  pinMode(BIN_2, OUTPUT);


  //Sensores
  pinMode(ECHO_4, INPUT);
  pinMode(ECHO_3, INPUT);
  pinMode(ECHO_2, INPUT);


  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);


  //Boton y led
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(LED_4, OUTPUT);


  analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
  analogWrite(PWM_B, PWM_CHILL);  //Motor Derecho
}

void loop() 
{
  actual_millis = millis();

  if (iniciar && actual_millis - prev_millis >= 5000)
  {
    LecturaUltrasonicos();
    ExistenciaUlt();
    LecturaCNY();
    DetectarLinea(); 
    
    no_caerse();
    maquina_seteadora(counter);
  }

  if(actual_millis - prev_dbnc_millis >= 1)
  {
    prev_dbnc_millis = actual_millis;

    funcion_debounce();
  }
}

void no_caerse()
{
  if (flag_cny_izq) 
  {
    // Serial.println("Atras");
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);
    Atras();
    delay(500);
    Izquierda();
    delay(200);
    analogWrite(PWM_A, PWM_CHILL);
    analogWrite(PWM_B, PWM_CHILL);
    // Serial.println("Derecha");
  } 
  else if (flag_cny_der) 
  {
    // Serial.println("Atras");
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);
    Atras();
    delay(500);
    Derecha();
    delay(150);
    analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_CHILL);
    // Serial.println("Izquierda");
  }
}

void maquina_seteadora(int strat)
{
  switch (strat)
  {
    case 1:
      Serial.println("crespin");
      crespin();
      break;

    case 2:
      Serial.println("pasitos");
      pasitos();
      break;

    case 3:
      Serial.println("radar");
      radar();
      break;

    case 4:
      Serial.println("bartolito");
      bartolito();
      break;

    case 5:
      Serial.println("torero");
      torero();
      break;
  }
}

void funcion_debounce(void)
{
  for(uint8_t i = 0; i < 2; i++)
  {
    estado_actual = digitalRead(pines_dbnc[i]);

    if(estado_actual != estado_previo[i])
    {
      contador[i] = CUENTAS_RESET;
      flag_evento[i] = false;
    }
    else
    {
      if(contador[i] > 0)
      {
        contador[i]--;

        if(contador[i] == 0)
        {
          flag_evento[i] = true;
          flag_tipo[i] = estado_actual;
          
          if(contador[0] == 0)
          {
            counter++;
            Serial.println(counter);
            mostrarBinario(counter);
            if (counter >= 5)
            {
              counter = 0;
            }
          }

          if (contador[1] == 0)
          {
            iniciar = true;
            prev_millis = actual_millis;
          }
        }
      }
    }
  }
}

void mostrarBinario(int valor) {

  // LEDs conectados al shift register (Q0, Q6, y Q7)
  uint8_t datosShiftRegister = 0b00000000;

  // LED en Q7 (valor binario 0001)
  if (valor & 0b0001) {
    datosShiftRegister |= LED_1; //LED 1
  }

  // LED en Q0 (valor binario 0010)
  if (valor & 0b0010) {
    datosShiftRegister |= LED_2;   //LED 2
  }

  // LED en Q6 (valor binario 0100)
  if (valor & 0b0100) {
    datosShiftRegister |= LED_3; // LED 3
  }

  // LED conectado directamente al pin 4 (LED_4)
  uint8_t estadoLED4 = (valor & 0b1000) ? HIGH : LOW;
  digitalWrite(LED_4, estadoLED4);

  // Enviar los datos al shift register
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, datosShiftRegister);
  digitalWrite(LATCH, HIGH);

  // Mostrar el estado de los LEDs en binario en el monitor serial
  /*Serial.print("Estado de los LEDs: ");
  Serial.print(estadoLED4 ? "1" : "0");       // LED 4 (pin 4)
  Serial.print((valor & 0b0100) ? "1" : "0");  // Q6 (LED 3)
  Serial.print((valor & 0b0010) ? "1" : "0");  // Q0 (LED 2)
  Serial.print((valor & 0b0001) ? "1" : "0");  // Q7 (LED 1)
  
  
 
  Serial.println();  // Nueva línea*/
}

void crespin()
{
  if (flag_ult_med)
  {
    analogWrite(PWM_A, 255);
    analogWrite(PWM_B, 255);
    Adelante();
  }
  else if (flag_ult_der)
  {
    Derecha();
  }
  else if (flag_ult_izq)
  {
    Izquierda;
  }
}

void torero()
{
  bool ole;
  ole = false;

  if (!flag_ult_med && !ole)
  {
    if (distancia_ult_der > 10 && distancia_ult_der <= 20)
    {
      analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
      analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
      Adelante();
      delay(500);

      analogWrite(PWM_A, 250);  //Motor Izquierdo
      analogWrite(PWM_B, 20);  //Motor Derecho
      Adelante();
      delay(600);

      ole = true;
    }
    else if (distancia_ult_izq > 10 && distancia_ult_izq <= 20)
    {
      analogWrite(PWM_A, 200);  //Motor Izquierdo
      analogWrite(PWM_B, 200);  //Motor Derecho
      Adelante();
      delay(200);

      analogWrite(PWM_A, 250);  //Motor Izquierdo
      analogWrite(PWM_B, 20);  //Motor Derecho
      Adelante();
      delay(600);

      ole = true;
    }
  }
  else if (flag_ult_med && ole)
  {
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
    Adelante();
  }
  else if (flag_ult_der && ole)
  {
    analogWrite(PWM_A, 250);  //Motor Izquierdo
    analogWrite(PWM_B, 100);  //Motor Derecho
    Derecha();
  }
  else if (flag_ult_izq && ole)
  {
    analogWrite(PWM_A, 250);  //Motor Izquierdo
    analogWrite(PWM_B, 100);  //Motor Derecho
    Izquierda();
  }
}

void radar()
{
  if (!flag_ult_med)
  {
    if (distancia_ult_der > 20 && distancia_ult_der <= 30)
    {
      analogWrite(PWM_A, 50);  //Motor Izquierdo
      analogWrite(PWM_B, 50);  //Motor Derecho
      Derecha();
    }
    else if (distancia_ult_der > 10 && distancia_ult_der <= 20)
    {
      analogWrite(PWM_A, 60);  //Motor Izquierdo
      analogWrite(PWM_B, 60);  //Motor Derecho
      Derecha();
    }
    else if (distancia_ult_der < 10 && distancia_ult_der != 0)
    {
      analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
      analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
      Derecha();
    }
    else if (distancia_ult_izq > 20 && distancia_ult_izq <= 30)
    {
      analogWrite(PWM_A, 50);  //Motor Izquierdo
      analogWrite(PWM_B, 50);  //Motor Derecho
      Izquierda();
    }
    else if (distancia_ult_izq > 10 && distancia_ult_izq <= 20)
    {
      analogWrite(PWM_A, 60);  //Motor Izquierdo
      analogWrite(PWM_B, 60);  //Motor Derecho
      Izquierda();
    }
    else if (distancia_ult_izq < 10 && distancia_ult_izq != 0)
    {
      analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
      analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
      Izquierda();
    }
    else 
    {
      Parado();
    }
  }
  else if (distancia_ult_med <= 20)
  {
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
    Adelante();
  }
}

void bartolito()
{
  if (!flag_ult_med)
  {
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
    Derecha();
  }
  else if (flag_ult_med)
  {
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
    Adelante();
  }
}

void pasitos()
{
  if (!flag_ult_med)
  {
    if (is_moving && actual_millis - step_millis >= 300)
    {
      Parado();
      stop_millis = actual_millis;
      is_moving = false;
    }
    else if (!is_moving && actual_millis - stop_millis >= 1000)
    {
      Adelante();
      analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
      analogWrite(PWM_B, PWM_CHILL);  //Motor Derecho
      step_millis = actual_millis;
      is_moving = true;
    }
  }
  else if (flag_ult_med)
  {
    Adelante();
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
  }
  
  
  if (flag_ult_izq)
  {
    //falta comprobar distancia
    Izquierda();
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
  }
  else if (flag_ult_der)
  {
    //falta comprobar distancia
    Derecha();
    analogWrite(PWM_A, PWM_FULL);  //Motor Izquierdo
    analogWrite(PWM_B, PWM_FULL);  //Motor Derecho
  }
}

void LecturaUltrasonicos()
{
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_3);
  digitalWrite(LATCH, HIGH);
  delay(10);
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
  digitalWrite(LATCH, HIGH);


  tiempo_ult_med = pulseIn(ECHO_3, HIGH, 10000);


  distancia_ult_med = tiempo_ult_med / 59;


  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_4);
  digitalWrite(LATCH, HIGH);
  delay(10);
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
  digitalWrite(LATCH, HIGH);


  tiempo_ult_der = pulseIn(ECHO_4, HIGH, 10000);


  distancia_ult_der = tiempo_ult_der / 59;


  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_2);
  digitalWrite(LATCH, HIGH);
  delay(10);
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
  digitalWrite(LATCH, HIGH);


  tiempo_ult_izq = pulseIn(ECHO_2, HIGH, 10000);


  distancia_ult_izq = tiempo_ult_izq / 59;
}


void ExistenciaUlt()
{
  /*Serial.print(distancia_ult_izq);
  Serial.print('\t');
  Serial.print(distancia_ult_med);
  Serial.print('\t');
  Serial.print(distancia_ult_der);
  Serial.println();*/
 
  if (distancia_ult_med < RANGO_ULT && distancia_ult_med != 0) {
    // Serial.println("Hay algo");
    flag_ult_med = true;
  } else {
    // Serial.println("No hay moros en la costa");
    flag_ult_med = false;
  }


  if (distancia_ult_der < RANGO_ULT && distancia_ult_der != 0) {
    flag_ult_der = true;
  } else {
    flag_ult_der = false;
  }


  if (distancia_ult_izq < RANGO_ULT && distancia_ult_izq != 0) {
    flag_ult_izq = true;
  } else
  {
    flag_ult_izq = false;
  }
}

void LecturaCNY() 
{
  for (int i = 0; i < 10; i++)
  {
    lectura_cny_izq = analogRead(CNY_IZQ);
    suma_cny_izq = suma_cny_izq + lectura_cny_izq;
  }


  for (int i = 0; i < 10; i++) 
  {
    lectura_cny_der = analogRead(CNY_DER);
    suma_cny_der = suma_cny_der + lectura_cny_der;
  }


  cny_izquierdo = suma_cny_izq / 10;
  cny_derecho = suma_cny_der / 10;


  suma_cny_izq = 0;
  suma_cny_der = 0;
}


void DetectarLinea()
{
  if (cny_izquierdo < izq_promedio) {
    // Serial.println("Blanco");
    flag_cny_izq = true;
  } else {
    // Serial.println("Negro");
    flag_cny_izq = false;
  }


  if (cny_derecho < der_promedio) {
    flag_cny_der = true;
  } else {
    flag_cny_der = false;
  }


  if (cny_izquierdo < izq_promedio && cny_derecho < der_promedio) {
    flag_cny_both = false;
  } else {
    flag_cny_both = true;
  }
}


void Parado()
{
  digitalWrite(AIN_1, LOW);
  digitalWrite(AIN_2, LOW);
 
  digitalWrite(BIN_1, LOW);
  digitalWrite(BIN_2, LOW);
}


void Adelante()
{
  digitalWrite(AIN_1, LOW);
  digitalWrite(AIN_2, HIGH);
 
  digitalWrite(BIN_1, HIGH);
  digitalWrite(BIN_2, LOW);
}


void Atras()
{
  digitalWrite(AIN_1, HIGH);
  digitalWrite(AIN_2, LOW);


  digitalWrite(BIN_1, LOW);
  digitalWrite(BIN_2, HIGH);
}


void Derecha()
{
  digitalWrite(AIN_1, LOW);
  digitalWrite(AIN_2, HIGH);


  digitalWrite(BIN_1, LOW);
  digitalWrite(BIN_2, HIGH);
}


void Izquierda()
{
  digitalWrite(AIN_1, HIGH);// Izquierda atras
  digitalWrite(AIN_2, LOW); // Izquierda adelante


  digitalWrite(BIN_1, HIGH); // Derecha adelante
  digitalWrite(BIN_2, LOW); // Derecha atras
}