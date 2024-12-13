#include "player.h"

void Player::DrawPlayer() {
    glPushMatrix();
        // Draw the body
        glTranslatef(gX, gY, 0);
        DrawRect(gBodyWidth, gBodyHeight, 0.0f, 1.0f, 0.0f);

        DrawHeadAndArm();

        DrawFrontLeg();

        DrawBackLeg();
    glPopMatrix();
}

void Player::DrawHeadAndArm() {
    glPushMatrix();
        // Draw the head
        glTranslatef(0, gBodyHeight + gHeadCircleRadius, 0);
        DrawCircle(gHeadCircleRadius, 0.0f, 1.0f, 0.0f);

        // Draw the arm
        glTranslatef(0, -(gHeadCircleRadius + (gBodyHeight/2)), 0);
        glRotatef(gArmAngle * gXDirection, 0, 0, 1);
        DrawRect(gArmWidth, gArmHeight, 1.0f, 1.0f, 0.0f);
    glPopMatrix();
}

void Player::DrawFrontLeg() {
    glPushMatrix();
        // Draw the front thigh
        glRotatef(gFrontThighAngle * gXDirection, 0, 0, 1);
        DrawRect(gThighWidth, gThighHeight, 1.0f, 0.0f, 0.0f);

        // // Draw the front leg
        glTranslatef(0, gThighHeight, 0);
        glRotatef(gFrontShinAngle * gXDirection, 0, 0, 1);
        DrawRect(gShinWidth, gShinHeight, 1.0f, 0.0f, 0.0f);
    glPopMatrix();
}

void Player::DrawBackLeg() {
    glPushMatrix();
        // Draw the back thigh
        glRotatef(gBackThighAngle * gXDirection, 0, 0, 1);
        DrawRect(gThighWidth, gThighHeight, 1.0f, 0.0f, 0.0f);

        // Draw the back leg
        glTranslatef(0, gThighHeight, 0);
        glRotatef(gBackShinAngle * gXDirection, 0, 0, 1);
        DrawRect(gShinWidth, gShinHeight, 1.0f, 0.0f, 0.0f);
    glPopMatrix();
}

void Player::DrawRect(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);

    glBegin(GL_POLYGON);
        glVertex2f(-width / 2, 0);
        glVertex2f(width / 2, 0);
        glVertex2f(width / 2, height);
        glVertex2f(-width / 2, height);
    glEnd();
}

void Player::DrawCircle(GLfloat radius, GLfloat R, GLfloat G, GLfloat B) {
    const int numSegments = 100;
    const GLfloat angleStep = 2.0f * M_PI / numSegments;

    glColor3f(R, G, B);

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f);
        for (int i = 0; i <= numSegments; ++i) {
            GLfloat angle = i * angleStep;
            GLfloat x = radius * cos(angle);
            GLfloat y = radius * sin(angle);
            glVertex2f(x, y);
        }
    glEnd();
}

GLfloat Player::GetGx() {
    return gX;
}

GLfloat Player::GetGy() {
    return gY;
}

void Player::MoveInX(GLfloat dx, GLfloat minPlayerPositionX, GLfloat maxPlayerPositionX, GLdouble timeDifference) {
    if (gX + dx * timeDifference * gXDirection >= minPlayerPositionX && 
        gX + dx * timeDifference * gXDirection <= maxPlayerPositionX) {
        gX += dx * timeDifference * gXDirection;
    }
}

void Player::MoveInY(GLfloat dy, GLfloat minPlayerPositionY, GLfloat maxPlayerPositionY, GLdouble timeDifference) {
    if (gY + dy * timeDifference * gYDirection >= minPlayerPositionY && 
        gY + dy * timeDifference * gYDirection <= maxPlayerPositionY) {
        gY += dy * timeDifference * gYDirection;
    }
}

void Player::RotateArm(GLfloat y, GLfloat windowHeight) {
    GLfloat mouseMin = 0;
    GLfloat mouseMax = windowHeight - mouseMin;

    GLfloat angleMax = -45.0f;
    GLfloat angleMin = -135.0f;

    gArmAngle = angleMin + ((y - mouseMin) / (mouseMax - mouseMin)) * (angleMax - angleMin);
    
    // gArmAngle *= gArmSpeed;

    if      (gArmAngle > angleMax) gArmAngle = angleMax;
    else if (gArmAngle < angleMin) gArmAngle = angleMin;
}

void Player::SetXDirection(GLint xDirection) {
    gXDirection = xDirection;
}

void Player::SetYDirection(GLint yDirection) {
    gYDirection = yDirection;
}