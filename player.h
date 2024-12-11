#ifndef PLAYER_H
#define PLAYER_H



#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>


class Player {
    GLfloat gX;
    GLfloat gY;

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
    void DrawCircle(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
    void DrawRect(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B);
    

public:
    Player(GLfloat x, GLfloat y, GLfloat baseCircleRadius) {
        gX = x;
        gY = y;
        gBaseCircleRadius = 40;
        gHeadCircleRadius = ((float) 22 / (float) 172) * gBaseCircleRadius;
        gBodyHeight = ((float) 53 / 172) * gBaseCircleRadius;
        gBodyWidth = (float) gBodyHeight / (float) 2;
        gInvisibleReactHeight = 2 * gBaseCircleRadius;
        gInvisibleReactWidth = gBodyWidth;
        gArmHeight = ((float) 57 / (float) 172) * gBaseCircleRadius;
        gArmWidth = (float) gArmHeight / (float) 6;
        gArmAngle = -90.0f;
        gThighHeight = ((float) 47 / (float) 172) * gBaseCircleRadius;
        gThighWidth = (float) gThighHeight / (float) 6;
        gThighAngle = 320.0f;
        gLegHeight = ((float) 50 / (float) 172) * gBaseCircleRadius;
        gLegWidth = (float) gLegHeight / (float)  6;
        gLegAngle = 280.0f;
        gSpeed = 10;
        gDirection = 1.0f;
    }

    void Draw() {
        DrawPlayer();
    }

    GLfloat GetGx();
    GLfloat GetGy();
    void MoveEmX(GLfloat dx, GLfloat minPlayerPositionX, GLfloat maxPlayerPositionX);
    void MoveEmY(GLfloat dy, GLfloat minPlayerPositionY, GLfloat maxPlayerPositionY);

};



#endif // PLAYER_H