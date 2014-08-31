//Receive and send bluetooth commands from/to the Android app 

//Commands
// GA = Get alarm time (HH;MM;)
// SA = Set alarm time (P SA HH MM;)
// GD = Get date (DD;MM;YY;)
// SD = Set date (P SD DD MM YY;)
// AA = Get alarm activation state (0 = off, 1 = on)
// TA = Toggle alarm (P TA 0; (0 = off, 1 = on))
// ST = Set time (P ST HH MM SS;)
// GM = Get manual brightness setting (0 = auto, 1 = man)
// SM = Set manual brightness setting (P SM 0; (0 = auto, 1 = man))
// GB = Get brightness val(0 = off, 255 = full)
// SB = Set brightness val (P SB 0; (0 = off, 255 = full))
// GT = Get temperature
// SS = Set single LED [1-150] (P SS 1;)
// MD = Set current mode  (P MD 1;)
// PS = Pong score
// MB = Move bat (pong, 0=up)

// Process the command received via Bluetooth
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
  } else if (strcmp(cmd, "TA") == 0) {
      activate_alarm(a);
  } else if (strcmp(cmd, "MD") == 0) {
      setCurrentMode(a);
  } else if (strcmp(cmd, "RA") == 0) {
      reset_alarm();
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
  get_RTC_alarm();
  mySerial.print("GA;");
  mySerial.print(hour());sendLimChar();
  mySerial.print(minute());sendLimChar();
  mySerial.print("END;");
  get_RTC_time();
}

void BT_GD() {
  mySerial.print("GD;");
  mySerial.print(day());sendLimChar();
  mySerial.print(month());sendLimChar();
  mySerial.print(year());sendLimChar();
}

void BT_PS(byte sc) {
  mySerial.print("PS;");
  mySerial.print(sc);sendLimChar();
}

void BT_AA() {
  mySerial.print("AA;");
  mySerial.print(is_alarm_active());sendLimChar();
}

void BT_FR() {
    mySerial.print("FR;");
    mySerial.print(freeRam()); sendLimChar();
}
    
void sendLimChar() {
  mySerial.print(";");
}


void unrecognized(const char * cmd) {
}
  
void LED_on() {
  digitalWrite(PORT_STATUS_LED, 0);
}

void LED_off() {
  digitalWrite(PORT_STATUS_LED, 1);
}


