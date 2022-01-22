#include "raylib.h"
#include "raymath.h"

class Character
{
    public:
        Vector2 getWorldPos() {return worldPos;}
        void setScreenPos(int windowWidth, int windowHeight);
        void tick(float deltaTime);
    private:
        Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
        Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
        Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
        Vector2 screenPos{};
        Vector2 worldPos{};
        // 1: facing right, -1: facing left
        float rightLeft {1.f};
        // animation variables
        float runningTime{};
        int frame{};
        const int maxFrames{6};
        const float updateTime{1.f/12.f};
        const float speed{4.f};
};

void Character::setScreenPos(int windowWidth, int windowHeight)
{
    screenPos = {
        (float)windowWidth/2.0f - 4.0f * (0.5f * (float)texture.width/6.0f),
        (float)windowHeight/2.0f - 4.0f * (0.5f * (float)texture.height)
    };
}

void Character::tick(float deltaTime)
{
    Vector2 direction{};
    if (IsKeyDown(KEY_A)) direction.x -= 1.0;
    if (IsKeyDown(KEY_D)) direction.x += 1.0;
    if (IsKeyDown(KEY_W)) direction.y -= 1.0;
    if (IsKeyDown(KEY_S)) direction.y += 1.0;

    if(Vector2Length(direction) != 0.0)
    {
        // set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

    // update animation frame
    runningTime += deltaTime;
    if(runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames) frame = 0;
    }

    // draw character
    Rectangle source{(float)texture.width/6 * frame, 0.f, rightLeft * (float)texture.width/6, (float)texture.height};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * (float)texture.width/6.0f, 4.0f * (float)texture.height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

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