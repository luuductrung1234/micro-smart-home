#include "rgb_lcd.h"

rgb_lcd lcd;
const int colorR = 78;
const int colorG = 183;
const int colorB = 187;

void setupLcd() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  lcd.setRGB(colorR, colorG, colorB);
}

void writeFirstLine(String text) {
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  // print the number of seconds since reset:
  lcd.print(text);
}

void writeSecondLine(String text) {
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(text);
}



/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
