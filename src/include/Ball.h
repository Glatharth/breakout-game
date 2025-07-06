#pragma once
#include "raylib/raylib.h"

typedef struct Ball{
    Vector2 pos;
    Vector2 vel;
    float radius;
    Color color;
}Ball;

void updateBall(Ball *b, float delta);
