/**
 * Button component can act as a `Pull-up Resistor` or `Pull-down Resistor`, it depends on where
 * you put the resistor and GPIO pin into the circuit:
 *
 * 1. Pull-up: 5V connects to 10K resistor, and put GPIO pin between resistor and button.
 *    When button be pushed down, `digitalRead()` got `0`
 *
 * 2. Pull-down: 5V connects to button, and then GPIO pin, and follow the resistor.
 *    When button be pushed down, `digitalRead()` got `1`
 *
 * In this demo, we connect an active buzzer to pin 4, and pull-up resistor read pin to 2.
 * When button pushes down, we set buzzer pin to `HIGH` to make some noise.
 */

#include <stdio.h>

const uint8_t PULL_UP_RESISTOR_READ_PIN = 2;
const uint8_t BUZZER_PIN = 4;

const char message[1024];

/**
 *
 */
void setup() {
    Serial.begin(9600);

    pinMode(PULL_UP_RESISTOR_READ_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    sprintf(message, "[ Button (pull-up resistor) control active buzzer demo]\n");
    Serial.println(message);

    sprintf(message, "PULL_UP_RESISTOR_READ_PIN %d set to 'INPUT' mode\n", PULL_UP_RESISTOR_READ_PIN);
    Serial.println(message);

    sprintf(message, "BUZZER_PIN %d set to 'OUTPUT' mode\n", BUZZER_PIN);
    Serial.println(message);
 }


 /**
  *
  */
void loop() {
    uint8_t pull_up_resistor_read_value = digitalRead(PULL_UP_RESISTOR_READ_PIN);
    Serial.print("pull_up_resistor_read_value: ");
    Serial.println(pull_up_resistor_read_value);

    if (pull_up_resistor_read_value == 0) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(50);
    } else {
      digitalWrite(BUZZER_PIN, LOW);
    }

    delay(50);
}
