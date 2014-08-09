#include "definities.h"
/* 
Wurdklok
 */
#include <SPI.h>
#include <Wire.h>
#include <DS1337.h>
#include "Adafruit_MCP9808.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial = SoftwareSerial(PORT_BT_TX,PORT_BT_RX); // (RX, TX)
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
DS1337 RTC = DS1337();

String commandBT = "";           // a string to hold incoming bluetooth command
boolean commandEnded = false;    // whether the command is completely received
static int currentMode;          // What mode the clock is in (clock, temperature, etc)

static int drawing[NR_LEDS];

void setup() {
  mySerial.begin(9600);
  hardware_initialize();
  commandBT.reserve(64);
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
    while (mySerial.available()) {
      // get the new byte:
      char inChar = (char)mySerial.read(); 
      // add it to the inputString:
      commandBT += inChar;
      // if the incoming character is a newline, set a flag
      // so the main loop can do something about it:
      if (inChar == ';') {
        commandEnded = true;
      } 
    }
    if (commandEnded) {
      decodeBTCommand(commandBT); 
      commandBT = "";
      commandEnded = false;
    }
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
