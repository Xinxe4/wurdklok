
void set_RTC_time(int y, int m, int d, int hh, int mm, int ss) {
  tmElements_t tmSet;
  tmSet.Year = y - 1970;
  tmSet.Month = m;
  tmSet.Day = d;
  tmSet.Hour = hh;
  tmSet.Minute = mm;
  tmSet.Second = ss;
  RTC.set(makeTime(tmSet), CLOCK_ADDRESS); // set the clock
}

void set_RTC_time(int hh, int mm, int ss) {
  tmElements_t tmSet;
  tmSet.Hour = hh;
  tmSet.Minute = mm;
  tmSet.Second = ss;
  RTC.set(makeTime(tmSet), CLOCK_ADDRESS); // set the clock
}

void set_RTC_date(int d, int m, int y) {
  tmElements_t tmSet;
  tmSet.Year = y - 1970;
  tmSet.Month = m;
  tmSet.Day = d;
  RTC.set(makeTime(tmSet), CLOCK_ADDRESS); // set the clock
}

void get_RTC_time() {
  setTime( RTC.get(CLOCK_ADDRESS) );
}

void set_RTC_alarm(int h, int m) {
  tmElements_t amSet;
  amSet.Hour = h;
  amSet.Minute = m;
  RTC.set(makeTime(amSet), ALARM1_ADDRESS); // set the clock
}

void get_RTC_alarm() {
  setTime( RTC.get(ALARM1_ADDRESS) );
}

boolean check_for_alarm() {
  if (digitalRead(PORT_ALARM)==HIGH) {
    LED_on();
    return true;
  } else {
    return false;
  }
}

void activate_alarm(int a) {
  (a>0) ? RTC.enableAlarm(ALARM1_ADDRESS) : RTC.disableAlarm(ALARM1_ADDRESS);
}

boolean is_alarm_active() {
  return RTC.alarm_is_set();
}

void reset_alarm() {
  return RTC.resetAlarms();
}



