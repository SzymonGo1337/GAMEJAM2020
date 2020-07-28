#include "camera.hpp"

Camera::Camera() {
	//view.setCenter();
}

Camera::~Camera() {

}

void Camera::update() {

}

void Camera::zoom(float factor) {
	view.zoom(factor);
}

sf::View *Camera::getView() {
	return &view;
}