#pragma once
#ifndef CIRCLE_PHYSICS
#define CIRCLE_PHYSICS

class Circle
{

private:

	struct GLfloatPoint2D {
		float x, y;
	};

	double radius;
	double mass;
	double velocity;
	GLfloatPoint2D center;
	//Used for storing velocity if object is paused
	double pVelocity;

	//Maybe needed?
	float momentum;

public:
	Circle();
	~Circle();
	double GetRadius();
	void SetRadius(double radius);
	double GetMass();
	double GetVelocity();
	void SetVelocity(double velocity);
	void PauseVelocity();
	void SetCenter(float x, float y);
	float GetCenterX();
	float GetCenterY();

};

#endif
