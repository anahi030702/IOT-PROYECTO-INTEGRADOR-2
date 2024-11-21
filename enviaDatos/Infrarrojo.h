//se agregarn los sensores como arreglos por si hay que agregar mas
const int outPins[] = {2, 3, 4};  
const int ledPins[] = {5, 6, 7};      


int lastStatus[3] = {HIGH, HIGH, HIGH};

void setup() {
  Serial.begin(9600);

  // Indicar los sensores infrarrojos como entrada de datos y los leds como salida para que indiquen que estan ocupados
  for (int i = 0; i < 3; i++) {
    pinMode(outPins[i], INPUT);
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); // Inicializar LEDs apagados
  }
}

void loop() {
  // Leer el estado de los sensores
  for (int i = 0; i < 3; i++) {
    int sensorState = digitalRead(outPins[i]);

    // Verificar si el estado del sensor ha cambiado y actuar en consecuencia
    if (sensorState != lastStatus[i]) {
      int estado = (sensorState == LOW) ? 1 : 0; 
      // encender o apagar el LED según el estado
      digitalWrite(ledPins[i], (sensorState == LOW) ? HIGH : LOW);

      lastStatus[i] = sensorState;  // Actualizar el estado anterior
    }
  }

  delay(100);  // Pequeña espera para evitar lecturas muy rápidas
}
