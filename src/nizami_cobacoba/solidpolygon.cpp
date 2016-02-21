#include "solidpolygon.h"
#include "line.h"
#include "print.h"

#include <algorithm>

void SolidPolygon::push_back(int x, int y){
	point p(x,y);
	push_back(p);
}

SolidPolygon SolidPolygon::hasilGeser(point delta){
	return hasilGeser(delta.getX(), delta.getY());
}

SolidPolygon SolidPolygon::hasilGeser(int deltax, int deltay){
	SolidPolygon retval = *this;
	for (int i=0;i<std::vector<point>::size();i++){
		retval[i].geser(deltax,deltay);
	}
	retval.texture = texture.hasilTranslasi(deltax, deltay);
	return retval;
}
SolidPolygon SolidPolygon::hasilPerbesar(float scale){
	SolidPolygon retval = *this;
	for (int i=0;i<std::vector<point>::size();i++){
		point& p = retval[i];
		p.setX(p.getX()*scale);
		p.setY(p.getY()*scale);
	}
	retval.texture = texture.hasilSkala(scale);
	return retval;
}

SolidPolygon SolidPolygon::hasilSkala(float scaleX, float scaleY){
	SolidPolygon retval = *this;
	for (int i=0;i<std::vector<point>::size();i++){
		point& p = retval[i];
		p.setX(p.getX()*scaleX);
		p.setY(p.getY()*scaleY);
	}
	retval.texture = texture.hasilSkala(scaleX,scaleY);
	return retval;
}

SolidPolygon SolidPolygon::hasilRotasi(float deltaDegree){
	SolidPolygon retval(std::vector<point>::size(),texture);
	for (int i=0;i<std::vector<point>::size();i++){
		const point& p = at(i);
		retval[i]=p.hasilRotasi(deltaDegree);
	}
	return retval;	
}

SolidPolygon SolidPolygon::hasilRotasi(float deltaDegree, point poros){
	SolidPolygon tmp1 = hasilGeser(poros.hasilMirror00());
	SolidPolygon tmp2 = tmp1.hasilRotasi(deltaDegree);
	return tmp2.hasilGeser(poros);
}

void SolidPolygon::draw(){
	if (size()<2) return;

	//cari ujung2 gambar
	/*int img_top, img_bot, img_left, img_right;
	img_top = at(0).getY();
	img_bot = at(0).getY();
	img_left = at(0).getX();
	img_right = at(0).getX();
	for (int i=1;i<size();i++){
		if (at(i).getY() < img_bot) img_bot = at(i).getY();
		if (at(i).getY() > img_top) img_top = at(i).getY();
	} */
	
	SolidPolygon& p = *this; //(biar gak repot ganti semua)
	//coba fill pakai point-in-SolidPolygon http://alienryderflex.com/SolidPolygon_fill/
	//TODO tukar loop x dan y supaya cepat (mungkin, cobain)
	for (int y=0;y<getYRes();y++){
		//ambil intersection dengan garis
		std::vector<int> intersections;
		for (int i=0;i<p.size()-1;i++){
			if (p[i].getY()!=p[i+1].getY())
			if ((y<p[i].getY() && y >= p[i+1].getY()) ||
				(y>=p[i].getY() && y < p[i+1].getY())){				
					int x=(int)((p[i].getX()+((float)y-p[i].getY())/((float)p[i+1].getY()-p[i].getY())*(p[i+1].getX()-p[i].getX())));
				intersections.push_back(x);
			}
		}
		int i=p.size()-1;
		if (p[i].getY()!=p[0].getY())
		if ((y<p[i].getY() && y >= p[0].getY()) ||
			 (y>=p[i].getY() && y < p[0].getY())){
			int x=(int)((p[i].getX()+((float)y-p[i].getY())/((float)p[0].getY()-p[i].getY())*(p[0].getX()-p[i].getX())));
			intersections.push_back(x);
		}

		std::sort(intersections.begin(),intersections.end());

		for (int i=0;i<intersections.size();i+=2){
//			if (intersections[i]>=img_right) break;
//			if (intersections[i+1]>img_left){
//				if (intersections[i]<img_left) intersections[i]=img_left;
//				if (intersections[i+1]>img_right) intersections[i+1]=img_right;
				for (int x=intersections[i];x<intersections[i+1];x++)
					texture.draw(x,y);
//			}
		}
	}
}

point computeIntersectionWithXline(point p1, point p2, int x){
	if (p1.getX()==p2.getX())
		return point(x,p1.getY());
	int y = (float)(p2.getY()-p1.getY())/(p2.getX()-p1.getX())*(x-p1.getX())+p1.getY();
	return point(x,y);
}

point computeIntersectionWithYline(point p1, point p2, int y){
	if (p1.getY()==p2.getY())
		return point(p1.getX(),y);
	int x = (float)(p2.getX()-p1.getX())/(p2.getY()-p1.getY())*(y-p1.getY())+p1.getX();
	return point(x,y);
}

//COHEN-SUTHERLAND?????
//https://en.wikipedia.org/wiki/Sutherland%E2%80%93Hodgman_algorithm
//dipermudah hahaha
//akdsjfalsdkfjal skdfjlaskd fjla;dskfsd
//alsdkfjalsdkfjlaskdjflaskdfja;skdfj;asdk;jf
//sori udah pusing
//males bikin komentar

SolidPolygon SolidPolygon::clip(point min, point max){
	SolidPolygon out = *this;
	SolidPolygon in;
	point S;

	int x0 = min.getX();
	int y0 = min.getY();
	int x1 = max.getX();
	int y1 = max.getY();

	//terhadap clipEdge x0y0,x0y1
	in = out;
	out.clear();
	S = in.back();

	for (iterator e = in.begin(); e<in.end(); e++){
		//if e inside clipEdge
		if (e->getX()>=x0){
			//if s not inside clipEdge
			if (S.getX()<x0){
				out.push_back(computeIntersectionWithXline(S,*e,x0));	
				//add compute intersection
			}
			out.push_back(*e);
		}else if (S.getX()>=x0){
			/*if (e->getY()<y0)
				out.push_back(x0,y0);
			if (e->getY()>y1)
				out.push_back(x0,y1);*/
			out.push_back(computeIntersectionWithXline(S,*e,x0));
		}
		S = *e;
	}

	//terhadap clipEdge x1y1,x0y1
	in = out;
	out.clear();
	S = in.back();

	for (iterator e = in.begin(); e<in.end(); e++){
		//if e inside clipEdge
		if (e->getY()<=y1){
			//if s not inside clipEdge
			if (S.getY()>y1){
				out.push_back(computeIntersectionWithYline(S,*e,y1));	
				//add compute intersection
			}
			out.push_back(*e);
		}else if (S.getY()<=y1){
			/*if (e->getX()<x0)
				out.push_back(x0,y1);
			if (e->getX()>x1)
				out.push_back(x1,y1);*/
			out.push_back(computeIntersectionWithYline(S,*e,y1));
		}
		S = *e;
	}

	//terhadap clipEdge x1y0,x0y0
	in = out;
	out.clear();
	S = in.back();

	for (iterator e = in.begin(); e<in.end(); e++){
		//if e inside clipEdge
		if (e->getY()>=y0){
			//if s not inside clipEdge
			if (S.getY()<y0){
				out.push_back(computeIntersectionWithYline(S,*e,y0));	
				//add compute intersection
			}
			out.push_back(*e);
		}else if (S.getY()>=y0){
			/*if (e->getX()<x0)
				out.push_back(x0,y0);
			if (e->getX()>x1)
				out.push_back(x1,y0);*/
			out.push_back(computeIntersectionWithYline(S,*e,y0));
		}
		S = *e;
	}

	//terhadap clipEdge x1y1,x1y0
	in = out;
	out.clear();
	S = in.back();

	for (iterator e = in.begin(); e<in.end(); e++){
		//if e inside clipEdge
		if (e->getX()<=x1){
			//if s not inside clipEdge
			if (S.getX()>x1){
				out.push_back(computeIntersectionWithXline(S,*e,x1));	
				//add compute intersection
			}
			out.push_back(*e);
		}else if (S.getX()<=x1){
			/*if (e->getY()<y0)
				out.push_back(x1,y0);
			if (e->getY()>y1)
				out.push_back(x1,y1);*/
			out.push_back(computeIntersectionWithXline(S,*e,x1));
		}
		S = *e;
	}

	return out;
}

