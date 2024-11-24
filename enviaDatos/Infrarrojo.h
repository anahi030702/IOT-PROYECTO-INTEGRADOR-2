//se agregarn los sensores como arreglos por si hay que agregar mas
const int outPins[] = {2, 3, 4};  
const int ledPins[] = {5, 6, 7};      


int lastStatus[3] = {HIGH, HIGH, HIGH};

void setup() {
  Serial.begin(9600);

  // indicar los sensores infrarrojos como entrada de datos y los leds como salida para que indiquen que estan ocupados
  for (int i = 0; i < 3; i++) {
    pinMode(outPins[i], INPUT);
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], HIGH);  // inicializar LEDs encendidos cuando el espacio esté desocupado
  }
}

void loop() {
  // leer el estado de los sensores
  for (int i = 0; i < 3; i++) {
    int sensorState = digitalRead(outPins[i]);

    // verificar si el estado del sensor ha cambiado y actuar en consecuencia
    if (sensorState != lastStatus[i]) {
      int estado = (sensorState == LOW) ? 1 : 0;

      if (estado == 1) {
        digitalWrite(ledPins[i], LOW);  // apagar el LED si está ocupado
      } else {
        digitalWrite(ledPins[i], HIGH); // encender el LED si está desocupado
      }

      lastStatus[i] = sensorState;  // actualizar el estado anterior
    }
  }

  delay(100); 
}



    
