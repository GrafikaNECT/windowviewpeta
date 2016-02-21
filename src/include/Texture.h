#ifndef Texture_h
#define Texture_h

#include <vector>
#include <iostream>

class Texture{
	public:
	Texture(){};
	Texture(std::vector<std::vector<int> > R,
		std::vector<std::vector<int> > G,
		std::vector<std::vector<int> > B,
		std::vector<std::vector<int> > A, int sizeX, int sizeY);

	//factory
	//bikin dari file
	//format:
	//M N
	//Rij Gij Bij Aij
	//urut-urutan ij 00,01,02, dst .... hingga (m-1)(n-1)
	static Texture fromStream(std::istream& inputfile);
	//bikin dari R,G,B,A
	static Texture createSingleColorTexture(int R,int G, int B, int A);

	//getter (malesh bikinnya)

	//setter (malesh bikinnya)

	//drawer
	//ingat x dan y kebalik dengan matriks di dalamnya (pusing)
	void draw(int x, int y);

	//transformasi
	Texture hasilSkala(float scale){return hasilSkala(scale, scale);}
	Texture hasilSkala(float xScale, float yScale);
	Texture hasilTranslasi(int deltaX, int deltaY);

	private:
	//ukuran vektor R, G, B, A selalu sama
	std::vector<std::vector<int> > R;
	std::vector<std::vector<int> > G;
	std::vector<std::vector<int> > B;
	std::vector<std::vector<int> > A;
	int sizeX; int sizeY; //x -> column numb, y -> row numb
};

#endif
