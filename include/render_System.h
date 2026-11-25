#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "raylib.h"
#include "transform_Component.h"
#include "render_Component.h"
#include "world.h"

void renderSystem_Draw(const World *world);
//void renderSystem_Draw(const transform_Component *tc, const render_Component *rc);

#endif