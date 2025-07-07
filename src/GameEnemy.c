#include "GameEnemy.h"
#include <stdio.h>
#include <stdlib.h>
#include "include/raylib/raylib.h"

GameEnemy* initGameEnemy(int stage) {
    GameEnemy *ge = malloc(sizeof(GameEnemy));
    ge->amount = 2 + (stage * 2); // Number of enemies per line
    ge->line = 2 + (stage * 3);
    ge->space = 5;
    ge->fromPosition = (Vector2){0, 50}; //800 => width || 450 => height
    ge->toPosition = (Vector2){GetScreenWidth(), 0.4 * GetScreenHeight()}; //800 => width || 450 => height
    ge->enemies = malloc(sizeof(Enemy*) * ge->amount * ge->line);
    ge->totalEnemies = ge->amount * ge->line;
    return ge;
}

void createGameEnemies(GameEnemy *ge) {
    ge->size = (Size) {
        ((int)ge->toPosition.x - (int)ge->fromPosition.x - (ge->space * (ge->amount - 1))) / ge->amount,
        ((int)ge->toPosition.y - (int)ge->fromPosition.y - (ge->space * (ge->line - 1))) / ge->line
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
            ge->enemies[arrayIndex]->maxHealth = 100;
            ge->enemies[arrayIndex]->pulse = 0;
            ge->enemies[arrayIndex]->exp = 5;
            ge->enemies[arrayIndex]->hide = false;
            ge->enemies[arrayIndex]->position = (Vector2){
                ge->fromPosition.x + (float)(i * (ge->size.width + ge->space)),
                ge->fromPosition.y + (float)(j * (ge->size.height + ge->space))
            };
            const int shift = 1;
            ge->enemies[arrayIndex]->color = (Color){
                (i << shift) % 256,
                (i << (shift + 2)) % 256,
                (i << (shift + 3)) % 256,
                255
            };
            arrayIndex++;
        }
    }
}

void drawGameEnemies(GameEnemy *ge) {
    for (int i = 0; i < ge->amount * ge->line; i++) {
        if (!ge->enemies[i]) {
            continue;
        }
        Enemy *enemy = ge->enemies[i];

        if (enemy->pulse > 0) {
            enemy->pulse--;
            if (enemy->pulse % 5 == 1) {
                enemy->hide = !enemy->hide;
                continue;
            }
            if (enemy->pulse == 0) {
                enemy->hide = true;
            }
        }

        if (enemy->health <= 0 && enemy->hide) {
            continue;
        }

        DrawRectangle(
           (int)enemy->position.x,
           (int)enemy->position.y,
           ge->size.width,
           ge->size.height,
           enemy->color
        );

    }
}

void updateEnemies(GameEnemy *ge) {
    for (int i = 0; i < ge->amount * ge->line; i++) {
        Enemy *enemy = ge->enemies[i];
        Color current = enemy->color;
        Color newColor = {
            (current.r + GetRandomValue(0, 2)) % 256,
            (current.g + GetRandomValue(0, 2)) % 256,
            (current.b + GetRandomValue(0, 2)) % 256,
            200
        };
        enemy->color = newColor;
    }
}

int updateEnemyHealth(Enemy *enemy, const int health) {
    if (!enemy) {
        fprintf(stderr, "Enemy not found!\n");
        return 0;
    }
    if (enemy->health > 0) {
        enemy->health += health;
        if (enemy->health <= 0) {
            setPulseEnemy(enemy, 3);
            return enemy->exp;
        }
    }
    return 0;
}

void setPulseEnemy(Enemy *enemy, const int pulse) {
    enemy->pulse = getPulseEnemy(pulse);
}

int getPulseEnemy(const int pulse) {
    return pulse * 10;
}

