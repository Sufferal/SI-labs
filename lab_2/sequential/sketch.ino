#include "task_push_button.h"
#include "task_blink.h"
#include "task_interval.h"
#include "task_idle.h"
#include "task_danger.h"

void setup() {
  task_push_button_setup();
  task_blink_setup();
  task_interval_setup();
  task_idle_setup();
  task_danger_setup();
}

void loop() {
  task_push_button();
  task_blink();
  task_interval();
  task_idle();
  task_danger();
}