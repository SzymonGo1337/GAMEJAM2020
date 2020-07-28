#include <SFML/Graphics.hpp>
#include <iostream>

typedef void (*buttonFunc)();

class Button {
private:
    sf::Color buttonColor;
    sf::Color buttonColorTwo;

    sf::Texture buttonTexture;
    sf::Texture buttonTextureTwo;

    sf::RectangleShape buttonShape;

    sf::Vector2f buttonPosition;

    bool isTexture;
    bool isColor;
public:
    Button(float x, float y, sf::Vector2f size);
    Button(float x, float y, sf::Vector2f size, sf::Color color);
    Button(float x, float y, sf::Vector2f size, sf::Color color, sf::Color colorTwo);
    Button(float x, float y, sf::Texture texture);
    Button(float x, float y, sf::Texture texture, sf::Texture textureTwo);
    void draw(sf::RenderTarget &target);
    void clicked(sf::Window &target, buttonFunc make);
};