#pragma once

#include <SFML/Graphics.hpp>
#include "../entity/entity.hpp"

class Camera {
private:
	sf::View view;
	Entity *entity;
	float smoothCameraSpeed = 10; //idk how to name it
	bool shake = false;

	int shakeForceX = 1;
	int shakeForceY = 1;

public:
	Camera();
	~Camera();

	void update(const float &dt);

	void zoom(float factor);
	void rotate(float factor);

	void setCameraSpeed(float factor);

	void setShake(bool status, int forceX, int forceY);

	void follow(Entity *entity);
	
	sf::View *getView();
};