#include "sistemwindowview.h"

SistemWindowView::SistemWindowView(point windowMin, point windowMax, point viewMin, point viewMax, Image map, point minimapPos, float minimapScale) {
	this->windowMin = windowMin;
	this->windowMax = windowMax;
	this->viewMin = viewMin;
	this->viewMax = viewMax;
	this->map = map;
	this->minimapPos = minimapPos;
	this->minimapScale = minimapScale;
	this->minimap = map.hasilSkala(minimapScale).hasilGeser(minimapPos);
}

point SistemWindowView::getWindowMin() {return windowMin;}
point SistemWindowView::getWindowMax() {return windowMax;}
point SistemWindowView::getViewMin() {return viewMin;}
point SistemWindowView::getViewMax() {return viewMax;}
Image SistemWindowView::getMap() {return map;}

void SistemWindowView::setWindowMin(point min) {windowMin = min;}
void SistemWindowView::setWindowMax(point max) {windowMax = max;}
void SistemWindowView::setViewMin(point min) {viewMin = min;}
void SistemWindowView::setViewMax(point max) {viewMax = max;}
void SistemWindowView::setMap(Image map) {this->map = map;}

void SistemWindowView::pan(std::string direction) {
	if (direction == "left") {
		windowMin.move(-PAN,0);
		windowMax.move(-PAN,0);
	}
	else if (direction == "right") {
		windowMin.move(PAN,0);
		windowMax.move(PAN,0);
	}
	else if (direction == "up") {
		windowMin.move(0,-PAN);
		windowMax.move(0,-PAN);
	}
	else if (direction == "down") {
		windowMin.move(0,PAN);
		windowMax.move(0,PAN);
	}
}

void SistemWindowView::zoom(std::string direction) {
	int min_x = windowMin.getX();
	int min_y = windowMin.getY();
	int max_x = windowMax.getX();
	int max_y = windowMax.getY();
	int width = max_x - min_x;
	int height = max_y - min_y;
	int deltax = ZOOM;
	int deltay = ((float)deltax/width)*height;
	
	if (direction == "in") {
		windowMin.move(deltax,deltay);
		windowMax.move(-deltax,-deltay);
	} else if (direction == "out") {
		windowMin.move(-deltax,-deltay);
		windowMax.move(deltax,deltay);
	}
}

void SistemWindowView::draw() {
	int viewWidth = viewMax.getX() - viewMin.getX();
	int viewHeight = viewMax.getY() - viewMin.getY();
	int windowWidth = windowMax.getX() - windowMin.getX();
	int windowHeight = windowMax.getY() - windowMin.getY();
	float ratio_x = (float)viewWidth/windowWidth;
	float ratio_y = (float)viewHeight/windowHeight;
	point move1(-windowMin.getX(),-windowMin.getY());
	point move2(viewMin.getX(),viewMin.getY());

	map.clip(windowMin,windowMax)
		.hasilGeser(move1)
		.hasilSkala(ratio_x,ratio_y)
		.hasilGeser(move2).draw();

	drawMinimap();
}

void SistemWindowView::drawMinimap() {
	minimap.draw();
	Texture lineTexture = Texture::createSingleColorTexture(0,0,255,255);
	line top(windowMin,point(windowMax.getX(),windowMin.getY()),lineTexture);
	line bottom(point(windowMin.getX(),windowMax.getY()),windowMax,lineTexture);
	line left(windowMin,point(windowMin.getX(),windowMax.getY()),lineTexture);
	line right(point(windowMax.getX(),windowMin.getY()),windowMax,lineTexture);
	Image window;
	window.addLine(top);
	window.addLine(bottom);
	window.addLine(left);
	window.addLine(right);
	window.hasilSkala(minimapScale).hasilGeser(minimapPos).draw();
}