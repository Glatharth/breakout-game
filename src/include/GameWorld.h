/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld struct and function declarations.
 * 
 * @copyright Copyright (c) 2025
 */
#pragma once
#include <stdint.h>

#include "GameEnemy.h"
#include "Ball.h"
#include "enums.h"
#include "Player.h"

extern uint64_t GAME_TIME;

typedef struct GameWorld {
    int life;
    State gameState;
    GameEnemy gameEnemy;
    Player player;
    Ball ball;
} GameWorld;

inline GameEnemy* getGameEnemy(GameWorld *gw) {
    return &gw->gameEnemy;
}

inline Player* getPlayer(GameWorld *gw) {
    return &gw->player;
}

inline Ball* getBall(GameWorld *gw) {
    return &gw->ball;
}

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void );

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw );

/**
 * @brief Reads user input and updates the state of the game.
 */
void updateGameWorld( GameWorld *gw, float delta );

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw );

void drawGameLayout(GameWorld *gw);

void drawPlayerStats(GameWorld *gw);

void updateLife(GameWorld *gw);

void toastyAnimation();