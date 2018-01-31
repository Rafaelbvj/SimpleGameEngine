#pragma once
#include <Windows.h>
#include <math.h>
#include <iostream>

using namespace std;

class Camera{
private:
	int *x, *y;
	int *width, *height;
	float angleX,countx;
	float angleY,county;
	float Sensibility;
	float convertIntoPlane(int *, int*);
public:
	Camera(int *positionx,int *positiony) {
		x = positionx;
		y = positiony;
		Sensibility = 40;
		angleX = 0;
		angleY = 0;
		countx = 0;
		county = 0;
 
	 
	}

	int SetScreenSize(int *, int *);
	float AngleByPositionX();
	float AngleByPositionY();
	int  SetSensibility(float);
 
};