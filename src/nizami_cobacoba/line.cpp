#include "line.h"
#include "print.h"
#include <iostream>

// Constructor
line::line(int _x1, int _y1, int _x2, int _y2, Texture t) {
	p1.setX(_x1);
	p1.setY(_y1);
	p2.setX(_x2);
	p2.setY(_y2);
	texture = t;
}
line::line(point _p1, point _p2, Texture t) {
	p1 = _p1;
	p2 = _p2;
	texture = t;
}

// Getter
point line::getP1() {return p1;}
point line::getP2() {return p2;}
int line::getX1() {return p1.getX();}
int line::getY1() {return p1.getY();}
int line::getX2() {return p2.getX();}
int line::getY2() {return p2.getY();}

// Operations
void line::move(point delta){move(delta.getX(),delta.getY());};
void line::move(int dx, int dy) {
	p1.move(dx,dy);
	p2.move(dx,dy);
}
void line::scale(float s) {
	p1.scale(s);
	p2.scale(s);
}
void line::scale(float sx, float sy){
	p1.scale(sx,sy);
	p2.scale(sx,sy);
}
void line::scale(float s, int x, int y) {
	p1.scale(s,x,y);
	p2.scale(s,x,y);
}
/*void line::scale(float s, point p) {
	p1.scale(s,p);
	p2.scale(s,p);
}*/
void line::rotate(float t) {
	p1.rotate(t);
	p2.rotate(t);
}
void line::rotate(float t, int x, int y) {
	p1.rotate(t,x,y);
	p2.rotate(t,x,y);
}
void line::rotate(float t, point p) {
	p1.rotate(t,p);
	p2.rotate(t,p);
}

OutCode line::ComputeOutCode(int x, int y, point min, point max){
	OutCode code;

	code = INSIDE;          // initialised as b eing inside of clip window

	if (x < min.getX())           // to the left of clip window
		code |= LEFT;
	else if (x > max.getX())      // to the right of clip window
		code |= RIGHT;
	if (y < min.getY())           // below the clip window
		code |= BOTTOM;
	else if (y > max.getY())      // above the clip window
		code |= TOP;

	return code;

}

line line::clip(point min, point max){
	// Cohen–Sutherland clipping algorithm clips a line from
// P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with 
// diagonal from (xmin, ymin) to (xmax, ymax).
	// compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
	int x1 = p1.getX();
	int x2 = p2.getY();
	int y1 = p1.getX();
	int y2 = p2.getY();
	OutCode outcode1 = ComputeOutCode(x1,y1,min,max);
	OutCode outcode2 = ComputeOutCode(x2,y2,min,max);
	bool accept = false;

	while (true) { 
		if (!(outcode1 | outcode2)) { // Bitwise OR is 0. Trivially accept and get out of loop
			accept = true;
			break;
		} else if (outcode1 & outcode2) { // Bitwise AND is not 0. Trivially reject and get out of loop
			break;
		} else {
			// failed both tests, so calculate the line segment to clip
			// from an outside point to an intersection with clip edge
			double x, y;
			int xmax = max.getX();
			int ymax = max.getY();
			int xmin = min.getX();
			int ymin = min.getY();

			// At least one endpoint is outside the clip rectangle; pick it.
			OutCode outcodeOut = outcode1 ? outcode1 : outcode2;

			// Now find the intersection point;
			// use formulas y = y1 + slope * (x - x1), x = x1 + (1 / slope) * (y - y1)
			if (outcodeOut & TOP) {           // point is above the clip rectangle
				x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
				y = ymax;
			} else if (outcodeOut & BOTTOM) { // point is below the clip rectangle
				x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
			 	y = ymin;
			} else if (outcodeOut & RIGHT) {  // point is to the right of clip rectangle
				y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
				x = xmax;
			} else if (outcodeOut & LEFT) {   // point is to the left of clip rectangle
				y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
				x = xmin;
			}

			// Now we move outside point to intersection point to clip
			// and get ready for next pass.
			if (outcodeOut == outcode1) {
				x1 = x;
				y1 = y;
				outcode1 = ComputeOutCode(x1, y1, min, max);
			} else {
				x2 = x;
				y2 = y;
				outcode2 = ComputeOutCode(x2, y2, min, max);
			}
		}
	}
	if (accept) {
        return line(x1,y1,x2,y2,texture);
	} else{
		return line(-1,-1,-1,-1, texture);
	}
}

// Graphics
void line::draw() {
	int x1 = p1.getX();
	int y1 = p1.getY();
	int x2 = p2.getX();
	int y2 = p2.getY();
	int i,j;
	int dy = y2-y1;
	int dx = x2-x1;
	short int cx, cy, cs;
	
	if (x1==x2) {	// Vertikal
		if (y1<=y2) {
			for (i=y1;i<=y2;i++) drawPix(x1,i,255,255,255,255);
		} else {
			for (i=y2;i<=y1;i++) drawPix(x1,i,255,255,255,255);
		}
	} else if (y1==y2) {	// Horizontal
		if (x1<=x2) {
			for (i=x1;i<=x2;i++) drawPix(i,y1,255,255,255,255);
		} else {
			for (i=x2;i<=x1;i++) drawPix(i,y1,255,255,255,255);
		}
	} else {
		// Check for quadrant position of p2
		if (dy>0) {
			if (dx>0) {	// Kuadran I
				cx = 1; cy = 1; cs = 1;
			} else {	// Kuadran II
				cx = -1; cy = 1; cs = -1;
			}
		} else {
			if (dx<0) {	// Kuadran III
				cx = -1; cy = -1; cs = 1;
			} else {	// Kuadran IV
				cx = 1; cy = -1; cs = -1;
			}
		}
		i = 0;
		j = 0;
		while (cx*i<=cx*dx) {
			texture.draw(x1+i,y1+j);
			while (i*dy*cs>j*dx*cs) {
				j = j+cy;
				texture.draw(x1+i,y1+j);
			}
			i = i+cx;
		}
	}
}
