#include "task_idle.h"

void task_idle_setup() {
  Serial.begin(BAUD_RATE);
  Serial.println("==================================================");
  Serial.println("> Green button - toggle green LED state (ON/OFF)");
  Serial.println("> Blue buttons - increment and decrement blink interval");
  Serial.println("==================================================");
  Serial.print("(Info): Current blink interval: ");
  Serial.print(blink_interval);
  Serial.print(" milliseconds.");
}

void task_idle() {
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
      Serial.print("\n(Status): Increment button was pushed.");
    }
    prev_inc_button_state_idle = inc_button_state;
  }

  if (prev_dec_button_state_idle != dec_button_state) {
    if (dec_button_state == HIGH) {
      Serial.print("\n(Status): Decrement button was pushed.");
    }
    prev_dec_button_state_idle = dec_button_state;
  }

  if (prev_blink_interval != blink_interval) {
    Serial.print("\n(Status): Blink interval was updated to: ");
    Serial.print(blink_interval);
    Serial.print(" milliseconds.");
    prev_blink_interval = blink_interval;
  }
}