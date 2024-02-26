#include "task_push_button.h"

bool prev_toggle_button_state = LOW;

void task_push_button_setup() {
  pinMode(OUTPUT_PORT, OUTPUT);
  pinMode(INPUT_PORT, INPUT);
}

void task_push_button() {
  toggle_button_state = digitalRead(INPUT_PORT);

  // Check if the button is pressed 
  // and was not pressed previously
  if (toggle_button_state == HIGH && prev_toggle_button_state == LOW) {
    toggle_led_state = !toggle_led_state;
    delay(200);
  }

  digitalWrite(OUTPUT_PORT, toggle_led_state);
  prev_toggle_button_state = toggle_button_state;
}