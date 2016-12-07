/************************************************************************************

File: 			main.cpp

Description:	Flight Simulator

Author:			Zihao Wu

*************************************************************************************/

/* include the library header files */
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <errno.h>
using namespace std;

/* Lighting variable initializations */
GLfloat lightPosition[] = { 100.0, 100.0, 100.0, 1.0 }; GLfloat zeroMaterial[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat lightningAmbient[] = { 0.0, 1.0, 1.0, 0.8 }; GLfloat lightningDiffuse[] = { 0.0, 1.0, 1.0, 1.0 };
GLfloat whiteSpecular[] = { 1.0, 1.0, 1.0, 1.0 }; GLfloat whiteAmbient[] = { 0.92, 0.92, 0.9, 1.0 };
GLfloat greyAmbient[] = { 0.25, 0.25, 0.25, 1.0 }; GLfloat greyDiffuse[] = { 0.27, 0.27, 0.27, 1.0 };
GLfloat lightGreenAmbient[] = { 0.22, 0.88, 0.22, 1.0 }; GLfloat lightGreenDiffuse[] = { 0.23, 0.90, 0.23, 1.0 };
GLfloat darkGreenAmbient[] = { 0.0, 0.24, 0.0, 1.0 }; GLfloat darkGreenDiffuse[] = { 0.0, 0.3, 0.0, 1.0 };
GLfloat pinkDiffuse[] = { 1.0, 0.5, 0.58, 0.1 }; GLfloat pinkAmbient[] = { 0.92, 0.45, 0.53, 1.0 };
GLfloat blueAmbient[] = { 0.0, 0.0, 0.85, 1.0 }; GLfloat blueDiffuse[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat redAmbient[] = { 0.85, 0.0, 0.0, 1.0 }; GLfloat redDiffuse[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat yellowAmbient[] = { 0.95, 0.95, 0.0, 1.0 }; GLfloat purpleDiffuse[] = { 1.0, 0.0, 1.0, 1.0 };
GLfloat purpleAmbient[] = { 0.9, 0.0, 0.9, 1.0 }; GLfloat lightPurpleAmbient[] = { 0.83, 0.0, 0.79, 1.0 };
GLfloat orangeAmbient[] = { 0.95, 0.6, 0.0, 1.0 }; GLfloat orangeDiffuse[] = { 1.0, 0.65, 0.0, 1.0 };
GLfloat greenAmbient[] = { 0.0, 0.85, 0.0, 1.0 }; GLfloat greenDiffuse[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat yellowDiffuse[] = { 1.0, 1.0, 0.0, 1.0 }; GLfloat blackDiffuse[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat lightPurpleDiffuse[] = { 0.87, 0.58, 0.98, 1.0 }; GLfloat floorDiffuse[] = { 0.35, 0.33, 0.5, 1.0 };
GLfloat goldDiffuse[] = { 1.0, 0.73, 0.2, 1.0 }; GLfloat goldAmbient[] = { 0.85, 0.67, 0.15, 1.0 };
GLfloat seaDiffuse[] = { 0.22, 0.71, 0.73, 1.0 }; GLfloat skyDiffuse[] = { 0.93, 0.6, 0.37, 1.0 }; 
GLfloat skyAmbient[] = { 0.9, 0.58, 0.35, 1.0 }; GLfloat mountainDiffuse[] = { 0.56, 0.4, 0.15, 1.0 }; 
GLfloat mountainAmbient[] = { 0.45, 0.33, 0.13, 1.0 }; GLfloat noShininess = 0.0; 
GLfloat highShininess = 50.0, emission = 1.0;

/* Variables for controlling plane movement */
GLfloat planeSpeed = 0.02, planeSpeedUD = 0.02;
GLint upEnable = 0, downEnable = 0, leftEnable = 0, rightEnable = 0,forwardEnable = 0, backwardEnable = 0;
GLfloat XPosition = 0.0, YPosition = 0.0, ZPosition = 0.0,currentX, currentWidth, previousX, leftRightTurn = 0.0;

/* Varibales for Basic scene */
GLint grid_size = 100, frame_solid_switch = 1, fsPressCount = 1,
full_screen = 0, full_screen_count = 1, landSeaScene = 0, lssPressCount = 0;

/* Variables for land sea scene */
GLint fogEffect = 0, fogPressCount = 0, mountainTexture = 0, 
      mountainTexturePressCount = 0, mountainOn = 0, mountainOnPressCount = 0;

/* Data structure for the generation of Plane */
typedef GLint planeface[4000];
typedef GLfloat plane[7000];
planeface f1 = {}; planeface f2 = {}; planeface f3 = {}; planeface f4 = {}; planeface f5 = {};
planeface f6 = {}; planeface f7 = {}; planeface f8 = {}; planeface f9 = {}; planeface f10 = {};
planeface f11 = {}; planeface f12 = {}; planeface f13 = {}; planeface f14 = {}; planeface f15 = {};
planeface f16 = {}; planeface f17 = {}; planeface f18 = {}; planeface colorCheck = {};
plane pX = {}; plane pY = {}; plane pZ = {}; plane pNX = {}; plane pNY = {}; plane pNZ = {};
GLint countFile = 0, countNormal = 0, countFace = 0;
GLfloat spinning = 0.0;

/* Variables for Snow effect */
typedef GLfloat snow[3200];
snow sX = {}; snow sY = {}; snow sZ = {};
GLint snowEnable = 0, snowPressCount = 0, windPressCount = 0, windEnable = 0;
GLfloat snowSpeed = 0.1, ypos = 0.0, wind = 0.0;

/* Variables for lightning effect */
typedef GLfloat lightning[1000];
lightning lX = {}; lightning lY = {}; lightning lZ = {};
GLint lightningCount = 0, lightningShow = 0, lightningEnable = 0, lightningPressCount = 0;

/* The ratio of the circumference to the diameter of a circle */
#define PI 3.14159265

/* Conversion multiplier for converting from degrees to Radians */
#define DEG_TO_RAD PI/180.0

/* Rotation parameter */
GLfloat rototating = 0.0, turning = 0.0;

/* Texture mapping initializations */
typedef GLubyte Pixel[3];
int imageWidth, imageHeight;
Pixel *Image;
GLuint texture1 = 0; GLuint texture2 = 0; GLuint texture3 = 0;
GLuint LoadTexture(char *fName);

/* Variables for generating random mountains */
GLint polygonsTotal, level = 6;
typedef GLfloat mountain[7000];
mountain mountainY = {};
mountain mountainX1 = {}; mountain mountainZ1 = {}; mountain mountainX2 = {}; mountain mountainZ2 = {};
mountain mountainX3 = {}; mountain mountainZ3 = {}; mountain mountainX4 = {}; mountain mountainZ4 = {};
GLfloat mountainHeight = 4.0, width = 0.35;

/* Rainbow */
GLint rainbowEnable = 0, rainbowPressCount = 0;

/* Weapon variables */
GLfloat firePower = 0.0, hitGround = 0.0;
GLint firePressCount = 0, fireEnable = 0, bombEnable = 0;

/************************************************************************

Function:		lightningGenerator

Description:	Generate random positions for each lightning

*************************************************************************/
void lightningGenerator(void){
	float lightningX, lightningY, lightningZ, maxHeight = 50.0, randomX, randomZ, rangeX, rangeZ;
	int count = 0;

	for (int i = 0; i <= 600; i++) {
		if (i % 15 == 0){
			rangeX = -100.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 200.0));
			rangeZ = -100.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 200.0));
			maxHeight = 50.0;
			count += 1;
		}
		else{
			lightningX = (rangeX - 3.0) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 3.0));
			lightningY = (maxHeight - 2.0) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.0));
			lightningZ = (rangeZ - 3.0) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 3.0));
			lX[i] = lightningX;
			lY[i] = lightningY;
			lZ[i] = lightningZ;
			maxHeight -= 6.0;
		}		
	}

	//printf("%d\n", count);
}

/************************************************************************

Function:		drawSnow

Description:	Generate random positions for each snowflower.

*************************************************************************/
void drawSnow(void){
	float snowX, snowY, snowZ;
	for (int i = 0; i < 3000; i++) {
		snowX = -100.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 200.0));
		snowY = 1.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 99.0));
		snowZ = -100.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 200.0));
		sX[i] = snowX;
		sY[i] = snowY;
		sZ[i] = snowZ;
	}		
}

/************************************************************************

Function:		mountainGenerator for mountain 1, 2 and 3

Description:	Generate random mountain.

*************************************************************************/
void mountainGenerator(void){
	GLint numOfPolygons = level * 10;
	polygonsTotal = numOfPolygons * numOfPolygons;
	GLfloat thisHeight = 0.0, smallestHeight = 0.0, randomHeight = 0.0, currentHeight = 0.0;
	GLint count = 0, countPR = 0, countPC = 0, levelAdded = -1,
		centerPos = 0, offset = 0, levelForHeight = 0, depth = 0, magicCount = 0;

	centerPos = ((numOfPolygons + 1) * (numOfPolygons + 1) + 1) / 2;
	offset = numOfPolygons + 1;
	levelForHeight = numOfPolygons / 2;

	/* Generate random heights for the mountain midpoints */
	for (int i = levelForHeight; i > 0; i = i - 1){
		depth += 1;

		if (i == levelForHeight){
			mountainY[centerPos] = mountainHeight;
			currentHeight = mountainHeight;
		}
		else
			currentHeight = thisHeight;
		
		thisHeight = mountainHeight - (mountainHeight / levelForHeight) * depth;
		
		for (int j = centerPos - (numOfPolygons + 2) * depth + 1; j <= (2 * depth - 1) + (centerPos - (numOfPolygons + 2) * depth + 1) - 1; j = j + 1){
			randomHeight = thisHeight + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (currentHeight - thisHeight)));
			mountainY[j] = randomHeight;
		}
		for (int j = centerPos - (numOfPolygons + 2) * depth + depth * 2 + (numOfPolygons + 1); j <= centerPos - (numOfPolygons + 2) * depth + depth * 2 + (numOfPolygons + 1) + (depth * 2 - 2) * (numOfPolygons + 1); j = j + (numOfPolygons + 1)){
			randomHeight = thisHeight + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (currentHeight - thisHeight)));
			mountainY[j] = randomHeight;
		}
		for (int j = centerPos + numOfPolygons * depth + 1; j <= centerPos + numOfPolygons * depth + (2 * depth - 1); j = j + 1){
			randomHeight = thisHeight + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (currentHeight - thisHeight)));
			mountainY[j] = randomHeight;
		}
		for (int j = centerPos - (numOfPolygons + 2) * depth + (numOfPolygons + 1); j <= centerPos - (numOfPolygons + 2) * depth + (numOfPolygons + 1) + (depth * 2 - 2) * (numOfPolygons + 1); j = j + (numOfPolygons + 1)){
			randomHeight = thisHeight + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (currentHeight - thisHeight)));
			mountainY[j] = randomHeight;
		}

		mountainY[centerPos - (numOfPolygons + 2) * depth] = thisHeight + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (currentHeight - thisHeight)));
		mountainY[centerPos - (numOfPolygons + 2) * depth + depth * 2] = thisHeight + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (currentHeight - thisHeight)));
		mountainY[centerPos + numOfPolygons * depth] = thisHeight + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (currentHeight - thisHeight)));
		mountainY[centerPos - (numOfPolygons + 2) * depth + (2 * depth) + (numOfPolygons + 1) * 2 * depth] = thisHeight + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (currentHeight - thisHeight)));
	}

	/* Assign x, z coordinates for all polygons */
	for (int i = 1; i <= numOfPolygons * numOfPolygons; i = i + 1){
		countPR += 1;
		if (i == 1){
			mountainX1[i] = width;
			mountainX2[i] = width;
			mountainX3[i] = width * 2;
			mountainX4[i] = width * 2;
			mountainZ1[i] = 0.0;
			mountainZ2[i] = width;
			mountainZ3[i] = width;
			mountainZ4[i] = 0.0;
		}
		else{
			if ((i - 1) % numOfPolygons == 0){
				countPR = 1;
				countPC += 1;
				mountainX1[i] = width;
				mountainX2[i] = width;
				mountainX3[i] = width * 2;
				mountainX4[i] = width * 2;
				mountainZ1[i] = countPC * width;
				mountainZ2[i] = countPC * width + width;
				mountainZ3[i] = countPC * width + width;
				mountainZ4[i] = countPC * width;
			}
			else{
				mountainX1[i] = width * countPR;
				mountainX2[i] = width * countPR;
				mountainX3[i] = width * countPR + width;
				mountainX4[i] = width * countPR + width;
				mountainZ1[i] = countPC * width;
				mountainZ2[i] = countPC * width + width;
				mountainZ3[i] = countPC * width + width;
				mountainZ4[i] = countPC * width;
			}
		}
	}
}

/************************************************************************

Function:		drawMountain

Description:	Draw mountain in solid or frame mode. 

*************************************************************************/
void drawMountain(void) {
	GLint pRow = 0, pCol = 0, add = level * 10 + 1;
	GLfloat texel = 1 / (GLfloat)(level * 10);

	/* Bind texture on button press and we are in solid mode */
	if (mountainTexture == 1){
		/* Enable texture mapping */
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture3);
	}

	/* Texture mapping for each polygons */
	for (int k = 0; k <= polygonsTotal; k++){
		if (mountainTexture == 0){
			if (mountainY[k + 1 * pRow] >= mountainHeight * 0.8){
				glMaterialfv(GL_FRONT, GL_AMBIENT, whiteAmbient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, whiteSpecular);
				glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
				glMaterialf(GL_FRONT, GL_SHININESS, noShininess);
			}
			else if (mountainY[k + 1 * pRow] >= mountainHeight * 0.7 && mountainY[k + 1 * pRow] < mountainHeight * 0.8){
				glMaterialfv(GL_FRONT, GL_AMBIENT, greyAmbient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, greyDiffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
				glMaterialf(GL_FRONT, GL_SHININESS, noShininess);
			}
			else if (mountainY[k + 1 * pRow] >= mountainHeight * 0.3 && mountainY[k + 1 * pRow] < mountainHeight * 0.7){
				glMaterialfv(GL_FRONT, GL_AMBIENT, lightGreenAmbient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, lightGreenDiffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
				glMaterialf(GL_FRONT, GL_SHININESS, noShininess);
			}
			else{
				glMaterialfv(GL_FRONT, GL_AMBIENT, darkGreenAmbient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, darkGreenDiffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
				glMaterialf(GL_FRONT, GL_SHININESS, noShininess);
			}
		}

		pCol += 1;
		if (k == 1){
			glShadeModel(GL_SMOOTH);
			glPushMatrix();
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f, 0.0f);	glVertex3f(mountainX1[k], mountainY[k], mountainZ1[k]);
			glTexCoord2f(0.0f, texel);  glVertex3f(mountainX2[k], mountainY[k + add], mountainZ2[k]);
			glTexCoord2f(texel, texel); glVertex3f(mountainX3[k], mountainY[k + add + 1], mountainZ3[k]);
			glTexCoord2f(texel, 0.0f);  glVertex3f(mountainX4[k], mountainY[k + 1], mountainZ4[k]);
			glEnd();
			glPopMatrix();
		}
		else{
			if ((k - 1) % (level * 10) == 0){
				glShadeModel(GL_SMOOTH);
				pRow += 1;
				pCol = 1;
				glPushMatrix();
				glBegin(GL_POLYGON);
				glTexCoord2f(0.0f, texel * pRow);			glVertex3f(mountainX1[k], mountainY[k + 1 * pRow], mountainZ1[k]);
				glTexCoord2f(0.0f, texel * pRow + texel);	glVertex3f(mountainX2[k], mountainY[k + 1 * pRow + add], mountainZ2[k]);
				glTexCoord2f(texel, texel * pRow + texel);	glVertex3f(mountainX3[k], mountainY[k + 1 * pRow + add + 1], mountainZ3[k]);
				glTexCoord2f(texel, texel * pRow);			glVertex3f(mountainX4[k], mountainY[k + 1 * pRow + 1], mountainZ4[k]);
				glEnd();
				glPopMatrix();
			}
			else{
				glShadeModel(GL_SMOOTH);
				glPushMatrix();
				glBegin(GL_POLYGON);
				glTexCoord2f(texel * pCol, texel * pRow);					glVertex3f(mountainX1[k], mountainY[k + 1 * pRow], mountainZ1[k]);
				glTexCoord2f(texel * pCol, texel * pRow + texel);			glVertex3f(mountainX2[k], mountainY[k + 1 * pRow + add], mountainZ2[k]);
				glTexCoord2f(texel * pCol + texel, texel * pRow + texel);	glVertex3f(mountainX3[k], mountainY[k + 1 * pRow + add + 1], mountainZ3[k]);
				glTexCoord2f(texel * pCol + texel, texel * pRow);			glVertex3f(mountainX4[k], mountainY[k + 1 * pRow + 1], mountainZ4[k]);
				glEnd();
				glPopMatrix();
			}
		}
	}
	/* Turn off texture mapping when done */
	glDisable(GL_TEXTURE_2D);
}

/************************************************************************

Function:		keyFunction

Description:	Check which key was pressed

*************************************************************************/
void keyFunction(unsigned char key, int x, int y){
	/* Press w key to switch between wire and solid rendering */
	if (key == 'w') {
		fsPressCount += 1;
		if (fsPressCount % 2 == 0){
			frame_solid_switch = 0;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else{
			frame_solid_switch = 1;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
	}

	/* Press f key to enable && disable full screen mode */
	if (key == 'f'){
		full_screen_count += 1;
		if (full_screen_count % 2 == 0){
			full_screen = 1;
			glutFullScreen();
		}
		else{
			full_screen = 0;
			glutReshapeWindow(1000, 800);
			glutPositionWindow(100, 150);
		}
	}

	/* Enable land && sea mode */
	if (key == 's'){
		lssPressCount += 1;
		if (lssPressCount % 2 != 0)
			landSeaScene = 1;
		else
			landSeaScene = 0;
	}

	/* Fog effect */
	if (key == 'b'){
		fogPressCount += 1;
		if (fogPressCount % 2 != 0)
			fogEffect = 1;
		else
			fogEffect = 0;
	}
	
	/* Draw texture for the mountain */
	if (key == 't'){
		mountainTexturePressCount += 1;
		if (mountainTexturePressCount % 2 != 0)
			mountainTexture = 1;
		else
			mountainTexture = 0;
	}

	/* Draw the mountain */
	if (key == 'm'){
		mountainOnPressCount += 1;
		if (mountainOnPressCount % 2 != 0)
			mountainOn = 1;
		else
			mountainOn = 0;
	}

	/* Draw the snow */
	if (key == 'o'){
		snowPressCount += 1;
		if (snowPressCount % 2 != 0)
			snowEnable = 1;
		else
			snowEnable = 0;
	}
	
	/* Lightning enable */
	if (key == 'l'){
		lightningPressCount += 1;
		if (lightningPressCount % 2 != 0)
			lightningEnable = 1;
		else
			lightningEnable = 0;
	}
	
	/* Trigger wind */
	if (key == 'd'){
		windPressCount += 1;
		if (windPressCount % 2 != 0)
			windEnable = 1;
		else
			windEnable = 0;
	}
	
	/* Trigger rainbow */
	if (key == 'r'){
		rainbowPressCount += 1;
		if (rainbowPressCount % 2 != 0)
			rainbowEnable = 1;
		else
			rainbowEnable = 0;
	}

	/* Trigger firing */
	if (key == 'g' && bombEnable == 0){
		firePressCount += 1;
		if (firePressCount % 2 != 0)
			fireEnable = 1;
		else
			fireEnable = 0;
	}

	/* Exit the program */
	if (key == 'q'){
		exit(0);
	}
}

/************************************************************************

Function:		keyForPlane

Description:	Key event for plane movement using arrow keys

*************************************************************************/
void keyForPlane(int key, int x, int y) {
	if (key == GLUT_KEY_PAGE_UP){
		forwardEnable = 1;
		backwardEnable = 0;
	}
	if (key == GLUT_KEY_PAGE_DOWN){
		backwardEnable = 1;
		forwardEnable = 0;
	}
	if (key == GLUT_KEY_UP)
		upEnable = 1;
	if (key == GLUT_KEY_DOWN)
		downEnable = 1;
}

/************************************************************************

Function:		keyUpPlane

Description:	Key release event for plane movement using arrow keys

*************************************************************************/
void keyUpPlane(int key, int x, int y){
	if (key == GLUT_KEY_PAGE_UP)
		forwardEnable = 0;
	if (key == GLUT_KEY_PAGE_DOWN)
		backwardEnable = 0;
	if (key == GLUT_KEY_UP)
		upEnable = 0;
	if (key == GLUT_KEY_DOWN)
		downEnable = 0;
}

/************************************************************************

Function:		mouseMovement

Description:	To handle mouse movements

*************************************************************************/
void mouseMovement(GLint x, GLint y){	
	currentX = (GLfloat)x / (GLfloat)currentWidth;
	
	if (currentX - previousX < 0)
		leftEnable = 1;
	else
		rightEnable = 1;

	previousX = currentX;
}

/************************************************************************

Function:		animation

Description:	animation controller

*************************************************************************/
void animation(void)
{
	/* Control weapon system */
	firePower += 0.01;
	
	/* Count lightning occurance */
	lightningCount += 1;

	/* Change plane speed */
	if (forwardEnable == 1)
		planeSpeed += 0.0005;
	if (backwardEnable == 1)
		planeSpeed -= 0.0005;
	if (planeSpeed < 0.02)
		planeSpeed = 0.02;
	
	/* Tilt the plane to left or right */
	if (leftEnable == 1){
		leftRightTurn += 1.0;
		leftEnable = 0;
	}
	if (rightEnable == 1){
		leftRightTurn -= 1.0;
		rightEnable = 0;
	}	
	if (leftRightTurn < -45)
		leftRightTurn = -45;
	if (leftRightTurn > 45)
		leftRightTurn = 45;

	/* Determine plane rototate position */
	if (leftRightTurn > 0){
		if (leftRightTurn < 10.0 && leftRightTurn > -10.0){
			rototating -= 0.0;
		}
		if (leftRightTurn < -30.0 || leftRightTurn > 30.0){
			rototating -= 0.5;
		}
		if (leftRightTurn < -20.0 || leftRightTurn > 20.0){
			rototating -= 0.3;
		}
	}
	else{
		if (leftRightTurn < 10.0 && leftRightTurn > -10.0){
			rototating += 0.0;
		}
		if (leftRightTurn < -30.0 || leftRightTurn > 30.0){
			rototating += 0.5;
		}
		if (leftRightTurn < -20.0 || leftRightTurn > 20.0){
			rototating += 0.3;
		}
	}
	if (rototating >= 360.0)
		rototating -= 360.0;
	if (rototating <= 0.0)
		rototating += 360;
	
	/* Control propeller rototating */
	spinning += 10.0;
	if (spinning >= 360.0)
		spinning -= 360.0;
	if (spinning <= 0.0)
		spinning += 360;

	/* Now force OpenGL to redraw the change */
	glutPostRedisplay();
}

/************************************************************************

Function:		basicScene

Description:	Draw basic scene

*************************************************************************/
void basicScene(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, redAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, redDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, noShininess);
	glLineWidth(5.0f);
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glEnd(); /* Draw x line */
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, greenAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, greenDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, noShininess);
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glEnd(); /* Draw y line */
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, blueAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blueDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, noShininess);
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 1.0);
	glEnd(); /* Draw z line */
	glPopMatrix();

	/* Draw a sphere on origin */
	glMaterialfv(GL_FRONT, GL_AMBIENT, zeroMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, whiteSpecular);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, noShininess);
	glPushMatrix();
	glutSolidSphere(0.1, 48, 48);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, zeroMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, floorDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, noShininess);

	glNormal3d(0, 1, 0);

	/* Draw QUAD */
	glLineWidth(1.0f);
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(50.0, 0.0, -50.0);
	glVertex3f(50.0, 0.0, 50.0);
	glVertex3f(-50.0, 0.0, 50.0);
	glVertex3f(-50.0, 0.0, -50.0);
	glEnd();
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, zeroMaterial);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, floorDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, noShininess);

	/* Draw 100 x 100 grids, size can be changed by changing the global constant of grid_size */
	for (int i = -grid_size / 2; i < grid_size / 2; i++){
		glPushMatrix();
		glBegin(GL_LINES);
		glVertex3f(grid_size / 2, 0.0, i);
		glVertex3f(-grid_size / 2, 0.0, i);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glBegin(GL_LINES);
		glVertex3f(i, 0.0, grid_size / 2);
		glVertex3f(i, 0.0, -grid_size / 2);
		glEnd();
		glPopMatrix();
	}
}

/************************************************************************

Function:		drawPlane

Description:	Draw the plane

*************************************************************************/
void drawPlane(GLint startFrom){
	int toThis = 0;
	if (startFrom == 1)
		toThis = 3640;
	else
		toThis = 4000;
	for (int i = startFrom; i < toThis; i++){
		glPushMatrix();
		glBegin(GL_POLYGON);

		if (colorCheck[i] <= 3){
			glMaterialfv(GL_FRONT, GL_AMBIENT, zeroMaterial);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, yellowDiffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecular);
			glMaterialf(GL_FRONT, GL_SHININESS, highShininess);
		}
		if (colorCheck[i] > 3 && colorCheck[i] <= 5){
			glMaterialfv(GL_FRONT, GL_AMBIENT, zeroMaterial);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, blackDiffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecular);
			glMaterialf(GL_FRONT, GL_SHININESS, highShininess);
		}
		if (colorCheck[i] == 6){
			glMaterialfv(GL_FRONT, GL_AMBIENT, zeroMaterial);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, lightPurpleDiffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecular);
			glMaterialf(GL_FRONT, GL_SHININESS, highShininess);
		}
		if (colorCheck[i] == 7){
			glMaterialfv(GL_FRONT, GL_AMBIENT, zeroMaterial);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDiffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecular);
			glMaterialf(GL_FRONT, GL_SHININESS, highShininess);
		}
		if (colorCheck[i] > 7 && colorCheck[i] <= 13){
			glMaterialfv(GL_FRONT, GL_AMBIENT, zeroMaterial);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, yellowDiffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecular);
			glMaterialf(GL_FRONT, GL_SHININESS, highShininess);
		}
		if (colorCheck[i] > 13 && colorCheck[i] <= 25){
			glMaterialfv(GL_FRONT, GL_AMBIENT, zeroMaterial);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, blueDiffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecular);
			glMaterialf(GL_FRONT, GL_SHININESS, highShininess);
		}
		if (colorCheck[i] > 25 && colorCheck[i] <= 31){
			glMaterialfv(GL_FRONT, GL_AMBIENT, zeroMaterial);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, yellowDiffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecular);
			glMaterialf(GL_FRONT, GL_SHININESS, highShininess);
		}
		if (colorCheck[i] == 32){
			glMaterialfv(GL_FRONT, GL_AMBIENT, zeroMaterial);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, yellowDiffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecular);
			glMaterialf(GL_FRONT, GL_SHININESS, highShininess);
		}
		if (colorCheck[i] == 33){
			glMaterialfv(GL_FRONT, GL_AMBIENT, zeroMaterial);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, whiteSpecular);
			glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecular);
			glMaterialf(GL_FRONT, GL_SHININESS, highShininess);
		}
		if (colorCheck[i] == 34){
			glMaterialfv(GL_FRONT, GL_AMBIENT, zeroMaterial);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, lightPurpleDiffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecular);
			glMaterialf(GL_FRONT, GL_SHININESS, highShininess);
		}
		if (colorCheck[i] == 35){
			glMaterialfv(GL_FRONT, GL_AMBIENT, zeroMaterial);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, redDiffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecular);
			glMaterialf(GL_FRONT, GL_SHININESS, highShininess);
		}

		glNormal3f(pNX[f1[i]], pNY[f1[i]], pNZ[f1[i]]);
		glNormal3f(pNX[f2[i]], pNY[f2[i]], pNZ[f2[i]]);
		glNormal3f(pNX[f3[i]], pNY[f3[i]], pNZ[f3[i]]);
		glVertex3f(pX[f1[i]], pY[f1[i]], pZ[f1[i]]);
		glVertex3f(pX[f2[i]], pY[f2[i]], pZ[f2[i]]);
		glVertex3f(pX[f3[i]], pY[f3[i]], pZ[f3[i]]);
		if (f4[i] != 0){
			glNormal3f(pNX[f4[i]], pNY[f4[i]], pNZ[f4[i]]);
			glVertex3f(pX[f4[i]], pY[f4[i]], pZ[f4[i]]);
		}
		if (f5[i] != 0){
			glNormal3f(pNX[f5[i]], pNY[f5[i]], pNZ[f5[i]]);
			glVertex3f(pX[f5[i]], pY[f5[i]], pZ[f5[i]]);
		}
		if (f6[i] != 0){
			glNormal3f(pNX[f6[i]], pNY[f6[i]], pNZ[f6[i]]);
			glVertex3f(pX[f6[i]], pY[f6[i]], pZ[f6[i]]);
		}
		if (f7[i] != 0){
			glNormal3f(pNX[f17[i]], pNY[f17[i]], pNZ[f17[i]]);
			glVertex3f(pX[f7[i]], pY[f7[i]], pZ[f7[i]]);
		}
		if (f8[i] != 0){
			glNormal3f(pNX[f8[i]], pNY[f8[i]], pNZ[f8[i]]);
			glVertex3f(pX[f8[i]], pY[f8[i]], pZ[f8[i]]);
		}
		if (f9[i] != 0){
			glNormal3f(pNX[f9[i]], pNY[f9[i]], pNZ[f9[i]]);
			glVertex3f(pX[f9[i]], pY[f9[i]], pZ[f9[i]]);
		}
		if (f10[i] != 0){
			glNormal3f(pNX[f10[i]], pNY[f10[i]], pNZ[f10[i]]);
			glVertex3f(pX[f10[i]], pY[f10[i]], pZ[f10[i]]);
		}
		if (f11[i] != 0){
			glNormal3f(pNX[f11[i]], pNY[f11[i]], pNZ[f11[i]]);
			glVertex3f(pX[f11[i]], pY[f11[i]], pZ[f11[i]]);
		}
		if (f12[i] != 0){
			glNormal3f(pNX[f12[i]], pNY[f12[i]], pNZ[f12[i]]);
			glVertex3f(pX[f12[i]], pY[f12[i]], pZ[f12[i]]);
		}
		if (f13[i] != 0){
			glNormal3f(pNX[f13[i]], pNY[f13[i]], pNZ[f13[i]]);
			glVertex3f(pX[f13[i]], pY[f13[i]], pZ[f13[i]]);
		}
		if (f14[i] != 0){
			glNormal3f(pNX[f14[i]], pNY[f14[i]], pNZ[f14[i]]);
			glVertex3f(pX[f14[i]], pY[f14[i]], pZ[f14[i]]);
		}
		if (f15[i] != 0){
			glNormal3f(pNX[f15[i]], pNY[f15[i]], pNZ[f15[i]]);
			glVertex3f(pX[f15[i]], pY[f15[i]], pZ[f15[i]]);
		}
		if (f16[i] != 0){
			glNormal3f(pNX[f16[i]], pNY[f16[i]], pNZ[f16[i]]);
			glVertex3f(pX[f16[i]], pY[f16[i]], pZ[f16[i]]);
		}
		if (f17[i] != 0){
			glNormal3f(pNX[f17[i]], pNY[f17[i]], pNZ[f17[i]]);
			glVertex3f(pX[f17[i]], pY[f17[i]], pZ[f17[i]]);
		}
		if (f18[i] != 0){
			glNormal3f(pNX[f18[i]], pNY[f18[i]], pNZ[f18[i]]);
			glVertex3f(pX[f18[i]], pY[f18[i]], pZ[f18[i]]);
		}
		glEnd();
		glPopMatrix();
	}
}

/************************************************************************

Function:		landseaScene

Description:	Draw the sea and sky with texture mappings applied

*************************************************************************/
void landseaScene(){
	/* Fog effect */
	if (fogEffect == 1){
		glEnable(GL_FOG);
		glPushMatrix();
		glFogfv(GL_FOG_COLOR, pinkDiffuse);
		glFogf(GL_FOG_MODE, GL_EXP);
		glFogf(GL_FOG_DENSITY, 0.02);
		glPopMatrix();
	}
	
	/* Enable texture mapping */
	glEnable(GL_TEXTURE_2D);
	
	/* Sea texture mapping and creation */
	glMaterialfv(GL_FRONT, GL_AMBIENT, seaDiffuse);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, seaDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, highShininess);
	glMaterialf(GL_FRONT, GL_EMISSION, emission);

	GLUquadric *seaDisk;
	seaDisk = gluNewQuadric();

	glBindTexture(GL_TEXTURE_2D, texture2);

	glPushMatrix();
	glShadeModel(GL_SMOOTH);
	gluQuadricNormals(seaDisk, GLU_SMOOTH);
	gluQuadricTexture(seaDisk, GL_TRUE);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluDisk(seaDisk, 0.0, 100.0, 100, 80);
	glPopMatrix();

	gluDeleteQuadric(seaDisk);
	glDisable(GL_FOG);

	/* Sky texture mapping and creation */
	glMaterialfv(GL_FRONT, GL_AMBIENT, skyAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, skyDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, highShininess);
	glMaterialf(GL_FRONT, GL_EMISSION, emission);

	GLUquadric *skyCylinder;
	skyCylinder = gluNewQuadric();
	
	glBindTexture(GL_TEXTURE_2D, texture1);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glTranslatef(0.5, 0.5, 0.0);
	glRotatef(180, 1.0, 0.0, 0.0);
	glTranslatef(-0.5, -0.5, 0.0);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glShadeModel(GL_SMOOTH);
	gluQuadricNormals(skyCylinder, GLU_SMOOTH);
	glColor3f(1.0f, 1.0f, 1.0f);
	gluQuadricTexture(skyCylinder, GL_TRUE);
	glTranslatef(0.0, -5.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(skyCylinder, 95.0, 95.0, 100.0, 100, 80);
	glPopMatrix();

	gluDeleteQuadric(skyCylinder);

	/* Disable texture mapping */
	glDisable(GL_TEXTURE_2D);
}

/************************************************************************

Function:		snowing

Description:	simulate snowing effect 

*************************************************************************/
void snowing(void){
	ypos += snowSpeed;
	wind += snowSpeed * 2;
	for (int i = 0; i < 3200; i = i + 1){
		glPushMatrix();
		glPointSize(2.0f);
		glMaterialfv(GL_FRONT, GL_AMBIENT, whiteAmbient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, whiteAmbient);
		glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecular);
		glMaterialf(GL_FRONT, GL_SHININESS, highShininess);
		glBegin(GL_POINTS);
		glVertex3f(sX[i], sY[i] - ypos, sZ[i] + cos(30 * DEG_TO_RAD) * wind * windEnable);
		glEnd();
		glPopMatrix();
	}
}

/************************************************************************

Function:		lightningEffect

Description:	simulate lightning effect

*************************************************************************/
void lightningEffect(void){
	lightningShow += 1;
	for (int i = 0; i <= 600; i = i + 1){
		glMaterialfv(GL_FRONT, GL_AMBIENT, lightningAmbient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, lightningDiffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecular);
		glMaterialf(GL_FRONT, GL_SHININESS, highShininess);

		if (i % 15 == 0){
			if (lightningCount % 10 == 0){
				glPushMatrix();
				glLineWidth(2.0f);
				glBegin(GL_LINE_STRIP);
				for (int j = i + 1; j <= i + 13; j = j + 1){
					glVertex3f(lX[j], lY[j], lZ[j]);
				}
				glEnd();
				glPopMatrix();
			}
		}
	}
}

/************************************************************************

Function:		rainbow

Description:	simulate rainbow effect

*************************************************************************/
void rainbow(GLfloat start){
	for (float j = start; j <= (start + 1.0); j = j + 0.1){
		glPushMatrix();
		if (start == 15){
			glMaterialfv(GL_FRONT, GL_AMBIENT, redAmbient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, redDiffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
			glMaterialf(GL_FRONT, GL_SHININESS, noShininess);
		}
		if (start == 16){
			glMaterialfv(GL_FRONT, GL_AMBIENT, orangeAmbient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, orangeDiffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
			glMaterialf(GL_FRONT, GL_SHININESS, noShininess);
		}
		if (start == 17){
			glMaterialfv(GL_FRONT, GL_AMBIENT, yellowAmbient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, yellowDiffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
			glMaterialf(GL_FRONT, GL_SHININESS, noShininess);
		}
		if (start == 18){
			glMaterialfv(GL_FRONT, GL_AMBIENT, greenAmbient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, greenDiffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
			glMaterialf(GL_FRONT, GL_SHININESS, noShininess);
		}
		if (start == 19){
			glMaterialfv(GL_FRONT, GL_AMBIENT, blueAmbient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, blueDiffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
			glMaterialf(GL_FRONT, GL_SHININESS, noShininess);
		}
		if (start == 20){
			glMaterialfv(GL_FRONT, GL_AMBIENT, purpleAmbient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, purpleDiffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
			glMaterialf(GL_FRONT, GL_SHININESS, noShininess);
		}
		if (start == 21){
			glMaterialfv(GL_FRONT, GL_AMBIENT, lightPurpleAmbient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, lightPurpleDiffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
			glMaterialf(GL_FRONT, GL_SHININESS, noShininess);
		}
		glLineWidth(1.0f);
		glBegin(GL_LINE_LOOP);
		for (GLdouble i = -90; i <= 90; i++){
			GLfloat degInRad = i * DEG_TO_RAD;
			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(80.0, cos(degInRad) * j - 0.1, (sin(degInRad) * j) * 1.8);
		}
		glEnd();

		/* Do this to disable rainbow effect on mountain */
		glMaterialfv(GL_FRONT, GL_AMBIENT, whiteAmbient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, whiteSpecular);
		glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
		glMaterialf(GL_FRONT, GL_SHININESS, noShininess);

		glPopMatrix();
	}
}

/************************************************************************

Function:		firing

Description:	Draw bomb to the ground

*************************************************************************/
void firing(){
	float randomX, randomY, randomZ, directionX = 1.0, directionZ = 1.0, directionY = 1.0;

	glMaterialfv(GL_FRONT, GL_AMBIENT, goldAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, zeroMaterial);
	glMaterialf(GL_FRONT, GL_SHININESS, noShininess);

	GLUquadric *bomb;
	bomb = gluNewQuadric();

	glBindTexture(GL_TEXTURE_2D, texture1);

	glPushMatrix();
	glShadeModel(GL_SMOOTH);
	gluQuadricNormals(bomb, GLU_SMOOTH);
	gluQuadricTexture(bomb, GL_TRUE);

	glTranslatef(XPosition, YPosition + 2.5 - firePower, ZPosition);
	gluCylinder(bomb, 0.1, 0.1, 0.5, 10, 2);
	glPopMatrix();

	hitGround = YPosition + 2.5 - firePower;
	
	/* Check if bomb hit the ground */
	if (hitGround < 0.1){
		firePower = 0.0;
		hitGround = 0.0;
		bombEnable = 0;
		
		for (int i = 0; i < 100; i = i + 1){
			randomX = 0.5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.5));
			randomY = 0.5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.5));
			randomZ = 0.5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1.5));

			if (i % 2 == 0){
				directionX = -1.0;
				directionZ = 1.0;
				directionY = 1.0;
			}
			else if (i % 3 == 0){
				directionX = 1.0;
				directionZ = 1.0;
				directionY = -1.0;
			}
			else if (i % 4 == 0){
				directionX = -1.0;
				directionZ = -1.0;
				directionY = 1.0;
			}
			else if (i % 5 == 0){
				directionX = 1.0;
				directionZ = -1.0;
				directionY = -1.0;
			}
			else{
				directionX = 1.0;
				directionZ = 1.0;
				directionY = 1.0;
			}
			glPushMatrix();
			glPointSize(4.0f);
			glMaterialfv(GL_FRONT, GL_AMBIENT, whiteAmbient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, whiteAmbient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecular);
			glMaterialf(GL_FRONT, GL_SHININESS, highShininess);
			glBegin(GL_POINTS);
			glVertex3f(XPosition * randomX * directionX, randomY * directionY, ZPosition * randomZ * directionZ);
			glEnd();
			glPopMatrix();
		}
	}
}

/************************************************************************

Function:		displayFunction

Description:	Display callback, draw the scene

*************************************************************************/
void displayFunction(void)
{
	/* clear the screen and depth buffer */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* load the identity matrix into the model view matrix */
	glLoadIdentity();

	/* Control plane movement */
	XPosition = XPosition + planeSpeed * cos(rototating * DEG_TO_RAD);
	ZPosition = ZPosition + planeSpeed * sin(rototating * DEG_TO_RAD);
	YPosition = YPosition + planeSpeedUD * upEnable + planeSpeedUD * (-1) * downEnable;
			
	/* Set camera position */
	gluLookAt(XPosition - 10.0 * cos(rototating * DEG_TO_RAD), 4.0 + YPosition, ZPosition - 10.0 * sin(rototating * DEG_TO_RAD),
		XPosition, 2.5 + YPosition, ZPosition,
		0.0, 0.1, 0.0);

	/* Draw the plane */ 
	glPushMatrix();

	// Translate the plane 
	glTranslatef(XPosition, 2.5 + YPosition, ZPosition);
	glRotatef(-rototating + 180, 0.0, 1.0, 0.0);

	// Tilt the plane on left right from -45 to 45
	glRotatef(leftRightTurn, 1.0, 0.0, 0.0); 
	glScalef(2.5, 2.5, 2.5);
	drawPlane(1);
	
	// Draw first propeller
	glPushMatrix();
	glTranslatef(-0.6, -0.15, 0.35);
	glRotatef(spinning, 1.0, 0.0, 0.0);
	glTranslatef(0.6, 0.15, -0.35);
	drawPlane(3640);
	glPopMatrix();
	
	// Draw second propeller
	glPushMatrix();
	glTranslatef(-0.6, -0.15, -0.35);
	glRotatef(spinning, 1.0, 0.0, 0.0);
	glTranslatef(0.6, 0.15, -0.35);
	drawPlane(3640);
	glPopMatrix();	
	
	glPopMatrix();

	/* Enable bombing effect */
	if (fireEnable == 1) {
		bombEnable = 1;
		firing();	
		fireEnable = 0;
		firePressCount = 0;
	}
	else{
		if (bombEnable == 1)	
			firing();			
	}
	
	/* Switch between basic and land sea scene. */
	if (landSeaScene == 0)
		basicScene();	
	else	
		landseaScene();		
	
	/* Enable mountains */
	if (mountainOn == 1){
		glPushMatrix();
		glScalef(3.2, 4.5, 1.5);
		glTranslatef(-15.0, 0.0, -45.0);
		drawMountain();
		glPopMatrix();
	}

	/* Enable rainbow effect */
	if (rainbowEnable == 1 && frame_solid_switch == 0){
		rainbow(15.0);
		rainbow(16.0);
		rainbow(17.0);
		rainbow(18.0);
		rainbow(19.0);
		rainbow(20.0);
		rainbow(21.0);
	}

	/* Enable lightning effect */
	if (lightningEnable == 1 && frame_solid_switch == 0)
		lightningEffect();

	/* Enable snowing effect */
	if (snowEnable == 1 && frame_solid_switch == 0)
		snowing();
	else{
		ypos = 0.0;
		wind = 0.0;
		windEnable = 0;
		windPressCount = 0;
	}

	/* swap the drawing buffers */
	glutSwapBuffers();
}

/************************************************************************

Function:		initializeGL

Description:	Initializes the OpenGL rendering context for display.

*************************************************************************/
void initializeGL(void)
{
	/* Define the light color and intensity */
	GLfloat ambientLight[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuseLight[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };

	/* Global ambient light level */
	GLfloat globalAmbientLight[] = { 2.0, 2.0, 2.0, 1.0 };

	/* Set the global ambient light level */
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);

	/* Define the color and intensity for light 0 */
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, diffuseLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, specularLight);

	/* Enable lighting */
	glEnable(GL_LIGHTING);

	/* Enable light 0 */
	glEnable(GL_LIGHT0);

	/* Enable depth testing */
	glEnable(GL_DEPTH_TEST);

	/* make sure the normals are unit vectors */
	glEnable(GL_NORMALIZE);

	/* Turn on smooth line drawing */
	glEnable(GL_LINE_SMOOTH);

	/*  Turn on transparency blending */
	glEnable(GL_BLEND);

	/* Set the blending mode */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Change into projection mode so that we can change the camera properties */
	glMatrixMode(GL_PROJECTION);

	/* Load the identity matrix into the projection matrix */
	glLoadIdentity();

	/* position light 0 */
	glPushMatrix();
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glPopMatrix();

	/* Change into model-view mode so that we can change the object positions */
	glMatrixMode(GL_MODELVIEW);
}

/************************************************************************

Function:		reShape

Description:	Reshape function to handle window resize

*************************************************************************/
void reShape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	currentWidth = w;
	glLoadIdentity();
	if (w <= h)
		gluPerspective(45, (float)w / (float)h, 1, 1000);
	else
		gluPerspective(80, (float)w / (float)h, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

/************************************************************************

Function:		readFile

Description:	Read data from file. File must be placed under the same
folder as the CPP file.

*************************************************************************/
void readFile(){
	FILE *file = fopen("cessna.txt", "r");
	FILE *file2 = fopen("propeller.txt", "r");
	char line[256], *p;
	float x1;
	int s, check = 0, count = 0, countG = 0;

	while (fgets(line, sizeof(line), file)) {
		if (line[0] == 'f'){
			count += 1;
		}
		if (line[0] == 'g'){
			countG += 1;
		}
		p = strtok(line, " ");
		check = 0;
		while (p != NULL)
		{
			if (line[0] == 'f'){
				if (strlen(p) != 1){
					s = atoi(p);
					check += 1;
					if (check == 1){
						f1[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 2){
						f2[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 3){
						f3[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 4){
						f4[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 5){
						f5[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 6){
						f6[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 7){
						f7[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 8){
						f8[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 9){
						f9[count] = s;
					}
					if (check == 10){
						f10[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 11){
						f11[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 12){
						f12[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 13){
						f13[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 14){
						f14[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 15){
						f15[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 16){
						f16[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 17){
						f17[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 18){
						f18[count] = s;
						colorCheck[count] = countG;
					}
				}
			}
			p = strtok(NULL, " ");
		}
	}

	while (fgets(line, sizeof(line), file2)) {
		if (line[0] == 'f'){
			count += 1;
		}
		if (line[0] == 'g'){
			countG += 1;
		}
		p = strtok(line, " ");
		check = 0;
		while (p != NULL)
		{
			if (line[0] == 'f'){
				if (strlen(p) != 1){
					s = atoi(p);
					check += 1;
					if (check == 1){
						f1[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 2){
						f2[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 3){
						f3[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 4){
						f4[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 5){
						f5[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 6){
						f6[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 7){
						f7[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 8){
						f8[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 9){
						f9[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 10){
						f10[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 11){
						f11[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 12){
						f12[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 13){
						f13[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 14){
						f14[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 15){
						f15[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 16){
						f16[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 17){
						f17[count] = s;
						colorCheck[count] = countG;
					}
					if (check == 18){
						f18[count] = s;
						colorCheck[count] = countG;
					}
				}
			}
			p = strtok(NULL, " ");
		}
	}

	fclose(file);
	fclose(file2);

	/* Get vertices from the file */
	ifstream infile("cessna.txt", ios::in);
	char vf;
	float sX, sY, sZ;
	if (!infile)
		cerr << "Cant open " << endl;
	while (infile >> vf >> sX >> sY >> sZ){
		if (vf == 'v'){
			countFile += 1;
			pX[countFile] = sX;
			pY[countFile] = sY;
			pZ[countFile] = sZ;
		}
		
		if (vf == 'n'){
			countNormal += 1;
			pNX[countNormal] = sX;
			pNY[countNormal] = sY;
			pNZ[countNormal] = sZ;
		}
	}
}

/************************************************************************

Function:		Main

Description:	Sets up the openGL rendering context and the windowing
system, then begins the display loop.

*************************************************************************/
void main(int argc, char** argv)
{
	/* Read Enterprise data from file */
	readFile();

	/* Generate snow */
	drawSnow();

	//cloudGenerator();
	lightningGenerator();

	/* Generate three mountains */
	mountainGenerator();
	
	/* Initialize the toolkit */
	glutInit(&argc, argv);

	/* Set display mode */
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	/* Set window size */
	glutInitWindowSize(1000, 800);

	/* Set window position on screen */
	glutInitWindowPosition(100, 150);

	/* Open the screen window */
	glutCreateWindow("Flight Simulator");

	/* Reshape function */
	glutReshapeFunc(reShape);

	/* Register display function */
	glutDisplayFunc(displayFunction);

	/* Register the animation function */
	glutIdleFunc(animation);

	/* Reigster the keyboard function */
	glutKeyboardFunc(keyFunction);

	/* Register the special key function */
	glutSpecialFunc(keyForPlane);

	/* Register the key release function */
	glutSpecialUpFunc(keyUpPlane);

	/* Register mouse function */
	glutPassiveMotionFunc(mouseMovement);

	/* Initialize the rendering context */
	initializeGL();

	/* Set the polygon mode for drawing the sphere */
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	/* Load textures */
	texture1 = LoadTexture("sky08.ppm");
	texture2 = LoadTexture("sea02.ppm");
	texture3 = LoadTexture("mount03.ppm");

	/* Print keyboard controls */ 
	printf("Scene Controls\n");
	printf("------------------------------\n");
	printf("\n");
	printf("f: toggle fullscreen\n");
	printf("w: toggle wire frame \n");
	printf("s: toggle sea & sky\n");
	printf("m: toggle mountains\n");
	printf("t: toggle mountains texture\n");
	printf("b: toggle fog\n");
	printf("o: toggle snow \n");
	printf("d: toggle wind\n");
	printf("l: toggle lightning \n");
	printf("r: toggle rainbow \n");
	printf("g: toggle bombing \n");
	printf("q: exit the program \n");
	
	printf("\n");
	printf("Camera Controls\n");
	printf("------------------------------\n");
	printf("Up      Arrow:      move up\n");
	printf("Down    Arrow:      move down\n");
	printf("Mouse   Right:      move right\n");
	printf("Mouse    Left:      move left\n");
	printf("Page    UP   :      forward\n");
	printf("Page    DOWN :      backward\n");
	
	/* Go into a perpetual loop*/
	glutMainLoop();
}

/**************************************************************************

Function:		LoadTexture

Description:	Load texture from file and process it for texture mappings

***************************************************************************/
GLuint LoadTexture(char *fName){
	/* Initializations */
	int w, h, max;
	int i, j;
	unsigned int r, g, b;
	int k;
	char ch;
	FILE *fp;

	/* Get basic info about this particular texture */
	fp = fopen(fName, "rb");
	fscanf(fp, "P%c\n", &ch);
	if (ch != '3') {
		fprintf(stderr, "Not a valid PPM");
		exit(-1);
	}
	fscanf(fp, "%d", &w);
	fscanf(fp, "%d", &h);
	fscanf(fp, "%d", &max);
	imageWidth = w;
	imageHeight = h;
	Image = (Pixel *)malloc(imageWidth*imageHeight*sizeof(Pixel));

	/* Read texture data from PPM file
	Reference from http://www0.cs.ucl.ac.uk/staff/a.steed/book_tmp/CGVE/code/Lib3D1.0/maintexture.c
	*/
	for (i = 0; i<imageHeight; ++i){
		for (j = 0; j<imageWidth; ++j) {
			fscanf(fp, "%d %d %d", &r, &g, &b);
			k = i*imageWidth + j;
			(*(Image + k))[0] = (GLubyte)r;
			(*(Image + k))[1] = (GLubyte)g;
			(*(Image + k))[2] = (GLubyte)b;
		}
		for (j = imageWidth; j<w; ++j) fscanf(fp, "%c %c %c", &r, &g, &b);
	}
	fclose(fp);

	/* Data structure for storing multiple textures */
	GLuint texture = 0;
	glGenTextures(1, &texture);

	/* Bind texture */
	glBindTexture(GL_TEXTURE_2D, texture);

	/* Enable texture mipmapping*/
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	/* Define information about the skyImage */
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imageWidth, imageHeight, GL_RGB, GL_UNSIGNED_BYTE, Image);

	/* Set up texture environment */
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	/* Return texture ID */
	return texture;
}