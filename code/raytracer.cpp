#include "vec3.h"
#include "color.h"
#include "ray.h"
#include <iostream>

vec3 ray_color(ray r)
{
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5*(unit_direction.y() + 1.0);
	vec3 c1 = multiply_by_scalar(vec3(1.0, 1.0, 1.0), 1.0 - t);
	vec3 c2 = multiply_by_scalar(vec3(0.5, 0.7, 1.0), t);
	return add_vectors(c1, c2);
}

int main()
{
	const float aspect_ratio = 16.0 / 9.0;
	const int image_width = 384;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	// Log the content of a ppm file format to console (so the caller of this program can pipe to a file to create an image file)
	const int max_color = 255;
	std::cout << "P3\n" << image_width << " " << image_height << "\n" << max_color << "\n";

	float viewport_height = 2.0;
	float viewport_width = aspect_ratio * viewport_height;
	float focal_length = 1.0;

	vec3 origin = vec3(0, 0, 0);
	vec3 horizontal = vec3(viewport_width, 0, 0);
	vec3 vertical = vec3(0, viewport_height, 0);

	vec3 half_horizontal = multiply_by_scalar(horizontal, 0.5);
	vec3 half_vertical = multiply_by_scalar(vertical, 0.5);
	vec3 lower_left_corner = subtract_vectors(origin, subtract_vectors(half_horizontal, subtract_vectors(half_vertical, vec3(0, 0, focal_length))));
	
	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
		for (int i = 0; i < image_width; ++i)
		{
			float u = float(i) / (image_width - 1);
			float v = float(j) / (image_height - 1);

			vec3 horizontal_v = multiply_by_scalar(horizontal, u);
			vec3 vertical_v = multiply_by_scalar(vertical, v);
			vec3 direction = add_vectors(lower_left_corner, add_vectors(horizontal_v, subtract_vectors(vertical_v, origin)));
			ray r = ray(origin, direction);

			vec3 pixel_color = ray_color(r);
			write_color(std::cout, pixel_color);
		}
	}
	std::cerr << "\nDone.\n";
}