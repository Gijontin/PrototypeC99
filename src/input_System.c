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

void spacebarLogic(World *world, uint32_t id){
    if (IsKeyPressed(KEY_SPACE)) {
    //PLATFORMER MODE
        if (world->movements[id].isGrounded && world->movements[id].gravity > 0.0f) {
            world->movements[id].wantsToJump = true;
        } 
    //TOP-DOWN MODE
        else {}
    }
}

/*
AI explaining how the binary bitshift-mask-shid comparison logic works with the if check and need for a variable like 'required':

0101  (entity's mask: Transform + Render)
& 0011  (required mask: Transform + Movement)
------
  0001  (Result: 0001 != 0011 -> Evaluates to FALSE, entity is skipped)

*/
void inputSystem_Update(World *world) {

    uint32_t required = COMP_TRANSFORM | COMP_MOVEMENT | COMP_PLAYER_INPUT;

    for (uint32_t i = 0; i < world->entityCount; i++) {
    
        if ((world->masks[i] & required) != required) {continue;}

    //WASD-movement + Shift(sprint)
        world->movements[i].direction = input_GetDirection();
        world->movements[i].speedMultiplier = isSprinting() ? 1.5f : 1.0f;

        spacebarLogic(world, i);     
    }

}