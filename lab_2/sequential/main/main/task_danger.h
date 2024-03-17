#pragma once
#include <Arduino.h>

#define DANGER_LED_PORT 8
extern int danger_led_state = LOW;

void task_danger_setup();
void task_danger();