#ifndef print_h
#define print_h

int initializePrinter();

int finishPrinter();

void drawCanvas(unsigned char R, unsigned char G, unsigned char B, unsigned char alpha);

void drawGameBackground();

void drawPix(int x, int y, unsigned char R, unsigned char G, unsigned char B, unsigned char alpha);

void drawPixSquare(int _x, int _y, int size, unsigned char R, unsigned char G, unsigned char B, unsigned char alpha);

void setColor(unsigned char R, unsigned char G, unsigned char B, unsigned char alpha);

void printToScreen();

int getXRes();
int getYRes();

#endif
