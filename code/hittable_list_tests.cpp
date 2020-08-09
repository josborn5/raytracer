#include "hittable_list.h"
#include <assert.h>

class simple_hittable : public hittable
{
	public:
		simple_hittable(float hit_time) : hit_time(hit_time) {}

		virtual bool hit(const ray& r, float t_min, float t_max, hit_record& hit) const override;

	public:
		float hit_time;
};

bool simple_hittable::hit(const ray& r, float t_min, float t_max, hit_record& hit) const
{
	if (hit_time > t_min & hit_time < t_max)
	{
		hit.time = hit_time;
		return true;
	}
	return false;
}

void run_hittable_list_tests()
{
	hittable_list list;
	simple_hittable hit_at_one = simple_hittable(1.0f);
	simple_hittable hit_at_two = simple_hittable(2.0f);
	list.add(std::make_shared<simple_hittable>(hit_at_two));
	list.add(std::make_shared<simple_hittable>(hit_at_one));

	vec3 arbitrary_vector = vec3(0.0f, 0.0f, 0.0f);
	ray arbitrary_ray = ray(arbitrary_vector, arbitrary_vector);

	hit_record hit;
	bool result;

	// returns hit for first object when both in time range
	hit = {};
	result = list.hit(arbitrary_ray, 0.0f, 10.0f, hit);
	assert(result == true);
	assert(hit.time == 1.0f);

	// returns hit for second object when it is only one in the time range
	hit = {};
	result = list.hit(arbitrary_ray, 1.5f, 10.0f, hit);
	assert(result == true);
	assert(hit.time == 2.0f);

	// returns no hit when no objects are in time range
	hit = {};
	result = list.hit(arbitrary_ray, 0.0f, 0.5f, hit);
	assert(result == false);
	assert(hit.time == 0.0f);
}