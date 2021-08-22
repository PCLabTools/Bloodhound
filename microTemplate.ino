/*************************************************************************
    File        : microTemplate.h (opens in arduino IDE www.arduino.cc)
    Description : Handles Stream Messages
    Date        : 31st July 2021
    Author      : Larry Colvin (PCLabTools)
*************************************************************************/

#include <Arduino.h>
#include <TimeLib.h>
#include "src/Errors.h"
#include "src/Functions.h"
#include "src/TeensyReset.h"
#include "src/Variables.h"
#include "src/SerialComms.h"

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  //
}

/*************************************************************************
    End of File : microTemplate.ino
*************************************************************************/
