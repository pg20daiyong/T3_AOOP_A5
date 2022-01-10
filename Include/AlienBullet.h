#pragma once

#include "IPoolableActor.h"

class AlienBullet : public IPoolableActor
{
    FACTORIZE

public:
    void Initialize() override;
    void Respawn() override;
    void Update(float dt) override;

    void Shoot(exVector2 position, float speed);

private:
    AlienBullet(int id);

    void UpdateMovement(float dt);
    void CheckOutOfScreen();

    float mSpeed;
};