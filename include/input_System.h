#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include "raylib.h"
#include "movement_Component.h"
#include "world.h"

Vector2 input_GetDirection();
bool isSprinting();
void inputSystem_Update(World *world, Entity player);
//void inputSystem_Update(movement_Component *mc);

#endif