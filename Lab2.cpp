// Bai3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"

using namespace std;

int		screenWidth = 1000;
int		screenHeight= 600;

Mesh	tetrahedron;
Mesh	cube;
Mesh	cylinder;
Mesh	shape1;
Mesh	shape2;
Mesh	shape3;
Mesh	shape4;
Mesh	shape5;

int		nChoice = 1;

void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(4, 0, 0);

		glVertex3f(0, 0, 0);
		glVertex3f(0, 4, 0);

		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 4);
	glEnd();
}
void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4.5, 4, 2, 0, 0, 0, 0, 1, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glViewport(0, 0, screenWidth/2, screenHeight);
	
	drawAxis();

	glColor3f(0, 0, 0);
	if(nChoice == 1)
		tetrahedron.DrawWireframe();
	else if(nChoice == 2)
		cube.DrawWireframe();
	else if (nChoice == 3)
		cylinder.DrawWireframe();
	else if (nChoice == 4)
		shape1.DrawWireframe();
	else if (nChoice == 5)
		shape2.DrawWireframe();
	else if (nChoice == 6)
		shape3.DrawWireframe();
	else if (nChoice == 7)
		shape4.DrawWireframe();
	else if (nChoice == 8)
		shape5.DrawWireframe();

	glViewport(screenWidth/2, 0, screenWidth/2, screenHeight);

	drawAxis();
	if (nChoice == 1)
		tetrahedron.DrawColor();
	else if (nChoice == 2)
		cube.DrawColor();
	else if (nChoice == 3)
		cylinder.DrawColor();
	else if (nChoice == 4)
		shape1.DrawColor();
	else if (nChoice == 5)
		shape2.DrawColor();
	else if (nChoice == 6)
		shape3.DrawColor();
	else if (nChoice == 7)
		shape4.DrawColor();
	else if (nChoice == 8)
		shape5.DrawColor();

	glFlush();
    glutSwapBuffers();
}

void myInit()
{
	float	fHalfSize = 4;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "1. Tetrahedron" << endl;
	cout << "2. Cube" << endl;
	cout << "3. Cylinder" << endl;
	cout << "4. Shape1" << endl;
	cout << "5. Shape2" << endl;
	cout << "6. Shape3" << endl;
	cout << "7. Shape4" << endl;
	cout << "8. Shape5" << endl;
	cout << "Input the choice: " << endl;
	cin  >> nChoice;

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Lab 2"); // open the screen window

	tetrahedron.CreateTetrahedron();
	cube.CreateCube(2,1,1);
	cylinder.CreateCylinder(10, 2, 0.5);
	shape1.CreatShape1(4, 0.5, 0.8, 7, 0.5);
	shape2.CreatShape2(0.3, 10, 0.2);
	shape3.CreatShape3(1, 0.4, 5);
	shape4.CreatShape4(1, 0.4, 10);
	shape5.CreatShape5(0.5, 0.4, 10);

	myInit();
    glutDisplayFunc(myDisplay);
	  
	glutMainLoop();
	return 0;
}

