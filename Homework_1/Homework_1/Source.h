//Patrick Flinner
//304607711
//Date: 9/24/2017
//Assignment: Homework 1

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

struct ColorSet {
	float red, blue, green;
};

ColorSet colors[5];
Circle *circleArray[5];
bool filled[5];

//Screen dimensions
const int screenHeight = 480;
const int screenWidth = 640;

//Will display couts if enabled
const bool DEBUG = false;

// Global changeable values
bool pause;
float speedUp = 15;
float speedDown=0.25;
float maxRadius = 75;
float minRadius = 10;
int mouseX;
int mouseY;
int selected;
int mouseObject;
bool mouseObjectSelected = false;
int numberOfBalls;
float delta;

#endif