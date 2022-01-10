#include "Bullet.h"
#include "World.h"
#include "Constants.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

Bullet::Bullet(int id)
    : IPoolableActor(id)
    , mSpeed(0)
{
    auto colliderComponent = new ColliderComponent(id);
    colliderComponent->SetTag(CollisionTag::BULLET);

    AddComponent(colliderComponent);

    auto renderComponent = new RenderComponent(id);
    renderComponent->SetColor(exColor(51, 51, 255));

    AddComponent(renderComponent);
}

void Bullet::Initialize()
{
    auto size = exVector2(10, 20);
    GetTransform()->SetSize(size);
}

void Bullet::Respawn()
{
#if VERBOSE
    printf("BULLET - Bullet %d has been respawned\n", mID);
#endif
    mIsActive = true;
}

void Bullet::Update(float dt)
{
    UpdateMovement(dt);
    CheckOutOfScreen();
}

void Bullet::Shoot(exVector2 position, float speed)
{
    mTransform->SetPosition(position);
    mSpeed = speed;
}

void Bullet::UpdateMovement(float dt)
{
    mTransform->Translate(exVector2(0, -mSpeed * dt));
}

void Bullet::CheckOutOfScreen()
{
    float halfSizeY = mTransform->GetSize().y / 2;
    if (mTransform->GetPosition().y + halfSizeY < 0)
    {
#if VERBOSE
        printf("BULLET - Bullet %d has been removed because it out of screen\n", mID);
#endif

        mIsActive = false;
    }
}