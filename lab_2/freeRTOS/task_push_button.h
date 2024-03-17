#ifndef task1_h
#define task1_h
#include <Arduino.h>

#define OUTPUT_PORT 10
#define INPUT_PORT 11
#define DELAY_TIME 0

int toggle_button_state = 0;
int toggle_led_state = LOW;

void task_push_button_setup(int offset, int rec);
void task_push_button_loop(void *pvParameters);

#endif