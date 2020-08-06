#include "stateManager.hpp"

StateManager::StateManager() {


}

StateManager::~StateManager() {

	if(!(state == nullptr)) {

		delete state;
		state = nullptr;

	}
	
}

State *StateManager::getState() {

	return this->state;

}

void StateManager::setState(State *state) {

	if(state == nullptr) {
		
		this->state = state;

	} else {

		delete this->state;
		this->state = state;

	}
}