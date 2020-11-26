// Bai3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"

//using namespace std;
//
//
//
//
//int		nChoice = 1;
//
//void drawAxis()
//{
//	glColor3f(0, 0, 1);
//	glBegin(GL_LINES);
//		glVertex3f(0, 0, 0);
//		glVertex3f(4, 0, 0);
//
//		glVertex3f(0, 0, 0);
//		glVertex3f(0, 4, 0);
//
//		glVertex3f(0, 0, 0);
//		glVertex3f(0, 0, 4);
//	glEnd();
//}
//void myDisplay()
//{
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(4.5, 4, 2, 0, 0, 0, 0, 1, 0);
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
//	//glViewport(0, 0, screenWidth/2, screenHeight);
//	
//	drawAxis();
//
//	glColor3f(0, 0, 0);
//	//if(nChoice == 1)
//	//	tetrahedron.DrawWireframe();
//	//else if(nChoice == 2)
//	//	cube.DrawWireframe();
//	//else if (nChoice == 3)
//	//	cylinder.DrawWireframe();
//	//else if (nChoice == 4)
//	//	LuoiDao.DrawWireframe();
//	//else if (nChoice == 5)
//	//	CanDao.DrawWireframe();
//	//else if (nChoice == 6)
//	//	GiaDo1.DrawWireframe();
//	//else if (nChoice == 7)
//	//	GiaDo2.DrawWireframe();
//	//else if (nChoice == 8)
//		TayNoi.DrawWireframe();
//
//	glViewport(screenWidth/2, 0, screenWidth/2, screenHeight);
//
//	drawAxis();
//	//if (nChoice == 1)
//	//	tetrahedron.DrawColor();
//	//else if (nChoice == 2)
//	//	cube.DrawColor();
//	//else if (nChoice == 3)
//	//	cylinder.DrawColor();
//	//else if (nChoice == 4)
//	//	LuoiDao.DrawColor();
//	//else if (nChoice == 5)
//	//	CanDao.DrawColor();
//	//else if (nChoice == 6)
//	//	GiaDo1.DrawColor();
//	//else if (nChoice == 7)
//	//	GiaDo2.DrawColor();
//	//else if (nChoice == 8)
//	//	TayNoi.DrawColor();
//
//	glFlush();
//    glutSwapBuffers();
//}
//
//void myInit()
//{
//	float	fHalfSize = 4;
//
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//
//	glFrontFace(GL_CCW);
//	glEnable(GL_DEPTH_TEST);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
//}
//
//
//


