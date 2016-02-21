#ifndef PETA_H
#define PETA_H

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class peta {
	
	
public:
	// Constructor
	peta(int num);
	
	// Getter
	int getJumlahPulau();
	
	// Setter
	void setJumlahPulau(int num);

	// Graphics
	void drawPulau(string fileName, int R, int G, int B, int alpha);

private:
	//Atribut
	int jumlahPulau;

};


#endif // PETA_H
