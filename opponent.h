#ifndef OPPONENT_H
#define OPPONENT_H



#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>


class Opponent {
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
    GLfloat gArmSpeed;

    GLfloat gThighWidth;
    GLfloat gThighHeight;
    GLfloat gFrontThighAngle;
    GLfloat gBackThighAngle;

    GLfloat gShinWidth;
    GLfloat gShinHeight;
    GLfloat gFrontShinAngle;
    GLfloat gBackShinAngle;

    GLfloat gSpeed;
    GLint gDirection; // 1 for right (front), -1 for left (back)


private:
    void DrawOpponent();
    void DrawCircle(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
    void DrawRect(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B);
    void DrawHeadAndArm();
    void DrawFrontLeg();
    void DrawBackLeg();
    

public:
    Opponent(GLfloat x, GLfloat y, GLfloat baseCircleRadius) {
        gX = x;
        gY = y;
        gBaseCircleRadius = baseCircleRadius;
        gHeadCircleRadius = ((float) 22 / (float) 172) * gBaseCircleRadius;
        gBodyHeight = ((float) 53 / 172) * gBaseCircleRadius;
        gBodyWidth = (float) gBodyHeight / (float) 2;
        gArmHeight = ((float) 57 / (float) 172) * gBaseCircleRadius;
        gArmWidth = (float) gArmHeight / (float) 6;
        gArmAngle = -90.0f;
        gArmSpeed = 1.0f;
        gThighHeight = ((float) 47 / (float) 172) * gBaseCircleRadius;
        gThighWidth = (float) gThighHeight / (float) 6;
        gFrontThighAngle = -140.0f;
        gBackThighAngle = -210.0f;
        gShinHeight = ((float) 50 / (float) 172) * gBaseCircleRadius;
        gShinWidth = (float) gShinHeight / (float)  6;
        gFrontShinAngle = -70.0f;
        gBackShinAngle = -30.0f;
        gSpeed = 10;
        gDirection = -1;
        gInvisibleReactHeight = gThighHeight + gShinHeight + gBodyHeight + 2 * gHeadCircleRadius;
        gInvisibleReactWidth = gBodyWidth;
    }

    void Draw() {
        DrawOpponent();
    }

    GLfloat GetGx();
    GLfloat GetGy();
    void MoveInX(GLfloat dx, GLfloat minOpponentPositionX, GLfloat maxOpponentPositionX);
    void MoveInY(GLfloat dy, GLfloat minOpponentPositionY, GLfloat maxOpponentPositionY);
    void RotateArm(GLfloat y, GLfloat windowHeight);
    void SetDirection(GLint direction);
    GLfloat GetInvisibleReactWidth();
    GLfloat GetInvisibleReactHeight();
    GLfloat GetThighHeight();
    GLfloat GetShinHeight();
};



#endif // OPPONENT_H