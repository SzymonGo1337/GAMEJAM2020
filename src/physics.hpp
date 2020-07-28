#include <SFML/Graphics.hpp>
#include <iostream>

class Box {
private:
    sf::RectangleShape rect;
public:
    Box(float x, float y, sf::Vector2f size, sf::Color color);
    void draw(sf::RenderTarget &target);
    void physics(float x, float y, float speed);
};