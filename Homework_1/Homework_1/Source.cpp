//Patrick Flinner
//304607711
//Date: 9/22/2017
//Assignment: Homework 1
#include <windows.h>   // use as needed for your system
#include <iostream>
#include <gl/Gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>
#include "Circle.h"

#define PI 3.14159
using namespace std;

struct vector {
	double x, y;
};

Circle circleArray[5];
int numberOfBalls;
int screenHeight = 640;
int screenWidth = 480;
double FindDistance(Circle circleA, Circle circleB);

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
	numberOfBalls = 2;
	Circle one;
	Circle two;
	two.SetCenter(screenHeight / 4, screenWidth / 4);
	circleArray[0] = one;
	circleArray[1] = two;
	glClearColor(0.0, 0.0, 0.0, 0.0);		// set the bg color to a bright white
	glColor3f(1.0f, 1.0f, 1.0f);			// set the drawing color to black 
	glPointSize(4.0);						//set the point size to 4 by 4 pixels
	glMatrixMode(GL_PROJECTION);			// set up appropriate matrices- to be explained 
	glLoadIdentity();						// to be explained
	gluOrtho2D(-1 * (screenHeight / 2), (screenHeight / 2), -(screenWidth / 2), (screenWidth / 2));		// to be explained
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
// the redraw function
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);		// clear the screen 

	for (int i = 0; i < numberOfBalls; i++) {

		glBegin(GL_POLYGON);
		for (double t = 0; t < 1; t += .01) {
			float y = circleArray[i].GetCenterY() + circleArray[i].GetRadius()*sin(2 * PI*t);
			float x = circleArray[i].GetCenterX() + circleArray[i].GetRadius()*cos(2 * PI*t);
			cout << "X: " << x << " Y: " << y << endl;
			glVertex2f(x, y);
		}
		glEnd();
	}

	glFlush();							// send all output to display 
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
	glutInit(&argc, argv);						 // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set the display mode
	glutInitWindowSize(640, 480);				 // set the window size
	glutInitWindowPosition(100, 150);			 // set the window position on the screen
	glutCreateWindow("Circle Physics");			 // open the screen window(with its exciting title)
	glutDisplayFunc(myDisplay);					 // register the redraw function
	myInit();
	glutMainLoop(); 							 // go into a perpetual loop
}

vector FindUnitVector(Circle circleA, Circle circleB) {
	vector unitVector;
	double distance;

	distance = FindDistance(circleA, circleB);
	unitVector.x = 1;
	unitVector.y = 1;

	return unitVector;
}

double FindDistance(Circle circleA, Circle circleB) {
	double cAX = 1;
	double cAY = 1;
	double cBX = 1;
	double cBY = 1;
	double distance;
	distance = sqrtf(pow((cBX - cAX), 2) + (pow(cBY - cAY, 2)));

	return distance;
}

double FindKValue(float unitVector, Circle circleA, Circle circleB) {
	return 0.0;
}

double FindNewV1(vector unitVector, Circle circle, double k) {
	return 0.0;
}

double FindNewV2(vector unitVector, Circle circle, double k) {
	return 0.0;
}