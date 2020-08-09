#include "sphere.h"
#include <assert.h>
#include <iostream>

void print_hit_result(const hit_record &hit, bool collision)
{
	std::cout << "collision: " << collision << "\n";
	std::cout << "hit.time: " << hit.time << "\n";
	std::cout << "hit.front_face: " << hit.front_face << "\n";
	std::cout << "hit.position.x: " << hit.position.x() << "\n";
	std::cout << "hit.position.y: " << hit.position.y() << "\n";
	std::cout << "hit.position.z: " << hit.position.z() << "\n";
	std::cout << "hit.normal.x: " << hit.normal.x() << "\n";
	std::cout << "hit.normal.y: " << hit.normal.y() << "\n";
	std::cout << "hit.normal.z: " << hit.normal.z() << "\n";
	std::cout << "hit.normal.length_squared: " << hit.normal.length_squared() << "\n";
}

void run_sphere_tests()
{
	float t_min = 0.0f;
	float t_max = 10.0f;
	float sphere_radius = 2.0f;
	vec3 origin = vec3(0.0f, 0.0f, 0.0f);
	vec3 positive_x_position = vec3(2.0f * sphere_radius, 0.0f, 0.0f);
	vec3 to_negative_x = vec3(-1.0f, 0.0f, 0.0f);
	ray ray_to_origin = ray(positive_x_position, to_negative_x);
	sphere sphere_at_origin = sphere(origin, sphere_radius);

	bool collision;
	hit_record output;

	// center-line hit along x-axis to sphere at origin
	output = {};
	collision = sphere_at_origin.hit(ray_to_origin, t_min, t_max, output);
	std::cout << "\ncenter-line hit along x-axis to sphere at origin\n";
	print_hit_result(output, collision);
	assert(collision == true);
	assert(output.front_face == true);
	assert(output.time == 2.0f);
	assert(output.position.x() == sphere_radius);
	assert(output.position.y() == 0.0f);
	assert(output.position.z() == 0.0f);
	assert(output.normal.x() == 1.0f);
	assert(output.normal.y() == 0.0f);
	assert(output.normal.z() == 0.0f);
	assert(output.normal.length_squared() <= 1.0f);

	// off center hit parallel to x-axis to sphere at origin
	float off_center_y_position = sphere_radius * 0.5f;
	vec3 off_center_x_position = vec3(2 * sphere_radius, off_center_y_position, 0.0f);
	ray ray_to_off_center_x = ray(off_center_x_position, to_negative_x);
	output = {};
	collision = sphere_at_origin.hit(ray_to_off_center_x, t_min, t_max, output);
	std::cout << "\noff center hit parallel to x-axis to sphere at origin\n";
	print_hit_result(output, collision);
	assert(collision == true);
	assert(output.front_face == true);
	assert(output.time > 2.0f);
	assert(output.position.x() < sphere_radius);
	assert(output.position.y() == off_center_y_position);
	assert(output.position.z() == 0.0f);
	assert(output.normal.x() < 1.0f);
	assert(output.normal.y() == 0.5f);
	assert(output.normal.z() == 0.0f);
	assert(output.normal.length_squared() <= 1.0f);

	// off center hit along x-axis to sphere off the origin
	sphere sphere_off_origin = sphere(vec3(0.0f, -0.5f, 0.0f), sphere_radius);

	output = {};
	collision = sphere_off_origin.hit(ray_to_origin, t_min, t_max, output);
	std::cout << "\noff center hit along x-axis to sphere off the origin\n";
	print_hit_result(output, collision);
	assert(collision == true);
	assert(output.front_face == true);
	assert(output.time > 2.0f);
	assert(output.position.x() < sphere_radius);	// collision point is different to the test case hitting the sphere at the origin
	assert(output.position.y() == 0.0f);
	assert(output.position.z() == 0.0f);
	assert(output.normal.x() < 1.0f);	// normal at collision point is the same as the test case hitting the sphere at the origin
	assert(output.normal.y() == 0.25f);
	assert(output.normal.z() == 0.0f);
	assert(output.normal.length_squared() <= 1.0f);
}