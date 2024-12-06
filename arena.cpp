#include "arena.h"

void Arena::LoadArena(const char* svg_file_path) {
    using namespace tinyxml2;

    XMLDocument doc;
    if (doc.LoadFile(svg_file_path) != XML_SUCCESS) {
        printf("Error loading SVG file: %s\n", svg_file_path);
        exit(1);
    }

    XMLElement* root = doc.FirstChildElement("svg");
    if (!root) {
        printf("<svg> element not found in file\n");
        exit(1);
    }

    // Pass trough <rect> and <circle> elements
    for (XMLElement* elem = root->FirstChildElement(); elem; elem = elem->NextSiblingElement()) {
        std::string tag = elem->Name();
        
        if (tag == "rect") {
            const char* fill = elem->Attribute("fill");

            if (fill) {
                std::string fillStr = fill;
                if (fillStr == "blue") {
                    // Arena parameters
                    gWidth = elem->FloatAttribute("width");
                    gHeight = elem->FloatAttribute("height");
                    gX = elem->FloatAttribute("x");
                    gY = elem->FloatAttribute("y");
                    gRed = 0.0f;
                    gGreen = 0.0f;
                    gBlue = 1.0f;

                    printf("Arena: width=%f, height=%f, x=%f, y=%f, red=%f, green=%f, blue=%f\n", gWidth, gHeight, gX, gY, gRed, gGreen, gBlue);

                } else if (fillStr == "black") {
                    // Obstacle parameters
                    GLfloat obstacleX = elem->FloatAttribute("x");
                    GLfloat obstacleY = elem->FloatAttribute("y");
                    GLfloat obstacleWidth = elem->FloatAttribute("width");
                    GLfloat obstacleHeight = elem->FloatAttribute("height");

                    printf("Obstacle: x=%f, y=%f, width=%f, height=%f\n", obstacleX, obstacleY, obstacleWidth, obstacleHeight);

                    gObstacles.push_back(new Obstacle(obstacleX, obstacleY, obstacleWidth, obstacleHeight, 0.0f, 0.0f, 0.0f));
                }
            }
        } else if (tag == "circle") {
            const char* fill = elem->Attribute("fill");

            if (fill) {
                std::string fillStr = fill;
                GLfloat cx = elem->FloatAttribute("cx");
                GLfloat cy = elem->FloatAttribute("cy");
                GLfloat radius = elem->FloatAttribute("r");

                if (fillStr == "green") {
                    // Player
                    printf("Player: cx=%f, cy=%f, radius=%f\n", cx, cy, radius);
                    // player = new Player(cx, cy, radius);
                } else if (fillStr == "red") {
                    // Opponent
                    printf("Opponent: cx=%f, cy=%f, radius=%f\n", cx, cy, radius);
                    // opponents.push_back(new Opponent(cx, cy, radius));
                }
            }
        }
    }

    // if (!player) {
    //     printf("Player (green circle) not found in SVG file.\n");
    //     exit(1);
    // }
}


void Arena::DrawArena() {
    glPushMatrix();
        // Draw arena
        glTranslatef(gX, gY, 0);
        DrawRect(gWidth, gHeight, gRed, gGreen, gBlue);
        glTranslatef(-gX, -gY, 0);

        // Draw obstacles
        for (Obstacle* obstacle : gObstacles) {
            obstacle->Draw();
        }

    glPopMatrix();
}


void Arena::DrawRect(GLfloat width, GLfloat height, GLfloat red, GLfloat green, GLfloat blue) {
    glColor3f(red, green, blue);

    glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f(width, 0);
        glVertex2f(width, height);
        glVertex2f(0, height);
    glEnd();
}