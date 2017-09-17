#include "Circle.h"



Circle::Circle()
{
	this->radius = 1;
	this->mass = radius*radius*radius;
	this->velocity = 1;
}


Circle::~Circle()
{
}

double Circle::GetRadius()
{
	return radius;
}

void Circle::SetRadius(double radius)
{
	this->radius = radius;
	this->mass = radius*radius*radius;
}

double Circle::GetMass()
{
	return mass;
}

double Circle::GetVelocity()
{
	return velocity;
}

void Circle::SetVelocity(double velocity)
{
	this->velocity=velocity;
}

void Circle::PauseVelocity()
{
	this->pVelocity = velocity;
	this->velocity = 0;
}

void Circle::SetCenter(GLfloat x, GLfloat y)
{
	center.x = x;
	center.y = y;
}
