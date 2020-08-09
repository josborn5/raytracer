#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

void write_color(std::ostream &out, const vec3 &color, int samples_per_pixel)
{
	float r = color.x();
	float g = color.y();
	float b = color.z();

	// Divide the color by the number of samples and gamma-correct got gamma=2.0
	float scale = 1.0f / samples_per_pixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	const float char_conversion = 256.0f;
	const float min_color = 0.0f;
	const float max_color = 0.999f;
	int ir = static_cast<int>(char_conversion * clamp(r, min_color, max_color));
	int ig = static_cast<int>(char_conversion * clamp(g, min_color, max_color));
	int ib = static_cast<int>(char_conversion * clamp(b, min_color, max_color));

	out << ir << " " << ig << " " << ib << "\n";
}

#endif
