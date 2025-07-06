#include "raylib/raylib.h"
#include "Player.h"
#include "Ball.h"
#include "GameEnemy.h"

//check the collision between the ball and the player
void updateCollision(Ball *b, Player *p, GameEnemy *ge){
    //verify if there was a collision in the top 
    if(b->pos.x + b->radius <= p->pos.x + p->width && b->pos.x - b->radius >= p->pos.x){
        if(b->pos.y + b->radius >= p->pos.y ){
            //general top collision modifier
            b->pos.y = b->pos.y - b->radius;
            b->vel.y = -b->vel.y;
        }else if(b->pos.y + b->radius < p->pos.y + p->height && b->pos.y - b->radius > p->pos.y){
            b->vel.y = -b->vel.y;
            b->vel.x = -b->vel.x;
        }
    }

    // for(int i = 0; i < ge->amount * ge->line; i++){
    //     const Enemy comparisonEnemy = *ge->enemies[i];
    //     const Size comparisonHeight = *ge->size.height;

    //     if(b->pos.y - b->radius < comparisonEnemy.position.y + ())
    // }
}
//randomize the ball's direction in the beginning of each round based on an odd or even number logic
int directionRandomizer (void){
    int direction = GetRandomValue(1, 10);
    if(direction % 2 == 0){
        return 150;
    }else{
        return -150;
    }
}