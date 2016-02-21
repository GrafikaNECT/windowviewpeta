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
void Map::initialize(string fileName, int R, int G, int B, int alpha) {
	ifstream infile(fileName);
	if (!infile) {
	    cerr << "File not found." << endl;
	    
	}

	int num = 0;

	// Using getline() to read one line at a time.
	string line;
	while (getline(infile, line)) {
		//std::vector<int> vx;
		std::vector<int> vy;


		if (line.empty()) continue;

		// Using istringstream to read the line into integers.
		istringstream iss(line);

		int next;
		bool isX = 1;

		num++;
		SolidPolygon smallIsland(Texture::createSingleColorTexture(R,G,B,alpha)); //TODO: GANTI WARNA

		int tempX;
		while (iss >> next) {

			if (isX) {
				isX = 0;
				//vx.push_back(next);
				tempX = next;
			} else {
				isX = 1;
				vy.push_back(next);
				smallIsland.push_back(tempX, next);
			}
			
			if (iss.peek() == ',')
				iss.ignore();
		}

		/*for (int i = 0; i < vx.size(); i++) {

			cout << vx.at(i) << " ";
			cout << vy.at(i) << "\n";
		}  
			cout << endl;*/

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