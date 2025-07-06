#pragma once
#include "raylib/raylib.h"

typedef struct Enemy {
    int health;     // Health of the enemy
    Vector2 position; // Enemy Position
    Color color;    // Color
} Enemy;

typedef struct Size {
    int width;
    int height;
} Size;

typedef struct GameEnemy {
    int amount;  // Amount of enemies per line
    int line; // Amount of lines to create enemies
    Size size; // Size enemies
    int space; // Space between enemies
    Vector2 fromPosition; // Starting position
    Vector2 toPosition; // Ending position
    Enemy **enemies; // Array of enemies
} GameEnemy;

GameEnemy* initGameEnemy();

void createGameEnemies(GameEnemy *ge);
void drawGameEnemies(const GameEnemy *ge);
void updateEnemies(GameEnemy *ge);