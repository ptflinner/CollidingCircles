//Patrick Flinner
//304607711
//Date: 9/24/2017
//Assignment: Homework 1

#include "Circle.h"
#include <iostream>


Circle::Circle()
{
	radius = 10;
	mass = radius*radius*radius;
	velocity.SetCoordinates(0,0);
	SetCenter(0, 0);
}

Circle::Circle(float x, float y, float vx, float vy, float r)
{
	center.SetCoordinates(x, y);
	velocity.SetCoordinates(vx, vy);
	radius = r;
	mass = radius*radius*radius;
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

void Circle::SetVelocity(float x, float y)
{
	Vector v(x, y);
	SetVelocity(v);
}

void Circle::SetCenter(float x, float y)
{
	center.SetX(x);
	center.SetY(y);
}

void Circle::SetCenter(Vector vector)
{
	center.SetX(vector.GetX());
	center.SetY(vector.GetY());
}

float Circle::GetCenterX()
{
	return center.GetX();
}

float Circle::GetCenterY()
{
	return center.GetY();
}

Vector Circle::GetCenter()
{
	return center;
}

//Moves the coordinate based on time and velocity
void Circle::MoveCoordinate(float t)
{
	float newX = (center.GetX() + velocity.GetX()*t);
	float newY = (center.GetY() + velocity.GetY()*t);
	SetCenter(newX, newY);
}

