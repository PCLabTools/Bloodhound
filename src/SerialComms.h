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

/*************************************************************************
    End of File : SerialComms.h
*************************************************************************/
