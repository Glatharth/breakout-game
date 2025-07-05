#include "include/GameEnemy.h"
#include <stdio.h>
#include <stdlib.h>
#include "include/raylib/raylib.h"

GameEnemy* initGameEnemy() {
    GameEnemy *ge = malloc(sizeof(GameEnemy));
    ge->amount = 20; // Number of enemies per line
    ge->line = 8;
    ge->fromPosition = (Vector2){0, 50}; //800 => width || 450 => height
    ge->toPosition = (Vector2){800, 200}; //800 => width || 450 => height
    ge->enemies = malloc(sizeof(Enemy*) * ge->amount * ge->line);
    return ge;
}

void createGameEnemies(GameEnemy *ge) {
     ge->size = (Size) {
        ((int)ge->fromPosition.x + (int)ge->toPosition.x) / ge->amount,
        ((int)ge->toPosition.y - (int)ge->fromPosition.y) / ge->line
    };
    int arrayIndex = 0;
    for (int i = 0; i < ge->amount; i++) {
        for (int j = 0; j < ge->line; j++) {
            ge->enemies[arrayIndex] = malloc(sizeof(Enemy));
            if (!ge->enemies[arrayIndex]) {
                fprintf(stderr, "Memory allocation failed!\n");
                exit(EXIT_FAILURE);
            }
            ge->enemies[arrayIndex]->health = 100;
            ge->enemies[arrayIndex]->position = (Vector2){
                ge->fromPosition.x + (float)(i * ge->size.width),
                ge->fromPosition.y + (float)(j * ge->size.height)
            };
            arrayIndex++;
        }
    }
}

void drawGameEnemies(const GameEnemy *ge) {
    for (int i = 0; i < ge->amount * ge->line; i++) {
        const int shift = 1;
        const Enemy enemy = *ge->enemies[i];
        DrawRectangle(
           (int)enemy.position.x,
           (int)enemy.position.y,
           ge->size.width,
           ge->size.height,
           // i % 2 == 0 ? GRAY : BLACK
           (Color){
                (i << shift) % 256,
                (i << (shift + 2)) % 256,
                (i << (shift + 4)) % 256,
                255
           }
        );
    }
}