
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
// MB#   = Move bat (pong, 0=up)

void unrecognized(const char * cmd) {
}
  
void LED_on() {
  digitalWrite(PORT_STATUS_LED, 0);
}

void LED_off() {
  digitalWrite(PORT_STATUS_LED, 1);
}

void processCommand() {

  char cmd[4];
  int a,b,c;
  char *arg;

  arg = sCmd.next();
  if (arg != NULL) {
    strcpy(cmd , arg);
  }

  arg = sCmd.next();
  if (arg != NULL) {
    a = atol(arg);
  }
  
  arg = sCmd.next();
  if (arg != NULL) {
    b = atol(arg);
  }
  
  arg = sCmd.next();
  if (arg != NULL) {
    c = atol(arg);
  }
  
  if (strcmp(cmd, "ST") == 0) {
      set_RTC_time(a, b, c);
      setCurrentMode(CLOCK_MODE);
      show_current_time();
  } else if (strcmp(cmd, "SM") == 0) {
      set_manual_brightness(a);
  } else if (strcmp(cmd, "SB") == 0) {
      set_brightness_value(a);
  } else if (strcmp(cmd, "MB") == 0) {
      moveBat(a);
  } else if (strcmp(cmd, "SS") == 0) {
      add_to_drawing(a);
  } else if (strcmp(cmd, "SD") == 0) {
      set_RTC_date(a, b, c);
  } else if (strcmp(cmd, "SA") == 0) {
      set_RTC_alarm(a, b);
  } else if (strcmp(cmd, "MD") == 0) {
      setCurrentMode(a);
  }
  mySerial.print(F("END;"));
}

void BT_GT() {
  mySerial.write("GT;");
  char tc[3] = {0};
  get_temperature_char( tc );
  mySerial.print(tc);
  sendLimChar();
}

void BT_GB() {
  mySerial.print("GB;");   
  mySerial.print(get_brightness_value());   
  sendLimChar();
} 

void BT_GM() {
  mySerial.print("GM;");
  mySerial.print(get_manual_brightness());
  sendLimChar();
} 

void BT_GA() {
  mySerial.print("GA;");
  mySerial.print("0000");
  sendLimChar();
}

void BT_GD() {
  mySerial.print("GD;");
  mySerial.print(day());sendLimChar();
  mySerial.print(month());sendLimChar();
} 

void sendLimChar() {
  mySerial.print(";");
}

//
//
//void decodeBTCommand(String command) {
//  //mySerial.write("Decoding...;");
//  digitalWrite(PORT_STATUS_LED, 0);
//  if (command == "on;") {
//    mySerial.write("LED On;");
//    digitalWrite(PORT_STATUS_LED, 0);
//  } 
//  else if (command == "off;") {
//    mySerial.write("LED Off;");
//    digitalWrite(PORT_STATUS_LED, 1);
//  } 
//  else if (command == "GA;") {
//    mySerial.write("GA;");
//    get_RTC_time();
//    String str;
//    str = String(hour());
//    mySerial.print(str);
//    mySerial.write(";");
//    str = String(minute());
//    mySerial.print(str);
//    mySerial.write(";");
//  } 
//  else if (command.startsWith("ST")) {
//    //mySerial.write("Set time:");
//    String hrs = command.substring(2,4);
//    String mins = command.substring(4,6);
//    int h = decodeString(hrs);
//    int m = decodeString(mins);
//    set_RTC_time(h, m, 0);
//    setCurrentMode(CLOCK_MODE);
//    show_current_time();
//    //mySerial.print(h);mySerial.write(":");mySerial.print(m);mySerial.write(";");
//  }
//  else if (command.startsWith("SD")) {
//    //mySerial.write("Set date:");
//    String day = command.substring(2,4);
//    String mon = command.substring(4,6);
//    String yea = command.substring(6,8);
//    int d = decodeString(day);
//    int m = decodeString(mon);
//    int y = decodeString(yea);
//    set_RTC_date(d, m, y);
//    show_current_time();
//    //mySerial.print(h);mySerial.write(":");mySerial.print(m);mySerial.write(";");
//  }  
//  else if (command == "GM;") {
//    mySerial.write("GM;");
//    mySerial.print(get_manual_brightness());
//    mySerial.write(";");
//  } 
//  else if (command.startsWith("SM")) {
//    //mySerial.write("Manual brightness:");
//    String toggle = command.substring(2,3);
//    boolean mb = decodeString(toggle);
//    set_manual_brightness(mb);
//    mySerial.write("GM;");
//    mySerial.print(get_manual_brightness());
//    mySerial.write(";");
//  } 
//  else if (command == "GB;") {
//    mySerial.write("GB;");
//    mySerial.print(get_brightness_value());
//    mySerial.write(";");
//  } 
//  else if (command == "PT;") {
//    setCurrentMode(TEMPERATURE_MODE);
//    print_temperature();
//  } 
//  else if (command.startsWith("SB")) {
//    //mySerial.write("Set brightness:");
//    String bright = command.substring(2,5);
//    int br = decodeString(bright);
//    set_brightness_value(br);
//    mySerial.write("GB;");
//    mySerial.print(get_brightness_value());
//    mySerial.write(";");
//  }
//  else if (command.startsWith("SS")) {
//    //mySerial.write("Set single led:");
//    String str_nr = command.substring(2,5);
//    int nr = decodeString(str_nr);
//    add_to_drawing(nr);
//  }
//  else if (command.startsWith("MD")) {
//    //mySerial.write("Set single led:");
//    String str_nr = command.substring(2,4);
//    int nr = decodeString(str_nr);
//    setCurrentMode(nr);
//  }
//  else if (command == "GT;") {
//    mySerial.write("GT;");
//    String str;
//    float tf = get_temperature();
//    tf = tf * 10;
//    int ti = (int)tf;
//    str = String(ti);
//    mySerial.print(str);
//    mySerial.write(";");
//  }
//   mySerial.write("END;");
//   digitalWrite(PORT_STATUS_LED, 1);
//}
//
//int decodeString(String str) {
//  char buf[str.length()+1];
//  str.toCharArray(buf,str.length()+1);
//  int i = atoi(buf);
//  return i;
//}



