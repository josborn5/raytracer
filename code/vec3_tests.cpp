#include "vec3.h"
#include <assert.h>

void run_vec3_tests()
{
	// vec3.length()
	vec3 unit_vector_x = vec3(1, 0, 0);
	float x_length = unit_vector_x.length();
	assert(x_length == 1);

	vec3 unit_vector_y = vec3(0, 1, 0);
	float y_length = unit_vector_y.length();
	assert(y_length == 1);

	vec3 unit_vector_z = vec3(0, 0, 1);
	float z_length = unit_vector_z.length();
	assert(z_length == 1);

	// unit_vector
	vec3 x_unit_vector = unit_vector(vec3(45, 0, 0));
	assert(x_unit_vector.x() == 1);
	assert(x_unit_vector.y() == 0);
	assert(x_unit_vector.z() == 0);

	// multiply_by_scalar
	vec3 scalar_multiple = multiply_by_scalar(vec3(2, 4, 6), 8);
	assert(scalar_multiple.x() == 16);
	assert(scalar_multiple.y() == 32);
	assert(scalar_multiple.z() == 48);

	// add_vectors
	vec3 vector_addition = add_vectors(vec3(1.2, -2.3, 3.4), vec3(1.2, -2.3, 3.4));
	assert(vector_addition.x() == (float)2.4);
	assert(vector_addition.y() == (float)-4.6);
	assert(vector_addition.z() == (float)6.8);

	vec3 three_vector_addition = add_vectors(vec3(1, -2, 3), vec3(1, -2, 3), vec3(1, -2, 3));
	assert(three_vector_addition.x() == (float)3);
	assert(three_vector_addition.y() == (float)-6);
	assert(three_vector_addition.z() == (float)9);

	// subtract_vectors
	vec3 vector_subtraction = subtract_vectors(vec3(1.2, -2.3, 3.4), vec3(-1.2, 2.3, -3.4));
	assert(vector_subtraction.x() == (float)2.4);
	assert(vector_subtraction.y() == (float)-4.6);
	assert(vector_subtraction.z() == (float)6.8);

	// dot_product
	float dot = dot_product(vec3(1, 2, 3), vec3(4, 5, 6));
	assert(dot == (float)32);

	// random_vec3
	for (int i = 0; i < 10; ++i)
	{
		vec3 random_vector = random_vec3(-45, 45);
		std::cout << "random_vector - x: " << random_vector.x() << " y: " << random_vector.y() << " z: " << random_vector.z() << "\n";
		assert(random_vector.x() < 45);
		assert(random_vector.x() > -45);
		assert(random_vector.y() < 45);
		assert(random_vector.y() > -45);
		assert(random_vector.z() < 45);
		assert(random_vector.z() > -45);
	}

	// random_in_unit_sphere
	for (int i = 0; i < 10; ++i)
	{
		vec3 random_vector_in_sphere = random_in_unit_sphere();
		std::cout << "random_vector_in_sphere - x: " << random_vector_in_sphere.x() << " y: " << random_vector_in_sphere.y() << " z: " << random_vector_in_sphere.z() << "\n";
		assert(random_vector_in_sphere.x() < 1);
		assert(random_vector_in_sphere.x() > -1);
		assert(random_vector_in_sphere.y() < 1);
		assert(random_vector_in_sphere.y() > -1);
		assert(random_vector_in_sphere.z() < 1);
		assert(random_vector_in_sphere.z() > -1);
		assert(random_vector_in_sphere.length_squared() < 1);
	}
}