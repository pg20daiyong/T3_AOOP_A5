#pragma once


#include "EngineInterface.h"
#include "EngineTypes.h"
#include "Bounds.h"
#include "ActorFactory.h"
#include "ComponentBase.h"
#include <vector>

class TransformComponent;

class Actor
{
    FACTORIZE

public:
    virtual void Update(float dt) = 0;
    
    int         GetID() const { return mID; }

    bool IsActive() const;
    void SetActive(bool active);

    void AddComponent(ComponentBase* component);
    void RemoveComponent(ComponentType type);

    template <typename T>
    T* GetComponent(ComponentType type) const;

    TransformComponent* GetTransform() const;

protected:
    int mID;

    bool mIsActive;

    std::vector<ComponentBase*> mComponents;

    TransformComponent* mTransform;

    Actor(int id, bool isActive = true);
};