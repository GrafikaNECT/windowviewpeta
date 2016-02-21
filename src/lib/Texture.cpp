#include "../include/Texture.h"
#include "../include/Printer.h"

Texture::Texture(std::vector<std::vector<int> > R,
		std::vector<std::vector<int> > G,
		std::vector<std::vector<int> > B,
		std::vector<std::vector<int> > A, int sizeX, int sizeY){
	this->R=R;
	this->G=G;
	this->B=B;
	this->A=A;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}

Texture Texture::createSingleColorTexture(int R, int G, int B, int A){
	std::vector<std::vector<int> > vecR(1);
	vecR[0].push_back(R);
	std::vector<std::vector<int> > vecG(1);
	vecG[0].push_back(G);
	std::vector<std::vector<int> > vecB(1);
	vecB[0].push_back(B);
	std::vector<std::vector<int> > vecA(1);
	vecA[0].push_back(A);

	return Texture(vecR, vecG, vecB, vecA, 1, 1);
}

Texture Texture::fromStream(std::istream& inputfile){
	int M,N;
	inputfile>>M;
	inputfile>>N;
	std::vector<std::vector<int> > vecR(M);
	std::vector<std::vector<int> > vecG(M);
	std::vector<std::vector<int> > vecB(M);
	std::vector<std::vector<int> > vecA(M);
	for (int i=0;i<M;i++){
		vecR[i].resize(N);
		vecG[i].resize(N);
		vecB[i].resize(N);
		vecA[i].resize(N);
		for (int j=0;j<N;j++){
			inputfile>>vecR[i][j];
			inputfile>>vecG[i][j];
			inputfile>>vecB[i][j];
			inputfile>>vecA[i][j];
		}
	}
	return Texture(vecR, vecG, vecB, vecA, N, M);
}

void Texture::draw(int x,int y){
	int j = x%sizeX;
	int i = y%sizeY;

	Printer::drawPix(x,y,R[i][j],G[i][j],B[i][j],A[i][j]);
}
