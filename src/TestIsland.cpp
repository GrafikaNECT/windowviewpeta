#include <iostream> 
#include <string>
#include "Map.h"
#include "nizami_cobacoba/print.h"

using namespace std;

int main () {
	Map map(20);
	Map mapkal(20);


	initializePrinter();
	drawCanvas(255,255,255,255);


	string file = "Peta/Sumatera.txt";

	map.initialize(file, 0,0,0,255);

	map.draw();
	printToScreen();

	string filekal = "Peta/Kalimantan.txt";

	mapkal.initialize(file, 0,0,0,255);

	mapkal.draw();
	printToScreen();

	return 0;
}