#pragma once
#include <Arduino.h>

#define DANGER_LED_PORT 8
extern int danger_led_state = LOW;

void task_push_button_setup();
void task_push_button();