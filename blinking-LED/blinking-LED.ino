/**
 * Basic LED blinking demo
 * 
 * We use `sprintf` to format our output content, that's why we need to import the `<stdio.h>` 
 * (standard IO header file). And `sprintf` use a `char array, and you need to make sure that
 * char array is bigger enough to hold all the content!!!
 * 
 * Here is the link for all the format string we can use in `sprintf`:
 * 
 * https://arduinobasics.blogspot.com/2019/05/sprintf-function.html
 */
 #include <stdio.h>
 
const uint8_t LED_PIN = 10;
const uint16_t LDE_BLINKING_DELAY = 1000;
const char message[100];


void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  sprintf (message, "LED PIN %d set to 'OUTPUT' mode.", LED_PIN);
  Serial.println(message);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(LDE_BLINKING_DELAY);
  digitalWrite(LED_PIN, LOW);
  delay(LDE_BLINKING_DELAY);

  sprintf(message, "Finish one round blinking");
  Serial.println(message);
}
