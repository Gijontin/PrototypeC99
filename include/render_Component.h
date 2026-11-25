#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H 

#include "raylib.h"

typedef enum {
    RND_CIRCLE,
    RND_REC,
    RND_SPRITE
} RENDER_TYPE;

typedef struct {
    Color color;
    RENDER_TYPE type;
    Texture2D *texture;
    int zIndex;
    bool isVisible;
} render_Component;


#endif