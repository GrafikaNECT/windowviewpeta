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


	string file = "Peta/Indonesia.txt";

	map.initialize(file);

	map.draw();
	Printer::printToScreen();

	// string filekal = "Peta/Kalimantan.txt";

	// mapkal.initialize(file);

	// mapkal.draw();
	// Printer::printToScreen();

	return 0;
}