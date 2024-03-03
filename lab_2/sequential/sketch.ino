#include "task_push_button.h"
#include "task_blink.h"
#include "task_interval.h"
#include "task_danger.h"
#include "task_idle.h"
#include <timer-api.h>

/* 
  Task time measurements: 
  Task push button: 16 µs
  Task blink:       4-8 µs
  Task interval:    12-16 µs
  Task danger:      8 µs
*/

// Execution frequency (ms)
#define REC_TASK_PUSH     2
#define REC_TASK_BLINK    1
#define REC_TASK_INTERVAL 3
#define REC_TASK_DANGER   3

#define OFFSET_TASK_PUSH     2
#define OFFSET_TASK_BLINK    1
#define OFFSET_TASK_INTERVAL 3
#define OFFSET_TASK_DANGER   6

int rec_counter_push     = OFFSET_TASK_PUSH;
int rec_counter_blink    = OFFSET_TASK_BLINK;
int rec_counter_interval = OFFSET_TASK_INTERVAL;
int rec_counter_danger   = OFFSET_TASK_DANGER;

int current_iteration = 1;

void setup() {
  task_push_button_setup();
  task_blink_setup();
  task_interval_setup();
  task_idle_setup();
  task_danger_setup();
  timer_init_ISR_1KHz(TIMER_DEFAULT);
}

void loop() {
  task_idle();
}

void timer_handle_interrupts(int timer) {
  if (--rec_counter_push <= 0) {
    task_push_button();
    rec_counter_push = REC_TASK_PUSH;
  }

  if (--rec_counter_blink <= 0) {
    task_blink();
    rec_counter_blink = REC_TASK_BLINK;
  }

  if (--rec_counter_interval <= 0) {
    task_interval();
    rec_counter_interval = REC_TASK_INTERVAL;
  }

  if (--rec_counter_danger <= 0) {
    task_danger();
    rec_counter_danger = OFFSET_TASK_DANGER;
  }
}

void time_per_task() {
  unsigned long start, stop;

  Serial.println("\nIteration: " + String(current_iteration));
  
  // Task Push Button
  start = micros();
  task_push_button();
  stop = micros();
  Serial.print("Task Push Button duration: ");
  Serial.print(stop - start);
  Serial.print(" µs.");

  // Task Blink
  start = micros();
  task_blink();
  stop = micros();
  Serial.print("\nTask Blink duration: ");
  Serial.print(stop - start);
  Serial.print(" µs.");

  // Task Interval
  start = micros();
  task_interval();
  stop = micros();
  Serial.print("\nTask Interval duration: ");
  Serial.print(stop - start);
  Serial.print(" µs.");

    // Task Danger
  start = micros();
  task_danger();
  stop = micros();
  Serial.print("\nTask Danger duration: ");
  Serial.print(stop - start);
  Serial.print(" µs.\n");

  current_iteration++;
}