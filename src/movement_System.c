#include "movement_System.h"

void movementSystem_Update(World *world, float dt) {
    
    uint32_t required = COMP_MOVEMENT | COMP_TRANSFORM;

    for (uint32_t i = 0; i < world->entityCount; i++) {
        if ((world->masks[i] & required) != required) {continue;}
        if (!world->movements[i].canMove) {continue;} 

    // X
        world->movements[i].velocity.x = world->movements[i].direction.x * (world->movements[i].speed * world->movements[i].speedMultiplier);
    
    // Y
    //PLATFORMER MODE (GRAVITY ON)
        if (world->movements[i].gravity > 0.0f) {
            
            //Jump request handling
            if (world->movements[i].wantsToJump && world->movements[i].isGrounded) {
                world->movements[i].isGrounded = false;
                world->movements[i].velocity.y = -world->movements[i].jumpForce;
            }
            
            //takes care of gravity properly applied when walking off edges, especially when not jumping (resolve still enables it so we good to set it to false here)
            world->movements[i].isGrounded = false;  

            //clamp maxFallSpeed to avoid unlimited acceleration whilst in-air
            if (world->movements[i].velocity.y < world->movements[i].maxFallSpeed) {
                world->movements[i].velocity.y += (world->movements[i].gravity * dt);
            } else {
                world->movements[i].velocity.y = world->movements[i].maxFallSpeed;
            }
            world->movements[i].wantsToJump = false;
        } 
    //TOP-DOWN MODE (GRAVITY OFF)
        else {
            world->movements[i].velocity.y = world->movements[i].direction.y * (world->movements[i].speed * world->movements[i].speedMultiplier);
        }

    //Update Position
        world->transforms[i].position.x += world->movements[i].velocity.x * dt;
        world->transforms[i].position.y += world->movements[i].velocity.y * dt;
    
    //Update Hurtbox/Hitbox Position
        if (world->masks[i] & COMP_COLLIDER) {
            world->colliders[i].collisionBox.x = world->transforms[i].position.x;
            world->colliders[i].collisionBox.y =  world->transforms[i].position.y;
        }

    }
}
/* void movementSystem_Update(transform_Component *tc, movement_Component *mc, float dt) {
    
    if (!mc->canMove) {return;}

    mc->velocity.x = mc->direction.x * (mc->speed * mc->speedMultiplier);
    mc->velocity.y = mc->direction.y * (mc->speed * mc->speedMultiplier);

    tc->position.x += mc->velocity.x * dt;
    tc->position.y += mc->velocity.y * dt;
    
} */