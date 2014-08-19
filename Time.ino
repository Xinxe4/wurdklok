
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
  setTime( RTC.get(ALARM1_ADDRESS) );
}

void check_for_alarm() {
  
}




