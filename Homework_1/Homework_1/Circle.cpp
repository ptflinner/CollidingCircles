#include "Circle.h"



Circle::Circle()
{
	radius = 50;
	mass = radius*radius*radius;
	velocity = 1;
	SetCenter(0, 0);
	pVelocity = 0;
}


Circle::~Circle()
{
}

double Circle::GetRadius()
{
	return radius;
}

void Circle::SetRadius(double newRadius)
{
	radius = newRadius;
	mass = radius*radius*radius;
}

double Circle::GetMass()
{
	return mass;
}

double Circle::GetVelocity()
{
	return velocity;
}

void Circle::SetVelocity(double newVelocity)
{
	velocity = newVelocity;
}

void Circle::PauseVelocity()
{
	pVelocity = velocity;
	velocity = 0;
}

void Circle::SetCenter(float x, float y)
{
	center.x = x;
	center.y = y;
}

float Circle::GetCenterX()
{
	return center.x;
}

float Circle::GetCenterY()
{
	return center.y;
}
