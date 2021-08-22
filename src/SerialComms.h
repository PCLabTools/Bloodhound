/*************************************************************************
    File        : SerialComms.h
    Description : Serial communications definition
*************************************************************************/

#include "MessageParser.h"
MessageParser uart_comms;
#include "Messages.h"

String readStream(Stream &STREAM) {
  String inputStream = "";
  while (STREAM.available()) {
    char inChar = (char)STREAM.read();
    inputStream += inChar;
  }
  return inputStream;
}

void serialEvent() {
  Message currentMessage = uart_comms.parse(readStream(Serial));
  if (currentMessage.state != "") {
    handleMessage(Serial, currentMessage);
    currentMessage.state = "";
  }
}

void serialEvent1() {
  while (Serial1.available()) {
    TX_BUFFER[TX_BUFFER_POINTER] = Serial1.read();
    TX_BUFFER_POINTER++;
    TX_BYTES_TOTAL++;
  }
}

void serialEvent2() {
  while (Serial2.available()) {
    RX_BUFFER[RX_BUFFER_POINTER] = Serial2.read();
    RX_BUFFER_POINTER++;
    RX_BYTES_TOTAL++;
  }
}

/*************************************************************************
    End of File : SerialComms.h
*************************************************************************/
