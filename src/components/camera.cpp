#include "camera.hpp"

#include "../time.hpp"

Camera::Camera() {
	//view.setCenter();
}

Camera::~Camera() {
	entity = nullptr;
}

void Camera::update() {

	if(shake) {

		if(rand()%2 == 1) {

			view.move((rand()%shakeForceX)*GameTime::dt(), (rand()%shakeForceY)*GameTime::dt());
			
		} else {

			view.move(-((rand()%shakeForceX)*GameTime::dt()), -((rand()%shakeForceY)*GameTime::dt()));

		}
	}

	sf::Vector2f movement = entity->getShape().getPosition() - view.getCenter();
	
    view.move(movement.x * GameTime::dt() * smoothCameraSpeed, movement.y * GameTime::dt() * smoothCameraSpeed);
	
}

void Camera::zoom(float factor) {
	view.zoom(factor);
}

void Camera::rotate(float factor) {
	view.rotate(factor);
}

void Camera::setCameraSpeed(float factor) {
	smoothCameraSpeed = factor;
}

void Camera::setShake(bool status, int forceX, int forceY) {
	shake = status;

	if(forceX == 0) forceX = 1;
	if(forceY == 0) forceY = 1;

	shakeForceX = forceX;
	shakeForceY = forceY;
}

void Camera::follow(Entity *entity) {
	this->entity = entity;
}

sf::View *Camera::getView() {
	return &view;
}