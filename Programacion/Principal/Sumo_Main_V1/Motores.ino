// Código Motores

void Adelante()
{
  digitalWrite(M1_B, HIGH);
  digitalWrite(M1_A, LOW);
  digitalWrite(M2_B, HIGH);
  digitalWrite(M2_A, LOW);
}

void Atras()
{
  digitalWrite(M1_B, LOW);
  digitalWrite(M1_A, HIGH);
  digitalWrite(M2_B, LOW);
  digitalWrite(M2_A, HIGH);
}

void Derecha()
{
  digitalWrite(M1_B, LOW);
  digitalWrite(M1_A, HIGH);
  digitalWrite(M2_B, HIGH);
  digitalWrite(M2_A, LOW);
}

void Izquierda()
{
  digitalWrite(M1_B, HIGH);
  digitalWrite(M1_A, LOW);
  digitalWrite(M2_B, LOW);
  digitalWrite(M2_A, HIGH);
}