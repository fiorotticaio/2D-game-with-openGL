#ifndef SHOT_H
#define SHOT_H



#include <GL/gl.h>
#include <GL/glu.h>


class Shot {
    GLfloat xInit; 
    GLfloat yInit;

    GLfloat x; 
    GLfloat y;

    GLfloat speed;
    GLfloat direction[2];


private:
    void DrawShot(GLfloat x, GLfloat y);


public:
    Shot(GLfloat xInit, GLfloat yInit, GLfloat speed, GLfloat direction[2]) {
        xInit = xInit;
        yInit = yInit;
        x = xInit;
        y = yInit;
        speed = speed;
        direction = direction;
    }

    void Draw() {
        DrawShot(x, y);
    }
};



#endif // SHOT_H