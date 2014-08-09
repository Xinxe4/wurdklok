
void hardware_initialize() {
 //Initialize ports
  pinMode(PORT_STATUS_LED, OUTPUT);
  pinMode(PORT_MTX_CLK, OUTPUT);
  pinMode(PORT_MTX_DATA, OUTPUT);
  pinMode(PORT_MTX_LOAD, OUTPUT);
  pinMode(PORT_LIGHT_SENSOR, INPUT);
  
 //Initialize LED matrix
  SPI.setBitOrder(MSBFIRST);
  SPI.begin();
  maxTransferDupl(0x00, 0x00);
  maxTransferDupl(0x0F, 0x00);
  // Enable no decode
  maxTransferDupl(0x09, 0x00);
  // Use lowest intensity
  maxTransferDupl(0x0A, 0x02);
  // Only scan 8 digits
  maxTransferDupl(0x0B, 0x07);
  // Turn on chip
  maxTransferDupl(0x0C, 0x01);
  //Fill shift registers with zeroes
   for (uint8_t i = 1; i<9; i++) {
     maxTransferDupl(i, 0);
   }
   for (uint8_t i = 1; i<9; i++) {
     maxTransferDupl(i, 255);
     maxTransferDupl(i-1, 0x00);
     delay(100);
   }
   maxTransferDupl(0x08, 0x00);
   
  RTC.start();
  if(!RTC.time_is_set()) // set a time, if none set already...
  {
    RTC.setSeconds(0);
    RTC.setMinutes(0);
    RTC.setHours(0);
    RTC.setDays(1);
    RTC.setMonths(1);
    RTC.setYears(2000);
    RTC.writeTime();
  }
}

void printMatrix(const int ledBits[]) {
  uint8_t arr1 = 0;
  uint8_t arr2 = 0;
  for (uint8_t r=0; r<LED_ROWS; r++) {
    arr1 = 0;
    arr2 = 0;
    for (uint8_t c=0; c<LED_COLS; c++) {
      if (ledBits[c+(r*LED_COLS)]==1) {
        if (c<7) {
          bitSet(arr2,c+1); // +1 because only 7 columns of MAX2 are used
        } else {
          bitSet(arr1,c-7);
        }
      }
    }
    maxTransfer2(r+1, arr1, r+1, arr2);
  }
}

/*
* Transfers data to a MAX7219/MAX7221 register.
*
* @param address The register to load data into
* @param value Value to store in the register
*/
void maxTransferDupl(uint8_t address, uint8_t value) {
// Expects 2 cascaded chips, send same commands to both
// Ensure LOAD/CS is LOW
digitalWrite(PORT_MTX_LOAD, LOW);
// Send the register address
SPI.transfer(address);
// Send the value
SPI.transfer(value);
// Send the register address
SPI.transfer(address);
// Send the value
SPI.transfer(value);
// Tell chip to load in data
digitalWrite(PORT_MTX_LOAD, HIGH);
}

void maxTransfer2(uint8_t address1, uint8_t value1, uint8_t address2, uint8_t value2) {
// Expects 2 cascaded chips, sends different commands to both
// Ensure LOAD/CS is LOW
digitalWrite(PORT_MTX_LOAD, LOW);
// Send the register address
SPI.transfer(address2);
// Send the value
SPI.transfer(value2);
// Send the register address
SPI.transfer(address1);
// Send the value
SPI.transfer(value1);
// Tell chip to load in data
digitalWrite(PORT_MTX_LOAD, HIGH);
}
