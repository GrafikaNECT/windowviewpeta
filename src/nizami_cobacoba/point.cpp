#include "point.h"
#include <math.h>
#include <iostream>

// Constructor
point::point(int _x, int _y) {
	x = _x;
	y = _y;
}

// Getter
int point::getX() const {
	return x;
}
int point::getY() const {
	return y;
}

// Setter
void point::setX(int _x) {
	x = _x;
}
void point::setY(int _y) {
	y = _y;
}

// Operations
void point::move(int dx, int dy) {
	x = x + dx;
	y = y + dy;
}
void point::scale(float s) {
	x = (int)x*s;
	y = (int)y*s;
}
void point::scale(float s, int cx, int cy) {
	move(-cx,-cy);
	scale(s);
	move(cx,cy);
}
void point::scale(float s, point& cp) {
	scale(s,cp.getX(),cp.getY());
}
void point::rotate(float t) {
	int x1 = round(cos(t)*x - sin(t)*y);
	int y1 = round(sin(t)*x + cos(t)*y);
	x = x1;
	y = y1;
}
void point::rotate(float t, int cx, int cy) {
	move(-cx,-cy);
	rotate(t);
	move(cx,cy);
}

void point::rotate(float t, const point& cp){
	rotate(t,cp.getX(),cp.getY());
}

point point::hasilRotasi(float deltaDegree) const{
	float deltaRad = deltaDegree*M_PI/180.0;
	point p((double)x*cos(deltaRad)-(double)y*sin(deltaRad),(double)x*sin(deltaRad)+(double)y*cos(deltaRad));
	return p;
}

point point::hasilMirror00() const{
	point p(-x,-y);
	return p;
}
