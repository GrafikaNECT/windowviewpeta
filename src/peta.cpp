#include "peta.h"
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

//CONSTRUCTOR
peta::peta(int num) {
	jumlahPulau = num;
}

//GETTER
int peta::getJumlahPulau() {
	return jumlahPulau;
}

//SETTER
void peta::setJumlahPulau(int num) {
	jumlahPulau = num;
}

//GRAPHICS
void peta::drawPulau(string fileName, int R, int G, int B, int alpha) {
	ifstream infile(fileName);
	if (!infile) {
	    cerr << "File not found." << endl;
	    
	}

	// Using getline() to read one line at a time.
	string line;
	while (getline(infile, line)) {
	std::vector<int> vx;
	std::vector<int> vy;


	if (line.empty()) continue;

	// Using istringstream to read the line into integers.
	istringstream iss(line);

	int next;
	bool isX = 1;

	while (iss >> next) {
		if (isX) {
			isX = 0;
			vx.push_back(next);
		} else {
			isX = 1;
			vy.push_back(next);
		}
		
		if (iss.peek() == ',')
			iss.ignore();
	}

	for (int i = 0; i < vx.size(); i++) {
		cout << vx.at(i) << " ";
		cout << vy.at(i) << "\n";
	}  
		cout << endl;
	}

	infile.close();

	  
}