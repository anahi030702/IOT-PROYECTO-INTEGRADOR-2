
const int MQ2_PIN = A0;  // Pin analógico donde está conectado el MQ-2

void leerHumo() {
  // int sensorValue = analogRead(MQ2_PIN);  
  // Serial.print("MQ-1:" + String(sensorValue) + ":MQ-2:" + String(sensorValue));

  Serial.println("MQ-2:35");
  delay(2000);
  Serial.println("HU-1:45");
  delay(2000);
  Serial.println("PO-1:55");
  delay(2000);
  Serial.println("RF-1:553 532 532 532");


}
