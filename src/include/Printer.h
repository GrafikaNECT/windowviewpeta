#ifndef Printer_h
#define Printer_h

using namespace std;

class Printer {
public:
	static int initializePrinter();

	static int finishPrinter();

	static void drawCanvas(unsigned char R, unsigned char G, unsigned char B, unsigned char alpha);

	static void drawGameBackground();

	static void drawPix(int x, int y, unsigned char R, unsigned char G, unsigned char B, unsigned char alpha);

	static void drawPixSquare(int _x, int _y, int size, unsigned char R, unsigned char G, unsigned char B, unsigned char alpha);

	static void setColor(unsigned char R, unsigned char G, unsigned char B, unsigned char alpha);

	static void PrintToScreen();

	static int getXRes();
	static int getYRes();
	
private:

};

#endif