/**
 * @file GameWindow.c
 * @author Prof. Dr. David Buzatto
 * @brief GameWindow implementation.
 * 
 * @copyright Copyright (c) 2025
 */
#include <stdlib.h>
#include <stdbool.h>

#include "GameWindow.h"

#include <stdint.h>

#include "GameWorld.h"
#include "ResourceManager.h"
#include "raylib/raylib.h"
#include "GamePhysics.h"

/**
 * @brief Creates a dinamically allocated GameWindow struct instance.
 */
GameWindow* createGameWindow( 
        int width, 
        int height, 
        const char *title, 
        int targetFPS,
        bool antialiasing, 
        bool resizable, 
        bool fullScreen,
        bool undecorated, 
        bool alwaysOnTop, 
        bool invisibleBackground, 
        bool alwaysRun, 
        bool loadResources, 
        bool initAudio ) {

    GameWindow *gameWindow = (GameWindow*) malloc( sizeof( GameWindow ) );

    gameWindow->width = width;
    gameWindow->height = height;
    gameWindow->title = title;
    gameWindow->targetFPS = targetFPS;
    gameWindow->antialiasing = antialiasing;
    gameWindow->resizable = resizable;
    gameWindow->fullScreen = fullScreen;
    gameWindow->undecorated = undecorated;
    gameWindow->alwaysOnTop = alwaysOnTop;
    gameWindow->invisibleBackground = invisibleBackground;
    gameWindow->alwaysRun = alwaysRun;
    gameWindow->loadResources = loadResources;
    gameWindow->initAudio = initAudio;
    gameWindow->gw = NULL;
    gameWindow->initialized = false;

    return gameWindow;

}

/**
 * @brief Initializes the Window, starts the game loop and, when it
 * finishes, the window will be finished and destroyed too.
 */
void initGameWindow( GameWindow *gameWindow ) {

    if ( !gameWindow->initialized ) {

        gameWindow->initialized = true;

        if ( gameWindow->antialiasing ) {
            SetConfigFlags( FLAG_MSAA_4X_HINT );
        }

        if ( gameWindow->resizable ) {
            SetConfigFlags( FLAG_WINDOW_RESIZABLE );
        }

        if ( gameWindow->fullScreen ) {
            SetConfigFlags( FLAG_FULLSCREEN_MODE );
        }

        if ( gameWindow->undecorated ) {
            SetConfigFlags( FLAG_WINDOW_UNDECORATED );
        }

        if ( gameWindow->alwaysOnTop ) {
            SetConfigFlags( FLAG_WINDOW_TOPMOST );
        }

        if ( gameWindow->invisibleBackground ) {
            SetConfigFlags( FLAG_WINDOW_TRANSPARENT );
        }

        if ( gameWindow->alwaysRun ) {
            SetConfigFlags( FLAG_WINDOW_ALWAYS_RUN );
        }

        InitWindow( gameWindow->width, gameWindow->height, gameWindow->title );

        if ( gameWindow->initAudio ) {
            InitAudioDevice();
        }

        SetTargetFPS( gameWindow->targetFPS );    

        if ( gameWindow->loadResources ) {
            loadResourcesResourceManager();
        }

        gameWindow->gw = createGameWorld();

        GameWorld *gWorld = getGameWorld(gameWindow);

        SetMusicVolume(rm.inGame, 0.1f);

        // game loop
        while ( !WindowShouldClose() ) {
            if(gWorld->gameState == GAME_PAUSE || gWorld->gameState == GAME_OVER){
                if(IsKeyPressed(KEY_SPACE)){
                    TOASTY = 0;
                    gWorld->gameState = GAME_START;
                    gWorld->ball.vel.x = directionRandomizer();
                    gWorld->ball.vel.y = 150;
                    if(gWorld->life == 0){
                        gWorld->life = 3;
                        getPlayer(gWorld)->score = 0;
                        for(int i = 0; i < gWorld->gameEnemy.amount * gWorld->gameEnemy.line; i++){
                            if(gWorld->gameEnemy.enemies[i]->health <= 0){
                                int randomizeEnemyHealth = GetRandomValue(1, 10);
                                gWorld->gameEnemy.enemies[i]->health =  randomizeEnemyHealth <= 3 ? 300 : 100;
                            }
                        }
                    }
                }
            }else if(getGameEnemy(gWorld)->totalEnemies <= 0){
                gWorld->gameState = GAME_WIN;
            }else{
                updateGameWorld( gameWindow->gw, GetFrameTime() );
            }
            drawGameWorld( gameWindow->gw );
        }

        if ( gameWindow->loadResources ) {
            unloadResourcesResourceManager();
        }

        destroyGameWindow( gameWindow );

        if ( gameWindow->initAudio ) {
            CloseAudioDevice();
        }

        CloseWindow();

    }


}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWindow( GameWindow *gameWindow ) {
    destroyGameWorld( gameWindow->gw );
    free( gameWindow );
}