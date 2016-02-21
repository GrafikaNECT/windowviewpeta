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

	finishPrinter();

	streamim.close();
	streamtex.close();
}
