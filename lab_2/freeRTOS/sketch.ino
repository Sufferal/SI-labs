#include "task_push_button.h"
#include "task_blink.h"
#include "task_interval.h"
#include "task_idle.h"
#include <Arduino_FreeRTOS.h>

#define REC_PUSH_BUTTON 2
#define REC_BLINK       1
#define REC_INTERVAL    3
#define REC_IDLE        1

#define OFFSET_PUSH_BUTTON 3
#define OFFSET_BLINK       2
#define OFFSET_INTERVAL    6
#define OFFSET_IDLE        1

int rec_counter_push_button = OFFSET_PUSH_BUTTON;
int rec_counter_blink       = OFFSET_BLINK;
int rec_counter_interval    = OFFSET_INTERVAL;
int rec_counter_idle        = OFFSET_IDLE;

void setup() {
  task_push_button_setup (rec_counter_push_button, REC_PUSH_BUTTON);
  task_blink_setup       (rec_counter_blink,       REC_BLINK);
  task_interval_setup    (rec_counter_interval,    REC_INTERVAL);
  task_idle_setup        (rec_counter_idle,        REC_IDLE);
  
  // Name, Stack size, Priority, (0 - 3)
  xTaskCreate(task_push_button_loop, "Toggle_LED",      128, NULL, 2, NULL);
  xTaskCreate(task_blink_loop,       "Blink_LED",       128, NULL, 1, NULL);
  xTaskCreate(task_interval_loop,    "Button_Interval", 128, NULL, 2, NULL);
  xTaskCreate(task_idle_loop,        "Idle",            128, NULL, 0, NULL);
}

void loop() {}
