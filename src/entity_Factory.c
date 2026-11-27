#include "entity_Factory.h"

void entity_createWall(World *world, Vector2 position) {
    Entity wall = world_CreateEntity(world);
        world->transforms[wall] = (transform_Component) {
            .position = position,
            .size = {TILESIZE, TILESIZE},
            .rotation = 0.0f
        };
        world->colliders[wall] = (collider_Component) {
            .collisionBox = (Rectangle){
                    world->transforms[wall].position.x,
                    world->transforms[wall].position.y,
                    world->transforms[wall].size.x,
                    world->transforms[wall].size.y,
                },
            .isImmovable = true,
            .isTrigger = false,
            };
        world->renders[wall] = (render_Component) {
            .color = RED,
            .isVisible = true,
            .type = RND_REC,
            .texture = NULL,
            .zIndex = 0,
            };
        world->masks[wall] = 
            COMP_TRANSFORM | COMP_COLLIDER | COMP_RENDER;
}

void entity_createEnemy(World *world, Vector2 position) {

}

void entity_createBIGCHEESE(World *world, Vector2 position) {
    Entity cheese = world_CreateEntity(world);
        world->transforms[cheese] = (transform_Component) {
            .position = position,
            .size = {TILESIZE, TILESIZE},
            .rotation = 0.0f
        };
        world->colliders[cheese] = (collider_Component) {
            .collisionBox = (Rectangle){
                    world->transforms[cheese].position.x,
                    world->transforms[cheese].position.y,
                    world->transforms[cheese].size.x,
                    world->transforms[cheese].size.y,
                },
            .isImmovable = false,
            .isTrigger = true,
            };
        world->renders[cheese] = (render_Component) {
            .color = YELLOW,
            .isVisible = true,
            .type = RND_REC,
            .texture = NULL,
            .zIndex = 0,
            };
        world->masks[cheese] = 
            COMP_TRANSFORM | COMP_COLLIDER | COMP_RENDER;
}