//includes
#include <iostream>
#include <fstream>

#include "print.h"
#include "point.h"
#include "image.h"
#include "sistemwindowview.h"
#include "kbhit.h"

#include "solidpolygon.h"
#include "line.h"

#define MARGIN 100
#define DEFAULTWINDOWWIDTH 400
#define BOTTOMTEXTSPACE 200

//warnawarna
#define VIEWCANVASTEXTURE Texture::createSingleColorTexture(0,0,0,255)

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

	//kanvas di view
	SolidPolygon viewCanvas(VIEWCANVASTEXTURE);
	viewCanvas.push_back(viewMin);
	viewCanvas.push_back(point(viewMin.getX(),viewMax.getY()));
	viewCanvas.push_back(viewMax);
	viewCanvas.push_back(point(viewMax.getX(),viewMin.getY()));

	//looping menerima kontrol untuk pan dan zoom serta menggambar
	//jangan lupa ada kontrol untuk quit
	drawCanvas(100,100,100,255);
	viewCanvas.draw();
	sistemWindowView.draw();
	printToScreen();
	bool cont=true;
	char c;
	initTermios();
	while (cont)
	if (kbhit())
	{
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
		viewCanvas.draw();
		sistemWindowView.draw();
		printToScreen();
	}

	resetTermios();
	//quit
	finishPrinter();
}
