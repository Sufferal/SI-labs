#include <Adafruit_LiquidCrystal.h>

const int lcd_dimensions[2] = {16, 2};

void reset_lcd() {
  lcd.clear();
  lcd.begin(lcd_dimensions[0], lcd_dimensions[1]);
  lcd.setCursor(1, 0);
  lcd.print("Enter PIN code \n");
  memset(user_input, '\0', sizeof(user_input));
  user_input_length = 0;
}
