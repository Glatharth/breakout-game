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

#include <stdint.h>

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

uint64_t GAME_TIME = 1;

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld(void) {
    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );

    gw->life = 3;
    gw->gameState = GAME_PAUSE;
    gw->gameEnemy = *initGameEnemy();
    createGameEnemies(&gw->gameEnemy);
    gw->player = (Player) {
        .pos = {
            .x = GetScreenWidth() / 2 - 35,
            .y = GetScreenHeight() - 75,
        },

        .vel = 350,

        .height = 10,

        .width = 70,

        .color = WHITE,

        .score = 0
    };
    gw->ball = (Ball) {
        .pos = {
            .x = GetScreenWidth() / 2,
            .y = GetScreenHeight() - 125
        },

        .vel = {
            .x = directionRandomizer(),
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
    Player* player = getPlayer(gw);
    GameEnemy* enemies = getGameEnemy(gw);
    Ball* ball = getBall(gw);
    if (GAME_TIME <= (uint64_t)GetTime()) {
        GAME_TIME++;
        TOASTY = 0;
    }if(IsKeyPressed(KEY_T)){
        TOASTY = 2;
    }
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
    toastyAnimation();
    EndDrawing();
}

void drawGameLayout(GameWorld *gw){
    const char *title = "BreakDown";
    const char *defrost = "Pressione <Espaco> para continuar";
    const char *lostLife = "Voce perdeu uma vida!";
    const char *gameOver = "Game Over!";
    const char *restart = "Pressione <Espaço> para recomeçar";
    const char *win = "Voce venceu!";

    int sizeTitle = MeasureText(title, 50);
    int sizeDefrost = MeasureText(defrost, 30);
    int sizeLostLife = MeasureText(lostLife, 40);
    int sizeGameOver = MeasureText(gameOver, 60);
    int sizeRestart =  MeasureText(restart, 30);
    int sizeWin = MeasureText(win, 60);


    Color backgroundColor = {0, 0, 0, 180};

    switch (gw->gameState) {
        case GAME_PAUSE:
            ShowCursor();
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), backgroundColor);
            if (gw->life == 3) {
                DrawText(title, GetScreenWidth() / 2 - sizeTitle / 2, GetScreenHeight() / 2 - 150, 50, PURPLE);
                DrawText(defrost, GetScreenWidth() / 2 - sizeDefrost / 2, GetScreenHeight() / 2 - 60, 30, WHITE);
                if (!IsMusicStreamPlaying(rm.blessCode)){
                    PlayMusicStream(rm.blessCode);
                } else {
                    UpdateMusicStream(rm.blessCode);
                }
            } else {
                DrawText(lostLife, GetScreenWidth() / 2 - sizeLostLife / 2, GetScreenHeight() / 2 - 100, 40, RED);
                DrawText(defrost, GetScreenWidth() / 2 - sizeDefrost / 2, GetScreenHeight() / 2 - 30, 30, WHITE);
            }
            break;
        case GAME_OVER:
            ShowCursor();
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), backgroundColor);
            DrawText(gameOver, GetScreenWidth() / 2 - sizeGameOver / 2, GetScreenHeight() / 2 - 150, 60, RED);
            DrawText(restart, GetScreenWidth() / 2 - sizeRestart / 2, GetScreenHeight() / 2 - 30, 30, WHITE);
            if (IsMusicStreamPlaying(rm.inGame)){
                StopMusicStream(rm.inGame);
            }
            break;
        case GAME_WIN:
            ShowCursor();
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
            DrawText(win, GetScreenWidth() / 2 - (sizeWin / 2), GetScreenHeight() / 2 - 150, 60, GREEN);
            drawPlayerStats(gw);
            break;
        default:
            HideCursor();
            if (IsMusicStreamPlaying(rm.blessCode)) {
                StopMusicStream(rm.blessCode);
            } else if (!IsMusicStreamPlaying(rm.inGame)){
                PlayMusicStream(rm.inGame);
            } else {
                UpdateMusicStream(rm.inGame);
            }
            break;
        }
}

void drawPlayerStats(GameWorld *gw){
    const char *life = "Vidas:  %d";
    const char *score = "Score: %d";

    int sizeScore = MeasureText(score, 30);

    if(gw->gameState == GAME_START || gw->gameState == GAME_WIN){
        DrawText(TextFormat(life, gw->life), 10, GetScreenHeight() - 40, 30, WHITE);
        DrawText(TextFormat(score, getPlayer(gw)->score), GetScreenWidth() - sizeScore - 30, GetScreenHeight() - 40, 30, WHITE);
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
            PlaySound(rm.gameOver);
            return;
        }
        PlaySound(rm.lostLife);
    }
}

void toastyAnimation() {
    static double startTime = 0;
    static int state = 0; // 0: idle, 1: in, 2: hold, 3: out
    static Vector2 pos;
    float scale = 0.2f;
    float imgW = rm.cuteDavi.width * scale;
    float imgH = rm.cuteDavi.height * scale;
    float inX = GetScreenWidth() - imgW;
    float inY = GetScreenHeight() - imgH;
    float outX = GetScreenWidth() + imgW;
    float outY = GetScreenHeight() + imgH;
    float holdTime = 1.5f;
    float slideTime = 0.5f;
    Color transparentWhite = WHITE;
    transparentWhite.a = 128;

    if (TOASTY >= 2 && state == 0) {
        PlaySound(rm.toasty);
        startTime = GetTime();
        state++;
    }

    if (state == 1) {
        double t = (GetTime() - startTime) / slideTime;
        if (t >= 1.0) {
            t = 1.0;
            startTime = GetTime();
            state++;
        }
        pos.x = outX + (inX - outX) * t;
        pos.y = outY + (inY - outY) * t;
        DrawTextureEx(rm.cuteDavi, pos, 0.0f, scale, transparentWhite);
    } else if (state == 2) {
        pos.x = inX;
        pos.y = inY;
        DrawTextureEx(rm.cuteDavi, pos, 0.0f, scale, transparentWhite);
        if (GetTime() - startTime >= holdTime) {
            startTime = GetTime();
            state++;
        }
    } else if (state == 3) {
        double t = (GetTime() - startTime) / slideTime;
        if (t >= 1.0) {
            t = 1.0;
            state = 0;
        }
        pos.x = inX + (outX - inX) * t;
        pos.y = inY + (outY - inY) * t;
        DrawTextureEx(rm.cuteDavi, pos, 0.0f, scale, transparentWhite);
    }
}