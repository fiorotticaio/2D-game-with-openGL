#include "obstacle.h"

void Obstacle::DrawObstacle() {
    glPushMatrix();
        glTranslatef(gX, gY, 0);
        DrawReact(gWidth, gHeight, gRed, gGreen, gBlue);
    glPopMatrix();
}

void Obstacle::DrawReact(GLfloat width, GLfloat height, GLfloat red, GLfloat green, GLfloat blue) {
    glColor3f(red, green, blue);

    glBegin(GL_POLYGON);
        glVertex2f(0, 0);
        glVertex2f(width, 0);
        glVertex2f(width, height);
        glVertex2f(0, height);
    glEnd();
}