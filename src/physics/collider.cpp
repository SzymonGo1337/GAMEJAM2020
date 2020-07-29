#include "collider.h"

Collider::Collider(sf::Vector2f position){
    Collider::position = position;
    rotation = 0;
    scale = *new sf::Vector2f(1, 1);
}