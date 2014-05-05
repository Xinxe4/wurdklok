

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
     String str;
     str = String(get_hours());
     mySerial.print(str);mySerial.write(";");
     str = String(get_minutes());
     mySerial.print(str);mySerial.write(";");
  } else if (command.startsWith("ST")) {
     //mySerial.write("Set time:");
     String hrs = command.substring(2,4);
     String mins = command.substring(4,6);
     int h = decodeString(hrs);
     int m = decodeString(mins);
     set_hours(h);
     set_minutes(m);
     //mySerial.print(h);mySerial.write(":");mySerial.print(m);mySerial.write(";");
  } else if (command == "GM;") {
     mySerial.write("GM;");
     boolean mb = get_manual_brightness();
     mySerial.print(mb);mySerial.write(";");
  } else if (command.startsWith("SM")) {
     //mySerial.write("Manual brightness:");
     String toggle = command.substring(2,3);
     boolean mb = decodeString(toggle);
     set_manual_brightness(mb);
     //mySerial.print(toggle);
     //mySerial.write(";");
  } else if (command.startsWith("SB")) {
     //mySerial.write("Set brightness:");
     String bright = command.substring(2,5);
     int br = decodeString(bright);
     set_brightness_value(br);
     //mySerial.print(br);
     //mySerial.write(";");
  }
}
  
 int decodeString(String str) {
     char buf[str.length()+1];
     str.toCharArray(buf,str.length()+1);
     int i = atoi(buf);
     return i;
 }


//Commands
// GA = Get alarm time (HHMM)
// SA#### = Set alarm time (HHMM)
// GD = Get date (DDMMYY)
// SD###### = Set date (DDMMYY)
// GS = Get alarms state (0 = off, 1 = on)
// ST#### = Set time (HHMM)
// GL# = Get alarm activated (0 = off, 1 = on)
// SL# = Activate alarm (0 = off, 1 = on)
// GM# = Get manual brightness setting (0 = auto, 1 = man)
// SM# = Set manual brightness setting (0 = auto, 1 = man)
// GB### = Get brightness val(0 = off, 255 = full)
// SB### = Set brightness val(0 = off, 255 = full)

