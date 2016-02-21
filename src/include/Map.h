#ifndef MAP_H
#define MAP_H

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "SolidPolygon.h"

using namespace std;

class Map {
	
	
public:
	// Constructor
	Map(int num);
	
	// Getter
	int getNumberOfIsland();
	
	// Setter
	void setNumberOfIsland(int num);

	// Graphics
	void initialize(string fileName, int R, int G, int B, int alpha);

	// Draw each island
	void draw();
	
private:
	//Atribut
	int numIsland;
	vector<SolidPolygon> island;

};


#endif // PETA_H
