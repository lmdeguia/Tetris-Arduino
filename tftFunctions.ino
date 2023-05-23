#include "tftInit.h"
#include "Arduino.h"

void lcdWrite(uint8_t input) {
  // input can be command or data
  digitalWrite(WR, LOW);
  PORTA = input;
  digitalWrite(WR, HIGH);
}

void lcdWriteCommand(uint8_t command) {
  digitalWrite(CS, LOW);
  digitalWrite(RS, LOW);
  lcdWrite(command);
  digitalWrite(RS, HIGH);
  digitalWrite(CS, HIGH);
}

void lcdWriteData(uint8_t data) {
  digitalWrite(CS, LOW);
  lcdWrite(data);
  digitalWrite(CS, HIGH);
}


void lcdInit() {
  int resetDelay = 15; //milliseconds

  digitalWrite(RST, HIGH);
  delay(resetDelay);
  digitalWrite(RST, LOW);
  delay(resetDelay);
  digitalWrite(RST, HIGH);
  delay(resetDelay);

  digitalWrite(RD, HIGH);
  digitalWrite(WR, HIGH);
  digitalWrite(RS, HIGH);
  digitalWrite(CS, HIGH);

  lcdWriteCommand(ILI9341_VCOMCONTROL1); // VCOM control 1
  lcdWriteData(B11111111); // VCOMH
  lcdWriteData(B00000000); // VCOML


  // MEMCONTROL set up so (x, y) = (0, 0) is at the bottom left and BGR orientation is set;
  // portrait mode enabled where 8bit pins are at the top

  lcdWriteCommand(ILI9341_MEMCONTROL);
  lcdWriteData(DEFAULT_ORIENTATION);

  // select 16 bit pixel format (vs 18 bit pixel format)
  lcdWriteCommand(ILI9341_PIXELFORMAT);
  lcdWriteData(0x55);

  lcdWriteCommand(ILI9341_SLEEPOUT);
  delay(120);

  lcdWriteCommand(ILI9341_DISPLAYON);
  lcdWriteCommand(ILI9341_MEMORYWRITE);
}



void setAddress(int16_t x1, int16_t x2, int16_t y1, int16_t y2) {
  lcdWriteCommand(0x2a);

  lcdWriteData(x1 >> 8);
  lcdWriteData(x1);
  lcdWriteData(x2 >> 8);
  lcdWriteData(x2);

  lcdWriteCommand(0x2b);

  lcdWriteData(y1 >> 8);
  lcdWriteData(y1);
  lcdWriteData(y2 >> 8);
  lcdWriteData(y2);

  lcdWriteCommand(0x2c);
}




void drawHorizontalLine(uint16_t color, int x0, int y0, int width, int t) {
  setAddress(x0, x0 + width, y0, y0 + (t - 1));

  int n = t*(width + 1) - 1;
  for (int i = 0; i <= n; i += 1) {
    lcdWriteData(color >> 8);
    lcdWriteData(color);
  }
}


void drawVerticalLine(uint16_t color, int x0, int y0, int height, int t) {

  setAddress(x0, x0 + (t - 1), y0, y0 + height);

  int n = t*(height + 1) - 1;
  for (int i = 0; i <= n; i += 1) {
    lcdWriteData(color >> 8);
    lcdWriteData(color);
  }

}