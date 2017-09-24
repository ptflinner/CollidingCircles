//Patrick Flinner
//304607711
//Date: 9/24/2017
//Assignment: Homework 1

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
	void SetCenter(float x, float y);
	void SetCenter(Vector vector);
	float GetCenterX();
	float GetCenterY();
	Vector GetCenter();
	void MoveCoordinate(float t);
};

#endif
