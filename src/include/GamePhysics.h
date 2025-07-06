#pragma once
#include "Ball.h"
#include "GameEnemy.h"
#include "Player.h"

void updateCollision(Ball *b, Player *p, GameEnemy *ge);

int directionRandomizer(void);