#include "Physic.h"
int Physic::SetGround(Object *g) {
	if (g == NULL) {
		return -1;
	}
	ground = g;
	return 0;
}
 
int Physic::AddGravity(RigidBody *pos) {
	if (pos == NULL) { return -1; }
	if (pos->OnMovement == true) {
		pos->y -= 0.001f;
	}
	return 0;
}
int Physic::AddCollision(Object *obj, RigidBody *pos) {
 
	pos->OnMovement = true;
	return 0;
}