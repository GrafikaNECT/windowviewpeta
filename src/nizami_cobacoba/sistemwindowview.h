#ifndef sistemwindowview_h
#define sistemwindowview_h

#define ZOOM 5
#define PAN 5

class SistemWindowView{
	//berisi informasi:
	//batas-batas window
	//batas-batas view
	//Image alam
	
	//berisi method:
	//pan: geser window
	//zoom (in dan out): ubah ukuran window
	//draw: memotong dari Image alam, translasi ke 0,0, skala ke ukuran view, translasi ke posisi view, lalu draw Image hasilnya

protected:
	point windowMin;
	point windowMax;
	point viewMin;
	point viewMax;
	Image map;

public:
	SistemWindowView(point windowMin, point windowMax, point viewMin, point viewMax, Image map);

	point getWindowMin();
	point getWindowMax();
	point getViewMin();
	point getViewMax();
	Image getMap();

	void setWindowMin(point min);
	void setWindowMax(point max);
	void setViewMin(point min);
	void setViewMax(point max);
	void setMap(Image map);


	void pan(string direction);
	void zoom(string direction);
	void draw();
};

#endif
