#include "stdafx.h"
#include "freeglut.h"
#include "ImageProcessor.h"	
#include <iostream>
#include <string>
#include <cmath>
#include "math.h"
#include "windows.h"
#define _USE_MATH_DEFINES

using namespace std;
char title[] = "3D Real Time App";
GLsizei windowH = 720;
GLsizei windowW = 1280;
GLfloat zAxis = 0;
GLfloat xAxis = 0;
GLfloat yAxis = 0;
int points = 0; 
bool playBool = false;
int times = 10;
int targets = 8; 
GLfloat s = 160;
GLfloat t = 0; 
GLfloat r; 

float tetaAngle;
float piAngle; 
char* pointer; GLbyte *pointerImage; GLint pointerW, pointerH, pointerComponent; GLenum pointerFormat;
double horizontal = 60;
double vertical = windowH - 60.0;

GLfloat degree = 0.0;
GLfloat sixFaceSkybox = 0.0; 
GLfloat  arrayLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat	 ambientL[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat	 spotL[] = { 0.0f, 20.0f, 0.0f, 1.0f };
GLfloat	 SpotPos[] = { 0.0f + xAxis, -5.0f + yAxis, 35.0f + zAxis, 1.0f };
GLfloat	 light = 128;
GLfloat recSpc[] = { 0.8f, 0.8f, 0.8f, 1.0f };

char* arraySpot[8];
bool camera = false;
char* textRed = "textures/targetRed.tga";
char* textBlue = "textures/targetBlue.tga";
char* textDull = "textures/targetDull.tga";
char* textGreen = "textures/targetGreen.tga";

//Usual Reshape Funtion
void reshape(int w, int h)
{
	GLfloat window;
	if (h == 0)	h = 1;
	glViewport(0, 0, w, h);
	window = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0f, window, 1.0, 600.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//sets the Orthographic view, for the sliders and score indicator
void setOrthographicProjection() {
	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	// save the previous matrix which contains the
	//set up for the perspective projection
	glPushMatrix();
	// reset matrix
	glLoadIdentity();
	// set a 2D orthographic projection
	gluOrtho2D(0, windowW, 0, windowH);
	// invert the y axis, down is positive
	glScalef(1, -1, 1);
	// mover the origin from the bottom left corner
	// to the upper left corner
	glTranslatef(0, -windowH, 0);
	//set for drawing again
	glMatrixMode(GL_MODELVIEW);
}

void perspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	if (camera == false) {
		gluPerspective(30.0, ((float)windowW / (float)windowH), 45, 600.0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		gluLookAt(0.00, 0.00, 100.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00);
	}
	else {
		gluPerspective(30.0, ((float)windowW / (float)windowH), 0.1, 300.0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		gluLookAt(1.0 + xAxis, 10.0 + yAxis, 30.0 + zAxis, xAxis, yAxis, zAxis, 0.00, 1.00, 0.00);
	}
}
// PregivenCode to Reset the Perspective Projection
void resetPerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
// Horizaontal Aim Bar
void horizontalBar() {
	glEnable(GL_TEXTURE_2D);
	pointer = "textures/fillBarHorizontal.tga";
	GLbyte *pointerImage;
	pointerImage = gltLoadTGA(pointer, &pointerW, &pointerH, &pointerComponent, &pointerFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, pointerComponent, pointerW, pointerH, 0, pointerFormat, GL_UNSIGNED_BYTE, pointerImage);
	free(pointerImage);
	// GL parameter List for the Image Texturing
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Vertical Bar [Rectangle]
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex2d(30.0, 30.0);
	glTexCoord2f(0.0, 1.0);
	glVertex2d(30.0, 50.0);
	glTexCoord2f(1.0, 1.0);
	glVertex2d(120.0, 50.0);
	glTexCoord2f(1.0, 0.0);
	glVertex2d(120.0, 30.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
// Vertical Aim Bar
void verticalBar() {
	glEnable(GL_TEXTURE_2D);

	pointer = "textures/fillBarVerticalR.tga";
	pointerImage = gltLoadTGA(pointer, &pointerW, &pointerH, &pointerComponent, &pointerFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, pointerComponent, pointerW, pointerH, 0, pointerFormat, GL_UNSIGNED_BYTE, pointerImage);
	free(pointerImage);
	// GL parameter List for the Image Texturing
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Vertical Bar [Rectangle]
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0);
	glVertex2d(windowW - 30.0, windowH - 30.0);
	glTexCoord2f(0.0, 0.0);
	glVertex2d(windowW - 50.0, windowH - 30.0);
	glTexCoord2f(0.0, 1.0);
	glVertex2d(windowW - 50.0, windowH - 120.0);
	glTexCoord2f(1.0, 1.0);
	glVertex2d(windowW - 30.0, windowH - 120.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
//Setting the Final Movement of the Bars
void setFinalMovement() {
	glColor3f(1.0, 1.0, 1.0);
	horizontalBar();
	verticalBar();
	glColor3f(1.0, 0.0, 0);
	glRectd(horizontal, 30.0, horizontal + 30.0, 50.0);
	glRectd(windowW - 30.0, vertical, windowW - 50.0, vertical + 30.0);
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2d(windowW - 120.0, 50.0);
	string message;
	if ((times == 0) || (targets = 0)) {message = "R to replay";}
	else {message = "Score: " + to_string(points);}
	const unsigned char* scoref = reinterpret_cast
		<const unsigned char*>(message.c_str());
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, scoref);
	glPopMatrix();
}

void SpecialKeys(int pressedKey, int x, int y) {
	if (pressedKey == GLUT_KEY_LEFT)
		horizontal -= 2;											
	if (pressedKey == GLUT_KEY_RIGHT)
		horizontal += 2;
	if (pressedKey == GLUT_KEY_UP)
		vertical -= 2;											
	if (pressedKey == GLUT_KEY_DOWN)
		vertical += 2;
	if (vertical < (windowH - 120.0))
		vertical = (windowH - 120.0);							
	if (vertical >(windowH - 60.0))								
		vertical = (windowH - 60.0);
	if (horizontal > 90.0)
		horizontal = 90.0;
	if (horizontal < 30.0)
		horizontal = 30.0;
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:	
		exit(0);
		break;
	case ' ':
		// Space Funtion 
		tetaAngle = ((22/7) / 2) - atan2(85.0f, ((horizontal / (30.0f / 38.0f)) - 76));
		piAngle = atan2(-((660 - vertical) / (-60.0f / 29.0f)), 85.0f);
		playBool = true;
		break;
	case'z':
		// Z Funtion Same as the Space Funtion
		tetaAngle = ((22 / 7) / 2) - atan2(85.0f, ((horizontal / (30.0f / 38.0f)) - 76));
		piAngle = atan2(-((660 - vertical) / (-60.0f / 29.0f)), 85.0f);
		playBool = true;
		break;
	case 'f':	
		camera = true;
		break;
	case 'r':	
		if ((times == 0) || (targets == 0)) {
			times = 10; points = 0;
		}
	}
}

void ball() {

	pointer = "textures/FootballCompleteMap.tga";
	pointerImage = gltLoadTGA(pointer, &pointerW, &pointerH, &pointerComponent, &pointerFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, pointerComponent, pointerW, pointerH, 0, pointerFormat, GL_UNSIGNED_BYTE, pointerImage);
	free(pointerImage);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	if (times > 0) {
		gluQuadricDrawStyle(quadric, GLU_FILL);
		gluQuadricTexture(quadric, true);
		glTranslatef(0 + xAxis, -11.0 + yAxis, 30 + zAxis);
		glRotatef(degree, 1.0f, 0.0f, 0.0f);
		gluSphere(quadric, 2.0f, 30, 17);
	}
	gluDeleteQuadric(quadric);
}

void groundGrass() {
	pointer = "textures/ground_grass_.tga";
	GLbyte *pointerImage;
	pointerImage = gltLoadTGA(pointer, &pointerW, &pointerH, &pointerComponent, &pointerFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, pointerComponent, pointerW, pointerH, 0, pointerFormat, GL_UNSIGNED_BYTE, pointerImage);
	free(pointerImage);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLfloat imageparameters[] = { 0.1, 0.0, 0.1, 1.0 };
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, imageparameters);
	glEnable(GL_TEXTURE_GEN_S);

	//the t parameter
	GLfloat textureparameters[] = { 0.0, 0.1, 0.1, 1.0 };
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, textureparameters);
	glEnable(GL_TEXTURE_GEN_T);

	glBegin(GL_QUADS);
	glVertex3f(40.0f, -13.0f, 55.0f);
	glVertex3f(-40.0f, -13.0f, 55.0f);
	glVertex3f(-40.0f, -13.0f, -55.0f);
	glVertex3f(40.0f, -13.0f, -55.0f);
	glEnd();

	glDisable(GL_TEXTURE_GEN_S); glDisable(GL_TEXTURE_GEN_T);
}
// Constructing the Walls
void walls(	float x1, float y1, float z1,	float x2, float y2, float z2,	float x3, float y3, float z3,	float x4, float y4, float z4) {
	pointer = "textures/brick_wall_backdrop.tga";
	GLbyte *pointerImage;
	pointerImage = gltLoadTGA(pointer, &pointerW, &pointerH, &pointerComponent, &pointerFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, pointerComponent, pointerW, pointerH, 0, pointerFormat, GL_UNSIGNED_BYTE, pointerImage);
	free(pointerImage);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLfloat imageparameters[] = { 0.04, 0.0, 0.04, 1.0 };
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, imageparameters);
	glEnable(GL_TEXTURE_GEN_S);

	GLfloat textureparameters[] = { 0.0, 0.04, 0.0, 1.0 };
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, textureparameters);
	glEnable(GL_TEXTURE_GEN_T);

	if ((z1 == z2) && (z2 == z3) && (z3 == z4) && (z4 == -55.0f)) {
		glNormal3f(0.0f, 0.0f, 1.0f);
	}
	if ((x1 == z2) && (x2 == x3) && (x3 == x4) && (x4 == -40.0f)) {
		glNormal3f(0.0f, 1.0f, 0.0f);
	}
	if ((x1 == z2) && (x2 == x3) && (x3 == x4) && (x4 == 40.0f)) {
		glNormal3f(0.0f, 1.0f, 0.0f);
	}

	glBegin(GL_QUADS);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glVertex3f(x3, y3, z3);
	glVertex3f(x4, y4, z4);
	glEnd();

	glDisable(GL_TEXTURE_GEN_S); glDisable(GL_TEXTURE_GEN_T);
}

// using the pragma pack to draw the spots
#pragma pack(1)
void spots(char* pointer,double posX, double posY, double posZ,double inner, double outer,	double xRot, double yRot) {				
	glPushMatrix();
	pointerImage = gltLoadTGA(pointer, &pointerW, &pointerH, &pointerComponent, &pointerFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, pointerComponent, pointerW, pointerH, 0, pointerFormat, GL_UNSIGNED_BYTE, pointerImage);
	free(pointerImage);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricTexture(quadric, true);
	glTranslatef(posX, posY, posZ);
	glRotatef(xRot, yRot, 0.0, 0.0);
	gluDisk(quadric, inner, outer, 30, 17);
	gluDeleteQuadric(quadric);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.0, 0.0, 0.0);
	glDisable(GL_LIGHT0); glDisable(GL_LIGHT1); glDisable(GL_LIGHTING);
	glRasterPos3d(posX - 1, posY - 0.75, posZ);			
	string points;									
	if (pointer == "textures/targetRed.tga") {points = "30";}
	if (pointer == "textures/targetGreen.tga") {points = "10";}
	if (pointer == "textures/targetBlue.tga") {points = "20";}
	const unsigned char* scoref = reinterpret_cast
		<const unsigned char*>(points.c_str());
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, scoref);
	glEnable(GL_LIGHT0); glEnable(GL_LIGHT1); glEnable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();
}

// Drawing the plants
#pragma pack(1)
void plants(char* pointer, int num, float x) {
	GLfloat y1 = 0;
	GLfloat y2 = 0;
	GLfloat z = 0;
	if (pointer == "textures/orangeFlowerFinal5.tga") {	y1 = -13.0;	y2 = -5.0;	z = -54.8;}
	if (pointer == "textures/yellowFlowerFinal.tga") {	y1 = -13.2;	y2 = -7.0;	z = -54.7;}
	glPushMatrix();
	glEnable(GL_BLEND);	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLbyte *pointerImage;
	pointerImage = gltLoadTGA(pointer, &pointerW, &pointerH, &pointerComponent, &pointerFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, pointerComponent, pointerW, pointerH, 0, pointerFormat, GL_UNSIGNED_BYTE, pointerImage);
	free(pointerImage);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_QUADS);
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

// Drawing the SlideWallPlants
#pragma pack(1)
void sidewallPlants() {
	GLfloat y1 = -13.0;  
	GLfloat y2 = 10.0; GLfloat x = -39.9;
	int num = 5;
	GLfloat z = -30;
	char* pointer = "textures/palmBranchA.tga";

	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLbyte *pointerImage;
	pointerImage = gltLoadTGA(pointer, &pointerW, &pointerH, &pointerComponent, &pointerFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, pointerComponent, pointerW, pointerH, 0, pointerFormat, GL_UNSIGNED_BYTE, pointerImage);
	free(pointerImage);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	for (int i = 0; i < num; i++) {
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.05);
		glVertex3f(x, y1, z + (12.0 * i));
		glTexCoord2f(1.0, 0.05);
		glVertex3f(x + 6, y1, z + (12.0 * i));
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x + 6, y2, z + (12.0 * i));
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x, y2, z + (12.0 * i));
		glEnd();
	}

	glPopMatrix();
	x = 39.9;	
	glPushMatrix();

	for (int i = 0; i < num; i++) {
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.05);
		glVertex3f(x, y1, z + (12.0 * i));
		glTexCoord2f(1.0, 0.05);
		glVertex3f(x - 6, y1, z + (12.0 * i));
		glTexCoord2f(1.0, 1.0);
		glVertex3f(x - 6, y2, z + (12.0 * i));
		glTexCoord2f(0.0, 1.0);
		glVertex3f(x, y2, z + (12.0 * i));
		glEnd();
	}

	glDisable(GL_BLEND);
	glPopMatrix();
}

// Skybox Funtion
#pragma pack(1)
void finalSkyBox() {
	pointer = "textures/stormydays_large.tga";
	pointerImage = gltLoadTGA(pointer, &pointerW, &pointerH, &pointerComponent, &pointerFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, pointerComponent, pointerW, pointerH, 0, pointerFormat, GL_UNSIGNED_BYTE, pointerImage);
	free(pointerImage);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	int accrosZAxis = 4;
	glFrontFace(GL_CW);
	glRotatef(sixFaceSkybox, 0.0f, 1.0f, 0.0f); 
	glBegin(GL_QUADS);
	glTexCoord2f(0.5, (2.0 / 3.0));
	glVertex3f(40.0f * 2, 20.0f * 2, -55.0f * accrosZAxis);
	glTexCoord2f(0.25, (2.0 / 3.0));
	glVertex3f(-40.0f * 2, 20.0f * 2, -55.0f * accrosZAxis);
	glTexCoord2f(0.25, 1.0);
	glVertex3f(-40.0f * 2, 20.0f * 2, 20.0f * accrosZAxis);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(40.0f * 2, 20.0f * 2, 20.0f * accrosZAxis);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.5, (2.0 / 3.0));
	glVertex3f(40.0f * 2, 20.0f * 2, -55.0f * accrosZAxis);
	glTexCoord2f(0.25, (2.0 / 3.0));
	glVertex3f(-40.0f * 2, 20.0f * 2, -55.0f * accrosZAxis);
	glTexCoord2f(0.25, (1.0 / 3.0));
	glVertex3f(-40.0f * 2, -13.0f * 2, -55.0f * accrosZAxis);
	glTexCoord2f(0.5, (1.0 / 3.0));
	glVertex3f(40.0f * 2, -13.0f * 2, -55.0f * accrosZAxis);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.5, (2.0 / 3.0));
	glVertex3f(40.0f * 2, 20.0f * 2, -55.0f * accrosZAxis);
	glTexCoord2f(0.75, (2.0 / 3.0));
	glVertex3f(40.0f * 2, 20.0f * 2, 20.0f * accrosZAxis);
	glTexCoord2f(0.75, (1.0 / 3.0));
	glVertex3f(40.0f * 2, -13.0f * 2, 20.0f * accrosZAxis);
	glTexCoord2f(0.5, (1.0 / 3.0));
	glVertex3f(40.0f * 2, -13.0f * 2, -55.0f * accrosZAxis);
	glEnd();
	
	glBegin(GL_QUADS);
	glTexCoord2f(0.25, (2.0 / 3.0));
	glVertex3f(-40.0f * 2, 20.0f * 2, -55.0f * accrosZAxis);
	glTexCoord2f(0.0, (2.0 / 3.0));
	glVertex3f(-40.0f * 2, 20.0f * 2, 20.0f * accrosZAxis);
	glTexCoord2f(0.0, (1.0 / 3.0));
	glVertex3f(-40.0f * 2, -13.0f * 2, 20.0f * accrosZAxis);
	glTexCoord2f(0.25, (1.0 / 3.0));
	glVertex3f(-40.0f * 2, -13.0f * 2, -55.0f * accrosZAxis);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.75, (2.0 / 3.0));
	glVertex3f(40.0f * 2, 20.0f * 2, 20.0f * accrosZAxis);
	glTexCoord2f(1.0, (2.0 / 3.0));
	glVertex3f(-40.0f * 2, 20.0f * 2, 20.0f * accrosZAxis);
	glTexCoord2f(1.0, (1.0 / 3.0));
	glVertex3f(-40.0f * 2, -13.0f * 2, 20.0f * accrosZAxis);
	glTexCoord2f(0.75, (1.0 / 3.0));
	glVertex3f(40.0f * 2, -13.0f * 2, 20.0f * accrosZAxis);
	glEnd();

	glFrontFace(GL_CCW);
}
// Final Wall and Plants Funtions
void wallsAndPlants() {
	glEnable(GL_TEXTURE_2D);		

	glPushMatrix();
	finalSkyBox();					
	glPopMatrix();
	glPushMatrix();
	
	groundGrass();					
	walls(40.0f, -13.0f, -55.0f,	-40.0f, -13.0f, -55.0f,	-40.0f, 20.0f, -55.0f,40.0f, 20.0f, -55.0f);
	walls(-40.0f, 20.0f, 20.0f,-40.0f, 20.0f, -55.0f,-40.0f, -13.0f, -55.0f,	-40.0f, -13.0f, 20.0f);
	walls(40.0f, 20.0f, -55.0f,40.0f, 20.0f, 20.0f,40.0f, -13.0f, 20.0f,	40.0f, -13.0f, -55.0f);

	glPopMatrix();
	sidewallPlants();
	plants("textures/orangeFlowerFinal5.tga", 4, -33.0f);
	plants("textures/yellowFlowerFinal.tga", 4, -30.0f);
	plants("textures/yellowFlowerFinal.tga", 2, 3.0f);
	plants("textures/yellowFlowerFinal.tga", 3, 25.0f);

	glPushMatrix();
	ball();					
	glPopMatrix();

	spots(textDull,	0, -12.9, 30, 1.2, 1.8,90.0, 1.0);
	spots(arraySpot[0],-37, -10, -54.9,2.1, 2.7,0.0, 1.0);
	spots(arraySpot[1],-30, 10.0, -54.9,4.1, 5.1,0.0, 1.0);
	spots(arraySpot[2],-10, 16, -54.9,	2.1, 2.7, 0.0, 1.0);
	spots(arraySpot[3],-2, -8, -54.9,3.1, 3.8,	0.0, 1.0);
	spots(arraySpot[4],10, 13, -54.9,3.1, 3.8,	0.0, 1.0);
	spots(arraySpot[5],20, -6.5, -54.9,4.1, 5.1,0.0, 1.0);
	spots(arraySpot[6],20, 10, -54.9,2.1, 2.7,	0.0, 1.0);
	spots(arraySpot[7],35, 5, -54.9,2.1, 2.7,0.0, 1.0);

	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glLoadIdentity(); 
}
// Final Score and Panel
void scorePanel(GLfloat x, GLfloat y) {
	if ((x < -35) && (x > -39) && (y < -8) && (y > -12) && (arraySpot[0] != textDull)) {
		points += 30;
		targets -= 1;
		arraySpot[0] = textDull;
	}
	if ((x < -26) && (x > -34) && (y < 14) && (y > 6) && (arraySpot[1] != textDull)) {
		points += 10;
		targets -= 1;
		arraySpot[1] = textDull;
	}
	if ((x < -8) && (x > -12) && (y < 18) && (y > 14) && (arraySpot[2] != textDull)) {
		points += 30;
		targets -= 1;
		arraySpot[2] = textDull;
	}
	if ((x < 1) && (x > -5) && (y < -5) && (y > -11) && (arraySpot[3] != textDull)) {
		points += 20;
		targets -= 1;
		arraySpot[3] = textDull;
	}
	if ((x < 13) && (x > 7) && (y < 16) && (y > 10) && (arraySpot[4] != textDull)) {
		points += 20;
		targets -= 1;
		arraySpot[4] = textDull;
	}
	if ((x < 24) && (x > 16) && (y < -2.5) && (y > -10.5) && (arraySpot[5] != textDull)) {
		points += 10;
		targets -= 1;
		arraySpot[5] = textDull;
	}
	if ((x < 22) && (x > 18) && (y < 12) && (y > 8) && (arraySpot[6] != textDull)) {
		points += 30;
		targets -= 1;
		arraySpot[6] = textDull;
	}
	if ((x < 37) && (x > 33) && (y < 7) && (y > 3) && (arraySpot[7] != textDull)) {
		points += 30;
		targets -= 1;
		arraySpot[7] = textDull;
	}
}
// Timer Function
void timer(int pointer)
{
	if (playBool)
	{		
		t += 0.01;	
		// Using the predefined Equatuin to Rotate the ball
		r = s*t;	
		xAxis = r*sin(tetaAngle)*cos(piAngle); 
		yAxis = r*sin(piAngle)*cos(tetaAngle); 
		if (yAxis < 0.0f)yAxis = -yAxis;
		zAxis = -r*cos(tetaAngle);
		degree -= 20.0;		
		if (zAxis < -83) {
			scorePanel(xAxis, yAxis - 11.0); 
			zAxis = 0;					   
			xAxis = 0;
			yAxis = 0;
			playBool = false;
			t = 0;
			degree = 0.0;
			times -= 1;						   
			camera = false;				   
		}
	}
	sixFaceSkybox += 0.2;		
	if (sixFaceSkybox > 360) {sixFaceSkybox = 0.0;}
	glutPostRedisplay();	
	glutTimerFunc(10, timer, 1);
}
// Target and setting the arraySpot
void targetLight() {
	arraySpot[0] = textRed;
	arraySpot[1] = textGreen;
	arraySpot[2] = textRed;
	arraySpot[3] = textBlue;
	arraySpot[4] = textBlue;
	arraySpot[5] = textGreen;
	arraySpot[6] = textRed;
	arraySpot[7] = textRed;
}
// Setting Up the Light
void finalLightTexture() {
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, recSpc);	
	glMateriali(GL_FRONT, GL_SHININESS, light);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientL);		
	glLightfv(GL_LIGHT0, GL_POSITION, spotL);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT1, GL_SPECULAR, arrayLight);		
	glLightfv(GL_LIGHT1, GL_POSITION, SpotPos);
	glEnable(GL_LIGHT1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
	glFrontFace(GL_CCW);
	targetLight();
}
// Positioning the Ball and backgroundLighting
void positionLights() {
	glLightfv(GL_LIGHT0, GL_POSITION, spotL);
	glLightfv(GL_LIGHT1, GL_POSITION, SpotPos);
	glEnable(GL_NORMALIZE);
}
//Predefined RenderFuntion
void RenderScene(void){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	positionLights();
	perspectiveProjection();
	glEnable(GL_DEPTH_TEST);
	wallsAndPlants();
	glDisable(GL_DEPTH_TEST);
	setOrthographicProjection();
	glDisable(GL_LIGHT0); glDisable(GL_LIGHT1); glDisable(GL_LIGHTING);
	setFinalMovement();
	glEnable(GL_LIGHT0); glEnable(GL_LIGHT1); glEnable(GL_LIGHTING);
	glPopMatrix();
	resetPerspectiveProjection();
	glutSwapBuffers();
}

// Main Funtion
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowW, windowH);
	glutCreateWindow(title);
	glutSpecialFunc(SpecialKeys);	
	glutKeyboardFunc(keyboard);	
	glutReshapeFunc(reshape);				
	glutDisplayFunc(RenderScene);				
	glutTimerFunc(10, timer, 1);		
	finalLightTexture();				
	glutMainLoop();							
	return 0;
}