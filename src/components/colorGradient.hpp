#pragma once

#include <SFML/Graphics/Color.hpp>
#include <vector>

/**
 * Represents gradient
 * 
 * Most of 'get' methods have undefined behavior for getKeysCount() == 0
 * Make sure to do not use with "empty" gradient
 */
class ColorGradient {
public:
	struct GradientKey {
		float position;
		sf::Color color;

		GradientKey(); // default

		GradientKey(const GradientKey &org); // copy

		GradientKey(float pPosition, sf::Color pColor); // parametric
	};

private:
	std::vector<GradientKey> values;


public:

	ColorGradient();

	/**
	 * Creates gradient filed with passed colors in equal distance, first color at position=0, and last one at position=1
	 */
	ColorGradient(std::initializer_list<sf::Color> colors);

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
	GradientKey getKey(unsigned int index);

	
	/**
	 * Sets specific key to specific values.
	 * If index not exists then do nothing.
	 */
	void setKey(unsigned int index, float position, sf::Color color);
	void setKey(unsigned int index, float position);
	void setKey(unsigned int index, sf::Color color);

	/**
	 * Copy all keys to array
	 * @param array array to fill with keys
	 * @returns number of keys
	 */
	int getAllKeys(GradientKey *array);

	/**
	 * Removes key at specific index or do nothing if index is out of bounds
	 */
	void removeKey(unsigned int index);

	/**
	 * @returns index of closest left key to specific position
	 */
	unsigned int getLeftKeyIndexFor(float position);

	/**
	 * Calcs gradient color at specific position
	 * @param position value to evaluate (for <0 is 0; for >1 is 1 )
	 * @returns color for passed value
	 */
	sf::Color evaluate(float position);

	/**
	 * Alias for evaluate(float)
	 * @see #evaluate(float)
	 */
	inline sf::Color colorAt(float position){
		return evaluate(position);
	}
};