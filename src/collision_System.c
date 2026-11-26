#include "collision_System.h"

//NOTE: Logic assume draws are made from BOTTOM-LEFT corner and UPWARDS
bool checkCollisionBetweenRecs(Rectangle a, Rectangle b) {
    return (a.x < (b.x + b.width))  &&  //A's left side vs B's right side (A coming from the right side cannot pass through B on B's right side)
           ((a.x + a.width) > b.x)  &&  //A's right side vs B's left side
           (a.y < (b.y + b.height)) &&  //A's bottom side vs B's top side (A coming from above cannot pass through B who's under)
           ((a.y + a.height) > b.y);    //A's top side vs B's bottom side
}

void collisionSystem_Update(World *world) {

    if (world->entityCount < 1) {return;}
    world->collisionPairBuffer = 0;
    uint32_t required = COMP_COLLIDER | COMP_TRANSFORM;

    //undvik att jämföra (i == j) och (0  vs 1 OCH SEDAN 1 vs 0) - sparar mycket compute om dessa "logikfel" undviks
    for (uint32_t i = 0; i < world->entityCount; i++) {

        if ((world->masks[i] & required) != required) {continue;}

        for (uint32_t j = i + 1; j < world->entityCount; j++) {

            if ((world->masks[j] & required) != required) {continue;}
            if (world->colliders[i].isImmovable && world->colliders[j].isImmovable) {continue;}

            if (checkCollisionBetweenRecs(world->colliders[i].collisionBox, world->colliders[j].collisionBox)) {
                if (world->collisionPairBuffer < (MAX_ENTITIES * 2)) {
                    world->collisionpairs[world->collisionPairBuffer++] = (collisionPair){i, j}; //increments after the line has been executed, neatly typecasts and adds i, j values into Entity A/B
                }
            }
        }
    }
}