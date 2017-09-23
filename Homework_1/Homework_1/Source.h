#ifndef LAB_ANIM_H
#define LAB_ANIM_H

#define PI 3.1415

#include <windows.h>   // use as needed for your system
#include <iostream>
#include <gl/Gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>
#include <ctime>
#include "Circle.h"

//Global Variables

Circle *circleArray[5];
bool filled[5];
int selected;
int numberOfBalls;

const int screenHeight = 480;
const int screenWidth = 640;
const bool DEBUG = false;
float speedUp = 15;
float speedDown=0.25;
// Initial values
float delta;

#endif