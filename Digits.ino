#include <ShiftRegister595.h>

bool displayTime;
int hours;
int minutes;

void show_current_time() {
  hours = get_hours();
  minutes = get_minutes();
  
  if (displayTime) {
    // show IT IS
  }
  
  if (minutes < 5) {
    // show OERE;
  } else if (minutes < 10) {
    // show FIIF;
    // show OER;
  } else if (minutes < 15) {
    // show TSIEN;
    // show OER;
  } else if (minutes < 20) {
    // show KERTIER;
    // show OER;
  } else if (minutes < 25) {
    // show TSIEN;
    // show FOAR;
    // show HEALWEI;
  } else if (minutes < 30) {
    // show FIIF;
    // show FOAR;
    // show HEALWEI;
  } else if (minutes < 35) {
    // show HEALWEI;
  } else if (minutes < 40) {
    // show FIIF;
    // show OER;
    // show HEALWEI;
  } else if (minutes < 45) {
    // show TSIEN;
    // show OER;
    // show HEALWEI;
  } else if (minutes < 50) {
    // show KERTIER;
    // show FOAR
    // show HEALWEI;
  } else if (minutes < 55) {
    // show TSIEN;
    // show FOAR;
  } else {
    // show FIIF;
    // show FOAR;
  }
  
  
  
}



