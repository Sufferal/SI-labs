#include "task_blink.h"

void task_blink_setup() {
  pinMode(BLINK_LED_PORT, OUTPUT);
}

void task_blink() {
  int current_millis = millis();

  if (!toggle_led_state) {
    if (current_millis - prev_millis >= blink_interval) {
      prev_millis = current_millis;
      digitalWrite(BLINK_LED_PORT, !digitalRead(BLINK_LED_PORT));
    }
  } else {
    digitalWrite(BLINK_LED_PORT, LOW);
  }
}