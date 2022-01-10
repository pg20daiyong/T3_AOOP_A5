#include "ColliderComponent.h"
#include "World.h"
#include "Events.h"
#include "EventSystem.h"
#include "TransformComponent.h"

bool ColliderComponent::sCollisionLayer[CollisionTag::COUNT][CollisionTag::COUNT] =
{
    // NONE, SHIP, BULLET, ASTEROID, ALIENSHIP, ALIENBULLET
    { false, false, false, false, false, false }, // NONE
    { false, false, false, true , false, true }, // SHIP
    { false, false, false, true , false, false}, // BULLET
    { false, true,   true, false, false, false}, // ASTEROID
    { false, false, false, false, false, false}, // ALIENSHIP
    { false, false, false, false, false, false} //ALIENBULLET
};

ColliderComponent::ColliderComponent(int actorID)
    : ComponentBase(actorID)
{}

void ColliderComponent::Update(float deltaTime)
{
    if (!GetOwner()->IsActive())
    {
        return;
    }

    auto handles = WORLD->GetActors();

    mCollisions.clear();
    for (ActorHandle* other : handles)
    {
        if (!other->IsValid())
        {
            continue;
        }

        if (GetOwner() == other->GetActor())
        {
            continue;
        }

        auto otherCollider = other->GetActor()->GetComponent<ColliderComponent>(ComponentType::Collider);
        if (other->GetActor()->IsActive() && otherCollider != nullptr)
        {
            if (CheckCollision(otherCollider))
            {
                CollisionEventArgs evt = { this, otherCollider->GetTag() };
                mCollisions.push_back(evt);
            }
        }
    }
}

void ColliderComponent::PostUpdate()
{
    for (auto& collision : mCollisions)
    {
        EventSystem::GetInstance()->Trigger(EventTypes::Collision, collision);
    }
    mCollisions.clear();
}

Bounds ColliderComponent::GetBounds() const 
{ 
    return GetOwner()->GetTransform()->GetBounds(); 
}

bool ColliderComponent::CheckCollision(const ColliderComponent* other)
{
    if (other == nullptr)
    {
        return false;
    }

    return (sCollisionLayer[GetTag()][other->GetTag()] && GetBounds().collides(other->GetBounds()));
}