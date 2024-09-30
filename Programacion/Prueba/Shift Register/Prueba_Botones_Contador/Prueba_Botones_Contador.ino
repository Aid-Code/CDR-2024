#define BTN_1 A4    // Pin del botón 1
#define LED_4 A3    // LED conectado directamente al Arduino (pin 4)

#define LED_1 0b00000001
#define LED_2 0b10000000
#define LED_3 0b00000010

#define DATA 11     
#define LATCH 12    
#define CLOCK 13   

int contador = 0;     // Inicializa el contador en 0
int estadoAnterior = HIGH;  // Estado previo del botón

void setup() {
  // Configuración de los pines
  pinMode(BTN_1, INPUT_PULLUP);  // Botón 1
  pinMode(LED_4, OUTPUT);        // LED conectado directamente al pin 4 del Arduino
  
  // Pines del shift register
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);

  // Inicializa la comunicación serial para el monitor
  Serial.begin(9600);
}

void loop() {

  
  int estadoBoton = digitalRead(BTN_1);  // Lee el estado del botón

  // Si se presiona el botón y el estado cambia
  if (estadoBoton == LOW && estadoAnterior == HIGH) {
    contador++;  // Incrementa el contador
    if (contador > 15) {
      contador = 0;  // Reinicia el contador si supera 15
    }

    // Muestra el valor binario de los LEDs en el monitor serial
    Serial.print("Contador: ");
    Serial.println(contador);
    
    mostrarBinario(contador);
  }

  estadoAnterior = estadoBoton;  // Actualiza el estado previo del botón

  delay(200);  // Pequeño retardo para evitar rebotes
}

// Función para encender los LEDs según el valor en binario
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
  Serial.print("Estado de los LEDs: ");
  Serial.print(estadoLED4 ? "1" : "0");       // LED 4 (pin 4)
  Serial.print((valor & 0b0100) ? "1" : "0");  // Q6 (LED 3)
  Serial.print((valor & 0b0010) ? "1" : "0");  // Q0 (LED 2)
  Serial.print((valor & 0b0001) ? "1" : "0");  // Q7 (LED 1)
  
  
 
  Serial.println();  // Nueva línea
}
