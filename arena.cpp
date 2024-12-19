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
                    gPlayer = new Player(cx, cy, radius);
                } else if (fillStr == "red") {
                    gOpponents.push_back(new Opponent(cx, cy, radius));
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
        DrawRect(gWidth, gHeight, gRed, gGreen, gBlue);
    glPopMatrix();

    for (Obstacle* obstacle : gObstacles) {
        obstacle->Draw();
    }

    gPlayer->Draw();

    for (Opponent* opponent : gOpponents) {
        opponent->Draw();
    }
}


void Arena::DrawRect(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);

    // The coordenates givem in the svg file are the left bottom corner of the arena
    glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f(width, 0);
        glVertex2f(width, height);
        glVertex2f(0, height);
    glEnd();
}


GLfloat Arena::GetWidth() {
    return gWidth;
}


GLfloat Arena::GetHeight() {
    return gHeight;
}


GLfloat Arena::GetPlayerGx() {
    return gPlayer->GetGx();
}


GLfloat Arena::GetPlayerGy() {
    return gPlayer->GetGy();
}


void Arena::MovePlayerInX(GLdouble timeDifference) {
    for (Obstacle* obstacle : gObstacles) {
        if (gPlayer->CollidesWithObstacle(obstacle, gPlayer->GetXSpeed(), 0)) {
            if (gPlayer->LandedInObstacle(obstacle, 0, gPlayer->GetYSpeed())) {
                continue;
            }
            return;
        }
    }

    for (Opponent* opponent : gOpponents) {
        if (gPlayer->CollidesWithOpponent(opponent, gPlayer->GetXSpeed(), 0)) {
            if (gPlayer->LandedInOpponent(opponent, 0, gPlayer->GetYSpeed())) {
                continue;
            }
            return;
        }
    }

    gPlayer->MoveInX(gX, gX + gWidth, timeDifference);
}


void Arena::MovePlayerInY(GLdouble timeDifference) {
    for (Obstacle* obstacle : gObstacles) {
        if (gPlayer->CollidesWithObstacle(obstacle, 0, gPlayer->GetYSpeed())) {
            return;
        }
    }

    for (Opponent* opponent : gOpponents) {
        if (gPlayer->CollidesWithOpponent(opponent, 0, gPlayer->GetYSpeed())) {
            return;
        }
    }

    gPlayer->MoveInY(gY, gY + gHeight, timeDifference);
}


void Arena::RotatePlayerArm(GLfloat y, GLfloat WindowHeight) {
    gPlayer->RotateArm(y, WindowHeight);
}


void Arena::SetPlayerXDirection(GLint xDirection) {
    gPlayer->SetXDirection(xDirection);
}


void Arena::SetPlayerYDirection(GLint yDirection) {
    gPlayer->SetYDirection(yDirection);
}


GLfloat Arena::GetPlayerFrontThighAngle() {
    return gPlayer->GetFrontThighAngle();
}


GLfloat Arena::GetPlayerBackThighAngle() {
    return gPlayer->GetBackThighAngle();
}


GLfloat Arena::GetPlayerFrontShinAngle() {
    return gPlayer->GetFrontShinAngle();
}


GLfloat Arena::GetPlayerBackShinAngle() {
    return gPlayer->GetBackShinAngle();
}


void Arena::RotatePlayerFrontThigh(GLfloat dAngle) {
    gPlayer->RotateFrontThigh(dAngle * gPlayer->GetXSpeed());
}


void Arena::RotatePlayerBackThigh(GLfloat dAngle) {
    gPlayer->RotateBackThigh(dAngle * gPlayer->GetXSpeed());
}


void Arena::RotatePlayerFrontShin(GLfloat dAngle) {
    gPlayer->RotateFrontShin(dAngle * gPlayer->GetXSpeed());
}


void Arena::RotatePlayerBackShin(GLfloat dAngle) {
    gPlayer->RotateBackShin(dAngle * gPlayer->GetXSpeed());
}


void Arena::SetPlayerFrontShinAngle(GLfloat angle) {
    gPlayer->SetFrontShinAngle(angle);
}


void Arena::SetPlayerBackShinAngle(GLfloat angle) {
    gPlayer->SetBackShinAngle(angle);
}


Shot* Arena::PlayerShoot(GLfloat maxDist) {
    return gPlayer->Shoot(maxDist);
}


GLint Arena::GetPlayerXDirection() {
    return gPlayer->GetXDirection();
}


GLint Arena::GetPlayerYDirection() {
    return gPlayer->GetYDirection();
}


void Arena::PlayerJump() {
    gPlayer->Jump();
}


GLfloat Arena::GetPlayerMaxJumpHeight() {
    return gPlayer->GetMaxJumpHeight();
}


GLfloat Arena::GetPlayerJumpHeight() {
    return gPlayer->GetJumpHeight();
}


GLfloat Arena::GetPlayerThighHeight() {
    return gPlayer->GetThighHeight();
}


GLfloat Arena::GetPlayerShinHeight() {
    return gPlayer->GetShinHeight();
}


bool Arena::PlayerReachedMaximumJumpHeight() {
    return gPlayer->ReachedMaximumJumpHeight();
}


bool Arena::PlayerLanded() {
    if (gPlayer->GetYDirection() == 1) return false; // If the player is still going up, it hasn't landed yet

    if (gPlayer->CollidedWithGround(gY, gPlayer->GetYSpeed())) {
        return true;
    }
    
    for (Obstacle* obstacle : gObstacles) {
        if (gPlayer->LandedInObstacle(obstacle, 0, gPlayer->GetYSpeed())) {
            return true;
        }
    }

    for (Opponent* opponent : gOpponents) {
        if (gPlayer->LandedInOpponent(opponent, 0, gPlayer->GetYSpeed())) {
            return true;
        }
    }

    return false;
}


std::vector<Obstacle*> Arena::GetObstacles() {
    return gObstacles;
}