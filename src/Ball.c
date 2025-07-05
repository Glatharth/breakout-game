#include "raylib/raylib.h"
#include "Ball.h"
#include "enums.h"
#include "GameWorld.h"
#include "GamePhysics.h"

void drawBall(Ball *b){
    DrawCircle(
        b->pos.x,
        b->pos.y,
        b->radius,
        b->color
    );
}

//manage the ball's movement
void updateBall(Ball *b, float delta){
    //ensure the ball will be reset the it's origianl position when a life is lost
    // if(gw->gameState){
    //     b->vel.x = 0;
    //     b->vel.y = 0;
    //     b->pos.x = GetScreenWidth() / 2;
    //     b->pos.y = GetScreenHeight() - 125;
    //     //starts the game whenever the play press the space bar
    //     if(IsKeyPressed(KEY_SPACE)){
    //         b->vel.x = directionRamdomizer();
    //         b->vel.y = 150;
    //         gw->gameState = false;
    //     }
    // }

    //make the ball always go straight up in the begging of the game
    b->pos.x += b->vel.x * delta;
    b->pos.y -= b->vel.y * delta;

    //checks for any lateral collisions
    if(b->pos.x + b->radius > GetScreenWidth()){
        b->pos.x = b->pos.x - b->radius;
        b->vel.x = -b->vel.x;
    }else if(b->pos.x - b->radius < 0){
        b->pos.x = b->pos.x + b->radius;
        b->vel.x = -b->vel.x;
    }

    //checks for any collision on the top of the screen
    if(b->pos.y - b->radius < 0){
        b->pos.y = b->pos.y + b->radius;
        b->vel.y = -b->vel.y;
        b->vel.x = b->vel.x;
    }

    //freezes the game as soon as the ball gets out of the bottom part of the screen and decrease the number of lives
    if(b->pos.y + b->radius > GetScreenHeight()){
        b->pos.y = GetScreenHeight() / 2;
        b->pos.x = GetScreenWidth() / 2;
        // gw->gameState = true;
        // gw->roundNumber++;
    }
}