#include "render_System.h"

void renderSystem_Draw(const World *world) {
    
    for (int i = 0; i < world->entityCount; i++) {
        if (!world->renders[i].isVisible) {continue;}

        switch (world->renders[i].type)
        {
        case RND_CIRCLE: {

        }
        break;
        case RND_REC: {
            DrawRectanglePro((Rectangle){
                world->transforms[i].position.x,
                world->transforms[i].position.y,
                world->transforms[i].size.x,
                world->transforms[i].size.y},
                (Vector2){0.0f, world->transforms[i].size.y},
                world->transforms[i].rotation,
                world->renders[i].color);
        }
        break;
        case RND_SPRITE: {

        }
        break;
        
        default:
            break;
        }
    }

}
/* void renderSystem_Draw(const transform_Component *tc, const render_Component *rc) {
    
    if (!rc->isVisible) {return;}

    switch (rc->type)
    {
    case RND_CIRCLE: {

    }
    break;
    case RND_REC: {
        DrawRectanglePro((Rectangle){tc->position.x, tc->position.y, tc->size.x, tc->size.y}, (Vector2){0.0f, tc->size.y} ,tc->rotation, rc->color);
    }
    break;
    case RND_SPRITE: {

    }
    break;
    
    default:
        break;
    }
} */