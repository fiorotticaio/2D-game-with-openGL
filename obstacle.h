#ifndef OBSTACLE_H
#define OBSTACLE_H


#include <GL/gl.h>
#include <GL/glu.h>


class Obstacle {
    GLfloat x;
    GLfloat y;

    GLfloat width;
    GLfloat height;
    
    GLfloat red;
    GLfloat green;
    GLfloat blue;


private:
    void DrawObstacle(GLfloat x, GLfloat y);


public:
    Obstacle(GLfloat x, GLfloat y, GLfloat width, GLfloat height, GLfloat red, GLfloat green, GLfloat blue) {
        x = x;
        y = y;
        width = width;
        height = height;
        red = red;
        green = green;
        blue = blue;
    }

    void Draw() {
        DrawObstacle(x, y);
    }
};



#endif // OBSTACLE_H