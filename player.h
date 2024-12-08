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
    Player(GLfloat x, GLfloat y, GLfloat baseCircleRadius) {
        gX = x;
        gY = y;
        gRed = 0.0f;
        gGreen = 1.0f;
        gBlue = 0.0f;
        gBaseCircleRadius = baseCircleRadius;
        gHeadCircleRadius = (22/172) * gBaseCircleRadius;
        gBodyHeight = (53/172) * gBaseCircleRadius;
        gBodyWidth = gBodyHeight / 2;
        gInvisibleReactHeight = 2 * gBaseCircleRadius;
        gInvisibleReactWidth = gBodyWidth;
        gArmHeight = (57/172) * gBaseCircleRadius;
        gArmWidth = gArmHeight / 6;
        gArmAngle = 45.0f;
        gThighHeight = (47/172) * gBaseCircleRadius;
        gThighWidth = gThighHeight / 6;
        gThighAngle = 320.0f;
        gLegHeight = (50/172) * gBaseCircleRadius;
        gLegWidth = gLegHeight / 6;
        gLegAngle = 280.0f;
        gSpeed = 10;
        gDirection = 1.0f;
    }

    void Draw() {
        DrawPlayer();
    }

    void MoveEmX(GLfloat dx, GLfloat minPlayerPositionX, GLfloat maxPlayerPositionX);
    void MoveEmY(GLfloat dy, GLfloat minPlayerPositionY, GLfloat maxPlayerPositionY);
    GLfloat GetGx();

};



#endif // PLAYER_H