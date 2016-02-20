#include "print.h"
#include "line.h"
#include <unistd.h>
#include <iostream>

int main() {
	initializePrinter();

	drawCanvas(0,0,0,255);

	line l(0,0,500,500);
	point min(0,50);
	point max(500,250);
	l.clip(min,max).draw();
	printToScreen();
	sleep(5);
	finishPrinter();

}
