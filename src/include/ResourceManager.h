/**
 * @file ResourceManager.h
 * @author Prof. Dr. David Buzatto
 * @brief ResourceManager struct and function declarations.
 * 
 * @copyright Copyright (c) 2025
 */
#pragma once

#include "raylib/raylib.h"

typedef struct ResourceManager {
    Texture2D cuteDavi;
    Sound deadEnemy;
    Sound gameOver;
    Sound lostLife;
    Sound hitPlayer;
    Sound toasty;
    Music blessCode;
    Music inGame;
} ResourceManager;

/**
 * @brief Global ResourceManager instance.
 */
extern ResourceManager rm;

/**
 * @brief Load global game resources, linking them in the global instance of
 * ResourceManager called rm.
 */
void loadResourcesResourceManager( void );

/**
 * @brief Unload global game resources.
 */
void unloadResourcesResourceManager( void );