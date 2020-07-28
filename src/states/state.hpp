#pragma once

class State{
private:

public:
	State()
	{

	}
	virtual ~State()
	{
		
	}

	virtual void update()=0;
	virtual void render()=0;
};