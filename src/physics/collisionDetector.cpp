#include "collisionDetector.hpp"
#include <typeinfo>
#include <math.h>

bool detectCollision(Collider *first, Collider *second){
    bool result = false;

    if (typeid(first) == typeid(RectangleCollider)
        && typeid(second) == typeid(RectangleCollider)){
        RectangleCollider* f = dynamic_cast<RectangleCollider*>(first);
        RectangleCollider* s = dynamic_cast<RectangleCollider*>(second);
        result = f->position.x < s->position.x + s->width 
            && f->position.x + f->width > s->position.x
            && f->position.y < s->position.y + s->height
            && f->position.y + f->height > s->position.y;
        delete f;
        delete s;
    }
    else if (typeid(first) == typeid(RectangleCollider)
        && typeid(second) == typeid(CircleCollider)){
        RectangleCollider* f = dynamic_cast<RectangleCollider*>(first);
        CircleCollider* s = dynamic_cast<CircleCollider*>(second);
        result = detectCollisionBetweenRectangleAndCircle(f, s);
        delete f;
        delete s;
    }
    else if (typeid(first) == typeid(CircleCollider)
        && typeid(second) == typeid(RectangleCollider)){
        CircleCollider* f = dynamic_cast<CircleCollider*>(first);
        RectangleCollider* s = dynamic_cast<RectangleCollider*>(second);
        result = detectCollisionBetweenRectangleAndCircle(s, f);
        delete f;
        delete s;
    }
    else if (typeid(first) == typeid(CircleCollider)
        && typeid(second) == typeid(CircleCollider)){
        CircleCollider* f = dynamic_cast<CircleCollider*>(first);
        CircleCollider* s = dynamic_cast<CircleCollider*>(second);
        int dx = f->position.x - s->position.x;
        int dy = f->position.y - s->position.y;
        float distance = sqrt(dx * dx + dy * dy);

        result = distance < f->radius + s->radius;
        delete f;
        delete s;
    }
    return result;
}

bool detectCollisionBetweenRectangleAndCircle(RectangleCollider* rectangle, CircleCollider* circle){
    float testX = circle->position.x;
    float testY = circle->position.y;

    if (circle->position.x < rectangle->position.x){
        testX = rectangle->position.x;
    }         
    else if (circle->position.x > rectangle->position.x + rectangle->width){
        testX = rectangle->position.x + rectangle->width;
    } 
    if (circle->position.y < rectangle->position.y){
        testY = rectangle->position.y;
    } 
    else if (circle->position.y > rectangle->position.y + rectangle->height){
        testX = rectangle->position.y + rectangle->height;
    } 

    // get distance from closest edges
    float distX = circle->position.x - testX;
    float distY = circle->position.y - testY;
    float distance = sqrt( (distX*distX) + (distY*distY) );

    // if the distance is less than the radius, collision!
    return distance <= circle->radius;
}