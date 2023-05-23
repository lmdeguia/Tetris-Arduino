// referenced https://github.com/adafruit/Adafruit_ILI9341/blob/master/Adafruit_ILI9341.h


#define ILI9341_SOFTRESET 0x01
#define ILI9341_SLEEPIN 0x10
#define ILI9341_SLEEPOUT 0x11
#define ILI9341_NORMALDISP 0x13
#define ILI9341_INVERTOFF 0x20
#define ILI9341_INVERTON 0x21
#define ILI9341_GAMMASET 0x26
#define ILI9341_DISPLAYOFF 0x28
#define ILI9341_DISPLAYON 0x29
#define ILI9341_COLADDRSET 0x2A
#define ILI9341_PAGEADDRSET 0x2B
#define ILI9341_MEMORYWRITE 0x2C
#define ILI9341_PIXELFORMAT 0x3A
#define ILI9341_FRAMECONTROL 0xB1
#define ILI9341_DISPLAYFUNC 0xB6
#define ILI9341_ENTRYMODE 0xB7
#define ILI9341_POWERCONTROL1 0xC0
#define ILI9341_POWERCONTROL2 0xC1
#define ILI9341_VCOMCONTROL1 0xC5
#define ILI9341_VCOMCONTROL2 0xC7
#define ILI9341_MEMCONTROL 0x36
#define ILI9341_MADCTL 0x36

#define ILI9341_MADCTL_MY 0x80
#define ILI9341_MADCTL_MX 0x40
#define ILI9341_MADCTL_MV 0x20
#define ILI9341_MADCTL_ML 0x10
#define ILI9341_MADCTL_RGB 0x00
#define ILI9341_MADCTL_BGR 0x08
#define ILI9341_MADCTL_MH 0x04

#define DEFAULT_ORIENTATION B11001000

#define BLACK 0x0000
#define WHITE 0xFFFF
#define LIGHTGREY 0xC618  
#define DARKGREY 0x7BEF
#define CYAN 0x07FF 
#define DARKCYAN 0x03EF
#define RED 0xF800
#define BLUE 0x001F
#define MAGENTA 0xF81F 
#define PURPLE 0x780F
#define OLIVE 0x7BE0


#define RD A0
#define WR A1
#define RS A2
#define CS A3
#define RST A4



void lcdWrite(uint8_t input);
void lcdWriteCommand(uint8_t command);
void lcdWriteData(uint8_t data);
void lcdInit();
void setAddress(int16_t x1, int16_t x2, int16_t y1, int16_t y2);
void drawHorizontalLine(uint16_t color, int x0, int y0, int width, int t);
void drawVerticalLine(uint16_t color, int x0, int y0, int height, int t);



