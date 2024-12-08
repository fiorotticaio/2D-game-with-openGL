#include "opponent.h"

void Opponent::DrawOpponent() {
    glPushMatrix();
        glTranslatef(gX, gY, 0);
        DrawCircle();
    glPopMatrix();
}

void Opponent::DrawCircle() {
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