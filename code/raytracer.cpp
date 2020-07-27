#include "constants.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include <iostream>

vec3 ray_color(const ray &r, const hittable_list &world)
{
	hit_record hit;
	if (world.hit(r, 0, infinity, hit))
	{
		vec3 normal_color = add_vectors(hit.normal, vec3(1.0f, 1.0f, 1.0f));
		return multiply_by_scalar(normal_color, 0.5f);
	}
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5f * (unit_direction.y() + 1.0f);
	vec3 white_blend = multiply_by_scalar(vec3(1.0, 1.0, 1.0), 1.0 - t);
	vec3 blue_blend = multiply_by_scalar(vec3(0.5, 0.7, 1.0), t);

	return add_vectors(white_blend, blue_blend);
}

int main()
{
	// Image
	const float aspect_ratio = 16.0f / 9.0f;
	const int image_width = 384;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	// Log the content of a ppm file format to console (so the caller of this program can pipe to a file to create an image file)
	const int max_color = 255;
	std::cout << "P3\n" << image_width << " " << image_height << "\n" << max_color << "\n";

	// World
	hittable_list world;
	world.add(std::make_shared<sphere>(vec3(0.0f, 0.0f, -1.0f), 0.5f));
	world.add(std::make_shared<sphere>(vec3(0.0f, -100.5f, -1.0f), -100.0f));

	float viewport_height = 2.0f;
	float viewport_width = aspect_ratio * viewport_height;
	float focal_length = 1.0f;

	vec3 origin = vec3(0, 0, 0);
	vec3 horizontal = vec3(viewport_width, 0, 0);
	vec3 vertical = vec3(0, viewport_height, 0);
	vec3 half_horizontal = multiply_by_scalar(horizontal, -0.5f);
	vec3 half_vertical  = multiply_by_scalar(vertical, -0.5f);

	vec3 lower_left = add_vectors(origin, half_horizontal, half_vertical);
	vec3 focal_plane_lower_left = add_vectors(lower_left, vec3(0, 0, -focal_length));
	
	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
		for (int i = 0; i < image_width; ++i)
		{
			float u = float(i) / (image_width - 1);
			float v = float(j) / (image_height - 1);

			vec3 horizontal_offset = multiply_by_scalar(horizontal, u);
			vec3 vertical_offset = multiply_by_scalar(vertical, v);

			vec3 point_on_focal_plane = add_vectors(focal_plane_lower_left, horizontal_offset, vertical_offset);
			vec3 direction = subtract_vectors(point_on_focal_plane, origin);
			ray r = ray(origin, direction);

			vec3 pixel_color = ray_color(r, world);
			write_color(std::cout, pixel_color);
		}
	}
	std::cerr << "\nDone.\n";
}