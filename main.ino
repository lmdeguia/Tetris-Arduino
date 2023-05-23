#include "Arduino.h"
#include "tftInit.h"
#include "tetrisSetup.h"


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
  if (currentRot == 0) {
    bottomValue = currentRow;
  } else if (currentRot == 2) {
    bottomValue = currentRow - 1;
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
  updateBottom();
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
  attachInterrupt(digitalPinToInterrupt(UP), upRoutine, RISING); 
  attachInterrupt(digitalPinToInterrupt(DOWN), downRoutine, RISING);  
}





