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

using namespace tinyxml2;

#define INC_KEYIDLE 0.3



/*****************************************************************************************/
/*********************************** GLOBAL VARIABLES ************************************/
/*****************************************************************************************/

int keyStatus[256];

// Window dimensions
const GLint Width = 500;
const GLint Height = 500;

// Viewing dimensions
GLint ViewingWidth = 0;
GLint ViewingHeight = 0;

// Components of the virtual world
Arena* arena = NULL;



/*****************************************************************************************/
/************************************ AUX FUNCTIONS **************************************/
/*****************************************************************************************/

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
    
	// arena->Draw();

	// Draw the new frame of the game
	glutSwapBuffers(); 
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


void keyup(unsigned char key, int x, int y) {
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
	glOrtho(-(ViewingWidth/2),   // X coordinate of left edge             
			(ViewingWidth/2),   // X coordinate of right edge            
			-(ViewingHeight/2),  // Y coordinate of bottom edge             
			(ViewingHeight/2),  // Y coordinate of top edge             
			-100,                // Z coordinate of the “near” plane            
			100);                // Z coordinate of the “far” plane
	glMatrixMode(GL_MODELVIEW);  // Select the projection matrix    

	glLoadIdentity();
}

void idle(void) {
	// for (int i = 0; i < 90000000; i++); // Simulate lower processing

	static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
	GLdouble currentTime, timeDiference;
	currentTime = glutGet(GLUT_ELAPSED_TIME);   // Get the time that has passed since the start of the application
	timeDiference = currentTime - previousTime; // Calculates the elapsed time since the last frame
	previousTime = currentTime;                 // Update the time of the last frame that occurred

	double inc = INC_KEYIDLE;

	// Treat keyPress
	if (keyStatus[(int)('a')]) {
		// Do something
	}
	// ...

	
	
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
	glutKeyboardUpFunc(keyup);
	
	init();

	glutMainLoop();

	return 0;
}