/*****************************************************************************************/
/******************************* INCLUDES AND DEFINES ************************************/
/*****************************************************************************************/

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "tinyxml2.h"
#include <string>
#include "arena.h"
#include "shot.h"

using namespace tinyxml2;



/*****************************************************************************************/
/*********************************** GLOBAL VARIABLES ************************************/
/*****************************************************************************************/

int keyStatus[256];

// Window dimensions
const GLint Width = 500;
const GLint Height = 500;

// Viewing dimensions
GLfloat ViewingWidth = 0;
GLfloat ViewingHeight = 0;
GLfloat xPositionArena = 0;
GLfloat yPositionArena = 0;

// Components of the virtual world
Arena* arena = NULL;
std::vector<Shot*> shots;

// Flags and aux variables
int animateLegs = 0;
float positionTolerance = 0.5f;
float mouseY = 0.0f;



/*****************************************************************************************/
/************************************ AUX FUNCTIONS **************************************/
/*****************************************************************************************/
void UpdateViewport(GLfloat playerX, GLfloat playerY, 
                    GLfloat arenaX, GLfloat arenaY, 
                    GLfloat arenaWidth, GLfloat arenaHeight, 
                    GLfloat viewingWidth, GLfloat viewingHeight) {
    GLfloat newViewportX, newViewportY;

    GLfloat centeredX = playerX - viewingWidth / 2;

    if (centeredX < arenaX) { // Min limit
        newViewportX = arenaX;
    } else if (centeredX + viewingWidth > arenaX + arenaWidth) { // Max limit
        newViewportX = arenaX + arenaWidth - viewingWidth;
    } else { // Normal case
        newViewportX = centeredX;
    }

    GLfloat centeredY = playerY - viewingHeight / 2;

    if (centeredY < arenaY) { // Min limit
        newViewportY = arenaY;
    } else if (centeredY + viewingHeight > arenaY + arenaHeight) { // Max limit
        newViewportY = arenaY + arenaHeight - viewingHeight;
    } else { // Normal case
        newViewportY = centeredY;
    }

    // Update the viewport
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(newViewportX,                       
            newViewportX + viewingWidth,        
            newViewportY,                       
            newViewportY + viewingHeight,       
            -100,                               
            100);                               
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


bool loadViewportSizeFromSvg(const char* svg_file_path) {
	XMLDocument doc;
    if (doc.LoadFile(svg_file_path) != XML_SUCCESS) {
        printf("Error loading SVG file: %s\n", svg_file_path);
        return false;
    }

    XMLElement* root = doc.FirstChildElement("svg");
    if (!root) {
        printf("<svg> element not found in file\n");
        return false;
    }

    for (XMLElement* elem = root->FirstChildElement("rect"); elem; elem = elem->NextSiblingElement("rect")) {
        const char* fill = elem->Attribute("fill");
        if (fill && std::string(fill) == "blue") {
            if (elem->Attribute("width") && elem->Attribute("height")) {
				ViewingWidth = elem->FloatAttribute("width");
				ViewingHeight = elem->FloatAttribute("height");
				xPositionArena = elem->FloatAttribute("x");
				yPositionArena = elem->FloatAttribute("y");
			} else {
				printf("Width or height attribute missing in blue rect.\n");
				return false;
			}

			// Make the viewing area a square with the smallest dimension
			if (ViewingWidth > ViewingHeight) {
				ViewingWidth = ViewingHeight;
			} else {
				ViewingHeight = ViewingWidth;
			}

            return true;
        }
    }

    printf("Blue rect not found in SVG file: %s\n", svg_file_path);
    return false;
}

void renderScene(void) {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT);
    
	arena->Draw();

	for (Shot* shot : shots) {
		if (shot) shot->Draw();
	}

	// Draw on the frame buffer
	glutSwapBuffers(); // Function suitable for double buffer window
}


void keyPress(unsigned char key, int x, int y) {
	switch (key) {
		case 'a':
		case 'A':
			keyStatus[(int)('a')] = 1;
			break;
		case 'd':
		case 'D':
			keyStatus[(int)('d')] = 1;
			break;
		case 'w':
		case 'W':
			keyStatus[(int)('w')] = 1;
			break;
		case 's':
		case 'S':
			keyStatus[(int)('s')] = 1;
			break;
		case 'f':
		case 'F':
			keyStatus[(int)('f')] = 1;
			break;
		case 'r':
		case 'R':
			keyStatus[(int)('r')] = 1;
			break;
		case 'g':
		case 'G':
			keyStatus[(int)('g')] = 1;
			break;
		case 't':
		case 'T':
			keyStatus[(int)('t')] = 1;
			break;
		case 'h':
		case 'H':
			keyStatus[(int)('h')] = 1;
			break;
		case 'y':
		case 'Y':
			keyStatus[(int)('y')] = 1;
			break;
		case ' ':
			keyStatus[(int)(' ')] = 1;
			break;
		case 27:
			exit(0);
	}

	glutPostRedisplay();
}


void keyUp(unsigned char key, int x, int y) {
	if (key == 'a' || key == 'A' || key == 'd' || key == 'D') {
		animateLegs = 0;
	}
	keyStatus[(int)(key)] = 0;
	glutPostRedisplay();
}


void ResetKeyStatus() {
	// Initialize keyStatus
	int i;
	for(i = 0; i < 256; i++) keyStatus[i] = 0;
}


void init(void) {
	ResetKeyStatus();

	// The color the windows will redraw. Its done to erase the previous frame
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black, no opacity (alpha)

	glMatrixMode(GL_PROJECTION); // Select the projection matrix    
	glOrtho(xPositionArena,                 // X coordinate of left edge             
			xPositionArena + ViewingWidth,  // X coordinate of right edge            
			yPositionArena,                 // Y coordinate of bottom edge             
			yPositionArena + ViewingHeight, // Y coordinate of top edge             
			-100,                           // Z coordinate of the “near” plane            
			100);                           // Z coordinate of the “far” plane
	glMatrixMode(GL_MODELVIEW); // Select the projection matrix    

	glLoadIdentity();
}


void passiveMotion(int x, int y) {
	// Invert the y position
	mouseY = Height - y;
}


void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        shots.push_back(arena->PlayerShoot(ViewingWidth));
    }
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && arena->PlayerLanded()) {
		arena->PlayerJump();
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		arena->SetPlayerYDirection(-1);
	}
}


void idle(void) {
	// for (int i = 0; i < 90000000; i++); // Simulate lower processing

	static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
	GLdouble currentTime, timeDifference;
	currentTime = glutGet(GLUT_ELAPSED_TIME);   // Get the time that has passed since the start of the application
	timeDifference = currentTime - previousTime; // Calculates the elapsed time since the last frame
	previousTime = currentTime;                 // Update the time of the last frame that occurred

	if (keyStatus[(int)('a')]) {
		animateLegs = 1;
		arena->SetPlayerXDirection(-1);
		arena->MovePlayerInX(timeDifference);
	}
	if (keyStatus[(int)('d')]) {
		animateLegs = 1;
		arena->SetPlayerXDirection(1);
		arena->MovePlayerInX(timeDifference);
	}

	UpdateViewport(arena->GetPlayerGx(), arena->GetPlayerGx(), 
				   xPositionArena, yPositionArena,
				   arena->GetWidth(), arena->GetHeight(),
				   ViewingWidth, ViewingHeight);
	
	if (arena->PlayerReachedMaximumJumpHeight()) {
		arena->SetPlayerYDirection(-1);
	}

	arena->RotatePlayerArm(mouseY, Height, timeDifference);
	arena->MovePlayerInY(timeDifference);
	arena->MoveOpponentsInY(timeDifference);
	arena->MoveOpponentsInX(timeDifference);
	arena->MoveOpponentsArms(timeDifference);
	
	for (size_t i = 0; i < shots.size(); ++i) {
        Shot* shot = shots[i];
        if (shot) {
            shot->Move(timeDifference);

			bool shotDeleted = false;

			if (arena->ObstaclesCollidesWithShot(shot)) {
				delete shot;
				shots.erase(shots.begin() + i);
				i--;
				shotDeleted = true;
			}

			if (shotDeleted) continue;

			if (arena->OpponentsCollidesWithShot(shot)) {
				delete shot;
				shots.erase(shots.begin() + i);
				i--;
				shotDeleted = true;
			}

			if (shotDeleted) continue;

            if (!shot->Valid()) {
                delete shot;
                shots.erase(shots.begin() + i);
                i--;
            }
        }
    }

	if (animateLegs) {
		static int frontThighAngleDir = 1;
		static int backThighAngleDir = 1;
		if      (arena->GetPlayerFrontThighAngle() > -140) frontThighAngleDir *= -1;
		else if (arena->GetPlayerFrontThighAngle() < -220) frontThighAngleDir *= -1;
		if      (arena->GetPlayerBackThighAngle()  > -140) backThighAngleDir  *= -1;
		else if (arena->GetPlayerBackThighAngle()  < -220) backThighAngleDir  *= -1;
		arena->RotatePlayerFrontThigh(frontThighAngleDir);
		arena->RotatePlayerBackThigh(backThighAngleDir);
	}
	
	glutPostRedisplay();
}



/*****************************************************************************************/
/************************************* MAIN FUNCTION *************************************/
/*****************************************************************************************/

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s <svg file>\n", argv[0]);
		exit(1);
	}

	if (!loadViewportSizeFromSvg(argv[1])) {
		exit(1);
	}

	// Initialize the arena
	arena = new Arena(argv[1]);

	// Initialize openGL with Double buffer and RGB color without transparency.
	// Its interesting to try GLUT_SINGLE instead of GLUT_DOUBLE.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// Create the window
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(150, 50);
	glutCreateWindow("Trabalho 2D");

	// Define callbacks
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyPress);
	glutIdleFunc(idle);
	glutKeyboardUpFunc(keyUp);
	glutPassiveMotionFunc(passiveMotion);
	glutMouseFunc(mouseClick);
	
	init();

	glutMainLoop();

	return 0;
}