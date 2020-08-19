#include "oanimate.h"
#include <stdio.h>
#include <math.h>

namespace olib {

	float oanimate::execute(float from, float to, float time) {
		if (!__non_blocking && __func != nullptr) {
			for (float a = 0; a <= 1 + __increment; a += __increment) {
				if (__ease_in && __ease_out) {
					call_func(from, to, _bezier(a));
				}
				else if (__ease_out) {
					call_func(from, to, _ease_out(a));
				}
				else if (__ease_in) {
					call_func(from, to, _ease_in(a));
				}else {
					call_func(from, to, a);
				}
			}
		}
		else {
			if(__ease_in && __ease_out)
				return (linear_lerp(from, to, _bezier(time)));
			else if (__ease_out)
				return linear_lerp(from, to, _ease_out(time));
			else if (__ease_in)
				return linear_lerp(from, to, _ease_in(time));
			else
				return linear_lerp(from, to, time);
		}
	}

	float oanimate::linear_lerp(float from, float to, float time) {
		return (1 - time) * from + time * to;
	}

	/*
	PRIVATE
	*/
	float oanimate::_ease_in(float t) {
		float sqrt = t * t;
		return sqrt / (2.0f * (0) + 1.0f);
		return t * t;
	}

	float oanimate::_ease_out(float t) {
			return sin(t * 1.57);
	}

	float oanimate::_bezier(float t) {
		float sqrt = t * t;
		return sqrt / (2.0f * (sqrt - t) + 1.0f);
	}
	/*//*/
}