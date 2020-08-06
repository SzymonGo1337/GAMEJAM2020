#pragma once

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "../data.hpp"
#include "../components/camera.hpp"

class State {
protected:
	Data *data;
public:
	State(Data *data) {
		this->data = data;
	}
	virtual ~State() {
		
	}
	virtual void updateEvents(sf::Event &event)=0;
	virtual void update(const float &dt)=0;
	virtual void render()=0;
};