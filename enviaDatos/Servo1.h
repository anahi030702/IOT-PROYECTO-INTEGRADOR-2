#include <Servo.h>

// CONEXION: el servo tiene 3 cables, naranja que es el de datos y se conecta a un digital, rojo que es el de alimentacion va al 5V y el cafe que va al ground

void levantarServo(Servo &myServo) {
  myServo.write(90);  
  Serial.println("levantado");
  delay(1000);        

}

void bajarServo(Servo &myServo){
  myServo.write(0);  
  Serial.println("bajado");
  delay(1000);        
}
