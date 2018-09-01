/**
 * handle key presses for movement etc.
 */

void keys() {
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
