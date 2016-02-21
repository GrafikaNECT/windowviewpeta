#include <iostream> 
#include <string>
#include "include/Map.h"
#include "include/Printer.h"

using namespace std;

int main () {
	Map map(20);
	Map mapkal(20);


	Printer::initializePrinter();
	Printer::drawCanvas(255,255,255,255);


	string file = "Peta/Sumatera.txt";

	map.initialize(file, 0,0,0,255);

	map.draw();
	Printer::printToScreen();

	string filekal = "Peta/Kalimantan.txt";

	mapkal.initialize(file, 0,0,0,255);

	mapkal.draw();
	Printer::printToScreen();

	return 0;
}