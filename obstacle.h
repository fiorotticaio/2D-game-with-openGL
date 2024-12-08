#ifndef OBSTACLE_H
#define OBSTACLE_H


#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdio>


class Obstacle {
    GLfloat gX;
    GLfloat gY;

    GLfloat gWidth;
    GLfloat gHeight;
    
    GLfloat gRed;
    GLfloat gGreen;
    GLfloat gBlue;


private:
    void DrawObstacle();
    void DrawReact();


public:
    Obstacle(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
        gX = x;
        gY = y;
        gWidth = width;
        gHeight = height;
        gRed = 0.0f;
        gGreen = 0.0f;
        gBlue = 0.0f;
    }

    void Draw() {
        DrawObstacle();
    }
};



#endif // OBSTACLE_H