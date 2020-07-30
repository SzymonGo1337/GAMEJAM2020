#pragma once

typedef float (*AnimationCurveFunction)(float time);


// Contains functions for animation curves
// For each animation curve:
// - returned value in [0;1]
// - input value (t) in [0;1]
//
// Desmos preview: https://www.desmos.com/calculator/opvmsvdq0x
namespace AnimationCurve{

	inline float Linear(float t){
		return t;
	}

	inline float EaseInOut(float t){
		return t*t / (2.0f * (t*t - t) + 1.0f);
	}

	inline float EaseIn(float t){
		return t * t;
	}

	inline float EaseOut(float t){
		return -t * (t - 2);
	}
}