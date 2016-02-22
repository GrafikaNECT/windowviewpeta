#ifndef image_h
#define image_h

#include "line.h"
#include "point.h"
#include "solidpolygon.h"
#include <list>

#include <iostream>

class Image {
	public:

	//menambah line
	//perhatikan orderGambar (spek di bawah)
	void addLine(line l);

	//memanggil addLine
	//misal: isi points adalah {p0,p1,p2, ... pn-1}
	//	maka, panggil 	addLine(line(p0,p1))
	//			addLine(line(p1,p2))
	//			.
	//			.
	//			.
	//			addLine(line(pn-2,pn-1))
	void addLines(const std::list<point>& points);

	//menambah SolidPolygon
	//perhatikan orderGambar (spek di bawah)
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

	static Image fromStreamFormatMap(std::istream& infile);

	//clip semua elemen
	Image clip(point min, point max);

	//geser semua elemen
	Image hasilGeser(point delta);

	//skala semua elemen gambar
	Image hasilSkala(float scale){return hasilSkala(scale,scale);}
	Image hasilSkala(float scaleX, float scaleY);

	//gambar
	//line dan poligon
	void draw();

	private:
	std::list<line> lines;
	std::list<SolidPolygon> solidPolygons;

//untuk iterasi menggambar,
//saat di-add, ini diisi dengan order gambar yang menaik
//misal: bila dipanggil addLine, addLine, addSolidPolygon, addLine, addLine, addSolidPolygon
//maka, ordergambarLine: {0,1,3,4}
//	orderGambarSolidPolygon: {2,5}
	std::list<int> orderGambarLine;
	std::list<int> orderGambarSolidPolygon;

	//untuk mentrack saat add orderGambar
	int numElmts=0;
};

#endif
