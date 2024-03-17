#pragma once
#include <Arduino.h>

#define OUTPUT_PORT 10
#define INPUT_PORT 11

int toggle_button_state = 0;
int toggle_led_state = LOW;

void task_push_button_setup();
void task_push_button();