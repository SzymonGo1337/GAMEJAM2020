#pragma once

#include <stdio.h>
#include <SFML/Graphics.hpp>

class State {
private:

public:
	State() {

	}
	virtual ~State() {
		
	}

	virtual void update()=0;
	virtual void render(sf::RenderWindow* window)=0;
};