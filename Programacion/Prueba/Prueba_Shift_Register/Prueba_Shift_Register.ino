#define BTN_1 3 //A4
#define BTN_2 2 //A5
#define LED_1 4 //A3

#define DATA 11
#define LATCH 12
#define CLOCK 13

uint8_t primer_led = 0b00000001;
uint8_t segundo_led = 0b00000010;
uint8_t tercer_led = 0b10000000;

void setup() 
{
  Serial.begin(9600);

  pinMode(LED_1, OUTPUT);

  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
}

void loop() 
{
  // Enciende los LEDs conectados al shift register (usando shiftOut)
  digitalWrite(LATCH, LOW);                      // Prepara el registro
  shiftOut(DATA, CLOCK, LSBFIRST, 0b00000010);        // Envía el valor binario al shift register
  digitalWrite(LATCH, HIGH);                     // Actualiza los LEDs

  delay(1000);

  /*digitalWrite(LATCH, LOW);                      // Prepara el registro
  shiftOut(DATA, CLOCK, LSBFIRST, segundo_led);        // Envía el valor binario al shift register
  digitalWrite(LATCH, HIGH);                     // Actualiza los LEDs

  delay(1000);*/

  /*digitalWrite(LATCH, LOW);                      // Prepara el registro
  shiftOut(DATA, CLOCK, LSBFIRST, tercer_led);        // Envía el valor binario al shift register
  digitalWrite(LATCH, HIGH);                     // Actualiza los LEDs

  delay(1000);*/
}
