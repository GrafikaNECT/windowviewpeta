#include "../include/Window.cpp"

using namespace std;

// Constructor
Window::Window() {
	top_left = 0;
	top_right = 0;
	bottom_left = 0;
	bottom_right = 0;
}
Window::Window(Point tl, Point tr, Point bl, Point br) {
	top_left = Point(tl.getX(), tl.getY());
	top_right = Point(tr.getX(), tr.getY());
	bottom_left = Point(bl.getX(), bl.getY());
	bottom_right = Point(br.getX(), br.getY());
}

// Operations
void Window::pan(float deltaX, float delta Y) {
	top_left.translate(deltaX, deltaY);
	top_right.translate(deltaX, deltaY);
	bottom_left.translate(deltaX, deltaY);
	bottom_right.translate(deltaX, deltaY);
}

void Window::zoom(float s) { //kalo di zoom windownya mengecil kan ya?
	top_left.scale(scale * (-1));
	top_right.scale(scale * (-1));
	bottom_left.scale(scale * (-1));
	bottom_right.scale(scale * (-1));
}

void Window::draw() {

}