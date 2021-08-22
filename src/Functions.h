/*************************************************************************
    File        : Functions.h
    Description : File containing general purpose functions
*************************************************************************/

String parseTime(int TIME) {
  String returnString = String(TIME);
  if (returnString.length() < 2) {
    returnString = "0" + returnString;
  }
  return returnString;
}

/*************************************************************************
    End of File : Functions.h
*************************************************************************/
