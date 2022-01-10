#pragma once

#include "Enums.h"
#include "Bounds.h"
#include "ComponentBase.h"
#include "Events.h"
#include <vector>

class ColliderComponent : public ComponentBase
{
public:
    ColliderComponent(int actorID);

    ComponentType GetType() override { return ComponentType::Collider; }

    void Update(float deltaTime) override;
    void PostUpdate() override;

    void SetTag(CollisionTag tag) { mTag = tag; }
    CollisionTag GetTag() const { return mTag; }

    Bounds GetBounds() const;
    
private:
    bool CheckCollision(const ColliderComponent* other);

    CollisionTag mTag = CollisionTag::NONE;

    static bool sCollisionLayer[CollisionTag::COUNT][CollisionTag::COUNT];

    std::vector<CollisionEventArgs> mCollisions;

};