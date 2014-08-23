
const byte bsize = 2;
byte b1y, b2y, pts;
enum Dir{
        LEFT_DOWN = 1,
        LEFT,
        LEFT_UP,
        RIGHT_DOWN,
        RIGHT,
        RIGHT_UP
    };
    
struct{
    byte x, y; /* positions */
    byte spd; // speed
    Dir dir; /* contains information about what direction the ball should move in */
} ball;


void initPong() {
  b1y = 4;
  b2y = 1;
  ball.x = 7;
  ball.y = 4;
  ball.dir = LEFT_DOWN;
  clear_matrix();
}

void runPong() {
  boolean ledBits[NR_LEDS];
  memfill(ledBits, NR_LEDS, 0);
  
  moveBall();
  
  compose2(xyToLed(ball.x,ball.y),ledBits); //ball
  compose2(xyToLed(0,b1y),ledBits);   //bat
  compose2(xyToLed(0,b1y+1),ledBits); //bat
  compose2(xyToLed(14,b2y),ledBits);  //bat
  compose2(xyToLed(14,b2y+1),ledBits);//bat
  
  printMatrix(ledBits);
}

void moveBall() {
  if (ball.x == 13 || ball.x == 1) {
    if (ballSaved()) {
      switch (ball.dir) {
        case RIGHT_DOWN: ball.x -= 1; ball.dir = LEFT_DOWN; break;
        case RIGHT_UP  : ball.x -= 1; ball.dir = LEFT_UP;   break;
        case RIGHT     : ball.x -= 1; ball.dir = LEFT_UP;   break;
        case LEFT_DOWN : ball.x += 1; ball.dir = RIGHT_DOWN; break;
        case LEFT_UP   : ball.x += 1; ball.dir = RIGHT_UP;   break;
        case LEFT      : ball.x += 1; ball.dir = RIGHT_UP;   break;
      }
    } else {
      initPong();
    }
  } else { //Ball in middle
      if (ball.dir == RIGHT_UP || ball.dir == RIGHT || ball.dir == RIGHT_DOWN) {
        ball.x += 1;
      } else {
        ball.x -= 1;
      }
  }

  //Ball at top/bottom
  if (ball.y == 0 || ball.y == 9) { 
     switch (ball.dir) {
      case RIGHT_DOWN: ball.y -= 1; ball.dir = RIGHT_UP;   break;
      case RIGHT_UP  : ball.y += 1; ball.dir = RIGHT_DOWN; break;
      case LEFT_DOWN : ball.y -= 1; ball.dir = LEFT_UP;    break;
      case LEFT_UP   : ball.y += 1; ball.dir = LEFT_DOWN;  break;
    }
  } else {
    if (ball.dir == LEFT_UP || ball.dir == RIGHT_UP) {
      ball.y -= 1;
    } else if (ball.dir == LEFT_DOWN || ball.dir == RIGHT_DOWN) {
      ball.y += 1;
    }
  }
}

void moveBat(byte drct) {
 if (drct == 0 && b1y > 0) {
   b1y -= 1;
 } else if (drct == 1 && b1y < 8) {
   b1y += 1;
 }
}

boolean ballSaved() {
  if (ball.x == 1) {
    return (ball.y == b1y || ball.y ==(b1y+1));
  } else {
    return (ball.y == b2y || ball.y ==(b2y+1));
  }
}

byte xyToLed(byte x, byte y) {
 return (x + (y*LED_COLS)); 
}
