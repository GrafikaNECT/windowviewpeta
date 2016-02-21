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
void Point::rotate(float t) {
	int x1 = round(cos(t)*x - sin(t)*y);
	int y1 = round(sin(t)*x + cos(t)*y);
	x = x1;
	y = y1;
}

void Point::scale(float s, Point& cp) {
	scale(s,cp.getX(),cp.getY());
}

void Point::rotate(float t, int cx, int cy) {
	move(-cx,-cy);
	rotate(t);
	move(cx,cy);
}