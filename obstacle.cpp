#include "obstacle.h"

void Obstacle::DrawRectangle(GLfloat width, GLfloat height, GLfloat red, GLfloat green, GLfloat blue) {
    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
        glVertex2f(-width/2, 0);
        glVertex2f(width/2, 0);
        glVertex2f(width/2, height);
        glVertex2f(-width/2, height);
    glEnd();
}