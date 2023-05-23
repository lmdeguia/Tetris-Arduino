#ifndef __TETRIS_SETUP__
#define __TETRIS_SETUP__

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

void fillScreen(uint16_t color);
void drawRectangleOutline(uint16_t color, int t, int x0, int y0, int height, int width);
void drawTetrisSquare(uint16_t fillColor, uint16_t borderColor, int row, int col, int* statusArray);

void checkOccupancy();
void dropTetrimino();

// orientation choices: {0, 1, 2, 3}

void drawTetrimino_I(uint16_t fillColor, uint16_t borderColor,
  int row, int col, int orientation, int* statusArray);





#endif