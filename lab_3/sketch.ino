#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdio_init.h"

// Pins
#define TRIG_PIN 9
#define ECHO_PIN 8
#define TEMP_PIN A0
#define BUFF_SIZE 5

// Should match the Beta Coefficient of the thermistor
const float BETA = 3950;
char output_str[10];
int temp_pos = 0, dist_pos = 0, temp_analog_value;
float celsius, salt_pepper_result, weighted_average_result, weighted_num, weighted_den;
float temp_arr[BUFF_SIZE], temp_arr_copy[BUFF_SIZE], weights[BUFF_SIZE],
      dist_arr[BUFF_SIZE], dist_arr_copy[BUFF_SIZE];

int duration;
char distance_str[10];

void setup() {
  stdio_init_all();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  set_weights();
  printf("%s\n", "===== Sensors: Temperature and Distance =====");
  printf("%s", "(Array) Weights: ");
  for (int i = 0; i < BUFF_SIZE; i++) {
    dtostrf(weights[i], 2, 2, output_str);
    printf("%s, ", output_str);
  }
}

void loop() {  
  display_temperature();
  display_distance();
  delay(1000);
}

void display_temperature() {
  printf("%s\n", "===== Temperature =====");

  temp_analog_value = analogRead(TEMP_PIN);
  printf("%s", "(Analog) Temperature: ");
  dtostrf(temp_analog_value, 4, 2, output_str);
  printf("%s\n", output_str);

  // Analog to °C
  celsius = 1 / (log(1 / (1023. / temp_analog_value - 1)) / BETA + 1.0 / 298.15) - 273.15;
  printf("%s", "(Physical) Temperature: ");
  // dtostrf(float_value, min_width, num_digits_after_decimal, where_to_store_string)
  dtostrf(celsius, 4, 2, output_str);
  printf("%s °C\n", output_str);

  // Salt and pepper
  salt_pepper_result = salt_pepper_filter_temp();
  printf("%s", "\n(Salt and pepper) Temperature: ");
  dtostrf(salt_pepper_result, 4, 2, output_str);
  printf("%s °C\n", output_str);

  // Weighted average filter
  weighted_average_result = weighted_average_filter(temp_arr);
  printf("%s", "(Weighted average filter) Temperature: ");
  dtostrf(weighted_average_result, 4, 2, output_str);
  printf("%s °C\n", output_str);
}

void display_distance() {
  printf("%s\n", "===== Distance =====");

  // Start a new measurement:
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Count the time it stays high (pulse length). 
  // The length of the ECHO high pulse is proportional to the distance.
  // Then convert pulse length in microseconds into centimeters / inches.
  duration = pulseIn(ECHO_PIN, HIGH);
  printf("%s", "(Digital) Duration: ");
  dtostrf(duration, 4, 2, distance_str);
  printf("%s µs\n", distance_str);

  printf("%s", "(Physical) Distance: ");
  dtostrf(duration / 58, 4, 2, distance_str);
  printf("%s cm, ", distance_str);
  dtostrf(duration / 148, 4, 2, distance_str);
  printf("%s in\n", distance_str);

  // Salt and pepper
  salt_pepper_result = salt_pepper_filter_dist();
  printf("%s", "\n(Salt and pepper) Distance: ");
  dtostrf(salt_pepper_result, 4, 2, output_str);
  printf("%s cm\n", output_str);

  // Weighted average filter
  weighted_average_result = weighted_average_filter(dist_arr);
  printf("%s", "(Weighted average filter) Distance: ");
  dtostrf(weighted_average_result, 4, 2, output_str);
  printf("%s cm\n\n", output_str);
}

float salt_pepper_filter_temp() {
  // Reset the index
  if (temp_pos > BUFF_SIZE) {
    temp_pos = 0;
  }
  temp_arr[temp_pos] = celsius;
  temp_pos++;

  // Copy the original array
  memcpy(temp_arr_copy, temp_arr, sizeof(temp_arr));
  // Sort the copied array
  qsort(temp_arr_copy, BUFF_SIZE, sizeof(float), compare_float);

  printf("%s", "(Array) Sorted Temperatures: ");
  for (int i = 0; i < BUFF_SIZE; i++) {
    dtostrf(temp_arr_copy[i], 4, 2, output_str);
    printf("%s°C, ", output_str);
  }

  return temp_arr_copy[BUFF_SIZE - 3];
}

float weighted_average_filter(float arr[]) {
  weighted_num = 0;

  for (int i = 0; i < BUFF_SIZE; i++) {
    weighted_num += arr[i] * weights[i];
  }

  return weighted_num / weighted_den;
}

void set_weights() {
  for (int i = 0; i < BUFF_SIZE; i++) {
    weights[i] = 1.0 / BUFF_SIZE;
    weighted_den += weights[i];
  }
}

int compare_float(const void *a, const void *b) {
  float float_a = *((float*)a);
  float float_b = *((float*)b);

  if (float_a < float_b) return -1;
  if (float_a > float_b) return 1;
  return 0;
}

float salt_pepper_filter_dist() {
  // Reset the index
  if (dist_pos > BUFF_SIZE) {
    dist_pos = 0;
  }
  dist_arr[dist_pos] = duration / 58;
  dist_pos++;

  // Copy the original array
  memcpy(dist_arr_copy, dist_arr, sizeof(dist_arr));
  // Sort the copied array
  qsort(dist_arr_copy, BUFF_SIZE, sizeof(float), compare_float);

  printf("%s", "(Array) Sorted Distances: ");
  for (int i = 0; i < BUFF_SIZE; i++) {
    dtostrf(dist_arr_copy[i], 4, 2, output_str);
    printf("%scm, ", output_str);
  }

  return dist_arr_copy[BUFF_SIZE - 3];
}

// printf("%s", "Numerator: ");
// dtostrf(weighted_num, 4, 2, output_str);
// printf("%s ", output_str);

// printf("%s", "Denominator: ");
// dtostrf(weighted_den, 4, 2, output_str);
// printf("%s", output_str);