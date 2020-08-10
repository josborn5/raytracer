#include "constants.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "lambertian.h"
#include "metal.h"
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
		ray scattered;
		vec3 attenuation;
		if (hit.mat_ptr->scatter(r, hit, attenuation, scattered))
		{
			vec3 new_color = ray_color(scattered, world, depth - 1);
			return multiply_vectors(attenuation, new_color);
		}
		return vec3(0.0f, 0.0f, 0.0f);
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
	lambertian ground = lambertian(vec3(0.8f, 0.8f, 0.0f));
	lambertian center = lambertian(vec3(0.7f, .3f, 0.3f));
	metal left = metal(vec3(0.8f, 0.8f, 0.8f));
	metal right = metal(vec3(0.8f, 0.6f, 0.2f));

	float small_radius = 0.5f;
	float big_radius = 100.0f;
	sphere small_sphere = sphere(vec3(0.0f, 0.0f, -1.0f), small_radius, std::make_shared<lambertian>(center));
	sphere big_sphere = sphere(vec3(0.0f, -(small_radius + big_radius), -1.0f), big_radius, std::make_shared<lambertian>(ground));
	sphere left_sphere = sphere(vec3((-2.0f * small_radius), 0.0f, -1.0f), small_radius, std::make_shared<metal>(left));
	sphere right_sphere = sphere(vec3((2.0f * small_radius), 0.0f, -1.0f), small_radius, std::make_shared<metal>(right));

	hittable_list world = hittable_list();
	world.add(std::make_shared<sphere>(small_sphere));
	world.add(std::make_shared<sphere>(big_sphere));
	world.add(std::make_shared<sphere>(left_sphere));
	world.add(std::make_shared<sphere>(right_sphere));

	// Camera
	camera cam = camera(vec3(-2,2,1), vec3(0,0,-1), vec3(0,1,0), 20.0f, aspect_ratio);
	
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