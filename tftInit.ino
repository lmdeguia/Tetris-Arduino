#include "Arduino.h"
#include "tftInit.h"

// d7 to d0 connectred to pins 22 to 29 (PORTA on atmega 2560)
// https://docs.arduino.cc/hacking/hardware/PinMapping2560?_gl=1*1r8yhd2*_ga*MTkzNDU2NzA4MS4xNjgyNDc4ODQz*_ga_NEXN8H46L5*MTY4NDExNTY3NC4yMi4xLjE2ODQxMTcyMTkuMC4wLjA.


// following is derived from https://electronicseternit.wixsite.com/electronicsforlife/post/using-2-4-tft-lcd-display-without-library
// and datasheet for ili9341


#define XCL 119
#define XCR 120

#define YCB 159
#define YCT 160

#define GRID_X0 10
#define GRID_Y0 20
#define GRID_HEIGHT 280
#define GRID_WIDTH 140
#define GRIDSQUARE_DIMENSION 14

#define UP 2
#define RIGHT 3
#define DOWN 18
#define LEFT 19

// #define occupancyStatus bool[200]

int *occupancyStatus = new int[200];
int *tetriminoQueue = new int[200];


// piece movement interrupts: interrupt up (rotate )


void fillScreen(uint16_t color) {
  drawHorizontalLine(color, 0, 0, 239, 100);
  drawHorizontalLine(color, 0, 100, 239, 100);
  drawHorizontalLine(color, 0, 200, 239, 100);
  drawHorizontalLine(color, 0, 300, 239, 20);
}


void drawRectangleOutline(uint16_t color, int t, int x0, int y0, int height, int width) {
  drawVerticalLine(color, x0 - t, y0 - t, height + t - 1, t);
  drawHorizontalLine(color, x0 - t, y0 - t, width + 2*t - 1, t);

  drawVerticalLine(color, x0 + width, y0 - t, height + t - 1, t);
  drawHorizontalLine(color, x0 - t, y0 + height, width + 2*t - 1, t);
}


void drawTetrisSquare(uint16_t fillColor, uint16_t borderColor, int row, int col, int* statusArray) {

  drawHorizontalLine(
    fillColor, GRID_X0 + col*GRIDSQUARE_DIMENSION, 
    GRID_Y0 + row*GRIDSQUARE_DIMENSION, 
    GRIDSQUARE_DIMENSION-2, GRIDSQUARE_DIMENSION-1);

  drawRectangleOutline(
    borderColor, 1, GRID_X0 + col*GRIDSQUARE_DIMENSION, 
    GRID_Y0 + row*GRIDSQUARE_DIMENSION, 
    GRIDSQUARE_DIMENSION-1, GRIDSQUARE_DIMENSION-1);

  int idx = 10*row + col;
  statusArray[idx] = (fillColor == BLACK && borderColor == BLACK) ? 0 : 1;

}

void checkOccupancy() {

}

void dropTetrimino() {

}



// orientation choices: {0, 1, 2, 3}

void drawTetrimino_I(uint16_t fillColor, uint16_t borderColor,
  int row, int col, int orientation, int* statusArray) {

  switch (orientation) {
    case 0:
      drawTetrisSquare(fillColor, borderColor, row, col, statusArray);
      drawTetrisSquare(fillColor, borderColor, row, col + 1, statusArray);
      drawTetrisSquare(fillColor, borderColor, row, col + 2, statusArray);
      drawTetrisSquare(fillColor, borderColor, row, col + 3, statusArray);
      break;
    case 1:
      drawTetrisSquare(fillColor, borderColor, row + 1, col + 2, statusArray);
      drawTetrisSquare(fillColor, borderColor, row, col + 2, statusArray);
      drawTetrisSquare(fillColor, borderColor, row - 1, col + 2, statusArray);
      drawTetrisSquare(fillColor, borderColor, row - 2, col + 2, statusArray);
      break;

    case 2:
      drawTetrisSquare(fillColor, borderColor, row - 1, col , statusArray);
      drawTetrisSquare(fillColor, borderColor, row - 1, col + 1, statusArray);
      drawTetrisSquare(fillColor, borderColor, row - 1, col + 2, statusArray);
      drawTetrisSquare(fillColor, borderColor, row - 1, col + 3, statusArray);
      break;

    case 3:
      drawTetrisSquare(fillColor, borderColor, row + 1, col + 1, statusArray);
      drawTetrisSquare(fillColor, borderColor, row, col + 1, statusArray);
      drawTetrisSquare(fillColor, borderColor, row - 1, col + 1, statusArray);
      drawTetrisSquare(fillColor, borderColor, row - 2, col + 1, statusArray);
      break;
  }


}


int currentType = 0;
int currentRow = 18;
int currentCol = 3;
int currentRot = 1;

int bottomValue;
int* bottom = &bottomValue;

int leftValue;
int* left = &leftValue;

int rightValue;
int* right = &rightValue;


void updateBottom() {

  if (currentRot == 0 || currentRot == 2) {
    bottomValue = currentRow;
  } else{
    bottomValue = currentRow - 2;
  }

}



void upRoutine() {
  drawTetrimino_I(BLACK, BLACK, currentRow, currentCol, currentRot, occupancyStatus);
  currentRot += 1;
  if (currentRot > 3) {
    currentRot = 0;
  }
  drawTetrimino_I(CYAN, 0x07DF, currentRow, currentCol, currentRot, occupancyStatus);
}


void downRoutine() {
  updateBottom();

  if (*bottom == 0) {
    return;
  }
  drawTetrimino_I(BLACK, BLACK, currentRow, currentCol, currentRot, occupancyStatus);
  currentRow -= 1;
  drawTetrimino_I(CYAN, 0x07DF, currentRow, currentCol, currentRot, occupancyStatus);
}




void setup() {

  //int statusFlagVal = 0;
  //int* statusFlag = &statusFlagVal;
  

  for (int idx = 0; idx < 200; idx += 1) {
    occupancyStatus[idx] = 0;
  }


  DDRA = B11111111; // set all bits of PORTA to output
  DDRF = B00011111; // set first five bits of PORTF to output

  // execute lcd initialization routine
  lcdInit();
  uint16_t bgColor = BLACK;
  fillScreen(bgColor);

  // draw Tetris grid
  int color = WHITE;
  int t = 3;
  drawRectangleOutline(color, t, GRID_X0, GRID_Y0, GRID_HEIGHT, GRID_WIDTH);

  drawTetrimino_I(CYAN, 0x07DF, currentRow, currentCol, currentRot, occupancyStatus);

  

  



  // delete tetriminoQueue;
  delete occupancyStatus;
}








void loop() {
  attachInterrupt(digitalPinToInterrupt(DOWN), downRoutine, RISING);  
}





