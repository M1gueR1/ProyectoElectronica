#include <Arduino.h>
#include <TM1637Display.h>

// ==================== Pines del motor ====================
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;
int demora = 20;

// ==================== Pines de los botones ====================
int BOTON_DERECHA = 2;  // Pulsador conectado a pin 2 y GND
int BOTON_IZQUIERDA = 3; // Pulsador conectado a pin 3 y GND

// ==================== Display TM1637 ====================
#define CLK 5
#define DIO 6
TM1637Display display(CLK, DIO);

// ==================== Variables globales ====================
int contador = 90; // inicia en 90
uint8_t data[] = {0x0, 0x0, 0x0, 0x0}; // buffer de segmentos

// ===========================================================
void setup() {
  // Pines del motor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Botones con resistencia pull-up
  pinMode(BOTON_DERECHA, INPUT_PULLUP);
  pinMode(BOTON_IZQUIERDA, INPUT_PULLUP);

  // Display
  display.setBrightness(0x0f);
  display.setSegments(data);
  display.showNumberDec(contador); // mostrar 90 al inicio
}

// ===========================================================
// Funciones de giro del motor
void girarDerecha() {
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
  // detener motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void girarIzquierda() {
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
  // detener motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// ===========================================================
void loop() {
  boolean der = digitalRead(BOTON_DERECHA) == LOW;
  boolean izq = digitalRead(BOTON_IZQUIERDA) == LOW;

  if (der) {
    delay(50); // debounce
    if (digitalRead(BOTON_DERECHA) == LOW) {
      contador++;
      if (contador > 9999) contador = 9999; // límite por el display
      display.showNumberDec(contador);
      girarDerecha();
      delay(200); // evita múltiples lecturas
    }
  }

  if (izq) {
    delay(50); // debounce
    if (digitalRead(BOTON_IZQUIERDA) == LOW) {
      contador--;
      if (contador < 0) contador = 0; // límite inferior
      display.showNumberDec(contador);
      girarIzquierda();
      delay(200);
    }
  }
}
