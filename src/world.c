#include <stdio.h>
#include <string.h>
#include "world.h"

void world_Init(World *world) {

    //fresh start (complete wipe, hopefully)
    memset(world, 0, sizeof(*world));
}

Entity world_CreateEntity(World *world) {

    //Purpose: increments the entityCount to keep track on the amount of entities created and avoid going over MAX_ENTITIES...

    //Scan for empty entityCount slot before assigning one from the "end" of the counter and incrementing...
    for (uint32_t i = 0; i < world->entityCount; i++) {
        if (world->masks[i] == COMP_NONE) {
            return i;
        }
    }

    //After the scan for empty slots falls through we check if we've actually reached max limit...
    if (world->entityCount >= MAX_ENTITIES) {printf("Entity limit reached.\nShit's cooked, dawg!"); return MAX_ENTITIES;}
    
    //Should be safe to execute this part, if both the safety check AND the scan falls through...
    uint32_t entityID = world->entityCount;
    world->entityCount += 1;
    return entityID;

    /* Look into generational 16bit x 16bit IDs to solve future "dangling IDs" problems */
}

void world_DestroyEntity(World *world, Entity id) {
    if (id < MAX_ENTITIES && world->masks[id] != COMP_NONE) {
        world->masks[id] = COMP_NONE;
    }
}