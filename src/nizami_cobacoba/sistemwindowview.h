#ifndef sistemwindowview_h
#define sistemwindowview_h

#define ZOOM 5
#define PAN 5

#include "point.h"
#include "image.h"
#include <string>

class SistemWindowView{

protected:
	point windowMin;
	point windowMax;
	point viewMin;
	point viewMax;
	Image map;
	point minimapPos;
	float minimapScale;
	Image minimap;

public:
	SistemWindowView(point windowMin, point windowMax, point viewMin, point viewMax, Image map, point minimapPos, float minimapScale);

	point getWindowMin();
	point getWindowMax();
	point getViewMin();
	point getViewMax();
	Image getMap();

	void setWindowMin(point min);
	void setWindowMax(point max);
	void setViewMin(point min);
	void setViewMax(point max);
	void setMap(Image map);


	void pan(std::string direction);
	void zoom(std::string direction);
	void draw();
	void drawMinimap();
};

#endif
