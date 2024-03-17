#include "task_push_button.h"

void task_danger_setup() {
  pinMode(DANGER_LED_PORT, OUTPUT);
}

void task_danger() {
  if (blink_interval == MIN_BLINK_INTERVAL || blink_interval == MAX_BLINK_INTERVAL) {
    danger_led_state = HIGH;
    delay(200);
  } else {
    danger_led_state = LOW;
  }

  digitalWrite(DANGER_LED_PORT, danger_led_state);
}