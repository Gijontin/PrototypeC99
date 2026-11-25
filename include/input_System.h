#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include "raylib.h"
#include "world.h"

Vector2 input_GetDirection();
bool isSprinting();
void inputSystem_Update(World *world);

#endif