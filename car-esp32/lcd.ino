#include <LiquidCrystal.h>  

const int contrast=150;
const int pinV0 = 11;
LiquidCrystal lcd(10, 9, 8, 7, 6, 5);   

void setupLcd() {
  analogWrite(pinV0, contrast);
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Hello World!");
    
  lcd.setCursor(0, 1);
  lcd.print("ready!");
}

void printLcd(String line1, String line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}
