#include "task_push_button.h"

bool prev_toggle_button_state = LOW;
int task_push_button_offset;
int task_push_button_rec;

void task_push_button_setup(int offset, int rec) {
  task_push_button_offset = offset;
  task_push_button_rec = rec;
  pinMode(OUTPUT_PORT, OUTPUT);
  pinMode(INPUT_PORT, INPUT);
}

void task_push_button_loop(void *pvParameters) {
  (void) pvParameters;

  vTaskDelay(task_push_button_offset);

  for(;;) {
    toggle_button_state = digitalRead(INPUT_PORT);

    // Check if the button is pressed 
    // and was not pressed previously
    if (toggle_button_state == HIGH && prev_toggle_button_state == LOW) {
      toggle_led_state = !toggle_led_state;
      delay(DELAY_TIME);
    }

    digitalWrite(OUTPUT_PORT, toggle_led_state);
    prev_toggle_button_state = toggle_button_state;
    vTaskDelay(task_push_button_rec);
  }
}