/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld implementation.
 * 
 * @copyright Copyright (c) 2025
 */
#include <stdio.h>
#include <stdlib.h>

#include "GameWorld.h"
#include "ResourceManager.h"
#include "GameEnemy.h"

#include "raylib/raylib.h"

#include "GamePhysics.h"
#include "Player.h"
#include "Ball.h"

//#include "raylib/raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raylib/raygui.h"       // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld(void) {
    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );

    gw->time = 1;
    gw->life = 3;
    gw->gameState = GAME_PAUSE;
    gw->gameEnemy = *initGameEnemy();
    createGameEnemies(&gw->gameEnemy);
    gw->player = (Player) {
        .pos = {
            .x = GetScreenWidth() / 2 - 35,
            .y = GetScreenHeight() - 75,
        },

        .vel = 250,

        .height = 10,

        .width = 70,

        .color = WHITE,

        .score = 0
    };
    gw->ball = (Ball) {
        .pos = {
            .x = GetScreenWidth() / 2,
            .y = GetScreenHeight() - 100
        },

        .vel = {
            .x = directionRandomizer(),
            .y = 150
        },

        .radius = 4,

        .color = WHITE
    };

    gw->stage = 1;

    return gw;
}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw ) {
    free( gw );
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void updateGameWorld( GameWorld *gw, float delta ) {
    //const uint64_t time = (uint64_t)GetTime();
    Player* player = getPlayer(gw);
    GameEnemy* enemies = getGameEnemy(gw);
    Ball* ball = getBall(gw);
    // if (gw->time == time) {
    //     gw->time++;
    //     updateEnemies(enemies);
    // }
    updateEnemies(enemies);
    updatePlayer(player, delta);
    updateBall(ball, delta);
    updateCollision(ball, player, enemies);
    updateLife(gw);
}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {
    Player* player = getPlayer(gw);
    Ball* ball = getBall(gw);
    BeginDrawing();
    ClearBackground(BLACK);
    drawGameEnemies(&gw->gameEnemy);
    drawPlayer(player);
    drawBall(ball);
    drawGameLayout(gw);
    drawPlayerStats(gw);

    EndDrawing();

}

void drawGameLayout(GameWorld *gw){
    const char *title = "BreakDown";
    const char *defrost = "Pressione <Espaco> para continuar";
    const char *lostLife = "Voce perdeu uma vida!";
    const char *gameOver = "Game Over!";
    const char *restart = "Pressione <Espaço> para recomeçar";
    const char *win = "Voce venceu!";
    const char *stage = "Fase %d";

    int sizeTitle = MeasureText(title, 50);
    int sizeDefrost = MeasureText(defrost, 30);
    int sizeLostLife = MeasureText(lostLife, 40);
    int sizeGameOver = MeasureText(gameOver, 60);
    int sizeRestart =  MeasureText(restart, 30);
    int sizeWin = MeasureText(win, 60);
    int sizeStage = MeasureText(TextFormat(stage, gw->stage), 30);



    Color backgroundColor = {0, 0, 0, 180};

    if(gw->gameState == GAME_PAUSE){
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), backgroundColor);
        if(gw->life == 3){
            DrawText(title, GetScreenWidth() / 2 - sizeTitle / 2, GetScreenHeight() / 2 - 150, 50, PURPLE);
            DrawText(defrost, GetScreenWidth() / 2 - sizeDefrost / 2, GetScreenHeight() / 2 - 60, 30, WHITE);
        }else {
            DrawText(lostLife, GetScreenWidth() / 2 - sizeLostLife / 2, GetScreenHeight() / 2 - 100, 40, RED);
            DrawText(defrost, GetScreenWidth() / 2 - sizeDefrost / 2, GetScreenHeight() / 2 - 30, 30, WHITE);
            DrawText(TextFormat(stage, gw->stage), GetScreenWidth() / 2 - sizeStage / 2, GetScreenHeight() - 40, 30, WHITE);
        }
    }else if(gw->gameState == GAME_OVER){
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), backgroundColor);
        DrawText(gameOver, GetScreenWidth() / 2 - sizeGameOver / 2, GetScreenHeight() / 2 - 150, 60, RED);
        DrawText(restart, GetScreenWidth() / 2 - sizeRestart / 2, GetScreenHeight() / 2 - 30,30,WHITE);
    }else if(gw->gameState == GAME_WIN){
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
        DrawText(win, GetScreenWidth() / 2 - (sizeWin / 2), GetScreenHeight() / 2 - 150, 60, GREEN);
        DrawText(defrost, GetScreenWidth() / 2 - sizeDefrost / 2, GetScreenHeight() / 2 - 30, 30, WHITE);
        drawPlayerStats(gw);
        DrawText(TextFormat(stage, gw->stage), GetScreenWidth() / 2 - sizeStage / 2, GetScreenHeight() - 40, 30, WHITE);
    }
}

void drawPlayerStats(GameWorld *gw){
    const char *life = "Vidas:  %d";
    const char *score = "Score: %d";
    const char *stage = "%d";

    int sizeScore = MeasureText(score, 30);
    int sizeStage = MeasureText(TextFormat(stage, gw->stage), 30);

    if(gw->gameState == GAME_START || gw->gameState == GAME_WIN){
        DrawText(TextFormat(life, gw->life), 10, GetScreenHeight() - 40, 30, WHITE);
        DrawText(TextFormat(score, getPlayer(gw)->score), GetScreenWidth() - sizeScore - 20, GetScreenHeight() - 40, 30, WHITE);
        DrawText(TextFormat(stage, gw->stage), GetScreenWidth() / 2 - sizeStage / 2, GetScreenHeight() - 40, 30, WHITE);
    }
}

void updateLife(GameWorld *gw){
    if(gw->ball.pos.y + gw->ball.radius > GetScreenHeight()){
        gw->ball.pos.y = GetScreenHeight() / 2;
        gw->ball.pos.x = GetScreenWidth() / 2;
        gw->ball.vel.x = 0;
        gw->ball.vel.y = 0;
        gw->gameState = GAME_PAUSE;
        gw->life--;
        gw->player.pos.x = GetScreenWidth() / 2 - 35;
        gw->player.pos.y = GetScreenHeight() - 75;
        if(gw->life == 0){
            gw->gameState = GAME_OVER;
        }
    }
}

