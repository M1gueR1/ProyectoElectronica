// Pines del motor
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;
int demora = 20;

// Pines del DIP switch
int DIP_DERECHA = 2;  // DIP 1 → gira a la derecha
int DIP_IZQUIERDA = 3; // DIP 2 → gira a la izquierda

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Configurar pines del DIP switch con resistencia pull-up interna
  pinMode(DIP_DERECHA, INPUT_PULLUP);
  pinMode(DIP_IZQUIERDA, INPUT_PULLUP);
}

void loop() {
  boolean der = digitalRead(DIP_DERECHA) == LOW;    // activado si está en ON
  boolean izq = digitalRead(DIP_IZQUIERDA) == LOW;  // activado si está en ON

  if (der) {
    // Giro horario (derecha)
    for (int i = 0; i < 6; i++) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      delay(demora);

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      delay(demora);

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      delay(demora);

      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      delay(demora);
    }
  } else if (izq) {
    // Giro antihorario (izquierda) → inversa de la secuencia anterior
    for (int i = 0; i < 6; i++) {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      delay(demora);

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      delay(demora);

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      delay(demora);

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      delay(demora);
    }
  }

  // Detener motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(500);
}