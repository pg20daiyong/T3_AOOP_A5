#pragma once
#include "actor.h"

class AlienShip : public Actor
{
FACTORIZE

public:
    void Initialize();

    void Update(float dt) override;

    void PlayHurt();

private:
    AlienShip(int id);
    void Search(float delta);
    void Shot(float delta);
    void RunAway(float delta);

    float ClampPosition(float delta);
    float RunAwayPosition(float delta);
 
    float mShootFrequency;
    float mShootCooldown;
    float mSpeed;

    exColor mNormalColor;
    exColor mHurtColor;
    float mHurtTimer;


};