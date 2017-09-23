//Patrick Flinner
//304607711
//Date: 9/22/2017
//Assignment: Homework 1
#include "Source.h"

using namespace std;

/******PROTOTYPES***********/
void InitializeCircles();
void myInit(void);
void CheckCollision(Circle &circle);
void myIdle();
void myDisplay(void);
Vector FindUnitVector(Circle circleA, Circle circleB);
float FindDistance(Circle circleA, Circle circleB);
float FindKValue(Vector unitVector, Circle circleA, Circle circleB);
Vector FindVelocityOne(Vector unitVector, Circle circle, float k,float mass);
Vector FindVelocityTwo(Vector unitVector, Circle circle, float k,float mass);
Vector NormalizeVector(Vector normalize);
Vector ReflectVector(Vector velocity,Vector n);

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
	/*
	glutInit(&argc, argv);						 // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set the display mode
	glutInitWindowSize(screenWidth, screenHeight);				 // set the window size
	glutInitWindowPosition(100, 150);			 // set the window position on the screen
	glutCreateWindow("Circle Physics");			 // open the screen window(with its exciting title)

	glutDisplayFunc(myDisplay);					 // register the redraw function
	glutIdleFunc(myIdle);						 // register idle callback function

	myInit();
	glutMainLoop();
	// go into a perpetual loop
*/
	
	Vector one(120, 320);
	Vector two(10, 10);
	Circle five(5,5,3,3,1);
	Circle four(2,2,0,0,2);
	Vector unitV = FindUnitVector(four, five);
	float three = 5.0;
	int now;	
	float k = FindKValue(unitV, four, five);
	one = (FindVelocityOne(unitV, four, k, five.GetMass()));
	two = (FindVelocityTwo(unitV, five, k, four.GetMass()));
	cout << k << endl;
	cout << one << endl;
	cout << two << endl;

	
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
		circle.SetVelocity(ReflectVector(circle.GetVelocity(),Vector(screenWidth/2,0)));
	}
	if (circle.GetCenterX() - circle.GetRadius() <= -screenWidth/2) {
		if (DEBUG) {
			cout << "REFLECT LEFT" << endl;
			cout << "OLD VELOCITY: " << x << " " << y << endl;
		}
		circle.SetCenter(-screenWidth/2 + circle.GetRadius(), circle.GetCenterY());
		circle.SetVelocity(ReflectVector(circle.GetVelocity(), Vector(-screenWidth / 2, 0)));
	}
	if (circle.GetCenterY() + circle.GetRadius() >= screenHeight/2) {
		if (DEBUG) {
			cout << "REFLECT TOP" << endl;
			cout << "OLD VELOCITY: " << x << " " << y << endl;
		}
		circle.SetCenter(circle.GetCenterX(),screenHeight / 2 - circle.GetRadius());
		circle.SetVelocity(ReflectVector(circle.GetVelocity(), Vector(0,screenHeight / 2)));
	}
	if (circle.GetCenterY() - circle.GetRadius() <= -screenHeight/2) {
		if (DEBUG) {
			cout << "REFLECT BOTTOM" << endl;
			cout << "OLD VELOCITY: " << x << " " << y << endl;
		}
		circle.SetCenter(circle.GetCenterX(), -screenHeight / 2 + circle.GetRadius());
		circle.SetVelocity(ReflectVector(circle.GetVelocity(), Vector(0,-screenHeight/ 2)));
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
	Sleep(1);
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
	Vector numerator;
	float distance;

	distance = FindDistance(circleA, circleB);
	numerator = circleB.GetCenter() - circleA.GetCenter();
	unitVector = numerator / distance;
	return unitVector;
}

float FindDistance(Circle circleA, Circle circleB) {
	double cAX = circleA.GetCenterX();
	double cAY = circleA.GetCenterY();
	double cBX = circleB.GetCenterX();
	double cBY = circleB.GetCenterY();
	double distance;
	distance = sqrtf(pow((cBX - cAX), 2) + (pow(cBY - cAY, 2)));

	return distance;
}

float FindKValue(Vector unitVector, Circle circleA, Circle circleB) {
	float k = 0.0;
	float v1 = 0.0;
	float v2 = 0.0;
	float mass = 0.0;
	float A1= circleA.GetVelocity()*unitVector;
	float A2= circleB.GetVelocity()*unitVector;

	if(DEBUG)cout << "A1: " << A1 << " A2: " << A2 << endl;
	mass = circleA.GetMass() + circleB.GetMass();
	if(DEBUG)cout << "Mass: " << mass << endl;
	k = 2 * (A1-A2) / mass;
	if(DEBUG)cout << "k: " << k << endl;
	return k;
}

Vector FindVelocityOne(Vector unitVector, Circle circle, float k,float mass) {
	Vector newV;
	Vector rhs = unitVector*mass*k;
	newV = circle.GetVelocity() - rhs;
	return newV;
}

Vector FindVelocityTwo(Vector unitVector, Circle circle, float k,float mass) {
	Vector newV;
	Vector rhs = unitVector*mass*k;
	newV = circle.GetVelocity() + rhs;
	return newV;
}

Vector NormalizeVector(Vector normalize)
{
	Vector normalized;
	float magnitude;
	magnitude = sqrt(pow(normalize.GetX(),2) + pow(normalize.GetY(),2));
	normalized.SetX(normalize.GetX() / magnitude);
	normalized.SetY(normalize.GetY() / magnitude);
	if(DEBUG)cout << "NORMALIZED: " << normalized.GetX() << " " << normalized.GetY() << endl;
	return normalized;
}

Vector ReflectVector(Vector velocity,Vector n)
{
	Vector r;
	Vector a;
	float base;
	
	base = velocity*NormalizeVector(n);
	if(DEBUG)cout << "BASE: " << base << endl;
	base = base * 2;
	if(DEBUG)cout << "BASE2: " << base << endl;
	a = NormalizeVector(n)*base;
	if(DEBUG)cout << "A: " << a.GetX() << " " << a.GetY() << endl;
	r = velocity - a;
	return r;
}
