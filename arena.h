#ifndef ARENA_H
#define ARENA_H



#include <GL/gl.h>
#include <GL/glu.h>
#include "player.h"
#include "obstacle.h"
#include "opponent.h"
#include <vector>


class Arena {
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


public:
    Arena(GLfloat width, GLfloat height, GLfloat red, GLfloat green, GLfloat blue, Player player, std::vector<Obstacle> obstacles, std::vector<Opponent> opponents) {
        width = width;
        height = height;
        red = red;
        green = green;
        blue = blue;
        player = player;
        obstacles = obstacles;
        opponents = opponents;
    }

    void Draw() {
        DrawArena();
    }
};



#endif // ARENA_H