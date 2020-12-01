#include "stdafx.h"
#include "Mesh.h"
#include <math.h>
#include <iostream>
#include "supportClass.h"

using namespace std;

#define PI			3.1415926
#define	COLORNUM		14

// Khai bao Mesh
#pragma region
Mesh	tetrahedron;
Mesh	DeDao;
Mesh	cylinder;
Mesh	LuoiDao;
Mesh	CanDao;
Mesh	GiaDo1;
Mesh	GiaDo2;
Mesh	TayNoi;
Mesh	chot;


int		screenWidth = 1200;
int		screenHeight = 600;
#pragma endregion

// Mesh
#pragma region
float ColorArr[COLORNUM][3] = {
	{1.0, 0.0, 0.0},
	{0.0, 1.0, 0.0},
	{0.0, 0.0, 1.0},
	{1.0, 1.0, 0.0},
	{1.0, 0.0, 1.0},
	{0.0, 1.0, 1.0},
	{0.3, 0.3, 0.3},
	{0.5, 0.5, 0.5},
	{0.9, 0.9, 0.9},
	{1.0, 0.5, 0.5},
	{0.5, 1.0, 0.5},
	{0.5, 0.5, 1.0},
	{0.0, 0.0, 0.0},
	{1.0, 1.0, 1.0}};

void Mesh::CreateTetrahedron()
{
	int i;
	numVerts=4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces= 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	

	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;	
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	
	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;
}

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;
			
			ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]); 
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::SetColor(int colorIdx)
{
	for (int f = 0; f < numFaces; f++)
	{
		for (int v = 0; v < face[f].nVerts; v++)
		{
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}

void Mesh::CalculateFacesNorm()
{
	for (int f = 0; f < numFaces; f++)
	{
		float mx = 0, my = 0, mz = 0;
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			int next = face[f].vert[(v + 1) % face[f].nVerts].vertIndex;
			mx += (pt[iv].y - pt[next].y) * (pt[iv].z + pt[next].z);
			my += (pt[iv].z - pt[next].z) * (pt[iv].x + pt[next].x);
			mz += (pt[iv].x - pt[next].x) * (pt[iv].y + pt[next].y);
		}
		face[f].facenorm.set(mx, my, mz);
		face[f].facenorm.normalize();
	}
}

// To mau
void Mesh::Draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			glColor3f(ColorArr[iv][0], ColorArr[iv][1], ColorArr[iv][2]);
			glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

// Thiet lap vat lieu cho doi tuong 
void Mesh::setupMaterial(float ambient[], float diffuse[], float specular[], float shiness)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}

void Mesh::CreateCuboid(float	fSizeX, float	fSizeY, float	fSizeZ)
{
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSizeX, fSizeY, fSizeZ);
	pt[1].set(fSizeX, fSizeY, fSizeZ);
	pt[2].set(fSizeX, fSizeY, -fSizeZ);
	pt[3].set(-fSizeX, fSizeY, -fSizeZ);
	pt[4].set(-fSizeX, -fSizeY, fSizeZ);
	pt[5].set(fSizeX, -fSizeY, fSizeZ);
	pt[6].set(fSizeX, -fSizeY, -fSizeZ);
	pt[7].set(-fSizeX, -fSizeY, -fSizeZ);


	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i<face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i<face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i<face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i<face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i<face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i<face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

}

void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius)
{
	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;

	pt[0].set(0, fHeight / 2, 0);
	for (i = 0; i<nSegment; i++)
	{
		x = fRadius* cos(fAngle*i);
		z = fRadius* sin(fAngle*i);
		y = fHeight / 2;
		pt[i + 1].set(x, y, z);

		y = -fHeight / 2;
		pt[i + 1 + nSegment].set(x, y, z);
	}
	pt[numVerts - 1].set(0, -fHeight / 2, 0);

	numFaces = nSegment * 3;
	face = new Face[numFaces];

	idx = 0;
	for (i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for (i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1;
		if (i <nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for (i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if (i < nSegment - 1)
			face[idx].vert[2].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex = 1 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}

}


void Mesh::CreateLuoiDao(float fSizeX, float fSizeY, float fSizeZ, int nSegment, float fRadius)
{
	int		i;
	int		idx;
	float	fAngle = PI / nSegment / 2;
	float	x, y, z;


	numVerts = 10 + (nSegment-1)*2;
	pt = new Point3[numVerts];
	pt[0].set(0, fSizeY, -fSizeZ);
	pt[1].set(0, 0, -fSizeZ);
	pt[2].set(0, 0, 0);
	pt[3].set(0, fSizeY, 0);
	pt[4].set(-fSizeX, fSizeY, -fRadius);
	pt[5].set(-fSizeX, 0, -fRadius);
	pt[6].set(-fSizeX, 0, 0);
	pt[7].set(-fSizeX, fSizeY, 0);
	pt[8].set(-fSizeX - fRadius, 0, 0);
	pt[9].set(-fSizeX - fRadius, fSizeY, 0);

	for (i = 1; i<nSegment; i++)
	{
		x = - fRadius* sin(fAngle*i) - fSizeX;
		z = - fRadius* cos(fAngle*i);
		y = fSizeY;
		pt[i + 9].set(x, y, z);

		y = 0;
		pt[i + 8 + nSegment].set(x, y, z);
	}

	numFaces = nSegment*3 + 5;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 3;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 8;
	face[0].vert[3].vertIndex = 9;
	for (i = 0; i<face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 1;
	face[1].vert[2].vertIndex = 5;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i<face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 7;
	face[2].vert[3].vertIndex = 4;
	for (i = 0; i<face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 2;
	face[3].vert[2].vertIndex = 6;
	face[3].vert[3].vertIndex = 5;
	for (i = 0; i<face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 0;
	face[4].vert[1].vertIndex = 1;
	face[4].vert[2].vertIndex = 2;
	face[4].vert[3].vertIndex = 3;
	for (i = 0; i<face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//cylinder
	idx = 5;
	for (i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 7;
		if (i == 0)
			face[idx].vert[1].vertIndex = 4;
		else
			face[idx].vert[1].vertIndex = i + 9;
		if (i == nSegment - 1)
			face[idx].vert[2].vertIndex = 9;
		else
			face[idx].vert[2].vertIndex = i + 10;
		idx++;
	}

	for (i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		if (i == 0) {
			face[idx].vert[0].vertIndex = 4;
			face[idx].vert[1].vertIndex = 5;
		}
		else {
			face[idx].vert[0].vertIndex = i + 9;
			face[idx].vert[1].vertIndex = i + nSegment + 8;
		}
		
		if (i == nSegment - 1) {
			face[idx].vert[2].vertIndex = 8;
			face[idx].vert[3].vertIndex = 9;
		}
		else {
			face[idx].vert[2].vertIndex = i + 9 + nSegment;
			face[idx].vert[3].vertIndex = i + 10;
		}
		idx++;
	}

	for (i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 6;
		if (i == 0)
			face[idx].vert[1].vertIndex = 5;
		else
			face[idx].vert[1].vertIndex = i + 8 + nSegment;
		if (i == nSegment - 1)
			face[idx].vert[2].vertIndex = 8;
		else
			face[idx].vert[2].vertIndex = i + 9 + nSegment;
		idx++;
	}

}

void Mesh::CreateCanDao(float fSizeY, int nSegment, float fRadius1)
{
	int		i;
	int		idx, idx2;
	float	fAngle = PI / nSegment;
	float	x, y, z;


	numVerts = 20 + (nSegment - 1) * 4;
	pt = new Point3[numVerts];
	pt[0].set(-fRadius1, fSizeY, 0);
	pt[1].set(-fRadius1, 0, 0);
	pt[2].set(-fRadius1, fSizeY, -fRadius1);
	pt[3].set(-fRadius1, 0, -fRadius1);
	pt[4].set(-fRadius1, 0, fRadius1);
	pt[5].set(-fRadius1, fSizeY, fRadius1);
	pt[6].set(-4*fRadius1, fSizeY, -fRadius1*3/4);
	pt[7].set(-4 * fRadius1, 0, -fRadius1 * 3 / 4);
	pt[8].set(-4 * fRadius1, 0, fRadius1 * 3 / 4);
	pt[9].set(-4 * fRadius1, fSizeY, fRadius1 * 3 / 4);
	pt[10].set(-4 * fRadius1, fSizeY, -fRadius1 * 1.8);
	pt[11].set(-4 * fRadius1, 0, -fRadius1 * 1.8);
	pt[12].set(-4 * fRadius1, 0, fRadius1 * 1.8);
	pt[13].set(-4 * fRadius1, fSizeY, fRadius1 * 1.8);
	pt[14].set(-25 * fRadius1, fSizeY, -fRadius1 * 1.5);
	pt[15].set(-25 * fRadius1, 0, -fRadius1 * 1.5);
	pt[16].set(-25 * fRadius1, 0, fRadius1 * 1.5);
	pt[17].set(-25 * fRadius1, fSizeY, fRadius1 * 1.5);
	pt[18].set(-25 * fRadius1, fSizeY, 0);
	pt[19].set(-25 * fRadius1, 0, 0);

	for (i = 1; i<nSegment; i++)
	{
		//near cylinder
		x = -fRadius1 + fRadius1 * sin(fAngle*i);
		z = fRadius1* cos(fAngle*i);
		y = fSizeY;
		pt[i + 19].set(x, y, z);

		y = 0;
		pt[i + 18 + nSegment].set(x, y, z);

		//far cylinder
		x = -25 * fRadius1 - fRadius1 * 1.5 * sin(fAngle*i);
		z = fRadius1 * 1.5 * cos(fAngle*i);
		y = fSizeY;
		pt[i + 19 + (nSegment-1) * 2].set(x, y, z);

		y = 0;
		pt[i + 18 + nSegment + (nSegment - 1) * 2].set(x, y, z);
	}

	numFaces = nSegment * 6 + 10;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 13;
	face[0].vert[1].vertIndex = 12;
	face[0].vert[2].vertIndex = 16;
	face[0].vert[3].vertIndex = 17;
	for (i = 0; i<face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 10;
	face[1].vert[1].vertIndex = 11;
	face[1].vert[2].vertIndex = 15;
	face[1].vert[3].vertIndex = 14;
	for (i = 0; i<face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 10;
	face[2].vert[1].vertIndex = 13;
	face[2].vert[2].vertIndex = 17;
	face[2].vert[3].vertIndex = 14;
	for (i = 0; i<face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 11;
	face[3].vert[1].vertIndex = 12;
	face[3].vert[2].vertIndex = 16;
	face[3].vert[3].vertIndex = 15;
	for (i = 0; i<face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near left
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 9;
	face[4].vert[1].vertIndex = 8;
	face[4].vert[2].vertIndex = 12;
	face[4].vert[3].vertIndex = 13;
	for (i = 0; i<face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//near right
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 10;
	face[5].vert[1].vertIndex = 11;
	face[5].vert[2].vertIndex = 7;
	face[5].vert[3].vertIndex = 6;
	for (i = 0; i<face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

	//small Left face
	face[6].nVerts = 4;
	face[6].vert = new VertexID[face[6].nVerts];
	face[6].vert[0].vertIndex = 9;
	face[6].vert[1].vertIndex = 8;
	face[6].vert[2].vertIndex = 4;
	face[6].vert[3].vertIndex = 5;
	for (i = 0; i<face[6].nVerts; i++)
		face[6].vert[i].colorIndex = 6;

	//small Right face
	face[7].nVerts = 4;
	face[7].vert = new VertexID[face[7].nVerts];
	face[7].vert[0].vertIndex = 6;
	face[7].vert[1].vertIndex = 7;
	face[7].vert[2].vertIndex = 3;
	face[7].vert[3].vertIndex = 2;
	for (i = 0; i<face[7].nVerts; i++)
		face[7].vert[i].colorIndex = 7;

	//small top face
	face[8].nVerts = 4;
	face[8].vert = new VertexID[face[8].nVerts];
	face[8].vert[0].vertIndex = 2;
	face[8].vert[1].vertIndex = 5;
	face[8].vert[2].vertIndex = 9;
	face[8].vert[3].vertIndex = 6;
	for (i = 0; i<face[8].nVerts; i++)
		face[8].vert[i].colorIndex = 8;

	//small bottom face
	face[9].nVerts = 4;
	face[9].vert = new VertexID[face[9].nVerts];
	face[9].vert[0].vertIndex = 3;
	face[9].vert[1].vertIndex = 4;
	face[9].vert[2].vertIndex = 8;
	face[9].vert[3].vertIndex = 7;
	for (i = 0; i<face[9].nVerts; i++)
		face[9].vert[i].colorIndex = 9;

	//cylinder
	idx = 10;
	idx2 = 10 + 3 * nSegment;

	for (i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;

		face[idx2].nVerts = 3;
		face[idx2].vert = new VertexID[face[idx2].nVerts];
		face[idx2].vert[0].vertIndex = 18;

		if (i == 0) {
			face[idx].vert[1].vertIndex = 5;
			face[idx2].vert[1].vertIndex = 17;
		}
		else {
			face[idx].vert[1].vertIndex = i + 19;
			face[idx2].vert[1].vertIndex = i + 19 + (nSegment - 1) * 2;
		}
		if (i == nSegment - 1) {
			face[idx].vert[2].vertIndex = 2;
			face[idx2].vert[2].vertIndex = 14;
		}
		else {
			face[idx].vert[2].vertIndex = i + 20;
			face[idx2].vert[2].vertIndex = i + 20 + (nSegment - 1) * 2;
		}
		idx++;
		idx2++;
	}

	for (i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx2].nVerts = 4;
		face[idx2].vert = new VertexID[face[idx2].nVerts];


		if (i == 0) {
			face[idx].vert[0].vertIndex = 5;
			face[idx].vert[1].vertIndex = 4;

			face[idx2].vert[0].vertIndex = 17;
			face[idx2].vert[1].vertIndex = 16;
		}
		else {
			face[idx].vert[0].vertIndex = i + 19;
			face[idx].vert[1].vertIndex = i + nSegment + 18;

			face[idx2].vert[0].vertIndex = i + 19 + (nSegment - 1) * 2;
			face[idx2].vert[1].vertIndex = i + 18 + nSegment + (nSegment - 1) * 2;
		}

		if (i == nSegment - 1) {
			face[idx].vert[2].vertIndex = 3;
			face[idx].vert[3].vertIndex = 2;

			face[idx2].vert[2].vertIndex = 15;
			face[idx2].vert[3].vertIndex = 14;
		}
		else {
			face[idx].vert[2].vertIndex = i + 19 + nSegment;
			face[idx].vert[3].vertIndex = i + 20;

			face[idx2].vert[2].vertIndex = i + 19 + nSegment + (nSegment - 1) * 2;
			face[idx2].vert[3].vertIndex = i + 20 + (nSegment - 1) * 2;
		}
		idx++;
		idx2++;
	}

	for (i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 1;

		face[idx2].nVerts = 3;
		face[idx2].vert = new VertexID[face[idx2].nVerts];
		face[idx2].vert[0].vertIndex = 19;

		if (i == 0) {
			face[idx].vert[1].vertIndex = 4;

			face[idx2].vert[1].vertIndex = 16;

		}
		else {
			face[idx].vert[1].vertIndex = i + 18 + nSegment;

			face[idx2].vert[1].vertIndex = i + 18 + nSegment + (nSegment - 1) * 2;

		}
		if (i == nSegment - 1) {
			face[idx].vert[2].vertIndex = 3;

			face[idx2].vert[2].vertIndex = 15;
		}
		else {
			face[idx].vert[2].vertIndex = i + 19 + nSegment;

			face[idx2].vert[2].vertIndex = i + 19 + nSegment + (nSegment - 1) * 2;
		}
		idx++;
		idx2++;
	}

}

void Mesh::CreateGiaDo1(float fSizeX, float fSizeY, int nSegment)
{
	int		i;
	int		idx;
	float	fAngle = 2 * PI / nSegment / 3;
	float	x, y, z;
	float	fRadius = fSizeX * 1 / sqrt(3);


	numVerts = 14 + (nSegment - 1) * 2;
	pt = new Point3[numVerts];
	pt[0].set(-4 * fSizeX, fSizeY, 0);
	pt[1].set(-4 * fSizeX, 0, 0);
	pt[2].set(-4 * fSizeX, 0, fSizeX);
	pt[3].set(-4 * fSizeX, fSizeY, fSizeX);
	pt[4].set(-5 * fSizeX / 4, fSizeY, 0);
	pt[5].set(-5 * fSizeX / 4, 0, 0);
	pt[6].set(fSizeX / 2, 0, fSizeX);
	pt[7].set(fSizeX / 2, fSizeY, fSizeX);
	pt[8].set(-fSizeX / 2, fSizeY, -(6 - sqrt(3)) * fSizeX / 6);
	pt[9].set(-fSizeX / 2, 0, -(6 - sqrt(3)) * fSizeX / 6);
	pt[10].set(0, fSizeY, -fSizeX);
	pt[11].set(0, 0, -fSizeX);
	pt[12].set(-fSizeX, fSizeY, -fSizeX);
	pt[13].set(-fSizeX, 0, -fSizeX);
	

	for (i = 1; i<nSegment; i++)
	{
		//near cylinder
		x = -fSizeX / 2 + fRadius * cos(fAngle*i + PI / 6);
		z = -(6 - sqrt(3)) / 6 * fSizeX - fRadius* sin(fAngle*i + PI / 6);
		y = fSizeY;
		pt[i + 13].set(x, y, z);

		y = 0;
		pt[i + 12 + nSegment].set(x, y, z);

	}

	numFaces = nSegment * 3 + 13;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 3;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 7;
	for (i = 0; i<face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 1;
	face[1].vert[2].vertIndex = 5;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i<face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 7;
	face[2].vert[3].vertIndex = 4;
	for (i = 0; i<face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 2;
	face[3].vert[2].vertIndex = 6;
	face[3].vert[3].vertIndex = 5;
	for (i = 0; i<face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 7;
	face[4].vert[1].vertIndex = 6;
	face[4].vert[2].vertIndex = 11;
	face[4].vert[3].vertIndex = 10;
	for (i = 0; i<face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 0;
	face[5].vert[1].vertIndex = 1;
	face[5].vert[2].vertIndex = 2;
	face[5].vert[3].vertIndex = 3;
	for (i = 0; i<face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

	//behind face
	face[6].nVerts = 4;
	face[6].vert = new VertexID[face[6].nVerts];
	face[6].vert[0].vertIndex = 13;
	face[6].vert[1].vertIndex = 12;
	face[6].vert[2].vertIndex = 4;
	face[6].vert[3].vertIndex = 5;
	for (i = 0; i<face[6].nVerts; i++)
		face[6].vert[i].colorIndex = 6;

	//top near face
	face[7].nVerts = 3;
	face[7].vert = new VertexID[face[7].nVerts];
	face[7].vert[0].vertIndex = 8;
	face[7].vert[1].vertIndex = 7;
	face[7].vert[2].vertIndex = 10;
	for (i = 0; i<face[7].nVerts; i++)
		face[7].vert[i].colorIndex = 7;

	//top mid face
	face[8].nVerts = 3;
	face[8].vert = new VertexID[face[8].nVerts];
	face[8].vert[0].vertIndex = 7;
	face[8].vert[1].vertIndex = 8;
	face[8].vert[2].vertIndex = 4;
	for (i = 0; i<face[8].nVerts; i++)
		face[8].vert[i].colorIndex = 8;

	//top far face
	face[9].nVerts = 3;
	face[9].vert = new VertexID[face[9].nVerts];
	face[9].vert[0].vertIndex = 12;
	face[9].vert[1].vertIndex = 4;
	face[9].vert[2].vertIndex = 8;
	for (i = 0; i<face[9].nVerts; i++)
		face[9].vert[i].colorIndex = 9;

	//bottom near face
	face[10].nVerts = 3;
	face[10].vert = new VertexID[face[7].nVerts];
	face[10].vert[0].vertIndex = 6;
	face[10].vert[1].vertIndex = 9;
	face[10].vert[2].vertIndex = 11;
	for (i = 0; i<face[10].nVerts; i++)
		face[10].vert[i].colorIndex = 10;

	//top mid face
	face[11].nVerts = 3;
	face[11].vert = new VertexID[face[8].nVerts];
	face[11].vert[0].vertIndex = 6;
	face[11].vert[1].vertIndex = 9;
	face[11].vert[2].vertIndex = 5;
	for (i = 0; i<face[11].nVerts; i++)
		face[11].vert[i].colorIndex = 11;

	//bottom far face
	face[12].nVerts = 3;
	face[12].vert = new VertexID[face[9].nVerts];
	face[12].vert[0].vertIndex = 5;
	face[12].vert[1].vertIndex = 9;
	face[12].vert[2].vertIndex = 13;
	for (i = 0; i<face[12].nVerts; i++)
		face[12].vert[i].colorIndex = 12;

	//cylinder
	idx = 13;

	for (i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 8;
		if (i == 0)
			face[idx].vert[1].vertIndex = 10;
		else
			face[idx].vert[1].vertIndex = i + 13;
		if (i == nSegment - 1)
			face[idx].vert[2].vertIndex = 12;
		else
			face[idx].vert[2].vertIndex = i + 14;
		idx++;
	}

	for (i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		if (i == 0) {
			face[idx].vert[0].vertIndex = 10;
			face[idx].vert[1].vertIndex = 11;
		}
		else {
			face[idx].vert[0].vertIndex = i + 13;
			face[idx].vert[1].vertIndex = i + nSegment + 12;
		}

		if (i == nSegment - 1) {
			face[idx].vert[2].vertIndex = 13;
			face[idx].vert[3].vertIndex = 12;
		}
		else {
			face[idx].vert[2].vertIndex = i + 13 + nSegment;
			face[idx].vert[3].vertIndex = i + 14;
		}
		idx++;
	}

	for (i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 9;
		if (i == 0)
			face[idx].vert[1].vertIndex = 11;
		else
			face[idx].vert[1].vertIndex = i + 12 + nSegment;
		if (i == nSegment - 1)
			face[idx].vert[2].vertIndex = 13;
		else
			face[idx].vert[2].vertIndex = i + 13 + nSegment;
		idx++;
	}

}

void Mesh::CreateGiaDo2(float fSizeX, float fSizeY, int nSegment)
{
	int		i;
	int		idx;
	float	fAngle = PI / nSegment;
	float	ang = 14.03624347 * PI / 180;
	float	x, y, z;
	float	fRadius = fSizeX * sqrt(10) / 8;


	numVerts = 12 + (nSegment - 1) * 2;
	pt = new Point3[numVerts];
	pt[0].set(0, fSizeY, 0);
	pt[1].set(0, 0, 0);
	pt[2].set(0, 0, 2 * fSizeX);
	pt[3].set(0, fSizeY, 2 * fSizeX);
	pt[4].set(-3.5 * fSizeX, fSizeY, 1.5 * fSizeX);
	pt[5].set(-3.5 * fSizeX, 0, 1.5 * fSizeX);
	pt[6].set(-2.5 * fSizeX, 0, 2 * fSizeX);
	pt[7].set(-2.5 * fSizeX, fSizeY, 2 * fSizeX);
	pt[8].set(-3.25 * fSizeX, fSizeY, 2.25 * fSizeX);
	pt[9].set(-3.25 * fSizeX, 0, 2.25 * fSizeX);
	pt[10].set(-27 * fSizeX / 8, fSizeY, 15 * fSizeX / 8);
	pt[11].set(-27 * fSizeX / 8, 0, 15 * fSizeX / 8);
	


	for (i = 1; i<nSegment; i++)
	{
		//near cylinder
		x = -27 * fSizeX / 8 - fRadius * sin(fAngle*i + ang);
		z = 15 * fSizeX / 8 - fRadius* cos(fAngle*i + ang);
		y = fSizeY;
		pt[i + 11].set(x, y, z);

		y = 0;
		pt[i + 10 + nSegment].set(x, y, z);

	}

	numFaces = nSegment * 3 + 10;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 3;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 7;
	for (i = 0; i<face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 1;
	face[1].vert[2].vertIndex = 5;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i<face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 7;
	face[2].vert[3].vertIndex = 4;
	for (i = 0; i<face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 2;
	face[3].vert[2].vertIndex = 6;
	face[3].vert[3].vertIndex = 5;
	for (i = 0; i<face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 0;
	face[4].vert[1].vertIndex = 1;
	face[4].vert[2].vertIndex = 2;
	face[4].vert[3].vertIndex = 3;
	for (i = 0; i<face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 6;
	face[5].vert[1].vertIndex = 7;
	face[5].vert[2].vertIndex = 8;
	face[5].vert[3].vertIndex = 9;
	for (i = 0; i<face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

	//behind face
	face[6].nVerts = 3;
	face[6].vert = new VertexID[face[6].nVerts];
	face[6].vert[0].vertIndex = 4;
	face[6].vert[1].vertIndex = 7;
	face[6].vert[2].vertIndex = 10;
	for (i = 0; i<face[6].nVerts; i++)
		face[6].vert[i].colorIndex = 6;

	//top near face
	face[7].nVerts = 3;
	face[7].vert = new VertexID[face[7].nVerts];
	face[7].vert[0].vertIndex = 8;
	face[7].vert[1].vertIndex = 7;
	face[7].vert[2].vertIndex = 10;
	for (i = 0; i<face[7].nVerts; i++)
		face[7].vert[i].colorIndex = 7;

	//top mid face
	face[8].nVerts = 3;
	face[8].vert = new VertexID[face[8].nVerts];
	face[8].vert[0].vertIndex = 6;
	face[8].vert[1].vertIndex = 5;
	face[8].vert[2].vertIndex = 11;
	for (i = 0; i<face[8].nVerts; i++)
		face[8].vert[i].colorIndex = 8;

	//top far face
	face[9].nVerts = 3;
	face[9].vert = new VertexID[face[9].nVerts];
	face[9].vert[0].vertIndex = 6;
	face[9].vert[1].vertIndex = 11;
	face[9].vert[2].vertIndex = 9;
	for (i = 0; i<face[9].nVerts; i++)
		face[9].vert[i].colorIndex = 9;

	

	//cylinder
	idx = 10;

	for (i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 10;
		if (i == 0)
			face[idx].vert[1].vertIndex = 4;
		else
			face[idx].vert[1].vertIndex = i + 11;
		if (i == nSegment - 1)
			face[idx].vert[2].vertIndex = 8;
		else
			face[idx].vert[2].vertIndex = i + 12;
		idx++;
	}

	for (i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		if (i == 0) {
			face[idx].vert[0].vertIndex = 4;
			face[idx].vert[1].vertIndex = 5;
		}
		else {
			face[idx].vert[0].vertIndex = i + 11;
			face[idx].vert[1].vertIndex = i + nSegment + 10;
		}

		if (i == nSegment - 1) {
			face[idx].vert[2].vertIndex = 9;
			face[idx].vert[3].vertIndex = 8;
		}
		else {
			face[idx].vert[2].vertIndex = i + 11 + nSegment;
			face[idx].vert[3].vertIndex = i + 12;
		}
		idx++;
	}

	for (i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 11;
		if (i == 0)
			face[idx].vert[1].vertIndex = 5;
		else
			face[idx].vert[1].vertIndex = i + 10 + nSegment;
		if (i == nSegment - 1)
			face[idx].vert[2].vertIndex = 9;
		else
			face[idx].vert[2].vertIndex = i + 11 + nSegment;
		idx++;
	}

}

void Mesh::CreateTayNoi(float fRadius, float fSizeY, int nSegment)
{
	int		i;
	int		idx, idx2;
	float	fAngle = PI / nSegment;
	float	x, y, z;


	numVerts = 12 + (nSegment - 1) * 4;
	pt = new Point3[numVerts];
	pt[0].set(3 * fRadius / 2, fSizeY, -fRadius);
	pt[1].set(3 * fRadius / 2, 0, -fRadius);
	pt[2].set(3 * fRadius / 2, 0, fRadius);
	pt[3].set(3 * fRadius / 2, fSizeY, fRadius);
	pt[4].set(-3 * fRadius / 2, fSizeY, -fRadius);
	pt[5].set(-3 * fRadius / 2, 0, -fRadius);
	pt[6].set(-3 * fRadius / 2, 0, fRadius);
	pt[7].set(-3 * fRadius / 2, fSizeY, fRadius);
	pt[8].set(-3 * fRadius / 2, fSizeY, 0);
	pt[9].set(-3 * fRadius / 2, 0, 0);
	pt[10].set(3 * fRadius / 2, fSizeY, 0);
	pt[11].set(3 * fRadius / 2, 0, 0);



	for (i = 1; i < nSegment; i++)
	{
		//near cylinder
		x = 3 * fRadius / 2 + fRadius * sin(fAngle*i);
		z = fRadius* cos(fAngle*i);
		y = fSizeY;
		pt[i + 11].set(x, y, z);

		y = 0;
		pt[i + 10 + nSegment].set(x, y, z);

		//far cylinder
		x = -x;
		y = fSizeY;
		pt[i + 11 + (nSegment - 1) * 2].set(x, y, z);

		y = 0;
		pt[i + 10 + nSegment + (nSegment - 1) * 2].set(x, y, z);

	}

	numFaces = nSegment * 6 + 4;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 3;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 7;
	for (i = 0; i < face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 1;
	face[1].vert[2].vertIndex = 5;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i < face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 7;
	face[2].vert[3].vertIndex = 4;
	for (i = 0; i < face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 2;
	face[3].vert[2].vertIndex = 6;
	face[3].vert[3].vertIndex = 5;
	for (i = 0; i < face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;



	//cylinder
	idx = 4;
	idx2 = 4 + nSegment * 3;

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 10;

		face[idx2].nVerts = 3;
		face[idx2].vert = new VertexID[face[idx2].nVerts];
		face[idx2].vert[0].vertIndex = 8;

		if (i == 0) {
			face[idx].vert[1].vertIndex = 3;
			face[idx2].vert[1].vertIndex = 7;
		}
		else {
			face[idx].vert[1].vertIndex = i + 11;
			face[idx2].vert[1].vertIndex = i + 11 + (nSegment - 1) * 2;
		}
		if (i == nSegment - 1) {
			face[idx].vert[2].vertIndex = 0;
			face[idx2].vert[2].vertIndex = 4;
		}
		else {
			face[idx].vert[2].vertIndex = i + 12;
			face[idx2].vert[2].vertIndex = i + 12 + (nSegment - 1) * 2;
		}
		idx++;
		idx2++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx2].nVerts = 4;
		face[idx2].vert = new VertexID[face[idx2].nVerts];

		if (i == 0) {
			face[idx].vert[0].vertIndex = 3;
			face[idx].vert[1].vertIndex = 2;

			face[idx2].vert[0].vertIndex = 7;
			face[idx2].vert[1].vertIndex = 6;
		}
		else {
			face[idx].vert[0].vertIndex = i + 11;
			face[idx].vert[1].vertIndex = i + nSegment + 10;

			face[idx2].vert[0].vertIndex = i + 11 + (nSegment - 1) * 2;
			face[idx2].vert[1].vertIndex = i + 10 + nSegment + (nSegment - 1) * 2;
		}

		if (i == nSegment - 1) {
			face[idx].vert[2].vertIndex = 1;
			face[idx].vert[3].vertIndex = 0;

			face[idx2].vert[2].vertIndex = 5;
			face[idx2].vert[3].vertIndex = 4;
		}
		else {
			face[idx].vert[2].vertIndex = i + 11 + nSegment;
			face[idx].vert[3].vertIndex = i + 12;

			face[idx2].vert[2].vertIndex = i + 11 + nSegment + (nSegment - 1) * 2;
			face[idx2].vert[3].vertIndex = i + 12 + (nSegment - 1) * 2;
		}
		idx++;
		idx2++;
	}

	for (i = 0; i < nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 11;

		face[idx2].nVerts = 3;
		face[idx2].vert = new VertexID[face[idx2].nVerts];
		face[idx2].vert[0].vertIndex = 9;

		if (i == 0) {
			face[idx].vert[1].vertIndex = 2;

			face[idx2].vert[1].vertIndex = 6;
		}
		else {
			face[idx].vert[1].vertIndex = i + 10 + nSegment;

			face[idx2].vert[1].vertIndex = i + 10 + nSegment + (nSegment - 1) * 2;
		}
		if (i == nSegment - 1) {
			face[idx].vert[2].vertIndex = 1;

			face[idx2].vert[2].vertIndex = 5;
		}
		else {
			face[idx].vert[2].vertIndex = i + 11 + nSegment;

			face[idx2].vert[2].vertIndex = i + 11 + nSegment + (nSegment - 1) * 2;
		}
		idx++;
		idx2++;
	}

}
#pragma endregion

// Kich thuoc
#pragma region
int nSegment = 20;
float base1RotateStep = 5;

// De Dao
float deX = 5;
float deY = 0.3;
float deZ = 1.5;

// Chot noi
float cHeight = 1.1;
float cRadius = 0.15;

// Luoi Dao
float lX = 4;
float lY = 0.5;
float lZ = 0.8;
float lRadius = 0.5;

// Can Dao
float canY = 0.5;
float canRadius = 0.2;

// Gia do 1
float gia1X = 1;
float gia1Y = 0.5;

// Gia do 2
float gia2X = 0.7;
float gia2Y = 0.5;

// Tay noi
float tayRadius = 0.3;
float tayY = 0.5;

bool isWireFrameMode = false;	//che dong khung hay to mau
bool turnOnLight2 = true;	// phim d D
bool isModeViewing = false;		// v V chuyen doi mode viewing

								// Tham so cho camera
float camera_angle;
float camera_height;
float camera_dis;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;
#pragma endregion

//callback Event(keyboard)
#pragma region
void myKeyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case '1':
		DeDao.rotateY += base1RotateStep;
		if (DeDao.rotateY > 360)
			DeDao.rotateY -= 360;
		break;
	case '2':
		DeDao.rotateY -= base1RotateStep;
		if (DeDao.rotateY < 0)
			DeDao.rotateY += 360;
		break;
	case 'w':
	case 'W':
		isWireFrameMode = !isWireFrameMode;
		break;
	case 'd':
	case 'D':
		turnOnLight2 = !turnOnLight2;
		break;
	case 'v':
	case 'V':
		isModeViewing = !isModeViewing;
		break;
	case '+':
		camera_dis += 0.5;
		break;
	case '-':
		camera_dis -= 0.5;
		break;
	}
	glutPostRedisplay();
}

void mySpecialKeyboard(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		camera_height += 0.5;
		break;
	case GLUT_KEY_DOWN:
		camera_height -= 0.5;
		break;
	case GLUT_KEY_RIGHT:
		camera_angle += 5;
		break;
	case GLUT_KEY_LEFT:
		camera_angle -= 5;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
#pragma endregion

//init
void init() {
	camera_angle = -30;  // Góc quay camera xung quanh trục Oy
	camera_height = 5.5; // Chiều cao camera so với mặt phẳng xOz
	camera_dis = 6.5;	// Khoảng cách đến trục Oy

	lookAt_X = 0;
	lookAt_Y = 1;
	lookAt_Z = 0;

	float fHalfSize = 4;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);


	const float ar = (float)screenWidth / (float)screenHeight;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 1.5, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	//glEnable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	GLfloat light_ambient0[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
}

void initObject()
{
	// De Dao
	DeDao.CreateCuboid(deX, deY, deZ);
	DeDao.SetColor(2);
	DeDao.CalculateFacesNorm();

	// Chot noi
	chot.CreateCylinder(nSegment, cHeight, cRadius);
	chot.SetColor(3);
	chot.CalculateFacesNorm();

	// Luoi Dao
	LuoiDao.CreateLuoiDao(lX, lY, lZ, nSegment, lRadius);
	LuoiDao.SetColor(4);
	LuoiDao.CalculateFacesNorm();

	// Can Dao
	CanDao.CreateCanDao(canY, nSegment, canRadius);
	CanDao.SetColor(5);
	CanDao.CalculateFacesNorm();

	// Gia Do 1
	GiaDo1.CreateGiaDo1(gia1X, gia1Y, nSegment);
	GiaDo1.SetColor(6);
	GiaDo1.CalculateFacesNorm();

	// Gia Do 2
	GiaDo2.CreateGiaDo2(gia2X, gia2Y, nSegment);
	GiaDo2.SetColor(7);
	GiaDo2.CalculateFacesNorm();

	// Tay Noi
	TayNoi.CreateTayNoi(tayRadius, tayY, nSegment);
	TayNoi.SetColor(8);
	TayNoi.CalculateFacesNorm();
}

// Ve vat the
#pragma region
void drawDeDao()
{
	glPushMatrix();
	glTranslated(0, -0.3, 0);
	glRotatef(0, 0, 1, 0);

	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	DeDao.setupMaterial(ambient, diffuse, specular, shininess);

	if (isWireFrameMode)
		DeDao.DrawWireframe();
	else
		DeDao.Draw();

	glPopMatrix();
}

void drawChotNoi()
{
	glPushMatrix();
	glTranslated(0, 0.5, 0);
	glRotatef(90, 1, 0, 0);
	glTranslated(0.2, 0.5, -0.3);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 56.0f/255.0f, 45.0f/255.0f, 44.0f/255.0f, 1.0f };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	chot.setupMaterial(ambient, diffuse, specular, shininess);

	if (isWireFrameMode)
		chot.DrawWireframe();
	else
		chot.Draw();
	glPopMatrix();

	// Chot 2
	glPushMatrix();
	glTranslated(0, 0.5, 0);
	glRotatef(90, 1, 0, 0);
	glTranslated(-1.4, 0.5, -0.4);

	chot.setupMaterial(ambient, diffuse, specular, shininess);

	if (isWireFrameMode)
		chot.DrawWireframe();
	else
		chot.Draw();
	glPopMatrix();

	// Chot 3
	glPushMatrix();
	glTranslated(0, 0.5, 0);
	glRotatef(90, 1, 0, 0);
	glTranslated(0.2, 0.5, -1.3);

	chot.setupMaterial(ambient, diffuse, specular, shininess);

	if (isWireFrameMode)
		chot.DrawWireframe();
	else
		chot.Draw();
	glPopMatrix();

	// Chot 4
	glPushMatrix();
	glTranslated(0, 0.5, 0);
	glRotatef(90, 1, 0, 0);
	glTranslated(1.2, 0.5, -1.9);

	chot.setupMaterial(ambient, diffuse, specular, shininess);

	if (isWireFrameMode)
		chot.DrawWireframe();
	else
		chot.Draw();
	glPopMatrix();
}

void drawLuoiDao()
{
	glPushMatrix();

	glTranslated(0, 0, 0);
	glRotatef(90, 1, 0, 0);
	glTranslated(0.5, 0, -0.55);

	GLfloat diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	LuoiDao.setupMaterial(ambient, diffuse, specular, shininess);

	if (isWireFrameMode)
		LuoiDao.DrawWireframe();
	else
		LuoiDao.Draw();

	glPopMatrix();
}

void drawCanDao()
{
	glPushMatrix();

	glTranslated(0, 4.2, 0);
	glRotatef(90, 1, 0, 0);
	glTranslated(4.5, 0, -0.1);
	glRotatef(30, 0, 1, 0);

	GLfloat diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	CanDao.setupMaterial(ambient, diffuse, specular, shininess);

	if (isWireFrameMode)
		CanDao.DrawWireframe();
	else
		CanDao.Draw();

	glPopMatrix();
}

void drawGiaDo1() {
	glPushMatrix();

	glTranslated(0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glTranslated(-1, 0.5, 0.5);
	glScalef(0.75, 1, 0.5);

	GLfloat diffuse[] = { 1.0f, 228.0f / 255.0f, 181.0f / 255.0f, 1.0f };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	GiaDo1.setupMaterial(ambient, diffuse, specular, shininess);

	if (isWireFrameMode)
		GiaDo1.DrawWireframe();
	else
		GiaDo1.Draw();

	glPopMatrix();
}

void drawGiaDo2() {
	glPushMatrix();

	glTranslated(0, 0, 0);
	glRotatef(90, 1, 0, 0);
	glTranslated(2.5, 0.5, 0);
	glRotatef(-90, 0, 1, 0);

	GLfloat diffuse[] = { 1.0f, 228.0f/255.0f, 181.0f/255.0f, 1.0f };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	GiaDo2.setupMaterial(ambient, diffuse, specular, shininess);

	if (isWireFrameMode)
		GiaDo2.DrawWireframe();
	else
		GiaDo2.Draw();

	glPopMatrix();
}

void drawTayNoi() {
	glPushMatrix();

	glTranslated(0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glTranslated(0.2, 0.5, -0.3);
	glRotatef(90, 0, 1, 0);

	GLfloat diffuse[] = { 1.0, 0.0, 1.0, 1.0 };
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 40.0;
	TayNoi.setupMaterial(ambient, diffuse, specular, shininess);

	if (isWireFrameMode)
		TayNoi.DrawWireframe();
	else
		TayNoi.Draw();

	glPopMatrix();
}

Point3 lineInter(Point3 p1, Point3 p2, Point3 p3, Point3 p4) {
	Point3 t;

	float A1, A2, B1, B2;
	A1 = (p2.z - p1.z) / (p2.x - p1.x);
	B1 = p1.z - A1*p1.x;

	A2 = (p4.z - p3.z) / (p4.x - p3.x);
	B2 = p3.z - A2*p3.x;

	t.x = (B2 - B1) / (A1 - A2);
	t.z = A1*t.x + B1;
	t.y = p1.y;
	return t;
}

void drawGach(float x, float y, float z) {
	Point3 A,B,C,D,E,F,G,H,I,K,L,M,N,P,Q,R,S;
	A.set(x, y, z);
	B.set(x - 1, y, z + 3);
	C.set(x + 0.5, y, z + 1.5);
	D.set(x - 1, y, z + 1);
	E.set(x - 1, y, z + 2);
	F.set(x , y, z + 3);
	G.set(x + 1, y, z + 3);
	H.set(x + 2, y, z + 3);
	I.set(x + 2, y, z + 2);
	K.set(x + 2, y, z + 1);
	L.set(x + 2, y, z);
	M.set(x + 1, y, z);
	Q.set(x - 0.25, y, z + 2.25);
	N = lineInter(A, B, C, D);
	P = lineInter(A, B, Q, E);
	R = lineInter(B, I, Q, F);
	S = lineInter(B, I, C, G);


	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(M.x, M.y, M.z);
	glVertex3f(C.x, C.y, C.z);
	glVertex3f(N.x, N.y, N.z);
	glVertex3f(A.x, A.y, A.z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(K.x, K.y, K.z);
	glVertex3f(C.x, C.y, C.z);
	glVertex3f(S.x, S.y, S.z);
	glVertex3f(I.x, I.y, I.z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(G.x, G.y, G.z);
	glVertex3f(S.x, S.y, S.z);
	glVertex3f(R.x, R.y, R.z);
	glVertex3f(F.x, F.y, F.z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(B.x, B.y, B.z);
	glVertex3f(R.x, R.y, R.z);
	glVertex3f(Q.x, Q.y, Q.z);
	glVertex3f(P.x, P.y, P.z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(E.x, E.y, E.z);
	glVertex3f(P.x, P.y, P.z);
	glVertex3f(N.x, N.y, N.z);
	glVertex3f(D.x, D.y, D.z);
	glEnd();

	/*glColor3f(0, 0, 0);
	glBegin(GL_LINE);
	glVertex3f(2, -0.6, 0); glVertex3f(3, -0.6, 3);
	glVertex3f(3, -0.6, 3); glVertex3f(6, -0.6, 4);
	glVertex3f(4, -0.6, 0); glVertex3f(4.5, -0.6, 1.5);
	glVertex3f(4.5, -0.6, 1.5); glVertex3f(6, -0.6, 2);
	glVertex3f(0, -0.6, 4); glVertex3f(3, -0.6, 3);
	glVertex3f(2, -0.6, 6); glVertex3f(3, -0.6, 3);
	glVertex3f(0, -0.6, 2); glVertex3f(6, -0.6, 0);
	glVertex3f(4, -0.6, 6); glVertex3f(6, -0.6, 0);
	glEnd();*/
}

//void setCameraVolume(float l, float r, float b, float t) {
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D((GLdouble)l, (GLdouble)r, (GLdouble)b, (GLdouble)t);
//}

//void setViewport(float l, float r, float b, float t) {
//	glViewport(l, b, r - l, t - b);
//}

void drawBlock() {
	glPushMatrix();
	// tâm: C.set(x + 0.5, y, z + 1.5);
	drawGach(1, -0.6, -3);
	glRotatef(90, 0, 1, 0);
	drawGach(1, -0.6, -3);
	glRotatef(90, 0, 1, 0);
	drawGach(1, -0.6, -3);
	glRotatef(90, 0, 1, 0);
	drawGach(1, -0.6, -3);
	glPopMatrix();
}

void drawNen() {
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int x = 30; x > -30; x-=6) {
		for (int z = 20; z > -20; z -= 6) {
			glPushMatrix();
			glTranslated(x, 0, z);
			drawBlock();
			// tâm: C.set(x + 0.5, y, z + 1.5);
			/*glTranslated(-(x + 0.5), 0, -(z + 1.5));
			glRotatef(90, 0, 1, 0);
			glTranslated((x + 0.5), 0, (z + 1.5));
			drawGach(x,-0.6,z);*/
			glPopMatrix();
		}
		/*int w = size / 2 * (loop % 2);
		int h = size / 2 * (loop / 2);

		

		setViewport(size / 4 + w, size / 2 + w, size / 4 + h, size / 2 + h);
		setCameraVolume(0, 6, 6, 0);
		drawGach();

		setViewport(size / 4 + w, size / 2 + w, 0+h, size / 4 + h);
		setCameraVolume(6, 0, 6, 0);
		drawGach();

		glPolygonMode(GL_FRONT, GL_FILL);
		setViewport(0 + w, size / 4 + w, 0 + h, size / 4 + h);
		setCameraVolume(0, 6, 6, 0);
		drawGach();*/
	}
	glEnable(GL_LIGHTING);
}
#pragma endregion

void drawAll()
{
	drawDeDao();
	drawChotNoi();
	drawLuoiDao();
	drawCanDao();
	drawGiaDo1();
	drawGiaDo2();
	drawTayNoi();

}

//void drawAxis()
//{
//	glColor3f(0, 0, 1);
//	glBegin(GL_LINES);
//	glVertex3f(0, 0, 0);
//	glVertex3f(4, 0, 0);
//
//	glVertex3f(0, 0, 0);
//	glVertex3f(0, 4, 0);
//
//	glVertex3f(0, 0, 0);
//	glVertex3f(0, 0, 4);
//	glEnd();
//}

void mydisplay() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat light_position0[] = { 10.0, 10.0, 10.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	// bat tat nguon sang thu 2
	if (turnOnLight2 == true)
	{
		glEnable(GL_LIGHT1);
		GLfloat diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat specular1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat ambient1[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat position1[] = { -10.0, 10.0, -10.0, 0.0 };

		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
		glLightfv(GL_LIGHT1, GL_POSITION, position1);
	}
	else
		glDisable(GL_LIGHT1);

	if (isModeViewing) {
		glEnable(GL_LIGHT2);
		GLfloat diffuse2[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat light_position2[] = { 0.0, 0.0, -1.0, 0.0 };
		glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
		glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	}
	else {
		glDisable(GL_LIGHT2);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera_X = camera_dis * sinf(camera_angle * PI / 180);
	camera_Y = camera_height;
	camera_Z = camera_dis * cosf(camera_angle * PI / 180);


	// che do nhin
	if (isModeViewing) {
		gluLookAt(0, 0, 15, 2, 2, -4, 0, 1, 0);
	}
	else if (camera_dis == 0)
	{
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, sinf(camera_angle * PI / 180), 0, cosf(camera_angle * PI / 180));
	}
	else
	{
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, 0, 1, 0);
	}

	glViewport(0, 0, screenWidth, screenHeight);

	//// Clear depth
	glClearDepth(1.0f);
	//// Draw
	drawAll();
	if (!isModeViewing) {
		drawNen();
	}
	//cout << isWireFrameMode << endl;
	//glTranslated(0, 0.3, 0);
	glPushMatrix();
	glScalef(1, -1, 1);
	glTranslatef(0, 1.2, 0);
	drawAll();
	glPopMatrix();
	//drawNen();
	/* Don't update color or depth. */
	glDisable(GL_DEPTH_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_DEPTH_TEST);

	//// Blend the floor onto the screen
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//drawBlock();
	//drawGach(9, -0.6, 9);
	glDisable(GL_BLEND);

	glFlush();
	glutSwapBuffers();
}

void consoleLog() {
	cout << "1, 2: Xoay de" << endl;
	cout << "W, w: Chuyen doi qua lai giua che do khung day va to mau" << endl;
	cout << "V, v: Chuyen doi qua lai giua hai che do nhin khac nhau" << endl;
	cout << "A, a: Turn on / off animation" << endl;
	cout << "+   : Tang khoang cach camera" << endl;
	cout << "-   : Giam khoang cach camera" << endl;
	cout << "up arrow  : Tang chieu cao camera" << endl;
	cout << "down arrow: Giam chieu cao camera" << endl;
	cout << "<-        : Quay camera theo chieu kim dong ho" << endl;
	cout << "->        : Quay camera nguoc chieu kim dong ho" << endl;
	cout << "D, d: Bat/tat nguon sang thu 2" << endl;
	cout << "A, a: Bat/tat nguon che do hoat hinh" << endl;
}



int _tmain(int argc, _TCHAR* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("Pham Van Do - 1711035");
	initObject();
	init();
	consoleLog();
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);
	glutDisplayFunc(mydisplay);
	glutMainLoop();
	return 0;
}