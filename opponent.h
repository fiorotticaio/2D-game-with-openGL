#ifndef OPPONENT_H
#define OPPONENT_H



#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>


class Opponent {
    GLfloat gX;
    GLfloat gY;

    GLfloat gRed;
    GLfloat gGreen;
    GLfloat gBlue;

    GLfloat gBaseCircleRadius; // Read in the svg file
    GLfloat gHeadCircleRadius;

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
    void DrawOpponent();
    void DrawCircle();
    

public:
    Opponent(GLfloat x, GLfloat y, GLfloat baseCircleRadius) {
        gX = x;
        gY = y;
        gRed = 1.0f;
        gGreen = 0.0f;
        gBlue = 0.0f;
                gBaseCircleRadius = baseCircleRadius;
        gHeadCircleRadius = ((float) 22 / (float) 172) * gBaseCircleRadius;
        gBodyHeight = ((float) 53 / 172) * gBaseCircleRadius;
        gBodyWidth = (float) gBodyHeight / (float) 2;
        gInvisibleReactHeight = 2 * gBaseCircleRadius;
        gInvisibleReactWidth = gBodyWidth;
        gArmHeight = ((float) 57 / (float) 172) * gBaseCircleRadius;
        gArmWidth = (float) gArmHeight / (float) 6;
        gArmAngle = 45.0f;
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
        DrawOpponent();
    }

};



#endif // OPPONENT_H