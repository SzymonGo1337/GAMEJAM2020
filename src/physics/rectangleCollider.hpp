#pragma once

#include "collider.hpp"

class RectangleCollider : public Collider{
    public:
        float width;
        float height;
    public:
        RectangleCollider();
        float getColliderMaxSizeFromPivot();
};