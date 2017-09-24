//Patrick Flinner
//304607711
//Date: 9/24/2017
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
Vector FindUnitVector(Circle *circleA, Circle *circleB);
float FindDistance(Circle *circleA, Circle *circleB);
float FindKValue(Vector unitVector, Circle *circleA, Circle *circleB);
Vector FindVelocityOne(Vector unitVector, Circle *circle, float k,float mass);
Vector FindVelocityTwo(Vector unitVector, Circle *circle, float k,float mass);
Vector NormalizeVector(Vector normalize);
Vector ReflectVector(Vector velocity,Vector n);
void MyKeyboard(unsigned char theKey,int mouseX,int mouseY);
void MySpecialKeyboard(int theKey, int mouseX, int mouseY);
void myMouse(int button, int state, int x, int y);
void Collision(Circle *circleA,Circle *circleB);
void MoveCenter(Circle *circleA, Circle *circleB);
void DragMotion(int x, int y);

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
	
	glutInit(&argc, argv);							// initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);	// set the display mode
	glutInitWindowSize(screenWidth, screenHeight);	// set the window size
	glutInitWindowPosition(100, 150);				// set the window position on the screen
	glutCreateWindow("Circle Physics");				// open the screen window(with its exciting title)
	glutKeyboardFunc(MyKeyboard);					// Normal Keyboard input
	glutSpecialFunc(MySpecialKeyboard);				// Special Keyboard Keys
	glutMouseFunc(myMouse);							// Used for mouse input
	glutDisplayFunc(myDisplay);						// register the redraw function
	glutIdleFunc(myIdle);							// register idle callback function
	glutMotionFunc(DragMotion);						// Mouse drag input
	myInit();
	glutMainLoop();
	
}

//<<<<<<<<<<<<<<<<<<<<<<< Initializers >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
	//Initialize various values
	srand((unsigned)time(0));
	InitializeCircles();
	delta = .5;
	pause = true;
	glClearColor(1.0, 1.0, 1.0, 0.0);		
	glColor3f(0.0f, 0.0f, 1.0f);			 
	glPointSize(4.0);						
	glMatrixMode(GL_PROJECTION);			 
	glLoadIdentity();			

	//Window will be from (-320,320,-240,240)
	gluOrtho2D(-(screenWidth / 2), (screenWidth / 2), -(screenHeight / 2), (screenHeight / 2));		
}

void InitializeCircles() {

	//Spawns two balls
	numberOfBalls = 2;

	//Initializes the array to null values
	//Color array is set up with random colors
	for (int i = 0; i < 5; i++) {
		circleArray[i] = NULL;
		filled[i] = true;
		colors[i].red = (float)rand() / RAND_MAX;
		colors[i].green = (float)rand() / RAND_MAX;
		colors[i].blue = (float)rand() / RAND_MAX;
	}

	//Sets up the first two circles
	circleArray[0] = new Circle(0,0,1,1,15);
	circleArray[1] = new Circle(screenHeight / 4, screenWidth / 4, 5, 5, 50);
}

//<<<<<<<<<<<<<<<<<<<<<<<< Display Functions >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	//Slows down the movement
	Sleep(10);
	glClear(GL_COLOR_BUFFER_BIT);		

	//Draws the circles to the screen
	for (int i = 0; i < numberOfBalls; i++) {
		glColor3f(colors[i].red, colors[i].green, colors[i].blue);
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

void myIdle()
{
	//Will move the circles around
	//Checks if the circle collides with anything
	for (int i = 0; i < numberOfBalls; i++) {
		CheckCollisionWall(circleArray[i]);
		if (DEBUG)cout << "NEW VELOCITY C" << i << ": " << circleArray[i]->GetVelocity();
		CheckCollisionBall(circleArray[i], i);
		if (!pause)	circleArray[i]->MoveCoordinate(delta);
	}
	glutPostRedisplay();
}

//<<<<<<<<<<<<<<< User Inputs >>>>>>>>>>>>>>>>>>>>>>
void MyKeyboard(unsigned char theKey, int mouseX, int mouseY) {
	float x;
	float y;
	float vx;
	float vy;
	float radius;

	//Determines what happens when a specific key is pressed
	//Case 1-5 selects a specific circle
	switch (theKey) {
	case 'a':
		//Will add a new circle if there are 4 or less
		if (numberOfBalls < 5) {
			
			//Randomizes the location, velocity, and radius
			x = rand() % screenWidth / 4+1;
			y = rand() % screenHeight / 4+1;
			vx = rand() % 5 + 1;
			vy = rand() % 5 + 1;
			radius = rand() % 50 + 10;

			circleArray[numberOfBalls] = new Circle(x, y, vx, vy, radius);
			filled[numberOfBalls] = true;
			numberOfBalls++;
		}
		break;
	case 'p':
		//Will fill or unfill the circle
		filled[selected] = !filled[selected];
		break;
	case 'n':
		//Restarts the program
		myInit();
		break;
	case 'q':
		//Exits the program
		exit(EXIT_SUCCESS);
		break;
	case 'r':
		//Removes a circle from the program
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
	
	float radius = circleArray[selected]->GetRadius();
	Vector velocity= circleArray[selected]->GetVelocity();

	//Special function key presses
	switch (theKey) {
	case GLUT_KEY_PAGE_UP:
		//Makes the circle radius larger
		if (circleArray[selected] != NULL) {
			if (radius < maxRadius) {
				circleArray[selected]->SetRadius(radius+5);
			}
		}
		break;
	case GLUT_KEY_PAGE_DOWN:
		//Makes the circle radius smaller
		if (circleArray[selected] != NULL) {
			if (radius > minRadius) {
				circleArray[selected]->SetRadius(radius - 5);
			}
		}
		break;
	case GLUT_KEY_UP:
		//Makes the circle velocity faster
		if (circleArray[selected] != NULL) {
			if (velocity.GetX() < speedUp && velocity.GetX() > -speedUp &&
				velocity.GetY() < speedUp && velocity.GetY() > -speedUp) {
				circleArray[selected]->SetVelocity(velocity.GetX()*1.2, velocity.GetY()*1.2);
			}
		}
		break;
	case GLUT_KEY_DOWN:
		//Decreases circle velocity
		if (circleArray[selected] != NULL) {
			if (velocity.GetX() >speedDown || velocity.GetX() <-speedDown &&
				velocity.GetY() >speedDown || velocity.GetY() <-speedDown) {
				circleArray[selected]->SetVelocity(velocity.GetX()*.8, velocity.GetY()*.8);
			}
		}
		break;
	}
}

//Mouse Click functionality
void myMouse(int button, int state, int x, int y) {

	//Transfers mouse coordinate to window coordinate
	mouseX = x - (screenWidth / 2);
	mouseY = (screenHeight / 2 - y);
	
	/*
		If the left mouse button is clicked on a circle, it can be held down and dragged
		otherwise nothing will happen. Also see DragMotion for second portion
	*/
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if(DEBUG)cout << "X: " << mouseX   << " Y: " <<  mouseY << endl;
		mouseObjectSelected = false;
		
		//Determines if circle is clicked on
		for (int i = 0; i < numberOfBalls; i++) {
			float newX = (circleArray[i]->GetCenterX() - mouseX);
			float newY = (circleArray[i]->GetCenterY() - mouseY);

			if (DEBUG)cout << "BALL VALUES: " << endl << "X: " << circleArray[i]->GetCenterX() << " Y: " << circleArray[i]->GetCenterY() << endl;
			if (DEBUG)cout << "NX: " << newX << " NY: " << newY << endl;

			float radiusOne = 0;
			float radiusTwo = circleArray[i]->GetRadius();

			if (DEBUG)cout << newX << " " << newY << " " << sqrt(newX* newX + newY *newY) << " " << radiusOne + radiusTwo << endl;

			if (sqrt(newX* newX + newY *newY) < (radiusOne + radiusTwo))
			{
				mouseObject = i;
				mouseObjectSelected = true;
			}
			
		}
	}

	float vx;
	float vy;
	float radius;

	//Adds a new circle to the program if less than 5 circles
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		if (numberOfBalls < 5) {
			vx = rand() % 5 - 5;
			vy = rand() % 5 - 5;
			radius = rand() % 50 + 10;
			circleArray[numberOfBalls] = new Circle(mouseX, mouseY, vx, vy, radius);
			filled[numberOfBalls] = true;
			numberOfBalls++;
		}
	}

	//Pauses the circle movements
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		pause = !pause;
	}
	glutPostRedisplay();

}

//if a circle has been clicked on, then a new velocity will be calculated when left mouse button is let go
void DragMotion(int x, int y) {
	x = x - (screenWidth / 2);
	y = (screenHeight / 2 - y);
	if (mouseObjectSelected) {
		
		float radius = circleArray[mouseObject]->GetRadius();
		circleArray[mouseObject]->SetVelocity(Vector((x - mouseX) / radius, (y - mouseY) / radius));
		if(DEBUG)cout << circleArray[mouseObject]->GetVelocity() << endl;

	}
}

//<<<<<<<< Collision Checkers >>>>>>>>>>>>

//Checks if a circle collides with a wall
void CheckCollisionWall(Circle* circle) {
	float x= circle->GetVelocity().GetX();
	float y=circle->GetVelocity().GetY();
	float radius = circle->GetRadius();
	Vector velocity = circle->GetVelocity();

	//If statements for all 4 sides of the screen
	if (circle->GetCenterX() + radius >= screenWidth/2) {
		if (DEBUG) {
			cout << "REFLECT RIGHT" << endl;
			cout << "OLD VELOCITY: " << x << " " << y << endl;
		}
		circle->SetCenter(screenWidth/2 - radius, circle->GetCenterY());
		circle->SetVelocity(ReflectVector(velocity,Vector(screenWidth/2,0)));
	}
	if (circle->GetCenterX() - radius <= -screenWidth/2) {
		if (DEBUG) {
			cout << "REFLECT LEFT" << endl;
			cout << "OLD VELOCITY: " << x << " " << y << endl;
		}
		circle->SetCenter(-screenWidth/2 + radius, circle->GetCenterY());
		circle->SetVelocity(ReflectVector(velocity, Vector(-screenWidth / 2, 0)));
	}
	if (circle->GetCenterY() + radius >= screenHeight/2) {
		if (DEBUG) {
			cout << "REFLECT TOP" << endl;
			cout << "OLD VELOCITY: " << x << " " << y << endl;
		}
		circle->SetCenter(circle->GetCenterX(),screenHeight / 2 - radius);
		circle->SetVelocity(ReflectVector(velocity, Vector(0,screenHeight / 2)));
	}
	if (circle->GetCenterY() - radius <= -screenHeight/2) {
		if (DEBUG) {
			cout << "REFLECT BOTTOM" << endl;
			cout << "OLD VELOCITY: " << x << " " << y << endl;
		}
		circle->SetCenter(circle->GetCenterX(), -screenHeight / 2 + radius);
		circle->SetVelocity(ReflectVector(velocity, Vector(0,-screenHeight/ 2)));
	}
}

//Checks if the circle collides with other circles
void CheckCollisionBall(Circle* circle,int ballNumber)
{
	for (int j = 0; j < numberOfBalls; j++) {
		if (j != ballNumber) {
			float x = (circleArray[j]->GetCenterX() - circleArray[ballNumber]->GetCenterX());
			float y = (circleArray[j]->GetCenterY() - circleArray[ballNumber]->GetCenterY());
			float radiusOne = circleArray[ballNumber]->GetRadius();
			float radiusTwo = circleArray[j]->GetRadius();
			if (sqrt(x* x + y *y) < (radiusOne + radiusTwo))
			{
				if (DEBUG) {
					cout << "COLLISION" << endl;
				}

				Collision(circleArray[ballNumber], circleArray[j]);

				if(DEBUG)cout << "NEW VELOCITY C1: " << circleArray[ballNumber]->GetVelocity();
				if(DEBUG)cout << "NEW VELOCITY C2: " << circleArray[j]->GetVelocity();
			}
		}
	}
}


//<<<<<<<<<<<<<<< Collision Related Formulas >>>>>>>>>>>>>>

//Begins collision calculations
void Collision(Circle* circleA, Circle* circleB)
{
	Vector unit = FindUnitVector(circleA, circleB);
	Vector velocityA = circleA->GetVelocity();
	Vector velocityB = circleB->GetVelocity();
	float k = FindKValue(unit, circleA, circleB);

	circleA->SetVelocity(FindVelocityOne(unit, circleA, k, circleB->GetMass()));
	circleB->SetVelocity(FindVelocityTwo(unit, circleB, k, circleA->GetMass()));

	velocityA = circleA->GetVelocity();
	velocityB = circleB->GetVelocity();

	if (!pause) {
		circleA->SetCenter(circleA->GetCenterX() + velocityA.GetX(), circleA->GetCenterY() + velocityA.GetY());
		circleB->SetCenter(circleB->GetCenterX() + velocityB.GetX(), circleB->GetCenterY() + velocityB.GetY());
	}
	if (pause) {
		MoveCenter(circleA, circleB);
	}
	
}

//Creates the unit vector (CenterTwo-CenterOne)/Distance
Vector FindUnitVector(Circle *circleA, Circle *circleB) {
	Vector unitVector;
	Vector numerator;
	float distance;

	distance = FindDistance(circleA, circleB);
	numerator = circleB->GetCenter() - circleA->GetCenter();
	unitVector = numerator / distance;
	return unitVector;
}

//Finds distance between 2 points/vectors |CenterOne CenterTwo|
float FindDistance(Circle *circleA, Circle* circleB) {
	double cAX = circleA->GetCenterX();
	double cAY = circleA->GetCenterY();
	double cBX = circleB->GetCenterX();
	double cBY = circleB->GetCenterY();
	double distance;
	distance = sqrtf(pow((cBX - cAX), 2) + (pow(cBY - cAY, 2)));

	return distance;
}

//Finds the k value. 2*(velocityVector1*unitVector-velocityVector2*unitVector)/(massA+massB)
float FindKValue(Vector unitVector, Circle *circleA, Circle *circleB) {
	float k = 0.0;
	float mass = circleA->GetMass() + circleB->GetMass();
	float A1= circleA->GetVelocity()*unitVector;
	float A2= circleB->GetVelocity()*unitVector;

	if(DEBUG)cout << "A1: " << A1 << " A2: " << A2 << endl;
	if(DEBUG)cout << "Mass: " << mass << endl;
	
	k = 2 * (A1-A2) / mass;
	if(DEBUG)cout << "k: " << k << endl;
	return k;
}

//Finds velocity for circle one newVelocity=velocityOne-k*massOfCircleTwo*unitVector
Vector FindVelocityOne(Vector unitVector, Circle *circle, float k,float mass) {
	Vector newV;
	Vector rhs = unitVector*mass*k;
	newV = circle->GetVelocity() - rhs;
	return newV;
}

//Finds velocity for circle two newVelocity=velocityTwo+k*massOfCircleOne*unitVector
Vector FindVelocityTwo(Vector unitVector, Circle *circle, float k,float mass) {
	Vector newV;
	Vector rhs = unitVector*mass*k;
	newV = circle->GetVelocity() + rhs;
	return newV;
}

//Normalizes the vector (x/sqrt(x^2+y^2),y/sqrt(x^2+y^2))
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

//Formula for reflecting a vector. Used when a circle contacts a wall
//r=a-2(a*n)n
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

//Finds the collision point for two circles 
//Moves the first circle based off of the point
//Only used when a ball is added and the screen is paused
//cx=(xA*radiusTwo + xB*radiusOne)/(radiusOne+radiusTwo)
//cx=(yA*radiusTwo + yB*radiusOne)/(radiusOne+radiusTwo)
void MoveCenter(Circle *circleA, Circle *circleB) {
	
	float cX=((circleA->GetCenterX()*circleB->GetRadius()+circleB->GetCenterX()*circleA->GetRadius())
	/(circleA->GetRadius()+circleB->GetRadius()));
	float cY= ((circleA->GetCenterY()*circleB->GetRadius() + circleB->GetCenterY()*circleA->GetRadius())
	/ (circleA->GetRadius() + circleB->GetRadius()));

	if (circleA->GetCenterX() < cX) {
		circleA->SetCenter( cX - circleA->GetRadius(), circleA->GetCenterY());
	}
	if(circleA->GetCenterX() >= cX){
		circleA->SetCenter(cX + circleA->GetRadius(), circleA->GetCenterY());
	}
	if (circleA->GetCenterY() < cY) {
		circleA->SetCenter(circleA->GetCenterX(),cY - circleA->GetRadius());
	}
	if(circleA->GetCenterY() >= cY){
		circleA->SetCenter(circleA->GetCenterX(), cY + circleA->GetRadius());
	}	
}