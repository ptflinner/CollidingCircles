#ifndef LAB_ANIM_H
#define LAB_ANIM_H

#define PI 3.1415

#include <windows.h>   // use as needed for your system
#include <iostream>
#include <gl/Gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>
#include "Circle.h"

struct GLintPoint2D {
	int x, y;
};

struct GLfloatPoint2D {
	float x, y;
};


//Global Variables

Circle circleArray[5];
int numberOfBalls;
const int screenHeight = 480;
const int screenWidth = 640;
const bool DEBUG = false;
// Initial values
double delta = 0.0;

#endif