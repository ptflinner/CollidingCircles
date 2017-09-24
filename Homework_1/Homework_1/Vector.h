//Patrick Flinner
//304607711
//Date: 9/24/2017
//Assignment: Homework 1

#pragma once
#include <iostream>

class Vector
{
private:
	float x, y;
public:
	Vector(float x, float y);
	Vector();
	~Vector();
	void SetX(float newX);
	void SetY(float newY);
	void SetCoordinates(float x,float y);
	float GetX();
	float GetY();

	//Operator Overload
	Vector operator-(Vector& rhs);
	Vector operator+(Vector& rhs);
	Vector operator*(float& rhs);
	Vector operator/(float& rhs);
	float operator*(Vector& rhs);
	void operator=(Vector& rhs);
	
	friend std::ostream& operator<<(std::ostream& os,Vector& rhs);
};

