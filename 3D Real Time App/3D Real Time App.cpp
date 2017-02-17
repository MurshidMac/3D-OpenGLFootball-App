// 3D Realtime App Football Play
#include "stdafx.h"
#include "freeglut.h"
#include <Windows.h>
#include <iostream>
#include <math.h>
#include <string>
#include <cmath>
#define _USE_MATH_DEFINES


using namespace std;
double distanceBall = 4.0;
double yAxis = -0.55;
double xAxis = 0.00;
double balldistance = 0.00;
double hozSliderX = 60;
double vertSliderY = 720 - 60.0;
int values = 10;
double i = 4.00;
int test = 10;
int tries = 10; //stores the number of remaining tries
int hoops = 8; //stores the number of hoops left to hit
static float ballRotation = 0.0;
int intialPoints = 0;

GLfloat targetOne[] = { -0.5,-0.3,-9.8 };	// Targets On the wall	20	
GLfloat targetTwo[] = { -3.2, 0.7, -9.8 };	// X, Y, Z				10
GLfloat targetThree[] = { 0.9, 1.0, -9.8 };	//						20
GLfloat targetFour[] = { -1.2, 1.0, -9.8 };	//						30
GLfloat targetFive[] = { 1.8, 0.0, -9.8 };	//						10
GLfloat targetSix[] = { -3.2, -0.5, -9.8 };	//						30
GLfloat targetSeven[] = { 3.2, 0.0, -9.8 }; //						30
GLfloat targetEight[] = { 2.7, 1.0, -9.8 };	// Targets End			30	

GLfloat boXRotate = 0.0;

GLbyte *textureOne; 
GLbyte *textureTwo; 
GLbyte *textureThree; 


// Lights
GLfloat  light[] = { 10.0f, 10.0f, 10.0f, 1.0f };
GLfloat  lightTwo[] = { 3.0f, 3.0f, 3.0f, 1.0f };

//Positions
GLfloat	 posOne[] = { 0.0f, 1.0f, -1.0f, 1.0f };
GLfloat	 posTwo[] = { 0.0f, 2.0f, 0.0f, 0.0f };

//Textures
GLint cordinateWidth, cordinateHeight, cordinateCo;
GLenum textureFormat;
bool lightVisible = false;
bool lightRotate = false;

// prededfined Funtions

// Import From pragma pack 
#pragma pack(1)
typedef struct
{
	GLbyte	identsize;              
	GLbyte	colorMapType;           
	GLbyte	imageType;              
	unsigned short	colorMapStart;  
	unsigned short	colorMapLength; 
	unsigned char 	colorMapBits;   
	unsigned short	xstart;         
	unsigned short	ystart;         
	unsigned short	width;          
	unsigned short	height;         
	GLbyte	bits;                   
	GLbyte	descriptor;             
} TGAHEADER;
// Importing to Use TGA File Reader
#pragma pack(8)
GLbyte *gltLoadTGA(const char *szFileName, GLint *cordinateWidth, GLint *cordinateHeight, GLint *cordinateCo, GLenum *textureFormat)
{
	FILE *pFile;			
	TGAHEADER tgaHeader;	
	unsigned long lImageSize;	
	short sDepth;			
	GLbyte	*pBits = NULL;  

	*cordinateWidth = 0;
	*cordinateHeight = 0;
	*textureFormat = GL_BGR_EXT;
	*cordinateCo = GL_RGB8;

	fopen_s(&pFile, szFileName, "rb");

	if (pFile == NULL)
		return NULL;

	fread(&tgaHeader, 18, 1, pFile);


	*cordinateWidth = tgaHeader.width;
	*cordinateHeight = tgaHeader.height;
	sDepth = tgaHeader.bits / 8;

	if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
		return NULL;

	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;
	pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
	if (pBits == NULL)
		return NULL;

	if (fread(pBits, lImageSize, 1, pFile) != 1)
	{
		free(pBits);
		return NULL;
	}

	switch (sDepth)
	{
	case 3:     
		*textureFormat = GL_BGR_EXT;
		*cordinateCo = GL_RGB8;
		break;
	case 4:
		*textureFormat = GL_BGRA_EXT;
		*cordinateCo = GL_RGBA8;
		break;
	case 1:
		*textureFormat = GL_LUMINANCE;
		*cordinateCo = GL_LUMINANCE8;
		break;
	};


	fclose(pFile);
	return pBits;
}
// Reshape Funtions of Objects 
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Perspective Projection
	gluPerspective(60.0, 16.0 / 9.0, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
}

void setOrthographicProjection() {
	// switch to projection mode     
	glMatrixMode(GL_PROJECTION);
	// save the previous matrix which contains the     
	//set up for the perspective projection     
	glPushMatrix();
	// reset matrix     
	glLoadIdentity();
	// set a 2D orthographic projection     
	gluOrtho2D(0, 600, 0, 800);
	// invert the y axis, down is positive     
	glScalef(1, -1, 1);
	// mover the origin from the bottom left corner     
	// to the upper left corner     
	glTranslatef(0, -800, 0);
	//set for drawing again     
	glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
// Pure Lighting
void backgroundSettle()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);



	glLightfv(GL_LIGHT0, GL_DIFFUSE, light);
	glLightfv(GL_LIGHT0, GL_POSITION, posOne);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightTwo);
	glLightfv(GL_LIGHT1, GL_POSITION, posTwo);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);

}

//ball Properties
void ball() {

	GLbyte *pBytes5;
	pBytes5 = gltLoadTGA("Textures/FootballCompleteMap.tga", &cordinateWidth, &cordinateHeight, &cordinateCo, &textureFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, cordinateCo, cordinateWidth, cordinateHeight, 0, textureFormat, GL_UNSIGNED_BYTE, pBytes5);
	free(pBytes5);
	glEnable(GL_TEXTURE_2D);

	//Calculating the 3D Vector
	glTranslated(xAxis, yAxis, -distanceBall);
	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricOrientation(quadric, GLU_OUTSIDE);
	//enable the texturing
	gluQuadricTexture(quadric, GL_TRUE);
	// Ball Drawn Using the GluSphere
	gluSphere(quadric, 0.20f, 20, 10);

}

//10 point target
void pointsTen() {

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	textureThree = gltLoadTGA("Textures/targetGreen.tga", &cordinateWidth, &cordinateHeight, &cordinateCo, &textureFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, cordinateCo, cordinateWidth, cordinateHeight, 0, textureFormat, GL_UNSIGNED_BYTE, textureThree);
	free(textureThree);
	
	GLUquadricObj *quadric;
	quadric = gluNewQuadric();

	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricOrientation(quadric, GLU_OUTSIDE);

	//enable the texturing
	gluQuadricTexture(quadric, GL_TRUE);
	gluDisk(quadric, 0.0, 0.6, 32, 32);
	glDisable(GL_BLEND);
}

// 20 point target
void pointsTwenty() {

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	textureTwo = gltLoadTGA("Textures/targetBlue.tga", &cordinateWidth, &cordinateHeight, &cordinateCo, &textureFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, cordinateCo, cordinateWidth, cordinateHeight, 0, textureFormat, GL_UNSIGNED_BYTE, textureTwo);
	free(textureTwo);

	GLUquadricObj *quadric;
	quadric = gluNewQuadric();

	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricOrientation(quadric, GLU_OUTSIDE);

	gluQuadricTexture(quadric, GL_TRUE);
	gluDisk(quadric, 0.0, 0.5, 32, 32);
	glDisable(GL_BLEND);
}

// 30 point target
void pointsThirty() {

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	textureOne = gltLoadTGA("Textures/targetRed.tga", &cordinateWidth, &cordinateHeight, &cordinateCo, &textureFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, cordinateCo, cordinateWidth, cordinateHeight, 0, textureFormat, GL_UNSIGNED_BYTE, textureOne);
	free(textureOne);

	GLUquadricObj *quadric;
	quadric = gluNewQuadric();

	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricOrientation(quadric, GLU_OUTSIDE);

	gluQuadricTexture(quadric, GL_TRUE);
	gluDisk(quadric, 0.0, 0.4, 32, 32);
	glDisable(GL_BLEND);
}

//Horizontal And Vertical Bars
void bars() {
	glEnable(GL_TEXTURE_2D);
	GLbyte *pBytes3;
	pBytes3 = gltLoadTGA("Textures/fillBarHorizontal.tga", &cordinateWidth, &cordinateHeight, &cordinateCo, &textureFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, cordinateCo, cordinateWidth, cordinateHeight, 0, textureFormat, GL_UNSIGNED_BYTE, pBytes3);
	free(pBytes3);
	
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 2.0);
	glVertex2d(30.0, 40.0);
	glTexCoord2f(2.0, 2.0);
	glVertex2d(120.0, 40.0);
	glTexCoord2f(2.0, 0.0);
	glVertex2d(120.0, 80.0);
	glTexCoord2f(0.0, 0.0);
	glVertex2d(30.0, 80.0);
	glEnd();

	GLbyte *pBytes4;
	pBytes4 = gltLoadTGA("Textures/fillBarVerticalR.tga", &cordinateWidth, &cordinateHeight, &cordinateCo, &textureFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, cordinateCo, cordinateWidth, cordinateHeight, 0, textureFormat, GL_UNSIGNED_BYTE, pBytes4);
	free(pBytes4);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 2.0);
	glVertex2d(550, 600);
	glTexCoord2f(0.0, 0.0);
	glVertex2d(550, 800);
	glTexCoord2f(2.0, 0.0);
	glVertex2d(580, 800);
	glTexCoord2f(2.0, 2.0);
	glVertex2d(580, 600);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


void drawOrtho() {
	/*glColor3f(1.0, 1.0, 1.0);

	drawSliderX();
	drawSliderY();

	glColor3f(1.0, 1.0, 0);
	glRectd(hozSliderX, 30.0, hozSliderX + 30.0, 50.0);
	glRectd(Wwidth - 30.0, vertSliderY, Wwidth - 50.0, vertSliderY + 30.0);
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2d(Wwidth - 120.0, 50.0);
	string scoreStr;
	if ((tries == 0) || (hoops = 0)) {
		scoreStr = "Game Over!";
	}
	else {
		scoreStr = "Score: " + to_string(score);
	}
	const unsigned char* scoref = reinterpret_cast
		<const unsigned char*>(scoreStr.c_str());
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, scoref);
	glPopMatrix();*/
}

//reusable function to draw flower-type scenery
void drawFlowers(char* imagePath, int num, float x) {//accepts texture (orange or
													 //yellow flowers), number of flowers
													 //needed, and the x position of the
													 //first flower
	GLfloat y1 = 0;  GLfloat y2 = 0; GLfloat z = 0;
	if (imagePath == "textures/orangeFlowerFinal5.tga") {
		y1 = -13.0;		//set height of the flowers
		y2 = -5.0;
		z = -54.8;		//and z-value of the flowers
	}
	if (imagePath == "textures/yellowFlowerFinal.tga") {
		y1 = -13.2;
		y2 = -7.0;
		z = -54.7;
	}
	glPushMatrix();
	glEnable(GL_BLEND);	//enable blending to make transparent texture
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLbyte *pBytes0;
	pBytes0 = gltLoadTGA(imagePath, &cordinateWidth, &cordinateHeight, &cordinateCo, &textureFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, cordinateCo, cordinateWidth, cordinateHeight, 0, textureFormat, GL_UNSIGNED_BYTE, pBytes0);
	free(pBytes0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_QUADS);

	//set up vertexes and texture coords
	glTexCoord2f(1.0*num, 0.05);
	glVertex3f(x, y1, z);
	glTexCoord2f(0.0, 0.05);
	glVertex3f(x + (6.0*num), y1, z);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x + (6.0*num), y2, z);
	glTexCoord2f(1.0*num, 1.0);
	glVertex3f(x, y2, z);

	glEnd();

	glDisable(GL_BLEND);
	glPopMatrix();
}


void sixFaceSkybox() {
	GLbyte *pBytes9;
	pBytes9 = gltLoadTGA("textures/stormydays_large.tga", &cordinateWidth, &cordinateHeight, &cordinateCo, &textureFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, cordinateCo, cordinateWidth, cordinateHeight, 0, textureFormat, GL_UNSIGNED_BYTE, pBytes9);
	free(pBytes9);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	int vertexZ = 4;
	glFrontFace(GL_CW);
	glRotatef(boXRotate, 0.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(0.5, (2.0 / 3.0));
	glVertex3f(40.0f * 2, 20.0f * 2, -55.0f * vertexZ);
	glTexCoord2f(0.25, (2.0 / 3.0));
	glVertex3f(-40.0f * 2, 20.0f * 2, -55.0f * vertexZ);
	glTexCoord2f(0.25, 1.0);
	glVertex3f(-40.0f * 2, 20.0f * 2, 20.0f * vertexZ);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(40.0f * 2, 20.0f * 2, 20.0f * vertexZ);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.5, (2.0 / 3.0));
	glVertex3f(40.0f * 2, 20.0f * 2, -55.0f * vertexZ);
	glTexCoord2f(0.25, (2.0 / 3.0));
	glVertex3f(-40.0f * 2, 20.0f * 2, -55.0f * vertexZ);
	glTexCoord2f(0.25, (1.0 / 3.0));
	glVertex3f(-40.0f * 2, -13.0f * 2, -55.0f * vertexZ);
	glTexCoord2f(0.5, (1.0 / 3.0));
	glVertex3f(40.0f * 2, -13.0f * 2, -55.0f * vertexZ);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.5, (2.0 / 3.0));
	glVertex3f(40.0f * 2, 20.0f * 2, -55.0f * vertexZ);
	glTexCoord2f(0.75, (2.0 / 3.0));
	glVertex3f(40.0f * 2, 20.0f * 2, 20.0f * vertexZ);
	glTexCoord2f(0.75, (1.0 / 3.0));
	glVertex3f(40.0f * 2, -13.0f * 2, 20.0f * vertexZ);
	glTexCoord2f(0.5, (1.0 / 3.0));
	glVertex3f(40.0f * 2, -13.0f * 2, -55.0f * vertexZ);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.25, (2.0 / 3.0));
	glVertex3f(-40.0f * 2, 20.0f * 2, -55.0f * vertexZ);
	glTexCoord2f(0.0, (2.0 / 3.0));
	glVertex3f(-40.0f * 2, 20.0f * 2, 20.0f * vertexZ);
	glTexCoord2f(0.0, (1.0 / 3.0));
	glVertex3f(-40.0f * 2, -13.0f * 2, 20.0f * vertexZ);
	glTexCoord2f(0.25, (1.0 / 3.0));
	glVertex3f(-40.0f * 2, -13.0f * 2, -55.0f * vertexZ);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.75, (2.0 / 3.0));
	glVertex3f(40.0f * 2, 20.0f * 2, 20.0f * vertexZ);
	glTexCoord2f(1.0, (2.0 / 3.0));
	glVertex3f(-40.0f * 2, 20.0f * 2, 20.0f * vertexZ);
	glTexCoord2f(1.0, (1.0 / 3.0));
	glVertex3f(-40.0f * 2, -13.0f * 2, 20.0f * vertexZ);
	glTexCoord2f(0.75, (1.0 / 3.0));
	glVertex3f(40.0f * 2, -13.0f * 2, 20.0f * vertexZ);
	glEnd();

	glFrontFace(GL_CCW);
}


void backgroundWalls() {

	glPushMatrix();
	GLbyte *pBytes2;
	//Photoshoped Bricked Flower Wall
	pBytes2 = gltLoadTGA("Textures/brick_texture_Flowers.tga", &cordinateWidth, &cordinateHeight, &cordinateCo, &textureFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, cordinateCo, cordinateWidth, cordinateHeight, 0, textureFormat, GL_UNSIGNED_BYTE, pBytes2);
	free(pBytes2);
	glEnable(GL_TEXTURE_2D);


	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-6.0f, -3.0f, -10.0f);
	glTexCoord2f(0.0f, 3.0f);
	glVertex3f(-6.0f, 4.0f, -10.0f);
	glTexCoord2f(3.0f, 3.0f);
	glVertex3f(6.0f, 4.0f, -10.0f);
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(6.0f, -3.0f, -10.0f);
	glEnd();
	

	GLbyte *pBytes;
	// Photoshoped Bricked Flower
	pBytes = gltLoadTGA("Textures/brick_texture_lo_res.tga", &cordinateWidth, &cordinateHeight, &cordinateCo, &textureFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, cordinateCo, cordinateWidth, cordinateHeight, 0, textureFormat, GL_UNSIGNED_BYTE, pBytes);
	free(pBytes);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0, 2.0);
	glVertex3f(-6.0f, 4.0f, 0.0f);
	glTexCoord2f(2.0, 2.0);
	glVertex3f(-6.0f, 4.0f, -10.0f);
	glTexCoord2f(2.0, 0.0);
	glVertex3f(-6.0f, -3.0f, -10.0f);

	glTexCoord2f(2.0, 0.0);
	glVertex3f(6.0f, -3.0f, 0.0f);
	glTexCoord2f(2.0, 2.0);
	glVertex3f(6.0f, 4.0f, 0.0f);
	glTexCoord2f(0.0, 2.0);
	glVertex3f(6.0f, 4.0f, -10.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(6.0f, -3.0f, -10.0f);
	glEnd();


	GLbyte *pBytes1;
	pBytes1 = gltLoadTGA("Textures/ground_grass_.tga", &cordinateWidth, &cordinateHeight, &cordinateCo, &textureFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, cordinateCo, cordinateWidth, cordinateHeight, 0, textureFormat, GL_UNSIGNED_BYTE, pBytes1);
	free(pBytes1);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-6.0f, -1.0f, 0.0f);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(6.0f, -1.0f, 0.0f);
	glTexCoord2f(2.0f, 2.0f);
	glVertex3f(6.0f, -1.0f, -10.0f);
	glTexCoord2f(0.0f, 2.0f);
	glVertex3f(-6.0f, -1.0f, -10.0f);
	glEnd();

	// Target One
	glPushMatrix();
	glTranslatef(targetOne[0], targetOne[1], targetOne[2]);
	pointsTwenty();		//20	
	glPopMatrix();
	// Target Two
	glPushMatrix();
	glTranslatef(targetTwo[0], targetTwo[1], targetTwo[2]);
	pointsTen();		//10
	glPopMatrix();
	// Target Three
	glPushMatrix();
	glTranslatef(targetThree[0], targetThree[1], targetThree[2]);
	pointsTwenty();		//20
	glPopMatrix();
	// Target Four
	glPushMatrix();
	glTranslatef(targetFour[0], targetFour[1], targetFour[2]);
	pointsThirty();		//30	
	glPopMatrix();
	// Target Five
	glPushMatrix();
	glTranslatef(targetFive[0], targetFive[1], targetFive[2]);
	pointsTen();		//10
	glPopMatrix();

	// Target Six
	glPushMatrix();
	glTranslatef(targetSix[0], targetSix[1], targetSix[2]);
	pointsThirty();		//30
	glPopMatrix();

	// Target Seven
	glPushMatrix();
	glTranslatef(targetSeven[0], targetSeven[1], targetSeven[2]);
	pointsThirty();		//30
	glPopMatrix();

	// Target Eight
	glPushMatrix();
	glTranslatef(targetEight[0], targetEight[1], targetEight[2]);
	pointsThirty();		// 30 
	glPopMatrix();

	glTranslated(-xAxis, -yAxis, distanceBall);

}


// Entire display Scenary
void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Wall Construction
	glPushMatrix();
	backgroundWalls();
	glPopMatrix();

	glPushMatrix();
	sixFaceSkybox();
	glPopMatrix();

	// Drawing the Cube Map

	drawFlowers("textures/yellowFlowerFinal.tga", 4, -50.0f);

	// Drawing the Mapp
	glPushMatrix();
	ball();
	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	setOrthographicProjection();
	// Call the scores in between here to change

	resetPerspectiveProjection();
	glEnable(GL_LIGHTING);
	glutSwapBuffers();
}


void scoreDisplay(int x, int y, char *string) {
	glRasterPos2f(x, y);
	int len = (int)strlen(string);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
};

void changingScore() {
	glDisable(GL_LIGHTING);
	char str[10] = { 0 };
	for (int i = 0; i < 10;i=i+1) {
		_itoa_s(values, str, str[i]);
	}
	scoreDisplay(510, 40, "Score: ");
	scoreDisplay(560, 40, str);

	if (test <1) {
		scoreDisplay(220, 250, "Press R to reset");
	}

	glPopMatrix();
}



void collisionDetection() {

}

void distanceFromtheBall() {

	if (distanceBall == 10) {
		distanceBall = 4.00;
		yAxis = -0.55;
		xAxis = 0.00;
		balldistance = 0.0;
	}

	if (distanceBall > 4.00) {
		yAxis = yAxis + (balldistance / 6);
		if ((yAxis) <= -0.55) {
			yAxis = -0.55;
		}
	}
}

void spaceFuntion(int xy) {

	distanceBall = distanceBall + 0.5;
	distanceFromtheBall();
	glutPostRedisplay();
	if (i < 10.00) {
		i = i + 0.5;

		ballRotation += 0.25f;
		glutTimerFunc(35, spaceFuntion, 1);
	}
	else {
		i = 4.0;
		distanceBall = 4.0;
	}
}

void SpecialKeys(int key, int x, int y) {
	if (test > 0) {
		if (key == GLUT_KEY_UP) {

			if (balldistance >= 1.5) {
				balldistance = balldistance;
			}
			else {
				balldistance = balldistance + 0.1;
			}
		}

		if (key == GLUT_KEY_DOWN) {

			if (balldistance <= -0.5) {
				balldistance = balldistance;
			}
			else {
				balldistance = balldistance - 0.1;
			}
		}

		if (key == GLUT_KEY_LEFT) {
			if (xAxis <= -3.1) {
				xAxis = -3.1;
			}
			else {
				xAxis = xAxis - 0.1;
			}
		}

		if (key == GLUT_KEY_RIGHT) {
			if (xAxis >= 3.1) {
				xAxis = 3.1;
			}
			else {
				xAxis = xAxis + 0.1;
			}
		}

		distanceFromtheBall();
		glutPostRedisplay();
	}
}

void timer(int value)
{
	/*
	if (kick) {		//if the ball has been kicked
		t += 0.01;	//time the motion
		r = s*t;	//calculate r for the given equation
		vectorX = r*sin(theta)*cos(phi); //calculate the X-position
										 //from the given eqn. (Reversed because x is the up vector)
		vectorY = r*sin(phi)*cos(theta); //calculate the Y-position
										 //from the given eqn.
		if (vectorY < 0.0f)
			vectorY = -vectorY;
		vectorZ = -r*cos(theta);//calculate the Z-position
								//from the given eqn. (Reversed because x is the up vector and not z)
		angle -= 20.0;		//increment the rotation of the ball
		if (vectorZ < -83) {
			checkScore(vectorX, vectorY - 11.0); //check the score
			vectorZ = 0;					   //reset variables
			vectorX = 0;
			vectorY = 0;
			kick = false;
			t = 0;
			angle = 0.0;
			tries -= 1;						   //update the tries taken
			followcam = false;				   //reset the following camera
		}
	}
	*/
	boXRotate += 0.1;		//rotate the skyBox slowly
	if (boXRotate > 360) {	//restart the rotation if the box comes full circle.
		boXRotate = 0.1;
	}
	glutPostRedisplay();	//redisplay the screen
	glutTimerFunc(10, timer, 1);
}


void keyInput(unsigned char key, int x, int y) {
	if (test > 0) {
		if (key == 32 || key == 'z') {
			i = 4.0;
			glutTimerFunc(25, spaceFuntion, 1);
			test--;
			glutPostRedisplay();
		}
	}
	if (test > 0) {
		if (key == 'r' || key == 'R') {
			glPushMatrix();
			glLoadIdentity();
			glDisable(GL_LIGHTING);
			setOrthographicProjection();

			scoreDisplay(250, 250, "Confirm Reset: press Y");

			glPopMatrix();
			resetPerspectiveProjection();
			glEnable(GL_LIGHTING);
			glutSwapBuffers();
		}
	}

	if (test > 0) {
		if (key == 'y' || key == 'Y') {
			test = 10;
			glutPostRedisplay();
		}
	}

	if (test < 1) {
		if (key == 'r' || key == 'R') {
			test = 10;
			glutPostRedisplay();
		}
	}

}



int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Real Time App");
	glutReshapeFunc(reshape);
	backgroundSettle();
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(keyInput);
	glutTimerFunc(10, timer, 1);		

	glutMainLoop();
	return 0;
}

