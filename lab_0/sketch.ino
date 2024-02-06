const int BUTTON_PIN = 7;  
const int LED_PIN    = 8;      
const int BAUD_RATE  = 9600;
  
int led_state = LOW;       
int last_button_state;      
int current_button_state; 
  
void setup() {
  Serial.begin(BAUD_RATE);                       
  pinMode(BUTTON_PIN, INPUT);  
  pinMode(LED_PIN, OUTPUT);      
  
  current_button_state = digitalRead(BUTTON_PIN);
}
  
void loop() {
  last_button_state    = current_button_state;              
  current_button_state = digitalRead(BUTTON_PIN);
  
  if(last_button_state == HIGH && current_button_state == LOW) {
    if(led_state == LOW) {
      led_state = HIGH;  
      Serial.println("Turning LED on");
    }
    else {
      led_state = LOW;
      Serial.println("Turning LED off");
    }
 
    digitalWrite(LED_PIN, led_state); 
    delay(100);
  }
}