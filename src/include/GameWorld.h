/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld struct and function declarations.
 * 
 * @copyright Copyright (c) 2025
 */
#pragma once
#include "GameEnemy.h"
#include "Ball.h"
#include "enums.h"
#include "Player.h"

typedef struct GameWorld {
    int dummy;
    int roundNumber;
    State gameState;
    GameEnemy gameEnemy;
    Player player;
    Ball ball;
} GameWorld;
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
