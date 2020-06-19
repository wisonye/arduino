/**
 * For the 1602 LCD which already combined with the I2C module, you need to download the lib from here:
 * https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c
 * 
 * And then copy the unzip folder `LiquidCrystal_I2C-1.1.2` into `~Documents/Arduino/libraries` and restart Arduino IDE.
 * From now on, you can open its example to have a look:)
 * 
 * 1602 LCD with I2C module on the back, below is the access address controlled by `A0, A1, A2`:
 * 
 * A0, A1, A2 - 0 0 0 -> 0x27
 * A0, A1, A2 - 1 0 0 -> 0x26
 * A0, A1, A2 - 0 1 0 -> 0x25
 * A0, A1, A2 - 1 1 0 -> 0x24
 * A0, A1, A2 - 0 0 1 -> 0x23
 * A0, A1, A2 - 1 0 1 -> 0x22
 * A0, A1, A2 - 0 1 1 -> 0x21
 * A0, A1, A2 - 1 1 1 -> 0x20
 * 
 */

/**
 * This `Wire` library allows you to communicate with I2C / TWI devices. 
 * On the Arduino boards with the R3 layout (1.0 pinout), the SDA (data line) 
 * and SCL (clock line) are on the pin headers close to the AREF pin.
 * 
 * As a reference the table below shows where TWI pins are located on various 
 * Arduino boards.
 *
 * Board I2C / TWI pins
 * Uno, Ethernet A4 (SDA), A5 (SCL)
 * Mega2560  20 (SDA), 21 (SCL)
 * Leonardo  2 (SDA), 3 (SCL)
 * Due 20 (SDA), 21 (SCL), SDA1, SCL1
 */
#include <Wire.h> 

#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
const LiquidCrystal_I2C lcd(0x27,16,2);  

// Below is the special character which use 8bit HEX to draw
uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
uint8_t note[8]  = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
uint8_t clock[8] = {0x0,0xe,0x15,0x17,0x11,0xe,0x0};
uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
uint8_t duck[8]  = {0x0,0xc,0x1d,0xf,0xf,0x6,0x0};
uint8_t check[8] = {0x0,0x1,0x3,0x16,0x1c,0x8,0x0};
uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
uint8_t retarrow[8] = {  0x1,0x1,0x5,0x9,0x1f,0x8,0x4};

// Use to print the special character
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

/**
 * Separate lines when needed
 */
void show_text(String content) {
  lcd.clear();
  lcd.setCursor(0, 0);

  const uint16_t len = content.length();
  if (len > 16) {
    String first_line = content.substring(0, 16);
    String next_line = content.substring(16);
    lcd.print(first_line);
    lcd.setCursor(0, 1);
    lcd.print(next_line);
  }
  else {
    lcd.print(content);
  }
}

 /**
  * 
  */
void setup() {
  Serial.begin(9600);

  // Init and enable the back light
  lcd.init();
  lcd.backlight();

  // Create special character, each one has a unique index
  lcd.createChar(0, bell);
  lcd.createChar(1, note);
  lcd.createChar(2, clock);
  lcd.createChar(3, heart);
  lcd.createChar(4, duck);
  lcd.createChar(5, check);
  lcd.createChar(6, cross);
  lcd.createChar(7, retarrow);

  // Clear and show prompt
  lcd.clear();
  show_text("Waiting for your input:)");
}

/**
 * 
 */
void loop() {
  // We can use `lcd.printByte(index)` to show a speical character defined above,
  // just change the `index` to which you defined in `lcd.createChar()`.

  //  for (index=0; index<8; index++) {
  //    lcd.scrollDisplayLeft();
  //    delay(1000);
  //  }

  // Wait for user type and send text via serial
  if (Serial.available()) {
    // Wait a bit for the entire message to arrive
    delay(100);

    const String content_to_display = Serial.readString();
    Serial.print("Got text to display: ");
    Serial.println(content_to_display);

    if (content_to_display.length() > 0) { show_text( content_to_display); }
  }
}
