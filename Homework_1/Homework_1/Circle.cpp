#include "Circle.h"
#include <iostream>


Circle::Circle()
{
	radius = 10;
	mass = radius*radius*radius;
	velocity.SetCoordinates(0,0);
	SetCenter(0, 0);
	pVelocity.SetCoordinates(0,0);
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

Vector Circle::GetVelocity()
{
	return velocity;
}

void Circle::SetVelocity(Vector newVelocity)
{
	velocity.SetX(newVelocity.GetX());
	velocity.SetY(newVelocity.GetY());
}

void Circle::PauseVelocity()
{
	Vector z;
	pVelocity = velocity;
	velocity = z;
}

void Circle::SetCenter(float x, float y)
{
	center.SetX(x);
	center.SetY(y);
}

float Circle::GetCenterX()
{
	return center.GetX();
}

float Circle::GetCenterY()
{
	return center.GetY();
}

void Circle::MoveCoordinate()
{
	double newX = (center.GetX() + velocity.GetX());
	double newY = (center.GetY() + velocity.GetY());
	SetCenter((center.GetX() + velocity.GetX()), (center.GetY() + velocity.GetY()));
}
