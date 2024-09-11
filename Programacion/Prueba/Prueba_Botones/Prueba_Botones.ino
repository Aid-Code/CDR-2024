#define BTN_1 3 //A4
#define BTN_2 2 //A5
#define LED_1 4 //A3

#define DATA 8 //11
#define LATCH 9 //12
#define CLOCK 10 //13

int contador;
int lectura_btn_1;
int lectura_btn_2;

void setup() 
{
  Serial.begin(9600);

  pinMode(BTN_1, INPUT_PULLUP);
  pinMode(BTN_2, INPUT_PULLUP);

  pinMode(LED_1, OUTPUT);

  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
}

void loop() 
{
  uint8_t datos = 0b11000001;
  
  lectura_btn_1 = digitalRead(BTN_1);
  lectura_btn_2 = digitalRead(BTN_2);

  //digitalWrite(LED_1, HIGH);
  
  // Enciende los LEDs conectados al shift register (usando shiftOut)
  digitalWrite(LATCH, LOW);                      // Prepara el registro
  shiftOut(DATA, CLOCK, LSBFIRST, datos);        // Envía el valor binario al shift register
  digitalWrite(LATCH, HIGH);                     // Actualiza los LEDs
}
