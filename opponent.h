#ifndef OPPONENT_H
#define OPPONENT_H



#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include "shot.h"


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

    GLfloat gXSpeed;
    GLfloat gYSpeed;
    GLint gXDirection; // 1 for right (front), -1 for left (back)
    GLint gYDirection; // 1 for up, -1 for down

    GLfloat maxJumpHeight;
    GLfloat jumpHeight;


private:
    void DrawOpponent();
    void DrawCircle(GLfloat radius, GLfloat R, GLfloat G, GLfloat B);
    void DrawRect(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B);
    void DrawHeadAndArm();
    void DrawFrontLeg();
    void DrawBackLeg();
    void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut);
    void TranslatePoint(GLfloat x, GLfloat y, GLfloat dx, GLfloat dy, GLfloat &xOut, GLfloat &yOut);
    void ScalePoint(GLfloat x, GLfloat y, GLfloat sx, GLfloat sy, GLfloat &xOut, GLfloat &yOut);
    

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
        gBackThighAngle = -220.0f;
        gShinHeight = ((float) 50 / (float) 172) * gBaseCircleRadius;
        gShinWidth = (float) gShinHeight / (float)  6;
        gFrontShinAngle = 0.0f;
        gBackShinAngle = 0.0f;
        gXSpeed = 0.025f;
        gYSpeed = 0.025f;
        gXDirection = -1;
        gYDirection = -1;
        gInvisibleReactHeight = gThighHeight + gShinHeight + gBodyHeight + 2 * gHeadCircleRadius;
        gInvisibleReactWidth = gBodyWidth;
        maxJumpHeight = 4 * gInvisibleReactHeight; // 4 instead of 3 to make the game more playable
        jumpHeight = 0;
    }

    void Draw() {
        DrawOpponent();
    }

    GLfloat GetGx();
    GLfloat GetGy();
    void MoveInX(GLfloat minOpponentPositionX, GLfloat maxOpponentPositionX, GLdouble timeDifference);
    void MoveInY(GLfloat minOpponentPositionY, GLfloat maxOpponentPositionY, GLdouble timeDifference);
    void RotateArm(GLfloat y, GLfloat windowHeight);
    void SetXDirection(GLint xDirection);
    GLint GetXDirection();
    void SetYDirection(GLint yDirection);
    GLint GetYDirection();
    GLfloat GetFrontThighAngle();
    GLfloat GetBackThighAngle();
    GLfloat GetFrontShinAngle();
    GLfloat GetBackShinAngle();
    void RotateFrontThigh(GLfloat dAngle);
    void RotateBackThigh(GLfloat dAngle);
    void RotateFrontShin(GLfloat dAngle);
    void RotateBackShin(GLfloat dAngle);
    void SetFrontShinAngle(GLfloat angle);
    void SetBackShinAngle(GLfloat angle);
    Shot* Shoot(GLfloat maxDist);
    GLfloat GetXSpeed();
    GLfloat GetYSpeed();
    void Jump();
    GLfloat GetMaxJumpHeight();
    GLfloat GetJumpHeight();
    GLfloat GetThighHeight();
    GLfloat GetShinHeight();
    bool ReachedMaximumJumpHeight();
    GLfloat GetInvisibleReactHeight();
    GLfloat GetInvisibleReactWidth();
};



#endif // OPPONENT_H