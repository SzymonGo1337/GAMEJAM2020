#pragma once

#include "physics.hpp"

class CircleCollider : public Collider{
    public:
        float radius;
    public:
        CircleCollider();
};