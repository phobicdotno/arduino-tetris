/**
 * handle key presses for movement etc.
 */
unsigned long timeNowDown = 0;
unsigned long timeNowLeft = 0;
unsigned long timeNowRight = 0;
int holdTime = 1000; // Millisecond delay
int holdTimeFaster = 100; // Millisecond delay

void keys() {
  // Joystick control
  if (joyUp.wasPressed()) {rotate_tetromino();}
  if (joyDown.wasPressed()) {move_tetromino_down();}
  if (joyLeft.wasPressed()) {move_tetromino_left();}
  if (joyRight.wasPressed()) {move_tetromino_right();}

  // Move faster if a direction is hold down
//  if (joyRight.isDown()) {
//    if(millis() > timeNowRight + holdTime){
//        timeNowRight = millis();
//        move_tetromino_right();
//    }
//  }
//
//  if (joyLeft.isDown()) {
//    if(millis() > timeNowLeft + holdTime){
//        timeNowLeft = millis();
//        move_tetromino_left();
//    }
//  }

  if (joyDown.isDown()) {
    if(millis() > timeNowDown + holdTimeFaster){
        timeNowDown = millis();
        move_tetromino_down();
    }
  }

  // Serial line control / keyboard input
  if (Serial.available() > 0) {
    int inByte = Serial.read();
    switch (inByte) {
      case 'd':
        move_tetromino_right();
        break;
      case 'a':
        move_tetromino_left();
        break;
      case 'w':
        rotate_tetromino();
        break;
      case 's':
        move_tetromino_down();
        break;
      case 'r':
        reset();
        break;
    }

  }

    if ( game_over ) {
      game_over = false;
      reset();
    }
}
