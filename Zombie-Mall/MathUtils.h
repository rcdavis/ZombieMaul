
#ifndef _MATH_UTILS_H_
#define _MATH_UTILS_H_

#include <cmath>

const float PI = std::atanf(1.0f) * 4.0f;

constexpr float DegreesToRadians(float degrees)
{
	return degrees * PI / 180.0f;
}

#endif // !_MATH_UTILS_H_
