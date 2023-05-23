#include "tetrisSetup.h"
#include "tftInit.h"

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



