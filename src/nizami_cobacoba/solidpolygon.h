#ifndef SolidPolygon_h
#define SolidPolygon_h

#include <vector>
#include "point.h"
#include "texture.h"

class SolidPolygon: public std::vector<point>{
	public:
	SolidPolygon(Texture t = Texture::createSingleColorTexture(0,0,0,0)):std::vector<point>(){texture=t;};
	SolidPolygon(std::vector<point>::size_type s,Texture t = Texture::createSingleColorTexture(0,0,0,0)):std::vector<point>(s){texture=t;};
	SolidPolygon hasilGeser(point delta);
	SolidPolygon hasilGeser(int deltax, int deltay);
	SolidPolygon hasilPerbesar(float scale);

	SolidPolygon hasilSkala(float scaleX, float scaleY);
	SolidPolygon hasilRotasi(float deltaDegree);
	SolidPolygon hasilRotasi(float deltaDegree, point poros);

	void push_back(int x, int y); 
	void push_back(const point& p){std::vector<point>::push_back(p);};

	void draw();

	SolidPolygon clip(int x0, int x1, int y0, int y1);

	private:

	Texture texture;
	
};

#endif
