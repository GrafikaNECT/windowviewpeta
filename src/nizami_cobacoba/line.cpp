#include "line.h"
#include "print.h"

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
void line::move(int dx, int dy) {
	p1.move(dx,dy);
	p2.move(dx,dy);
}
void line::scale(float s) {
	p1.scale(s);
	p2.scale(s);
}
void line::scale(float s, int x, int y) {
	p1.scale(s,x,y);
	p2.scale(s,x,y);
}
void line::scale(float s, point p) {
	p1.scale(s,p);
	p2.scale(s,p);
}
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

OutCode line::ComputeOutCode(int x, int y, int xmin, int xmax, int ymin, int ymax){
	OutCode code;

	code = INSIDE;          // initialised as b eing inside of clip window

	if (x < xmin)           // to the left of clip window
		code |= LEFT;
	else if (x > xmax)      // to the right of clip window
		code |= RIGHT;
	if (y < ymin)           // below the clip window
		code |= BOTTOM;
	else if (y > ymax)      // above the clip window
		code |= TOP;

	return code;

}

line line::clip(int x0, int x1, int y0, int y1){
	// Cohen–Sutherland clipping algorithm clips a line from
// P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with 
// diagonal from (xmin, ymin) to (xmax, ymax).
	// compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
	OutCode outcode0 = ComputeOutCode(x0, y0);
	OutCode outcode1 = ComputeOutCode(x1, y1);
	bool accept = false;

	while (true) { 
		if (!(outcode0 | outcode1)) { // Bitwise OR is 0. Trivially accept and get out of loop
			accept = true;
			break;
		} else if (outcode0 & outcode1) { // Bitwise AND is not 0. Trivially reject and get out of loop
			break;
		} else {
			// failed both tests, so calculate the line segment to clip
			// from an outside point to an intersection with clip edge
			double x, y;

			// At least one endpoint is outside the clip rectangle; pick it.
			OutCode outcodeOut = outcode0 ? outcode0 : outcode1;

			// Now find the intersection point;
			// use formulas y = y0 + slope * (x - x0), x = x0 + (1 / slope) * (y - y0)
			if (outcodeOut & TOP) {           // point is above the clip rectangle
				x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
				y = ymax;
			} else if (outcodeOut & BOTTOM) { // point is below the clip rectangle
				x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
			 	y = ymin;
			} else if (outcodeOut & RIGHT) {  // point is to the right of clip rectangle
				y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
				x = xmax;
			} else if (outcodeOut & LEFT) {   // point is to the left of clip rectangle
				y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
				x = xmin;
			}

			// Now we move outside point to intersection point to clip
			// and get ready for next pass.
			if (outcodeOut == outcode0) {
				x0 = x;
				y0 = y;
				outcode0 = ComputeOutCode(x0, y0);
			} else {
				x1 = x;
				y1 = y;
				outcode1 = ComputeOutCode(x1, y1);
			}
		}
	}
	if (accept) {
               return line(xmin, ymin, xmax, ymax);
	}else{
		return line(-1,-1,-1,-1)
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
			drawPix(x1+i,y1+j,255,255,255,255);
			while (i*dy*cs>j*dx*cs) {
				j = j+cy;
				drawPix(x1+i,y1+j,255,255,255,255);
			}
			i = i+cx;
		}
	}
}
