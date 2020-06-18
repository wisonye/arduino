/**
 * Basic voltage detection demo
 * 
 * `analogRead` let us to read from an analog value pin, it represents `0~1023` to map `0 ~ max volts`
 * on the board.
 * 
 * By default, in Arduino UNO, default voltage is 5V, but you can use `analogReference` to change it.
 * 
 * In this demo, we connect 2 LEDs with 2 resistors, 5V from board directly. For reading the analog vlaue,
 * we HAVE TO use the `A0` ~ `A5` pins. Then we pick `A0` and `A2` in this demo to read 2 different voltage 
 * before each LED's positive pin.
 */
 #include <stdio.h>
 
const uint8_t READ_PIN_1 = A0;
const uint8_t READ_PIN_2 = A2;
const uint16_t MAX_READ_ANALOG_VALUE = 1023;
const uint8_t ON_BOARD_VOLTAGE = 5;
const uint16_t LED_RESISTOR_OHMS_VALUE = 200;
const char message[1024];

/**
 * 
 */
float read_volts_from_analog_pin(uint8_t analog_pin) {
  uint16_t analog_value = analogRead(analog_pin);
  float read_value_per_unit = float(ON_BOARD_VOLTAGE) / float(MAX_READ_ANALOG_VALUE);

  sprintf(message, "analog_value: %d", analog_value); 
  Serial.println(message);
  
  return (float)(analog_value * read_value_per_unit);
}

/**
 * I = V/R, and we want unit is `mA`
 */
 float calculate_current_by_volts(float *volts) {
  return (*volts / (float)LED_RESISTOR_OHMS_VALUE) * 1000;
 }


/**
 * 
 */
void setup() {
  Serial.begin(9600);
  pinMode(READ_PIN_1, INPUT);
  pinMode(READ_PIN_2, INPUT);
  sprintf (message, "[ Voltage detection demo ]\nAnalog read PIN %d and %d set to 'INPUT' mode.\n", READ_PIN_1, READ_PIN_2);
  Serial.println(message);

  sprintf(message, 
    "ON_BOARD_VOLTAGE: %d V\nMAX_READ_ANALOG_VALUE: %d\nLED_RESISTOR_OHMS_VALUE: %d OHMs\n",
    ON_BOARD_VOLTAGE,
    MAX_READ_ANALOG_VALUE,
    LED_RESISTOR_OHMS_VALUE
   );
   Serial.println(message);  
}


/**
 * 
 */
void loop() {
  float realtime_volts_1 = read_volts_from_analog_pin(READ_PIN_1);
  float realtime_current_1 = calculate_current_by_volts(&realtime_volts_1);

  float realtime_volts_2 = read_volts_from_analog_pin(READ_PIN_2);
  float realtime_current_2 = calculate_current_by_volts(&realtime_volts_2);
  
  Serial.print("READ_PIN_1 voltage: ");
  Serial.print(realtime_volts_1);
  Serial.print(" v, current: ");
  Serial.print(realtime_current_1);
  Serial.println(" mA.\n");
  Serial.print("READ_PIN_2 voltage: ");
  Serial.print(realtime_volts_2);
  Serial.print(" v, current: ");
  Serial.print(realtime_current_2);
  Serial.println(" mA.\n\n");

  delay(1000);
}
