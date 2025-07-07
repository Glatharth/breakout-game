#include "raylib/raylib.h"
#include "Player.h"
#include "Ball.h"
#include "GameEnemy.h"

//check the collision between the ball and the player
void updateCollision(Ball *b, Player *p, GameEnemy *ge){
    //verify if there was a collision in the top 
    if(b->pos.x + b->radius < p->pos.x + p->width && b->pos.x - b->radius > p->pos.x){
        if(b->pos.y + b->radius > p->pos.y ){
            if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
                if(b->vel.x > 0){
                    //b->pos.y = b->pos.y - b->radius;
                    b->vel.y = -b->vel.y;
                    b->vel.x = -b->vel.x;
                }
            }
        }else if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)){
                if(b->vel.x < 0){
                    //b->pos.y = b->pos.y - b->radius;
                b->vel.y = -b->vel.y;
                b->vel.x = -b->vel.x;
            }
        }else{
                //b->pos.y = b->pos.y - b->radius;
            b->vel.y = -b->vel.y;
        }
    }

    
        
    
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