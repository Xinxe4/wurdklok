

void decodeBTCommand(String command) {
  //mySerial.write("Decoding...;");
  if (command == "on;") {
    mySerial.write("LED On;");
    digitalWrite(PORT_STATUS_LED, 0);
  } else if (command == "off;") {
    mySerial.write("LED Off;");
    digitalWrite(PORT_STATUS_LED, 1);
   } else if (command == "GA;") {
     mySerial.write("GA;");
     String str; char c[3];
     str = String(get_hours());
     str.toCharArray(c,3);
     mySerial.write(c);mySerial.write(";");
     str = String(get_minutes());
     str.toCharArray(c,3);
     mySerial.write(c);mySerial.write(";");
   } else if (command.startsWith("ST")) {
     mySerial.write("Set time:");
     String hrs = command.substring(2,4);
     String mins = command.substring(4,6);
     int h = decodeTwoString(hrs);
     int m = decodeTwoString(mins);
     set_hours(h);
     set_minutes(m);
     mySerial.write(";");
  }
}
  
  
 int decodeTwoString(String str) {
     char buf[3];
     str.toCharArray(buf,str.length()+1);
     int i = atoi(buf);
     return i;
 }


//Commands
// GA = Get alarm time (HHMM)
// GD = Get date (DDMMYY)
// GS = Get alarms state (0 = off, 1 = on)
// ST#### = Set time (HHMM)
// SA#### = Set alarm time (HHMM)
// SD###### = Set date (DDMMYY)
// AA# = Activate alarm (0 = off, 1 = on)

