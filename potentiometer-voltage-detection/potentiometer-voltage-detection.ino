/**
 * Basic potentiomenter control LED brightness demo
 * 
 * Potentiometer has 2 resistors inside and it allows you to change the output voltage by turning the knob.
 * 
 * `analogRead` let us to read from an analog value pin, it represents `0~1023` to map `0 ~ max volts`
 * on the board.
 * 
 * By default, in Arduino UNO, default voltage is 5V, but you can use `analogReference` to change it.
 * 
 * In this demo, our circuit looks like this:
 * 
 * - Potentiomenter (10K), 5V and ground directly from the board. We use `A0` to read the live voltage.
 * - After get the live voltage, we use another analog pin write to LED's positive, control the brightness.
 */
 #include <stdio.h>
 
const uint8_t POTENTIOMENTER_ANALOG_PIN = A0;
const uint16_t POTENTIOMENTER_RESISTOR_OHMS_VALUE = 10000;

const uint16_t MAX_READ_ANALOG_VALUE = 1023;
const uint16_t MAX_WRITE_ANALOG_VALUE = 255;
const uint8_t ON_BOARD_VOLTAGE = 5;

const uint8_t LED_PIN = 10;

const char message[1024];

/**
 * 
 */
float read_volts_from_analog_pin(uint8_t analog_pin) {
  uint16_t potentiometer_analog_value = analogRead(analog_pin);
  float read_value_per_unit = float(ON_BOARD_VOLTAGE) / float(MAX_READ_ANALOG_VALUE);

  sprintf(message, "potentiometer_analog_value: %d", potentiometer_analog_value); 
  Serial.println(message);
  
  return (float)(potentiometer_analog_value * read_value_per_unit);
}

/**
 * I = V/R, and we want unit is `mA`
 */
 float calculate_current_by_volts(float *volts) {
  return (*volts / (float)POTENTIOMENTER_RESISTOR_OHMS_VALUE) * 1000;
 }

/**
 * Analog write value from `0 ~ MAX_WRITE_ANALOG_VALUE` which will map to `0 ~ ON_BOARD_VOLTAGE`
 */
 float calculate_led_analog_value_by_volts(float *volts) {
  float analog_write_per_unit = (float)MAX_WRITE_ANALOG_VALUE / (float)ON_BOARD_VOLTAGE;
  float value_to_write = *volts * analog_write_per_unit;
  Serial.print("Analog write value for LED is: ");
  Serial.println(value_to_write);
  return value_to_write;
 }

/**
 * 
 */
void setup() {
  Serial.begin(9600);
  pinMode(POTENTIOMENTER_ANALOG_PIN, INPUT);
  
  sprintf (message, "[ Potentiomenter control LED brightness demo ]\nPotentiometer analog read PIN %d set to 'INPUT' mode.\nLED PIN %d set to 'OUTPTU' mode.\n", POTENTIOMENTER_ANALOG_PIN, LED_PIN);
  Serial.println(message);

  sprintf(message, 
    "ON_BOARD_VOLTAGE: %d V\nMAX_READ_ANALOG_VALUE: %d\nMAX_WRITE_ANALOG_VALUE: %d\nLED_RESISTOR_OHMS_VALUE: %d OHMs\n",
    ON_BOARD_VOLTAGE,
    MAX_READ_ANALOG_VALUE,
    MAX_WRITE_ANALOG_VALUE,
    POTENTIOMENTER_RESISTOR_OHMS_VALUE
   );
   Serial.println(message);  
}


/**
 * 
 */
void loop() {
  float realtime_volts = read_volts_from_analog_pin(POTENTIOMENTER_ANALOG_PIN);
  float realtime_current = calculate_current_by_volts(&realtime_volts);
  
  Serial.print("\nPOTENTIOMENTER_ANALOG_PIN voltage: ");
  Serial.print(realtime_volts);
  Serial.print(" v, current: ");
  Serial.print(realtime_current);
  Serial.println(" mA.");

  // Now, we use voltage convert back to `0~255` and write it to the LED pin
  analogWrite(LED_PIN, calculate_led_analog_value_by_volts(&realtime_volts));

  delay(500);
}
