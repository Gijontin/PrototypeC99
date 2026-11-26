#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include "raylib.h"

typedef struct {
    Rectangle collisionBox; //collidable area, usually transform_Component's size
    Vector2 offset;       //for re-adjusting the box in case needed (special enemies or realistic grounded hitboxes etc)
    bool isTrigger;       //trigger for item-pickup, dmg (trap?), "hardcoded" dialogue triggers etc...
    bool isImmovable;     //walls n shid, yo... (unless it's a special secret wall, ey, eeey?)
} collider_Component;

#endif