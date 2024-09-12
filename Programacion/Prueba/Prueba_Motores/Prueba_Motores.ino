// Prueba de Motores

// Motor Izquierdo
#define M1_B 7
#define M1_A 6
#define PWM_A 5

// Motor Derecho
#define M2_B 4
#define M2_A 3
#define PWM_B 2

void setup() {
  Serial.begin(9600);

  pinMode(M1_B, OUTPUT);
  pinMode(M1_A, OUTPUT);
  pinMode(M1_B, OUTPUT);
  pinMode(M1_A, OUTPUT);
  pinMode(PWM_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);

  analogWrite(PWM_A, 30);
  analogWrite(PWM_B, 30);
}

void loop() {

  Adelante();
  delay(1000);
  Atras();
  delay(1000);
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
  digitalWrite(M1_B, LOW);
  digitalWrite(M2_B, HIGH);
  digitalWrite(M1_A, LOW);
  digitalWrite(M2_A, HIGH);
}

void Izquierda() {
  digitalWrite(M1_B, HIGH);
  digitalWrite(M2_B, LOW);
  digitalWrite(M1_A, HIGH);
  digitalWrite(M2_A, LOW);
}
