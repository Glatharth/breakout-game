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
    gw->score = 0;

    gw->roundNumber = 0;
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

        .color = WHITE
    };
    gw->ball = (Ball) {
        .pos = {
            .x = GetScreenWidth() / 2,
            .y = GetScreenHeight() - 125
        },

        .vel = {
            .x = 0,
            .y = 150
        },

        .radius = 4,

        .color = WHITE
    };

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
    const uint64_t time = (uint64_t)GetTime();
    Player* player = getPlayer(gw);
    GameEnemy* enemies = getGameEnemy(gw);
    Ball* ball = getBall(gw);
    if (gw->time == time) {
        gw->time++;
        updateEnemies(enemies);
    }
    updatePlayer(player, delta);
    updateBall(ball, delta);
    updateCollision(ball, player, enemies);
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

    // const char *text = "Basic game template";
    // Vector2 m = MeasureTextEx( GetFontDefault(), text, 40, 4 );
    // int x = GetScreenWidth() / 2 - m.x / 2;
    // int y = GetScreenHeight() / 2 - m.y / 2;
    // DrawRectangle( x, y, m.x, m.y, BLACK );
    // DrawText( text, x, y, 40, WHITE );
    //DrawFPS( 0, 0 );

    EndDrawing();

}

// void drawGameLayout(GameWorld *gw){
//     const char *title = "BreakDown";
//     const char *defrost = "Pressione <Espaco> para continuar";
//     const char *lostLife = "Voce perdeu uma vida!";
//     const char *gameOver = "Game Over!";
//     const char *restart = "Pressione <Espaço> para recomeçar";

//     int sizeTitle = MeasureText(title, 50);
//     int sizeDefrost = MeasureText(defrost, 30);
//     int sizeLostLife = MeasureText(lostLife, 40);
//     int sizeGameOver = MeasureText(gameOver, 60);
//     int sizeRestart =  MeasureText(restart, 30);

//     if(gw->gameState = GAME_PAUSE){
//         if(lifeManager() == 3){
//             DrawText(title, GetScreenWidth() / 2 - sizeTitle / 2, GetScreenHeight() / 2 - 150, 50, PURPLE);
//             DrawText(defrost, GetScreenWidth() / 2 - sizeDefrost / 2, GetScreenHeight() / 2 - 60, 30, WHITE);
//         }else if(lifeManager() < 3 && lifeManager() > 0){
//             DrawText(lostLife, GetScreenWidth() / 2 - sizeLostLife / 2, GetScreenHeight() / 2 - 100, 40, RED);
//             DrawText(defrost, GetScreenWidth() / 2 - sizeDefrost / 2, GetScreenHeight() / 2 - 30, 30, WHITE);

//         }else{
//             DrawText(gameOver, GetScreenWidth() / 2 - sizeGameOver / 2, GetScreenHeight() / 2 - 150, 60, RED);
//             DrawText(restart, GetScreenWidth() / 2 - sizeRestart / 2, GetScreenHeight() / 2 - 30,30,WHITE);
//         }
//     }
// }

