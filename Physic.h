#pragma once
#include "Graphic.h"
typedef struct boundary {
	float coord[8];					//Relative Coordinates
}Boundary;
typedef struct rigidbody{
	float x;
	float y;
	float z;
	Boundary bounds;
	bool OnMovement;
}RigidBody;

class Physic {
private:
	Object *ground;
	
	vector<float> ver;
public:
	int SetGround(Object *);
	int AddCollision(Object *, RigidBody *);
	int AddGravity(RigidBody*);


};
