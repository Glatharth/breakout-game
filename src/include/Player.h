#pragma once
#include "raylib/raylib.h"

typedef struct Player{
    Vector2 pos;
    int vel;
    int height;
    int width;
    Color color;
}Player;

void drawPlayer(Player *p);

void updatePlayer(Player *p, float delta);

int lifeManager(void);