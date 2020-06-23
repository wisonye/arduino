/**
 * In this demo we use `IR Remote` lib to receive the IR signal, make use you install it before run the demo.
 * Open `Tools --> Manage Libraries` and search `IR remote` (by shirriff) and install it.
 * 
 */
 #include <IRremote.h>
 #include <stdio.h>

const uint8_t IR_SENSOR_PIN = 4;
const char debug_message[1024];

// NEC remote control button consts
const uint8_t BUTTON_0 = 0;
const uint8_t BUTTON_1 = 1;
const uint8_t BUTTON_2 = 2;
const uint8_t BUTTON_3 = 3;
const uint8_t BUTTON_4 = 4;
const uint8_t BUTTON_5 = 5;
const uint8_t BUTTON_6 = 6;
const uint8_t BUTTON_7 = 7;
const uint8_t BUTTON_8 = 8;
const uint8_t BUTTON_9 = 9;
const uint8_t BUTTON_CHANNEL_MINUS = 10;
const uint8_t BUTTON_CHANNEL = 11;
const uint8_t BUTTON_CHANNEL_PLUS = 12;
const uint8_t BUTTON_PREV = 13;
const uint8_t BUTTON_NEXT = 14;
const uint8_t BUTTON_PLAY = 15;
const uint8_t BUTTON_MINUS = 16;
const uint8_t BUTTON_PLUS = 17;
const uint8_t BUTTON_EQUAL = 18;
const uint8_t BUTTON_100_PLUS = 19;
const uint8_t BUTTON_200_PLUS = 20;
const uint8_t LAST_PRESSED_BUTTON = 254;
const uint8_t UNKNOWN_BUTTON = 255;

// Last pressed button
uint8_t last_pressed_button;

// IR receiver and result object
IRrecv irrecv(IR_SENSOR_PIN);
decode_results ir_decode_result;


/**
 * 
 */
uint8_t get_button_from_ir_value(uint32_t ir_value) {
  switch (ir_value) {
    case 0xFF6897: return BUTTON_0;
    case 0xFF30CF: return BUTTON_1;
    case 0xFF18E7: return BUTTON_2;
    case 0xFF7A85: return BUTTON_3;
    case 0xFF10EF: return BUTTON_4;
    case 0xFF38C7: return BUTTON_5;
    case 0xFF5AA5: return BUTTON_6;
    case 0xFF42BD: return BUTTON_7;
    case 0xFF4AB5: return BUTTON_8;
    case 0xFF52AD: return BUTTON_9;
    case 0xFFA25D: return BUTTON_CHANNEL_MINUS;
    case 0xFF629D: return BUTTON_CHANNEL;
    case 0xFFE21D: return BUTTON_CHANNEL_PLUS;
    case 0xFF22DD: return BUTTON_PREV;
    case 0xFF02FD: return BUTTON_NEXT;
    case 0xFFC23D: return BUTTON_PLAY;
    case 0xFFE01F: return BUTTON_MINUS;
    case 0xFFA857: return BUTTON_PLUS;
    case 0xFF906F: return BUTTON_EQUAL;
    case 0xFF9867: return BUTTON_100_PLUS;
    case 0xFFB04F: return BUTTON_200_PLUS;    
    
    case 0xFFFFFFFF: return LAST_PRESSED_BUTTON;
    default: return UNKNOWN_BUTTON;
  }
}

/**
 * 
 */
String get_button_desc(uint8_t button_value) {
  switch (button_value) {
    case BUTTON_0: return "BUTTON_0";
    case BUTTON_1: return "BUTTON_1";
    case BUTTON_2: return "BUTTON_2";
    case BUTTON_3: return "BUTTON_3";
    case BUTTON_4: return "BUTTON_4";
    case BUTTON_5: return "BUTTON_5";
    case BUTTON_6: return "BUTTON_6";
    case BUTTON_7: return "BUTTON_7";
    case BUTTON_8: return "BUTTON_8";
    case BUTTON_9: return "BUTTON_9";
    case BUTTON_CHANNEL_MINUS: return "BUTTON_CHANNEL_MINUS";
    case BUTTON_CHANNEL: return "BUTTON_CHANNEL";
    case BUTTON_CHANNEL_PLUS: return "BUTTON_CHANNEL_PLUS";
    case BUTTON_PREV: return "BUTTON_PREV";
    case BUTTON_NEXT: return "BUTTON_NEXT";
    case BUTTON_PLAY: return "BUTTON_PLAY";
    case BUTTON_MINUS: return "BUTTON_MINUS";
    case BUTTON_PLUS: return "BUTTON_PLUS";
    case BUTTON_EQUAL: return "BUTTON_EQUAL";
    case BUTTON_100_PLUS: return "BUTTON_100_PLUS";
    case BUTTON_200_PLUS: return "BUTTON_200_PLUS";
    case LAST_PRESSED_BUTTON: return "LAST_PRESSED_BUTTON";
    case UNKNOWN_BUTTON: return "UNKNOWN_BUTTON";
    default: return "UNKNOWN_BUTTON";
  }
}

/**
 * 
 */
void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  Serial.println("Already enable IR receiver.");
}

/**
 * 
 */
void loop() {
  String brand = "";

  // If we can decode something
  if (irrecv.decode(&ir_decode_result)) {

    /**
     * As we're using the `NEC` protocol device which `decode_type` will be `NEC` (unint8_t value of `3`),
     * then we should ignore all non-NEC cases FF9867
     * and all fail to decode cases!!!
     */
    if (ir_decode_result.decode_type == NEC) {
      uint8_t temp_value = get_button_from_ir_value(ir_decode_result.value);
      if (temp_value != LAST_PRESSED_BUTTON) {
        last_pressed_button = temp_value;  
      }

      Serial.print("Got value: ");
      Serial.print(ir_decode_result.value, HEX);
      Serial.print(", button: ");
      Serial.println(get_button_desc(last_pressed_button));
    }

    // Resume to next round
    irrecv.resume();
  }

  delay(10);
}
