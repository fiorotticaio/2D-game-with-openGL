#include "shot.h"
#include <math.h>

#define MAX_DIST 500


void Shot::DrawShot(GLfloat x, GLfloat y) {
    glPushMatrix();
        glTranslatef(x, y, 0);
        DrawCircle(SHOT_RADIUS, 1.0f, 1.0f, 1.0f);
    glPopMatrix();
}


void Shot::DrawCircle(GLfloat radius, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);

    glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 20) {
            GLfloat angle = 2.0f * M_PI * i / 360;
            GLfloat x = radius * cos(angle);
            GLfloat y = radius * sin(angle);   
            glVertex2f(x, y);
        }
    glEnd();
}


void Shot::Move(GLdouble timeDifference) {
    gX += direction[0] * speed * timeDifference;
    gY += direction[1] * speed * timeDifference;
}


bool Shot::Valid() {
    // Checks if the shot has already traveled a maximum distance
    return sqrt(pow(gX - gXInit, 2) + pow(gY - gYInit, 2)) < MAX_DIST;
}