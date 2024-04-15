#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define RELAY_PIN 13
#define BAUD_RATE 9600
#define LCD_COLS 16
#define LCD_ROWS 2 
#define LCD_ADDRESS 32
#define enA 10
#define in1 7
#define in2 6
const int defaultSpeed = 255;
const int minSpeed = -100;
const int linkSpeed = 0;
const int maxSpeed = 100;

class LCD {
  private:
    LiquidCrystal_I2C lcd;
  public:
    LCD(int address, int cols, int rows) : lcd(address, cols, rows) {}

  void init() {
    lcd.begin(LCD_COLS, LCD_ROWS);
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Enter command");
    lcd.setCursor(4, 1);
    lcd.print("or speed");
  }
  
  void print(String message, int col, int row) {
    lcd.setCursor(col, row);
    lcd.print(message);
  }
  
  void clear() {
    lcd.clear();
  }
};

class Relay {
  private:
    int pin;
  public:
    Relay(int pinNumber) : pin(pinNumber) {}

  void init() {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW); 
  }

  void setState(bool state) {
    digitalWrite(pin, state ? HIGH : LOW);
  }
};

class MotorController {
private:
  int enablePin;
  int directionPin1;
  int directionPin2;
public:
  MotorController(int enA_pin, int in1_pin, int in2_pin) : 
    enablePin(enA_pin), directionPin1(in1_pin), directionPin2(in2_pin) {}

  void init() {
    pinMode(enablePin, OUTPUT);
    pinMode(directionPin1, OUTPUT);
    pinMode(directionPin2, OUTPUT);
    digitalWrite(enablePin, LOW); 
  }

  void setSpeed(int speed) {
    int mappedSpeed = map(speed, minSpeed, maxSpeed, 0, defaultSpeed);
    if (speed >= linkSpeed) {
      analogWrite(enablePin, mappedSpeed);
      digitalWrite(directionPin1, HIGH);
      digitalWrite(directionPin2, LOW);
    } else {
      analogWrite(enablePin, mappedSpeed);
      digitalWrite(directionPin1, LOW);
      digitalWrite(directionPin2, HIGH);
    }
  }
};

String input;
LCD lcd_tmp(LCD_ADDRESS, LCD_COLS, LCD_ROWS);
Relay relay(RELAY_PIN);
MotorController motor(enA, in1, in2);

void setup() {
  Serial.begin(BAUD_RATE);
  lcd_tmp.init();
  relay.init(); 
  motor.init();
}

void loop() {
  
  if (Serial.available() > 0) {
    input = Serial.readString();

    if(input == "ON" || input == "on") {
      Serial.println("(Status): The relay is turned on.");
      relay.setState(true); 
      lcd_tmp.clear();
      lcd_tmp.print("The light bulb", 1, 0);
      lcd_tmp.print(">>> is on! <<<", 1, 1);
      return;
    } else if (input == "OFF" || input == "off") {
      Serial.println("(Status): The relay is turned off.");
      relay.setState(false); 
      lcd_tmp.clear();
      lcd_tmp.print("The light bulb", 1, 0);
      lcd_tmp.print(">>> is off <<<", 1, 1);
      return;
    } 
    
    int speed = input.toInt();
    
    if (speed >= minSpeed && speed <= maxSpeed) {
      motor.setSpeed(speed);
      lcd_tmp.clear();
      lcd_tmp.print("Speed set to", 2, 0);
      lcd_tmp.print(String(speed), 6, 1);
      lcd_tmp.print("%", 9, 1);
      delay(3000);
      return;
    } else {
      lcd_tmp.clear();
      lcd_tmp.print("Invalid speed!", 1, 0);
      lcd_tmp.print("> Out of range <", 0, 1);
      delay(3000);
      return;
    }
  }
}
