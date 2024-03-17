#include "task_idle.h"

int task_idle_offset;
int task_idle_rec;

void task_idle_setup(int offset, int rec) {
  task_idle_offset = offset;  
  task_idle_rec = rec;
  Serial.begin(BAUD_RATE);
  Serial.println("==================================================");
  Serial.println("> Green button - toggle green LED state (ON/OFF)");
  Serial.println("> Blue buttons - increment and decrement blink interval");
  Serial.println("==================================================");
  Serial.print("(Info): Current blink interval: ");
  Serial.print(blink_interval);
  Serial.print(" milliseconds.");
}

void task_idle_loop(void *pvParameters) {
  (void) pvParameters;

  vTaskDelay(task_idle_offset);
  for (;;) {
    if (prev_toggle_led_state != toggle_led_state) {
      Serial.print("\n(Status): Toggle LED state now is ");

      if(toggle_led_state) {
        Serial.print("ON.");
      } else {
        Serial.print("OFF.");
      }

      prev_toggle_led_state = toggle_led_state;
    }

    if (prev_inc_button_state_idle != inc_button_state) {
      if (inc_button_state == HIGH) {
        Serial.print("\n(Status): Increment button was pushed (+ms) ");
      }
      prev_inc_button_state_idle = inc_button_state;
    }

    if (prev_dec_button_state_idle != dec_button_state) {
      if (dec_button_state == HIGH) {
        Serial.print("\n(Status): Decrement button was pushed (-ms) ");
      }
      prev_dec_button_state_idle = dec_button_state;
    }

    if (prev_blink_interval != blink_interval) {
      Serial.print(blink_interval);
      prev_blink_interval = blink_interval;
    }

    vTaskDelay(task_idle_rec);
  }
}