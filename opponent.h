#ifndef OPPONENT_H
#define OPPONENT_H



#include <GL/gl.h>
#include <GL/glu.h>


class Opponent {
    GLfloat x;
    GLfloat y;

    GLfloat red;
    GLfloat green;
    GLfloat blue;

    GLfloat baseCircleRadius; // Read in the svg file
    GLfloat headCircleRadius;

    GLfloat bodyWidth;
    GLfloat bodyHeight;
    // Invisible rectangle for collision detection
    GLfloat invisibleReactWidth;
    GLfloat invisibleReactHeight;

    GLfloat armWidth;
    GLfloat armHeight;
    GLfloat armAngle;

    GLfloat thighWidth;
    GLfloat thighHeight;
    GLfloat thighAngle;

    GLfloat legWidth;
    GLfloat legHeight;
    GLfloat legAngle;

    GLfloat speed;
    GLfloat direction;


private:
    void DrawOpponent(GLfloat x, GLfloat y);
    

public:
    Opponent(GLfloat x, GLfloat y, GLfloat red, GLfloat green, GLfloat blue, 
                   GLfloat baseCircleRadius, GLfloat headCircleRadius, 
                   GLfloat bodyWidth, GLfloat bodyHeight, 
                   GLfloat invisibleReactWidth, GLfloat invisibleReactHeight, 
                   GLfloat armWidth, GLfloat armHeight, GLfloat armAngle, 
                   GLfloat thighWidth, GLfloat thighHeight, GLfloat thighAngle, 
                   GLfloat legWidth, GLfloat legHeight, GLfloat legAngle, 
                   GLfloat speed, GLfloat direction) {
        x = x;
        y = y;
        red = red;
        green = green;
        blue = blue;
        baseCircleRadius = baseCircleRadius;
        headCircleRadius = headCircleRadius;
        bodyWidth = bodyWidth;
        bodyHeight = bodyHeight;
        invisibleReactWidth = invisibleReactWidth;
        invisibleReactHeight = invisibleReactHeight;
        armWidth = armWidth;
        armHeight = armHeight;
        armAngle = armAngle;
        thighWidth = thighWidth;
        thighHeight = thighHeight;
        thighAngle = thighAngle;
        legWidth = legWidth;
        legHeight = legHeight;
        legAngle = legAngle;
        speed = speed;
        direction = direction;
    }

    void Draw() {
        DrawOpponent(x, y);
    }

};



#endif // OPPONENT_H