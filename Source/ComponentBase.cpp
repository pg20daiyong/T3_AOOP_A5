#include "ComponentBase.h"
#include "Actor.h"
#include "World.h"

ComponentBase::ComponentBase(int actorID) :
    mActorID(actorID)
{}

Actor* ComponentBase::GetOwner() const
{
    if (WORLD->GetActor(mActorID)->IsValid())
    {
        return WORLD->GetActor(mActorID)->GetActor();
    }
    return nullptr;    
}