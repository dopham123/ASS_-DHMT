#include "stdafx.h"
#include "Mesh.h"
#include <math.h>

#define PI			3.1415926
#define	COLORNUM		14


float	ColorArr[COLORNUM][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0}, 
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0}, 
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}};





void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius)
{
	numVerts=nSegment*2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2*PI/nSegment;
	float	x, y, z;

	pt[0].set(0, fHeight/2, 0);
	for(i = 0; i<nSegment; i++)
	{
		x = fRadius* cos(fAngle*i);
		z = fRadius* sin(fAngle*i);
		y = fHeight/2;
		pt[i+1].set(x, y, z);

		y = -fHeight/2;
		pt[i +1 + nSegment].set(x, y, z);
	}
	pt[numVerts-1].set(0, -fHeight/2, 0);

	numFaces= nSegment*3;
	face = new Face[numFaces];

	idx = 0;
	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if(i < nSegment -1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		
		face[idx].vert[0].vertIndex = i+1;
		if(i <nSegment - 1)
			face[idx].vert[1].vertIndex = i+2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if(i < nSegment -1)
			face[idx].vert[2].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex = 1 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}

}

void Mesh::CreateCube(float	fSizeX, float	fSizeY, float	fSizeZ)
{
	int i;

	numVerts=8;
	pt = new Point3[numVerts];
	pt[0].set(-fSizeX, fSizeY, fSizeZ);
	pt[1].set( fSizeX, fSizeY, fSizeZ);
	pt[2].set( fSizeX, fSizeY, -fSizeZ);
	pt[3].set(-fSizeX, fSizeY, -fSizeZ);
	pt[4].set(-fSizeX, -fSizeY, fSizeZ);
	pt[5].set( fSizeX, -fSizeY, fSizeZ);
	pt[6].set( fSizeX, -fSizeY, -fSizeZ);
	pt[7].set(-fSizeX, -fSizeY, -fSizeZ);


	numFaces= 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	
	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;

}


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

void Mesh::CreatShape1(float	fSizeX, float	fSizeY, float	fSizeZ, int nSegment, float fRadius)
{
	int		i;
	int		idx;
	float	fAngle = PI / nSegment / 2;
	float	x, y, z;


	numVerts = 10 + nSegment*2;
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

void Mesh::CreatShape2(float fSizeY, int nSegment, float fRadius1)
{
	int		i;
	int		idx, idx2;
	float	fAngle = PI / nSegment;
	float	x, y, z;


	numVerts = 20 + nSegment * 4;
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

void Mesh::CreatShape3(float fSizeX, float fSizeY, int nSegment)
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

void Mesh::CreatShape4(float fSizeX, float fSizeY, int nSegment)
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

void Mesh::CreatShape5(float fRadius, float fSizeY, int nSegment)
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

