

void decodeBTCommand(String command) {
  //mySerial.write("Decoding...;");
  if (command == "on;") {
    mySerial.write("LED On;");
    digitalWrite(PORT_STATUS_LED, 0);
  } 
  else if (command == "off;") {
    mySerial.write("LED Off;");
    digitalWrite(PORT_STATUS_LED, 1);
  } 
  else if (command == "GA;") {
    mySerial.write("GA;");
    String str;
    str = String(get_hours());
    mySerial.print(str);
    mySerial.write(";");
    str = String(get_minutes());
    mySerial.print(str);
    mySerial.write(";");
  } 
  else if (command.startsWith("ST")) {
    //mySerial.write("Set time:");
    String hrs = command.substring(2,4);
    String mins = command.substring(4,6);
    int h = decodeString(hrs);
    int m = decodeString(mins);
    set_hours(h);
    set_minutes(m);
    show_current_time();
    //mySerial.print(h);mySerial.write(":");mySerial.print(m);mySerial.write(";");
  } 
  else if (command == "GM;") {
    mySerial.write("GM;");
    mySerial.print(get_manual_brightness());
    mySerial.write(";");
  } 
  else if (command.startsWith("SM")) {
    //mySerial.write("Manual brightness:");
    String toggle = command.substring(2,3);
    boolean mb = decodeString(toggle);
    set_manual_brightness(mb);
    mySerial.write("GM;");
    mySerial.print(get_manual_brightness());
    mySerial.write(";");
  } 
  else if (command == "GB;") {
    mySerial.write("GB;");
    mySerial.print(get_brightness_value());
    mySerial.write(";");
  } 
  else if (command == "PT;") {
    setCurrentMode(TEMPERATURE_MODE);
    print_temperature();
  } 
  else if (command.startsWith("SB")) {
    //mySerial.write("Set brightness:");
    String bright = command.substring(2,5);
    int br = decodeString(bright);
    set_brightness_value(br);
    mySerial.write("GB;");
    mySerial.print(get_brightness_value());
    mySerial.write(";");
  }
  else if (command.startsWith("SS")) {
    //mySerial.write("Set single led:");
    String str_nr = command.substring(2,5);
    int nr = decodeString(str_nr);
    add_to_drawing(nr);
  }
  else if (command.startsWith("MD")) {
    //mySerial.write("Set single led:");
    String str_nr = command.substring(2,4);
    int nr = decodeString(str_nr);
    setCurrentMode(nr);
  }
  else if (command == "GT;") {
    mySerial.write("GT;");
    String str;
    float tf = get_temperature();
    tf = tf * 10;
    int ti = (int)tf;
    str = String(ti);
    mySerial.print(str);
    mySerial.write(";");
  }
   mySerial.write("END;");
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
// GT### = Get temperature
// SS### = Set single LED [1-150]
// MD##  = Set current mode
// PT    = Print temperature



