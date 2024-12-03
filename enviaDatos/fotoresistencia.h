
// CONEXION: la fotorsistencia una pata(cualquiera) conectada al 5V y la otra al A0, ahi mismo se conecta una resistencia de 10K ohms y ahi mismo debe salir
// un cable hacia el ground del arduino. Despues el led conectamos el catodo al ground y el anodo a un resistencia de 220 ohms y despues de esa resistencia 
// a una salida digital

void setupFotoresis(){
  pinMode(3, OUTPUT); //para la fotoresistencia
}
void checkLuz() {
  int ldrValue = analogRead(A0); // Leer el valor de la LDR
  // Serial.println(ldrValue);          // Mostrar el valor en el monitor serial
  
  if (ldrValue < 10) {
    digitalWrite(3, HIGH); // Encender el LED si hay poca luz
  } else {
    digitalWrite(3, LOW);  // Apagar el LED si hay suficiente luz
  }
  
  delay(100); // Pequeña pausa para estabilidad
}