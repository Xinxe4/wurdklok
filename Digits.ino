
const int IT[] = { 0, 1, -1 };
const int IS[] = { 3, 4, -1 };
const int FIIF_M[] = { 21, 22, 23, 24, -1 };
const int TSIEN_M[] = { 15, 16, 17, 18, 19, -1 };
const int KERTIER[] = { 6, 7, 8, 9, 10, 11, 12, -1 };
const int HEALWEI[] = { 34, 35, 36, 37, 38, 39, 40, -1 };
const int FOAR[] = { 26, 27, 28, 29, -1 };
const int OER[] = { 30, 31, 32, -1 };
const int OERE[] = { 116, 117, 118, 119, -1 };

const int IEN[] = { 78,79,80, -1 };
const int TWA[] = { 95,96,97, -1 };
const int TRIJE[] = { 60,61,62,63,64, -1 };
const int FJOUWER[] = { 45,46,47,48,49,50,51, -1 };
const int FIIF[] = { 21,22,23,24, -1 };
const int SEIS[] = { 41,42,43,44, -1 };
const int SAN[] = { 90,91,92, -1 };
const int ACHT[] = { 110,111,112,113, -1 };
const int NJOGGEN[] = { 65,66,67,68,69,70,71, -1 };
const int TSIEN[] = { 76,77,78,79,80, -1 };
const int ALVE[] = { 100,101,102,103, -1 };
const int TOLVE[] = { 84,85,86,87,88, -1 };

const int IENEN[] = { 78,79,80,81,82, -1 };
const int TWAEN[] = { 95,96,97,98,99, -1 };
const int TRIJEN[] = { 60,61,62,63,64,65, -1 };
const int FJOUWEREN[] = { 45,46,47,48,49,50,51,52,53 -1 };
const int FIVEN[] = { 105,106,107,108,109, -1 };
const int SEIZEN[] = { 54,55,56,57,58,59, -1 };
const int SANEN[] = { 90,91,92,93,94, -1 };
const int ACHTEN[] = { 110,111,112,113,114,115, -1 };
const int NJOGGENEN[] = { 65,66,67,68,69,70,71,72,73, -1 };
const int TSIENEN[] = { 76,77,78,79,80,81,82, -1 };
const int ALVEN[] = { 100,101,102,103,104, -1 };
const int TOLVEN[] = { 84,85,86,87,88,89, -1 };

void show_current_time() {
  int hours;
  int minutes;
  
  int ledBits[NR_LEDS];
  memfill(ledBits, NR_LEDS, 0);

  get_RTC_time();
  hours = hour();
  minutes = minute();
  
  int reducedHour;
  int roundMinute = (minutes / 5) * 5;
 
  if (hours<=12) {
    reducedHour = hours;
  } else {
    reducedHour = hours - 12;
  }
 
  compose(IT, ledBits);
  compose(IS, ledBits);
 
  if (minutes < 5) {
    compose(OERE, ledBits);
  } else if (minutes < 10) {
    compose(FIIF_M, ledBits);
    compose(OER, ledBits);
  } else if (minutes < 15) {
    compose(TSIEN_M, ledBits);
    compose(OER, ledBits);
  } else if (minutes < 20) {
    compose(KERTIER, ledBits);
    compose(OER, ledBits);
  } else if (minutes < 25) {
    compose(TSIEN_M, ledBits);
    compose(FOAR, ledBits);
    compose(HEALWEI, ledBits);
    reducedHour++;
  } else if (minutes < 30) {
    compose(FIIF_M, ledBits);
    compose(FOAR, ledBits);
    compose(HEALWEI, ledBits);
    reducedHour++;
  } else if (minutes < 35) {
    compose(HEALWEI, ledBits);
    reducedHour++;
  } else if (minutes < 40) {
    compose(FIIF_M, ledBits);
    compose(OER, ledBits);
    compose(HEALWEI, ledBits);
    reducedHour++;
  } else if (minutes < 45) {
    compose(TSIEN_M, ledBits);
    compose(OER, ledBits);
    compose(HEALWEI, ledBits);
    reducedHour++;
  } else if (minutes < 50) {
    compose(KERTIER, ledBits);
    compose(FOAR, ledBits);
    reducedHour++;
  } else if (minutes < 55) {
    compose(TSIEN_M, ledBits);
    compose(FOAR, ledBits);
    reducedHour++;
  } else {
    compose(FIIF_M, ledBits);
    compose(FOAR, ledBits);
    reducedHour++;
  }
 
  if (roundMinute == 0) {
    switch (reducedHour) {
      case 0: compose(TOLVE, ledBits);
          break;
      case 1: compose(IEN, ledBits);
          break;
      case 2: compose(TWA, ledBits);
          break;
      case 3: compose(TRIJE, ledBits);
          break;
      case 4: compose(FJOUWER, ledBits);
          break;
      case 5: compose(FIIF, ledBits);
          break;
      case 6: compose(SEIS, ledBits);
          break;
      case 7: compose(SAN, ledBits);
          break;
      case 8: compose(ACHT, ledBits);
          break;
      case 9: compose(NJOGGEN, ledBits);
          break;
      case 10: compose(TSIEN, ledBits);
          break;
      case 11: compose(ALVE, ledBits);
          break;     
      case 12: compose(TOLVE, ledBits);
          break;    
    }  
  } else {
    switch (reducedHour) {
      case 0: compose(TOLVEN, ledBits);
          break;
      case 1: compose(IENEN, ledBits);
          break;
      case 2: compose(TWAEN, ledBits);
          break;
      case 3: compose(TRIJEN, ledBits);
          break;
      case 4: compose(FJOUWEREN, ledBits);
          break;
      case 5: compose(FIVEN, ledBits);
          break;
      case 6: compose(SEIZEN, ledBits);
          break;
      case 7: compose(SANEN, ledBits);
          break;
      case 8: compose(ACHTEN, ledBits);
          break;
      case 9: compose(NJOGGENEN, ledBits);
          break;
      case 10: compose(TSIENEN, ledBits);
          break;
      case 11: compose(ALVEN, ledBits);
          break;     
      case 12: compose(TOLVEN, ledBits);
          break;    
    }   
  }
 
  printMatrix(ledBits);
}

void set_led(int nr) {
  if(nr > NR_LEDS) { nr = NR_LEDS;}
  int ledBits[NR_LEDS];
  memfill(ledBits, NR_LEDS, 0);
  const int constNr[] = { nr, -1};
  compose(constNr, ledBits);
  printMatrix(ledBits);
}

void clear_matrix() {
  memfill(drawing, 150, 0);
  printMatrix(drawing);
}

void add_to_drawing(int led) {
  compose2(led, drawing);
  printMatrix(drawing);
}

static void compose(const int arrayToAdd[], int ledBits[]) {
  int pos;
  int i = 0;
  while ((pos = arrayToAdd[i++]) != -1) {
    ledBits[pos] = 1;
  }
}

static void compose2(int ledToAdd, int ledBits[]) {
   ledBits[ledToAdd] = 1;
}

void print_temperature() {
  char tc[3] = {0};
  get_temperature_char( tc );
  
  int ledBits[NR_LEDS];
  memfill(ledBits, NR_LEDS, 0);
  
  for (int i=0; i<3; i++) {
    if (i<2) {
      print_char_4x5(ledBits, i*5, 0, tc[i]);
    } else {
      print_char_4x5(ledBits, (i*5)+1, 0, tc[i]);
    }
  }

  compose2(84,ledBits);
  
  printMatrix(ledBits);
}


/**
Fill the given array with the given value.
As the Ardunio programming language does not initialize
arrays on the stack with a value, all arrays dynamically
created need to be filled with a default value manually.
Use this function to perform this.
@param array (out) the array to be filled
@param length the length of the array
@param value the value to fill array with
*/
void memfill(int array[], const int length, const int value) {
  for (int i = 0; i < length; i++) {
    array[i] = value;
  }
}


