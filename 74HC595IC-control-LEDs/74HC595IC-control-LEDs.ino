/*
 * 74HC595 IC bit pattern shift demo. Why use 74HC595 IC? Because it allows us use 3 GPIO pins
 * to drive up to 8 LEDs (or another electrical component). 
 * 
 * How it works?
 * 
 * 1. Before sending data to the chip, we need to set `Latch Pin` to `LOW`.
 * 2. Then we can use `shiftOut` to send a byte via the `Serial Data Pin`.
 * 3. After finish data sending, we need to set the `Latch Pin` to `HIGH`.
 * 
 * The `byte` we sent represents 8 switch status which will map to the IC `Output Pins` (Q0 ~ Q7).
 * The bit mapping order is controlled the `bitOrder` param which will be `MSBFIRST` or `LSBFIRST`, 
 * it means either `bit7 ~ bit0` or `bit0 ~ bit7`.
 * 
 * Some pins we need to pay attention to:
 * 
 * Q0 ~ Q7: Voltage output pin, output `HIGH` or `LOW`, data source is from `Pin 14 (Serial Data Pin)`
 * Pin10: Master reclear, active low. If you don't want the `reclear` works, then we need to set it to `HIGH` or just connect to the 5V.
 * Pin11: Clock pin
 * Pin12: Latch pin
 * Pin13: Output enable, active low. Control whether the `Q0 ~ Q7` enable or not, set to `LOW` or connect to the ground.
 * Pin14: Serial data input, we will this pin to send bit data
 * 
 * The real visual effect of this demo: We should see 8 LEDs will light up from right to left one-by-one.
 */
uint8_t LEDS_ARRAY[] = {
  B00000000,
  B00000001,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000,
};

// Test setting, all light up or all light off
const uint8_t ALL_ENABLE_VALUE = 0xFF;
const uint8_t ALL_DISABLE_VALUE = 0x00;

const uint8_t IC_DATA_PIN = 3;
const uint8_t IC_LATCH_PIN = 5;
const uint8_t IC_CLOCK_PIN = 7;

const char message[1024];

/**
 * 
 */
void setup() {
  Serial.begin(9600);
  pinMode(IC_LATCH_PIN, OUTPUT);
  pinMode(IC_CLOCK_PIN, OUTPUT);
  pinMode(IC_DATA_PIN, OUTPUT);
  
  sprintf(message, 
    "[ 74HC595 IC bit pattern shit demo ]\nIC_DATA_PIN: %d\nIC_LATCH_PIN: %d\nIC_CLOCK_PIN: %d\n",
    IC_DATA_PIN,
    IC_LATCH_PIN,
    IC_CLOCK_PIN
  );
  Serial.println(message); 
}

/**
 * 
 */
void test() {
  // Before we can use `shiftOut` to send down the data to the chip, the `Latch pin` must be `LOW`.
  digitalWrite(IC_LATCH_PIN, LOW);

  // Just for test, light up all the LEDs
  shiftOut(IC_DATA_PIN, IC_CLOCK_PIN, LSBFIRST, ALL_ENABLE_VALUE);
  
  // After we finish sending the data via the data pin, we should set the `Latch pin` back to `HIGHT.
  digitalWrite(IC_LATCH_PIN, HIGH);
}

/**
 * 
 */
void loop() {
  // The the entire light up pattern
  for (int arrIndex = 0; arrIndex < sizeof(LEDS_ARRAY); arrIndex++ ) {
    digitalWrite(IC_LATCH_PIN, LOW);
    
    shiftOut(IC_DATA_PIN, IC_CLOCK_PIN, MSBFIRST, LEDS_ARRAY[ arrIndex ]);
    
    digitalWrite(IC_LATCH_PIN, HIGH);
    
    delay(250);
  }


  // Deplay before the next light up pattern
  delay(1000);


}
