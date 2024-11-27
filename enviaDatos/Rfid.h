/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read new NUID from a PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * Example sketch/program showing how to the read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
 * Reader on the Arduino SPI interface.
 * 
 * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
 * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
 * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
 * will show the type, and the NUID if a new card has been detected. Note: you may see "Timeout in communication" messages
 * when removing the PICC from reading distance too early.
 * 
 * @license Released into the public domain.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 * More pin layouts for other boards can be found here: https://github.com/miguelbalboa/rfid#pin-layout
 */

#include <SPI.h>
#include <MFRC522.h>
#include "Servo1.h"
#include "pantalla.h"

#define RST_PIN 9  // Configurable
#define SS_PIN 10  // Configurable

int inicio = 0;
int indice = 0;
int bandera = 0;


MFRC522 mfrc522(SS_PIN, RST_PIN);  // Crear instancia MFRC522

void setupSensorRfid() {
  SPI.begin();         
  mfrc522.PCD_Init();  
  setupLcd();
  setupServo();
}

void checkArray(String rfid, String cadena){
  inicio = 0;  
  bandera = 0; 
  cadena.trim();
  rfid.trim();
  while ((indice = cadena.indexOf(',', inicio)) != -1) {
    String palabra = cadena.substring(inicio, indice); // Extraer la palabra
    palabra.trim();
    if (palabra == rfid){
      Serial.println(palabra);
      mostrarInfo("Acceso", "Autorizado");
      levantarServo();
      bajarServo();
      bandera = 1;
      break;
    }
    inicio = indice + 1; // Mover el inicio al siguiente segmento
  }

  if (bandera == 0){
      mostrarInfo("Acceso", "Denegado");
  }
}

void leerRfid(String cadena) {  
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

  checkArray(uid, cadena);  
  
  // Detener comunicación con la tarjeta
  mfrc522.PICC_HaltA();
}



