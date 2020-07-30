#pragma once

#include <SFML/Graphics/Color.hpp>
#include <vector>

class ColorGradient {
public:
	struct GradientKey {
		float position;
		sf::Color color;

		GradientKey() : // default
			position(-1),
			color(0,0,0) {}

		GradientKey(const GradientKey &org) : // copy/clone
			position(org.position),
			color(org.color) {} 

		GradientKey(float pPosition, sf::Color pColor) : // parametric
			position(position),
			color(pColor) {}
	};

private:
	std::vector<GradientKey> values;


public:

	ColorGradient() {}

	/**
	 * Adds new key to gradient
	 * @param position Position of key. Value form 0 to 1 inclusive.
	 * @param color Color of key.
	 */
	void addKey(float position, sf::Color color);

	/**
	 * @returns number of keys
	 */
	int getKeysCount();

	/**
	 * Returns gradient key
	 * @param index Index of key
	 * @returns gradient key at index or first/last gradient key if index < 0 or index >= getKeysCount()
	 */
	GradientKey getKey(int index);

	
	/**
	 * Sets specific key to specific values.
	 * If index not exists then do nothing.
	 */
	void setKey(int index, float position, sf::Color color);
	void setKey(int index, float position);
	void setKey(int index, sf::Color color);

	/**
	 * Copy all keys to array
	 * @param array array to fill with keys
	 * @returns number of keys
	 */
	int getAllKeys(GradientKey *array);

	/**
	 * Removes key at specific index or do nothing if index is out of bounds
	 */
	void removeKey(int index);

};