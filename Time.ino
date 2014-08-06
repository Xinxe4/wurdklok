
int hh = 0;
int mm = 0;
int ss = 0;

void set_RTC_time(int h, int m, int s) {
    RTC.readTime();
    RTC.setSeconds(s);
    RTC.setMinutes(m);
    RTC.setHours(h);
    RTC.writeTime();  
}

void set_RTC_date(int D, int M, int Y) {
    RTC.readTime();
    RTC.setDays(D);
    RTC.setMonths(M);
    RTC.setYears(Y); // 2-digit or 4-digit years are supported
    RTC.writeTime();  
}

void check_for_alarm() {
  
}


