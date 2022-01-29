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
    velocity = Vector2Normalize(Vector2Subtract(target -> getScreenPos(), getScreenPos()));
    BaseCharacter::tick(deltaTime);
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target -> getWorldPos());
}