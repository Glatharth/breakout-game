#include "GameEnemy.h"
#include <stdio.h>
#include <stdlib.h>

#include "ResourceManager.h"
#include "include/raylib/raylib.h"

int TOASTY = 0;

GameEnemy* initGameEnemy() {
    GameEnemy *ge = calloc(1, sizeof(GameEnemy));
    ge->amount = 20; // Number of enemies per line
    ge->line = 8;
    ge->space = 5;
    ge->fromPosition = (Vector2){0, 50}; //800 => width || 450 => height
    ge->toPosition = (Vector2){800, 200}; //800 => width || 450 => height
    ge->enemies = calloc(ge->amount * ge->line, sizeof(Enemy*));
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
            const int randomizeEnemyHealth = GetRandomValue(1, 10);
            ge->enemies[arrayIndex]->health = randomizeEnemyHealth <= 3 ? 300 : 100;
            ge->enemies[arrayIndex]->maxHealth = randomizeEnemyHealth <= 3 ? 300 : 100;
            ge->enemies[arrayIndex]->pulse = 0;
            ge->enemies[arrayIndex]->exp = (int)(ge->enemies[arrayIndex]->maxHealth * 0.05);
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
        enemy->color = ColorFromHSV(i * 2, 1, 1);
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
            PlaySound(rm.deadEnemy);
            TOASTY++;
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