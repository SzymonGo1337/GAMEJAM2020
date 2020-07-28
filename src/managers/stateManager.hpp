#pragma once

#include "state.hpp"

class StateManager {
private:
	State *state = nullptr;

public:
	StateManager();
	~StateManager();

	State *getState();
	void setState(State *state);
};