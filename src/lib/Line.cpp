#include "../include/Line.h"
#include "../include/Printer.h"
#include <iostream>

// Constructor
Line::Line(int _x1, int _y1, int _x2, int _y2, Texture t) {
	p1.setX(_x1);
	p1.setY(_y1);
	p2.setX(_x2);
	p2.setY(_y2);
	texture = t;
}
Line::Line(Point _p1, Point _p2, Texture t) {
	p1 = _p1;
	p2 = _p2;
	texture = t;
}

// Getter
Point Line::getP1() {return p1;}
Point Line::getP2() {return p2;}
int Line::getX1() {return p1.getX();}
int Line::getY1() {return p1.getY();}
int Line::getX2() {return p2.getX();}
int Line::getY2() {return p2.getY();}

// Operations
void Line::move(int dx, int dy) {
	p1.translate(dx,dy);
	p2.translate(dx,dy);
}
void Line::scale(float s) {
	p1.scale(s);
	p2.scale(s);
}
void Line::scale(float s, int x, int y) {
	p1.scale(s,x,y);
	p2.scale(s,x,y);
}
void Line::scale(float s, Point p) {
	p1.scale(s,p);
	p2.scale(s,p);
}
void Line::rotate(float t) {
	p1.rotate(t);
	p2.rotate(t);
}
void Line::rotate(float t, int x, int y) {
	p1.rotate(t,x,y);
	p2.rotate(t,x,y);
}
void Line::rotate(float t, Point p) {
	p1.rotate(t,p);
	p2.rotate(t,p);
}

OutCode Line::ComputeOutCode(int x, int y, Point min, Point max){
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

Line Line::clip(Point min, Point max){
	// Cohen–Sutherland clipping algorithm clips a Line from
// P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with 
// diagonal from (xmin, ymin) to (xmax, ymax).
	// compute outcodes for P0, P1, and whatever Point lies outside the clip rectangle
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
			// failed both tests, so calculate the Line segment to clip
			// from an outside Point to an intersection with clip edge
			double x, y;
			int xmax = max.getX();
			int ymax = max.getY();
			int xmin = min.getX();
			int ymin = min.getY();

			// At least one endPoint is outside the clip rectangle; pick it.
			OutCode outcodeOut = outcode1 ? outcode1 : outcode2;

			// Now find the intersection Point;
			// use formulas y = y1 + slope * (x - x1), x = x1 + (1 / slope) * (y - y1)
			if (outcodeOut & TOP) {           // Point is above the clip rectangle
				x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
				y = ymax;
			} else if (outcodeOut & BOTTOM) { // Point is below the clip rectangle
				x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
			 	y = ymin;
			} else if (outcodeOut & RIGHT) {  // Point is to the right of clip rectangle
				y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
				x = xmax;
			} else if (outcodeOut & LEFT) {   // Point is to the left of clip rectangle
				y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
				x = xmin;
			}

			// Now we move outside Point to intersection Point to clip
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
        return Line(x1,y1,x2,y2);
	} else{
		return Line(-1,-1,-1,-1);
	}
}

// Graphics
void Line::draw() {
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
			for (i=y1;i<=y2;i++) Printer::drawPix(x1,i,255,255,255,255);
		} else {
			for (i=y2;i<=y1;i++) Printer::drawPix(x1,i,255,255,255,255);
		}
	} else if (y1==y2) {	// Horizontal
		if (x1<=x2) {
			for (i=x1;i<=x2;i++) Printer::drawPix(i,y1,255,255,255,255);
		} else {
			for (i=x2;i<=x1;i++) Printer::drawPix(i,y1,255,255,255,255);
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
			Printer::drawPix(x1+i,y1+j,255,255,255,255);
			while (i*dy*cs>j*dx*cs) {
				j = j+cy;
				Printer::drawPix(x1+i,y1+j,255,255,255,255);
			}
			i = i+cx;
		}
	}
}
