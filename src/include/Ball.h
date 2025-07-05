#pragma once
#include "raylib/raylib.h"
#include "GameWorld.h"
#include "GamePhysics.h"

typedef struct Ball{
    Vector2 pos;
    Vector2 vel;
    float radius;
    Color color;
}Ball;

void updateBall(Ball *b, float delta, GameWorld *gw);
