

void decodeBTCommand(String command) {
  mySerial.write("Decoding...");
  if (command == "on;") {
    mySerial.write("LED On");
    digitalWrite(STATUS_LED, 1);
  } else if (command == "off;") {
    mySerial.write("LED Off");
    digitalWrite(STATUS_LED, 0);
  }
}
  
  
  
  


//Commands
// GA = Get alarm time (HHMM)
// GD = Get date (DDMMYY)
// GS = Get alarms state (0 = off, 1 = on)
// ST#### = Set time (HHMM)
// SA#### = Set alarm time (HHMM)
// SD###### = Set date (DDMMYY)
// AA# = Activate alarm (0 = off, 1 = on)

