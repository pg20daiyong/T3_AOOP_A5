#include <chrono>
#include "AlienShip.h"
#include "World.h"
#include "EventSystem.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

AlienShip::AlienShip(int id) : Actor(id)
{
    auto renderComponent = new RenderComponent(id);
    renderComponent->SetColor(exColor(66, 33, 0));

    AddComponent(renderComponent);
}

void AlienShip::Initialize()
{
    auto wSize = WORLD->GetWorldSize();
    int padding = 10;

    auto size = exVector2(50, 20);
    GetTransform()->SetSize(size);
    // ~ Daiyong
    // position will be changed
    GetTransform()->SetPosition(exVector2(wSize.x / 2.0f,  size.y + padding)); 
    mNormalColor = exColor(66, 33, 0);
    mHurtColor = exColor(255, 0, 0);
    mHurtTimer = 0;

    mSpeed = 100;

    mShootFrequency = 1.0f;

    mShootCooldown = 0.0f;
}

void AlienShip::Update(float dt)
{
    void Search(float delta);
    void Shot(float delta);
    void RunAway(float delta);
}

void AlienShip::Search(float dt)
{
    // add move
    if(rand() % 100 > 50)
        mTransform->Translate(exVector2(ClampPosition(mSpeed * dt * -1), 0));
    else 
        mTransform->Translate(exVector2(ClampPosition(mSpeed * dt * +1), 0));
}

void AlienShip::Shot(float dt)
{
    mShootCooldown -= dt;
    if (mShootCooldown <= 0.0f)
    {
        mShootCooldown = mShootFrequency;
        auto transform = GetComponent<TransformComponent>(ComponentType::Transform);
        auto pos = transform->GetPosition();
        auto size = transform->GetSize();
        ShootEventArgs args = { exVector2(pos.x, pos.y + size.y) };
        EVTSYS->Trigger(EventTypes::Shoot, args);
    }
}

void AlienShip::RunAway(float dt)
{
}

float AlienShip::ClampPosition(float delta)
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

float AlienShip::RunAwayPosition(float delta)
{
    auto pos = mTransform->GetPosition();

    float halfSizeY = mTransform->GetSize().x / 2;

    //if ((delta < 0.0f && (pos.y - halfSizeY + delta) < 0) ||
    //    (delta > 0.0f && (pos.y + halfSizeY + delta) > kViewportWidth))
    //{
    //    return 0.0f;
    //}
    return delta;
}