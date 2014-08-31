/**
  Functions for rendering fonts on the LED display.
*/

#include "fontdef.h"

/**
  Extracts the font definition for a given character from the font array.
  
  @param (out) data the bytes of the character
  @param (in) c the character to extract font information for
  @param (in) font the font definition
  @param (in) height the height of one character in the font in pixel 
*/
void character_definition(byte data[], const char c, const byte font[], const int height) {
  
  int offset = 0;
  
  if (c >= '0' && c <= '9') {
    offset = c - '0';
  }
  else if (c >= 'A' && c <= 'Z') {
    offset = c - 'A' + 10;
  }
  else if (c == '?') {
    offset = 36;
  }
  else if (c == ':') {
    offset = 37;
  }
  else {
    offset = 38;
  }
  
  for (int i = 0; i < height; i++) {
    data[i] = font[(offset * height) + i];
  }
}


/**
  Add a character from the 4x5 font to the led array at the given position.
  
  Positions outside of the LED array will be silently ignored.
  
  @param (out) ledBits bits for the LEDs (will NOT be cleared)
  @param (in) xpos horizontal position of the characters left upper edge 
              (starts at 0)
  @param (in) ypos vertical position of the characters left upper edge 
              (starts at 0)
  @param (in) c the character to display
*/  
void print_char_4x5(boolean ledBits[], const int xpos, const int ypos, const char c) {
  print_char(ledBits, xpos, ypos, c, CHAR_SET_4x5, 4, 5);
}

/**
  Add a character from the 3x5 font to the led array at the given position.
  
  Positions outside of the LED array will be silently ignored.
  
  @param (out) ledBits bits for the LEDs (will NOT be cleared)
  @param (in) xpos horizontal position of the characters left upper edge 
              (starts at 0)
  @param (in) ypos vertical position of the characters left upper edge 
              (starts at 0)
  @param (in) c the character to display
*/  
void print_char_3x5(boolean ledBits[], const int xpos, const int ypos, const char c) {
  print_char(ledBits, xpos, ypos, c, CHAR_SET_3x5, 3, 5);
}

void print_char_7x4(boolean ledBits[], const int xpos, const int ypos, const char c) {
  print_char(ledBits, xpos, ypos, c, CHAR_SET_7x4, 7, 4);
}

/**
  Add a charcter from to the led array at the given position.
  
  Positions outside of the LED array will be silently ignored.
  
  @param (out) ledBits bits for the LEDs (will NOT be cleared)
  @param (in) xpos horizontal position of the characters left upper edge 
              (starts at 0)
  @param (in) ypos vertical position of the characters left upper edge 
              (starts at 0)
  @param (in) c the character to display
  @param (in) font font definition
  @param (in) width width of the font in pixel
  @param (in) height height of the font in pixel
*/  

void print_char(boolean ledBits[], const int xpos, const int ypos, const char c, 
    const byte font[], const int width, const int height) {

  byte data[height];  
  character_definition(data, c, font, height); 
    
  byte x = 0;
  byte y = 0;
  
  for (byte i = 0; i < height; i++) {
    for (byte k = 0; k < width; k++) {
    
      if ((data[i] & (1 << k)) != 0) {
        
        byte effectiveX = xpos + x;
        byte effectiveY = ypos + y;
        
        if ((effectiveX < LED_COLS) && (effectiveY < LED_ROWS) && (effectiveX >= 0) && (effectiveY >= 0)) { 
          byte ledIndex = (effectiveY) * LED_COLS + (effectiveX);
          ledBits[ledIndex] = 1;
        }
      }
    
      x++;
    
      if (x >= width) {
        x = 0;
        y++;
      }
    }
  }
}

///**
//  Scroll a text on the screen.
//  
//  @param (in) text the text to be scrolled
//  @param (in) delayInMilli delay for the scrolling in milliseconds
//*/
//void scroll_text_8x8(const char* text, int delayInMilli) {
//  char* pos;
//  int ledBits[NUMBER_OF_LEDS];
// 
//  int length = 0;
//  pos = (char*) text;
//  while (*pos++) length++;
//  
//  for (int xpos = LED_COLUMNS; xpos > length * -9; xpos--) {
//    memfill(ledBits, NUMBER_OF_LEDS, 0);
//    
//    int offset = 0;
//    pos = (char*) text;
//    while (*pos) {
//      print_char_8x8(ledBits, xpos + (8 * offset++), 1, *pos++);
//    }
//    
//    send_to_shift_registers(ledBits);
//  }
//}


