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
        glRotatef(gArmAngle, 0, 0, 1);
        DrawRect(gArmWidth, gArmHeight, 1.0f, 1.0f, 0.0f);
    glPopMatrix();
}

void Player::DrawFrontLeg() {
    glPushMatrix();
        // Draw the front thigh
        glRotatef(gFrontThighAngle, 0, 0, 1);
        DrawRect(gThighWidth, gThighHeight, 1.0f, 0.0f, 0.0f);

        // // Draw the front leg
        glTranslatef(0, gThighHeight, 0);
        glRotatef(gFrontShinAngle, 0, 0, 1);
        DrawRect(gShinWidth, gShinHeight, 1.0f, 0.0f, 0.0f);
    glPopMatrix();
}

void Player::DrawBackLeg() {
    glPushMatrix();
        // Draw the back thigh
        glRotatef(gBackThighAngle, 0, 0, 1);
        DrawRect(gThighWidth, gThighHeight, 1.0f, 0.0f, 0.0f);

        // Draw the back leg
        glTranslatef(0, gThighHeight, 0);
        glRotatef(gBackShinAngle, 0, 0, 1);
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

void Player::MoveEmX(GLfloat dx, GLfloat minPlayerPositionX, GLfloat maxPlayerPositionX) {
    if (gX + dx >= minPlayerPositionX && gX + dx <= maxPlayerPositionX) {
        gX += dx;
    }
}

void Player::MoveEmY(GLfloat dy, GLfloat minPlayerPositionY, GLfloat maxPlayerPositionY) {
    if (gY + dy >= minPlayerPositionY && gY + dy <= maxPlayerPositionY) {
        gY += dy;
    }
}
