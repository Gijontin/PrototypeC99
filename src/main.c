#include "project.h"

int main(void){

    //1280x720, kinda baseline 720p resolution, but can easily scale to 1080, 1440, and 4K by multiplying with 1.5x, 2x, or 3x (respectively)
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Första Försöket");
    SetTargetFPS(60);

    World world = {0};
    Entity player = world_CreateEntity(&world); //sets player (ID) to 0 and bump up the world.entityCount to 1 (which will assign ID '1' to next Entity)
        world.transforms[player] = (transform_Component) {
            .position = {SCREENWIDTH * 0.5, SCREENHEIGHT * 0.5},
            .size = {40, 40},
            .rotation = 0.0f,
            };
        world.movements[player] = (movement_Component) {
            .speed = 4.0f,
            .speedMultiplier = 1.5f,
            .canMove = true,
            };
        world.renders[player] = (render_Component) {
            .color = BLUE,
            .isVisible = true,
            .type = RND_REC,
            .texture = NULL,
            .zIndex = 0,
            };


    while (!WindowShouldClose()){

        float deltaTime = GetFrameTime() * 60.0f; //normalize speed regardless of fps

        inputSystem_Update(&world, player);
        movementSystem_Update(&world, deltaTime);

        BeginDrawing();
            ClearBackground(BEIGE);
            DrawText(PROJECT_VERSION, 320, 180, 20, BLACK);
            renderSystem_Draw(&world);
        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}