/**
 * handle key presses for movement etc.
 */
unsigned long time_now = 0;
int holdTime = 500; // Millisecond delay

void keys() {
  // Joystick control
  if (joyUp.wasPressed()) {rotate_tetromino();}
  if (joyDown.wasPressed()) {move_tetromino_down();}
  if (joyLeft.wasPressed()) {move_tetromino_left();}
  if (joyRight.wasPressed()) {move_tetromino_right();}


  

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

    if ( game_over ) {
      game_over = false;
      reset();
    }
  }
}
