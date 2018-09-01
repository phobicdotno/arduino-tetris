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
      key_pressed = true;
  }
  
  if ( millis() - last_interaction < 200 )
    return;

  int left_right = analogRead(LEFT_RIGHT);
  int down_rotate = analogRead(DOWN_ROTATE);

  if ( left_right == 1023 ) {
    move_tetromino_right();
  }
  else if ( left_right == 0 ) {
    move_tetromino_left();
  }

  if ( down_rotate == 0 ) {
    move_tetromino_down();
  }
  
  else if ( down_rotate == 1023 ) {
    rotate_tetromino();
  }

    if ( game_over ) {
      game_over = false;
      reset();
    }
  else {
    key_pressed = false;
    last_interaction = 0;
  }
  }

/*
//Original

void keys() {
  if ( millis() - last_interaction < 200 )
    return;

  int keypress = analogRead(SWITCH);

  if ( keypress > 1020 ) {
    move_tetromino_right();
  }
  else if ( keypress > 990 ) {
    move_tetromino_down();
  }
  else if ( keypress > 680 ) {
    move_tetromino_left();
  }
  else if ( keypress > 490 ) {
    rotate_tetromino();
  }

  if ( keypress > 490 ) {
    // allow for faster reactions when key keeps being pressed
    if ( key_pressed )
      last_interaction = millis() - 100;
    else
      last_interaction = millis();

    key_pressed = LOW;

    if ( game_over ) {
      game_over = false;
      reset();
    }
  }
  else {
    key_pressed = false;
    last_interaction = 0;
  }
}


*/
