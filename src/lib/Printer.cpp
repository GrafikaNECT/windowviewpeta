#include "../include/Printer.h"

int Printer::fbfd = 0;
long int Printer::screensize = 0;
char Printer::*fbp = 0;
long int Printer::location = 0;
unsigned char Printer::*workspaceframe = NULL;

int Printer::getXRes(){
	return vinfo.xres;
}

int Printer::getYRes(){
	return vinfo.yres;
}

int Printer::initializePrinter(){
    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        return 1;
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        return 2;
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        return 3;
    }

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    screensize = finfo.smem_len;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        return 4;
    }
    printf("The framebuffer device was mapped to memory successfully.\n");
    printf("%d", vinfo.xres*vinfo.yoffset);

    workspaceframe = malloc(screensize);
    memcpy(workspaceframe,fbp,screensize);

    return 0;
}

int Printer::finishPrinter(){
    if (workspaceframe) free(workspaceframe);
    if (fbp) munmap(fbp, screensize);
    if (fbfd) close(fbfd);
}

void Printer::drawPix(int x, int y, unsigned char R, unsigned char G, unsigned char B, unsigned char alpha){
	if (x>=0 && y>=0 && x<getXRes() && y<getYRes()){
		location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
		           (y+vinfo.yoffset) * finfo.line_length;
		setColor(R,G,B,alpha);
	}
}

void Printer::drawPixSquare(int _x, int _y, int size, unsigned char R, unsigned char G, unsigned char B, unsigned char alpha) {
    int x,y;
    for (y = _y; y < _y+size; y++) {
        for (x = _x; x < _x+size; x++) {
            if (x>=0 && y>=0 && x<getXRes() && y<getYRes()) {
                location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                           (y+vinfo.yoffset) * finfo.line_length;
                setColor(R,G,B,alpha);
            }
        }
    }
        
}

void Printer::setColor(unsigned char R, unsigned char G, unsigned char B, unsigned char alpha) {
    if (vinfo.bits_per_pixel == 32) {
        *(workspaceframe + location) = (unsigned char) (B * alpha/255 + (*(workspaceframe + location)) * (255 - alpha)/255);        // Some blue
        *(workspaceframe + location + 1) = (unsigned char) (G * alpha/255 + (*(workspaceframe + location + 1)) * (255 - alpha)/255);     //  green
        *(workspaceframe + location + 2) = (unsigned char) (R * alpha/255 + (*(workspaceframe + location + 2)) * (255 - alpha)/255);    //  red
        *(workspaceframe + location + 3) = alpha+(*(workspaceframe + location + 3))*(1-alpha)/255;      // alpha

    } else  { //assume 16bpp
        int b = B/8;
        int g = G/8;     // A little green
        int r = R/8;    // A lot of red
        unsigned short int t = r<<11 | g << 5 | b;
        *((unsigned short int*)(fbp + location)) = t;
    }
}

void Printer::drawCanvas(unsigned char R, unsigned char G, unsigned char B, unsigned char alpha){
    int x = 0, y = 0;       // Where we are going to put the pixel

    // Figure out where in memory to put the pixel
    for (y = 0; y < vinfo.yres; y++)
        for (x = 0; x < vinfo.xres; x++) {

            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (y+vinfo.yoffset) * finfo.line_length;

		setColor(R, G, B, alpha);

        }
}

void Printer::printToScreen(){
	memcpy(fbp,workspaceframe,screensize);
}
