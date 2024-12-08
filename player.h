#ifndef PLAYER_H
#define PLAYER_H



#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>


class Player {
    GLfloat gX;
    GLfloat gY;

    GLfloat gRed;
    GLfloat gGreen;
    GLfloat gBlue;

    GLfloat gBaseCircleRadius; // Read in the svg file
    GLfloat gHeadCircleRadius;
    GLfloat gHeadAngle;

    GLfloat gBodyWidth;
    GLfloat gBodyHeight;
    // Invisible rectangle for collision detection
    GLfloat gInvisibleReactWidth;
    GLfloat gInvisibleReactHeight;

    GLfloat gArmWidth;
    GLfloat gArmHeight;
    GLfloat gArmAngle;

    GLfloat gThighWidth;
    GLfloat gThighHeight;
    GLfloat gThighAngle;

    GLfloat gLegWidth;
    GLfloat gLegHeight;
    GLfloat gLegAngle;

    GLfloat gSpeed;
    GLfloat gDirection;


private:
    void DrawPlayer();
    void DrawCircle();
    

public:
    Player(GLfloat x, GLfloat y, GLfloat red, GLfloat green, GLfloat blue, GLfloat baseCircleRadius) {
        gX = x;
        gY = y;
        gRed = red;
        gGreen = green;
        gBlue = blue;
        gBaseCircleRadius = baseCircleRadius;
        gHeadCircleRadius = 5.0f;
        gHeadAngle = 0.0f;
        gBodyWidth = 5.0f;
        gBodyHeight = 10.0f;
        gInvisibleReactWidth = 5.0f;
        gInvisibleReactHeight = gBodyHeight + 2 * gHeadCircleRadius;
        gArmWidth = 2.0f;
        gArmHeight = 4.0f;
        gArmAngle = 45;
        gThighWidth = 3.0f;
        gThighHeight = 6.0f;
        gThighAngle = 290;
        gLegWidth = 3.0f;
        gLegHeight = 7.0f;
        gLegAngle = 280;
        gSpeed = 10.0f;
        gDirection = 1.0f;
    }

    void Draw() {
        DrawPlayer();
    }

    void MoveEmX(GLfloat dx);
    void MoveEmY(GLfloat dy);
    GLfloat GetGx();

};



#endif // PLAYER_H