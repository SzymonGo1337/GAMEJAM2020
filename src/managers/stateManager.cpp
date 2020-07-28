#include "stateManager.hpp"

StateManager::StateManager(){


}

StateManager::~StateManager(){


}

State *StateManager::getState(){
	return this->state;
}

void StateManager::setState(State *state){
	this->state = state;

}
