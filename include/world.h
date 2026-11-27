#ifndef WORLD_H
#define WORLD_H

#include <stdint.h>
#include "config.h"
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
    Vector2 worldGrid[MAX_COLS * MAX_ROWS];
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
bool world_DestroyEntity(World *world, Entity id);
void world_CubeWallFloorSpawner(World *world);
void world_Debug(const World *world, bool beEfficient, bool show);

//static skapar en tillgänglig kopia för alla som använder headern och inline gör nått skit så att matten används och körs direkt ifrån headern eller nått
//ska vara effektivare när det är små kalkulationer som görs...
static inline Vector2 world_TileInputToPosition(uint32_t col, uint32_t row) {
    
    if (col >= MAX_COLS || row >= MAX_ROWS) {return (Vector2){0, 0};}

    return (Vector2){col * TILESIZE, (row + 1) * TILESIZE};
}
static inline Vector2 world_SnapPosToTile(Vector2 position) {
    //effectively just a snap-2-tile anchor function shid

    //bad LLM om en sjukare lösning på min simpla guard med samma effekt and it delivered:
        //så, med en dubbel-typecast FRÅN SIGNED(int32_t) TILL UNSIGNED(uint32_t) - ORDNINGEN LÄSES INNIFRÅN OCH UT - så blir negative (tal) floats integer overflows till typ max summan vilket är långt över screen-height/-width
        //samtidigt som att en unsigned type inte tillåter värde under 0 så det blir en position < 0 check samtidigt ...sjukt, indeed
    if ((uint32_t)(int32_t)position.x >= SCREENWIDTH || (uint32_t)(int32_t)position.y >= SCREENHEIGHT) {return (Vector2){0, 0};}

    uint32_t col = (uint32_t)(position.x / TILESIZE);
    uint32_t row = (uint32_t)(position.y / TILESIZE);

    return (Vector2){col * TILESIZE, (row + 1) * TILESIZE};
}

#endif