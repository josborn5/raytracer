#include "constants.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include <iostream>

vec3 ray_color(const ray &r, const hittable_list &world, int depth)
{
	hit_record hit;

	if (depth <= 0)
	{
		return vec3(0.0f, 0.0f, 0.0f);
	}

	if (world.hit(r, 0.001, infinity, hit))
	{
		vec3 target = add_vectors(hit.position, hit.normal, random_unit_vec3());
		ray new_ray = ray(hit.position, subtract_vectors(target, hit.position));
		vec3 normal_color = ray_color(new_ray, world, depth - 1);
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
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;
	int max_depth = 50;

	// Log the content of a ppm file format to console (so the caller of this program can pipe to a file to create an image file)
	const int max_color = 255;
	std::cout << "P3\n" << image_width << " " << image_height << "\n" << max_color << "\n";

	// World
	hittable_list world = hittable_list();
	float small_radius = 0.5f;
	float big_radius = 100.0f;
	sphere small_sphere = sphere(vec3(0.0f, 0.0f, -1.0f), small_radius);
	sphere big_sphere = sphere(vec3(0.0f, -(small_radius + big_radius), -1.0f), big_radius);
	world.add(std::make_shared<sphere>(small_sphere));
	world.add(std::make_shared<sphere>(big_sphere));

	// Camera
	camera cam;
	
	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
		for (int i = 0; i < image_width; ++i)
		{
			vec3 pixel_color = vec3(0.0f, 0.0f, 0.0f);
			for (int s = 0; s < samples_per_pixel; ++s)
			{
				float u = (i + random_float()) / (image_width - 1);
				float v = (j + random_float()) / (image_height - 1);

				ray r = cam.get_ray(u, v);
				vec3 sample_color = ray_color(r, world, max_depth);
				pixel_color.add_current(sample_color);
			}

			write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}
	std::cerr << "\nDone.\n";
}