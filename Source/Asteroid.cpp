#include "Asteroid.h"
#include "World.h"
#include "Constants.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "Game.h"

Asteroid::Asteroid(int id)
    : IPoolableActor(id)
{
    auto colliderComponent = new ColliderComponent(id);
    colliderComponent->SetTag(CollisionTag::ASTEROID);

    AddComponent(colliderComponent);

    auto renderComponent = new RenderComponent(id);
    renderComponent->SetShapeType(ShapeType::CoreSquare);
    renderComponent->SetColor(exColor(77, 38, 0));

    AddComponent(renderComponent);
}

void Asteroid::Initialize()
{
    auto wSize = WORLD->GetWorldSize();

    auto size = exVector2(40, 40);
    GetTransform()->SetSize(size);
}

void Asteroid::Respawn()
{
    mIsActive = true;
#if VERBOSE
    printf("Asteroid - Asteoird %d has been respawned\n", mID);
#endif
}

void Asteroid::Update(float dt)
{
    UpdateMovement(dt);
    CheckOutOfScreen();
}

void Asteroid::Launch(exVector2 position, exVector2 direction, float speed)
{
    mTransform->SetPosition(position);
    mDirection = direction;
    mSpeed = speed;
#if VERBOSE
    printf("Asteroid - Asteroid %d has been launched from %f.2, %f.2 at %f.3, %f.3\n", 
        mID, position.x, position.y, mDirection.x, mDirection.y);
#endif

}

void Asteroid::UpdateMovement(float dt)
{
    mTransform->Translate(exVector2(mDirection.x * mSpeed * dt, mDirection.y * mSpeed * dt));
}

void Asteroid::CheckOutOfScreen()
{
    float halfSizeY = mTransform->GetSize().y / 2;
    if (mTransform->GetPosition().y - halfSizeY > kViewportHeight)
    {
#if VERBOSE
        printf("Asteroid - Asteroid %d has been removed because is out of screen\n", mID);
#endif
        mIsActive = false;
    }
}
