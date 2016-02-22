#include "print.h"

#include "image.h"

#include <fstream>
#include <unistd.h>

int main(){
	std::fstream streamim("testimage.txt");
	std::fstream streamtex("testimage_texture.txt");

	Image i;

	initializePrinter();

	i.addLine(line(0,0,1000,1000,Texture::createSingleColorTexture(255,0,0,255)));
	drawCanvas(0,0,0,255);
	i.draw();
	printToScreen();
	sleep(1);

	i = Image::fromStream(streamim,streamtex);
	
	drawCanvas(0,0,0,255);
	i.draw();
	printToScreen();
	sleep(1);

	i.clip(point(100,100),point(200,200));
	drawCanvas(0,0,0,255);
	i.draw();
	printToScreen();
	sleep(1);

	std::fstream streammap("testimage_formatmap.txt");
	i = Image::fromStreamFormatMap(streammap);
	drawCanvas(0,0,100,255);
	i.draw();
	printToScreen();
	sleep(1);

	for (int x0=0;x0<100;x0+=10){
		for (int y0=0;y0<100;y0+=10){
			for (int x1=x0+10;x1<150;x1+=10){
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

					point min(x0,y0);
					point max(x1,y1);

					i.clip(min,max).draw();
					printToScreen();
				}
			}
		}
	}

	finishPrinter();

	streamim.close();
	streamtex.close();
}
