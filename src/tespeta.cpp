#include <iostream> 
#include <string>
#include "peta.h"

using namespace std;

int main () {
	peta map(20);

	string file = "Peta/Sumatera.txt";

	map.drawPulau(file, 0,0,0,0);


	return 0;
}