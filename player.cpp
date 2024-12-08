#include "player.h"

void Player::DrawPlayer() {
    glPushMatrix();
        // Draw the body
        glTranslatef(gX, gY, 0);
        DrawRect();

        // Draw the head
        glTranslatef(0, gBodyHeight + gHeadCircleRadius, 0);
        DrawCircle();
    glPopMatrix();
}

void Player::DrawRect() {
    glColor3f(gRed, gGreen, gBlue);

    glBegin(GL_POLYGON);
        glVertex2f(-gBodyWidth / 2, 0);
        glVertex2f(gBodyWidth / 2, 0);
        glVertex2f(gBodyWidth / 2, gBodyHeight);
        glVertex2f(-gBodyWidth / 2, gBodyHeight);
    glEnd();
}

void Player::DrawCircle() {
    const int numSegments = 100;
    const GLfloat angleStep = 2.0f * M_PI / numSegments;

    glColor3f(gRed, gGreen, gBlue);

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f);
        for (int i = 0; i <= numSegments; ++i) {
            GLfloat angle = i * angleStep;
            GLfloat x = gHeadCircleRadius * cos(angle);
            GLfloat y = gHeadCircleRadius * sin(angle);
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
