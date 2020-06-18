/**
 * Basic LED dimming demo demo
 * 
 * `analogWrite` let us to write an analog value (PWM wave) to a pin, it's the way we control how
 * much volts we want to set to a pin. The value of the `analogWrite` is use `0~255` to map `0 ~ max volts`
 * on the board.
 * 
 * By default, in Arduino UNO, default voltage is 5V, but you can use `analogReference` to change it.
 * 
 * In this demo, we use the analog pin 10.
 */
 #include <stdio.h>
 
const uint8_t LED_PIN = 10;
const uint8_t LED_DIMMING_CYCLE_IN_SECOND = 8;
const uint8_t MAX_ANALOG_VALUE = 255;
const uint16_t LED_DIMMING_DELAY = 1000;
const uint8_t ON_BOARD_VOLTAGE = 5;
const uint16_t LED_RESISTOR_OHMS_VALUE = 200;
const char message[1024];

// How many times we should dim from `0 ~ ON_BOARD_VOLTAGE`?
const uint8_t total_dimming_count = LED_DIMMING_CYCLE_IN_SECOND * 1000 / LED_DIMMING_DELAY;

// The voltage will increased per dimming
const float volts_increase_per_dimming = (float)ON_BOARD_VOLTAGE / (float)total_dimming_count;

/**
 * 
 */
float calculate_next_volts(float *realtime_volts) {
  return *realtime_volts * (float)MAX_ANALOG_VALUE / (float)(ON_BOARD_VOLTAGE);
}

/**
 * I = V/R, and we want unit is `mA`
 */
 float calculate_next_current(float *volts) {
  return (*volts / (float)LED_RESISTOR_OHMS_VALUE) * 1000;
 }

// Init volts and analog value
float realtime_volts = 0.0;
float realtime_volts_analog_value = 0.0;

// The current we want to calculate as well
float realtime_current_value = 0.0;


/**
 * 
 */
void reset_dimming() {
  realtime_volts = 0.0;
  realtime_current_value = 0.0;
  realtime_volts_analog_value = 0.0;
}

/**
 * 
 */
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  sprintf (message, "LED dimming demo.\n\nLED PIN %d set to 'OUTPUT' mode.", LED_PIN);
  Serial.println(message);

  sprintf(message, 
    "LED_DIMMING_CYCLE_IN_SECOND: %d\nLED_DIMMING_DELAY: %d\nON_BOARD_VOLTAGE: %d\ntotal_dimming_count: %d", 
    LED_DIMMING_CYCLE_IN_SECOND, 
    LED_DIMMING_DELAY,
    ON_BOARD_VOLTAGE, 
    total_dimming_count
  );
  Serial.println(message);

  // Due to some performance reasons `%f` is not included in the Arduino's implementation of sprintf().
  // So we have to use another way to print out the floating point value
  Serial.print("volts_increase_per_dimming: ");
  Serial.println(volts_increase_per_dimming);

  // Reset
  reset_dimming();
}


/**
 * 
 */
void loop() {
  Serial.println("\nDimming cycle start...");

  // Here is one dimming cycle
  while (realtime_volts <= ON_BOARD_VOLTAGE) {
    Serial.print("realtime_volts: ");
    Serial.print(realtime_volts);
    Serial.print(" v, ");
    Serial.print("realtime_volts_analog_value: ");
    Serial.print(realtime_volts_analog_value);
    Serial.print(", realtime_current_value: ");
    Serial.print(realtime_current_value);
    Serial.println(" mA");

    analogWrite(LED_PIN, realtime_volts_analog_value);

    delay(LED_DIMMING_DELAY);

    realtime_volts += volts_increase_per_dimming;
    realtime_volts_analog_value = calculate_next_volts(&realtime_volts);
    realtime_current_value = calculate_next_current(&realtime_volts);
  }

  Serial.println("Dimming cycle done.");

  // After done, we nee to reset to next round :)
  reset_dimming();
}
