#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

int main()
{
    int windowWidth{384};
    int windowHeight{384};

    // initialize window
    InitWindow(windowWidth, windowHeight, "Clash of Class");

    Character knight{windowWidth, windowHeight};

    Enemy goblin{
        Vector2{0.f, 0.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    goblin.setTarget(&knight);

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}
    };

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

        // draw the props
        for(auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        knight.tick(GetFrameTime());

        // check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        // check props collisions
        for(auto prop : props)
        {
            if (CheckCollisionRecs(knight.getCollisionRec(), prop.getCollisionRec(knight.getWorldPos()))){
                knight.undoMovement();
            }
        }

        goblin.tick(GetFrameTime());

        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}