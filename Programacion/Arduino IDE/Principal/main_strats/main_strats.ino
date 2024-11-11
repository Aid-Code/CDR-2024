// Sensores
#define CNY_IZQ A6
#define CNY_DER A7

#define ECHO_1 8 // izquierda
#define ECHO_2 9 // izquierda 45
#define ECHO_3 10 // Medio 
#define ECHO_4 A1 // derecha 45
#define ECHO_5 A2 // derecha

#define TRIG_1 0b00000100 // izquierda
#define TRIG_2 0b01000000 // izquierda 45
#define TRIG_3 0b00100000 // Medio
#define TRIG_4 0b00001000 // derecha 45
#define TRIG_5 0b00010000 // derecha

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
#define PWM_CHILL 100 //100
#define PWM_FULL 255
#define RANGO_ULT 40
#define CUENTAS_RESET 5
#define GIRO_TICTAC 400
#define CANT_ESTRATEGIAS 6

#define GIRO_IZQ_45 90
#define GIRO_IZQ_90 140
#define GIRO_IZQ_180 280

#define GIRO_DER_45 90
#define GIRO_DER_90 135
#define GIRO_DER_180 220

uint16_t pines_trig_ultrasonicos[5] = {TRIG_1, TRIG_2, TRIG_3, TRIG_4, TRIG_5};
uint16_t pines_echo_ultrasonicos[5] = {ECHO_1, ECHO_2, ECHO_3, ECHO_4, ECHO_5};

// CNY Izquierdo
uint32_t lectura_cny_izq = 0;
uint32_t cny_izquierdo = 0;
uint32_t suma_cny_izq = 0;

uint32_t izq_blanco = 640;
uint32_t izq_negro = 752;

uint32_t izq_promedio = (izq_blanco + izq_negro) / 2;

//CNY Derecho
uint32_t lectura_cny_der = 0;
uint32_t cny_derecho = 0;
uint32_t suma_cny_der = 0;

uint32_t der_blanco = 420;
uint32_t der_negro = 814;

uint32_t der_promedio = (der_blanco + der_negro) / 2;

bool flag_cny_der = false;
bool flag_cny_izq = false;
bool flag_cny_both = false;

// Ultrasonicos
long tiempo_ult = 0;
long distancia_ult = 0;

bool lecturas_ult[5] = {false,false,false,false,false};
uint16_t distancias_ult[5] = {0,0,0,0,0};

// Millis
uint16_t actual_millis = 0;
uint16_t prev_millis = 0;

uint16_t stop_millis = 0;
uint16_t step_millis = 0;
uint16_t tictac_millis = 0;
uint16_t radar_millis = 0;
uint16_t arranque_millis = 0;

// Auxiliares

bool is_moving = false;
bool ole = false;
bool flag_arranque = false;

uint8_t flag_tictac = 0;
uint8_t auxiliar = 0;
uint16_t tiempo_direccion_arranque = 0;


// Debounce

bool estado_previo[2];
uint8_t contador[2] = {0,0};
uint8_t pines_dbnc[2] = {BTN_1, BTN_2};

bool flag_evento[2] = {false,false};
bool flag_tipo[2] = {false,false};
bool estado_actual;
bool iniciar = false;

auto prev_dbnc_millis = millis();

// Counters

uint8_t counter_direccion = 0;
uint8_t counter_strat = 0;
uint8_t counter_setear = 0;

void funcion_debounce();
void no_caerse();
void maquina_seteadora(int strat);
void direcciones(int direccion);
void mostrarBinario(int valor);

bool lectura(int trig, int echo);
uint16_t distancia(int trig, int echo);
void LecturaCNY();
void DetectarLinea();

void adelante(int pwm_a, int pwm_b);
void atras(int pwm_a, int pwm_b);
void izquierda(int pwm_a, int pwm_b);
void derecha(int pwm_a, int pwm_b);
void parado();

void crespin();
void pasitos();
void tic_tac();
void bartolito();
void torero();
void radar();


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

  //Placa botones
  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);
  pinMode(LED_4, OUTPUT);

  analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
  analogWrite(PWM_B, (PWM_CHILL-30));  //Motor Derecho

  Serial.println("Setear direccion");

  actual_millis = millis();
  prev_millis = millis();
  step_millis = millis();
  stop_millis = millis();
  radar_millis = millis();
  tictac_millis = millis();
  arranque_millis = millis();
}

void loop() 
{
  if(millis() - prev_dbnc_millis >= 1)
  {
    prev_dbnc_millis = millis();

    funcion_debounce();
  }
  
  if (iniciar && millis() - prev_millis >= 5000)
  {
    for (uint8_t i = 0; i < 5; i++)
    {
      distancias_ult[i] = distancia(pines_trig_ultrasonicos[i], pines_echo_ultrasonicos[i]);
      
      if (distancias_ult[i]  <= RANGO_ULT && distancias_ult[i] != 0)
      {
        lecturas_ult[i] = true;
      }
      else if (distancias_ult[i]  > RANGO_ULT || distancias_ult[i] == 0)
      {
        lecturas_ult[i] = false;
      }
    }
    LecturaCNY();
    DetectarLinea(); 
    no_caerse();

    if (!flag_arranque)
    {
      analogWrite(PWM_A, PWM_FULL);
      analogWrite(PWM_B, (PWM_FULL-30));

      if (auxiliar == 0)
      {
        arranque_millis = millis();
        auxiliar = 1;
      }
      direcciones(counter_direccion);

      if (millis() - arranque_millis >= tiempo_direccion_arranque)
      {
        flag_arranque = true;
      }
    }
    
    if (flag_arranque)
    {
      maquina_seteadora(counter_strat);
      //parado();
    }
  }
}

void no_caerse()
{
  if (flag_cny_izq) 
  {
    // Serial.println("atras");
    atras(PWM_FULL, (PWM_FULL-30));
    delay(400);
    derecha(PWM_FULL, (PWM_FULL-30));
    delay(100);
    analogWrite(PWM_A, PWM_CHILL);
    analogWrite(PWM_B, (PWM_CHILL-30));
    // Serial.println("derecha");
  } 
  else if (flag_cny_der) 
  {
    // Serial.println("atras");
    atras(PWM_FULL, (PWM_FULL-30));
    delay(400);
    izquierda(PWM_FULL, (PWM_FULL-30));
    delay(120);
    analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
    analogWrite(PWM_B, (PWM_CHILL-30));
    // Serial.println("izquierda");
  }
  else if (flag_cny_both)
  {
    // Serial.println("atras");
    atras(PWM_FULL, (PWM_FULL-30));
    delay(600);
    izquierda(PWM_FULL, (PWM_FULL-30));
    delay(100);
    analogWrite(PWM_A, PWM_CHILL);  //Motor Izquierdo
    analogWrite(PWM_B, (PWM_CHILL-30));
    // Serial.println("izquierda");
  }
}

void direcciones (int direccion)
{
  switch (direccion)
  {
    case 1:
      //Serial.println("izquierda 45");
      izquierda(PWM_FULL, (PWM_FULL-30));
      tiempo_direccion_arranque = GIRO_IZQ_45;
      break;

    case 2:
      //Serial.println("izquierda 90");
      izquierda(PWM_FULL, (PWM_FULL-30));
      tiempo_direccion_arranque = GIRO_IZQ_90;
      break;

    case 3:
      //Serial.println("izquierda 180");
      tiempo_direccion_arranque = GIRO_IZQ_180;
      izquierda(PWM_FULL, (PWM_FULL-30));
      break;

    case 4:
      //Serial.println("derecha 45");
      tiempo_direccion_arranque = GIRO_DER_45;
      derecha(PWM_FULL, (PWM_FULL-30));
      break;

    case 5:
      //Serial.println("derecha 90");
      tiempo_direccion_arranque = GIRO_DER_90;
      derecha(PWM_FULL, (PWM_FULL-30));
      break;

    case 6:
      //Serial.println("derecha 180");
      tiempo_direccion_arranque = GIRO_DER_180;
      derecha(PWM_FULL, (PWM_FULL-30));
      break;

    default:
      derecha(PWM_FULL, (PWM_FULL-30));
      break;
  }
}

void maquina_seteadora (int strat)
{
  switch (strat)
  {
    case 1:
      //Serial.println("crespin");
      crespin();
      break;

    case 2:
      //Serial.println("pasitos");
      pasitos();
      break;

    case 3:
      //Serial.println("tic-tac");
      tic_tac();
      break;

    case 4:
      //Serial.println("bartolito");
      bartolito();
      break;

    case 5:
      //Serial.println("torero");
      torero();
      break;

    case 6:
      //Serial.println("radar");
      radar();
      break;

    default:
      pasitos();
      break;
  }
}

void crespin()
{
  if (lecturas_ult[2])
  {
    adelante(PWM_FULL, (PWM_FULL-30));
  }
  else if (lecturas_ult[0])
  {
    derecha(PWM_FULL, (PWM_FULL-30));
  }
  else if (lecturas_ult[4])
  {
    izquierda(PWM_FULL, (PWM_FULL-30));
  }
  else if (!lecturas_ult[2])
  {
    adelante(PWM_CHILL, (PWM_CHILL-30));
  }
}

void torero()
{
  if (!lecturas_ult[2] && !ole)
  {
    if (distancias_ult[4] > 10 && distancias_ult[4] <= 50)
    {
      adelante(PWM_FULL, (PWM_FULL-30));
      delay(500);

      adelante(PWM_FULL, 20);
      delay(600);

      ole = true;
    }
    else if (distancias_ult[0] > 10 && distancias_ult[0] <= 20)
    {
      adelante(PWM_FULL, (PWM_FULL-30));
      delay(200);

      adelante(20, (PWM_FULL-30));
      delay(600);

      ole = true;
    }
  }
  else if (distancias_ult[2] && ole)
  {
    adelante(PWM_FULL, (PWM_FULL-30));
  }
  else if (distancias_ult[4] && ole)
  {
    adelante(100, (PWM_FULL-30));
  }
  else if (distancias_ult[0] && ole)
  {
    adelante(PWM_FULL, 100);
  }
}

void tic_tac()
{
  if (!lecturas_ult[2] && !lecturas_ult[0] && !lecturas_ult[4])
  {
    if (flag_tictac == 0)
    {
      Serial.println("derecha 1");
      derecha(PWM_CHILL, (PWM_CHILL-30));

      if ((millis() - tictac_millis) >= GIRO_TICTAC)
      {
        flag_tictac = 1;
        tictac_millis = millis();
      }
    }
    else if (flag_tictac == 1)
    {
      Serial.println("izquierda 1");
      izquierda(PWM_CHILL, (PWM_CHILL-30));

      if ((millis() - tictac_millis) >= GIRO_TICTAC)
      {
        flag_tictac = 2;
        tictac_millis = millis();
      }
    }
    else if (flag_tictac == 2)
    {
      Serial.println("parado 1");
      parado();

      if ((millis() - tictac_millis) >= GIRO_TICTAC)
      {
        flag_tictac = 3;
        tictac_millis = millis();
      }
    }
    else if (flag_tictac == 3)
    {
      Serial.println("izquierda 2");
      izquierda(PWM_CHILL, (PWM_CHILL-30));

      if ((millis() - tictac_millis) >= GIRO_TICTAC)
      {
        flag_tictac = 4;
        tictac_millis = millis();
      }
    }
    else if (flag_tictac == 4)
    {
      Serial.println("derecha 2");
      derecha(PWM_CHILL, (PWM_CHILL-30));

      if ((millis() - tictac_millis) >= GIRO_TICTAC)
      {
        flag_tictac = 5;
        tictac_millis = millis();
      }
    }
    else if (flag_tictac == 5)
    {
      Serial.println("parado 2");
      parado();

      if ((millis() - tictac_millis) >= GIRO_TICTAC)
      {
        flag_tictac = 0;
        tictac_millis = millis();
      }
    }
  }
  else if (lecturas_ult[2])
  {
    adelante(PWM_FULL, (PWM_FULL-30));
  }
  else if (lecturas_ult[0])
  {
    Serial.println("girando izquierda");
    izquierda(PWM_CHILL, (PWM_CHILL-30));
  }
  else if (lecturas_ult[4])
  {
    Serial.println("grando derecha");
    derecha(PWM_CHILL, (PWM_CHILL-30));
  }
}

void radar()
{
  if (!lecturas_ult[2])
  {
    if (lecturas_ult[4])
    {
      derecha(PWM_FULL, (PWM_FULL-30));
    }
    else if (lecturas_ult[0])
    {
      izquierda(PWM_FULL, (PWM_FULL-30));
    }
    else 
    {
      parado();
    }
  }
  else if (distancias_ult[2] <= 20 && distancias_ult[2] != 0)
  {
    adelante(PWM_FULL, (PWM_FULL-30));
  }
}

void bartolito()
{
  if (!lecturas_ult[2])
  {
    derecha(PWM_FULL, (PWM_FULL-30));
  }
  else if (lecturas_ult[2])
  {
    adelante(PWM_FULL, (PWM_FULL-30));
  }
}

void pasitos()
{
  if (!lecturas_ult[0] && !lecturas_ult[2] && !lecturas_ult[4])
  {
    if (is_moving && millis() - step_millis >= 100)
    {
      //Serial.println("parado");
      parado();
      stop_millis = millis();
      is_moving = false;
    }
    else if (!is_moving && millis() - stop_millis >= 1000)
    {
      //Serial.println("pasito");
      adelante(PWM_CHILL, (PWM_CHILL-30));
      step_millis = millis();
      is_moving = true;
    }
  }
  else if (lecturas_ult[2])
  {
    //Serial.println("adelante");
    adelante(PWM_FULL, (PWM_FULL-30));
  }
  else if (lecturas_ult[0])
  {
    //Serial.println("izquierda");
    izquierda(PWM_FULL, (PWM_FULL-30));
  }
  else if (lecturas_ult[4])
  {
    //Serial.println("derecha");
    derecha(PWM_FULL, (PWM_FULL-30));
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
          //Serial.println(contador[1]);

          flag_evento[i] = true;
          flag_tipo[i] = estado_actual;
          
          if(contador[0] == 0)
          {
            if (counter_setear == 0)
            {
              counter_direccion++;
              //Serial.println(counter_direccion);
              mostrarBinario(counter_direccion);
              if (counter_direccion > 6)
              {
                counter_direccion = 0;
              }
            }
            else if (counter_setear == 1)
            {
              counter_strat++;
              //Serial.println(counter_strat);
              mostrarBinario(counter_strat);
              if (counter_strat > CANT_ESTRATEGIAS)
              {
                counter_strat = 0;
              }
            }
          }

          if (contador[1] == 0)
          {
            counter_setear++;

            if (counter_setear == 1)
            {
              mostrarBinario(0);
              //Serial.println("Setear Estrategia");
            }
            else if (counter_setear == 2)
            {
              //Serial.println("Iniciar");
              iniciar = true;
              prev_millis = millis();
            }
          }
        }
      }
    }
  }
}

void mostrarBinario(int valor) 
{

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

/*bool lectura(int trig, int echo)
{
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, trig);
  digitalWrite(LATCH, HIGH);
  delay(10);
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
  digitalWrite(LATCH, HIGH);


  tiempo_ult = pulseIn(echo, HIGH, 10000);


  distancia_ult = tiempo_ult / 59;

  if (distancia_ult < RANGO_ULT && distancia_ult != 0) 
  {
    //Serial.println("Hay algo");
    return true;
  } 
  else 
  {
    //Serial.println("No hay moros en la costa");
    return false;
  }
}*/

uint16_t distancia (int trig, int echo)
{
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, trig);
  digitalWrite(LATCH, HIGH);
  delayMicroseconds(10);
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, LSBFIRST, TRIG_L);
  digitalWrite(LATCH, HIGH);


  tiempo_ult = pulseIn(echo, HIGH, 10000);


  distancia_ult = tiempo_ult / 59;

  return distancia_ult;
}

void LecturaCNY() 
{
  for (int i = 0; i < 5; i++)
  {
    lectura_cny_izq = analogRead(CNY_IZQ);
    suma_cny_izq = suma_cny_izq + lectura_cny_izq;
  }


  for (int i = 0; i < 5; i++) 
  {
    lectura_cny_der = analogRead(CNY_DER);
    suma_cny_der = suma_cny_der + lectura_cny_der;
  }


  cny_izquierdo = suma_cny_izq / 5;
  cny_derecho = suma_cny_der / 5;

  /*Serial.println(cny_derecho);
  Serial.print('\t');
  Serial.println(cny_izquierdo);
  Serial.println();*/


  suma_cny_izq = 0;
  suma_cny_der = 0;
}


void DetectarLinea()
{
  if (lectura_cny_izq < izq_promedio) 
  {
    // Serial.println("Blanco");
    flag_cny_izq = true;
  } 
  else 
  {
    // Serial.println("Negro");
    flag_cny_izq = false;
  }


  if (lectura_cny_der < der_promedio) 
  {
    flag_cny_der = true;
  } 
  else 
  {
    flag_cny_der = false;
  }


  if (flag_cny_der && flag_cny_izq) 
  {
    flag_cny_both = true;
  } 
  else 
  {
    flag_cny_both = false;
  }
}


void parado()
{
  digitalWrite(AIN_1, LOW);
  digitalWrite(AIN_2, LOW);
 
  digitalWrite(BIN_1, LOW);
  digitalWrite(BIN_2, LOW);
}


void adelante(int pwm_a, int pwm_b)
{
  analogWrite(PWM_A, pwm_a);
  analogWrite(PWM_B, pwm_b);

  digitalWrite(AIN_1, LOW);
  digitalWrite(AIN_2, HIGH);
 
  digitalWrite(BIN_1, HIGH);
  digitalWrite(BIN_2, LOW);
}


void atras(int pwm_a, int pwm_b)
{
  analogWrite(PWM_A, pwm_a);
  analogWrite(PWM_B, pwm_b);

  digitalWrite(AIN_1, HIGH);
  digitalWrite(AIN_2, LOW);

  digitalWrite(BIN_1, LOW);
  digitalWrite(BIN_2, HIGH);
}


void derecha(int pwm_a, int pwm_b)
{
  analogWrite(PWM_A, pwm_a);
  analogWrite(PWM_B, pwm_b);

  digitalWrite(AIN_1, LOW);
  digitalWrite(AIN_2, HIGH);

  digitalWrite(BIN_1, LOW);
  digitalWrite(BIN_2, HIGH);
}


void izquierda(int pwm_a, int pwm_b)
{
  analogWrite(PWM_A, pwm_a);
  analogWrite(PWM_B, pwm_b);

  digitalWrite(AIN_1, HIGH);// izquierda atras
  digitalWrite(AIN_2, LOW); // izquierda adelante

  digitalWrite(BIN_1, HIGH); // derecha adelante
  digitalWrite(BIN_2, LOW); // derecha atras
}