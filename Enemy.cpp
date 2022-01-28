#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    worldPos = pos;
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 3.5f;
}

void Enemy::tick(float deltaTime)
{
    // calculate vector for enemy movement and normalize
    Vector2 toTarget = Vector2Normalize(Vector2Subtract(target -> getScreenPos(), screenPos));

    // adding speed
    toTarget = Vector2Scale(toTarget, speed);

    // moving enemy
    worldPos = Vector2Add(worldPos, toTarget);

    screenPos = Vector2Subtract(worldPos, target -> getWorldPos());
    BaseCharacter::tick(deltaTime);
}