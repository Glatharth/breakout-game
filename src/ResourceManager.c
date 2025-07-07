/**
 * @file ResourceManager.c
 * @author Prof. Dr. David Buzatto
 * @brief ResourceManager implementation.
 * 
 * @copyright Copyright (c) 2025
 */
#include <stdio.h>
#include <stdlib.h>

#include "ResourceManager.h"
#include "raylib/raylib.h"

ResourceManager rm = { 0 };

void loadResourcesResourceManager( void ) {
    rm.cuteDavi = LoadTexture("resources/images/cuteDavi.png");
    rm.deadEnemy = LoadSound("resources/sfx/dead_enemy.wav");
    rm.gameOver = LoadSound("resources/sfx/game_over.wav");
    rm.lostLife = LoadSound("resources/sfx/lost_life.wav");
    rm.hitPlayer = LoadSound("resources/sfx/hit_player.wav");
    rm.toasty = LoadSound("resources/sfx/toasty.wav");
    rm.blessCode = LoadMusicStream("resources/musics/blessCode.ogg");
    rm.inGame = LoadMusicStream("resources/musics/inGame.ogg");
}

void unloadResourcesResourceManager( void ) {
    UnloadTexture(rm.cuteDavi);
    UnloadSound(rm.deadEnemy);
    UnloadSound(rm.gameOver);
    UnloadSound(rm.lostLife);
    UnloadSound(rm.hitPlayer);
    UnloadSound(rm.toasty);
    UnloadMusicStream(rm.blessCode);
    UnloadMusicStream(rm.inGame);
}