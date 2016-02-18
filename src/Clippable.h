#ifndef Clippable_h
#define Clippable_h

class Clippable{
	public:
	//x0<x1, y0<y1
	virtual void Clip(int x0, int x1, int y0, int y1) = 0;
};

#endif
