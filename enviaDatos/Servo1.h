#include <Servo.h>

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
