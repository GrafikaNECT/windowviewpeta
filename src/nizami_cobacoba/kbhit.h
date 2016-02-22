#ifndef kbhit_h
#define kbhit_h

#include <stdlib.h> 
#include <unistd.h> 
#include <sys/select.h> 
#include <termios.h> 
#include <time.h> 
#include <stdio.h>

static struct termios old_termios, new_termios;
/* restore new terminal i/o settings */
void resetTermios(){
	tcsetattr(0,TCSANOW,&old_termios);
}
/* initialize new terminal i/o settings */
void initTermios(){
	tcgetattr(0,&old_termios); // store old terminal 
	new_termios = old_termios; // assign to new setting 
	new_termios.c_lflag &= ~ICANON; // disable buffer i/o 
	new_termios.c_lflag &= ~ECHO; // disable echo mode 
	tcsetattr(0,TCSANOW,&new_termios); // use new terminal setting 
}
/* detect keyboard press */
int kbhit(){
	struct timeval tv = {0L,0L};
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(0,&fds);
	return select(1,&fds,NULL,NULL,&tv);
}
/* read 1 character */
char getch(){
	char ch;
	ch = getchar();
	return ch;
}

#endif
