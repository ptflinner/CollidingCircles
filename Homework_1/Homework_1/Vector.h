#pragma once
class Vector
{
private:
	float x, y;
public:
	Vector();
	~Vector();
	void SetX(float newX);
	void SetY(float newY);
	void SetCoordinates(float x,float y);
	float GetX();
	float GetY();
};

