#include <Keypad.h>

const byte rows = 4;
const byte columns = 4;

char keypadArray[rows][columns] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};

byte rowPins[rows] = {14, 15, 16, 17};
byte columnPins[columns] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keypadArray), rowPins, columnPins, rows, columns);

char get_keypad_key() {
  return keypad.getKey();
}