// Prueba de Motores

// Motor Izquierdo
#define M1_B 3
#define M1_A 4
#define PWM_A 6

// Motor Derecho
#define M2_B 2
#define M2_A 7
#define PWM_B 5

void setup() {
  Serial.begin(9600);
  pinMode(M1_B, OUTPUT);
  pinMode(M1_A, OUTPUT);
  pinMode(M1_B, OUTPUT);
  pinMode(M1_A, OUTPUT);
  pinMode(PWM_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);

  analogWrite(PWM_A, 255);
  analogWrite(PWM_B, 255);
}

void loop() {

  digitalWrite(M1_B, HIGH);
  digitalWrite(M2_B, LOW);
  digitalWrite(M1_A, LOW);
  digitalWrite(M2_A, LOW);
}

void Adelante() {

  digitalWrite(M1_B, HIGH);
  digitalWrite(M2_B, LOW);
  digitalWrite(M1_A, LOW);
  digitalWrite(M2_A, HIGH);
}

void Atras() {
  digitalWrite(M1_B, LOW);
  digitalWrite(M2_B, HIGH);
  digitalWrite(M1_A, HIGH);
  digitalWrite(M2_A, LOW);
}

void Derecha() {
  digitalWrite(M1_B, HIGH);
  digitalWrite(M2_B, HIGH);
  digitalWrite(M1_A, LOW);
  digitalWrite(M2_A, LOW);
}

void Izquierda() {
  digitalWrite(M1_B, LOW); // Izquierda adelante
  digitalWrite(M2_B, LOW); // Derecha atras
  digitalWrite(M1_A, HIGH);// Izquierda atras
  digitalWrite(M2_A, HIGH); // Derecha adelante
}
