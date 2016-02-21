#ifndef image_h
#define image_h

#include "line.h"
#include "point.h"
#include "solidpolygon.h"
#include <list>

#include <iostream>

class Image {
	public:

	void addLine(line l);
	void addLines(const std::list<point>& points);

	void addSolidPolygon(SolidPolygon solidPolygon);
	
	//membuat image dari streamImage
	//
	//sebelumnya meload stream tekstur terlebih dahulu
	//Tekstur: baris pertama bilangan bulat N menyatakan banyaknya tekstur
	//		selanjutnya N buah tekstur yang formatnya
	//		didefinisikan di texture.h
	//
	//streamGambar
	//baris pertama: bilangan bulat N, menyatakan banyaknya elemen
	//berikutnya, diikuti N elemen dengan format masing2 berikut:
	//sebaris bilangan bulat {0,1}: 0 menyatakan garis atau polyline,
	//				(polyline diubah jadi set of garis)
	//				1 menyatakan SolidPolygon
	//baris berikutnya menyatakan nomor tekstur untuk elemen tersebut
	//baris berikutnya, sebuah bilangan bulat M menyatakan banyak titik
	//M baris berikutnya, masing2 bilangan bulat X Y menyatakan titik
	//-titik ujung garis (line) atau titik sudut (polygon)
	static Image fromStream(std::istream& streamGambar,
				std::istream& streamTekstur);

	Image clip(point min, point max);
	Image hasilGeser(point delta);
	Image hasilSkala(float scale){return hasilSkala(scale,scale);}
	Image hasilSkala(float scaleX, float scaleY);

	void draw();

	private:
	std::list<line> lines;
	std::list<SolidPolygon> solidPolygons;

//untuk iterasi menggambar,
//saat di-add, ini diisi dengan order gambar yang menaik
	std::list<int> orderGambarLine;
	std::list<int> orderGambarPolygon;
};

#endif
