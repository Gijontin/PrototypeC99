#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "world.h"

extern Entity player;

void player_Init(World *world, Entity *player, Vector2 spawnPos);

#endif