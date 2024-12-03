void setupBuzzer(){
  pinMode(6, OUTPUT);  // Configura el pin 6 como salida
  digitalWrite(6, LOW);  // Asegúrate de que comience apagado
}

void activarBuzzer(){
  digitalWrite(6, HIGH);   
  Serial.println("AL-1:1");
  delay(5000);               
}

void apagarBuzzer(){
  digitalWrite(6, LOW);    // poner el Pin en LOW
  delay(5000);  
}