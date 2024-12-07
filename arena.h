#ifndef ARENA_H
#define ARENA_H



#include <GL/gl.h>
#include <GL/glu.h>
#include "player.h"
#include "obstacle.h"
#include "opponent.h"
#include <vector>
#include "tinyxml2.h"
#include <string>


class Arena {
    GLfloat gX;
    GLfloat gY;

    GLfloat gWidth;
    GLfloat gHeight;

    GLfloat gRed;
    GLfloat gGreen;
    GLfloat gBlue;
    
    Player* gPlayer;
    std::vector<Obstacle*> gObstacles;
    std::vector<Opponent*> gOpponents;


private:
    void LoadArena(const char* svg_file_path);
    void DrawArena();
    void DrawRect(GLfloat width, GLfloat height, GLfloat red, GLfloat green, GLfloat blue);


public:
    Arena(const char* svg_file_path) {
        LoadArena(svg_file_path);
    }

    void Draw() {
        DrawArena();
    }
};



#endif // ARENA_H