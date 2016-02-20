#ifndef POINT_H
#define POINT_H

class point {
	int x, y;
public:
	// Constructor
	point(int _x, int _y);
	point() {point(0,0);};
	
	// Getter
	int getX() const;
	int getY() const;
	
	// Setter
	void setX(int _x);
	void setY(int _y);
	
	// Operations
	void move(int dx, int dy);
	void scale(float s);
	void scale(float s, int cx, int cy);
	void scale(float s, point& cp);
	void rotate(float t);
	void rotate(float t, int cx, int cy);
	void rotate(float t, const point& cp);

	void geser(int _x, int _y){x+=_x; y+=_y;};
	point hasilGeser(int _x, int _y) const{
		point p(getX()+_x,getY()+_y);
		return p;
	};
	point hasilRotasi(float deltaDegree) const;
	point hasilMirror00() const;
};

#endif // POINT_H
