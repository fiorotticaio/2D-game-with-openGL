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
    GLfloat x;
    GLfloat y;

    GLfloat width;
    GLfloat height;

    GLfloat red;
    GLfloat green;
    GLfloat blue;
    
    Player* player;
    std::vector<Obstacle*> obstacles;
    std::vector<Opponent*> opponents;


private:
    void DrawArena();
    void LoadArena(const char* svg_file_path);


public:
    Arena(const char* svg_file_path) {
        LoadArena(svg_file_path);
    }

    void Draw() {
        DrawArena();
    }
};



#endif // ARENA_H