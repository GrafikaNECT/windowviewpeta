//includes
#include <iostream>
#include <fstream>

#include "print.h"
#include "point.h"
#include "image.h"
#include "sistemwindowview.h"
#include "conio.h"

#define MARGIN 20
#define DEFAULTWINDOWWIDTH 1657
#define BOTTOMTEXTSPACE 50

using std::endl;
using std::cerr;

//kbhit untuk kontrol?

int main(int argc, char *argv[] ){
	//cek argumen
	//buka dua buah ifstream dari nama file yang disuplai di argc argv
	//itu untuk gambar dan tekstur
	Image i;
	if (argc==2){
		std::ifstream f(argv[1]);
		i = Image::fromStreamFormatMap(f);
	}else if (argc==3){
		std::ifstream fgambar(argv[1]);
		std::ifstream ftekstur(argv[2]);
		i = Image::fromStream(fgambar,ftekstur);
	}else{
		cerr<<"usage:\
			./main <file dengan format map Candy dan Tifani - tanya Candy dan Tifani>\
			./main <file Gambar> <file Tekstur>"<<endl;
	}

	//inisialisasi printer
	initializePrinter();

	//Hitung ukuran window dan ukuran view
	//hitung view
	point viewMin(MARGIN,MARGIN);
	point viewMax(getXRes()-MARGIN,getYRes()-BOTTOMTEXTSPACE-MARGIN);
	point windowMin(0,0);
	point windowMax(DEFAULTWINDOWWIDTH,viewMax.getY()*DEFAULTWINDOWWIDTH/viewMax.getX());

	//buat sebuah objek sistemwindowview
	SistemWindowView sistemWindowView(windowMin,windowMax,viewMin,viewMax,i);
	
	//looping menerima kontrol untuk pan dan zoom serta menggambar
	//jangan lupa ada kontrol untuk quit

	bool cont=true;
	char c;
	while (cont){
		c=getch();
		switch(c){
		case 'w':
			sistemWindowView.pan("up");
		break;
		case 's':
			sistemWindowView.pan("down");
		break;
		case 'a':
			sistemWindowView.pan("left");
		break;
		case 'd':
			sistemWindowView.pan("right");
		break;
		case 'z':
			sistemWindowView.zoom("in");
		break;
		case 'x':
			sistemWindowView.zoom("out");
		break;
		case 'q':
			cont=false;
		break;
		default:
			cerr<<"No action bound for key '"<<c<<"'"<<endl;
		break;
		}
		sistemWindowView.draw();
		printToScreen();
	}


	//quit
	finishPrinter();
}
