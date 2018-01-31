#include "Camera.h"
int Camera::SetSensibility(float sens) {
	if (sens <= 0) {
		return -1;
	}

	Sensibility = sens;
	return 0;
}
float Camera::convertIntoPlane(int *pos,int *op) {
	if (*pos == *op / 2) {
		return 0;
	}
	return float(*pos - (float)*op / 2);
}
float Camera::AngleByPositionY(){
	
	if (*x >= *width - 300|| *x <= 300) {
		
		county = angleY;
	 
		SetCursorPos(*width/2, *y);
	}
 
	else {
	
			angleY = county + Sensibility * convertIntoPlane(x, width) / float((*width - 300.0f) / 2.0f);
	
		
	}
	return (float)angleY;
}
float Camera::AngleByPositionX() {
	
	if (*y >= *height - 100||*y<= 100) {
		 
		countx = angleX;
		SetCursorPos(*x, *height / 2);
	}
	else {

			angleX = countx + Sensibility * convertIntoPlane(y, height) / float((*height - 100.0f) / 2.0f);
		 
	}

	return angleX;
}
 
int Camera::SetScreenSize(int *w, int *h) {
	if (*w < 0 || *h < 0) { return -1; }
	width = w;
	height = h;
	return 0;
}