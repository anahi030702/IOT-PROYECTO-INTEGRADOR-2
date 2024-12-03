// #include "Buzzer.h"

// const int MQ2_PIN = A0;  // Pin analógico donde está conectado el MQ-2
// const int POWER_PIN = 7; // Pin digital que controlará la alimentación del sensor

void setupSensorGas() {
  // pinMode(POWER_PIN, OUTPUT);
  // digitalWrite(POWER_PIN, HIGH); // Encender el sensor
  // setupBuzzer();
}

// void reiniciarSensor() {
//   Serial.println("Reiniciando sensor...");
//   digitalWrite(POWER_PIN, LOW);  // Apagar el sensor
//   delay(300000);                   // Esperar un segundo
//   digitalWrite(POWER_PIN, HIGH); // Encender el sensor
//   delay(300000);                   // Esperar que el sensor se estabilice
// }

void leerHumo() {
  int sensorValue = 126;
  // int sensorValue = analogRead(MQ2_PIN);  
  // Serial.println(sensorValue);

  if (sensorValue >= 125) {
    // reiniciarSensor();
    // activarBuzzer();
    // apagarBuzzer();

  }

  // Serial.println("MQ-2:35");
  // delay(2000);
  // Serial.println("HU-1:45");
  // delay(2000);
  // Serial.println("PO-1:55");
  // delay(2000);
  // Serial.println("RF-1:553 532 532 532");


}
