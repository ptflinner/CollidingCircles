#pragma once
#ifndef CIRCLE_PHYSICS
#define CIRCLE_PHYSICS
#include "Vector.h"

class Circle
{

private:

	double radius;
	double mass;
	Vector velocity;
	Vector center;
	//Used for storing velocity if object is paused
	Vector pVelocity;

public:
	Circle();
	~Circle();
	double GetRadius();
	void SetRadius(double radius);
	double GetMass();
	Vector GetVelocity();
	void SetVelocity(Vector newVelocity);
	void PauseVelocity();
	void SetCenter(float x, float y);
	float GetCenterX();
	float GetCenterY();
	void MoveCoordinate();
};

#endif
