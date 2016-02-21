#include "peta.h"
#include "point.h"
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

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

	//Read from file
	string line;
	int num = 0;
	while (getline(infile, line))
	{
	    std::istringstream iss(line);
	    
	    if (line == "") {
	    } else {
	    	cout << line << endl;	
	    	num++;
	    }

	}
	cout << num << endl;
}