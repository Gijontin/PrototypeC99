#ifndef WORLD_H
#define WORLD_H

#include <stdint.h>
#include "transform_Component.h"
#include "movement_Component.h"
#include "render_Component.h"

#define MAX_ENTITIES 256

typedef uint32_t Entity;

typedef struct {
    transform_Component transforms[MAX_ENTITIES];
    movement_Component movements[MAX_ENTITIES];
    render_Component renders[MAX_ENTITIES];
    uint32_t entityCount;
} World;

void world_Init(World *world);
Entity world_CreateEntity(World *world);

#endif