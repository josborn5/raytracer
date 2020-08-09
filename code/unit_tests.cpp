#include "vec3_tests.cpp"
#include "sphere_tests.cpp"
#include "hittable_list_tests.cpp"
#include <iostream>

int main()
{
	run_vec3_tests();
	std::cout << "vec3 tests passed.\n";

	run_sphere_tests();
	std::cout << "sphere tests passed.\n";

	run_hittable_list_tests();
	std::cout << "hittable list tests passed.\n";
}