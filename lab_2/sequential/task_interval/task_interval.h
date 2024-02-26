#pragma once
#include <Arduino.h>

#define DEC_BUTTON_PORT 12
#define INC_BUTTON_PORT 13
#define BLINK_INTERVAL_SIZE 500
#define MIN_BLINK_INTERVAL 0
#define MAX_BLINK_INTERVAL 10000

int dec_button_state = LOW;
int inc_button_state = LOW;
int prev_dec_button_state = LOW; 
int prev_inc_button_state = LOW;

void task_interval_setup();
void task_interval();
