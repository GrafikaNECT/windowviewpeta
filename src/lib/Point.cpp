#include "../include/Point.h"
#include <math.h>
#include <iostream>

// Constructor
Point::Point(int _x, int _y) {
	x = _x;
	y = _y;
}

// Getter
int Point::getX() const {
	return x;
}

int Point::getY() const {
	return y;
}

// Setter
void Point::setX(int _x) {
	x = _x;
}

void Point::setY(int _y) {
	y = _y;
}

// Operations
void Point::rotate(float rotateDeg) {
	int x1 = round(cos(rotateDeg)*x - sin(rotateDeg)*y);
	int y1 = round(sin(rotateDeg)*x + cos(rotateDeg)*y);
	x = x1;
	y = y1;
}

void Point::rotate(float t, int cx, int cy) {
	translate(-cx,-cy);
	rotate(t);
	translate(cx,cy);
}

void Point::rotate(float t, const Point& cp) {
	rotate(t,cp.getX(),cp.getY());
}

void Point::scale(float scaleX, float scaleY) {
	x = (int) x*scaleX;
	y = (int) y*scaleY;
}

void Point::scale(float s, int cx, int cy) {
	translate(-cx,-cy);
	scale(s);
	translate(cx,cy);
}

void Point::scale(float s, Point& cp) {
	scale(s,cp.getX(),cp.getY());
}

void Point::translate(int deltaX, int deltaY) {
	x = x * deltaX;
	y = y * deltaY;
}