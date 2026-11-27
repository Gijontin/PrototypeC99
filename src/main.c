#include "project.h"

int main(void){
    //debug prototype-calls
    void debug_displayFPS();
    void debug_displayPlayerPosition(const World *world, Entity player, Vector2 position, int fontsize);
    void debug_displayActiveEntities(const World *world, Vector2 position, int fontsize);

    //1280x720, kinda baseline 720p resolution, but can easily scale to 1080, 1440, and 4K by multiplying with 1.5x, 2x, or 3x (respectively)
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "PrototypeC99");
    SetTargetFPS(60);

    bool debugIsOn = false;

    World world = {0};
    world_Init(&world);
    player_Init(&world, &player, world_TileInputToPosition(MAX_COLS * 0.5, MAX_ROWS * 0.5));

    world_CubeWallFloorSpawner(&world);

    while (!WindowShouldClose()){
    //Toggle Debug
        if (IsKeyPressed(KEY_B)){
            debugIsOn = !debugIsOn;
        }
    //Delta Time calc, normalized even further to Pixels Per Second
        float deltaTime = GetFrameTime() * 60.0f; 
    
    //Updaters
        cursor_Update(&cursorPosition);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            entity_createBIGCHEESE(&world, world_SnapPosToTile(cursorPosition));
        }

        inputSystem_Update(&world);
        movementSystem_Update(&world, deltaTime);
        collisionSystem_Update(&world);
        resolveSystem_Update(&world);

        BeginDrawing();

            ClearBackground(BEIGE);
            cursor_Debug();
            renderSystem_Draw(&world);
            world_Debug(&world, true, debugIsOn);
            debug_displayFPS();
            debug_displayPlayerPosition(&world, player, (Vector2){5.0f, 20.0f * 2}, 20);
            debug_displayActiveEntities(&world, (Vector2){5.0f, 20.0f * 3}, 20);

        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}

void debug_displayFPS(){
    int fontsize = 25;
    int fps = GetFPS();
    const char *text = TextFormat("%dFPS", fps);
    int textWidth = MeasureText(text, fontsize);
    
    DrawText(text, GetScreenWidth() - textWidth - 10, 5, fontsize, BLACK);
}
void debug_displayPlayerPosition(const World *world, Entity player, Vector2 position, int fontsize) {
    const char *text = TextFormat("PlayerPosition: %1.fx, %1.fy", world->transforms[player].position.x, world->transforms[player].position.y);
    int textWidth = MeasureText(text, fontsize);
    
    DrawText(text, position.x, position.y, fontsize, BLACK);
}
void debug_displayActiveEntities(const World *world, Vector2 position, int fontsize) {
    const char *text = TextFormat("Active entities: %d", world->entityCount);
    int textWidth = MeasureText(text, fontsize);

    DrawText(text, position.x, position.y, fontsize, BLACK);
}