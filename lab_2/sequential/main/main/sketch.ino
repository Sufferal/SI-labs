#include "task_push_button.h"
#include "task_blink.h"
#include "task_interval.h"
#include "task_danger.h"
#include "task_idle.h"
#include <timer-api.h>

// Execution frequency (ms)
int rec_counter = 0;
int current_iteration = 1;

void setup() {
  task_push_button_setup();
  task_blink_setup();
  task_interval_setup();
  task_danger_setup();
  task_idle_setup();
  timer_init_ISR_1KHz(TIMER_DEFAULT);
}

void loop() {
  task_idle();

  if (rec_counter == 1) {
    task_push_button();
    rec_counter = 2;
  }

  task_idle();

  if (rec_counter == 2) {
    task_blink();
    rec_counter = 3;
  }

  task_idle();

  if (rec_counter == 3) {
    task_interval();
    rec_counter = 4;
  }

  task_idle();

  if (rec_counter == 4) {
    task_danger();
  }

  rec_counter = 0;
}

void timer_handle_interrupts(int timer) {
  rec_counter++;
}

/* 
  Task time measurements: 
  Task push button: 16 µs
  Task blink:       4-8 µs
  Task interval:    12-16 µs
  Task danger:      8 µs
*/

void measure_tasks() {
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