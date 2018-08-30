void setup() {
  pinMode(SWITCH, INPUT);
  Serial.begin(9600);

  matrix.setRotation(3);  // Rotate for portrait-mode 64x32
  matrix.begin();

  // draw the basic game setup

  matrix.fillScreen(BLACK);

  // bucket
  matrix.drawLine(1, 5, 1, 22, GRAY);
  matrix.drawLine(12, 5, 12, 22, GRAY);
  matrix.drawLine(2, 22, 11, 22, GRAY);

  // preview box for next item
  matrix.drawLine(20, 3, 25, 3, GRAY);
  matrix.drawLine(20, 8, 25, 8, GRAY);
  matrix.drawLine(20, 4, 20, 7, GRAY);
  matrix.drawLine(25, 4, 25, 7, GRAY);

  // lv (= level)
  matrix.drawLine(14, 10+33, 14, 15+33, GRAY);
  matrix.drawLine(16, 12+33, 16, 15+33, GRAY);
  matrix.drawLine(18, 12+33, 18, 13+33, GRAY);
  matrix.drawPixel(17, 14+33, GRAY);

  // ln (= lines)
  matrix.drawLine(14, 17+33, 14, 22+33, GRAY);
  matrix.drawLine(16, 19+33, 16, 22+33, GRAY);
  matrix.drawLine(18, 20+33, 18, 22+33, GRAY);
  matrix.drawPixel(17, 19+33, GRAY);

  // pt (= points)
  matrix.drawLine(1, 25+33, 1, 29+33, GRAY);
  matrix.drawPixel(2, 25+33, GRAY);
  matrix.drawLine(2, 27+33, 3, 26+33, GRAY);
  matrix.drawLine(5, 25+33, 5, 28+33, GRAY);
  matrix.drawPixel(6, 26+33, GRAY);
  matrix.drawPixel(6, 29+33, GRAY);

  // initialize scores etc.
  reset();

  // and start dropping the first tetromino
  get_next_tetromino();

  tetr_type  = next_tetr_type;
  tetr_color = next_tetr_color;

  get_next_tetromino();
  preview_tetromino();

  drop_tetromino();
}
