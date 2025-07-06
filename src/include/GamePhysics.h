#include "raylib/raylib.h"
#include "Ball.h"
#include "enums.h"
#include "GameEnemy.h"
#include "GameWorld.h"
#include "Player.h"

void updateCollision(Ball *b, Player *p, GameEnemy *ge);

int directionRandomizer(void);