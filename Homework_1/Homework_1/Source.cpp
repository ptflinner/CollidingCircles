//Patrick Flinner
//304607711
//Date: 9/22/2017
//Assignment: Homework 1
#include "Source.h"

using namespace std;

void InitializeCircles();
void myInit(void);
void CheckCollision(Circle &circle);
void myIdle();
void myDisplay(void);
Vector FindUnitVector(Circle circleA, Circle circleB);
double FindDistance(Circle circleA, Circle circleB);
double FindKValue(float unitVector, Circle circleA, Circle circleB);
Vector FindVelocityOne(Vector unitVector, Circle circle, double k);
Vector FindVelocityTwo(Vector unitVector, Circle circle, double k);
Vector NormalizeVector(Vector normalize);
Vector ReflectVector(Circle circle);

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
	glutInit(&argc, argv);						 // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set the display mode
	glutInitWindowSize(screenWidth, screenHeight);				 // set the window size
	glutInitWindowPosition(100, 150);			 // set the window position on the screen
	glutCreateWindow("Circle Physics");			 // open the screen window(with its exciting title)

	glutDisplayFunc(myDisplay);					 // register the redraw function
	glutIdleFunc(myIdle);						 // register idle callback function

	myInit();
	glutMainLoop(); 							 // go into a perpetual loop
}
//<<<<<<<<<<<<<<<<<<<<<<< Initializer >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
	InitializeCircles();
	glClearColor(1.0, 1.0, 1.0, 0.0);		
	glColor3f(0.0f, 0.0f, 1.0f);			 
	glPointSize(4.0);						
	glMatrixMode(GL_PROJECTION);			 
	glLoadIdentity();						
	gluOrtho2D(-(screenWidth / 2), (screenWidth / 2), -(screenHeight / 2), (screenHeight / 2));		
}

void InitializeCircles() {
	numberOfBalls = 2;
	Circle one;
	one.SetVelocity(Vector(1, 1));
	Circle two;
	two.SetVelocity(Vector(5, 5));
	two.SetCenter(screenHeight / 4, screenWidth / 4);
	circleArray[0] = one;
	circleArray[1] = two;
}

void CheckCollision(Circle &circle) {
	float x= circle.GetVelocity().GetX();
	float y=circle.GetVelocity().GetY();
	if (circle.GetCenterX() + circle.GetRadius() >= screenWidth/2) {
		if (DEBUG) {
			cout << "REFLECT RIGHT" << endl;
			cout << "OLD VELOCITY: " << x << " " << y << endl;
		}
		circle.SetCenter(screenWidth/2 - circle.GetRadius(), circle.GetCenterY());
		circle.SetVelocity(Vector(-x,y));
	}
	if (circle.GetCenterX() - circle.GetRadius() <= -screenWidth/2) {
		if (DEBUG) {
			cout << "REFLECT LEFT" << endl;
			cout << "OLD VELOCITY: " << x << " " << y << endl;
		}
		circle.SetCenter(-screenWidth/2 + circle.GetRadius(), circle.GetCenterY());
		circle.SetVelocity(Vector(-x,y));
	}
	if (circle.GetCenterY() + circle.GetRadius() >= screenHeight/2) {
		if (DEBUG) {
			cout << "REFLECT TOP" << endl;
			cout << "OLD VELOCITY: " << x << " " << y << endl;
		}
		circle.SetCenter(circle.GetCenterX(),screenHeight / 2 - circle.GetRadius());
		circle.SetVelocity(Vector(x, -y));
	}
	if (circle.GetCenterY() - circle.GetRadius() <= -screenHeight/2) {
		if (DEBUG) {
			cout << "REFLECT BOTTOM" << endl;
			cout << "OLD VELOCITY: " << x << " " << y << endl;
		}
		circle.SetCenter(circle.GetCenterX(), -screenHeight / 2 + circle.GetRadius());
		circle.SetVelocity(Vector(x, -y));
	}
}

void myIdle()
{	
	for (int i = 0; i < numberOfBalls; i++) {
		CheckCollision(circleArray[i]);
		circleArray[i].MoveCoordinate();
		
	}
	glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
// the redraw function
void myDisplay(void)
{
	Sleep(10);
	glClear(GL_COLOR_BUFFER_BIT);		// clear the screen 

	for (int i = 0; i < numberOfBalls; i++) {
		glBegin(GL_POLYGON);
		for (double t = 0; t < 1; t += .01) {
			float x = circleArray[i].GetCenterX() + circleArray[i].GetRadius()*cos(2 * PI*t);
			float y = circleArray[i].GetCenterY() + circleArray[i].GetRadius()*sin(2 * PI*t);
			glVertex2f(x, y);
		}
		
		glEnd();
	}

	glutSwapBuffers();
}

Vector FindUnitVector(Circle circleA, Circle circleB) {
	Vector unitVector;
	double distance;

	distance = FindDistance(circleA, circleB);
	unitVector.SetX(1);
	unitVector.SetY(1);

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

Vector FindVelocityOne(Vector unitVector, Circle circle, double k) {
	Vector newV;
	return newV;
}

Vector FindVelocityTwo(Vector unitVector, Circle circle, double k) {
	Vector newV;
	return newV;
}

Vector NormalizeVector(Vector normalize)
{
	return Vector();
}

Vector ReflectVector(Circle circle)
{
	return Vector();
}
