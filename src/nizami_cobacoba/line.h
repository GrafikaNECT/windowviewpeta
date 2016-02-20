#ifndef LINE_H
#define LINE_H

#include "point.h"
#include "texture.h"

typedef int OutCode;

class line {
	point p1, p2;
	Texture texture;
	
public:
	// Constructor
	line(int x1, int y1, int x2, int y2, Texture t = Texture::createSingleColorTexture(0,0,0,0));
	line(point _p1, point _p2, Texture t = Texture::createSingleColorTexture(0,0,0,0));
	line() {line(0,0,0,0);};
	
	// Getter
	point getP1();
	point getP2();
	int getX1();
	int getY1();
	int getX2();
	int getY2();
	
	// Operations
	void move(int dx, int dy);
	void scale(float s);
	void scale(float s, int x, int y);
	void scale(float s, point p);
	void rotate(float t);
	void rotate(float t, int x, int y);
	void rotate(float t, point p);
	
	OutCode ComputeOutCode(int x0, int x1, int y0, int y1);
	line clip(int x0, int x1, int y0, int y1);

	// Graphics
	void draw();

	private:

//UNTUK CLIPPING
static const int INSIDE = 0; // 0000
static const int LEFT = 1;   // 0001
static const int RIGHT = 2;  // 0010                      
static const int BOTTOM = 4; // 0100
static const int TOP = 8;    // 1000

};


#endif // LINE_H
