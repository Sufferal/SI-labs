#include "task_interval.h"

int task_interval_offset;
int task_interval_rec;

void task_interval_setup(int offset, int rec) {
  task_interval_offset = offset;
  task_interval_rec = rec;
  pinMode(DEC_BUTTON_PORT, INPUT);
  pinMode(INC_BUTTON_PORT, INPUT);
}

void task_interval_loop(void *pvParameters) {
  (void) pvParameters;

  vTaskDelay(task_interval_offset);

  for (;;) {
    dec_button_state = digitalRead(DEC_BUTTON_PORT);
    inc_button_state = digitalRead(INC_BUTTON_PORT);

    if (dec_button_state == HIGH && prev_dec_button_state == LOW){
      if (blink_interval > MIN_BLINK_INTERVAL) { 
        blink_interval -= BLINK_INTERVAL_SIZE;
      }
      delay(DELAY_TIME);
    }

    
    if (inc_button_state == HIGH && prev_inc_button_state == LOW){
      if (blink_interval < MAX_BLINK_INTERVAL) {
        blink_interval += BLINK_INTERVAL_SIZE;
      }
      delay(DELAY_TIME);
    }

    prev_dec_button_state = dec_button_state;
    prev_inc_button_state = inc_button_state;
    vTaskDelay(task_interval_rec);   
  }
}