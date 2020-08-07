#pragma once

#include <iostream>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>
#include <map>

// angle in degrees * deg2rad == angle in radians
#define deg2rad 0.017453293
// angle in radians * rad2deg == angle in degrees
#define rad2deg 57.295779513

#define MinMax MinMaxf

struct MinMaxf {
private:
	float min, max;

public:
	MinMaxf(float min, float max);
	MinMaxf(const MinMaxf &o);

	float getMin() const;
	float getMax() const;

	friend std::ostream& operator<< (std::ostream &out, const MinMaxf &mm);
};

struct MinMaxi {
private:
	int min, max;

public:

	MinMaxi(int min, int max);
	MinMaxi(const MinMaxi &o);

	int getMin() const;
	int getMax() const;

	friend std::ostream& operator<< (std::ostream &out, const MinMaxi &mm);
};

float lerp(float start, float end, float t);

float clamp(float value, float min, float max);
int clamp(int value, int min, int max);


float sign(float x);

/**
 * @returns random value between 0 (inclusive) and 1 (exclusive)
 */
float randomFloat();

std::string tostr(float x);
std::string tostr(int x);

template <typename T>
std::string tostr(sf::Vector2<T> x){
	return "[" + std::to_string(x.x) + ", " + std::to_string(x.y) + "]";
}

void setKey(const std::string &key, const std::string &value);
void removeKey(const std::string &key);

std::map<std::string, sf::Text> &getLogMap();


std::ostream& operator<<(std::ostream &out, const sf::Color &c);
std::ostream& operator<<(std::ostream &out, const sf::Vector2f &c);