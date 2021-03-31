#include "RectShapeComponent.h"



RectShapeComponent::RectShapeComponent() : RectShapeComponent(b2Vec2{0, 0}, b2Vec2{0, 0})
{

}

RectShapeComponent::RectShapeComponent(const b2Vec2& topLeft, unsigned int width, unsigned int height)
{
    mPoints.push_back(topLeft);
    mPoints.push_back(b2Vec2(topLeft.x + width - 1, topLeft.y + height - 1));
}

RectShapeComponent::RectShapeComponent(const b2Vec2& topLeft, const b2Vec2& bottomRight)
{
    mPoints.push_back(topLeft);
    mPoints.push_back(bottomRight);
}

void RectShapeComponent::MoveTo(const b2Vec2& position)
{
    float width = GetWidth();
    float height = GetHeight();

    SetTopLeftPoint(position);
    SetBottomRightPoint(b2Vec2(position.x + width - 1, position.y + height));
}

b2Vec2 RectShapeComponent::GetCenterPoint() const
{
    return b2Vec2(GetTopLeftPoint().x + GetWidth() / 2.0f, GetTopLeftPoint().y + GetHeight() / 2.0f);
}

std::vector<b2Vec2> RectShapeComponent::GetPoints() const
{
    std::vector<b2Vec2> points;
    points.push_back(mPoints[0]);
    points.push_back(b2Vec2(mPoints[1].x, mPoints[0].y));
    points.push_back(mPoints[1]);
    points.push_back(b2Vec2(mPoints[0].x, mPoints[1].y));

    return points;
}