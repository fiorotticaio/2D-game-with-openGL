#include "opponent.h"

void Opponent::DrawOpponent() {
    glPushMatrix();
        // Draw the body
        glTranslatef(gX, gY, 0);
        DrawRect(gBodyWidth, gBodyHeight, 1.0f, 0.0f, 0.0f);

        DrawHeadAndArm();

        DrawFrontLeg();

        DrawBackLeg();
    glPopMatrix();
}

void Opponent::DrawHeadAndArm() {
    glPushMatrix();
        // Draw the head
        glTranslatef(0, gBodyHeight + gHeadCircleRadius, 0);
        DrawCircle(gHeadCircleRadius, 1.0f, 0.0f, 0.0f);

        // Draw the arm
        glTranslatef(0, -(gHeadCircleRadius + (gBodyHeight/2)), 0);
        glRotatef(gArmAngle * gDirection, 0, 0, 1);
        DrawRect(gArmWidth, gArmHeight, 1.0f, 1.0f, 0.0f);
    glPopMatrix();
}

void Opponent::DrawFrontLeg() {
    glPushMatrix();
        // Draw the front thigh
        glRotatef(gFrontThighAngle * gDirection, 0, 0, 1);
        DrawRect(gThighWidth, gThighHeight, 0.0f, 1.0f, 0.0f);

        // // Draw the front leg
        glTranslatef(0, gThighHeight, 0);
        glRotatef(gFrontShinAngle * gDirection, 0, 0, 1);
        DrawRect(gShinWidth, gShinHeight, 0.0f, 1.0f, 0.0f);
    glPopMatrix();
}

void Opponent::DrawBackLeg() {
    glPushMatrix();
        // Draw the back thigh
        glRotatef(gBackThighAngle * gDirection, 0, 0, 1);
        DrawRect(gThighWidth, gThighHeight, 0.0f, 1.0f, 0.0f);

        // Draw the back leg
        glTranslatef(0, gThighHeight, 0);
        glRotatef(gBackShinAngle * gDirection, 0, 0, 1);
        DrawRect(gShinWidth, gShinHeight, 0.0f, 1.0f, 0.0f);
    glPopMatrix();
}

void Opponent::DrawRect(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);

    glBegin(GL_POLYGON);
        glVertex2f(-width / 2, 0);
        glVertex2f(width / 2, 0);
        glVertex2f(width / 2, height);
        glVertex2f(-width / 2, height);
    glEnd();
}

void Opponent::DrawCircle(GLfloat radius, GLfloat R, GLfloat G, GLfloat B) {
    const int numSegments = 100;
    const GLfloat angleStep = 2.0f * M_PI / numSegments;

    glColor3f(R, G, B);

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f);
        for (int i = 0; i <= numSegments; ++i) {
            GLfloat angle = i * angleStep;
            GLfloat x = radius * cos(angle);
            GLfloat y = radius * sin(angle);
            glVertex2f(x, y);
        }
    glEnd();
}

GLfloat Opponent::GetGx() {
    return gX;
}

GLfloat Opponent::GetGy() {
    return gY;
}

void Opponent::MoveInX(GLfloat dx, GLfloat minOpponentPositionX, GLfloat maxOpponentPositionX) {
    if (gX + dx >= minOpponentPositionX && gX + dx <= maxOpponentPositionX) {
        gX += dx * gSpeed * gDirection; 
    }
}

void Opponent::MoveInY(GLfloat dy, GLfloat minOpponentPositionY, GLfloat maxOpponentPositionY) {
    if (gY + dy >= minOpponentPositionY && gY + dy <= maxOpponentPositionY) {
        gY += dy * gSpeed;
    }
}

void Opponent::RotateArm(GLfloat y, GLfloat windowHeight) {
    GLfloat mouseMin = 0;
    GLfloat mouseMax = windowHeight - mouseMin;

    GLfloat angleMax = -45.0f;
    GLfloat angleMin = -135.0f;

    gArmAngle = angleMin + ((y - mouseMin) / (mouseMax - mouseMin)) * (angleMax - angleMin);
    
    gArmAngle *= gArmSpeed; // FIXME: This is not too cool

    if      (gArmAngle > angleMax) gArmAngle = angleMax;
    else if (gArmAngle < angleMin) gArmAngle = angleMin;
}

void Opponent::SetDirection(GLint direction) {
    gDirection = direction;
}


GLfloat Opponent::GetInvisibleReactWidth() {
    return gInvisibleReactWidth;
}


GLfloat Opponent::GetInvisibleReactHeight() {
    return gInvisibleReactHeight;
}


GLfloat Opponent::GetThighHeight() {
    return gThighHeight;
}


GLfloat Opponent::GetShinHeight() {
    return gShinHeight;
}