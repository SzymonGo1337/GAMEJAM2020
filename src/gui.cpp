#include "gui.hpp"

Button::Button(float x, float y, sf::Vector2f size) {
    isTexture = false;
    buttonPosition = sf::Vector2f(x, y);
    buttonShape.setSize(size);
    buttonShape.setPosition(buttonPosition);
    buttonShape.setFillColor(sf::Color::White);
}

Button::Button(float x, float y, sf::Vector2f size, sf::Color color) {
    isTexture = false;
    buttonColor = color;
    buttonPosition = sf::Vector2f(x, y);
    buttonShape.setSize(size);
    buttonShape.setPosition(buttonPosition);
    buttonShape.setFillColor(buttonColor);
}

Button::Button(float x, float y, sf::Vector2f size, sf::Color color, sf::Color colorTwo) {
    isTexture = false;
    buttonColor = color;
    buttonColorTwo = colorTwo;
    buttonPosition = sf::Vector2f(x, y);
    buttonShape.setSize(size);
    buttonShape.setPosition(buttonPosition);
    buttonShape.setFillColor(buttonColor);
}

Button::Button(float x, float y, sf::Texture texture) {
    isTexture = true;
    buttonTexture = texture;
    buttonPosition = sf::Vector2f(x, y);
    buttonShape.setSize(sf::Vector2f(buttonTexture.getSize().x, buttonTexture.getSize().y));
    buttonShape.setTexture(&buttonTexture);
    buttonShape.setPosition(buttonPosition);
}

Button::Button(float x, float y, sf::Texture texture, sf::Texture textureTwo) {
    isTexture = true;
    buttonTexture = texture;
    buttonTextureTwo = textureTwo;
    buttonPosition = sf::Vector2f(x, y);
    buttonShape.setSize(sf::Vector2f(buttonTexture.getSize().x, buttonTexture.getSize().y));
    buttonShape.setTexture(&buttonTexture);
    buttonShape.setPosition(buttonPosition);
}

void Button::draw(sf::RenderTarget &target) {
    target.draw(buttonShape);
}

void Button::clicked(sf::Window &target, buttonFunc make) {
    if(buttonShape.getGlobalBounds().contains(sf::Mouse::getPosition(target).x, sf::Mouse::getPosition(target).y) &&
       sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        make();
    }
}