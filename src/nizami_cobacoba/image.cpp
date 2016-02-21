
/*
 * Nama Berkas			: image.cpp
 * Deskripsi			: Realisasi dari image.h
 */

#ifndef image_cpp
#define image_cpp

#include "image.h"
#include "texture.h"

#include <vector>

//menambah line
//perhatikan orderGambar (spek di bawah)
void Image::addLine(line l){
	lines.push_back(l);
	orderGambarLine.push_back(numElmts);
	numElmts++;
}

//memanggil addLine
//misal: isi points adalah {p0,p1,p2, ... pn-1}
//	maka, panggil 	addLine(line(p0,p1))
//			addLine(line(p1,p2))
//			.
//			.
//			.
//			addLine(line(pn-2,pn-1))
void Image::addLines(const std::list<point>& points){
	std::list<point>::const_iterator it = points.begin();
	std::list<point>::const_iterator prev = it;
	for (it++;it!=points.end();it++){
		addLine(line(*prev,*it));
		prev=it;
	}
}

//menambah SolidPolygon
//perhatikan orderGambar (spek di bawah)
void Image::addSolidPolygon(SolidPolygon solidPolygon){
	solidPolygons.push_back(solidPolygon);
	orderGambarSolidPolygon.push_back(numElmts);
	numElmts++;
}

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
Image Image::fromStream(std::istream& streamGambar,
			std::istream& streamTekstur){
	//load tekstur
	int N;
	std::vector<Texture> textures;
	streamTekstur>>N;
	for (int i=0;i<N;i++){
		textures.push_back(Texture::fromStream(streamTekstur));
	}

	Image retval;
	streamGambar>>N;
	for (int i=0;i<N;i++){
		int jenis;
		streamGambar>>jenis;
		int no_tekstur;
		streamGambar>>no_tekstur;
		int M;
		streamGambar>>M;
		std::vector<point> points(M);
		for (int i=0;i<M;i++){
			int X,Y;
			streamGambar>>X>>Y;
			points[i].setX(X);
			points[i].setY(Y);
		}
		int prev;
		switch(jenis){
		case 0:
			prev=0;
			for (int i=1;i<M;i++){
				retval.addLine(line(points[prev],points[i],textures[no_tekstur]));
				prev=i;
			}
		break;
		case 1:
			retval.addSolidPolygon(SolidPolygon(points,textures[no_tekstur]));
		break;
		}
	}
	return retval;
}

//clip semua elemen
Image Image::clip(point min, point max){
	Image retval;
	std::list<line>::iterator itline = lines.begin();
	std::list<SolidPolygon>::iterator itpol = solidPolygons.begin();
	std::list<int>::iterator itordline = orderGambarLine.begin();
	std::list<int>::iterator itordpol = orderGambarSolidPolygon.begin();
	
	while (itline != lines.end() && itpol != solidPolygons.end()){
		if (itordpol==orderGambarSolidPolygon.end()){
			line l = itline->clip(min,max);
			if (!(l.getX1()==-1 && l.getX2()==-1
				&&l.getY1()==-1 && l.getY2()==-1)){
				retval.addLine(l);
			}
			itline++;
			itordline++;
		}else if(itordline==orderGambarLine.end()){
			addSolidPolygon(itpol->clip(min,max));
			itpol++;
			itordpol++;
		}else if (*itordline<*itordpol){
			line l = itline->clip(min,max);
			if (!(l.getX1()==-1 && l.getX2()==-1
				&&l.getY1()==-1 && l.getY2()==-1)){
				retval.addLine(l);
			}
			itline++;
			itordline++;
		}else{
			addSolidPolygon(itpol->clip(min,max));
			itpol++;
			itordpol++;
		}
	}
	return retval;
}

//geser semua elemen
Image Image::hasilGeser(point delta){
	Image retval=*this;
	for (std::list<line>::iterator itline = retval.lines.begin();
		itline!=retval.lines.end();itline++){
		itline->move(delta);
	}
	for (std::list<SolidPolygon>::iterator itpol = retval.solidPolygons.begin();
		itpol!=retval.solidPolygons.end();itpol++){
		*itpol = itpol->hasilGeser(delta);
	}
	return retval;
}

//skala semua elemen gambar
Image Image::hasilSkala(float scaleX, float scaleY){
	Image retval=*this;
	for (std::list<line>::iterator itline = retval.lines.begin();
		itline!=retval.lines.end();itline++){
		itline->scale(scaleX,scaleY);
	}
	for (std::list<SolidPolygon>::iterator itpol = retval.solidPolygons.begin();
		itpol!=retval.solidPolygons.end();itpol++){
		*itpol = itpol->hasilSkala(scaleX,scaleY);
	}
	return retval;
}

//gambar
//line dan poligon
void Image::draw(){
	std::list<line>::iterator itline = lines.begin();
	std::list<SolidPolygon>::iterator itpol = solidPolygons.begin();
	std::list<int>::iterator itordline = orderGambarLine.begin();
	std::list<int>::iterator itordpol = orderGambarSolidPolygon.begin();
	
	while (itline != lines.end() || itpol != solidPolygons.end()){
		if (itordpol==orderGambarSolidPolygon.end()){
			itline->draw();
			itline++;
			itordline++;
		}else if(itordline==orderGambarLine.end()){
			itpol->draw();
			itpol++;
			itordpol++;
		}else if (*itordline<*itordpol){
			itline->draw();
			itline++;
			itordline++;
		}else{
			itpol->draw();
			itpol++;
			itordpol++;
		}
	}
}

#endif


