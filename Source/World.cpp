#include "World.h"
#include "EngineInterface.h"
#include "ActorFactoryImpl.h"
#include "ActorPoolImpl.h"
#include "ActorImpl.h"
#include "AlienShip.h"
#include "Ship.h"
#include "EventSystem.h"
#include "Callbacks.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

World* World::sWorld = nullptr;

void ShootCallback(const IEventArgs& shootEvt);
void CollisionCallback(const IEventArgs& collisionEvt);

World* World::GetInstance()
{
    if (sWorld == nullptr)
    {
        sWorld = new World();
    }
    return sWorld;
}

World::~World()
{

}

void World::Initialize()
{
    mPlayerLives = 3;
    mPlayerScore = 0;
    mPlayedTime = 0.0f;

    SetupAlienShip();
    SetupShip();
    SetupBulletPool();
    SetupAsteroidManager();
    SetupCallbacks();
}

void World::Update(float deltaTime)
{
    if (mGameState == GameState::Playing)
    {
        mPlayedTime += deltaTime;

        mAsteroidMgr.Update(deltaTime);

        for (ActorHandle* handle : mActors)
        {
            if (handle->IsValid())
            {
                if (handle->GetActor()->IsActive())
                {
                    handle->GetActor()->Update(deltaTime);
                }
            }
        }

        for (ActorHandle* handle : mActors)
        {
            if (handle->IsValid())
            {
                auto* collider = handle->GetActor()->GetComponent<ColliderComponent>(ComponentType::Collider);
                if (handle->GetActor()->IsActive() && collider != nullptr)
                {
                    collider->Update(deltaTime);
                }
            }
        }

        for (ActorHandle* handle : mActors)
        {
            if (handle->IsValid())
            {
                auto* render = handle->GetActor()->GetComponent<RenderComponent>(ComponentType::Rendering);
                if (handle->GetActor()->IsActive())
                {
                    render->Update(deltaTime);
                }
            }
        }
    }  
}

void World::PostUpdate()
{
    if (mGameState == GameState::Playing)
    {
        for (ActorHandle* handle : mActors)
        {
            if (handle->IsValid())
            {
                auto* collider = handle->GetActor()->GetComponent<ColliderComponent>(ComponentType::Collider);
                if (handle->GetActor()->IsActive() && collider != nullptr)
                {
                    collider->PostUpdate();
                }
            }
        }
    }
}

void World::HurtPlayer(int damage)
{
    mPlayerLives -= damage;

    if (mPlayerLives <= 0)
    {
        mGameState = GameState::GameOver;
    }
    else
    {
        if (mActors[mShipID]->IsValid())
        {
            Ship* ship = static_cast<Ship*>(mActors[mShipID]->GetActor());
            ship->PlayHurt();
        }
    }
}

void World::AddActor(Actor* actor)
{
    mActors.push_back(new ActorHandle(actor));
}

void World::SetupAlienShip()
{
    auto alienShip = ACTORFAC->CreateActor<AlienShip>();
    mAlienShipID = alienShip->GetID();
    alienShip->Initialize();
}

void World::SetupShip()
{
    auto ship = ACTORFAC->CreateActor<Ship>();
    mShipID = ship->GetID();
    ship->Initialize();
}

void World::SetupBulletPool()
{
    mBulletPoolSize = 10;
    mBulletPool = new ActorPool<Bullet>(); 
    mBulletPool->InitializePool(mBulletPoolSize);
    mAlienBulletPool = new ActorPool<AlienBullet>();
    mAlienBulletPool->InitializePool(mBulletPoolSize);
}

void World::SetupAsteroidManager()
{
    // lambda 
    auto generator = [this]() -> exVector2
    {
        exVector2 target = exVector2((rand() % 150) - 75, 0);
        if (mActors[mShipID]->IsValid())
        {
            auto shipTransfom = mActors[mShipID]->GetActor()->GetTransform();
            target.x += shipTransfom->GetPosition().x;
            target.y += shipTransfom->GetPosition().y;
        }
        return target;
        
    };

    mAsteroidMgr.Initialize(20, 2.0f, generator);
}

void World::SetupCallbacks()
{
    EVTSYS->StartListening(EventTypes::Shoot, &ShootCallback);
    EVTSYS->StartListening(EventTypes::Collision, &CollisionCallback);
}