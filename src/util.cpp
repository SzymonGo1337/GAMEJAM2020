#include "util.hpp"

MinMaxf::MinMaxf(float min, float max){
	if(max < min){
		float tmp = max;
		max = min;
		min = tmp;
	}
	this->min = min;
	this->max = max;
}

MinMaxf::MinMaxf(const MinMaxf &o) : min(o.min), max(o.max) {
}

float MinMaxf::getMin() const {
	return min;
}

float MinMaxf::getMax() const {
	return max;
}

std::ostream& operator<< (std::ostream &out, const MinMaxf &mm){
	out << "["<< mm.min << ";"<< mm.max << "]";
	return out;
}

MinMaxi::MinMaxi(int min, int max) {
	if(max < min){
		float tmp = max;
		max = min;
		min = tmp;
	}
	this->min = min;
	this->max = max;
}

MinMaxi::MinMaxi(const MinMaxi &o) : min(o.min), max(o.max) {
}

int MinMaxi::getMin() const {
	return min;
}

int MinMaxi::getMax() const {
	return max;
}

float lerp(float start, float end, float t) {
	return (end - start) * t + start;
}

float randomFloat() {
	return std::rand()/float(RAND_MAX);
}