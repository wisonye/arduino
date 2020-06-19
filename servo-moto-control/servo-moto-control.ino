/**
 * Usually, servo motor only can rotate 90 ~ 180 degree, the one we have is `SG-90` which can done
 * 180 degree and finish 60 degree in `0.12` sec. So it only needs `0.36` sec to finish 180 degree
 * rotation, but for safety, we should give it enough time which as `0.5` sec per 180 degree rotation.
 *
 * In this demo, we simulate a car park entrace which got a railing. By default the railing is down
 * which means the servo motor should point to 0 degree. Then we got a buttons (pull-up resistor) to
 * control the railing:
 *
 * - Open: When pushing down, make the active buzzer beeping for 0.5 sec and servo motor to 90 degree.
 * - Close: When pushing down, make the active buzzer beeping for 0.5 sec and servo motor to 0 degree.
 */
#include <Servo.h>
#include <stdio.h>

// Servo motor object instance
Servo car_park_railing;

const uint8_t SERVO_MOTOR_PIN = 9; // Have to use PWM pin!!!
const uint8_t RAILLING_CLOSE_ANGLE = 0;
const uint8_t RAILLING_OPEN_ANGLE = 90;
const uint8_t WAIT_FOR_RAILING_TO_FINISH = 500; // Unit in ms
const uint8_t BUZZER_PIN = 6;
const uint8_t TOGGLE_BUTTON_PIN = 2;
const char message[1024];

bool is_rail_opened = false;
bool toggle_button_prev_value = 1;

/**
 *
 */
void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);

  // Init servo motor
  car_park_railing.attach(SERVO_MOTOR_PIN);
  car_park_railing.write(RAILLING_CLOSE_ANGLE);
  delay(WAIT_FOR_RAILING_TO_FINISH);

  sprintf(
    message, 
    "[ Car park railing simulate demo ]\nSERVO_MOTOR_PIN: %d\nBUZZER_PIN: %d\nTOGGLE_BUTTON_IN: %d\n",
    SERVO_MOTOR_PIN,
    BUZZER_PIN,
    TOGGLE_BUTTON_PIN
  );

  Serial.println(message);
}

/**is_rail_opened
 *
 */
void toggle_railing() {
    // Servo motor angle change
    if (is_rail_opened == true) {
      car_park_railing.write(RAILLING_CLOSE_ANGLE);
    } else {
      car_park_railing.write(RAILLING_OPEN_ANGLE);
    }

    // Beeping and wait for the servo motor to finish
    digitalWrite(BUZZER_PIN, HIGH);
    delay(WAIT_FOR_RAILING_TO_FINISH);
    digitalWrite(BUZZER_PIN, LOW);

    // Update status
    is_rail_opened = !is_rail_opened;
}


/**
 *
 */
void loop() {
    // It's a pull-up resistor circuit, when pushing down, we will get `0` and then get back `1`
    // when releasing it.
    uint8_t toggle_button_value = digitalRead(TOGGLE_BUTTON_PIN);
    if (toggle_button_prev_value == 1 && toggle_button_value == 0) {
        sprintf(message, "Toggle rail status from '%#x' to '%#x'", is_rail_opened, !is_rail_opened);
        Serial.println(message);

        toggle_railing();
    }

    toggle_button_prev_value = toggle_button_value;
    delay(200);
}
