/*************************************************************************
    File        : Messages.h
    Description : Message definition file
*************************************************************************/

/**
 * MESSAGES:
 * 
 *    *IDN?   - Identity
 *    *ECHO   - Echo Data
 *    *RST    - Reset
 *    *TST?   - Self-Test
 *    *ERR?   - Error
 *    *AST    - Assert Error
 *    *CLR    - Clear Error Status
 *    *TIME?  - Query Current Time
 *    *SYNC   - Syncrhonise Time Clock
 *    BAUD    - Set BAUD Rate
 *    BAUD?   - Get BAUD Rate
 *    BYTES?  - Get Total Bytes Sniffed
 * 
 **/

void handleMessage(Stream &STREAM, Message MESSAGE) {

  /*************************************************************************
      State       : *IDN?
      Parameters  : -
      Description : Queries the hardware and software ID
  *************************************************************************/
  if (MESSAGE.state == "*idn?") {
    STREAM.println(SOFTWARE_ID + " | " + COMPANY_ID + " | Serial: " + String(HARDWARE_ID) + "/" + String(HARDWARE_VERSION, HEX) + " | Version: " + String(SOFTWARE_VERSION_MAJOR, HEX) + "." + String(SOFTWARE_VERSION_MINOR, HEX) + "." + String(SOFTWARE_VERSION_FIX, HEX));
  } 

  /*************************************************************************
      State       : *ECHO
      Parameters  : -
      Description : Instructs the target to echo the message data[0]
  *************************************************************************/
  else if (MESSAGE.state == "*echo") {
    STREAM.println(MESSAGE.data[0]);
  } 

  /*************************************************************************
      State       : *RST
      Parameters  : -
      Description : Software resets the microcontroller
  *************************************************************************/
  else if (MESSAGE.state == "*rst") {
    CPU_RESTART;
  } 

  /*************************************************************************
      State       : *TST?
      Parameters  : -
      Description : Instruct the system to perform a self-test and report
                    the system status
  *************************************************************************/
  else if (MESSAGE.state == "*tst?") {
    STREAM.println(String("Performing Self Test..."));
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    if (SYSTEM_ERROR) {STREAM.println(String("FAIL"));}
    else {STREAM.println(String("PASS"));}
  } 

  /*************************************************************************
      State       : *ERR?
      Parameters  : -
      Description : Queries the system for the current error code
  *************************************************************************/
  else if (MESSAGE.state == "*err?") {
    STREAM.println(String(SYSTEM_ERROR));
  } 

  /*************************************************************************
      State       : *AST
      Parameters  : -
      Description : Assert a system error which can be used for code testing
  *************************************************************************/
  else if (MESSAGE.state == "*ast") {
    SYSTEM_ERROR = ASSERT_ERROR;
  } 

  /*************************************************************************
      State       : *CLR
      Parameters  : -
      Description : Clears the current system error and return to 0
  *************************************************************************/
  else if (MESSAGE.state == "*clr") {
    SYSTEM_ERROR = 0x0000;
  } 

/*************************************************************************
      State       : *TIME?
      Parameters  : -
      Description : Requests the current time from the target [HH:MM:SS dd/mm/yy]
  *************************************************************************/
  else if (MESSAGE.state == "*time?") {
    STREAM.println(parseTime(hour()) + ":" + parseTime(minute()) + ":" + parseTime(second()) + " " + parseTime(day()) + "/" + parseTime(month()) + "/" + parseTime(year()));
  } 

  /*************************************************************************
      State       : *SYNC
      Parameters  : -
      Description : Synchronises the MCU time [HH,MM,SS,dd,mm,yy]
  *************************************************************************/
  else if (MESSAGE.state == "*sync") {
    setTime(MESSAGE.data[0].toInt(), MESSAGE.data[1].toInt(), MESSAGE.data[2].toInt(), MESSAGE.data[3].toInt(), MESSAGE.data[4].toInt(), MESSAGE.data[5].toInt());
    STREAM.println("Time Synchronised");
  } 

  /*************************************************************************
      State       : BAUD
      Parameters  : -
      Description : Sets the sniffer's BAUD rate
  *************************************************************************/
  else if (MESSAGE.state == "*baud") {
    Serial1.flush();
    Serial1.begin(MESSAGE.data[0].toInt());
    Serial2.flush();
    Serial2.begin(MESSAGE.data[0].toInt());
    COMMS_BAUD_RATE = MESSAGE.data[0].toInt();
  } 

  /*************************************************************************
      State       : BAUD?
      Parameters  : -
      Description : Get the currently configured BAUD rate
  *************************************************************************/
  else if (MESSAGE.state == "*baud?") {
    STREAM.println(String(COMMS_BAUD_RATE));
  } 

  /*************************************************************************
      State       : BYTES
      Parameters  : -
      Description : Gets the total number of sniffed bytes [TX,RX]
  *************************************************************************/
  else if (MESSAGE.state == "bytes") {
    STREAM.println(String(TX_BYTES_TOTAL) + "," + String(RX_BYTES_TOTAL));
  } 

  /*************************************************************************
      State       : -
      Parameters  : -
      Description : Invalid STATE called produce system error (2)
  *************************************************************************/
  else {
    SYSTEM_ERROR = UNKNOWN_STATE_CALLED_ERROR;
    STREAM.println("UNKNOWN_STATE_CALLED_ERROR");
  }
}

/*************************************************************************
    End of File : Messages.h
*************************************************************************/
