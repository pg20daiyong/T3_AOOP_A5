#pragma once

enum class EventTypes
{
    Shoot,
    Collision
};

enum CollisionTag
{
    NONE,
    SHIP,
    BULLET,
    ASTEROID,
    ALIENSHIP,
    ALIENBULLET,
    COUNT
};

enum class GameState
{
    Playing,
    GameOver
};

enum ComponentType
{
    Transform,
    Collider,
    Rendering,
    Count
};

enum ShapeType
{
    Square,
    CoreSquare
};