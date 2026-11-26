#ifndef WORLD_H
#define WORLD_H

#include <stdint.h>
#include "transform_Component.h"
#include "collider_Component.h"
#include "movement_Component.h"
#include "render_Component.h"

#define MAX_ENTITIES 256

typedef uint32_t Entity;


/* 
-- bit-shift:ade enum värden som agerar som flaggor för vilka components en entity har och inte har --

(man ser hur man bit-shiftar 1:an till vänster med '<<' och ett nummer )
Hur många decimaler varje enum har och Binary-koden i samma ordningsföljd som enum deklarationen, tack vare bit-shifting då:
0, 0000
1, 0001
2, 0010
4, 0100
8, 1000
*/
typedef enum {
    COMP_NONE = 0,
    COMP_TRANSFORM = 1 << 0,
    COMP_MOVEMENT = 1 << 1,
    COMP_RENDER = 1 << 2,
    COMP_PLAYER_INPUT = 1 << 3,
    COMP_COLLIDER = 1 << 4
} componentMask;

typedef struct {
    Entity A;
    Entity B;
} collisionPair;

typedef struct {
    transform_Component transforms[MAX_ENTITIES];
    collider_Component colliders[MAX_ENTITIES];
    movement_Component movements[MAX_ENTITIES];
    render_Component renders[MAX_ENTITIES];
    collisionPair collisionpairs[MAX_ENTITIES * 2]; // "* 2" you know why...
    uint32_t masks[MAX_ENTITIES];
    uint32_t entityCount;
    uint32_t collisionPairBuffer;
} World;

/*
masks use case exempel:

playern har de flesta components, och flertal bits får plats i ett element så:
world.masks[player] = COMP_TRANSFORM | COMP_MOVEMENT | COMP_RENDER | COMP_PLAYER_INPUT;

låt oss säga att en vägg-entitet fått id:t '3':
world.masks[3] = COMP_TRANSFORM | COMP_RENDER; //då har den bara transform för position och render för att ritas i programmet
*/

void world_Init(World *world);
Entity world_CreateEntity(World *world);

#endif