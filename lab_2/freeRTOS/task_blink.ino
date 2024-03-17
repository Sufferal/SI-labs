#include "task_blink.h"

int task_blink_offset;
int task_blink_rec;

void task_blink_setup(int offset, int rec) {
  task_blink_offset = offset;
  task_blink_rec = rec;
  pinMode(BLINK_LED_PORT, OUTPUT);
}

void task_blink_loop(void *pvParameters) {
  (void) pvParameters;

  vTaskDelay(task_blink_offset);
  for (;;) {
    int current_millis = millis();

    if (!toggle_led_state) {
      if (current_millis - prev_millis >= blink_interval) {
        prev_millis = current_millis;
        digitalWrite(BLINK_LED_PORT, !digitalRead(BLINK_LED_PORT));
      }
    } else {
      digitalWrite(BLINK_LED_PORT, LOW);
    }
    vTaskDelay(task_blink_rec);
  }
}