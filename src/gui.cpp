#include "gui.hpp"

Button::Button(float x, float y, sf::Vector2f size) {
    isColor = true;
    isTexture = false;
    buttonPosition = sf::Vector2f(x, y);
    buttonShape.setSize(size);
    buttonShape.setPosition(buttonPosition);
    buttonShape.setFillColor(sf::Color::White);
}

Button::Button(float x, float y, sf::Vector2f size, sf::Color color) {
    isColor = true;
    isTexture = false;
    buttonColor = color;
    buttonPosition = sf::Vector2f(x, y);
    buttonShape.setSize(size);
    buttonShape.setPosition(buttonPosition);
    buttonShape.setFillColor(buttonColor);
}

Button::Button(float x, float y, sf::Vector2f size, sf::Color color, sf::Color colorTwo) {
    isColor = true;
    isTexture = false;
    buttonColor = color;
    buttonColorTwo = colorTwo;
    buttonPosition = sf::Vector2f(x, y);
    buttonShape.setSize(size);
    buttonShape.setPosition(buttonPosition);
    buttonShape.setFillColor(buttonColor);
}

Button::Button(float x, float y, sf::Texture texture) {
    isColor = false;
    isTexture = true;
    buttonTexture = texture;
    buttonPosition = sf::Vector2f(x, y);
    buttonShape.setSize(sf::Vector2f(buttonTexture.getSize().x, buttonTexture.getSize().y));
    buttonShape.setTexture(&buttonTexture);
    buttonShape.setPosition(buttonPosition);
}

Button::Button(float x, float y, sf::Texture texture, sf::Texture textureTwo) {
    isColor = false;
    isTexture = true;
    buttonTexture = texture;
    buttonTextureTwo = textureTwo;
    buttonPosition = sf::Vector2f(x, y);
    buttonShape.setSize(sf::Vector2f(buttonTexture.getSize().x, buttonTexture.getSize().y));
    buttonShape.setTexture(&buttonTexture);
    buttonShape.setPosition(buttonPosition);
}

Button::Button(float x, float y, std::string texture, std::string textureTwo) {
    isColor = false;
    isTexture = true;
    buttonTexture.loadFromFile(texture);
    buttonTextureTwo.loadFromFile(textureTwo);
    buttonPosition = sf::Vector2f(x, y);
    buttonShape.setSize(sf::Vector2f(buttonTexture.getSize().x, buttonTexture.getSize().y));
    buttonShape.setTexture(&buttonTexture);
    buttonShape.setPosition(buttonPosition);
}

void Button::draw(sf::RenderTarget &target) {
    target.draw(buttonShape);
}

void Button::clicked(sf::Window &target, buttonFunc make) {
    if(buttonShape.getGlobalBounds().contains(sf::Mouse::getPosition(target).x, sf::Mouse::getPosition(target).y)) {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            make();
        } else if(isTexture == true && isColor == false) {
            buttonShape.setTexture(&buttonTextureTwo);
        } else if(isTexture == false && isColor == true) {
            buttonShape.setFillColor(buttonColorTwo);
        }
    } else if(isTexture == true && isColor == false) {
        buttonShape.setTexture(&buttonTexture);
    } else if(isTexture == false && isColor == true) {
        buttonShape.setFillColor(buttonColor);
    }
}

Slider::Slider(float x, float y, sf::Texture texture, sf::Texture textureTwo) {
    pointTexture = texture;
    pointShape.setTexture(&pointTexture);
    pointShape.setPosition(10.0f, 10.0f);

    slideTexture = textureTwo;
    slideShape.setTexture(&slideTexture);
    slideShape.setOrigin(0.0f, 0.0f);
    slideShape.setPosition(x, y);
}

Slider::Slider(float x, float y, sf::Color color, sf::Color colorTwo) {
    pointColor = color;
    pointShape.setFillColor(color);
    pointShape.setSize(sf::Vector2f(25.0, 25.0f));
    pointShape.setOrigin(12.5f, 12.5f);
    pointShape.setPosition(x, y + 7.25f);

    slideColor = colorTwo;
    slideShape.setFillColor(colorTwo);
    slideShape.setSize(sf::Vector2f(200.0f, 15.0f));
    slideShape.setPosition(x, y);
}

void Slider::draw(sf::RenderTarget &target) {
    target.draw(slideShape);
    target.draw(pointShape);
}

void Slider::clicked(sf::Window &target, sliderFunc make) {
    if(pointShape.getGlobalBounds().contains(sf::Mouse::getPosition(target).x, sf::Mouse::getPosition(target).y)) {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if(pointShape.getPosition().x < slideShape.getPosition().x) {
                pointShape.setPosition(slideShape.getPosition().x, pointShape.getPosition().y);
            } else if(pointShape.getPosition().x > slideShape.getPosition().x + slideShape.getSize().x) {
                pointShape.setPosition(slideShape.getPosition().x + slideShape.getSize().x, pointShape.getPosition().y);
            } else {
                pointShape.setPosition(sf::Mouse::getPosition(target).x, pointShape.getPosition().y);
            }
            make(pointShape.getPosition().x - slideShape.getPosition().x);
        }
    }
}