/* 
Fryske Wurdklok
 - by Rinze
 
Main arduino code. Includes the header files, setup and loop functions.

 
 */
#include "definities.h"
#include <SerialCommand.h>
#include <SPI.h>
#include <Wire.h>
#include <DS1337RTC.h>
#include <Time.h>
#include "Adafruit_MCP9808.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial = SoftwareSerial(PORT_BT_TX,PORT_BT_RX); // (RX, TX)
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
SerialCommand sCmd;     // SerialCommand object


static int currentMode;          // Keeps track of what mode the clock is in (clock, temperature, etc)
int togg_maxmin = true;          // Toggles between max & min temperature
static boolean drawing[NR_LEDS]; // Vector representing the on/off state of each LED


void setup() {
  mySerial.begin(38400);
  hardware_initialize();
  digitalWrite(PORT_STATUS_LED, 1);
  sCmd.addCommand("ON",    LED_on);          // Turns LED on
  sCmd.addCommand("OFF",   LED_off);         // Turns LED off
  sCmd.addCommand("GT",    BT_GT); 
  sCmd.addCommand("GB",    BT_GB);
  sCmd.addCommand("GA",    BT_GA);
  sCmd.addCommand("GM",    BT_GM);
  sCmd.addCommand("AA",    BT_AA);
  sCmd.addCommand("FR",    BT_FR);
  sCmd.addCommand("P",     processCommand);  // Converts two arguments to integers and echos them back
  sCmd.setDefaultHandler(unrecognized);      // Handler for command that isn't matched
  if (!RTC.time_is_set()) {set_RTC_time(2014,8,10,13,20,0);}
show_current_time();
  if (!tempsensor.begin(0x1A)) {
    mySerial.println(F("No MCP9808!"));
  } else {
    tempsensor.write8( MCP9808_REG_RESOLUTION , MCP9808_RESOLUTION_00625);
  }
  currentMode = CLOCK_MODE;
  mySerial.print(F("Init;"));
}


void loop() {
  static unsigned long loopCounter;
  
  if (loopCounter % LOOP_2SEC == 0) {
    if (currentMode == CLOCK_MODE) {
      show_current_time();
    } else if (currentMode == TEMP_MINMAX_MODE) {
      togg_maxmin = !togg_maxmin;
      print_maxmin(togg_maxmin);
    }
  }
  if (loopCounter % LOOP_20S == 0) {
    check_for_alarm();
  }
  if (loopCounter % LOOP_1SEC == 0) {
    read_temperature();
    if (currentMode == TEMPERATURE_MODE) {
      print_temperature();
    }
    adjust_brightness();
  }
  if (loopCounter % LOOP_70MS == 0) {
     if (currentMode == PONG_MODE ) {
       runPong();
     }
  }
  if (loopCounter % LOOP_20MS == 0) {
        sCmd.readSerial(mySerial);  
  }
  delay(INTERVAL);
  loopCounter++;
}

void setCurrentMode(int mode) {
  currentMode = mode;
  if (mode == DRAW_MODE) {
    clear_matrix();
  } else if (mode == CLOCK_MODE) {
    show_current_time();
  } else if (currentMode == TEMPERATURE_MODE) {
    print_temperature();
  } else if (currentMode == TEMP_MINMAX_MODE) {
    print_maxmin(togg_maxmin);
  } else if (currentMode == DATE_MODE) {
    show_date();
  } else if (currentMode == PONG_MODE) {
    initPong();
  }
}

int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
  
