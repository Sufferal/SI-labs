#ifndef task2_h
#define task2_h
#include <Arduino.h>

#define BLINK_LED_PORT 9

int prev_millis = 0;
extern int blink_interval = 1500;

void task_blink_setup(int offset, int rec);
void task_blink_loop(void *pvParameters);

#endif