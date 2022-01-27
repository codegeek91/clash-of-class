#include "raylib.h"

class Enemy
{
    public:
        Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
        Vector2 getWorldPos() {return worldPos;}
        void tick(float deltaTime);
        void undoMovement();
        Rectangle getCollisionRec();
    private:
        Texture2D texture{};
        Texture2D idle{};
        Texture2D run{};
        Vector2 worldPos{};
        Vector2 screenPos{};
        Vector2 worldPosLastFrame{};
        // 1: facing right, -1: facing left
        float rightLeft {1.f};
        // animation variables
        float runningTime{};
        int frame{};
        int maxFrames{6};
        float updateTime{1.f/12.f};
        float speed{4.f};
        float width{};
        float height{};
        float scale{4.0f};
};