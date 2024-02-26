#pragma once
#include <Arduino.h>

#define BAUD_RATE 9600

int prev_blink_interval = blink_interval;
int prev_toggle_led_state = toggle_led_state;
int prev_dec_button_state_idle = dec_button_state;
int prev_inc_button_state_idle = inc_button_state;

void task_idle_setup();
void task_idle();
