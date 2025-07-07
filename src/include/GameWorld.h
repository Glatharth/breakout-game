/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld struct and function declarations.
 * 
 * @copyright Copyright (c) 2025
 */
#pragma once
#include "GameEnemy.h"
#include <stdint.h>
#include "Ball.h"
#include "enums.h"
#include "Player.h"

typedef struct GameWorld {
    uint64_t time;
    int score;
    int roundNumber;
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

// inline int getRoundNumber(GameWorld *gw) {
//     return gw->roundNumber;
// }

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

void updateScore(GameWorld *gw);

void drawGameLayout(GameWorld *gw);

void drawPlayerStats(GameWorld *gw);

void updateLife(GameWorld *gw);