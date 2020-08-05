#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

namespace GameTime {
	void init();

	void update();

	float delta();
	float dt();

	float elapsed();

	int elapsedMs();

	int FPS();
}