#ifndef OBSTACLE_H
#define OBSTACLE_H


#include <GL/gl.h>
#include <GL/glu.h>


class Obstacle {
    GLfloat gX;
    GLfloat gY;
    GLfloat gWidth;
    GLfloat gHeight;
    GLfloat gRed;
    GLfloat gGreen;
    GLfloat gBlue;


private:
    void DrawRectangle(GLfloat width, GLfloat height, GLfloat red, GLfloat green, GLfloat blue);


public:
    Obstacle(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat red, GLfloat green, GLfloat blue) {
        gX = x;
        gY = y;
        gWidth = width;
        gHeight = height;
        gRed = red;
        gGreen = green;
        gBlue = blue;
    }

    void Draw() {
        DrawRectangle(gWidth, gHeight, gRed, gGreen, gBlue);
    }
};



#endif // OBSTACLE_H