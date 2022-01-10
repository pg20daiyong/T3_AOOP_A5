#pragma once

#include "ComponentBase.h"
#include "Bounds.h"

class RenderComponent : public ComponentBase
{
public:
    RenderComponent(int actorID);

    ComponentType GetType() override { return ComponentType::Rendering; }

    void Update(float deltaTime) override;

    exColor   GetPosition() const { return mColor; }
    ShapeType   GetShape() const { return mShape; }

    void SetColor(exColor color) { mColor = color; }
    void SetShapeType(ShapeType shape) { mShape = shape; }

private:
    exColor mColor;
    ShapeType mShape;
}; 
