#include "humo.h"
#include "Rfid.h"
#include "Buzzer.h"
#include "Servo1.h"
#include "pantalla.h"
#include "fotoresistencia.h"

Servo myServo;  // Crea un objeto Servo
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
MFRC522 rfid(SS_PIN, RST_PIN); // Instancia de la clase



void setup() {
  Serial.begin(9600); 

  // pinMode(3, OUTPUT); //para la fotoresistencia
  // pinMode(9, OUTPUT);  //para el buzzer 
  myServo.attach(9);  // Conecta el servo al pin 9
  myServo.write(0);   // Coloca el servo en 0°
  // lcd.init(); //para la pantalla
  // lcd.backlight(); //para la pantalla
  // SPI.begin(); // Init SPI bus
  // rfid.PCD_Init(); // para el RFID
}

void loop() {
  leerHumo();
  delay(2000);

  // leerCard();
  // delay(2000);

  // activarBuzzer();
  // apagarBuzzer();

  // levantarServo(myServo);
  // delay(5000);

  // bajarServo(myServo);
  // delay(5000);

  // mostrarInfo(lcd, "Hola", "a todos!");
  // delay(5000);

  // leerRfid(rfid);
  // delay(1000);

    // checkLuz();







}
