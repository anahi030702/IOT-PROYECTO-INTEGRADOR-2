
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//CONEXION: SDA al A4 del arduino y el SCL al A5
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void bienvenida(){
  lcd.setCursor(0,0);
  lcd.print("Bienvenido");
  lcd.setCursor(0,1);
  lcd.print("a SmartPark");
}

void setupLcd(){
  lcd.init(); //para la pantalla
  lcd.backlight(); //para la pantalla
  bienvenida();
}

void mostrarInfo(String renglon1, String renglon2)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(renglon1);
  lcd.setCursor(0,1);
  lcd.print(renglon2);
  delay(3000);
  lcd.clear();
  bienvenida();
}
