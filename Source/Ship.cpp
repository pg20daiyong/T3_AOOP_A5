#include "Ship.h"
#include "World.h"
#include "InputManager.h"
#include "Constants.h"
#include "EventSystem.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "ActorImpl.h"

Ship::Ship(int id) : Actor(id)
{
    auto colliderComponent = new ColliderComponent(id);
    colliderComponent->SetTag(CollisionTag::SHIP);

    AddComponent(colliderComponent);

    auto renderComponent = new RenderComponent(id);
    renderComponent->SetColor(exColor(66, 33, 0));

    AddComponent(renderComponent);
}

void Ship::Initialize()
{
    auto wSize = WORLD->GetWorldSize();
    int padding = 10;

    auto size = exVector2(50, 20);
    GetTransform()->SetSize(size);
    GetTransform()->SetPosition(exVector2(wSize.x / 2.0f, wSize.y - size.y - padding));

    mNormalColor = exColor(66, 33, 0);
    mHurtColor = exColor(255, 0, 0);
    mHurtTimer = 0;

    mSpeed = 100;

    mShootFrequency = 1.0f;

    mShootCooldown = 0.0f;
}

void Ship::Update(float dt)
{
    CheckMovement(dt);

    CheckShoot(dt);

    CheckHurtRoutine(dt);
}

void Ship::PlayHurt()
{
    auto rendering = GetComponent<RenderComponent>(ComponentType::Rendering);
    rendering->SetColor(mHurtColor);
    mHurtTimer = HURT_DURATION;
}

void Ship::CheckMovement(float dt)
{
    if (INPUT->IsMovingLeft())
    {
        mTransform->Translate(exVector2(ClampPosition(mSpeed * dt * -1), 0));
    }

    if (INPUT->IsMovingRight())
    {
        mTransform->Translate(exVector2(ClampPosition(mSpeed * dt), 0));
    }
}

void Ship::CheckShoot(float dt)
{
    mShootCooldown -= dt;
    if (INPUT->IsShooting() && mShootCooldown <= 0.0f)
    {
        mShootCooldown = mShootFrequency;
        
        auto transform = GetComponent<TransformComponent>(ComponentType::Transform);
        auto pos = transform->GetPosition();
        auto size = transform->GetSize();
        ShootEventArgs args = { exVector2(pos.x, pos.y - size.y) };
        EVTSYS->Trigger(EventTypes::Shoot, args);
    }
}

void Ship::CheckHurtRoutine(float dt)
{
    if (mHurtTimer > 0.0f)
    {
        mHurtTimer -= dt;
        if (mHurtTimer <= 0.0f)
        {
            auto rendering = GetComponent<RenderComponent>(ComponentType::Rendering);
            rendering->SetColor(mNormalColor);
        }
    }
}

float Ship::ClampPosition(float delta)
{
    auto pos = mTransform->GetPosition();

    float halfSizeX = mTransform->GetSize().y / 2;

    if ((delta < 0.0f && (pos.x - halfSizeX + delta) < 0) ||
        (delta > 0.0f && (pos.x + halfSizeX + delta) > kViewportWidth))
    {
        return 0.0f;
    }
    return delta;
}