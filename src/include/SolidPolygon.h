#ifndef SolidPolygon_h
#define SolidPolygon_h

#include <vector>
#include "Point.h"
#include "Texture.h"

class SolidPolygon: public std::vector<Point>{
	public:
	SolidPolygon(Texture t = Texture::createSingleColorTexture(0,0,0,0)):std::vector<Point>(){texture=t;};
	SolidPolygon(std::vector<Point>::size_type s,Texture t = Texture::createSingleColorTexture(0,0,0,0)):std::vector<Point>(s){texture=t;};
	SolidPolygon hasilGeser(Point delta);
	SolidPolygon hasilGeser(int deltax, int deltay);
	SolidPolygon hasilPerbesar(float scale);

	SolidPolygon hasilSkala(float scaleX, float scaleY);
	SolidPolygon hasilRotasi(float deltaDegree);
	SolidPolygon hasilRotasi(float deltaDegree, Point poros);

	void push_back(int x, int y); 
	void push_back(const Point& p){std::vector<Point>::push_back(p);};

	void draw();

	SolidPolygon clip(Point min, Point max);

	private:

	Texture texture;
	
};

#endif
