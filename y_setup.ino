void setup() {
  Serial.begin(19200);
  matrix.setRotation(3);  // Rotate for portrait-mode 64x32
  matrix.begin();

  // draw the basic game setup

  matrix.fillScreen(BLACK);

  // Visual bucket
  matrix.drawLine(1, BUCKET_OFFS_Y, 1, BUCKET_DEPTH+BUCKET_OFFS_Y, GRAY);                            // Left |
  matrix.drawLine(30, BUCKET_OFFS_Y, 30, BUCKET_DEPTH+BUCKET_OFFS_Y, GRAY);                          // Right |
  matrix.drawLine(BUCKET_OFFS_X, BUCKET_DEPTH+BUCKET_OFFS_Y, 29, BUCKET_DEPTH+BUCKET_OFFS_Y, GRAY);  // Bottom _

  // preview box for next item
  matrix.drawLine(1, 43, 6, 43, GRAY);  // Top _
  matrix.drawLine(1, 48, 6, 48, GRAY);  // Bottom _
  matrix.drawLine(1, 44, 1, 47, GRAY);  // Left |
  matrix.drawLine(6, 44, 6, 47, GRAY);  // Right |

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
