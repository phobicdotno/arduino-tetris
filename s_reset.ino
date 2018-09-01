/**
 * start a new game
 */
void reset() {
  // get the randomizer running
  unsigned long seed = 0;
  
  for ( byte i = 0; i < 32; i++ ) {
    seed = seed | ((analogRead(A4) & 0x01) << i);
  }

  randomSeed ( seed );

  tick_length = 1000;

  // empty bucket
  matrix.fillRect(2, 5, 10, 34, BLACK);

  // note: the top of the bucket corresponds to the floor on the panel
  // so it's upside down
  for ( byte i = 0; i < 34; i++ )
    for ( byte j = 0; j < 10; j++ )
      bucket[i*10+j] = BLACK;

  // reset scores
  level  = 1;
  lines  = 0;
  points = 0;

  LXLedPanelNumbers_write(level,  SCORE_LEVEL);
  LXLedPanelNumbers_write(lines,  SCORE_LINES);
  LXLedPanelNumbers_write(points, SCORE_POINTS);

  next_tick = millis() + tick_length;
}
