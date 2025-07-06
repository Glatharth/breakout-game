#pragma once
#include "raylib/raylib.h"

typedef struct Enemy {
    int health;     // Health of the enemy
    int maxHealth;
    int exp;
    int pulse;
    bool hide;
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
void drawGameEnemies(GameEnemy *ge);
void updateEnemies(GameEnemy *ge);
int updateEnemyHealth(Enemy *enemy, int health);
void setPulseEnemy(Enemy *enemy, int pulse);
int getPulseEnemy(int pulse);