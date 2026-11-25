#include <stdio.h>
#include <string.h>
#include "world.h"

void world_Init(World *world) {

    //fresh start (complete wipe, hopefully)
    memset(world, 0, sizeof(world));
}

Entity world_CreateEntity(World *world) {

    //Purpose: increments the entityCount to keep track on the amount of entities created and avoid going over MAX_ENTITIES...

    if (world->entityCount >= MAX_ENTITIES) {printf("Entity limit reached.\nShit's cooked, dawg!"); return MAX_ENTITIES;}
    else {
        uint32_t entityID = world->entityCount;
        world->entityCount += 1;
        return entityID;
    }

}