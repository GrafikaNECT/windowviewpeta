SistemWindowView::SistemWindowView(point windowMin, point windowMax, point viewMin, point viewMax, Image map) {
	this.windowMin = windowMin;
	this.windowMax = windowMax;
	this.viewMin = viewMin;
	this.viewMax = viewMax;
	this.map = map;
}

void SistemWindowView::pan(string direction) {
	switch (direction) {
		case 'left':
			windowMin.move(-PAN,0);
			windowMax.move(-PAN,0);
			break;
		case 'right':
			windowMin.move(PAN,0);
			windowMax.move(PAN,0);
			break;
		case 'up':
			windowMin.move(0,-PAN);
			windowMax.move(0,-PAN);
			break;
		case 'down':
			windowMin.move(0,PAN);
			windowMax.move(0,PAN);
			break;
	}
}

void SistemWindowView::zoom(string direction) {
	switch (direction) {
		case 'in':
			//change X
			windowMin.move(-ZOOM,0);
			break;
		case 'out':
			break;
	}
}