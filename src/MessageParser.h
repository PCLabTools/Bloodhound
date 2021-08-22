/*************************************************************************
    File        : MessageParser.h
    Description : Parses stream data and formats into message
    Date        : 31st July 2021
    Author      : Larry Colvin
    Contact     : larry.colvin@dyson.com
*************************************************************************/

#define MAX_DATA_ELEMENTS 10

struct Message {
  String state;
  String data[MAX_DATA_ELEMENTS];
};

#ifndef MessageParser_h

  #define MessageParser_h

  class MessageParser {
    public:
      MessageParser(String DELIMITER = "::", String DATA_DELIMITER = ",", String END_OF_MESSAGE = "\n");
      Message parse(String RAW_STRING);
      String serialise(Message MESSAGE);
             
     private:
      String _DELIMITER;
      String _DATA_DELIMITER;
      String _END_OF_MESSAGE;
      String _BUFFER;
  };

#endif

/*************************************************************************
    End of File : MessageParser.h
*************************************************************************/