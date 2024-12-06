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
                    // Arena dimensions
                    width = elem->FloatAttribute("width");
                    height = elem->FloatAttribute("height");
                    x = elem->FloatAttribute("x");
                    y = elem->FloatAttribute("y");
                    red = 0.0f;
                    green = 0.0f;
                    blue = 1.0f;

                    printf("Arena: width=%f, height=%f, x=%f, y=%f, red=%f, green=%f, blue=%f\n", width, height, x, y, red, green, blue);

                } else if (fillStr == "black") {
                    // Obstacle
                    GLfloat x = elem->FloatAttribute("x");
                    GLfloat y = elem->FloatAttribute("y");
                    GLfloat obstacleWidth = elem->FloatAttribute("width");
                    GLfloat obstacleHeight = elem->FloatAttribute("height");

                    printf("Obstacle: x=%f, y=%f, width=%f, height=%f\n", x, y, obstacleWidth, obstacleHeight);

                    // obstacles.push_back(new Obstacle(x, y, obstacleWidth, obstacleHeight));
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
    // ...
}