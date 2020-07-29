#pragma once

#include "physics.hpp"

class RectangleCollider : public Collider{
    public:
        float width;
        float height;
    public:
        RectangleCollider();
};