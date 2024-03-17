#pragma once
#include <Arduino.h>

#define BLINK_LED_PORT 9

int prev_millis = 0;
extern int blink_interval = 1500;

void task_blink_setup();
void task_blink();
