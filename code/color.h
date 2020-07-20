#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

void write_color(std::ostream &out, vec3 &color)
{
	const float char_conversion = 255.999;
	int ir = static_cast<int>(char_conversion * color.x());
	int ig = static_cast<int>(char_conversion * color.y());
	int ib = static_cast<int>(char_conversion * color.z());

	out << ir << " " << ig << " " << ib << "\n";
}

#endif
