#include "movement_System.h"

void movementSystem_Update(World *world, float dt) {
    
    for (int i = 0; i < world->entityCount; i++) {
        if (!world->movements[i].canMove) {continue;;}

        world->movements[i].velocity.x = world->movements[i].direction.x * (world->movements[i].speed * world->movements[i].speedMultiplier);
        world->movements[i].velocity.y = world->movements[i].direction.y * (world->movements[i].speed * world->movements[i].speedMultiplier);

        world->transforms[i].position.x += world->movements[i].velocity.x * dt;
        world->transforms[i].position.y += world->movements[i].velocity.y * dt;
    }
}
/* void movementSystem_Update(transform_Component *tc, movement_Component *mc, float dt) {
    
    if (!mc->canMove) {return;}

    mc->velocity.x = mc->direction.x * (mc->speed * mc->speedMultiplier);
    mc->velocity.y = mc->direction.y * (mc->speed * mc->speedMultiplier);

    tc->position.x += mc->velocity.x * dt;
    tc->position.y += mc->velocity.y * dt;
    
} */