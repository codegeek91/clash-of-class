#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{
    int windowWidth{384};
    int windowHeight{384};

    // initialize window
    InitWindow(windowWidth, windowHeight, "Clash of Class");

    Character knight;
    knight.setScreenPos(windowWidth, windowHeight);

    // load textures
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");

    Vector2 mapPos{0.0, 0.0};

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);
        knight.tick(GetFrameTime());

        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}