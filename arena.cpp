#include "arena.h"

GLfloat MapYCoordinate(GLfloat yRead, GLfloat yPositionArena, GLfloat ViewingHeight) {
    // The y coordenates of the svg are inverted
    return yPositionArena + ViewingHeight - (yRead - yPositionArena);
}

void Arena::LoadArena(const char* svg_file_path, GLfloat ViewingWidth, GLfloat ViewingHeight) {
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

                } else if (fillStr == "black") {
                    // Obstacle parameters
                    GLfloat obstacleX = elem->FloatAttribute("x");
                    GLfloat obstacleY = elem->FloatAttribute("y");
                    GLfloat obstacleWidth = elem->FloatAttribute("width");
                    GLfloat obstacleHeight = elem->FloatAttribute("height");

                    obstacleY = MapYCoordinate(obstacleY, gY, ViewingHeight);

                    gObstacles.push_back(new Obstacle(obstacleX, obstacleY, obstacleWidth, obstacleHeight));
                }
            }
        } else if (tag == "circle") {
            const char* fill = elem->Attribute("fill");

            if (fill) {
                std::string fillStr = fill;
                GLfloat cx = elem->FloatAttribute("cx");
                GLfloat cy = elem->FloatAttribute("cy");
                GLfloat radius = elem->FloatAttribute("r");

                cy = MapYCoordinate(cy, gY, ViewingHeight);

                if (fillStr == "green") {
                    gPlayer = new Player(cx, cy, 0.0f, 1.0f, 0.0f, radius);
                } else if (fillStr == "red") {
                    // Opponent
                    opponents.push_back(new Opponent(cx, cy, radius));
                }
            }
        }
    }

    if (!gPlayer) {
        printf("Player (green circle) not found in SVG file.\n");
        exit(1);
    }
}


void Arena::DrawArena() {
    glPushMatrix();
        // Draw arena background
        glTranslatef(gX, gY, 0);
        DrawRect();
    glPopMatrix();

    for (Obstacle* obstacle : gObstacles) {
        obstacle->Draw();
    }

    gPlayer->Draw();
}


void Arena::DrawRect() {
    glColor3f(gRed, gGreen, gBlue);

    glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f(gWidth, 0);
        glVertex2f(gWidth, gHeight);
        glVertex2f(0, gHeight);
    glEnd();
}

GLfloat Arena::GetWidth() {
    return gWidth;
}

GLfloat Arena::GetPlayerGx() {
    return gPlayer->GetGx();
}

void Arena::MovePlayerEmX(GLfloat dx) {
    gPlayer->MoveEmX(dx, gX, gX + gWidth);
}

void Arena::MovePlayerEmY(GLfloat dy) {
    gPlayer->MoveEmY(dy);
}