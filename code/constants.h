#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdlib>
#include <limits>

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;

float degrees_to_radians(float degrees)
{
	return degrees * pi / 180.0f;
}

float random_float()
{
	return rand() / (static_cast<float>RAND_MAX + 1.0f);
}

float random_float(float min, float max)
{
	return min + ((max - min) * random_float());
}

float clamp(float val, float min, float max)
{
	if (val < min) return min;
	if (val > max) return max;
	return val;
}

#endif