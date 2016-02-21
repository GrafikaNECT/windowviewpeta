#ifndef LINE_H
#define LINE_H

#include "Point.h"
#include "Texture.h"

typedef int OutCode;

class Line {
	Point p1, p2;
	Texture texture;
	
public:
	// Constructor
	Line(int x1, int y1, int x2, int y2, Texture t = Texture::createSingleColorTexture(0,0,0,0));
	Line(Point _p1, Point _p2, Texture t = Texture::createSingleColorTexture(0,0,0,0));
	Line() {Line(0,0,0,0);};
	
	// Getter
	Point getP1();
	Point getP2();
	int getX1();
	int getY1();
	int getX2();
	int getY2();
	
	// Operations
	void move(int dx, int dy);
	void scale(float s);
	void scale(float s, int x, int y);
	void scale(float s, Point p);
	void rotate(float t);
	void rotate(float t, int x, int y);
	void rotate(float t, Point p);
	
	OutCode ComputeOutCode(int x, int y, Point max, Point min);
	Line clip(Point min, Point max);

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
