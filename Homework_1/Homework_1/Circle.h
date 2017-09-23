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
	Circle(float x,float y, float vx,float vy,float r);
	~Circle();
	double GetRadius();
	void SetRadius(double radius);
	double GetMass();
	Vector GetVelocity();
	void SetVelocity(Vector newVelocity);
	void SetVelocity(float x,float y);
	void PauseVelocity();
	void SetCenter(float x, float y);
	void SetCenter(Vector vector);
	float GetCenterX();
	float GetCenterY();
	Vector GetCenter();
	void MoveCoordinate(float t);
};

#endif
