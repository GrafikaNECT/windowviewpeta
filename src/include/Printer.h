#ifndef PRINTER_H
#define PRINTER_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

class Printer {
public:
	static int initializePrinter();
	static int finishPrinter();
	static void drawCanvas(unsigned char R, unsigned char G, unsigned char B, unsigned char alpha);
	static void drawPix(int x, int y, unsigned char R, unsigned char G, unsigned char B, unsigned char alpha);
	static void drawPixSquare(int _x, int _y, int size, unsigned char R, unsigned char G, unsigned char B, unsigned char alpha);
	static void setColor(unsigned char R, unsigned char G, unsigned char B, unsigned char alpha);
	static void printToScreen();

	static int getXRes(){ return vinfo.xres; };
	static int getYRes(){ return vinfo.yres; };

    static int fbfd;
    static struct fb_var_screeninfo vinfo;
    static struct fb_fix_screeninfo finfo;
    static long int screensize;
    static char *fbp;
    static long int location;
	static unsigned char * workspaceframe;
};


#endif
