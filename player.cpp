#include "player.h"

void Player::DrawPlayer() {
    glPushMatrix();
        // Draw the body
        glTranslatef(gX, gY, 0);
        DrawRect(gBodyWidth, gBodyHeight, 0.0f, 1.0f, 0.0f);

        DrawHeadAndArm();

        DrawBackLeg();

        DrawFrontLeg();
    glPopMatrix();
}

void Player::DrawHeadAndArm() {
    glPushMatrix();
        // Draw the head
        glTranslatef(0, gBodyHeight + gHeadCircleRadius, 0);
        DrawCircle(gHeadCircleRadius, 0.0f, 1.0f, 0.0f);

        // Draw the arm
        glTranslatef(0, -(gHeadCircleRadius + (gBodyHeight/2)), 0);
        glRotatef(gArmAngle * gXDirection, 0, 0, 1);
        DrawRect(gArmWidth, gArmHeight, 1.0f, 1.0f, 0.0f);
    glPopMatrix();
}

void Player::DrawFrontLeg() {
    glPushMatrix();
        // Draw the front thigh
        glRotatef(gFrontThighAngle * gXDirection, 0, 0, 1);
        DrawRect(gThighWidth, gThighHeight, 1.0f, 1.0f, 1.0f);

        // Draw the front leg
        glTranslatef(0, gThighHeight, 0);
        glRotatef(gFrontShinAngle * gXDirection, 0, 0, 1);
        DrawRect(gShinWidth, gShinHeight, 1.0f, 1.0f, 1.0f);
    glPopMatrix();
}

void Player::DrawBackLeg() {
    glPushMatrix();
        // Draw the back thigh
        glRotatef(gBackThighAngle * gXDirection, 0, 0, 1);
        DrawRect(gThighWidth, gThighHeight, 1.0f, 0.0f, 0.0f);

        // Draw the back leg
        glTranslatef(0, gThighHeight, 0);
        glRotatef(gBackShinAngle * gXDirection, 0, 0, 1);
        DrawRect(gShinWidth, gShinHeight, 1.0f, 0.0f, 0.0f);
    glPopMatrix();
}

void Player::DrawRect(GLfloat width, GLfloat height, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);

    glBegin(GL_POLYGON);
        glVertex2f(-width / 2, 0);
        glVertex2f(width / 2, 0);
        glVertex2f(width / 2, height);
        glVertex2f(-width / 2, height);
    glEnd();
}

void Player::DrawCircle(GLfloat radius, GLfloat R, GLfloat G, GLfloat B) {
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

GLfloat Player::GetGx() {
    return gX;
}

GLfloat Player::GetGy() {
    return gY;
}

void Player::MoveInX(GLfloat minPlayerPositionX, GLfloat maxPlayerPositionX, GLdouble timeDifference) {
    if (gX + gSpeed * timeDifference * gXDirection >= minPlayerPositionX && 
        gX + gSpeed * timeDifference * gXDirection <= maxPlayerPositionX) {
        gX += gSpeed * timeDifference * gXDirection;
    }
}

void Player::MoveInY(GLfloat minPlayerPositionY, GLfloat maxPlayerPositionY, GLdouble timeDifference) {
    if (gY + gSpeed * timeDifference * gYDirection >= minPlayerPositionY && 
        gY + gSpeed * timeDifference * gYDirection <= maxPlayerPositionY) {
        gY += gSpeed * timeDifference * gYDirection;
    }
}

void Player::RotateArm(GLfloat y, GLfloat windowHeight) {
    GLfloat mouseMin = 0;
    GLfloat mouseMax = windowHeight - mouseMin;

    GLfloat angleMax = -45.0f;
    GLfloat angleMin = -135.0f;

    gArmAngle = angleMin + ((y - mouseMin) / (mouseMax - mouseMin)) * (angleMax - angleMin);
    
    // gArmAngle *= gArmSpeed;

    if      (gArmAngle > angleMax) gArmAngle = angleMax;
    else if (gArmAngle < angleMin) gArmAngle = angleMin;
}

void Player::SetXDirection(GLint xDirection) {
    gXDirection = xDirection;
}

void Player::SetYDirection(GLint yDirection) {
    gYDirection = yDirection;
}

GLfloat Player::GetFrontThighAngle() {
    return gFrontThighAngle;
}

GLfloat Player::GetBackThighAngle() {
    return gBackThighAngle;
}

GLfloat Player::GetFrontShinAngle() {
    return gFrontShinAngle;
}

GLfloat Player::GetBackShinAngle() {
    return gBackShinAngle;
}

void Player::RotateFrontThigh(GLfloat dAngle) {
    gFrontThighAngle += dAngle;
}

void Player::RotateBackThigh(GLfloat dAngle) {
    gBackThighAngle += dAngle;
}

void Player::RotateFrontShin(GLfloat dAngle) {
    gFrontShinAngle += dAngle;
}

void Player::RotateBackShin(GLfloat dAngle) {
    gBackShinAngle += dAngle;
}

void Player::SetFrontShinAngle(GLfloat angle) {
    gFrontShinAngle = angle;
}

void Player::SetBackShinAngle(GLfloat angle) {
    gBackShinAngle = angle;
}

// Aux rotation func
void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut) {
    // Rotation matrix
    GLfloat rotMatrix[3][3] = {
        {cos(angle), -sin(angle), 0},
        {sin(angle), cos(angle) , 0},
        {0         , 0          , 1},
    };

    // Input vector
    GLfloat inVector[3] = {x, y, 1};

    // Output vector
    GLfloat outVector[3] = {0, 0, 0};

    // Multiply matrix by vector
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            outVector[i] += rotMatrix[i][j] * inVector[j];
        }
    }

    // Output values
    xOut = outVector[0];
    yOut = outVector[1];
}

// Aux translate func
void TranslatePoint(GLfloat x, GLfloat y, GLfloat dx, GLfloat dy, GLfloat &xOut, GLfloat &yOut) {
    // Translation matrix
    GLfloat transMatrix[3][3] = {
        {1, 0, dx},
        {0, 1, dy},
        {0, 0, 1},
    };

    // Input vector
    GLfloat inVector[3] = {x, y, 1};

    // Output vector
    GLfloat outVector[3] = {0, 0, 0};

    // Multiply matrix by vector
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            outVector[i] += transMatrix[i][j] * inVector[j];
        }
    }

    // Output values
    xOut = outVector[0];
    yOut = outVector[1];
}

// Aux scale func
void ScalePoint(GLfloat x, GLfloat y, GLfloat sx, GLfloat sy, GLfloat &xOut, GLfloat &yOut) {
    // Sacle matriz
    GLfloat scaleMatrix[3][3] = {
        {sx, 0 , 0},
        {0 , sy, 0},
        {0 , 0 , 1},
    };

    // Input vector
    GLfloat inVector[3] = {x, y, 1};

    // Output vector
    GLfloat outVector[3] = {0, 0, 0};

    // Multiply matrix by vector
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            outVector[i] += scaleMatrix[i][j] * inVector[j];
        }
    }

    // Output values
    xOut = outVector[0];
    yOut = outVector[1];
}

Shot* Player::Shoot(GLfloat maxDist) {
    GLfloat xBaseArm = 0.0, yBaseArm = 0.0;
    GLfloat xTopArm = 0.0, yTopArm = 0.0;

    glPushMatrix();
        // Getting top position
        GLfloat x = 0.0, y = 0.0;
        GLfloat xOut = 0.0, yOut = 0.0;

        TranslatePoint(x, y, 0, gArmHeight, xOut, yOut);
        x = xOut; y = yOut;

        RotatePoint(x, y, (gArmAngle * M_PI / 180) * gXDirection, xOut, yOut);
        x = xOut; y = yOut;

        TranslatePoint(x, y, 0, gBodyHeight/2, xOut, yOut);
        x = xOut; y = yOut;

        TranslatePoint(x, y, gX, gY, xOut, yOut);
        x = xOut; y = yOut;

        xTopArm = x;
        yTopArm = y;


        // Getting base position
        x = 0.0; y = 0.0;
        xOut = 0.0, yOut = 0.0;

        RotatePoint(x, y, (gArmAngle * M_PI / 180) * gXDirection, xOut, yOut);
        x = xOut; y = yOut;

        TranslatePoint(x, y, 0, gBodyHeight/2, xOut, yOut);
        x = xOut; y = yOut;

        TranslatePoint(x, y, gX, gY, xOut, yOut);
        x = xOut; y = yOut;

        xBaseArm = x;
        yBaseArm = y;


        // Findig the direction
        GLfloat baseVector[2] = {xBaseArm, yBaseArm};
        GLfloat topVector[2] = {xTopArm, yTopArm};

        GLfloat xResVector = topVector[0] - baseVector[0];
        GLfloat yResVector = topVector[1] - baseVector[1];

        GLfloat norm = sqrt(pow(xResVector, 2) + pow(yResVector, 2));
        xResVector /= norm;
        yResVector /= norm;

        GLfloat shotDirection[2] = {xResVector, yResVector};
    glPopMatrix();

    return new Shot(xTopArm, yTopArm, gSpeed, shotDirection, maxDist, gBaseCircleRadius/5);
}


bool Player::CollidesWithObstacle(Obstacle* obstacle, GLfloat dx, GLfloat dy) {
    GLfloat x = gX + dx * gXDirection;
    GLfloat y = gY + dy * gYDirection;

    GLfloat playerLeftX = x - gInvisibleReactWidth / 2;
    GLfloat playerRightX = x + gInvisibleReactWidth / 2;
    GLfloat playerBottomY = y - gThighHeight - gShinHeight;
    GLfloat playerTopY = y - gThighHeight - gShinHeight + gInvisibleReactHeight;

    GLfloat obstacleLeftX = obstacle->GetX();
    GLfloat ObstacleRightX = obstacle->GetX() + obstacle->GetWidth();
    GLfloat obstacleTopY = obstacle->GetY();
    GLfloat obstacleBottomY = obstacle->GetY() - obstacle->GetHeight();

    if (playerRightX > obstacleLeftX && playerLeftX < ObstacleRightX &&
        playerTopY > obstacleBottomY && playerBottomY < obstacleTopY) {
        return true;
    }

    return false;
}


GLfloat Player::GetSpeed() {
    return gSpeed;
}