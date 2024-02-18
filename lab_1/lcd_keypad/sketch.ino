#include <string.h>
#include <Adafruit_LiquidCrystal.h>

const int BAUD_RATE = 9600;
const int INPUT_LENGTH = 5;
const int LED_ERROR_PIN = 18;
const int LED_SUCCESS_PIN = 19;

// LCD
const int RS = 12, ENABLE = 11, D4 = 9, D5 = 8, D6 = 7, D7 = 6;
Adafruit_LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7); 

// User input
char user_input[INPUT_LENGTH];
int user_input_length = 0;

// Keypad
char backspace_key = '#';
char enter_key = 'D';
char pin_code[] = "1010";

void setup() {
  pinMode(LED_SUCCESS_PIN, OUTPUT);
  pinMode(LED_ERROR_PIN, OUTPUT);

  Serial.begin(BAUD_RATE);

  Serial.println("================================");
  Serial.println("Enter the PIN code by pressing the characters on the keypad.");
  Serial.println("> D - try pin code");
  Serial.println("> # - delete a character");
  Serial.println("================================");

  reset_lcd();
}

void loop() {
  char current_key = get_keypad_key();
  lcd.setCursor(user_input_length + 6, 1);

  if (current_key && user_input_length < INPUT_LENGTH - 1 
      && current_key != enter_key 
      && current_key != backspace_key) {
    user_input[user_input_length] = current_key;
    user_input_length++;
    lcd.print(current_key);
  } 
  
  else if (current_key == enter_key){
    user_input[user_input_length] = '\0';
    Serial.println("User PIN code try: " + String(user_input));

    if (user_input_length == 0) {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("No empty PIN");
      Serial.println("(Status): Please enter characters.");
    } else if (strcmp(user_input, pin_code) != 0) {
      digitalWrite(LED_ERROR_PIN, HIGH);
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Invalid PIN.");
      Serial.println("(Status): Invalid PIN, please try again.");
    } else {
      digitalWrite(LED_SUCCESS_PIN, HIGH);
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("You're in.");
      Serial.println("(Status): Valid PIN, you're in.");
    }

    delay(1500);
    reset_lcd();
    digitalWrite(LED_ERROR_PIN, LOW);
    digitalWrite(LED_SUCCESS_PIN, LOW);
  } 
  
  else if (current_key == backspace_key && user_input_length > 0) {
    user_input_length--;
    user_input[user_input_length] = '\0';
    lcd.setCursor(user_input_length + 6, 1);
    lcd.print(' ');
    lcd.setCursor(user_input_length + 6, 1);
  }
}