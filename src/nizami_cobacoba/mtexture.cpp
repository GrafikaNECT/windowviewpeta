#include "texture.h"
#include "print.h"
#include <vector>
#include <unistd.h>
using namespace std;
int main(){


	vector<vector<int> > R(256);
	vector<vector<int> > G(256);
	vector<vector<int> > B(256);
	vector<vector<int> > A(256);

	for (int i=0;i<256;i++){
		R[i].resize(128);
		G[i].resize(128);
		B[i].resize(128);
		A[i].resize(128);
		for (int j=0;j<128;j++){
			R[i][j]=i;
			G[i][j]=j*2;
			B[i][j]=(i+j)%256;
			A[i][j]=i*j%256;
		}
	}

	Texture t(R,G,B,A,256,128);

	initializePrinter();
	for (int y=0;y<getYRes();y++)
	for (int x=0;x<getXRes();x++){
		t.draw(x,y);
	}
	printToScreen();
	sleep(1);
	finishPrinter();
}
