#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include <stdio.h> //bra för att få tag på 'NULL', lol mannen
#include "raylib.h"
#include "world.h"

void entity_createUndefined(World *world, Vector2 position);
void entity_createWall(World *world, Vector2 position);
void entity_createEnemy(World *world, Vector2 position);
void entity_createBIGCHEESE(World *world, Vector2 position);

#endif