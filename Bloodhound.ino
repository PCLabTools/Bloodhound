/*************************************************************************
    File        : Bloodhound.h (opens in arduino IDE www.arduino.cc)
    Description : Sniffs UART communications and prints it to the debug port
    Date        : 31st July 2021
    Author      : Larry Colvin (PCLabTools)
*************************************************************************/

/** NOTE:
 *    The hardware serial buffers for sniffing can be increased by
 *    editing serial1.c and serial2.c to increase buffer size definition
 * 
 *    <Arduino>\hardware\teensy\avr\cores\teensy3\serial1.c
 *    <Arduino>\hardware\teensy\avr\cores\teensy3\serial2.c
 **/

#include <Arduino.h>
#include <TimeLib.h>
#include "src/Errors.h"
#include "src/Functions.h"
#include "src/TeensyReset.h"
#include "src/Variables.h"
#include "src/SerialComms.h"
#include "src/MicroLCD.h"

LCD_SSD1306 LCD;

/*************************************************************************
    SETUP
*************************************************************************/

void setup() {
  setupPins();
  setupSerial();
  setupLCD();
}

void setupPins() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(21, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  attachInterrupt(22, backButton, FALLING);
  attachInterrupt(21, fwrdButton, FALLING);
}

void setupSerial() {
  Serial.begin(115200);
  Serial1.begin(COMMS_BAUD_RATE);
  Serial1.setTimeout(0);
  Serial2.begin(COMMS_BAUD_RATE);
  Serial2.setTimeout(0);
}

void setupLCD() {
  LCD.begin();
  LCD.setFontSize(FONT_SIZE_SMALL);
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.draw(LOGO, 128, 64);
  LCD.setCursor(0, 7);
  LCD.print(SOFTWARE_ID);
  delay(3000);
  LCD.clear();
}

/*************************************************************************
    MAIN
*************************************************************************/

void loop() {
  printDebug();
  updateDisplay();
}

void printDebug() {
  if ((millis()-SNIFF_TIME) > SNIFF_RATE) {
    if (TX_BUFFER_POINTER) {
      for (uint16_t i=0; i<TX_BUFFER_POINTER; i++) {
        Serial.write(TX_BUFFER[i]);
      }
      TX_BUFFER_POINTER = 0;
    }
    if (RX_BUFFER_POINTER) {
      for (uint16_t i=0; i<RX_BUFFER_POINTER; i++) {
        Serial.write(RX_BUFFER[i]);
      }
      RX_BUFFER_POINTER = 0;
    }
    SNIFF_TIME = millis();
  }
}

void updateDisplay() {
  if ((millis()-LCD_TIME) > LCD_RATE) {
    // SET ORIGIN
    LCD.setCursor(0,0);
    // LINE 0
    LCD.println("Time: " + parseTime(hour()) + ":" + parseTime(minute()) + ":" + parseTime(second()));
    // LINE 1
    LCD.println("BAUD: " + String(COMMS_BAUD_RATE));
    // LINE 2
    LCD.println("[TX:" + String(TX_BYTES_TOTAL) + "  RX:" + String(RX_BYTES_TOTAL) + "]");
    // LINE 3
    LCD.println();
    // LINE 4
    LCD.draw(UP_ARROW, 8, 8);
    LCD.println(":");
    // LINE 5
    LCD.println();
    // LINE 6
    LCD.draw(DOWN_ARROW, 8, 8);
    LCD.println(":");
    // LINE 7
    LCD.println();
    LCD_TIME = millis();
  }
}

/*************************************************************************
    INTERRUPTS
*************************************************************************/

void backButton() {
  if ((millis()-LAST_PRESS) > PRESS_RATE) {
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.draw(LOGO, 128, 64);
    LCD.setCursor(0, 7);
    LCD.print("FORWARD");
    delay(500);
    LCD.clear();
    LAST_PRESS = millis();
  }
}

void fwrdButton() {
  if ((millis()-LAST_PRESS) > PRESS_RATE) {
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.draw(LOGO, 128, 64);
    LCD.setCursor(0, 7);
    LCD.print("BACKWARD");
    delay(500);
    LCD.clear();
    LAST_PRESS = millis();
  }
}
/*************************************************************************
    End of File : Bloodhound.ino
*************************************************************************/
