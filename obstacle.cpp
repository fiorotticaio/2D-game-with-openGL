#include "obstacle.h"

void Obstacle::DrawObstacle() {
    glPushMatrix();
        glTranslatef(gX, gY, 0);
        DrawReact();
    glPopMatrix();
}

void Obstacle::DrawReact() {
    glColor3f(gRed, gGreen, gBlue);

    // The coordenates givem in the svg file are the left top corner of the rectangle
    glBegin(GL_POLYGON);
        glVertex2f(0, -gHeight);
        glVertex2f(gWidth, -gHeight);
        glVertex2f(gWidth, 0);
        glVertex2f(0, 0);
    glEnd();
}