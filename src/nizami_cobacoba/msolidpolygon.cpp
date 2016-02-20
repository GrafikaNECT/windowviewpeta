#include "print.h"
#include <random>
#include "solidpolygon.h"
#include <unistd.h>
#include <iostream>

int main(){
	initializePrinter();

	SolidPolygon sp(Texture::createSingleColorTexture(255,255,255,255));
	//cobain biasa
	sp.push_back(4,4);
	sp.push_back(30,100);
	sp.push_back(100,4);
	sp.push_back(30,400);
	drawCanvas(10,10,10,255);
	sp.draw();
	printToScreen();
	sleep(1);

	for (int x0=0;x0<400;x0+=10){
		for (int y0=0;y0<400;y0+=10){
			for (int x1=x0+10;x1<400;x1+=10){
				for (int y1=y0+10;y1<400;y1+=10){
					drawCanvas(10,10,10,255);

					//draw supposed clip boundaries
					for (int y=y0;y<y1;y++){
						drawPix(x0,y,0,0,255,255);
						drawPix(x1,y,0,0,255,255);
					}
					for (int x=x0;x<x1;x++){
						drawPix(x,y0,0,0,255,255);
						drawPix(x,y1,0,0,255,255);
					}


					SolidPolygon sp2 = sp.clip(x0,x1,y0,y1);
					std::cout<<"size="<<sp.size()<<std::endl;
					for (int i=0;i<sp2.size();i++){
						std::cout<<sp2[i].getX()<<" "<<sp2[i].getY()<<std::endl;
					}
					sp2.draw();
					printToScreen();
				}
			}
		}
	}

	finishPrinter();
}
