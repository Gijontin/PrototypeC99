#include "project.h"

int main(void){

    //1280x720, kinda baseline 720p resolution, but can easily scale to 1080, 1440, and 4K by multiplying with 1.5x, 2x, or 3x (respectively)
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "PrototypeC99");
    SetTargetFPS(60);

    World world = {0};
    world_Init(&world);

    Entity player = world_CreateEntity(&world); //sets player (ID) to 0 and bump up the world.entityCount to 1 (which will assign ID '1' to next Entity)
        world.transforms[player] = (transform_Component) {
            .position = {SCREENWIDTH * 0.5, SCREENHEIGHT * 0.5},
            .size = {TILE64, TILE64},
            .rotation = 0.0f,
            };
        world.movements[player] = (movement_Component) {
            .speed = 4.0f,
            .speedMultiplier = 1.5f,
            .canMove = true,

            .gravity = 0.60f,
            .jumpForce = 15.0f,
            .maxFallSpeed = 20.0f, //keep it below half of a tilesize...
            .isGrounded = false,
            };
        world.colliders[player] = (collider_Component) {
            .collisionBox = (Rectangle){
                    world.transforms[player].position.x,
                    world.transforms[player].position.y,
                    world.transforms[player].size.x,
                    world.transforms[player].size.y,
                },
            .isImmovable = false,
            .isTrigger = false,
            };
        world.renders[player] = (render_Component) {
            .color = BLUE,
            .isVisible = true,
            .type = RND_REC,
            .texture = NULL,
            .zIndex = 0,
            };
        world.masks[player] = 
            COMP_TRANSFORM | COMP_MOVEMENT | COMP_COLLIDER | COMP_RENDER | COMP_PLAYER_INPUT;
    Entity wall = world_CreateEntity(&world);
        world.transforms[wall] = (transform_Component) {
            .position = {500.0f, 200.0f},
            .size = {TILE64, TILE64},
            .rotation = 0.0f
        };
        world.colliders[wall] = (collider_Component) {
            .collisionBox = (Rectangle){
                    world.transforms[wall].position.x,
                    world.transforms[wall].position.y,
                    world.transforms[wall].size.x,
                    world.transforms[wall].size.y,
                },
            .isImmovable = true,
            .isTrigger = false,
            };
        world.renders[wall] = (render_Component) {
            .color = RED,
            .isVisible = true,
            .type = RND_REC,
            .texture = NULL,
            .zIndex = 0,
            };
        world.masks[wall] = 
            COMP_TRANSFORM | COMP_COLLIDER | COMP_RENDER;

    world_CubeWallFloorSpawner(&world);

    while (!WindowShouldClose()){

        float deltaTime = GetFrameTime() * 60.0f; //normalize speed regardless of fps

        cursor_Update(&cursorPosition);

        inputSystem_Update(&world);
        movementSystem_Update(&world, deltaTime);
        collisionSystem_Update(&world);
        resolveSystem_Update(&world);

        BeginDrawing();
            ClearBackground(BEIGE);
            DrawText(PROJECT_VERSION, 320, 180, 20, BLACK);
            DrawText(PROJECT_VERSION, 320, 180, 20, BLACK);
            cursor_Debug();
            renderSystem_Draw(&world);
            world_Debug(&world, true);
        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}