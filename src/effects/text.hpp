#pragma once

#include <SFML/Graphics.hpp>
#include "../entity/entity.hpp"

class Text : public sf::Drawable {
private:
	sf::Text text;
	sf::Font font;

	Entity *entity;

	sf::Vector2f offset;
public:
	Text(const std::string &path, const std::string &string, sf::Vector2f pos, int charSize = 24) {
		font.loadFromFile(path);
		text.setFont(font);
		text.setString(string);
		text.setCharacterSize(charSize);
	}

	~Text() {

	}
	void setOffset(float x, float y) {

		offset = {x, y};
		
	}

	void setString(const std::string &string) {

		text.setString(string);

	}

	void follow(Entity *entity, const float &dt, float speed = 10) {

		sf::Vector2f movement = entity->getShape().getPosition() - text.getPosition();
	
    	text.move((movement.x + offset.x) * dt * speed, (movement.y + offset.y) * dt * speed);

	}

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override {

		target.draw(text, states);

	}
};