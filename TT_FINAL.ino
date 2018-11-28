#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

 
#define PIN 6
 
// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


struct RGB {
  byte r;
  byte g;
  byte b;
};

RGB white = { 255, 255, 255 };
RGB red = { 255, 0, 0 };
RGB off = { 0, 0, 0 };

//initializes matrix
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(16, 16, PIN,
  NEO_MATRIX_TOP    + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);
 
//array of colors Text is shown in 
const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(255, 255, 0), matrix.Color(255, 0, 255), matrix.Color(255,255,255) };
/*-----------------------------------------------------------------------------------------------------------------------------------------
 * setup      - sets up parameters for matrix
 * 
 * parameters - none
 * 
 * returns    - null
-----------------------------------------------------------------------------------------------------------------------------------------*/
void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
}
 
int x     = matrix.width();
int pass  = 0;
int count = 0;
/*-----------------------------------------------------------------------------------------------------------------------------------------
 * loop       - main loop
 * 
 * parameters - none
 * 
 * returns    - null
-----------------------------------------------------------------------------------------------------------------------------------------*/
void loop(){
  loop1();
  crossFade({ 0, 0, 255 }, { 255, 0, 0 }, 60, 20);
  showImage(matrix.Color(255,255, 0 ),matrix.Color(225,0, 0 ));
  showImage(matrix.Color(255,255, 0 ),matrix.Color(200,0, 0 ));
  showImage(matrix.Color(255,255, 0 ),matrix.Color(150,0, 0 ));
  colorWipe(matrix.Color(0, 0, 0), 5);
}
/*-----------------------------------------------------------------------------------------------------------------------------------------
 * flip       - flips matrix values 
 * 
 * parameters - y value
 * 
 * returns    - flipped y value
-----------------------------------------------------------------------------------------------------------------------------------------*/
int flip(int y) 
{
  int flippedY = 15 - y;
  return flippedY;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------
 * loop1       - secondary loop
 *             - runs text accross matrix
 * 
 * parameters - text
 * 
 * returns    - null
-----------------------------------------------------------------------------------------------------------------------------------------*/
void loop1() 
{
  count=0;
  while (count < 105)
  {
    matrix.fillScreen(matrix.Color(0, 0, 0));
    matrix.setCursor(x, 0);
    matrix.print(F("Rush Theta Tau!"));
 
    if(--x < -88) 
    {
      x = matrix.width();
 
      if(++pass >= 5) pass = 0;
      matrix.setTextColor(colors[pass]);
    }
    matrix.show();
    delay(50);
    count= count+1;
  }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------
 * fadePixel  - main loop
 * 
 * parameters - int x (x values)
 *            - int y (y value) 
 *            - RGB startColor (starting color of pixel)
 *            - RGB endColor (ending color of pixel)
 *            - int steps (how many steps to transition from color to color
 *            - int wait (how long to wait before moving steps
 * 
 * returns    - null
-----------------------------------------------------------------------------------------------------------------------------------------*/
void fadePixel(int x, int y, RGB startColor, RGB endColor, int steps, int wait) {
  for(int i = 0; i <= steps; i++) 
  {
     int newR = startColor.r + (endColor.r - startColor.r) * i / steps;
     int newG = startColor.g + (endColor.g - startColor.g) * i / steps;
     int newB = startColor.b + (endColor.b - startColor.b) * i / steps;

     matrix.drawPixel(x, y, matrix.Color(newR, newG, newB));
     matrix.show();
     delay(wait);
  }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------
 * showImage  - displays the Theta Tau letters
 * 
 * parameters - unit32_t c (color of Theta Tau letters) 
 *            - unit32_t b (color of background)
 * 
 * returns    - null
-----------------------------------------------------------------------------------------------------------------------------------------*/
void showImage(uint32_t c, uint32_t b){
  //Theta
  matrix.drawPixel(2, 5, c);
  matrix.drawPixel(2,6,c);
  matrix.drawPixel(2,7,c);
  matrix.drawPixel(2,8,c);
  matrix.drawPixel(2,9,c);
  matrix.drawPixel(6,5,c);
  matrix.drawPixel(6,6,c);
  matrix.drawPixel(6,7,c);
  matrix.drawPixel(6,8,c);
  matrix.drawPixel(6,9,c);
  matrix.drawPixel(3,4,c);
  matrix.drawPixel(4,4,c);
  matrix.drawPixel(5,4,c);
  matrix.drawPixel(3,10,c);
  matrix.drawPixel(4,10,c);
  matrix.drawPixel(5,10,c);
  matrix.drawPixel(3,7,c);
  matrix.drawPixel(4,7,c);
  matrix.drawPixel(5,7,c);
  //Tau
  matrix.drawPixel(9,4,c);
  matrix.drawPixel(10,4,c);
  matrix.drawPixel(11,4,c);
  matrix.drawPixel(12,4,c);
  matrix.drawPixel(13,4,c);
  matrix.drawPixel(11,5,c);
  matrix.drawPixel(11,6,c);
  matrix.drawPixel(11,7,c);
  matrix.drawPixel(11,8,c);
  matrix.drawPixel(11,9,c);
  matrix.drawPixel(11,10,c);
  matrix.drawPixel(9,5,c);
  matrix.drawPixel(13,5,c);

  matrix.show();
  delay(750);
  matrix.fillScreen(b);
  
  matrix.show();
  delay(250);
}
/*-----------------------------------------------------------------------------------------------------------------------------------------
 * crossFade  - crossfades entire matrix, implements fadePixel()
 * 
 * parameters - RGB start color (starting color)
 *            - RGB end color (ending color)
 *            - int steps (how many steps to take between colors)
 *            - int wait (how long to wait in between steps)
 * 
 * returns    - null
-----------------------------------------------------------------------------------------------------------------------------------------*/
void crossFade(RGB startColor, RGB endColor, int steps, int wait) {
  for(int i = 0; i <= steps; i++)
  {
     int newR = startColor.r + (endColor.r - startColor.r) * i / steps;
     int newG = startColor.g + (endColor.g - startColor.g) * i / steps;
     int newB = startColor.b + (endColor.b - startColor.b) * i / steps;

     matrix.fillScreen(matrix.Color(newR, newG, newB));
     matrix.show();
     delay(wait);
  }
}
/*-----------------------------------------------------------------------------------------------------------------------------------------
 * colorWipe  - main loop
 * 
 * parameters - unit32_t c (color of wipe)
 *            - unit8_t wait (speed of colorWipe)
 * 
 * returns    - null
-----------------------------------------------------------------------------------------------------------------------------------------*/
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<16; i++) {
      matrix.drawPixel(0, i, c);
      matrix.show();
      delay(wait);
  }
  for(uint16_t i=0; i<=16; i++) {
      matrix.drawPixel(1, 16-i, c);
      matrix.show();
      delay(wait);
  }
  for(uint16_t i=0; i<16; i++) {
      matrix.drawPixel(2, i, c);
      matrix.show();
      delay(wait);
  }
  for(uint16_t i=0; i<=16; i++) {
      matrix.drawPixel(3, 16-i, c);
      matrix.show();
      delay(wait);
  }
  for(uint16_t i=0; i<16; i++) {
      matrix.drawPixel(4, i, c);
      matrix.show();
      delay(wait);
  }
  for(uint16_t i=0; i<=16; i++) {
      matrix.drawPixel(5, 16-i, c);
      matrix.show();
      delay(wait);
  }
  for(uint16_t i=0; i<16; i++) {
      matrix.drawPixel(6, i, c);
      matrix.show();
      delay(wait);
  }
  for(uint16_t i=0; i<=16; i++) {
      matrix.drawPixel(7, 16-i, c);
      matrix.show();
      delay(wait);
  }
  for(uint16_t i=0; i<16; i++) {
      matrix.drawPixel(8, i, c);
      matrix.show();
      delay(wait);
  }
  for(uint16_t i=0; i<=16; i++) {
      matrix.drawPixel(9, 16-i, c);
      matrix.show();
      delay(wait);
  }
  for(uint16_t i=0; i<16; i++) {
      matrix.drawPixel(10, i, c);
      matrix.show();
      delay(wait);
  }
  for(uint16_t i=0; i<=16; i++) {
      matrix.drawPixel(11, 16-i, c);
      matrix.show();
      delay(wait);
  }
  for(uint16_t i=0; i<16; i++) {
      matrix.drawPixel(12, i, c);
      matrix.show();
      delay(wait);
  }
  for(uint16_t i=0; i<=16; i++) {
      matrix.drawPixel(13, 16-i, c);
      matrix.show();
      delay(wait);
  }
  for(uint16_t i=0; i<16; i++) {
      matrix.drawPixel(14, i, c);
      matrix.show();
      delay(wait);
  }
  for(uint16_t i=0; i<=16; i++) {
      matrix.drawPixel(15, 16-i, c);
      matrix.show();
      delay(wait);
  }
}
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * * * END LINE * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 */
