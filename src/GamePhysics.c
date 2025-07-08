#include "raylib/raylib.h"
#include "Player.h"
#include "Ball.h"
#include "GameEnemy.h"
#include "ResourceManager.h"

int distance(int x1, int y1, int x2, int y2){
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

//check the collision between the ball and the player
void updateCollision(Ball *b, Player *p, GameEnemy *ge){
    int xPoint = b->pos.x;
    int yPoint = b->pos.y;

    if(xPoint < p->pos.x){
        xPoint = p->pos.x;
    }else if(xPoint > p->pos.x + p->width){
        xPoint = p->pos.x + p->width;
    }

    if(yPoint < p->pos.y){
        yPoint = p->pos.y;
    }else if(yPoint > p->pos.y + p->height){
        yPoint = p->pos.y;
    }

    if(distance(xPoint, yPoint, b->pos.x, b->pos.y) < (b->radius * b->radius)){
        if(IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)){
            if(b->vel.x > 0){
                b->vel.x = -b->vel.x;
            }

        }else if(IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)){
            if(b->vel.x < 0){
                b->vel.x = -b->vel.x;
            }
        }
        b->pos.y = p->pos.y - b->radius;
        b->vel.y = -b->vel.y;
        PlaySound(rm.hitPlayer);
    }

    for(int i = 0; i < ge->amount * ge->line; i++){
        int xEnemy = b->pos.x;
        int yEnemy = b->pos.y;
        Enemy *e = ge->enemies[i];

        if(e->health > 0){
            if(xEnemy < e->position.x){
                xEnemy = e->position.x;
            } else if(xEnemy > e->position.x + ge->size.width){
                xEnemy = e->position.x + ge->size.width;
            }

            if(yEnemy < e->position.y){
                yEnemy = e->position.y;
            } else if(yEnemy > e->position.y + ge->size.height){
                yEnemy = e->position.y + ge->size.height;
            }

            if(distance(xEnemy, yEnemy, b->pos.x, b->pos.y) < (b->radius * b->radius)){
                const int exp = updateEnemyHealth(e, -100);
                if (exp > 0){
                    p->score += exp;
                    ge->totalEnemies--;
                }
                b->pos.y = b->pos.y + b->radius;
                b->vel.y = -b->vel.y;
            }
        }
    }
}
          

//randomize the ball's direction in the beginning of each round based on an odd or even number logic
int directionRandomizer (void){
    int direction = GetRandomValue(1, 10);
    if(direction % 2 == 0){
        return 350;
    }else{
        return -350;
    }
}