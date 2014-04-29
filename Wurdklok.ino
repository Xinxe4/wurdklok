#include "definities.h"
/* 
Wurdklok
 */
#include <SoftwareSerial.h>
SoftwareSerial mySerial = SoftwareSerial(PORT_BT_TX,PORT_BT_RX); // (RX, TX)

String commandBT = "";           // a string to hold incoming bluetooth command
boolean commandEnded = false;    // whether the command is completely received


void setup() {
  hardware_initialize();
  mySerial.begin(9600);
  commandBT.reserve(64);
  show_current_time();
  mySerial.println("Initiated");  
}

void loop() {
  
  static unsigned long loopCounter;
  
  if (loopCounter % LOOP_CLOCK == 0) {
    show_current_time();
  }
  if (loopCounter % LOOP_ALARM == 0) {
    check_for_alarm();
  }
  if (loopCounter % LOOP_BRIGHTNESS == 0) {
    adjust_brightness();
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


