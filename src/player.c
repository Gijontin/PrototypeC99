#include <stdio.h>
#include "config.h"
#include "player.h"

Entity player = 0;

void player_Init(World *world, Entity *player, Vector2 spawnPos){
    *player = world_CreateEntity(world); //sets player (ID) to 0 and bump up the world.entityCount to 1 (which will assign ID '1' to next Entity)

        world->transforms[*player] = (transform_Component) {
            .position = spawnPos,
            .size = {TILESIZE, TILESIZE},
            .rotation = 0.0f,
            };
        world->movements[*player] = (movement_Component) {
            .speed = 4.0f,
            .speedMultiplier = 1.5f,
            .canMove = true,

            .gravity = 0.0f, //0.60f felt pretty fine for a platformer
            .jumpForce = 15.0f,
            .maxFallSpeed = 20.0f, //keep it below half of a tilesize...
            .isGrounded = false,
            };
        world->colliders[*player] = (collider_Component) {
            .collisionBox = (Rectangle){
                    world->transforms[*player].position.x,
                    world->transforms[*player].position.y,
                    world->transforms[*player].size.x,
                    world->transforms[*player].size.y,
                },
            .isImmovable = false,
            .isTrigger = false,
            };
        world->renders[*player] = (render_Component) {
            .color = BLUE,
            .isVisible = true,
            .type = RND_REC,
            .texture = NULL,
            .zIndex = 0,
            };
        world->masks[*player] = 
            COMP_TRANSFORM | COMP_MOVEMENT | COMP_COLLIDER | COMP_RENDER | COMP_PLAYER_INPUT;
}