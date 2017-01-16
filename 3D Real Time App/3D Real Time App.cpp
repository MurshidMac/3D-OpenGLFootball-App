// 3D Realtime App Football Play
#include "stdafx.h"
#include "freeglut.h"
#include <Windows.h>
#include <iostream>
#include <math.h>

using namespace std;
double distanceBall = 4.0;
double yAxis = -0.55;
double xAxis = 0.00;
double balldistance = 0.00;
int values = 10;
double i = 4.00;
int test = 10;
static float ballRotation = 0.0;

GLfloat targetOne[] = { 0.0,0.5,-9.8 };
GLfloat targetTwo[] = { -2.0, 0.0, -9.8 };
GLfloat targetThree[] = { 3.0, 1.0, -9.8 };
GLfloat targetFour[] = { -3.2, 1.0, -9.8 };
GLfloat targetFive[] = { 1.8, 0.0, -9.8 };
GLfloat targetSix[] = { 1.8, 0.0, -9.8 };
GLfloat targetSeven[] = { 1.8, 0.0, -9.8 };
GLfloat targetEight[] = { 1.8, 0.0, -9.8 };

GLbyte *textureOne; 
GLbyte *textureTwo; 
GLbyte *textureThree; 
GLfloat cubeMapVertex[108] =
{

	0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, 0.5f,

	0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,

	-0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	
	0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f

};

GLfloat cubeMapSkybox[72] = {
	0.75,0.33,  
	0.75,0.67,  
	0.5,0.33,  
	0.5,0.33,  
	0.75,0.67, 
	0.5,0.67,  
	0.5,1.0, 
	0.25,1, 
	0.5,0.67,
	0.5,0.67,
	0.25,1.0,
	0.25,0.67, 
    0,0.67,
    0,0.33,
	0.25,0.67,
	0.25,0.67,
	0,0.33,
	0.25,0.33,
	0.25,0.0,
	0.5,0.0,
	0.25,0.33,
	0.25,0.33,
    0.5,0.0,
	0.5,0.33,
	0.5,0.67,
	0.25,0.67,
	0.5,0.33,
	0.5,0.33,
	0.25,0.67,
	0.25,0.33,
	0.75,0.33,
	1.0,0.33,
	0.75,0.67,
	0.75,0.67,
	1.0,0.33,
	1.0,0.67
};

GLfloat cubeMapNormals[108] =
{
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,

	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,

	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f

};

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

void sixFaceSkybox() {

}

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

//Football Properties
void ball() {

	GLbyte *pBytes5;
	pBytes5 = gltLoadTGA("Textures/FootballCompleteMap.tga", &cordinateWidth, &cordinateHeight, &cordinateCo, &textureFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, cordinateCo, cordinateWidth, cordinateHeight, 0, textureFormat, GL_UNSIGNED_BYTE, pBytes5);
	free(pBytes5);
	glEnable(GL_TEXTURE_2D);


	glTranslated(xAxis, yAxis, -distanceBall);
	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricOrientation(quadric, GLU_OUTSIDE);
	//enable the texturing
	gluQuadricTexture(quadric, GL_TRUE);
	gluSphere(quadric, 0.35f, 50, 35);

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
	gluDisk(quadric, 0.5, 0.6, 32, 32);
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
	gluDisk(quadric, 0.4, 0.5, 32, 32);
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
	gluDisk(quadric, 0.3, 0.4, 32, 32);
	glDisable(GL_BLEND);
}

void backgroundWalls() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLbyte *pBytes2;
	pBytes2 = gltLoadTGA("Textures/brick_texture_Flowers.tga", &cordinateWidth, &cordinateHeight, &cordinateCo, &textureFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, cordinateCo, cordinateWidth, cordinateHeight, 0, textureFormat, GL_UNSIGNED_BYTE, pBytes2);
	free(pBytes2);
	glEnable(GL_TEXTURE_2D);


	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-4.0f, -1.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-4.0f, 1.5f, -10.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(4.0f, 1.5f, -10.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.0f, -1.0f, -10.0f);
	glEnd();
	
	GLbyte *pBytes;
	pBytes = gltLoadTGA("Textures/brick_texture_lo_res.tga", &cordinateWidth, &cordinateHeight, &cordinateCo, &textureFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, cordinateCo, cordinateWidth, cordinateHeight, 0, textureFormat, GL_UNSIGNED_BYTE, pBytes);
	free(pBytes);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-4.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-4.0f, 1.5f, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-4.0f, 1.5f, -10.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-4.0f, -1.0f, -10.0f);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(4.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(4.0f, 1.5f, 0.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(4.0f, 1.5f, -10.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(4.0f, -1.0f, -10.0f);
	glEnd();

	GLbyte *pBytes1;
	pBytes1 = gltLoadTGA("Textures/ground_grass_.tga", &cordinateWidth, &cordinateHeight, &cordinateCo, &textureFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, cordinateCo, cordinateWidth, cordinateHeight, 0, textureFormat, GL_UNSIGNED_BYTE, pBytes1);
	free(pBytes1);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-4.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(4.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(4.0f, -1.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-4.0f, -1.0f, -10.0f);
	glEnd();

	glPushMatrix();
	glTranslatef(targetOne[0], targetOne[1], targetOne[2]);
	pointsTwenty();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(targetTwo[0], targetTwo[1], targetTwo[2]);
	pointsTen();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(targetThree[0], targetThree[1], targetThree[2]);
	pointsTwenty();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(targetFour[0], targetFour[1], targetFour[2]);
	pointsThirty();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(targetFive[0], targetFive[1], targetFive[2]);
	pointsTen();
	glPopMatrix();
	ball();
	glTranslated(-xAxis, -yAxis, distanceBall);
}

void scoreDisplay(int x, int y, char *string) {
	glRasterPos2f(x, y);
	int len = (int)strlen(string);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
};

void RenderScene(void) {

	backgroundWalls();
	glPushMatrix();
	glLoadIdentity();
	setOrthographicProjection();
	glDisable(GL_LIGHTING);
	GLbyte *pBytes3;
	pBytes3 = gltLoadTGA("Textures/fillBarHorizontal.tga", &cordinateWidth, &cordinateHeight, &cordinateCo, &textureFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, cordinateCo, cordinateWidth, cordinateHeight, 0, textureFormat, GL_UNSIGNED_BYTE, pBytes3);
	free(pBytes3);
	glEnable(GL_TEXTURE_2D);


	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex2d(30.0, 40.0);
	glTexCoord2f(1.0, 1.0);
	glVertex2d(120.0, 40.0);
	glTexCoord2f(1.0, 0.0);
	glVertex2d(120.0, 80.0);
	glTexCoord2f(0.0, 0.0);
	glVertex2d(30.0, 80.0);
	glEnd();

	GLbyte *pBytes4;
	pBytes4 = gltLoadTGA("Textures/fillBarVerticalR.tga", &cordinateWidth, &cordinateHeight, &cordinateCo, &textureFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, cordinateCo, cordinateWidth, cordinateHeight, 0, textureFormat, GL_UNSIGNED_BYTE, pBytes4);
	free(pBytes4);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex2d(550, 600);
	glTexCoord2f(0.0, 0.0);
	glVertex2d(550, 800);
	glTexCoord2f(1.0, 0.0);
	glVertex2d(580, 800);

	glTexCoord2f(1.0, 1.0);
	glVertex2d(580, 600);
	glEnd();


	char str[10] = { 0 };
	_itoa_s(values, str, 10);
	scoreDisplay(510, 40, "Score: ");
	scoreDisplay(560, 40, str);
	
	if (test <1) {
		scoreDisplay(220, 250, "Press R to reset");
	}

	glPopMatrix();
	resetPerspectiveProjection();
	glEnable(GL_LIGHTING);
	glutSwapBuffers();
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
	//glutTimerFunc(60, rotator, 1);

	glutMainLoop();
	return 0;
}

