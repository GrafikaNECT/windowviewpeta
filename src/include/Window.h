#ifndef Window_h
#define Window_h

//definisikan Window di sini
class Window{
public:
	// Constructor
	Window();
	Window(Point tl, Point tr, Point bl, Point br);

	// Operations
	void pan(float deltaX, float delta Y);
	void zoom(float s);
	void draw();

private:
	Point top_left;
	Point top_right;
	Point bottom_left;
	Point bottom_right;

	Map map;
};

#endif
