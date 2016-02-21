#include "../include/Map.h"


#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

//CONSTRUCTOR
Map::Map(int num) {
	numIsland = num;
}

//GETTER
int Map::getNumberOfIsland() {
	return numIsland;
}

//SETTER
void Map::setNumberOfIsland(int num) {
	numIsland = num;
}

//GRAPHICS
void Map::initialize(string fileName) {
	ifstream infile(fileName);
	if (!infile) {
	    cerr << "File not found." << endl;
	    
	}

	int num = 0;

	// Using getline() to read one line at a time.
	string line;
	while (getline(infile, line)) {

		if (line.empty()) continue;

		// Using istringstream to read the line into integers.
		getline(infile, line);
		istringstream iss(line);

		int next;
		bool isX = 1;

		num++;

		iss >> next;
		int R = next;
		iss >> next;
		int G = next;
		iss >> next;
		int B = next;
		iss >> next;
		int alpha = next;

		SolidPolygon smallIsland(Texture::createSingleColorTexture(R,G,B,alpha)); //TODO: GANTI WARNA
	
		getline(infile, line);
		istringstream issCoor(line);

		int tempX;
		while (issCoor >> next) {
			if (isX) {
				isX = 0;
				tempX = next;
			} else {
				isX = 1;
				smallIsland.push_back(tempX, next);
			}
			
			if (issCoor.peek() == ',')
				issCoor.ignore();
		}
		cout << endl;

		island.push_back(smallIsland);

	}

	infile.close();

	num = num/2;
}

void Map::draw() {
	for(int i=0; i<island.size(); i++) {
		island.at(i).draw();
	}
}