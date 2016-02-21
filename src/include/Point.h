#ifndef Point_h
#define Point_h

#include "Transformable.h"

class Point:public Transformable{
public:
	// Constructor
	Point(int _x, int _y);
	Point() { Point(0,0); };

	// Getter
	int getX() const;
	int getY() const;

	// Setter
	void setX(int _x);
	void setY(int _y);

	// Operations
	void rotate(float rotateDeg);
	void scale(float scaleX, float scaleY);
	void translate(int deltaX, int deltaY);

private:
	int x;
	int y;
};

#endif
