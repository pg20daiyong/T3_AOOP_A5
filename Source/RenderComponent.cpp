#include "RenderComponent.h"
#include "Actor.h"
#include "TransformComponent.h"
#include "Game.h"

RenderComponent::RenderComponent(int actorID)
    : ComponentBase(actorID)
    , mShape(ShapeType::Square)
{

}

void RenderComponent::Update(float deltaTime)
{
    auto engine = Game::GetInstance()->GetEngine();
    auto t = GetOwner()->GetTransform();
    auto bounds = t->GetBounds();
    switch (mShape)
    {
    case ShapeType::Square:
    {
        engine->DrawBox(bounds.min, bounds.max, mColor, 0);
        break;
    }
    case ShapeType::CoreSquare:
    {
        engine->DrawLineBox(bounds.min, bounds.max, mColor, 0);
        exVector2 halfSize = exVector2(t->GetSize().x / 2, t->GetSize().y / 2);

        auto coreBounds = bounds;
        coreBounds.min.x += halfSize.x / 2.0f;
        coreBounds.min.y += halfSize.y / 2.0f;

        coreBounds.max.x -= halfSize.x / 2.0f;
        coreBounds.max.y -= halfSize.y / 2.0f;

        engine->DrawBox(coreBounds.min, coreBounds.max, mColor, 0);
        break;
    }
    default:
        break;
    }
}