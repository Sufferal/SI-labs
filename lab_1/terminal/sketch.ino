#include <stdio.h>
#include <string.h>

const int LED_PIN   = 8;
const int BAUD_RATE = 9600;
int led_state = LOW;
char command[50];

int sput(char c, __attribute__((unused)) FILE* f) {
  return !Serial.write(c);
}

void setup() {
  Serial.begin(BAUD_RATE);

  // https://forum.arduino.cc/t/printf-on-arduino/888528/3
  FILE f_out;
  // https://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html#gaf41f158c022cbb6203ccd87d27301226
  fdev_setup_stream(&f_out, sput, nullptr, _FDEV_SETUP_WRITE);
  stdout = &f_out;

  printf("================================ \n");
  printf("Commands: \n");
  printf("# led on - turns the LED on \n");
  printf("# led off - turns the LED off \n");
  printf("================================ \n");
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  memset(command, '\0', sizeof(command));
  // Wait for input
  while (Serial.available() == 0) {}
  Serial.readBytesUntil('\n', command, sizeof(command));

  if (strcmp(command, "led on") == 0) {
    if (led_state == HIGH) {
      printf("[Status]: LED is already turned on. \n");
    } else {
      printf("[Status]: LED is turning on. \n");
      digitalWrite(LED_PIN, HIGH);
      led_state = HIGH;
    }
  } else if (strcmp(command, "led off") == 0) {
    if (led_state == LOW) {
      printf("[Status]: LED is already turned off. \n");
    } else {
      printf("[Status]: LED is turning off. \n");
      digitalWrite(LED_PIN, LOW);
      led_state = LOW;
    }
  } else if (strcmp(command, "led") == 0 || strcmp(command, "help") == 0) {
      printf("Commands: \n");
      printf("# led on - turns the LED on \n");
      printf("# led off - turns the LED off \n\n");
  } else {
    printf("[Error]: Unknown command \n");
  }
}
