#define BTN_1 5    // Pin del botón 1
#define LED_4 4    // LED conectado directamente al Arduino (pin 4)

#define DATA 11     
#define LATCH 12    
#define CLOCK 13  

uint16_t milis = 0;
uint16_t milisAnt = 0;

int x = 0;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(BTN_1, INPUT_PULLUP);  // Botón 1
  pinMode(LED_4, OUTPUT);        // LED conectado directamente al pin 4 del Arduino
  
  // Pines del shift register
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);

  // Inicializa la comunicación serial para el monitor
  Serial.begin(9600);
}

void loop() 
{

  milis = millis();

  if (digitalRead(BTN_1) == LOW)
  {
    x = 1;
    milisAnt = milis;
    Serial.println("Apretado");
    
  }

  if (x == 1 && milis - milisAnt >= 5000)
  {
    x = 0;
    digitalWrite(LED_4, HIGH);
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, 0b10000011);
    digitalWrite(LATCH, HIGH);
    Serial.println("Encendido");

    delay(5000);

    digitalWrite(LED_4, LOW);
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, 0b00000000);
    digitalWrite(LATCH, HIGH);
    Serial.println("Apagado");
  }
}
