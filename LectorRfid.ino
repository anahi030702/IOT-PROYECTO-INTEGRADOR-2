//  * Typical pin layout used:
//  * -----------------------------------------------------------------------------------------
//  *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
//  *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
//  * Signal      Pin          Pin           Pin       Pin        Pin              Pin
//  * -----------------------------------------------------------------------------------------
//  * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
//  * SPI SS      SDA(SS)      10            53        D10        10               10
//  * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
//  * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
//  * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
//  *
//  * More pin layouts for other boards can be found here: https://github.com/miguelbalboa/rfid#pin-layout
//  */

#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define RST_PIN 9  // Configurable
#define SS_PIN 10  // Configurable

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Crear instancia MFRC522
LiquidCrystal_I2C lcd(0x27,16,2);  // Dirección I2C para pantalla de 16x2

void setup() {
  Serial.begin(9600);  // Inicializar comunicación serial
  SPI.begin();         // Iniciar bus SPI
  mfrc522.PCD_Init();  // Inicializar el lector RFID
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Acerca la");
  lcd.setCursor(0,1);
  lcd.print("tarjeta a leer");
}

void loop() {
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

  // Mostrar el UID en el LCD
  lcd.clear();  // Limpiar pantalla
  lcd.setCursor(0, 0);
  lcd.print("No. RFID:");
  lcd.setCursor(0, 1);
  lcd.print(uid);

  //  Mostrar el UID en el LCD
  // lcd.clear();  // Limpiar pantalla
  // lcd.setCursor(0, 0);
  // lcd.print("Tarjeta Rfid");
  // lcd.setCursor(0, 1);
  // lcd.print("Leida y enviada");

  delay(2000);

  lcd.clear();  // Limpiar pantalla
  lcd.setCursor(0,0);
  lcd.print("Acerca la");
  lcd.setCursor(0,1);
  lcd.print("tarjeta a leer");

  // Detener comunicación con la tarjeta
  mfrc522.PICC_HaltA();
}

