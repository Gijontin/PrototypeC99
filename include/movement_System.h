#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "raylib.h"
#include "movement_Component.h"
#include "transform_Component.h"
#include "collider_Component.h"
#include "world.h"

void movementSystem_Update(World *world, float dt);
//void movementSystem_Update(transform_Component *tc, movement_Component *mc, float dt);

#endif