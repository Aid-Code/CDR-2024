#define BTN_1 3 //A4
#define BTN_2 2 //A5
#define LED_1 4 //A3

#define DATA 8 //11
#define LATCH 9 //12
#define CLOCK 10 //13

int contador;
int lectura_btn_1;
int lectura_btn_2;

uint8_t primer_led = 0b00000001;
uint8_t segundo_led = 0b00000010;
uint8_t tercer_led = 0b10000000;

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
  // Enciende los LEDs conectados al shift register (usando shiftOut)
  /*digitalWrite(LATCH, LOW);                      // Prepara el registro
  shiftOut(DATA, CLOCK, LSBFIRST, primer_led);        // Envía el valor binario al shift register
  digitalWrite(LATCH, HIGH);                     // Actualiza los LEDs

  delay(1000);*/

  digitalWrite(LATCH, LOW);                      // Prepara el registro
  shiftOut(DATA, CLOCK, LSBFIRST, segundo_led);        // Envía el valor binario al shift register
  digitalWrite(LATCH, HIGH);                     // Actualiza los LEDs

  delay(1000);

  /*digitalWrite(LATCH, LOW);                      // Prepara el registro
  shiftOut(DATA, CLOCK, LSBFIRST, tercer_led);        // Envía el valor binario al shift register
  digitalWrite(LATCH, HIGH);                     // Actualiza los LEDs

  delay(1000);*/
}
