#include "raytracer.cpp"
#include "color.h"
#include <list>

int main()
{
	// Image
	const float aspect_ratio = 16.0f / 9.0f;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 64;
	const int max_color = 255;

	std::list<vec3> image = ray_trace(image_width, image_height, max_color, samples_per_pixel);

	// Log the content of a ppm file format to console (so the caller of this program can pipe to a file to create an image file)
	std::cout << "P3\n" << image_width << " " << image_height << "\n" << max_color << "\n";
	for (vec3 &pixel_data : image)
	{
		write_color(std::cout, pixel_data, samples_per_pixel);
	}
}