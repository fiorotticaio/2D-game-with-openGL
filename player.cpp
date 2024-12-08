#include "player.h"

void Player::DrawPlayer() {
    glPushMatrix();
        glTranslatef(gX, gY, 0);
        DrawCircle();
    glPopMatrix();
}

void Player::DrawCircle() {
    const int numSegments = 100;
    const GLfloat angleStep = 2.0f * M_PI / numSegments;

    glColor3f(gRed, gGreen, gBlue);

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f);
        for (int i = 0; i <= numSegments; ++i) {
            GLfloat angle = i * angleStep;
            GLfloat x = gBaseCircleRadius * cos(angle);
            GLfloat y = gBaseCircleRadius * sin(angle);
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
