#include "vec3.h"
#include <assert.h>
#include <iostream>

int main()
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
	vec3 vector_addition = add_two_vectors(vec3(1.2, -2.3, 3.4), vec3(1.2, -2.3, 3.4));
	assert(vector_addition.x() == (float)2.4);
	assert(vector_addition.y() == (float)-4.6);
	assert(vector_addition.z() == (float)6.8);

	vec3 three_vector_addition = add_three_vectors(vec3(1, -2, 3), vec3(1, -2, 3), vec3(1, -2, 3));
	assert(three_vector_addition.x() == (float)3);
	assert(three_vector_addition.y() == (float)-6);
	assert(three_vector_addition.z() == (float)9);

	// subtract_vectors
	vec3 vector_subtraction = subtract_vectors(vec3(1.2, -2.3, 3.4), vec3(-1.2, 2.3, -3.4));
	assert(vector_subtraction.x() == (float)2.4);
	assert(vector_subtraction.y() == (float)-4.6);
	assert(vector_subtraction.z() == (float)6.8);
}