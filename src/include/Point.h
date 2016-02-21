#ifndef Point_h
#define Point_h

#include "Transformable.h"

using namespace std;

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
	void rotate(float t, int cx, int cy);
	void rotate(float t, const Point& cp);
	void scale(float s);
	void scale(float scaleX, float scaleY);
	void scale(float s, int cx, int cy);
	void scale(float s, Point& cp);
	void translate(int deltaX, int deltaY);

	// Others
	void geser(int _x, int _y){x+=_x; y+=_y;};
	Point hasilGeser(int _x, int _y) const{
		Point p(getX()+_x,getY()+_y);
		return p;
	};
	Point hasilRotasi(float deltaDegree) const;
	Point hasilMirror00() const;

private:
	int x;
	int y;
};

#endif
