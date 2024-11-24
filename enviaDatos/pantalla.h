
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//CONEXION: SDA al A4 del arduino y el SCL al A5

void mostrarInfo(LiquidCrystal_I2C &lcd, String renglon1, String renglon2)
{
  lcd.setCursor(0,0);
  lcd.print(renglon1);
  lcd.setCursor(0,1);
  lcd.print(renglon2);
}