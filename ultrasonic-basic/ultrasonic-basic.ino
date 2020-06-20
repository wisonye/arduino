/**
 * How the ultrasonic sensor works? It's pretty easy:
 *
 * 1. `Trigger Pin` send `LOW - HIGH - LOW`, and then the component will emit an ultrasonic wave
 * 2. After the ultrasonic wave goes out, the `Echo Pin` will keep `HIGH` until it receive the
 *    wave back then it will turn `LOW`.
 *
 * In this demo, our circuit is very simple:
 * 
 * - VCC: connects to the 5V
 * - Trigger Pin: connects to pin 4
 * - Echo pin: connects to pin 2
 */
#include <stdio.h>

const uint8_t TRIGGER_PIN = 4;
const uint8_t ECHO_PIN = 2;
const char message[1024];

/**
 *
 */
void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  sprintf(
    message, 
    "[ Ultrasonic basic demo ]\nTRIGGER_PIN %d set to 'OUTPUT'\nECHO_PIN %d set to 'INPUT'\n",
    TRIGGER_PIN,
    ECHO_PIN
  );

  Serial.println(message);
}

/**
 *
 */
void emit_wave() {
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
}

/**
 *
 */
uint32_t wait_for_wave_back_and_get_the_travle_time() {
    /**
     * Reads a pulse (either HIGH or LOW) on a pin. For example, if value is HIGH, pulseIn() waits 
     * for the pin to go HIGH, starts timing, then waits for the pin to go LOW and stops timing.
     * Returns the length of the pulse in microseconds or 0 if no complete pulse was received 
     * within the timeout.
     */
    return pulseIn(ECHO_PIN, HIGH);
}
/**
 *
 */
void loop() {
    emit_wave();
    uint32_t wave_travel_time_in_microseconds = wait_for_wave_back_and_get_the_travle_time();
    float distance_in_cm = float(wave_travel_time_in_microseconds) / float(1000000) * float(340 / 2) * float(100);
    Serial.print("Ultrasonic wave travel time: ");
    Serial.print(wave_travel_time_in_microseconds);
    Serial.print(", distance in CM: ");
    Serial.println(distance_in_cm);
    delay(25);
}
