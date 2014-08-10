#include "definities.h"
/* 
Wurdklok
 */
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

//char* commandBT;                // a string to hold incoming bluetooth command
//commandBT = (char*)malloc(64 * sizeof(char));
//commandBT = "";
boolean commandEnded = false;    // whether the command is completely received
static int currentMode;          // What mode the clock is in (clock, temperature, etc)

static int drawing[NR_LEDS];

void setup() {
  mySerial.begin(9600);
  hardware_initialize();
  digitalWrite(PORT_STATUS_LED, 1);
  sCmd.addCommand("ON",    LED_on);          // Turns LED on
  sCmd.addCommand("OFF",   LED_off);         // Turns LED off
  sCmd.addCommand("GT",    BT_GT); 
  sCmd.addCommand("GB",    BT_GB); 
  sCmd.addCommand("GM",    BT_GM);
  sCmd.addCommand("P",     processCommand);  // Converts two arguments to integers and echos them back
  sCmd.setDefaultHandler(unrecognized);      // Handler for command that isn't matched
  if (!RTC.time_is_set()) {set_RTC_time(2014,8,10,13,20,0);}
  show_current_time();
  if (!tempsensor.begin(0x1A)) {
    mySerial.println("Couldn't find MCP9808!");
  } else {
    tempsensor.write8( MCP9808_REG_RESOLUTION , MCP9808_RESOLUTION_00625);
  }
  currentMode = CLOCK_MODE;
  mySerial.print("Initiated;");
}

void loop() {
  
  static unsigned long loopCounter;
  
  if (loopCounter % LOOP_CLOCK == 0) {
    if (currentMode == CLOCK_MODE) {
      show_current_time();
    }
  }
  if (loopCounter % LOOP_ALARM == 0) {
    check_for_alarm();
  }
  if (loopCounter % LOOP_BRIGHTNESS == 0) {
    adjust_brightness();
  }
  if (loopCounter % LOOP_TEMPERATURE == 0) {
    read_temperature();
    if (currentMode == TEMPERATURE_MODE) {
      print_temperature();
    }
  }
  
  if (loopCounter % LOOP_BLUETOOTH == 0) {
        sCmd.readSerial(mySerial);  
  }
  
  delay(INTERVAL);
  loopCounter++;
}

void setCurrentMode(int mode) {
  currentMode = mode;
  if (mode == DRAW_MODE) {
    clear_matrix();
  }
}
  
