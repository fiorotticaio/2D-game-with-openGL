#ifndef SHOT_H
#define SHOT_H



#include <GL/gl.h>
#include <GL/glu.h>

#define SHOT_RADIUS 5


class Shot {
    GLfloat gXInit; 
    GLfloat gYInit;

    GLfloat gX; 
    GLfloat gY;

    GLfloat gSpeed;
    GLfloat gDirection[2];


private:
    void DrawShot(GLfloat x, GLfloat y);
    void DrawCircle(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);


public:
    Shot(GLfloat gXInit, GLfloat gYInit, GLfloat* d) {
        gXInit = gXInit;
        gYInit = gYInit;
        gX = gXInit;
        gY = gYInit;
        gSpeed = 1;
        gDirection[0] = d[0];
        gDirection[1] = d[1];
    }

    void Draw() {
        DrawShot(gX, gY);
    }

    void Move(GLdouble timeDifference);
    bool Valid();
    void GetPos(GLfloat &xOut, GLfloat &yOut) {
        xOut = gX;
        yOut = gY;
    }	
};



#endif // SHOT_H