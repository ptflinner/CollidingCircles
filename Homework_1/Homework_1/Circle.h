#pragma once
#ifndef CIRCLE_PHYSICS
#define CIRCLE_PHYSICS
#include <gl/Gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

class Circle
{

private:

	struct GLfloatPoint2D {
		GLfloat x, y;
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
	void SetCenter(GLfloat x,GLfloat y);

};

#endif
