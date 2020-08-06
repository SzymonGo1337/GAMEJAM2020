#pragma once

#include <SFML/Graphics.hpp>
#include "math.h"

class Animation {
private:
	float index = 0;
	sf::Texture texture;
	sf::RectangleShape *targetShape;

	sf::Vector2f tileSize;

	sf::Clock clock;

	sf::IntRect rect = {0, 0, 24, 24};

	bool over;
public:
	Animation(const std::string &path, sf::RectangleShape *targetShape, sf::Vector2f tileSize = {24, 24}) {
		texture.loadFromFile(path);
		this->targetShape = targetShape;
		targetShape->setTexture(&texture);

		this->tileSize = tileSize;
	}
	~Animation() {

	}

	void update(const float &dt, float speed, int offsetY) {


		if(clock.getElapsedTime().asSeconds() * speed > 1.0f) {

			rect.top = offsetY*tileSize.y;

			if(rect.left == texture.getSize().x / tileSize.x * tileSize.x - tileSize.x) {

				over = true;
				rect.left = 0;

			} else {
										
				over = false;
				rect.left += tileSize.x;
			}

			targetShape->setTextureRect(rect);
			clock.restart();
		}

	}
	void reset() {

		rect.left = 0;

	}
	bool isOver() {

		return over;

	}
};