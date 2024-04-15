#include <stdio.h>
#include <string.h>

int sputc(char __c, FILE *__f) {
  if(__f == stderr) {
    Serial.write(__c);
  } else {
    Serial.write(__c);
  }
  return __c;
}

int sputs(const char* __str) {
  for(int i = 0; i < strlen(__str); i++) {
    sputc(__str[i], stdout);
  }
}

char sgetc() {
  return Serial.read();
}

void stdio_init_all(unsigned long baud = 9600) {
  Serial.begin(baud);
  fdevopen(&sputc, &sgetc); 
}