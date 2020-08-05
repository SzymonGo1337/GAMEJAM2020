#pragma once

#include <SFML/Graphics.hpp>

class Camera {
private:
	sf::View view;

public:
	Camera();
	~Camera();

	void update();
	void zoom(float factor);
	sf::View *getView();
};