#pragma once

#include "collider.hpp"

class CircleCollider : public Collider{
    public:
        float radius;
    public:
        CircleCollider();
        float getColliderMaxSizeFromPivot();
};