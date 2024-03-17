#include "task_interval.h"

void task_interval_setup() {
  pinMode(DEC_BUTTON_PORT, INPUT);
  pinMode(INC_BUTTON_PORT, INPUT);
}

void task_interval(){
  dec_button_state = digitalRead(DEC_BUTTON_PORT);
  inc_button_state = digitalRead(INC_BUTTON_PORT);

  if (dec_button_state == HIGH && prev_dec_button_state == LOW){
    if (blink_interval > MIN_BLINK_INTERVAL) { 
      blink_interval -= BLINK_INTERVAL_SIZE;
    }
    delay(200);
  }

  
  if (inc_button_state == HIGH && prev_inc_button_state == LOW){
    if (blink_interval < MAX_BLINK_INTERVAL) {
      blink_interval += BLINK_INTERVAL_SIZE;
    }
    delay(200);
  }

  prev_dec_button_state = dec_button_state;
  prev_inc_button_state = inc_button_state;
}