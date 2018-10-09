/**
 * PhobicTris
 * 
 * for Arduino Mega 1280 and a 64x32 LED matrix panel
 * 
 * Modified version of RomanSixty's version:
 * https://github.com/RomanSixty/arduino-tetris
 */

#include <RGBmatrixPanel.h>
#include <BobaBlox.h>

// Joystick input
Button joyUp(5);
Button joyRight(6);
Button joyDown(7);
Button joyLeft(8);

#define CLK 11
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

// colors
#define BLACK  matrix.Color333(0, 0, 0)
#define GRAY   matrix.Color333(1, 1, 1)
#define YELLOW matrix.Color333(3, 2, 0)
#define BLUE   matrix.Color333(0, 0, 1)
#define GREEN  matrix.Color333(0, 1, 0)
#define ORANGE matrix.Color333(3, 1, 0)
#define RED    matrix.Color333(1, 0, 0)
#define PURPLE matrix.Color333(1, 0, 1)
#define CYAN   matrix.Color333(0, 1, 1)

// for positions on the panel
#define SCORE_POINTS 1
#define SCORE_LINES  2
#define SCORE_LEVEL  3

// for collision checking
#define ROTATE 1
#define LEFT   2
#define RIGHT  3
#define FALL   4

// bucket offset on the panel
#define BUCKET_OFFS_X 2
#define BUCKET_OFFS_Y 7

// Bucket dimensions
#define BUCKET_DEPTH 34
#define BUCKET_WIDTH 28

uint16_t bucket[BUCKET_DEPTH*BUCKET_WIDTH]; // Size of bucket: 952

unsigned long last_interaction =    0; // when was the last button pressed? 
unsigned long next_tick        =    0; // when will the next automatic step happen?
int           tick_length      = 1000; // how long does on step take? (decreases on higher levels)

// scores
byte level;
byte lines;
unsigned long points;

// current tetromino
byte     tetr_type, next_tetr_type;
uint16_t tetr_color, next_tetr_color;
byte     tetr_rotation;
int      tetr_offsX;
int      tetr_offsY;

bool game_over   = false;
bool key_pressed = false;

/**
 * those are the 7 different tetris bricks, each placed in a 4x4 square
 * set bits are the parts where a brick is solid
 * the four quartets represent the four directions a tetromino can rotate
 */
const PROGMEM uint16_t TETROMINOES[36] = {
  // X
  // X
  // X
  // X
  0b0000000011110000, 0b0100010001000100, 0b0000000011110000, 0b0100010001000100,

  // XX
  // XX
  //0b0000000001100110, 0b0000000001100110, 0b0000000001100110, 0b0000000001100110,
  102, 102, 102, 102, 

  // XX
  //  XX
  //0b0000000001100011, 0b00000000001001100100, 0b000001100011, 0b0000001001100100,
  99, 612, 99, 612,

  //  XX
  // XX
  //0b0000000001101100, 0b0000100011000100, 0b0000000001101100, 0b0000100011000100,
  108, 2244, 108, 2244,

  // X
  // X
  // XX
  //0b0000000001110100, 0b0000010001000110, 0b0000000000010111, 0b0000011000100010,
  116, 1094, 23, 1570,
  
  //  X
  //  X
  // XX
  //0b0000000011100010, 0b0000011001000100, 0b0000000010001110, 0b0000001000100110,
  226, 1604, 142, 550,

  //  X
  // XXX
  //0b0000000011100100, 0b0000010001100100, 0b0000010011100000, 0b0000010011000100
  228, 1124, 1248, 1220,

    // TESTING add of Tetrominoes
  // XXXX
  // XXXX
  // XXXX
  // XXXX
  //0b1111111111111111, 0b1111100110011111, 0b1010101010101010, 0b0101010101010101,
  65535, 63903, 43690, 21845,

  // TESTING add of Tetrominoes
  // XX
  // XX
  // XX
  // XX
  0b1100110011001100, 0b0000000011111111, 0b1100110011001100, 0b0000000011111111
};

const unsigned char PROGMEM phobic_bitmap[] = {
0xea, 0xee, 0xb8, 0xaa, 0xaa, 0xa0, 0xee, 0xac, 0xa0, 0x8a, 0xaa, 0xa0, 0x8a, 0xee, 0xb8, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
};    // 24x8 pixels
