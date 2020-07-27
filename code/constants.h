#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <limits>

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;

float degrees_to_radians(float degrees)
{
	return degrees * pi / 180.0f;
}

#endif