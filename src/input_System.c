#include "input_System.h"

#define DIAG_MOVEMENT_NORMALIZATION 0.70710678f

Vector2 input_GetDirection(){

    static Vector2 lastDirection = {0.0f, 0.0f};

//Last Input Priority Logic:
    if (IsKeyPressed(KEY_A)) { lastDirection.x = -1; }
    if (IsKeyPressed(KEY_D)) { lastDirection.x = 1; }
    if (IsKeyPressed(KEY_W)) { lastDirection.y = -1; }
    if (IsKeyPressed(KEY_S)) { lastDirection.y = 1; }

    Vector2 direction = {0.0f, 0.0f};

//X (LEFT & RIGHT)
    if (IsKeyDown(KEY_A) && IsKeyDown(KEY_D)) { direction.x = lastDirection.x; }
        else if (IsKeyDown(KEY_A)) { direction.x = -1; }
        else if (IsKeyDown(KEY_D)) { direction.x = 1; }
//Y (UP & DOWN)
    if (IsKeyDown(KEY_W) && IsKeyDown(KEY_S)) { direction.y = lastDirection.y; } 
        else if (IsKeyDown(KEY_W)) { direction.y = -1; } 
        else if (IsKeyDown(KEY_S)) { direction.y = 1; }

    if (direction.x != 0 && direction.y != 0) {
            direction.x *= DIAG_MOVEMENT_NORMALIZATION;
            direction.y *= DIAG_MOVEMENT_NORMALIZATION;
    }
    
    return direction;
}

bool isSprinting(){
    return IsKeyDown(KEY_LEFT_SHIFT);
}

void inputSystem_Update(World *world, Entity player) {
    world->movements[player].direction = input_GetDirection();
    world->movements[player].speedMultiplier = isSprinting() ? 1.5 : 1;

    //mc->direction = input_GetDirection();
    //mc->speedMultiplier = isSprinting() ? 1.5 : 1;
}