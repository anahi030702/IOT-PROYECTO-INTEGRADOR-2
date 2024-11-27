#include <SPI.h>
#include <MFRC522.h>
#include "pantalla.h"
#include "servo.h"


#define RST_PIN 9  // Configurable
#define SS_PIN 10  // Configurable

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Crear instancia MFRC522
String cadena = "inicial";
int inicio = 0;
int indice = 0;


void setup() {
  Serial.begin(9600);  // Inicializar comunicación serial
  SPI.begin();         // Iniciar bus SPI
  mfrc522.PCD_Init();  // Inicializar el lector RFID
  setupLcd();
  setupServo();
}

void loop() {
   if (Serial.available() > 0) {  // Verifica si hay datos disponibles
        String data = Serial.readString();  // Lee los datos recibidos
        cadena = data;
        Serial.println(data);
  
    }


  // Verificar si hay una nueva tarjeta
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Intentar leer la tarjeta
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Crear una cadena para almacenar el UID completo
  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      uid += "0";  // Añadir un cero si es menor a 16
    }
    uid += String(mfrc522.uid.uidByte[i], HEX);  // Concatenar en hexadecimal
  }

  // Imprimir el UID en el monitor serial
  Serial.println(uid);

  checkArray(uid);

  // // Mostrar el UID en el LCD
  // lcd.clear();  // Limpiar pantalla
  // lcd.setCursor(0, 0);
  // lcd.print("No. RFID:");
  // lcd.setCursor(0, 1);
  // lcd.print(uid);

  //  Mostrar el UID en el LCD
  // lcd.clear();  // Limpiar pantalla
  // lcd.setCursor(0, 0);
  // lcd.print("Tarjeta Rfid");
  // lcd.setCursor(0, 1);
  // lcd.print("Leida y enviada");

  delay(2000);

  // lcd.clear();  // Limpiar pantalla
  // lcd.setCursor(0,0);
  // lcd.print("Acerca la");
  // lcd.setCursor(0,1);
  // lcd.print("tarjeta a leer");

  // Detener comunicación con la tarjeta
  mfrc522.PICC_HaltA();
}

void checkArray(String rfid){
      Serial.println("CHECK ARRAY 1");
  while ((indice = cadena.indexOf(',', inicio)) != -1) {
    String palabra = cadena.substring(inicio, indice); // Extraer la palabra
    Serial.println("---------------------------------------------------------------");
    Serial.println(palabra);
    Serial.println(rfid);
    if (palabra == rfid){
      mostrarInfo("Acceso", "Autorizado");
      Serial.println("OK");
      levantarServo();
      bajarServo();
    }
    inicio = indice + 1; // Mover el inicio al siguiente segmento
  }
  Serial.println("CHECK ARRAY 2");
  // Imprimir el último segmento (después de la última coma)
  String ultimaPalabra = cadena.substring(inicio);
  ultimaPalabra.trim();
    Serial.println(ultimaPalabra);
    Serial.println(rfid);
  if (ultimaPalabra == rfid){
    mostrarInfo("Acceso", "Autorizado");
    levantarServo();
    bajarServo();
    Serial.println("OKULTIMO");
    delay(2000);
   }
  else{
    mostrarInfo("Acceso", "Denegado");
  }
}

