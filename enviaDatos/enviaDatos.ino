#include "humo.h"
#include "Rfid.h"
#include "fotoresistencia.h"
#include "Buzzer.h"

String cadena = "inicial";





void setup() {
  Serial.begin(9600); 
  setupBuzzer();
  // activarBuzzer();
  // setupSensorGas();
  // setupFotoresis();
  setupSensorRfid();
  
  
}

void loop() {
  if (Serial.available() > 0) {  // Verifica si hay datos disponibles
        String data = Serial.readString();  // Lee los datos recibidos
        if (data == "AL-1:0"){
          apagarBuzzer();
        }else{
          cadena = data;
          Serial.println(data);
        }
    }

  // leerHumo();
  // delay(2000);

  // leerCard();
  // delay(2000);

  // levantarServo(myServo);
  // delay(5000);

  // bajarServo(myServo);
  // delay(5000);

  // mostrarInfo(lcd, "Hola", "a todos!");
  // delay(5000);

  leerRfid(cadena);
  delay(1000);

    // checkLuz();

    

    // delay(3000);
    // Serial.println(cadena);
    // delay(3000);






}
