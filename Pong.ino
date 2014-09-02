//Code for playing pong on the wordclock

const byte bsize = 2;
boolean showSplash;
byte AImove;
byte b1y, b2y, pts;
enum Dir{
        LEFT_DOWN = 1,
        LEFT,
        LEFT_UP,
        RIGHT_DOWN,
        RIGHT,
        RIGHT_UP
    };
    
enum Speed{
        FASTEST = 1,
        FAST,
        MEDIUM,
        SLOW,
        SLOWEST
    };    
    
struct{
    byte lastMove;
    byte x, y; /* positions */
    Speed spd; // speed
    Dir dir; /* contains information about what direction the ball should move in */
} ball;


void initPong() {
  pts = 0;
  AImove = 0;
  showSplash = true;
  b1y = 4;
  b2y = 4;
  ball.lastMove = 0;
  ball.x = 7;
  ball.y = 4;
  ball.dir = Dir(random(1,7));
  ball.spd = SLOWEST;
  showStartPong();
  BT_PS(pts);
}

void showStartPong() {
  boolean ledBits[NR_LEDS];
  memfill(ledBits, NR_LEDS, 0);
  
  char sp[4] = {'B','0','C','9'}; //pong
  
  for (int i=0; i<4; i++) {
      print_char_3x5(ledBits, i*4, 0, sp[i]);
  }
  
  printMatrix(ledBits);
}

void runPong() {
  if (!showSplash) {
    
    if (ball.lastMove == ball.spd) {
      ball.lastMove = 0;
      if (moveBall()) {
        //Ball dropped
        initPong();
      } else {
        updatePongScreen();
      }
    } else {
        ball.lastMove += 1;
    }
    
    if (AImove == (int)FASTEST) {
      moveAI();
      AImove = 0;
      updatePongScreen();
    } else {
      AImove += 1;
    }
  }
}

void updatePongScreen() {
    boolean ledBits[NR_LEDS];
    memfill(ledBits, NR_LEDS, 0);
    
    compose2(xyToLed(ball.x,ball.y),ledBits); //ball
    compose2(xyToLed(0,b1y),ledBits);   //bat
    compose2(xyToLed(0,b1y+1),ledBits); //bat     
    compose2(xyToLed(14,b2y),ledBits);  //bat
    compose2(xyToLed(14,b2y+1),ledBits);//bat     
    
    printMatrix(ledBits);
}
  
  
boolean moveBall() {
  boolean droppedBall = false;
  
  if (ball.x == 13 || ball.x == 1) {
    if (ballSaved()) {
      switch (ball.dir) {
        case RIGHT_DOWN: ball.x -= 1; ballToLeft();  break;
        case RIGHT_UP  : ball.x -= 1; ballToLeft();  break;
        case RIGHT     : ball.x -= 1; ballToLeft();  break;
        case LEFT_DOWN : ball.x += 1; ballToRight(); break;
        case LEFT_UP   : ball.x += 1; ballToRight(); break;
        case LEFT      : ball.x += 1; ballToRight(); break;
      }
      if (ball.spd>FASTEST) {
        ball.spd = (Speed) ((int)ball.spd-1);
      }
    } else {
      droppedBall = true;
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
  
  return droppedBall;
}

void ballToRight() { 
  byte r = random(100);
  if (r<40) {
    ball.dir = RIGHT_UP;
  } else if (r<80) {
    ball.dir = RIGHT_DOWN;
  } else {
    ball.dir = RIGHT;
  }
}
  
void ballToLeft() { 
  byte r = random(100);
  if (r<40) {
    ball.dir = LEFT_UP;
  } else if (r<80) {
    ball.dir = LEFT_DOWN;
  } else {
    ball.dir = LEFT;
  }
}

void moveAI() {
  if (ball.dir == RIGHT_UP || ball.dir == RIGHT || ball.dir == RIGHT_DOWN) {
    if (ball.y > b2y && b2y < 8) {
      b2y += 1;
    } else if (ball.y < b2y && b2y > 0) {
      b2y -= 1;
    }
  }
}

void moveBat(byte drct) {
  showSplash = false;
  if (drct == 0 && b1y > 0) {
    b1y -= 1;
  } else if (drct == 1 && b1y < 8) {
    b1y += 1;
  }
  updatePongScreen();
}

boolean ballSaved() {
  if (ball.x == 1) {
    if ((ball.y == b1y) || (ball.y ==(b1y+1)) || (ball.y == b1y-1 && ball.dir == LEFT_DOWN) || (ball.y == b1y+2 && ball.dir == LEFT_UP)) {
      BT_PS(++pts);
      return true;
    } else { 
      return false;
    }
  } else {
    return (ball.y == b2y || ball.y ==(b2y+1));
  }
}

byte xyToLed(byte x, byte y) {
 return (x + (y*LED_COLS)); 
}
