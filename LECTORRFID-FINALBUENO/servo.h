#include <Servo.h>

Servo myServo;  // Crea un objeto Servo

// CONEXION: el servo tiene 3 cables, naranja que es el de datos y se conecta a un digital, rojo que es el de alimentacion va al 5V y el cafe que va al ground
void setupServo(){
  myServo.attach(3);  // Conecta el servo al pin 9
  myServo.write(0);   // Coloca el servo en 0°
}

void levantarServo() {
  myServo.write(90);  
  // Serial.println("levantado");
  delay(5000);        

}

void bajarServo(){
  myServo.write(0);  
  // Serial.println("bajado");
  delay(1000);        
}