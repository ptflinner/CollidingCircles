#include "Vector.h"



Vector::Vector(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector::Vector()
{
	x = 0;
	y = 0;
}


Vector::~Vector()
{
}

void Vector::SetX(float newX)
{
	x = newX;
}

void Vector::SetY(float newY)
{
	y = newY;
}

void Vector::SetCoordinates(float x, float y)
{
	SetX(x);
	SetY(y);
}

float Vector::GetX()
{
	return x;
}

float Vector::GetY()
{
	return y;
}
