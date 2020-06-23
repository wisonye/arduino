/**
 * In this game demo, we will use a servo motor as a preset answer indicator. It got 6 fixed answer 
 * bind to 6 preset direction (angle). And we use an infrared remote control to command the motor
 * to point to which preset direction. Then we can hide the remote control in the pocket and run this 
 * funny game:)
 * 
 * We use `IR Remote` lib to receive the IR signal, make use you install it before running the demo.
 * Open `Tools --> Manage Libraries` and search `IR remote` (by shirriff) and install it.
 * 
 * Usually, servo motor only can rotate 90 ~ 180 degree, the one we got is `SG-90` model which can deal
 * with 180 degree and finish 60 degree in `0.12` sec. So it only needs `0.36` sec to finish 180 degree
 * rotation, but for safety, we should give it enough time which is `0.5` sec per 180 degree rotation.
 * 
 * Also, we use 3 LED as the `brain` status indicator. 
 * - `Green` means understand the question or command and executed the motor to the specified direction.
 * - `Yellow` means listening or thinking what's happening.
 * - `Red` means confusing and can't firgure what's going on.
 *
 * Circuit:
 * 
 * IR Sensor VCC: 5V
 * IR Sensor GND: GND
 * IR Sensor VOUT: Pin 8
 * 
 * SG-90 motor Brown: GND
 * SG-90 motor Red: 5V
 * SG-90 motor Orange: Pin 9 (Have to use PWN pin)
 * 
 * Indicator LED Green: Pin 2
 * Indicator LED Yellow: Pin 4
 * Indicator LED Red: Pin 6
 */
//#include <stdio.h>
#include <Servo.h>
#include <IRremote.h>

/**
 * Circuit pins
 */
const uint8_t GREEN_LED_PIN = 2;
const uint8_t YELLOW_LED_PIN = 4;
const uint8_t RED_LED_PIN = 6;
const uint8_t IR_SENSOR_PIN = 8;
const uint8_t MOTO_PIN = 9;

/**
 * NEC remote control button consts
 */
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

/**
 * Preset 6 fixed answer directions
 */
const uint8_t ANSWER_A_DIRECTION = 45;
const uint8_t ANSWER_B_DIRECTION = 60;
const uint8_t ANSWER_C_DIRECTION = 75;
const uint8_t ANSWER_D_DIRECTION = 90;
const uint8_t ANSWER_E_DIRECTION = 105;
const uint8_t ANSWER_F_DIRECTION = 120;
 

// Servo motor object instance
Servo execute_motor;
const uint8_t MOTO_INIT_DIRECTION = 0;
const uint8_t WAIT_FOR_MOTOR_TO_FINISH = 500; // Unit in ms

// IR receiver and result object
IRrecv irrecv(IR_SENSOR_PIN);
decode_results ir_decode_result;
uint8_t last_pressed_button;


const char debug_message[1024];

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
 * Brain status related
 */
void listening_or_thinking() {
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, HIGH);
  
  uint8_t blinking_index = 0;
  uint8_t blinking_delay = 30;
  uint8_t blinking_count = 30;
  while (blinking_index < blinking_count) {
    digitalWrite(YELLOW_LED_PIN, LOW);
    delay(blinking_delay);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    delay(blinking_delay);
    digitalWrite(YELLOW_LED_PIN, LOW);
    delay(blinking_delay);

    blinking_index++;
  }
}

void understand_or_done_executing() {
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, HIGH);
  delay(1000);
  digitalWrite(GREEN_LED_PIN, LOW);
}

void confusing_or_fail() {
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, HIGH);
  delay(1000);
  digitalWrite(RED_LED_PIN, LOW);
}

/**
 *
 */
void setup() {
  Serial.begin(9600);

  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  // Init servo motor
  execute_motor.attach(MOTO_PIN);
  execute_motor.write(MOTO_INIT_DIRECTION);
  delay(WAIT_FOR_MOTOR_TO_FINISH);

  // Enable IR listen mode
  irrecv.enableIRIn();

//  sprintf(
//    debug_message, 
//    "[ IR motor guess game demo ]\nMOTO_PIN: %d\nGREEN_LED_PIN: %d\nYELLOW_LED_PIN: %d\nRED_LED_PIN: %d\nIR sensor is in receive mode.\nSetup done.",
//    MOTO_PIN,
//    GREEN_LED_PIN,
//    YELLOW_LED_PIN,
//    RED_LED_PIN
//  );

  Serial.println(debug_message);
}

/**
 * Execute the anwser action:
 * - Show green light
 * - Motor point to correct answer direction
 */
void execute_answer(uint8_t button_value) {
//  sprintf(debug_message, "Execute answer: %s", get_button_desc(button_value));
  Serial.println(debug_message);

  switch (button_value) {
      case BUTTON_1: {
        understand_or_done_executing();
        execute_motor.write(ANSWER_A_DIRECTION);
        delay(WAIT_FOR_MOTOR_TO_FINISH);
        break;
      }

      case BUTTON_2: {
        understand_or_done_executing();
        execute_motor.write(ANSWER_B_DIRECTION);
        delay(WAIT_FOR_MOTOR_TO_FINISH);
        break;
      }

      case BUTTON_3: {
        understand_or_done_executing();
        execute_motor.write(ANSWER_C_DIRECTION);
        delay(WAIT_FOR_MOTOR_TO_FINISH);
        break;
      }

      case BUTTON_4: {
        understand_or_done_executing();
        execute_motor.write(ANSWER_D_DIRECTION);
        delay(WAIT_FOR_MOTOR_TO_FINISH);
        break;
      }

      case BUTTON_5: {
        understand_or_done_executing();
        execute_motor.write(ANSWER_E_DIRECTION);
        delay(WAIT_FOR_MOTOR_TO_FINISH);
        break;
      }

      case BUTTON_6: {
        understand_or_done_executing();
        execute_motor.write(ANSWER_F_DIRECTION);
        delay(WAIT_FOR_MOTOR_TO_FINISH);
        break;
      }

      default:
        break;
  }
}

/**
 *
 */
void loop() {

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

      switch (last_pressed_button) {
        case BUTTON_100_PLUS:
          listening_or_thinking();
          break;

        case BUTTON_200_PLUS:
          confusing_or_fail();
          execute_motor.write(MOTO_INIT_DIRECTION);
          delay(WAIT_FOR_MOTOR_TO_FINISH);
          break;

        case BUTTON_1: {
          execute_answer(last_pressed_button);
          break;
        }

        case BUTTON_2: {
          execute_answer(last_pressed_button);
          break;
        }

        case BUTTON_3: {
          execute_answer(last_pressed_button);
          break;
        }

        case BUTTON_4: {
          execute_answer(last_pressed_button);
          break;
        }

        case BUTTON_5: {
          execute_answer(last_pressed_button);
          break;
        }

        case BUTTON_6: {
          execute_answer(last_pressed_button);
          break;
        }

        default:
          break;
      }
    }

    // Resume to next round
    irrecv.resume();
  }

  delay(10);

//  listening_or_thinking();
//  delay(2000);
//  confusing_or_fail();
//  delay(2000);
//  understand_or_done_executing();
//  delay(2000);
} 
