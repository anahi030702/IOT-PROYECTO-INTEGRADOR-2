
 
void activarBuzzer(){
  digitalWrite(9, HIGH);   
  Serial.println("Encendido");
  delay(5000);               
}

void apagarBuzzer(){
  digitalWrite(9, LOW);    // poner el Pin en LOW
  Serial.println("Apagado");
  delay(5000);  
}