//Patrick Flinner
//304607711
//Date: 9/24/2017
//Assignment: Homework 1

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

//Overloaded operators

//Vector Subtraction
Vector Vector::operator-( Vector & rhs)
{
	Vector subtracted;
	subtracted.SetX(x - rhs.GetX());
	subtracted.SetY(y - rhs.GetY());
	return subtracted;
}

//Vector Addition
Vector Vector::operator+(Vector & rhs)
{
	Vector added;
	added.SetX(x + rhs.GetX());
	added.SetY(y + rhs.GetY());
	return added;
}

//Dot Product
float Vector::operator*(Vector & rhs)
{
	float dot;

	dot = x*rhs.GetX() + y*rhs.GetY();
	return dot;
}

//Vector times a scalar
Vector Vector::operator*(float& rhs)
{
	Vector newVector;
	newVector.SetX(x*rhs);
	newVector.SetY(y*rhs);

	return newVector;
}

//Sets a vector to another
void Vector::operator=(Vector & rhs)
{
	x = rhs.GetX();
	y = rhs.GetY();
}

//Divides a vector by float value
Vector Vector::operator/(float & rhs)
{
	return Vector(x/rhs,y/rhs);
}

//Prints the vector
std::ostream & operator<<(std::ostream & os, Vector & rhs)
{
	os << rhs.GetX()<< " " << rhs.GetY() << std::endl;
	return os;
}
