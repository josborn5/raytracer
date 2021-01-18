#include "raytracer.cpp"
#include "color.h"
#include <string>

int samples_per_pixel;

void WritePixel(int x, int y, vec3 pixel_data)
{
	write_color(std::cout, pixel_data, samples_per_pixel);
}

int main(int arg_c, char *arg_v[])
{
	if (arg_c != 3)
	{
		std::cerr << "Usage: .\\console.exe <image_width> <samples_per_pixel>\n";
		return 1;
	}

	int image_width = std::stoi(arg_v[1]);
	samples_per_pixel = std::stoi(arg_v[2]);
	
	// Image
	const float aspect_ratio = 16.0f / 9.0f;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int max_color = 255;

	// Log the content of a ppm file format to console (so the caller of this program can pipe to a file to create an image file)
	std::cout << "P3\n" << image_width << " " << image_height << "\n" << max_color << "\n";
	ray_trace(image_width, image_height, max_color, samples_per_pixel, &WritePixel);
}