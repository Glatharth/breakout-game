#include "raylib/raylib.h"
#include "Player.h"
#include "enums.h"
//draws the player on the screen
void drawPlayer(Player *p){
    DrawRectangle(
        p->pos.x,
        p->pos.y,
        p->width,
        p->height,
        p->color
    );
}

//manage the players movement 
void updatePlayer(Player *p, float delta){
    
    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
        p->pos.x -= p->vel * delta;
    }

    if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
        p->pos.x += p->vel * delta;
    }
    //don't let the player get out of the screen
    if(p->pos.x < 0){
        p->pos.x = 0;
    }else if(p->pos.x + p->width > GetScreenWidth()){
        p->pos.x = GetScreenWidth() - p->width;
    }
}