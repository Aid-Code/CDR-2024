#define M1_AD A2
#define M1_AT A1
#define PWM_A A4

// Motor Derecho
#define M2_AD A5
#define M2_AT A0
#define PWM_B A3

void setup() 
{
  Serial.begin(9600);
  
  pinMode(M1_AD, OUTPUT);
  pinMode(M1_AT, OUTPUT);
  pinMode(M2_AD, OUTPUT); 
  pinMode(M2_AT, OUTPUT);
  pinMode(PWM_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);

  digitalWrite(PWM_A, HIGH);
  digitalWrite(PWM_B, HIGH);
}

void loop() 
{
  digitalWrite(M1_AD, LOW);
  digitalWrite(M1_AT, LOW);
  digitalWrite(M2_AD, HIGH);
  digitalWrite(M2_AT, HIGH);
}

void Adelante()
{
  digitalWrite(PWM_A, HIGH);
  digitalWrite(PWM_B, HIGH);

  digitalWrite(M1_AD, HIGH);
  digitalWrite(M1_AT, LOW);
  digitalWrite(M2_AD, HIGH);
  digitalWrite(M2_AT, LOW);
}

void Atras()
{
  digitalWrite(PWM_A, HIGH);
  digitalWrite(PWM_B, HIGH);

  digitalWrite(M1_AD, LOW);
  digitalWrite(M1_AT, HIGH);
  digitalWrite(M2_AD, LOW);
  digitalWrite(M2_AT, HIGH);
}

void Derecha()
{
  digitalWrite(PWM_A, HIGH);
  digitalWrite(PWM_B, HIGH);

  digitalWrite(M1_AD, LOW);
  digitalWrite(M1_AT, HIGH);
  digitalWrite(M2_AD, HIGH);
  digitalWrite(M2_AT, LOW);
}

void Izquierda()
{
  digitalWrite(PWM_A, HIGH);
  digitalWrite(PWM_B, HIGH);

  digitalWrite(M1_AD, HIGH);
  digitalWrite(M1_AT, LOW);
  digitalWrite(M2_AD, LOW);
  digitalWrite(M2_AT, HIGH);
}