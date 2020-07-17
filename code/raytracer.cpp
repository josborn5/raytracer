#include "vec3.h"
#include "color.h"
#include <iostream>

int main()
{
	const int image_height = 256;
	const int image_width = 256;

	// Log the content of a ppm file format to console (so the caller of this program can pipe to a file to create an image file)
	const int max_color = 255;
	std::cout << "P3\n" << image_width << " " << image_height << "\n" << max_color << "\n";

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
		for (int i = 0; i < image_width; ++i)
		{
			double r = double(i) / double(image_width - 1);
			double g = double(j) / double(image_height - 1);
			double b = 0.25;

			vec3 color = vec3(r, g, b);

			write_color(std::cout, color);
		}
	}
	std::cerr << "\nDone.\n";
}