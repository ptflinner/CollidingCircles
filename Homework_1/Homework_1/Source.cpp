//Patrick Flinner
//304607711
//Date: 9/22/2017
//Assignment: Homework 1
#include "Source.h"

using namespace std;

/******PROTOTYPES***********/
void InitializeCircles();
void myInit(void);
void CheckCollisionWall(Circle* circle);
void CheckCollisionBall(Circle* circle,int ballNumber);
void myIdle();
void myDisplay(void);
Vector FindUnitVector(Circle circleA, Circle circleB);
float FindDistance(Circle circleA, Circle circleB);
float FindKValue(Vector unitVector, Circle circleA, Circle circleB);
Vector FindVelocityOne(Vector unitVector, Circle circle, float k,float mass);
Vector FindVelocityTwo(Vector unitVector, Circle circle, float k,float mass);
Vector NormalizeVector(Vector normalize);
Vector ReflectVector(Vector velocity,Vector n);
void MyKeyboard(unsigned char theKey,int mouseX,int mouseY);
void MySpecialKeyboard(int theKey, int mouseX, int mouseY);
void myMouse(int button, int state, int x, int y);

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
	
	glutInit(&argc, argv);						 // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set the display mode
	glutInitWindowSize(screenWidth, screenHeight);				 // set the window size
	glutInitWindowPosition(100, 150);			 // set the window position on the screen
	glutCreateWindow("Circle Physics");			 // open the screen window(with its exciting title)
	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(MySpecialKeyboard);
	//glutMouseFunc(myMouse);
	glutDisplayFunc(myDisplay);					 // register the redraw function
	glutIdleFunc(myIdle);						 // register idle callback function

	myInit();
	glutMainLoop();
	// go into a perpetual loop

	/*
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

	*/
}
//<<<<<<<<<<<<<<<<<<<<<<< Initializer >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
	InitializeCircles();
	srand((unsigned)time(0));
	delta = .5;
	glClearColor(1.0, 1.0, 1.0, 0.0);		
	glColor3f(0.0f, 0.0f, 1.0f);			 
	glPointSize(4.0);						
	glMatrixMode(GL_PROJECTION);			 
	glLoadIdentity();						
	gluOrtho2D(-(screenWidth / 2), (screenWidth / 2), -(screenHeight / 2), (screenHeight / 2));		
}

void InitializeCircles() {
	numberOfBalls = 2;
	for (int i = 0; i < 5; i++) {
		circleArray[i] = NULL;
		filled[i] = true;
	}
	circleArray[0] = new Circle(0,0,1,1,15);
	circleArray[1] = new Circle(screenHeight / 4, screenWidth / 4, 5, 5, 50);
}

void MyKeyboard(unsigned char theKey, int mouseX, int mouseY) {
	float x;
	float y;
	float vx;
	float vy;
	float radius;
	switch (theKey) {
	case 'a':
		if (numberOfBalls < 5) {
			x = rand() % screenWidth / 4+1;
			y = rand() % screenHeight / 4+1;
			vx = rand() % 5 + 1;
			vy = rand() % 5 + 1;
			radius = rand() % 50 + 1;
			circleArray[numberOfBalls] = new Circle(x, y, vx, vy, radius);
			numberOfBalls++;
		}
		break;
	case 'p':
		if (filled[selected])filled[selected] = false;
		else filled[selected] = true;
		break;
	case 'n':
		myInit();
		break;
	case 'q':
		exit(EXIT_SUCCESS);
		break;
	case 'r':
		if (numberOfBalls > 1) {
			numberOfBalls--;
			circleArray[numberOfBalls] = NULL;
		}
		break;
	case '1':
		if (circleArray[0] != NULL) {
			selected = 0;
		}
		
		break;
	case '2':
		if (circleArray[1] != NULL) {
			selected = 1;
		}
		
		break;
	case '3':
		if (circleArray[2] != NULL) {
			selected = 2;
		}
		
		break;
	case '4':
		if (circleArray[3] != NULL) {
			selected = 3;
		}
		
		break;
	case '5':
		if (circleArray[4] != NULL) {
			selected = 4;
		}
		
		break;
	}
}

void MySpecialKeyboard(int theKey, int mouseX, int mouseY) {
	switch (theKey) {
	case GLUT_KEY_PAGE_UP:
		if (circleArray[selected] != NULL) {
			if (circleArray[selected]->GetRadius() < 150) {
				circleArray[selected]->SetRadius(circleArray[selected]->GetRadius()+5);
			}
		}
		break;
	case GLUT_KEY_PAGE_DOWN:
		if (circleArray[selected] != NULL) {
			if (circleArray[selected]->GetRadius() > 5) {
				circleArray[selected]->SetRadius(circleArray[selected]->GetRadius() - 5);
			}
		}
		break;
	case GLUT_KEY_UP:
		if (circleArray[selected] != NULL) {
			if (circleArray[selected]->GetVelocity().GetX() < speedUp && circleArray[selected]->GetVelocity().GetX() > -speedUp &&
				circleArray[selected]->GetVelocity().GetY() < speedUp && circleArray[selected]->GetVelocity().GetY() > -speedUp) {
				circleArray[selected]->SetVelocity(circleArray[selected]->GetVelocity().GetX()*1.2, circleArray[selected]->GetVelocity().GetY()*1.2);
			}
		}
		break;
	case GLUT_KEY_DOWN:
		if (circleArray[selected] != NULL) {
			if (circleArray[selected]->GetVelocity().GetX() >speedDown || circleArray[selected]->GetVelocity().GetX() <-speedDown &&
				circleArray[selected]->GetVelocity().GetY() >speedDown || circleArray[selected]->GetVelocity().GetY() <-speedDown) {
				circleArray[selected]->SetVelocity(circleArray[selected]->GetVelocity().GetX()*.8, circleArray[selected]->GetVelocity().GetY()*.8);
			}
		}
		break;
	}
}

void myMouse(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (int i = 0; i < numberOfBalls; i++) {

		}
	}

	glutPostRedisplay();

}

void CheckCollisionWall(Circle* circle) {
	float x= circle->GetVelocity().GetX();
	float y=circle->GetVelocity().GetY();

	if (circle->GetCenterX() + circle->GetRadius() >= screenWidth/2) {
		if (DEBUG) {
			cout << "REFLECT RIGHT" << endl;
			cout << "OLD VELOCITY: " << x << " " << y << endl;
		}
		circle->SetCenter(screenWidth/2 - circle->GetRadius(), circle->GetCenterY());
		circle->SetVelocity(ReflectVector(circle->GetVelocity(),Vector(screenWidth/2,0)));
	}
	if (circle->GetCenterX() - circle->GetRadius() <= -screenWidth/2) {
		if (DEBUG) {
			cout << "REFLECT LEFT" << endl;
			cout << "OLD VELOCITY: " << x << " " << y << endl;
		}
		circle->SetCenter(-screenWidth/2 + circle->GetRadius(), circle->GetCenterY());
		circle->SetVelocity(ReflectVector(circle->GetVelocity(), Vector(-screenWidth / 2, 0)));
	}
	if (circle->GetCenterY() + circle->GetRadius() >= screenHeight/2) {
		if (DEBUG) {
			cout << "REFLECT TOP" << endl;
			cout << "OLD VELOCITY: " << x << " " << y << endl;
		}
		circle->SetCenter(circle->GetCenterX(),screenHeight / 2 - circle->GetRadius());
		circle->SetVelocity(ReflectVector(circle->GetVelocity(), Vector(0,screenHeight / 2)));
	}
	if (circle->GetCenterY() - circle->GetRadius() <= -screenHeight/2) {
		if (DEBUG) {
			cout << "REFLECT BOTTOM" << endl;
			cout << "OLD VELOCITY: " << x << " " << y << endl;
		}
		circle->SetCenter(circle->GetCenterX(), -screenHeight / 2 + circle->GetRadius());
		circle->SetVelocity(ReflectVector(circle->GetVelocity(), Vector(0,-screenHeight/ 2)));
	}
}

void CheckCollisionBall(Circle* circle,int ballNumber)
{
	for (int i = 0; i < numberOfBalls; i++) {
		for (double t = 0; t < 1; t += .01) {
			float x = circleArray[i]->GetCenterX() + circleArray[i]->GetRadius()*cos(2 * PI*t);
			float y = circleArray[i]->GetCenterY() + circleArray[i]->GetRadius()*sin(2 * PI*t);

			float x2 = circle->GetCenterX() + circle->GetRadius()*cos(2 * PI*t);
			float y2 = circle->GetCenterY() + circle->GetRadius()*sin(2 * PI*t);
		}
	}
}

void myIdle()
{	
	for (int i = 0; i < numberOfBalls; i++) {
		CheckCollisionWall(circleArray[i]);
		CheckCollisionBall(circleArray[i], i);
		circleArray[i]->MoveCoordinate(delta);
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
		if (!filled[i])glBegin(GL_LINE_LOOP);
		else glBegin(GL_POLYGON);
		for (double t = 0; t < 1; t += .01) {
			float x = circleArray[i]->GetCenterX() + circleArray[i]->GetRadius()*cos(2 * PI*t);
			float y = circleArray[i]->GetCenterY() + circleArray[i]->GetRadius()*sin(2 * PI*t);
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
