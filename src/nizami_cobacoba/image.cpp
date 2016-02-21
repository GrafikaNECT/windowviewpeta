/*
 * Nama Berkas			: image.cpp
 * Deskripsi			: Realisasi dari image.h
 */

#include "image.h"

using namespace std;

void Image::addLine(line l) {
	// menambah line
	// perhatikan orderGambar (spek di bawah)
}

void Image::addLines(const std::list<point>& points) {
	// memanggil addLine
	// misal: isi points adalah {p0, p1, p2, ..., pn-1}
	// maka, panggil addLine(line(p0, p1))
	// 		addLine(line(p1, p2))
	//		.
	//		.
	//		.
	//		addLine(line(pn-2, pn-1))
}

void Image::addSolidPolygon(SolidPolygon solidPolygon) {
	//menambah SolidPolygon
	// perhatikan orderGambar (spek di bawah)
}

Image Image::fromStream(std::istream& streamGambar, std::istream& streamTekstur) {
	// membuat image dari streamImage
	//
	// sebelumnya meload stream tekstur terlebih dahulu
	// Tekstur: baris pertama bilangan bulat N menyatakan banyaknya tekstur
	//		selanjutnya N buah tekstur yang formatnya
	//		didefinisikan di texture.h
	//
	// streamGambar
	// baris pertama: bilangan bulat N, menyatakan banyaknya elemen
	// berikutnya, diikuti N elemen dengan format masing2 berikut:
	// sebaris bilangan bulat {0,1}: 0 menyatakan garis atau polyline,
	//			(polyline diubah jadi set of garis)
	//			1 menyatakan SolidPolygon
	// baris berikutnya menyatakan nomor tekstur untuk elemen tersebut
	// baris berikutnya, sebuah bilangan bulat M menyatakan banyak titik
	// M baris berikutnya, masing2 bilangan bulat X Y menyatakan titik
	// -titik ujung garis (line) atau titik sudut (polygon)
}

Image Image::clip(point min, point max) {
	// clip semua elemen
}

Image Image::hasilGeser(point delta) {
	// geser semua elemen
}

void Image::draw() {
	// gambar
	// line dan poligon
}