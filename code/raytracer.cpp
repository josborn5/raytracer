#include "constants.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "vec3.h"
#include "ray.h"
#include "lambertian.h"
#include "metal.h"
#include <iostream>
#include <list>

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

std::list<vec3> ray_trace(int image_width, int image_height, int max_color, int samples_per_pixel)
{
	// Output
	std::list<vec3> image_data;
	int pixel_count = image_width * image_height;
	
	// Image
	const float aspect_ratio = static_cast<float>(image_width) / static_cast<float>(image_height);
	int max_depth = 50;

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
	camera cam = camera(vec3(-2,2,1), vec3(0,0,-1), vec3(0,1,0), 45.0f, aspect_ratio);
	
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

			image_data.push_back(pixel_color);
		}
	}
	std::cerr << "\nDone.\n";

	return image_data;
}