#include "Actor.h"
#include "ActorImpl.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "Game.h"

Actor::Actor(int id, bool isActive)
    : mID(id)
    , mIsActive(isActive)
{
    mTransform = new TransformComponent(id);
    AddComponent(mTransform);
}

void Actor::AddComponent(ComponentBase* component)
{
    mComponents.push_back(component);
}

void Actor::RemoveComponent(ComponentType type)
{
    for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
    {
        if ((*it)->GetType() == type)
        {
            mComponents.erase(it);
            return;
        }
    }
}

bool Actor::IsActive() const 
{
    return mIsActive; 
}

void Actor::SetActive(bool active) 
{ 
    mIsActive = active; 
}

TransformComponent* Actor::GetTransform() const
{
    return mTransform;
}