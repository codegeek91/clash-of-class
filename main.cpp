#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{
    int windowWidth{384};
    int windowHeight{384};

    // initialize window
    InitWindow(windowWidth, windowHeight, "Clash of Class");

    Character knight{windowWidth, windowHeight};

    // load textures
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
        knight.tick(GetFrameTime());

        // check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}