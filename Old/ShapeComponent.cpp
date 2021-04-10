#include "ShapeComponent.h"

void ShapeComponent::MoveBy(const b2Vec2& deltaOffset)
{
    for(auto& point : mPoints)
    {
        point = point + deltaOffset;
    }
}