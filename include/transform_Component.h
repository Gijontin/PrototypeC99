#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "raylib.h"

typedef struct {
    Vector2 position;
    Vector2 size;
    float rotation;
} transform_Component;

#endif