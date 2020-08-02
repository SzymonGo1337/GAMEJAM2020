#pragma once

#include <iostream>

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

/**
 * @returns random value between 0 (inclusive) and 1 (exclusive)
 */
float randomFloat();