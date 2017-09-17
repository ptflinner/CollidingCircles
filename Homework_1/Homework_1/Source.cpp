//Patrick Flinner
//304607711
//Date: 9/22/2017
//Assignment: Homework 1

#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>
#include "Circle.h"

using namespace std;

struct vector {
	double x, y;
};
//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);		// set the bg color to a bright white
	glColor3f(0.0f, 0.0f, 0.0f);			// set the drawing color to black 
	glPointSize(4.0);						//set the point size to 4 by 4 pixels
	glMatrixMode(GL_PROJECTION);			// set up appropriate matrices- to be explained 
	glLoadIdentity();						// to be explained
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);		// to be explained
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
// the redraw function
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);		// clear the screen 

	glEnd();
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

	distance = FindDistance(circleA,circleB);
	unitVector.x = 1;
	unitVector.y = 1;
	
	return unitVector;
}

double FindDistance(Circle circleA, Circle circleB) {
	double cAX;
	double cAY;
	double cBX;
	double cBY;
	double distance;
	distance = sqrtf(pow((cBX - cAX), 2) + (pow(cBY - cAY, 2)));

	return distance;
}

double FindKValue(float unitVector,Circle circleA,Circle circleB) {

}

double FindNewV1(vector unitVector,Circle circle,double k) {

}

double FindNewV2(vector unitVector,Circle circle,double k) {

}